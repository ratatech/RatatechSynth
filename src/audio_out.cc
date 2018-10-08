/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 21, 2015
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

#include "audio_out.h"


uint8_t dataLow,dataHigh;

using namespace std;

/**
 * Write one sample to the DAC
 * @param data Unsigned 16bit samples
 */
void audio_out_write(uint16_t data)
{
	// Drive CS low, enabling the shift register.
	GPIOA->BRR = GPIO_Pin_9;

    // Send 24 bit word as specified in MAX5216 datasheet.
    // Transmit the 24 bits of data through SPI (MSB first and LSB last).
    // The transmission is done in two 16b SPI calls instead of three of 8b.
    // DAC output is the same but a substantial number of cycles is reduced.
	SPI_send(SPI1,(uint16_t)(data>>2 | 0x4000));
	SPI_send(SPI1,(uint16_t)(data<<14));

	// Drive CS High
	GPIOA->BSRR = GPIO_Pin_9;

	// Let CS High for at least 20ns as specified in the MAX5216.
	// 1clk cycle ~= 13.889ns @72MHz
    __asm__("nop");
    __asm__("nop");

}
