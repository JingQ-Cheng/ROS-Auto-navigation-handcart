/*
 * My_UART.h
 *
 *  Created on: May 22, 2022
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_MY_UART_H_
#define INC_CUSTOM_H_MY_UART_H_

#include "custom_h/all_header.h"

#define RPi_Tx_Lenght 20
#define RPi_Rx_Lenght 20

typedef struct
{
	uint8_t* Send_Buffer;					//发送缓存指针
	uint8_t* Receive_Buffer;				//接收缓存指针
	void(*Send_array)(uint8_t*,uint16_t);	//串口发送数组
	void (*SendString)(uint8_t*);          //串口发送字符串
}UART_t;

//typedef struct
//{
//	uint8_t* RPi_Tx_Buff;           //发送缓存指针
//	uint8_t* RPi_Rx_Buff;            //接收缓存指针
//	void (*RPI_Init)();
//	void (*RPi_Tx)(uint8_t *RPi_Rx_Buff);
//	void (*RPi_Rx)(uint8_t *RPi_Rx_Buff);
//}UART_t;



#endif /* INC_CUSTOM_H_MY_UART_H_ */
