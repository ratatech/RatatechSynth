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
		uint16_t triangleTop;
		uint16_t triangleMax;
		uint16_t sawTop;
		uint16_t squareTop;
		osc_shape shape;
		double buffSample_ref;



		// Set oscillator frequency in Hz for a fractional and integer phase increment
		void setFreqFrac(double freqHz)
		{
			phaseIncFrac = (((double)NR_OF_SAMPLES/(double)FS)*freqHz);
			phaseInc = floor(phaseIncFrac);
			KFrac = phaseIncFrac - phaseInc;
			K = round(KFrac*256); // round or floor? needs to be tested

			if(shape == TRI)
			{
				phaseIncFrac = (((double)(triangleTop)/(double)FS)*freqHz*2);
				phaseInc = floor(phaseIncFrac);
				KFrac = phaseIncFrac - phaseInc;
				K = round(KFrac*(triangleTop<<1)); // round or floor? needs to be tested
				triangleMax = triangleTop*2;


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


		// Set oscillator shape
		void setOscShape(osc_shape shape_type)
		{
			shape = shape_type;

			switch (shape_type)
			{

			// Sinusoidal shape
			case SIN:

				// Store address of the sinus wavetable
				wavetable = sinWt;

			break;

			// Square shape
			case SQU:

				// Store address of the square wavetable
				wavetable = sawWt[0];
				squareTop = 0xFF;
			break;

			// Sawtooth shape
			case SAW:

				// Store address of the sawtooth wavetable
				wavetable = sawWt[0];
				sawTop = 0xFF;
			break;

			// Triangle shape
			case TRI:
				triangleTop = 0xFF;

			break;
			}

		}

		// updateOsc function prototype
		uint16_t updateOsc(void);
		uint16_t computeSine(void);
		uint16_t computeSquare(void);
		uint16_t computeTriangle(void);
		uint16_t computeSaw(void);

};


#endif /* INCLUDE_OSCILLATOR_H_ */
