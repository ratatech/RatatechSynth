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
enum adsr_state { ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};


class ADSREnv {
	public:

		double attack;
		double decay;
		double sustain;
		double release;
		int16_t adsr_amp;
		adsr_state adsr_st;
		int32_t ph_inc_A;
		int32_t ph_inc_D;
		int32_t ph_inc_S;
		int32_t ph_inc_R;
		int32_t ph_ind;
		int32_t decay_len;


		void calcAdsrSteps(void){
			ph_inc_A = (int32_t)((((double)LUT_ENV_5_BIT/(double)(CONTROL_RATE*attack)))*1048576);

			decay_len = (int64_t)((((double)LUT_ENV_5_BIT*sustain))*1048576);

			ph_inc_D = (int32_t)((((double)decay_len/(double)(CONTROL_RATE*decay))));

			int32_t release_len = (LUT_ENV_5_BIT<<20)-decay_len;

			ph_inc_R = (int32_t)((((double)(release_len)/(double)(CONTROL_RATE*release))));

		}

		void update(synth_params_t *synth_params){

			switch (adsr_st)
			{
				case ATTACK_STATE:
				if (ph_ind>=(LUT_ENV_20_BIT))
				{
					adsr_st = DECAY_STATE;
					ph_ind = 0;
					break;

				}
				ph_ind += ph_inc_A;
				adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_up_lut_q15,ph_ind,LUT_ENV_5_BIT);

				break;

				case DECAY_STATE:

				if (ph_ind>=(decay_len))
				{
					//adsr_st = SUSTAIN_STATE;
					break;
				}

				ph_ind += ph_inc_D;
				adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_down_lut_q15,ph_ind,LUT_ENV_5_BIT);

				break;

				case SUSTAIN_STATE:
					//do nothing, wait the key to be released and jump to the next state
					//trace_printf("SUSTAINEDDD!\n");
				break;

				case RELEASE_STATE:

					if (ph_ind>=(LUT_ENV_20_BIT))
					{
						adsr_st = IDLE_STATE;
						ph_ind = 0;
						adsr_amp = 0;
						break;
					}
					adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_down_lut_q15,ph_ind,LUT_ENV_5_BIT);
					ph_ind += ph_inc_R;


				break;
			}
			synth_params->adsr_amp = adsr_amp;


		}

};


#endif /* INCLUDE_ADSR_H_ */
