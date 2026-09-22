#ifndef _DS18B20_H_
#define _DS18B20_H_
// Prevents the header file from being included more than once
// Function to reset the DS18B20 sensor
unsigned char ResetDS1820(void);
// Function to read one bit from the sensor
unsigned char ReadBit(void);
// Function to write one bit to the sensor
void WriteBit(unsigned char);
// Function to read one byte from the sensor
unsigned char ReadByte(void);
// Function to write one byte to the sensor
void WriteByte(unsigned char);
// Function to read temperature from the sensor
int ReadTemp(void);
#endif
