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

#ifndef __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_SYSTEM_MIMX8MN6_CM7_H
#define __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_SYSTEM_MIMX8MN6_CM7_H


/* i.MX8MN Definitions */
#ifndef DISABLE_WDOG
#define DISABLE_WDOG 1
#endif
/* Define clock source values */
#define CPU_XTAL_SOSC_CLK_24MHZ 24000000u /* Value of the external System Oscillator Clock(SOSC) frequency in Hz */
#define CLK_PAD_CLK 0u                    /* The value could be changed according to the  actual usage */
#define DEFAULT_SYSTEM_CLOCK 600000000u   /* Default System clock value */

#endif // __ARCH_ARM_SRC_IMX8_HARDWARE_IMX8MN_SYSTEM_MIMX8MN6_CM7_H
