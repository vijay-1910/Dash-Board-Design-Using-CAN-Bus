#include <LPC21xx.h>         
#include "delay.h"            
#include "can.h"              
#include "types.h"           
#include "lcd.h"              
#include "pin_connect_block.h"
#include "ds18b20.h"          
#include "fuel.h"     


/* Indicator states */
#define OFF   0
#define LEFT  1
#define RIGHT 2
/* Convert ADC value into battery percentage */
u32 convert(u32 x)
{
    // If value is less than minimum make it 0
    if(x<1)
    {
        x=0;
    }
    // Limit maximum ADC value
    if(x>330)
    {
        x=330;
    }
    // Convert ADC value to percentage
    return (x*100)/330;
}

/* Global variables */
volatile u32 percent=0;       // Stores Fuel percentage
f32 voltage;                  // Voltage value (not used)
u8 battery_percent,i;         // Battery variables
u32 level=0;                  // Battery level icon

/* Current indicator status */
volatile u8 indicator_status=OFF;

/* CAN transmit and receive frame */
CANF txF;
CANF rxF;
/* Custom character for left arrow */
u8 left_arrow[8]={0x03,0x07,0x0F,0x1F,0x0F,0x07,0x03,0x01};
/* Custom character for right arrow */
u8 right_arrow[8]={0x18,0x1C,0x1E,0x1F,0x1E,0x1C,0x18,0x10};
/* Function declarations */
void LoadCustomChars(void);
void sendsignal(void);
void eint0_isr(void)__irq;
void eint1_isr(void)__irq;

int temp;
u8 tp,tpd;

int main(void)
{
    // Initialize CAN controller
    Init_CAN1();
    // Initialize LCD
    initlcd();
    // First line
    cmdlcd(0x80);
    strlcd(" <<< DASH BOARD >>> ");
    // Create degree symbol
    //temp_symbol();
    // Second line
    cmdlcd(0xC0);
    strlcd("Indicator ");
    // Store arrow symbols in LCD
    LoadCustomChars();
    // Store fuel symbols (0%,25%,50%,75%,100%)
    StoreCustCharFont(0);
    StoreCustCharFont1(25);
    StoreCustCharFont2(50);
    StoreCustCharFont3(75);
    StoreCustCharFont4(100);
    // Display left arrow
    cmdlcd(0xC0+13);
    charlcd(5);
    // Display right arrow
    cmdlcd(0xC0+15);
    charlcd(6);
    /* Configure External Interrupt 0 */
    // Configure P0.1 as EINT0
    cfgportpinfunc(0,1,3);
    // Configure P0.3 as EINT1
    cfgportpinfunc(0,3,3);
    // Select edge triggered interrupt
    EXTMODE|=(1<<0)|(1<<1);
    // Select falling edge
    EXTPOLAR&=~((1<<0)|(1<<1));
    // Clear pending interrupts
    EXTINT=(1<<0)|(1<<1);
    // Assign ISR to EINT0
    VICVectCntl0=(1<<5)|14;
    VICVectAddr0=(u32)eint0_isr;
    // Assign ISR to EINT1
    VICVectCntl1=(1<<5)|15;
    VICVectAddr1=(u32)eint1_isr;
    // Enable both interrupts
    VICIntEnable=(1<<14)|(1<<15);
    while(1)
    {
        /* LEFT indicator blinking */
        if(indicator_status==LEFT)
        {
            // Show left arrow
            cmdlcd(0xC0+13);
            charlcd(5);
            // Blink delay
            delay_ms(300);
            // Hide left arrow
            cmdlcd(0xC0+13);
            charlcd(' ');
            // Keep right arrow visible
            cmdlcd(0xC0+15);
            charlcd(6);
        }
        /* RIGHT indicator blinking */
        else if(indicator_status==RIGHT)
        {
            // Keep left arrow visible
            cmdlcd(0xC0+13);
            charlcd(5);

            // Show right arrow
            cmdlcd(0xC0+15);
            charlcd(6);

            delay_ms(300);

            // Hide right arrow
            cmdlcd(0xC0+15);
            charlcd(' ');
        }

        /* Indicator OFF */

        else
        {
            // Display both arrows continuously
            cmdlcd(0xC0+13);
            charlcd(5);
            cmdlcd(0xC0+15);
            charlcd(6);
        }
        delay_ms(100);
        // Read temperature from DS18B20
        temp=ReadTemp();
        // Integer part
        tp=temp>>4;
        // Decimal part (.0 or .5)
        tpd=(temp&0x08)?'5':'0';
        // Display temperature
        cmdlcd(0xD4);
        strlcd("Temp ");       // Degree symbol
        strlcd(" : ");
        u32lcd(tp);
        charlcd('.');
        charlcd(tpd);
        charlcd(223);
        strlcd("C ");
        // Check if CAN message is received
        if(C1GSR&(1<<0))
        {
            // Read received CAN frame
            CAN1_Rx(&rxF);
            // Check valid message
            if(rxF.ID)
            {
                // Convert ADC value to percentage
                percent=convert(rxF.Data1);
                // Display battery percentage
                cmdlcd(0x94);
                strlcd("FUEL: ");
                u32lcd(percent);
                strlcd("% ");
                // Select battery icon
                if(percent<=0)
                {
                    level=0;
                }
                else if(percent<=25)
                {
                    level=1;
                }
                else if(percent<=50)
                {
                    level=2;
                }
                else if(percent<=75)
                {
                    level=3;
                }
                else
                {
                    level=4;
                }
                // Display battery symbol
                cmdlcd(0x94+13);
                charlcd(level);
            }
        }
        delay_ms(200);
    }
}

/* EINT0 Interrupt Service Routine */
void eint0_isr(void)__irq
{
    // Toggle LEFT indicator
    indicator_status=(indicator_status==LEFT)?OFF:LEFT;
    // Send status through CAN
    sendsignal();
    // Clear interrupt flag
    EXTINT=(1<<0);
    // End of interrupt
    VICVectAddr=0;
}

/* EINT1 Interrupt Service Routine */
void eint1_isr(void)__irq
{
    // Toggle RIGHT indicator
    indicator_status=(indicator_status==RIGHT)?OFF:RIGHT;
    // Send status through CAN
    sendsignal();
    // Clear interrupt flag
    EXTINT=(1<<1);
    // End of interrupt
    VICVectAddr=0;
}

/* Send indicator status through CAN */
void sendsignal(void)
{
    // CAN Message ID
    txF.ID=0x11;
    // Data frame
    txF.BFV.RTR=0;
    // One byte data
    txF.BFV.DLC=1;
    // Send L,R or O
    txF.Data1=(indicator_status==LEFT)?'L':
              (indicator_status==RIGHT)?'R':'O';

    // Transmit CAN frame
    CAN1_Tx(txF);
}

/* Load arrow symbols into LCD CGRAM */
void LoadCustomChars(void)
{
    u8 i;

    // Store left arrow
    cmdlcd(0x68);
    for(i=0;i<8;i++)
        charlcd(left_arrow[i]);

    // Store right arrow
    cmdlcd(0x70);
    for(i=0;i<8;i++)
        charlcd(right_arrow[i]);
}
