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
extern void memset(void *a0, int a1, int a2);

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
    memset(D_00700770, z, 0x12C0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/staffroll", staffRollWide);

extern int dl_Swap(void);
extern void debug_StdPrintfDummy(char *a0);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern int func_001F7718(char *a0, int a1);
extern int D_004B8C90[];
extern char D_0060FD60[];
extern char D_0060FD78[];
extern int D_0062B484;
extern char D_0062D2E8[];

typedef struct {
    int f0;
    float f4;
    unsigned char f8;
    unsigned char f9;
    unsigned char pad[6];
} Slot;
extern Slot staffroll_slots[] __asm__("D_00700770");

int func_001B58B0(void) {
    int n;
    int i;
    int off;
    int var5;
    unsigned char *p;
    int counter;
    int *ptr;
    char *slot;

    n = dl_Swap() + 1;
    if ((float)D_0062C1C8 <= D_0062C1C4 / (float)n) {
        p = D_00700770;
        off = 0;
        for (i = 0; i < 0x12C; i++) {
            if (*(int *)p == 0) {
                goto found;
            }
            off += 0x10;
            p += 0x10;
        }
        debug_StdPrintfDummy(D_0060FD60);
    found:
        func_001AAD00(D_0060FD78, 0xBD);
        __assert(D_0060FD78, 0xBD, D_0062D2E8);
        counter = D_0062C1C8;
        ptr = &D_004B8C90[counter];
        slot = (char *)&D_00700770[i * 0x10];
        D_0062C1C8 = counter + 1;
        if (*ptr != 0) {
            *(int *)slot = (int)ptr;
        }
        *(float *)(slot + 4) = (float)(dl_Swap() + 0x1C1);
        *(slot + 8) = (char)func_001F7718(slot + 9, **(int **)slot);
    }
    return D_0062C1C8 >= D_0062B484;
}


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
