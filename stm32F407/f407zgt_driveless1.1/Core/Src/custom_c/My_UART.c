/*
 * My_UART.c
 *
 *  Created on: May 22, 2022
 *      Author: 86157
 */

#include "custom_h/all_header.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart5 , (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
