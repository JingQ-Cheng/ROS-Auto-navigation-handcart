/*
 * Peripheral.h
 *
 *  Created on: May 22, 2022
 *      Author: 86157
 */

#ifndef INC_CUSTOM_H_DRIVER_INIT_H_
#define INC_CUSTOM_H_DRIVER_INIT_H_

typedef struct
{
	void (*Peripheral_Init)(void);
	void (*Peripheral_Stop)(void);
}Driver_Init_t;

extern Driver_Init_t Driver_Init;

void Peripheral_Init();
void Peripheral_Stop();

#endif /* INC_CUSTOM_H_DRIVER_INIT_H_ */
