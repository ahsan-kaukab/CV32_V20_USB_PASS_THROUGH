#define HID_REPORT_SIZE   8   // Example HID report size
#define ACTIVITY_FLAG_SIZE 1  // Size of the activity flag (1 byte)
#define BUFFER_SIZE       128 // Define buffer size for your application

uint8_t Com_Buf[BUFFER_SIZE]; // Buffer for incoming data from USB-1
uint8_t forward_data[HID_REPORT_SIZE + ACTIVITY_FLAG_SIZE]; // Data to send on USB-2

RingBuffer_Comm_t RingBuffer_Comm;

int main(void)
{
    /* Initialize system configuration */
    Delay_Init();
    USART_Printf_Init(9600);
    DUG_PRINTF("SystemClk:%d\r\n", SystemCoreClock);
    DUG_PRINTF("USBFS HOST KM Test\r\n");

    /* Initialize TIM3 */
    TIM3_Init(9, SystemCoreClock / 10000 - 1);
    DUG_PRINTF("TIM3 Init OK!\r\n");

    /* Initialize USBFS host */
#if DEF_USBFS_PORT_EN
    DUG_PRINTF("USBFS Host Init\r\n");
    USBFS_RCC_Init();
    USBFS_Host_Init(ENABLE);
    memset(&RootHubDev.bStatus, 0, sizeof(ROOT_HUB_DEVICE));
    memset(&HostCtl[DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL].InterfaceNum, 0, sizeof(HOST_CTL));
#endif

    /* Initialize USB-2 (device mode) */
    USBFS_Device_Init(ENABLE);
    NVIC_EnableIRQ(USBHD_IRQn);

    /* Initialize RingBuffer */
    Var_Init();

    while (1)
    {
        /* Poll USB-1 for incoming HID data */
        USBH_MainDeal();
        
        /* Simulate receiving data from USB-1 (host mode) */
        if (New_USB1_Data_Available()) // Replace with actual condition
        {
            // Assuming data is stored in Com_Buf
            for (int i = 0; i < HID_REPORT_SIZE; i++)
            {
                Com_Buf[i] = Get_USB1_Data(); // Replace with actual function
            }

            // Add data to ring buffer for forwarding to USB-2
            Add_To_RingBuffer(Com_Buf, HID_REPORT_SIZE);
        }

        // Process data and send over USB-2
        Process_RingBuffer_To_USB2();
    }
}

/* Function to add data to the ring buffer */
void Add_To_RingBuffer(uint8_t *data, uint16_t len)
{
    if (RingBuffer_Comm.RemainPack < DEF_Ring_Buffer_Max_Blks)
    {
        memcpy(&RingBuffer_Comm.Data[RingBuffer_Comm.LoadPtr], data, len);
        RingBuffer_Comm.PackLen[RingBuffer_Comm.LoadPtr] = len;
        RingBuffer_Comm.LoadPtr++;
        if (RingBuffer_Comm.LoadPtr == DEF_Ring_Buffer_Max_Blks)
        {
            RingBuffer_Comm.LoadPtr = 0;
        }
        RingBuffer_Comm.RemainPack++;
    }
    else
    {
        DUG_PRINTF("Ring Buffer Full, data lost\r\n");
    }
}

/* Function to process ring buffer and send data over USB-2 */
void Process_RingBuffer_To_USB2()
{
    uint8_t ret;
    
    if (RingBuffer_Comm.RemainPack > 0)
    {
        // Add activity flag (1 byte) before sending
        forward_data[0] = 1; // Activity flag set to 1

        // Copy data from ring buffer
        memcpy(&forward_data[1], &RingBuffer_Comm.Data[RingBuffer_Comm.DealPtr], RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr]);

        // Send data over USB-2
        ret = USBFS_Endp_DataUp(DEF_UEP2, forward_data, RingBuffer_Comm.PackLen[RingBuffer_Comm.DealPtr] + 1, DEF_UEP_DMA_LOAD);
        
        if (ret == 0) // Transmission successful
        {
            NVIC_DisableIRQ(USBHD_IRQn);
            RingBuffer_Comm.RemainPack--;
            RingBuffer_Comm.DealPtr++;
            if (RingBuffer_Comm.DealPtr == DEF_Ring_Buffer_Max_Blks)
            {
                RingBuffer_Comm.DealPtr = 0;
            }
            NVIC_EnableIRQ(USBHD_IRQn);
        }
    }
}
