#include "debug.h"
#include "motionManager2.h"
#include "lodManager.h"
#include "gamesys.h"
#include "include_asm.h"

/* Two node lists and the two parallel tables SetLodLevel indexes by the LOD
   level: level 0 is the demo mode
   (an empty node list, the leading -1), levels 1 and 2 share the same
   list, and level 3 gets every node. */
static int lodNodesGame[] = {
    -1, 0,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 36, 37, 40, 41, 48, 52, -1,
}; /* derived name */

static int lodNodesLow0[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, -1,
}; /* derived name */

static int *lodNodeTable[4] = {lodNodesGame, &lodNodesGame[2], &lodNodesGame[2],
                               lodNodesLow0}; /* derived name */

static char *lodNameTable[4] = {"DEMO MODE", "GAMEMODE HIGH", "GAMEMODE LOW",
                                "GAMEMODE LOW0"}; /* derived name */

INCLUDE_ASM(SetLodLevel);
