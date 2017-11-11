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

public:

	volatile uint32_t ph_ind_frac;
	volatile uint64_t ph_ind_frac_ovf,wrap_lut_ovf;
	uint32_t mask, shift_phase, lut_length, wrap_lut;

	/** Constructor.
	 *
	 */
	Lut_interp(uint16_t lut_n_bits, uint8_t frac_n_bits){
		ph_ind_frac 	= 0;
		ph_ind_frac_ovf	= 0;
		mask 			= (1<< frac_n_bits) - 1;
		shift_phase	 	= frac_n_bits;
		lut_length 		= 1<<lut_n_bits;
		wrap_lut 		= 1 << (lut_n_bits + frac_n_bits);
		wrap_lut_ovf	= (uint64_t)wrap_lut<<1;
	};

//	virtual ~Lut_interp();

	void reset(void);

	q15_t get_sample(uint32_t ph_inc_frac, const q15_t *wavetable);

};

#endif /* LUTINTERP_H_ */
