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

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT))
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);

	return (int16_t) arm_linear_interp_q15(sin_lut_q15,ph_ind_frac,NR_OF_SAMPLES);


}

int16_t Oscillator::computeTriangle(void)
{

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT<<1))
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT<<1);

	return (int16_t) arm_linear_interp_q15(tri_lut_q15,ph_ind_frac,SAMPLES_TRIANGLE);

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
int16_t Oscillator::computeSquare(void)
{

	ph_ind_frac += ph_inc_frac;

	if(top)
	{
		square_out = 0x7FFF;
	}else
	{
		square_out =  -128<<8;
	}

	if (ph_ind_frac>=(NR_OF_SAMPLES_20_BIT))
	{
		ph_ind_frac -= (NR_OF_SAMPLES_20_BIT);
		top = !top;
	}
	return (int16_t)(square_out);

}
