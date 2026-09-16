#include "common.h"

/* The layout-name table src/sceneManager.c and src/gamesys.c also index with
   0x64-byte records. */
extern char D_002C1270[];

/* Two parallel node tables indexed by the LOD level. */
/* lodManager.o's whole .data run.  Two node lists and the two parallel
   tables SetLodLevel indexes by the LOD level: level 0 is the demo mode
   (an empty node list, the leading -1), levels 1 and 2 share the same
   list, and level 3 gets every node. */
static int lodNodesGame[] = {
    -1, 0,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 36, 37, 40, 41, 48, 52, -1,
};

static int lodNodesLow0[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, -1,
};

static int *lodNodeTable[4] = {lodNodesGame, &lodNodesGame[2], &lodNodesGame[2], lodNodesLow0};

static char *lodNameTable[4] = {"DEMO MODE", "GAMEMODE HIGH", "GAMEMODE LOW", "GAMEMODE LOW0"};

extern void debug_StdPrintfDummy();
extern void SetMotionBlendlessNode(char *self, int *node);

void SetLodLevel(char *self, int lv)
{
    int n = *(int *)(self + 0xC);
    char *p;

    if (n >= 0) {
        /* %s: the LOD of "%s" was set to "%s" */
        debug_StdPrintfDummy(
            "%s: \"\033[36m%s\033[m\"のLODが\"\033[36m%s\033[m\"に設定されました\n", __FILE__,
            D_002C1270 + n * 0x64, lodNameTable[lv]);
    }
    SetMotionBlendlessNode(self, lodNodeTable[lv]);
    p = *(char **)(self + 0x15C);
    if (p != 0) {
        if (*(int *)(p + 0x848) != 0) {
            (*(void (**)(int))(p + 0x848))(lv);
        }
    }
}
