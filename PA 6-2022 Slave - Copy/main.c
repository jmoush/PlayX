// user button connected to PF4 (increment counter on falling edge)

#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
//#include "SysTickInts.h"
#include "PLL.h"
#include "UART.h"

#define SW1							0x01											// on the left side of the Launchpad board
#define SW2							0x10											// on the right side of the Launchpad board

#define RED_LED     		0x02
#define BLUE_LED  	  	0x04
#define GREEN_LED				0x08
#define YELLOW_LED			0x0A
#define WHITE_LED				0x0E
#define PA2 (*((volatile unsigned long *)0x40004010))
#define PA3 (*((volatile unsigned long *)0x40004020))
#define PA4 (*((volatile unsigned long *)0x40004040))
#define PA5 (*((volatile unsigned long *)0x40004080))
#define PA6 (*((volatile unsigned long *)0x40004100))
//#define PA7 (*((volatile unsigned long *)0x40004200))
void EnableInterrupts(void);
void DisableInterrupts(void);

void PortA_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGCGPIO_R |= 0x00000001;     // 1) activate clock for Port A
  delay = SYSCTL_RCGCGPIO_R;           // allow time for clock to start
  GPIO_PORTA_AMSEL_R &= ~0x7C;      // 3) disable analog on PA2-7
  GPIO_PORTA_PCTL_R &= ~0xFFFFFFFF; // 4) PCTL GPIO on PA2-7
	GPIO_PORTA_DIR_R |=0x7C;        // 5) direction PA2-7 output  
	GPIO_PORTA_AFSEL_R &= ~0x7C;      // 6) PA2-7 regular port function
  GPIO_PORTA_DEN_R |= 0x7C;         // 7) enable PA2-7 digital port
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
	///* Interrupts
	GPIO_PORTF_IS_R &= ~0x11;     		// PF4 and PF0 edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11;    		// PF4 and PF0 are not both edges
	GPIO_PORTF_IEV_R &= ~0x11;    		// PF4 and PF0 falling edge event
	GPIO_PORTF_ICR_R = 0x11;      		// clear flag4 and flag0
	GPIO_PORTF_IM_R |= 0x11;      		// arm interrupt on PF4 and PF1
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // priority 5
  NVIC_EN0_R = 0x40000000;      		// enable interrupt 30 (port F) in NVIC
  EnableInterrupts();           		// Clears the I bit
//*/
}

// Read PF4,PF0 inputs
uint32_t PortF_Input(void){     
  return (GPIO_PORTF_DATA_R&0x11);
}

// Write PF3-PF1 outputs
void PortF_Output(uint32_t data){
  GPIO_PORTF_DATA_R |= data;    
}
void PortF_Toggle(uint32_t data){
  GPIO_PORTF_DATA_R ^= data;    
}

void PortF_Off(uint32_t data){
  GPIO_PORTF_DATA_R &= ~data;    
}
//PortA functions
void PortA_Output(uint32_t data){
  GPIO_PORTA_DATA_R = data;    
}
void PortA_Toggle(uint32_t data){
  GPIO_PORTA_DATA_R ^= data;    
}

void PortA_Off(uint32_t data){
  GPIO_PORTA_DATA_R &= ~data;    
}

// PortF_handler
void GPIOPortF_Handler(void){
	if (PortF_Input() == SW1){
		PortF_Off(0xff);
		//UART_OutChar('1');
		}
 		if (PortF_Input() == SW2){
			PortF_Output(GREEN_LED);//turn off all output
		//	UART_OutChar('2');
		}
//	// acknowledge flag4 and flag0
	GPIO_PORTF_ICR_R = 0x11;
}

int main(void){
	volatile uint32_t ui32Loop;
  PortF_Init();
	PortA_Init();										// Initialize port F: Port F interrupt is enabled
	DisableInterrupts(); 
	PLL_Init();												// bus clock at 10 MHz
	UART_Init();      								// initialize UART
  EnableInterrupts();
	//DisableInterrupts();
	//PortF_Output(BLUE_LED);
	while (1){
		switch (UART_InChar()){
			case 'A': PortA_Output(0x04);break; 		//PortA_Output(0x04)
			case 'B': PortA_Output(0x08);break;		  //PortA_Output(0x08)
			case 'C': PortA_Output(0x10);break;			//PortA_Output(0x10)
			case 'M': PortA_Toggle(0x20);break;     //PortA_Togggle(0x20) toggles the mode
			case 'H': PortA_Toggle(0x40);break;			//PortA_Output(0x40)
			//case 'L': PortA_Output(0x80);break; 	//PortA_Output(0x80) Not in use since volume was turned into one button
			//default is optional since there should not be any characters other than the ones in the case statement
		}		
	}
}

      
