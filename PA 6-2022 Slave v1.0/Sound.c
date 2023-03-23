// Sound.c, derived from SysTickInts.c


// Use the SysTick timer to request interrupts at a particular period.

// Port B bits 2-0 have the 3-bit DAC

// Port E, SW1(PE0) and SW2(PE2)
// SysTick ISR: Calls SineWave 

#include <stdint.h>
#include "tm4c123gh6pm.h"
#define PB012   (*((volatile uint32_t *)0x40005011))		 //PABase Add + 0x08+0x04 +0x10




unsigned char Index;  

// 3-bit 16-element sine wave
const unsigned char SineWave[16] = {4,5,6,7,7,7,6,5,4,3,2,1,1,1,2,3};

//4-bit 32-element Sine wave for Piano
const unsigned shortwave[32] = {	
  8,9,11,12,13,14,14,15,15,15,14,	
  14,13,12,11,9,8,7,5,4,3,2,	
  2,1,1,1,2,2,3,4,5,7};	

// **************DAC_Init*********************
// Initialize 3-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){unsigned long volatile delay;	
	
	SYSCTL_RCGCGPIO_R |= 0x02; 				// activate port B
  delay = SYSCTL_RCGCGPIO_R;    		// allow time to finish PortB clock activating
	GPIO_PORTB_PCTL_R &= ~0x0000FFFF; // regular function 
	GPIO_PORTB_AMSEL_R &= ~0x0f;   		// no analog 
  GPIO_PORTB_DIR_R |= 0x0f;      		// make PB3-0 out
	GPIO_PORTB_AFSEL_R &= ~0x0f;   		// disable alt funct on PB3-0
	GPIO_PORTB_DEN_R |= 0x0f;      		// enable digital I/O on PB3-0
	

}

// **************Sound_Init*********************
// Initialize Systick periodic interrupts, this is basically demonstrate SysTick usage
// Input: interrupt period
//        Units of period are 12.5ns
//        Maximum is 2^24-1
//        Minimum is determined by lenght of ISR
// Output: none
void Sound_Init(unsigned long period){
  DAC_Init();          // Port B is DAC
  Index = 0;
	// your code begins below
	
  NVIC_ST_CTRL_R = 0; 						 // disable SysTick during setup// disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;		 // reload value should be as per the value passed in period
	NVIC_ST_CURRENT_R = 0; 					 // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
  NVIC_ST_CTRL_R = 0x07;           // enable SysTick with core clock and interrupts
}

// **************DAC_Out*********************
// output to DAC
// Input: 3-bit data, 0 to 7 
// Output: none
void DAC_Out(unsigned long data){
  // write the value to Data register at PortB
	 GPIO_PORTB_DATA_R = data;
}

// Interrupt service routine
// Executed every 20ns*(period)
void SysTick_Handler(void){
 
	// Increment the Index and make sure it should roll over to 0 after 0x1F , i.e. 32 in decimal,  
	// corresponding to size of the variable SineWave[32]

	Index = (Index +1) & 0x1F ;	
	// calll DAC_out function and pass 
 // DAC_Out(SineWave[Index]); 						// Comment this line for Part 3
	
	// Pass shortwave samples for Piano - in Part 3
	//Index = (Index +1) & 0xFF>>3 ;	
	DAC_Out(shortwave[Index]); 

}


