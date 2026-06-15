#include "common.h"

/* act2 0x164 actor-state view (local) */
typedef struct { char _0[0x438]; int f_438; } Act2State;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", BeforeFunc2);

void actDummy(void *a0, int a1) {
    Act2State *p = *(Act2State **)((char *)a0 + 0x164);
    if (p) {
        p->f_438 = a1;
    }
}

extern int D_00271240[];
extern void iosSemaCreate(void);

void func_002013B0(int a0, int a1) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201470);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void func_002015C8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

extern void debug_assertMessage(void *a0);
extern char D_00613C00[];

void func_002015F8(int a0, int *a1, int *a2) {
    int idx = a2[0];
    if (idx < 0x10) {
        a2[0] = idx + 1;
        a1[idx] = a0;
        return;
    }
    debug_assertMessage(D_00613C00);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201628);

extern void GetRootMatrixByDObj(void *out, void *obj);
extern void func_00240008(void *out, void *a, void *b);
extern float func_0023FE70(void *a, void *b);

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
    func_00240008(buf2, buf0, buf1);
    if (func_0023FE70(buf2, buf2) < threshold) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201840);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_002018E0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act2", func_00201AF0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070B520;  /* stride 0x8 */

/* end struct shapes */
