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

void func_00201470(void *self) {
    void *p = *(void **)((char *)self + 0x164);

    if (p == 0) {
        return;
    }
    {
        void *list[3] = {
            *(void **)((char *)p + 0xB4),
            *(void **)((char *)p + 0xB0),
            (void *)-1
        };
        int *ctx = (int *)((char *)self + 0x54);
        int k = 0;
        int n;
        int id;
        int j;
        int off;
        int *arr;
        Act2Ent *e;
        Act2Desc *d;

        if (list[0] == (void *)-1) {
            ctx[1] = 0;
            return;
        }
    loop_head:
        d = (Act2Desc *)list[k];
        if (d == 0) {
            goto inc;
        }
        if (d->f_0 == 0x188) {
            k++;
            goto advance;
        }
    scan:
        n = ctx[1];
        if (n > 0) {
            id = d->f_0;
            arr = ctx + 2;
            j = 0;
            do {
                if (arr[j << 1] == id) {
                    goto found;
                }
                j++;
            } while (j < n);
        }
        d++;
        if (d->f_0 != 0x188) {
            goto scan;
        }
    inc:
        k++;
    advance:
        if (list[k] != (void *)-1) {
            goto loop_head;
        }
        ctx[1] = 0;
        goto end;
    found:
        *(int *)((char *)p + 0xB8) = id;
        ctx[1] = 0;
        if (d->f_4) {
            actChangeActMain(D_0062A4DC, d->f_4, (void **)((char *)p + 4));
        }
        if (d->f_C) {
            actCreateSubThread(d->f_C, 0x14);
        }
        if (d->f_8) {
            actCreateMotionThread(d->f_8, (void *)0x15, (void **)((char *)p + 8));
        }
    end:;
    }
}


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
