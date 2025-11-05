############################################################################
# boards/arm/imx8/imx8mn-ddr3-evk-m7/src/Makefile
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

include $(TOPDIR)/Make.defs

#CSRCS = imx8_boot.c imx8_flexspi_nor_boot.c imx8_flexspi_nor_flash.c
CSRCS = imx8_boot.c

ifeq ($(CONFIG_IMX8_SDRAMC),y)
CSRCS += imx8_sdram.c
endif

ifeq ($(CONFIG_BOARDCTL),y)
CSRCS += imx8_appinit.c imx8_bringup.c
else ifeq ($(CONFIG_BOARD_LATE_INITIALIZE),y)
CSRCS += imx8_bringup.c
endif

# ifeq ($(CONFIG_ARCH_LEDS),y)
# CSRCS += imx8_autoleds.c
# else
# CSRCS += imx8_userleds.c
# endif

ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += imx8_buttons.c
endif

ifeq ($(CONFIG_IMX8_ENET),y)
CSRCS += imx8_ethernet.c
endif

ifeq ($(CONFIG_IMX8_LPSPI),y)
CSRCS += imx8_spi.c
endif

ifeq ($(CONFIG_IMX8_LCD),y)
CSRCS += imx8_lcd.c
endif

ifeq ($(CONFIG_MMCSD_SPI),y)
CSRCS += imx8_mmcsd_spi.c
endif

ifeq ($(CONFIG_DEV_GPIO),y)
CSRCS += imx8_gpio.c
endif

ifeq ($(CONFIG_IMX8MN_DDR3_EVK_M7_SDRAM),y)
CSRCS += imx8_sdram_ini_dcd.c
endif

include $(TOPDIR)/boards/Board.mk
