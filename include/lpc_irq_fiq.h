/***********************************************************************
 * $Id:: lpc_irq_fiq.h 1008 2008-08-06 18:15:33Z wellsk                $
 *
 * Project: ARM core interrupt functions
 *
 * Description:
 *     This file contains the function declarations for routines for
 *     enabling, disabling and restoring the state of IRQ and FIQ
 *     exceptions.
 *
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef LPC_IRQ_FIQ_H
#define LPC_IRQ_FIQ_H
#include "lpc_types.h"

static __inline UNS_32 disable_irq(void)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "MRS %0, CPSR" "\n\t"
    "ORR %1, %0, #0x80" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
  );

  return ret;
}

static __inline UNS_32 disable_fiq(void)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "MRS %0, CPSR" "\n\t"
    "ORR %1, %0, #0x40" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
  );

  return ret;
}

static __inline UNS_32 disable_irq_fiq(void)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "MRS %0, CPSR" "\n\t"
    "ORR %1, %0, #0xC0" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
  );

  return ret;
}

static __inline UNS_32 enable_irq(void)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "MRS %0, CPSR" "\n\t"
    "BIC %1, %0, #0x80" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
  );

  return ret;
}

static __inline UNS_32 enable_fiq(void)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "MRS %0, CPSR" "\n\t"
    "BIC %1, %0, #0x40" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
  );

  return ret;
}

static __inline UNS_32 enable_irq_fiq(void)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "MRS %0, CPSR" "\n\t"
    "BIC %1, %0, #0xC0" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
  );

  return ret;
}

static __inline UNS_32 disable_irq_fiq_mask(UNS_32 mask)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "BIC %1, %2, #0x2F" "\n\t"
    "MRS %0, CPSR" "\n\t"
    "ORR %1, %0, %1" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
        : "r"(mask)
      );

  return ret;
}

static __inline UNS_32 enable_irq_fiq_mask(UNS_32 mask)
{
  register UNS_32 ret, tmp;

  asm volatile
  (
    "BIC %1, %2, #0x2F" "\n\t"
    "MRS %0, CPSR" "\n\t"
    "BIC %1, %0, %1" "\n\t"
    "MSR CPSR_c, %1" "\n\t"
  : "=r"(ret), "=r"(tmp)
        : "r"(mask)
      );

  return ret;
}

static __inline UNS_32 restore_exceptions(UNS_32 old)
{
  register UNS_32 ret, tmp, tmp2;

  asm volatile
  (
    "BIC %1, %3, #0x2F" "\n\t"
    "MRS %0, CPSR" "\n\t"
    "BIC %2, %0, #0xC0" "\n\t"
    "ORR %2, %2, %1" "\n\t"
    "MSR CPSR_c, %2" "\n\t"
  : "=r"(ret), "=r"(tmp), "=r"(tmp2)
        : "r"(old)
      );

  return ret;
}



#endif /* LPC_IRQ_FIQ_H */
