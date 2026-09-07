#include "common.h"

#include "ico/types.h"

typedef struct { int a, b, c; } S12;

typedef struct { char pad[4]; float f4; } CCPResult;

ASM_LIT4_SLOT(D_00638D30, 0.8f);
ASM_LIT4_SLOT(D_00638D34, 4.9e+03f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", findChainInJump);
INCLUDE_ASM("asm/nonmatchings/src/boyact", CorrectOrient_RopeCliff);
extern void debug_StdPrintfDummy();
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void iosOmSendMail(void *gobj, int mail, void *arg);
extern void *D_00639EA8;
extern void *D_0063A61C;
extern char D_00552770[];

void motBoyHand50(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00552770);
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x5C, D_0063A61C);
        }
        if (*(int *)(sub + 0xE0) & 1) {
            break;
        }
        _ACTWait(1);
    }
    while (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0
           || 2 <= *(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0)) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x5D, D_0063A61C);
        }
        if (*(int *)(sub + 0xE0) & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(0x2D);
    *(int *)(sub + 0x14) = 0;
    while (1) {
        ACTSendMailCorrect(a0, 0x47);
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", motBoyHand100);
INCLUDE_ASM("asm/nonmatchings/src/boyact", motBoyHand200);
INCLUDE_ASM("asm/nonmatchings/src/boyact", handoff_heroin);
INCLUDE_ASM("asm/nonmatchings/src/boyact", CheckCollisionAttr);
typedef struct {
    int id;                     /* 0x00 */
    float f04;
    float f08;
    unsigned char b0C;          /* 0x0C */
    unsigned char b0D;
    unsigned char b0E;
    unsigned char b0F;
    float f10;                  /* 0x10 */
    char pad14[0x20 - 0x14];
    float f20[4];               /* 0x20 */
    float f30[4];               /* 0x30 */
} BgaEntry;

extern BgaEntry D_0029C690[];
extern void *test_CURRENTORIENT(void *a0);
extern CCPResult *test_CURRENTROOT(void *a0);
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void _OrientXZGV(void *dst, void *a, void *b);
extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void ActGame_GetOrientQ(void *q, void *v, int deg);
extern void _ApplyRyGV(void *v, float ry);
extern float stage_PlayBgAnimation(float frame, int id, void *a, void *b);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern char D_00552808[];
extern char D_0063A6D0[];

void BoyBgaManager(void *self, int id, void *dst)
{
    /* UpdateGeo is a NESTED function in the ROM: BoyBgaManager passes it the
       static chain in $2 (STATIC_CHAIN_REGNUM) and UpdateGeo reads `self` out
       of the enclosing frame at 0($sp).  The PAL listing names it
       `UpdateGeo.170`, gcc's mangling for a nested function. */
    void UpdateGeo(BgaEntry *p)
    {
        float dir[4];
        float tmp[4];
        void *obj;

        if (p->b0F != 0) {
            dir[0] = ((float *)test_CURRENTORIENT(self))[0];
            dir[1] = ((float *)test_CURRENTORIENT(self))[1];
            dir[2] = ((float *)test_CURRENTORIENT(self))[2];
        } else {
            obj = isysGObjSearchFromObjKindID_begin(0x2F);
            _OrientXZGV(dir, test_CURRENTROOT(obj), test_CURRENTROOT(self));
        }
        sceVu0ScaleVector(dir, dir, p->f10);
        ActGame_GetOrientQ(p->f30, dir, 0);
        sceVu0ScaleVector(tmp, test_CURRENTORIENT(self), p->f08);
        sceVu0AddVector(p->f20, test_CURRENTROOT(self), tmp);
        sceVu0ScaleVector(tmp, test_CURRENTORIENT(self), p->f04);
        _ApplyRyGV(tmp, 1.5707964f);
        sceVu0AddVector(p->f20, p->f20, tmp);
        p->f20[1] += (float)p->b0D;
    }
    BgaEntry *p;
    int i;
    int v;
    int r;

    for (i = 0; 0 <= D_0029C690[i].id; i++) {
        if (D_0029C690[i].id == id) {
            p = &D_0029C690[i];
            goto found;
        }
    }
    debug_assert(D_00552808, 1731);
    __assert(D_00552808, 1731, D_0063A6D0);
    p = 0;
found:
    v = *(int *)dst;
    if (v < 0) {
        return;
    }
    if (p->b0C != 0) {
        UpdateGeo(p);
        goto reload;
    }
    if (v == 0) {
        UpdateGeo(p);
    reload:
        v = *(int *)dst;
    }
    r = (int)stage_PlayBgAnimation((float)v, p->id, p->f20, p->f30);
    if (p->b0E == 0) {
        *(int *)dst = r;
    } else if (0 <= r) {
        *(int *)dst = r;
    }
}
extern unsigned char D_0063C1F6;
extern unsigned char D_0063C1F7;
extern unsigned char D_0063C1F8;
extern void *test_CURRENTORIENT(void *a0);
extern CCPResult *test_CURRENTROOT(void *a0);
extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void SetDirectRootPositionNoFitting(void *w, float *pos);
extern int gflagChk(int a0);
extern void gflagOff(int a0);
extern int GetStageStartInfo(void *self, int a1, int a2, int *w1, int *w2, int *w3);
extern void scpPlayStart(void *a0);
extern void scpPlayMotReq(void *a0, int a1);
extern void scpPlayEnd(void *a0);

void E3_StageStartBoy(void *self)
{
    float buf[4];
    int w1;
    int w2;
    int w3;

    if (D_0063C1F6 != 0) {
        sceVu0ScaleVector(buf, test_CURRENTORIENT(self), 100.0f);
        sceVu0AddVector(buf, buf, test_CURRENTROOT(self));
        SetDirectRootPositionNoFitting(self, buf);
    }
    if (gflagChk(0x17D)) {
        gflagOff(0x17D);
        return;
    }
    if (GetStageStartInfo(self, 0, 0, &w1, &w2, &w3) == 0) {
        return;
    }
    if (D_0063C1F8 != 0) {
        return;
    }
    if (D_0063C1F7 != 0) {
        return;
    }
    _ACTWait(3);
    GetStageStartInfo(self, 0, 0, &w1, &w2, &w3);
    _ACTWait(w1);
    scpPlayStart(self);
    scpPlayMotReq(self, 8);
    _ACTWait(w2);
    scpPlayEnd(self);
    _ACTWait(w3);
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", GetChainSlope);
ASM_LIT4_SLOT(D_00638D3C, 8.5e+02f);
ASM_LIT4_SLOT(D_00638D40, 0.1f);
ASM_LIT4_SLOT(D_00638D44, 3.1415927f);
ASM_LIT4_SLOT(D_00638D48, 7.5e+02f);
ASM_LIT4_SLOT(D_00638D4C, 0.1f);
ASM_LIT4_SLOT(D_00638D50, 0.99f);
ASM_LIT4_SLOT(D_00638D54, 0.1f);
ASM_LIT4_SLOT(D_00638D58, 0.99f);
ASM_LIT4_SLOT(D_00638D5C, 0.1f);
ASM_LIT4_SLOT(D_00638D60, 0.1f);
ASM_LIT4_SLOT(D_00638D64, 0.1f);
ASM_LIT4_SLOT(D_00638D68, 0.1f);
ASM_LIT4_SLOT(D_00638D6C, 0.1f);
ASM_LIT4_SLOT(D_00638D70, 0.1f);
ASM_LIT4_SLOT(D_00638D74, 0.1f);
ASM_LIT4_SLOT(D_00638D78, 0.1f);
ASM_LIT4_SLOT(D_00638D7C, 0.1f);
ASM_LIT4_SLOT(D_00638D80, 0.1f);
ASM_LIT4_SLOT(D_00638D84, 0.1f);
ASM_LIT4_SLOT(D_00638D88, 0.1f);
ASM_LIT4_SLOT(D_00638D8C, 0.1f);
ASM_LIT4_SLOT(D_00638D90, 0.1f);
ASM_LIT4_SLOT(D_00638D94, 0.1f);
ASM_LIT4_SLOT(D_00638D98, 0.1f);
ASM_LIT4_SLOT(D_00638D9C, 0.1f);
ASM_LIT4_SLOT(D_00638DA0, 2.5e+05f);
ASM_LIT4_SLOT(D_00638DA4, 0.1f);
ASM_LIT4_SLOT(D_00638DA8, 0.1f);
ASM_LIT4_SLOT(D_00638DAC, 0.1f);
ASM_LIT4_SLOT(D_00638DB0, 0.95f);
ASM_LIT4_SLOT(D_00638DB4, 0.95f);
ASM_LIT4_SLOT(D_00638DB8, 0.1f);
ASM_LIT4_SLOT(D_00638DBC, 0.1f);
ASM_LIT4_SLOT(D_00638DC0, 0.1f);
ASM_LIT4_SLOT(D_00638DC4, 0.1f);
ASM_LIT4_SLOT(D_00638DC8, 0.1f);
ASM_LIT4_SLOT(D_00638DCC, 0.99f);
ASM_LIT4_SLOT(D_00638DD0, 0.1f);
ASM_LIT4_SLOT(D_00638DD4, 0.99f);
ASM_LIT4_SLOT(D_00638DD8, 0.1f);
ASM_LIT4_SLOT(D_00638DDC, 0.1f);
ASM_LIT4_SLOT(D_00638DE0, 0.1f);
ASM_LIT4_SLOT(D_00638DE4, 0.1f);
ASM_LIT4_SLOT(D_00638DE8, 0.1f);
ASM_LIT4_SLOT(D_00638DEC, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", subBoyControl);
extern long long D_006C0AD0[];

typedef struct { int a; int b; } CharPos;

typedef struct {
    int boyID;                      /* 0x00 */
    int girlID;                     /* 0x04 */
    unsigned long long pad0 : 32;   /* 0x08 */
    unsigned long long bit32 : 1;
    unsigned long long fire : 1;
    unsigned long long torch : 1;
    unsigned long long escort : 1;
    char pad10[0x10];               /* 0x10 */
    void *weapon;                   /* 0x20 */
    void *nextWeapon;               /* 0x24 */
    char pad28[0x30 - 0x28];        /* 0x28 */
    float f30;                      /* 0x30 */
    float f34;
    float f38;
    char pad3C[4];
    float f40;                      /* 0x40 */
    float f44;
    float f48;
    char pad4C[4];
    CharPos f50;                    /* 0x50 */
} BoyInfo;
#define BOYINFO (*(BoyInfo *)D_006C0AD0)

typedef struct {
    char pad00[0x0C];
    float f0C;                      /* 0x0C */
    float f10;
    float f14;
    float f18;                      /* 0x18 */
    float f1C;
    float f20;
    char pad24[0x4C - 0x24];
} WeaponOffsetRow;                  /* 0x4C */

extern char D_002C2DC8[];
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *gamesysObjInfoGet(int a0, int a1);

void InitSwapWeapon(void *self)
{
    char *sub = *(char **)((char *)self + 0x164);
    char *info;
    char *p;
    WeaponOffsetRow *row;

    if (BOYINFO.boyID != 0) {
        BOYINFO.weapon = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
    } else {
        BOYINFO.weapon = 0;
    }
    info = *(char **)(sub + 0x608);
    BOYINFO.nextWeapon = info;
    p = (char *)gamesysObjInfoGet(*(int *)(info + 0xC), *(int *)(info + 0x8));
    if (p != 0) {
        BOYINFO.f30 = *(float *)(p + 0x10);
        BOYINFO.f34 = *(float *)(p + 0x14);
        BOYINFO.f38 = *(float *)(p + 0x18);
        BOYINFO.f40 = *(float *)(p + 0x20);
        BOYINFO.f44 = *(float *)(p + 0x24);
        BOYINFO.f48 = *(float *)(p + 0x28);
    } else {
        row = (WeaponOffsetRow *)(*(int *)(info + 0x8) * sizeof(WeaponOffsetRow)
                                  + D_002C2DC8);
        BOYINFO.f30 = -row->f18;
        BOYINFO.f34 = -row->f1C;
        BOYINFO.f38 = -row->f20;
        BOYINFO.f40 = row->f0C * 3.1415927f / 180.0f;
        BOYINFO.f44 = row->f10 * 3.1415927f / 180.0f;
        BOYINFO.f48 = row->f14 * 3.1415927f / 180.0f;
    }
}
extern void InitMotionGeoInfo(void *node, float x, float y, float z, float rx, float ry, float rz);
extern int CheckWeaponKind(void *w);
extern void UpdateRootMatrix(void *a0);
extern void SetWeaponOffsetMode(void *w, int mode);
extern long long D_006C0AD0[];

void PutWeapon(void)
{
    char *p = (char *)D_006C0AD0;

    if (*(void **)(p + 0x20) != 0) {
        InitMotionGeoInfo(*(char **)(*(char **)(p + 0x20) + 0x15C) + 0xA0,
                          *(float *)(p + 0x30), *(float *)(p + 0x34), *(float *)(p + 0x38),
                          -*(float *)(p + 0x40), -*(float *)(p + 0x44), -*(float *)(p + 0x48));
        if (CheckWeaponKind(*(void **)(p + 0x20)) == 9) {
            SetWeaponOffsetMode(*(void **)(p + 0x20), 1);
        }
        UpdateRootMatrix(*(void **)(p + 0x20));
    }
}
ASM_LIT4_SLOT(D_00638DF4, 0.05f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", OtherStageGirlPinchCamera_After);
extern void BoyBgaManager(void *self, int id, void *p);

void ACTDispLwsBoyStonize_InQueenStage(void *self)
{
    BoyBgaManager(self, 0x1E0, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A0);
    BoyBgaManager(self, 0x1E1, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A4);
    BoyBgaManager(self, 0x1E5, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2B0);
    BoyBgaManager(self, 0x1E5, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2AC);
    BoyBgaManager(self, 0x1E6, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A8);
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", PrivInsCamProcess);
ASM_LIT4_SLOT(D_00638DF8, 0.1f);
ASM_LIT4_SLOT(D_00638DFC, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", subBoyCollision);
ASM_LIT4_SLOT(D_00638E00, 4e+04f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoySwim);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyWalk);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyRun);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyAttack);
extern CCPResult *test_CURRENTROOT(void *a0);
extern void *test_CURRENTORIENT(void *a0);
extern void _OrientXZGV(void *dst, void *a, void *b);
extern void SetMotionDirection(void *self, float *dir);
extern int _AbsRotyGV(void *a, void *b);
extern void _ACTMotDirSmzDirect(void *self, float *dir);
extern int D_0028F4C0[];

void actBoyTakeWeaponReady(volatile int a0)
{
    float w[4];
    float p[4];
    float dir[4];
    char *obj;
    int first = 1;
    int n = 0;

    obj = *(char **)(*(char **)((char *)a0 + 0x164) + 0x608);
    w[0] = ((float *)test_CURRENTROOT(obj))[0];
    w[1] = ((float *)test_CURRENTROOT(obj))[1];
    w[2] = ((float *)test_CURRENTROOT(obj))[2];
    while (1) {
        p[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
        p[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
        p[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
        _OrientXZGV(dir, w, p);
        if (first) {
            SetMotionDirection((void *)a0, dir);
            first = 0;
        } else if (_AbsRotyGV(test_CURRENTORIENT((void *)a0), dir) < 0x1E) {
            _ACTMotDirSmzDirect((void *)a0, dir);
        } else {
            ACTSendMailCorrect(a0, 0xCC);
        }
        if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < n++) {
            ACTSendMailCorrect(a0, 0xCC);
        }
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyTakeWeapon);
extern void ACTAdjustPlane(int a0, void *p);
extern void GetOrientOfWall(void *out, void *wall, void *pos);
extern int CompareAttribute(int attr, int mask);
extern void brainSetSpMode(void);

#define BOY_WALL(o) (*(char **)(*(char **)((char *)(o) + 0x164) + 0x688))

void actBoyCliffHesitate(volatile int a0)
{
    int hit = 0;

    ACTAdjustPlane(a0, BOY_WALL(a0) + 0x8C0);
    GetOrientOfWall(BOY_WALL(a0) + 0x8D0, *(void **)(BOY_WALL(a0) + 0x8C8),
                    BOY_WALL(a0) + 0x8C0);
    if (CompareAttribute(*(int *)(*(char **)(BOY_WALL(a0) + 0x8C8) + 0x48), 0x400)) {
        hit = 1;
        *(S12 *)(BOY_WALL(a0) + 0x490) = *(S12 *)(BOY_WALL(a0) + 0x8C0);
    }
    while (1) {
        if (hit) {
            ACTSendMailCorrect(a0, 0x8C);
        }
        if (D_00639EA8 != 0) {
            brainSetSpMode();
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x3D, D_0063A61C);
            }
        }
        ACTSendMailCorrect(a0, 0x128);
        _ACTWait(1);
    }
}
extern void *D_00639EA4;
extern CCPResult *test_CURRENTROOT(void *a0);

#define BOY_GIRL_DY() (((float *)test_CURRENTROOT(D_00639EA8))[1] \
                       - ((float *)test_CURRENTROOT(D_00639EA4))[1])

void ACTSendMail_PULLUP_GO(void)
{
    char *g = (char *)D_00639EA4;
    char *sub = *(char **)(g + 0x164);

    switch (*(int *)(sub + 0x5E4)) {
    case 0x64:
        ACTSendMailCorrect((int)g, 0x4A);
        *(int *)(sub + 0x44) = 0x6B;
        break;
    case 0xC8:
        ACTSendMailCorrect((int)g, 0x4A);
        *(int *)(sub + 0x44) = 0x6D;
        break;
    case 0x12C:
        if (*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34) != 0x50) {
            break;
        }
        if (!(300.0f < (BOY_GIRL_DY() < 0.0f ? -BOY_GIRL_DY() : BOY_GIRL_DY()))) {
            ACTSendMailCorrect((int)g, 0x4A);
            *(int *)(sub + 0x44) = 0x6F;
        } else if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x52, D_0063A61C);
        }
        break;
    }
}
extern void *D_00639EA0;
extern void *D_00639EA4;
extern void *D_00639EA8;
extern void *D_0063A61C;
extern CCPResult *test_CURRENTROOT(void *a0);
extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern float sceVu0InnerProduct(void *a, void *b);
extern float _DistxzGV(void *a, void *b);
extern float _DistSqGV(void *a, void *b);
extern void GetSkeltonPosition(float *out, void *gobj, int node);
extern void iosOmSendMail(void *gobj, int mail, void *arg);
extern void ACTSendMailCorrect(int a0, int mail);

int pullup_check_heroin_position(void)
{
    float buf[4];
    float p1[4];
    float p2[4];
    char *g = (char *)D_00639EA4;
    char *s = *(char **)(g + 0x164);

    if (D_00639EA0 != 0 && *(int *)(s + 0x5E4) == 300) {
        switch (*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34)) {
        case 4:
            GetSkeltonPosition(p1, D_00639EA8, 0x16);
            GetSkeltonPosition(p2, D_00639EA4, 6);
            if (_DistSqGV(p1, p2) < 3600.0f) {
                if (D_00639EA8 != 0) {
                    iosOmSendMail(D_00639EA8, 0x59, D_0063A61C);
                }
            }
            return 0;
        case 0x51:
            ACTSendMailCorrect((int)D_00639EA4, 0x58);
            return 0;
        default:
            return 0;
        }
    }
    sceVu0SubVector(buf, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    if (0.0f < sceVu0InnerProduct(buf, s + 0x4C0)
        && _DistxzGV(s + 0x500, test_CURRENTROOT(D_00639EA8)) < 100.0f
        && ((unsigned int)(*(unsigned long long *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x18) >> 54) & 1)
        && (D_00639EA8 == 0 || D_00639EA4 == 0
            || !(test_CURRENTROOT(D_00639EA8)->f4 > test_CURRENTROOT(D_00639EA4)->f4 + 450.0f))) {
        return 1;
    }
    return 0;
}
extern void *D_00639EA4;
extern void *D_00639EA8;
extern CCPResult *test_CURRENTROOT(void *a0);
extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern float sceVu0InnerProduct(void *a, void *b);
extern float _DistxzGV(void *a, void *b);

int ditch_check_heroin_position(void)
{
    float buf[4];
    char *s = *(char **)((char *)D_00639EA4 + 0x164);

    sceVu0SubVector(buf, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    if (0.0f < sceVu0InnerProduct(buf, (float *)(s + 0x4C0))
        && _DistxzGV(s + 0x510, test_CURRENTROOT(D_00639EA8)) < 31.0f
        && (D_00639EA8 == 0 || D_00639EA4 == 0
            || !(test_CURRENTROOT(D_00639EA8)->f4 > test_CURRENTROOT(D_00639EA4)->f4 + 200.0f))) {
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyPullupReady);
ASM_LIT4_SLOT(D_00638E04, 0.99f);
ASM_LIT4_SLOT(D_00638E08, 0.1f);
ASM_LIT4_SLOT(D_00638E0C, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyPullupGo);
ASM_LIT4_SLOT(D_00638E10, 0.2f);
ASM_LIT4_SLOT(D_00638E14, 2.5e+03f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyBelift);
ASM_LIT4_SLOT(D_00638E18, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyReadyMove);
ASM_LIT4_SLOT(D_00638E1C, 0.05f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyRescueReady);
ASM_LIT4_SLOT(D_00638E20, 2.5e+05f);
ASM_LIT4_SLOT(D_00638E24, 9e+04f);
ASM_LIT4_SLOT(D_00638E28, 1e+04f);
ASM_LIT4_SLOT(D_00638E2C, 7.84e+04f);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyDitch3mReady);
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyRescueGirlBhang);
extern float _ACTGame_GetParamF(int idx);
extern void ExecuteSEPackage(int a0, int a1);
extern void GetOtherStageGirlOrient(float *out, void *cam);
extern float *GetCurrentCameraSet2(void);
extern void InsertCamera_SetNoraml(float *a, float *b, int c, int d);

void SetStatusBoy_OtherStageGirlPinch(void)
{
    float buf[4];
    float cam[4];
    float pos[4];
    char *g = (char *)D_00639EA4;
    char *w;
    float a;
    float b;
    float t;
    int frames;

    a = _ACTGame_GetParamF(0xD);
    b = _ACTGame_GetParamF(0xE);
    t = a * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f
        + b * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f;
    ExecuteSEPackage(0, 0x7F);
    GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
    w = *(char **)(*(char **)(g + 0x164) + 0x688);
    frames = (int)t;
    *(int *)(w + 0x4B0) = frames;
    *(float *)(w + 0x4A0) = buf[0];
    *(float *)(w + 0x4A4) = buf[1];
    *(float *)(w + 0x4A8) = buf[2];
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    pos[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
    pos[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
    pos[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
    InsertCamera_SetNoraml(cam, pos, frames, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", actBoyStart);
extern void ConvertStickToAbsCoord();
extern void _RotyGV();

void CorrectStickInfo(int a0)
{
    int buf[4];
    ConvertStickToAbsCoord(buf);
    _RotyGV(buf, a0);

}
extern void *D_00639EA4;

void *GetBoyWeaponGObj(void) {
    char *g = (char *)D_00639EA4;
    if (g != 0) {
        return *(void **)(*(char **)(g + 0x164) + 0x150);
    }
    return 0;
}
typedef struct {
    char pad00[0x18C];
    unsigned int flags18C;
    char pad190[4];
} BoyParaRow;

extern char D_0055FE58[];
extern void ACTAdjustPlane(int a0, void *p);
extern void _ACTWait(int a0);

void actBoyStand(volatile int a0)
{
    BoyParaRow *row = (BoyParaRow *)(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0)
                                     * sizeof(BoyParaRow) + D_0055FE58);

    if ((row->flags18C >> 8) & 1) {
        ACTAdjustPlane(a0, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8B0);
    }
    while (1) {
        _ACTWait(1);
    }
}
extern void ACTAdjustPlane(int a0, void *p);
extern void _ACTWait(int a0);

void actBoyHang(volatile int a0)
{
    char *g = (char *)a0;
    ACTAdjustPlane(a0, *(char **)(*(char **)(g + 0x164) + 0x688) + 0x8B0);
    _ACTWait(0);
}
extern void ACTAdjustPlane(int a0, void *p);
extern void _ACTWait(int a0);

void actBoyBHang(volatile int a0) {
    char *g = (char *)a0;
    ACTAdjustPlane(a0, *(char **)(*(char **)(g + 0x164) + 0x688) + 0x8B0);
    _ACTWait(0);
}
extern void debug_StdPrintfDummy();
extern char D_00552B90[];

void actBoyFall(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00552B90);
    *(int *)(sub + 0x34) = 5;
    while (1) {
        _ACTWait(1);
    }
}
extern char D_00552BD8[];

void actBoyCall(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00552BD8);
    *(int *)(sub + 0x34) = 9;
    _ACTWait(2);
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x41, D_0063A61C);
    }
    while (1) {
        if ((*(int *)(sub + 0x2E0) & 8) == 0) {
            ACTSendMailCorrect(a0, 0xC7);
        }
        _ACTWait(1);
    }
}
typedef struct {
    char pad000[0x470];
    float f470;                 /* 0x470 */
    float f474;
    float f478;
    char pad47C[0x480 - 0x47C];
    S12 f480;                   /* 0x480 */
} HangTarget;

#define HANG_TARGET(o) \
    ((HangTarget *)*(char **)(*(char **)((char *)(o) + 0x164) + 0x688))

void actBoyHangBefore(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    ACTAdjustPlane(a0, (char *)HANG_TARGET(a0) + 0x8C0);
    HANG_TARGET(a0)->f470 = *(float *)(sub + 0x4C0);
    HANG_TARGET(a0)->f474 = *(float *)(sub + 0x4C4);
    HANG_TARGET(a0)->f478 = *(float *)(sub + 0x4C8);
    HANG_TARGET(a0)->f480 = *(S12 *)(sub + 0x630);
    while (1) {
        ACTSendMailCorrect(a0, 0x128);
        _ACTWait(1);
    }
}
extern void *test_CURRENTORIENT(void *a0);
extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void *D_0063C200;

void actBoyBeslam(volatile int a0)
{
    char *p = *(char **)((char *)a0 + 0x15C) + 0x130;

    sceVu0ScaleVector(p, test_CURRENTORIENT(D_0063C200), 30.0f);
    while (1) {
        ACTSendMailCorrect(a0, 0x13A);
        _ACTWait(1);
    }
}
void actBoyRescueSrc(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}
void actBoySupportGBBegin(volatile int a0)
{
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x17D, D_0063A61C);
        }
        ACTSendMailCorrect(a0, 0x17B);
        _ACTWait(1);
    }
}
static inline unsigned char IsBoyStatus_SupportGB(void)
{
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34);
    if (st < 0x6B) {
        if (st >= 0x68) {
            return 1;
        }
    }
    return 0;
}

void actBoySupportGBLoop(volatile int a0)
{
    while (1) {
        if (!IsBoyStatus_SupportGB()) {
            ACTSendMailCorrect(a0, 0xE2);
        }
        _ACTWait(1);
    }
}
void actBoySupportGBEnd(volatile int a0)
{
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x17F, D_0063A61C);
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}
void actBoySupportBGBegin(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0x183);
        _ACTWait(1);
    }
}
void actBoyDitch3mExec(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0x190);
        _ACTWait(1);
    }
}
extern void afterBoyHangG3M(int x);

void actBoyHangG3M(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    *(void **)(sub + 0x18) = (void *)afterBoyHangG3M;
    while (1) {
        if (0.1f < *(float *)(sub + 0x34C) || (*(int *)(sub + 0x2E0) & 0x10)) {
            ACTSendMailCorrect(a0, 0x192);
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x195, D_0063A61C);
            }
        }
        _ACTWait(1);
    }
}
extern unsigned char D_0063C1F5;

unsigned char IsAbleBoyControl(void) {
    return D_0063C1F5;
}
extern char D_00552740[];
extern char D_00552758[];
extern void afterBoyHand50(volatile int a0);

void actBoyHand50(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00552740);
    *(int *)(sub + 0x34) = 0x52;
    *(void **)(sub + 0x14) = (void *)afterBoyHand50;
    *(int *)(sub + 0xE0) = 0;
    while ((*(int *)(sub + 0xE0) & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy(D_00552758);
    while (1) {
        ACTSendMailCorrect(a0, 0x60);
        _ACTWait(1);
    }
}
extern char D_00552730[];
extern void debug_StdPrintfDummy();

void afterBoyHand50(volatile int a0)
{
    debug_StdPrintfDummy(D_00552730);
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x60, D_0063A61C);
    }
}
extern char D_00552788[];
extern char D_005527A0[];
extern void afterBoyHand100(volatile int a0);

void actBoyHand100(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00552788);
    *(int *)(sub + 0x34) = 0x53;
    *(void **)(sub + 0x14) = (void *)afterBoyHand100;
    *(int *)(sub + 0xE0) = 0;
    while ((*(int *)(sub + 0xE0) & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy(D_005527A0);
    while (1) {
        ACTSendMailCorrect(a0, 0x65);
        _ACTWait(1);
    }
}
void afterBoyHand100(volatile int a0)
{
    debug_StdPrintfDummy(D_00552730);
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x65, D_0063A61C);
    }
}
extern char D_005527D8[];
extern void afterBoyHand200(volatile int a0);

void actBoyHand200(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_005527D8);
    *(int *)(sub + 0x34) = 0x54;
    *(void **)(sub + 0x14) = (void *)afterBoyHand200;
    *(int *)(sub + 0xE0) = 0;
    while ((*(int *)(sub + 0xE0) & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy(D_005527A0);
    while (1) {
        ACTSendMailCorrect(a0, 0x6A);
        _ACTWait(1);
    }
}
void afterBoyHand200(volatile int a0)
{
    debug_StdPrintfDummy(D_00552730);
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x6A, D_0063A61C);
    }
}
extern float _DistGV(CCPResult *a, CCPResult *b);
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *);
extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern void *test_CURRENTORIENT(void *a0);
extern CCPResult *test_CURRENTROOT(void *a0);

void ACTSearchEnemy(void *a0, int *out_id, float *out_vec) {
    float buf[4];
    void *node;
    int best;
    float thresh = 300.0f;

    node = isysGObjSearchFromObjKindID_begin((*(int *)((char *)a0 + 0xC) ^ 1) ? 1 : 4);
    *out_id = 0;
    best = 0x5A;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = test_CURRENTROOT(a0);
                if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = test_CURRENTROOT(node);
                    sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
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
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}
extern void memset(void *a0, int a1, int a2);
extern void SetDirectRootPositionNoFitting(void *w, float *pos);
extern void ReleaseWeapon(void *w);
extern int gamesysObjInfoPosSetStage(void *w, int a1, int a2, int stage);
extern int stage_no;
extern long long D_006C0AD0[];
extern int D_006C0B38[];

void DeleteBoyWeapon(void)
{
    union { float f[4]; long long ll[2]; } buf;
    char *sub;

    if (D_00639EA4 != 0) {
        sub = *(char **)((char *)D_00639EA4 + 0x164);
        if (*(void **)(sub + 0x150) != 0) {
            ReleaseWeapon(*(void **)(sub + 0x150));
            memset(&buf, 0, 0x10);
            buf.f[0] = 10000000.0f;
            SetDirectRootPositionNoFitting(*(void **)(sub + 0x150), buf.f);
            gamesysObjInfoPosSetStage(*(void **)(sub + 0x150), 0, 0, stage_no);
            *(int *)(*(char **)(sub + 0x150) + 0x16C) = 0;
        }
        D_006C0B38[0] = 0;
        ((int *)D_006C0AD0)[0] = 0;
        *(void **)(sub + 0x150) = 0;
    }
}
extern void *D_00639EA4;

int isLiftBoyEnable(void) {
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);
    if (st >= 0x60) {
        return 1;
    }
    if (st < 0x5E) {
        return 1;
    }
    return 0;
}
extern int D_006C0B30[];

void SetKidnapInfo(int a0, int a1) {
    D_006C0B30[5] = a0;
    D_006C0B30[6] = a1;
}
void GetKidnapInfo(int *a0, int *a1) {
    *a0 = D_006C0B30[5];
    *a1 = D_006C0B30[6];
}
typedef struct {
    float pos[3];           /* 0x00 */
    float unk0C;
    float tgt[3];           /* 0x10 */
    float unk1C;
    int unk20;              /* 0x20 */
    int unk24;
    int unk28;
    float unk2C;
    float unk30;
    unsigned char unk34;    /* 0x34 */
    unsigned char pad35[7];
    int on;                 /* 0x3C */
} PrivInsCam;

extern PrivInsCam D_006C0B50;

void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, float f5, float f6, unsigned char a7)
{
    D_006C0B50.pos[0] = pos[0];
    D_006C0B50.pos[1] = pos[1];
    D_006C0B50.pos[2] = pos[2];
    D_006C0B50.tgt[0] = tgt[0];
    D_006C0B50.tgt[1] = tgt[1];
    D_006C0B50.tgt[2] = tgt[2];
    D_006C0B50.unk20 = a2;
    D_006C0B50.unk24 = a3;
    D_006C0B50.unk28 = a4;
    D_006C0B50.unk2C = f5;
    D_006C0B50.unk30 = f6;
    D_006C0B50.unk34 = a7;
    D_006C0B50.on = 1;
}
extern int ACTGame_isWeaponEnableCatchfire(void *w);
extern int IsTorchLightOn(int x);
extern int ACTGame_FLAG_TETSUNAGI(void);


void BoyInfoUpdate_StageChange(void)
{
    char *g = (char *)D_00639EA4;
    char *sub = *(char **)(g + 0x164);
    char *w;
    int x;

    BOYINFO.torch = 0;
    w = *(char **)(sub + 0x150);
    if (w != 0) {
        x = ACTGame_isWeaponEnableCatchfire(w);
        if (x != 0) {
            if (IsTorchLightOn(x)) {
                BOYINFO.torch = 1;
            }
        }
    }
    BOYINFO.fire = 0;
    if (ACTGame_FLAG_TETSUNAGI()) {
        BOYINFO.fire = 1;
    }
}
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern char D_00552808[];
extern char D_0063A6D0[];

int IsBoyStatus_EnemyMustWait(void)
{
    char *sub;
    unsigned int st;

    if (D_00639EA4 == 0) {
        debug_assert(D_00552808, 5795);
        __assert(D_00552808, 5795, D_0063A6D0);
        return 0;
    }
    sub = *(char **)((char *)D_00639EA4 + 0x164);
    st = *(unsigned int *)(sub + 0x34);
    if (st >= 0x13) {
        if (st >= 0x16) {
            if (st < 0x18) {
                return 1;
            }
        } else if (*(int *)(*(char **)(sub + 0x680) + 0x29C) != 0) {
            return 1;
        }
    }
    if (st == 0x15 || 0 < *(int *)(*(char **)(sub + 0x688) + 0x37C)) {
        return 1;
    }
    return 0;
}
extern long long D_006C0AD8[];

int IsGirlEscortedInNextStage(void) {
    return (int)((unsigned char)((unsigned long long)D_006C0AD8[0] >> 35)) & 1;
}
extern unsigned char D_0063C1F4;

unsigned char IsGirlEscortedInCurrentStage(void) {
    return D_0063C1F4;
}
extern void *D_00639EA4;
extern void *D_00639EA8;
int GetSaveSofaLayoutID(void) {
    int *a = (int *)D_00639EA4;
    int *b = (int *)D_00639EA8;
    int *pa, *pb, *r;
    int v;
    if (a == 0) goto err;
    if (b == 0) goto err;
    pa = (int *)a[0x164/4];
    v = pa[0x34/4];
    if (v != 0x2D) goto err;
    pb = (int *)b[0x164/4];
    if (pb[0x34/4] != v) goto err;
    r = (int *)pa[0x160/4];
    return r[2];
err:
    return -1;
}
extern long long D_006C0AD0[];

void OnGirlEscortFlag(void) {
    D_006C0AD0[1] |= 0x800000000LL;
}
extern void PickupWeapon(void *w, void *boy, int kind);
extern void SetWeaponOffsetMode(void *w, int mode);
extern void ReleaseWeapon(void *w);
extern void PutWeapon(void);
extern int gamesysObjInfoPosSetStage(void *w, int a1, int a2, int stage);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();
extern int stage_no;
extern char D_00552808[];
extern char D_00552A38[];
extern char D_0063A6F0[];

/* boyact.c:3002-3021 in the PAL listing: a static helper with no out-of-line
   copy in ROM, inlined into SetBoyWeaponGObj and afterBoyTakeWeapon. */
static inline int SwapBoyWeapon(void *oldW, void *newW, void *boy)
{
    char *sub = *(char **)((char *)boy + 0x164);

    if (oldW == newW) {
        return 0;
    }
    if (newW == 0) {
        debug_assert(D_00552808, 3007);
        __assert(D_00552808, 3007, D_0063A6F0);
        return 0;
    }
    PickupWeapon(newW, boy, 0x16);
    ((int *)D_006C0AD0)[0] = *(int *)((char *)newW + 0x8);
    *(void **)(sub + 0x150) = newW;
    SetWeaponOffsetMode(newW, 0);

    if (oldW == 0) {
        return 1;
    }
    ReleaseWeapon(oldW);
    PutWeapon();
    gamesysObjInfoPosSetStage(oldW, 0, 0, stage_no);
    debug_StdPrintfDummy(D_00552A38, *(int *)((char *)oldW + 0x8), *(int *)((char *)newW + 0x8));
    return 1;
}

void SetBoyWeaponGObj(void *w)
{
    if (D_00639EA4 != 0 && w != 0) {
        SwapBoyWeapon(0, w, D_00639EA4);
    }
}
int IsBoyStatus_NotDanger(void) {
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);
    if (st < 0x17) {
        if (st >= 0x14) {
            return 1;
        }
    }
    return 0 < *(int *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x688) + 0x37C);
}
extern void ACTGame_StageChangeGObjDirect(void *a0, void *a1, void *a2, int a3);
extern char D_00552C10[];
extern void *D_00639EA4;
extern unsigned char D_006C0B20[];
extern int RequestStageChangeSimple(void *a0, int a1, int a2, int a3, float a4, float a5);

int RequestStageChangeKidnapEnd(void *a0, int a1) {
    char buf[0x10];
    int rv = 0;
    if (D_00639EA4 != 0) {
        rv = RequestStageChangeSimple(a0, 0, 0, 0, 0.25f, 4.0f) & 0xFF;
        if (rv != 0) {
            D_006C0B20[0] = 1;
            *(int *)(D_006C0B20 + 4) = a1;
            *(long *)buf = *(long *)D_00552C10;
            *(long *)(buf + 8) = *(long *)(D_00552C10 + 8);
            ACTGame_StageChangeGObjDirect(D_00639EA4, a0, buf, 0);
        }
    }
    return rv;
}
extern unsigned char D_006C0B20[];

int GetEfStageCameraTargetID(void)
{
    if (D_006C0B20[0]) {
        return *(int *)(D_006C0B20 + 4);
    }
    return 0;
}
int IsBackFromEfStage(void) {
    return D_006C0B20[0];
}
extern int D_006C0B8C[];
int PrivInsCamChk(void) {
    return D_006C0B8C[0] != 0;
}
extern unsigned char D_006C0B84[];

unsigned char PrivInsCamChk_Control(void) {
    return D_006C0B84[0];
}
extern int D_006C0B30[];

int *GetbufpCharacterPacket(void) {
    return D_006C0B30;
}
int GetsizeCharacterPacket(void) {
    return 32;
}
typedef struct { int w[8]; } BoyKidnapWork;

extern BoyKidnapWork D_0029C670;
extern void BoyInfoUpdate_StageChange(void);

void MakeCharacterPacket(void)
{
    char *pkt = (char *)D_006C0B30;
    char *sub;
    char *g;

    *(BoyKidnapWork *)D_006C0B30 = D_0029C670;
    if (D_00639EA4 != 0) {
        sub = *(char **)((char *)D_00639EA4 + 0x164);
        if (*(char **)(sub + 0x150) != 0) {
            *(int *)(pkt + 0x8) = *(int *)(*(char **)(sub + 0x150) + 0x8);
        }
        if (*(char **)(sub + 0x154) != 0) {
            *(int *)(pkt + 0xC) = *(int *)(*(char **)(sub + 0x154) + 0x8);
        }
        if (*(int *)(sub + 0x34) == 0x2D) {
            *(int *)(pkt + 0x10) = *(int *)(*(char **)(sub + 0x160) + 0x8);
        }
        g = (char *)D_00639EA8;
        if (g != 0 && *(int *)(*(char **)(g + 0x164) + 0x34) == 0x2D) {
            *(int *)(pkt + 0x1C) |= 1;
        }
        BoyInfoUpdate_StageChange();
        *(int *)(pkt + 0x1C) = (*(int *)(pkt + 0x1C) & ~0x10000)
            | (((int)((unsigned char)((unsigned long long)D_006C0AD0[1] >> 34)) & 1) << 16);
        *(unsigned char *)(pkt + 0x1D) =
            (int)((unsigned char)((unsigned long long)D_006C0AD0[1] >> 33)) & 1;
        *(CharPos *)pkt = BOYINFO.f50;
    }
}
typedef struct {
    CharPos pos;            /* 0x00 */
    int boyID;              /* 0x08 */
    int girlID;             /* 0x0C */
    int f10;                /* 0x10 */
    int f14;
    int f18;
    unsigned int b1C : 8;   /* 0x1C */
    unsigned int b1D : 8;
    unsigned int h1E : 16;  /* 0x1E */
} CharacterPacket;

void ReadCharacterPacket(void)
{
    CharacterPacket *p = (CharacterPacket *)D_006C0B30;

    BOYINFO.boyID = p->boyID;
    BOYINFO.girlID = p->girlID;
    BOYINFO.pad0 = p->f10;
    BOYINFO.bit32 = p->b1C;
    BOYINFO.fire = p->b1D;
    BOYINFO.torch = p->h1E;
    BOYINFO.f50 = p->pos;
}
void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh) {
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjKindID_begin(a1);
    *out_id = 0;
    best = a2;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = test_CURRENTROOT(a0);
                if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = test_CURRENTROOT(node);
                    sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
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
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}
extern S12 InitialColInfo;
extern char D_0063A700[];
extern void RequestChangeHandMode(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);
extern void debug_StdPrintfDummy(void *msg);

void afterBoySwim(volatile int a0) {
    RequestChangeHandMode((void *)a0, 0, 3, 0, 0, 0, 0);
    *(S12 *)((char *)GOBJ_SUB(a0) + 0x1C0) = InitialColInfo;
    debug_StdPrintfDummy(D_0063A700);
}
extern void ACTSendMailCorrect(int a0, int mail);
extern void _ACTWait(int a0);

void actBoyJump(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0xBD);
        _ACTWait(1);
    }
}
void afterBoyTakeWeapon(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    SwapBoyWeapon(BOYINFO.weapon, BOYINFO.nextWeapon, (void *)a0);
    *(void **)(sub + 0x150) = BOYINFO.nextWeapon;
}
void afterBoyHangG3M(int x) {
    volatile int local = x;
}
extern void ACTGame_DisconnectHand(void);

void afterBoyRescueGirlBhang(volatile int a0) {
    ACTGame_DisconnectHand();
}
extern void _ACTWait();

void subBoyBrainMain(int a0)
{
    volatile int local = a0;
    while (1) {
        _ACTWait(1);
    }
}
void SetBoyInfo(int *a0, int *a1) {
    int n;
    int i;
    if (a0 != 0) {
        ((int *)D_006C0AD0)[0] = a0[2];
    } else {
        ((int *)D_006C0AD0)[0] = 0;
    }
    i = 0;
    n = 1;
    if (a1 != i) {
        ((int *)D_006C0AD0)[n] = a1[2];
    } else {
        ((int *)D_006C0AD0)[n] = i;
    }
}
extern void GetRootPosition(void *out, void *gobj);
extern float _DistSqGV(void *a, void *b);

void GetBoyRootPositionForCamera(float *out)
{
    float buf[4];
    char *g = (char *)D_00639EA4;
    char *sub;

    sub = *(char **)(g + 0x164);
    GetRootPosition(buf, g);
    if (_DistSqGV(buf, sub + 0x110) < 40000.0f) {
        out[0] = *(float *)(sub + 0x110);
        out[1] = *(float *)(sub + 0x114);
        out[2] = *(float *)(sub + 0x118);
    } else {
        GetRootPosition(sub + 0x110, g);
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}
typedef struct { long long w[12]; } BoyWork;

extern BoyWork D_0029C610;

void Boy_Init(void)
{
    *(BoyWork *)D_006C0AD0 = D_0029C610;
    *(BoyKidnapWork *)D_006C0B30 = D_0029C670;
}
