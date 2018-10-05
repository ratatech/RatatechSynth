/*
@file mov_avg.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 13, 2017
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

#include "mov_avg.h"


using namespace std;

/**
 * Update moving average filter
 * @param x New value
 * @return New filtered sample
 */
q15_t MovAvg::update(q15_t x)
{
	/** Temp vars */
	q31_t 	 _x32,x32;
	int64_t x64;

	_x32 = (q31_t)(x<<16);						// Shift input data(q15) 16 bit to match the state type(q31)
    x32 = state - _x32; 						// x32 = s0.31 - s0.31 = s0.31
    x64 = ((int64_t)x32) * ((int64_t)beta);		// x64 = s0.31 * s0.31 = s0.62
    x32 = x64>>31;								// x32 = s0.31 >> 31   = s0.31
    state = _x32 + x32;							// x32 = s0.31 + s0.31 = s0.31
    return((q15_t)(state>>16));					// 	 y = s0.31 >> 16   = s0.15

}

/**
 * Process an input data frame through the moving average filter
 * @param synth_params Synth global structure
 * @param pMovAvg Pointer to store the filtered samples
 */
void MovAvg::process_frame(synth_params_t *synth_params, q15_t* pIn, q15_t* pOut)
{

	q15_t *_pIn = pIn;		/* input pointer */
	q15_t *_pOut = pOut;	/* output pointer */

	// Generate samples and store it in the output buffer
	for(int i=0;i<FRAME_SIZE;i++){
		*_pOut++ =  update(*_pIn++);
	}

}

