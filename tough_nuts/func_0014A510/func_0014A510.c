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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", ActGame_GetOrientQ);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", _GetRootObjectOrient);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", ACTCheckCollis_VIEW);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-wish", ACTCheckViewClDetail);

void func_0014A3E0(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    *(float *)((char *)q + 0x58) = 1.0f;
    q[0x15] = 0;
}

extern char D_0055DA10_a[] __asm__("D_0055DA10");
extern int D_00629DE8;
extern float GetHeightOfCliffFromGObj(void *a0, float a1);

float func_0014A400(int *a0) {
    int *p = (int *)a0[0x164 / 4];
    char *sub = (char *)p[0x670 / 4];
    unsigned int state = *(unsigned int *)(sub + 0x54);
    int flag = 0;
    float f12 = 1.0f;
    char *e;
    if (state < 3) {
        flag = (a0 == (int *)D_00629DE8);
    }
    if (state == 1) {
        e = D_0055DA10_a + ((int *)a0[0x15C / 4])[0x490 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 22) & 1) {
            f12 = *(float *)(sub + 0x58);
            flag = 0;
        }
    } else {
        e = D_0055DA10_a + ((int *)a0[0x15C / 4])[0x490 / 4] * 0x190;
        if (((*(unsigned int *)(e + 0x188) >> 21) & 1) == 0) {
            f12 = *(float *)(sub + 0x58);
        }
    }
    if (flag != 0) {
        f12 = 1.0f;
    }
    return GetHeightOfCliffFromGObj(a0, f12);
}

extern int DispIcoMisc(int *buf);
extern void queen_barrier_anim(int a0, int a1, int a2, int *buf);
extern int D_00629C90;

void GetGirlPositionAtThisStage(int a0)
{
    int buf[4];
    int v0 = DispIcoMisc(buf);
    queen_barrier_anim(a0, D_00629C90, v0, buf);
}

extern int D_002E0100[][37];
extern int D_005CA4B0[];

void func_0014A510(int *out, int mask, int seed)
{
    int j;
    volatile int home = seed;

    for (j = 0; j < 37; j++) {
        if ((mask >> j) & 1) {
            int *t = D_005CA4B0;
            int k;
            for (k = 0; k < 71; k++) {
                int v = D_002E0100[k][j];
                if (v > 0xFFFF) {
                    int base = v - 0x10000;
                    int cnt = 0;
                    int idx = base;
                    while (t[idx] != 0x440) {
                        idx++;
                        cnt++;
                    }
                    if (cnt != 0) {
                        v = t[base + home % cnt];
                    } else {
                        v = 0x440;
                    }
                }
                if (v != 0x440) {
                    out[k] = v;
                }
            }
        }
    }
}


extern int D_002E0100[][37];

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
