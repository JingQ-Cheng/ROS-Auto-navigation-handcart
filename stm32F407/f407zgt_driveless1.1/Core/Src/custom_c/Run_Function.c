/*
 * Run_Function.c
 *
 *  Created on: 2022年6月6日
 *      Author: 86157
 */
#include "custom_h/all_header.h"

void Read_Speed();
void Write_Speed(float Speed_right_send,float Speed_left_send);
void Run_Function();

void Print_Function(){
//	printf("\r\n Encoder_pulse_Left:%d \r\n",Motor.Encoder_pulse_Left);
//	printf("\r\n WheelSpeed_Left:%f\r\n",Motor.WheelSpeed_Left);
//	printf("\r\n Encoder_pulse_Right:%d \r\n",Motor.Encoder_pulse_Right);
//	printf("\r\n WheelSpeed_Right:%f\r\n",Motor.WheelSpeed_Right);
//
//	printf("\r\n MotorOutput_Left:%d\r\n",Motor.MotorOutput_Left);

	//图像调参
//	  printf("%d,%d,%d,%d,",
//			 Motor.Encoder_pulse_Left,//左轮当前值
//			Motor.Encoder_pulse_Right,//右轮当前值
//			Motor.MotorOutput_Left,//左轮目标值
//			Motor.MotorOutput_Right//右轮目标值
//			);
//	  printf("%f,%f,%f,%f,%f,%f,%f\r\n",pid[0],pid[1],pid[2],Speed_left_target,Speed_right_target,Motor.WheelSpeed_Left,Motor.WheelSpeed_Right);
//	  printf("%f,%f,%d,%d,",
//			Speed_left_target,//上层_L
//			Speed_right_target,//上层_R
//			Motor.PWMOutput_Left,//L_pwm
//			Motor.PWMOutput_Right);//R_pwm
	  printf("%f,%f,%f,",pid[0],pid[1],pid[2]);
	  printf("%ld,%ld,%ld,%ld,",TIM1->CCR1,TIM1->CCR2,TIM1->CCR3,TIM1->CCR4);
	  printf("%f,%f,",Speed_left_target,Speed_right_target);
	  printf("%f,%f\r\n",Motor.WheelSpeed_Left,Motor.WheelSpeed_Right);
}

void Run_Function()
{
	/*已改用串口空闲中断接收*/
	//Read_Speed();

	Motor.Motor_Solve();//解算输出
	HAL_Delay(10);

	Write_Speed(Motor.WheelSpeed_Left,Motor.WheelSpeed_Right);//发送
	HAL_Delay(1);



	Print_Function();//打印测试
	HAL_Delay(1);



}
