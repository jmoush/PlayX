import serial

ser = serial.Serial('COM6', 9600, timeout=None)

while True:
    s = ser.read()
    s = int.from_bytes(s, byteorder='little') - 48
    print(f'You pressed "SW{s}" of TIVA')
    value = input("Please enter R or r: ")
    print(f'You entered "{value}"')
    ser.write(value.encode())
