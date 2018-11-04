/*
@file synthSettings.cpp


@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Nov 4, 2018
This file is part of Ratatech 3019.

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

#include "synthSettings.h"

// Implementation file SynthSettings.cpp
SynthSettings* SynthSettings::pInstance_ = 0;
SynthSettings::SynthSettings()
{}

void SynthSettings::intDefaultSettings(void){

	/** Oscillator settings */
	SynthSettings::osc_params.shape_osc = SIN;
	SynthSettings::osc_params.mixAB = 0;
	SynthSettings::osc_params.osc_detune = 1;
	SynthSettings::osc_params.freq_frac = 1000;
	SynthSettings::osc_params.banlim_ind = 0;

	/** LFO settings */
	SynthSettings::lfo_params.shape_osc = SIN;
	SynthSettings::lfo_params.lfo_amo = 0;
	SynthSettings::lfo_params.freq_frac = 100;

	/** Moving average filter settings */
	SynthSettings::mov_avg_params.beta = 0;
	SynthSettings::mov_avg_params.state = 0 ;
	SynthSettings::mov_avg_params.init_state = 0;

	/** ADSR settings */
	//SynthSettings::adsr_params.ph_inc_att = adsr_time_phinc_lut[1000];
	//SynthSettings::adsr_params.ph_inc_dec = adsr_time_phinc_lut[3000];
	//SynthSettings::adsr_params.ph_inc_rel = adsr_time_phinc_lut[4094];
	SynthSettings::adsr_params.sustain_level = MAX_AMP;
	SynthSettings::adsr_vol_amp = 0;

	/** MIDI */
	SynthSettings::midi_dest = OSC1;
	SynthSettings::pitch = 0;
	SynthSettings::vel = 0;
	SynthSettings::note_ON = 0;

	//SynthSettings::adc_read[0] = 960;
	SynthSettings::FM_mod_amp = 0;
	SynthSettings::I = 0;
	SynthSettings::FM_synth = 0;

	/** Mux */
	SynthSettings::DMA_ADC_transfer_complete = false;
}

