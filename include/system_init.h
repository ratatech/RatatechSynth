/*
 * system_init.h
 *
 *  Created on: May 31, 2015
 *      Author: rata
 */

#ifndef INCLUDE_SYSTEM_INIT_H_
#define INCLUDE_SYSTEM_INIT_H_

#include "ratatechSynth.h"
#include "types.h"


void RCC_Clocks_Init(void);
void GPIO_Conf_Init(void);
void ButtonsInitEXTI(void);
void ADC_Conf_Init(void);
void USART_Conf_Init(void);
void DMA_Conf_Init(uint16_t* ADCConvertedValue);
void ratatech_init(synth_params_t* synth_params);

#endif /* INCLUDE_SYSTEM_INIT_H_ */
