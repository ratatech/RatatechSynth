/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 7, 2015
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

#include "spi.h"

void Spi_Config(void){

	extern SPI_HandleTypeDef SpiHandle;

	/* Private typedef -----------------------------------------------------------*/
	/* Private define ------------------------------------------------------------*/
	enum {
		TRANSFER_WAIT,
		TRANSFER_COMPLETE,
		TRANSFER_ERROR
	};

	/* Private macro -------------------------------------------------------------*/
	/* Uncomment this line to use the board as master, if not it is used as slave */
	#define MASTER_BOARD

	/* Private variables ---------------------------------------------------------*/
	/* SPI handler declaration */
	extern SPI_HandleTypeDef SpiHandle;

	/* transfer state */
	__IO uint32_t wTransferState = TRANSFER_WAIT;

	  /*##-1- Configure the SPI peripheral #######################################*/
	  /* Set the SPI parameters */
	  SpiHandle.Instance               = SPIx;
	  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
	  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
	  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	  SpiHandle.Init.CRCPolynomial     = 7;
	  SpiHandle.Init.NSS               = SPI_NSS_SOFT;

	#ifdef MASTER_BOARD
	  SpiHandle.Init.Mode = SPI_MODE_MASTER;
	#else
	  SpiHandle.Init.Mode = SPI_MODE_SLAVE;
	#endif /* MASTER_BOARD */

	  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
	  {
	    /* Initialization Error */
		  trace_printf("SPI Init error!\n");
	  }

	#ifdef MASTER_BOARD
	  /* SPI block is enabled prior calling SPI transmit/receive functions, in order to get CLK signal properly pulled down.
	     Otherwise, SPI CLK signal is not clean on this board and leads to errors during transfer */
	  //__HAL_SPI_ENABLE(&SpiHandle);

	#endif /* MASTER_BOARD */

}
