/* Linker script for NuttX on i.MX8MN (M7)
 * ENTRY symbol: __start (NuttX)
 *
 * Memory regions based on values you provided:
 *   itcm  : 0x00000000 (128K)
 *   dtcm  : 0x20000000 (128K)
 *   sram  : 0x00900000 (512K)  (OCRAM)
 *   flash : 0xC0000000 (256M)  (QSPI)
 */

OUTPUT_ARCH(arm)
ENTRY(__start)

MEMORY
{
  itcm  (rwx) : ORIGIN = 0x00000000, LENGTH = 128K
  dtcm  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
  sram  (rwx) : ORIGIN = 0x00900000, LENGTH = 512K
  flash (rx)  : ORIGIN = 0xC0000000, LENGTH = 256M
}

/* External symbols you may need in startup code */
EXTERN(_vectors)
EXTERN(_sbss)
EXTERN(_ebss)
EXTERN(_sdata)
EXTERN(_edata)
EXTERN(_framfuncs)


/* HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x0400; */
/* STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x0400; */

/* Sections */
SECTIONS
{
  /* ---------------------------
   * Optionally place a boot header/IVT in flash here if required
   * (uncomment/adjust if your platform needs an IVT or ROM header).
   * --------------------------- */

  /* --- Small ITCM region: vectors + hot code (VMA=ITCM, LMA in flash) --- */
  .itcm_text : ALIGN(4)
  {
    __sitcm = ABSOLUTE(.);
    /* Vectors must be in ITCM for deterministic vectored ISR latency */
    KEEP(*(.vectors))
    /* Small, hot routines that are latency-sensitive can be put in .itcm_text */
    KEEP(*(.itcm.text .itcm.text.*))
    KEEP(*(.itcm.rodata .itcm.rodata.*))
    . = ALIGN(4);
    __eitcm = ABSOLUTE(.);
  } > itcm AT > flash

  /* Save LMA of itcm_text (useful in startup to copy itcm_image -> itcm) */
  _litcm_load = LOADADDR(.itcm_text);

  /* --- Bulk FLASH-resident code (XIP) --- */
  .text : ALIGN(4)
  {
    _stext = ABSOLUTE(.);
    *(.text .text.*)
    *(.fixup)
    *(.gnu.warning)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.t.*)
    *(.glue_7)
    *(.glue_7t)
    *(.got)
    *(.gcc_except_table)
    *(.gnu.linkonce.r.*)
    _etext = ABSOLUTE(.);
  } > flash

  .init_section :
  {
    _sinit = ABSOLUTE(.);
    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP(*(.init_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o) .ctors))
    _einit = ABSOLUTE(.);
  } > flash

  .ARM.extab :
  {
    *(.ARM.extab*)
  } > flash

  .ARM.exidx :
  {
    __exidx_start = ABSOLUTE(.);
    *(.ARM.exidx*)
    __exidx_end = ABSOLUTE(.);
  } > flash

  /* Mark the end of the readonly region used as the source for initialized data */
  _eronly = ABSOLUTE(.);

  /* --- Data: VMA in OCRAM, image stored in flash --- */
  .data : ALIGN(4)
  {
    _sdata = ABSOLUTE(.);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    CONSTRUCTORS
    . = ALIGN(4);
    _edata = ABSOLUTE(.);
  } > sram AT > flash

  /* --- RAM functions: VMA in OCRAM, image stored in flash --- */
  .ramfunc : ALIGN(4)
  {
    _sramfuncs = ABSOLUTE(.);
    *(.ramfunc .ramfunc.*)
    _eramfuncs = ABSOLUTE(.);
  } > sram AT > flash

  /* LMA source for ramfunc copy */
  _framfuncs = LOADADDR(.ramfunc);

  /* --- DTCM data: deterministic fast data (VMA = DTCM, image in flash) --- */
  .dtcm_data : ALIGN(4)
  {
    __sdtcm = ABSOLUTE(.);
    *(.dtcm .dtcm.*)          /* variables annotated with .dtcm will land here */
    . = ALIGN(4);
    __edtcm = ABSOLUTE(.);
  } > dtcm AT > flash

  /* LMA source for dtcm_data copy */
   _ldtcm_load = LOADADDR(.dtcm_data);   /* <-- add this */

  /* --- BSS in OCRAM (no LMA, NOLOAD) --- */
  .bss (NOLOAD) : ALIGN(4)
  {
    _sbss = ABSOLUTE(.);
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = ABSOLUTE(.);
  } > sram

  /* Heap and stack in OCRAM */
  .heap : ALIGN(8)
  {
    . = ALIGN(8);
    __heap_start = .;
    . += 0x400; /* small default heap (adjust via Kconfig/Makefile) */
    __heap_end = .;
  } > sram

  .stack : ALIGN(8)
  {
    . = ALIGN(8);
    __stack_top = .;
    . += 0x400; /* default stack size (adjust as needed) */
    __stack_limit = .;
  } > sram

  /* Debug sections (unchanged) */
  .ARM.attributes 0 : { *(.ARM.attributes) }
  .comment 0 : { *(.comment) }
  .debug_info 0 : { *(.debug_info) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_line 0 : { *(.debug_line) }
  .debug_str 0 : { *(.debug_str) }
}
