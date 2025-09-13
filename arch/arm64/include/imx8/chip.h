/****************************************************************************
 * arch/arm64/include/imx8/chip.h
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

#ifndef __ARCH_ARM64_INCLUDE_IMX8_CHIP_H
#define __ARCH_ARM64_INCLUDE_IMX8_CHIP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Number of bytes in x kibibytes/mebibytes/gibibytes */

#define KB(x)   ((x) << 10)
#define MB(x)   (KB(x) << 10)
#define GB(x)   (MB(UINT64_C(x)) << 10)

#if defined(CONFIG_ARCH_CHIP_IMX8_QUADMAX)

#if CONFIG_ARM64_GIC_VERSION == 3 || CONFIG_ARM64_GIC_VERSION == 4

#define CONFIG_GICD_BASE          0x51a00000
#define CONFIG_GICR_BASE          0x51b00000
#define CONFIG_GICR_OFFSET        0x20000

#else

#error "CONFIG_ARM64_GIC_VERSION should be 3 or 4 for i.MX8 QuadMax"

#endif /* CONFIG_ARM64_GIC_VERSION */

#define CONFIG_RAMBANK1_ADDR      0x80000000
#define CONFIG_RAMBANK1_SIZE      MB(128)

#define CONFIG_DEVICEIO_BASEADDR  0x40000000
#define CONFIG_DEVICEIO_SIZE      MB(512)
#define CONFIG_LOAD_BASE          0x80280000

#elif defined(CONFIG_ARCH_CHIP_IMX8_MN)

#if CONFIG_ARM64_GIC_VERSION == 3 || CONFIG_ARM64_GIC_VERSION == 4

#define CONFIG_GICD_BASE       0x38800000
#define CONFIG_GICR_BASE       0x38880000
#define CONFIG_GICR_OFFSET     0x20000

#else

#error "CONFIG_ARM64_GIC_VERSION should be 3 or 4 for i.MX8MN"

#endif /* CONFIG_ARM64_GIC_VERSION */

#define CONFIG_RAMBANK1_ADDR     0x40000000
#define CONFIG_RAMBANK1_SIZE     MB(512)
/* Peripherals (Device I/O) – separate from DDR */
#define CONFIG_DEVICEIO_BASEADDR 0x30000000  /* Example safe address */
/* #define CONFIG_DEVICEIO_SIZE     0x09000000  /\* ~144 MB, covers UART + GIC *\/ */
#define CONFIG_DEVICEIO_SIZE     0x10000000  /* ~144 MB, covers UART + GIC */
#define CONFIG_LOAD_BASE         0x40400000

#else
#error "No i.MX8 SoC variant selected"
#endif

/* Common definitions */
#define MPID_TO_CLUSTER_ID(mpid)  ((mpid) & ~0xff)

/****************************************************************************
 * Assembly Macros
 ****************************************************************************/

#ifdef __ASSEMBLY__

.macro  get_cpu_id xreg0
  mrs    \xreg0, mpidr_el1
  ubfx   \xreg0, \xreg0, #0, #8
.endm

#endif /* __ASSEMBLY__ */

#endif /* __ARCH_ARM64_INCLUDE_IMX8_CHIP_H */
