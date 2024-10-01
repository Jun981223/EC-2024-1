/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Han Dongjun
Created          : 05-03-2021
Modified         : 10-01-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_EXTI
/----------------------------------------------------------------*/


#include "ecSTM32F4v2.h"

#define BUTTON_PIN PC_13
// OUTPUT LED_PIN define is defined by function, sevensegment_display_init2
// pinNames_EXTI[4] = {PA_7, PB_6, PC_7, PA_9};

unsigned int cnt = 0;

// Initialiization 
void setup(void)
{
	RCC_PLL_init();
	//SysTick_init();

	//initialize output source
  sevensegment_display_init2(); // OUTPUT, PushPull, EC_NPUNPD, MediumSpeed
	
	//initialize input source
	GPIO_init(BUTTON_PIN, INPUT);
	GPIO_pupd(BUTTON_PIN, EC_PU);
	
	// Priority Highest(0) External Interrupt 
	EXTI_init(BUTTON_PIN, FALL, 0); // when Input button is released (1->0 / Falling edge), interrupt 
}

int main(void) {
	setup();
	
	// Inifinite Loop
	while(1){
	//not doing anything, and waiting for interrupt
	}
}


//EXTI for Pin 13
void EXTI15_10_IRQHandler(void) {
	if (is_pending_EXTI(BUTTON_PIN)) {
		//increasing the number of 7segment
		cnt ++;
		//division number into 10 to get rest
		sevensegment_display(cnt % 10);
		//clear the interrupt
		clear_pending_EXTI(BUTTON_PIN); 
	}
}