/* Includes ------------------------------------------------------------------*/
#include "custom_h/all_header.h"
/*
 * KEY0：+
 * KEY1：-
 * KEY_up:切换P、I、D
 * */


/* Public variables-----------------------------------------------------------*/
//结构体定义

/*
	* @name   KEY_Detect
	* @brief  按键检测，低电平有效
	* 初始化方式：KEY_Detect(&KEY1, KEY1_GPIO_Port, KEY1_Pin,&Position_KP);
*/
void KEY_Scan(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == KEY_up_Pin)
	{
		pid_count++;
		if(pid_count == 3)
			{pid_count =0;}
	}
	if(GPIO_Pin == KEY0_Pin)
	{
		pid[pid_count] = pid[pid_count]+0.1;
	};
	if(GPIO_Pin == KEY1_Pin)
	{
		pid[pid_count]= pid[pid_count]-0.1;
	};

}


/********************************************************
  End Of File
********************************************************/
