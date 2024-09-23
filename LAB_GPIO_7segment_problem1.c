/**
******************************************************************************
* @author	Han Dongjun
* @Mod		09-23-2024
* @brief	Embedded Controller:  LAB GPIO 7segment
*					 - Increasing the displayed number from 0 to 9 with each button press
* 
******************************************************************************
*/


#include "stm32f4xx.h"
#include "ecRCC2_student.h"
#include "ecGPIO2_student.h"


#define LED_PIN_D PA_7
#define LED_PIN_C PB_6
#define LED_PIN_B PC_7
#define LED_PIN_A PA_9


#define BUTTON_PIN PC_13

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	int buttonState = 0;
	int lastButtonState = 1;  
	
	unsigned int cnt = 0;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		buttonState = GPIO_read(BUTTON_PIN);
		
	//Problem 1: Display a Number with Button Press with decorder		
		sevensegment_display(cnt % 10);
		
		if(buttonState == 0 && lastButtonState == 1)
			cnt++; 
        if (cnt > 9)
					cnt = 0;
		  //for(int i = 0; i < 500000; i++){}  // delay_ms(500);
				
			lastButtonState = buttonState;
	}
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	
//Problem 1: Display a Number with Button Press with decorder
	sevensegment_display_init(LED_PIN_D, LED_PIN_C, LED_PIN_B, LED_PIN_A);  // Decoder input D,C,B,A
}