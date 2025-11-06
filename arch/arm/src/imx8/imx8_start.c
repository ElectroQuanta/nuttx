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

/* #include "imx8_clockconfig.h" */
/* #include "imx8_mpuinit.h" */
/* #include "imx8_userspace.h" */
/* #include "imx8_lowputc.h" */
/* #include "imx8_serial.h" */
#include "imx8_start.h"
#include "imx8_boardinit_sdk.h"
/* #include "sdk/board.h" */
/* #include "sdk/clock_config.h" */
#include "sdk/fsl_debug_console.h"
/* #include "sdk/pin_mux.h" */
/* #include "imx8_config.h" */
/* #include "imx8_rdc.h" */
/* #include "imx8_iomuxc.h" */

/* #include "hardware/imx8mn/armv7m_cachel1.h" */
/* #include "hardware/imx8mn/board.h" */
/* #include "hardware/imx8mn/fsl_clock.h" */
/* #include "hardware/imx8mn/MIMX8MN6_cm7_COMMON.h" */
/* #include "hardware/imx8mn/system_MIMX8MN6_cm7.h" */
/* #include "hardware/imx8mn/fsl_debug_console.h" */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define IDLE_STACK      ((unsigned)&_ebss+CONFIG_IDLETHREAD_STACKSIZE)

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

/* /\* Fractional PLLs: Fout = ((mainDiv+dsm/65536) * refSel) / (preDiv * 2^ postDiv) *\/ */
/* /\* AUDIO PLL1 configuration *\/ */
/* const ccm_analog_frac_pll_config_t g_audioPll1Config = { */
/*     .refSel  = kANALOG_PllRefOsc24M, /\*!< PLL reference OSC24M *\/ */
/*     .mainDiv = 262U, */
/*     .dsm     = 9437U, */
/*     .preDiv  = 2U, */
/*     .postDiv = 3U, /\*!< AUDIO PLL1 frequency  = 393215996HZ *\/ */
/* }; */

/* /\* AUDIO PLL2 configuration *\/ */
/* const ccm_analog_frac_pll_config_t g_audioPll2Config = { */
/*     .refSel  = kANALOG_PllRefOsc24M, /\*!< PLL reference OSC24M *\/ */
/*     .mainDiv = 361U, */
/*     .dsm     = 17511U, */
/*     .preDiv  = 3U, */
/*     .postDiv = 3U, /\*!< AUDIO PLL2 frequency  = 361267197HZ *\/ */
/* }; */

/* /\* Integer PLLs: Fout = (mainDiv * refSel) / (preDiv * 2^ postDiv) *\/ */
/* /\* SYSTEM PLL1 configuration *\/ */
/* const ccm_analog_integer_pll_config_t g_sysPll1Config = { */
/*     .refSel  = kANALOG_PllRefOsc24M, /\*!< PLL reference OSC24M *\/ */
/*     .mainDiv = 400U, */
/*     .preDiv  = 3U, */
/*     .postDiv = 2U, /\*!< SYSTEM PLL1 frequency  = 800MHZ *\/ */
/* }; */

/* /\* SYSTEM PLL2 configuration *\/ */
/* const ccm_analog_integer_pll_config_t g_sysPll2Config = { */
/*     .refSel  = kANALOG_PllRefOsc24M, /\*!< PLL reference OSC24M *\/ */
/*     .mainDiv = 250U, */
/*     .preDiv  = 3U, */
/*     .postDiv = 1U, /\*!< SYSTEM PLL2 frequency  = 1000MHZ *\/ */
/* }; */

/* /\* SYSTEM PLL3 configuration *\/ */
/* const ccm_analog_integer_pll_config_t g_sysPll3Config = { */
/*     .refSel = kANALOG_PllRefOsc24M, /\*!< PLL reference OSC24M *\/ */
/*     .mainDiv = 300, */
/*     .preDiv = 3U, */
/*     .postDiv = 2U, /\*!< SYSTEM PLL3 frequency  = 600MHZ *\/ */
/* }; */


/* uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK; */


/* /\*! */
/*  * @brief CCM reg macros to extract corresponding registers bit field. */
/*  *\/ */
/* #define CCM_BIT_FIELD_VAL(val, mask, shift) (((val)&mask) >> shift) */

/* /\*! */
/*  * @brief CCM reg macros to get corresponding registers values. */
/*  *\/ */
/* #define CCM_ANALOG_REG_VAL(base, off) (*((volatile uint32_t *)((uint32_t)(base) + (off)))) */


/* uint32_t GetFracPllFreq(const volatile uint32_t *base) */
/* { */
/*     uint32_t fracCfg0   = CCM_ANALOG_REG_VAL(base, 0U); */
/*     uint32_t fracCfg1   = CCM_ANALOG_REG_VAL(base, 4U); */
/*     uint32_t fracCfg2   = CCM_ANALOG_REG_VAL(base, 8U); */
/*     uint32_t refClkFreq = 0U; */
/*     uint64_t fracClk    = 0U; */

/*     uint8_t refSel   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg0, CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK, */
/*                                                 CCM_ANALOG_AUDIO_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_SHIFT); */
/*     uint32_t mainDiv = CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK, */
/*                                          CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_MAIN_DIV_SHIFT); */
/*     uint8_t preDiv   = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK, */
/*                                                 CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_PRE_DIV_SHIFT); */
/*     uint8_t postDiv  = (uint8_t)CCM_BIT_FIELD_VAL(fracCfg1, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK, */
/*                                                  CCM_ANALOG_AUDIO_PLL1_FDIV_CTL0_PLL_POST_DIV_SHIFT); */
/*     uint32_t dsm     = CCM_BIT_FIELD_VAL(fracCfg2, CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_MASK, */
/*                                      CCM_ANALOG_AUDIO_PLL1_FDIV_CTL1_PLL_DSM_SHIFT); */

/*     if (refSel == 0U) /\* OSC 24M Clock *\/ */
/*     { */
/*         refClkFreq = CPU_XTAL_SOSC_CLK_24MHZ; */
/*     } */
/*     else */
/*     { */
/*         refClkFreq = CLK_PAD_CLK; /\* CLK_PAD_CLK Clock, please note that the value is 0hz by default, it could be set at */
/*                                      system_MIMX8MNx_cm7.h :96 *\/ */
/*     } */
/*     fracClk = (uint64_t)refClkFreq * ((uint64_t)mainDiv * 65536UL + (uint64_t)dsm) / */
/*               ((uint64_t)65536UL * preDiv * (1UL << postDiv)); */

/*     return (uint32_t)fracClk; */
/* } */

/* uint32_t GetIntegerPllFreq(const volatile uint32_t *base) */
/* { */
/*     uint32_t integerCfg0 = CCM_ANALOG_REG_VAL(base, 0U); */
/*     uint32_t integerCfg1 = CCM_ANALOG_REG_VAL(base, 4U); */
/*     uint32_t refClkFreq  = 0U; */
/*     uint64_t pllOutClock = 0U; */

/*     uint8_t pllBypass = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg0, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_BYPASS_MASK, */
/*                                                    CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_BYPASS_SHIFT); */
/*     uint8_t refSel    = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg0, CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_MASK, */
/*                                                 CCM_ANALOG_SYS_PLL1_GEN_CTRL_PLL_REF_CLK_SEL_SHIFT); */
/*     uint32_t mainDiv  = CCM_BIT_FIELD_VAL(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_MASK, */
/*                                          CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_MAIN_DIV_SHIFT); */
/*     uint8_t preDiv    = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_MASK, */
/*                                                 CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_PRE_DIV_SHIFT); */
/*     uint8_t postDiv   = (uint8_t)CCM_BIT_FIELD_VAL(integerCfg1, CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_MASK, */
/*                                                  CCM_ANALOG_SYS_PLL1_FDIV_CTL0_PLL_POST_DIV_SHIFT); */

/*     if (refSel == 0U) /\* OSC 24M Clock *\/ */
/*     { */
/*         refClkFreq = CPU_XTAL_SOSC_CLK_24MHZ; */
/*     } */
/*     else */
/*     { */
/*         refClkFreq = CLK_PAD_CLK; /\* CLK_PAD_CLK Clock, please note that the value is 0hz by default, it could be set at */
/*                                      system_MIMX8MNx_cm7.h :96 *\/ */
/*     } */

/*     if (pllBypass != 0U) */
/*     { */
/*         pllOutClock = refClkFreq; */
/*     } */

/*     else */
/*     { */
/*         pllOutClock = (uint64_t)refClkFreq * mainDiv / (((uint64_t)(1U) << postDiv) * preDiv); */
/*     } */

/*     return (uint32_t)pllOutClock; */
/* } */

/* static */
/* void SystemCoreClockUpdate(void) */
/* { */
/*     volatile uint32_t *M7_ClockRoot = (volatile uint32_t *)(&(CCM)->ROOT[1].TARGET_ROOT); */
/*     uint32_t pre  = ((*M7_ClockRoot & CCM_TARGET_ROOT_PRE_PODF_MASK) >> CCM_TARGET_ROOT_PRE_PODF_SHIFT) + 1U; */
/*     uint32_t post = ((*M7_ClockRoot & CCM_TARGET_ROOT_POST_PODF_MASK) >> CCM_TARGET_ROOT_POST_PODF_SHIFT) + 1U; */

/*     uint32_t freq = 0U; */

/*     switch ((*M7_ClockRoot & CCM_TARGET_ROOT_MUX_MASK) >> CCM_TARGET_ROOT_MUX_SHIFT) */
/*     { */
/*         case 0U: /\* OSC 24M Clock *\/ */
/*             freq = CPU_XTAL_SOSC_CLK_24MHZ; */
/*             break; */
/*         case 1U:                                                             /\* System PLL2 DIV5 *\/ */
/*             freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL2_GEN_CTRL)) / 5U; /\* Get System PLL2 DIV5 freq *\/ */
/*             break; */
/*         case 2U:                                                             /\* System PLL2 DIV4 *\/ */
/*             freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL2_GEN_CTRL)) / 4U; /\* Get System PLL2 DIV4 freq *\/ */
/*             break; */
/*         case 3U:                                                             /\* System PLL1 DIV3 *\/ */
/*             freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL1_GEN_CTRL)) / 3U; /\* Get System PLL1 DIV3 freq *\/ */
/*             break; */
/*         case 4U:                                                        /\* System PLL1 *\/ */
/*             freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL1_GEN_CTRL)); /\* Get System PLL1 freq *\/ */
/*             break; */
/*         case 5U:                                                       /\* AUDIO PLL1 *\/ */
/*             freq = GetFracPllFreq(&(CCM_ANALOG->AUDIO_PLL1_GEN_CTRL)); /\* Get AUDIO PLL1 freq *\/ */
/*             break; */
/*         case 6U:                                                       /\* VIDEO PLL1 *\/ */
/*             freq = GetFracPllFreq(&(CCM_ANALOG->VIDEO_PLL1_GEN_CTRL)); /\* Get VIDEO PLL1 freq *\/ */
/*             break; */
/*         case 7U:                                                        /\* System PLL3 *\/ */
/*             freq = GetIntegerPllFreq(&(CCM_ANALOG->SYS_PLL3_GEN_CTRL)); /\* Get System PLL3 freq *\/ */
/*             break; */
/*         default: */
/*             freq = CPU_XTAL_SOSC_CLK_24MHZ; */
/*             break; */
/*     } */

/*     SystemCoreClock = freq / pre / post; */
/* } */

/* static */
/* void setup_boot_clocks(void) */
/* { */
/*     /\* * The following steps just show how to configure the PLL clock sources using the clock driver on M7 core side . */
/*      * Please note that the ROM has already configured the SYSTEM PLL1 to 800Mhz when power up the SOC, meanwhile A core */
/*      * would enable the Div output for SYSTEM PLL1 & PLL2 by U-Boot. */
/*      * Therefore, there is no need to configure the system PLL again on M7 side, otherwise it would have a risk to make */
/*      * the SOC hang. */
/*      *\/ */

/*     /\* switch AHB NOC root to 24M first in order to configure the SYSTEM PLL1. *\/ */
/*     CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxOsc24M); */

/*     /\* switch AXI M7 root to 24M first in order to configure the SYSTEM PLL3. *\/ */
/*     CLOCK_SetRootMux(kCLOCK_RootM7, kCLOCK_M7RootmuxOsc24M); */

/*     /\* Init Audio PLL1/Audio PLL2 *\/ */
/*     CLOCK_InitAudioPll1(&g_audioPll1Config); /\* init AUDIO PLL1 run at 393215996HZ *\/ */
/*     CLOCK_InitAudioPll2(&g_audioPll2Config); /\* init AUDIO PLL2 run at 361267197HZ *\/ */

/*     /\* As ROM not enables PLL3 by default, enable PLL3 to 600M if A core not set it. *\/ */
/*     if (CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_SysPll3InternalPll1BypassCtrl) == 1) */
/*     { */
/*         CLOCK_InitSysPll3(&g_sysPll3Config); */
/*     } */
/*     CLOCK_SetRootDivider(kCLOCK_RootM7, 1U, 1U);              /\* Set M7 root clock freq to 600M / 1 = 600M *\/ */
/*     CLOCK_SetRootMux(kCLOCK_RootM7, kCLOCK_M7RootmuxSysPll3); /\* switch cortex-m7 to SYSTEM PLL3 *\/ */

/*     CLOCK_SetRootDivider(kCLOCK_RootAhb, 1U, 1U);                   /\* Set root clock freq to 133M / 1= 133MHZ *\/ */
/*     CLOCK_SetRootMux(kCLOCK_RootAhb, kCLOCK_AhbRootmuxSysPll1Div6); /\* switch AHB to SYSTEM PLL1 DIV6 *\/ */

/*     CLOCK_SetRootDivider(kCLOCK_RootAudioAhb, 1U, 2U);                    /\* Set root clock freq to 800MHZ/ 2= 400MHZ*\/ */
/*     CLOCK_SetRootMux(kCLOCK_RootAudioAhb, kCLOCK_AudioAhbRootmuxSysPll1); /\* switch AUDIO AHB to SYSTEM PLL1 *\/ */

/*     CLOCK_SetRootDivider(kCLOCK_RootUart4, 1U, 1U);                     /\* Set root clock freq to 80MHZ/ 1= 80MHZ *\/ */
/*     CLOCK_SetRootMux(kCLOCK_RootUart4, kCLOCK_UartRootmuxSysPll1Div10); /\* Set UART source to SysPLL1 Div10 80MHZ *\/ */

/*     CLOCK_EnableClock(kCLOCK_Rdc);   /\* Enable RDC clock *\/ */
/*     CLOCK_EnableClock(kCLOCK_Ocram); /\* Enable Ocram clock *\/ */

/*     /\* The purpose to enable the following modules clock is to make sure the M7 core could work normally when A53 core */
/*      * enters the low power status.*\/ */
/*     CLOCK_EnableClock(kCLOCK_Sim_display); */
/*     CLOCK_EnableClock(kCLOCK_Sim_m); */
/*     CLOCK_EnableClock(kCLOCK_Sim_main); */
/*     CLOCK_EnableClock(kCLOCK_Sim_s); */
/*     CLOCK_EnableClock(kCLOCK_Sim_wakeup); */
/*     CLOCK_EnableClock(kCLOCK_Debug); */
/*     CLOCK_EnableClock(kCLOCK_Dram); */
/*     CLOCK_EnableClock(kCLOCK_Sec_Debug); */

/*     /\* Update core clock *\/ */
/*     SystemCoreClockUpdate(); */
/* } */

/* void BOARD_InitDebugConsole(void) */
/* { */
/*   uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ; */
/*   CLOCK_EnableClock(kCLOCK_Uart4); */
/*   DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq); */
/* } */
  

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
  __asm__ __volatile__ ("MSR MSP, %0\n" : : "r" (IDLE_STACK) :);

  /* Make sure that we use MSP from now on */

  __asm__ __volatile__ ("MSR CONTROL, %0\n" : : "r" (0) :);
  __asm__ __volatile__("ISB SY\n");

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

  /* Configure the UART so that we can get debug output as soon as possible */

  /* M7 has its local cache and enabled by default,
   * need to set smart subsystems (0x28000000 ~ 0x3FFFFFFF)
   * non-cacheable before accessing this address region */
  /* BOARD_InitMemory(); */
  imx8_init_mem();
  /* rdc_init(); // BOARD_RdcInit */
  BOARD_RdcInit();
  BOARD_InitBootPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();
  PRINTF("NuttX starting...\r\n");


  /* M7 has its local cache and enabled by default,
   * need to set smart subsystems (0x28000000 ~ 0x3FFFFFFF)
   * non-cacheable before accessing this address region */
  /* BOARD_InitMemory(); */
  /* imx8_enablemem(); // BOARD_InitMemory(); */
  
  /* rdc_init(); // BOARD_RdcInit */

  /* // BOARD_InitBootPins() */
  /* IOMUXC_SetPinMux(IOMUXC_UART4_RXD_UART4_RX, 0U); */
  /* IOMUXC_SetPinConfig(IOMUXC_UART4_RXD_UART4_RX, */
  /* 					  IOMUXC_SW_PAD_CTL_PAD_DSE(6U) | */
  /* 					  IOMUXC_SW_PAD_CTL_PAD_FSEL(2U)); */
  /* IOMUXC_SetPinMux(IOMUXC_UART4_TXD_UART4_TX, 0U); */
  /* IOMUXC_SetPinConfig(IOMUXC_UART4_TXD_UART4_TX, */
  /* 					  IOMUXC_SW_PAD_CTL_PAD_DSE(6U) | */
  /* 					  IOMUXC_SW_PAD_CTL_PAD_FSEL(2U)); */

  /* // BOARD_BootClockRUN */
  /* setup_boot_clocks(); */
  /* BOARD_InitDebugConsole(); */

  /* up_putc('H'); */
  /* up_putc('E'); */

  
  /* imx8_lowsetup(); */
  /* showprogress('B'); */

  /* Enable/disable tightly coupled memories */

  /* imx8_tcmenable(); */

  /* Initialize onboard resources */

  imx8_boardinitialize();

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

  /* Enable I- and D-Caches */
  /* On the imx8mn the I- D-caches should not be enabled
     (see IMX8MNRM - section 4.2.2.1 )*/
  /* up_enable_icache(); */
  /* up_enable_dcache(); */

  /* Perform early serial initialization */

/* #ifdef USE_EARLYSERIALINIT */
/*   imx8_earlyserialinit(); */
/* #endif */

  /* Then start NuttX */

  nx_start();

  /* Shouldn't get here */

  for (; ; );
}
