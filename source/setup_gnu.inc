/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Notes:
;     CodeSourcery GNU toolchain version
;
/* LPC3220 users should changes to following define to 0x20000, while
   other LCP32x0 users should keep this at 0x40000 */
.equ CLK_PM_BASE_ADDR ,0x40004000
.equ TIMCLK_CTRL ,(CLK_PM_BASE_ADDR+0xBC)

.EQU IRAM_SIZE,              0x40000
.EQU END_OF_IRAM, 			 0x8040000
