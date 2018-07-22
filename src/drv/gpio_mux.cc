/*
@file gpio_mux.cc

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

#include "gpio_mux.h"

/**
 * Configure multiplexer input port and pins
 * @param synth_params	Synth global structure
 * @param GPIO_CTRL		GPIO port used for swtiching states of the MUX
 * @param GPIO_Pin_A	Specifies the port bit to be written. Control input A of the multiplexer
 * @param GPIO_Pin_B	Specifies the port bit to be written. Control input B of the multiplexer
 * @param GPIO_READ		GPIO port used for reading GPIO pins connected to the MUX output
 * @param GPIO_Pin_X	GPIO pin connected to MUX output X
 * @param GPIO_Pin_Y	GPIO pin connected to MUX output Y
 * @param _MUX_ID		Specifies the selected multiplexer ID
 */
void GpioMux::config(synth_params_t* synth_params, GPIO_TypeDef* GPIO_CTRL, uint16_t GPIO_Pin_A, uint16_t GPIO_Pin_B, GPIO_TypeDef* GPIO_READ, uint16_t GPIO_Pin_X, uint16_t GPIO_Pin_Y,MUX_ID_e _MUX_ID){

	/** Asign main config parameters */
	MUX_PORT_CTRL	= GPIO_CTRL;
	MUX_A 			= GPIO_Pin_A;
	MUX_B 			= GPIO_Pin_B;
	MUX_ID 			= _MUX_ID;
	MUX_PORT_READ	= GPIO_READ;
	MUX_X			= GPIO_Pin_X;
	MUX_Y			= GPIO_Pin_Y;

	switch(MUX_ID){
		case MUX_ADC_0:
			pMux_x = synth_params->mux_adc_0_out.mux_x;
			pMux_y = synth_params->mux_adc_0_out.mux_y;
		break;
		case MUX_ADC_1:
			pMux_x = synth_params->mux_adc_1_out.mux_x;
			pMux_y = synth_params->mux_adc_1_out.mux_y;
		break;
		case MUX_GPIO_0:
			pMux_x = synth_params->mux_gpio_0_out.mux_x;
			pMux_y = synth_params->mux_gpio_0_out.mux_y;
		break;
		case MUX_GPIO_1:
			pMux_x = synth_params->mux_gpio_1_out.mux_x;
			pMux_y = synth_params->mux_gpio_1_out.mux_y;
		break;
		case MUX_GPIO_2:
			pMux_x = synth_params->mux_gpio_2_out.mux_x;
			pMux_y = synth_params->mux_gpio_2_out.mux_y;
		break;
	}

}

/**
 * Iterate over the possible multiplexer inputs and store the read GPIO values into the buffer.
 * Each multiplexed input is read every call to the update function.
 * @param synth_params_t	Synth global structure
 * @param pMux				Output buffer containing the mux read values
 */
void GpioMux::update(synth_params_t* synth_params, uint16_t seq)
{

	/** Read gpio pins and store the value corresponding to the selected bit */
	uint16_t pin_state_x = GPIO_ReadInputDataBit(MUX_PORT_READ,MUX_X);
	uint16_t pin_state_y = GPIO_ReadInputDataBit(MUX_PORT_READ,MUX_Y);

	pMux_x[seq] = pin_state_x;
	pMux_y[seq] = pin_state_y;

}

