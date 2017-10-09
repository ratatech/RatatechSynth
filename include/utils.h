/*
 * utils.h
 *
 *  Created on: Jul 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include "ratatechSynth.h"

uint16_t int16_2_uint16(q15_t x);
uint16_t int32_2_uint16(int32_t x);
int32_t mul_int16(int16_t x1,int16_t x2);

/**
 * Mix two frames with a given mix parameter
 * @param synth_params 	Synth global structure
 * @param pFrame_a		Frame A to mix
 * @param pFrame_b 		Frame B to mix
 * @param pFrame_mix 	Destination mix frame
 * @param mix_par 		Mix parameter
 */
void mix(synth_params_t *synth_params,q15_t* pFrame_a, q15_t* pFrame_b, q15_t* pFrame_mix , q15_t mix_par);


#endif /* INCLUDE_UTILS_H_ */
