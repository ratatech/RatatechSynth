/*
 * adsr.h
 *
 *  Created on: Jul 18, 2015
 *      Author: rata
 */

#ifndef INCLUDE_ADSR_H_
#define INCLUDE_ADSR_H_

#include "ratatechSynth.h"
#include "tables.h"
#include <math.h>

#define ENV_LUT_LENGTH 256
enum adsr_state_e {ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};
enum adsr_mode_e {LIN,EXP};


class ADSREnv {
	public:

		double attack;
		double decay;
		double sustain;
		double release;
		int16_t adsr_amp;
		adsr_state_e adsr_state;
		adsr_mode_e adsr_mode;
		int32_t ph_inc_A;
		int32_t ph_inc_D;
		int32_t ph_inc_S;
		int32_t ph_inc_R;
		int32_t ph_ind;
		int32_t decay_len;
		bool note_ON;
		int32_t exp_Coeff;
		double k;
		int32_t attack_init_val;


		/** Constructor.
		 * Set the Linear/Exponential envelope generator mode and initialize several parameters
		 * @param mode
		 */
		ADSREnv(adsr_mode_e mode){
 	 		adsr_mode = mode;
 	 		note_ON = false;
 	 		adsr_state = IDLE_STATE;
 	 		k = 4;
		}

		/**
		 * Calculate the number of steps needed in each of the ADSR states
		 */
		void calcAdsrSteps(void){

			if(adsr_mode == LIN){

				/********************************************//**
				 *  Linear ADSR Steps
				 ***********************************************/
				ph_inc_A = (int32_t)((((double)LUT_ENV_5_BIT/(double)(CONTROL_RATE*attack)))*SHIFT_20_BIT);
				decay_len = (int64_t)((((double)LUT_ENV_5_BIT*sustain))*SHIFT_20_BIT);
				ph_inc_D = (int32_t)((((double)decay_len/(double)(CONTROL_RATE*decay))));
				int32_t release_len = (LUT_ENV_5_BIT<<20)-decay_len;
				ph_inc_R = (int32_t)((((double)(release_len)/(double)(CONTROL_RATE*release))));

			}else{

				/********************************************//**
				 *  Exponential ADSR Steps
				 ***********************************************/
				ph_inc_A = (int32_t)((((double)LUT_ENV_5_BIT/(double)(CONTROL_RATE*attack)))*SHIFT_20_BIT);
				decay_len = (int64_t)((((double)LUT_ENV_5_BIT*sustain))*SHIFT_20_BIT);
				ph_inc_D = (int32_t)((((double)decay_len/(double)(CONTROL_RATE*decay))));
				int32_t release_len = (LUT_ENV_5_BIT<<20)-decay_len;
				ph_inc_R = (int32_t)((((double)(release_len)/(double)(CONTROL_RATE*release))));



				double exp_Coeff_temp = ((exp(-log((1.0 + k) / k) / (attack*CONTROL_RATE))));
				exp_Coeff = (int32_t)(exp_Coeff_temp*2147483648);
				attack_init_val = (int32_t)((1.0 + k) * (1.0 - exp_Coeff_temp)*2147483648);
				ph_inc_A = 0;

			}


		}

		/**
		 * Update ADSR states
		 * @param synth_params
		 */
		void update(synth_params_t *synth_params){

			if(adsr_mode == LIN){

				/********************************************//**
				 *  Linear ADSR
				 ***********************************************/
				switch (adsr_state)
				{
					case ATTACK_STATE:
					if (ph_ind>=(LUT_ENV_20_BIT))
					{
						adsr_state = DECAY_STATE;
						ph_ind = 0;
						break;

					}
					ph_ind += ph_inc_A;
					adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_up_lut_q15,ph_ind,LUT_ENV_5_BIT);

					break;

					case DECAY_STATE:

						if (ph_ind>=(decay_len))
						{
							if (note_ON)
							{
								adsr_state = SUSTAIN_STATE;
							}else{
								adsr_state = RELEASE_STATE;
							}

							break;
						}

						ph_ind += ph_inc_D;
						adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_down_lut_q15,ph_ind,LUT_ENV_5_BIT);

					break;

					case SUSTAIN_STATE:
						//do nothing, wait the key to be released and jump to the next state
						//trace_printf("SUSTAINEDDD!\n");
						//adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_up_lut_q15,ph_ind,LUT_ENV_5_BIT);
					break;

					case RELEASE_STATE:

						if (ph_ind>=(LUT_ENV_20_BIT))
						{
							adsr_state = IDLE_STATE;
							ph_ind = 0;
							adsr_amp = 0;
							note_ON = false;
							break;
						}
						adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_down_lut_q15,ph_ind,LUT_ENV_5_BIT);
						ph_ind += ph_inc_R;


					break;
				}
			}else{

				/********************************************//**
				 *  Exponential ADSR
				 ***********************************************/
				switch (adsr_state)
				{
					case ATTACK_STATE:
						int64_t temp;
						temp = synth_params->adsr_amp<<15;
						temp *= exp_Coeff;
						temp >>= 31;
						temp += attack_init_val;
						adsr_amp = temp>>15;
						//trace_printf("%i\n",adsr_amp);
						if (adsr_amp >=(0x7FFF)  || adsr_amp <= 0)
						{
							adsr_amp = 0x7FFF;
							adsr_state = DECAY_STATE;
							ph_ind = 0;
							break;
						}

					break;

					case DECAY_STATE:

						if (ph_ind>=(decay_len))
						{
							if (note_ON)
							{
								adsr_state = SUSTAIN_STATE;
							}else{
								adsr_state = RELEASE_STATE;
							}

							break;
						}

						ph_ind += ph_inc_D;
						adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_down_lut_q15,ph_ind,LUT_ENV_5_BIT);

					break;

					case SUSTAIN_STATE:
						//do nothing, wait the key to be released and jump to the next state
						//trace_printf("SUSTAINEDDD!\n");
						//adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_up_lut_q15,ph_ind,LUT_ENV_5_BIT);
					break;

					case RELEASE_STATE:

						if (ph_ind>=(LUT_ENV_20_BIT))
						{
							adsr_state = IDLE_STATE;
							ph_ind = 0;
							adsr_amp = 0;
							note_ON = false;
							break;
						}
						adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_down_lut_q15,ph_ind,LUT_ENV_5_BIT);
						ph_ind += ph_inc_R;


					break;
				}
			}

			// Save calculated amplitude to the data structure
			synth_params->adsr_amp = adsr_amp;


		}

};


#endif /* INCLUDE_ADSR_H_ */
