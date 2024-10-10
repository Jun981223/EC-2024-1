/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Han Dongjun
Created          : 05-03-2021
Modified         : 09-23-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/



#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO2.h"

PinName_t pinNames[8] = {PA_5, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10};
PinName_t pinNames_EXTI[4] = {PA_7, PB_6, PC_7, PA_9};

void GPIO_init(PinName_t pinName, uint32_t mode){     
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	
	
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	if (Port == GPIOC)
		RCC_GPIOC_enable();
	if (Port == GPIOD)
		RCC_GPIOD_enable();
	if (Port == GPIOE)
		RCC_GPIOE_enable();

	if (Port == GPIOH)
		RCC_GPIOH_enable();
	

	// You can also make a more general function of
	void RCC_GPIO_enable(GPIO_TypeDef *Port); 

	GPIO_mode(pinName, mode);
}



// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
   Port->MODER &= ~(3UL<<(2*pin));     
   Port->MODER |= mode<<(2*pin);    
}



// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, int speed){
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
		Port->OSPEEDR &= ~ (3UL<<(2 * pin));
		Port->OSPEEDR |= speed<<(2 * pin);
}


// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, int type){
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);

		Port->OTYPER &= ~ (1UL<<(pin)); 		    // Clear '00'
	  Port->OTYPER |= type<<pin;  
}


// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, int pupd){
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
   Port->PUPDR &= ~ (3UL<<(2 * pin));	 	
	 Port->PUPDR |= pupd<<(2 * pin);
}


void GPIO_write(PinName_t pinName, int Output){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    if (Output == HIGH)
        Port->ODR |= (1UL << pin);
    else
        Port->ODR &= ~(1UL << pin);
}


int GPIO_read(PinName_t pinName){
    GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    unsigned int btVal = 0;
    btVal = (Port->IDR & (1UL << pin)) ? 1 : 0;

    return btVal;
}
 

char decoder_output[10][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 0},
	{0, 0, 1, 1},
	{0, 1, 0, 0},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{0, 1, 1, 1},
	{1, 0, 0, 0},
	{1, 0, 0, 1}
};



void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD)
{
	  GPIO_init(pinNameA, OUTPUT);
    GPIO_init(pinNameB, OUTPUT);
    GPIO_init(pinNameC, OUTPUT);
    GPIO_init(pinNameD, OUTPUT);
    
    GPIO_otype(pinNameA, PushPull);
    GPIO_otype(pinNameB, PushPull);
    GPIO_otype(pinNameC, PushPull);
    GPIO_otype(pinNameD, PushPull);
    
    GPIO_pupd(pinNameA, EC_NPUNPD);
    GPIO_pupd(pinNameB, EC_NPUNPD);
    GPIO_pupd(pinNameC, EC_NPUNPD);
    GPIO_pupd(pinNameD, EC_NPUNPD);
    
    GPIO_ospeed(pinNameA, MediumSpeed);
    GPIO_ospeed(pinNameB, MediumSpeed);
    GPIO_ospeed(pinNameC, MediumSpeed);
    GPIO_ospeed(pinNameD, MediumSpeed);
}

void sevensegment_display_init2(void){
    for(int i = 0; i < 4; i++) {
        GPIO_init(pinNames_EXTI[i], OUTPUT);       
        GPIO_otype(pinNames_EXTI[i], PushPull);    
        GPIO_pupd(pinNames_EXTI[i], EC_NPUNPD);    
        GPIO_ospeed(pinNames_EXTI[i], MediumSpeed);
    }
}


// main.c, counting the number
void sevensegment_display(uint8_t num){
    if (num > 9) return;

    // bringing set of 4 bits number from decoder_output
    char *code = decoder_output[num];

    // defining each bit number for each pin
    GPIO_write(PA_7, code[0]);  // D
    GPIO_write(PB_6, code[1]);  // C
    GPIO_write(PC_7, code[2]);  // B
    GPIO_write(PA_9, code[3]);  // A
}


// Anode
char decoder_alphabet[10][8] = {
//a, b, c, d, e, f, g, h 
	{0, 0, 0, 0, 0, 0, 1, 0},
	{1, 0, 0, 1, 1, 1, 1, 0},
	{0, 0, 1, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0},
	{1, 0, 0, 1, 1, 0, 0, 0},
	{0, 1, 0, 0, 1, 0, 0, 0},	
	{1, 1, 0, 0, 0, 0, 0, 0},	
	{0, 0, 0, 1, 1, 1, 1, 0},	
	{0, 0, 0, 0, 0, 0, 0, 0},	
	{0, 0, 0, 1, 1, 0, 0, 0}		
};

/* Cathode
{1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 0, 0, 0},
	{1, 1, 0, 1, 1, 0, 1, 0},
	{1, 1, 1, 1, 0, 0, 1, 0},
	{0, 1, 1, 0, 0, 1, 1, 0},
	{1, 0, 1, 1, 0, 1, 1, 0},	
	{0, 0, 1, 1, 1, 1, 1, 0},	
	{1, 1, 1, 0, 0, 0, 0, 0},	
	{1, 1, 1, 1, 1, 1, 1, 0},	
	{1, 1, 1, 0, 0, 1, 1, 0}	
*/

void sevensegment_decoder_init(void){
    for(int i = 0; i < 8; i++) {
        GPIO_init(pinNames[i], OUTPUT);       
        GPIO_otype(pinNames[i], PushPull);    
        GPIO_pupd(pinNames[i], EC_NPUNPD);    
        GPIO_ospeed(pinNames[i], MediumSpeed);
    }
}


void sevensegment_decoder(uint8_t  num){
    if (num > 9) return;

    // bringing set of 8 bits number from decoder_alphabet
    char *code = decoder_alphabet[num];

    // defining each bit number for each pin
    GPIO_write(PA_5, code[0]);  // a
    GPIO_write(PA_6, code[1]);  // b
    GPIO_write(PA_7, code[2]);  // c
    GPIO_write(PB_6, code[3]);  // d
	  GPIO_write(PC_7, code[4]);  // e
    GPIO_write(PA_9, code[5]);  // f
    GPIO_write(PA_8, code[6]);  // g
    GPIO_write(PB_10, code[7]);  // h
}

/*
//In each 1 sec, toggling LED
void LED_toggle(void){
    GPIOA->ODR ^= (1<<5);
}
*/

void LED_toggle(void) {
    // Read current state of the LED pin
    if(GPIOA->ODR & (1<<5))    // If PA_5 is high (LED on)
        GPIO_write(LED_PIN, LOW);   // Turn off the LED
    else
        GPIO_write(LED_PIN, HIGH);  // Turn on the LED
}


void MCU_init(void){
    // CLOCK PLL 84MHz
    RCC_PLL_init();
    
    // SysTick 1msec
  //  SysTick_init();    
    
    // Button PC13
    GPIO_init(PC_13, INPUT);
    GPIO_pupd(PC_13, EC_PD);    
    
    // LED PA5
    GPIO_init(PA_5, OUTPUT);    

    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...        
    // USART Default Initialization
    // ...
    // Others
}


