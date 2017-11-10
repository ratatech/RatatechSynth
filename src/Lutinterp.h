/*
 * Lutinterp.h
 *
 *  Created on: Nov 10, 2017
 *      Author: rata
 */

#ifndef LUTINTERP_H_
#define LUTINTERP_H_

#include <arm_math.h>
#include "types.h"
#include "utils.h"


/**
 * Lutinterp class
 */
class Lut_interp {

private:

	volatile uint32_t ph_ind_frac;
	uint32_t mask, shift_phase, lut_length, wrap_lut;

public:
	/** Constructor.
	 *
	 */
	Lut_interp(uint16_t lut_n_bits, uint8_t frac_n_bits){
		ph_ind_frac = 0;
		mask 		= (1<< frac_n_bits) - 1;
		shift_phase = frac_n_bits;
		lut_length 	= 1<<lut_n_bits;
		wrap_lut 	= 1 << (lut_n_bits + frac_n_bits);
	};

//	virtual ~Lut_interp();

	q15_t get_sample(uint32_t ph_inc_frac, const q15_t *wavetable);

};

#endif /* LUTINTERP_H_ */
