#include "config.h"
#include "lpc3250.h"
#if U5_INT_ENABLE
#include "lpc32xx_intc_driver.h"
#endif
#include "serial.h"
/***********************************************************************
 * Function: uart5_int_handler 
 * Purpose:串口5的接收中断处理函数
 * Processing:
 *     查看串口5中断状态寄存器，查看是触发了哪些中断。接收到新数据，则将数据写入接收buffer,
 *     这个buffer暂时为64B。
 * Parameters: None
 * Outputs: Rsv_N接收的数据大小，Rsv_buffer接收数据数组
 **********************************************************************/
#if U5_INT_ENABLE
void uart5_int_handler(void)
{
	//(*(volatile unsigned*)(0x40028004))=0x100;
	int i=(int)(U5IIR&0xf);
	switch(i)
	{
		case 0x1:
			break;
		case 0x4:
		case 0xc:
			Rsv_N=(int)U5RXLEV;
		
			for(i=0;i<Rsv_N && i<64;i++)
			{
				Rsv_buffer[i]=(unsigned char)U5RBR;
			}
			//Rsv_buffer[i]=(unsigned char)(Rsv_N+0X30);
			break;
		default:
			break;
	}
}
#endif
/***********************************************************************
 * Function: u5_init 
 * Purpose:串口的初始化函数
 * Processing:
 *     设置波特率，baud rate=Source clock*x/y*(1/(16*(256*UnDLM+UnDLL)))
 * 	   设置中断
 **********************************************************************/
int u5_init()
{
	//bandrate
	U5LCR=0x83;
	U5DLM=0;
	U5DLL=1;
	//enable rbr thr ier 8bit n 1 no break trasmmit
	U5LCR=0x3;
	U5CLK=(134<<0)|(19<<8);//phriph_clock,x=19,y=134
	//
	//注册中断处理函数
#if U5_INT_ENABLE
	int_install_irq_handler(IRQ_UART_IIR5,uart5_int_handler);
	//使能中断，使能fifo，设置触发深度16，使能RDA中断
	U5FCR=0x3f;
	U5IER=0x1;
#endif
	return 0;
}
/***********************************************************************
 * Function: u5_sendbuf 
 * Purpose:串口5的发送函数
 * Processing:
 *     发送数据
 * Parameters: count 数据大小，sendbuffer数据数组
 **********************************************************************/

void u5_sendbuf(int count,unsigned char* sendbuffer )
{
	int i=0;
	for(i=0;i<count;i++)
	{
		U5THR=sendbuffer[i];
	}
}
