# PlayX
This project is for the 22-23 Senior Design Team 02-PlayXtension at the University Of Kentucky. 
The resources for Keil,Stellaris,and AT commands are included in this project for reference and ease of access.  
# Microcontroller Connections
Based on the Tiva TM4C123GXL:  
The port used for the pushbuttons are Port A 2-6  
The HC-05 pin connections are:  
RXD-PE5  
TXD-PE4  
VCC-VBUS  
GND-GND  
# Master and Slave Files
The source code files is PA6.uvprojx which is located under the two folders named PA6-2022 Master v1.0 & PA6-2022 Slave v1.0.
This project makes use of two Tiva TM4C123GXL boards and two HC-05 Bluetooth modules.  
The Master source code is intended to be flashed on a Tiva TM4C123GXL board connected to a HC-05 Bluetooth Module that is in master mode.  
The Slave source code is intended to be flashed on a Tiva TM4C123GXL board connected to a HC-05 Bluetooth Module that is in slave mode.
# AT commands
HC-05 Bluetooth Module can be in Master and/or Slave mode and pair to another HC-05 using AT commands.
A pdf of AT commands available for the HC-05 is provided at https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf for reference. The AT commands were implemented using an Arduino IDE and Arduino UNO because of the convienence, but they can also be implemented inside Keil and using a serial terminal like PuTTy.  
# List of AT commands that were used:  
AT+ADDR?\r\n (To get the slave’s module Bluetooth address to allow master to pair using Bind command).  
AT+NAME \r\n (Optional, I changed the name of master module to MasterHC05 and slave module to slaveHC05).  
AT+ROLE=0 sets module role to slave, AT+ROLE=1 sets module role to master.   
AT+BIND=1234, 56, abcdef\r\n (Master binds pairing to personal slave’s address. AT command only sent to master).  
# Keil Resources
The code was compiled using MDK 5.38,version 5.06 update 7 (build 960) of keil uvision 5 and the stellaris drivers for debugging.  
The ARM compiler version can be downloaded at https://developer.arm.com/downloads/view/ACOMP5.  
If using version 5.29 or higher of MDK, Stellaris debugger needs an addon to work which can be downloaded at https://developer.arm.com/documentation/ka002280/latest.  
