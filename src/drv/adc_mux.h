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

/**
 * Multiplexer IDs
 */
typedef enum {
	MUX_ADC_0_CH0, //!< MUX_ADC_0
	MUX_ADC_0_CH1, //!< MUX_ADC_0
	MUX_ADC_1_CH0, //!< MUX_ADC_0
	MUX_ADC_1_CH1, //!< MUX_ADC_0
}MUX_ID_CH_e;

class AdcMux: public Mux{

	public:
		/** Constructor
		*/
		AdcMux(){}

		/**
		 * Iterate over the possible multiplexer inputs and store the read ADC values into the buffer.
		 * Each multiplexed input is read every call to the update function.
		 * @param synth_params_t	Synth global structure
		 */
		void update(synth_params_t* synth_params_t);

};



#endif /* INCLUDE_ADC_MUX_H_ */