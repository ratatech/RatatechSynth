/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Mar 29, 2017
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


#include "unity.h"

#include "DumbExample.h"
#include <stdio.h>

#include <stdio.h>
#define UNITY_OUTPUT_CHAR(a)   (void)print_char(a)


void test_AverageThreeBytes_should_AverageMidRangeValues(void)
{
	TEST_ASSERT_EQUAL_HEX8(40, AverageThreeBytes(30, 40, 50));
	TEST_ASSERT_EQUAL_HEX8(40, AverageThreeBytes(10, 70, 40));
	TEST_ASSERT_EQUAL_HEX8(33, AverageThreeBytes(33, 33, 33));
}

void test_AverageThreeBytes_should_AverageHighValues(void)
{
	TEST_ASSERT_EQUAL_HEX8(80, AverageThreeBytes(70, 80, 90));
	TEST_ASSERT_EQUAL_HEX8(127, AverageThreeBytes(127, 127, 127));
	TEST_ASSERT_EQUAL_HEX8(84, AverageThreeBytes(0, 126, 126));
}

void test_print(void){
    iprintf("Greetings Earthlings");
    iprintf("\n");
}

void print_char(const char x){
	const char* pch ;
	pch = &x;
	 iprintf(pch);

}

int main(void)
{

	RCC_ClocksTypeDef RCC_Clocks;

	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    // COnfigure and init peripherals
	GPIO_Conf_Init();
	USART_Conf_Init();

    // turn off buffers, so IO occurs immediately
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);


    UNITY_BEGIN();

    RUN_TEST(test_AverageThreeBytes_should_AverageMidRangeValues);
    RUN_TEST(test_AverageThreeBytes_should_AverageHighValues);
    return UNITY_END();
}
