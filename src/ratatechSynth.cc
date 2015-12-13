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

#define DEBUG_AMP 32767

// Object instances
Oscillator osc1,osc2;
CircularBuffer out_buffer;
ADSREnv adsrEnv(LOG,EXP,EXP,0.09);
LFO lfo,FM_mod;
DIGI_POT potF2P1(GPIO_Pin_11),potF2P2(GPIO_Pin_10),potF1P1(GPIO_Pin_12),potF1P2(GPIO_Pin_8);
MIDI midi;

// Structure instances
synth_params_t synth_params;

int16_t data;
int32_t data_acc;
uint16_t u_data;
uint16_t out_sample;
int16_t envt;
double env=0;
bool status = true;
int a = 0;
bool low_rate_ISR_flag = false;
bool useADC = false;
bool randomSeq = false;

int32_t randNum;
uint32_t noteCounter = 0;
int16_t adc;

uint32_t Q,fc = 0;

uint16_t C4_Octave[12] = {261,277,293,311,329,349,369,392,415,440,466,493};
uint16_t MIDI_Octaves[12] = {8,16,32,65,130,261,523,1046,2093,4186,8372,12543};
uint16_t octaveCounter = 0;

enum application_e {NORMAL,NO_ADSR};
application_e app = NORMAL;


int main(void)
	{

	// Init system and peripherals
	ratatech_init();

	GPIOA->BSRR = GPIO_Pin_12;

	// Configure LFO
	osc_shape_t shape_lfo = SIN;
	lfo.FM_synth = false;
	lfo.shape = shape_lfo;
	/* LFO Amount Parameter
	 *
	 * lfo.lfo_amo = 0x7FFF;
	 * lfo.lfo_amo = 0x4000;
	 * lfo.lfo_amo = 0x2000;
	 * lfo.lfo_amo = 0xA;
	 * lfo.lfo_amo = 0;
	 *
	 * */
	lfo.lfo_amo = 0x0;
	lfo.setFreqFrac(50);

	//LFO destination
	synth_params.lfo_dest = OSC1;

	// Configure FM modulator oscillator
	synth_params.FM_synth = false;
	if(synth_params.FM_synth){
		osc_shape_t shape_FM_mod = SIN;
		FM_mod.shape = shape_FM_mod;
		FM_mod.FM_synth = true;
		FM_mod.lfo_amo = 0x7FFF;
		synth_params.I = 7;
		FM_mod.setFreqFrac(2000);
	}

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SIN;
	if(synth_params.FM_synth){
		osc_shape_t shape_osc1 = SIN;
		osc1.FM_synth = synth_params.FM_synth;
	}
	osc1.set_shape(shape_osc1);
	osc1.setFreqFrac(2600);

	// Configure oscillator 2
	osc_shape_t shape_osc2 = SIN;
	osc2.set_shape(shape_osc2);
	osc2.setFreqFrac(440);

	/* Mix Parameter between osc1 and osc2
	 *
	 * synth_params.osc_mix = 32768;
	 * 0x0000 Mix 100% Osc2
	 * 0x8000 Mix 100% Osc1
	 * 0x4000 Mix 50%
	 *
	 * */
	synth_params.osc_mix = 0x7FFF;


	/* *****************************************************************************************
	 *
	 * ADSR
	 *
	 * Configure ADSR. Values correspond for duration of the states in seconds except for
	 * the sustain which is the amplitude (substracted from 1, -1 corresponds to 1). Duration
	 * of the Decay and release states is calculated based on the amplitude of the sustain value.
	 * * *****************************************************************************************/
	adsrEnv.attack  = 0.1;
	adsrEnv.decay   = 0.2;
	adsrEnv.sustain = 0.5;
	adsrEnv.release = 0.2;
	adsrEnv.calcAdsrSteps();
	//adsrEnv.adsr_state = ATTACK_STATE;

	//Pre-fill the output buffer
	fill_buffer();

	/* *****************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{

		// Events happening every CONTROL_RATE
		if(low_rate_ISR_flag)
			low_rate_tasks();

		// Fill audio buffer with a new sample
		fill_buffer();
	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
inline void low_rate_tasks(void){


	switch(app){

		case NORMAL:

			//Check note button
			if (adsrEnv.note_ON)
			{
				if (!ButtonRead(GPIOA, GPIO_Pin_0))
				{
					adsrEnv.calcAdsrSteps();
					adsrEnv.adsr_state = RELEASE_STATE;
					adsrEnv.note_ON = false;
					adsrEnv.range_rel = adsrEnv.adsr_amp<<16;
				}
			}

			// Update Envelope, LFO and midi objects
			if(midi.new_event){

				midi.update(&synth_params);
				osc1.setFreqFrac(midi_freq_lut[synth_params.pitch]);
				osc2.setFreqFrac(midi_freq_lut[synth_params.pitch]);
				if(midi.attack_trigger){
					adsrEnv.initStates();
					midi.attack_trigger = false;

				}
				//adsrEnv.note_ON = synth_params.note_ON;
				midi.new_event = false;
			}

			adsrEnv.update(&synth_params);
			lfo.update(&synth_params);
			/*Update FM modulator*/
			FM_mod.update(&synth_params);

			//Trigger notes base on a pseudo-random number generation
			if(randomSeq){
				srand(1);
				if(noteCounter>=1000 ){
					randNum = rand();
					randNum = ((randNum>>21));
					trace_printf("random num = %i\n",randNum);
					if(randNum>8000)
						randNum = 8000;
					if(randNum<30)
						randNum = 30;
					//osc1.setFreqFrac(C4_Octave[octaveCounter]);
					osc1.setFreqFrac(randNum);
					//adsrEnv.note_ON = true;
					adsrEnv.adsr_state = ATTACK_STATE;
					noteCounter=0;
					octaveCounter++;
					if(octaveCounter>=12)
						octaveCounter = 0;
				}
				noteCounter++;
			}

			if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET && useADC)
			{


				adc = (int16_t)((double)ADC_GetConversionValue(ADC1)*255/4095);

				fc = adc;
				trace_printf("%i\n",adc);

				/* Probably overkill */
				ADC_ClearFlag(ADC1, ADC_FLAG_EOC);

				/* Start ADC1 Software Conversion */
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			}

			if(adsrEnv.adsr_state != SUSTAIN_STATE){

				//fc = 255-(adsrEnv.adsr_amp>>7);
				//fc = (adsrEnv.adsr_amp>>7)+1;
				//fc = (lfo.lfo_amp>>7);
				//fc = 4;
				//fc = 0;
				if(fc>250){
					fc = 200;
				}
			}

			// Set potentiometer values
//			potF1P1.write(fc);
//			potF1P2.write(fc);
//			potF2P1.write(fc);
//			potF2P2.write(fc);

			//fc = 255-(adsrEnv.adsr_amp>>7);
			fc = (int16_t)((double)(adsrEnv.adsr_amp)*(0x10000>>7)/0x7FFF);
			//fc = (int16_t)((double)(lfo.lfo_amp)*(0x10000>>7)/0x7FFF);
			//fc = 13107;
			//fc = 0;
			//fc = 65535 - 1;
			//fc = 4096;
			//fc = 0x10000>>2;
			TIM3->CCR2 = fc;


		break;

		case NO_ADSR:

			/*Set amplitude to 1, no ADSR*/
			synth_params.adsr_amp = 0x7FFF;
			/*Update LFO*/
			lfo.update(&synth_params);
			/*Update FM modulator*/
			FM_mod.update(&synth_params);

		break;
	}

	// Put low rate interrupt flag down
	low_rate_ISR_flag = false;

}

/**
 * Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{
	int32_t osc_mix,osc1_mix_temp,osc2_mix_temp;
	while(out_buffer.check_status()){

		/* *****************************************************************************************
		 * OSCILLATOR 1
		 *
		 * Compute a new oscillator1 sample and apply modulations
		 * *****************************************************************************************/

		osc_mix = osc1.compute_osc(&synth_params);
		osc_mix = ((int32_t)(osc_mix)*(synth_params.osc_mix)>>15);

		// Modulate signal with the LFO
		if(synth_params.lfo_dest == OSC1){

			osc1_mix_temp = osc_mix;
			osc_mix = ((int32_t)(osc_mix)*(synth_params.lfo_amp)>>15);

			// Mix LFO with amount parameter
			osc_mix = osc_mix + ((int32_t)(osc1_mix_temp)*(0x7FFF - synth_params.lfo_amo)>>15);
		}

		// Save temporal output
		osc1_mix_temp = osc_mix;

		/* *****************************************************************************************
		 * OSCILLATOR 2
		 *
		 * Compute a new oscillator2 sample and apply modulations
		 * *****************************************************************************************/

		osc_mix = osc2.compute_osc(&synth_params);
		osc_mix = ((int32_t)(osc_mix)*(0x7FFF-synth_params.osc_mix)>>15);

		// Modulate signal with the LFO
		if(synth_params.lfo_dest == OSC2){

			osc2_mix_temp = osc_mix;
			osc_mix = ((int32_t)(osc_mix)*(synth_params.lfo_amp)>>15);

			// Mix LFO with amount parameter
			osc_mix = osc_mix + ((int32_t)(osc2_mix_temp)*(0x7FFF - synth_params.lfo_amo)>>15);
		}

		/* *****************************************************************************************
		 * OSC1/OSC2 MIXING
		 *
		 * Mix the the two nex computed samples and apply ADSR Modulation.
		 * Finally scale the signal to 12 bits and store it in the output buffer.
		 * *****************************************************************************************/

		// Mix the two oscillators
		osc_mix += osc1_mix_temp;

		// Modulate signal with the ADSR envelope
		osc_mix = ((int32_t)(osc_mix)*(synth_params.adsr_amp)>>15);

		// Convert to unsigned
		osc_mix = int16_2_uint16(osc_mix);

		// Shift back to 12 bits required by the DAC
		osc_mix>>=4;

		status = out_buffer.write(osc_mix);

	}

}

/** Read if a buton is active or not
 *
 * @param Buttton_port Selected port
 * @param Buttton  Button number
 * @return void
 */
uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button)
{
  return !GPIO_ReadInputDataBit(Button_Port, Button);
}

extern "C" {

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	//TimingDelay_Decrement();

}

/*****************************************************************************************************************************
******************* EXTERNAL INTERRUPTS **************************************************************************************
******************************************************************************************************************************/

/**
  * @brief  This function handles External Interrupt 0 Handler.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{

    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
    	//Set freq
    	osc1.setFreqFrac(12000);
    	adsrEnv.note_ON = true;
		adsrEnv.adsr_state = ATTACK_STATE;
		adsrEnv.calcAdsrSteps();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line0);
}

/**
  * @brief  This function handles External Interrupt 1 Handler.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{


    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
    	//Set freq
    	osc1.setFreqFrac(C4_Octave[2]);
    	adsrEnv.note_ON = true;
		adsrEnv.adsr_state = ATTACK_STATE;
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line1);
}

/**
  * @brief  This function handles External Interrupt 2 Handler.
  * @param  void
  * @retval void
  */
void EXTI2_IRQHandler(void)
{


    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
    	//Set freq
    	osc1.setFreqFrac(C4_Octave[4]);
    	adsrEnv.note_ON = true;
		adsrEnv.adsr_state = ATTACK_STATE;
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line2);
}

/**
  * @brief  This function handles External Interrupt 3 Handler.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{


    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
    	//Set freq
    	osc1.setFreqFrac(C4_Octave[5]);
    	adsrEnv.note_ON = true;
		adsrEnv.adsr_state = ATTACK_STATE;
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line3);
}

/**
  * @brief  This function handles External Interrupt 4 Handler.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{


    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
    	//Set freq
    	osc1.setFreqFrac(C4_Octave[7]);
    	adsrEnv.note_ON = true;
		adsrEnv.adsr_state = ATTACK_STATE;
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line4);
}



///**
//  * @brief  This function handles External Interrupt 5 Handler.
//  * @param  None
//  * @retval None
//  */
//void EXTI5_IRQHandler(void)
//{
//
//
//    //Check if EXTI_Line0 is asserted
//    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
//    {
//    	//Set freq
//    	osc1.setFreqFrac(C4_Octave[9]);
//		adsrEnv.adsr_state = ATTACK_STATE;
//    }
//    //we need to clear line pending bit manually
//    EXTI_ClearITPendingBit(EXTI_Line5);
//}
//
///**
//  * @brief  This function handles External Interrupt 6 Handler.
//  * @param  None
//  * @retval None
//  */
//void EXTI6_IRQHandler(void)
//{
//
//
//    //Check if EXTI_Line0 is asserted
//    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
//    {
//    	//Set freq
//    	osc1.setFreqFrac(C4_Octave[10]);
//		adsrEnv.adsr_state = ATTACK_STATE;
//    }
//    //we need to clear line pending bit manually
//    EXTI_ClearITPendingBit(EXTI_Line6);
//}



/*****************************************************************************************************************************
******************* TIMER INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{

		low_rate_ISR_flag = true;
		//Do something here

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}


}

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{

	//trace_printf("READ\n");
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{

		status = out_buffer.read(&out_sample);
		audio_out_write(out_sample);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	}


}

}

/*****************************************************************************************************************************
******************* USART INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
* USART interrupt handler
*/
void USART1_IRQHandler(void)
{

	//trace_printf("MIDI Rx\n");
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
    	uint16_t midi_in = USART_ReceiveData(USART1);
    	midi.parseMsg(midi_in);

    }

    /* ------------------------------------------------------------ */
    /* Other USART1 interrupts handler can go here ...             */
}
// ----------------------------------------------------------------------------
