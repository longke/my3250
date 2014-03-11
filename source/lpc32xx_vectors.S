    .text
    .code 32

    .global lpc32xx_undefined_handler
    .global lpc32xx_swi_handler
    .global lpc32xx_prefetch_handler
    .global lpc32xx_abort_handler
    .global lpc32xx_irq_handler
    .global lpc32xx_fiq_handler

    .global irq_func_ptrs

.EQU MIC_BASE_ADDR, 0x40008000    /* Base address of MIC */
.EQU SIC1_BASE_ADDR, 0x4000C000   /* Base address of SIC1 */
.EQU SIC2_BASE_ADDR, 0x40010000   /* Base address of SIC2 */
.EQU IRQ_STATUS_OFF, 0x08         /* Masked IRQ status offset */


/***********************************************************************************
* Function: lpc32xx_undefined_handler
***********************************************************************************/
lpc32xx_undefined_handler:
    B    lpc32xx_undefined_handler

/***********************************************************************************
* Function: lpc32xx_swi_handler
***********************************************************************************/
lpc32xx_swi_handler:
    B    lpc32xx_swi_handler

/***********************************************************************************
* Function: lpc32xx_prefetch_handler
***********************************************************************************/
lpc32xx_prefetch_handler:
    B    lpc32xx_prefetch_handler

/***********************************************************************************
* Function: lpc32xx_abort_handler
***********************************************************************************/
lpc32xx_abort_handler:
    B    lpc32xx_abort_handler

/***********************************************************************************
  * Function: lpc32xx_irq_handler
  * Purpose:中断处理函数
  * Processing:查看中断源，定位中断处理函数
***********************************************************************************/
lpc32xx_irq_handler:
    SUB    lr, lr, #4                 /* Get return address */
    STMFD  sp!, {r0-r12, lr}          /* Save registers */
    /* Read the MIC interrupt status registers */
    LDR    r2, =MIC_BASE_ADDR
    LDR    r3, [r2, #IRQ_STATUS_OFF]
    AND    r3, r3, #0xFFFFFFFC /* Mask off subIRQ bits */
    MOV    r4, #0

    /* If there the MIC IRQ status is 0, then there are no MIC
       interrupts pending. That means, go service SIC1 interrupts
       instead. */
service_mic:
    CMP    r3, #0                  
    BNE    int_found 
    /* The interrupt was not from MIC */
service_sic1:
    /* Read the SIC1 interrupt status registers */
    LDR    r2, =SIC1_BASE_ADDR     
    LDR    r3, [r2, #IRQ_STATUS_OFF]
    MOV    r4, #32

    /* If there the SIC1 IRQ status is 0, then there are no SIC1
       interrupts pending. That means, go service SIC2 interrupts
       instead. */
    CMP    r3, #0 
    BNE    int_found
	/*bne gpioset*/
    /* The interrupt was not from SIC1 */

service_sic2:
    /* Read the SIC2 interrupt status registers  */
    LDR    r2, =SIC2_BASE_ADDR     
    LDR    r3, [r2, #IRQ_STATUS_OFF]
    MOV    r4, #64
    CMP    r3, #0                  
    BEQ    int_exit 
    /* The interrupt was not from SIC2 */

int_found:
	ldr r7,=0x40028004
	ldr r8,=0x100
	str r8,[r7] 
    CLZ    r1, r3
    RSB    r1, r1, #31
    ADD    r1, r1, r4
    LDR    r0, =irq_func_ptrs    /* Get address of jump table */
    ADD    r0, r0, r1, LSL #2    /* Add by interrupt offset */
    LDR    r0, [r0]              /* Get handler address */
    CMP    r0, #0                /* Is handler address NULL? */
    BEQ    int_exit              /* If null, the exit */
    MOV    lr, pc                /* Will return to int_exit */
    BX     r0                    /* Jump to handler */

int_exit:
    LDMFD  sp!, {r0-r12, pc}^    /* Restore registers and exit */

/***********************************************************************************
* Function: lpc32xx_fiq_handler
**********************************************************************************/
lpc32xx_fiq_handler:
    B    lpc32xx_fiq_handler

    .end
