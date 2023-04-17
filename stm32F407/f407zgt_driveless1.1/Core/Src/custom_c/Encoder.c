/*
 * Encoder.c
 *
 *  Created on: Jul 18, 2022
 *      Author: 86157
 */

#include "custom_h/all_header.h"

float Encoder_PWMtoSpeed(int Encoder_pulse);
int Encoder_SpeedtoPWM(float Speed);

Encoder_t Encoder =
{
	.Wheel_circumference = 3.14*0.13,//轮子周长 Wheel_circumference
	.Encoder_accuracy = 4*13*30,//编码器精度= 编码器倍频数*编码器线数*电机减速比 Encoder_accuracy
	Encoder_PWMtoSpeed,
	Encoder_SpeedtoPWM
};

float Encoder_PWMtoSpeed(int Encoder_pulse)
{
	static float WheelSpeed;
	//static unsigned int Wheel_circumference = 3.14 * 0.13;
	//static unsigned int Encoder_accuracy = 4*13*30;
	WheelSpeed = (Encoder_pulse * 100 * Encoder.Wheel_circumference)/(Encoder.Encoder_accuracy);//求轮子速度

	return WheelSpeed;
}

int Encoder_SpeedtoPWM(float Speed)
{
	static int MotorPWM;
	MotorPWM = Speed/100/Encoder.Wheel_circumference*Encoder.Encoder_accuracy;

	return MotorPWM;
}

