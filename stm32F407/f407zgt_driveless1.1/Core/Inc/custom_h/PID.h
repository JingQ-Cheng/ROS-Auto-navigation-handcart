/*
 * PID.h
 *
 *  Created on: Jun 8, 2022
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_PID_H_
#define INC_CUSTOM_H_PID_H_

#include "custom_h/all_header.h"

extern float pid[3];

extern int dsp_PID(float position,float target);

int Position_PID(int position,int target);
float Position_PIDspeed(float position,float target);

int FeedforwardController(float target_in);

extern uint8_t pid_count;

//extern float pid[3];
#endif /* INC_CUSTOM_H_PID_H_ */
