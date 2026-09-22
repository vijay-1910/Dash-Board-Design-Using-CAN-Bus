#include<LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "defines.h"

#define LCD_DAT 8    // LCD data pins start from P0.8
#define RS 17         // Register Select pin
#define RW 18         // Read/Write pin
#define EN 19         // Enable pin

void writelcd(char ch)
{
    // Select write operation
    WRITEBIT(IOCLR0,RW,1);
    // Send one byte to LCD data pins
    WRITEBYTE(IOPIN0,LCD_DAT,ch);
    // Generate enable pulse
    WRITEBIT(IOSET0,EN,1);
    WRITEBIT(IOCLR0,EN,1);
    // Wait for LCD to complete the operation
    delay_ms(2);
}

void cmdlcd(char cmd)
{
    // Select command register
    WRITEBIT(IOCLR0,RS,1);
    // Send command to LCD
    writelcd(cmd);
}
void initlcd(void)
{
    // Configure LCD data pins as output
    WRITEBYTE(IODIR0,LCD_DAT,0xFF);
    // Configure control pins as output
    WRITEBIT(IODIR0,RS,1);
    WRITEBIT(IODIR0,RW,1);
    WRITEBIT(IODIR0,EN,1);
    // Wait for LCD power-up
    delay_ms(15);
    // Initialize LCD
    cmdlcd(0x30);
    delay_ms(5);
    cmdlcd(0x30);
    delay_us(100);
    cmdlcd(0x30);

    // Select 8-bit mode, 2-line display
    cmdlcd(0x38);
    // Turn ON display, cursor OFF
    cmdlcd(0x0C);
    // Move cursor to next position automatically
    cmdlcd(0x06);
    // Clear LCD screen
    cmdlcd(0x01);
}

void charlcd(char dat)
{
    // Select data register
    WRITEBIT(IOSET0,RS,1);
    // Send one character to LCD
    writelcd(dat);
}
void strlcd(char *p)
{
    // Display characters until null character
    while(*p)
        charlcd(*p++);
}
void u32lcd(signed int n)
{
    char a[10],i=0;
    // Check for negative number
    if(n<0)
    {
        // Display minus sign
        charlcd('-');
        // Convert to positive
        n=-n;
    }
    // Extract digits one by one
    do
    {
        a[i++]=n%10+48;
        n=n/10;
    }while(n);
    // Display digits in correct order
    for(;i>0;i--)
        charlcd(a[i-1]);
}
void f32lcd(float f,char i)
{
    // Get integer part
    unsigned long int n=f;
    // Display integer part
    u32lcd(n);
    // Display decimal point
    charlcd('.');
    // Display digits after decimal point
    for(;i>0;i--)
    {
        f=f*10;
        n=f;
        charlcd(n%10+48);
    }
}
