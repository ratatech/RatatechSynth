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

//	//wait for DMA complete
//	while (!synth_params->DMA_ADC_transfer_complete){};
//	synth_params->DMA_ADC_transfer_complete = false;
//	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
//    DMA_ClearFlag(DMA1_FLAG_GL1);
//    DMA_ClearFlag(DMA1_FLAG_TC1);


	/** BIT 0 */
	((seq_x & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_A,sb);

	/** BIT 1 */
	(((seq_x>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_B,sb);


	/** Add small delay to allow the ADC finish the conversion
	30 cycles delay seems to work well for "ADC_SampleTime_7Cycles5"
	Just observed behavior, to be checked if this is the right value
	*/
	for(uint d=0;d<50;d++){
		__asm__("nop");
	}

	/** Read adc value corresponding to each mux selected bit */
	synth_params->pMux_x[seq_x] = (synth_params->adc_read[0]);
	synth_params->pMux_y[seq_y] = (synth_params->adc_read[1]);

	/** Increment buffer index and wrap around */
	seq_x++;
	seq_x %= 4;
	seq_y++;
	seq_y %= 4;



}

