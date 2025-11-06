/****************************************************************************
 * arch/arm/src/imx8/imx8_boardinit.h
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

#ifndef __ARCH_ARM_SRC_IMX8_IMX8_BOARDINIT_H
#define __ARCH_ARM_SRC_IMX8_IMX8_BOARDINIT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/** ========= SDK ===================*/
/* void BOARD_InitMemory(void); */
void BOARD_InitDebugConsole(void);
void BOARD_RdcInit(void);
void BOARD_InitBootPins(void);
void BOARD_BootClockRUN(void);

/** ========= Port ===================*/
void imx8_init_mem(void);


#endif /* __ARCH_ARM_SRC_IMX8_IMX8_BOARDINIT_H */
