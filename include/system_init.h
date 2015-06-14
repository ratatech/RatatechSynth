/*
 * system_init.h
 *
 *  Created on: May 31, 2015
 *      Author: rata
 */

#ifndef INCLUDE_SYSTEM_INIT_H_
#define INCLUDE_SYSTEM_INIT_H_

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void SystemClock_Config(void);
void MX_GPIO_Init(void);


#endif /* INCLUDE_SYSTEM_INIT_H_ */
