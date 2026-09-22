#include<LPC21xx.h>
#include "delay.h"

#define D 1<<16          // DS18B20 data pin connected to P0.16
#define R (IOPIN0&(1<<16)) // Read the current state of P0.16
/* Reset the DS18B20 and check whether it is present */
unsigned char ResetDS18b20(void)
{
    unsigned int presence;
    // Configure data pin as output
    IODIR0 |= D;
    // Keep data line HIGH
    IOPIN0 |= D;
    // Small delay
    delay_us(1);
    // Pull data line LOW to send reset pulse
    IOPIN0 &= ~(D);
    // Hold reset pulse
    delay_us(478);
    // Release data line
    IOPIN0 |= D;
    // Wait for sensor response
    delay_us(54);
    // Read presence pulse from sensor
    presence = IOPIN0;
    // Wait until reset sequence completes
    delay_us(423);
    // If line is HIGH, sensor is not detected
    if(presence & R)
        return 1;
    else
        return 0;
}

/* Read one bit from DS18B20 */
unsigned char ReadBit(void)
{
    unsigned int B;

    // Pull data line LOW to start read slot
    IOPIN0 &= ~(D);
    delay_us(1);
    // Release data line
    IOPIN0 |= D;
    // Configure pin as input
    IODIR0 &= ~(D);
    // Wait before reading
    delay_us(10);
    // Read bit from data line
    B = IOPIN0;
    // Configure pin back as output
    IODIR0 |= D;
    // Return received bit
    if(B & R)
        return 1;
    else
        return 0;
}

/* Write one bit to DS18B20 */
void WriteBit(unsigned char Dbit)
{
    // Pull data line LOW
    IOPIN0 &= ~(D);
    delay_us(1);
    // If bit is 1, release line
    if(Dbit)
        IOPIN0 |= D;
    // Complete write time slot
    delay_us(58);
    // Release data line
    IOPIN0 |= D;
    delay_us(1);
}

/* Read one byte from DS18B20 */
unsigned char ReadByte(void)
{
    unsigned char i;
    unsigned char Din = 0;
    // Read 8 bits
    for(i=0;i<8;i++)
    {
        // Store each received bit
        Din |= ReadBit() ? (0x01<<i) : Din;
        delay_us(45);
    }
    // Return received byte
    return Din;
}

/* Write one byte to DS18B20 */
void WriteByte(unsigned char Dout)
{
    unsigned char i;
    // Send 8 bits one by one
    for(i=0;i<8;i++)
    {
        // Send least significant bit first
        WriteBit(Dout & 0x01);
        // Shift next bit to LSB position
        Dout = Dout >> 1;
        delay_us(1);
    }

    // Wait after sending one byte
    delay_us(98);
}

/* Read temperature from DS18B20 */
int ReadTemp(void)
{
    unsigned char n, buff[2];
    int temp;
    // Reset the sensor
    ResetDS18b20();
    // Skip ROM command
    WriteByte(0xCC);
    // Start temperature conversion
    WriteByte(0x44);
    // Wait until conversion is completed
    while(ReadByte() == 0xFF);
    // Reset sensor again
    ResetDS18b20();
    // Skip ROM command
    WriteByte(0xCC);
    // Read scratchpad command
    WriteByte(0xBE);
    // Read first two bytes of temperature data
    for(n=0;n<2;n++)
    {
        buff[n] = ReadByte();
    }
    // Store MSB
    temp = buff[1];
    // Shift MSB to higher byte
    temp = temp << 8;
    // Combine with LSB
    temp = temp | buff[0];
    // Return 16-bit temperature value
    return temp;
}
