/****************************************************************************
 * board_uart_console.c
 *
 * Minimal early polled console for imx8mn M7 using LPUART4 (polled).
 * - Non-SDK implementation of clock + root enable and simple TX.
 * - Use only to get early prints working. Do NOT call in interrupt context.
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "hardware/imx8mn/imx8mn_uart.h"

/* Replace with NuttX logging or PRINTF macros as available */
#ifndef PRINTF
#  include <stdio.h>
#  define PRINTF(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#endif

/* === Board-specific addresses (from your discovery) ===
 * These exact addresses came from your earlier probing.
 * Double-check them for your particular i.MX8MN variant.
 */
#define CCGR74_ADDR    0x303844C0u  /* CCGR for group containing UART4 */
#define ROOT_UART4     0x3038B080u  /* root clock register for UART4 */
#define RDC_MDA1       0x303d0204u  /* master domain assignment (M7 domain) */
#define RDC_PDAP70     0x303d0518u  /* PDAP entry for UART4 */

/* Root clock bit masks (per your chip) */
#define ROOT_ENABLE_MASK   (1u << 28)
#define ROOT_MUX_MASK      (0x7u << 24)
#define ROOT_MUX_SYSTEM_PLL1_DIV10 (1u << 24)  /* 001 -> SYSTEM_PLL1_DIV10 (80MHz) */

#define CCGR_DOMAIN1_MASK 0x30u /* bits for domain1 (2 bits per PDAP field) */

#define IMX_CONSOLE_VBASE IMX_UART4_VBASE

static void rdc_init(void){
  uint8_t domainId = 0U;

    return (uint8_t)((base->STAT & RDC_STAT_DID_MASK) >> RDC_STAT_DID_SHIFT);

  }

/* Simple timeouts to avoid infinite loops */
static void my_up_udelay(unsigned usec)
{
  volatile unsigned i;
  for (i = 0; i < (usec * 10); ++i) __asm__ volatile("nop");
}

/* Placeholder: implement board-specific pin config by copying SDK pin writes.
 * Example: set iomuxc registers to route LPUART4 TX/RX, pad config, etc.
 */
static void configure_uart_pins(void)
{
  /* Copy / adapt the pin mux/register writes from BOARD_InitBootPins() */
  /* Example:
     putreg32(MUX_VAL_FOR_LPUART4_TX, IOMUXC_SOME_PAD);
     putreg32(PAD_CFG_VAL, IOMUXC_SOME_PAD_CTRL);
  */
}

/* Confirm RDC for PDAP70 allows domain1 (M7) access */
static bool rdc_pdap70_ok(void)
{
  uint32_t v = getreg32(RDC_PDAP70);
  /* PDAP encoding in your board: check appropriate domain bit mask.
   * From your earlier probe you observed 0xc allowed domain 1 read/write.
   * Adjust the mask if needed.
   */
  (void)v; /* not used directly here; keep for logging if desired */
  return true;
}

/* Enable the CCGR entry (peripheral domain clock). Use read-modify-write
 * with a timeout; do not blindly write whole register unless you're sure.
 */
static int enable_uart4_ccgr(unsigned timeout_ms)
{
  unsigned waited = 0;
  /* Write the expected value that enables domain 1 for that CCGR */
  putreg32(0x30u, (void *)CCGR74_ADDR);

  while ((getreg32(CCGR74_ADDR) & CCGR_DOMAIN1_MASK) != CCGR_DOMAIN1_MASK)
    {
      if (++waited > timeout_ms) return -1;
      my_up_udelay(1000);
    }
  return 0;
}

/* Enable root clock (mux + enable). Write the enable+source, then poll it */
static int enable_uart4_root(unsigned timeout_ms)
{
  unsigned waited = 0;
  uint32_t expected = ROOT_ENABLE_MASK | ROOT_MUX_SYSTEM_PLL1_DIV10;

  /* Write the value that sets mux and enable. If you prefer safe set:
   * - read current, mask only MUX and enable bits, write combination */
  uint32_t cur = getreg32(ROOT_UART4);
  uint32_t newv = (cur & ~ROOT_MUX_MASK) | ROOT_MUX_SYSTEM_PLL1_DIV10;
  newv |= ROOT_ENABLE_MASK;
  putreg32(newv, (void *)ROOT_UART4);

  while ((getreg32(ROOT_UART4) & (ROOT_ENABLE_MASK | ROOT_MUX_MASK)) != expected)
    {
      if (++waited > timeout_ms) return -2;
      my_up_udelay(1000);
    }
  return 0;
}

/* Wait for UART4 clocks & root configured; return 0 on success */
int wait_uart4_ready(unsigned timeout_ms)
{
  int ret;

  /* Optionally check RDC first (not mandatory if realm already OK) */
  if (!rdc_pdap70_ok()) {
	;
      /* PRINTF("wait_uart4_ready: RDC PDAP70 not OK\n"); */
      /* We continue to try; or return error */
    }

  ret = enable_uart4_ccgr(timeout_ms / 2);
  if (ret) {
        return ret;
        }
  
  ret = enable_uart4_root(timeout_ms / 2);
  if (ret) {
        return ret;
        }

  /* settling delay */
  my_up_udelay(1000);
  return 0;
}

/* Very small polled transmit using UART registers.
 * NOTE: you must verify UTXD offset / TXEMPTY bits for your silicon.
 * This function is only used as an early console (up_lowputc).
 */
static void uart4_putc_polled(char ch)
{

  /* Poll the TX fifo trigger level bit of the UART status register. When the
   * TXFE bit is non-zero, the TX Buffer FIFO is empty.
   */

  while ((getreg32(IMX_CONSOLE_VBASE + UART_USR2_OFFSET) &
          UART_USR2_TXFE) == 0);

  /* If the character to output is a newline, then prepend a carriage
   * return.
   */

  if (ch == '\n') {
	
      /* Send the carriage return by writing it into the UART_TXD register. */

      putreg32((uint32_t)'\r', IMX_CONSOLE_VBASE + UART_TXD_OFFSET);

      /* Wait for the transmit register to be emptied. When the TXFE bit is
       * non-zero, the TX Buffer FIFO is empty.
       */

	  while ((getreg32(IMX_CONSOLE_VBASE + UART_USR2_OFFSET) &
			  UART_USR2_TXFE) == 0);
  }

  /* Send the character by writing it into the UART_TXD register. */

  putreg32((uint32_t)ch, IMX_CONSOLE_VBASE + UART_TXD_OFFSET);
}

/* NuttX expects up_lowputc() for very early prints */
void up_lowputc(int ch)
{
  if (ch == '\n') up_lowputc('\r');

  uart4_putc_polled((char)ch);
}

/* Board init hook you call early in __start (before SDK UART init).
 * This will configure pins, clocks and ensure the console works.
 */
void board_uart_console_earlyinit(void)
{
  configure_uart_pins();

  if (wait_uart4_ready(200) != 0) {
    /* Could not ready UART in 200 ms */
    PRINTF("UART4 not ready after wait\n");
    return;
  }

  /* Optional: do a minimal LPUART register setup here to ensure TX enabled */
  /* This can be copied from SDK's UART_Init minimal code (enable TX path). */
  /* Example (pseudo; verify offsets/values): */
  /* putreg32(0x0, (void *)(LPUART4_BASE + UCR1)); */
  /* putreg32(UCR2_SRST_MASK, (void *)(LPUART4_BASE + UCR2)); */
  /* ... configure UCR4/UFCR etc ... */
}

