// Sound.h, 

// Runs on LM4F120 or TM4C123, 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// September 15, 2013
// Port B bits 2-0 have the 3-bit DAC
// Port F is onboard LaunchPad switches and LED
// Port F bit 4 is negative logic switch to play sound, SW1
// Piano: PF3 ISR heartbeat

// **************DAC_Init*********************
// Initialize 3-bit DAC 
// Input: none
// Output: none
void DAC_Init(void);

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 12.5ns
//        Maximum is 2^24-1
//        Minimum is determined by lenght of ISR
// Output: none
void Sound_Init(unsigned long period);

// the 256 comes from the length of the sine wave table
// bus is 50 MHz
// Period =  50000000/32/Freq=5000000/Freq
#define C    1493   // 1046.5 Hz		
#define B    1582   // 987.8 Hz		
#define BF   1676   // 932.3 Hz		
#define A    1776   // 880 Hz		
#define AF   1881   // 830.6 Hz		
#define G    1993   // 784 Hz		
#define GF  2112   // 740 Hz		
#define F   2237   // 698.5 Hz		
#define E   2370   // 659.3 Hz		
#define EF  2511   // 622.3 Hz		
#define D   2660   // 587.3 Hz		
#define DF  2819   // 554.4 Hz		
#define C0  2986   // 523.3 Hz		



// **************DAC_Out*********************
// output to DAC
// Input: 3-bit data, 0 to 7 
// Output: none
void DAC_Out(unsigned long data);
