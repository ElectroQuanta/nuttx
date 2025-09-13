/****************************************************************************
 * arch/arm64/src/imx8/imx8_lowputs.S
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
#include "arm64_macro.inc"

/****************************************************************************
 * Public Symbols
 ****************************************************************************/

    .file    "imx8_lowputc.S"

/****************************************************************************
 * Assembly Macros
 ****************************************************************************/


#ifdef CONFIG_ARCH_CHIP_IMX8_QUADMAX
#define UART_BASE_ADDR_EP 0x5a060000
/* Register offsets */
#define UART_USR          (0x14)    /* Status Register 1 */
#define UART_UTXD          (0x1C)    /* Transmitter Register */
/* Status bits in USR2 register */
#define UARTSTAT_TRDY      (1 << 23) /* Transmitter ready */

#elif defined(CONFIG_ARCH_CHIP_IMX8_MN)

#define UART_BASE_ADDR_EP 0x30890000
/* Register offsets */
#define UART_USR          (0x94)    /* Status Register 1 */
#define UART_UTXD          (0x40)    /* Transmitter Register */
/* Status bits in USR2 register */
#define UARTSTAT_TRDY      (1 << 13) /* Transmitter ready */
#endif


/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/* PL011 UART initialization */

GTEXT(arm64_earlyprintinit)
SECTION_FUNC(text, arm64_earlyprintinit)
    /* Already initialized in bootloader */
    ret


/* i.MX8MN wait LPUART to be ready to transmit
 * rb: register which contains the UART base address
 * rc: scratch register
 */
.macro early_uart_ready xb, c
1:
    ldr   w\c, [\xb, #UART_USR]   /* Load USR1 status register */
    tst   w\c, #UARTSTAT_TRDY      /* Check Transmitter Ready bit */
    beq   1b                       /* Wait for the UART to be ready */
.endm

/* i.MX8MN LPUART transmit character
 * rb: register which contains the UART base address
 * rt: register which contains the character to transmit */
.macro early_uart_transmit xb, wt
    str   \wt, [\xb, #UART_UTXD]   /* Write to Transmitter Register */
.endm

/*
 * Print a character on the UART - this function is called by C
 * x0: character to print
 */
GTEXT(arm64_lowputc)
SECTION_FUNC(text, arm64_lowputc)
    ldr   x15, =UART_BASE_ADDR_EP
    early_uart_ready x15, 2
    early_uart_transmit x15, w0
    ret
