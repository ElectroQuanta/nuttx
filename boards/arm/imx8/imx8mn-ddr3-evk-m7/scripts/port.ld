/* board-flash-nuttx.ld
 *
 * Merged / NuttX-friendly linker script derived from imxrt + SDK examples.
 * Comments are inline (you asked for comments *inside* code).
 */

/* Entry for startup - NuttX expects _stext as entry for kernel text */
ENTRY(_stext)

/* If you need page-aligned sections (e.g. on MMU/AArch64), change ALIGN(4)
 * below to ALIGN(4096). */

/* Define memory regions - adapt ORIGIN/LENGTH for your board */
MEMORY
{
  itcm (rwx)  : ORIGIN = 0x00000000, LENGTH = 128K
  dtcm (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
  sram (rwx)  : ORIGIN = 0x00900000, LENGTH = 512K
  flash (rx)  : ORIGIN = 0xC0000000, LENGTH = 64M
}

/* -------- Sections -------- */
SECTIONS
{
  /* Optional boot header / IVT for i.MX style boot (keep if your bootloader needs it). */
  .boot_hdr : ALIGN(4)
  {
    /* Fill to 0xff so any unused header bytes are 0xff (common in i.MX images) */
    FILL(0xff)
    __boot_hdr_start__ = ABSOLUTE(.);
    KEEP(*(.boot_hdr.conf))       /* board-specific boot header config */
    . = 0x1000;                   /* keep at device-specific offset if required */
    KEEP(*(.boot_hdr.ivt))        /* image vector table */
    . = 0x1020;
    KEEP(*(.boot_hdr.boot_data))  /* boot data (address, length etc) */
    . = 0x1030;
    KEEP(*(.boot_hdr.dcd_data))   /* device configuration data */
    __boot_hdr_end__ = ABSOLUTE(.);
    . = 0x2000;
  } > flash

  /* Kernel / application code and read-only data live in flash (execute in place). */
  .text :
  {
    /* mark start of kernel text for NuttX */
    _stext = ABSOLUTE(.);
    /* include vector table placed in .vectors or .isr_vector from object files */
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))       /* SDK uses .isr_vector */
    *(.text .text.*)           /* normal code sections */
    *(.fixup)
    *(.gnu.warning)
    *(.rodata .rodata.*)       /* constants, strings */
    *(.gnu.linkonce.t.*)
    *(.glue_7)
    *(.glue_7t)
    *(.gcc_except_table)
    *(.gnu.linkonce.r.*)
    _etext = ABSOLUTE(.);
    /* End of read-only (text + rodata). imx8_start.c expects _eronly */
    _eronly = ABSOLUTE(.);
  } > flash

  /* Constructor/Init arrays (if you depend on C++ ctors/ctors order) */
  .init_section :
  {
    _sinit = ABSOLUTE(.);
    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP(*(.init_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o) .ctors))
    _einit = ABSOLUTE(.);
  } > flash

  /* Exception tables */
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

  /* -----------------------
   * Initialized data (.data) lives in RAM at runtime but is stored in flash.
   * LOADADDR is wherever .text/.etext placed it in flash; the linker will
   * generate relocation info so the startup copies it into RAM at boot.
   * ----------------------- */
  .data :
  {
    _sdata = ABSOLUTE(.);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    CONSTRUCTORS         /* keep constructors if present */
    . = ALIGN(4);        /* change to ALIGN(4096) if you want page-aligned */
    _edata = ABSOLUTE(.);
  } > sram AT > flash

  /* Functions that must run out of RAM (.ramfunc) */
  .ramfunc ALIGN(4):
  {
    _sramfuncs = ABSOLUTE(.);
    *(.ramfunc  .ramfunc.*)
    _eramfuncs = ABSOLUTE(.);
  } > sram AT > flash

  /* Load address useful for startup relocation */
  _framfuncs = LOADADDR(.ramfunc);

  /* Uninitialized data (.bss) in RAM */
  .bss :
  {
    _sbss = ABSOLUTE(.);
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = ABSOLUTE(.);
  } > sram

  /* Optional debug / stabs sections (kept but not loaded) */
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_info 0 : { *(.debug_info) }
  .debug_line 0 : { *(.debug_line) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  .debug_aranges 0 : { *(.debug_aranges) }

  /* Heap + stack definitions inside SRAM region */
  /* Place heap/stack at the end of RAM region (common convention) */
  .heap :
  {
    . = ALIGN(8);
    __end__ = .;       /* symbol for end of data (for sbrk) */
    PROVIDE(end = .);
    __HeapBase = .;
    . += 0x00001000;   /* default heap size (adjust or make configurable) */
    __HeapLimit = .;
    __heap_limit = .;  /* some libraries expect __heap_limit */
  } > sram

  .stack :
  {
    . = ALIGN(8);
    . += 0x00000800;   /* default stack size (adjust for your app) */
  } > sram

  /* Provide stack top symbol (useful for C startup) */
  __StackTop = ORIGIN(sram) + LENGTH(sram);
  __StackLimit = __StackTop - SIZEOF(.stack);
  PROVIDE(__stack = __StackTop);

  /* Provide typical symbols NuttX/startup and C runtime expect */
  PROVIDE(_etext = _etext);
  PROVIDE(_sdata = _sdata);
  PROVIDE(_edata = _edata);
  PROVIDE(_sbss = _sbss);
  PROVIDE(_ebss = _ebss);

  /* Small sanity assertion: ensure data fits into sram if you want it. */
  /* You can remove the ASSERT or change the region names to check sizes. */
  /* ASSERT(_edata <= ORIGIN(sram) + LENGTH(sram), "sram overflowed by .data") */
}
