/********************************** (C) COPYRIGHT *******************************
 * File Name          : usbd_composite_km.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/20
 * Description        : USB keyboard and mouse processing.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
*******************************************************************************/


/*******************************************************************************/
/* Header Files */
#include "usbd_composite_km.h"

/*******************************************************************************/
/* Variable Definition */

volatile uint8_t  KB_LED_Cur_Status = 0x00; // Keyboard LED Current Result

/* USART */
volatile uint8_t  USART_Recv_Dat = 0x00;

/*******************************************************************************/
/* Interrupt Function Declaration */
void USART2_IRQHandler(void) __attribute__((naked));

/*********************************************************************
 * @fn      USART2_IRQHandler
 *
 * @brief   Wrapper function for USART2_IRQHandler_Real
 *
 * @return  none
 */
void USART2_IRQHandler( void )
{
    __asm volatile ("call USART2_IRQHandler_Real; mret");
}

/*********************************************************************
 * @fn      USART2_IRQHandler_Real
 *
 * @brief   This function handles USART2 global interrupt request.
 *
 * @return  none
 */
void USART2_IRQHandler_Real( void )
{
    if( USART_GetITStatus( USART2, USART_IT_RXNE) != RESET )
    {
        /* Save the key value received from USART2 */
        USART_Recv_Dat = USART_ReceiveData( USART2 ) & 0xFF;
    }
}


/*********************************************************************
 * @fn      MCU_Sleep_Wakeup_Operate
 *
 * @brief   Perform sleep operation
 *
 * @return  none
 */
void MCU_Sleep_Wakeup_Operate( void )
{
    EXTI_ClearFlag( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 );
    EXTI_ClearFlag( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 );

//    printf( "Sleep\r\n" );
    __WFE( );
    
    if( EXTI_GetFlagStatus( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 ) != RESET  )
    {
        EXTI_ClearFlag( EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15 );
        Resume(RESUME_INTERNAL);
    }
    else if( EXTI_GetFlagStatus( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 ) != RESET )
    {
        EXTI_ClearFlag( EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7 );
        Resume(RESUME_INTERNAL);
    }
//    printf( "Wake\r\n" );
}



