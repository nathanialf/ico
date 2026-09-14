/* libgcc.a member _fixdfdi.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/_fixdfdi", __fixdfdi);
