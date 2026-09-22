void delay_us(unsigned int tdly)
{
    // Convert microseconds into loop count
    tdly *= 12;
    // Wait until loop completes
    while(tdly--);
}
void delay_ms(unsigned int tdly)
{
    // Convert milliseconds into loop count
    tdly *= 12000;
    // Wait until loop completes
    while(tdly--);
}
void delay_s(unsigned int tdly)
{
    // Convert seconds into loop count
    tdly *= 12000000;
    // Wait until loop completes
    while(tdly--);
}
