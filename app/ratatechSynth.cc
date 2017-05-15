/*
 @file ratatechSynth.cc

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
#include "ratatechSynth.h"

using namespace std;


// Object instances
Oscillator osc1,osc2;
interrupt_vars_t interrupt_vars;

/** ADSR object instance*/
Mixer mixer;

// Structure instances
synth_params_t synth_params;
uint16_t u_data;

bool status = true;


int main(void)
	{

	// Init system and peripherals
	ratatech_init();

	set_interrupt_vars(&interrupt_vars);

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SQU;
	osc1.set_shape(shape_osc1);
	osc1.set_freq_frac(1000);

	// Configure oscillator 2
	osc_shape_t shape_osc2 = SAW;
	osc2.set_shape(shape_osc2);
	osc2.set_freq_frac(1000);

	/* Mix Parameter between osc1 and osc2
	 *
	 * synth_params.osc_mix = 32768;
	 * 0x0000 Mix 100% Osc2
	 * 0x7FFF Mix 100% Osc1
	 * 0x3FFF Mix 50%
	 *
	 * */
	synth_params.osc_mix = 0x2FFF;

	//Pre-fill the output buffer
	fill_buffer();

	/* *****************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{

		// Events happening every CONTROL_RATE
		if(interrupt_vars.low_rate_ISR_flag){
			low_rate_tasks();
		}

		// Fill audio buffer with a new sample
		fill_buffer();
	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){

}

/**
 * Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{
	int32_t sample_osc1, sample_osc2, osc_mix;
	while(interrupt_vars.out_buffer.check_status()){
	/* *****************************************************************************************
	 * AUDIO CHAIN START
	 *
	 * *****************************************************************************************/

		/** 1 - Oscillator 1 */
		sample_osc1 =  osc1.get_sample(&synth_params);

		/** 2 - Oscillator 2 */
		sample_osc2 =  osc2.get_sample(&synth_params);

		/** 3- Mix samples */
		osc_mix = mixer.mix(sample_osc1,sample_osc2,&synth_params);

		/** 4-  Mini VCA */
		//osc_mix = mul_int16(osc_mix,adsr_vol.adsr_amp);

		/** 5- Fill output buffer */
		status = interrupt_vars.out_buffer.write( int16_2_uint16(osc_mix));
	}

}

