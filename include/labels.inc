# This file is used by the original compiler/assembler.
# Defines the expected assembly macros.

# A function symbol.
.macro glabel label, visibility=global
    .\visibility \label
    .type \label, @function
    \label:
        .ent \label
.endm

# The end of a function symbol.
.macro endlabel label
    .size \label, . - \label
    .end \label
.endm

# An alternative entry to a function.
.macro alabel label, visibility=global
    .\visibility \label
    .type \label, @function
    \label:
        .aent \label
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
.macro dlabel label, visibility=global
    .\visibility \label
    .type \label, @object
    \label:
.endm

# End of a data symbol.
.macro enddlabel label
    .size \label, . - \label
.endm


# Label to signal the symbol haven't been matched yet.
.macro nonmatching label, size=1
    .global \label\().NON_MATCHING
    .type \label\().NON_MATCHING, @object
    .size \label\().NON_MATCHING, \size
    \label\().NON_MATCHING:
.endm
