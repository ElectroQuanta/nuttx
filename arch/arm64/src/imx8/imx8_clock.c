// Based on uboot clock_imx8mm.c
#include "imx8_clock.h"

void init_uart_clk(u32 index)
{
	/*
	 * set uart clock root
	 * 24M OSC
	 */
	switch (index) {
	case 0:
		clock_enable(CCGR_UART1, 0);
		clock_set_target_val(UART1_CLK_ROOT, CLK_ROOT_ON |
				     CLK_ROOT_SOURCE_SEL(0));
		clock_enable(CCGR_UART1, 1);
		return;
	case 1:
		clock_enable(CCGR_UART2, 0);
		clock_set_target_val(UART2_CLK_ROOT, CLK_ROOT_ON |
				     CLK_ROOT_SOURCE_SEL(0));
		clock_enable(CCGR_UART2, 1);
		return;
	case 2:
		clock_enable(CCGR_UART3, 0);
		clock_set_target_val(UART3_CLK_ROOT, CLK_ROOT_ON |
				     CLK_ROOT_SOURCE_SEL(0));
		clock_enable(CCGR_UART3, 1);
		return;
	case 3:
		clock_enable(CCGR_UART4, 0);
		clock_set_target_val(UART4_CLK_ROOT, CLK_ROOT_ON |
				     CLK_ROOT_SOURCE_SEL(0));
		clock_enable(CCGR_UART4, 1);
		return;
	default:
		/* printf("Invalid uart index\n"); */
		return;
	}
}
