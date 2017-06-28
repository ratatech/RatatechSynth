/*
@file circular_buffer.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 27, 2017
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

#include "circular_buffer.h"

/**
 * Check buffer status
 * @return Return status
 */
bool CircularBuffer::check_status(void)
{
	if ( ( end + 1 == start ) || ( start == 0 && end + 1 == BUFFER_SIZE ) )
				 return false;
	return true;

}

/**
 * Write a sample to the circular buffer
 * @param sample Audio sample
 * @return Return status
 */
bool CircularBuffer::write(uint16_t sample)
{
	if ( ( end + 1 == start ) || ( start == 0 && end + 1 == BUFFER_SIZE ) )
		 return false;


	buffer[end] = sample;
	end++;
	if (end >= BUFFER_SIZE)
		end = 0;
	return true;

}

/**
 * Read a sample from the circular buffer
 * @param sample Pointer to the audio sample to be read
 * @return Return status
 */
bool CircularBuffer::read(uint16_t *sample)
{
	if ((start == end) || (start + 1 == end))
		return false;

	*sample = buffer[start];
	start++;
	if (start >= BUFFER_SIZE)
		start = 0;

	return true;
}


/**
 * Write a frame to the circular buffer
 * @param pFrame Audio frame
 * @return Return status
 */
bool CircularBuffer::write_frame(q15_t* pFrame)
{
	bool status = true;
	q15_t * pOut = pFrame;	/** Output pointer */
	uint16_t sample;
	int i=0;
	while(i<FRAME_SIZE & status)
	{
		sample = int16_2_uint16(*pOut++);
		status = write(sample);
		i++;
	}

	return status;

}
