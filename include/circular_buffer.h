/*
 * circular_buffer.h
 *
 *  Created on: Jul 12, 2015
 *      Author: rata
 */

#ifndef INCLUDE_CIRCULAR_BUFFER_H_
#define INCLUDE_CIRCULAR_BUFFER_H_

#define BUFFER_SIZE 128

class CircularBuffer
{

public:
	/** Constructor
	*/
	CircularBuffer()
	{
		start = 0;
		end = 0;
	}


	uint8_t start;
	uint8_t end;
	uint16_t buffer[BUFFER_SIZE];

	bool check_status(void)
	{
		if ( ( end + 1 == start ) || ( start == 0 && end + 1 == BUFFER_SIZE ) )
					 return false;
		return true;

	}
	bool write(uint16_t sample)
	{
		if ( ( end + 1 == start ) || ( start == 0 && end + 1 == BUFFER_SIZE ) )
			 return false;


		buffer[end] = sample;
		end++;
		if (end >= BUFFER_SIZE)
		    end = 0;
		return true;

	}
	bool read(uint16_t *sample)
	{
		if ((start == end) || (start + 1 == end))
			return false;

		*sample = buffer[start];
		start++;
		if (start >= BUFFER_SIZE)
		    start = 0;

		return true;
	}
};



#endif /* INCLUDE_CIRCULAR_BUFFER_H_ */
