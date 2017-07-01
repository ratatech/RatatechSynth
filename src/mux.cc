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
 * Iterate over the possible multiplexer inputs and store the read values into the buffer
 * @param synth_params_t	Synth global structure
 * @param pMux				Output buffer containing the mux read values
 */
void Mux::update(synth_params_t* synth_params_t, uint16_t* pMux)
{
	BitAction sb;

	/** Iterate over the 8 mux inputs*/
	for(uint s=0;s<MUX_BITS;s++)
	{

		/** BIT 0 */
		((s & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
		GPIO_WriteBit(GPIOB,GPIO_Pin_5,sb);

		/** BIT 1 */
		(((s>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
		GPIO_WriteBit(GPIOB,GPIO_Pin_6,sb);

		/** BIT 2 */
		(((s>>2) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,sb);

		/** Store each multiplexed input into the buffer */
		*pMux++ = readADC1(4);

	}


}

/**
 * Read the selected channel on the ADC1
 * @param channel
 * @return ADC covnerted value
 */
uint16_t Mux::readADC1(uint8_t channel)
{
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
  // Start the conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}
