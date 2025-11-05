/****************************************************************************
 * arch/arm/src/imx8/imx8_rdc.h
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

#ifndef __ARCH_ARM_SRC_IMX8_IMX8_RDC_H
#define __ARCH_ARM_SRC_IMX8_IMX8_RDC_H

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

#define RDC_STAT_DID_MASK                        (0xFU)
#define RDC_STAT_DID_SHIFT                       (0U)


/*!
 * @brief Structure for the RDC mapping
 *
 * Defines the structure for the RDC resource collections.
 */

typedef enum _rdc_master {
  kRDC_Master_A53 = 0U,           /**< ARM Cortex-A53 RDC Master */
  kRDC_Master_M7 = 1U,            /**< ARM Cortex-M7 RDC Master */
  kRDC_Reserved0 = 2U,            /**< Reserved */
  kRDC_Master_SDMA3_PERIPH = 3U,  /**< SDMA3 PERIPHERAL RDC Master */
  kRDC_Reserved1 = 4U,            /**< Reserved */
  kRDC_Master_LCDIF = 5U,         /**< LCDIF RDC Master */
  kRDC_Master_ISI = 6U,           /**< ISI PORT RDC Master */
  kRDC_Master_SDMA3_BURST = 7U,   /**< SDMA3 BURST RDC Master */
  kRDC_Master_Coresight = 8U,     /**< CORESIGHT RDC Master */
  kRDC_Master_DAP = 9U,           /**< DAP RDC Master */
  kRDC_Master_CAAM = 10U,         /**< CAAM RDC Master */
  kRDC_Master_SDMA1_PERIPH = 11U, /**< SDMA1 PERIPHERAL RDC Master */
  kRDC_Master_SDMA1_BURST = 12U,  /**< SDMA1 BURST RDC Master */
  kRDC_Master_APBHDMA = 13U,      /**< APBH DMA RDC Master */
  kRDC_Master_NAND = 14U,         /**< RAW NAND RDC Master */
  kRDC_Master_USDHC1 = 15U,       /**< USDHC1 RDC Master */
  kRDC_Master_USDHC2 = 16U,       /**< USDHC2 RDC Master */
  kRDC_Master_USDHC3 = 17U,       /**< USDHC3 RDC Master */
  kRDC_Master_GPU = 18U,          /**< GPU RDC Master */
  kRDC_Master_USB1 = 19U,         /**< USB1 RDC Master */
  kRDC_Reserved2 = 20U,           /**< Reserved */
  kRDC_Master_TESTPORT = 21U,     /**< TESTPORT RDC Master */
  kRDC_Master_ENET1TX = 22U,      /**< ENET1 TX RDC Master */
  kRDC_Master_ENET1RX = 23U,      /**< ENET1 RX RDC Master */
  kRDC_Master_SDMA2_PERIPH = 24U, /**< SDMA2 PERIPH RDC Master */
  kRDC_Master_SDMA2_BURST = 24U,  /**< SDMA2 BURST RDC Master */
  kRDC_Master_SDMA2_SPBA2 = 24U,  /**< SDMA2 to SPBA2 RDC Master */
  kRDC_Master_SDMA3_SPBA2 = 25U,  /**< SDMA3 to SPBA2 RDC Master */
  kRDC_Master_SDMA1_SPBA1 = 26U,  /**< SDMA1 to SPBA1 RDC Master */
} rdc_master_t;


/*!
 * @addtogroup RDC_Peripheral_Access_Layer RDC Peripheral Access Layer
 * @{
 */

/** RDC - Size of Registers Arrays */
#define RDC_MDA_COUNT                             27u
#define RDC_PDAP_COUNT                            118u
#define RDC_MR_COUNT                              52u

/** RDC - Register Layout Typedef */
typedef struct {
  __I  uint32_t VIR;                               /**< Version Information, offset: 0x0 */
       uint8_t RESERVED_0[32];
  __IO uint32_t STAT;                              /**< Status, offset: 0x24 */
  __IO uint32_t INTCTRL;                           /**< Interrupt and Control, offset: 0x28 */
  __IO uint32_t INTSTAT;                           /**< Interrupt Status, offset: 0x2C */
       uint8_t RESERVED_1[464];
  __IO uint32_t MDA[RDC_MDA_COUNT];                /**< Master Domain Assignment, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_2[404];
  __IO uint32_t PDAP[RDC_PDAP_COUNT];              /**< Peripheral Domain Access Permissions, array offset: 0x400, array step: 0x4 */
       uint8_t RESERVED_3[552];
  struct {                                         /* offset: 0x800, array step: 0x10 */
    __IO uint32_t MRSA;                              /**< Memory Region Start Address, array offset: 0x800, array step: 0x10 */
    __IO uint32_t MREA;                              /**< Memory Region End Address, array offset: 0x804, array step: 0x10 */
    __IO uint32_t MRC;                               /**< Memory Region Control, array offset: 0x808, array step: 0x10 */
    __IO uint32_t MRVS;                              /**< Memory Region Violation Status, array offset: 0x80C, array step: 0x10 */
  } MR[RDC_MR_COUNT];
} RDC_Type;

typedef enum _rdc_periph {
  kRDC_Periph_GPIO1 = 0U,           /**< GPIO1 RDC Peripheral */
  kRDC_Periph_GPIO2 = 1U,           /**< GPIO2 RDC Peripheral */
  kRDC_Periph_GPIO3 = 2U,           /**< GPIO3 RDC Peripheral */
  kRDC_Periph_GPIO4 = 3U,           /**< GPIO4 RDC Peripheral */
  kRDC_Periph_GPIO5 = 4U,           /**< GPIO5 RDC Peripheral */
  kRDC_Periph_ANA_TSENSOR = 6U,     /**< ANA_TSENSOR RDC Peripheral */
  kRDC_Periph_ANA_OSC = 7U,         /**< ANA_OSC RDC Peripheral */
  kRDC_Periph_WDOG1 = 8U,           /**< WDOG1 RDC Peripheral */
  kRDC_Periph_WDOG2 = 9U,           /**< WDOG2 RDC Peripheral */
  kRDC_Periph_WDOG3 = 10U,          /**< WDOG3 RDC Peripheral */
  kRDC_Periph_SDMA3 = 11U,          /**< SDMA3 RDC Peripheral */
  kRDC_Periph_SDMA2 = 12U,          /**< SDMA2 RDC Peripheral */
  kRDC_Periph_GPT1 = 13U,           /**< GPT1 RDC Peripheral */
  kRDC_Periph_GPT2 = 14U,           /**< GPT2 RDC Peripheral */
  kRDC_Periph_GPT3 = 15U,           /**< GPT3 RDC Peripheral */
  kRDC_Periph_ROMCP = 17U,          /**< ROMCP RDC Peripheral */
  kRDC_Periph_IOMUXC = 19U,         /**< IOMUXC RDC Peripheral */
  kRDC_Periph_IOMUXC_GPR = 20U,     /**< IOMUXC_GPR RDC Peripheral */
  kRDC_Periph_OCOTP_CTRL = 21U,     /**< OCOTP_CTRL RDC Peripheral */
  kRDC_Periph_ANA_PLL = 22U,        /**< ANA_PLL RDC Peripheral */
  kRDC_Periph_SNVS_HP = 23U,        /**< SNVS_HP GPR RDC Peripheral */
  kRDC_Periph_CCM = 24U,            /**< CCM RDC Peripheral */
  kRDC_Periph_SRC = 25U,            /**< SRC RDC Peripheral */
  kRDC_Periph_GPC = 26U,            /**< GPC RDC Peripheral */
  kRDC_Periph_SEMAPHORE1 = 27U,     /**< SEMAPHORE1 RDC Peripheral */
  kRDC_Periph_SEMAPHORE2 = 28U,     /**< SEMAPHORE2 RDC Peripheral */
  kRDC_Periph_RDC = 29U,            /**< RDC RDC Peripheral */
  kRDC_Periph_CSU = 30U,            /**< CSU RDC Peripheral */
  kRDC_Periph_LCDIF = 32U,          /**< LCDIF RDC Peripheral */
  kRDC_Periph_MIPI_DSI = 33U,       /**< MIPI_DSI RDC Peripheral */
  kRDC_Periph_ISI = 34U,            /**< ISI RDC Peripheral */
  kRDC_Periph_MIPI_CSI = 35U,       /**< MIPI_CSI RDC Peripheral */
  kRDC_Periph_USB1 = 36U,           /**< USB1 RDC Peripheral */
  kRDC_Periph_PWM1 = 38U,           /**< PWM1 RDC Peripheral */
  kRDC_Periph_PWM2 = 39U,           /**< PWM2 RDC Peripheral */
  kRDC_Periph_PWM3 = 40U,           /**< PWM3 RDC Peripheral */
  kRDC_Periph_PWM4 = 41U,           /**< PWM4 RDC Peripheral */
  kRDC_Periph_SYS_COUNTER_RD = 42U, /**< System counter read RDC Peripheral */
  kRDC_Periph_SYS_COUNTER_CMP =
      43U, /**< System counter compare RDC Peripheral */
  kRDC_Periph_SYS_COUNTER_CTRL =
      44U,                         /**< System counter control RDC Peripheral */
  kRDC_Periph_GPT6 = 46U,          /**< GPT6 RDC Peripheral */
  kRDC_Periph_GPT5 = 47U,          /**< GPT5 RDC Peripheral */
  kRDC_Periph_GPT4 = 48U,          /**< GPT4 RDC Peripheral */
  kRDC_Periph_TZASC = 56U,         /**< TZASC RDC Peripheral */
  kRDC_Periph_PERFMON1 = 60U,      /**< PERFMON1 RDC Peripheral */
  kRDC_Periph_PERFMON2 = 61U,      /**< PERFMON2 RDC Peripheral */
  kRDC_Periph_PLATFORM_CTRL = 62U, /**< PLATFORM_CTRL RDC Peripheral */
  kRDC_Periph_QOSC = 63U,          /**< QOSC RDC Peripheral */
  kRDC_Periph_I2C1 = 66U,          /**< I2C1 RDC Peripheral */
  kRDC_Periph_I2C2 = 67U,          /**< I2C2 RDC Peripheral */
  kRDC_Periph_I2C3 = 68U,          /**< I2C3 RDC Peripheral */
  kRDC_Periph_I2C4 = 69U,          /**< I2C4 RDC Peripheral */
  kRDC_Periph_UART4 = 70U,         /**< UART4 RDC Peripheral */
  kRDC_Periph_MU_A = 74U,          /**< MU_A RDC Peripheral */
  kRDC_Periph_MU_B = 75U,          /**< MU_B RDC Peripheral */
  kRDC_Periph_SEMAPHORE_HS = 76U,  /**< SEMAPHORE_HS RDC Peripheral */
  kRDC_Periph_SAI2 = 79U,          /**< SAI2 RDC Peripheral */
  kRDC_Periph_SAI3 = 80U,          /**< SAI3 RDC Peripheral */
  kRDC_Periph_SAI5 = 82U,          /**< SAI5 RDC Peripheral */
  kRDC_Periph_SAI6 = 83U,          /**< SAI6 RDC Peripheral */
  kRDC_Periph_USDHC1 = 84U,        /**< USDHC1 RDC Peripheral */
  kRDC_Periph_USDHC2 = 85U,        /**< USDHC2 RDC Peripheral */
  kRDC_Periph_USDHC3 = 86U,        /**< USDHC3 RDC Peripheral */
  kRDC_Periph_SAI7 = 87U,          /**< SAI7 RDC Peripheral */
  kRDC_Periph_SPBA2 = 90U,         /**< SPBA2 RDC Peripheral */
  kRDC_Periph_QSPI = 91U,          /**< QSPI RDC Peripheral */
  kRDC_Periph_SDMA1 = 93U,         /**< SDMA1 RDC Peripheral */
  kRDC_Periph_ENET1 = 94U,         /**< ENET1 RDC Peripheral */
  kRDC_Periph_SPDIF1 = 97U,        /**< SPDIF1 RDC Peripheral */
  kRDC_Periph_ECSPI1 = 98U,        /**< ECSPI1 RDC Peripheral */
  kRDC_Periph_ECSPI2 = 99U,        /**< ECSPI2 RDC Peripheral */
  kRDC_Periph_ECSPI3 = 100U,       /**< ECSPI3 RDC Peripheral */
  kRDC_Periph_MICFIL = 101U,       /**< MICFIL RDC Peripheral */
  kRDC_Periph_UART1 = 102U,        /**< UART1 RDC Peripheral */
  kRDC_Periph_UART3 = 104U,        /**< UART3 RDC Peripheral */
  kRDC_Periph_UART2 = 105U,        /**< UART2 RDC Peripheral */
  kRDC_Periph_ASRC = 107U,         /**< ASRC RDC Peripheral */
  kRDC_Periph_SPBA1 = 111U,        /**< SPBA1 RDC Peripheral */
  kRDC_Periph_MODULE_EN_GLB0 = 112U, /**< MODULE_EN_GLB0 RDC Peripheral */
  kRDC_Periph_MODULE_EN_GLB1 = 113U, /**< MODULE_EN_GLB1 RDC Peripheral */
  kRDC_Periph_CAAM = 114U,           /**< CAAM RDC Peripheral */
} rdc_periph_t;


/*!
 * @brief Master domain assignment.
 */
typedef struct _rdc_domain_assignment
{
    uint32_t domainId : 2U; /*!< Domain ID.                  */
    uint32_t : 29U;         /*!< Reserved.                   */
    uint32_t lock : 1U;     /*!< Lock the domain assignment. */
} rdc_domain_assignment_t;

#define RDC_BASE                                 (0x303D0000u)
#define RDC                                      ((RDC_Type *)RDC_BASE)


/*!
 * @brief Gets the domain ID of the current bus master.
 *
 * This function returns the domain ID of the current bus master.
 *
 * @param base RDC peripheral base address.
 * @return Domain ID of current bus master.
 */
static inline uint8_t RDC_GetCurrentMasterDomainId(RDC_Type *base)
{
    return (uint8_t)((base->STAT & RDC_STAT_DID_MASK) >> RDC_STAT_DID_SHIFT);
}


static inline uint8_t RDC_GetPeriphAccessPolicy(RDC_Type *base, rdc_periph_t periph, uint8_t domainId)
{
    assert((uint32_t)periph < RDC_PDAP_COUNT);

    return (uint8_t)((base->PDAP[periph] >> (domainId * 2U)) & 0x03U);
}

/*!
 * @brief Set master domain assignment
 *
 * @param base RDC peripheral base address.
 * @param master Which master to set.
 * @param domainAssignment Pointer to the assignment.
 */
void RDC_SetMasterDomainAssignment(RDC_Type *base,
                                   rdc_master_t master,
                                   const rdc_domain_assignment_t *domainAssignment);

/**
 * @brief Initialize the RDC
 */
void rdc_init(void);

#endif //  __ARCH_ARM_SRC_IMX8_IMX8_RDC_H
