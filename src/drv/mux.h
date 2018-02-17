/*
@file mux.h

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
#ifndef INCLUDE_MUX_H_
#define INCLUDE_MUX_H_

#include "types.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MUX_BITS 8

class Mux{

	private:
		GPIO_TypeDef* MUX_PORT;
		uint16_t MUX_A;
		uint16_t MUX_B;
		uint16_t MUX_C;

	public:

		uint16_t seq_x,seq_y;


		/** Constructor
		*/
		Mux(){

			//mux_mov_avg = MovAvg();

		}

		/**
		 * Configure multiplexer input port and pins
		 * @param GPIOx			Where x can be (A..C) to select the GPIO peripheral.
		 * @param GPIO_Pin_A 	Specifies the port bit to be written. Control input A of the multiplexer
		 * @param GPIO_Pin_B	Specifies the port bit to be written. Control input B of the multiplexer
		 * @param GPIO_Pin_C	Specifies the port bit to be written. Control input C of the multiplexer
		 */
		void config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_A, uint16_t GPIO_Pin_B, uint16_t GPIO_Pin_C){

			MUX_PORT = GPIOx;
			//MUX_A = GPIO_Pin_0;
			MUX_A = GPIO_Pin_1;
			MUX_B = GPIO_Pin_12;
		}

		/**
		 * Iterate over the possible multiplexer inputs and store the read values into the buffer
		 * @param synth_params_t	Synth global structure
		 */
		void update(synth_params_t* synth_params_t);


};



#endif /* INCLUDE_MUX_H_ */
