# PlayX
This project is for the 2022-2023 Senior Design Team 02-PlayXtension at the University Of Kentucky. This project makes use of two Tiva TM4C123GXL boards and two HC-05 Bluetooth modules as well as the Keil uVision 5 IDE.
# Keil uVision 5 Resources
The ARM compiler version can be downloaded at https://developer.arm.com/downloads/view/ACOMP5. If using version 5.29 or higher of MDK, Stellaris debugger needs an addon to work which can be downloaded at https://developer.arm.com/documentation/ka002280/latest. The code was compiled using MDK 5.38,version 5.06 update 7 (build 960) of keil uvision 5 and the stellaris drivers for debugging.  
# Microcontroller Connections
Based on the Tiva TM4C123GXL:  
The port used for the pushbuttons are Port A 2-6  
The HC-05 pin connections are:  
RXD-PE5  
TXD-PE4  
VCC-VBUS  
GND-GND  
# Master and Slave Files
Their are two source code files which are contained in the two folders named PA6-2022 Master v1.0 & PA6-2022 Slave v1.0. with the project file being PA6.uvprojx. 
The Master source code is intended to be flashed on a Tiva TM4C123GXL board connected to a HC-05 Bluetooth Module that is in master mode. The Slave source code is intended to be flashed on a Tiva TM4C123GXL board connected to a HC-05 Bluetooth Module that is in slave mode.
# AT Commands
HC-05 Bluetooth Module can be in Master and/or Slave mode and pair to another HC-05 using AT commands.
A pdf of AT commands available for the HC-05 is provided at https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf for reference. The AT commands were implemented using an Arduino IDE and Arduino UNO because of the convienence, but they can also be implemented inside Keil and using a serial terminal like PuTTy.  
# List of AT Commands Used:  
*AT+ADDR?\r\n*. Retrieves the slave’s module Bluetooth address to allow master to pair using the bind command.  
*AT+NAME \r\n*. Optional, I changed the name of master module to MasterHC05 and slave module to slaveHC05.  
*AT+ROLE=0*. Sets module role to slave. AT+ROLE=1 sets module role to master.   
*AT+BIND=1234, 56, abcdef\r\n*. Master binds pairing to personal slave’s address. AT command only sent to master.  
