/*
@file mux.h

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
#ifndef INCLUDE_MACRO_MUX_H_
#define INCLUDE_MACRO_MUX_H_

#include "types.h"
#include "mux.h"
#include "gpio_mux.h"
#include "adc_mux.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MUX_BITS 8
#define MUX_CHANNELS 4

class MacroMux{

	public:
		GPIO_TypeDef* MUX_PORT_CTRL, *MUX_PORT_READ;
		uint16_t MUX_A,MUX_B,MUX_X,MUX_Y;
		MUX_ID_e MUX_ID;

		uint16_t seq;
		mux_out_t pMux;
		uint16_t *pMux_x,*pMux_y;

		AdcMux 	*am_0;
		AdcMux 	*am_1;
		GpioMux *gm_0;
		GpioMux *gm_1;
		GpioMux *gm_2;

		/** Constructor
		*/
		MacroMux(){

			/** Instantiate mux objects*/
			am_0 = new AdcMux();
			am_1 = new AdcMux();
			gm_0 = new GpioMux();
			gm_1 = new GpioMux();
			gm_2 = new GpioMux();

		}

		/**
		 * Update the macro mutliplexer states
		 * @param synth_params	Synth global structure
		 */
		void update(synth_params_t* synth_params);
};



#endif /* INCLUDE_MACRO_MUX_H_ */
