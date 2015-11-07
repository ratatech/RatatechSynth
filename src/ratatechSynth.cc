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



RCC_ClocksTypeDef RCC_Clocks;


using namespace std;

#define DEBUG_AMP 32767

// Object instances
Oscillator osc1,osc2;
CircularBuffer out_buffer;
ADSREnv adsrEnv(EXP);
LFO lfo;
DIGI_POT potQ(GPIO_Pin_10),potFc0(GPIO_Pin_12),potFc1(GPIO_Pin_8);
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

uint8_t Q,fc = 0;

uint16_t C4_Octave[12] = {261,277,293,311,329,349,369,392,415,440,466,493};
uint16_t MIDI_Octaves[12] = {8,16,32,65,130,261,523,1046,2093,4186,8372,12543};
uint16_t octaveCounter = 0;

int main(void)
	{

	// Configure lfo
	osc_shape_t shape_lfo = SIN;
	lfo.shape = shape_lfo;
	lfo.lfo_amo = 0x7FFF;
//	lfo.lfo_amo = 0x4000;
//	lfo.lfo_amo = 0x2000;
//	lfo.lfo_amo = 0xA;
	lfo.lfo_amo = 0;
	lfo.setFreqFrac(0.1);

	// Configure oscillator 1
	osc_shape_t shape_osc1 = TRI;
	osc1.set_shape(shape_osc1);
	osc1.setFreqFrac(12000);

	// Configure oscillator 2
	osc_shape_t shape_osc2 = TRI;
	osc2.set_shape(shape_osc2);
	osc2.setFreqFrac(1000);

	// Mix Parameter between osc1 and osc2
	//synth_params.osc_mix = 32768;
	// 0x0000 Mix 100% Osc2
	// 0xFFFF Mix 100% Osc1
	// 0x00FF Mix 50%
	synth_params.osc_mix = 0xFFFF;

	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    // COnfigure and init peripherals
	GPIO_Conf_Init();
	SPI_Config();
	fill_buffer();
	TIM_Config();
	ButtonsInitEXTI();


	//Configure ADSR. Values correspond for duration of the states in seconds except for the sustain which is the amplitude
	//(substracted from 1, -1 corresponds to 1). Duration of the Decay and release states is calculated based on the
	// amplitude of the sustain value.
	adsrEnv.attack =1;
	adsrEnv.decay = 1;
	adsrEnv.sustain = 0.5;
	adsrEnv.release = 0.1;
	adsrEnv.calcAdsrSteps();


	double randNumFreq;
	int randNum;
	uint32_t noteCounter = 0;

	/* Infinite loop */
	while(1)
	{
		//trace_printf("MAIN a = %i\n",a);

		if(low_rate_ISR_flag)
		{


			//Read note button
			if (adsrEnv.note_ON)
			{
				if (!ButtonRead(GPIOA, GPIO_Pin_0))
				{
					adsrEnv.calcAdsrSteps();
					adsrEnv.adsr_state = RELEASE_STATE;
					adsrEnv.note_ON = false;
				}

			}

			// Update Envelope and LFO objects
			adsrEnv.update(&synth_params);
			lfo.update(&synth_params);


//			if(noteCounter>=8000 ){
//				randNum = rand();
//				randNumFreq = (double)(randNum>>24)*10;
//				if(randNumFreq>8000)
//					randNumFreq = 8000;
//				if(randNumFreq<30)
//					randNumFreq = 30;
//				//osc1.setFreqFrac(C4_Octave[octaveCounter]);
//				osc1.setFreqFrac(randNumFreq);
//		    	//adsrEnv.note_ON = true;
//				adsrEnv.adsr_state = ATTACK_STATE;
//				noteCounter=0;
//				octaveCounter++;
//				if(octaveCounter>=255)
//					octaveCounter = 0;
//			}
//			noteCounter++;

			Q = 255;
			//fc = 255-(adsrEnv.adsr_amp>>7)+1;
			//fc = (adsrEnv.adsr_amp>>7)+1;
			//fc = (lfo.lfo_amp>>7);


			//fc = octaveCounter;
			potQ.write(Q);
			potFc0.write(fc);
			potFc1.write(fc);


			// Put low rate interrupt flag down
			low_rate_ISR_flag = false;
		}

		fill_buffer();


	}


}


/** Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{
	uint32_t osc_mix,osc_mix_temp;
	while(out_buffer.check_status()){

		osc_mix = osc1.compute_osc(&synth_params);
		osc_mix = ((uint32_t)(osc_mix)*(synth_params.osc_mix)>>16);
		osc_mix_temp = osc_mix;
		osc_mix = osc2.compute_osc(&synth_params);
		osc_mix = ((uint32_t)(osc_mix)*(0xFFFF-synth_params.osc_mix)>>16);
		osc_mix += osc_mix_temp;
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
    	osc1.setFreqFrac(200);
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

/**
* @}
*/
// ----------------------------------------------------------------------------
