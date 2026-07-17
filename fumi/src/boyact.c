#include "common.h"

/* boyact 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; } BoyState;
#include "ico/types.h"

void findChainInJump(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", CorrectOrient_RopeCliff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", motBoyHand100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", motBoyHand200);

extern char D_00552530[];
extern void *D_00629DE8;
extern void *D_0062A4DC;
extern void debug_assertMessage(void *msg);
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(void *a0, int a1);

void hand_heroin(volatile int a0)
{
    int *m = *(int **)((char *)a0 + 0x164);

    debug_assertMessage(D_00552530);
    while (1) {
        if (D_00629DE8 != 0) {
            iosOmBeforeFuncStandard(D_00629DE8, 0x54, D_0062A4DC);
        }
        if (*(int *)((char *)m + 0xC0) & 1) {
            break;
        }
        _ACTWait(1);
    }
    while (1) {
        if (*(int *)(*(int *)((char *)a0 + 0x15C) + 0x490) >= 0 &&
            *(int *)(*(int *)((char *)a0 + 0x15C) + 0x490) < 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        if (D_00629DE8 != 0) {
            iosOmBeforeFuncStandard(D_00629DE8, 0x55, D_0062A4DC);
        }
        if (*(int *)((char *)m + 0xC0) & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(0x2D);
    *(int *)((char *)m + 0x14) = 0;
    while (1) {
        BoxBarSoundOn((void *)a0, 0x42);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014C0C0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014C370);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014C660);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", CheckCollisionAttr);

typedef struct { char pad[4]; float f4; } CCPResult;
extern float D_00628E24;

typedef struct {
    char _0[4];
    float f4;          /* 0x4 */
    float f8;          /* 0x8 */
    char _c;           /* 0xC */
    unsigned char fD;  /* 0xD */
    char _e;           /* 0xE */
    unsigned char fF;  /* 0xF */
    float f10;         /* 0x10 */
    char _14[12];      /* 0x14 */
    char f20[4];       /* 0x20 */
    float f24;         /* 0x24 */
    char _28[8];       /* 0x28 */
    char f30[16];      /* 0x30 */
} Geo;

extern void *subCommonIdle(void *a0);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern void func_00191FD0(void *a0, void *a1, void *a2);
extern void func_00240038(void *a0, void *a1, float a2);
extern void func_0014A008(void *a0, void *a1, int a2);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void func_00191DB8(void *a0, float a1);

/* BoyBgaManager */
typedef struct {
    int field0;
    char _4[0x8];
    unsigned char fC;
    char _d;
    unsigned char fE;
    char _f[0x11];
    char f20[0x10];
    char f30[0x10];
} BgaEntry;

extern BgaEntry D_0027DF90[];
extern char D_005525C8[];
extern char D_0062C3F8[];
extern void func_001AAD00(char *file, int line);
extern void func_00260380(char *file, int line, char *msg);
extern float stage_SetParentOfGObj(int a0, void *a1, void *a2, float a3);

void BoyBgaManager(void *a0, int a1, int *a2) {
    BgaEntry *found;
    int i;
    int result;
    void UpdateGeo(Geo *e) {
        float buf_a[4];
        float buf_b[4];
        if (e->fF != 0) {
            buf_a[0] = ((float *) subCommonIdle(a0))[0];
            buf_a[1] = ((float *) subCommonIdle(a0))[1];
            buf_a[2] = ((float *) subCommonIdle(a0))[2];
        } else {
            void *g = isysGObjSearchFromObjLayoutID(0x2E);
            func_00191FD0(buf_a, ContinueCorrectPosition(g), ContinueCorrectPosition(a0));
        }
        func_00240038(buf_a, buf_a, e->f10);
        func_0014A008(e->f30, buf_a, 0);
        func_00240038(buf_b, subCommonIdle(a0), e->f8);
        func_0023FFF0(e->f20, ContinueCorrectPosition(a0), buf_b);
        func_00240038(buf_b, subCommonIdle(a0), e->f4);
        func_00191DB8(buf_b, D_00628E24);
        func_0023FFF0(e->f20, e->f20, buf_b);
        e->f24 = e->f24 + (float) e->fD;
    }
    i = 0;
    if (D_0027DF90[0].field0 >= 0) {
        for (;;) {
            if (D_0027DF90[i].field0 == a1) {
                found = &D_0027DF90[i];
                goto have_found;
            }
            i++;
            if (D_0027DF90[i].field0 < 0) {
                break;
            }
        }
    }
    found = 0;
    func_001AAD00(D_005525C8, 0x5D5);
    func_00260380(D_005525C8, 0x5D5, D_0062C3F8);
have_found:
    if (*a2 >= 0) {
        if (found->fC != 0) {
            UpdateGeo((Geo *) found);
        } else if (*a2 == 0) {
            UpdateGeo((Geo *) found);
        }
        result = (int) stage_SetParentOfGObj(found->field0, found->f20, found->f30, (float) *a2);
        if (found->fE == 0) {
            *a2 = result;
        } else if (result >= 0) {
            *a2 = result;
        }
    }
}


extern unsigned char D_0062BFDE;
extern unsigned char D_0062BFDF;
extern unsigned char D_0062BFE0;
extern void *subCommonIdle(void *a0);
extern void func_00240038(void *a0, void *a1, float a2);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void CylinderCollision(void *a0, void *a1);
extern int func_00178DB0(int a0);
extern void func_00178E08(int a0);
extern int staffRollScroll(void *a0, int a1, int a2, int *p, int *q, int *r);
extern void _ACTWait(int a0);
extern void func_001790A8(void *a0);
extern void BoySekikaTexScroll(void *a0, int a1);
extern void func_001790E8(void *a0);

void E3_StageStartBoy(void *a0) {
    float buf[4];
    int w10, w14, w18;

    if (D_0062BFDE) {
        func_00240038(buf, subCommonIdle(a0), 100.0f);
        func_0023FFF0(buf, buf, ContinueCorrectPosition(a0));
        CylinderCollision(a0, buf);
    }
    if (func_00178DB0(0x15B)) {
        func_00178E08(0x15B);
        return;
    }
    if (staffRollScroll(a0, 0, 0, &w10, &w14, &w18)) {
        if (D_0062BFE0) {
            return;
        }
        if (D_0062BFDF) {
            return;
        }
        _ACTWait(3);
        staffRollScroll(a0, 0, 0, &w10, &w14, &w18);
        _ACTWait(w10);
        func_001790A8(a0);
        BoySekikaTexScroll(a0, 7);
        _ACTWait(w14);
        func_001790E8(a0);
        _ACTWait(w18);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", GetChainSlope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", subBoyControl);

extern int isysGObjAddHead();
extern void *disp_memory_partition(int a0, int a1);
extern char D_002A0A90[];
extern float D_00628EE4;
extern long long D_006A45A0[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014E858);


extern long long D_006A45A0[];
extern void GetLowerPlaneCollision(char *p, float a, float b, float c, float d, float e, float f);
extern void func_00102828(int obj);

void InitSwapWeapon(void)
{
    char *base = (char *)D_006A45A0;
    int *obj_ptr = *(int **)(base + 0x20);
    char *sub;
    if (obj_ptr == 0) return;
    sub = ((GObj *)((char *)obj_ptr))->p_15C;
    GetLowerPlaneCollision(sub + 0xA0,
                  *(float *)(base + 0x30),
                  *(float *)(base + 0x34),
                  *(float *)(base + 0x38),
                  -*(float *)(base + 0x40),
                  -*(float *)(base + 0x44),
                  -*(float *)(base + 0x48));
    func_00102828(*(int *)(base + 0x20));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", PutWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", OtherStageGirlPinchCamera_After);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014FBA8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014FD98);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_0014FF08);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150078);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150298);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150420);


extern void *D_00629DE4;
extern void *D_00629DE8;
extern CCPResult *ContinueCorrectPosition(void *);
extern void func_00240008(void *, CCPResult *, CCPResult *);
extern float func_0023FE70(void *, void *);
extern float InitHandCameraCorrect(void *, CCPResult *);

int func_00150608(void) {
    void *g = *(int *)((char *)D_00629DE4 + 0x164);
    CCPResult buf;
    CCPResult *r16 = ContinueCorrectPosition(D_00629DE8);
    func_00240008(&buf, r16, ContinueCorrectPosition(D_00629DE4));
    if (func_0023FE70(&buf, (char *)g + 0x4B0) > 0.0f) {
        if (InitHandCameraCorrect((char *)g + 0x4F0, ContinueCorrectPosition(D_00629DE8)) < 100.0f) {
            void *g2 = *(int *)((char *)D_00629DE8 + 0x164);
            long long flag = *(unsigned short *)((char *)g2 + 0x1E);
            if (((int)flag & 1) == 0) return 0;
            if (D_00629DE8 == 0) goto r1;
            if (D_00629DE4 == 0) goto r1;
            {
                CCPResult *ra = ContinueCorrectPosition(D_00629DE8);
                CCPResult *rb = ContinueCorrectPosition(D_00629DE4);
                if (rb->f4 + 450.0f < ra->f4) goto r0;
            }
r1:
            return 1;
r0:
            return 0;
        }
    }
    return 0;
}




int subBoyCollision(void) {
    void *g = *(int *)((char *)D_00629DE4 + 0x164);
    CCPResult buf;
    CCPResult *r16 = ContinueCorrectPosition(D_00629DE8);
    func_00240008(&buf, r16, ContinueCorrectPosition(D_00629DE4));
    if (func_0023FE70(&buf, (char *)g + 0x4B0) > 0.0f) {
        if (InitHandCameraCorrect((char *)g + 0x500, ContinueCorrectPosition(D_00629DE8)) < 31.0f) {
            if (D_00629DE8 == 0) goto r1;
            if (D_00629DE4 == 0) goto r1;
            {
                CCPResult *ra = ContinueCorrectPosition(D_00629DE8);
                CCPResult *rb = ContinueCorrectPosition(D_00629DE4);
                if (rb->f4 + 450.0f < ra->f4) goto r0;
            }
r1:
            return 1;
r0:
            return 0;
        }
    }
    return 0;
}



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoySwim);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150A30);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150BC8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00150FA4);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00151440);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", func_00151840);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", actBoyWalk);

extern void BeforeFunc2(void *a0);
extern void HandCameraCorrect(void *a0, void *a1);

void actBoyRun(void *a0) {
    char buf[0x10];
    BeforeFunc2(buf);
    HandCameraCorrect(buf, a0);
}

extern void *D_00629DE4;

int actBoyAttack(void) {
    void *p = D_00629DE4;
    void *q;
    if (p == 0) goto ret0;
    q = *(void **)((char *)p + 0x164);
    return *(int *)((char *)q + 0x130);
ret0:
    return 0;
}

typedef struct { char _0[0x188]; unsigned int f188; char _18c[4]; } WpnEntry;
extern char D_0055DA10[];

void actBoyTakeWeaponReady(int *volatile a0) {
    int idx = *(int *)((char *)*(int **)((char *)a0 + 0x15C) + 0x490);
    if ((((WpnEntry *)(D_0055DA10 + idx * 0x190))->f188 >> 11) & 1) {
        funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7C0);
    }
    while (1) {
        _ACTWait(1);
    }
}


void func_00151E98(int *volatile a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7C0);
    _ACTWait(0);
}


void actBoyTakeWeapon(int *volatile a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7C0);
    _ACTWait(0);
}

extern void debug_assertMessage(void *);
extern char D_00552940[];

void pullup_check_heroin_position(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00552940);
    *(int *)((char *)obj + 0x30) = 5;
    while (1) {
        _ACTWait(1);
    }
}

extern char D_00552988[];
extern void iosOmBeforeFuncStandard(void *, int, void *);
extern void *D_0062A4DC;

void func_00151F48(volatile int a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00552988);
    *(int *)((char *)obj + 0x30) = 9;
    _ACTWait(2);
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard(D_00629DE8, 0x3C, D_0062A4DC);
    }
    while (1) {
        if (!(*(int *)((char *)obj + 0x2D0) & 8)) {
            BoxBarSoundOn(a0, 0xB4);
        }
        _ACTWait(1);
    }
}

extern void BoxBarSoundOn(void *a0, int a1);

void func_00151FC0(volatile int a0) {
    while (1) {
        BoxBarSoundOn(a0, 0xB4);
        _ACTWait(1);
    }
}

extern char D_005529A0[];

void func_00151FF0(volatile int a0) {
    float buf[4];
    debug_assertMessage(D_005529A0);
    while (1) {
        func_00240038(buf, subCommonIdle(a0), 15.0f);
        BoxBarSoundOn(a0, 0xB4);
        _ACTWait(1);
    }
}

extern float fzMagnitudefv(int a0, int a1, int a2);
extern void brainInitGirlSet(void);

void func_00152050(volatile int a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7D0);
    fzMagnitudefv(*(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7E0,
                  *(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7D8),
                  *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7D0);
    while (1) {
        if (D_00629DE8 != 0) {
            brainInitGirlSet();
            if (D_00629DE8 != 0) {
                iosOmBeforeFuncStandard(D_00629DE8, 0x39, D_0062A4DC);
            }
        }
        BoxBarSoundOn(a0, 0x114);
        _ACTWait(1);
    }
}

typedef struct { long long a; int b; } __attribute__((packed, aligned(4))) S12u;
void func_001520F8(volatile int a0) {
    extern void funcCommonJumpDircorrect();
    int *p = *(int **)((char *)a0 + 0x164);
    int q0, q1, q2, q3;
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7D0);
    q0 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    q1 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    *(float *)(q0 + 0x410) = *(float *)((char *)p + 0x4B0);
    q2 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    q3 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    *(float *)(q1 + 0x414) = *(float *)((char *)p + 0x4B4);
    *(float *)(q2 + 0x418) = *(float *)((char *)p + 0x4B8);
    *(S12u *)(q3 + 0x420) = *(S12u *)((char *)p + 0x620);
    while (1) { BoxBarSoundOn(a0, 0x114); _ACTWait(1); }
}

typedef struct { char _0[0x20]; float f20; int i24; int i28; int _2c; } __attribute__((aligned(8))) Buf30;
extern float RotateAccordingToStick_PatternThree(CCPResult *a0, void *a1);
extern void funcCommonFallDircorrect(int a0, void *a1);

void func_001521A8(volatile int a0) {
    void *m = *(void **)((char *)a0 + 0x164);
    Buf30 buf;
    buf = *(Buf30 *)*(void **)((char *)(*(int *)((char *)a0 + 0x164)) + 0x2C);
    while (1) {
        funcCommonFallDircorrect(a0, (char *)&buf + 0x10);
        if (buf.i28 != 0) {
            long long v = *(long long *)((char *)m + 0x480);
            v |= 0x1000;
            v |= 2;
            *(long long *)((char *)m + 0x480) = v;
        }
        if (buf.i24-- < 0) BoxBarSoundOn(a0, 0xF7);
        if (RotateAccordingToStick_PatternThree(ContinueCorrectPosition((void *)a0), &buf) < buf.f20 * buf.f20)
            BoxBarSoundOn(a0, 0xF7);
        _ACTWait(1);
    }
}

extern void *D_0062BFE8;

void func_001522B8(volatile int a0) {
    void *obj = (char *)*(void **)((char *)a0 + 0x15C) + 0x120;
    func_00240038(obj, subCommonIdle(D_0062BFE8), 30.0f);
    while (1) {
        BoxBarSoundOn(a0, 0x124);
        _ACTWait(1);
    }
}

void func_00152310(volatile int a0) {
    while (1) {
        BoxBarSoundOn(a0, 0xB4);
        _ACTWait(1);
    }
}

extern void iosOmBeforeFuncStandard(void *, int, void *);
extern void *D_0062A4DC;

void func_00152340(volatile int a0) {
    while (1) {
        if (D_00629DE8 != 0) {
            iosOmBeforeFuncStandard(D_00629DE8, 0x15D, D_0062A4DC);
        }
        BoxBarSoundOn(a0, 0x15B);
        _ACTWait(1);
    }
}

static __inline__ unsigned char boyStateIsGrab(void) {
    void *p = D_00629DE8;
    void *q = p;
    unsigned int lo = *(unsigned int *)((char *)*(void **)((char *)p + 0x164) + 0x30);
    unsigned int hi = *(unsigned int *)((char *)*(void **)((char *)q + 0x164) + 0x30);
    if (hi >= 0x68) return 0;
    if (lo < 0x65) return 0;
    return 1;
}

void func_00152380(volatile int a0) {
    while (1) {
        if (!boyStateIsGrab()) {
            BoxBarSoundOn(a0, 0xCF);
        }
        _ACTWait(1);
    }
}

void func_001523E0(volatile int a0) {
    while (1) {
        if (D_00629DE8 != 0) {
            iosOmBeforeFuncStandard(D_00629DE8, 0x15F, D_0062A4DC);
        }
        BoxBarSoundOn(a0, 0xB4);
        _ACTWait(1);
    }
}

void func_00152420(volatile int a0) {
    while (1) {
        BoxBarSoundOn(a0, 0x163);
        _ACTWait(1);
    }
}

void func_00152450(volatile int a0) {
    while (1) {
        BoxBarSoundOn(a0, 0x16E);
        _ACTWait(1);
    }
}

extern float D_00628F18;
extern unsigned char D_0062BFDD;

void func_00152480(volatile int a0) {
    void *obj = *(void **)((char *)a0 + 0x164);
    float thresh = D_00628F18;
    while (1) {
        if (thresh < *(float *)((char *)obj + 0x33C) ||
            (*(int *)((char *)obj + 0x2D0) & 0x10)) {
            BoxBarSoundOn(a0, 0x170);
            if (D_00629DE8 != 0) {
                iosOmBeforeFuncStandard(D_00629DE8, 0x173, D_0062A4DC);
            }
        }
        _ACTWait(1);
    }
}

int func_00152500(void) {
    return D_0062BFDD;
}

extern void debug_assertMessage(void *);
extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00552500[];
extern char D_00552518[];
void func_00152588(volatile int a0);

void ditch_check_heroin_position(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00552500);
    *(int *)((char *)obj + 0x30) = 0x4F;
    *(void **)((char *)obj + 0x14) = (void *)func_00152588;
    *(int *)((char *)obj + 0xC0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)((char *)obj + 0xC0) & 0x10) == 0);
    debug_assertMessage(D_00552518);
    while (1) {
        BoxBarSoundOn(a0, 0x58);
        _ACTWait(1);
    }
}


extern void debug_assertMessage(void *);
extern void iosOmBeforeFuncStandard(void *, int, void *);
extern char D_005524F0[];
extern void *D_0062A4DC;

void func_00152588(volatile int a0) {
    debug_assertMessage(D_005524F0);
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard(D_00629DE8, 0x58, D_0062A4DC);
    }
}


extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00552548[];
extern char D_00552560[];
void func_00152640(volatile int a0);

void actBoyPullupReady(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00552548);
    *(int *)((char *)obj + 0x30) = 0x50;
    *(void **)((char *)obj + 0x14) = (void *)func_00152640;
    *(int *)((char *)obj + 0xC0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)((char *)obj + 0xC0) & 0x10) == 0);
    debug_assertMessage(D_00552560);
    while (1) {
        BoxBarSoundOn(a0, 0x5D);
        _ACTWait(1);
    }
}


extern void debug_assertMessage(void *);
extern void iosOmBeforeFuncStandard(void *, int, void *);
extern char D_005524F0[];
extern void *D_0062A4DC;

void func_00152640(volatile int a0) {
    debug_assertMessage(D_005524F0);
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard(D_00629DE8, 0x5D, D_0062A4DC);
    }
}


extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00552598[];
extern char D_00552560[];
void func_001526F8(volatile int a0);

void actBoyPullupGo(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00552598);
    *(int *)((char *)obj + 0x30) = 0x51;
    *(void **)((char *)obj + 0x14) = (void *)func_001526F8;
    *(int *)((char *)obj + 0xC0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)((char *)obj + 0xC0) & 0x10) == 0);
    debug_assertMessage(D_00552560);
    while (1) {
        BoxBarSoundOn(a0, 0x62);
        _ACTWait(1);
    }
}


extern void debug_assertMessage(void *);
extern void iosOmBeforeFuncStandard(void *, int, void *);
extern char D_005524F0[];
extern void *D_0062A4DC;

void func_001526F8(volatile int a0) {
    debug_assertMessage(D_005524F0);
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard(D_00629DE8, 0x62, D_0062A4DC);
    }
}


extern float ClearHandCameraCorrect(CCPResult *, CCPResult *);
extern void *isysGObjSearchFromObjKindID_begin(void *);

void actBoyBelift(void *a0, int *out_id, float *out_vec) {
    float buf[4];
    void *node;
    int best;
    float thresh = 300.0f;

    node = isysGObjSearchFromObjLayoutID((*(int *)((char *)a0 + 0xC) ^ 1) ? 1 : 4);
    *out_id = 0;
    best = 0x5A;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = ContinueCorrectPosition(a0);
                if (ClearHandCameraCorrect(r1, ContinueCorrectPosition(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = ContinueCorrectPosition(node);
                    func_00240008(buf, r4, ContinueCorrectPosition(a0));
                    sign = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    } else {
                        dist = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    }
                    if (dist < best) {
                        best = dist;
                        out_vec[0] = buf[0];
                        out_vec[1] = buf[1];
                        out_vec[2] = buf[2];
                        *out_id = (int)node;
                    }
                }
            }
            node = isysGObjSearchFromObjKindID_begin(node);
        } while (node != 0);
    }
}


extern void ExecWeaponHitReaction(void *a0);
extern void func_00260568(void *a0, int a1, int a2);
extern int func_001AB9B8(int a0, int a1, int a2, void *a3);
extern int D_006A4608[];
extern float D_00628F1C;
extern void *D_00629C90;

void actBoyRescueReady(void) {
    union { float f[4]; int i[4]; } buf;
    int *s16;
    if (D_00629DE4 == 0) return;
    s16 = *(int **)((char *)D_00629DE4 + 0x164);
    if (*(int *)((char *)s16 + 0x130) != 0) {
        ExecWeaponHitReaction(*(void **)((char *)s16 + 0x130));
        func_00260568(&buf, 0, 0x10);
        buf.f[0] = D_00628F1C;
        CylinderCollision((void *)*(int *)((char *)s16 + 0x130), &buf);
        func_001AB9B8(*(int *)((char *)s16 + 0x130), 0, 0, D_00629C90);
        *(int *)(*(int *)((char *)s16 + 0x130) + 0x16C) = 0;
    }
    D_006A4608[0] = 0;
    *(int *)D_006A45A0 = 0;
    *(int *)((char *)s16 + 0x130) = 0;
}



int actBoyDitch3mReady(void) {
    BoyState *p = *(BoyState **)((char *)D_00629DE4 + 0x164);
    unsigned int v = p->f_30;
    if (v >= 0x5D) {
        return 1;
    }
    if (v < 0x5B) {
        return 1;
    }
    return 0;
}

extern void *ACTGameCollisionOff(void *a0);
extern int TorchGeo(void *a0);
extern int ACTEnvGetTest(void);

union BoyStatFlags { long long ll; int w[2]; };
extern union BoyStatFlags D_006A45A0_sf[] __asm__("D_006A45A0");

void SetStatusBoy_OtherStageGirlPinch(void)
{
    void *r;
    long long f = D_006A45A0_sf[1].ll;
    void *work = *(void **)((char *)D_00629DE4 + 0x164);
    void *st;

    D_006A45A0_sf[1].ll = f & ~(1LL << 34);
    st = *(void **)((char *)work + 0x130);
    if (st != 0) {
        r = ACTGameCollisionOff(st);
        if (r != 0) {
            if (TorchGeo(r) != 0) {
                D_006A45A0_sf[1].ll |= (1LL << 34);
            }
        }
    }
    D_006A45A0_sf[1].ll &= ~(1LL << 33);
    if (ACTEnvGetTest() != 0) {
        D_006A45A0_sf[1].ll |= (1LL << 33);
    }
}


extern int D_0062A894;

int actBoyStart(int *a0) {
    int *o = (int *)a0[0x59];
    if (o[0xC] == 0x35) goto ret1;
    {
        int *p = (int *)o[0x19E];
        if (p[0xE0] == 0) goto ret0;
        if (D_0062A894 == 0) goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

int CorrectStickInfo(void) {
    void *o = D_00629DE4;
    int *s5;
    unsigned int v;
    int rv;
    int new_var;
    int result;
    if (o == 0) {
        func_001AAD00(D_005525C8, 0x1403);
        func_00260380(D_005525C8, 0x1403, D_0062C3F8);
        result = 0;
        goto done;
    }
    s5 = *(int **)((char *)o + 0x164);
    v = *(int *)((char *)s5 + 0x30);
    if (v < 0x13) { rv = 0x15; goto B00; }
    if (v >= 0x16) {
        if (v < 0x18) { result = 1; goto done; }
        rv = 0x15;
        goto B00;
    }
    if (*(int *)((char *)*(int **)((char *)s5 + 0x670) + 0x29C) != 0) { result = 1; goto done; }
    rv = 0x15;
B00:
    if (v == rv) { result = 0; result = 1; goto done; }
    if (*(int *)((char *)*(int **)((char *)s5 + 0x678) + 0x368) > (new_var = 0)) { result = 1; rv = 0x15; goto done; }
    result = 0;
done:
    return result;
}



extern unsigned long long D_006A45A8[];

int GetBoyWeaponGObj(void) {
    return (unsigned char)(D_006A45A8[0] >> 35) & 1;
}

extern unsigned char D_0062BFDC;

int actBoyStand(void) {
    return D_0062BFDC;
}

extern void *D_00629DE8;
int actBoyHang(void) {
    if (D_00629DE4 != 0 && D_00629DE8 != 0) {
        BoyState *p5 = *(BoyState **)((char *)D_00629DE4 + 0x164);
        int v4 = p5->f_30;
        if (v4 == 0x2D) {
            BoyState *p2 = *(BoyState **)((char *)D_00629DE8 + 0x164);
            if (p2->f_30 == v4) {
                int *q = *(int **)((char *)p5 + 0x140);
                return q[2];
            }
        }
    }
    return -1;
}


extern long long D_006A45A0_ll[] __asm__("D_006A45A0");
void actBoyBHang(void) {
    D_006A45A0_ll[1] |= 0x800000000LL;
}

extern char D_005529E0[];
extern unsigned char D_006A45F0[];
extern int actSwordEff(void *a0, int a1, int a2, int a3, float a4, float a5);
extern void ACTGame_BeforeFunc(void *a0, void *a1, void *a2, int a3);

int actBoyFall(void *a0, int a1) {
    char buf[0x10];
    int rv = 0;
    if (D_00629DE4 != 0) {
        rv = actSwordEff(a0, 0, 0, 0, 0.25f, 4.0f) & 0xFF;
        if (rv != 0) {
            D_006A45F0[0] = 1;
            *(int *)(D_006A45F0 + 4) = a1;
            *(long *)buf = *(long *)D_005529E0;
            *(long *)(buf + 8) = *(long *)(D_005529E0 + 8);
            ACTGame_BeforeFunc(D_00629DE4, a0, buf, 0);
        }
    }
    return rv;
}

extern unsigned char D_006A45F0[];

int actBoyCall(void) {
    if (D_006A45F0[0] == 0) goto ret0;
    return *(int *)(D_006A45F0 + 4);
ret0:
    return 0;
}

extern int D_006A4600[];

int actBoyItem(void) {
    return D_006A45F0[0];
}

void *actBoyItemAfter(void) {
    return D_006A4600;
}

int actBoyCliffHesitate(void) {
    return 0x18;
}

typedef struct { int d[6]; } HB_S18;
typedef struct { int d[2]; } HB_S8;
extern void *D_00629DE4;
extern void *D_00629DE8;
extern long long D_006A45A0[];
extern int D_006A4600[];
extern int D_0027DF70[];
extern void SetStatusBoy_OtherStageGirlPinch(void);

void actBoyHangBefore(void) {
    char *boy = (char *)D_00629DE4;
    char *dst = (char *)D_006A4600;

    *(HB_S18 *)D_006A4600 = *(HB_S18 *)D_0027DF70;

    if (boy != 0) {
        char *p = *(char **)(boy + 0x164);
        char *a = *(char **)(p + 0x130);
        if (a != 0) {
            *(int *)(dst + 0x8) = *(int *)(a + 0x8);
        }
        a = *(char **)(p + 0x134);
        if (a != 0) {
            *(int *)(dst + 0xC) = *(int *)(a + 0x8);
        }
        if (*(int *)(p + 0x30) == 0x2D) {
            *(int *)(dst + 0x10) = *(int *)(*(char **)(p + 0x140) + 0x8);
        }
        if (D_00629DE8 != 0 &&
            *(int *)(*(char **)((char *)D_00629DE8 + 0x164) + 0x30) == 0x2D) {
            *(int *)(dst + 0x14) |= 1;
        }
        SetStatusBoy_OtherStageGirlPinch();
        {
            unsigned long long v = D_006A45A0[1];
            *(int *)(dst + 0x14) =
                (*(int *)(dst + 0x14) & 0xFFFEFFFF) |
                (((unsigned char)(v >> 0x22) & 1) << 0x10);
            *(char *)(dst + 0x15) = (unsigned char)(v >> 0x21) & 1;
        }
        *(HB_S8 *)dst = *(HB_S8 *)((char *)D_006A45A0 + 0x50);
    }
}


typedef struct {
    int f0; int f4;
    union { long long ll; int i[2]; } u8;
    char pad[0x50 - 0x10];
    char c50[8];
} RMDst;
void actBoyReadyMove(void) {
    char *src = (char *)D_006A4600;
    RMDst *dst = (RMDst *)D_006A45A0;
    long long v;
    dst->u8.i[0] = *(int *)(src + 0x10);
    v = dst->u8.ll;
    v &= ~(1LL << 32); v |= (long long)(*(unsigned char *)(src + 0x14) & 1) << 32;
    v &= ~(1LL << 33); v |= (long long)(*(unsigned char *)(src + 0x15) & 1) << 33;
    v &= ~(1LL << 34); v |= (long long)(*(unsigned short *)(src + 0x16) & 1) << 34;
    dst->f4 = *(int *)(src + 0xC);
    dst->f0 = *(int *)(src + 0x8);
    dst->u8.ll = v;
    *(HB_S8 *)dst->c50 = *(HB_S8 *)(src + 0);
}



/* actBoyBeslam: iterate over layout objects, pick best hand-camera match */
extern float ClearHandCameraCorrect(CCPResult *, CCPResult *);
extern void *isysGObjSearchFromObjKindID_begin(void *);

void actBoyBeslam(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh) {
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjLayoutID(a1);
    *out_id = 0;
    best = a2;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = ContinueCorrectPosition(a0);
                if (ClearHandCameraCorrect(r1, ContinueCorrectPosition(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = ContinueCorrectPosition(node);
                    func_00240008(buf, r4, ContinueCorrectPosition(a0));
                    sign = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    } else {
                        dist = ((int (*)(void *, void *))HandCameraCorrect)(buf, subCommonIdle(a0));
                    }
                    if (dist < best) {
                        best = dist;
                        out_vec[0] = buf[0];
                        out_vec[1] = buf[1];
                        out_vec[2] = buf[2];
                        *out_id = (int)node;
                    }
                }
            }
            node = isysGObjSearchFromObjKindID_begin(node);
        } while (node != 0);
    }
}


extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);
extern void debug_assertMessage(void *msg);
typedef struct { int a, b, c; } S12;
extern S12 D_0027E9D0;
extern char D_0062C428[];

void actBoyRescueSrc(volatile int a0) {
    _ACTGame_SearchGObj((void *)a0, 0, 3, 0, 0, 0, 0);
    *(S12 *)((char *)GOBJ_SUB(a0) + 0x1B0) = D_0027E9D0;
    debug_assertMessage(D_0062C428);
}


void actBoySupportGBBegin(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (1) {
        BoxBarSoundOn((void *)buf[0], 0xAE);
        _ACTWait(1);
    }
}


extern void WeaponCurPos(int a0, int a1, int a2);
extern char D_005527E8[];
extern char D_0062C418[];

extern int D_006A45A0_i[] __asm__("D_006A45A0");
void func_001530C0(int *volatile a0) {
    int s1 = D_006A45A0_i[8];
    int s0 = D_006A45A0_i[9];
    int s4 = *(int *)((char *)a0 + 0x164);
    int *p = a0;
    int s2 = *(int *)((char *)p + 0x164);
    if (s1 != s0) {
        if (s0 == 0) {
            func_001AAD00(D_005525C8, 0xA87);
            func_00260380(D_005525C8, 0xA87, D_0062C418);
        } else {
            int w;
            WeaponCurPos(s0, (int)p, 0x16);
            w = *(int *)((char *)s0 + 0x8);
            *(int *)((char *)s2 + 0x130) = s0;
            D_006A45A0_i[0] = w;
            if (s1 != 0) {
                ExecWeaponHitReaction((void *)s1);
                InitSwapWeapon();
                func_001AB9B8(s1, 0, 0, D_00629C90);
                ((void (*)(char *, int, int))debug_assertMessage)(D_005527E8, *(int *)((char *)s1 + 0x8), *(int *)((char *)s0 + 0x8));
            }
        }
    }
    *(int *)((char *)s4 + 0x130) = D_006A45A0_i[9];
}


void actBoySupportGBLoop(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void _ACTWait(int);

void actBoySupportGBEnd(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    buf[0];
    while (1) {
        _ACTWait(1);
    }
}

void func_001531E8(int *a0, int *a1) {
    int n;
    int i;
    if (a0 != 0) {
        ((int *)D_006A45A0)[0] = a0[2];
    } else {
        ((int *)D_006A45A0)[0] = 0;
    }
    i = 0;
    n = 1;
    if (a1 != i) {
        ((int *)D_006A45A0)[n] = a1[2];
    } else {
        ((int *)D_006A45A0)[n] = i;
    }
}

extern void GetRootMatrixByDObj(void *dest, void *dobj);
extern float HandyCamera_TargetMoveType(void *a0, void *a1);
extern float D_00628F20;

void actBoySupportBGBegin(float *out) {
    void *o = D_00629DE4;
    float buf[4];
    char *s16 = *(char **)((char *)o + 0x164);
    char *p;
    GetRootMatrixByDObj(buf, o);
    p = s16 + 0xF0;
    if (HandyCamera_TargetMoveType(buf, p) < D_00628F20) {
        out[0] = *(float *)(s16 + 0xF0);
        out[1] = *(float *)(s16 + 0xF4);
        out[2] = *(float *)(s16 + 0xF8);
    } else {
        GetRootMatrixByDObj(p, o);
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}

typedef struct { long long d[12]; } S60;
typedef struct { int d[6]; } S18;
extern S60 src60_a __asm__("D_0027DF10");
extern S60 dst60_a __asm__("D_006A45A0");
extern S18 src18_a __asm__("D_0027DF70");
extern S18 dst18_a __asm__("D_006A4600");

void actBoyDitch3mExec(void) {
    dst60_a = src60_a;
    dst18_a = src18_a;
}

extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);

void actBoyHangG3M(void *a0, void *a1) {
    GetCylinderCollisionWithExceptOwnCollision(a0, a1);
}

extern void SetRootMatrixWithTransOffset(void *a0);

void IsAbleBoyControl(void *a0) {
    SetRootMatrixWithTransOffset(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", ACTSearchEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", DeleteBoyWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", isLiftBoyEnable);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/boyact", BoyInfoUpdate_StageChange);

extern void ACTWay_SetBeginPositionIllegal(void *g);

void ACTChkAttackIgnore_BOY(void *g) {
    ACTWay_SetBeginPositionIllegal(g);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned long long f_8;  /* 0x08 */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
} S_006A45A0;

typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned char      f_14;  /* 0x14 */
    unsigned char      f_15;  /* 0x15 */
    unsigned short     f_16;  /* 0x16 */
} S_006A4600;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027E0F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552600;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005527D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552810;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A590;  /* stride 0x4 */

/* end struct shapes */
