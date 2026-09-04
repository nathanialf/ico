#include "common.h"

/* st25a 0x164 actor-state view (local) */
typedef struct { char _0[0x100]; int f_100, f_104, f_108; char _pad10c[0x21C]; int f_328, f_32C; char _pad330[0xC]; int f_33C; } St25State;

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenAppear);

extern int *isysGObjSearchFromObjLayoutID(int x);
extern void Generator_Mask(int *p);
extern int *isysGObjSearchFromObjKindID_next(int *p);

void scpMaskGeneratorAll(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x21);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

extern int *isysGObjAddHead(void);
extern void iosOmSendMail(int a, int b, int c);
extern unsigned char D_002A0A90[];

void actConte11(void)
{
  char *new_var;
  int *p = isysGObjAddHead();
  if (p != 0)
  {
    iosOmSendMail((int) p, 0x26, (int) p);
    new_var = (char *) D_002A0A90;
    *((unsigned short *) ((new_var + (p[0x8 / 4] * 0x4C)) + 0x42)) = 0;
  }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenTalkChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte12);

void actConte12Jimaku(void *a0) {
    St25State *p = *(St25State **)((char *)a0 + 0x164);
    p->f_33C = 0;
    p->f_100 = 0;
    p->f_104 = 0;
    p->f_108 = 0;
    p->f_32C = 0x7F;
    p->f_328 = 0x7F;
}


int actSt25aQueenDeadChk(void) {
    return isysGObjAddHead();
}

extern void memset(void *a0, int a1, int a2);
extern void GetHeightOfFieldPlaneDifference(void *a0, void *a1, int a2, int a3, void *a4, float f12, float f13, float f14, float f15);
extern void gflagOff(void *a0, int a1);

void scpPlayMotNode(void *a0, int a1, void *a2, int a3) {
    float buf[4];
    memset(buf, 0, 0x10);
    buf[3] = 1.0f;
    GetHeightOfFieldPlaneDifference(a0, a2, 0, a3, buf, 0.0f, 0.0f, 0.0f, 1.0f);
    gflagOff(a0, a1);
}

extern int ExecMotionOrient(void *a0, int a1, void *a2);

void BoySekikaTexScroll(void *a0, int a1) {
    char *p = *(char **)((char *)a0 + 0x164);
    *(int *)(p + 0x110) = ExecMotionOrient(a0, a1, p + 0x610);
}

extern void memset(void *a0, int a1, int a2);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);
extern void InitMotionRotElem(void *a0);

void scpPlayPosSet(void *a0, float f12, float f13, float f14) {
    float buf[4];
    memset(buf, 0, 0x10);
    buf[0] = f12;
    buf[1] = f13;
    buf[2] = f14;
    GetCylinderCollisionWithExceptOwnCollision(a0, buf);
    InitMotionRotElem(a0);
}

extern void _ACTWait(int a0);

void actSt25aQueenBefore(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    while ((*(int *)(*(char **)(p + 0x110) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
}

extern int D_0062C030;

void actSt25aQueenTalk(void) {
    D_0062C030 = 0;
}

extern int actItouQueenAttack(int a0, int a1, int a2, int a3, int a4, int a5);
int RequestStageChange(int a0, int a1, int a2) {
    return actItouQueenAttack(a0, a1, a2, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actItouQueenAttack);

extern int D_00629DF0;
extern void stgmgrForceSwitch(int a0, int a1, int a2, int a3);

int RequestStageChangeSimple(int a0, int a1, int a2, int a3)
{
    int ret = 0;
    a1 = a1 & 0xFF;
    a2 = a2 & 0xFF;
    a3 = a3 & 0xFF;
    if (D_00629DF0 == 0) {
        if (D_0062C030 == 0) {
            stgmgrForceSwitch(a0, a1, a2, a3);
            D_0062C030 = 1;
            ret = 1;
        }
    }
    return ret;
}

extern void ACTGame_StageChangeGObjDirect(void *a0);
extern void ACTGame_CommonLoop(void *a0);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);

typedef struct { long long _0; long long _8; } SwordEffParam;
extern SwordEffParam D_00554440;

void RequestStageChangeDirect(void *a0) {
    SwordEffParam tmp;
    ACTGame_StageChangeGObjDirect(a0);
    ACTGame_CommonLoop(a0);
    tmp = D_00554440;
    GetCylinderCollisionWithExceptOwnCollision(a0, &tmp);
    iosOmSendMail((int)a0, 0x27, (int)a0);
}

extern float D_0062BA7C;
extern int D_0062BA80, D_0062BA78;
extern unsigned char D_0062BA88, D_0062BA89, D_0062BA8A;

void scpFadeOut(float a0, int a1, int a2, int a3) {
    D_0062BA78 = 1;
    D_0062BA7C = a0;
    D_0062BA80 = 1;
    D_0062BA88 = a1;
    D_0062BA89 = a2;
    D_0062BA8A = a3;
}

extern int D_0062BA78;
extern int D_0062BA80;

void scpFadeIn(float a0) {
    D_0062BA78 = 1;
    D_0062BA7C = -a0;
    D_0062BA80 = 0;
}

int scpFadeChk(void) {
    int g = D_0062BA78;
    if (g == 0) {
        goto ret0;
    }
    if (g != 3) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

extern int *D_00629DE4;
extern int checkHit(int a0);

int actItouQueenAttackChk(void) {
    int *p = (int *)D_00629DE4[0x59];
    int v = p[0x4C];
    if (v == 0) {
        return 0;
    }
    return checkHit(v);
}

extern int func_001BDF80(void);

int func_0017BCC0(void) {
    return func_001BDF80();
}

extern int ACTGameCollisionOn(void);

int func_0017BCE0(void) {
    return ACTGameCollisionOn() != 0;
}

int scpIsHangChainOptional(int a0, int a1) {
    int p = ACTGameCollisionOn();
    int ret = 0;
    if (p) ret = (*(int *)(p + 8) ^ a1) == 0;
    return ret;
}

extern float _GetRandom(void);
extern int rand(void);
extern int IsActCharDead(void *p);
extern void func_001B8470(int a0);
extern void _ACTWait(int a0);
extern float D_00629164;
struct DQW { float f0, f4, f8, fc, f10, f14; char _18[0x18]; int f30; };
extern struct DQW D_002869B0;

void scpBornSpider(int n, float a, float b, float c, float d) {
    int i;
    float t1, t2;
    int r, dead;
    for (i = 0; i < n; i++) {
        t1 = _GetRandom();
        D_002869B0.f4 = b;
        D_002869B0.f0 = a + d * (t1 + t1 - 1.0f);
        t2 = _GetRandom();
        D_002869B0.f8 = c + d * (t2 + t2 - 1.0f);
        r = rand();
        D_002869B0.f30 = 1;
        D_002869B0.f14 = (float)((r >> 4) & 0xFFFF) * D_00629164 * 3.0517578125e-05f;
        dead = IsActCharDead(&D_002869B0);
        _ACTWait(1);
        func_001B8470(dead);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BE60);

extern void MatrixDrive_TurnObjectMatrix(void *a0, float *a1);

void func_0017BF18(char *a0, float x, float y, float z) {
    float v[4] = {x, y, z, 0};
    int p = *(int *)(a0 + 0x15C);
    MatrixDrive_TurnObjectMatrix((void *)(p + 0x660), v);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", scpWakeupItemWithBoundary);
