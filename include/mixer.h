/*
@file mixer.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 25, 2017
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
#ifndef INCLUDE_MIXER_H_
#define INCLUDE_MIXER_H_

#include "ratatechSynth.h"
#include "types.h"
#include "arm_math.h"
#include "tables.h"
#include <math.h>



/**
 * Oscillator class
 */
class Mixer {

	public:
		int32_t osc_mix,osc1_mix_temp,osc2_mix_temp;

	/** Constructor.
	*/
	Mixer(void){
		osc_mix = 0;
		osc1_mix_temp = 0;
		osc2_mix_temp = 0;
	}

	 /**
	  *  Mix samples
	  * @param sample_osc1 Oscillator 1 sample
	  * @param sample_osc2 Oscillator 2 sample
	  * @param synth_params Synth global structure
	  * @return mix_out The mixed output sample
	  */
	int32_t mix(int32_t sample_osc1,int32_t sample_osc2,synth_params_t *synth_params);

};



#endif /* INCLUDE_MIXER_H_ */
