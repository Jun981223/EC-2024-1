/**
******************************************************************************
* @author	Han Dongjun
* @Mod		09-12-2024
* @brief	Embedded Controller:  LAB Digital In/Out
*					 - Toggle LED LD2 by Button B1 pressing
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC2_student.h"
#include "ecGPIO2_student.h"

PinName_t LED_pin0 = PA_5;
PinName_t LED_pin1 = PA_6;
PinName_t LED_pin2 = PA_7;
PinName_t LED_pin3 = PB_6;

PinName_t button_pin = PC_13;


void setup(void);
	
	
int main(void) { 
	// Initialization
	setup();
	
	int buttonState = 0;
	int lastButtonState = 1;  
	int ledIndex = 0; // Current on-LED
	PinName_t ledPins[4] = {LED_pin0, LED_pin1, LED_pin2, LED_pin3}; // LED arrangement
	
	// Infinite loop
	while(1) {
		buttonState = GPIO_read(button_pin);  
		
		// respond when button pressed
		if(buttonState == 0 && lastButtonState == 1) {
			
			// Turn off the current LED
			GPIO_write(ledPins[ledIndex], 0);  
			
			// Move to next LED Index (0 -> 1 -> 2 -> 3 -> 0 ...)
			ledIndex = (ledIndex + 1) % 4;
			
			// Turn on the next LED
			GPIO_write(ledPins[ledIndex], 1);  
		}
		
		// last button state update
		lastButtonState = buttonState;
	}
}

/*
int main(void) { 
	// Initialization
	setup();
	
	int buttonState = 0;
	int lastButtonState = 0;  
	
  int ledState0 = 0;	
	int ledState1 = 0;	
	int ledState2 = 0;	
	int ledState3 = 0;     
	
	
	// Infinite loop
    while(1){
      buttonState = GPIO_read(button_pin);  
			ledState0 = GPIO_read(LED_pin0);
			ledState1 = GPIO_read(LED_pin1);
			ledState2 = GPIO_read(LED_pin2);
			ledState3 = GPIO_read(LED_pin3);

			
        if(buttonState == 0 && lastButtonState == 1){
					if(ledState3 == 0) {
					
					ledState3 = !ledState3; 
          ledState0 = !ledState0; 
					
					GPIO_write(LED_pin3, ledState3);
          GPIO_write(LED_pin0, ledState0);
					
					//lastButtonState = buttonState;
				}else if(ledState0 == 1){
							
					ledState0 = !ledState0;
          ledState1 = !ledState1;
					
					GPIO_write(LED_pin0, ledState0);
          GPIO_write(LED_pin1, ledState1);
					
					//lastButtonState = buttonState;
					
				}else if(ledState1 == 1){
							
					ledState1 = !ledState1;
          ledState2 = !ledState2;
					
					GPIO_write(LED_pin1, ledState1);
          GPIO_write(LED_pin2, ledState2);
					
					//lastButtonState = buttonState;
					
				}else if(ledState2 == 1)
				{
					
					ledState2 = !ledState2;
          ledState3 = !ledState3;
					
					GPIO_write(LED_pin2, ledState2);
          GPIO_write(LED_pin3, ledState3);
					
					//lastButtonState = buttonState;
				
				}
				lastButtonState = buttonState;
			}
		}
	}
*/

// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	
	GPIO_init(LED_pin0, OUTPUT);
	GPIO_init(LED_pin1, OUTPUT);
	GPIO_init(LED_pin2, OUTPUT);
	GPIO_init(LED_pin3, OUTPUT);
	
	GPIO_otype(LED_pin0, PushPull);
	GPIO_otype(LED_pin1, PushPull);
	GPIO_otype(LED_pin2, PushPull);
	GPIO_otype(LED_pin3, PushPull);
	
	GPIO_pupd(LED_pin0, EC_PU);
	GPIO_pupd(LED_pin1, EC_PU);
	GPIO_pupd(LED_pin2, EC_PU);
	GPIO_pupd(LED_pin3, EC_PU);
	
	GPIO_ospeed(LED_pin0, MediumSpeed);
	GPIO_ospeed(LED_pin1, MediumSpeed);
	GPIO_ospeed(LED_pin2, MediumSpeed);
	GPIO_ospeed(LED_pin3, MediumSpeed);
	
}
