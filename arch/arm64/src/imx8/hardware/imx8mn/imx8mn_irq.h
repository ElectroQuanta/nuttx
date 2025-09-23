/****************************************************************************
 * arch/arm64/src/imx8/hardware/imx8mn/imx8mn_irq.h
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

#ifndef __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IRQ_H
#define __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
// #include <arch/imx6/chip.h> // NOT REQUIRED for now

#define IMX_IRQ_UART1 58
#define IMX_IRQ_UART2 59
#define IMX_IRQ_UART3 60
#define IMX_IRQ_UART4 61

#endif /* __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IRQ_H */

