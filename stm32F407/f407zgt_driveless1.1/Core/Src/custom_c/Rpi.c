/*
	USART3：
		棕色线-PB10
		红色线-PB11
 */

#include "custom_h/all_header.h"

  //信息头尾帧
const unsigned char Message_Header = 0xB0;
const unsigned char Message_Ender = 0xA0;
  //车左右轮目标速度
float Speed_left_target = 0;
float Speed_right_target = 0;
char Steering_engine_Angle = 0;

unsigned char Buf_Tx[12]; //发送缓存区 buff[0]-buff[9]
unsigned char Buf_Rx[Rx_size]; //信息头（1位）,左轮线速度（4位）,右轮线速度（4位）,舵机角度（1位）,信息尾（1位）,CRC(2位) buff[0]-buff[12]

//uint8_t RXflag = 0;

union floatData//union的作用是实现char数组和float之间的转换
{
     float float_dat;
     unsigned char byte_data[4];
}Speed_x_write,Speed_w_write,Speed_left_receive,Speed_right_receive;

void Read_Speed()
{

	uint8_t Index = 0;
	uint8_t* pBuf_Rx = Buf_Rx;
	for(int i = 0;i<Rx_size;i++)
	{
		if(Index ==0)
		{
			if(*(pBuf_Rx+i) != Message_Header)
				continue;
		}
		*(pBuf_Rx+Index) = *(pBuf_Rx+i);
		if(Index == Protocol_length)
		{
			break;
		}
		Index++;
	}

//	CRC_16.CRC_Value   =  CRC_16.CRC_Check(Buf_Rx,Protocol_length-2); //计算CRC值
//	CRC_16.CRC_H       = (uint8_t)(CRC_16.CRC_Value >> 8);
//	CRC_16.CRC_L       = (uint8_t)CRC_16.CRC_Value;
//
//	//校验CRC-16
//	if(((*(pBuf_Rx+12) == CRC_16.CRC_L) && (*(pBuf_Rx+13) == CRC_16.CRC_H))
//			||
//		  ((*(pBuf_Rx+12) == CRC_16.CRC_H) && (*(pBuf_Rx+13) == CRC_16.CRC_L)))
//	{
		for(int j=0;j<4;j++)
		{
			Speed_left_receive.byte_data[j] = Buf_Rx[1+j];
		}
		for(int j=0;j<4;j++)
		{
			Speed_right_receive.byte_data[j] = Buf_Rx[5+j];
		}
		//获取左右轮目标速度
		Speed_right_target = Speed_right_receive.float_dat;//接收 目标值
		Speed_left_target = Speed_left_receive.float_dat;
		Steering_engine_Angle = Buf_Rx[9];                    //获取舵机角度
//		for(int j=0;j<10;j++){
//				  printf("RXbuf[%d]: %x \r\n",j,Buf_Tx[j]); //打印buf内容需要用16进制才能正常显示
//				}
//	}//CRC
	memset(Buf_Rx,0,sizeof(Buf_Rx));
}

//void Read_Speed()
//{
//
//	uint8_t Index = 0;
//	for(int i = 0;i<Rx_size;i++)
//	{
//		if(Index ==0)
//		{
//			if(Buf_Rx[i] != Message_Header)
//				continue;
//		}
//		Buf_Rx[Index] = Buf_Rx[i];
//		if(Index == 12)
//			break;
//		Index++;
//	}
//
//	for(int j=0;j<4;j++)
//	{
//		Speed_left_receive.byte_data[j] = Buf_Rx[1+j];
//	}
//	for(int j=0;j<4;j++)
//	{
//		Speed_right_receive.byte_data[j] = Buf_Rx[5+j];
//	}
//	//获取左右轮目标速度
//	Speed_right_target = Speed_right_receive.float_dat;//接收 目标值
//	Speed_left_target = Speed_left_receive.float_dat;
//	Steering_engine_Angle = Buf_Rx[9];                    //获取舵机角度
//	for(int j=0;j<10;j++){
//			  printf("RXbuf[%d]: %x \r\n",j,Buf_Tx[j]); //打印buf内容需要用16进制才能正常显示
//			}
//	memset(Buf_Rx,0,sizeof(Buf_Rx));
//}

//接收决策层的控制指令，读取后轮线速度，舵机角度

//void Read_Speed()
//{
////	FIFO_read(&FIFO,Buf_Rx,12);
//    //此处应有读取Buf_Rx的函数！
////	HAL_UART_Receive_DMA(&huart3,Buf_Rx,20);
////	printf("\r\n receive Data begin\r\n");
//
////	HAL_Delay(10);
//
////计算CRC-16
//CRC_16.CRC_Value   =  CRC_16.CRC_Check(Buf_Rx,10); //计算CRC值
//CRC_16.CRC_H       = (uint8_t)(CRC_16.CRC_Value >> 8);
//CRC_16.CRC_L       = (uint8_t)CRC_16.CRC_Value;
//
//	for(int i=0;i<12;i++)
//	{
//		if((Buf_Rx[i]==Message_Header)&&(Buf_Rx[i+10]==Message_Ender))
//		{
//			// 计算CRC-16
//			CRC_16.CRC_Value = CRC_16.CRC_Check(&Buf_Rx[i], 11); // 计算CRC值
//			CRC_16.CRC_H = (uint8_t)(CRC_16.CRC_Value >> 8);
//			CRC_16.CRC_L = (uint8_t)CRC_16.CRC_Value;
//
//			 // 校验CRC-16
//			if (((Buf_Rx[i + 11] == CRC_16.CRC_L) && (Buf_Rx[i + 12] == CRC_16.CRC_H))
//											||
//				((Buf_Rx[i + 11] == CRC_16.CRC_H) && (Buf_Rx[i + 12] == CRC_16.CRC_L)))
//			{
//				for(int j=0;j<4;j++)
//				{
//					Speed_left_receive.byte_data[j] = Buf_Rx[i+j+1];
//				}
//				for(int j=0;j<4;j++)
//				{
//					Speed_right_receive.byte_data[j] = Buf_Rx[i+j+5];
//				}
//				 //获取左右轮目标速度
//				Speed_right_target = Speed_right_receive.float_dat;//接收 目标值
//				Speed_left_target = Speed_left_receive.float_dat;
//				Steering_engine_Angle = Buf_Rx[i+9];                    //获取舵机角度
////				printf("\r\nRx Data\r\n");
//	//			printf("\r\nSpeed_right_target:%f\r\nSpeed_left_target:%f\r\nSteering_engine_Angle:%d\r\n",Speed_right_target,Speed_left_target,Steering_engine_Angle);
//				 //HAL_UART_Transmit_DMA(&huart1,Buf_Rx,20);
//				}
//			}
//	//	else
//	//	{
//	//		printf("CRC error");
//	//		Speed_right_target = 0;
//	//		Speed_left_target = 0;
//	//	}
//	//
//	//	HAL_UART_DMAStop(&huart3);
////		memset(Buf_Rx,0,sizeof(Buf_Rx));
//	}
//	for(int j=0;j<Rx_size;j++){
//		   printf("RXbuf[%d]: %x \r\n",j,Buf_Tx[j]); //打印buf内容需要用16进制才能正常显示
//		}
//}

 /*发送给树莓派的变量定义*/
float Wheel_Distance = 0.48;//两前轮轮距，待录入！
//传入编码器读取后左右轮速度，并计算出直行速度Vx，转弯线速度Vz并上传决策层
void Write_Speed(float Speed_right_send,float Speed_left_send)//传入实际值
{
	int i = 0;
    float Speed_x = 0;
    float Speed_z = 0;
	Speed_x = (Speed_right_send + Speed_left_send)/2;
	Speed_z = (Speed_left_send - Speed_right_send)/Wheel_Distance;//运动学解算得到公式
//      printf("\r\nSend Data\r\n");
//      printf("\r\nSpeed_x:%f\r\nSpeed_z:%f\r\n",Speed_x,Speed_z);

      //计算CRC-16
	CRC_16.CRC_Value   =  CRC_16.CRC_Check(Buf_Tx,9); //计算CRC值
	CRC_16.CRC_H       = (uint8_t)(CRC_16.CRC_Value >> 8);
	CRC_16.CRC_L       = (uint8_t)CRC_16.CRC_Value;
	Buf_Tx[0] = 0xB0;//header
    Buf_Tx[9] = 0XA0;//ender;
    Buf_Tx[10] = CRC_16.CRC_H ;
    Buf_Tx[11] = CRC_16.CRC_L;
    Speed_x_write.float_dat = Speed_x;//线速度
    Speed_w_write.float_dat = Speed_z;//角速度
//      printf("\r\nSpeed_x_write.float_dat:%f\r\n",Speed_x_write.float_dat);
//      printf("Speed_w_write.float_dat:%f\r\n",Speed_w_write.float_dat);

    for(i=0;i<4;i++)
    {
      	Buf_Tx[i+1] = Speed_x_write.byte_data[i];
     }
	for(i=0;i<4;i++)
    {
		Buf_Tx[i+5] = Speed_w_write.byte_data[i];
     }
/*      for(int j=0;j<20;j++){
    	  printf("TXbuf[%d]: %x \r\n",j,Buf_Tx[j]); //打印buf内容需要用16进制才能正常显示
      }*/
      //此处写发送buf_TX函数！
    HAL_UART_Transmit_DMA(&huart6,Buf_Tx,12);

}
