/*
 @file ratatechSynth.cc


 @brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

 @ Created by Jordi Hidalgo, Ratatech, Jun 21, 2015
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

#include "ratatechSynth.h"

using namespace std;

/** Parameter structures */
synth_params_t synth_params;
object_pool_t object_pool;

/** Make a local copy of the object instances */
Oscillator 		osc1,osc2,osc3,osc4;
LFO 			lfo;
CircularBuffer	out_buffer;
MIDI 			midi;
SoundGenerator 	snd_gen;
ADSR			adsr;
//Mux				mux_0,mux_1,mux_2,mux_3,mux_4;
Svf 			svf;

MacroMux macroMux;

/** Pointer to main output frame buffer  **/
q15_t pOut[FRAME_SIZE];

/** Sample to be written in the DAC */
q15_t out_sample;

/** Output buffer status */
bool status = true;

uint16_t* pAdc;


uint32_t cycles; // number of cycles //


volatile size_t frame_read_n;
volatile size_t frame_write_n;

// Temp vars, to be removed
uint16_t enc_cnt;
char enc_cnt_buf[8];
bool LCD_FLAG = false;
//#define DEBUG_MUX_ADC_0
//#define DEBUG_MUX_ADC_1
#define DEBUG_MUX_GPIOS
uint16_t exti_trigger_cnt = 0;

bool touch_keys[12];
bool touch_key_on = false;

int main(void)
{

	KIN1_InitCycleCounter(); 			// enable DWT hardware
	KIN1_ResetCycleCounter(); 			// reset cycle counter
	KIN1_EnableCycleCounter(); 			// start counting

	/** Put objects in the pool */
	object_pool.osc1 = 			&osc1;
	object_pool.osc2 = 			&osc2;
	object_pool.osc3 = 			&osc3;
	object_pool.osc4 = 			&osc4;
	object_pool.lfo = 			&lfo;
	object_pool.out_buffer = 	&out_buffer;
	object_pool.midi = 			&midi;
	object_pool.adsr = 			&adsr;
	object_pool.mux = 			NULL;
	object_pool.svf =			&svf;

	/** Link output frame ponter to global structure */
	synth_params.pOut = &pOut[0];

	synth_params.lfo_amp = &lfo.lfo_amp;


	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	macroMux.config(&synth_params);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Init oscillator with default settings */
	osc1.init(&synth_params.osc_params);
	osc2.init(&synth_params.osc_params);
	osc3.init(&synth_params.osc_params);
	osc4.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc1.set_shape(SAW);
	osc2.set_shape(SAW);
	osc3.set_shape(SAW);
	osc4.set_shape(TRI);

	/** Init adsr */
	adsr.init(&synth_params);

	/** Configure lfo */
	lfo.FM_synth = false;
	lfo.set_shape(SIN);
	lfo.set_freq_frac(50);

	/** Init SVF filter params*/
	svf.init(&synth_params);
	svf.configure(&synth_params);
	svf.configure(&synth_params);
	svf.configure(&synth_params);



	/** Pre-fill the output buffer */
	fill_buffer();

    //DelayInit();

	/*******************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{

		/** Fill audio buffer with a new frames */
		if(out_buffer.frame_read != out_buffer.frame_write){
			fill_buffer();
		}


		/** QUICK N DIRTY LCD + ENCODER
		 * TO BE REMOVED
		 * */

		// Get encoder value
        enc_cnt = TIM_GetCounter(TIM4)>>2;

        // Print encoder value
        sprintf(enc_cnt_buf, "%i", enc_cnt);
//        lcd16x2_clrscr();
//        lcd16x2_puts(enc_cnt_buf);

        // Get encoder value
        //iprintf("ENCODER = %i\n",enc_cnt);



		// Print encoder value
//		sprintf(enc_cnt_buf, "%i %i %i %i %i %i %i %i", synth_params.mux_adc_0_out.mux_x[0]>>3,synth_params.mux_adc_0_out.mux_x[1]>>3, synth_params.mux_adc_0_out.mux_x[2]>>3,synth_params.mux_adc_0_out.mux_x[3]>>3
//													  , synth_params.mux_adc_0_out.mux_y[0]>>3,synth_params.mux_adc_0_out.mux_y[1]>>3, synth_params.mux_adc_0_out.mux_y[2]>>3,synth_params.mux_adc_0_out.mux_y[3]>>3);
//
//		lcd16x2_clrscr();
//		lcd16x2_puts(enc_cnt_buf);
		/** QUICK N DIRTY LCD + ENCODER
		 * TO BE REMOVED
		 * */

//		DelayMs(10);



		// Add a couple of cycles delay between main loop
	    __asm__("nop");
	    __asm__("nop");

	}

}

static void print_mux_adc(void){

#ifdef DEBUG_MUX_ADC_0
		iprintf("mux_0_x0 =%.4i mux_0_x1 =%.4i mux_0_x2 =%.4i mux_0_x3 =%.4i mux_0_y0 =%.4i mux_0_y1 =%.4i mux_0_y2 =%.4i y3 =%.4i \r",
		synth_params.mux_adc_0_out.mux_x[0],synth_params.mux_adc_0_out.mux_x[1],synth_params.mux_adc_0_out.mux_x[2],synth_params.mux_adc_0_out.mux_x[3],
		synth_params.mux_adc_0_out.mux_y[0],synth_params.mux_adc_0_out.mux_y[1],synth_params.mux_adc_0_out.mux_y[2],synth_params.mux_adc_0_out.mux_y[3]);
#endif

#ifdef DEBUG_MUX_ADC_1
		iprintf("mux_1_x0 =%.4i mux_1_x1 =%.4i mux_1_x2 =%.4i mux_1_x3 =%.4i mux_1_y0 =%.4i mux_1_y1 =%.4i mux_1_y2 =%.4i y3 =%.4i \r",
		synth_params.mux_1_out.mux_x[0],synth_params.mux_1_out.mux_x[1],synth_params.mux_1_out.mux_x[2],synth_params.mux_1_out.mux_x[3],
		synth_params.mux_1_out.mux_y[0],synth_params.mux_1_out.mux_y[1],synth_params.mux_1_out.mux_y[2],synth_params.mux_1_out.mux_y[3]);
#endif

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){


//	/** Read inputs */
//	KIN1_ResetCycleCounter();
//
	macroMux.read(&synth_params);
//	cycles = KIN1_GetCycleCounter();
//	update_touch_keys(0);

#ifdef DEBUG_MUX_ADC_0
	print_mux_adc();
#endif

#ifdef DEBUG_MUX_ADC_1
	print_mux_adc();
#endif

	synth_params.mux_adc_1_out.mux_x[1] = macroMux.am1->pMux_x[1];
	synth_params.mux_adc_0_out.mux_y[0] = macroMux.am0->pMux_y[0];


//	iprintf("SVF FC = %i SVF Q = %i\r",
//			synth_params.mux_adc_1_out.mux_x[1],
//			synth_params.mux_adc_0_out.mux_y[0]);

	svf.set_fc(&synth_params);
	svf.set_q(&synth_params);


	synth_params.mux_adc_1_out.mux_y[0] = macroMux.am1->pMux_y[0];
	synth_params.mux_adc_1_out.mux_y[1] = macroMux.am1->pMux_y[1];
	synth_params.mux_adc_1_out.mux_y[2] = macroMux.am1->pMux_y[2];
	synth_params.mux_adc_1_out.mux_y[3] = macroMux.am1->pMux_y[3];
	adsr.set_params(&synth_params);

//	lfo.set_freq_lut(macroMux.am0->pMux_x[2]);
//	lfo.lfo_amo = (uint32_t)(macroMux.am0->pMux_y[1]*MAX_AMP)>>12;

}

//#define DEBUG_ADSR

/**
 * Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{


#ifdef DEBUG_ADSR
	printf("ADSR STATE = %i ADSR S_LVL = %i ADSR LVL = %i\r",adsr.adsr_state,adsr.sustain_level,synth_params.adsr_vol_amp);
#endif


	/** Sound generation */
	snd_gen.gen_voice(&synth_params, pOut);

    /** Wait DMA transfer to be complete*/
	while(!out_buffer.dma_transfer_complete);

	/** Fill the output buffer with fresh frames*/
	status = out_buffer.write_frame_dma(pOut);


}

/**
 * Read a sample of the output buffer and write it to the DAC @AUDIO FS
 */
void audio_gen(void){
	out_buffer.read(&out_sample);
	audio_out_write(int16_2_uint16(out_sample));
}

/*****************************************************************************************************************************
******************* TIMER INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		audio_gen();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}

}

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		low_rate_tasks();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


/**
  * @brief  This function handles Timer 3 Handler.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	/**
	 * Do nothing for now. Still the function needs to be define when enabling the timer interrupt.
	 *  Dithering mechanism to be included here...
	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	*/
}


/*****************************************************************************************************************************
******************* USART INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
* USART1 interrupt handler
*/
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
    	uint16_t midi_in = USART_ReceiveData(USART1);
    	midi.parseMsg(midi_in);

    	/** Update midi information */
    	midi.update(&synth_params);

    	if(midi.new_event){
			/** If a new note is received reset ADSR */
    		adsr.reset();

			/** Set OSC freq from the MIDI table */
			osc1.set_freq_midi(synth_params.pitch);
			osc2.set_freq_midi(synth_params.pitch+1);
			osc3.set_freq_midi(synth_params.pitch+2);
			osc4.set_freq_midi(synth_params.pitch+3);
			midi.new_event = false;

		}else{
			//printf("MIDI STATUS = %i MIDI NOTE = %i MIDI VEL = %i\r",midi.midi_buffer[0],midi.midi_buffer[1],midi.midi_buffer[2]);
			//printf("MIDI STATUS = %i MIDI NOTE = %i MIDI VEL = %i\r",midi.midi_buffer[0],midi.midi_buffer[1],synth_params.vel);
			synth_params.note_ON = false;
		}

    	if(midi.note_ON && (synth_params.vel == 0)){
    		synth_params.note_ON = false;
    	}

    }




    /** ------------------------------------------------------------ */
    /** Other USART1 interrupts handler can go here ...             */
}


/*****************************************************************************************************************************
******************* DMA INTERRUPTS *******************************************************************************************
******************************************************************************************************************************/

void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC1))
  {
	iprintf("ADC-DMA interrupt trigger!!!\r");
	status = true;
    DMA_ClearITPendingBit(DMA1_IT_TC1);
    DMA_ClearITPendingBit(DMA1_IT_GL1);
  }
}


void DMA1_Channel2_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC2))
  {
    out_buffer.dma_transfer_complete = true;
    DMA_ClearITPendingBit(DMA1_IT_GL2);
  }
}


/*****************************************************************************************************************************
******************* EXTI INTERRUPTS ******************************************************************************************
******************************************************************************************************************************/

///**
//  * @brief  This function handles External Interrupt 4 Handler.
//  * @param  None
//  * @retval None
//  */
//void EXTI4_IRQHandler(void)
//{
//
//
//    //Check if EXTI_Line0 is asserted
//    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//    {
//    	iprintf("EXTI4 trigger!!!\r");
//    }
//    //we need to clear line pending bit manually
//    EXTI_ClearITPendingBit(EXTI_Line4);
//}

/**
  * @brief  This function handles External Interrupt 4 Handler.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
    	if(GPIOB->IDR & 0x01){
    		touch_key_on = true;
    	}else{
    		touch_key_on = false;
    	}
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line0);
}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		iprintf("EXTI9_5_IRQHandler trigger!!!\r");

		/* Clear the  EXTI line 9 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}
