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

#define ADSR_TOP 0xFFFF
#define ENV_LUT_LENGTH 256
enum adsr_state { ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};

const unsigned char env_lut[ENV_LUT_LENGTH] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
};


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
				if (adsrAmp >= ADSR_TOP || (adsrAmp + aSteps)<ADSR_TOP )
				{
					adsr_st = DECAY_STATE;
					break;

				}
				adsrAmp += aSteps;

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
