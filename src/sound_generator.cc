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

	volatile uint32_t cycles; // number of cycles //
	Oscillator* 	osc 	= (Oscillator*)synth_params->object_pool.osc;
	LFO*			lfo		= (LFO*)		synth_params->object_pool.lfo;
	ADSR* 			adsr 	= (ADSR*)		synth_params->object_pool.adsr;

	q15_t mod_adsr, mod_lfo, sample_a, sample_b, mix_out;


	/** --- FRAME RATE PROCESSING ---- */

	/** Get ADSR sample and modulate the output */
	mod_adsr = adsr->get_sample(synth_params);


	reset_profiling(); // PROFILING START ---------------------------------------------------------------------------------------
	//
	/** --- SAMPLE RATE PROCESSING --- */
	for(uint i=0;i<FRAME_SIZE;i++){

		/** Get oscillator A and B samples */
		sample_a = osc->get_sample_dual(synth_params);

		/** Get LFO sample and modulate the output */
		mod_lfo = lfo->get_sample(synth_params);
		mix_out = mul_q15_q15(sample_a, mod_lfo);

		/** Get ADSR sample and modulate the output */
		mix_out = mul_q15_q15(mix_out,mod_adsr);

		/** Store output sample */
		*pSndGen++ = mix_out;

	}
	//
	cycles = get_cycles_profiling(); // PROFILING END --------------------------------------------------------------------------
	__asm("nop");

}
