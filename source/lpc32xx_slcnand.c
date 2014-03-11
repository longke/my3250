#include "lpc32xx_slcnand.h"
#include "lpc32xx_nand.h"
#include "lpc3250.h"
/****************************************************
 *Function: _setaddr
 *parameters:
 *blockaddr:which block;pageaddr:which page in the block;
 *offset:offset to the page 
 *
 * **************************************************/
int _setaddr(unsigned int blockaddr,unsigned int pageaddr,unsigned int offset)
{
	//5 cycles
	SLCNAND->slc_addr=(unsigned char) (offset);
	SLCNAND->slc_addr=(unsigned char)((offset>>8)&0xf);
	SLCNAND->slc_addr=(unsigned char)((pageaddr&0x3f)|((blockaddr<<6)&0xc0));	
	SLCNAND->slc_addr=(unsigned char) (blockaddr>>2)&0xff;
	SLCNAND->slc_addr=(unsigned char)(blockaddr>>10)&0x1;
	return 0;
}
/****************************************************
 *Function: _setblockaddr
 *parameters:
 *blockaddr block address only address A18 to A28 is valid while A12-A17 is ignored
 *so just send row address to it 
 * ************************************************/
int _setblockaddr(unsigned int blockaddr)
{
	SLCNAND->slc_addr=(unsigned char) (blockaddr<<6)&0x00c0;
	SLCNAND->slc_addr=(unsigned char) (blockaddr>>2)&0xff;
	SLCNAND->slc_addr=(unsigned char)(blockaddr>>10)&0x1;
}
/****************************************************
 *Function: slcnand_readbyte
 *parameters:
 *blockaddr:which block;pageaddr:which page in the block;
 *offset:offset to the page ,these three parameters tell  
 *the slc nand controller from what address we want get the data on the nand flash;the num is the count of data we want ,and the data is a pointer to the data array
 * **************************************************/
int slcnand_readbyte(unsigned int blockaddr,unsigned int pageaddr,unsigned int offset,unsigned int num,unsigned char* data)
{
	unsigned int i;
	while((SLCNAND->slc_stat&0x01)!=0x01);//wait ready
	SLCNAND->slc_cmd= CMD_READ;
	_setaddr(blockaddr,pageaddr,offset);
	SLCNAND->slc_cmd= CMD_READ_READY;//go
	while(SLCNAND->slc_stat&0x2!=0x2);
	for (i=0;i<num;)
	{
		if(SLCNAND->slc_stat&0x2==0x2)
		{
			data[i+i]=SLCNAND->slc_data;
			i++;		
		}
		else 
		{
			delay(0xf000);
		}
	}
	return 0;
}
/****************************************************
 *Function: slcnand_init
 *Purpose:nand init with on ecc no dma 
 * **************************************************/
void slcnand_init()
{
	FLASHCLK_CTRL=0x5;
	SLCNAND->slc_cfg=0x0;//no ecc no DMA
	SLCNAND->slc_tac=(15<<0)|(15<<4)|(15<<8)|(15<<12)|(15<<16)|(15<<20)|(15<<24)|(15<<28);
	//SLCNAND->slc_cfg=(1<<3);//ecc enable
}

/***********************************************************************
 * Function: slcnand_read_id 
 * Purpose:read the chip id
 * Parameters: put the id in the buff
 **********************************************************************/
 
int slcnand_read_id(unsigned char * buff)
{
	unsigned int i;
	while((SLCNAND->slc_stat&0x01)!=0x01);//wait for nand ready

	SLCNAND->slc_cmd=CMD_READ_ID;
	SLCNAND->slc_addr=0x00;
	while((SLCNAND->slc_stat&0x2)!=0x02);
	for (i=0;i<5;i++)
	{
		buff[i]=SLCNAND->slc_data;
	}
	return 0;
}
/***********************************************************************
 * Function: slcnand_program_page
 * Purpose: write nand 
 * Processing:
 *    
 * Parameters:
 *blockaddr:which block;pageaddr:which page in the block;
 *offset:offset to the page ,these three parameters tell  
 *the slc nand controller from what address we want write the data to the nand flash;
 *the num is the count of data we want to send ,and the data is a pointer to the data array
 **********************************************************************/
int slcnand_program_page(unsigned int blockaddr,unsigned int pageaddr,unsigned int offset,unsigned int num,unsigned char *data)
{
	unsigned int i;
	if(blockaddr>=2048)
		return 1;
	if(num>=2048)
		return 1;
	while((SLCNAND->slc_stat&0x1)!=0x1);//wait ready

	SLCNAND->slc_cmd=CMD_PAGE_PROGRAM;
	_setaddr(blockaddr,pageaddr,offset);
	for(i=0;i<num;i++)
	{
		SLCNAND->slc_data=data[i];
	}
	SLCNAND->slc_cmd=CMD_PAGEPROG;
	SLCNAND->slc_cmd=CMD_STATUS;
	while((SLCNAND->slc_stat&0x1)==0x1);
	return 0;
}
