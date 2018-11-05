/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Aug 8, 2015
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

#include "lfo.h"

using namespace std;

/**
 * Compute a new lfo sample
 * @return lfo_amp The computed lfo sample
 */
q15_t LFO::get_sample(void)
{

	q31_t y,_y0,_y1;
	uint32_t ind_frac,ind_int;

	ph_ind_frac += ph_inc_frac;
	ph_ind_frac %= WRAP_AROUND_LUT;

    /** 9 bits for the integer part, 23 bits for the fractional part */
    ind_frac = (ph_ind_frac & MASK_PHASE_FRAC);
    ind_int = (ph_ind_frac >> SHIFT_PHASE_INT);

    /** Read two nearest output values from the index */
    _y0 = wavetable[ind_int];
    _y1 = wavetable[(ind_int + 1 ) % LUT_LENGTH];

    /** Linear interpolation */
    y = ((q63_t)(_y1 - _y0)*ind_frac)>>SHIFT_PHASE_INT;
    y += _y0;

	/** Scale the waveform and add offset to have only positive numbers*/
	y = (y>>1)+ LFO_DC_OFFSET;

    return y;
}

/**
 * Interpolate lfo samples
 * @param y		 		Interpolated value
 */
q15_t LFO::interp(q15_t y1,uint8_t ind)
{
	q63_t y = interp_q15(interp_state,y1,FRAME_INTERP_K*ind,SHIFT_FRAME_INTERP);
	return (q15_t)y;
}

/**
 * Compute a new lfo frame
 * @param pLfo Pointer to store the oscillator samples
 * @param block_size 	Number of samples in the vector
 */
void LFO::get_frame(q15_t* pLfo, uint32_t block_size)
{
	q15_t *pOut = pLfo;	/* output pointer */

	// Generate samples and store it in the output buffer
	for(uint8_t i=0;i<block_size;i++){
		*pOut++ = get_sample();
	}

}

/** Init lfo.
 * @param lfo_param Structure holding init parameters
 */
void LFO::init(lfo_params_t* lfo_param){
	set_shape(lfo_param->shape_osc);
	set_freq_frac(lfo_param->freq_frac);
	lfo_amo = lfo_param->lfo_amo;
	interp_state = 0;

}


