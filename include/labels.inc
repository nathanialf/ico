# This file is used by the original compiler/assembler.
# Defines the expected assembly macros.

# A function symbol.
# __in_text tracks whether we are inside a function body so dlabel (below)
# can tell in-function embedded data from splat-migrated rodata blocks.
.macro glabel label, visibility=global
    __in_text = 1
    .\visibility \label
    .type \label, @function
    \label:
        .ent \label
.endm

# The end of a function symbol.
.macro endlabel label
    .size \label, . - \label
    .end \label
    __in_text = 0
.endm

# An alternative entry to a function.
.macro alabel label, visibility=global
    .\visibility \label
    .type \label, @function
    \label:
    /* .aent omitted: ee-as 2.10 doesn't support the pseudo and it's
     * stabs debugger metadata only — no effect on emitted bytes. */
.endm

# A label referenced by an error handler table.
.macro ehlabel label, visibility=global
    .\visibility \label
    \label:
.endm


# A label referenced by a jumptable.
#
# visibility=global so jumptable target labels (e.g. `.L0010F564`) emit
# as global symbols. ICO has one giant rodata subseg (no per-TU .rodata),
# so when an INCLUDE_ASM'd function's rodata jumptable lands in the global
# rodata .o, its `.word .L*` references must cross .o boundaries — only
# global labels resolve. Upstream default is local (parappa2/oot use
# per-TU .rodata subsegs so the migration keeps them local within one .o).
.macro jlabel label, visibility=global
    .\visibility \label
    \label:
.endm


# A data symbol.
#
# A dlabel block that is a splat-migrated rodata object switches into its
# own `.rodata.<sym>` section (the rodata analog of INCLUDE_ASM_FS / gcc's
# -fdata-sections, whose section names the C-side carve defs already
# carry).  labels.inc is included only by C-TU compiles (blob data objects
# use macro.inc), so this fires exactly for stub rodata and INCLUDE_RODATA
# blocks.  Without it, every stub block appends to ONE plain `.rodata`
# input section positioned at the first block's file order, so a full-run
# per-TU carve cannot interleave stub-emitted rodata with C definitions.
# With per-symbol sections, .o section order == source order == VMA order
# and the whole-object `(.rodata*)` glob reproduces the original layout.
#
# The switch must NOT fire for a dlabel naming data embedded inside a
# .text function body (vendor constant pools, e.g. vendor_252D28's
# D_00254CE0, whose block even carries the data-form `nonmatching`) —
# yanking those into .rodata breaks the function's bytes and its
# cross-section .size.  Discriminator: in-function data can only appear
# between glabel and endlabel/enddlabel, so glabel arms __in_text and both
# end macros disarm it; dlabel switches sections only OUTSIDE a function
# body.  (An in-text data run is closed by `enddlabel <funcname>` sizing
# the whole function, which is why enddlabel must also clear the flag.)
#
# The .align 3 mirrors what splat emits ahead of every migrated
# block (ee-gcc pads each rodata object to 8); a block whose VMA is only
# 4-aligned would need special handling — none exists in the current split.
__in_text = 0
.macro dlabel label, visibility=global
    .if __in_text == 0
        .section .rodata.\label, "a", @progbits
        .align 3
    .endif
    .\visibility \label
    .type \label, @object
    \label:
.endm

# End of a data symbol.  Also closes an in-.text embedded-data run (see
# dlabel above), where splat sizes the enclosing FUNCTION with enddlabel.
.macro enddlabel label
    .size \label, . - \label
    __in_text = 0
.endm


# Label to signal the symbol haven't been matched yet.
.macro nonmatching label, size=1
    .global \label\().NON_MATCHING
    .type \label\().NON_MATCHING, @object
    .size \label\().NON_MATCHING, \size
    \label\().NON_MATCHING:
.endm
