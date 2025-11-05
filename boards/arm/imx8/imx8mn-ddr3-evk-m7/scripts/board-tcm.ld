/* iMX8MN Cortex-M7 NuttX linker script - TCM + OCRAM */

/* Entry point */
ENTRY(_stext)

/* Memory regions */
MEMORY
{
  itcm  (rx)  : ORIGIN = 0x00000000, LENGTH = 128K    /* instructions */
  dtcm  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K    /* data/BSS */
  sram  (rwx) : ORIGIN = 0x00900000, LENGTH = 512K    /* RAM functions, heap, stack */
  flash (rx)  : ORIGIN = 0xC0000000, LENGTH = 256M     /* external flash for LMA */
}

/* -------- Sections -------- */
SECTIONS
{
  /* ---------- Vector table and startup code in ITCM ---------- */
  .vectors :
  {
    _stext = ABSOLUTE(.);
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))
  } > itcm

  /* ---------- Code + read-only data in ITCM ---------- */
  .text : AT(0xC0000000) /* LMA in flash */
  {
    _stext = ABSOLUTE(.);
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.glue_7 .glue_7t)
    *(.gcc_except_table)
    *(.gnu.linkonce.t.*)
    _etext = ABSOLUTE(.);
    _eronly = ABSOLUTE(.);  /* end of read-only for data init */
  } > itcm

  /* ---------- RAM functions section ---------- */
  .ramfunc ALIGN(4) : AT(0xC0000000 + SIZEOF(.text))  /* LMA in flash */
  {
    _sramfuncs = ABSOLUTE(.);    /* start in SRAM */
    *(.ramfunc .ramfunc.*)
    _eramfuncs = ABSOLUTE(.);    /* end in SRAM */
  } > sram

  _framfuncs = LOADADDR(.ramfunc);  /* source in flash */

  /* ---------- Initialized data in DTCM ---------- */
  .data : AT(_eronly) /* load from flash after text */
  {
    _sdata = ABSOLUTE(.);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    CONSTRUCTORS
    . = ALIGN(4);
    _edata = ABSOLUTE(.);
  } > dtcm

  /* ---------- Uninitialized data in DTCM ---------- */
  .bss :
  {
    _sbss = ABSOLUTE(.);
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = ABSOLUTE(.);
  } > dtcm

  /* ---------- Heap in SRAM ---------- */
  .heap :
  {
    . = ALIGN(8);
    __HeapBase = .;
    . += 0x10000;      /* 64 KB heap */
    __HeapLimit = .;
    __heap_limit = .;
  } > sram

  /* ---------- Stack in SRAM ---------- */
  .stack :
  {
    . = ALIGN(8);
    . += 0x0800;       /* 2 KB stack */
  } > sram

  __StackTop   = ORIGIN(sram) + LENGTH(sram);
  __StackLimit = __StackTop - SIZEOF(.stack);
  PROVIDE(__stack = __StackTop);

  /* ---------- Constructors ---------- */
  .init_array :
  {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    PROVIDE_HIDDEN(__init_array_end = .);
  } > dtcm

  /* ---------- Debug sections (optional) ---------- */
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_info 0   : { *(.debug_info) }
  .debug_line 0   : { *(.debug_line) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
}
