/*
 * ico2/common/src/demoDisc.c
 *
 * The demo disc's hand-back to the magazine menu: an argument parser and the
 * pair of functions that record the arguments the menu started the game with
 * and later reload the menu's ELF with them.  The file name is derived: the
 * build ships no map.  The Aug-6-2001 map links the same three functions as
 * /usr/local/sce/ee/lib/libscedemo.a(libscedemo.o) right after libsndn2
 * (.text 0x1b8: sceDemoStart at +0x70 and sceDemoEnd at +0x168, as here) with
 * argv_copy and argc_copy in .scommon, so the member was built -G 8: the code
 * addresses its two words through $gp, unlike libsndn2's sound.o, whose small
 * static the demo addresses with %hi/%lo; it follows sound.o in every section.
 */
#include "include_asm.h"
#include <eekernel.h>
#include <eeregs.h>
#include <stdio.h>

/* .sbss: the argument vector and count sceDemoStart records, which
   sceDemoEnd hands back to LoadExecPS2 with the menu's path (the Aug-6
   map's two common symbols of libscedemo.o; static here, which keeps them in
   .sbss under the game's -fno-common) */
static char **argv_copy;

static int argc_copy;

/* the decimal-string-to-short helper the argument parser calls six times
   (a nested function of sceDemoStart: $v0 carries the static chain) */
INCLUDE_ASM(func_002467B8);

INCLUDE_ASM(sceDemoStart);

void sceDemoEnd(int status)
{
    *GS_BGCOLOR = 0;
    *GS_PMODE = 0;
    sprintf(argv_copy[7], "%d", status);
    LoadExecPS2("cdrom0:\\SCE_DD\\SCE_DD.ELF;1", argc_copy, argv_copy);
}
