// Switch.c
// This software configures the on-board switches and LEDs.

// Port B bits 2-0 have the 3-bit DAC

// Port E is for switches PE0(SW1) and PE1 (SW2)

#include <stdint.h>
#include "tm4c123gh6pm.h"

//---------------------Switch_Init---------------------
// initialize switch interface
// Input: none
// Output: none 
void Switch_Init(void){ volatile unsigned long  delay;
	// Following function initializw PE0 and PE1 to be used as switch	
	SYSCTL_RCGCGPIO_R |= 0x10; 				// activate port E
  delay = SYSCTL_RCGCGPIO_R;    		// allow time to finish PortE clock activating
	GPIO_PORTE_PCTL_R &= ~0x000000FF; // regular function 
	GPIO_PORTE_AMSEL_R &= ~0x03;   		// no analog 
  GPIO_PORTE_DIR_R &= ~0x03;      		// make PE2-0 out
	GPIO_PORTE_AFSEL_R &= ~0x03;   		// disable alt funct on PE2-0
	GPIO_PORTE_DEN_R |= 0x03;      		// enable digital I/O on PE2-0
}


//---------------------Delay10ms---------------------
// wait 10ms for switches to stop bouncing
// Input: none
// Output: none
void Delay10ms(void){unsigned long volatile time;
  time = 166667;  // 10ms/20ns/3
  while(time > 0){
		time--;
  }                         // This while loop takes approximately 3 cycles
}
//---------------------Switch_In---------------------
// read the values of the two switches
// Input: none
// Output: 0x00,0x01,0x10,0x11 from the two switches
//         0 if no switch is pressed
// bit1 PE1 SW1 switch
// bit0 PE0 SW2 switch 
unsigned long Switch_In(void){ 
	volatile uint32_t input;	
  // read the switch status
	input = GPIO_PORTE_DATA_R&0x03;
	// Delay 20 ms, call 10 ms twice (Think, why it is written differently from previous assignemnt. what could be the reason? 
	Delay10ms();
	Delay10ms();
	// read switch status again
	// if both read shows same status (pressed) then only, take decision that switch is pressed
	if ( (GPIO_PORTE_DATA_R&0x03) == input){
		return input; 
	}
	
	else
	return 0;               // remoVe this
}


