/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jul 21, 2015
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

#include "utils.h"

uint16_t int16_2_uint16(q15_t x){

	if(x<0)
	{
		return (uint16_t)((int32_t)x+0x8000);
	}
	else
	{
		return (uint16_t)(x)+0x7FFF;

	}

}

uint16_t int32_2_uint16(int32_t x){

	if(x<0)
	{
		return (uint16_t)(x+65536);
	}
	else
	{
		return (uint16_t)(x)+65536;

	}

}


int32_t mul_int16(int16_t x1,int16_t x2){

	return ((int32_t)((x1)*(x2))>>15);

}


q15_t mul_q15_q15(q15_t x1,q15_t x2){
	return(((q31_t)(x1)*(x2))>>15);
}


/**
 * Mix two values with a given mix parameter
 * @param synth_params 	Synth global structure
 * @param a			Value A to mix
 * @param b			Value B to mix
 * @param mix 		Destination mix frame
 * @param mix_par	Mix parameter
 */
q15_t mix(synth_params_t *synth_params,q15_t a, q15_t b , q15_t mix_par){

	q15_t mix_out =	mul_q15_q15(a,(MAX_AMP-mix_par));
	mix_out += 		mul_q15_q15(b,(mix_par));
	return(mix_out);

}

/**
 * Mix two frames with a given mix parameter
 * @param synth_params 	Synth global structure
 * @param pFrame_a		Frame A to mix
 * @param pFrame_b 		Frame B to mix
 * @param pFrame_mix 	Destination mix frame
 * @param mix_par 		Mix parameter(0...0x7FFF), 0 ---> MIX A 100%, 0x7FFF ---> MIX B 100%,
 */
void mix_frames(synth_params_t *synth_params,q15_t* pFrame_a, q15_t* pFrame_b, q15_t* pFrame_mix , q15_t mix_par){


	q15_t *_pFrame_a = pFrame_a;			/* Frame A */
	q15_t *_pFrame_b = pFrame_b;			/* Frame B */
	q15_t *_pFrame_mix = pFrame_mix;		/* Mixed frame */
	q15_t _pFrame_mix_temp[FRAME_SIZE];		/* Intermediate calculation frame */

	arm_scale_q15(_pFrame_a,(MAX_AMP-mix_par),0,_pFrame_mix,FRAME_SIZE);
	arm_scale_q15(_pFrame_b,(mix_par),0,_pFrame_mix_temp,FRAME_SIZE);
	arm_add_q15(_pFrame_mix, _pFrame_mix_temp ,_pFrame_mix,FRAME_SIZE);
}

void reset_profiling(void){
	KIN1_ResetCycleCounter(); 			// reset cycle counter
	KIN1_EnableCycleCounter(); 			// start counting
}

uint32_t get_cycles_profiling(void){
	volatile uint32_t cycles = KIN1_GetCycleCounter(); 	// get cycle counter
	KIN1_DisableCycleCounter();
	return cycles;
}

