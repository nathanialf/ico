/* config/link.pal.ld: the link script of the PAL retail ELF (SCES_507.60).
 *
 * Hand-written. Every output section sits at the base ELF's address, so a
 * section that comes up short fails the byte gate on its own and one that runs
 * long is an ld overlap error (no --no-check-sections). Inputs are taken in the
 * one object order of config/link_order.pal.txt, which is the order the objects
 * reach ld's command line. ld makes the one PT_LOAD itself; the link passes
 * -z max-page-size=0x1000, which gives it the base's file offset 0x1000 and
 * alignment (a PHDRS command leaves .sbss/.bss out of its memsz).
 *
 * Transitional lines, gone at the cut-over:
 *  - the two INCLUDEs: while the order file still carries part:/<sec>= tokens,
 *    tools/gen_ninja_plain.py lists .data and .rodata input by input there;
 *    with none they are empty and the wildcard after them places everything.
 *
 * What this script cannot give the file, measured with tools/check_elf.py
 * --full-diff against the base (report B-5): .vudata and .vubss keep their
 * names and addresses but come out PROGBITS/W and at the end of the file,
 * because no input carries them (the base's VU objects, from the DVP
 * assembler, bring empty .vudata "aw" and .vubss "aw",@nobits sections);
 * .reginfo's entsize 1 (ld writes 1 only for the IRIX-compatible
 * elf32-littlemips output, which Debian's mips-linux-gnu-ld does not have);
 * the .DVP.* overlay tables; the base linker's .shstrtab string order and
 * its file offsets of NOBITS and non-ALLOC sections.
 */
ENTRY(_start)

SECTIONS
{
    _gp = 0x00640AF0;

    .text 0x00100000 : { *(.text) }
    .vutext 0x00289BD0 : { *(.vutext) }
    /* Synthesised by ld's MIPS backend from the inputs' .reginfo; not ALLOC,
     * as in the base, so it takes no room in the image. */
    .reginfo 0x0028ECB0 : { *(.reginfo) }
    .data 0x0028ED00 : {
        INCLUDE build/plain/data.inputs.ld
        *(.data .data.*)
    }
    /* The assignment keeps the output section when its inputs are empty,
     * as the base's .vudata and .vubss are. */
    .vudata 0x0054D320 : { *(.vudata) . = .; }
    .rodata 0x0054D380 : {
        INCLUDE build/plain/rodata.inputs.ld
        *(.rodata .rodata.*)
    }
    .lit4 0x00638B00 : { *(.lit4) }
    .sdata 0x00639C80 : { *(.sdata .sdata.*) }
    .sbss 0x0063C100 (NOLOAD) : { *(.sbss) *(.scommon) }
    .bss 0x0063C600 (NOLOAD) : { *(.bss) *(COMMON) }
    .vubss . (NOLOAD) : { *(.vubss) . = .; }

    /DISCARD/ : { *(.mdebug) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }
}
