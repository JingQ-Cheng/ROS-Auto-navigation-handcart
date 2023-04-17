/*
 * Peripheral.c
 *
 *  Created on: May 22, 2022
 *      Author: 86157
 */

/*所有驱动初始化*/

#include "custom_h/all_header.h"
Driver_Init_t Driver_Init =
{
	Peripheral_Init,
	Peripheral_Stop
};

void Peripheral_Init()
{

//	HAL_UART_Receive_DMA(&huart3,Buf_Rx,20); //串口3开启DMA接收
	HAL_UARTEx_ReceiveToIdle_DMA(&huart6,Buf_Rx, 20);//开启串口空闲3中断DMA接收数据
//	FIFO_init(&FIFO,Buf_Rx,Rx_size);

	Motor.Motor_Start_Init();

}

void Peripheral_Stop()
{

}
