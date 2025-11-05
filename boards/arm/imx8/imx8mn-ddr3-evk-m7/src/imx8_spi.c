/****************************************************************************
 * boards/arm/imx8/imx8mn-ddr-evk-m7/src/imx8_spi.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/spi/spi.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "imx8_config.h"
#include "imx8_lpspi.h"
#include "imx8_gpio.h"
#include "imx8mn-ddr-evk-m7.h"

#if defined(CONFIG_IMX8_LPSPI1) || defined(CONFIG_IMX8_LPSPI2) || \
    defined(CONFIG_IMX8_LPSPI3) || defined(CONFIG_IMX8_LPSPI4)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: imx8_spidev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the imx8mn-ddr-evk-m7
 *    board.
 *
 ****************************************************************************/

void weak_function imx8_spidev_initialize(void)
{
#ifdef CONFIG_IMX8_LPSPI1
  imx8_config_gpio(GPIO_LPSPI1_CS); /* LPSPI1 chip select */
  imx8_config_gpio(GPIO_MMCSD_EN);
#endif
#ifdef CONFIG_IMX8_LPSPI3
  imx8_config_gpio(GPIO_LPSPI3_CS); /* LPSPI3 chip select */
#endif
}

/****************************************************************************
 * Name:  imx8_lpspi1/2/3select and imx8_lpspi1/2/3status
 *
 * Description:
 *   The external functions, imx8_lpspi1/2/3select and
 *   imx8_lpspi1/2/3status must be provided by board-specific logic.
 *   They are implementations of the select and status methods of the SPI
 *   interface defined by struct spi_ops_s (see include/nuttx/spi/spi.h).
 *   All other methods (including imx8_lpspibus_initialize()) are provided
 *   by common STM32 logic.  To use this common SPI logic on your board:
 *
 *   1. Provide logic in imx8_boardinitialize() to configure SPI chip select
 *      pins.
 *   2. Provide imx8_lpspi1/2/3select() and imx8_lpspi1/2/3status()
 *      functions in your board-specific logic.
 *      These functions will perform chip selection and status operations
 *      using GPIOs in the way your board is configured.
 *   3. Add a calls to imx8_lpspibus_initialize() in your low level
 *      application initialization logic
 *   4. The handle returned by imx8_lpspibus_initialize() may then be used
 *      to bind the SPI driver to higher level logic (e.g., calling
 *      mmcsd_spislotinitialize(), for example, will bind the SPI driver to
 *      the SPI MMC/SD driver).
 *
 ****************************************************************************/

#ifdef CONFIG_IMX8_LPSPI1
void imx8_lpspi1select(struct spi_dev_s *dev, uint32_t devid,
                        bool selected)
{
  spiinfo("devid: %d CS: %s\n", (int)devid,
          selected ? "assert" : "de-assert");

  imx8_gpio_write(GPIO_LPSPI1_CS, !selected);
}

uint8_t imx8_lpspi1status(struct spi_dev_s *dev, uint32_t devid)
{
  return 0;
}
#endif

#ifdef CONFIG_IMX8_LPSPI2
void imx8_lpspi2select(struct spi_dev_s *dev, uint32_t devid,
                        bool selected)
{
  spiinfo("devid: %d CS: %s\n", (int)devid,
          selected ? "assert" : "de-assert");

  imx8_gpio_write(GPIO_LPSPI2_CS, !selected);
}

uint8_t imx8_lpspi2status(struct spi_dev_s *dev, uint32_t devid)
{
  return 0;
}
#endif

#ifdef CONFIG_IMX8_LPSPI3
void imx8_lpspi3select(struct spi_dev_s *dev, uint32_t devid,
                        bool selected)
{
  spiinfo("devid: %d CS: %s\n", (int)devid,
          selected ? "assert" : "de-assert");

  imx8_gpio_write(GPIO_LPSPI3_CS, !selected);
}

uint8_t imx8_lpspi3status(struct spi_dev_s *dev, uint32_t devid)
{
  return 0;
}
#endif

#ifdef CONFIG_IMX8_LPSPI4
void imx8_lpspi4select(struct spi_dev_s *dev, uint32_t devid,
                        bool selected)
{
  spiinfo("devid: %d CS: %s\n", (int)devid,
          selected ? "assert" : "de-assert");

  imx8_gpio_write(GPIO_LPSPI4_CS, !selected);
}

uint8_t imx8_lpspi4status(struct spi_dev_s *dev, uint32_t devid)
{
  return 0;
}
#endif

/****************************************************************************
 * Name: imx8_lpspi1cmddata
 *
 * Description:
 *   Set or clear the SH1101A A0 or SD1306 D/C n bit to select data (true)
 *   or command (false). This function must be provided by platform-specific
 *   logic. This is an implementation of the cmddata method of the SPI
 *   interface defined by struct spi_ops_s (see include/nuttx/spi/spi.h).
 *
 * Input Parameters:
 *
 *   spi - SPI device that controls the bus the device that requires the CMD/
 *         DATA selection.
 *   devid - If there are multiple devices on the bus, this selects which one
 *         to select cmd or data.  NOTE:  This design restricts, for example,
 *         one one SPI display per SPI bus.
 *   cmd - true: select command; false: select data
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

#ifdef CONFIG_SPI_CMDDATA
#ifdef CONFIG_IMX8_LPSPI1
int imx8_lpspi1cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd)
{
  return -ENODEV;
}
#endif

#ifdef CONFIG_IMX8_LPSPI2
int imx8_lpspi2cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd)
{
  return -ENODEV;
}
#endif

#ifdef CONFIG_IMX8_LPSPI3
int imx8_lpspi3cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd)
{
  return -ENODEV;
}
#endif

#ifdef CONFIG_IMX8_LPSPI4
int imx8_lpspi4cmddata(struct spi_dev_s *dev, uint32_t devid, bool cmd)
{
  return -ENODEV;
}
#endif
#endif /* CONFIG_SPI_CMDDATA */
#endif /* CONFIG_IMX8_LPSPI1 || CONFIG_IMX8_LPSPI2 */
