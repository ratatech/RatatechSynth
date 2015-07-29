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
#include "waveTables.h"

#include <math.h>



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

		int16_t sin_lut_q15[NR_OF_SAMPLES] = {                -1, 3, 6, 9, 12, 15, 18, 21, 24, 28,
	            31, 34, 37, 40, 43, 46, 48, 51, 54, 57, 60, 63, 65, 68, 71, 73, 76, 78, 81, 83,
	            85, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 109, 111, 112, 114, 115,
	            117, 118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 126, 127, 127, 127, 127,
	            127, 127, 127, 127, 127, 127, 127, 126, 126, 125, 124, 124, 123, 122, 121, 120,
	            119, 118, 117, 115, 114, 112, 111, 109, 108, 106, 104, 102, 100, 98, 96, 94, 92,
	            90, 88, 85, 83, 81, 78, 76, 73, 71, 68, 65, 63, 60, 57, 54, 51, 48, 46, 43, 40,
	            37, 34, 31, 28, 24, 21, 18, 15, 12, 9, 6, 3, 0, -4, -7, -10, -13, -16, -19, -22,
	            -25, -29, -32, -35, -38, -41, -44, -47, -49, -52, -55, -58, -61, -64, -66, -69,
	            -72, -74, -77, -79, -82, -84, -86, -89, -91, -93, -95, -97, -99, -101, -103,
	            -105, -107, -109, -110, -112, -113, -115, -116, -118, -119, -120, -121, -122,
	            -123, -124, -125, -125, -126, -127, -127, -128, -128, -128, -128, -128, -128,
	            -128, -128, -128, -128, -128, -127, -127, -126, -125, -125, -124, -123, -122,
	            -121, -120, -119, -118, -116, -115, -113, -112, -110, -109, -107, -105, -103,
	            -101, -99, -97, -95, -93, -91, -89, -86, -84, -82, -79, -77, -74, -72, -69, -66,
	            -64, -61, -58, -55, -52, -49, -47, -44, -41, -38, -35, -32, -29, -25, -22, -19,
	            -16, -13, -10, -7, -4,};

		int16_t tri_lut_q15[SAMPLES_TRIANGLE] = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
                52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
                72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
                92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
                109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124,
                125, 126, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115,
                114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99,
                98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79,
                78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59,
                58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39,
                38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,
                18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3,
                -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20,
                -21, -22, -23, -24, -25, -26, -27, -28, -29, -30, -31, -32, -33, -34, -35, -36,
                -37, -38, -39, -40, -41, -42, -43, -44, -45, -46, -47, -48, -49, -50, -51, -52,
                -53, -54, -55, -56, -57, -58, -59, -60, -61, -62, -63, -64, -65, -66, -67, -68,
                -69, -70, -71, -72, -73, -74, -75, -76, -77, -78, -79, -80, -81, -82, -83, -84,
                -85, -86, -87, -88, -89, -90, -91, -92, -93, -94, -95, -96, -97, -98, -99, -100,
                -101, -102, -103, -104, -105, -106, -107, -108, -109, -110, -111, -112, -113,
                -114, -115, -116, -117, -118, -119, -120, -121, -122, -123, -124, -125, -126,
                -127, -128, -128, -128, -127, -126, -125, -124, -123, -122, -121, -120, -119,
                -118, -117, -116, -115, -114, -113, -112, -111, -110, -109, -108, -107, -106,
                -105, -104, -103, -102, -101, -100, -99, -98, -97, -96, -95, -94, -93, -92, -91,
                -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75,
                -74, -73, -72, -71, -70, -69, -68, -67, -66, -65, -64, -63, -62, -61, -60, -59,
                -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43,
                -42, -41, -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27,
                -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11,
                -10, -9, -8, -7, -6, -5, -4, -3, -2, -1
		};

		// Set oscillator frequency in Hz for a fractional and integer phase increment
		void setFreqFrac(double freqHz)
		{
			ph_inc_frac = (int32_t)((((double)NR_OF_SAMPLES/(double)FS)*freqHz)*1048576);
			k_frac = ph_inc_frac & 0xFFFFF;


			if(shape == TRI)
			{
				ph_inc_frac = (int32_t)((((double)SAMPLES_TRIANGLE/(double)FS)*freqHz)*1048576);
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


		// Set oscillator shape
		void setOscShape(osc_shape shape_type)
		{
			shape = shape_type;

			switch (shape_type)
			{

			// Sinusoidal shape
			case SIN:

				// Store address of the sinus wavetable
				wavetable = sin_lut;



			break;

			// Square shape
			case SQU:

				// Store address of the square wavetable
				squareTop = 0xFF;
			break;

			// Sawtooth shape
			case SAW:

				// Store address of the sawtooth wavetable
				sawTop = 0xFF;
			break;

			// Triangle shape
			case TRI:
				//wavetable = tri_lut;

			break;
			}

		}

		// updateOsc function prototype
		uint16_t updateOsc(void);
		int16_t computeSine(void);
		int16_t computeSquare(void);
		int16_t computeTriangle(void);
		int16_t computeSaw(void);
		int16_t computeSine_arm_interp(void);
		int16_t computeTriangle_arm_interp(void);

};


#endif /* INCLUDE_OSCILLATOR_H_ */
