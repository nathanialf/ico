/*
 * ico2/common/src/demoDisc.c
 *
 * The demo disc's hand-back to the magazine menu: an argument parser and the
 * pair of functions that record the arguments the menu started the game with
 * and later reload the menu's ELF with them.  The file name is derived: the
 * build ships no map.  The code addresses its two words through $gp, so it is
 * a game object (-G 8), not part of libsndn2's sound.o, whose small static
 * the demo addresses with %hi/%lo; it follows sound.o in every section.
 */
#include "include_asm.h"
#include <eekernel.h>
#include <eeregs.h>
#include <stdio.h>

/* .sbss: the argument vector and count func_00246828 records, which
   DemoDiscEnd hands back to LoadExecPS2 with the menu's path */
static char **demoArgv; /* derived name */

static int demoArgc; /* derived name */

/* the decimal-string-to-short helper the argument parser calls six times
   (a nested function of func_00246828: $v0 carries the static chain) */
INCLUDE_ASM(func_002467B8);

INCLUDE_ASM(func_00246828);

void DemoDiscEnd(int status) /* derived name */
{
    *GS_BGCOLOR = 0;
    *GS_PMODE = 0;
    sprintf(demoArgv[7], "%d", status);
    LoadExecPS2("cdrom0:\\SCE_DD\\SCE_DD.ELF;1", demoArgc, demoArgv);
}
