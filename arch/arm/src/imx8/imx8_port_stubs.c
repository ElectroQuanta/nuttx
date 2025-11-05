/* arch/arm/src/imx8/imx8_port_stubs.c
 * Minimal port stubs to satisfy NuttX link-time expectations.
 * Replace TODOs with real implementations using your SDK.
 */

#include <nuttx/config.h>
#include <stdint.h>
#include <stddef.h>

/* #include "sdk/MIMX8MN6_cm7_COMMON.h" */
/* #include "sdk/core_cm7.h" */
#include "hardware/imx8mn/imx8mn_uart.h"
#include "arm_internal.h"

/* Use RAM start/size from defconfig if provided; otherwise adapt.
 * Prefer using linker symbols if you have them (see notes below).
 */
/* #ifndef CONFIG_RAM_START */
/* #  define CONFIG_RAM_START 0x20200000 */
/* #endif */
/* #ifndef CONFIG_RAM_SIZE */
/* #  define CONFIG_RAM_SIZE (512 * 1024) */
/* #endif */


//#define IMX_CONSOLE_VBASE IMX8_UART4_VBASE
#define IMX_CONSOLE_VBASE IMX8_UART2_VBASE

/* Top-of-idle-stack used by up_allocate_heap */
const uintptr_t g_idle_topstack =
    (uintptr_t)(CONFIG_RAM_START + CONFIG_RAM_SIZE);


/* IRQ control (NVIC wrappers) - TODO: call CMSIS NVIC_EnableIRQ / NVIC_DisableIRQ */
void up_enable_irq(int irq)
{
  /* (void)irq; */
  /* TODO: NVIC_EnableIRQ((IRQn_Type)irq); */
  /* NVIC_EnableIRQ(irq); */
  (void)irq;
}

void up_disable_irq(int irq)
{
  /* NVIC_DisableIRQ(irq); */
  (void)irq;
}

/* Acknowledge a peripheral IRQ (clear peripheral status). */
void arm_ack_irq(int irq)
{
  (void)irq;
  /* TODO: clear interrupt flag in peripheral registers if needed */
}

/* Called by scheduler to initialize arch IRQs. */
void up_irqinitialize(void)
{
    /* Ensure vector table already set */
    /* Disable all NVIC interrupts and clear pending bits */
    /* for (int i = 0; i < (NVIC_NUM_INTERRUPTS + 31) / 32; ++i) { */
    /*     NVIC->ICER[i] = 0xFFFFFFFFu;  /\* disable *\/ */
    /*     NVIC->ICPR[i] = 0xFFFFFFFFu;  /\* clear pending *\/ */
    /* } */
    /* Optionally set all priorities to a default here */
}


/* Timer init: provide an OS tick source here.
 * For now provide a minimal stub. Replace with SysTick/GPT setup later.
 */
void up_timer_initialize(void)
{
  /* TODO: configure SysTick or a peripheral timer for CONFIG_USEC_PER_TICK */
}

/* arch-level serial registration hook */
void arm_serialinit(void)
{
  /* Call your arch/board up_serialinit() that initializes and registers UART */
  /* extern void up_serialinit(void); */
  /* up_serialinit(); */
  (void)arm_serialinit;
}

/* Very small polled putc used by syslog and very early prints.
 * NuttX calls up_putc()/up_lowputc() in various places.
 */
void up_putc(int ch)
{
  /* extern void up_lowputc(int ch); */
  up_lowputc(ch);
}

/* /\* up_lowputc should be implemented in your imx8_lowputc.c and */
/*  * do a blocking write to LPUART4 (or whichever console you've chosen). */
/*  * Provide a weak definition here only if the real one isn't present. */
/*  *\/ */
/* __attribute__((weak)) */
/* void up_lowputc(int ch) */
/* { */
/*   (void)ch; */
/*   /\* TODO: use SDK LPUART_WriteBlocking(LPUART4, &ch, 1) *\/ */
/* } */

/* Very small polled transmit using UART registers.
 * NOTE: you must verify UTXD offset / TXEMPTY bits for your silicon.
 * This function is only used as an early console (up_lowputc).
 */
static void uart4_putc_polled(char ch) {

  volatile uint32_t *uart4_usr =
      (volatile uint32_t *)(IMX_CONSOLE_VBASE + UART_USR2_OFFSET);

  volatile uint32_t *uart4_txd =
      (volatile uint32_t *)(IMX_CONSOLE_VBASE + UART_TXD_OFFSET);

  /* Poll the TX fifo trigger level bit of the UART status register. When the
   * TXFE bit is non-zero, the TX Buffer FIFO is empty.
   */

  while ((getreg32(uart4_usr) & UART_USR2_TXFE) == 0)
    ;

  /* Send the character by writing it into the UART_TXD register. */

  putreg32((uint32_t)ch, uart4_txd);
}

/* NuttX expects up_lowputc() for very early prints */
void up_lowputc(int ch)
{
  if (ch == '\n') up_lowputc('\r');

  uart4_putc_polled((char)ch);
}

/* up_nputs is usually provided by libarch, but if any reference exists
 * you can leave it to libarch; otherwise it's fine.
 */
