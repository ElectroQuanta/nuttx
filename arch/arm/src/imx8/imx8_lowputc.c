/* arch/arm/src/imx8/imx8_lowputc.c */
#include <nuttx/config.h>
#include <stdint.h>

/* If your SDK exposes a blocking write (for example LPUART_WriteBlocking or
 * fsl_debug_console putchar), call it here. Example calls below are illustrative.
 *
 * If the SDK provides a function `int DbgConsole_Putchar(int ch)`, use it.
 * If not, implement register-level TX polling here.
 */

extern int DbgConsole_Putchar(int ch); /* if from fsl_debug_console */

void up_lowputc(int ch)
{
  /* If SDK debug console is already initialized, use it: */
  (void)DbgConsole_Putchar; /* avoid unused decl warning if not present */

  /* If DbgConsole_Putchar exists, call it: */
#ifdef CONFIG_HAVE_FSL_DBGCONSOLE
  DbgConsole_Putchar(ch);
#else
  /* Fallback: do nothing for now; replace with register write */
  (void)ch;
#endif
}
