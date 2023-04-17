/*
 * Motor.h
 *
 *  Created on: May 22, 2022
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_MOTOR_H_
#define INC_CUSTOM_H_MOTOR_H_

#include "custom_h/all_header.h"

void Motor_ouput();

typedef struct
{
	float WheelSpeed_Left,WheelSpeed_Right;// 左右电机当前速度数值，从编码器中获取
	int MotorOutput_Left,MotorOutput_Right;// 电机输出
	int PWMOutput_Left,PWMOutput_Right;// PWM输出
	short Encoder_pulse_Left,Encoder_pulse_Right; //编码器的脉冲计数

	int Amplitude;//限制幅度
	uint8_t Motor_flag;

	void (* Motor_Start_Init)();
	void (* Motor_PWM_Left)(uint16_t Left,uint16_t Right);
	void (* Motor_PWM_Right)(uint16_t Left,uint16_t Right);
	void (*Motor_Start_Stop)();
	void (*Motor_Solve)();
	void (*Motor_ouput)();
}Motor_t;

int Motor_PWMlimit(int pwm);

extern Motor_t Motor;

#endif /* INC_CUSTOM_H_MOTOR_H_ */
