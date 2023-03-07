#include "stdint.h"
#ifndef _SysTick_h
#define _SysTick_h

void SysTick_Init(void);
void SysTick_Init_Interrupts(void);
void SysTick_Delay1s_16MHz(void);
void SysTick_Delay1s_25MHz(void);
void SysTick_Delay10ms_25MHz(void);
void SysTick_Wait10ms(uint32_t delay);
#endif
