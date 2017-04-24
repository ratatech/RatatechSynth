/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Aug 8, 2015
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

#include "lfo.h"

using namespace std;

/**
 * Compute a new lfo sample
 * @return lfo_amp The computed lfo sample
 */
int32_t LFO::get_sample(synth_params_t *synth_params)
{
	uint32_t int_ind;

	/** Increase phase index*/
	ph_ind_frac += ph_inc_frac;

	/** Wrap around */
	if (ph_ind_frac >=(LUT_8_20_BIT))
		ph_ind_frac -= (LUT_8_20_BIT);

	/** Discard fractional part*/
	int_ind = ((ph_ind_frac & 0xFFF00000) >> 20);

	/** Get the sample from the wavetable scaled to 16bits */
	lfo_amp = wavetable[int_ind]<<8;

	/** Scale the waveform and add offset to have only positive numbers*/
	lfo_amp = (lfo_amp>>1)+ LFO_DC_OFF;

	/** Store sample in global struct */
	synth_params->lfo_amp = lfo_amp;

	return lfo_amp;
}


void LFO::update(synth_params_t *synth_params)
{

	if(FM_synth){
		synth_params->FM_mod_amp = lfo_amp;
	}else{
		synth_params->lfo_amp = lfo_amp;
		synth_params->lfo_amo = lfo_amo;
	}


}
