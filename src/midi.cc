/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Nov 15, 2015
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

#include "midi.h"
#include "stdio.h"
#include "soundGen.h"

uint8_t midiBuffer[MAX_MIDI_BYTES];
uint8_t midiMsgType;

void parseMsg(uint8_t byte){

	/** Check if message is status or data type */
	if(byte > 0x7F){
		//iprintf("MIDI IN - status = %i\n\n",byte);
		midiBuffer[0] = byte;
		midiMsgType = STATUS;
	}else{

		/** If not Status, classify between note or velocity data */
		switch(midiMsgType){
					/** If last message type was the status(MIDI first byte), now it
					should be the note byte */
					case STATUS:
						midiBuffer[1] = byte;
						midiMsgType = DATA_NOTE;

					break;
					/** Expecting note byte to parse the last byte with velocity or
					 * additional data */
					case DATA_NOTE:
						//iprintf("MIDI IN - vel = %i\n\n",byte);
						midiBuffer[2] = byte;
						midiMsgType = DATA_VEL;
						//iprintf("MIDI IN/ status:%i note:%i vel:%i\n",midiBuffer[0],midiBuffer[1],midiBuffer[2]);
						updateOscFreq(midiBuffer[1]);
					break;
		}

	}
}

/**
* USART1 interrupt handler
*/
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {

    	uint8_t midi_in = USART_ReceiveData(USART1);
    	parseMsg(midi_in);
    }

}
