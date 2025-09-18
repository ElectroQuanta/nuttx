/****************************************************************************
 * arch/arm64/src/imx8/hardware/imx8mn/imx8mn_ccm.h
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

#ifndef __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IMX8MN_CCM_H
#define __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IMX8MN_CCM_H

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

/* CCM Register Offsets *****************************************************/
#define IMX_CCM_SET_OFFSET 0x0004 /* Set shadow SET register offset */
#define IMX_CCM_CLEAR_OFFSET 0x0008 /* Set shadow CLEAR register offset */
#define IMX_CCM_TOGGLE_OFFSET 0x000c /* Set shadow TOGGLE register offset */

#define IMX_CCM_SET(base) ((base) + IMX_CCM_SET_OFFSET)
#define IMX_CCM_CLR(base) ((base) + IMX_CCM_CLEAR_OFFSET)
#define IMX_CCM_TOG(base) ((base) + IMX_CCM_TOGGLE_OFFSET)

#define IMX_CCM_GPR0_OFFSET 0x0000

/* CCM PLL CTRL OFFSET */
#define IMX_CCM_PLL_CTRL_OFFSET(n)  (0x0800u + ((n) * 0x10u))

#define IMX_CCM_PLL_CTRLN_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38)

/* Instantiate all CCM_PLL_CTRL registers */
#define X(n)  \
    enum { IMX_CCM_PLL_CTRL##n = IMX_CCM_PLL_CTRL_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_PLL_CTRLN_LIST

#undef X


/* CCM CCGR OFFSET */
#define IMX_CCM_CCGR_OFFSET(n) (0x4000u + ((n)*0x10u))

#define IMX_CCM_CCGR_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38) X(39) \
    X(40) X(41) X(42) X(43) X(44) \
    X(45) X(46) X(47) X(48) X(49) \
    X(50) X(51) X(52) X(53) X(54) \
    X(55) X(56) X(57) X(58) X(59) \
    X(60) X(61) X(62) X(63) X(64) \
    X(65) X(66) X(67) X(68) X(69) \
    X(70) X(71) X(72) X(73) X(74) \
    X(75) X(76) X(77) X(78) X(79) \
    X(80) X(81) X(82) X(83) X(84) \
    X(85) X(86) X(87) X(88) X(89) \
    X(90) X(91) X(92) X(93) X(94) \
    X(95) X(96) X(97) X(98) X(99) \
    X(100)  X(101)  X(102)  X(103)  X(104) \
    X(105)  X(106)  X(107)  X(108)  X(109) \
    X(110) X(111) X(112) X(113) X(114) \
    X(115) X(116) X(117) X(118) X(119) \
    X(120) X(121) X(122) X(123) X(124) \
    X(125) X(126) X(127) X(128) X(129) \
    X(130) X(131) X(132) X(133) X(134) \
    X(135) X(136) X(137) X(138) X(139) \
    X(140) X(141) X(142) X(143) X(144) \
    X(145) X(146) X(147) X(148) X(149) \
    X(150) X(151) X(152) X(153) X(154) \
    X(155) X(156) X(157) X(158) X(159) \
    X(160) X(161) X(162) X(163) X(164) \
    X(165) X(166) X(167) X(168) X(169) \
    X(170) X(171) X(172) X(173) X(174) \
    X(175) X(176) X(177) X(178) X(179) \
    X(180) X(181) X(182) X(183) X(184) \
    X(185) X(186) X(187) X(188) X(189) \
    X(190) X(191)

/* Instantiate all CCM_CCGR_CTRL registers */
#define X(n)  \
    enum { IMX_CCM_CCGR##n = IMX_CCM_CCGR_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_CCGR_LIST

#undef X

/********** CCM TARGET ROOT **************************/
#define IMX_CCM_TARGET_ROOT_OFFSET(n) (0x8000u + ((n)*0x80u))

#define IMX_CCM_TARGET_ROOT_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38) X(39) \
    X(40) X(41) X(42) X(43) X(44) \
    X(45) X(46) X(47) X(48) X(49) \
    X(50) X(51) X(52) X(53) X(54) \
    X(55) X(56) X(57) X(58) X(59) \
    X(60) X(61) X(62) X(63) X(64) \
    X(65) X(66) X(67) X(68) X(69) \
    X(70) X(71) X(72) X(73) X(74) \
    X(75) X(76) X(77) X(78) X(79) \
    X(80) X(81) X(82) X(83) X(84) \
    X(85) X(86) X(87) X(88) X(89) \
    X(90) X(91) X(92) X(93) X(94) \
    X(95) X(96) X(97) X(98) X(99) \
    X(100)  X(101)  X(102)  X(103)  X(104) \
    X(105)  X(106)  X(107)  X(108)  X(109) \
    X(110) X(111) X(112) X(113) X(114) \
    X(115) X(116) X(117) X(118) X(119) \
    X(120) X(121) X(122) X(123) X(124) \
    X(125) X(126) X(127) X(128) X(129) \
    X(130) X(131) X(132) X(133) X(134) \
    X(135) X(136) X(137) X(138) X(139) \
    X(140) X(141)

/* Instantiate all CCM_TARGET_ROOT registers */
#define X(n)  \
    enum { IMX_CCM_TARGET_ROOT##n = IMX_CCM_TARGET_ROOT_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_TARGET_ROOT_LIST

#undef X


/********** CCM MISC **************************/
#define IMX_CCM_MISC_OFFSET(n) (0x8010u + ((n)*0x80u))

#define IMX_CCM_MISC_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38) X(39) \
    X(40) X(41) X(42) X(43) X(44) \
    X(45) X(46) X(47) X(48) X(49) \
    X(50) X(51) X(52) X(53) X(54) \
    X(55) X(56) X(57) X(58) X(59) \
    X(60) X(61) X(62) X(63) X(64) \
    X(65) X(66) X(67) X(68) X(69) \
    X(70) X(71) X(72) X(73) X(74) \
    X(75) X(76) X(77) X(78) X(79) \
    X(80) X(81) X(82) X(83) X(84) \
    X(85) X(86) X(87) X(88) X(89) \
    X(90) X(91) X(92) X(93) X(94) \
    X(95) X(96) X(97) X(98) X(99) \
    X(100)  X(101)  X(102)  X(103)  X(104) \
    X(105)  X(106)  X(107)  X(108)  X(109) \
    X(110) X(111) X(112) X(113) X(114) \
    X(115) X(116) X(117) X(118) X(119) \
    X(120) X(121) X(122) X(123) X(124) \
    X(125) X(126) X(127) X(128) X(129) \
    X(130) X(131) X(132) X(133) X(134) \
    X(135) X(136) X(137) X(138) X(139) \
    X(140) X(141)

/* Instantiate all CCM_MISC registers */
#define X(n)  \
    enum { IMX_CCM_MISC##n = IMX_CCM_MISC_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_MISC_LIST

#undef X


/********** CCM POST Divider register **************************/
#define IMX_CCM_POST_OFFSET(n) (0x8020u + ((n)*0x80u))

#define IMX_CCM_POST_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38) X(39) \
    X(40) X(41) X(42) X(43) X(44) \
    X(45) X(46) X(47) X(48) X(49) \
    X(50) X(51) X(52) X(53) X(54) \
    X(55) X(56) X(57) X(58) X(59) \
    X(60) X(61) X(62) X(63) X(64) \
    X(65) X(66) X(67) X(68) X(69) \
    X(70) X(71) X(72) X(73) X(74) \
    X(75) X(76) X(77) X(78) X(79) \
    X(80) X(81) X(82) X(83) X(84) \
    X(85) X(86) X(87) X(88) X(89) \
    X(90) X(91) X(92) X(93) X(94) \
    X(95) X(96) X(97) X(98) X(99) \
    X(100)  X(101)  X(102)  X(103)  X(104) \
    X(105)  X(106)  X(107)  X(108)  X(109) \
    X(110) X(111) X(112) X(113) X(114) \
    X(115) X(116) X(117) X(118) X(119) \
    X(120) X(121) X(122) X(123) X(124) \
    X(125) X(126) X(127) X(128) X(129) \
    X(130) X(131) X(132) X(133) X(134) \
    X(135) X(136) X(137) X(138) X(139) \
    X(140) X(141)

/* Instantiate all CCM_POST registers */
#define X(n)  \
    enum { IMX_CCM_POST##n = IMX_CCM_POST_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_POST_LIST

#undef X


/********** CCM PRE Divider register **************************/
#define IMX_CCM_PRE_OFFSET(n) (0x8030u + ((n)*0x80u))

#define IMX_CCM_PRE_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38) X(39) \
    X(40) X(41) X(42) X(43) X(44) \
    X(45) X(46) X(47) X(48) X(49) \
    X(50) X(51) X(52) X(53) X(54) \
    X(55) X(56) X(57) X(58) X(59) \
    X(60) X(61) X(62) X(63) X(64) \
    X(65) X(66) X(67) X(68) X(69) \
    X(70) X(71) X(72) X(73) X(74) \
    X(75) X(76) X(77) X(78) X(79) \
    X(80) X(81) X(82) X(83) X(84) \
    X(85) X(86) X(87) X(88) X(89) \
    X(90) X(91) X(92) X(93) X(94) \
    X(95) X(96) X(97) X(98) X(99) \
    X(100)  X(101)  X(102)  X(103)  X(104) \
    X(105)  X(106)  X(107)  X(108)  X(109) \
    X(110) X(111) X(112) X(113) X(114) \
    X(115) X(116) X(117) X(118) X(119) \
    X(120) X(121) X(122) X(123) X(124) \
    X(125) X(126) X(127) X(128) X(129) \
    X(130) X(131) X(132) X(133) X(134) \
    X(135) X(136) X(137) X(138) X(139) \
    X(140) X(141)

/* Instantiate all CCM_PRE registers */
#define X(n)  \
    enum { IMX_CCM_PRE##n = IMX_CCM_PRE_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_PRE_LIST

#undef X


/********** CCM Access Control register **************************/
#define IMX_CCM_ACCESS_CTRL_OFFSET(n) (0x8030u + ((n)*0x80u))

#define IMX_CCM_ACCESS_CTRL_LIST \
    X(0)  X(1)  X(2)  X(3)  X(4) \
    X(5)  X(6)  X(7)  X(8)  X(9) \
    X(10) X(11) X(12) X(13) X(14) \
    X(15) X(16) X(17) X(18) X(19) \
    X(20) X(21) X(22) X(23) X(24) \
    X(25) X(26) X(27) X(28) X(29) \
    X(30) X(31) X(32) X(33) X(34) \
    X(35) X(36) X(37) X(38) X(39) \
    X(40) X(41) X(42) X(43) X(44) \
    X(45) X(46) X(47) X(48) X(49) \
    X(50) X(51) X(52) X(53) X(54) \
    X(55) X(56) X(57) X(58) X(59) \
    X(60) X(61) X(62) X(63) X(64) \
    X(65) X(66) X(67) X(68) X(69) \
    X(70) X(71) X(72) X(73) X(74) \
    X(75) X(76) X(77) X(78) X(79) \
    X(80) X(81) X(82) X(83) X(84) \
    X(85) X(86) X(87) X(88) X(89) \
    X(90) X(91) X(92) X(93) X(94) \
    X(95) X(96) X(97) X(98) X(99) \
    X(100)  X(101)  X(102)  X(103)  X(104) \
    X(105)  X(106)  X(107)  X(108)  X(109) \
    X(110) X(111) X(112) X(113) X(114) \
    X(115) X(116) X(117) X(118) X(119) \
    X(120) X(121) X(122) X(123) X(124) \
    X(125) X(126) X(127) X(128) X(129) \
    X(130) X(131) X(132) X(133) X(134) \
    X(135) X(136) X(137) X(138) X(139) \
    X(140) X(141)

/* Instantiate all CCM_PRE registers */
#define X(n)  \
    enum { IMX_CCM_ACCESS_CTRL##n = IMX_CCM_ACCESS_CTRL_OFFSET(n) + IMX_CCM_VBASE};

IMX_CCM_ACCESS_CTRL_LIST

#undef X



/* CCM Register Bit Definitions *********************************************/

/* CCM Control Register */
// CCM CCGR Low Power modes
typedef enum ccm_lp_mode {
  lpmode_none = 0,
  lpmode_run = 1,
  lpmode_run_wait = 2,
  lpmode_all = 3
} ccm_lp_mode_t;



#define IMX_CCM_CCGR_UART1 IMX_CCM_CCGR73
#define IMX_CCM_CCGR_UART2 IMX_CCM_CCGR74
#define IMX_CCM_CCGR_UART3 IMX_CCM_CCGR75
#define IMX_CCM_CCGR_UART4 IMX_CCM_CCGR76

#define IMX_CCM_TARGET_ROOT_UART1 IMX_CCM_TARGET_ROOT94
#define IMX_CCM_TARGET_ROOT_UART2 IMX_CCM_TARGET_ROOT95
#define IMX_CCM_TARGET_ROOT_UART3 IMX_CCM_TARGET_ROOT96
#define IMX_CCM_TARGET_ROOT_UART4 IMX_CCM_TARGET_ROOT97

#define IMX_CCM_PLL_CTRL_PLL1_DIV10 IMX_CCM_PLL_CTRL23

#define IMX_CCM_CCGR_IOMUXC IMX_CCM_CCGR27

typedef enum ccm_clk_root_uart_mux {
  clk_ref_24M = 0,
  clk_sys_pll1_div10 = 1,
  clk_sys_pll2_div5 = 2,
  clk_sys_pll2_div10 = 3,
  clk_sys_pll3_clk = 4,
  clk_ext_clk_2 = 5,
  clk_ext_clk_3 = 6,
  clk_audio_pll2_clk = 7
} ccm_clk_root_uart_mux_t;

#define SYSTEM_PLL1_DIV10_CLK_FREQ (80000000u)

#define IMX_CCM_TARGET_ENABLE_BIT (28)
#define IMX_CCM_TARGET_MUX_BITS (24)
#define IMX_CCM_TARGET_PRE_PODF_BITS (16)
#define IMX_CCM_TARGET_POST_PODF_BITS (0)

static inline void ccm_set_mode(unsigned long addr, ccm_lp_mode_t mode) {
  uint32_t reg = getreg32(addr);
  reg &= ~0x3;              /* clear domain 0’s bits [1:0] */
  reg |= (uint32_t)mode;    /* set new mode */
  putreg32(reg, addr);
}


static inline void ccm_clk_root_enable(unsigned long addr,
                                       ccm_clk_root_uart_mux_t val,
                                       bool enable) {
  uint32_t reg = getreg32(addr);
  /* Clear MUX + dividers */
    reg &= ~((0b111 << IMX_CCM_TARGET_MUX_BITS) |
             (0b111 << IMX_CCM_TARGET_PRE_PODF_BITS) |
             (0b111111 << IMX_CCM_TARGET_POST_PODF_BITS));

    /* Set MUX = SYS PLL1 ÷10, dividers = ÷1, enable = 1 */
    reg |= (val << IMX_CCM_TARGET_MUX_BITS) |
           (0 << IMX_CCM_TARGET_PRE_PODF_BITS) |
           (0 << IMX_CCM_TARGET_POST_PODF_BITS) |
           ( ( (uint32_t)enable ) << IMX_CCM_TARGET_ENABLE_BIT);

	putreg32(reg, addr);
}


#endif /* __ARCH_ARM64_SRC_IMX8_HARDWARE_IMX8MN_IMX8MN_CCM_H */
