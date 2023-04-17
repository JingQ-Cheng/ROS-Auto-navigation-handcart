/*
 * fifo_test.h
 *
 *  Created on: 2023年3月19日
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_FIFO_TEST_H_
#define INC_CUSTOM_H_FIFO_TEST_H_

#include "custom_h/all_header.h"

//#define fifo_size 20

typedef struct
{
	uint8_t* pHeader;       //FIFO缓冲区头地址
	uint8_t* pTail;	     	//FIFO缓冲区尾地址

	uint8_t* pVHeader;       //已使用缓冲区头地址
	uint8_t* pVTail;	    //已使用缓冲区尾地址

	uint8_t Occupied_len; 	//FIFO已占用长度

//    uint8_t FIFO_buff[fifo_size];     //缓存区
}FIFO_t;
extern FIFO_t FIFO;
extern void FIFO_init(FIFO_t *FIFO,uint8_t* rxbuff,uint8_t fifo_size);
extern void FIFO_read(FIFO_t *FIFO,uint8_t* rxbuff,uint8_t len);
extern void FIFO_write(FIFO_t *FIFO,uint8_t* txbuff,uint8_t len,uint8_t fifo_size);
#endif /* INC_CUSTOM_H_FIFO_TEST_H_ */
