/* arch/arm/src/imx8/imx8_lowputc.c */
#include <nuttx/config.h>
#include <stdint.h>
#include "sdk/fsl_debug_console.h"

/* If your SDK exposes a blocking write (for example LPUART_WriteBlocking or
 * fsl_debug_console putchar), call it here. Example calls below are illustrative.
 *
 * If the SDK provides a function `int DbgConsole_Putchar(int ch)`, use it.
 * If not, implement register-level TX polling here.
 */

//extern int DbgConsole_Putchar(int ch); /* if from fsl_debug_console */

void up_lowputc(int ch)
{
  DbgConsole_Putchar(ch);
}
