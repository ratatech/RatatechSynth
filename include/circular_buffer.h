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
#define NFRAMES  BUFFER_SIZE/FRAME_SIZE
class CircularBuffer
{

public:
	/** Constructor
	*/
	CircularBuffer()
	{
		start = 0;
		end = 0;
		frame_read = 0;
		frame_write = 0;
		dma_transfer_complete = false;
	}


	uint16_t start;
	uint16_t end;
	uint16_t frame_read;
	uint16_t frame_write;
	q15_t buffer[BUFFER_SIZE];
	volatile bool dma_transfer_complete;

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
	bool write(q15_t sample);

	/**
	 * Read a sample from the circular buffer
	 * @param sample Pointer to the audio sample to be read
	 * @return Return status
	 */
	bool read(q15_t *sample);


	/**
	 * Write a frame to the circular buffer
	 * @param pFrame Audio frame
	 * @return Return status
	 */
	bool write_frame(q15_t* pFrame);

	/**
	 * Write a frame to the circular buffer using DMA
	 * @param pFrame Audio frame
	 * @return Return status
	 */
	bool write_frame_dma(q15_t* pFrame);

	/**
	 * Check DMA transfer status
	 * @return Return status
	 */
	bool get_dma_transfer_status(void);

	/**
	 * Set DMA transfer status
	 */
	void set_dma_transfer_status(void);

};



#endif /* INCLUDE_CIRCULAR_BUFFER_H_ */
