/*
 * circular_buffer.h
 *
 *  Created on: Jul 12, 2015
 *      Author: rata
 */

#ifndef INCLUDE_CIRCULAR_BUFFER_H_
#define INCLUDE_CIRCULAR_BUFFER_H_

#include "utils.h"
#include "types.h"
#include "stm32f10x_conf.h"
#include "stm32f10x.h"


#define NFRAMES  BUFFER_SIZE/FRAME_SIZE
class CircularBuffer
{

public:
//	/** Constructor
//	*/
//	CircularBuffer()
//	{
//		start = 0;
//		end = 0;
//		frame_read = 0;
//		frame_write = 0;
//		dma_transfer_complete = true;
//	}

	uint16_t start;
	uint16_t end;
	uint16_t frame_read;
	uint16_t frame_write;
	q15_t buffer[BUFFER_SIZE];
	volatile bool dma_transfer_complete;

	/**
	 * Init buffer
	 */
	void init(void);

	/**
	 * Check buffer status
	 * @return Return status
	 */
	bool check_status(void);

	/**
	 * Check if there is a free slot in the buffer for writing a frame
	 * @return True if free, False otherwise
	 */
	bool hasFrameFree(void);

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

	static CircularBuffer* getInstance(void){ // Unique point of access
			if (!pInstance_)
				pInstance_ = new CircularBuffer;
			return pInstance_;
	}
private:
	CircularBuffer(); // Prevent clients from creating a new CircularBuffer
	CircularBuffer(const CircularBuffer&); // Prevent clients from creating
	// a copy of the CircularBuffer
	static CircularBuffer* pInstance_; // The one and only instance
};




#endif /* INCLUDE_CIRCULAR_BUFFER_H_ */
