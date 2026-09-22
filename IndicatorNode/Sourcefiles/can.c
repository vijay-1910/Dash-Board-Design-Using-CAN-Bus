#include <LPC21xx.h>         
#include "types.h"            
#include "defines.h"         
#include "can_defines.h"      
#include "delay.h"           

/* Structure to store CAN Frame */
typedef struct CAN_Frame
{
    u32 ID;                   // CAN Message Identifier
    /* Bit field for CAN frame information */
    struct BitField
    {
        u32 RTR : 1;          // Remote Transmission Request bit
        u32 DLC : 4;          // Data Length Code (0 to 8 bytes)
    }BFV;

    u32 Data1,Data2;          // Data bytes (Maximum 8 bytes)
}CANF;

/* CAN1 Initialization */
void Init_CAN1(void)
{
    // Configure CAN1 TX and RX pins
    PINSEL1 |= 0x00040000;
    // Enter Reset Mode for configuration
    SETBIT(C1MOD,RM_BIT);
    // Enable Acceptance Filter
    CLRBIT(AFMR,AccOFF_BIT);
    // Bypass Acceptance Filter (accept all messages)
    SETBIT(AFMR,AccBP_BIT);
    // Set CAN Bit Timing (Baud Rate)
    C1BTR = BTR_LVAL;
    // Exit Reset Mode and start CAN
    CLRBIT(C1MOD,RM_BIT);
}

/* CAN Transmit Function */
void CAN1_Tx(CANF txFrame)
{
    // Wait until Transmit Buffer-1 becomes free
    while(READBIT(C1GSR,TBS1_BIT)==0);
    // Load Message Identifier
    C1TID1 = txFrame.ID;
    // Load RTR bit and DLC into Frame Information Register
    C1TFI1 = (txFrame.BFV.RTR<<RTR_BIT) |
             (txFrame.BFV.DLC<<DLC_BITS);
    // If it is a Data Frame
    if(txFrame.BFV.RTR != 1)
    {
        // Load first 4 bytes of data
        C1TDA1 = txFrame.Data1;
        // Load next 4 bytes of data
        C1TDB1 = txFrame.Data2;
    }
    // Request transmission using Buffer-1
    C1CMR |= (1<<STB1_BIT) | (1<<TR_BIT);
    // Wait until transmission is completed
    while(READBIT(C1GSR,TCS1_BIT)==0);
}
/* CAN Receive Function */
void CAN1_Rx(CANF *rxFrame)
{
    // Wait until a CAN message is received
    while(READBIT(C1GSR,RBS_BIT)==0);
    // Read Message Identifier
    rxFrame->ID = C1RID;
    // Read RTR bit
    rxFrame->BFV.RTR = (C1RFS>>RTR_BIT)&1;
    // Read Data Length Code
    rxFrame->BFV.DLC = (C1RFS>>DLC_BITS)&0x0F;
    // If received frame is a Data Frame
    if(rxFrame->BFV.RTR == 0)
    {
        // Read first 4 bytes
        rxFrame->Data1 = C1RDA;
        // Read next 4 bytes
        rxFrame->Data2 = C1RDB;
    }

    // Release Receive Buffer for next message
    SETBIT(C1CMR,RRB_BIT);
}
