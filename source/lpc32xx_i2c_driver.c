#include "lpc32xx_i2c.h"
#include "lpc32xx_intc.h"
volatile unsigned int I2C_sla;
volatile unsigned char I2C_Status; 		//状态
volatile unsigned char* I2C_recvbuf; 	//接收数组
volatile unsigned char* I2C_sendbuf; 	//发送数组
volatile unsigned int I2C_recvnum; 		//已接收的数据量
volatile unsigned int I2C_sendnum; 		//已发送的数据量
volatile unsigned int I2C_recvAllnum; 	//要接收的数据量
volatile unsigned int I2C_sendAllnum; 	//要发送的数据量
/***********************************************************************
 * Function: Wait_i2c_end 
 * Processing:
 *  wait the one i2c communication end or timeout
 * Parameters:
 *     dly   : time to delay
 * Returns:
 *     0 : communication end 
 *     1 : timeout
 **********************************************************************/
unsigned int static Wait_i2c_end(unsigned int dly)
{
	int i;
	if(I2C_Status==I2C_DONE)
		return 0;
	for (;dly>0;dly--)
		for(i=0;i<50000;i++)
		{
			if(I2C_Status==I2C_DONE)return 0;
		}
	return 1;
}
/***********************************************************************
 * Function: int_get_controller
 * Processing: i2c interrpt  handler 
 * Stat: testing  
 **********************************************************************/
void I2C_int_handler(void)
{
	unsigned int stat;
	
	//(*(volatile unsigned*)(0x40028004))=0x100;
	//while ((bsend<I2C_sendnum)
	while((I2C_recvAllnum-I2C_recvnum>0)
			&&((I2C1->i2c_stat&(1<<10))==0))//发送fifo未满,但还有数据需要接收
	{
		//(*(volatile unsigned*)(0x40028004))=0x100;
		if((I2C1->i2c_stat&(1<<9))==0)//recv fifo not empty
		{
			*I2C_recvbuf++ =I2C1->i2c_txrx;
			I2C_recvnum++;
			if(I2C_recvAllnum-I2C_recvnum==0)
				I2C1->i2c_txrx=0xff|(1<<9);
			else
				I2C1->i2c_txrx=0xff;
		}
	}
	while((I2C_sendAllnum-I2C_sendnum>0) &&
			(I2C1->i2c_stat&(1<<10))==0 &&
			(I2C1->i2c_stat&(1<<2))==0)//发送fifo未满且仍有数据等待发送
	{
		u5_sendbuf(1,I2C_sendbuf+I2C_sendnum);
		if(I2C_sendAllnum-I2C_sendnum==1)
		{
			(*(volatile unsigned*)(0x40028004))=0x100;
			I2C1->i2c_txrx=I2C_sendbuf[I2C_sendnum]|I2C_STOP_FLAG;
		}
		else
			I2C1->i2c_txrx=I2C_sendbuf[I2C_sendnum];
		I2C_sendnum++;
	}
	if(I2C_sendnum==I2C_sendAllnum)//数据已发完
	{
	//	(*(volatile unsigned*)(0x40028004))=0x100;
		I2C1->i2c_ctrl &= ~I2C_TFFIE;
	}
	if(I2C1->i2c_stat&(1)!=0)//已发送结束信号
	{
		I2C1->i2c_ctrl=0;
		I2C_Status=I2C_DONE;
	(*(volatile unsigned*)(0x40028004))=0x100;
	}


		
}
/***********************************************************************
 * Function: I2Cinit 
 * Purpose:I2C初始化函数
 * Processing:
 *     设置波特率
 * 	   设置中断
 **********************************************************************/
void I2Cinit(unsigned int i2c_clk)
{
	I2CCLK_CTRL=0x03;
	I2C1->i2c_ctrl= 1<<8;
	while ((I2C1->i2c_ctrl &(1<<8))!=0);
	switch(i2c_clk)
	{
		case I2C_CLK_100K:
			I2C1->i2c_clk_hi= 520;
			I2C1->i2c_clk_lo=520;
			break;
		case I2C_CLK_400K:
			I2C1->i2c_clk_hi=96;
			I2C1->i2c_clk_lo=166;
			break;
		default:
			break;
	}

	int_install_irq_handler(IRQ_I2C_1,I2C_int_handler);
	
}
/***********************************************************************
 * Function: I2C_WriteNByte 
 * Purpose:I2C写,发送函数
 * Processing:
 *    写
 * 	   设置中断
 * Parameters:
 * sla: i2c slave device address 
 * num:data count 
 * data:point to the data array that you want to send
 **********************************************************************/
unsigned int I2C_WriteNByte(unsigned int sla,unsigned int subaddr_type,unsigned int subaddr,unsigned int num ,unsigned char* data)
{
	unsigned int err=1;
	unsigned int time=0xffff;
	unsigned char se[2];
	se[0]='=';
	se[1]='!';
	I2C_sendnum=0;
	I2C_recvnum=0;
	I2C_recvAllnum=0;
	while (I2C1->i2c_stat & I2C_ACTIVE);
	I2C1->i2c_stat=0x3;
	I2C1->i2c_ctrl=(1<<8);
	while ((I2C1->i2c_ctrl&(1<<8)!=0));
	I2C_sendAllnum=num;
	I2C_sendbuf=data;
	if(I2C_sendnum==I2C_sendAllnum)
		u5_sendbuf(1,se);
	else
		u5_sendbuf(1,se+1);
	
	I2C_Status=I2C_BEGIN;
	I2C1->i2c_txrx=(sla&0xfe)|I2C_START_FLAG;
	I2C1->i2c_ctrl=(I2C_TFFIE|I2C_NAIE|I2C_AFIE|I2C_TDIE);
	err &=Wait_i2c_end(30);
	//while((I2C1->i2c_stat & I2C_NAI)!=0)
#if 0	
	while(I2C_Status==I2C_DONE)
	{
		time--;
		if(time<=0)
		{	
			err=1;
			break;
		}
	}
	if(I2C_Status==I2C_DONE)
	{
		err=3;
	}
#endif
	return err;
}

unsigned int I2C_probe(unsigned int sla,unsigned char subaddr_type,unsigned int subaddr,unsigned int num ,unsigned char* data)
{
	unsigned int err=0;
	unsigned int time=0xffff;
	while (I2C1->i2c_stat & I2C_ACTIVE);
	I2C1->i2c_stat=0x3;
	I2C1->i2c_ctrl=(1<<8);
	while ((I2C1->i2c_ctrl&(1<<8)!=0));
	
	I2C_Status=I2C_BEGIN;
	I2C1->i2c_ctrl=(I2C_TFFIE|I2C_NAIE|I2C_AFIE|I2C_TDIE);
	I2C1->i2c_txrx=(sla&0xfe)|I2C_START_FLAG|I2C_STOP_FLAG;

	err &=Wait_i2c_end(10);
	//while((I2C1->i2c_stat & I2C_NAI)!=0)
	while(I2C_Status==I2C_DONE)
	{
		time--;
		if(time<=0)
		{	
			err=1;
			break;
		}
	}
	if(I2C_Status==I2C_DONE)
	{
		err=3;
	}
	return err;
}



