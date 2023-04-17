/*
 * Callback.h
 *
 *  Created on: Jun 4, 2022
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_CALLBACK_H_
#define INC_CUSTOM_H_CALLBACK_H_

#include "custom_h/all_header.h"


extern int Position;
extern int Target_Position; //编码器的脉冲计数

void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);

/* USER CODE END 4 */


#endif /* INC_CUSTOM_H_CALLBACK_H_ */
