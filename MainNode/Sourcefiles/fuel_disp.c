#include <LPC21xx.h>
#include "lcd.h"

void StoreCustCharFont(unsigned char p)
{
    unsigned char i;
    // fuel symbol for 0%
    unsigned char fuel0[8] =
    {
        0x0E,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x1F
    };
    // Select first CGRAM location
    cmdlcd(0x40);
    // Store fuel symbol in LCD CGRAM
    for(i=0;i<8;i++)
        charlcd(fuel0[i]);
}

void StoreCustCharFont1(unsigned char p)
{
    unsigned char i;
    // fuel symbol for 25%
    unsigned char fuel25[8] =
    {
        0x0E,
        0x11,
        0x11,
        0x11,
        0x11,
        0x1F,
        0x1F,
        0x1F
    };
    // Select second CGRAM location
    cmdlcd(0x48);
    // Store fuel symbol in LCD CGRAM
    for(i=0;i<8;i++)
        charlcd(batt25[i]);
}

void StoreCustCharFont2(unsigned char p)
{
    unsigned char i;
    // Battery symbol for 50%
    unsigned char fuel50[8] =
    {
        0x0E,
        0x11,
        0x11,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F
    };
    // Select third CGRAM location
    cmdlcd(0x50);
    // Store fuel symbol in LCD CGRAM
    for(i=0;i<8;i++)
        charlcd(batt50[i]);
}

void StoreCustCharFont3(unsigned char p)
{
    unsigned char i;
    // fuel symbol for 75%
    unsigned char fuel75[8] =
    {
        0x0E,
        0x11,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F
    };
    // Select fourth CGRAM location
    cmdlcd(0x58);
    // Store fuel symbol in LCD CGRAM
    for(i=0;i<8;i++)
        charlcd(batt75[i]);
}

void StoreCustCharFont4(unsigned char p)
{
    unsigned char i;
    // fuel symbol for 100%
    unsigned char batt100[8] =
    {
        0x0E,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F,
        0x1F
    };
    // Select fifth CGRAM location
    cmdlcd(0x60);
    // Store fuel
 symbol in LCD CGRAM
    for(i=0;i<8;i++)
        charlcd(batt100[i]);
}
