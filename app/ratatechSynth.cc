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
ADSREnv adsr_vol(LOG,EXP,EXP,0.009),adsr_fc(LOG,EXP,EXP,0.009);
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
bool useADC = true;


int32_t randNum;
uint32_t noteCounter = 0;
uint16_t adc;
int16_t control_rate_decimate = 0;

uint32_t q_adc,fc_adc,fc_env,fc_lfo,fc = 0;
double lfo_adc;

uint16_t C4_Octave[12] = {261,277,293,311,329,349,369,392,415,440,466,493};
uint16_t MIDI_Octaves[12] = {8,16,32,65,130,261,523,1046,2093,4186,8372,12543};
uint16_t octaveCounter = 0;

uint16_t code;
uint32_t  MAXcode;
uint8_t byte1;
uint8_t byte2;
uint8_t byte3;

double attack_state = 0;

BitAction sb;

enum application_e {NORMAL,NO_ADSR};
application_e app = NORMAL;


int main(void)
	{

	// Init system and peripherals
	ratatech_init();


	// Configure LFO
	//TODO(JoH):Check wavetables for LFO. SOUNDS CRAP, ONLY FADES 0-0.5!
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
	lfo.lfo_amo = 0x0000;
	lfo.setFreqFrac(2);

	//LFO destination
		synth_params.lfo_dest = OSC1;

	// Configure FM modulator oscillator
	synth_params.FM_synth = false;
	if(synth_params.FM_synth){
		osc_shape_t shape_FM_mod = SIN;
		FM_mod.shape = shape_FM_mod;
		FM_mod.FM_synth = true;
		FM_mod.lfo_amo = 0x5FFF;
		synth_params.I = 3;
		FM_mod.setFreqFrac(1000);
	}

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SAW;
	if(synth_params.FM_synth){
		osc_shape_t shape_osc1 = SIN;
		osc1.FM_synth = synth_params.FM_synth;
	}
	osc1.set_shape(shape_osc1);
	osc1.setFreqFrac(300);

	// Configure oscillator 2
	osc_shape_t shape_osc2 = SAW;
	osc2.set_shape(shape_osc2);
	osc2.setFreqFrac(1000);

	/* Mix Parameter between osc1 and osc2
	 *
	 * synth_params.osc_mix = 32768;
	 * 0x0000 Mix 100% Osc2
	 * 0x7FFF Mix 100% Osc1
	 * 0x3FFF Mix 50%
	 *
	 * */
	synth_params.osc_mix = 0x0;
	synth_params.midi_dest = OSC2;


	GPIOA->BRR = GPIO_Pin_12;
	GPIOA->BSRR = GPIO_Pin_11;




	//TODO(JoH): Review the whole ADSR algo. The behavious seems weird
	/* *****************************************************************************************
	 *
	 * ADSR
	 *
	 * Configure ADSR. Values correspond for duration of the states in seconds except for
	 * the sustain which is the amplitude (substracted from 1, -1 corresponds to 1). Duration
	 * of the Decay and release states is calculated based on the amplitude of the sustain value.
	 * * *****************************************************************************************/
	// Volume envelope
	adsr_vol.attack  = 0.1;
	adsr_vol.decay   = 0.041;
	adsr_vol.sustain = 0.99;
	adsr_vol.release = 0.05;
	adsr_vol.calcAdsrSteps();

	// VCF envelope
	adsr_fc.attack  = 0.1;
	adsr_fc.decay   = 0.01;
	adsr_fc.sustain = 0.99;
	adsr_fc.release = 0.01;
	static bool copyVolumeEnvelope = false;
	if(copyVolumeEnvelope){
		adsr_fc.attack  = adsr_vol.attack;
		adsr_fc.decay   = adsr_vol.decay;
		adsr_fc.sustain = adsr_vol.sustain;
		adsr_fc.release = adsr_vol.release;
	}
	adsr_fc.calcAdsrSteps();


	//Pre-fill the output buffer
	fill_buffer();

	midi.new_event = true;

	/* *****************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{

		// Events happening every CONTROL_RATE
		if(low_rate_ISR_flag){
			low_rate_tasks();
			control_rate_decimate++;

			if(control_rate_decimate > 5000){
			}

		}




		// Fill audio buffer with a new sample
		fill_buffer();
	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){


	switch(app){

		case NORMAL:

			// Update Envelope, LFO and midi objects
			if(midi.new_event){

				midi.update(&synth_params);
				switch(synth_params.midi_dest){
					case OSC1:
						osc1.setFreqFrac(midi_freq_lut[synth_params.pitch]);
					break;
					case OSC2:
						osc2.setFreqFrac(midi_freq_lut[synth_params.pitch]);
					break;
				}

				if(midi.attack_trigger){
					adsr_vol.initStates();
					adsr_fc.initStates();
					midi.attack_trigger = false;

				}
				adsr_vol.note_ON = synth_params.note_ON;
				midi.new_event = false;
			}


			adsr_vol.update();
			adsr_fc.update();
			lfo.update(&synth_params);
			/*Update FM modulator*/
			if(synth_params.FM_synth)
				FM_mod.update(&synth_params);

			// ------------------ DEBUG ----------------------------//
			/*Set amplitude to 1, no ADSR*/
//			synth_params.adsr_amp_vol = 0x7FFF>>1;
//			adsr_vol.adsr_amp = synth_params.adsr_amp_vol ;
			// ------------------ DEBUG ----------------------------//

			if (useADC)
			{


				for(int s=0;s<8;s++){


					((s & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
					GPIO_WriteBit(GPIOB,GPIO_Pin_5,sb);

					(((s>>1) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
					GPIO_WriteBit(GPIOB,GPIO_Pin_6,sb);

					(((s>>2) & 0x01) > 0) ? sb = Bit_SET : sb = Bit_RESET;
					GPIO_WriteBit(GPIOB,GPIO_Pin_9,sb);


					switch(s){
//						case 0 :
//							trace_printf("ADC read MUX y0 = %i\n",readADC1(4));
//						break;
//
//						case 1 :
//							trace_printf("ADC read MUX y1 = %i\n",readADC1(4));
//						break;
//
						case 2 :
							adc = readADC1(4);
							q_adc = (uint32_t)(adc*PWM_PERIOD)>>12;
							trace_printf("ADC read MUX y2 = %i\n",readADC1(4));
						break;
//
						case 3 :
							adc = readADC1(4);
//							adsr_vol.attack = (double)(((double)adc/4095)*0.1);
//							adsr_fc.attack = adsr_vol.attack;
							trace_printf("ADC read MUX y3 = %i\n",readADC1(4));
						break;

						case 4 :
							adc = readADC1(4);
							fc_adc = (uint32_t)(adc*PWM_PERIOD)>>12;
							trace_printf("ADC read MUX y4 = %i\n",fc_adc);

						break;

						case 5 :
							adc = readADC1(4);
//							adsr_vol.release = (double)(((double)adc/4095)*0.8);
//							adsr_fc.release = adsr_vol.release;
							trace_printf("ADC read MUX y5 = %i\n",readADC1(4));
						break;
//
//						case 6 :
//							trace_printf("ADC read MUX y6 = %i\n",readADC1(4));
//						break;
//
//						case 7 :
//							trace_printf("ADC read MUX y7 = %i\n",readADC1(4));
//						break;
					}
				}

			}


			fc_env = mul_int16(adsr_fc.adsr_amp,PWM_PERIOD);
			fc_lfo =  mul_int16(lfo.lfo_amp,PWM_PERIOD);
			//fc = fc_adc+fc_env;
//			fc = fc_adc;
//			if(fc_adc< 200)
//				fc_adc = 400;
//			fc = fc_adc;
			//fc = fc_env;
			if(fc > PWM_PERIOD)
				fc = PWM_PERIOD;
			//fc = lfo.lfo_amp;
			//fc_adc = PWM_PERIOD;
			TIM3->CCR2 = q_adc;


			TIM3->CCR4 = PWM_PERIOD-(fc_env-fc_adc);
			//lfo.setFreqFrac(lfo_adc);


			//****************************** DEBUG SHIFT COUNTER *************************************************************
			// CS High
			//GPIOA->BRR = GPIO_Pin_11;

			byte1 = 0x00;

			// Transmit the two 8bit SPI messages
			SPI_send(SPI2,byte1);

			// CS Low
			//GPIOA->BSRR = GPIO_Pin_11;

			//****************************** DEBUG SHIFT COUNTER *************************************************************

		break;

		case NO_ADSR:

			/*Set amplitude to 1, no ADSR*/
			synth_params.adsr_amp_vol = 0x7FFF;
			adsr_vol.adsr_amp = 0x7FFF;
			/*Update LFO*/
			lfo.setFreqFrac(lfo_adc);
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

		// Modulate signal with the ADSR envelope if a MIDI note is received
		if(synth_params.midi_dest == OSC1){

			osc1_mix_temp = osc_mix;
			osc_mix = ((int32_t)(osc_mix)*(adsr_vol.adsr_amp)>>15);
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

		// Modulate signal with the ADSR envelope if a MIDI note is received
		if(synth_params.midi_dest == OSC2){

			osc2_mix_temp = osc_mix;
			osc_mix = ((int32_t)(osc_mix)*(adsr_vol.adsr_amp)>>15);
		}

		/* *****************************************************************************************
		 * OSC1/OSC2 MIXING
		 *
		 * Mix the the two next computed samples and apply ADSR Modulation.
		 * Finally scale the signal to 12 bits and store it in the output buffer.
		 * *****************************************************************************************/

		// Mix the two oscillators
		osc_mix += osc1_mix_temp;

		osc_mix = ((int32_t)(osc_mix)*(adsr_vol.adsr_amp)>>15);
		//osc_mix = adsr_vol.adsr_amp;

		// Convert to unsigned
		osc_mix = int16_2_uint16(osc_mix);
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
    	adsr_vol.note_ON = true;
		adsr_vol.adsr_state = ATTACK_STATE;
		adsr_vol.calcAdsrSteps();
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
    	adsr_vol.note_ON = true;
		adsr_vol.adsr_state = ATTACK_STATE;
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
    	adsr_vol.note_ON = true;
		adsr_vol.adsr_state = ATTACK_STATE;
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
    	adsr_vol.note_ON = true;
		adsr_vol.adsr_state = ATTACK_STATE;
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
    	adsr_vol.note_ON = true;
		adsr_vol.adsr_state = ATTACK_STATE;
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
//		adsr_vol.adsr_state = ATTACK_STATE;
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
//		adsr_vol.adsr_state = ATTACK_STATE;
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
* USART1 interrupt handler
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

/*
* USART2 interrupt handler
*/
/*void USART2_IRQHandler(void)
{

	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
	{
		USART_SendData(USART2,counter);
		USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
		counter++;
		counter%=100;
	}*/

    /* ------------------------------------------------------------ */
    /* Other USART1 interrupts handler can go here ...             */
//}


// ----------------------------------------------------------------------------
