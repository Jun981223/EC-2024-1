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

PinName_t LED_pin = PA_5;
PinName_t button_pin = PC_13;
 

void setup(void);
	
int main(void) { 
	// Initialization
	setup();
	
	int buttonState = 0;       
	int lastButtonState = 0;   
	int ledState = 0;      
	
	// Infinite loop
    while(1){
        buttonState = GPIO_read(button_pin);  
			
        if(buttonState == 0 && lastButtonState == 1) {
            ledState = !ledState; 	// Toggling the state of LED
            GPIO_write(LED_pin, ledState);
        }
        
        lastButtonState = buttonState;
    }
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	GPIO_init(LED_PIN, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(LED_PIN, EC_PU);
	GPIO_otype(LED_PIN, OpenDrain);
	GPIO_ospeed(LED_PIN, MediumSpeed);
}
