/*
 * adsr.h
 *
 *  Created on: Jul 18, 2015
 *      Author: rata
 */

#ifndef INCLUDE_ADSR_H_
#define INCLUDE_ADSR_H_

#include "tables.h"
#include "mov_avg.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define ENV_LUT_LENGTH 256
#define TARGET_REACH 32440 // 90% of target level in q15 format

enum adsr_state_e {ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};
enum adsr_mode_e {LIN,EXP,LOG};

class ADSR{

	public:

		q31_t beta,beta_att,beta_dec,beta_rel;
		q31_t base,base_att,base_dec,base_rel;
		q31_t state;
		q15_t target_level,target_level_att,target_level_dec,sustain_level;
		int64_t ratio;
		adsr_state_e adsr_state;
		bool note_ON;



		/** ADSR Constructor.
		 *
		 */
		ADSR(void){}

		/**
		 * Set initial ADSR parameters
		 * @param synth_params Synth global structure
		 */
		void init(synth_params_t* synth_params){

			beta_att = synth_params->adsr_params.beta_att;
			beta_dec = synth_params->adsr_params.beta_dec;
			beta_rel = synth_params->adsr_params.beta_rel;
			state = synth_params->mov_avg_params.init_state;
            beta  = synth_params->mov_avg_params.beta;
            target_level_att = (MAX_AMP);
            target_level = target_level_att;
            adsr_state = IDLE_STATE;
            sustain_level = synth_params->adsr_params.sustain_level;
            target_level_dec = sustain_level;

            note_ON = false;
			beta = beta_att;
	        base = base_att;
	        ratio = synth_params->adsr_params.ratio;

	        set_base(synth_params);
		}

		/**
		 * Get a new adsr envelope frame
		 * @param synth_params 	Synth global structure
		 * @param pAdsr 		ADSR envelope output buffer
		 * @param block_size 	Number of samples in the vector
		 */
		void get_frame(synth_params_t *synth_params, q15_t* pAdsr,uint32_t block_size);

		/**
		 * Reset internal variables and go back to attack state
		 */
		void reset(void);

		/** Get the newly read values from the ADC and set the coefficients */
		void set_params(synth_params_t *synth_params);

		/**
		 *  Compute a new ADSR sample
		 * @return ADSR sample
		 */
		q15_t update(void);

		void set_base(synth_params_t *synth_params);


};


#endif /* INCLUDE_ADSR_H_ */
