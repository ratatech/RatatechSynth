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
 * Configure multiplexer input port and pins
 * @param synth_params_t	Synth global structure
 * @param GPIOx				Where x can be (A..C) to select the GPIO peripheral.
 * @param GPIO_Pin_A 		Specifies the port bit to be written. Control input A of the multiplexer
 * @param GPIO_Pin_B		Specifies the port bit to be written. Control input B of the multiplexer
 * @param MUX_ID			Specifies the selected multiplexer ID
 */
void Mux::config(synth_params_t* synth_params, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_A, uint16_t GPIO_Pin_B, MUX_ID_e _MUX_ID){

	/** Asign main config parameters */
	MUX_PORT 	= GPIOx;
	MUX_A 		= GPIO_Pin_A;
	MUX_B 		= GPIO_Pin_B;
	MUX_ID 		= _MUX_ID;

	switch(MUX_ID){
		case MUX_ADC_0:
			pMux_x = synth_params->mux_adc_0_out.mux_x;
			pMux_y = synth_params->mux_adc_0_out.mux_y;
		break;
		case MUX_ADC_1:
			pMux_x = synth_params->mux_adc_1_out.mux_x;
			pMux_y = synth_params->mux_adc_1_out.mux_y;
		break;
		case MUX_EXTI_0:
			pMux_x = synth_params->mux_gpio_0_out.mux_x;
			pMux_y = synth_params->mux_gpio_0_out.mux_y;
		break;
	}


}

/**
 * Iterate over the possible multiplexer inputs and store the read ADC values into the buffer.
 * Each multiplexed input is read every call to the update function.
 * @param synth_params_t	Synth global structure
 */
void Mux::adc_update(synth_params_t* synth_params)
{

	BitAction sb;

	/** Read simultuaneously ADC1 and ADC2 and store the value corresponding to the selected bit.
	 * ADC1 and ADC2 converted values are stored in a 32bit word and then splited in two 16bit samples.
	 * */
	pMux_x[seq_x] = (synth_params->adc_read[MUX_ID] >> 16) ;
	pMux_y[seq_x] = (synth_params->adc_read[MUX_ID] & 0xFFFF);

	/** Increment buffer index and wrap around */
	seq_x++;
	seq_x %= MUX_CHANNELS;

	/** BIT 0 */
	((seq_x & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_A,sb);

	/** BIT 1 */
	(((seq_x>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_B,sb);

}

/**
 * Iterate over the possible multiplexer inputs and store the read GPIO values into the buffer.
 * Each multiplexed input is read every call to the update function.
 * @param synth_params_t	Synth global structure
 * @param pMux				Output buffer containing the mux read values
 */
void Mux::gpio_update(synth_params_t* synth_params)
{

	BitAction sb;

	/** BIT 0 */
	((seq_x & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_A,sb);

	/** BIT 1 */
	(((seq_x>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
	GPIO_WriteBit(MUX_PORT,MUX_B,sb);

	/** Read gpio pins and store the value corresponding to the selected bit */
	uint16_t pin_state = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	volatile uint16_t port_state = GPIO_ReadInputData(GPIOB);
	pMux_x[seq_x] = pin_state;
	pMux_y[seq_x] = pin_state;

	/** Increment buffer index and wrap around */
	seq_x++;
	seq_x %= MUX_CHANNELS;


}

