/*
@file sound_generator.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 29, 2017
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

#include "sound_generator.h"

void SoundGenerator::gen_voice(synth_params_t *synth_params, q15_t* pSndGen){


	Oscillator* osc = (Oscillator*)synth_params->object_pool.osc;
	q15_t adsr_vol_amp = synth_params->adsr_vol_amp;
	q15_t lfo_amp = synth_params->lfo_amp;
	q15_t temp_buff[FRAME_SIZE];


	/** Get oscillator frame */
	osc->get_frame(synth_params,temp_buff,FRAME_SIZE);


	/** LFO modulation */
	//arm_scale_q15(temp_buff,lfo_amp,0,pSndGen,FRAME_SIZE);

	/** Apply ADSR envelope */
	arm_scale_q15(temp_buff,adsr_vol_amp,0,pSndGen,FRAME_SIZE);

}
