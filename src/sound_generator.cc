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

	Oscillator* 	osc1 = (Oscillator*)synth_params->object_pool.osc1;
	Oscillator* 	osc2 = (Oscillator*)synth_params->object_pool.osc2;
	LFO*			lfo	= (LFO*)		synth_params->object_pool.lfo;
	ADSR* 			adsr = (ADSR*)		synth_params->object_pool.adsr;

	q15_t adsr_vol_amp;
	q15_t* lfo_amp;

	q15_t temp_buff1[FRAME_SIZE];
	q15_t temp_buff2[FRAME_SIZE];

	/** Get oscillator frame */
	osc1->get_frame(synth_params,temp_buff1,FRAME_SIZE);

	/** Get oscillator frame */
	//osc2->get_frame(synth_params,temp_buff2,FRAME_SIZE);

	//Mixer mixer;

	//mixer.mix(synth_params,temp_buff1,temp_buff2,temp_buff1,MAX_AMP>>1);

//	/** Compute a new LFO envelope frame/sample */
//	lfo.get_frame(&synth_params,pLfo,LFO_BLOCK_SIZE);
//
	/** Compute a new ADSR envelope frame/sample */
	adsr->get_sample(synth_params,&adsr_vol_amp);

	/** LFO modulation */
	//arm_scale_q15(temp_buff,lfo_amp,0,pSndGen,FRAME_SIZE);


	/** Apply ADSR envelope */
	arm_scale_q15(temp_buff1,MAX_AMP,0,pSndGen,FRAME_SIZE);

}
