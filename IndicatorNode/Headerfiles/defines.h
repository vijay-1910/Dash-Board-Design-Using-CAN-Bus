// Set the specified bit to 1
#define SETBIT(WORD,BITPOS) (WORD|=(1<<BITPOS))
// Clear the specified bit to 0
#define CLRBIT(WORD,BITPOS) (WORD&=~(1<<BITPOS))
// Toggle the specified bit
#define CPLBIT(WORD,BITPOS) (WORD^=(1<<BITPOS))
// Write 0 or 1 to the specified bit
#define WRITEBIT(WORD,BITPOS,BIT) (BIT?SETBIT(WORD,BITPOS):CLRBIT(WORD,BITPOS))
// Read the value of the specified bit
#define READBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)
// Copy one bit from one position to another
#define READWRITEBIT(WORD,WBIT,RBIT) (WORD=((WORD&~(1<<WBIT))|(((WORD>>RBIT)&1)<<WBIT)))
// Write 4 bits (nibble) into the specified position
#define WRITENIBBLE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x0000000F<<BITPOS))|((BYTE&0X0F)<<BITPOS))
// Read 4 bits (nibble) from the specified position
#define READNIBBLE(WORD,BITPOS) ((WORD>>BITPOS)&0x0000000F)
// Write one byte (8 bits) into the specified position
#define WRITEBYTE(WORD,BITPOS,BYTE) (WORD=(WORD&~(0x000000FF<<BITPOS))|(BYTE<<BITPOS))
// Read one byte (8 bits) from the specified position
#define READBYTE(WORD,BITPOS) ((WORD>>BITPOS)&0x000000FF)
