/*
 * Rpi.h
 *
 *  Created on: 2022年7月15日
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_RPI_H_
#define INC_CUSTOM_H_RPI_H_

#include "custom_h/all_header.h"
#define Protocol_length 11
#define Rx_size 20

extern float Speed_left_target;
extern float Speed_right_target;
extern unsigned char Buf_Rx[Rx_size];



extern void Read_Speed();
extern void Write_Speed(float Speed_right_send,float Speed_left_send);

#endif /* INC_CUSTOM_H_RPI_H_ */
