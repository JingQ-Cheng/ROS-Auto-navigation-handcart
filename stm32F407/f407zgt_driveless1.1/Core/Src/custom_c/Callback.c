/*
 * Callback.c
 *
 *  Created on: Jun 4, 2022
 *      Author: 86157
 */
#include "custom_h/all_header.h"



/* USER CODE BEGIN 4 */


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	KEY_Scan(GPIO_Pin);//按键控制
}

/* UASRT callback function
 * 串口回调函数
 * */

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{//Size为接收到的数据大小
	if(huart->Instance == USART6)
	{
	    HAL_UART_DMAStop(&huart6);//关闭是为了重新设置发送多少数据，不关闭会造成数据错误

	    Read_Speed();//接收

		HAL_UARTEx_ReceiveToIdle_DMA(&huart6,Buf_Rx, 50);//继续开启空闲中断DMA发送
	}
}


//void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
//{
//
//}
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//
//}

/*	Interrupt callback function
 * 中断回调函数
 *
 * Moto processing function
 * 电机处理函数
 * */
//int Position=2000,Target_Position=5000;
//unsigned int MotorSpeed;  // 电机当前速度数值，从编码器中获取
//int MotorOutput;		  // 电机输出
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//printf("\r\ncallback now!\r\n");
//    static unsigned char i = 0;

    if (htim == (&htim2))
    {

    	Motor.Encoder_pulse_Left = __HAL_TIM_GET_COUNTER(&htim3);//左轮用TIM3 PA6 PA7
    	Motor.Encoder_pulse_Right = __HAL_TIM_GET_COUNTER(&htim4);//右轮用TIM4 PB6 PB7

    	Motor.WheelSpeed_Left  = Encoder.Encoder_PWMtoSpeed(Motor.Encoder_pulse_Left);//PWM转换速度
    	Motor.WheelSpeed_Right  = Encoder.Encoder_PWMtoSpeed(Motor.Encoder_pulse_Right);

    	__HAL_TIM_SET_COUNTER(&htim3,0);
    	__HAL_TIM_SET_COUNTER(&htim4,0);  // 计数器清零


    }
}
//void PWM_Limit(void)
//{
//	  //int Amplitude=7290;    //===PWM满幅是8400 限制在8390
//	  if(MotorOutput<-7290) MotorOutput=-7290;
//	  if(MotorOutput>7290)  MotorOutput=7290;
//
//}

