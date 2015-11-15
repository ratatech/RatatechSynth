/*
@file fileName.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Nov 15, 2015
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
#ifndef INCLUDE_MIDI_H_
#define INCLUDE_MIDI_H_


#include "ratatechSynth.h"


enum midi_msg_type_e {STATUS,DATA_NOTE,DATA_VEL};

//MIDI status type definitions
// www.midi.org/techspecs/midimessa
enum status_type_e{
	note_on    = 0x90,
	note_off   = 0x80,
	pitch_bend = 0xE0,
};

/**
 * MIDI class
 */
class MIDI {

	public:

		uint16_t midi_buffer[3];
		midi_msg_type_e midi_msg_type;
		bool note_ON,attack_trigger,new_event;

		/** Constructor.
		@param pin The pin number used for the SPI chip select.
		*/
		MIDI(void){
			memset(midi_buffer, 0, sizeof(midi_buffer));
			midi_buffer[0] = note_off;
		}

		/**
		 * Parse the information arriving from the USART interface
		 * @param byte
		 */
		void parseMsg(uint16_t byte);

		/**
		 * After the three bytes have been reveived, trigger events and update data.
		 */
		void update(synth_params_t *synth_params){

			synth_params->note_ON = note_ON;

			if(note_ON){
				synth_params->pitch = midi_buffer[1];
				synth_params->vel = midi_buffer[2];
			}

		}

};


#endif /* INCLUDE_MIDI_H_ */
