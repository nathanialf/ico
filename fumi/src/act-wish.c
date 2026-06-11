#include "common.h"

extern int D_006A4428[];

typedef struct { char _0[0x1B8]; int f1B8; } WishC;
typedef struct { char _0[0x670]; WishC *f670; } WishB;
typedef struct { char _0[0x164]; WishB *f164; } WishA;
extern int InitMultiBgaManager(int a0);

void ACTGetWish_FromPad(WishA *a0) {
    int v = InitMultiBgaManager(1);
    a0->f164->f670->f1B8 = v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_00149F60);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A008);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A0B0);

extern void avoidInsideOfWall(void *p);

void func_0014A110(int *a0) {
    volatile int *o = (volatile int *)a0[0x59];
    void *p = (void *)o[0x58];
    if (p != 0) {
        avoidInsideOfWall(p);
        o[0x59] = 0;
        o[0x58] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A150);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A250);

void func_0014A3E0(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    *(float *)((char *)q + 0x58) = 1.0f;
    q[0x15] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A400);

extern int DispIcoMisc(int *buf);
extern void queen_barrier_anim(int a0, int a1, int a2, int *buf);
extern int D_00629C90;

void func_0014A4D0(int a0)
{
    int buf[4];
    int v0 = DispIcoMisc(buf);
    queen_barrier_anim(a0, D_00629C90, v0, buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", func_0014A510);

extern int D_002E0100[];

void func_0014A668(int *unused)
{
    int *dst = D_006A4428;
    char *src = (char *)D_002E0100;
    int i = 0x46;
    (void)unused;
    do {
        *dst = *(int *)src;
        i--;
        src += 0x94;
        dst++;
    } while (i >= 0);
}

extern int D_006A4428[];

void *func_0014A6A8(void) {
    return D_006A4428;
}

int func_0014A6B8(int a0, int a1) {
    int r = a0 ? 9 : 1;
    int t = r | 4;
    return a1 ? t : r;
}
