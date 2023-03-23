# PlayX
# This project is for the 22-23 Senior Design Team 02-PlayXtension at the University Of Kentucky
# The source code files is PA6.uvprojx which is located under the two folders named PA6-2022 Master v1.0 & PA6-2022 Slave v1.0. The old files are the original PA6-2022 Master and PA6-2022 Slave.
# This project makes use of two Tiva TM4C123GXL boards and two HC-05 Bluetooth modules.
# The Master source code is intended to be flashed on a Tiva TM4C123GXL board connected to a HC-05 Bluetooth Module that is in master mode.
# The Slave source code is for the HC-05 Bluetooth module that is in slave mode. 
# HC-05 Bluetooth Module can be in Master and/or Slave mode using AT commands. A pdf of AT commands is provided in the file HC-05_ATCommandSet.pdf. The AT commands were implemented using an Arduino IDE and Arduino UNO because of the convienence, but they can also be implemeneted inside Keil and using a serial terminal like PuTTy.
# The code was compiled using MDK 5.38,version 5.06 update 7 (build 960) of keil uvision 5 and the stellaris drivers for debugging.
# The ARM compiler version can be downloaded at https://developer.arm.com/downloads/view/ACOMP5.
# If using version 5.29 or higher of MDK, Stellaris debugger needs an addon to work which can be downloaded at https://developer.arm.com/documentation/ka002280/latest.
