/*
@file fileName.cc

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

#include "midi.h"
#include "ratatechSynth.h"

/**
 * Parse incomming MIDI message
 * @param byte Incomming MIDI byte
 */
void MIDI::parseMsg(uint16_t byte){

	/** Check if message is status or data type */
	if(byte > 0x7F){
		switch(byte){

			case note_on:
				if(midi_buffer[0] == note_off){
					attack_trigger = true;
				}
				midi_buffer[0] = note_on;
				midi_msg_type = STATUS;
				note_ON = true;


			break;

			case note_off:

				midi_buffer[0] = note_off;
				midi_msg_type = STATUS;
				note_ON = false;

			break;
		}


	}else{

		/** If not Status, classify between note or velocity data */
		switch(midi_msg_type){

					case STATUS:

						midi_buffer[1] = byte;
						midi_msg_type = DATA_NOTE;

					break;

					case DATA_NOTE:

						midi_buffer[2] = byte;
						midi_msg_type = DATA_VEL;

					break;
		}

	}

	/** Trigger a new event just after reading the three bytes */
	if(midi_msg_type == DATA_VEL){
		if(midi_buffer[2]>0){
			new_event = true;
		}else{
			new_event = false;
		}

	}



}
