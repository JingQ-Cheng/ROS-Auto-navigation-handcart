/*
 * Encoder.h
 *
 *  Created on: Jul 18, 2022
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_ENCODER_H_
#define INC_CUSTOM_H_ENCODER_H_

#include "custom_h/all_header.h"

typedef struct
{
	float Wheel_circumference;
	float Encoder_accuracy;

	float (*Encoder_PWMtoSpeed)(int Encoder_pulse);
	int (*Encoder_SpeedtoPWM)(float Speed);
}Encoder_t;

extern Encoder_t Encoder;

#endif /* INC_CUSTOM_H_ENCODER_H_ */
