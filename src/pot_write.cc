/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Oct 30, 2015
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

#include "pot_write.h"




using namespace std;

void pot_write(uint8_t cmd, uint8_t pot_val)
{

	// Split 12bit data and store it into 2 8bit
	uint8_t dataHigh = 0b00000011;
	uint8_t dataLow  = (0x00FF & 0x0000);



	// CS High
	GPIOA->BRR = GPIO_Pin_8;

	// Transmit the two 8bit SPI messages
	SPI_send(SPI2,dataHigh);
	SPI_send(SPI2,dataLow);

	// CS Low
	GPIOA->BSRR = GPIO_Pin_8;


}
