/*
@file fileName.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Nov 1, 2015
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
#ifndef INCLUDE_DIGITAL_POT_H_
#define INCLUDE_DIGITAL_POT_H_

#include "ratatechSynth.h"


/**
 * Digital potentiometer class
 */
class DIGI_POT {

	public:

		uint16_t CS_pin;

		/** Constructor.
		@param pin The pin number used for the SPI chip select.
		*/
		DIGI_POT(uint16_t pin){
			CS_pin = pin;
		}

		/**
		 * Writes a 8bit value into the digital potentiometer
		 * @param val
		 */
		void write(uint8_t val);

};





#endif /* INCLUDE_DIGITAL_POT_H_ */
