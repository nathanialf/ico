/* config/link.pal.ld: the link script of the PAL retail ELF (SCES_507.60).
 *
 * Hand-written. Every output section sits at the base ELF's address, so a
 * section that comes up short fails the byte gate on its own and one that runs
 * long is an ld overlap error (no --no-check-sections). Inputs are taken in the
 * one object order of config/link_order.pal.txt, which is the order the objects
 * reach ld's command line. ld makes the one PT_LOAD itself, at the base's
 * file offset 0x1000 and alignment, the page size of its elf32-littlemips
 * output (a PHDRS command leaves .sbss/.bss out of its memsz).
 *
 * Transitional lines, gone at the cut-over:
 *  - the two INCLUDEs: while the order file still carries part:/<sec>= tokens,
 *    tools/gen_ninja_plain.py lists .data and .rodata input by input there;
 *    with none they are empty and the wildcard after them places everything.
 *
 * The linker is GNU ld 2.10 with tools/binutils-2.10-ee.patch (built by
 * tools/setup.sh), writing elf32-littlemips as MAIN.MAP's OUTPUT line does:
 * that era's BFD gives the base's .shstrtab order, NOBITS file offsets and
 * .reginfo entsize 1, the patch the R5900 e_flags and the .DVP.ovlytab link.
 * ld 2.10 has no INCLUDE inside a section, so tools/gen_ninja_plain.py links
 * with build/plain/link.ld, this file with the INCLUDE lines expanded.
 *
 * What the link still does not give the file, measured with
 * tools/check_elf.py --full-diff (report B-6): .bss's 128 (debug_exception.c's
 * .bss in the base) and the names of the seven overlays dvp-as starts by
 * itself every 256 instructions, and so the string tables' sizes and every
 * file offset after .DVP.ovlystrtab.
 */
ENTRY(_start)

SECTIONS
{
    _gp = 0x00640AF0;
    /* The SDK script's start-up values, MAIN.MAP lines 724-726: crt0 hands
     * _stack and _stack_size to the SetupThread syscall and _heap_size to
     * SetupHeap. */
    _stack_size = 0x10000;
    _stack = 0x1ff0000;
    _heap_size = 0x10000;

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
    /* dvp-as's overlay table and its string table, not allocated: the base
     * has both at the end of .vubss. The .DVP.overlay.* sections follow as
     * orphans, one output section per input section at address 0, by the
     * linker's own DVP rule (tools/binutils-2.10-dvp-ld.patch). */
    .DVP.ovlytab 0x00736198 : { *(.DVP.ovlytab) }
    .DVP.ovlystrtab 0x00736198 : { *(.DVP.ovlystrtab) }

    /DISCARD/ : { *(.mdebug) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }
}
