
#ifndef  __I2CINT_H
#define  __I2CINT_H
#include "lpc3250.h"

#define I2C_CLK_100K 1
#define I2C_CLK_400K 4

#define I2C1_BASE 0x400A0000 /* I2C1 registers base*/
#define I2C2_BASE 0x400A8000 /* I2C1 registers base*/
typedef struct
{
	volatile unsigned int i2c_txrx; 	/*i2c tx/rx data fifo*/
	volatile unsigned int i2c_stat; 	//i2c status register 
	volatile unsigned int i2c_ctrl; 	//i2c control register
	volatile unsigned int i2c_clk_hi; 	//i2c clock divider high
	volatile unsigned int i2c_clk_lo; 	//i2c clock divider low
	volatile unsigned int i2c_adr; 		//i2c slave address
	volatile unsigned int i2c_rxfl; 	//i2c rx fifo level
	volatile unsigned int i2c_txfl; 	//i2c tx fifo level
	volatile unsigned int i2c_rxb; 		//i2c Receive number of bytes
	volatile unsigned int i2c_txb; 		//i2c Transmit number of bytes
	volatile unsigned int i2c_stxfl; 	//i2c slave Transmit fifo level
}I2C_REGS_T;
#define I2C1 ((I2C_REGS_T *)(I2C1_BASE))
#define I2C2 ((I2C_REGS_T *)(I2C2_BASE))

/**********************************************************************
* i2c_txrx register definitions
**********************************************************************/
#define I2C_START_FLAG    _BIT(8)                                       /* generate a START before      */
                                                                        /* this B                       */
#define I2C_STOP_FLAG     _BIT(9)                                       /* generate a STOP after this B */

/*********************************************************************************************************
* i2c_stat register definitions
*********************************************************************************************************/
#define I2C_TDI     _BIT(0)      /* Transaction Done Interrupt   */
#define I2C_AFI     _BIT(1)      /* Arbitration Failure Interrupt*/
#define I2C_NAI     _BIT(2)      /* No Acknowledge Interrupt     */
#define I2C_DRMI    _BIT(3)      /* Master Data Request Interrupt*/
#define I2C_DRSI    _BIT(4)      /* Slave Data Request Interrupt */
#define I2C_ACTIVE  _BIT(5)      /* Busy bus indicator           */
#define I2C_SCL     _BIT(6)      /* The current SCL signal value */
#define I2C_SDA     _BIT(7)      /* The current SDA signal value */
#define I2C_RFF     _BIT(8)      /* Receive FIFO Full            */
#define I2C_RFE     _BIT(9)      /* Receive FIFO Empty           */
#define I2C_TFF     _BIT(10)     /* Transmit FIFO Full           */
#define I2C_TFE     _BIT(11)     /* Transmit FIFO Empty          */
#define I2C_TFFS    _BIT(12)     /* Slave Transmit FIFO Full     */
#define I2C_TFES    _BIT(13)     /* Slave Transmit FIFO Empty    */

/*********************************************************************************************************
* i2c_ctrl register definitions
*********************************************************************************************************/
#define I2C_TDIE    _BIT(0)     /* Transaction Done Int Enable  */
#define I2C_AFIE    _BIT(1)     /* Arbitration Failure Int Ena  */
#define I2C_NAIE    _BIT(2)     /* No Acknowledge Int Enable    */
#define I2C_DRMIE   _BIT(3)     /* Master Data Request Int Ena  */
#define I2C_DRSIE   _BIT(4)     /* Slave Data Request Int Ena   */
#define I2C_RFFIE   _BIT(5)     /* Receive FIFO Full Int Ena    */
#define I2C_RFDAIE  _BIT(6)     /* Rcv Data Available Int Ena   */
#define I2C_TFFIE   _BIT(7)     /* Trnsmt FIFO Not Full Int Ena */
#define I2C_RESET   _BIT(8)     /* Soft Reset                   */
#define I2C_SEVEN   _BIT(9)     /* Seven-bit slave address      */
#define I2C_TFFSIE  _BIT(10)    /* Slave Trnsmt FIFO Not Full IE*/

/*********************************************************************************************************
* 执行结果
*********************************************************************************************************/
#define   I2C_BEGIN           0x01
#define   I2C_DONE               0x02
#define   I2C_NAK                  0x03
#define   I2C_ARF                0x04
#define   I2C_ERR               0xFF

/*********************************************************************************************************
* I2C操作码
*********************************************************************************************************/
#define   I2C_CMD_WR_EX_ADDR    0x01
#define   I2C_CMD_WR_DATA       0x02
#define   I2C_CMD_RD_DATA       0x03

#define    ONE_BYTE_SUBA    1
#define TWO_BYTE_SUBA    2
#define X_ADD_8_SUBA    3

extern void I2CInit(unsigned int i2c_clk);
extern unsigned int Wait_I2c_End(unsigned int  dly);

extern unsigned int I2C_probe(unsigned int sla,unsigned char subaddr_type,unsigned int subaddr,unsigned int num ,unsigned char* data);
extern unsigned int I2C_ReadNByte (unsigned int sla, unsigned int suba_type, unsigned int subaddr,unsigned int num, unsigned char *data);
extern unsigned int I2C_WriteNByte(unsigned int sla, unsigned int suba_type, unsigned int suba,  unsigned int num,unsigned char *data);
extern void I2C_Excetion(void);

#endif
