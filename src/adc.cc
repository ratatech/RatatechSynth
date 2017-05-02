/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 11, 2016
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

#include "adc.h"

/**
 * Read the selected channel on the ADC1
 * @param channel
 * @return ADC covnerted value
 */
uint16_t readADC1(uint8_t channel)
{
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
  // Start the conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}

void mux_adc_read(mux_adc_t* mux_adc){

	BitAction sb;

    /** Set the tree bits to the according pins to iterate the 8 values */
	for(int s=0;s<8;s++){

		/** BIT 0 */
		((s & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
		GPIO_WriteBit(GPIOB,GPIO_Pin_5,sb);

		/** BIT 1 */
		(((s>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
		GPIO_WriteBit(GPIOB,GPIO_Pin_6,sb);

		/** BIT 2 */
		(((s>>2) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,sb);

	   /** Read adc corresponding to each selected bit */
		switch(s){
			/** MUX x0 */
			case 0 :
				mux_adc->mux_x0 = readADC1(4);
				trace_printf("ADC read MUX x0 = %i\n",mux_adc->mux_x0);
			break;

			/** MUX x1 */
			case 1 :
				mux_adc->mux_x1 = readADC1(4);
				trace_printf("ADC read MUX x1 = %i\n",mux_adc->mux_x1);
			break;

			/** MUX x2 */
			case 2 :
				mux_adc->mux_x2 = readADC1(4);
				trace_printf("ADC read MUX x2 = %i\n",mux_adc->mux_x2);
			break;

			/** MUX x3 */
			case 3 :
				mux_adc->mux_x3 = readADC1(4);
				trace_printf("ADC read MUX x3 = %i\n",mux_adc->mux_x3);
			break;

			/** MUX x4 */
			case 4 :
				mux_adc->mux_x4 = readADC1(4);
				trace_printf("ADC read MUX x4 = %i\n",mux_adc->mux_x4);
			break;

			/** MUX x5 */
			case 5 :
				mux_adc->mux_x5 = readADC1(4);
				trace_printf("ADC read MUX x5 = %i\n",mux_adc->mux_x5);
			break;

			/** MUX x6 */
			case 6 :
				mux_adc->mux_x6 = readADC1(4);
				trace_printf("ADC read MUX x6 = %i\n",mux_adc->mux_x6);
			break;

			/** MUX x7 */
			case 7 :
				mux_adc->mux_x7 = readADC1(4);
				trace_printf("ADC read MUX x7 = %i\n",mux_adc->mux_x7);
			break;
		}



	}



}
