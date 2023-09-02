ENTRY(Reset_Handler)

STACK_SIZE = 4K;

/* FLASH_ITCM aliases the FLASH_AXIM address space, but allows for ART caching and prefetch.
 * NOTE: ITCM and AXIM flash must always be paired with ALIGN_WITH_INPUT and
 * >FLASH_ITCM AT >FLASH_AXIM to ensure ITCM correctly aliases the right AXIM memory. */
MEMORY {
  ITCM_RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 16K
  FLASH_ITCM (rx) : ORIGIN = 0x00200000, LENGTH = 1M
  FLASH_AXIM (rx) : ORIGIN = 0x08000000, LENGTH = 1M
  DTCM_RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
  SRAM1 (rwx) : ORIGIN = 0x20010000, LENGTH = 240K
  SRAM2 (rwx) : ORIGIN = 0x2004C000, LENGTH = 16K
}

/* Section starts and ends are word aligned to allow for word copies.
 * Specifying ALIGN_WITH_INPUT and . = ALIGN(4) is the only way to ensure minimum VMA and LMA
 * alignment */
SECTIONS {
  .isr_vector : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    KEEP(*(.isr_vector))  /* Interrupt vector table */
  } >FLASH_ITCM AT >FLASH_AXIM

  .text : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    *(.text)
    *(.text*)
  } >FLASH_ITCM AT >FLASH_AXIM

  .rodata : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
  } >FLASH_ITCM AT >FLASH_AXIM

  .ARM : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    *(.ARM.exidx*)  /* Used for stack unwinding. */
  } >FLASH_ITCM AT >FLASH_AXIM

  /* Used by __libc_init_array() for constructors and destructors. */
  .preinit_array : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    __preinit_array_start = .;
    KEEP(*(.preinit_array*))
    __preinit_array_end = .;
  } >FLASH_ITCM AT >FLASH_AXIM

  .init_array : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    __init_array_start = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    __init_array_end = .;
  } >FLASH_ITCM AT >FLASH_AXIM

  .fini_array : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    __fini_array_start = .;
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array*))
    __fini_array_end = .;
  } >FLASH_ITCM AT >FLASH_AXIM

  /* Stack is allocated at beginning of DTCM so a stack overflow will generate a fault. */
  .stack (NOLOAD) : ALIGN(8) {
    . += STACK_SIZE;
    . = ALIGN(8);  /* Stack start (end of memory segment) should be 8 byte aligned. */
    _estack = .;
  } >DTCM_RAM

  .data : ALIGN_WITH_INPUT {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >DTCM_RAM AT >FLASH_AXIM
  _sidata = LOADADDR(.data);

  .bss (NOLOAD) : ALIGN(4) {
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >DTCM_RAM

  /* Catch and error on any unassigned input sections. */
  .orphan (NOLOAD) : {
    INPUT_SECTION_FLAGS(SHF_ALLOC) *(*)
  }
  ASSERT(SIZEOF(.orphan) == 0, "Unassigned input sections!")
}
