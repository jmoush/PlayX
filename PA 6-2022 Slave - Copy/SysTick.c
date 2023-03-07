#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

// Used in part 2B
volatile uint32_t g_handler_calls;

//Initialize Systick
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;																						// Disable SysTick during setup
	NVIC_ST_RELOAD_R = 0;
	NVIC_ST_CURRENT_R = 0; 																				// Any write to CURRENT clears it
	NVIC_ST_CTRL_R = 0x05; 																				// Enable Systick w/o interrupts	
}


// Configure SysTick to generate an interrupt every 10ms, used in part 2B
// Assume 16 MHz clock
void SysTick_Init_Interrupts(void){
	g_handler_calls = 0; 																					// Initialize counter as 0
	NVIC_ST_CTRL_R=0;																							// disable SysTick during setup
	NVIC_ST_RELOAD_R = 250000-1;																		// Reload Value = 10ms/40ns = 250,000  40ns is period for 25MHz
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;  	// priority 2   , doesn't matter here
	NVIC_ST_CTRL_R = 0x07;																				// enable SysTick with core clock and interrupts
}


// Clock speed is 16 MHz
// 100us is equivalent to 1,600 clock cycles
// 40000  -----> 1 ms (
static void SysTick_Delay100us_16MHz(void){
	//Use the Systick Timer to generate a 100uS delay
	NVIC_ST_RELOAD_R = 1600-1; 																		// Number of clock ticks to wait
	NVIC_ST_CURRENT_R = 0; 																				// Any value written to write clears it
	while((NVIC_ST_CTRL_R&0x00010000)==0){} 											// Wait for count flag
}


// Write code to generate a 1 sec delay
// Your code should call SysTick_Delay1ms()
void SysTick_Delay1s_16MHz(void){
	int i=0;
	for(i=0; i<10000; i++){
		SysTick_Delay100us_16MHz();
	}
} 


// Write code to generate 1ms delay assuming a clock speed of 25MHz
static void SysTick_Delay100us_25MHz(void){
	//Use the Systick Timer to generate a 100uS delay
	NVIC_ST_RELOAD_R = 2500-1; 																		// Number of clock ticks to wait
	NVIC_ST_CURRENT_R = 0; 																				// Any value written to write clears it
	while((NVIC_ST_CTRL_R&0x00010000)==0){} 											// Wait for count flag
}


// Write code to generate a 1 sec delay when the clock speed is 25MHz
// Your code should call SysTick_Delay100us_25MHz()
void SysTick_Delay1s_25MHz(void){
	int i=0;
	for(i=0; i<10000; i++){
		SysTick_Delay100us_25MHz();
	}
}
// New defined Function
void SysTick_Delay10ms_25MHz(void){
	int i=0;
	for(i=0; i<100; i++){
		SysTick_Delay100us_25MHz();
	}
}
void SysTick_Wait10ms(uint32_t delay){
	int i=0;
	for(i=0; i<delay; i++){
		SysTick_Delay10ms_25MHz();
	}
}

uint32_t countY=0, countG=0;

void SysTick_Handler(void){
	
	if(g_handler_calls % 10000 == 0){															// 1 Second  = 100us*10,000
		GPIO_PORTA_DATA_R ^=  0x04  ;																// Red LED Toggles at every one Second
		countY++; countG++;
		
		if( (countY != 1) ){																				// Yellow LED, 1 S ON, 2 S OFF
			GPIO_PORTA_DATA_R &= ~0x08;																// Yellow LED OFF
			if (countY == 3){countY=0;}
		} 
		else GPIO_PORTA_DATA_R |= 0x08;															// Yellow LED ON
		
		if( (countG != 1) ){																				// Green LED, 1 S ON, 3 S OFF
			GPIO_PORTA_DATA_R &= ~0x10;																// Green LED OFF
			if (countG == 4){countG=0;}
		} 
		else GPIO_PORTA_DATA_R |= 0x10;															// Green LED ON
	}
	
	g_handler_calls++;																						// Incrementing Interrupt Handler Call
}
