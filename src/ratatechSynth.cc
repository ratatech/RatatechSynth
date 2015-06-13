//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <ratatechSynth.h>



// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via STDOUT).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the STDOUT output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------


TIM_HandleTypeDef   TimHandle;
SPI_HandleTypeDef   SpiHandle;
uint8_t aTxBuffer[] = "****SPI - Two Boards communication based on Polling **** SPI Message ******** SPI Message ******** SPI Message ****";
uint16_t testData;
uint8_t *audioOutPt;
uint32_t Timeout;

#define SPI_TX_SIZE                       (COUNTOF(aTxBuffer) - 1)

// sine lookup table pre-calculated
uint8_t sinetable[256] = {
  128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,
  176,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,
  218,220,222,224,226,228,230,232,234,236,237,239,240,242,243,245,
  246,247,248,249,250,251,252,252,253,254,254,255,255,255,255,255,
  255,255,255,255,255,255,254,254,253,252,252,251,250,249,248,247,
  246,245,243,242,240,239,237,236,234,232,230,228,226,224,222,220,
  218,216,213,211,209,206,204,201,199,196,193,191,188,185,182,179,
  176,174,171,168,165,162,159,156,152,149,146,143,140,137,134,131,
  128,124,121,118,115,112,109,106,103,99, 96, 93, 90, 87, 84, 81,
  79, 76, 73, 70, 67, 64, 62, 59, 56, 54, 51, 49, 46, 44, 42, 39,
  37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10,
  9,  8,  7,  6,  5,  4,  3,  3,  2,  1,  1,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  1,  1,  2,  3,  3,  4,  5,  6,  7,  8,
  9,  10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35,
  37, 39, 42, 44, 46, 49, 51, 54, 56, 59, 62, 64, 67, 70, 73, 76,
  79, 81, 84, 87, 90, 93, 96, 99, 103,106,109,112,115,118,121,124
};

uint8_t testTable[2] = {
  255,0
};


uint16_t i=4095;


/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	trace_printf("InUtero\n");
//	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_7);
//	//testData = sinetable[i];
//	testData = 0xFF;
//	testData |= 0x3000;
//
////	i++;
////	i%=4095;
//	i--;
//	if(i<1)i=4095;
//
//
//
//
//	GPIOA->BRR = GPIO_PIN_9;
//	testData = (i >> 8)|0x30;
////	if (HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &testData,1,5000)==HAL_OK)
////	{
////		trace_printf("Successfully transmitted over SPI\n");
////	}
//	HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &testData,1,5000);
//
//	testData = (i & 0xFF )|0x1;
////	if (HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &testData,1,5000)==HAL_OK)
////	{
////		trace_printf("Successfully transmitted over SPI\n");
////	}
//	HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &testData,1,5000);
//	GPIOA->BSRR = GPIO_PIN_9;






}

uint8_t SPIx_send(uint8_t data){

	SPIx->DR = data;
	//SPIx->DR = data; // write data to be transmitted to the SPI data register
	while (!(SPI1->SR & SPI_SR_TXE));
	//while( !(SPIx->SR & SPI_FLAG_TXE) ); // wait until transmit complete
	while( !(SPIx->SR & SPI_FLAG_RXNE) ); // wait until receive complete
	while( SPIx->SR & SPI_FLAG_BSY ); // wait until SPI is not busy anymore
	return SPIx->DR; // return received data from SPI data register
}

int
main(int argc, char* argv[])
{
	uint32_t a=0;
	testData = 23;
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();

	/* Configure the timer*/
	timer_Config();

	/* Configure the SPI*/
	Spi_Config();

	int del=0;
	uint16_t outputValue = 0; // a word is a 16-bit number
	uint8_t data = 0; // and a byte is an 8-bit number

	#define lowByte(w) ((w) & 0xff)
	#define highByte(w) ((w) >> 8)

	// Infinite loop
	while (1)
	{
//	  a++;
//	  a %=10;
//	  trace_printf("a %i\n", a);
//			if (HAL_SPI_Transmit(&SpiHandle,(uint8_t*)aTxBuffer, SPI_TX_SIZE,5000)==HAL_OK)
//			{
//				trace_printf("Successfully transmitted over SPI");
//			}
	   // ADD YOUR CODE HERE.
	  /* Insert delay 100 ms */
	  //HAL_Delay(100);
	  //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);


		for (int a=0; a<=4095; a++)
		{
			outputValue = a;
			GPIOA->BRR = GPIO_PIN_9;
			data = highByte(outputValue);
			data = 0b00001111 & data;
			data = 0b00110000 | data;
			SPIx_send(data);
			//HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &data,1,5000);
			data = lowByte(outputValue);
			//HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &data,1,5000);
			SPIx_send(data);
			GPIOA->BSRR = GPIO_PIN_9;
			HAL_Delay(del);
		}
		HAL_Delay(del+25);
		for (int a=4095; a>=0; --a)
		{
			outputValue = a;
			GPIOA->BRR = GPIO_PIN_9;
			data = highByte(outputValue);
			data = 0b00001111 & data;
			data = 0b00110000 | data;
			HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &data,1,5000);
			data = lowByte(outputValue);
			HAL_SPI_Transmit(&SpiHandle,(uint8_t*) &data,1,5000);
			GPIOA->BSRR = GPIO_PIN_9;
			HAL_Delay(del);
		}
		HAL_Delay(del+25);
	}
}



// ----------------------------------------------------------------------------
