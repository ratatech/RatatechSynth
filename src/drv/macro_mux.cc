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

#include "macro_mux.h"


///**
// * Configure multiplexer input port and pins
// * @param synth_params	Synth global structure
// * @param GPIO_CTRL		GPIO port used for swtiching states of the MUX
// * @param GPIO_Pin_A	Specifies the port bit to be written. Control input A of the multiplexer
// * @param GPIO_Pin_B	Specifies the port bit to be written. Control input B of the multiplexer
// * @param GPIO_READ		GPIO port used for reading GPIO pins connected to the MUX output
// * @param GPIO_Pin_X	GPIO pin connected to MUX output X
// * @param GPIO_Pin_Y	GPIO pin connected to MUX output Y
// * @param _MUX_ID		Specifies the selected multiplexer ID
// */
//void MacroMux::config(synth_params_t* synth_params, GPIO_TypeDef* GPIO_CTRL, uint16_t GPIO_Pin_A, uint16_t GPIO_Pin_B, GPIO_TypeDef* GPIO_READ, uint16_t GPIO_Pin_X, uint16_t GPIO_Pin_Y){
//
//	/** Asign main config parameters */
//	MUX_PORT_CTRL	= GPIO_CTRL;
//	MUX_A 			= GPIO_Pin_A;
//	MUX_B 			= GPIO_Pin_B;
//	MUX_PORT_READ	= GPIO_READ;
//	MUX_X			= GPIO_Pin_X;
//	MUX_Y			= GPIO_Pin_Y;
//
//	am_0->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0, MUX_ADC_0_CH0, MUX_ADC_0_CH1);
//	am_1->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0, MUX_ADC_1_CH0, MUX_ADC_1_CH1);
//	gm_0->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOA, GPIO_Pin_8, GPIO_Pin_12, 0, 0);
//	gm_1->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_0, GPIO_Pin_8, 0, 0);
//	gm_2->config(synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_9, GPIO_Pin_14, 0, 0);
//
//
//}

/**
 * Iterate over the possible multiplexer inputs and store the read GPIO values into the buffer.
 * Each multiplexed input is read every call to the update function.
 * @param synth_params	Synth global structure
 */
void MacroMux::update(synth_params_t* synth_params)
{

//	BitAction sb;
//
//	/** BIT 0 (MSB) */
//	((seq & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
//	//sb = Bit_SET;
//	GPIO_WriteBit(MUX_PORT_CTRL,MUX_B,sb);
//
//	/** BIT 1 (LSB) */
//	(((seq>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
//	//sb = Bit_SET;
//	GPIO_WriteBit(MUX_PORT_CTRL,MUX_A,sb);
//
//	am_0->update(synth_params, seq);
////	am_1->update(synth_params, seq);
////	gm_0->update(synth_params, seq);
////	gm_1->update(synth_params, seq);
////	gm_2->update(synth_params, seq);
//
//	/** Increment buffer index and wrap around */
//	seq++;
//	seq %= MUX_INPUTS;

}

