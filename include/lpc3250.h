
/*************
 * clock
************/
#define I2CCLK_CTRL (*(volatile unsigned long *)(0x400040ac))
#define I2S_CTRL (*(volatile unsigned long *)(0x4000407c))
#define FLASHCLK_CTRL (*(volatile unsigned long *)(0x400040c8))

/****
 *mux
 ***/
#define P_MUX_CLR (*(volatile unsigned long *)(0x40028104))
#define P0_MUX_SET (*(volatile unsigned long *)(0x40028104))





/*
 *UART5
 */
#define UART5_BASE_ADDR 0x40090000
//UART Receiver Buffer Register read only get the top of Receiver buffer
#define     U5RBR                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x00))
//Transmitter Holding Register  write only write to the top of the Transmitter buffer
#define     U5THR                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x00))
// Divisor Latch LSB Register and Divisor Latch MSB Register the UnDLL and UnDLM registers together form a 16 bit divisor to divide UART clock in order to  produce the baud rate clock
#define     U5DLL                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x00))
#define     U5DLM                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x04))
//Interrupt Enable Register see the user manual p454 for more 
#define     U5IER                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x04))
//Interrupt Identification Register see the user manual p454 for more
#define     U5IIR                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x08))
//FIFO Control Register Bits in UnFCR allow enabling the FIFOs, resetting the FIFOs, and selecting the FIFO trigger levels
#define     U5FCR                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x08))
//Line Control Register  determines the format of the data character that is to be transmitted or received
#define     U5LCR                   (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x0C))
//Line Status Register 
#define     U5LSR 	                (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x14))
//FIFO Level Register 
#define     U5RXLEV                 (*(volatile unsigned long *)(UART5_BASE_ADDR + 0x1C))

#define     UART_CLK_BASE_ADDR	    0x40004000
#define     U5CLK                   (*(volatile unsigned long *)(UART_CLK_BASE_ADDR + 0xD8))

#define     UART_CTRL_BASE_ADDR	    0x40054000
#define     UART_CTRL               (*(volatile unsigned long *)(UART_CTRL_BASE_ADDR + 0x00))
#define     UART_CLKMODE            (*(volatile unsigned long *)(UART_CTRL_BASE_ADDR + 0x04))
#define     UART_LOOP               (*(volatile unsigned long *)(UART_CTRL_BASE_ADDR + 0x08))

/*
 * Interrupt Controller vic
 */
#define     MIC_BASE_ADDR	        0x40008000
//Enable Register for the Main Interrupt Controller 
#define     MIC_ER		            (*(volatile unsigned long *)(MIC_BASE_ADDR + 0x00))
//Raw Status Register for the Main Interrupt Controller read (status) and write(clear)
#define     MIC_RSR		            (*(volatile unsigned long *)(MIC_BASE_ADDR + 0x04))
//Status Register for the Main Interrupt Controller is pending?
#define     MIC_SR		            (*(volatile unsigned long *)(MIC_BASE_ADDR + 0x08))
//Main Interrupt Controller Activation Polarity Register 中断极性 0:下降沿falling 1：上升沿rising
#define     MIC_APR		            (*(volatile unsigned long *)(MIC_BASE_ADDR + 0x0C))	
//Main Interrupt Controller Activation Type Register 沿触发还是电平触发
#define     MIC_ATR		            (*(volatile unsigned long *)(MIC_BASE_ADDR + 0x10))
//Main Interrupt Controller Interrupt Type Register FIQ or IRQ
#define     MIC_ITR		            (*(volatile unsigned long *)(MIC_BASE_ADDR + 0x14))

#define     SIC1_BASE_ADDR	        0x4000C000
#define     SIC1_ER		            (*(volatile unsigned long *)(SIC1_BASE_ADDR + 0x00))
#define     SIC1_RSR	            (*(volatile unsigned long *)(SIC1_BASE_ADDR + 0x04))
#define     SIC1_SR		            (*(volatile unsigned long *)(SIC1_BASE_ADDR + 0x08))
#define     SIC1_APR	            (*(volatile unsigned long *)(SIC1_BASE_ADDR + 0x0C))
#define     SIC1_ATR	            (*(volatile unsigned long *)(SIC1_BASE_ADDR + 0x10))
#define     SIC1_ITR	            (*(volatile unsigned long *)(SIC1_BASE_ADDR + 0x14))

#define     SIC2_BASE_ADDR	        0x40010000
#define     SIC2_ER		            (*(volatile unsigned long *)(SIC2_BASE_ADDR + 0x00))
#define     SIC2_RSR	            (*(volatile unsigned long *)(SIC2_BASE_ADDR + 0x04))
#define     SIC2_SR		            (*(volatile unsigned long *)(SIC2_BASE_ADDR + 0x08))
#define     SIC2_APR	            (*(volatile unsigned long *)(SIC2_BASE_ADDR + 0x0C))
#define     SIC2_ATR	            (*(volatile unsigned long *)(SIC2_BASE_ADDR + 0x10))
#define     SIC2_ITR	            (*(volatile unsigned long *)(SIC2_BASE_ADDR + 0x14))

#define     SWI_BASE_ADDR	        0x40004000
//SoftwareInterrupt
#define     SW_INT		            (*(volatile unsigned long *)(SWI_BASE_ADDR + 0xA8))

