/*
@file serial_com_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, May 4, 2017
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


#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "ratatechSynth.h"
#include "tst_utils.h"



/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256


/**
 * Serial comm ref buffer
 */
int32_t buff_serial_com_ref[BUFF_SIZE] = {
		26250,29116,5796,-23023,-32004,-12446,17595,32130,17595,-12495,-32004,-23114,5819,29232,26250,0,-26536,-29028,-6100,21449,29760,11139,-16685,-29696,
		-16188,10622,27528,19580,-5375,-24898,-22256,0,21105,22736,4370,-17108,-22932,-8771,11937,21042,11385,-7742,-19530,-13559,3289,16240,14070,0,-13268,-
		13924,-2875,9701,13144,4700,-6603,-11520,-6035,3854,9424,6230,-1675,-7316,-6313,0,5145,5452,966,-3640,-4410,-1519,2001,3150,1587,-980,-2142,-1365,276,
		1276,945,0,-535,-472,-75,178,124,47,0,0,0,0,124,89,-50,-354,-535,0,735,1044,253,-1274,-1890,-882,1380,2898,1863,-1421,-4158,-3185,920,5104,4935,0,-5778,-6962,
		-1625,5963,9052,3572,-5822,-11264,-6390,4559,12400,9434,-2800,-13570,-12947,0,13755,15892,3220,-13286,-18774,-7595,11178,20790,11730,-8477,-22554,-16835,
		4324,22388,20580,0,-22042,-24544,-5325,19135,27280,10528,-16046,-29440,-16472,11045,29512,21360,-6075,-28792,-26322,0,26250,29116,5796,-23023,-32004,
		-12446,17595,32130,17595,-12495,-32004,-23114,5819,29232,26250,0,-26536,-29028,-6100,21449,29760,11139,-16685,-29696,-16188,10622,27528,19580,-5375,
		-24898,-22256,0,21105,22736,4370,-17108,-22932,-8771,11937,21042,11385,-7742,-19530,-13559,3289,16240,14070,0,-13268,-13924,-2875,9701,13144,4700,-6603,
		-11520,-6035,3854,9424,6230,-1675,-7316,-6313,0,5145,5452,966,-3640,-4410,-1519,2001,3150,1587,-980,-2142,-1365,276,1276,945,0,-535,-472,-75,178,124,47,0,0,0,0,
		124,89,-50,-354,-535,0,



};
/**
 * Unit test output buffer
 */
int32_t buff_out [BUFF_SIZE];


/**
 * Serial communication test
 */
void test_serial_com(void){


	/** Just copy paste sampeles */
	for(int i=0; i<BUFF_SIZE; i++){
		buff_out[i] = buff_serial_com_ref[i];
	}
	/** Print output buffer */
	printOutBuff("buff_serial_com_out", &buff_out[0], BUFF_SIZE);

}

int main(void)
{

	/** System init */
	RCC_ClocksTypeDef RCC_Clocks;
	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/** SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    /** Configure and init peripherals  */
	GPIO_Conf_Init();
	USART_Conf_Init();

	test_serial_com();

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    wait_usart_ready();

	/** Ready to start test  */
    iprintf("\nTEST:    SERIAL COM\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_serial_com);

    /** FInish unity */
    return UNITY_END();
}

