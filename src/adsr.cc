/*
@file adsr.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 14, 2017
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

#include "adsr.h"

using namespace std;

/**
 * Get a new adsr envelope frame
 * @param synth_params Synth global structure
 * @param pAdsr ADSR envelope output buffer
 */
void ADSR::get_frame(synth_params_t *synth_params, q15_t* pAdsr)
{
	q15_t * pOut = pAdsr;	/* output pointer */

	for(int i=0;i<FRAME_SIZE;i++){
		*pOut++ = update(0x7fff);
	}

}

///**
// * Process an input data frame through the moving average filter
// * @param synth_params Synth global structure
// * @param pMovAvg Pointer to store the filtered samples
// */
//void MovAvg::process_frame(synth_params_t *synth_params, q15_t* pIn, q15_t* pOut)
//{
//
//	q15_t *_pIn = pIn;		/* input pointer */
//	q15_t *_pOut = pOut;	/* output pointer */
//
//	 // Generate samples and store it in the output buffer
//	 for(int i=0;i<FRAME_SIZE;i++){
//		 *pOut++ =  update(*pIn++);
//	 }
//
//}
