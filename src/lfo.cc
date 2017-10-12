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
q15_t LFO::get_sample(synth_params_t *synth_params)
{

	int32_t interp_lut,interp_lut_temp,frac,mod;

	ph_ind_frac += ph_inc_frac;
	ph_ind_frac %= LUT_8_20_BIT;

	/** Interpolate LUT */
	lfo_amp = arm_linear_interp_q15((int16_t*)wavetable,ph_ind_frac,LUT_8_BIT);

	/** Scale the waveform and add offset to have only positive numbers*/
	lfo_amp = (lfo_amp>>1)+ LFO_DC_OFF;

	return lfo_amp;
}


/**
 * Compute a new lfo frame
 * @param synth_params Synth global structure
 * @param pLfo Pointer to store the oscillator samples
 * @param block_size 	Number of samples in the vector
 */
void LFO::get_frame(synth_params_t *synth_params, q15_t* pLfo, uint32_t block_size)
{
	 q15_t *pOut = pLfo;	/* output pointer */

	 // Generate samples and store it in the output buffer
	 for(uint i=0;i<block_size;i++){
		 *pOut++ = get_sample(synth_params);
	 }

}

/** Init lfo.
 *
 * @param lfo_param Structure holding init parameters
 */
void LFO::init(lfo_params_t* lfo_param){
	set_shape(lfo_param->shape_osc);
	set_freq_frac(lfo_param->freq_frac);
	lfo_amo = lfo_param->lfo_amo;

}


