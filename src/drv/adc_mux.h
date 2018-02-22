/*
@file adc_mux.h

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
#ifndef INCLUDE_ADC_MUX_H_
#define INCLUDE_ADC_MUX_H_

#include "types.h"
#include "mux.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

class AdcMux: public Mux{

	public:
		/** Constructor
		*/
		AdcMux(){}

		/**
		 * Configure multiplexer input port and pins
		 * @param synth_params	Synth global structure
		 * @param GPIO_CTRL		GPIO port used for swtiching states of the MUX
		 * @param GPIO_Pin_A	Specifies the port bit to be written. Control input A of the multiplexer
		 * @param GPIO_Pin_B	Specifies the port bit to be written. Control input B of the multiplexer
		 * @param GPIO_READ		GPIO port used for reading GPIO pins connected to the MUX output
		 * @param GPIO_Pin_X	GPIO pin connected to MUX output X
		 * @param GPIO_Pin_Y	GPIO pin connected to MUX output Y
		 * @param _MUX_ID		Specifies the selected multiplexer ID
		 */
		void config(synth_params_t* synth_params, GPIO_TypeDef* GPIO_CTRL, uint16_t GPIO_Pin_A, uint16_t GPIO_Pin_B, GPIO_TypeDef* GPIO_READ, uint16_t GPIO_Pin_X, uint16_t GPIO_Pin_Y,MUX_ID_e _MUX_ID);

		/**
		 * Iterate over the possible multiplexer inputs and store the read ADC values into the buffer.
		 * Each multiplexed input is read every call to the update function.
		 * @param synth_params_t	Synth global structure
		 */
		void update(synth_params_t* synth_params_t);

};



#endif /* INCLUDE_ADC_MUX_H_ */
