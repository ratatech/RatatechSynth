/*
 * circular_buffer.h
 *
 *  Created on: Jul 12, 2015
 *      Author: rata
 */

#ifndef INCLUDE_CIRCULAR_BUFFER_H_
#define INCLUDE_CIRCULAR_BUFFER_H_

#include "utils.h"

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

	/**
	 * Check buffer status
	 * @return Return status
	 */
	bool check_status(void);

	/**
	 * Write a sample to the circular buffer
	 * @param sample Audio sample
	 * @return Return status
	 */
	bool write(uint16_t sample);

	/**
	 * Read a sample from the circular buffer
	 * @param sample Pointer to the audio sample to be read
	 * @return Return status
	 */
	bool read(uint16_t *sample);


	/**
	 * Write a frame to the circular buffer
	 * @param pFrame Audio frame
	 * @return Return status
	 */
	bool write_frame(q15_t* pFrame);

};



#endif /* INCLUDE_CIRCULAR_BUFFER_H_ */
