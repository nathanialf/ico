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

/* the decimal-string-to-short helper the argument parser calls five times */
INCLUDE_ASM(func_002467B8);

/* .sbss: the argument vector and count func_00246828 records, which
   func_00246920 hands back to LoadExecPS2 with the menu's path */
static char **demoArgv; /* derived name */

static int demoArgc; /* derived name */

INCLUDE_ASM(func_00246828);

INCLUDE_ASM(func_00246920);
