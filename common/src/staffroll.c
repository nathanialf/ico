#include "common.h"

extern int D_0062C1B4;
extern int D_0062C1B8;
extern int D_0062C1BC;

void staffRollStart(int a0, int a1, int a2, int a3) {
    D_0062C1B4 = a1;
    D_0062C1B8 = a2;
    D_0062C1BC = a3;
}

extern int D_00629CB0;

int staffRollScroll(int a0, int a1, int a2, int *p, int *q, int *r) {
    int ret = 1;
    if (D_00629CB0 == 0) {
        *r = 1;
        *q = 1;
        *p = 1;
    } else {
        *p = D_0062C1B4;
        *q = D_0062C1B8;
        *r = D_0062C1BC;
        if (*q == 0) ret = 0;
        if (*p == 0) *p = 1;
        if (*q == 0) *q = 1;
        if (*r == 0) *r = 1;
    }
    *q = 0x32;
    return ret;
}

extern char D_0062B448;
extern int D_0062B44C;

void staffRollNameOut(void) {
    D_0062B448 = 0;
    D_0062B44C = -1;
}

extern float D_0062C1C4;
extern float D_0062C1C0;
extern float D_0062B45C;
extern float D_0062B460;
extern int D_0062B474;
extern int D_0062B458;
extern int D_004B8C80[];
extern int D_0062C1C8;
extern int D_0062C1DC;
extern int D_0062C1CC;
extern int D_0062C1D8;
extern unsigned char D_00700770[];
extern void func_00260568(void *a0, int a1, int a2);

void staffRollMain(int a0, float arg) {
    int z = 0;
    D_0062C1C4 = 0.0f;
    D_0062B474 = a0;
    D_0062B458 = 1;
    D_004B8C80[0] = 0x500;
    D_0062C1C0 = arg + arg;
    D_0062C1C8 = 0;
    D_0062C1DC = 0;
    D_0062C1CC = z;
    D_0062C1D8 = z;
    D_0062B460 = D_0062C1C4;
    D_0062B45C = D_0062C1C4;
    func_00260568(D_00700770, z, 0x12C0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", staffRollWide);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", func_001B58B0);

/* parked: needs jtbl carve + crutch-free rederivation.
 * See tough_nuts/func_001B59F0/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", func_001B59F0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004B8C90;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FD90;  /* stride 0x4 */

/* end struct shapes */
