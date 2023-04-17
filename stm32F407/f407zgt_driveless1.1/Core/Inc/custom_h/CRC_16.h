#ifndef __CRC_16_H__
#define __CRC_16_H__
#include "custom_h/all_header.h"

//定义结构体类型
typedef struct
{
	uint16_t CRC_Value; //CRC校验值
	uint8_t  CRC_H;     //高位
	uint8_t  CRC_L;     //地位
	uint16_t (*CRC_Check)(uint8_t*,uint8_t);  //CRC校验
} CRC_16_t;

/* extern variables-----------------------------------------------------------*/
extern CRC_16_t CRC_16;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
