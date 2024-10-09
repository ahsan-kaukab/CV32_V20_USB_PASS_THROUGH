#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <mutex>
#include <sstream>
#include <dirent.h>

std::mutex inputDevicesMutex;
std::ofstream outputFile("output.txt");  // Open the output file once at the start

// Function to print raw data in hexadecimal format to console and file
void PrintRawDataHex(const uint8_t* data, size_t size) {
    std::lock_guard<std::mutex> lock(inputDevicesMutex);
    std::ostringstream hexStream;
    hexStream << "Raw HID Data (Hex): ";
    for (size_t i = 0; i < size; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    hexStream << std::dec << std::endl;
    std::cout << hexStream.str();
    outputFile << hexStream.str();
}

// Function to open input devices
std::vector<int> OpenInputDevices() {
    std::vector<int> devices;
    DIR* dir = opendir("/dev/input");
    struct dirent* entry;

    if (dir == nullptr) {
        std::cerr << "Failed to open /dev/input directory.\n";
        return devices;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (strncmp(entry->d_name, "event", 5) == 0) {
            std::string path = "/dev/input/" + std::string(entry->d_name);
            int fd = open(path.c_str(), O_RDONLY | O_NONBLOCK);
            if (fd != -1) {
                devices.push_back(fd);
            }
        }
    }
    closedir(dir);
    return devices;
}

// Process raw input data from keyboard and mouse
void ProcessRawInput(int fd) {
    struct input_event ev[64];
    int bytesRead = read(fd, ev, sizeof(ev));

    if (bytesRead < (int)sizeof(struct input_event)) {
        return; // No complete event read
    }

    for (int i = 0; i < bytesRead / sizeof(struct input_event); ++i) {
        if (ev[i].type == EV_KEY) {
            std::lock_guard<std::mutex> lock(inputDevicesMutex);
            std::ostringstream keyboardStream;
            keyboardStream << "Keyboard Event: "
                           << "Keycode = " << ev[i].code
                           << ", Value = " << ev[i].value << std::endl;
            std::cout << keyboardStream.str();
            outputFile << keyboardStream.str();
        } else if (ev[i].type == EV_REL || ev[i].type == EV_ABS) {
            std::lock_guard<std::mutex> lock(inputDevicesMutex);
            std::ostringstream mouseStream;
            if (ev[i].type == EV_REL) {
                mouseStream << "Mouse Movement: "
                            << "X = " << (ev[i].code == REL_X ? ev[i].value : 0)
                            << ", Y = " << (ev[i].code == REL_Y ? ev[i].value : 0)
                            << std::endl;
            }
            std::cout << mouseStream.str();
            outputFile << mouseStream.str();
        }
    }
}

int main() {
    // Check if the output file opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file.\n";
        return -1;
    }

    // Open input devices (keyboard and mouse)
    std::vector<int> inputDevices = OpenInputDevices();
    if (inputDevices.empty()) {
        std::cerr << "No input devices found.\n";
        return -1;
    }

    std::cout << "Monitoring mouse and keyboard inputs. Press Ctrl+C to exit.\n";
    while (true) {
        for (int fd : inputDevices) {
            ProcessRawInput(fd);
        }
        usleep(10000); // Sleep for 10ms to reduce CPU usage
    }

    // Close the output file before exiting
    outputFile.close();
    for (int fd : inputDevices) {
        close(fd); // Close input device file descriptors
    }
    return 0;
}
