/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, May 31, 2015
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

#include "system_init.h"
#include "ratatechSynth.h"


#define ADC1_DR_Address    ((uint32_t)0x4001244C)

uint16_t adc_read_test;


/****************************************************************************************
 *
 * STM32F01 PERIPHERALS
 *
 ***************************************************************************************/



void RCC_Clocks_Init(void)
{

	ErrorStatus HSEStartUpStatus;

	/* Reset the RCC clock configuration to default reset state */
	RCC_DeInit();

	/* Configure the High Speed External oscillator */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait for HSE start-up */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* Set the code latency value: FLASH Two Latency cycles */
		FLASH_SetLatency(FLASH_Latency_2);

		/* Configure the AHB clock(HCLK): HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		/* Configure the High Speed APB2 clcok(PCLK2): PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);

		/* Configure the Low Speed APB1 clock(PCLK1): PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);

		/* Configure the PLL clock source and multiplication factor     */
		/* PLLCLK = HSE*PLLMul = 8*9 = 72MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

		/* Enable PLL   */
		RCC_PLLCmd(ENABLE);

		/* Check whether the specified RCC flag is set or not */
		/* Wait till PLL is ready       */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Get System Clock Source */
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08);
	}

	/* Enable peripheral clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1 |
						RCC_APB2Periph_TIM1 | RCC_APB2Periph_USART1 | RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2 | RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 |
						RCC_APB1Periph_SPI2, ENABLE);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* ADCCLK = PCLK2/4 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);



}
/**
  * @brief  Configures GPIO.
  * @retval None
  */
void GPIO_Conf_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Configure PA4 pin as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* CS DAC (PA9) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 Rx */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* SHR_LATCH (PA11) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Tx as push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART3 Tx as push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

    /* Configure USART3 Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

	/* TIM3 PWM PINS */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            // Alt Function - Push Pull

	GPIO_Init( GPIOC, &GPIO_InitStructure );
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);


	/* Configure PB5/6/9 as OUTPUT for multiplexing */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void ButtonsInitEXTI(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    //NVIC structure to set up NVIC controller
    NVIC_InitTypeDef NVIC_InitStructure;
    //GPIO structure used to initialize Button pins
    //Connect EXTI Lines to Button Pins
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);


    //select EXTI line0
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    //select interrupt mode
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    //generate interrupt on rising edge
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    //enable EXTI line
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    //send values to registers
    EXTI_Init(&EXTI_InitStructure);

//    //select EXTI line1
//    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
//    EXTI_Init(&EXTI_InitStructure);
//
//    //select EXTI line2
//    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
//    EXTI_Init(&EXTI_InitStructure);
//
//    //select EXTI line3
//    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
//    EXTI_Init(&EXTI_InitStructure);
//
//    //select EXTI line4
//    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
//    EXTI_Init(&EXTI_InitStructure);
//
//    //select EXTI line5
//    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
//    EXTI_Init(&EXTI_InitStructure);
//
//    //select EXTI line6
//    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
//    EXTI_Init(&EXTI_InitStructure);

    //configure NVIC
    //select NVIC channel 0 to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    //set priority to lowest
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    //set subpriority to lowest
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    //enable IRQ channel
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);
//
//    //select NVIC channel 1 to configure
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
//    //update NVIC registers
//    NVIC_Init(&NVIC_InitStructure);
//
//    //select NVIC channel 2 to configure
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
//    //update NVIC registers
//    NVIC_Init(&NVIC_InitStructure);
//
//    //select NVIC channel 3 to configure
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
//    //update NVIC registers
//    NVIC_Init(&NVIC_InitStructure);
//
//    //select NVIC channel 4 to configure
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
//    //update NVIC registers
//    NVIC_Init(&NVIC_InitStructure);

//    //select NVIC channel 5 to configure
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI5_IRQn;
//    //update NVIC registers
//    NVIC_Init(&NVIC_InitStructure);
//
//    //select NVIC channel 6 to configure
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI6_IRQn;
//    //update NVIC registers
//    NVIC_Init(&NVIC_InitStructure);

}

/**
 * Configure and initialize ADC Peripheral
 */
void ADC_Conf_Init(void){

	ADC_DeInit(ADC1);

	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel14 configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 0, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_13Cycles5 );

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));

	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);


}

/**
 * Configure and initialize DMA Peripheral
 */
void DMA_Conf_Init(synth_params_t* synth_params){

	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&synth_params->adc_read;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = ADC_ARRAY_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* Enable DMA1 interrupt on channel1 */
    //DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

	q15_t* _pOut = synth_params->pOut;
	q15_t* _pBuff;

	/* DMA1 channel2 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_Channel2);

    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = FRAME_SIZE*2;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)_pOut;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)_pBuff;

    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

/**
 * Configure and initialize USART Peripheral
 */
void USART_Conf_Init(void){

    /* USART configuration structure for USART */
    USART_InitTypeDef usart_InitStructure;

    USART_ClockInitTypeDef usart_ClockInitStructure;

    /* NVIC configuration structure for USART */
    NVIC_InitTypeDef NVIC_InitStructure;


	// ---------------------------------------------------------------------------------------//
	//		USART1
    // ---------------------------------------------------------------------------------------//
    USART_Cmd(USART1, ENABLE);
    /* Baud rate 31250, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart_InitStructure.USART_BaudRate = 31250;
    usart_InitStructure.USART_WordLength = USART_WordLength_8b;
    usart_InitStructure.USART_StopBits = USART_StopBits_1;
    usart_InitStructure.USART_Parity = USART_Parity_No ;
    usart_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	/* USART1 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    /* Configure USART1 */
    USART_Init(USART1, &usart_InitStructure);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART1_IRQn);

#if 1
	// ---------------------------------------------------------------------------------------//
	//		USART2
    // ---------------------------------------------------------------------------------------//
    USART_Cmd(USART2, ENABLE);
    /* Baud rate 115200, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart_InitStructure.USART_BaudRate = 115200;
    usart_InitStructure.USART_WordLength = USART_WordLength_8b;
    usart_InitStructure.USART_StopBits = USART_StopBits_1;
    usart_InitStructure.USART_Parity = USART_Parity_No ;
    usart_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	/* USART2 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    /* Configure USART2 */
    USART_Init(USART2, &usart_InitStructure);
    /* Enable RXNE interrupt */
    //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    /* Enable USART2 global interrupt */
    NVIC_EnableIRQ(USART2_IRQn);
#endif

	// ---------------------------------------------------------------------------------------//
	//		USART3
    // ---------------------------------------------------------------------------------------//
    USART_Cmd(USART3, ENABLE);
    /* Baud rate 115200, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart_InitStructure.USART_BaudRate = 115200;
    usart_InitStructure.USART_WordLength = USART_WordLength_8b;
    usart_InitStructure.USART_StopBits = USART_StopBits_1;
    usart_InitStructure.USART_Parity = USART_Parity_No ;
    usart_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;


	/* USART3 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    /* Configure USART3 */
    USART_Init(USART3, &usart_InitStructure);
    /* Enable USART3 Receive and Transmit interrupts */
    //USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    /* Enable USART3 global interrupt */
    NVIC_EnableIRQ(USART3_IRQn);

}

/****************************************************************************************
 *
 * EXTERNAL HARDWARE
 *
 ***************************************************************************************/


void init_rotary_encoder(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Step 1: Initialize GPIO as input for rotary encoder
    // PB7 (TIM4_CH2) (encoder pin A), PB8 (TIM4_CH3) (encoder pin B)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Step 2: Setup TIM4 for encoder input
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
        TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
    TIM_Cmd(TIM4, ENABLE);
}

/**
 * Init system related routines(STM32F1) and all prefipherals needed for the synthesizer
 */
void ratatech_init(synth_params_t* synth_params){

	RCC_ClocksTypeDef RCC_Clocks;
	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/** SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);    //4 bits for preemp priority 0 bit for sub priority

    /** Configure and init peripherals */
	GPIO_Conf_Init();
	SPI_Config();
	ButtonsInitEXTI();
	ADC_Conf_Init();
	USART_Conf_Init();
	DMA_Conf_Init(synth_params);
	TIM_Config();

	/** Configure and init HW */
	init_rotary_encoder();
    // LCD initialization
    lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);

}



