/*
 * timer.h
 *
 *  Created on: Jun 3, 2015
 *      Author: rata
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "stm32f1xx_hal.h"

void timer_Config(void);

#define TIMx                           TIM3
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()


/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM3_IRQn
#define TIMx_IRQHandler                TIM3_IRQHandler

#endif /* INCLUDE_TIMER_H_ */
