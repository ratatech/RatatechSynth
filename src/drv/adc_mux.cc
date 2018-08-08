/*
@file adc_mux.cc

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

#include "adc_mux.h"

/**
 * Iterate over the possible multiplexer inputs and store the read ADC values into the buffer.
 * Each multiplexed input is read every call to the update function.
 * @param synth_params_t	Synth global structure
 */
void AdcMux::update(synth_params_t* synth_params)
{
	BitAction sb;

	/** Read first then switch the state of the multiplxer. This way we can avoid
	 * to introduce some delay between the storage of the values and the multiplexer
	 * state switching.
	 * */
	pMux_x[seq] = (synth_params->adc_read[MUX_CHANNEL_X]) ;
	pMux_y[seq] = (synth_params->adc_read[MUX_CHANNEL_Y]);

	seq++;
	seq %= MUX_INPUTS;

	/** BIT 0 (MSB) */
	(((seq>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT_CTRL,MUX_B,sb);

	/** BIT 1 (LSB) */
	((seq & 0x01) > 0) 		? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT_CTRL,MUX_A,sb);

}


