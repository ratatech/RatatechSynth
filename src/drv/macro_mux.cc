/*
@file mux.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jul 1, 2017
This file is part of XXXXXXX

    XXXXXXX is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    XXXXXXX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
*/

#include "macro_mux.h"


/**
 * Configure multiplexers input port and pins
 * @param synth_params	Synth global structure
 */
void MacroMux::config(synth_params_t* synth_params){

	am0->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0,  MUX_ADC_0_CH0, MUX_ADC_0_CH1);
	am1->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0,  MUX_ADC_1_CH0, MUX_ADC_1_CH1);
	gm0->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOA, GPIO_Pin_8, GPIO_Pin_12, 0, 0);
	gm1->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_0, GPIO_Pin_8, 0, 0);
	gm2->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_9, GPIO_Pin_14, 0, 0);

}

/**
 * Iterate over the possible multiplexer inputs and store the values of each mux object
 * @param synth_params_t	Synth global structure
 */
void MacroMux::read(synth_params_t* synth_params)
{

	/** Read all mutiplexer instances */
	am0->read(synth_params);
	am1->read(synth_params);
	gm0->read(synth_params);
	gm1->read(synth_params);
	gm2->read(synth_params);

	/** Update the multiplexer states just a single time which works for all instances */
	am0->update(synth_params);
}

