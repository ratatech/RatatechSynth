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



void LFO::compute_lfo_Sine(void)
{
	uint32_t int_ind;
	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac >=(LUT_SIN_20_BIT))
		ph_ind_frac -= (LUT_SIN_20_BIT);

	int_ind = ((ph_ind_frac & 0xFFF00000) >> 20);
	lfo_amp = sin_lut_q15[int_ind]<<8;
	lfo_amp = (lfo_amp>>1)+ 16384;
	lfo_amp = ((int32_t)(lfo_amp)*(lfo_amo)>>15);

}

void LFO::compute_lfo_Triangle(void)
{

	uint32_t int_ind;
	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(LUT_SIN_20_BIT<<1))
		ph_ind_frac -= (LUT_SIN_20_BIT<<1);

	int_ind = ((ph_ind_frac & 0xFFF00000) >> 20);
	lfo_amp = tri_lut_q15[int_ind]<<8;
	lfo_amp = (lfo_amp>>1)+ 16384;
	lfo_amp = ((int32_t)(lfo_amp)*(lfo_amo)>>15);

}



void LFO::compute_lfo_Saw(void)
{
	uint32_t int_ind;
	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac >=(LUT_SIN_20_BIT))
		ph_ind_frac -= (LUT_SIN_20_BIT);

	int_ind = ((ph_ind_frac & 0xFFF00000) >> 20);

	lfo_amp = saw_lut_q15[int_ind]<<8;
	lfo_amp = (lfo_amp>>1)+ 16384;
	lfo_amp = ((int32_t)(lfo_amp)*(lfo_amo)>>15);
}


void LFO::update(synth_params_t *synth_params)
{

	// Get a new oscillator sample
	switch (shape)
	{
		case SIN:
			LFO::compute_lfo_Sine();
			break;

		case SAW:
			LFO::compute_lfo_Saw();
			break;

		case TRI:
			LFO::compute_lfo_Triangle();
			break;

	}

	if(FM_synth){
		synth_params->FM_mod_amp = lfo_amp;
	}else{
		synth_params->lfo_amp = lfo_amp;
		synth_params->lfo_amo = lfo_amo;
	}


}
