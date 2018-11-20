/*
@file circular_buffer.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 27, 2017
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

#include "circular_buffer.h"


CircularBuffer* CircularBuffer::pInstance_ = 0;
CircularBuffer::CircularBuffer()
{}

/**
 * Init buffer
 */
void CircularBuffer::init(void){
	this->start = 0;
	this->end = 0;
	this->frame_read = 0;
	this->frame_write = 0;
	this->dma_transfer_complete = true;
}

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
 * Check if there is a free slot in the buffer for writing a frame
 * @return True if free, False otherwise
 */
bool CircularBuffer::hasFrameFree(void)
{
	return frame_read != frame_write;
}

/**
 * Write a sample to the circular buffer
 * @param sample Audio sample
 * @return Return status
 */
bool CircularBuffer::write(q15_t sample)
{

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
bool CircularBuffer::read(q15_t *sample)
{
	*sample = buffer[start++];
	start %= BUFFER_SIZE;
	if((start % FRAME_SIZE) == 0){
		frame_read++;
		frame_read %= NFRAMES;
	}

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
	arm_copy_q15(pOut,buffer+end,FRAME_SIZE);
	end+=FRAME_SIZE;
	end %= BUFFER_SIZE;
	frame_write++;
	frame_write %= NFRAMES;

	return status;

}

/**
 * Write a frame to the circular buffer using DMA
 * @param pFrame Audio frame
 * @return Return status
 */
bool CircularBuffer::write_frame_dma(q15_t* pFrame)
{
	bool status = true;

	/** Output pointer */
	q15_t * pOut = pFrame;

	/** Disable dma transfer flag*/
	dma_transfer_complete = false;

	/** DMA transfer tasks */
	DMA_Cmd(DMA1_Channel2, DISABLE);
    DMA1_Channel2->CNDTR = FRAME_SIZE;
    DMA1_Channel2->CPAR = (uint32_t)pOut;
    DMA1_Channel2->CMAR = (uint32_t)buffer+(end<<1);
    DMA_ClearFlag(DMA1_FLAG_GL2);
    DMA_ClearFlag(DMA1_FLAG_TC2);
    DMA_Cmd(DMA1_Channel2, ENABLE);

    /** Increase sample and frame counters*/
	end+=FRAME_SIZE;
	end %= BUFFER_SIZE;
	frame_write++;
	frame_write %= NFRAMES;

	return status;

}

bool CircularBuffer::get_dma_transfer_status(void){
	return(dma_transfer_complete);
}

void CircularBuffer::set_dma_transfer_status(void){
	dma_transfer_complete = true;
}
