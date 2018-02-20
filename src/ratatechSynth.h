/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RATATECHSYNTH_H
#define __RATATECHSYNTH_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "system_init.h"
#include "stm32f10x.h"
#include "timer.h"
#include "spi.h"
#include "settings.h"
#include "oscillator.h"
#include "audio_out.h"
#include "circular_buffer.h"
#include "adsr.h"
#include "utils.h"
#include "lfo.h"
#include "diag/Trace.h"
#include "midi.h"
#include "svf.h"
#include "types.h"
#include "mov_avg.h"
#include "sound_generator.h"
#include "drv/mux.h"
#include "drv/macro_mux.h"


// Add debugging tools
#include "tst_utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fill_buffer(void);
void low_rate_tasks(void);
void audio_gen(void);

uint32_t ButtonRead(GPIO_TypeDef*, uint16_t);

extern "C" {

void SysTick_Handler(void);
void TIM2_IRQHandler(void);
void TIM1_UP_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI5_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI6_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

void DMA1_Channel2_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
}


#endif /* __RATATECHSYNTH_H */

