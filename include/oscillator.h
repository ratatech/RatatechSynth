/*
 * oscillator.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_OSCILLATOR_H_
#define INCLUDE_OSCILLATOR_H_

#include "ratatechSynth.h"
#include "waveTables.h"
#include <math.h>

#define DO_INTERPOLATION true



class Oscillator {

	public:
		double phaseInd;
		double phaseIncFrac;
		uint16_t phaseInc;
		uint16_t K;
		double KFrac;
		const unsigned char *wavetable;
		uint16_t tableShift;
		double sampleDebug;
		double sampleDebug2;
		double sampleDebug3;
		uint16_t sampleDebugInt;
		unsigned char debugChar;
		uint16_t sampleRef;

		// Set oscillator frequency in Hz for a fractional and integer phase increment
		void setFreqFrac(uint16_t freqHz)
		{
			phaseIncFrac = (((double)NR_OF_SAMPLES/(double)FS)*freqHz);
			phaseInc = floor(phaseIncFrac);
			KFrac = phaseIncFrac - phaseInc;
			K = round(KFrac*256); // round or floor? needs to be tested
		}

		// Read next sample in a wavetable from a given phase index without interpolation
		uint16_t incPhase(double phaseInd)
		{
			uint16_t indInt = floor(phaseInd);
			return (uint16_t)wavetable[indInt];
		}

		// Read next sample in a wavetable from a given phase index with linear interpolation
		uint16_t incPhaseFrac(int phaseInd)
		{

			uint16_t nextSample = wavetable[phaseInd+tableShift]<<8;
			//uint16_t nextSample = pgm_read_byte(wavetable+phaseInd)<<8;
			uint16_t interpSample = (nextSample-sampleRef);
			interpSample *= K;
			interpSample >>= 8;
			interpSample += (sampleRef);
			sampleRef = nextSample;
			return interpSample;
		}

		// Set oscillator shape
		void setOscShape(uint16_t shape)
		{

			switch (shape)
			{

			// Sinusoidal shape
			case 0:

				// Store address of the sinus wavetable
				wavetable = sinWt;

			break;

			// Square shape
			case 1:

				// Store address of the square wavetable
				wavetable = sawWt[0];
			break;

			// Sawtooth shape
			case 2:

				// Store address of the sawtooth wavetable
				wavetable = sawWt[0];
			break;

			// Triangle shape
			case 3:

				// Store address of the triangle wavetable
				wavetable = sawWt[0];
			break;
			}

		}

		// updateOsc function prototype
		uint16_t updateOsc(void);
		uint16_t computeSine(void);

};


#endif /* INCLUDE_OSCILLATOR_H_ */
