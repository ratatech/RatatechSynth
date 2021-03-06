/*
 * spi.h
 *
 *  Created on: Jun 7, 2015
 *      Author: rata
 */

#include "stm32f10x_spi.h"
#include "diag/Trace.h"

#ifndef SPI_H_
#define SPI_H_

void SPI_Config(void);
uint8_t SPI_send(SPI_TypeDef*,uint16_t);
uint8_t SPI_DMA_send(SPI_TypeDef* SPIx);


#endif /* SPI_H_ */
