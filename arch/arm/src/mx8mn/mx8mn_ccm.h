/****************************************************************************
 * arch/arm/src/mx8mn/mx8mn_ccm.h
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

#ifndef __ARCH_ARM_SRC_MX8MN_MX8MN_CCM_H
#define __ARCH_ARM_SRC_MX8MN_MX8MN_CCM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>

#include "hardware/mx8mn_ccm.h"

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: mx8mn_ccm_get_root_clock
 *
 * Description:
 *   Retrieve the root clock frequency.
 *
 ****************************************************************************/

uint32_t mx8mn_ccm_get_root_clock(int clk_root_index);

/****************************************************************************
 * Name: mx8mn_ccm_get_clock
 *
 * Description:
 *   Retrieve the clock frequency.
 *
 ****************************************************************************/

uint32_t mx8mn_ccm_get_clock(int clk_index);

/****************************************************************************
 * Name: mx8mn_ccm_configure_clock
 *
 * Description:
 *   Configure a clock by setting its root clock source
 *   and its dividers.
 *
 ****************************************************************************/

int mx8mn_ccm_configure_clock(int clk_index,
                              int clk_root_src,
                              uint32_t pre_div,
                              uint32_t post_div);

/****************************************************************************
 * Name: mx8mn_ccm_enable_clock
 *
 * Description:
 *   Enable a clock.
 *
 ****************************************************************************/

void mx8mn_ccm_enable_clock(int clk_index);

/****************************************************************************
 * Name: mx8mn_ccm_gate_clock
 *
 * Description:
 *   Apply desired gating configuration to the clock.
 *
 ****************************************************************************/

void mx8mn_ccm_gate_clock(int gate_index, uint32_t value);

/****************************************************************************
 * Name: mx8mn_ccm_gate_pll
 *
 * Description:
 *   Apply desired gating configuration to the PLL.
 *
 ****************************************************************************/

void mx8mn_ccm_gate_pll(int pll_index, uint32_t value);

/****************************************************************************
 * Name: mx8mn_ccm_configure_pll
 *
 * Description:
 *   Configure a PLL by settings its divider and DSM (if any).
 *
 ****************************************************************************/

void mx8mn_ccm_configure_pll(int pll_index,
                             uint32_t main_div,
                             uint32_t pre_div,
                             uint32_t post_div,
                             uint32_t dsm);

#endif /* __ARCH_ARM_SRC_MX8MN_MX8MN_CCM_H */
