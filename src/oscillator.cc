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

uint16_t Oscillator::updateOsc(void)
{

		static uint16_t buffSample = 0;

		// When interpolation enabled
		if (DO_INTERPOLATION)
		{

			buffSample = incPhaseFrac(phaseInd);
			phaseInd += phaseIncFrac;

			if (phaseInd>=NR_OF_SAMPLES-1)
			{
				phaseInd = 0;
			}

		}// If interpolation not enabled simply output samples in the wavetable
		else
		{
			buffSample = incPhase(phaseInd);
			phaseInd += phaseInc;
			if (phaseInd>=NR_OF_SAMPLES-1)
			{
				phaseInd = 0;
			}
		}

		return buffSample;
}


