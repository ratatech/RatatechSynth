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



uint16_t Oscillator::computeSine(int16_t adsrEnv)
{
	int32_t interpLut;
	uint16_t u_interpLut;

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT))
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);


	// Interpolate LUT
	interpLut = arm_linear_interp_q15(sin_lut_q15,ph_ind_frac,NR_OF_SAMPLES)<<8;

	// Modulate signal with the ADSR envelope
	interpLut = ((int32_t)(interpLut)*(adsrEnv)>>15);

	// Convert to unsigned
	u_interpLut = int16_2_uint16(interpLut);

	// Shift back to 12 bits required by the DAC
	u_interpLut>>=4;

	return u_interpLut;


}

uint16_t Oscillator::computeTriangle(int16_t adsrEnv)
{
	int32_t interpLut;
	uint16_t u_interpLut;

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT<<1))
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT<<1);

	// Interpolate LUT
	interpLut = arm_linear_interp_q15(tri_lut_q15,ph_ind_frac,NR_OF_SAMPLES<<1)<<8;

	// Modulate signal with the ADSR envelope
	interpLut = ((int32_t)(interpLut)*(adsrEnv)>>15);

	// Convert to unsigned
	u_interpLut = int16_2_uint16(interpLut);

	// Shift back to 12 bits required by the DAC
	u_interpLut>>=4;

	return u_interpLut;

}



uint16_t Oscillator::computeSaw(int16_t adsrEnv)
{
	int32_t saw_gen;
	uint16_t u_saw_gen;

	ph_ind_frac += ph_inc_frac;

	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT>>1))
	{
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);
	}
	saw_gen = ph_ind_frac>>12;

	// Modulate signal with the ADSR envelope
	saw_gen = ((int32_t)(saw_gen)*(adsrEnv)>>15);

	// Convert to unsigned
	u_saw_gen = int16_2_uint16(saw_gen);

	// Shift back to 12 bits required by the DAC
	u_saw_gen>>=4;

	return u_saw_gen;
}
uint16_t Oscillator::computeSquare(int16_t adsrEnv)
{
	int32_t sq_gen;
	uint16_t u_sq_gen;

	ph_ind_frac += ph_inc_frac;

	if(top)
	{
		sq_gen = 0x7FFF;
	}else
	{
		sq_gen =  -128<<8;
	}

	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT))
	{
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);
		top = !top;
	}

	// Modulate signal with the ADSR envelope
	sq_gen = ((int32_t)(sq_gen)*(adsrEnv)>>15);

	// Convert to unsigned
	u_sq_gen = int16_2_uint16(sq_gen);

	// Shift back to 12 bits required by the DAC
	u_sq_gen>>=4;

	return u_sq_gen;

}
