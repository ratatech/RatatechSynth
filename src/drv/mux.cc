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

#include "mux.h"

/**
 * Iterate over the possible multiplexer inputs and store the read values into the buffer.
 * Each multiplexed input is read every call to the update function.
 * @param synth_params_t	Synth global structure
 * @param pMux				Output buffer containing the mux read values
 */
void Mux::update(synth_params_t* synth_params)
{

	BitAction sb;

	/** Read adc value corresponding to each mux selected bit */
	synth_params->pMux_x[seq_x] = (synth_params->adc_read[0] >> 16) ;
	synth_params->pMux_y[seq_y] = (synth_params->adc_read[0] & 0xFFFF);

	/** Increment buffer index and wrap around */
	seq_x++;
	seq_x %= MUX_CHANNELS;
	seq_y++;
	seq_y %= MUX_CHANNELS;

	/** BIT 0 */
	((seq_x & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_A,sb);

	/** BIT 1 */
	(((seq_x>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_B,sb);

}

