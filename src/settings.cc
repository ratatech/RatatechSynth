/*
@file settings.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 4, 2017
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

#include "settings.h"

void init_settings(synth_params_t* synth_params){

		/** Oscillator settings */
		synth_params->osc_params.shape_osc = SIN;
		synth_params->osc_params.osc_mix = 0;
		synth_params->osc_params.freq_frac = 1000;

		/** LFO settings */
		synth_params->lfo_params.shape_osc = SIN;
		synth_params->lfo_params.lfo_amo = 0;
		synth_params->lfo_params.freq_frac = 100;

		/** Moving average filter settings */
		synth_params->mov_avg_params.beta = 0;
		synth_params->mov_avg_params.state = 0 ;
		synth_params->mov_avg_params.init_state = 0;

		/** ADSR settings */
		synth_params->adsr_params.beta_att = 0;
		synth_params->adsr_params.beta_dec = 0;
		synth_params->adsr_params.beta_rel = 0;


		synth_params->midi_dest = OSC1;
		synth_params->adsr_amp_vol = 0;

		synth_params->pitch = 0;
		synth_params->vel = 0;
		synth_params->note_ON = 0;
		synth_params->FM_mod_amp = 0;
		synth_params->I = 0;
		synth_params->FM_synth = 0;
}
