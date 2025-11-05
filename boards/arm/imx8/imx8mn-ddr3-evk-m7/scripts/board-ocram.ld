/* board-ocram.ld - OCRAM-based linker script for i.MX8MN Cortex-M7 + NuttX */

/* Entry point */
ENTRY(__start)

/* Memory layout */
MEMORY
{
  itcm (rwx)  : ORIGIN = 0x00000000, LENGTH = 128K
  dtcm (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
  sram (rwx)  : ORIGIN = 0x00900000, LENGTH = 512K /* OCRAM */
  flash (rx)  : ORIGIN = 0xC0000000, LENGTH = 256M /* QSPI Flash */
}

/* Sections placed contiguously in OCRAM (VMA == LMA => flat binary easy) */
SECTIONS
{
  /* Vector table at OCRAM start */
  .vectors 0x00900000 :
  {
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))
  } > ocram

  /* Text + RO data in OCRAM */
  .text :
  {
    _stext = ABSOLUTE(.);
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.glue_7 .glue_7t)
    *(.gcc_except_table)
    *(.gnu.linkonce.t.*)
    _etext = ABSOLUTE(.);
    _eronly = ABSOLUTE(.); /* end of read-only for data init */
  } > ocram

  /* RAM functions (execute from OCRAM) */
  .ramfunc ALIGN(4) :
  {
    _sramfuncs = ABSOLUTE(.);
    *(.ramfunc .ramfunc.*)
    _eramfuncs = ABSOLUTE(.);
  } > ocram

  /* Initialized data placed after text (in OCRAM) */
  .data :
  {
    _sdata = ABSOLUTE(.);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    CONSTRUCTORS
    . = ALIGN(4);
    _edata = ABSOLUTE(.);
  } > ocram

  /* BSS in OCRAM */
  .bss :
  {
    _sbss = ABSOLUTE(.);
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = ABSOLUTE(.);
  } > ocram

  /* Heap and stack in OCRAM */
  .heap :
  {
    . = ALIGN(8);
    __HeapBase = .;
    . += 0x10000;      /* default 64 KB heap */
    __HeapLimit = .;
    __heap_limit = .;
  } > ocram

  .stack :
  {
    . = ALIGN(8);
    . += 0x0800;       /* 2 KB stack (adjust as needed) */
  } > ocram

  __StackTop   = ORIGIN(ocram) + LENGTH(ocram);
  __StackLimit = __StackTop - SIZEOF(.stack);
  PROVIDE(__stack = __StackTop);

  /* constructors */
  .init_array :
  {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN(__init_array_end = .);
  } > ocram

  /* debug sections preserved at end of file (optional) */
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_info 0   : { *(.debug_info) }
  .debug_line 0   : { *(.debug_line) }
}
