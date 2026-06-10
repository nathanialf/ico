#include "common.h"

extern int D_0062C260;

void dpk_SwapBuffer(int a0) {
    if (a0 < 0) {
        D_0062C260 = 0;
    } else if (a0 >= 0xD) {
        D_0062C260 = 0xC;
    } else {
        D_0062C260 = a0;
    }
}

extern int D_0070A5C0[];
extern int dl_GetPri(void);

void dpk_Init(int a0, int a1, int a2) {
    int *entry = &D_0070A5C0[D_0062C260 * 10];
    int old;
    if (entry[0]) {
        dl_GetPri();
    }
    old = entry[9];
    *(long long *)(entry + 6) = a0;
    entry[4] = a2;
    entry[0] = 1;
    *(long long *)(entry + 2) = (long long)a1 & 0xFFFFFFFLL;
    entry[1] = old;
    entry[9] = old + 0x10;
}


int dpk_CheckBufferSize(void) {
    return D_0062C260;
}

extern int D_0062A314;
extern int D_004C3850[];
extern int iosFree(int handle, int size, char *file, int line);

extern char D_00613770[];

void func_001F87B0(void)
{
    D_004C3850[0] = 0;
    D_004C3850[1] = iosFree(D_0062A314, 0x80000, D_00613770, 0x86) | 0x30000000;
    D_004C3850[2] = iosFree(D_0062A314, 0x80000, D_00613770, 0x87) | 0x30000000;
    D_004C3850[4] = (D_004C3850 + D_004C3850[0])[1];
}

/* CRUTCH (zero-byte asm): the empty "+r" barrier keeps `off` materialized
 * so combine can't refold off+4 into (idx+1)*4, and its extra refs give the
 * scaled value first allocno pick — both needed for the ROM register
 * rotation. Two 30-stall fires + permuter shots found no clean shape
 * (tough_nuts/func_001F8848/). Candidate for the crutch-strip workstream. */
void func_001F8848(void) {
    int idx = D_004C3850[0] ^ 1;
    int off;
    D_004C3850[0] = idx;
    off = idx * 4;
    __asm__("" : "+r"(off));
    D_004C3850[4] = *(int *)((char *)D_004C3850 + off + 4);
    D_004C3850[5] = 0;
    D_004C3850[6] = 0;
    D_004C3850[7] = 0;
}
