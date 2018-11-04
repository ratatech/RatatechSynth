/*
@file mux.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jul 1, 2017
This file is part of Ratatech 3019

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

#include "macro_mux.h"


/**
 * Configure multiplexers input port and pins
 */
void MacroMux::config(void){

	am0->config(GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0,  MUX_ADC_0_CH0, MUX_ADC_0_CH1);
	am1->config(GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0,  MUX_ADC_1_CH0, MUX_ADC_1_CH1);
	gm0->config(GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOA, GPIO_Pin_8, GPIO_Pin_12, 0, 0);
	gm1->config(GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_0, GPIO_Pin_8, 0, 0);
	gm2->config(GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_9, GPIO_Pin_14, 0, 0);

}

/**
 * Iterate over the possible multiplexer inputs and store the values of each mux object
 */
void MacroMux::read(void)
{

	/** Read all mutiplexer instances */
	am0->read();
	am1->read();
	gm0->read();
	gm1->read();
	gm2->read();

	/** Update the multiplexer states just a single time which works for all instances */
	am0->update();
}

