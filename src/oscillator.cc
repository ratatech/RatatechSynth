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



uint16_t Oscillator::computeSine(amp_mod_t *amp_mod)
{
	int32_t interpLut;
	uint16_t u_interpLut;

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(LUT_SIN_20_BIT))
		ph_ind_frac -= (LUT_SIN_20_BIT);


	// Interpolate LUT
	interpLut = arm_linear_interp_q15((int16_t*)sin_lut_q15,ph_ind_frac,LUT_SIN_8_BIT)<<8;

	// Modulate signal with the ADSR envelope
	interpLut = ((int32_t)(interpLut)*(amp_mod->adsr_amp)>>15);

	// Modulate signal with the LFO
	interpLut = ((int32_t)(interpLut)*(amp_mod->lfo_amp)>>15);

	// Convert to unsigned
	u_interpLut = int16_2_uint16(interpLut);

	// Shift back to 12 bits required by the DAC
	u_interpLut>>=4;

	return u_interpLut;


}

uint16_t Oscillator::computeTriangle(amp_mod_t *amp_mod)
{
	int32_t interpLut;
	uint16_t u_interpLut;

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(LUT_SIN_20_BIT<<1))
		ph_ind_frac -= (LUT_SIN_20_BIT<<1);

	// Interpolate LUT
	interpLut = arm_linear_interp_q15((int16_t*)tri_lut_q15,ph_ind_frac,LUT_SIN_8_BIT<<1)<<8;

	// Modulate signal with the ADSR envelope
	//interpLut = ((int32_t)(interpLut)*(amp_mod->adsr_amp)>>15);

	// Modulate signal with the LFO
	//interpLut = ((int32_t)(interpLut)*(amp_mod->lfo_amp)>>15);

	// Convert to unsigned
	u_interpLut = int16_2_uint16(interpLut);

	// Shift back to 12 bits required by the DAC
	u_interpLut>>=4;

	return u_interpLut;

}



uint16_t Oscillator::computeSaw(amp_mod_t *amp_mod)
{

	int32_t interpLut;
	uint16_t u_interpLut;

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(LUT_SIN_20_BIT))
		ph_ind_frac -= (LUT_SIN_20_BIT);


	// Interpolate LUT
	interpLut = arm_linear_interp_q15((int16_t*)saw_lut_q15,ph_ind_frac,LUT_SIN_8_BIT)<<8;

	// Modulate signal with the ADSR envelope
	interpLut = ((int32_t)(interpLut)*(amp_mod->adsr_amp)>>15);

	// Modulate signal with the LFO
	interpLut = ((int32_t)(interpLut)*(amp_mod->lfo_amp)>>15);

	// Convert to unsigned
	u_interpLut = int16_2_uint16(interpLut);

	// Shift back to 12 bits required by the DAC
	u_interpLut>>=4;

	return u_interpLut;
}

uint16_t Oscillator::computeSquare(amp_mod_t *amp_mod)
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

	if (ph_ind_frac>=(LUT_SIN_20_BIT))
	{
		ph_ind_frac -= (LUT_SIN_20_BIT);
		top = !top;
	}

	// Modulate signal with the ADSR envelope
	sq_gen = ((int32_t)(sq_gen)*(amp_mod->adsr_amp)>>15);

	// Modulate signal with the LFO
	sq_gen = ((int32_t)(sq_gen)*(amp_mod->lfo_amp)>>15);

	// Convert to unsigned
	u_sq_gen = int16_2_uint16(sq_gen);

	// Shift back to 12 bits required by the DAC
	u_sq_gen>>=4;

	return u_sq_gen;

}

uint16_t Oscillator::update(amp_mod_t *amp_mod)
{
	uint16_t u_data;

	// Get a new oscillator sample
	switch (shape)
	{
		case SIN:
			u_data = Oscillator::computeSine(amp_mod);
			break;

		case SQU:
			u_data = Oscillator::computeSquare(amp_mod);
			break;

		case SAW:
			u_data = Oscillator::computeSaw(amp_mod);
			break;

		case TRI:
			u_data = Oscillator::computeTriangle(amp_mod);
			break;

	}
	return u_data;
}
