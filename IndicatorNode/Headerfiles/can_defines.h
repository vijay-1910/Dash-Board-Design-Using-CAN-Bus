// CAN1 TX pin uses the default alternate function
#define TD1_PIN
// Configure P0.25 as CAN1 RX pin
#define RD1_PIN_0_25
// Peripheral Clock Frequency
#define PCLK 15000000      // 15 MHz
// Required CAN baud rate
#define BIT_RATE 125000    // 125 kbps
// Number of time quanta in one CAN bit
#define QUANTA 20
// Baud Rate Prescaler value
#define BRP (PCLK/(BIT_RATE*QUANTA))
// Sample point at 70% of the bit time
#define SAMPLE_POINT (0.7 * QUANTA)
// Time Segment 1
#define TSEG1 ((u32)SAMPLE_POINT-1)
// Time Segment 2
#define TSEG2 (QUANTA-(1+TSEG1))
// Synchronization Jump Width
#define SJW ((TSEG2>=5)?4:(TSEG2-1))
// CAN Bit Timing Register value
#define SAM 0      // Single sampling mode
// Calculate complete Bit Timing Register value
#define BTR_LVAL (SAM<<23 | \
                  ((TSEG2-1)<<20) | \
                  ((TSEG1-1)<<16) | \
                  ((SJW-1)<<14) | \
                  (BRP-1))
// Command Register bit positions
#define TR_BIT 0       // Transmission Request bit
#define RRB_BIT 2      // Release Receive Buffer bit
#define STB1_BIT 5     // Select Transmit Buffer 1
// Global Status Register bit positions
#define RBS_BIT 0      // Receive Buffer Status
#define TBS1_BIT 2     // Transmit Buffer 1 Status
#define TCS1_BIT 3     // Transmission Complete Status
// Frame Information Register bit positions
#define RTR_BIT 30     // Remote Transmission Request bit
#define DLC_BITS 16    // Data Length Code bits

// Mode Register bit position
#define RM_BIT 0       // Reset Mode bit

// Acceptance Filter Mode Register bit positions
#define AccOFF_BIT 0   // Acceptance Filter OFF bit
#define AccBP_BIT 1    // Acceptance Filter Bypass bit
