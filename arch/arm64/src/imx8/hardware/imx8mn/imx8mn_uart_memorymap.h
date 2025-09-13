/****************************************************************************
 * arch/arm64/src/imx8/hardware/imx8mn/imx8mn_uart_memorymap.h
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

/* Reference:
 *   "i.MX 6Dual/6Quad ApplicationsProcessor Reference Manual",
 *   Document Number IMX6DQRM, Rev. 3, 07/2015, FreeScale.
 */

#ifndef __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_UART_MEMORYMAP_H
#define __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_UART_MEMORYMAP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
// #include <arch/imx6/chip.h> // NOT REQUIRED for now

/* i.MX6 Virtual (mapped) Memory Map
 *
 * board_memorymap.h contains special mappings that are needed when a ROM
 * memory map is used.  It is included in this odd location because it
 * depends on some the virtual address definitions provided above.
 * The following include is a symbolic link to board's memory map
 */

#include <arch/board/board_memorymap.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Overview *****************************************************************
 *
 *  i.MX6 Physical (unmapped) Memory Map
 *  - i.MX6 System 1MB PSECTIONS
 *  - i.MX6 DMA PSECTION Offsets
 *  - i.MX6 OCRAM PSECTION Offsets
 *  - i.MX6 ARM MP PSECTION Offsets
 *  - i.MX6 PCIE PSECTION Offsets
 *  - i.MX6 AIPS-1 PSECTION Offsets
 *  - i.MX6 AIPS-2 PSECTION Offsets
 *  - i.MX6 DAP AIPS-2 PSECTION Offsets
 *  - i.MX6 SATA PSECTION Offsets
 *  - i.MX6 DMA Physical Base Addresses
 *  - i.MX6 OCRAM Physical Base Addresses
 *  - i.MX6 ARM MP Physical Base Addresses
 *  - i.MX6 PCIE Physical Base Addresses
 *  - i.MX6 AIPS-1 Physical Base Addresses
 *  - i.MX6 AIPS-2 Physical Base Addresses
 *  - i.MX6 DAP AIPS-2 Physical Base Addresses
 *  - i.MX6 SATA Physical Base Addresses
 *  Sizes of memory regions in bytes
 *  Sizes of memory regions in sections
 *  Section MMU Flags
 *  i.MX6 Virtual (mapped) Memory Map
 *  - i.MX6 DMA Virtual Base Addresses
 *  - i.MX6 OCRAM Virtual Base Addresses
 *  - i.MX6 ARM MP Virtual Base Addresses
 *  - i.MX6 PCIE Virtual Base Addresses
 *  - i.MX6 AIPS-1 Virtual Base Addresses
 *  - i.MX6 AIPS-2 Virtual Base Addresses
 *  - i.MX6 DAP AIPS-2 Virtual Base Addresses
 *  - i.MX6 SATA Virtual Base Addresses
 *  - NuttX virtual base address
 *  MMU Page Table Location
 *  Page table start addresses
 *  Base address of the interrupt vector table
 *
 ****************************************************************************/

/* i.MX6 Physical (unmapped) Memory Map *************************************/

#define IMX_AIPS1_PSECTION       0x30000000  /* 30000000-303fffff   4 MB Peripheral IPs via AIPS-1 */
#define IMX_AIPS2_PSECTION       0x30400000  /* 30400000-307fffff   4 MB Peripheral IPs via AIPS-2 */
#define IMX_AIPS3_PSECTION       0x30800000  /* 30800000-307fffff   4 MB Peripheral IPs via AIPS-3 */
#define IMX_AIPS4_PSECTION       0x32C00000  /* 32C00000-32ffffff   4 MB Peripheral IPs via AIPS-4 */

/* i.MX6 AIPS-2 PSECTION Offsets */
#define IMX_UART1_OFFSET         0x00060000  /* 00060000 0000ffff UART1 64 KB */
#define IMX_UART2_OFFSET         0x00090000  /* 00090000 0009ffff UART2 64 KB */
#define IMX_UART3_OFFSET         0x00080000  /* 00080000 0008ffff UART3 64 KB */
#define IMX_UART4_OFFSET         0x00260000  /* 00260000 0026ffff UART4 64 KB */

/* i.MX8 AIPS-3 Physical Base Addresses */
#define IMX_UART1_PBASE          (IMX_AIPS3_PSECTION+IMX_UART1_OFFSET)
#define IMX_UART2_PBASE          (IMX_AIPS3_PSECTION+IMX_UART2_OFFSET)
#define IMX_UART3_PBASE          (IMX_AIPS2_PSECTION+IMX_UART3_OFFSET)
#define IMX_UART4_PBASE          (IMX_AIPS2_PSECTION+IMX_UART4_OFFSET)

#  define IMX_AIPS1_VSECTION     IMX_AIPS1_PSECTION        /*   1 MB Peripheral IPs via AIPS-1 */
#  define IMX_AIPS2_VSECTION     IMX_AIPS2_PSECTION        /*   1 MB Peripheral IPs via AIPS-2 */
#  define IMX_AIPS3_VSECTION     IMX_AIPS3_PSECTION        /*   1 MB Peripheral IPs via AIPS-2 */
#  define IMX_AIPS4_VSECTION     IMX_AIPS4_PSECTION        /*   1 MB Peripheral IPs via AIPS-2 */

#define IMX_UART1_VBASE          (IMX_AIPS3_VSECTION+IMX_UART1_OFFSET)
#define IMX_UART2_VBASE          (IMX_AIPS3_VSECTION+IMX_UART2_OFFSET)
#define IMX_UART3_VBASE          (IMX_AIPS3_VSECTION+IMX_UART3_OFFSET)
#define IMX_UART4_VBASE          (IMX_AIPS3_VSECTION+IMX_UART4_OFFSET)


#endif /* __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_UART_MEMORYMAP_H */
