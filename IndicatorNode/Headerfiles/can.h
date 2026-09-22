#include "types.h"
/* Structure to store a CAN message */
typedef struct CAN_Frame
{
    u32 ID;          // CAN Message Identifier
    struct BitField
    {
        u32 RTR : 1; // Remote Transmission Request bit
        u32 DLC : 4; // Data Length Code (Number of data bytes)
    }BFV;
    u32 Data1,Data2; // CAN data bytes
    //u8 Data[8];    // Can also be used to store 8 individual data bytes
}CANF;
/* Function to initialize CAN controller */
void Init_CAN1(void);
/* Function to transmit a CAN frame */
void CAN1_Tx(CANF txFrame);
/* Function to receive a CAN frame */
void CAN1_Rx(CANF *rxFrame);
