/****************************************************************************
 * arch/arm/src/imx8/imx8_clockconfig.h
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

#ifndef __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_BOARD_H
#define __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_BOARD_H


#include "fsl_clock.h"
#include "fsl_component_serial_manager.h"

#define BOARD_NAME        "MIMX8MN-EVK"
#define MANUFACTURER_NAME "NXP"
#define BOARD_DOMAIN_ID   (1)
/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BAUDRATE 115200u
#define BOARD_DEBUG_UART_BASEADDR UART4_BASE
#define BOARD_DEBUG_UART_INSTANCE 4U
#define BOARD_DEBUG_UART_CLK_FREQ                                                           \
    CLOCK_GetPllFreq(kCLOCK_SystemPll1Ctrl) / (CLOCK_GetRootPreDivider(kCLOCK_RootUart4)) / \
        (CLOCK_GetRootPostDivider(kCLOCK_RootUart4)) / 10
#define BOARD_UART_IRQ         UART4_IRQn
#define BOARD_UART_IRQ_HANDLER UART4_IRQHandler

#define GPV5_BASE_ADDR        (0x32500000)
#define FORCE_INCR_OFFSET     (0x4044)
#define FORCE_INCR_BIT_MASK   (0x2)
#define CSU_SA_ADDR           (0x303E0218) /* Secure access register base address. */
#define CSU_SA_NSN_M_BIT_MASK (0x4U)       /* Non-secure access policy indicator bit. */

#define BOARD_GPC_BASEADDR GPC
#define BOARD_MU_IRQ_NUM   MU_M7_IRQn

#define RESOURCE_TABLE_OFFSET (0xFF000)

#endif // __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_BOARD_H
