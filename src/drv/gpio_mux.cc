/*
@file gpio_mux.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jul 1, 2017
This file is part of Ratatech 3019

    Ratatech 3019 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ratatech 3019 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
*/

#include "gpio_mux.h"

/**
 * Iterate over the possible multiplexer inputs and store the read GPIO values into the buffer.
 * @param synth_params_t	Synth global structure
 */
void GpioMux::read(synth_params_t* synth_params)
{


	/** Read gpio pins and store the value corresponding to the selected bit */
	uint16_t pin_state_x = GPIO_ReadInputDataBit(MUX_PORT_READ,MUX_X);
	uint16_t pin_state_y = GPIO_ReadInputDataBit(MUX_PORT_READ,MUX_Y);

	pMux_x[seq] = pin_state_x;
	pMux_y[seq] = pin_state_y;

	seq++;
	seq %= MUX_INPUTS;

}

