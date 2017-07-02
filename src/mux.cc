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
void Mux::update(synth_params_t* synth_params, uint16_t* pMux)
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

		/** Add small delay to allow the DAC finish the conversion
		250 cycles delay seems to work well for "ADC_SampleTime_239Cycles5"
		Just observed behaviour, to be checked if this is the right value
		*/
		for(uint d=0;d<250;d++){
			__asm__("nop");
		}

	   /** Read adc corresponding to each selected bit */
		switch(s){
			/** MUX x0 */
			case 0 :
				mux_x0 = synth_params->adc_read;

			break;

			/** MUX x1 */
			case 1 :
				mux_x1 = synth_params->adc_read;

			break;

			/** MUX x2 */
			case 2 :
				mux_x2 = synth_params->adc_read;

			break;

			/** MUX x3 */
			case 3 :
				mux_x3 = synth_params->adc_read;

			break;

			/** MUX x4 */
			case 4 :
				mux_x4 = synth_params->adc_read;

			break;

			/** MUX x5 */
			case 5 :
				mux_x5 = synth_params->adc_read;

			break;

			/** MUX x6 */
			case 6 :
				mux_x6 = synth_params->adc_read;

			break;

			/** MUX x7 */
			case 7 :
				mux_x7 = synth_params->adc_read;

			break;
		}

	}


}

/**
 * Read the selected channel on the ADC1
 * @param channel
 * @return ADC covnerted value
 */
uint16_t Mux::readADC1(uint8_t channel)
{
//  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
//  // Start the conversion
//  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//  // Wait until conversion completion
//  //while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
//  // Get the conversion value
//  return ADC_GetConversionValue(ADC1);

  uint16_t data_adc;
//  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//  while(ADC_GetSoftwareStartConvStatus(ADC1));
//  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
//  data_adc = ADC_GetConversionValue(ADC1);
//  ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
  return(data_adc);


}
