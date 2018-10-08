/*
@file settings.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 4, 2017
This file is part of Ratatech 3019

    Ratatech 3019 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ratatech 3019 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
*/

#include "settings.h"
#include "tables.h"

void init_settings(synth_params_t* synth_params, object_pool_t object_pool){

		/** Oscillator settings */
		synth_params->osc_params.shape_osc = SIN;
		synth_params->osc_params.mixAB = 0;
		synth_params->osc_params.osc_detune = 1;
		synth_params->osc_params.freq_frac = 1000;
		synth_params->osc_params.banlim_ind = 0;

		/** LFO settings */
		synth_params->lfo_params.shape_osc = SIN;
		synth_params->lfo_params.lfo_amo = 0;
		synth_params->lfo_params.freq_frac = 100;

		/** Moving average filter settings */
		synth_params->mov_avg_params.beta = 0;
		synth_params->mov_avg_params.state = 0 ;
		synth_params->mov_avg_params.init_state = 0;

		/** ADSR settings */
		synth_params->adsr_params.ph_inc_att = adsr_time_phinc_lut[1000];
		synth_params->adsr_params.ph_inc_dec = adsr_time_phinc_lut[3000];
		synth_params->adsr_params.ph_inc_rel = adsr_time_phinc_lut[4094];
		synth_params->adsr_params.sustain_level = MAX_AMP;
		synth_params->adsr_vol_amp = 0;

		/** Object pool */
		synth_params->object_pool = object_pool;

		/** MIDI */
		synth_params->midi_dest = OSC1;
		synth_params->pitch = 0;
		synth_params->vel = 0;
		synth_params->note_ON = 0;

		//synth_params->adc_read[0] = 960;
		synth_params->FM_mod_amp = 0;
		synth_params->I = 0;
		synth_params->FM_synth = 0;

		/** Mux */
		synth_params->DMA_ADC_transfer_complete = false;

}
