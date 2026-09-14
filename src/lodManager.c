#include "common.h"

/* The layout-name table src/sceneManager.c and src/gamesys.c also index with
   0x64-byte records. */
extern char D_002C1270[];
/* Two parallel node tables indexed by the LOD level. */
extern int *D_004EB738[];
extern int *D_004EB748[];
extern char D_0061FB08[];
extern char D_0061FB40[];
extern void debug_StdPrintfDummy();
extern void SetMotionBlendlessNode(char *self, int *node);

void SetLodLevel(char *self, int lv)
{
    int n = *(int *)(self + 0xC);
    char *p;

    if (n >= 0) {
        debug_StdPrintfDummy(D_0061FB08, D_0061FB40, D_002C1270 + n * 0x64, D_004EB748[lv]);
    }
    SetMotionBlendlessNode(self, D_004EB738[lv]);
    p = *(char **)(self + 0x15C);
    if (p != 0) {
        if (*(int *)(p + 0x848) != 0) {
            (*(void (**)(int))(p + 0x848))(lv);
        }
    }
}
