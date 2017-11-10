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

	/** Constructor.
	 *
	 */
	Lut_interp(){

	};

	virtual ~Lut_interp();

	q15_t get_sample(uint32_t ph_inc_frac, q15_t *wavetable);

};

#endif /* LUTINTERP_H_ */
