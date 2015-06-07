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

/* Prescaler declaration */
uint32_t uwPrescalerValue = 0;



/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	trace_printf("InUtero\n");
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

}


int
main(int argc, char* argv[])
{

	/*##-1- Configure the TIM peripheral #######################################*/
	/* -----------------------------------------------------------------------
	In this example TIM3 input clock (TIM3CLK)  is set to APB1 clock (PCLK1) x2,
	since APB1 prescaler is set to 4 (0x100).
	   TIM3CLK = PCLK1*2
	   PCLK1   = HCLK/2
	=> TIM3CLK = PCLK1*2 = (HCLK/2)*2 = HCLK = SystemCoreClock
	To get TIM3 counter clock at 10 KHz, the Prescaler is computed as following:
	Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	Prescaler = (SystemCoreClock /10 KHz) - 1

	Note:
	 SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f1xx.c file.
	 Each time the core clock (HCLK) changes, user had to update SystemCoreClock
	 variable value. Otherwise, any configuration based on this variable will be incorrect.
	 This variable is updated in three ways:
	  1) by calling CMSIS function SystemCoreClockUpdate()
	  2) by calling HAL API function HAL_RCC_GetSysClockFreq()
	  3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
	----------------------------------------------------------------------- */

	/* Compute the prescaler value to have TIMx counter clock equal to 10000 Hz */
	uwPrescalerValue = (uint32_t)(SystemCoreClock / 10000) - 1;

	/* Set TIMx instance */
	TimHandle.Instance = TIMx;

	/* Initialize TIMx peripheral as follows:
	   + Period = 10000 - 1
	   + Prescaler = (SystemCoreClock/10000) - 1
	   + ClockDivision = 0
	   + Counter direction = Up
	*/
	TimHandle.Init.Period            = 10000 - 1;
	TimHandle.Init.Prescaler         = uwPrescalerValue;
	TimHandle.Init.ClockDivision     = 0;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;

	if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
	{
		/* Initialization Error */
		trace_printf("Timer inizialization error!\n");
	}

	/*##-2- Start the TIM Base generation in interrupt mode ####################*/
	/* Start Channel1 */
	if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	{
		/* Starting Error */
		trace_printf("Timer starting error!\n");
	}




	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();

	/* Configure the timer*/
	timer_Config();

	uint32_t a=0;
	// Infinite loop
	while (1)
	{
	  a++;
	  a %=10;
	  trace_printf("a %i\n", a);
	   // ADD YOUR CODE HERE.
	  /* Insert delay 100 ms */
	  //HAL_Delay(100);
	  //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	}
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = 16
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};

  /* Configure PLL ------------------------------------------------------*/
  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
  /* Enable HSI and activate PLL with HSi_DIV2 as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  oscinitstruct.HSEState        = RCC_HSE_OFF;
  oscinitstruct.LSEState        = RCC_LSE_OFF;
  oscinitstruct.HSIState        = RCC_HSI_ON;
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}


// ----------------------------------------------------------------------------
