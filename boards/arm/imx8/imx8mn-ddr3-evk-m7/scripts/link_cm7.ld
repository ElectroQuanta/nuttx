/* link_cm7_fixed.ld
   - VMAs are CM7 local (ITCM 0x0000_0000, DTCM 0x2000_0000)
   - LMAs are system windows where the flat binary will be copied:
       sys_itcm_load = 0x007E0000
       sys_dtcm_load  = 0x00800000
   - Provide symbols expected by startup: _sbss, _ebss, _sdata, _edata, _eronly, etc.
*/

OUTPUT_ARCH(arm)
ENTRY(__start)

MEMORY
{
  itcm_local   (rx) : ORIGIN = 0x00000000, LENGTH = 0x00020000  /* 128K VMA */
  dtcm_local   (rw) : ORIGIN = 0x20000000, LENGTH = 0x00020000  /* 128K VMA */

  /* LMAs (system windows) used for placement in the binary file */
  sys_itcm_load (r) : ORIGIN = 0x007E0000, LENGTH = 0x00020000
  sys_dtcm_load (rw): ORIGIN = 0x00800000, LENGTH = 0x00020000

  sram (rwx) : ORIGIN = 0x00900000, LENGTH = 0x00080000 /* optional */
}

/* Helpful named constants */
PROVIDE(__itcm_vma = ORIGIN(itcm_local));
PROVIDE(__dtcm_vma = ORIGIN(dtcm_local));
PROVIDE(__itcm_lma = ORIGIN(sys_itcm_load));
PROVIDE(__dtcm_lma = ORIGIN(sys_dtcm_load));

SECTIONS
{
  /* Start VMA at ITCM base */
  . = ORIGIN(itcm_local);

  /* Vectors: VMA at 0x0000_0000, LMA at sys_itcm_load */
  .vectors : AT(ORIGIN(sys_itcm_load))
  {
    KEEP(*(.vectors))       /* vector table (must be first) */
    __vectors_start = .;
    *(.vectors*)            /* any other vector-like sections */
    __vectors_end = .;
  } > itcm_local

  /* Text (.text & .rodata) in ITCM VMA, but LMA must follow vectors in file.
     We compute LMA start as sys_itcm_load + SIZEOF(.vectors). */
  .text : AT( ORIGIN(sys_itcm_load) + SIZEOF(.vectors) )
  {
    __text_start = .;
    *(.text*)               /* code */
    *(.rodata*)             /* read-only data following code */
    __text_end = .;
  } > itcm_local

  /* Align to word boundary after ITCM region in VMA */
  . = ALIGN(4);

  /* Data: VMA in DTCM local, LMA at sys_dtcm_load (we place init-data in file at this absolute address) */
  .data : AT( ORIGIN(sys_dtcm_load) )
  {
    __data_start = .;
    *(.data*)
    __data_end = .;
  } > dtcm_local

  /* BSS (NOLOAD) in DTCM VMA */
  .bss (NOLOAD) :
  {
    __bss_start = .;
    *(.bss*)
    *(COMMON)
    __bss_end = .;
  } > dtcm_local

  /* Provide stack top - typical choice: top of DTCM */
  PROVIDE(__stack_top = ORIGIN(dtcm_local) + LENGTH(dtcm_local));
  PROVIDE(__stack_bottom = __stack_top - 0x1000); /* optional reserve */

  /* Discard sections we don't need in flat binary */
  /DISCARD/ : { *(.note*) *(.comment) }
}

/* Aliases expected by your startup code (exact symbol names) */
PROVIDE(_sbss   = __bss_start);
PROVIDE(_ebss   = __bss_end);
PROVIDE(_sdata  = __data_start);
PROVIDE(_edata  = __data_end);

/* _eronly is the address in the binary where initialized data begins.
   We placed init-data in the file at ORIGIN(sys_dtcm_load), so set _eronly accordingly. */
PROVIDE(_eronly = ORIGIN(sys_dtcm_load));

/* Also provide common alternative names used by some code */
PROVIDE(__bss_start = __bss_start);
PROVIDE(__bss_end   = __bss_end);
PROVIDE(__data_start = __data_start);
PROVIDE(__data_end   = __data_end);

