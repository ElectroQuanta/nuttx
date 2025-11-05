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

#ifndef __ARCH_ARM_SRC_IMX8_IMX8_CLOCKCONFIG_H
#define __ARCH_ARM_SRC_IMX8_IMX8_CLOCKCONFIG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
/* #include "common.h" */
#include "hardware/imx8mn/core_cm7.h"
#include "hardware/imx8mn/MIMX8MN6_cm7_COMMON.h"
#include "hardware/imx8mn/PERI_CCM.h"
#include "hardware/imx8mn/fsl_clock.h"

/* ------- devices/MIMX8MN6/drivers/fsl_clock.c */
#define FracPLL_GNRL_CTL_Offset  (0U)
#define FracPLL_FDIV_CTL0_Offset (4U)
#define FracPLL_FDIV_CTL1_Offset (8U)

#define IntegerPLL_GNRL_CTL_Offset (0U)
#define IntegerPLL_DIV_CTL_Offset (4U)
/* ------------------------------------------ */

/*!
 * @name CCM Gate Control
 * @{
 */

/*!
 * lockrief Set PLL or CCGR gate control
 *
 * @param ccmGate Gate control (see @ref clock_pll_gate_t and @ref clock_ip_name_t enumeration)
 * @param control Gate control value (see @ref clock_gate_value_t)
 */
static inline void imx8_clock_ControlGate(uintptr_t ccmGate, clock_gate_value_t control)
{
    CCM_REG(ccmGate) = (uint32_t)control;
}

void imx8_clock_enable(clock_ip_name_t ccmGate);

#endif //__ARCH_ARM_SRC_IMX8_IMX8_CLOCKCONFIG_H
