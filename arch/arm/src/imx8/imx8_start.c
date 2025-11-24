/****************************************************************************
 * arch/arm/src/imx8/imx8_start.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/cache.h>
#include <nuttx/init.h>
#include <arch/barriers.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "nvic.h"
#include "ram_vectors.h"

#include "imx8_start.h"
#include "imx8_boardinit.h"
#include "sdk/fsl_debug_console.h" // PRINTF macro for debug
#include "sdk/core_cm7.h"


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* #define IDLE_STACK      ((unsigned)&_ebss+CONFIG_IDLETHREAD_STACKSIZE) /\*
 * *\/ */

extern uint8_t _estack_idle[], _sstack_idle[];
#define IDLE_STACK_TOP      ((uintptr_t)&_estack_idle) /*  */

#ifdef CONFIG_DEBUG_FEATURES
#define showprogress(c) imx8_lowputc(c)
#else
#  define showprogress(c)
#endif

/* Memory Map ***************************************************************/

/* 0x2020:0000 - Start of on-chip RAM (OCRAM) and start of .data (_sdata)
 *             - End of .data (_edata) and start of .bss (_sbss)
 *             - End of .bss (_ebss) and bottom of idle stack
 *             - _ebss + CONFIG_IDLETHREAD_STACKSIZE = end of idle stack,
 *               start of heap. NOTE that the ARM uses a decrement before
 *               store stack so that the correct initial value is the end of
 *               the stack + 4;
 * 0x2027:ffff - End of OCRAM and end of heap (assuming 512Kb OCRAM)
 *
 * NOTE:  This assumes that all internal RAM is configured for OCRAM (vs.
 * ITCM or DTCM).  The RAM that holds .data and .bss is called the "Primary
 * RAM".  Many other configurations are possible, including configurations
 * where the primary ram is in external memory.  Those are not considered
 * here.
 */

/* Linker symbols for ramfuncs / itcm / dtcm (these may not be declared in arm_internal.h) */
/* extern uint8_t _sramfuncs[];    /\* VMA start of .ramfunc in RAM *\/ */
/* extern uint8_t _eramfuncs[];    /\* VMA end of .ramfunc in RAM *\/ */
/* extern uint8_t _framfuncs[];    /\* LMA source for .ramfunc (LOADADDR) *\/ */

/* extern uint8_t __sitcm[];       /\* VMA start of .itcm_text *\/ */
/* extern uint8_t __eitcm[];       /\* VMA end of .itcm_text *\/ */
/* extern uint8_t _litcm_load[];   /\* LMA source for .itcm_text *\/ */

/* extern uint8_t __sdtcm[];       /\* VMA start dtcm_data *\/ */
/* extern uint8_t __edtcm[];       /\* VMA end dtcm_data *\/ */
/* extern uint8_t _ldtcm_load[];   /\* LMA source for dtcm_data *\/ */

/****************************************************************************
 * Private Types
 ****************************************************************************/

#ifdef CONFIG_ARMV7M_STACKCHECK
/* we need to get r10 set before we can allow instrumentation calls */

void __start(void) noinstrument_function;
#endif

extern const void * const _vectors[];

/****************************************************************************
 * Name: imx8_tcmenable
 *
 * Description:
 *   Enable/disable tightly coupled memories.  Size of tightly coupled
 *   memory regions is controlled by GPNVM Bits 7-8.
 *
 ****************************************************************************/

static inline void imx8_tcmenable(void)
{
  uint32_t regval;
  UP_MB();

  /* Enabled/disabled ITCM */
  regval  = NVIC_TCMCR_EN | NVIC_TCMCR_RMW | NVIC_TCMCR_RETEN;
  putreg32(regval, NVIC_ITCMCR);

  /* Enabled/disabled DTCM */
  regval  = NVIC_TCMCR_EN | NVIC_TCMCR_RMW | NVIC_TCMCR_RETEN;
  putreg32(regval, NVIC_DTCMCR);

  UP_MB();
}
  

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: __start
 *
 * Description:
 *   This is the reset entry point.
 *
 ****************************************************************************/

osentry_function
void __start(void)
{
  const register uint32_t *src;
  register uint32_t *dest;

  /* Make sure that interrupts are disabled and set MSP */

  __asm__ __volatile__ ("\tcpsid  i\n");
  __asm__ __volatile__("MSR MSP, %0\n" : : "r"(IDLE_STACK_TOP) :);

  SCB->CCR |= SCB_CCR_STKALIGN_Msk;
  __DSB();
  __ISB();


  /* Make sure that we use MSP from now on */

  __asm__ __volatile__ ("MSR CONTROL, %0\n" : : "r" (0) :);
  __asm__ __volatile__("ISB SY\n");

  /* Enable/disable tightly coupled memories */

  imx8_tcmenable();

  /* Make sure VECTAB is set to NuttX vector table
   * and not the one from the boot ROM and have consistency
   * with debugger that automatically set the VECTAB
   */

  putreg32((uint32_t)_vectors, NVIC_VECTAB);

#ifdef CONFIG_ARMV7M_STACKCHECK
  /* Set the stack limit before we attempt to call any functions */

  __asm__ volatile("sub r10, sp, %0" : :
                   "r"(CONFIG_IDLETHREAD_STACKSIZE - 64) :);
#endif

/* #if defined(CONFIG_BOOT_RUNFROMISRAM) || defined(CONFIG_IMX8_INIT_FLEXRAM) */
/*     imx8_ocram_initialize(); */
/* #endif */

  /* Clear .bss.  We'll do this inline (vs. calling memset) just to be
   * certain that there are no issues with the state of global variables.
   */

  for (dest = (uint32_t *)_sbss; dest < (uint32_t *)_ebss; )
    {
      *dest++ = 0;
    }

  /* Move the initialized data section from his temporary holding spot in
   * FLASH into the correct place in OCRAM.  The correct place in OCRAM is
   * give by _sdata and _edata.  The temporary location is in FLASH at the
   * end of all of the other read-only data (.text, .rodata) at _eronly.
   */

  for (src = (const uint32_t *)_eronly,
       dest = (uint32_t *)_sdata; dest < (uint32_t *)_edata;
      )
    {
      *dest++ = *src++;
    }

  /* Copy any necessary code sections from FLASH to RAM.  The correct
   * destination in OCRAM is given by _sramfuncs and _eramfuncs.  The
   * temporary location is in flash after the data initialization code
   * at _framfuncs.  This should be done before imx8_clockconfig() is
   * called (in case it has some dependency on initialized C variables).
   */

#ifdef CONFIG_ARCH_RAMFUNCS
  for (src = (const uint32_t *)_framfuncs,
       dest = (uint32_t *)_sramfuncs; dest < (uint32_t *)_eramfuncs;
      )
    {
      *dest++ = *src++;
    }
#endif

#ifdef CONFIG_ARCH_RAMVECTORS
  arm_ramvec_initialize();
#endif

  volatile int dbg = 1;
  while(dbg) ;
  
#ifdef CONFIG_ARMV7M_STACKCHECK
  arm_stack_check_init();
#endif

  arm_fpuconfig();


  /* Initialize onboard resources
   * - initialize MPU and disable icache and dcache
   * - initialize RDC
   * - Configure IO pins
   * - Setup the clocks
   * - Init boot console
   */
  imx8_boardinitialize();
  PRINTF("NuttX starting...\r\n");
  up_putc('H');
  up_putc('E');
  up_putc('L');
  up_putc('L');
  up_putc('O');
  up_putc('\r');
  up_putc('\n');

  syslog(LOG_INFO,
       "idle: base=%p top=%p msp=%p ebss=%p size=%u\n",
       _sstack_idle, _estack_idle, (void*)IDLE_STACK_TOP, _ebss,
       (unsigned)((uintptr_t)_estack_idle - (uintptr_t)_sstack_idle));

  /* imx8_lowsetup(); */
  /* showprogress('B'); */

#ifdef CONFIG_ARM_MPU
#ifdef CONFIG_BUILD_PROTECTED
  /* For the case of the separate user-/kernel-space build, perform whatever
   * platform specific initialization of the user memory is required.
   * Normally this just means initializing the user space .data and .bss
   * segments.
   */

  imx8_userspace();
#endif

  /* Configure the MPU to permit user-space access to its FLASH and RAM (for
   * CONFIG_BUILD_PROTECTED) or to manage cache properties in external
   * memory regions.
   */

  /* imx8_mpu_initialize(); */
#endif


  /* Perform early serial initialization */

/* #ifdef USE_EARLYSERIALINIT */
/*   imx8_earlyserialinit(); */
/* #endif */

  /* Then start NuttX */

  nx_start();

  /* Shouldn't get here */

  for (; ; );
}
