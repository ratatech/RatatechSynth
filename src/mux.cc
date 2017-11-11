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
//#define DEBUG_ADC

/**
 * Iterate over the possible multiplexer inputs and store the read values into the buffer
 * @param synth_params_t	Synth global structure
 * @param pMux				Output buffer containing the mux read values
 */
void Mux::update(synth_params_t* synth_params, uint16_t* pMux)
{
	BitAction sb;

	/** BIT 0 */
	((seq_x & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(GPIOB,GPIO_Pin_5,sb);

	/** BIT 1 */
	(((seq_x>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(GPIOB,GPIO_Pin_6,sb);

	/** BIT 2 */
	(((seq_x>>2) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(GPIOB,GPIO_Pin_9,sb);

	/** Add small delay to allow the ADC finish the conversion
	30 cycles delay seems to work well for "ADC_SampleTime_7Cycles5"
	Just observed behavior, to be checked if this is the right value
	*/
	for(uint d=0;d<50;d++){
		__asm__("nop");
	}

	/** Read adc value corresponding to each mux selected bit */
	pMux[seq_x] = (synth_params->adc_read>>1)<<1;

	seq_x++;
	seq_x %= MUX_BITS;

#ifdef DEBUG_ADC
		iprintf("x0 =%.4i x1 =%.4i x2 =%.4i x3 =%.4i x4 =%.4i x5 =%.4i x6 =%.4i x7 =%.4i \r",
		synth_params->pMux[0],synth_params->pMux[1],synth_params->pMux[2],synth_params->pMux[3],
		synth_params->pMux[4],synth_params->pMux[5],synth_params->pMux[6],synth_params->pMux[7]);
#endif

}

