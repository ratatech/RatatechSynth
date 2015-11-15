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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1 |
						  RCC_APB2Periph_TIM1 | RCC_APB2Periph_USART1 | RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_SPI2, ENABLE);





}
/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg LED2
  * @retval None
  */
void GPIO_Conf_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;


	/* Configure PC7 as out LED */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure PA5 as out LED */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Configure PA0 PA1 pins as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Configure PA1pins as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PB0 pins as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* CS DAC (PA9)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* CS POT_F2P1 (PA11)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* CS POT_F1P1 (PA12)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* CS POT_F1P2 (PA8)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART Rx */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void ButtonsInitEXTI(void)
{
    //enable AFIO clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
    EXTI_InitTypeDef EXTI_InitStructure;
    //NVIC structure to set up NVIC controller
    NVIC_InitTypeDef NVIC_InitStructure;
    //GPIO structure used to initialize Button pins
    //Connect EXTI Lines to Button Pins
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
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

    //select EXTI line1
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_Init(&EXTI_InitStructure);

    //select EXTI line2
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_Init(&EXTI_InitStructure);

    //select EXTI line3
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_Init(&EXTI_InitStructure);

    //select EXTI line4
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_Init(&EXTI_InitStructure);

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

    //select NVIC channel 1 to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);

    //select NVIC channel 2 to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);

    //select NVIC channel 3 to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);

    //select NVIC channel 4 to configure
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    //update NVIC registers
    NVIC_Init(&NVIC_InitStructure);

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

	ADC_InitTypeDef ADC_InitStructure;

	  /* ADC1 configuration ------------------------------------------------------*/
	  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_InitStructure.ADC_ScanConvMode = DISABLE; // Single Channel
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Scan on Demand
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfChannel = 1;
	  ADC_Init(ADC1, &ADC_InitStructure);

	  /* ADC1 regular channel1 configuration */
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);

	  /* Enable ADC1 */
	  ADC_Cmd(ADC1, ENABLE);

	  /* Enable ADC1 reset calibaration register */
	  ADC_ResetCalibration(ADC1);

	  /* Check the end of ADC1 reset calibration register */
	  while(ADC_GetResetCalibrationStatus(ADC1));

	  /* Start ADC1 calibaration */
	  ADC_StartCalibration(ADC1);

	  /* Check the end of ADC1 calibration */
	  while(ADC_GetCalibrationStatus(ADC1));

	  /* Start ADC1 Software Conversion */
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);


}

/**
 * Configure and initialize USART Peripheral
 */
void USART_Conf_Init(void){

    /* USART configuration structure for USART1 */
    USART_InitTypeDef usart1_InitStructure;

    /* NVIC configuration structure for USART1 */
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);
    /* Baud rate 31250, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart1_InitStructure.USART_BaudRate = 31250;
    usart1_InitStructure.USART_WordLength = USART_WordLength_8b;
    usart1_InitStructure.USART_StopBits = USART_StopBits_1;
    usart1_InitStructure.USART_Parity = USART_Parity_No ;
    usart1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;


	/* USART1 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    /* Configure USART1 */
    USART_Init(USART1, &usart1_InitStructure);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART1_IRQn);


}



