/*
 * fifo_test.c
 *
 *  Created on: 2023年3月19日
 *      Author: 86157
 */
#include "custom_h/all_header.h"

//FIFO_t FIFO = {NULL};//初始化为0
FIFO_t FIFO = {NULL};//初始化为0
void FIFO_init(FIFO_t *FIFO,uint8_t* rxbuff,uint8_t fifo_size)
{
//	FIFO->FIFO_buff = rxbuff;
	FIFO->pHeader = FIFO->pVHeader = FIFO->pVTail = rxbuff;
	FIFO->pTail = FIFO->pHeader + fifo_size;

	FIFO->Occupied_len = 0;
}

void FIFO_read(FIFO_t *FIFO,uint8_t* rxbuff,uint8_t len)
{
	if(FIFO->Occupied_len == 0)//判读当前缓冲区是否已满
	{
		printf("fifo full");
	}
	if(len > (FIFO->Occupied_len) )//
	{
		len = FIFO->Occupied_len;
	}

	//判断剩余缓冲区是否足够
	if(FIFO->pVHeader + len > FIFO->pTail)
	{
		uint8_t len1 = (FIFO->pTail) - (FIFO->pVTail);
		uint8_t len2 = len - len1;

		memcpy(rxbuff,FIFO->pVHeader,len1);
		memcpy(rxbuff+len1,FIFO->pHeader,len2);

		FIFO->pVHeader = FIFO->pVHeader + len1 + len2;//更新已使用的缓冲区首地址
	}
	else
	{
		memcpy(rxbuff,FIFO->pVTail,len);
		FIFO->pVHeader = FIFO->pVHeader + len;//更新已使用的缓冲区首地址
	}
	FIFO->Occupied_len -= len;//更新已使用缓冲区长度
}

void FIFO_write(FIFO_t *FIFO,uint8_t* txbuff,uint8_t len,uint8_t fifo_size)
{
	if(FIFO->Occupied_len > fifo_size)//判读当前缓冲区是否已满
	{
		printf("len too long");
	}
	if(FIFO->pVTail + len > FIFO->pTail)
	{
		uint8_t len1 = (FIFO->pTail) - (FIFO->pVTail);
		uint8_t len2 = len - len1;
		memcpy(FIFO->pVTail,txbuff,len1);
		memcpy(FIFO->pHeader,txbuff + len1,len2);
		FIFO->pVTail = FIFO->pHeader + len2;
	}
	else
	{
		memcpy(FIFO->pVTail,txbuff,len);
		FIFO->pVTail += len;
	}

	//重新计算已使用的缓冲区头地址
	if(FIFO->Occupied_len +len > fifo_size)
	{
		int move_len = FIFO->Occupied_len +len - fifo_size;
		if(FIFO->pVHeader + move_len > FIFO->pTail)
		{
			int len1 = FIFO->pTail - FIFO->pVHeader;
			int len2 = move_len -len1;
			FIFO->pVHeader = FIFO->pHeader +len2;
		}
		else
		{
			FIFO->pVHeader = FIFO->pVHeader + move_len;
		}
		FIFO->Occupied_len += fifo_size;
	}
	else
	{
		FIFO->Occupied_len += len;
	}
}


