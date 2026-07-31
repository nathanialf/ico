#include "common.h"

#include "ico/types.h"

typedef struct { int d[6]; } HB_S18;

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

typedef struct { int a, b, c; } S12;

typedef struct { int d[6]; } S18;
typedef struct { long long d[12]; } S60;

typedef struct { int d[2]; } HB_S8;
typedef struct {
    int f0; int f4;
    union { long long ll; int i[2]; } u8;
    char pad[0x50 - 0x10];
    char c50[8];
} RMDst;

typedef struct { char _0[0x30]; int f_30; } BoyState;

typedef struct { char pad[4]; float f4; } CCPResult;













extern void ACTWay_SetBeginPositionIllegal();
extern void SetRootMatrixWithTransOffset();
extern void GetCylinderCollisionWithExceptOwnCollision();
extern int D_006AAB40[];
extern unsigned char D_006AAB30[];
extern void WeaponCurPos(int *self, int *other, int a2);
extern long long D_006AAAE0[];
extern int *D_00631AE4;
extern void *D_00631AE8;
extern unsigned char D_00633CEC;
extern long long D_006AAAE8[];
extern void _ACTWait();
extern void funcCommonJumpDircorrect();
extern void HandCameraCorrect();
extern void BeforeFunc2();
void findChainInJump(void) {}

INCLUDE_ASM("asm/nonmatchings/src/boyact", CorrectOrient_RopeCliff);

INCLUDE_ASM("asm/nonmatchings/src/boyact", motBoyHand100);

INCLUDE_ASM("asm/nonmatchings/src/boyact", motBoyHand200);

extern int D_006321DC__hh __asm__("D_006321DC");
extern char D_00558230[];
extern void debug_assertMessage(void *msg);
extern void iosOmBeforeFuncStandard(void *a0, int a1, int a2);
extern void BoxBarSoundOn(void *a0, int a1);

void hand_heroin(volatile int a0)
{
    int *m = *(int **)((char *)a0 + 0x164);

    debug_assertMessage(D_00558230);
    while (1) {
        if (D_00631AE8 != 0) {
            iosOmBeforeFuncStandard(D_00631AE8, 0x55, D_006321DC__hh);
        }
        if (*(int *)((char *)m + 0xD0) & 1) {
            break;
        }
        _ACTWait(1);
    }
    while (1) {
        if (*(int *)(*(int *)((char *)a0 + 0x15C) + 0x4A0) >= 0 &&
            *(int *)(*(int *)((char *)a0 + 0x15C) + 0x4A0) < 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        if (D_00631AE8 != 0) {
            iosOmBeforeFuncStandard(D_00631AE8, 0x56, D_006321DC__hh);
        }
        if (*(int *)((char *)m + 0xD0) & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(0x2D);
    *(int *)((char *)m + 0x14) = 0;
    while (1) {
        BoxBarSoundOn((void *)a0, 0x43);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014D978);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014DC28);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014DF18);

extern int ACTEnvGetTest(void);
extern void *D_00631990;
extern void *D_00631AE4__p4 __asm__("D_00631AE4");
extern int D_00631AF0;
extern int D_006AAAF0[16];
extern int ForMotionViewer_GetCurrentAnimationFrame(void *a0, int a1);
extern int actGirlBecall(void *a0, int a1);
extern int actSt25aQueenDead(int a0, void *a1, void *a2, float a3, float a4);
extern float func_0014B358(int a0);
extern union { long long fl[2]; int ix[8]; } D_006AAAE0u __asm__("D_006AAAE0");

void CheckCollisionAttr(void *a0) {
    void *sub = *(void**)((char*)a0 + 0x15C);
    int i, hit = 0, flag20 = 1;
    if (func_0014B358(2) < *(float*)((char*)sub + 0x560)) return;
    if (*(int*)((char*)*(void**)((char*)a0+0x164) + 0x30) == 0x16) return;
    if (D_00631AF0 != 0) return;
    for (i = 1; i < 0x10; i++) {
        if (ForMotionViewer_GetCurrentAnimationFrame(a0, i) == 0) continue;
        flag20 = 0;
        if (D_006AAAE0u.ix[4] < 0) { D_006AAAE0u.ix[4] = i; goto done; }
        if (D_006AAAE0u.ix[4] == i) continue;
        if (ACTEnvGetTest()) hit = 1;
        else if (D_00631AE8 != 0) { if (actGirlBecall(D_00631990, i)) hit = 1; }
        if (hit) { D_006AAAE0u.fl[1] |= (1LL<<35);
                   actSt25aQueenDead(i, D_00631AE4__p4, D_00631AE8, 1.0f, 8.0f); }
        else       actSt25aQueenDead(i, D_00631AE4__p4, 0,          1.0f, 8.0f);
    }
    if (flag20) D_006AAAF0[0] = 0xFF;
done: ;
}


extern BgaEntry D_00281C10[];
extern char D_005582C8[];
extern float D_00630B28;
extern char D_00632290[];
extern void func_0014B660(void *a0, void *a1, int a2);
extern void func_001945B8(void *a0, float a1);
extern void func_001947D0(void *a0, void *a1, void *a2);
extern void func_001AD768(char *file, int line);
extern void func_00243AD0(void *a0, void *a1, void *a2);
extern void func_00243B18(void *a0, void *a1, float a2);
extern void func_00263FF0(char *file, int line, char *msg);
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
            func_001947D0(buf_a, ContinueCorrectPosition(g), ContinueCorrectPosition(a0));
        }
        func_00243B18(buf_a, buf_a, e->f10);
        func_0014B660(e->f30, buf_a, 0);
        func_00243B18(buf_b, subCommonIdle(a0), e->f8);
        func_00243AD0(e->f20, ContinueCorrectPosition(a0), buf_b);
        func_00243B18(buf_b, subCommonIdle(a0), e->f4);
        func_001945B8(buf_b, D_00630B28);
        func_00243AD0(e->f20, e->f20, buf_b);
        e->f24 = e->f24 + (float) e->fD;
    }
    i = 0;
    if (D_00281C10[0].field0 >= 0) {
        for (;;) {
            if (D_00281C10[i].field0 == a1) {
                found = &D_00281C10[i];
                goto have_found;
            }
            i++;
            if (D_00281C10[i].field0 < 0) {
                break;
            }
        }
    }
    found = 0;
    func_001AD768(D_005582C8, 0x607);
    func_00263FF0(D_005582C8, 0x607, D_00632290);
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

extern void BoySekikaTexScroll(void *a0, int a1);
extern void CylinderCollision(void *a0, void *a1);
extern unsigned char D_00633CEE;
extern unsigned char D_00633CEF;
extern unsigned char D_00633CF0;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void func_0017B288(int a0);
extern void func_0017B528(void *a0);
extern void func_0017B568(void *a0);
extern void func_00243AD0(void *a0, void *a1, void *a2);
extern void func_00243B18(void *a0, void *a1, float a2);
extern int staffRollScroll(void *a0, int a1, int a2, int *p, int *q, int *r);

void E3_StageStartBoy(void *a0) {
    float buf[4];
    int w10, w14, w18;

    if (D_00633CEE) {
        func_00243B18(buf, subCommonIdle(a0), 100.0f);
        func_00243AD0(buf, buf, ContinueCorrectPosition(a0));
        CylinderCollision(a0, buf);
    }
    if (func_0017B230(0x15C)) {
        func_0017B288(0x15C);
        return;
    }
    if (staffRollScroll(a0, 0, 0, &w10, &w14, &w18)) {
        if (D_00633CF0) {
            return;
        }
        if (D_00633CEF) {
            return;
        }
        _ACTWait(3);
        staffRollScroll(a0, 0, 0, &w10, &w14, &w18);
        _ACTWait(w10);
        func_0017B528(a0);
        BoySekikaTexScroll(a0, 7);
        _ACTWait(w14);
        func_0017B568(a0);
        _ACTWait(w18);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", GetChainSlope);

INCLUDE_ASM("asm/nonmatchings/src/boyact", subBoyControl);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001501A0);

extern void GetLowerPlaneCollision(char *p, float a, float b, float c, float d, float e, float f);
extern void func_00102858(int obj);

void InitSwapWeapon(void)
{
    char *base = (char *)D_006AAAE0;
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
    func_00102858(*(int *)(base + 0x20));
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00150348);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001504D8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00150568);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00151678);

extern int ACTEnvGetTest(void);
extern void ActOrientTest(void *out, void *src, int mode);
extern float ClearHandCameraCorrect(CCPResult *a, CCPResult *b);
extern int func_00263FB0(float);
extern int func_00262BE8(int, double);
extern int func_00262B80(double, int);
extern float func_002633B8(int);
extern void func_0014B330(void *a0, int a1, float a2);
extern int D_00274EC0[];

/* func_00151868 / func_001519D8: twin act-state loops.  The two double
 * literals of each (0.2/0.9 and 0.2/0.7) live in a boyact-owned .lit8 pool
 * at VMA 0x558620; reference the pool slots directly so no second pool is
 * emitted.  `int *volatile a0` = addressable param home-store/reload; d
 * reused as the pre-clamp temp forces mov.s $f1,$f0. */
void func_00151868(int *volatile a0) {
    float buf1[4], buf2[4];
    int *s4 = *(int **)((char *)a0 + 0x164);
    while (1) {
        if (ACTEnvGetTest()) {
            float d;
            int cnt;
            ActOrientTest(buf2, D_00631AE4, 2);
            ActOrientTest(buf1, D_00631AE8, 0x12);
            d = ClearHandCameraCorrect((CCPResult *)buf1, (CCPResult *)buf2);
            cnt = ((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) * 0x64 / 0x3C;
            if (cnt < *(int *)((char *)s4 + 0x48) && 80.0f < d) {
                float clamped;
                int r1, r2, r3;
                float r4;
                d = (d - 80.0f) / 10.0f;
                if (d < 0.0f) clamped = 0.0f;
                else if (1.0f < d) clamped = 1.0f;
                else clamped = d;
                r1 = func_00263FB0(clamped);
                r2 = func_00262BE8(r1, 0.2);
                r3 = func_00262B80(0.9, r2);
                r4 = func_002633B8(r3);
                func_0014B330((void *)a0, 2, r4);
            }
        }
        _ACTWait(1);
    }
}

void func_001519D8(int *volatile a0) {
    float buf1[4], buf2[4];
    int *s4 = *(int **)((char *)a0 + 0x164);
    while (1) {
        if (ACTEnvGetTest()) {
            float d;
            int cnt;
            ActOrientTest(buf2, D_00631AE4, 2);
            ActOrientTest(buf1, D_00631AE8, 0x12);
            d = ClearHandCameraCorrect((CCPResult *)buf1, (CCPResult *)buf2);
            cnt = ((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) * 0x64 / 0x3C;
            if (cnt < *(int *)((char *)s4 + 0x48) && 90.0f < d) {
                float clamped;
                int r1, r2, r3;
                float r4;
                d = (d - 90.0f) / 10.0f;
                if (d < 0.0f) clamped = 0.0f;
                else if (1.0f < d) clamped = 1.0f;
                else clamped = d;
                r1 = func_00263FB0(clamped);
                r2 = func_00262BE8(r1, 0.2);
                r3 = func_00262B80(0.7, r2);
                r4 = func_002633B8(r3);
                func_0014B330((void *)a0, 2, r4);
            }
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00151B48);

extern int D_00274EC0[];
extern int dispPlane(void *a0, void *a1);
extern void funcCommonFallDircorrect2(void *a0, void *a1) __asm__("funcCommonFallDircorrect");
extern int func_00194590(void *a0, void *a1);

void func_00151D78(int *volatile a0) {
    float buf10[4], buf20[4], buf30[4];
    void *g = *(void **)((char *)a0 + 0x164);
    void *s16 = *(void **)((char *)g + 0x5F8);
    int first = 1;
    int cnt = 0;
    buf10[0] = ((float *)ContinueCorrectPosition(s16))[0];
    buf10[1] = ((float *)ContinueCorrectPosition(s16))[1];
    buf10[2] = ((float *)ContinueCorrectPosition(s16))[2];
    while (1) {
        buf20[0] = ((float *)ContinueCorrectPosition(a0))[0];
        buf20[1] = ((float *)ContinueCorrectPosition(a0))[1];
        buf20[2] = ((float *)ContinueCorrectPosition(a0))[2];
        func_001947D0(buf30, buf10, buf20);
        if (first) {
            dispPlane(a0, buf30);
            first = 0;
        } else if (func_00194590(subCommonIdle(a0), buf30) < 0x1E) {
            funcCommonFallDircorrect2(a0, buf30);
        } else {
            BoxBarSoundOn(a0, 0xBC);
        }
        if (((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) * 2 < cnt++)
            BoxBarSoundOn(a0, 0xBC);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00151F00);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001520E8);

INCLUDE_ASM("asm/nonmatchings/src/boyact", subBoyCollision);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoySwim);

extern int ACTGame_InsertCamera_GirlIsPinch(void);
extern float D_00630BF8;
extern float D_00630BFC;
extern float D_00630C00;
extern void *D_006321DC__p4 __asm__("D_006321DC");
extern void iosOmBeforeFuncStandard__p4(void *a0, int a1, void *a2) __asm__("iosOmBeforeFuncStandard");

void func_00152508(int *arg){
    int state=*(int*)((char*)*(void**)((char*)D_00631AE4__p4+0x164)+0x5D4);
    void *obj=*(void**)((char*)(*(int * volatile *)&arg)+0x164);
    float lo,hi;
    switch (state) {
    case 0x64: if (D_00631AE8) iosOmBeforeFuncStandard__p4(D_00631AE8,0x4D,D_006321DC__p4); *(int*)((char*)*(void**)((char*)D_00631AE8+0x164)+0x40)=0x5C; break;
    case 0xC8: if (D_00631AE8) iosOmBeforeFuncStandard__p4(D_00631AE8,0x4D,D_006321DC__p4); *(int*)((char*)*(void**)((char*)D_00631AE8+0x164)+0x40)=0x5D; break;
    case 0x12C:if (D_00631AE8) iosOmBeforeFuncStandard__p4(D_00631AE8,0x4D,D_006321DC__p4); *(int*)((char*)*(void**)((char*)D_00631AE8+0x164)+0x40)=0x5E; break;
    }
    lo=*(volatile float*)&D_00630BF8;hi=*(volatile float*)&D_00630BFC;
    while (1) {
        if (ACTGame_InsertCamera_GirlIsPinch()==0) BoxBarSoundOn(*(int * volatile *)&arg,0x47);
        else{ float v=*(float*)((char*)obj+0x33C); int ci; float c;
            ci=*(int*)&v; c=*(float*)&ci;
            if(!(D_00630C00<v)) goto t2;
            if(!(D_00630C00<v)) goto l47;
            if(v<lo) goto t2;
            if(*(volatile int*)((char*)obj+0x2D0)&0x20) goto t2;
            l47: BoxBarSoundOn(*(int * volatile *)&arg,0x48); goto w;
            t2: if(hi<c && (v<lo||(*(volatile int*)((char*)obj+0x2D0)&0x20))) BoxBarSoundOn(*(int * volatile *)&arg,0x49);
                else BoxBarSoundOn(*(int * volatile *)&arg,0x4A);
            w:; }
        _ACTWait(1); } }

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001526A0);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00152A70);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00152F18);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153318);

INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyWalk);

void actBoyRun(int a0)
{
    int buf[4];
    BeforeFunc2(buf);
    HandCameraCorrect(buf, a0);

}

int func_001538F8(void)
{
    char *o = (char *)D_00631AE4;
    if (o != 0) {
        return *(int *)(*(char **)(o + 0x164) + 0x140);
    }
    return 0;
}

typedef struct { char _0[0x188]; unsigned int f188; char _18c[4]; } WpnEntry;
extern char D_00565060[];

void actBoyTakeWeaponReady(int *volatile a0) {
    int idx = *(int *)((char *)*(int **)((char *)a0 + 0x15C) + 0x4A0);
    if ((((WpnEntry *)(D_00565060 + idx * 0x190))->f188 >> 11) & 1) {
        funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7E0);
    }
    while (1) {
        _ACTWait(1);
    }
}

void func_00153980(int *volatile a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7E0);
    _ACTWait(0);
}

void actBoyTakeWeapon(volatile unsigned int a0)
{
    volatile int local;
    int *v1 = *(int **)(a0 + 0x164);
    int a1 = v1[0x678 / 4];
    funcCommonJumpDircorrect(a0, a1 + 0x7E0);
    _ACTWait(0);
}

extern int D_006321DC;
extern void iosOmBeforeFuncStandard(void *a0, int a1, int a2);
extern void debug_assertMessage(void *a0);
extern void BoxBarSoundOn(void *a0, int a1);
extern void *subCommonIdle(void *a0);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern char D_00558640[];

void pullup_check_heroin_position(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00558640);
    *(int *)((char *)obj + 0x30) = 5;
    while (1) {
        _ACTWait(1);
    }
}

extern char D_00558688[];

void func_00153A30(volatile int a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00558688);
    *(int *)((char *)obj + 0x30) = 9;
    _ACTWait(2);
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3D, D_006321DC);
    }
    while (1) {
        if (!(*(int *)((char *)obj + 0x2D0) & 8)) {
            BoxBarSoundOn((void *)a0, 0xB7);
        }
        _ACTWait(1);
    }
}

void func_00153AA8(volatile int a0) {
    while (1) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern char D_005586A0[];

void func_00153AD8(volatile int a0) {
    float buf[4];
    debug_assertMessage(D_005586A0);
    while (1) {
        func_00243B18(buf, subCommonIdle((void *)a0), 15.0f);
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

extern float fzMagnitudefv(int a0, int a1, int a2);
extern void brainInitGirlSet(void);

void func_00153B38(volatile int a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7F0);
    fzMagnitudefv(*(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x800,
                  *(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7F8),
                  *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7F0);
    while (1) {
        if (D_00631AE8 != 0) {
            brainInitGirlSet();
            if (D_00631AE8 != 0) {
                iosOmBeforeFuncStandard(D_00631AE8, 0x3A, D_006321DC);
            }
        }
        BoxBarSoundOn((void *)a0, 0x117);
        _ACTWait(1);
    }
}

typedef struct { long long a; int b; } __attribute__((packed, aligned(4))) S12u;
void func_00153BE0(volatile int a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int q0, q1, q2, q3;
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7F0);
    q0 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    q1 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    *(float *)(q0 + 0x430) = *(float *)((char *)p + 0x4B0);
    q2 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    q3 = *(int *)(*(int *)((char *)a0 + 0x164) + 0x678);
    *(float *)(q1 + 0x434) = *(float *)((char *)p + 0x4B4);
    *(float *)(q2 + 0x438) = *(float *)((char *)p + 0x4B8);
    *(S12u *)(q3 + 0x440) = *(S12u *)((char *)p + 0x620);
    while (1) { BoxBarSoundOn((void *)a0, 0x117); _ACTWait(1); }
}

typedef struct { char _0[0x20]; float f20; int i24; int i28; int _2c; } __attribute__((aligned(8))) Buf30;
extern float RotateAccordingToStick_PatternThree(CCPResult *a0, void *a1);
extern void funcCommonFallDircorrect(int a0, void *a1);

void func_00153C90(volatile int a0) {
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
        if (buf.i24-- < 0) BoxBarSoundOn((void *)a0, 0xFA);
        if (RotateAccordingToStick_PatternThree(ContinueCorrectPosition((void *)a0), &buf) < buf.f20 * buf.f20)
            BoxBarSoundOn((void *)a0, 0xFA);
        _ACTWait(1);
    }
}

extern void *D_00633CF8;

void func_00153DA0(volatile int a0) {
    void *obj = (char *)*(void **)((char *)a0 + 0x15C) + 0x130;
    func_00243B18(obj, subCommonIdle(D_00633CF8), 30.0f);
    while (1) {
        BoxBarSoundOn((void *)a0, 0x127);
        _ACTWait(1);
    }
}

void func_00153DF8(volatile int a0) {
    while (1) {
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_00153E28(volatile int a0) {
    while (1) {
        if (D_00631AE8 != 0) {
            iosOmBeforeFuncStandard(D_00631AE8, 0x161, D_006321DC);
        }
        BoxBarSoundOn((void *)a0, 0x15F);
        _ACTWait(1);
    }
}

static __inline__ unsigned char boyStateIsGrab(void) {
    void *p = D_00631AE8;
    void *q = p;
    unsigned int lo = *(unsigned int *)((char *)*(void **)((char *)p + 0x164) + 0x30);
    unsigned int hi = *(unsigned int *)((char *)*(void **)((char *)q + 0x164) + 0x30);
    if (hi >= 0x68) return 0;
    if (lo < 0x65) return 0;
    return 1;
}

void func_00153E68(volatile int a0) {
    while (1) {
        if (!boyStateIsGrab()) {
            BoxBarSoundOn((void *)a0, 0xD2);
        }
        _ACTWait(1);
    }
}

void func_00153EC8(volatile int a0) {
    while (1) {
        if (D_00631AE8 != 0) {
            iosOmBeforeFuncStandard(D_00631AE8, 0x163, D_006321DC);
        }
        BoxBarSoundOn((void *)a0, 0xB7);
        _ACTWait(1);
    }
}

void func_00153F08(volatile int a0) {
    while (1) {
        BoxBarSoundOn((void *)a0, 0x167);
        _ACTWait(1);
    }
}

void func_00153F38(volatile int a0) {
    while (1) {
        BoxBarSoundOn((void *)a0, 0x172);
        _ACTWait(1);
    }
}

extern float D_00630C1C;

void func_00153F68(volatile int a0) {
    void *obj = *(void **)((char *)a0 + 0x164);
    float thresh = D_00630C1C;
    while (1) {
        if (thresh < *(float *)((char *)obj + 0x33C) ||
            (*(int *)((char *)obj + 0x2D0) & 0x10)) {
            BoxBarSoundOn((void *)a0, 0x174);
            if (D_00631AE8 != 0) {
                iosOmBeforeFuncStandard(D_00631AE8, 0x177, D_006321DC);
            }
        }
        _ACTWait(1);
    }
}

extern unsigned char D_00633CED;

unsigned char func_00153FE8(void)
{
    return D_00633CED;
}

extern void BoxBarSoundOn(void *a0, int a1);
extern char D_00558200[];
extern char D_00558218[];
extern void debug_assertMessage(void *msg);
extern void func_00154070();

void ditch_check_heroin_position(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00558200);
    *(int *)((char *)obj + 0x30) = 0x4F;
    *(void **)((char *)obj + 0x14) = (void *)func_00154070;
    *(int *)((char *)obj + 0xD0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)((char *)obj + 0xD0) & 0x10) == 0);
    debug_assertMessage(D_00558218);
    while (1) {
        BoxBarSoundOn(a0, 0x59);
        _ACTWait(1);
    }
}

extern char D_005581F0[];
extern int D_006321DC;
extern void iosOmBeforeFuncStandard(void *a0, int a1, int a2);

void func_00154070(volatile int a0) {
    debug_assertMessage(D_005581F0);
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x59, D_006321DC);
    }
}

extern char D_00558248[];
extern char D_00558260[];
extern void func_00154128();

void actBoyPullupReady(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00558248);
    *(int *)((char *)obj + 0x30) = 0x50;
    *(void **)((char *)obj + 0x14) = (void *)func_00154128;
    *(int *)((char *)obj + 0xD0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)((char *)obj + 0xD0) & 0x10) == 0);
    debug_assertMessage(D_00558260);
    while (1) {
        BoxBarSoundOn(a0, 0x5E);
        _ACTWait(1);
    }
}

void func_00154128(volatile int a0) {
    debug_assertMessage(D_005581F0);
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x5E, D_006321DC);
    }
}

extern char D_00558298[];
extern void func_001541E0();

void actBoyPullupGo(int *volatile a0) {
    int *obj = *(int **)((char *)a0 + 0x164);
    debug_assertMessage(D_00558298);
    *(int *)((char *)obj + 0x30) = 0x51;
    *(void **)((char *)obj + 0x14) = (void *)func_001541E0;
    *(int *)((char *)obj + 0xD0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)((char *)obj + 0xD0) & 0x10) == 0);
    debug_assertMessage(D_00558260);
    while (1) {
        BoxBarSoundOn(a0, 0x63);
        _ACTWait(1);
    }
}

void func_001541E0(volatile int a0) {
    debug_assertMessage(D_005581F0);
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x63, D_006321DC);
    }
}

extern float ClearHandCameraCorrect(CCPResult *a, CCPResult *b);
extern CCPResult *ContinueCorrectPosition(void *a0);
extern void func_00243AE8(void *, CCPResult *, CCPResult *);
extern void *isysGObjSearchFromObjKindID_begin(void *);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *subCommonIdle(void *a0);

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
                    func_00243AE8(buf, r4, ContinueCorrectPosition(a0));
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

extern void CylinderCollision(void *a0, void *a1);
extern float D_00630C20;
extern void *D_00631990;
extern void *D_00631AE4__p4 __asm__("D_00631AE4");
extern int D_006AAB48[];
extern void ExecWeaponHitReaction(void *a0);
extern int func_001AE420(int a0, int a1, int a2, void *a3);
extern void func_002641D8(void *a0, int a1, int a2);

void actBoyRescueReady(void) {
    union { float f[4]; int i[4]; } buf;
    int *s16;
    if (D_00631AE4__p4 == 0) return;
    s16 = *(int **)((char *)D_00631AE4__p4 + 0x164);
    if (*(int *)((char *)s16 + 0x140) != 0) {
        ExecWeaponHitReaction(*(void **)((char *)s16 + 0x140));
        func_002641D8(&buf, 0, 0x10);
        buf.f[0] = D_00630C20;
        CylinderCollision((void *)*(int *)((char *)s16 + 0x140), &buf);
        func_001AE420(*(int *)((char *)s16 + 0x140), 0, 0, D_00631990);
        *(int *)(*(int *)((char *)s16 + 0x140) + 0x16C) = 0;
    }
    D_006AAB48[0] = 0;
    *(int *)D_006AAAE0 = 0;
    *(int *)((char *)s16 + 0x140) = 0;
}

int actBoyDitch3mReady(void) {
    BoyState *p = *(BoyState **)((char *)D_00631AE4 + 0x164);
    unsigned int v = p->f_30;
    if (v >= 0x5D) {
        return 1;
    }
    if (v < 0x5B) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154448);

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154520);

int GetBoyWeaponGObj(void) {
    return (int)((unsigned char)((unsigned long long)D_006AAAE8[0] >> 35)) & 1;
}

unsigned char actBoyStand(void) {
    return D_00633CEC;
}

int actBoyHang(void)
{
    int *a = (int *)D_00631AE4;
    int *b = (int *)D_00631AE8;
    int *pa, *pb, *r;
    int v;
    if (a == 0) goto err;
    if (b == 0) goto err;
    pa = (int *)a[0x164/4];
    v = pa[0x30/4];
    if (v != 0x2D) goto err;
    pb = (int *)b[0x164/4];
    if (pb[0x30/4] != v) goto err;
    r = (int *)pa[0x150/4];
    return r[2];
err:
    return -1;
}

void func_00154648(void) {
    D_006AAAE0[1] |= 0x800000000LL;
}

void func_00154668(int *self)
{
    int new_var;
    int *d;
    int *p;
    d = (int *) D_00631AE4;
    if (0 == d) return;
    if (self == 0) return;
    new_var = 0x164;
    p = (int *) d[new_var / 4];
    WeaponCurPos(self, d, 0x16);
    new_var = self[0x8 / 4];
    p[0x140 / 4] = (int) self;
    *(int *)D_006AAAE0 = new_var;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001546C0);

int actBoyCall(void)
{
    if (D_006AAB30[0]) {
        return *(int *)(D_006AAB30 + 4);
    }
    return 0;
}

unsigned char actBoyItem(void) {
    return D_006AAB30[0];
}

int *func_001547A0(void) {
    return D_006AAB40;
}

int func_001547B0(void) {
    return 24;
}

extern int D_00281BF0[];
extern void func_00154448(void);

void actBoyHangBefore(void) {
    char *boy = (char *)D_00631AE4__p4;
    char *dst = (char *)D_006AAB40;

    *(HB_S18 *)D_006AAB40 = *(HB_S18 *)D_00281BF0;

    if (boy != 0) {
        char *p = *(char **)(boy + 0x164);
        char *a = *(char **)(p + 0x140);
        if (a != 0) {
            *(int *)(dst + 0x8) = *(int *)(a + 0x8);
        }
        a = *(char **)(p + 0x144);
        if (a != 0) {
            *(int *)(dst + 0xC) = *(int *)(a + 0x8);
        }
        if (*(int *)(p + 0x30) == 0x2D) {
            *(int *)(dst + 0x10) = *(int *)(*(char **)(p + 0x150) + 0x8);
        }
        if (D_00631AE8 != 0 &&
            *(int *)(*(char **)((char *)D_00631AE8 + 0x164) + 0x30) == 0x2D) {
            *(int *)(dst + 0x14) |= 1;
        }
        func_00154448();
        {
            unsigned long long v = D_006AAAE0[1];
            *(int *)(dst + 0x14) =
                (*(int *)(dst + 0x14) & 0xFFFEFFFF) |
                (((unsigned char)(v >> 0x22) & 1) << 0x10);
            *(char *)(dst + 0x15) = (unsigned char)(v >> 0x21) & 1;
        }
        *(HB_S8 *)dst = *(HB_S8 *)((char *)D_006AAAE0 + 0x50);
    }
}

void actBoyReadyMove(void) {
    char *src = (char *)D_006AAB40;
    RMDst *dst = (RMDst *)D_006AAAE0;
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
                    func_00243AE8(buf, r4, ContinueCorrectPosition(a0));
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

extern S12 D_00282660;
extern char D_006322C0[];
extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);
extern void debug_assertMessage(void *msg);

void actBoyRescueSrc(volatile int a0) {
    _ACTGame_SearchGObj((void *)a0, 0, 3, 0, 0, 0, 0);
    *(S12 *)((char *)GOBJ_SUB(a0) + 0x1C0) = D_00282660;
    debug_assertMessage(D_006322C0);
}

void actBoySupportGBBegin(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (1) {
        BoxBarSoundOn((void *)buf[0], 0xB0);
        _ACTWait(1);
    }
}

extern char D_005584E8[];
extern char D_006322B0[];

extern int D_006AAAE0_i[] __asm__("D_006AAAE0");
void func_00154BC0(int *volatile a0) {
    int s1 = D_006AAAE0_i[8];
    int s0 = D_006AAAE0_i[9];
    int s4 = *(int *)((char *)a0 + 0x164);
    int *p = a0;
    int s2 = *(int *)((char *)p + 0x164);
    if (s1 != s0) {
        if (s0 == 0) {
            func_001AD768(D_005582C8, 0xAC5);
            func_00263FF0(D_005582C8, 0xAC5, D_006322B0);
        } else {
            int w;
            WeaponCurPos((int *)s0, p, 0x16);
            w = *(int *)((char *)s0 + 0x8);
            *(int *)((char *)s2 + 0x140) = s0;
            D_006AAAE0_i[0] = w;
            if (s1 != 0) {
                ExecWeaponHitReaction((void *)s1);
                InitSwapWeapon();
                func_001AE420(s1, 0, 0, D_00631990);
                ((void (*)(char *, int, int))debug_assertMessage)(D_005584E8, *(int *)((char *)s1 + 0x8), *(int *)((char *)s0 + 0x8));
            }
        }
    }
    *(int *)((char *)s4 + 0x140) = D_006AAAE0_i[9];
}

void actBoySupportGBLoop(int x) {
    volatile int local = x;
}

void actBoySupportGBEnd(int a0)
{
    volatile int local = a0;
    while (1) {
        _ACTWait(1);
    }
}

void func_00154CE8(int *a0, int *a1)
{
    if (a0 != 0) {
        D_006AAAE0_i[0] = a0[2];
    } else {
        D_006AAAE0_i[0] = 0;
    }
    if (a1 != 0) {
        D_006AAAE0_i[1] = a1[2];
    } else {
        D_006AAAE0_i[1] = 0;
    }
}

extern float D_00630C24;
extern void GetRootMatrixByDObj(void *dest, void *dobj);
extern float HandyCamera_TargetMoveType(void *a0, void *a1);

void actBoySupportBGBegin(float *out) {
    void *o = D_00631AE4__p4;
    float buf[4];
    char *s16 = *(char **)((char *)o + 0x164);
    char *p;
    GetRootMatrixByDObj(buf, o);
    p = s16 + 0x100;
    if (HandyCamera_TargetMoveType(buf, p) < D_00630C24) {
        out[0] = *(float *)(s16 + 0x100);
        out[1] = *(float *)(s16 + 0x104);
        out[2] = *(float *)(s16 + 0x108);
    } else {
        GetRootMatrixByDObj(p, o);
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}

extern S18 dst18_a __asm__("D_006AAB40");
extern S60 dst60_a __asm__("D_006AAAE0");
extern S18 src18_a __asm__("D_00281BF0");
extern S60 src60_a __asm__("D_00281B90");

void actBoyDitch3mExec(void) {
    dst60_a = src60_a;
    dst18_a = src18_a;
}

void actBoyHangG3M(int a0, int a1, int a2, int a3)
{
    GetCylinderCollisionWithExceptOwnCollision(a0, a1, a2, a3);
}

void IsAbleBoyControl(int a0, int a1, int a2, int a3)
{
    SetRootMatrixWithTransOffset(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", ACTSearchEnemy);

INCLUDE_ASM("asm/nonmatchings/src/boyact", DeleteBoyWeapon);

INCLUDE_ASM("asm/nonmatchings/src/boyact", isLiftBoyEnable);

INCLUDE_ASM("asm/nonmatchings/src/boyact", BoyInfoUpdate_StageChange);

void ACTChkAttackIgnore_BOY(int a0, int a1, int a2, int a3)
{
    ACTWay_SetBeginPositionIllegal(a0, a1, a2, a3);
}

