#include "common.h"

/* commonact 0x164 actor-state view (local) */
typedef struct { char _0[0xBC]; unsigned int f_BC; char _padc0[0x144]; int f_204; char _pad208[0x48]; int f_250; } CBrain670;
typedef struct { char _0[0x30]; int f_30; unsigned int f_34; char _pad38[0x638]; CBrain670 *p_670; char _pad674[4]; void *p_678; } CommonActState;

extern void weaponFumbleSE(void *);
extern char *D_00629DE4;

void ACTSetPositionWithFitting(char *self) {
    char *s164 = *(char **)(self + 0x164);
    int *p2C = *(int **)(s164 + 0x2C);
    int a1;
    if (p2C != 0) {
        a1 = *p2C;
    } else {
        a1 = *(int *)(s164 + 0x5D0);
    }
    if (self == D_00629DE4) {
        char *p130 = *(char **)(s164 + 0x130);
        if (p130 != 0) {
            char *p15C = *(char **)(p130 + 0x15C);
            *(int *)(p15C + 0x5E4) = a1;
            weaponFumbleSE(p130);
        }
    }
}

extern void func_001EF4F0(int a0);
extern int isysGObjSearchFromObjLayoutID(int a0);
extern int iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern int D_00629C90, D_0062B058;
void ACTSetPositionNodeWithFitting(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v = *(int *)(p + 0x130);
    void *obj;
    if (v != 0) {
        func_001EF4F0(v);
        *(int *)(p + 0x130) = 0;
    }
    if (D_00629C90 == 0x53 || D_0062B058 != 0) {
        obj = (void *)isysGObjSearchFromObjLayoutID(0x35);
        if (obj != 0) {
            iosOmBeforeFuncStandard(obj, 0xD, a0);
        }
    }
}

extern int GetChainHangRange(void *a0, int *a1);
extern int InitMailAdditionalData(int a0);
extern void func_00191DB8(void *a0, float a1);
extern float func_00191E30(void *a0);
extern int func_00192160(int a0);
extern void func_00260568(void *a0, int a1, int a2);
extern float D_00628F24;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ChangeMailInLadder);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTCorrectMsg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTGetOrientFromIntrK);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00154FE8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155138);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155288);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_001555B4);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155738);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTRunIntrCorrect);

extern void IsWallLeverStatus(void *a, void *b, int c);
extern void func_001BDE70(void *a, void *b, int c);

void func_00155FF8(void *a0, void *a1)
{
    int n = *(int *)((char *)a1 + 0xC);
    if (n >= 0x16) {
        if (n >= 0x18) {
            if (n < 0x1A) {
                func_001BDE70(a1, a0, 0x16);
            }
        } else {
            IsWallLeverStatus(a1, a0, 0x16);
        }
    }
}

extern void *ContinueCorrectPosition(void *a0);
extern void CylinderCollision(void *a0, void *a1);

void WithMailFunc_WayBeginPosError(void *a0, void *a1) {
    void *ret = ContinueCorrectPosition(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    CylinderCollision(a0, a1);
}

extern void SetRootMatrixWithTransOffsetByDObj(void *a0, int a1, void *a2, float a3);
extern void WallLeverGeo(void *a0, void *a1);
extern void _ACTWait(int a0);
extern void pushStartSE(void *a0, void *a1);
extern void dispPlane(void *a0, void *a1);
extern void func_00240038_p(void *a0, int a1, float f) __asm__("func_00240038");
extern int D_00271240[];
extern float D_00628F40;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_AttackFail);


extern void func_0018F2A0(void *a0);

void func_001561E8(void *a0, int a1) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        func_0018F2A0(a0);
}

extern char *D_00629DE8;
extern void debug_assertMessage();
extern void func_001561E8(void *a0, int a1);
extern void UpdatePointBlur(void *a0, void *a1, void *a2);
extern char D_0062C450[];
void WithMailFunc_AttackRejectInQueen(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v;
    debug_assertMessage(D_0062C450);
    if (a0 != (void *)D_00629DE8) {
        char *q = *(char **)((char *)a0 + 0x164);
        *(float *)(p + 0x1D0) -= (float)*(int *)(q + 0x1C0);
    }
    v = *(int *)((char *)a0 + 0xC);
    if (v == 4) {
        char *s;
        func_001561E8(a0, 5);
        s = *(char **)(*(char **)((char *)a0 + 0x164) + 0x670);
        UpdatePointBlur(a0, s + 0xE0, s + 0xF0);
    }
}

extern void WithMailFunc_AttackRejectInQueen(void *a0);

void GetCorrectOrientOfChain(void *a0)
{
    WithMailFunc_AttackRejectInQueen(a0);
    if (*(int *)((char *)a0 + 0xC) == 1) {
        void *p = *(void **)((char *)a0 + 0x164);
        func_001561E8(*(void **)((char *)p + 0x1A0), 6);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", CollisCheckInRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00156750);

extern float pac_DispQW(void);
extern void ACTParaStatus_Exec(void *a0);
extern void func_00156750(int a0, int a1, void *a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRope);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnR);

extern void traceLine(int a0, int a1, int a2, void *a3, int a4);
extern void ActPara_GetDefTbl(int a0, int a1);
extern char D_00552C78[], D_00552C88[];
extern void actCommonOne(volatile int a0);
extern void func_0015B4C8(void);
extern int D_0062AF84;
extern void BoxBarSoundOn(void *a0, int a1);

void motCommonRopeTurnL(volatile int self) {
    char *s164 = *(char **)(self + 0x164);
    char *o0 = *(char **)(*(char **)(self + 0x164) + 0x670);
    *(int *)(s164 + 0x14) = (int)actCommonOne;
    *(int *)(o0 + 0x2A0) = 0;
    for (;;) {
        if (D_0062AF84 & 1) {
            traceLine(0xA, 0xAA, 0x0FFFFFFF, D_00552C78,
                      *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0xCC));
            if (D_0062AF84 & 1) {
                traceLine(0xA, 0xB4, 0x0FFFFFFF, D_00552C88,
                          *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C));
            }
        }
        {
            int st = *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C);
            if (st < 0) goto tbl22;
            if (st < 2) goto after;
            if (st != 2) goto tbl22;
            ActPara_GetDefTbl(self, 0x21);
            goto after;
        tbl22:
            ActPara_GetDefTbl(self, 0x22);
        after:;
        }
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0xCC) < 0) {
            BoxBarSoundOn((void *)self, 0xB4);
            *(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C) = 0;
        }
        if (*(int *)(s164 + 0x48) >= 0x3D) {
            if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x670) + 0x29C) >= 3) {
                func_0015B4C8();
                _ACTWait(0);
            }
        }
        BoxBarSoundOn((void *)self, 0x68);
        _ACTWait(1);
    }
}

extern void BoxGeoRestore(int a0, int a1);
extern void RotObjectGeo(int a0);

void func_00156D18(void *a0) {
    CommonActState *s = *(CommonActState **)((char *)a0 + 0x164);
    int x = s->f_30;
    if (x == 0x31) goto h1;
    if (x == 0x33) goto h2;
    return;
h1:
    BoxGeoRestore(*(int *)((char *)s + 0x138), *(int *)((char *)s + 0x34));
    return;
h2:
    RotObjectGeo(*(int *)((char *)s + 0x5E8));
}

extern void BoxExtGeoRestore(void *a0);
extern void getRootMatrix(void *a0);

void actCommonRopeClimbEnd1(void *a0) {
    CommonActState *s = *(CommonActState **)((char *)a0 + 0x164);
    int state = s->f_30;
    if (state == 0x31) goto l1;
    if (state == 0x33) goto l2;
    return;
l1:
    BoxExtGeoRestore(*(void **)((char *)s + 0x138));
    return;
l2:
    getRootMatrix(*(void **)((char *)s + 0x5E8));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRopeCliff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", TestCageUpDown);

extern void dispPlane(void *a0, void *a1);

extern void ACTParaStatus_Clear(int a0);
void actCommonRopeSpecial(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    void *x = p->p_678;
    dispPlane(a0, (char *)x + 0x350);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", lever_nego1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", SetDirectRootPositionXZ);

extern void func_00104D20(void);
extern void func_00105068(void);
extern int func_00105078(void);
extern void func_001050A8(void *a0);
extern void func_0010F9D0(void);
extern void func_00118AA0(int a0);
extern void func_001D1DF0(int *a0, int *a1, int *a2, int *a3, int a4);
extern void gif_SpriteOffset(int a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float a3);
extern int D_0027E730[];

typedef struct { float x, y, z, w; } __attribute__((aligned(8))) Vec4;
typedef struct { Vec4 a, b; } Vec4Pair;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00157E70);


extern void func_00104D20(void);
extern int func_00105078(void);
extern void func_00118AA0(int a0);
extern void gif_SpriteOffset(int a0);
extern void func_001050A8(void *a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float f);
extern void func_0010F9D0(void);
extern void func_00105068(void);

void actCommonLever(void *a0, void *a1, float f) {
    func_00104D20();
    func_00118AA0(func_00105078());
    gif_SpriteOffset(0xB);
    func_001050A8(a0);
    reg_dispBoxLine(a1, 4, 4, f);
    func_0010F9D0();
    func_00105068();
}

extern void func_00104DC0(int a0);
extern void func_00105108(float a, float b, float c);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern int ClipWallBoxStop(void *a0);
extern int ChangeFieldCollisionDebugMode(void *a0);
extern void _TransposeRotationCurrentMatrix(void *a0, void *a1, void *a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", EBRAIN_SEND_MES);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DamageFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DownFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDown);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDie);

extern void debug_assertMessage();
extern char D_00552F88[];
extern char D_0062C478[];
extern char D_0062C480[];
void Cling(char *a0, void *a1, char *a2) {
    char *str = D_00552F88;
    void *p = *(void **)(a0 + 0x164);
    char *arg5;
    char *arg6;
    *(int *)((char *)p + 0xC0) |= 2;
    arg5 = (a2 == D_00629DE4) ? D_0062C478 : D_0062C480;
    arg6 = (a0 == D_00629DE4) ? D_0062C478 : D_0062C480;
    debug_assertMessage(str, arg5, arg6);
}

extern void debug_assertMessage();
extern char D_00552FA0[];
extern char D_0062C478[];
extern char D_0062C480[];
void actCommonCling(char *a0, void *a1, char *a2) {
    char *str = D_00552FA0;
    void *p = *(void **)(a0 + 0x164);
    char *arg5;
    char *arg6;
    *(int *)((char *)p + 0xC0) |= 8;
    arg5 = (a2 == D_00629DE4) ? D_0062C478 : D_0062C480;
    arg6 = (a0 == D_00629DE4) ? D_0062C478 : D_0062C480;
    debug_assertMessage(str, arg5, arg6);
}

extern void debug_assertMessage();
extern char D_00552FB8[];
extern char D_0062C478[];
extern char D_0062C480[];
void actCommonSlip(char *a0, void *a1, char *a2) {
    char *str = D_00552FB8;
    void *p = *(void **)(a0 + 0x164);
    char *arg5;
    char *arg6;
    *(int *)((char *)p + 0xC0) |= 0x10;
    arg5 = (a2 == D_00629DE4) ? D_0062C478 : D_0062C480;
    arg6 = (a0 == D_00629DE4) ? D_0062C478 : D_0062C480;
    debug_assertMessage(str, arg5, arg6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStoneDead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStone);

void BoxBarSoundOn(void *a0, int a1) {
    char *p = *(char **)((char *)a0 + 0x164);
    if ((a1 == 0xA6 || a1 == 0xAB) && *(int *)((char *)a0 + 0xC) == 1) {
        unsigned long long f470 = *(unsigned long long *)(p + 0x470);
        if ((unsigned int)(f470 >> 60) & 1) {
            if ((unsigned int)(*(unsigned long long *)(p + 0x480) >> 60) & 1) {
                a1 = 0xA7;
                goto done;
            }
        }
        if ((unsigned int)(f470 >> 58) & 1) {
            if ((unsigned int)(*(unsigned long long *)(p + 0x480) >> 58) & 1)
                a1 = 0xA8;
        }
    }
done:
    iosOmBeforeFuncStandard(a0, a1, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", BoxBarSoundOff);

void *subCommonIdle(char *a0);
extern int HandCameraCorrect(void *a0, void *a1);
extern void func_00191DB8(void *a0, float a1);
extern float D_00628FB4;

int _boxbar_set_sound(char *a0) {
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x170)) + 0x0);
    buf[1] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x170)) + 0x4);
    buf[2] = *(float *)((char *)subCommonIdle(*(char **)(*(char **)(a0 + 0x15C) + 0x170)) + 0x8);
    func_00191DB8(buf, D_00628FB4);
    return HandCameraCorrect(subCommonIdle(a0), buf) < 0
               ? -HandCameraCorrect(subCommonIdle(a0), buf) < 0x2D
               : HandCameraCorrect(subCommonIdle(a0), buf) < 0x2D;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBox);

extern void traceLine(int a0, int a1, int a2, void *a3, int a4);
extern void _OrientXZGV(void *a0, void *a1, void *a2, float a3, float a4);
extern char D_005530A8[];
extern int D_0062AF84;

extern void func_0023FE98(void *a0, void *a1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015AF10);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBar);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B250);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B398);

extern int D_00629DF4;
extern void lt_fade_status(int a0);

void func_0015B4C8(void) {
    if (D_00629DF4 == 0) {
        D_00629DF4 = 1;
        lt_fade_status(0x3A);
    }
}

extern void setNodePursueParticleEffectWithUpperLimit(int a0, int a1, float a2);

void funcCommonJumpDircorrect(int a0, int a1) {
    setNodePursueParticleEffectWithUpperLimit(a0, a1, 30.0f);
}

extern char D_0055DA10_a[] __asm__("D_0055DA10");
extern int actCommonStoneDead(void *a0, float *a1, float a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonFallDircorrect);


typedef struct { int _0, _4, _8, _C, _10; } ChainEntry;
extern ChainEntry D_00288FD0[];
typedef struct { int w[6]; } SlowrunRec;
extern SlowrunRec D_0028E680[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", correctJumpOrientByChain);


void actCommonJump(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    q->f_204--;
}

extern void func_0023FE98(void *a0, void *a1);
extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern int func_00260340(float a0);
extern int func_0025F4A0(int a0, double a1);

void actCommonFall(int self) {
    float buf[3];
    int sub = *(int *)(self + 0x15C);
    int r;

    buf[0] = *(float *)(sub + 0x1C0);
    buf[1] = *(float *)(sub + 0x1C4);
    buf[2] = *(float *)(sub + 0x1C8);
    func_0023FE98(buf, buf);
    r = func_00260340(MatrixDrive_GetTurnYAngleXZ(buf[0] * buf[0] + buf[2] * buf[2]));
    if (func_0025F4A0(r, 0.3) > 0) {
        buf[1] = 0.0f;
        func_0023FE98(buf, buf);
        dispPlane((void *)self, buf);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", debugDispFlyLimit);

extern void isExistEnemyParticle(char *a0);

void func_0015B740(volatile int a0) {
    CylinderCollision((void *)a0, *(char **)(a0 + 0x164) + 0x150);
    isExistEnemyParticle((char *)a0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xCF);
        _ACTWait(1);
    }
}


extern char D_00552BC0[];

void func_0015B790(volatile int a0) {
    debug_assertMessage(D_00552BC0);
    _ACTWait(0);
}


void debugDispSphere(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    if (*(int *)(s164 + 0xB8) == 0x17E && (*(int *)(s164 + 0x118) & 1)) {
        int q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
        *(short *)(s164 + 0x11A) = q * 5;
    }
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}


void func_0015B850(volatile int a0) {
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", getLandOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B938);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B9B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BA28);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BAA0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BAD8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BB20);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BB70);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BCA8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BD00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BD60);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BE38);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BEC8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015BF88);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C000);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C080);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", getAvoidCollisionFlyLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C0D8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C268);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C300);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C3F8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C418);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C4D8);

void emergencyCheck(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (1) {
        BoxBarSoundOn((void *)buf[0], 0xAE);
        _ACTWait(1);
    }
}

void func_0015C568(volatile int a0) {
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", flyCoreLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C5B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C620);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C650);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C708);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C778);

void actCommonFly(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}

extern void boss_effect_process(int a0);

void func_0015C7B8(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    *(int *)(s164 + 0x14) = (int)boss_effect_process;
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonLadder);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C818);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C870);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C8D0);

extern void _ACTWait(int a0);

void actCommonDodge(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 0xFFFFFFFF;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonEdgeHang);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015C9B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015CA48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015CAE0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015CB20);

extern void debug_assertMessage(void *a0);
extern void _ACTWait(int a0);
extern char D_00552F18[];
extern char D_00552F38[];

void funcCommonBeginReady(volatile int a0) {
    debug_assertMessage(D_00552F18);
    _ACTWait(0);
}

void funcCommonEndReady(volatile int a0) {
    debug_assertMessage(D_00552F38);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonEndExec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015CD08);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015CE60);

extern int CanWallLeverPull(int a0, int a1);
extern char D_0062C498[];
extern char D_0062C4A0[];

void funcCommonError(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(0x1E);
    CanWallLeverPull(v, -1);
    debug_assertMessage(D_0062C498);
    _ACTWait(0);
}

void SetMotionDirectionSmooze(volatile int a0) {
    char *state = *(char **)(a0 + 0x164);
    int v = *(int *)(state + 0x5EC);
    _ACTWait(0x1E);
    CanWallLeverPull(v, 1);
    debug_assertMessage(D_0062C4A0);
    _ACTWait(0);
}

void _ACTDebugPrint(int **a0, int a1, int a2) {
    int *p = a0[0x59];
    p[0x60] = a2;
}

extern int isBottomOfChain(int a0, int a1);
extern char D_00552B48[];
void ACTSendMailCorrect(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    int self;
    debug_assertMessage(D_00552B48);
    isBottomOfChain(*(int *)(s + 0x180), a0);
    self = a0;
    *(int *)(s + 0x184) = *(int *)(s + 0x180);
    *(int *)(*(int *)(self + 0x15C) + 0x410) = 0;
}


void _ACTCommonMailTest(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}


extern void *D_0062A4DC;

void func_0015CFF0(volatile int a0) {
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard((void *)D_00629DE8, 0x3F, D_0062A4DC);
    }
    for (;;) {
        _ACTWait(1);
    }
}


extern int D_0062A7E8;

void func_0015D028(int a0) {
    if (a0 == (int)D_00629DE8) {
        D_0062A7E8 = 1;
    }
}


void E3_LeverCheck(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    q->f_250 = 0;
}

extern void *ExecMotionOrient(void *a0, void *a1, void *a2);

int actCommonBecarry(void *a0, void *a1) {
    char *s = *(char **)((char *)a0 + 0x164);
    void *r = ExecMotionOrient(a0, a1, s + 0x610);
    *(void **)(s + 0x110) = r;
    return *(int *)((char *)r + 0xC) != 0;
}

extern char *D_00629DE8;
extern char D_006A4620[];
extern void InitKeyInput(void *a0, void *a1);
extern int GetOrientOfWallOfGObj(void *a0, void *a1);
void *subCommonIdle(char *a0) {
    char *p;
    if (a0 != D_00629DE4 && a0 != D_00629DE8 && *(int *)(a0 + 0xC) != 4) {
        InitKeyInput(D_006A4620, a0);
        return D_006A4620;
    }
    p = *(char **)(a0 + 0x164) + 0xD0;
    GetOrientOfWallOfGObj(p, a0);
    return p;
}

extern void GetRootMatrixByDObj(void *out, void *obj);
extern void CageFixDL(void *a0, void *a1, void *a2);
extern char D_006A4630[];

void *ContinueCorrectPosition(void *a0) {
    char *s0;
    int x = *(int *)((char *)a0 + 0xC);
    switch (x) {
    case 1:
    case 2:
    case 4:
        s0 = *(char **)((char *)a0 + 0x164) + 0xE0;
        GetRootMatrixByDObj(s0, a0);
        return s0;
    case 0x2B: {
        int local[4];
        CageFixDL(D_006A4630, local, a0);
        return D_006A4630;
    }
    default:
        GetRootMatrixByDObj(D_006A4630, a0);
        return D_006A4630;
    }
}


typedef struct { char _p670[0x670]; char *p670; } S164;
typedef struct { char _p164[0x164]; S164 *p164; } SObj;


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonTurn);
#undef TURN_OBJ


int actCommonBackhand(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    long long v = q->f_BC;
    return (int)v & 1;
}

void actCommonSlowrun(int a0, int a1) {
    D_0028E680[a0].w[2] = a1;
}

extern void func_00240038(void *a0, float f);

void ACT_LAYOUT_GAMEOVER(void *a0) {
    int local[4];
    func_00240038(local, -1.0f);
    dispPlane(a0, local);
}

extern void func_00240038_p(void *a0, int a1, float f) __asm__("func_00240038");

void ACTAdjustPlane(int *self)
{
    int buf[4];
    func_00240038_p(buf, (int)((char *)self[0x164 / 4] + 0x4A0), -1.0f);
    dispPlane((void *)self, buf);
}

extern void ChangeMailInLadder(void *buf, void *obj);

void _ACTMotDirSmzDirect(void *a0) {
    int local[4];
    ChangeMailInLadder(local, a0);
    dispPlane(a0, local);
}

extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern void eBrainInit(int a0);
extern char D_00552B60[];
extern char D_00552B70[];

void WithMailFunc_Idling(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    if (*(int *)(s + 0x180) == 0) {
        func_001AAD00(D_00552B60, 0x593);
        func_00260380(D_00552B60, 0x593, D_00552B70);
    }
    eBrainInit(*(int *)(s + 0x180));
}


extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern void eBrainInit(int a0);
extern char D_00552B60[];
extern char D_00552B70[];

void WithMailFunc_BossDamaged(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    if (*(int *)(s + 0x180) == 0) {
        func_001AAD00(D_00552B60, 0x60D);
        func_00260380(D_00552B60, 0x60D, D_00552B70);
    }
    eBrainInit(*(int *)(s + 0x180));
}


void WithMailFunc_FallDead(volatile int a0) {
    int q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    void *p = *(void **)(*(char **)(a0 + 0x164) + 0x678);
    *(int *)((char *)p + 0x368) = q * 0x82 / 0x3C;
}


void actCommonRevive(volatile int a0) {
    ACTParaStatus_Clear(a0);
}

void actCommonReviveAir(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actCommonPlay(volatile int a0) {
    ACTParaStatus_Clear(a0);
}

void actCommonOne(volatile int a0) {
    int x = a0;
    int y = a0;
    *(int *)(*(int *)(*(int *)(x + 0x164) + 0x670) + 0x2A0) = -1;
    *(int *)(*(int *)(*(int *)(y + 0x164) + 0x670) + 0x2A4) = 0;
}

extern void actCommonRopeCliff(int a0, int a1);

void actCommonDelete(volatile int a0) {
    actCommonRopeCliff(a0, 0);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_00288FD0;  /* stride 0x14 */

typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
} S_0027E700;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
} S_0028E680;  /* stride 0x18 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0055D4B0;  /* stride 0x4 */

/* end struct shapes */


