/* linker-imx8mn-itcm-flat.ld
 *
 * Build a single flat image whose LMA is ITCM (local 0x00000000).
 * The binary can be copied by U-Boot to system-level ITCM (0x007E0000)
 * and then started with "bootaux 0x007E0000".
 *
 * NOTE: All loadable (LMA) bytes are placed in ITCM. .data/.dtcm/.ramfunc
 *       VMAs remain in OCRAM/DTCM as appropriate but their LMA (initial
 *       image) is placed inside ITCM so startup can copy them into place.
 *
 * Ensure final binary (size of ITCM-resident loadable parts) <= 128K.
 */

OUTPUT_ARCH(arm)
ENTRY(__start)

MEMORY
{
  itcm (rwx)  : ORIGIN = 0x00000000, LENGTH = 128K
  dtcm (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
  sram (rwx)  : ORIGIN = 0x00900000, LENGTH = 512K /* OCRAM */
  flash (rx)  : ORIGIN = 0xC0000000, LENGTH = 256M /* QSPI Flash */
}
/* ITCM image: vectors + code + data initializers + ramfunc init + dtcm init */
SECTIONS
{
/* ITCM image: code and initializers */
.itcm_image : ALIGN(4)
{
  __sitcm = ABSOLUTE(.);
  KEEP(*(.vectors))
  *(.itcm.text .itcm.text.*)
  *(.text .text.*)
  *(.rodata .rodata.*)
  _eronly = ABSOLUTE(.);   /* end of readonly area in the image */

  /* data initializers (LMA inside the ITCM image) */
  .itcm_data_init : ALIGN(4)
  {
     KEEP(*(.itcm.data.init))      /* use explicit attr in C for items that must be in image */
  } > itcm

  /* ramfunc initializers (LMA inside the ITCM image) */
  .itcm_ramfunc_init : ALIGN(4)
  {
     KEEP(*(.itcm.ramfunc.init))   /* or other specific wildcard */
  } > itcm

  /* dtcm initializers (LMA inside the ITCM image) */
  .itcm_dtcm_init : ALIGN(4)
  {
     KEEP(*(.itcm.dtcm.init))
  } > itcm

  __eitcm = ABSOLUTE(.);
} > itcm

/* Now define the LOADADDR symbols for each init sub-section */
_ldata_load     = LOADADDR(.itcm_data_init);
_lramfuncs_load = LOADADDR(.itcm_ramfunc_init);
_ldtcm_load     = LOADADDR(.itcm_dtcm_init);

  /* Provide runtime VMA symbols for .data/.ramfunc/.dtcm (their VMAs are not in ITCM) */
  PROVIDE(_sdata = ORIGIN(sram));
  PROVIDE(_edata = ORIGIN(sram) + SIZEOF(.data));   /* note: SIZEOF(.data) computed at link time */
  PROVIDE(_sramfuncs = ORIGIN(sram) + SIZEOF(.data));
  PROVIDE(_eramfuncs = ORIGIN(sram) + SIZEOF(.data) + SIZEOF(.ramfunc));
  PROVIDE(__sdtcm = ORIGIN(dtcm));
  PROVIDE(__edtcm = ORIGIN(dtcm) + SIZEOF(.dtcm));

  /* BSS in OCRAM (runtime only) */
  .bss (NOLOAD) :
  {
    _sbss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > sram

  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    PROVIDE(__heap_start = .);
    . += 0x400;
    PROVIDE(__heap_end = .);
  } > sram

  .stack (NOLOAD) :
  {
    . = ALIGN(8);
    PROVIDE(__stack_top = .);
    . += 0x400;
    PROVIDE(__stack_limit = .);
  } > sram

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
