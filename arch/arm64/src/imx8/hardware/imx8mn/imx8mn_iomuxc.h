/****************************************************************************
 * arch/arm64/src/imx8/hardware/imx8mn/imx8mn_iomuxc.h
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

#ifndef __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IMX8MN_IOMUXC_H
#define __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IMX8MN_IOMUXC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>
#include <stdint.h>
#include "imx8mn_memorymap.h"
//#include <arch/arm64/src/common/arm64_arch.h>
#include "arm64_arch.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Mux, PAD, and DAISY Register Offsets *****************************************************/
/* UART Mux registers (MUX_CTL) */
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART1_RXD (IMX_IOMUXC_PBASE + 0x0234)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART1_TXD (IMX_IOMUXC_PBASE + 0x0238)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART2_RXD (IMX_IOMUXC_PBASE + 0x023C)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART2_TXD (IMX_IOMUXC_PBASE + 0x0240)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART3_RXD (IMX_IOMUXC_PBASE + 0x0244)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART3_TXD (IMX_IOMUXC_PBASE + 0x0248)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART4_RXD (IMX_IOMUXC_PBASE + 0x024C)
#define IMX_IOMUXC_SW_MUX_CTL_PAD_UART4_TXD (IMX_IOMUXC_PBASE + 0x0250)

/* UART Daisy chain registers (_SELECT_INPUT) */
#define IMX_IOMUXC_UART1_RTS_B_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x04F0)
#define IMX_IOMUXC_UART1_RX_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x04F4)
#define IMX_IOMUXC_UART2_RTS_B_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x04F8)
#define IMX_IOMUXC_UART2_RX_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x04FC)
#define IMX_IOMUXC_UART3_RTS_B_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x0500)
#define IMX_IOMUXC_UART3_RX_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x0504)
#define IMX_IOMUXC_UART4_RTS_B_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x0508)
#define IMX_IOMUXC_UART4_RX_SELECT_INPUT (IMX_IOMUXC_PBASE + 0x050C)

/* UART PAD registers (PAD_CTL) */
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART1_RXD (IMX_IOMUXC_PBASE + 0x049C)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART1_TXD (IMX_IOMUXC_PBASE + 0x04A0)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART2_RXD (IMX_IOMUXC_PBASE + 0x04A4)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART2_TXD (IMX_IOMUXC_PBASE + 0x04A8)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART3_RXD (IMX_IOMUXC_PBASE + 0x04AC)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART3_TXD (IMX_IOMUXC_PBASE + 0x04B0)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART4_RXD (IMX_IOMUXC_PBASE + 0x03B4)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_UART4_TXD (IMX_IOMUXC_PBASE + 0x04B8)

#define IMX_IOMUXC_SW_MUX_CTL_SION 4 /* SW Enable Bit */

#define IMX_IOMUXC_SW_MUX_CTL_UART1_RXD_ALT0 (0b000) /* UART1_RX */
#define IMX_IOMUXC_SW_MUX_CTL_UART1_RXD_ALT1 (0b001)
#define IMX_IOMUXC_SW_MUX_CTL_UART1_RXD_ALT5 (0b101)

#define IMX_IOMUXC_SW_MUX_CTL_UART1_TXD_ALT0 (0b000) /* UART1_TX */
#define IMX_IOMUXC_SW_MUX_CTL_UART1_TXD_ALT1 (0b001)
#define IMX_IOMUXC_SW_MUX_CTL_UART1_TXD_ALT5 (0b101)


#define IMX_IOMUXC_SW_MUX_CTL_UART2_RXD_ALT0 (0b000) /* UART2_RX */
#define IMX_IOMUXC_SW_MUX_CTL_UART2_TXD_ALT0 (0b000) /* UART2_TX */
#define IMX_IOMUXC_SW_MUX_CTL_UART3_RXD_ALT0 (0b000) /* UART3_RX */
#define IMX_IOMUXC_SW_MUX_CTL_UART3_TXD_ALT0 (0b000) /* UART3_TX */
#define IMX_IOMUXC_SW_MUX_CTL_UART4_RXD_ALT0 (0b000) /* UART4_RX */
#define IMX_IOMUXC_SW_MUX_CTL_UART4_TXD_ALT0 (0b000) /* UART4_TX */

#define IMX_IOMUXC_UART1_RX_DAISY_ALT0 (0b000) 
#define IMX_IOMUXC_UART2_RX_DAISY_ALT0 (0b000) 
#define IMX_IOMUXC_UART3_RX_DAISY_ALT0 (0b010)
#define IMX_IOMUXC_UART4_RX_DAISY_ALT0 (0b010)

#define IMX_IOMUXC_SW_PAD_CTL_PAD_PE (1 << 8) // Pull resistors enable
#define IMX_IOMUXC_SW_PAD_CTL_PAD_IS (1 << 7) // Hysteresis 
#define IMX_IOMUXC_SW_PAD_CTL_PAD_PUE (1 << 6) // pull-up(1), pull-down(0)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_ODE (1 << 5) // Open drain Enable
#define IMX_IOMUXC_SW_PAD_CTL_PAD_SR (1 << 4)  //  Slew rate (0 slow, 1 fast)
#define IMX_IOMUXC_SW_PAD_CTL_PAD_DSE_X1 (0b000)  //  Drive strength X1
#define IMX_IOMUXC_SW_PAD_CTL_PAD_DSE_X4 (0b010)  //  Drive strength X4
#define IMX_IOMUXC_SW_PAD_CTL_PAD_DSE_X2 (0b100)  //  Drive strength X2
#define IMX_IOMUXC_SW_PAD_CTL_PAD_DSE_X6 (0b110)  //  Drive strength X6


/* CCM Register Bit Definitions *********************************************/

/* CCM Control Register */


static inline void iomuxc_config_mux(unsigned long addr, uint32_t mux_cfg) {
  uint32_t reg = getreg32(addr);
  reg &= ~(0b10111); /* clear domain 0’s bits [4:2-0] */
  reg |= mux_cfg;    /* set new mux config (ignore SION bit) */
  putreg32(reg, addr);
}

static inline void iomuxc_config_daisy(unsigned long addr, uint32_t daisy_cfg) {
  uint32_t reg = getreg32(addr);
  reg &= ~(0b111); /* clear domain 0’s bits [2-0] */
  reg |= daisy_cfg;    /* set new mux config (ignore SION bit) */
  putreg32(reg, addr);
}

static inline void iomuxc_config_pad(unsigned long addr, uint32_t pad_cfg) {
  uint32_t reg = getreg32(addr);
  reg &= ~(0x1ff); /* clear domain 0’s bits [8-0] */
  reg |= pad_cfg;    /* set new mux config */
  putreg32(reg, addr);
}


#endif /* __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IMX8MN_IOMUXC_H */
