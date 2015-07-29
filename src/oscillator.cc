/*
 @file fileName.cc

 @brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

 @ Created by Jordi Hidalgo, Ratatech, Jun 21, 2015
 This file is part of XXXXXXX

 XXXXXXX is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 XXXXXXX is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
 */

#include "oscillator.h"
using namespace std;

int16_t Oscillator::computeSine(void)
{

		int32_t nextSample = wavetable[(ph_ind_frac)>>20]<<8;
		int64_t interpSample = (nextSample-sampleRef);
		interpSample *= k_frac;
		interpSample >>= 20;
		interpSample += (sampleRef);
		sampleRef = nextSample;

		ph_ind_frac += ph_inc_frac;
		//trace_printf("ph_ind_frac val = %i\n",ph_ind_frac>>20);
		if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT))
		{
			ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);
		}

		return (int16_t)interpSample;
		//return (int16_t)nextSample;

}



uint16_t Oscillator::computeTriangle(void)
{
	static uint16_t buffSample = 0;

	phaseInd += phaseIncFrac;
	if (phaseInd>=512)
	{
		phaseInd = 0;
	}

	if(phaseInd<255){
		buffSample = (uint16_t)phaseInd;
		buffSample_ref = phaseInd;
		if(phaseInd + phaseIncFrac >= 255)
			buffSample_ref = phaseInd + phaseIncFrac;
	}
	else{
		buffSample = (uint16_t)(buffSample_ref - phaseIncFrac);
		buffSample_ref = buffSample;
//		if(phaseInd + phaseIncFrac >= 512)
//			buffSample_ref = phaseInd + phaseIncFrac;
	}


//	if(phaseInd > triangleTop)
//		phaseInd = triangleTop;
//	if(phaseInd < 0)
//		phaseInd = 1;




	return (uint16_t)buffSample;
}


int16_t Oscillator::computeSaw(void)
{

	ph_ind_frac += ph_inc_frac;

	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT>>1))
	{
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);
	}
	return (int16_t)(ph_ind_frac>>12);
}
uint16_t Oscillator::computeSquare(void)
{

		static uint16_t buffSample = 0;
		static bool top = true;
		double squareVal;


		phaseInd += phaseIncFrac;

		if (phaseInd>=squareTop-1)
		{
			phaseInd = 0;
			top = !top;

		}

		if(top)
		{
			squareVal = squareTop>>1;
		}else
		{
			squareVal =  0;
		}

		buffSample = (uint16_t)squareVal;
		return buffSample;
}
