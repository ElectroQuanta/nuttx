/****************************************************************************
 * arch/arm/src/imx8/hardware/imx8mn/armv7m_cache1.h
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

#ifndef __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_ARMV7M_CACHE1_H
#define __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_ARMV7M_CACHE1_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "core_cm7.h"


/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_CacheFunctions Cache Functions
  \brief    Functions that configure Instruction and Data cache.
  @{
 */

/* Cache Size ID Register Macros */
#define CCSIDR_WAYS(x)         (((x) & SCB_CCSIDR_ASSOCIATIVITY_Msk) >> SCB_CCSIDR_ASSOCIATIVITY_Pos)
#define CCSIDR_SETS(x)         (((x) & SCB_CCSIDR_NUMSETS_Msk      ) >> SCB_CCSIDR_NUMSETS_Pos      )

#ifndef __SCB_DCACHE_LINE_SIZE
#define __SCB_DCACHE_LINE_SIZE  32U /*!< Cortex-M7 cache line size is fixed to 32 bytes (8 words). See also register SCB_CCSIDR */
#endif

#ifndef __SCB_ICACHE_LINE_SIZE
#define __SCB_ICACHE_LINE_SIZE  32U /*!< Cortex-M7 cache line size is fixed to 32 bytes (8 words). See also register SCB_CCSIDR */
#endif

/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_FORCEINLINE void SCB_DisableICache (void)
{
    __DSB();
    __ISB();
    SCB->CCR &= ~(uint32_t)SCB_CCR_IC_Msk;  /* disable I-Cache */
    SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    __DSB();
    __ISB();
}


/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_FORCEINLINE void SCB_InvalidateICache (void)
{
    __DSB();
    __ISB();
    SCB->ICIALLU = 0UL;
    __DSB();
    __ISB();
}


/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  */
__STATIC_FORCEINLINE void SCB_DisableDCache (void)
{
  #if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    struct {
      uint32_t ccsidr;
      uint32_t sets;
      uint32_t ways;
    } locals
    #if ((defined(__GNUC__) || defined(__clang__)) && !defined(__OPTIMIZE__))
       __ALIGNED(__SCB_DCACHE_LINE_SIZE)
    #endif
    ;

    SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    __DSB();

    SCB->CCR &= ~(uint32_t)SCB_CCR_DC_Msk;  /* disable D-Cache */
    __DSB();

    #if !defined(__OPTIMIZE__)
      /*
       * For the endless loop issue with no optimization builds.
       * More details, see https://github.com/ARM-software/CMSIS_5/issues/620
       *
       * The issue only happens when local variables are in stack. If
       * local variables are saved in general purpose register, then the function
       * is OK.
       *
       * When local variables are in stack, after disabling the cache, flush the
       * local variables cache line for data consistency.
       */
      /* Clean and invalidate the local variable cache. */
      SCB->DCCIMVAC = (uint32_t)&locals;
      __DSB();
      __ISB();
    #endif

    locals.ccsidr = SCB->CCSIDR;
                                            /* clean & invalidate D-Cache */
    locals.sets = (uint32_t)(CCSIDR_SETS(locals.ccsidr));
    do {
      locals.ways = (uint32_t)(CCSIDR_WAYS(locals.ccsidr));
      do {
        SCB->DCCISW = (((locals.sets << SCB_DCCISW_SET_Pos) & SCB_DCCISW_SET_Msk) |
                       ((locals.ways << SCB_DCCISW_WAY_Pos) & SCB_DCCISW_WAY_Msk)  );
        #if defined ( __CC_ARM )
          __schedule_barrier();
        #endif
      } while (locals.ways-- != 0U);
    } while(locals.sets-- != 0U);

    __DSB();
    __ISB();
  #endif
}

#endif // __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_ARMV7M_CACHE1_H
