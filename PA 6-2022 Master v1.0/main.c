// user button connected to PF4 (increment counter on falling edge)
//Slave HC-05 is the module with the imprint in the middle. 
#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
//#include "SysTickInts.h"
#include "PLL.h"
#include "UART.h"

//Port F buttons
#define SW1							0x01											// on the left side of the Launchpad board
#define SW2							0x10											// on the right side of the Launchpad board

//Port F LEDs
#define RED_LED     		0x02
#define BLUE_LED  	  	0x04
#define GREEN_LED				0x08
#define YELLOW_LED			0x0A
#define WHITE_LED				0x0E
//Addresses for Port A.
#define PA2 (*((volatile unsigned long *)0x40004010))
#define PA3 (*((volatile unsigned long *)0x40004020))
#define PA4 (*((volatile unsigned long *)0x40004040))
#define PA5 (*((volatile unsigned long *)0x40004080))
#define PA6 (*((volatile unsigned long *)0x40004100))
//#define PA7 (*((volatile unsigned long *)0x40004200)) use if there are two volume buttons

//defined to suppress warnings.
void EnableInterrupts(void);
void DisableInterrupts(void);

//Delay to remedy debounce
//Don't worry about compiler errors since it is assembly code. It compiles without throwing a warning/error.
__asm void Delay(unsigned long counter){
 subs r0, #1
 bne Delay // 3 clock cycle delay loop
 bx lr
}
// Initialize port F.
void PortF_Init(void){ volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x00000020; 	// activate clock for port F
  delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF0-4
  GPIO_PORTF_AMSEL_R = 0x00;        // disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // PCTL GPIO on PF0-4
  GPIO_PORTF_DIR_R = 0x0E;          // PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // disable alt funct on PF0-7
  GPIO_PORTF_PUR_R = 0xFF;          // enable pull-up on PF0-7
  GPIO_PORTF_DEN_R = 0x1F;          // enable digital I/O on PF0-4
	
	GPIO_PORTF_IS_R &= ~0x11;     		// PF4 and PF0 edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11;    		// PF4 and PF0 are not both edges
	GPIO_PORTF_IEV_R &= ~0x11;    		// PF4 and PF0 falling edge event
	GPIO_PORTF_ICR_R = 0x11;      		// clear flag4 and flag0
	GPIO_PORTF_IM_R |= 0x11;      		// arm interrupt on PF4 and PF1
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // priority 5
  NVIC_EN0_R = 0x40000000;      		// enable interrupt 30 (port F) in NVIC
  EnableInterrupts();           		// Clears the I bit
}
//If using two volumes buttons and PA7(use 0xFC for the initialization)
void PortA_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGCGPIO_R |= 0x00000001;     // 1) activate clock for Port A
  delay = SYSCTL_RCGCGPIO_R;           // allow time for clock to start
  GPIO_PORTA_AMSEL_R &= ~0x7C;      // 3) disable analog on PA2-6
  GPIO_PORTA_PCTL_R &= ~0xFFFFFFFF; // 4) PCTL GPIO on PA2-6
	GPIO_PORTA_DIR_R &=~0x7C;        // 5) direction PA2-6 input  
	GPIO_PORTA_AFSEL_R &= ~0x7C;      // 6) PA2-6 regular port function
  GPIO_PORTA_DEN_R |= 0x7C;         // 7) enable PA2-6 digital port
}
// Read PF4,PF0 inputs
uint32_t PortF_Input(void){     
  return (GPIO_PORTF_DATA_R&0x11);
}

// Write PF3-PF1 outputs
void PortF_Output(uint32_t data){
  GPIO_PORTF_DATA_R = data;    
}
void PortF_Toggle(uint32_t data){
  GPIO_PORTF_DATA_R ^= data;    
}


// Port F handler
void GPIOPortF_Handler(void){
	// Add your code here
	if (PortF_Input() == SW1){ // for debugging since PortA is primarily used
//			UART_OutChar('M');
		PortF_Output(GREEN_LED);
		}
 		if (PortF_Input() == SW2){
//			UART_OutChar('L');
			PortF_Output(0);
		}
//	// acknowledge flag4 and flag0
	GPIO_PORTF_ICR_R = 0x11;
}
int main(void){
	volatile uint32_t ui32Loop;
  PortF_Init();											// Initialize port F: Port F interrupt is enabled
	DisableInterrupts(); 
	PortA_Init();
	PLL_Init();												// bus clock at 10 MHz
	UART_Init();      								// initialize UART
  EnableInterrupts();//comment this or uncomment DisableInterrupts for final version. 
	//DisableInterrupts(); //PortF interrupts used for debugging.
	while(1){
//if input is high, output corresponding character
//Debouncing code within each if statement to alleviate bouncing of the swtiches.
//Buttons A-C on toy,M for mode and H is for volume.
//Use L if there is two buttons for volume control.
	if (PA2 == 0x04){
		UART_OutChar('A');
		Delay(1000000);//between 100000-1000000
		while(PA2 != 0x00){}
		Delay(1);
	} 
	if (PA3 == 0x08){
		UART_OutChar('B');
		Delay(1000000);
		while (PA3 != 0x00){}
		Delay(1);
	}
	if (PA4 == 0x10){
		UART_OutChar('C');
		Delay(1000000);
		while (PA4 != 0x00){}
		Delay(1);
	}
	if (PA5 == 0x20){
	UART_OutChar('M');
	Delay(1000000);//between 100000-1000000
	while(PA5 != 0x00){}
	Delay(1);
//	PortF_Toggle(RED_LED);//debugging
	}
	if (PA6 == 0x40){
		UART_OutChar('H');
		Delay(1000000);
		while (PA6 != 0x00){}
	//PortF_Toggle(BLUE_LED);//debugging
		Delay(1);
	}	
	/*
	if (PA7 == 0x80){
		UART_OutChar('L');
		Delay(1000000);
		while (PA7 != 0x00){}
	//PortF_Toggle(BLUE_LED);//debugging
		Delay(1);
		//If volume low is its own button.
	}
*/	
}
}
