#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "SysTickInts.h"

#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void SysTick_Init(uint32_t period){
  NVIC_ST_CTRL_R = 0;        																	// disable SysTick during setup
  NVIC_ST_RELOAD_R = period - 1;															// reload value
  NVIC_ST_CURRENT_R = 0;      																// any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x10000000; 	// priority 4
  NVIC_ST_CTRL_R = 0x00000005;																// enable SysTick with core clock.
}
