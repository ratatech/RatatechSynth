/*
 * adsr.h
 *
 *  Created on: Jul 18, 2015
 *      Author: rata
 */

#ifndef INCLUDE_ADSR_H_
#define INCLUDE_ADSR_H_

#include "ratatechSynth.h"
#include <math.h>

#define ADSR_TOP 4096
enum adsr_state { ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};

class ADSREnv {
	public:

		uint16_t attack;
		double aSteps;
		uint16_t decay;
		double dSteps;
		uint16_t sustain;
		double sSteps;
		uint16_t release;
		double rSteps;
		uint16_t adsrAmp;
		adsr_state adsr_st;


		void calcAdsrSteps(void){
			aSteps = floor(ADSR_TOP/attack);
			dSteps = floor(ADSR_TOP/decay);
			sSteps = floor(ADSR_TOP/sustain);
			rSteps = floor(ADSR_TOP/release);
		}

		double updateEnv(void){

			switch (adsr_st)
			{
				case ATTACK_STATE:
				adsrAmp += aSteps;
				if (adsrAmp >= ADSR_TOP)
				{
					adsr_st = DECAY_STATE;
				}
				break;

				case DECAY_STATE:
				adsrAmp -= dSteps;
				if (adsrAmp <= 0)
				{
					adsr_st = IDLE_STATE;
				}

				break;

				case SUSTAIN_STATE:
				break;
				case RELEASE_STATE:
				break;
			}


		}

};


#endif /* INCLUDE_ADSR_H_ */
