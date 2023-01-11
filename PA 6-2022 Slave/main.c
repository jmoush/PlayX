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

// Read PF4,PF0 inputs
uint32_t PortF_Input(void){     
  return (GPIO_PORTF_DATA_R&0x11);
}

// Write PF3-PF1 outputs
void PortF_Output(uint32_t data){
  GPIO_PORTF_DATA_R = data;    
}


// Port F handlerA
void GPIOPortF_Handler(void){
	// Add your code here
	if (PortF_Input() == SW1){
		UART_OutChar('B');
	//	PortF_Output(BLUE_LED);
		}
 		if (PortF_Input() == SW2){
			UART_OutChar('b');
			//PortF_Output(0x00);
		}
//	// acknowledge flag4 and flag0
	GPIO_PORTF_ICR_R = 0x11;
}
// Write port A for output GPIO pins.
//expand inf while loop to probably switch case to handle all the inputs.
//Turn the DATA_R register on when input is 1.
void HC05_PrintChar(char input){
  while((UART5_FR_R&UART_FR_TXFF) != 0) {};
  UART5_DR_R = input;
//  UART_OutChar(input); // echo debugging
}
void HC05SendCommand(const char* inputString){
  int index = 0;
  while(inputString[index] != 0){
    HC05_PrintChar(inputString[index++]);
  }
}

int main(void){
	volatile uint32_t ui32Loop;
  PortF_Init();											// Initialize port F: Port F interrupt is enabled
	DisableInterrupts(); 
	PLL_Init();												// bus clock at 10 MHz
	UART_Init();      								// initialize UART
  EnableInterrupts();
	//DisableInterrupts();
	//HC05SendCommand("AT+NAME=SlaveHC-05\r\n"); //Changes Module name
	//HC05SendCommand("AT+ROLE=0"); //sets to slave
//	HC05SendCommand("AT+ADDR?\r\n"); //gets module address
//  HC05SendCommand("AT+NAME?\r\n");
	while (1){
		// Add your code here.
		// PA0='A',PA1='a',PB0='B',PB1='b',PC0='C',PC1='c'
		/*
switch (UART_InChar()){
		case('A'){
		PortA_Output();
		}
		case('a'){
		PortA_Output();
		}
		case('B'){
		PortB_Output();
		}
		case('b'){
		PortB_Output();
		}
		case('C'){
		PortC_Output();
		}
		case('C'){
		PortC_Output();
		}
		}
		*/
		if (UART_InChar() == 'G'){
		PortF_Output(GREEN_LED);
		}
		if (UART_InChar() == 'g'){
		PortF_Output(0x00);
		}
	}
}