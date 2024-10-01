/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Han Dongjun
Created          : 05-03-2021
Modified         : 10-01-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_SysTick
/----------------------------------------------------------------*/


#ifndef __EC_SYSTICK2_H
#define __EC_SYSTICK2_H

#include "stm32f4xx.h"
#include "ecRCC2_student.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void SysTick_init(void);
void SysTick_Handler(void);
void SysTick_counter();
void delay_ms(uint32_t msec);
void SysTick_reset(void);
uint32_t SysTick_val(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_SYSTICK2_H
