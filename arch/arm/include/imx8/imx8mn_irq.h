/****************************************************************************
 * arch/arm/include/imx8/imx8mn_irq.h
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

/* This file should never be included directly but, rather,
 * only indirectly through nuttx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_IMX8_IMX8MN_IRQ_H
#define __ARCH_ARM_INCLUDE_IMX8_IMX8MN_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Prototypes
 ****************************************************************************/

/* External interrupts (priority levels >= 256) *****************************/

#define IMX8_IRQ_EDMA0_16     (IMX8_IRQ_EXTINT + 0)   /* eDMA Channel 0/16 Transfer Complete */
#define IMX8_IRQ_EDMA1_17     (IMX8_IRQ_EXTINT + 1)   /* eDMA Channel 1/17 Transfer Complete */
#define IMX8_IRQ_EDMA2_18     (IMX8_IRQ_EXTINT + 2)   /* eDMA Channel 2/18 Transfer Complete */
#define IMX8_IRQ_EDMA3_19     (IMX8_IRQ_EXTINT + 3)   /* eDMA Channel 3/19 Transfer Complete */
#define IMX8_IRQ_EDMA4_20     (IMX8_IRQ_EXTINT + 4)   /* eDMA Channel 4/20 Transfer Complete */
#define IMX8_IRQ_EDMA5_21     (IMX8_IRQ_EXTINT + 5)   /* eDMA Channel 5/21 Transfer Complete */
#define IMX8_IRQ_EDMA6_22     (IMX8_IRQ_EXTINT + 6)   /* eDMA Channel 6/22 Transfer Complete */
#define IMX8_IRQ_EDMA7_23     (IMX8_IRQ_EXTINT + 7)   /* eDMA Channel 7/23 Transfer Complete */
#define IMX8_IRQ_EDMA8_24     (IMX8_IRQ_EXTINT + 8)   /* eDMA Channel 8/24 Transfer Complete */
#define IMX8_IRQ_EDMA9_25     (IMX8_IRQ_EXTINT + 9)   /* eDMA Channel 9/25 Transfer Complete */
#define IMX8_IRQ_EDMA10_26    (IMX8_IRQ_EXTINT + 10)  /* eDMA Channel 10/26 Transfer Complete */
#define IMX8_IRQ_EDMA11_27    (IMX8_IRQ_EXTINT + 11)  /* eDMA Channel 11/27 Transfer Complete */
#define IMX8_IRQ_EDMA12_28    (IMX8_IRQ_EXTINT + 12)  /* eDMA Channel 12/28 Transfer Complete */
#define IMX8_IRQ_EDMA13_29    (IMX8_IRQ_EXTINT + 13)  /* eDMA Channel 13/29 Transfer Complete */
#define IMX8_IRQ_EDMA14_30    (IMX8_IRQ_EXTINT + 14)  /* eDMA Channel 14/30 Transfer Complete */
#define IMX8_IRQ_EDMA15_31    (IMX8_IRQ_EXTINT + 15)  /* eDMA Channel 15/31 Transfer Complete */
#define IMX8_IRQ_EDMA_ERROR   (IMX8_IRQ_EXTINT + 16)  /* Error Interrupt, Channels 0-15 / 16-31 */
#define IMX8_IRQ_CM70         (IMX8_IRQ_EXTINT + 17)  /* CTI trigger outputs (internal: CTIIRQ[0]) */
#define IMX8_IRQ_CM71         (IMX8_IRQ_EXTINT + 18)  /* CTI trigger outputs (internal: CTIIRQ[1]) */
#define IMX8_IRQ_CM7CP        (IMX8_IRQ_EXTINT + 19)  /* CorePlatform exception IRQ */
#define IMX8_IRQ_LPUART1      (IMX8_IRQ_EXTINT + 20)  /* UART1 TX/RX interrupt */
#define IMX8_IRQ_LPUART2      (IMX8_IRQ_EXTINT + 21)  /* UART2 TX/RX interrupt */
#define IMX8_IRQ_LPUART3      (IMX8_IRQ_EXTINT + 22)  /* UART3 TX/RX interrupt */
#define IMX8_IRQ_LPUART4      (IMX8_IRQ_EXTINT + 23)  /* UART4 TX/RX interrupt */
#define IMX8_IRQ_LPUART5      (IMX8_IRQ_EXTINT + 24)  /* UART5 TX/RX interrupt */
#define IMX8_IRQ_LPUART6      (IMX8_IRQ_EXTINT + 25)  /* UART6 TX/RX interrupt */
#define IMX8_IRQ_LPUART7      (IMX8_IRQ_EXTINT + 26)  /* UART7 TX/RX interrupt */
#define IMX8_IRQ_LPUART8      (IMX8_IRQ_EXTINT + 27)  /* UART8 TX/RX interrupt */
#define IMX8_IRQ_LPI2C1       (IMX8_IRQ_EXTINT + 28)  /* I2C1 Interrupt */
#define IMX8_IRQ_LPI2C2       (IMX8_IRQ_EXTINT + 29)  /* I2C2 Interrupt */
#define IMX8_IRQ_LPI2C3       (IMX8_IRQ_EXTINT + 30)  /* I2C3 Interrupt */
#define IMX8_IRQ_LPI2C4       (IMX8_IRQ_EXTINT + 31)  /* I2C4 Interrupt */
#define IMX8_IRQ_LPSPI1       (IMX8_IRQ_EXTINT + 32)  /* LPSPI1 interrupt */
#define IMX8_IRQ_LPSPI2       (IMX8_IRQ_EXTINT + 33)  /* LPSPI2 interrupt */
#define IMX8_IRQ_LPSPI3       (IMX8_IRQ_EXTINT + 34)  /* LPSPI3 interrupt */
#define IMX8_IRQ_LPSPI4       (IMX8_IRQ_EXTINT + 35)  /* LPSPI4 interrupt */
#define IMX8_IRQ_CAN1         (IMX8_IRQ_EXTINT + 36)  /* CAN1 interrupt */
#define IMX8_IRQ_CAN2         (IMX8_IRQ_EXTINT + 37)  /* CAN2 interrupt */
#define IMX8_IRQ_CM7FR        (IMX8_IRQ_EXTINT + 38)  /* FlexRAM address fault */
#define IMX8_IRQ_KPP          (IMX8_IRQ_EXTINT + 39)  /* Keypad Interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 40)  RESERVED */
#define IMX8_IRQ_GPRIRQ       (IMX8_IRQ_EXTINT + 41)  /* Notify cores on exception while boot */

/* RESERVED                    (IMX8_IRQ_EXTINT + 42)  RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 43)  RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 44)  RESERVED */
#define IMX8_IRQ_WDOG2        (IMX8_IRQ_EXTINT + 45)  /* Watchdog Timer reset */
#define IMX8_IRQ_SNVS         (IMX8_IRQ_EXTINT + 46)  /* SNVS Functional Interrupt */
#define IMX8_IRQ_SNVSSEC      (IMX8_IRQ_EXTINT + 47)  /* SNVS Security Interrupt */
#define IMX8_IRQ_SNVSSB       (IMX8_IRQ_EXTINT + 48)  /* ON-OFF short button press */
#define IMX8_IRQ_CSU          (IMX8_IRQ_EXTINT + 49)  /* CSU Interrupt Request 1 */
#define IMX8_IRQ_DCP          (IMX8_IRQ_EXTINT + 50)  /* DCP channel/CRC interrupts (channel != 0) */
#define IMX8_IRQ_DCP0         (IMX8_IRQ_EXTINT + 51)  /* DCP channel 0 interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 52)  RESERVED */
#define IMX8_IRQ_TRNG         (IMX8_IRQ_EXTINT + 53)  /* TRNG Interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 54)  RESERVED */
#define IMX8_IRQ_BEE          (IMX8_IRQ_EXTINT + 55)  /* BEE IRQ */
#define IMX8_IRQ_SAI1         (IMX8_IRQ_EXTINT + 56)  /* SAI1 interrupt (RX/TX) */
#define IMX8_IRQ_SAI2         (IMX8_IRQ_EXTINT + 57)  /* SAI2 interrupt (RX/TX) */
#define IMX8_IRQ_SAI3RX       (IMX8_IRQ_EXTINT + 58)  /* SAI3 RX interrupt (RX/TX) */
#define IMX8_IRQ_SAI3TX       (IMX8_IRQ_EXTINT + 59)  /* SAI3 TX interrupt (RX/TX) */
#define IMX8_IRQ_SPDIF        (IMX8_IRQ_EXTINT + 60)  /* SPDIF interrupt */
#define IMX8_IRQ_PMU          (IMX8_IRQ_EXTINT + 61)  /* Brown-out event 1.1, 2.5 or 3.0 regulators */

/* RESERVED                    (IMX8_IRQ_EXTINT + 62)  RESERVED */
#define IMX8_IRQ_TEMP         (IMX8_IRQ_EXTINT + 63)  /* Temperature Monitor */
#define IMX8_IRQ_TEMPPANIC    (IMX8_IRQ_EXTINT + 64)  /* TempSensor panic */
#define IMX8_IRQ_USBPHY0      (IMX8_IRQ_EXTINT + 65)  /* USBPHY (UTMI0) interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 66)  RESERVED */
#define IMX8_IRQ_ADC1         (IMX8_IRQ_EXTINT + 67)  /* ADC1 interrupt */
#define IMX8_IRQ_ADC2         (IMX8_IRQ_EXTINT + 68)  /* ADC2 interrupt */
#define IMX8_IRQ_DCDC         (IMX8_IRQ_EXTINT + 69)  /* DCDC interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 70)  RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 71)  RESERVED */
#define IMX8_IRQ_GPIO1_0      (IMX8_IRQ_EXTINT + 72)  /* GPIO1 INT0 interrupt */
#define IMX8_IRQ_GPIO1_1      (IMX8_IRQ_EXTINT + 73)  /* GPIO1 INT1 interrupt */
#define IMX8_IRQ_GPIO1_2      (IMX8_IRQ_EXTINT + 74)  /* GPIO1 INT2 interrupt */
#define IMX8_IRQ_GPIO1_3      (IMX8_IRQ_EXTINT + 75)  /* GPIO1 INT3 interrupt */
#define IMX8_IRQ_GPIO1_4      (IMX8_IRQ_EXTINT + 76)  /* GPIO1 INT4 interrupt */
#define IMX8_IRQ_GPIO1_5      (IMX8_IRQ_EXTINT + 77)  /* GPIO1 INT5 interrupt */
#define IMX8_IRQ_GPIO1_6      (IMX8_IRQ_EXTINT + 78)  /* GPIO1 INT6 interrupt */
#define IMX8_IRQ_GPIO1_7      (IMX8_IRQ_EXTINT + 79)  /* GPIO1 INT7 interrupt */
#define IMX8_IRQ_GPIO1_0_15   (IMX8_IRQ_EXTINT + 80)  /* GPIO1 INT0-15 interrupt */
#define IMX8_IRQ_GPIO1_16_31  (IMX8_IRQ_EXTINT + 81)  /* GPIO1 INT16-31 interrupt */
#define IMX8_IRQ_GPIO2_0_15   (IMX8_IRQ_EXTINT + 82)  /* GPIO2 INT0-15 interrupt */
#define IMX8_IRQ_GPIO2_16_31  (IMX8_IRQ_EXTINT + 83)  /* GPIO2 INT16-31 interrupt */
#define IMX8_IRQ_GPIO3_0_15   (IMX8_IRQ_EXTINT + 84)  /* GPIO3 INT0-15 interrupt */
#define IMX8_IRQ_GPIO3_16_31  (IMX8_IRQ_EXTINT + 85)  /* GPIO3 INT16-31 interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 86)  RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 87)  RESERVED */
#define IMX8_IRQ_GPIO5_0_15   (IMX8_IRQ_EXTINT + 88)  /* GPIO5 INT0-15 interrupt */
#define IMX8_IRQ_GPIO5_16_31  (IMX8_IRQ_EXTINT + 89)  /* GPIO5 INT16-31 interrupt */
#define IMX8_IRQ_FLEXIO1      (IMX8_IRQ_EXTINT + 90)  /* FlexIO Interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 91)  RESERVED */
#define IMX8_IRQ_WDOG1        (IMX8_IRQ_EXTINT + 92)  /* Watchdog Timer reset */
#define IMX8_IRQ_RTWDOG       (IMX8_IRQ_EXTINT + 93)  /* Watchdog Timer reset */
#define IMX8_IRQ_EWM          (IMX8_IRQ_EXTINT + 94)  /* EWM interrupt */
#define IMX8_IRQ_CCM_1        (IMX8_IRQ_EXTINT + 95)  /* CCM interrupt 1 */
#define IMX8_IRQ_CCM_2        (IMX8_IRQ_EXTINT + 96)  /* CCM interrupt 2 */
#define IMX8_IRQ_GPC          (IMX8_IRQ_EXTINT + 97)  /* GPC interrupt 1 */
#define IMX8_IRQ_SRC          (IMX8_IRQ_EXTINT + 98)  /* SRC interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 99)  RESERVED */
#define IMX8_IRQ_GPT1         (IMX8_IRQ_EXTINT + 100) /* GPT1 interrupt */
#define IMX8_IRQ_GPT2         (IMX8_IRQ_EXTINT + 101) /* GPT2 interrupt */
#define IMX8_IRQ_FLEXPWM1_0   (IMX8_IRQ_EXTINT + 102) /* FLEXPWM1 capture/compare/reload 0 interrupt */
#define IMX8_IRQ_FLEXPWM1_1   (IMX8_IRQ_EXTINT + 103) /* FLEXPWM1 capture/compare/reload 1 interrupt */
#define IMX8_IRQ_FLEXPWM1_2   (IMX8_IRQ_EXTINT + 104) /* FLEXPWM1 capture/compare/reload 2 interrupt */
#define IMX8_IRQ_FLEXPWM1_3   (IMX8_IRQ_EXTINT + 105) /* FLEXPWM1 capture/compare/reload 3 interrupt */
#define IMX8_IRQ_FLEXPWM1_F   (IMX8_IRQ_EXTINT + 106) /* FLEXPWM1 fault interrupt OR reload error */

/* RESERVED                    (IMX8_IRQ_EXTINT + 107) RESERVED */
#define IMX8_IRQ_FLEXSPI      (IMX8_IRQ_EXTINT + 108) /* FlexSPI interrupt */
#define IMX8_IRQ_SEMC         (IMX8_IRQ_EXTINT + 109) /* SEMC interrupt */
#define IMX8_IRQ_USDHC1       (IMX8_IRQ_EXTINT + 110) /* USDHC1 interrupt */
#define IMX8_IRQ_USDHC2       (IMX8_IRQ_EXTINT + 111) /* USDHC2 interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 112) RESERVED */
#define IMX8_IRQ_USBOTG1      (IMX8_IRQ_EXTINT + 113) /* USBO2 USB OTG1 interrupt */
#define IMX8_IRQ_ENET         (IMX8_IRQ_EXTINT + 114) /* ENET MAC 0 interrupt */
#define IMX8_IRQ_ENET1588     (IMX8_IRQ_EXTINT + 115) /* ENET MAC 0 1588 Timer Interrupt */
#define IMX8_IRQ_XBAR1_0_1    (IMX8_IRQ_EXTINT + 116) /* XBAR1 interrupt 0/1 */
#define IMX8_IRQ_XBAR1_2_3    (IMX8_IRQ_EXTINT + 117) /* XBAR1 interrupt 2/3 */
#define IMX8_IRQ_ADCETC_0     (IMX8_IRQ_EXTINT + 118) /* ADC_ETC interrupt 0 */
#define IMX8_IRQ_ADCETC_1     (IMX8_IRQ_EXTINT + 119) /* ADC_ETC interrupt 1 */
#define IMX8_IRQ_ADCETC_2     (IMX8_IRQ_EXTINT + 120) /* ADC_ETC interrupt 2 */
#define IMX8_IRQ_ADCETC_ERR   (IMX8_IRQ_EXTINT + 121) /* ADC_ETC error interrupt */
#define IMX8_IRQ_PIT          (IMX8_IRQ_EXTINT + 122) /* PIT interrupt */
#define IMX8_IRQ_ACMP1        (IMX8_IRQ_EXTINT + 123) /* ACMP1 interrupt */
#define IMX8_IRQ_ACMP2        (IMX8_IRQ_EXTINT + 124) /* ACMP2 interrupt */
#define IMX8_IRQ_ACMP3        (IMX8_IRQ_EXTINT + 125) /* ACMP3 interrupt */
#define IMX8_IRQ_ACMP4        (IMX8_IRQ_EXTINT + 126) /* ACMP4 interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 127) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 128) RESERVED */
#define IMX8_IRQ_ENC1         (IMX8_IRQ_EXTINT + 129) /* ENC1 interrupt */
#define IMX8_IRQ_ENC2         (IMX8_IRQ_EXTINT + 130) /* ENC2 interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 131) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 132) RESERVED */
#define IMX8_IRQ_QTIMER1      (IMX8_IRQ_EXTINT + 133) /* QTIMER1 timer 0-3 interrupt */
#define IMX8_IRQ_QTIMER2      (IMX8_IRQ_EXTINT + 134) /* QTIMER2 timer 0-3 interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 135) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 136) RESERVED */
#define IMX8_IRQ_FLEXPWM2_0   (IMX8_IRQ_EXTINT + 137) /* FLEXPWM2 capture/compare/reload 0 interrupt */
#define IMX8_IRQ_FLEXPWM2_1   (IMX8_IRQ_EXTINT + 138) /* FLEXPWM2 capture/compare/reload 1 interrupt */
#define IMX8_IRQ_FLEXPWM2_2   (IMX8_IRQ_EXTINT + 139) /* FLEXPWM2 capture/compare/reload 1 interrupt */
#define IMX8_IRQ_FLEXPWM2_3   (IMX8_IRQ_EXTINT + 140) /* FLEXPWM2 capture/compare/reload 3 interrupt */
#define IMX8_IRQ_FLEXPWM2_F   (IMX8_IRQ_EXTINT + 141) /* FLEXPWM2 fault interrupt */

/* RESERVED                    (IMX8_IRQ_EXTINT + 142) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 143) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 144) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 146) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 147) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 148) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 149) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 150) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 151) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 152) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 153) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 154) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 155) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 156) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 157) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 158) RESERVED */

/* RESERVED                    (IMX8_IRQ_EXTINT + 159) RESERVED */

#define IMX8_IRQ_NEXTINT      160

/* GPIO second level interrupt **********************************************/

#define IMX8_GPIO_IRQ_FIRST   (IMX8_IRQ_EXTINT + IMX8_IRQ_NEXTINT)
#define _IMX8_GPIO1_0_15_BASE IMX8_GPIO_IRQ_FIRST

#ifdef CONFIG_IMX8_GPIO1_0_15_IRQ
  /* GPIO1 has dedicated interrupts for pins 0-7
   * REVISIT:
   * I am assuming that you really cannot use the dedicated and the multiplex
   * interrupts concurrently.
   */

#  define IMX8_IRQ_GPIO1_0    (_IMX8_GPIO1_0_15_BASE + 0)   /* GPIO1 pin 0 interrupt */
#  define IMX8_IRQ_GPIO1_1    (_IMX8_GPIO1_0_15_BASE + 1)   /* GPIO1 pin 1 interrupt */
#  define IMX8_IRQ_GPIO1_2    (_IMX8_GPIO1_0_15_BASE + 2)   /* GPIO1 pin 2 interrupt */
#  define IMX8_IRQ_GPIO1_3    (_IMX8_GPIO1_0_15_BASE + 3)   /* GPIO1 pin 3 interrupt */
#  define IMX8_IRQ_GPIO1_4    (_IMX8_GPIO1_0_15_BASE + 4)   /* GPIO1 pin 4 interrupt */
#  define IMX8_IRQ_GPIO1_5    (_IMX8_GPIO1_0_15_BASE + 5)   /* GPIO1 pin 5 interrupt */
#  define IMX8_IRQ_GPIO1_6    (_IMX8_GPIO1_0_15_BASE + 6)   /* GPIO1 pin 6 interrupt */
#  define IMX8_IRQ_GPIO1_7    (_IMX8_GPIO1_0_15_BASE + 7)   /* GPIO1 pin 7 interrupt */
#  define IMX8_IRQ_GPIO1_8    (_IMX8_GPIO1_0_15_BASE + 8)   /* GPIO1 pin 8 interrupt */
#  define IMX8_IRQ_GPIO1_9    (_IMX8_GPIO1_0_15_BASE + 9)   /* GPIO1 pin 9 interrupt */
#  define IMX8_IRQ_GPIO1_10   (_IMX8_GPIO1_0_15_BASE + 10)  /* GPIO1 pin 10 interrupt */
#  define IMX8_IRQ_GPIO1_11   (_IMX8_GPIO1_0_15_BASE + 11)  /* GPIO1 pin 11 interrupt */
#  define IMX8_IRQ_GPIO1_12   (_IMX8_GPIO1_0_15_BASE + 12)  /* GPIO1 pin 12 interrupt */
#  define IMX8_IRQ_GPIO1_13   (_IMX8_GPIO1_0_15_BASE + 13)  /* GPIO1 pin 13 interrupt */
#  define IMX8_IRQ_GPIO1_14   (_IMX8_GPIO1_0_15_BASE + 14)  /* GPIO1 pin 14 interrupt */
#  define IMX8_IRQ_GPIO1_15   (_IMX8_GPIO1_0_15_BASE + 15)  /* GPIO1 pin 15 interrupt */

#  define _IMX8_GPIO1_8_15_NIRQS 16
#  define _IMX8_GPIO1_16_31_BASE (_IMX8_GPIO1_0_15_BASE + _IMX8_GPIO1_8_15_NIRQS)
#else
#  define _IMX8_GPIO1_8_15_NIRQS 0
#  define _IMX8_GPIO1_16_31_BASE _IMX8_GPIO1_0_15_BASE
#endif

#ifdef CONFIG_IMX8_GPIO1_16_31_IRQ
#  define IMX8_IRQ_GPIO1_16   (_IMX8_GPIO1_16_31_BASE + 0)  /* GPIO1 pin 16 interrupt */
#  define IMX8_IRQ_GPIO1_17   (_IMX8_GPIO1_16_31_BASE + 1)  /* GPIO1 pin 17 interrupt */
#  define IMX8_IRQ_GPIO1_18   (_IMX8_GPIO1_16_31_BASE + 2)  /* GPIO1 pin 18 interrupt */
#  define IMX8_IRQ_GPIO1_19   (_IMX8_GPIO1_16_31_BASE + 3)  /* GPIO1 pin 19 interrupt */
#  define IMX8_IRQ_GPIO1_20   (_IMX8_GPIO1_16_31_BASE + 4)  /* GPIO1 pin 10 interrupt */
#  define IMX8_IRQ_GPIO1_21   (_IMX8_GPIO1_16_31_BASE + 5)  /* GPIO1 pin 21 interrupt */
#  define IMX8_IRQ_GPIO1_22   (_IMX8_GPIO1_16_31_BASE + 6)  /* GPIO1 pin 22 interrupt */
#  define IMX8_IRQ_GPIO1_23   (_IMX8_GPIO1_16_31_BASE + 7)  /* GPIO1 pin 23 interrupt */
#  define IMX8_IRQ_GPIO1_24   (_IMX8_GPIO1_16_31_BASE + 8)  /* GPIO1 pin 24 interrupt */
#  define IMX8_IRQ_GPIO1_25   (_IMX8_GPIO1_16_31_BASE + 9)  /* GPIO1 pin 25 interrupt */
#  define IMX8_IRQ_GPIO1_26   (_IMX8_GPIO1_16_31_BASE + 10) /* GPIO1 pin 26 interrupt */
#  define IMX8_IRQ_GPIO1_27   (_IMX8_GPIO1_16_31_BASE + 11) /* GPIO1 pin 27 interrupt */
#  define IMX8_IRQ_GPIO1_28   (_IMX8_GPIO1_16_31_BASE + 12) /* GPIO1 pin 28 interrupt */
#  define IMX8_IRQ_GPIO1_29   (_IMX8_GPIO1_16_31_BASE + 13) /* GPIO1 pin 29 interrupt */
#  define IMX8_IRQ_GPIO1_30   (_IMX8_GPIO1_16_31_BASE + 14) /* GPIO1 pin 30 interrupt */
#  define IMX8_IRQ_GPIO1_31   (_IMX8_GPIO1_16_31_BASE + 15) /* GPIO1 pin 31 interrupt */

#  define _IMX8_GPIO1_16_31_NIRQS 16
#  define _IMX8_GPIO2_0_15_BASE (_IMX8_GPIO1_16_31_BASE + _IMX8_GPIO1_16_31_NIRQS)
#  define IMX8_GPIO1_NIRQS    (_IMX8_GPIO1_8_15_NIRQS + _IMX8_GPIO1_16_31_NIRQS)
#else
#  define _IMX8_GPIO2_0_15_BASE _IMX8_GPIO1_16_31_BASE
#  define IMX8_GPIO1_NIRQS    _IMX8_GPIO1_8_15_NIRQS
#endif

#ifdef CONFIG_IMX8_GPIO2_0_15_IRQ
#  define IMX8_IRQ_GPIO2_0    (_IMX8_GPIO2_0_15_BASE + 0)   /* GPIO2 pin 0 interrupt */
#  define IMX8_IRQ_GPIO2_1    (_IMX8_GPIO2_0_15_BASE + 1)   /* GPIO2 pin 1 interrupt */
#  define IMX8_IRQ_GPIO2_2    (_IMX8_GPIO2_0_15_BASE + 2)   /* GPIO2 pin 2 interrupt */
#  define IMX8_IRQ_GPIO2_3    (_IMX8_GPIO2_0_15_BASE + 3)   /* GPIO2 pin 3 interrupt */
#  define IMX8_IRQ_GPIO2_4    (_IMX8_GPIO2_0_15_BASE + 4)   /* GPIO2 pin 4 interrupt */
#  define IMX8_IRQ_GPIO2_5    (_IMX8_GPIO2_0_15_BASE + 5)   /* GPIO2 pin 5 interrupt */
#  define IMX8_IRQ_GPIO2_6    (_IMX8_GPIO2_0_15_BASE + 6)   /* GPIO2 pin 6 interrupt */
#  define IMX8_IRQ_GPIO2_7    (_IMX8_GPIO2_0_15_BASE + 7)   /* GPIO2 pin 7 interrupt */
#  define IMX8_IRQ_GPIO2_8    (_IMX8_GPIO2_0_15_BASE + 8)   /* GPIO2 pin 8 interrupt */
#  define IMX8_IRQ_GPIO2_9    (_IMX8_GPIO2_0_15_BASE + 9)   /* GPIO2 pin 9 interrupt */
#  define IMX8_IRQ_GPIO2_10   (_IMX8_GPIO2_0_15_BASE + 10)  /* GPIO2 pin 10 interrupt */
#  define IMX8_IRQ_GPIO2_11   (_IMX8_GPIO2_0_15_BASE + 11)  /* GPIO2 pin 11 interrupt */
#  define IMX8_IRQ_GPIO2_12   (_IMX8_GPIO2_0_15_BASE + 12)  /* GPIO2 pin 12 interrupt */
#  define IMX8_IRQ_GPIO2_13   (_IMX8_GPIO2_0_15_BASE + 13)  /* GPIO2 pin 13 interrupt */
#  define IMX8_IRQ_GPIO2_14   (_IMX8_GPIO2_0_15_BASE + 14)  /* GPIO2 pin 14 interrupt */
#  define IMX8_IRQ_GPIO2_15   (_IMX8_GPIO2_0_15_BASE + 15)  /* GPIO2 pin 15 interrupt */

#  define _IMX8_GPIO2_0_15_NIRQS 16
#  define _IMX8_GPIO2_16_31_BASE (_IMX8_GPIO2_0_15_BASE + _IMX8_GPIO2_0_15_NIRQS)
#else
#  define _IMX8_GPIO2_0_15_NIRQS 0
#  define _IMX8_GPIO2_16_31_BASE _IMX8_GPIO2_0_15_BASE
#endif

#ifdef CONFIG_IMX8_GPIO2_16_31_IRQ
#  define IMX8_IRQ_GPIO2_16   (_IMX8_GPIO2_16_31_BASE + 0)  /* GPIO2 pin 16 interrupt */
#  define IMX8_IRQ_GPIO2_17   (_IMX8_GPIO2_16_31_BASE + 1)  /* GPIO2 pin 17 interrupt */
#  define IMX8_IRQ_GPIO2_18   (_IMX8_GPIO2_16_31_BASE + 2)  /* GPIO2 pin 18 interrupt */
#  define IMX8_IRQ_GPIO2_19   (_IMX8_GPIO2_16_31_BASE + 3)  /* GPIO2 pin 19 interrupt */
#  define IMX8_IRQ_GPIO2_20   (_IMX8_GPIO2_16_31_BASE + 4)  /* GPIO2 pin 20 interrupt */
#  define IMX8_IRQ_GPIO2_21   (_IMX8_GPIO2_16_31_BASE + 5)  /* GPIO2 pin 21 interrupt */
#  define IMX8_IRQ_GPIO2_22   (_IMX8_GPIO2_16_31_BASE + 6)  /* GPIO2 pin 22 interrupt */
#  define IMX8_IRQ_GPIO2_23   (_IMX8_GPIO2_16_31_BASE + 7)  /* GPIO2 pin 23 interrupt */
#  define IMX8_IRQ_GPIO2_24   (_IMX8_GPIO2_16_31_BASE + 8)  /* GPIO2 pin 24 interrupt */
#  define IMX8_IRQ_GPIO2_25   (_IMX8_GPIO2_16_31_BASE + 9)  /* GPIO2 pin 25 interrupt */
#  define IMX8_IRQ_GPIO2_26   (_IMX8_GPIO2_16_31_BASE + 10) /* GPIO2 pin 26 interrupt */
#  define IMX8_IRQ_GPIO2_27   (_IMX8_GPIO2_16_31_BASE + 11) /* GPIO2 pin 27 interrupt */
#  define IMX8_IRQ_GPIO2_28   (_IMX8_GPIO2_16_31_BASE + 12) /* GPIO2 pin 28 interrupt */
#  define IMX8_IRQ_GPIO2_29   (_IMX8_GPIO2_16_31_BASE + 13) /* GPIO2 pin 29 interrupt */
#  define IMX8_IRQ_GPIO2_30   (_IMX8_GPIO2_16_31_BASE + 14) /* GPIO2 pin 30 interrupt */
#  define IMX8_IRQ_GPIO2_31   (_IMX8_GPIO2_16_31_BASE + 15) /* GPIO2 pin 31 interrupt */

#  define _IMX8_GPIO2_16_31_NIRQS 16
#  define _IMX8_GPIO3_0_15_BASE (_IMX8_GPIO2_16_31_BASE + _IMX8_GPIO2_16_31_NIRQS)
#  define IMX8_GPIO2_NIRQS    (_IMX8_GPIO2_0_15_NIRQS + _IMX8_GPIO2_16_31_NIRQS)
#else
#  define _IMX8_GPIO3_0_15_BASE _IMX8_GPIO2_16_31_BASE
#  define IMX8_GPIO2_NIRQS    _IMX8_GPIO2_0_15_NIRQS
#endif

#ifdef CONFIG_IMX8_GPIO3_0_15_IRQ
#  define IMX8_IRQ_GPIO3_0    (_IMX8_GPIO3_0_15_BASE + 0)   /* GPIO3 pin 0 interrupt */
#  define IMX8_IRQ_GPIO3_1    (_IMX8_GPIO3_0_15_BASE + 1)   /* GPIO3 pin 1 interrupt */
#  define IMX8_IRQ_GPIO3_2    (_IMX8_GPIO3_0_15_BASE + 2)   /* GPIO3 pin 2 interrupt */
#  define IMX8_IRQ_GPIO3_3    (_IMX8_GPIO3_0_15_BASE + 3)   /* GPIO3 pin 3 interrupt */
#  define IMX8_IRQ_GPIO3_4    (_IMX8_GPIO3_0_15_BASE + 4)   /* GPIO3 pin 4 interrupt */
#  define IMX8_IRQ_GPIO3_5    (_IMX8_GPIO3_0_15_BASE + 5)   /* GPIO3 pin 5 interrupt */
#  define IMX8_IRQ_GPIO3_6    (_IMX8_GPIO3_0_15_BASE + 6)   /* GPIO3 pin 6 interrupt */
#  define IMX8_IRQ_GPIO3_7    (_IMX8_GPIO3_0_15_BASE + 7)   /* GPIO3 pin 7 interrupt */
#  define IMX8_IRQ_GPIO3_8    (_IMX8_GPIO3_0_15_BASE + 8)   /* GPIO3 pin 8 interrupt */
#  define IMX8_IRQ_GPIO3_9    (_IMX8_GPIO3_0_15_BASE + 9)   /* GPIO3 pin 9 interrupt */
#  define IMX8_IRQ_GPIO3_10   (_IMX8_GPIO3_0_15_BASE + 10)  /* GPIO3 pin 10 interrupt */
#  define IMX8_IRQ_GPIO3_11   (_IMX8_GPIO3_0_15_BASE + 11)  /* GPIO3 pin 11 interrupt */
#  define IMX8_IRQ_GPIO3_12   (_IMX8_GPIO3_0_15_BASE + 12)  /* GPIO3 pin 12 interrupt */
#  define IMX8_IRQ_GPIO3_13   (_IMX8_GPIO3_0_15_BASE + 13)  /* GPIO3 pin 13 interrupt */
#  define IMX8_IRQ_GPIO3_14   (_IMX8_GPIO3_0_15_BASE + 14)  /* GPIO3 pin 14 interrupt */
#  define IMX8_IRQ_GPIO3_15   (_IMX8_GPIO3_0_15_BASE + 15)  /* GPIO3 pin 15 interrupt */

#  define _IMX8_GPIO3_0_15_NIRQS 16
#  define _IMX8_GPIO3_16_31_BASE (_IMX8_GPIO3_0_15_BASE + _IMX8_GPIO3_0_15_NIRQS)
#else
#  define _IMX8_GPIO3_0_15_NIRQS 0
#  define _IMX8_GPIO3_16_31_BASE _IMX8_GPIO3_0_15_BASE
#endif

#ifdef CONFIG_IMX8_GPIO3_16_31_IRQ
#  define IMX8_IRQ_GPIO3_16   (_IMX8_GPIO3_16_31_BASE + 0)  /* GPIO3 pin 16 interrupt */
#  define IMX8_IRQ_GPIO3_17   (_IMX8_GPIO3_16_31_BASE + 1)  /* GPIO3 pin 17 interrupt */
#  define IMX8_IRQ_GPIO3_18   (_IMX8_GPIO3_16_31_BASE + 2)  /* GPIO3 pin 18 interrupt */
#  define IMX8_IRQ_GPIO3_19   (_IMX8_GPIO3_16_31_BASE + 3)  /* GPIO3 pin 19 interrupt */
#  define IMX8_IRQ_GPIO3_20   (_IMX8_GPIO3_16_31_BASE + 4)  /* GPIO3 pin 20 interrupt */
#  define IMX8_IRQ_GPIO3_21   (_IMX8_GPIO3_16_31_BASE + 5)  /* GPIO3 pin 21 interrupt */
#  define IMX8_IRQ_GPIO3_22   (_IMX8_GPIO3_16_31_BASE + 6)  /* GPIO3 pin 22 interrupt */
#  define IMX8_IRQ_GPIO3_23   (_IMX8_GPIO3_16_31_BASE + 7)  /* GPIO3 pin 23 interrupt */
#  define IMX8_IRQ_GPIO3_24   (_IMX8_GPIO3_16_31_BASE + 8)  /* GPIO3 pin 24 interrupt */
#  define IMX8_IRQ_GPIO3_25   (_IMX8_GPIO3_16_31_BASE + 9)  /* GPIO3 pin 25 interrupt */
#  define IMX8_IRQ_GPIO3_26   (_IMX8_GPIO3_16_31_BASE + 10) /* GPIO3 pin 26 interrupt */
#  define IMX8_IRQ_GPIO3_27   (_IMX8_GPIO3_16_31_BASE + 11) /* GPIO3 pin 27 interrupt */
#  define IMX8_IRQ_GPIO3_28   (_IMX8_GPIO3_16_31_BASE + 12) /* GPIO3 pin 28 interrupt */
#  define IMX8_IRQ_GPIO3_29   (_IMX8_GPIO3_16_31_BASE + 13) /* GPIO3 pin 29 interrupt */
#  define IMX8_IRQ_GPIO3_30   (_IMX8_GPIO3_16_31_BASE + 14) /* GPIO3 pin 30 interrupt */
#  define IMX8_IRQ_GPIO3_31   (_IMX8_GPIO3_16_31_BASE + 15) /* GPIO3 pin 31 interrupt */

#  define _IMX8_GPIO3_16_31_NIRQS 16
#  define _IMX8_GPIO5_0_15_BASE (_IMX8_GPIO3_16_31_BASE + _IMX8_GPIO3_16_31_NIRQS)
#  define IMX8_GPIO3_NIRQS    (_IMX8_GPIO3_0_15_NIRQS + _IMX8_GPIO3_16_31_NIRQS)
#else
#  define _IMX8_GPIO5_0_15_BASE _IMX8_GPIO3_16_31_BASE
#  define IMX8_GPIO3_NIRQS    _IMX8_GPIO3_0_15_NIRQS
#endif

/* There is no GPIO4 on this chip */

#ifdef CONFIG_IMX8_GPIO5_0_15_IRQ
#  define IMX8_IRQ_GPIO5_0    (_IMX8_GPIO5_0_15_BASE + 0)   /* GPIO5 pin 0 interrupt */
#  define IMX8_IRQ_GPIO5_1    (_IMX8_GPIO5_0_15_BASE + 1)   /* GPIO5 pin 1 interrupt */
#  define IMX8_IRQ_GPIO5_2    (_IMX8_GPIO5_0_15_BASE + 2)   /* GPIO5 pin 2 interrupt */
#  define IMX8_IRQ_GPIO5_3    (_IMX8_GPIO5_0_15_BASE + 3)   /* GPIO5 pin 3 interrupt */
#  define IMX8_IRQ_GPIO5_4    (_IMX8_GPIO5_0_15_BASE + 4)   /* GPIO5 pin 4 interrupt */
#  define IMX8_IRQ_GPIO5_5    (_IMX8_GPIO5_0_15_BASE + 5)   /* GPIO5 pin 5 interrupt */
#  define IMX8_IRQ_GPIO5_6    (_IMX8_GPIO5_0_15_BASE + 6)   /* GPIO5 pin 6 interrupt */
#  define IMX8_IRQ_GPIO5_7    (_IMX8_GPIO5_0_15_BASE + 7)   /* GPIO5 pin 7 interrupt */
#  define IMX8_IRQ_GPIO5_8    (_IMX8_GPIO5_0_15_BASE + 8)   /* GPIO5 pin 8 interrupt */
#  define IMX8_IRQ_GPIO5_9    (_IMX8_GPIO5_0_15_BASE + 9)   /* GPIO5 pin 9 interrupt */
#  define IMX8_IRQ_GPIO5_10   (_IMX8_GPIO5_0_15_BASE + 10)  /* GPIO5 pin 10 interrupt */
#  define IMX8_IRQ_GPIO5_11   (_IMX8_GPIO5_0_15_BASE + 11)  /* GPIO5 pin 11 interrupt */
#  define IMX8_IRQ_GPIO5_12   (_IMX8_GPIO5_0_15_BASE + 12)  /* GPIO5 pin 12 interrupt */
#  define IMX8_IRQ_GPIO5_13   (_IMX8_GPIO5_0_15_BASE + 13)  /* GPIO5 pin 13 interrupt */
#  define IMX8_IRQ_GPIO5_14   (_IMX8_GPIO5_0_15_BASE + 14)  /* GPIO5 pin 14 interrupt */
#  define IMX8_IRQ_GPIO5_15   (_IMX8_GPIO5_0_15_BASE + 15)  /* GPIO5 pin 15 interrupt */

#  define _IMX8_GPIO5_0_15_NIRQS 16
#  define _IMX8_GPIO5_16_31_BASE (_IMX8_GPIO5_0_15_BASE + _IMX8_GPIO5_0_15_NIRQS)
#else
#  define _IMX8_GPIO5_0_15_NIRQS 0
#  define _IMX8_GPIO5_16_31_BASE _IMX8_GPIO5_0_15_BASE
#endif

#ifdef CONFIG_IMX8_GPIO5_16_31_IRQ
#  define IMX8_IRQ_GPIO5_16   (_IMX8_GPIO5_16_31_BASE + 0)  /* GPIO5 pin 16 interrupt */
#  define IMX8_IRQ_GPIO5_17   (_IMX8_GPIO5_16_31_BASE + 1)  /* GPIO5 pin 17 interrupt */
#  define IMX8_IRQ_GPIO5_18   (_IMX8_GPIO5_16_31_BASE + 2)  /* GPIO5 pin 18 interrupt */
#  define IMX8_IRQ_GPIO5_19   (_IMX8_GPIO5_16_31_BASE + 3)  /* GPIO5 pin 19 interrupt */
#  define IMX8_IRQ_GPIO5_20   (_IMX8_GPIO5_16_31_BASE + 4)  /* GPIO5 pin 20 interrupt */
#  define IMX8_IRQ_GPIO5_21   (_IMX8_GPIO5_16_31_BASE + 5)  /* GPIO5 pin 21 interrupt */
#  define IMX8_IRQ_GPIO5_22   (_IMX8_GPIO5_16_31_BASE + 6)  /* GPIO5 pin 22 interrupt */
#  define IMX8_IRQ_GPIO5_23   (_IMX8_GPIO5_16_31_BASE + 7)  /* GPIO5 pin 23 interrupt */
#  define IMX8_IRQ_GPIO5_24   (_IMX8_GPIO5_16_31_BASE + 8)  /* GPIO5 pin 24 interrupt */
#  define IMX8_IRQ_GPIO5_25   (_IMX8_GPIO5_16_31_BASE + 9)  /* GPIO5 pin 25 interrupt */
#  define IMX8_IRQ_GPIO5_26   (_IMX8_GPIO5_16_31_BASE + 10) /* GPIO5 pin 26 interrupt */
#  define IMX8_IRQ_GPIO5_27   (_IMX8_GPIO5_16_31_BASE + 11) /* GPIO5 pin 27 interrupt */
#  define IMX8_IRQ_GPIO5_28   (_IMX8_GPIO5_16_31_BASE + 12) /* GPIO5 pin 28 interrupt */
#  define IMX8_IRQ_GPIO5_29   (_IMX8_GPIO5_16_31_BASE + 13) /* GPIO5 pin 29 interrupt */
#  define IMX8_IRQ_GPIO5_30   (_IMX8_GPIO5_16_31_BASE + 14) /* GPIO5 pin 30 interrupt */
#  define IMX8_IRQ_GPIO5_31   (_IMX8_GPIO5_16_31_BASE + 15) /* GPIO5 pin 31 interrupt */

#  define _IMX8_GPIO5_16_31_NIRQS 16
#  define IMX8_GPIO5_NIRQS    (_IMX8_GPIO5_0_15_NIRQS + _IMX8_GPIO5_16_31_NIRQS)
#else
#  define IMX8_GPIO5_NIRQS    _IMX8_GPIO5_0_15_NIRQS
#endif

#define IMX8_GPIO_NIRQS       (IMX8_GPIO1_NIRQS + IMX8_GPIO2_NIRQS + \
                                IMX8_GPIO3_NIRQS + IMX8_GPIO5_NIRQS)
#define IMX8_GPIO_IRQ_LAST    (_IMX8_GPIO1_0_15_BASE + IMX8_GPIO_NIRQS)

/* Total number of IRQ numbers **********************************************/

#define NR_IRQS                (IMX8_IRQ_EXTINT + IMX8_IRQ_NEXTINT + IMX8_GPIO_NIRQS)

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Inline functions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__
#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif
#endif

#endif /* __ARCH_ARM_INCLUDE_IMX8_IMX8MN_IRQ_H */
