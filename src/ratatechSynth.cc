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

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

TIM_HandleTypeDef   TimHandle;


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

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
