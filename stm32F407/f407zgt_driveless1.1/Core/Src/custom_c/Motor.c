/*
 * Motor.c
 *
 *  Created on: May 22, 2022
 *      Author: 86157
 *
 *      左轮PWM PA8 PA9
 *      右轮PWM PA10 PA11
 *      左编码器用TIM3 PA6 PA7
 *      右编码器用TIM4 PB6 PB7
 */

#include "custom_h/all_header.h"

void Motor_Start_Init();
void Motor_PWM_Left (uint16_t Left,uint16_t Right);
void Motor_PWM_Right (uint16_t Left,uint16_t Right);
void Motor_PWM (uint16_t Left,uint16_t Right);

void Motor_Start_Stop();
static void Motor_Solve();
void Motor_ouput();

Motor_t Motor =
{
	.WheelSpeed_Left = 0,.WheelSpeed_Right = 0, //这里默认情况下必须设置为0
	.MotorOutput_Left = 0,.MotorOutput_Right = 0,
	.PWMOutput_Left=0,.PWMOutput_Right=0,// 电机输出
	.Encoder_pulse_Left = 0,.Encoder_pulse_Right = 0,
	.Amplitude = 6000, //限制幅度
	.Motor_flag = 0,

	Motor_Start_Init,
	Motor_PWM_Left,
	Motor_PWM_Right,
	Motor_Start_Stop,
	Motor_Solve,
	Motor_ouput
};

void Motor_Start_Init()//Motor initialization
{

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1); // enable Encoder_A
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2); // enable Encoder_A
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1); // enable Encoder_B
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2); // enable Encoder_B
	HAL_TIM_Base_Start_IT(&htim2);                // enable TIM2_interrupt

}

void Motor_Start_Stop()
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}
void Motor_PWM_Left (uint16_t Left,uint16_t Right)//PWM set
{
	TIM1->CCR1 = Left; //左轮PA8 PA9
	TIM1->CCR2 = Right;
}
void Motor_PWM_Right (uint16_t Left,uint16_t Right)//PWM set
{
	TIM1->CCR3 = Left; //右轮PA10 PA11
	TIM1->CCR4 = Right;
}


int Motor_PWMlimit(int pwm)
{
	if(pwm > 100)
	{
		pwm = 100;
	}
	if(pwm < (-100))
	{
		pwm = -100;
	}
	else
		pwm = pwm;
	return pwm;
}

static void Motor_Solve()
{

		/*速度转换为占空比*/
		Motor.MotorOutput_Left = Encoder.Encoder_SpeedtoPWM(Speed_left_target);
		Motor.MotorOutput_Right = Encoder.Encoder_SpeedtoPWM(Speed_right_target);

//		Motor.PWMOutput_Left = Motor.MotorOutput_Left;//开环
//		Motor.PWMOutput_Right = Motor.MotorOutput_Right;

		Motor.PWMOutput_Left = Position_PID(Motor.Encoder_pulse_Left, Motor.MotorOutput_Left);
		Motor.PWMOutput_Right = Position_PID(Motor.Encoder_pulse_Right,Motor.MotorOutput_Right);

//		Motor.PWMOutput_Left = dsp_PID(Motor.Encoder_pulse_Left, Motor.MotorOutput_Left);
//		Motor.PWMOutput_Right = dsp_PID(Motor.Encoder_pulse_Right,Motor.MotorOutput_Right);

		//前馈1
//		float FL_err = FeedforwardController(Motor.MotorOutput_Left);
//		float FR_err = FeedforwardController(Motor.MotorOutput_Right);
//		Motor.PWMOutput_Left = FL_err + dsp_PID(Motor.Encoder_pulse_Left, Motor.MotorOutput_Left);
//		Motor.PWMOutput_Right = FR_err + dsp_PID(Motor.Encoder_pulse_Right,Motor.MotorOutput_Right);

		//前馈2
//		float FL_err = FeedforwardController(Motor.MotorOutput_Left);
//		float FR_err = FeedforwardController(Motor.MotorOutput_Right);
//		Motor.PWMOutput_Left = FL_err + Position_PID(Motor.Encoder_pulse_Left, Motor.MotorOutput_Left);
//		Motor.PWMOutput_Right = FR_err + Position_PID(Motor.Encoder_pulse_Right,Motor.MotorOutput_Right);
//
		Motor.Motor_ouput(Motor.PWMOutput_Left,Motor.PWMOutput_Right);

}

void Motor_ouput(int Output_Left,int Output_Right )
{
	if(Output_Left >= 0)//正转
	{
		Motor.Motor_PWM_Left(Output_Left,0);
	}
	else
	{
		Motor.Motor_PWM_Left(0,-Output_Left);
	}
	if(Output_Right >= 0)//正转
	{
		Motor.Motor_PWM_Right(Output_Right,0);
	}
	else
	{
		Motor.Motor_PWM_Right(0,-Output_Right);
	}
//	if(Output_Left < 0)//反转
//	{
//		//调参
//		Motor.Motor_PWM_Left(0,Output_Left);
//
////		Motor.Motor_PWM_Left(0,-Output_Left);//开环正常
//	}
//	else//正转
//	{
//		Motor.Motor_PWM_Left(Output_Left,0);
//
//		//Motor.Motor_PWM_Left(Motor.MotorOutput_Left,0);//开环正常
//	}
//	if(Output_Right < 0)
//	{
//		Motor.Motor_PWM_Right(0,Output_Right);//调参
//
////		Motor.Motor_PWM_Right(0,-Output_Right);//开环正常
//	}
//	else
//	{
//		Motor.Motor_PWM_Right(Output_Right,0);
////		Motor.Motor_PWM_Right(Motor.MotorOutput_Right,0);//开环正常
//	}

}
