/*
 * oscillator.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_OSCILLATOR_H_
#define INCLUDE_OSCILLATOR_H_

#include "ratatechSynth.h"
#include "arm_math.h"
#include "tables.h"

#include <math.h>


/**
BABLALBALBALBL
ABABABA
BABAB
BABABA
@todo BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
@note BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
@section BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
*/
class Oscillator {

	public:
		double phaseInd;
		double phaseIncFrac;
		uint16_t phaseInc;
		uint16_t K;
		double KFrac;
		const char *wavetable;
		uint16_t tableShift;
		double sampleDebug;
		double sampleDebug2;
		double sampleDebug3;
		uint16_t sampleDebugInt;
		unsigned char debugChar;
		int32_t sampleRef;
		uint16_t triangleTop;
		uint16_t triangleMax;
		uint16_t sawTop;
		uint16_t squareTop;
		osc_shape shape;


		int32_t ph_inc_frac;
		int32_t ph_ind_frac;
		int32_t k_frac;
		int32_t triangle_out;
		int32_t triangle_ref;
		int32_t square_out;

		bool top;


		/** BLALALALALALAFAFDDFAF
		@param frequency FADFADFADFDFD
		*/
		void setFreqFrac(double freqHz)
		{
			ph_inc_frac = (int32_t)((((double)LUT_SIN_8_BIT/(double)FS)*freqHz)*1048576);
			k_frac = ph_inc_frac & 0xFFFFF;


			if(shape == TRI)
			{
				ph_inc_frac = (int32_t)((((double)LUT_TRI_8_BIT/(double)FS)*freqHz)*1048576);
				k_frac = ph_inc_frac & 0xFFFFF;


			}

			if(shape == SAW)
			{
				phaseIncFrac = (((double)(sawTop)/(double)FS)*freqHz*2);
				phaseInc = floor(phaseIncFrac);
				KFrac = phaseIncFrac - phaseInc;
				K = round(KFrac*(sawTop<<1)); // round or floor? needs to be tested

			}
			if(shape == SQU)
			{
				phaseIncFrac = (((double)(squareTop)/(double)FS)*freqHz*2);
				phaseInc = floor(phaseIncFrac);
				phaseInd = squareTop;

			}
		}


		// Function prototypes
		uint16_t update(amp_mod_t *amp_mod);
		uint16_t computeSine(amp_mod_t *amp_mod);
		uint16_t computeSquare(amp_mod_t *amp_mod);
		uint16_t computeTriangle(amp_mod_t *amp_mod);
		uint16_t computeSaw(amp_mod_t *amp_mod);


};


#endif /* INCLUDE_OSCILLATOR_H_ */
