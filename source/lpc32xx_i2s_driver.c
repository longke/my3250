#include "lpc32xx_i2s.h"
#include "lpc3250.h"


void i2s_init()
{
	P_MUX_CLR=(1<<2)|(1<<3)|(1<<4);
	P0_MUX_SET= 0x03;
	
	I2S_CTRL=(1<<1)|(1<<5);//|(1<<4);
	//使用irq transmit depth=4
	//I2S1->i2s_irq =0x2|(0x4<<16);
	//不使用irq 
	I2S1->i2s_irq =0x00;
	//传输波特率 p538
	I2S1->i2s_tx_rate=215|(47<<8);//testing
	//I2S1->i2s_tx_rate=237|(7<<8);//testing
	
	I2S1->i2s_dao &= ~0x03;
	I2S1->i2s_dao &= ~0x4;
	I2S1->i2s_dao &= ~(0x00007ec0);//清空采样周期设置位？
	I2S1->i2s_dao |= (0x01);//帧宽(16->0x01,8->0x00,32->0x11)
	I2S1->i2s_dao |= (0xf<<6);//设置采样周期为n个i2s_clk n是宽度的两倍，计算方法是n/2-1
	I2S1->i2s_dao |= 0x04;//单声道0x04,立体声0x00;
	I2S1->i2s_dao |= (0x01<<4)|(0x01<<3);//异步复位音频输出通道和FIFO 禁止访问FIFO，静音
	I2S1->i2s_dao &= ~((0x01<<5)|(0x1<<15));//主机模式 取消静音功能
	I2S1->i2s_dao &= ~((0x01<<4)|(0x01<<3));//使能发送fifo
}


int i2s_send(unsigned int * data,unsigned int length)
{
	//send a
	int i=0;
	int y=0xffffff;
	while(1)
	{
		if((I2S1->i2s_stat &(0xf0000)) <0x80000)
		{
			I2S1->i2s_tx_fifo= data[i];
			i=i+1;
			length=length-4;
		}
		else 
			while((I2S1->i2s_stat &(0xf0000))>=0x80000)
			{
				y--;
				if(y==0)
					return 1;
			}
		if(length<=0)
			return 0;
	}
	return 1;
}

