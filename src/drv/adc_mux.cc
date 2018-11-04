/*
@file adc_mux.cc

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

#include "adc_mux.h"

/**
 * Iterate over the possible multiplexer inputs and store the read ADC values into the buffer.
 */
void AdcMux::read(void)
{
    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

	/** Read first then switch the state of the multiplxer. This way we can avoid
	 * to introduce some delay between the storage of the values and the multiplexer
	 * state switching.
	 * */
	switch(seq){
		case 0:
			pMux_x[0] = movAvg_x0->update(s->adc_read[MUX_CHANNEL_X]);
			pMux_y[0] = movAvg_y0->update(s->adc_read[MUX_CHANNEL_Y]);
		break;

		case 1:
			pMux_x[1] = movAvg_x1->update(s->adc_read[MUX_CHANNEL_X]);
			pMux_y[1] = movAvg_y1->update(s->adc_read[MUX_CHANNEL_Y]);
		break;

		case 2:
			pMux_x[2] = movAvg_x2->update(s->adc_read[MUX_CHANNEL_X]);
			pMux_y[2] = movAvg_y2->update(s->adc_read[MUX_CHANNEL_Y]);
		break;

		case 3:
			pMux_x[3] = movAvg_x3->update(s->adc_read[MUX_CHANNEL_X]);
			pMux_y[3] = movAvg_y3->update(s->adc_read[MUX_CHANNEL_Y]);
		break;
	}

	seq++;
	seq %= MUX_INPUTS;

}


