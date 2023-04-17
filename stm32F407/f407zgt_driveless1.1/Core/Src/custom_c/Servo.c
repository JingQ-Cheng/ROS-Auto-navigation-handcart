/*
 * Servo.c
 *
 *  Created on: 2022年6月13日
 *      Author: 86157
 */

#include "custom_h/all_header.h"

void Servo_Control(uint16_t angle)
{
   float temp;
   temp =(1.0 / 9.0) * angle + 5.0;//
   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint16_t )temp);
}

