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

/***
 * MACROMUX
 *
 * This class creates instances of adc and gpio class objects and handles them together.
 * It is really coupled with teh HW architecture, then, pins, channels and other configuration
 * parameters are directly hardcoded in the config method.
 */
class MacroMux{

	public:

		AdcMux 	*am0;
		AdcMux 	*am1;
		GpioMux *gm0;
		GpioMux *gm1;
		GpioMux *gm2;

		/** Constructor
		*/
		MacroMux(){

			/** Instantiate mux objects*/
			am0 = new AdcMux();
			am1 = new AdcMux();
			gm0 = new GpioMux();
			gm1 = new GpioMux();
			gm2 = new GpioMux();

		}

		/**
		 * Configure multiplexers input port and pins
		 * @param synth_params	Synth global structure
		 */
		void config(synth_params_t* synth_params);

		/**
		 * Iterate over the possible multiplexer inputs and store the values of each mux object
		 * @param synth_params_t	Synth global structure
		 */
		void read(synth_params_t* synth_params);

};



#endif /* INCLUDE_MACRO_MUX_H_ */
