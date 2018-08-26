
#include "target.h"   // use delay_us()

#if  (!WIN32)

#include "s3c6410_addr.h"


#define rGPKCON0        (*(volatile unsigned *)(0x7F008800))
#define rGPKCON1        (*(volatile unsigned *)(0x7F008804))
#define rGPKDAT         (*(volatile unsigned *)(0x7F008808))
#define rGPKPUD         (*(volatile unsigned *)(0x7F00880C))
/*
static void _port_init(void) {
    rGPKCON0 = (rGPKCON0 & ~(0xffffU<<16))|(0x1111U<<16);
    rGPKPUD  = (rGPKPUD  & ~(0xffU << 8))|(0x00U<<8);
}
*/
void bsp_uart_init(void) {
	//_port_init();

    // UART I/O port initialize (RXD0 : GPA0, TXD0: GPA1)
    rGPACON = (rGPACON & ~(0xff<<0)) | (0x22<<0);    // GPA0->RXD0, GPA1->TXD0
    rGPAPUD = (rGPAPUD & ~(0xf<<0)) | (0x1<<0);        // RXD0: Pull-down, TXD0: pull up/down disable
	
    // Initialize UART Ch0
    rULCON0 = (0<<6)|(0<<3)|(0<<2)|(3<<0);                    // Normal Mode, No Parity, 1 Stop Bit, 8 Bit Data
    rUCON0 = (0<<10)|(1<<9)|(1<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(1<<2)|(1<<0);    // PCLK divide, Polling Mode
    rUFCON0 = (0<<6)|(0<<4)|(0<<2)|(0<<1)|(0<<0);            // Disable FIFO
    rUMCON0 = (0<<5)|(0<<4)|(0<<0);                        // Disable Auto Flow Control
	
    rUBRDIV0 = 35;                                    // Baud rate
    rUDIVSLOT0 = 0x80;//aSlotTable[DivSlot];
}

void bsp_uart_sendbyte(int data) {
    while(!(rUTRSTAT0 & 0x2));   //Wait until THR is empty.
    delay_us(5);
    WrUTXH0(data);
}

void bsp_uart_sendstring(char *pt) {
    while(*pt)
		bsp_uart_sendbyte(*pt++);
}

void bsp_uart_print(char *pt) {
	bsp_uart_sendstring(pt);
}

#else

void bsp_uart_init(void) {}
void bsp_uart_sendbyte(int data) {}
void bsp_uart_sendstring(char *pt) {}
void bsp_uart_print(char *pt) {}



#endif  /*!WIN32*/

