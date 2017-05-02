/*
@file fileName.h

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
#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#include "ratatechSynth.h"

struct mux_adc_t{
	uint16_t mux_x0;
	uint16_t mux_x1;
	uint16_t mux_x2;
	uint16_t mux_x3;
	uint16_t mux_x4;
	uint16_t mux_x5;
	uint16_t mux_x6;
	uint16_t mux_x7;
};


/**
 * Read the selected channel on the ADC1
 * @param channel
 * @return ADC covnerted value
 */
uint16_t readADC1(uint8_t channel);

/**
 * Read multiplexed adc values
 * @param mux_adc A structure conatinging the read mux values
 */
void mux_adc_read(mux_adc_t* mux_adc);

#endif /* INCLUDE_ADC_H_ */
