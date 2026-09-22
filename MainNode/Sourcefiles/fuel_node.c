#include <LPC21xx.h>
#include "adc.h"
#include "delay.h"
#include "types.h"
#include "can.h"
#include "lcd.h"

CANF txF;          // CAN frame for transmission
f32 eAR;           // Stores ADC voltage value
u32 adcDVal;       // Stores ADC digital value

int main(void)
{
    u32 volt_mv;   // Stores voltage to be sent through CAN
    // Initialize LCD
    initlcd();
    // Initialize CAN controller
    Init_CAN1();
    // Initialize ADC Channel 1
    initadc(1);
    // Set CAN Message ID
    txF.ID = 0x301;
    // Configure as Data Frame
    txF.BFV.RTR = 0;
    // Set Data Length Code to 4 bytes
    txF.BFV.DLC = 4;
    while(1)
    {
        // Clear LCD display
        cmdlcd(0x01);
        // Read ADC voltage and digital value
        Read_ADC(1, &eAR, &adcDVal);
        // Convert voltage into required value
        volt_mv = (eAR * 100);
        // Store voltage in CAN data field
        txF.Data1 = volt_mv;
        // Second data field is not used
        txF.Data2 = 0;
        // Transmit CAN message
        CAN1_Tx(txF);
        // Wait before sending next value
        delay_ms(500);
    }
}
