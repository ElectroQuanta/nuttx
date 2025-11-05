/* itcm.ld - ITCM-only linker script for i.MX8MN Cortex-M7 NuttX */

/* Entry point */
ENTRY(__start)

/* ITCM memory region */
MEMORY
{
  itcm (rx) : ORIGIN = 0x00000000, LENGTH = 128K
}

/* Sections */
SECTIONS
{
  /* ---------- Vector table at start of ITCM ---------- */
  .vectors 0x00000000 :
  {
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))
  } > itcm

  /* ---------- Code and read-only data ---------- */
  .text :
  {
    _stext = ABSOLUTE(.);        /* start of text for reference */
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.glue_7 .glue_7t)
    *(.gcc_except_table)
    *(.gnu.linkonce.t.*)
    _etext = ABSOLUTE(.);
  } > itcm

  /* Optional: constructors in ITCM if needed */
  .init_array :
  {
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
  } > itcm

  /* RAM function symbols (if copying from ITCM to OCRAM is needed) */
  _sramfuncs = 0;
  _eramfuncs = 0;
}
