/* Linker script for NuttX on i.MX8MN (M7)
 * ENTRY symbol: __start (NuttX)
 *
 * Memory regions based on values you provided:
 *   itcm  : 0x00000000 (128K)
 *   dtcm  : 0x20000000 (128K)
 *   sram  : 0x00900000 (512K)  (OCRAM)
 *   flash : 0xC0000000 (256M)  (QSPI)
 */

#include <nuttx/config.h>

OUTPUT_ARCH(arm)
ENTRY(__start)

MEMORY
{
  itcm  (rwx) : ORIGIN = 0x00000000, LENGTH = 128K
  dtcm  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
  /* sram  (rwx) : ORIGIN = 0x00900000, LENGTH = 512K */
  /* flash (rx)  : ORIGIN = 0xC0000000, LENGTH = 256M */
}

EXTERN(_vectors)

SECTIONS
{
	.interrupts :
	{
	_stext = ABSOLUTE(.);
	*(.vectors)
	. = ALIGN(128);
	} > itcm

    .text :
    {
        /* _stext = ABSOLUTE(.); */
        /* *(.vectors) */
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
		. = ALIGN(8);
        _etext = ABSOLUTE(.);
    } > itcm

    .init_section :
    {
        _sinit = ABSOLUTE(.);
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP(*(.init_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o) .ctors))
        _einit = ABSOLUTE(.);
    } > itcm

    .ARM.extab :
    {
        *(.ARM.extab*)
    } > itcm

    .ARM.exidx :
    {
        __exidx_start = ABSOLUTE(.);
        *(.ARM.exidx*)
        __exidx_end = ABSOLUTE(.);
    } > itcm

    _eronly = ABSOLUTE(.);
	__DATA_ROM = _eronly;

    .data : AT(__DATA_ROM)
    {
        _sdata = ABSOLUTE(.);
        *(.data .data.*)
        *(.gnu.linkonce.d.*)
        CONSTRUCTORS
        . = ALIGN(8);
        _edata = ABSOLUTE(.);
    } > dtcm 

    .bss :
    {
        _sbss = ABSOLUTE(.);
        *(.bss .bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(8);
        _ebss = ABSOLUTE(.);
    } > dtcm

	/* Idle stack lives in DTCM; NOLOAD so it isn't zero-filled by the loader */
	.idle_stack (NOLOAD) : ALIGN(8)
	{
	_sstack_idle = .;                         /* low address (stack grows down) */
	. = . + CONFIG_IDLETHREAD_STACKSIZE;      /* e.g., 4096 */
	. = ALIGN(8);
	_estack_idle = .;                         /* top of idle stack */
	} > dtcm

    /* Stabs debugging sections. */

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
}
