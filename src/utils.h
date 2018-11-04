/*
 * utils.h
 *
 *  Created on: Jul 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

uint16_t int16_2_uint16(q15_t x);
uint16_t int32_2_uint16(int32_t x);
int32_t mul_int16(int16_t x1,int16_t x2);
q15_t mul_q15_q15(q15_t x1,q15_t x2);


 /**
 * Mix two values with a given mix parameter
 * @param a			Value A to mix
 * @param b			Value B to mix
 * @param mix_par	Mix parameter
  * @return mix		Mix output
  */
q15_t mix(q15_t a, q15_t b, q15_t mix_par);

/**
 * Mix two frames with a given mix parameter
 * @param pFrame_a		Frame A to mix
 * @param pFrame_b 		Frame B to mix
 * @param pFrame_mix 	Destination mix frame
 * @param mix_par 		Mix parameter
 */
void mix_frames(q15_t* pFrame_a, q15_t* pFrame_b, q15_t* pFrame_mix , q15_t mix_par);

/**
 * Linear interpolatin
 * @param y0			Sample at instant t0
 * @param y1			Sample at instant t1
 * @param k				Fractional part
 * @param shift_frac	Shift to be applied corresponding to the fractional part multiplication
 * @return				Interpolated sample
 */
inline q15_t interp_q15(q15_t y0,q15_t y1,uint32_t k,uint8_t shift_frac){
	q63_t y = ((q63_t)(y1 - y0)*k)>>shift_frac;
	y += y0;
	return (q15_t)y;
}

#define RATATECH_PROFILING

#ifdef RATATECH_PROFILING

/* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
  #define KIN1_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))
    /*!< DWT Control register */
  #define KIN1_DWT_CYCCNTENA_BIT       (1UL<<0)
    /*!< CYCCNTENA bit in DWT_CONTROL register */
  #define KIN1_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004))
    /*!< DWT Cycle Counter register */
  #define KIN1_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
  #define KIN1_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */

#define KIN1_InitCycleCounter() \
  KIN1_DEMCR |= KIN1_TRCENA_BIT
  /*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */

#define KIN1_ResetCycleCounter() \
  KIN1_DWT_CYCCNT = 0
  /*!< Reset cycle counter */

#define KIN1_EnableCycleCounter() \
  KIN1_DWT_CONTROL |= KIN1_DWT_CYCCNTENA_BIT
  /*!< Enable cycle counter */

#define KIN1_DisableCycleCounter() \
  KIN1_DWT_CONTROL &= ~KIN1_DWT_CYCCNTENA_BIT
  /*!< Disable cycle counter */

#define KIN1_GetCycleCounter() \
  KIN1_DWT_CYCCNT
  /*!< Read cycle counter register */

/** Usage :


	uint32_t cycles; // number of cycles //

	KIN1_InitCycleCounter(); 			// enable DWT hardware
	KIN1_ResetCycleCounter(); 			// reset cycle counter
	KIN1_EnableCycleCounter(); 			// start counting
	foo(); 								// call function and count cycles
	cycles = KIN1_GetCycleCounter(); 	// get cycle counter
	KIN1_DisableCycleCounter(); 		// disable counting if not used any more

*/

/**
 * Reset profiling. Required to have a meaningful value when calling get_cycles_profiling()
 */
void reset_profiling(void);

/**
 * Get the number of cycles elapsed since last call to reset_profiling()
 * @return Number of cycles
 */
uint32_t get_cycles_profiling(void);

#endif

#endif /* INCLUDE_UTILS_H_ */
