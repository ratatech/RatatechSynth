/*
@file mov_avg.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 13, 2017
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
#ifndef INCLUDE_MOV_AVG_H_
#define INCLUDE_MOV_AVG_H_

#include "arm_math.h"
#include "tables.h"
#include "types.h"
#include <math.h>
#include "settings.h"

/**
 * Moving average filter class
 */
class MovAvg {

	public:
		q31_t beta;
		q31_t state;


		/** Constructor.
		 *
		 * @param osc_param Structure holding init parameters
		 */
		MovAvg(void){
		}

		/** Init moving average filter
		 *
		 * @param mov_avg_param Structure holding init parameters
		 */
		void init(mov_avg_params_t* mov_avg_param){
            state = mov_avg_param->init_state;
            beta  = mov_avg_param->beta;
		}

		/**
		 * Update moving average filter
		 * @param x New value
		 * @return New filtered sample
		 */
		q15_t update(q15_t x);

		/**
		 * Process an input data frame through the moving average filter
		 * @param synth_params Synth global structure
		 * @param pMovAvg Pointer to store the filtered samples
		 */
		void process_frame(synth_params_t *synth_params, q15_t* pIn, q15_t* pOut);



};




#endif /* INCLUDE_MOV_AVG_H_ */
