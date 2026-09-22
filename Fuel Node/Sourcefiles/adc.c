#include <lpc21xx.h>
#include "types.h"
#include "delay.h"

#define FOSC 12000000            // Oscillator frequency
#define CCLK (FOSC*5)       // CPU clock frequency
#define PCLK (CCLK/4)          // Peripheral clock frequency
#define ADCCLK 3000000             // ADC clock frequency
#define CLKDIV ((PCLK/ADCCLK)-1)      // ADC clock divider value
// ADCR Register bit positions
#define CLKDIV_BITS 8    // Clock divider starts from bit 8
#define PDN_BIT 21         // Power Down bit
#define ADC_CONV_START_BIT 24  // Start conversion bit
// ADDR Register bit positions
#define DIGITAL_DATA_BITS 6    // ADC result starts from bit 6
#define DONE_BIT 31     // Conversion complete bit
// ADC channel pin selections
#define AIN0_PIN_0_27 0x00400000
#define AIN1_PIN_0_28 0x01000000
#define AIN2_PIN_0_29 0x04000000
#define AIN3_PIN_0_30 0x10000000
// ADC channel numbers
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3
// Configure the required pin function
void cfgportpinfunc(u32 portNo, u32 pinNo, u32 pinFunc)
{
    // Check for Port 0
    if(portNo==0)
    {
        // Configure pins P0.0 to P0.15
        if(pinNo<=15)
        {
            PINSEL0=((PINSEL0&~(3<<(pinNo*2)))|
                     (pinFunc<<(pinNo*2)));
        }
        // Configure pins P0.16 to P0.31
        else if((pinNo>=16)&&(pinNo<=31))
        {
            PINSEL1=((PINSEL1&~(3<<((pinNo-16)*2)))|
                     (pinFunc<<((pinNo-16)*2)));
        }
    }
}
// ADC pin selection table
u32 adcChSel[4]=
{
    AIN0_PIN_0_27,
    AIN1_PIN_0_28,
    AIN2_PIN_0_29,
    AIN3_PIN_0_30
};
// Initialize ADC
void initadc(u32 chNo)
{
    // Configure selected pin as ADC pin
    PINSEL1 &= ~(adcChSel[chNo]);
    PINSEL1 |= adcChSel[chNo];
    // Power ON ADC and set ADC clock
    ADCR |= (1<<PDN_BIT) | (CLKDIV<<CLKDIV_BITS);
}
// Read ADC value
void Read_ADC(u32 chNo,f32 *eAR,u32 *adcDVal)
{
    // Clear previous channel selection
    ADCR &= 0xFFFFFF00;
    // Select ADC channel and start conversion
    ADCR |= ((1<<ADC_CONV_START_BIT) | (1<<chNo));
    // Small delay for conversion
    delay_us(3);
    // Wait until conversion is completed
    while(((ADDR>>DONE_BIT)&1)==0);
    // Stop ADC conversion
    ADCR &= ~(1<<ADC_CONV_START_BIT);
    // Read 10-bit digital ADC value
    *adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);
    // Convert digital value into voltage
    *eAR=*adcDVal*(3.3/1023);
}
// Read temperature from LM35
f32 read_lm35()
{
    u32 adcDVal;
    f32 eAR,tDeg;
    // Read ADC value from Channel 1
    Read_ADC(CH1,&eAR,&adcDVal);
    // Convert voltage into temperature
    tDeg=eAR*100;
    return tDeg;
}
// Read temperature using differential inputs
f32 Read_LM35_NP()
{
    u32 adcDVal1,adcDVal2;
    f32 eAR1,eAR2,tDeg;
    // Read Channel 0
    Read_ADC(CH0,&eAR1,&adcDVal1);
    // Read Channel 1
    Read_ADC(CH1,&eAR2,&adcDVal2);
    // Calculate temperature difference
    tDeg=(eAR1-eAR2)*100;
    return tDeg;
}
