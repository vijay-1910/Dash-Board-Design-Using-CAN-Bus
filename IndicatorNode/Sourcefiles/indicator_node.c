#include<LPC21xx.h>
#include "delay.h"
#include "can.h"
#include "types.h"

#define OFF 0     // Indicator OFF state
#define LEFT 1              // Left indicator state
#define RIGHT 2        // Right indicator state
#define LED_START 23   // First LED is connected to P1.23
#define LED_MASK (0xFF << LED_START) // Mask for 8 LEDs (P1.23 to P1.30)
CANF rxF;              // CAN frame for received data
volatile u8 indicator = OFF;   // Stores current indicator status
volatile u8 pos = 0;        // Stores current LED position
/* Function Prototypes */
void blink_left_step(void);
void blink_right_step(void);
int main(void)
{
    // Initialize CAN controller
    Init_CAN1();
    // Configure LED pins as output
    IODIR1 |= LED_MASK;
    // Turn OFF all LEDs
    IOSET1 = LED_MASK;
    while (1)
    {
        // Check if a CAN message is received
        if (C1GSR & (1 << 0))
        {
            // Read received CAN frame
            CAN1_Rx(&rxF);
            // Release receive buffer
            C1CMR = (1 << 2);
            // Check message ID
            if (rxF.ID == 0x11)
            {
                // Left indicator command
                if (rxF.Data1 == 'L')
                {
                    indicator = LEFT;
                    pos = 0;
                }
                // Right indicator command
                else if (rxF.Data1 == 'R')
                {
                    indicator = RIGHT;
                    pos = 7;
                }
                // Indicator OFF command
                else if (rxF.Data1 == 'O')
                {
                    indicator = OFF;
                    pos = 0;
                    // Turn OFF all LEDs
                    IOSET1 = LED_MASK;
                }
            }
        }
        // Perform left indicator action
        if (indicator == LEFT)
        {
            blink_left_step();
        }
        // Perform right indicator action
        else if (indicator == RIGHT)
        {
            blink_right_step();
        }
        // Keep all LEDs OFF
        else
        {
            IOSET1 = LED_MASK;
        }
        // Delay between LED movements
        delay_ms(50);
    }
}
/* Move LED from right to left */
void blink_right_step(void)
{
    // Turn OFF all LEDs
    IOSET1 = LED_MASK;
    // Turn ON current LED
    IOCLR1 = (1 << (LED_START + pos));
    // Move to next LED
    pos++;
    // Restart from first LED after last LED
    if (pos >= 8)
        pos = 0;
}
/* Move LED from left to right */
void blink_left_step(void)
{
    // Turn OFF all LEDs
    IOSET1 = LED_MASK;
    // Move to previous LED
    if (pos == 0)
        pos = 7;
    else
        pos--;
    // Turn ON selected LED
    IOCLR1 = (1 << (LED_START + pos));
}
