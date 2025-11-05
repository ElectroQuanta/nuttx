/****************************************************************************
 * boards/arm/imx8/imx8-ddr3-evk-m7/src/imx8_lcd.c
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

#include <stdbool.h>
#include <debug.h>

#include "imx8_lcd.h"
#include "imx8_gpio.h"

#include "imx8-ddr3-evk-m7.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: imx8_lcd_initialize
 *
 * Description:
 *   Initialize the LCD.  Setup backlight (initially off)
 *
 ****************************************************************************/

void imx8_lcd_initialize(void)
{
  /* Configure the LCD backlight (and turn the backlight off) */

  imx8_config_gpio(GPIO_LCD_BL);
}

/****************************************************************************
 * Name: imx8_backlight
 *
 * Description:
 *   If CONFIG_IMX8_LCD_BACKLIGHT is defined, then the board-specific
 *   logic must provide this interface to turn the backlight on and off.
 *
 ****************************************************************************/

#ifdef CONFIG_IMX8_LCD_BACKLIGHT
void imx8_backlight(bool blon)
{
  imx8_gpio_write(GPIO_LCD_BL, blon); /* High illuminates */
}
#endif
