#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <mutex>

RAWINPUTDEVICE Rid[2];  // Array to register mouse and keyboard devices
std::mutex inputDevicesMutex;
std::ofstream outputFile("output.txt");  // Open the output file once at the start

// Register mouse and keyboard devices for raw input
void RegisterDevices(HWND hwnd) {
    // Register mouse (Usage Page 0x01, Usage 0x02)
    Rid[0].usUsagePage = 0x01;
    Rid[0].usUsage = 0x02;  // Mouse
    Rid[0].dwFlags = RIDEV_INPUTSINK;  // Capture input even when the window is not in focus
    Rid[0].hwndTarget = hwnd;  // Set to the window handle

    // Register keyboard (Usage Page 0x01, Usage 0x06)
    Rid[1].usUsagePage = 0x01;
    Rid[1].usUsage = 0x06;  // Keyboard
    Rid[1].dwFlags = RIDEV_INPUTSINK;  // Capture input even when the window is not in focus
    Rid[1].hwndTarget = hwnd;  // Set to the window handle

    if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
        DWORD errorCode = GetLastError();
        std::cerr << "Failed to register raw input device. Error code: " << errorCode << "\n";
    } else {
        std::cout << "Devices registered successfully.\n";
    }
}

// Function to print raw data in hexadecimal format to console and file
void PrintRawDataHex(const BYTE* data, UINT size) {
    std::lock_guard<std::mutex> lock(inputDevicesMutex);
    std::ostringstream hexStream;
    hexStream << "Raw HID Data (Hex): ";
    for (UINT i = 0; i < size; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    hexStream << std::dec << std::endl;
    std::cout << hexStream.str();
    outputFile << hexStream.str();
}

// Process raw input data from mouse and keyboard
void ProcessRawInput(LPARAM lParam) {
    UINT dwSize;
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
    LPBYTE lpb = new BYTE[dwSize];
    if (lpb == NULL) {
        return;
    }

    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
        std::cerr << "GetRawInputData does not return correct size!\n";
        delete[] lpb;
        return;
    }

    RAWINPUT* raw = (RAWINPUT*)lpb;

    // Print the raw HID data
    PrintRawDataHex(lpb, dwSize);

    // Handle mouse input
    if (raw->header.dwType == RIM_TYPEMOUSE) {
        std::lock_guard<std::mutex> lock(inputDevicesMutex);
        std::ostringstream mouseStream;
        mouseStream << "Mouse Movement: X = " << raw->data.mouse.lLastX
                    << ", Y = " << raw->data.mouse.lLastY << std::endl;
        if (raw->data.mouse.usButtonFlags) {
            mouseStream << "Mouse Button Event Detected: Flags = " << raw->data.mouse.usButtonFlags << std::endl;
        }
        std::cout << mouseStream.str();
        outputFile << mouseStream.str();
    }
    // Handle keyboard input
    else if (raw->header.dwType == RIM_TYPEKEYBOARD) {
        std::lock_guard<std::mutex> lock(inputDevicesMutex);
        std::ostringstream keyboardStream;
        keyboardStream << "Keyboard Key Pressed: Keycode = " << raw->data.keyboard.VKey << std::endl;
        std::cout << keyboardStream.str();
        outputFile << keyboardStream.str();
    }

    delete[] lpb;  // Clean up allocated memory
}

// Window procedure to handle raw input messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_INPUT:
            ProcessRawInput(lParam);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    // Check if the output file opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file.\n";
        return -1;
    }

    // Create a dummy window to receive raw input messages
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "RawInputClass";

    if (!RegisterClass(&wc)) {
        std::cerr << "Failed to register window class.\n";
        return -1;
    }

    HWND hwnd = CreateWindowEx(
        0, "RawInputClass", "Raw Input Monitor",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        std::cerr << "Failed to create window.\n";
        return -1;
    }

    // Register the devices (mouse and keyboard) with the correct window handle
    RegisterDevices(hwnd);

    // Show the window (not visible but necessary for capturing input)
    ShowWindow(hwnd, SW_HIDE);

    // Main message loop
    MSG msg = { 0 };
    std::cout << "Monitoring mouse and keyboard inputs. Press Ctrl+C to exit.\n";
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Close the output file before exiting
    outputFile.close();
    return 0;
}
