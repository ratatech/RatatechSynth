/*
 * adsr.h
 *
 *  Created on: Jul 18, 2015
 *      Author: rata
 */

#ifndef INCLUDE_ADSR_H_
#define INCLUDE_ADSR_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include "mov_avg.h"
#include "utils.h"
#include "Lutinterp.h"


class Lut_interp;

#define ENV_LUT_LENGTH 256

enum adsr_state_e {ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};
enum adsr_mode_e {LIN,EXP,LOG};

class ADSR{

	public:

		q31_t ph_inc,ph_inc_att,ph_inc_dec,ph_inc_rel;
		q15_t state;
		q15_t target_level,top_level_rel,top_level_dec,sustain_level,interp_state;
		int64_t ratio;
		adsr_state_e adsr_state;
		uint16_t ind;
		q15_t *adsr_table;
		Lut_interp *pLut_interp;

		/** ADSR Constructor.
		 *
		 */
		ADSR(void){}

		/**
		 * Set initial ADSR parameters
		 */
		void init(void);

		/**
		 * Get a new adsr envelope sample
		 * @return				ADSR sample
		 */
		q15_t get_sample(void);

		/**
		 * Reset internal variables and go back to attack state
		 */
		void reset(void);

		/** Get the newly read values from the ADC and set the coefficients
		 */
		void set_params(void);

		/**
		 *  Compute a new ADSR sample
		 * @return ADSR sample
		 */
		q15_t update(void);

		/**
		 * Set internal adsr coefficients
		 */
		void set_base(void);

		/**
		 * Interpolate adsr samples
		 * @param y		 		Interpolated value
		 */
		q15_t interp(q15_t y1, uint8_t ind);


};


#endif /* INCLUDE_ADSR_H_ */
