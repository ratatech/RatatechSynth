/*
@file dma_spi_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 23, 2017
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

#include <stdio.h>
#include "unity.h"
#include "ratatechSynth.h"
#include "tst_utils.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

/**
 * ADSR unit test reference buffer
 */
q15_t buff_dma_spi_ref[BUFF_SIZE] = {
		25599,31231,12031,-16384,-32512,-23296,3839,27903,29695,8191,-19968,-32767,-19968,8191,29695,27903,3839,-23296,-32512,-16384,12031,31231,25599,
		0,-26112,-31744,-12544,15871,31999,22783,-4352,-28416,-28022,-7536,15814,24759,14181,-6056,-20162,-18278,-2869,13779,18867,9152,-7095,-17652,
		-14308,-554,13697,16551,6459,-8551,-16866,-12022,1972,14279,15145,4166,-10131,-16589,-10091,4133,14964,14044,2059,-11705,-16324,-8350,6033,15656,
		12827,0,-13077,-15894,-6408,7943,16012,11399,-2178,-14215,-15110,-4354,9730,16130,9857,-4353,-15106,-14209,-2305,11392,16000,8064,-6272,-15872,
		-13056,-512,12799,15615,6143,-8192,-16256,-11648,1919,13951,14847,4095,-9984,-16383,-10112,4095,14847,13951,2047,-11648,-16256,-8320,6015,15615,
		12799,0,-13056,-15872,-6400,7935,15999,11391,-2176,-14208,-14526,-4025,8652,13794,8106,-3443,-11491,-10395,-1621,7707,10411,5045,-3775,-9186,
		-7266,-275,6588,7729,2924,-3751,-7157,-4986,781,5462,5591,1483,-3478,-5487,-3257,1268,4423,3997,564,-3087,-4142,-2039,1417,3538,2789,0,-2632,
		-3077,-1193,1422,2757,1909,-347,-2179,-2228,-618,1326,2115,1242,-528,-1762,-1594,-249,1182,1595,773,-579,-1409,-1115,-42,1010,1184,448,-575,
		-1098,-765,119,837,857,227,-534,-841,-500,194,677,612,86,-473,-635,-313,217,542,427,0,-404,-472,-183,217,422,292,-54,-334,-342,-95,203,323,
		190,-81,-271,-244,-39,180,244,118,-89,-216,-171,-7,154,181,68,-88,-168,-118,18,127,131,34,-82,-129,-77,29,103,93,

};




/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * Oscillator class instance
 */
Oscillator osc;

/**
 * Unit test output buffer
 */
q15_t pdma_spi_out [BUFF_SIZE];

#define BufferSize         32
#define SPI_MASTER                   SPI1
#define SPI_MASTER_CLK               RCC_APB2Periph_SPI1
#define SPI_MASTER_GPIO              GPIOA
#define SPI_MASTER_GPIO_CLK          RCC_APB2Periph_GPIOA
#define SPI_MASTER_PIN_SCK           GPIO_Pin_5
#define SPI_MASTER_PIN_MISO          GPIO_Pin_6
#define SPI_MASTER_PIN_MOSI          GPIO_Pin_7
#define SPI_MASTER_DMA               DMA1
#define SPI_MASTER_DMA_CLK           RCC_AHBPeriph_DMA1
#define SPI_MASTER_Rx_DMA_Channel    DMA1_Channel2
#define SPI_MASTER_Rx_DMA_FLAG       DMA1_FLAG_TC2
#define SPI_MASTER_Tx_DMA_Channel    DMA1_Channel3
#define SPI_MASTER_Tx_DMA_FLAG       DMA1_FLAG_TC3
#define SPI_MASTER_DR_Base           0x4001300C


/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
DMA_InitTypeDef    DMA_InitStructure;
uint8_t SPI_MASTER_Buffer_Rx[BufferSize], SPI_SLAVE_Buffer_Rx[BufferSize];
volatile uint8_t SPI_MASTERCRCValue = 0, SPI_SLAVECRCValue = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

uint16_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x0100,0x0200,0x0300,0x0400,0x0500,0x0600,0x0700,0x0800,0x0900,0x0A00,0x0B00,0x0C00,0x0D00,0x0E00,0x0F00,0x1000,
											0x1100,0x1200,0x1300,0x1400,0x1500,0x1600,0x1700,0x1800,0x1900,0x1A00,0x1B00,0x1C00,0x1D00,0x1E00,0x1F00,0x2000};

/**
 * 	DMA SPI test
 */
void test_dma_spi_out(void){


//    DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);
//    DMA_StructInit(&DMA_InitStructure);
//
//
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
//    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)SPI_MASTER_Buffer_Tx;
//    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
//    DMA_InitStructure.DMA_BufferSize         = BufferSize;
//    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
//    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Disable;
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
//    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
//    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
//
//
//    DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure);
//    DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, ENABLE);
//
//
////	/* SPI_MASTER_Tx_DMA_Channel configuration ---------------------------------*/
////	DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);
////	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
////	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI_MASTER_Buffer_Tx;
////	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
////	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
////	DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure);
//
//	/* Enable SPI_MASTER DMA Tx request */
//	SPI_I2S_DMACmd(SPI_MASTER, SPI_I2S_DMAReq_Tx, ENABLE);

	int i=0;
	while (1)
	{
//		/* Transfer complete */
//		while(!DMA_GetFlagStatus(SPI_MASTER_Tx_DMA_FLAG));
//
//		/* Wait for SPI_MASTER data reception: CRC transmitted by SPI_SLAVE */
//		while(SPI_I2S_GetFlagStatus(SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
		audio_out_write(i<<1);

//		iprintf("i = ");
//		intNum2CharStr(i);
//		iprintf("\n");
		i++;
		i%=0x2000;

	}
}


int main(void)
{

	/** Init system and peripherals */
	ratatech_init();


	/** Load initial default settings */
	init_settings(&synth_params);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	/** Ready to start test  */
    iprintf("\nTEST:  DMA SPI \n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_dma_spi_out);

    /** FInish unity */
    return UNITY_END();
}
