.section .vector,"x"

.code 32
.global _start
_start:
	ldr pc,=arm926ejs_entry
	ldr pc,=undefined_instruction
	ldr pc,=software_interrupt
	ldr pc,=prefetch_abort
	ldr pc,=data_abort
	nop	
	ldr pc,=irq
	ldr pc,=fiq
.text

.code 32

.global c_entry 

.global lpc32xx_irq_handler

.equ IRQ_STACK_LEGTH,2

.include "setup_gnu.inc"


arm926ejs_entry:
	/*close wtd*/
	ldr r0,=TIMCLK_CTRL
	mov r1,#0
	str r1,[r0]
/*	
	ldr sp,=END_OF_IRAM
	sub sp,sp,#(16*512)
	msr CPSR_c,#0xd2
	ldr sp,StackIrq
	msr CPSR_c,#0xd3
	*/
/*跳转到C*/
	@b loop
	BL c_entry
/*debug*/
loop:
	bl gpioset	
	ldr r2,=0xffff
	bl delay
	bl gpioclr
	ldr r2,=0xffff
	bl delay
	b loop
delay:
	sub r2,r2,#1
	cmp r2,#0
	moveq pc,lr 
	b delay
gpioset:
	ldr r0,=0x40028004
	ldr r1,=0x100
	str r1,[r0]
	mov pc ,lr
gpioclr:
	ldr r0,=0x40028008
	ldr r1,=0x100
	str r1,[r0]
	mov pc,lr	

undefined_instruction:
	b loop
software_interrupt:
	b loop
prefetch_abort:
	b loop
data_abort:
 	b loop
irq:
	b loop
	@b lpc32xx_irq_handler
fiq:
	b loop

StackIrq: .word IrqStackSpace+IRQ_STACK_LEGTH*4
IrqStackSpace: .space IRQ_STACK_LEGTH*4

