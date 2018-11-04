/*
@file system_init.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Oct 9, 2018
This file is part of Ratatech 3019.

    Ratatech 3019 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ratatech 3019 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef SYSTEM_INIT_H_
#define SYSTEM_INIT_H_

#include "types.h"
#include "lcd16x2.h"
#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include "spi.h"
#include "timer.h"
#include "synthSettings.h"

void RCC_Clocks_Init(void);
void GPIO_Conf_Init(void);
void ButtonsInitEXTI(void);
void ADC_Conf_Init(void);
void USART_Conf_Init(void);
void DMA_Conf_Init(void);
void ratatech_init(void);
void init_rotary_encoder(void);


#endif /* SYSTEM_INIT_H_ */
