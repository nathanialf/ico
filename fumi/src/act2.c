#include "common.h"

/* act2 0x164 actor-state view (local) */
typedef struct { char _0[0x438]; int f_438; } Act2State;

extern void sceVu0TransposeMatrix(void *a0, void *a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern int D_00629C70;

typedef union { float f[4]; long long ll[2]; } Vec4;

void BeforeFunc2(void *a0, float *a1) {
    Vec4 v = {{ a1[3], 0.0f, -a1[4], 0.0f }};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)(D_00629C70 + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}

void actDummy(void *a0, int a1) {
    Act2State *p = *(Act2State **)((char *)a0 + 0x164);
    if (p) {
        p->f_438 = a1;
    }
}

extern int D_00271240[];
extern void iosSemaCreate(void);

void actWaitCondition(int a0, int a1) {
    int t = a0 & a1;
    if (t == 0) {
        do {
            int count = (0x3C - D_00271240[0] * 0xA) / D_00271240[1] / 0x3C;
            int n = 1;
            if (count != 0) {
                n = count;
            }
            if (n == 0) {
                for (;;) {
                    iosSemaCreate();
                }
            }
            if (n > 0) {
                int i = n;
                do {
                    iosSemaCreate();
                    i--;
                } while (i != 0);
            }
        } while (t == 0);
    }
}

extern void actChangeActMain(void *a0, void *a1, void **a2);
extern int actCreateSubThread(void *a0, int a1);
extern void actCreateMotionThread(void *a0, void *a1, void **a2);
extern void *D_0062A4DC;

typedef struct {
    unsigned short f_0;
    unsigned short pad2;
    void *f_4;
    void *f_8;
    void *f_C;
} Act2Desc;

typedef struct {
    int id;
    int w;
} Act2Ent;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201470);


extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void func_002015C8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

extern void debug_StdPrintfDummy(void *a0);
extern char D_00613C00[];

void func_002015F8(int a0, int *a1, int *a2) {
    int idx = a2[0];
    if (idx < 0x10) {
        a2[0] = idx + 1;
        a1[idx] = a0;
        return;
    }
    debug_StdPrintfDummy(D_00613C00);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201628);

extern void GetRootMatrixByDObj(void *out, void *obj);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern float sceVu0InnerProduct(void *a, void *b);

int func_002017A0(void *a0, void *a1, void *a2) {
    float buf0[4];
    float buf1[4];
    float buf2[4];
    float threshold;
    threshold = (float)(*(int *)((char *)a2 + 0x30) * *(int *)((char *)a2 + 0x30));
    if (a0 == 0 || a1 == 0) {
        return 0;
    }
    GetRootMatrixByDObj(buf0, a0);
    GetRootMatrixByDObj(buf1, a1);
    sceVu0SubVector(buf2, buf0, buf1);
    if (sceVu0InnerProduct(buf2, buf2) < threshold) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201840);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", WayLengthOfPos_Pos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", WayPointWithRangeFromPos);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070B520;  /* stride 0x8 */

/* end struct shapes */
