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
extern int iosOmSendMail(void *a0, int a1, void *a2);
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
            iosOmSendMail(obj, 0xD, a0);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ChangeMailInLadder);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTCorrectMsg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTGetOrientFromIntrK);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_AttackFail);

extern void func_0018F2A0(void *a0);

void func_001561E8(void *a0, int a1) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        func_0018F2A0(a0);
}

extern char *D_00629DE8;
extern void debug_StdPrintfDummy();
extern void func_001561E8(void *a0, int a1);
extern void UpdatePointBlur(void *a0, void *a1, void *a2);
extern char D_0062C450[];
void WithMailFunc_AttackRejectInQueen(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    int v;
    debug_StdPrintfDummy(D_0062C450);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnL);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00157E70);

extern void func_00104D20(void);
extern int func_00105078(void);
extern void _UnitMatrix(int a0);
extern void gif_SpriteOffset(int a0);
extern void func_001050A8(void *a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float f);
extern void func_0010F9D0(void);
extern void MatrixDrive_PopMatrix(void);

void actCommonLever(void *a0, void *a1, float f) {
    func_00104D20();
    _UnitMatrix(func_00105078());
    gif_SpriteOffset(0xB);
    func_001050A8(a0);
    reg_dispBoxLine(a1, 4, 4, f);
    func_0010F9D0();
    MatrixDrive_PopMatrix();
}

void EBRAIN_SEND_MES(void) {
    /* TODO: scaffold unavailable — recover from asm */
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DamageFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DownFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDown);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDie);

extern void debug_StdPrintfDummy();
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
    debug_StdPrintfDummy(str, arg5, arg6);
}

extern void debug_StdPrintfDummy();
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
    debug_StdPrintfDummy(str, arg5, arg6);
}

extern void debug_StdPrintfDummy();
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
    debug_StdPrintfDummy(str, arg5, arg6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStoneDead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStone);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", BoxBarSoundOn);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", BoxBarSoundOff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _boxbar_set_sound);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015AF10);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBar);

extern int D_00629DF4;
extern void lt_fade_status(int a0);

void func_0015B4C8(void) {
    if (D_00629DF4 == 0) {
        D_00629DF4 = 1;
        lt_fade_status(0x3A);
    }
}

extern void AdjustRootPositionToVerticalSidePlaneOfWall(int a0, int a1, float a2);

void funcCommonJumpDircorrect(int a0, int a1) {
    AdjustRootPositionToVerticalSidePlaneOfWall(a0, a1, 30.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonFallDircorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", correctJumpOrientByChain);

void actCommonJump(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    q->f_204--;
}

extern void sceVu0Normalize(void *a0, void *a1);
extern float FSqrt(float a0);
extern int fptodp(float a0);
extern int dpcmp(int a0, long long a1);
extern long long D_005530B8_a[] __asm__("D_005530B8");

void actCommonFall(int self) {
    float buf[3];
    int sub = *(int *)(self + 0x15C);
    int r;

    buf[0] = *(float *)(sub + 0x1C0);
    buf[1] = *(float *)(sub + 0x1C4);
    buf[2] = *(float *)(sub + 0x1C8);
    sceVu0Normalize(buf, buf);
    r = fptodp(FSqrt(buf[0] * buf[0] + buf[2] * buf[2]));
    if (dpcmp(r, D_005530B8_a[0]) > 0) {
        buf[1] = 0.0f;
        sceVu0Normalize(buf, buf);
        dispPlane((void *)self, buf);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", debugDispFlyLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", debugDispSphere);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", getLandOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", getAvoidCollisionFlyLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", emergencyCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", flyCoreLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonFly);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonLadder);

extern void _ACTWait(int a0);

void actCommonDodge(volatile int a0) {
    CommonActState *s = *(CommonActState **)(a0 + 0x164);
    s->f_34 = 0xFFFFFFFF;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonEdgeHang);

extern void debug_StdPrintfDummy(void *a0);
extern void _ACTWait(int a0);
extern char D_00552F18[];
extern char D_00552F38[];

void funcCommonBeginReady(volatile int a0) {
    debug_StdPrintfDummy(D_00552F18);
    _ACTWait(0);
}

void funcCommonEndReady(volatile int a0) {
    debug_StdPrintfDummy(D_00552F38);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonEndExec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonError);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", SetMotionDirectionSmooze);

void _ACTDebugPrint(int **a0, int a1, int a2) {
    int *p = a0[0x59];
    p[0x60] = a2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTSendMailCorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTCommonMailTest);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ContinueCorrectPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonTurn);

int actCommonBackhand(void *a0) {
    CommonActState *p = *(CommonActState **)((char *)a0 + 0x164);
    CBrain670 *q = p->p_670;
    long long v = q->f_BC;
    return (int)v & 1;
}

typedef struct { int w[6]; } SlowrunRec;
extern SlowrunRec D_0028E680[];

void ControlMotionOrient(int a0, int a1) {
    D_0028E680[a0].w[2] = a1;
}

extern void sceVu0ScaleVector(void *a0, float f);

void _ACTMotDir_V(void *a0) {
    int local[4];
    sceVu0ScaleVector(local, -1.0f);
    dispPlane(a0, local);
}

extern void func_00240038_p(void *a0, int a1, float f) __asm__("sceVu0ScaleVector");

void ACTAdjustPlane(int *self)
{
    int buf[4];
    func_00240038_p(buf, (int)((char *)self[0x164 / 4] + 0x4A0), -1.0f);
    dispPlane((void *)self, buf);
}

extern void ChangeMailInLadder(void *buf, void *obj);

void SetCorrectOrientOfChain(void *a0) {
    int local[4];
    ChangeMailInLadder(local, a0);
    dispPlane(a0, local);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_Idling);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_BossDamaged);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_FallDead);

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

void afterCommonBox(volatile int a0) {
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
