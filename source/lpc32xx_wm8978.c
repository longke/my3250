#include "lpc32xx_i2c.h"
#include "serial.h"
//启动wm8978，打通wm8978内播放通路的命令
const unsigned  char wm8978initdata[][2]=
{
	{0x8,0x90},
	{0xc,0x00},
	{0x8,0x90},
	{0xe,0x00},
	{0x2,0x0d},
	{0x6,0x03},
	{0x6,0x0f},
	{0x6,0x6f},
	{0x2,0x0d},
	{0x14,0x0},
	{0x14,0x40}
};

int wm8978_i2c(unsigned char addr,unsigned int data)
{
	unsigned char sendbuf[2];
	sendbuf[0]=addr;
	sendbuf[1]=data;
	return I2C_WriteNByte(0x34,0,0,2,sendbuf);
	
}
int wm8978_automute()
{
	if(wm8978_i2c(wm8978initdata[10][0],wm8978initdata[10][1]))
		return 1;
	return 0;
}

int wm8978_init()
{
	int i=0;
	while(i<10)
	{
		if(wm8978_i2c(wm8978initdata[i][0],wm8978initdata[i][1]))
			return 1;
		i++;
	}
	return 0;
}

