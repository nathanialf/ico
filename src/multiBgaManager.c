#include "common.h"

typedef struct {
    float f0;          /* 0x00 */
    char  pad04[0xC];  /* 0x04 */
    char  m10[0x10];   /* 0x10 */
    char  m20[0x10];   /* 0x20 */
    char  m30[0x10];   /* 0x30 */
    int   obj;         /* 0x40 */
    char  pad44[0xC];  /* 0x44 */
} BgaDisp;

typedef struct { long long w[10]; } MultiBga;
extern MultiBga D_004ECCA0;
extern char D_006208C8[];
extern int D_0063A438;
void *InitMultiBgaManager(int n) {
    MultiBga *base = (MultiBga *)iosMallocDebug(D_0063A438, n * 0x50, D_006208C8, 0xB);
    int i;
    for (i = 0; i < n; i++) {
        base[i] = D_004ECCA0;
    }
    return base;
}
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", EntryMultiBgaManager);
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", EntryMultiBgaManagerSensitive);
extern int D_0028F4C0[];
extern void _AddVector(void *a0, void *a1, void *a2);
extern float stage_PlayBgAnimation(int obj, void *a1, void *a2, float f);

void DispMultiBgaManager(BgaDisp *base, int n)
{
    int i;
    int ri;
    float f;
    for (i = 0; i < n; i++) {
        BgaDisp *e = &base[i];
        f = e->f0;
        if (f < 0.0f) {
            continue;
        }
        ri = (int)stage_PlayBgAnimation(e->obj, e->m10, e->m30, f);
        if (D_0028F4C0[5] != 0) {
            continue;
        }
        e->f0 = (float)ri;
        _AddVector(e->m10, e->m10, e->m20);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", EntryMultiBgaManagerNoKind);
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", DispMultiBgaManagerWithKind);
