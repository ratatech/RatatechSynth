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


/** Object instances */
Oscillator osc;
LFO lfo;
Mixer mixer;
MIDI midi;
CircularBuffer 	out_buffer;

/** Parameter structures */
synth_params_t synth_params;


uint16_t u_data;

bool status = true;


int main(void)
{

	/** Init system and peripherals */
	ratatech_init();

	/** Load initial default settings */
	init_settings(&synth_params);

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(1000);
	osc.set_shape(SIN);

	// Configure oscillator 2
//	osc2.init(&synth_params.osc_params);
//	osc2.set_shape(SAW);

	/** Configure lfo */
	osc_shape_t shape_lfo = SIN;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(0.1);

	//Pre-fill the output buffer
	fill_buffer();

	/* *****************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{
		// Fill audio buffer with a new sample
		fill_buffer();
	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){
	lfo.get_sample(&synth_params);

	if(midi.attack_trigger){
		iprintf("MIDI IN!!!\n");
		midi.attack_trigger = false;

	}

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
	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	while(out_buffer.check_status()){
	/* *****************************************************************************************
	 * AUDIO CHAIN START
	 *
	 * *****************************************************************************************/

		/** 1 - Oscillator 1 */
		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc);

		status = out_buffer.write_frame(pOsc);
	}

}

void audio_gen(void){

	uint16_t out_sample;
	out_buffer.read(&out_sample);
//	iprintf("Audio sample out =");
//	intNum2CharStr(out_sample);
//	iprintf("\n");
	audio_out_write(out_sample);

}


/**
* USART1 interrupt handler
*/
void USART1_IRQHandler(void)
{

	//trace_printf("MIDI Rx\n");
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
    	uint16_t midi_in = USART_ReceiveData(USART1);
    	midi.parseMsg(midi_in);

    }

    /* ------------------------------------------------------------ */
    /* Other USART1 interrupts handler can go here ...             */
}
