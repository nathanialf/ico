#include "common.h"











extern int ACTGameCollisionOn();
extern int *D_00631AE4;
extern int checkHit(char *self);
extern float D_0063379C;
extern int D_006337A0;
extern int D_00633798;
extern void ACTGame_StageChangeGObjDirect();
extern void ACTGame_CommonLoop(char *a0);
extern long long D_0055A1B0[];
extern void SetDirectRootPosition();
extern void stgmgrForceSwitch();
extern int D_00631AF0;
extern int D_00633D40;
extern void _ACTWait();
extern int ExecMotionOrient();
extern int iosOmSendMail(char *self_arg, int val5, int val6);
extern char D_002A4C48[];
extern int isysGObjAddHead();
extern int isysGObjSearchFromObjKindID_next();
extern int isysGObjSearchFromObjLayoutID();
extern void Generator_Mask(char *self);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenAppear);

void scpMaskGeneratorAll(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x21);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

void scpKillEnemyOne(void)
{
  char *new_var;
  int *p = isysGObjAddHead();
  if (p != 0)
  {
    iosOmSendMail((int) p, 0x26, (int) p);
    new_var = (char *) D_002A4C48;
    *((unsigned short *) ((new_var + (p[0x8 / 4] * 0x4C)) + 0x42)) = 0;
  }
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenTalkChk);

INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12);

typedef struct { char _0[0x110]; int f_110, f_114, f_118; char _pad11c[0x20C]; int f_328, f_32C; char _pad330[0xC]; int f_33C; } St25State;

void actConte12Jimaku(void *a0) {
    St25State *p = *(St25State **)((char *)a0 + 0x164);
    p->f_33C = 0;
    p->f_110 = 0;
    p->f_114 = 0;
    p->f_118 = 0;
    p->f_32C = 0x7F;
    p->f_328 = 0x7F;
}

int actSt25aQueenDeadChk(void) {
    return isysGObjAddHead();
}

extern void GetHeightOfFieldPlaneDifference(void *a0, void *a1, int a2, int a3, void *a4, float f12, float f13, float f14, float f15);
extern void memset(void *a0, int a1, int a2);
extern void gflagOff(void *a0, int a1);

void scpPlayMotNode(void *a0, int a1, void *a2, int a3) {
    float buf[4];
    memset(buf, 0, 0x10);
    buf[3] = 1.0f;
    GetHeightOfFieldPlaneDifference(a0, a2, 0, a3, buf, 0.0f, 0.0f, 0.0f, 1.0f);
    gflagOff(a0, a1);
}

void BoySekikaTexScroll(int a0, int a1)
{
    int s0 = *(int *)(a0 + 0x164);
    *(int *)(s0 + 0x120) = ExecMotionOrient(a0, a1, s0 + 0x610);
}

extern void InitMotionRotElem(void *a0);

void scpPlayPosSet(void *a0, float f12, float f13, float f14) {
    float buf[4];
    memset(buf, 0, 0x10);
    buf[0] = f12;
    buf[1] = f13;
    buf[2] = f14;
    SetDirectRootPosition(a0, buf);
    InitMotionRotElem(a0);
}

void actSt25aQueenBefore(int *self) {
    int *p = (int *)self[0x164/4];
    while ((((int *)p[0x120/4])[0x5C/4] & 1) == 0) {
        _ACTWait(1);
    }
}

void actSt25aQueenTalk(void) {
    D_00633D40 = 0;
}

extern int actItouQueenAttack(int a0, int a1, int a2, int a3, int a4, int a5);

int RequestStageChange(int a0, int a1, int a2) {
    return actItouQueenAttack(a0, a1, a2, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", actItouQueenAttack);

int RequestStageChangeSimple(int a0, int a1, int a2, int a3)
{
    int ret = 0;
    a1 = a1 & 0xFF;
    a2 = a2 & 0xFF;
    a3 = a3 & 0xFF;
    if (D_00631AF0 == 0) {
        if (D_00633D40 == 0) {
            stgmgrForceSwitch(a0, a1, a2, a3);
            D_00633D40 = 1;
            ret = 1;
        }
    }
    return ret;
}

void RequestStageChangeDirect(int *self)
{
    long long buf[2];
    ACTGame_StageChangeGObjDirect((int)self);
    ACTGame_CommonLoop((int)self);
    buf[0] = D_0055A1B0[0];
    buf[1] = D_0055A1B0[1];
    SetDirectRootPosition(self, (int *)buf);
    iosOmSendMail((int)self, 0x27, (int)self);
}

extern unsigned char D_006337A8;
extern unsigned char D_006337A9;
extern unsigned char D_006337AA;

void scpFadeOut(float a0, int a1, int a2, int a3) {
    D_00633798 = 1;
    D_0063379C = a0;
    D_006337A0 = 1;
    D_006337A8 = a1;
    D_006337A9 = a2;
    D_006337AA = a3;
}

void scpFadeIn(float f) {
    D_00633798 = 1;
    D_006337A0 = 0;
    D_0063379C = -f;
}

int scpFadeChk(void)
{
  int v = D_00633798;
  if (v == 0)
  {
    return 0;
  }
  if (v == 3)
  {
    v = 0;
    return v;
  }
  return 1;
}

int actItouQueenAttackChk(void)
{
    int *v0 = D_00631AE4;
    int *v1 = (int *)v0[0x164 / 4];
    int a = v1[0x140 / 4];
    if (a == 0) {
        return 0;
    }
    return checkHit(a);
}

extern int func_001C0BF8(void);

int func_0017E5E0(void)
{
    return func_001C0BF8();
}

int func_0017E600(void) {
    return ACTGameCollisionOn() != 0;
}

int scpIsHangChainOptional(int a0, int b)
{
    register int *p;  /* v1 */
    register int b_save;  /* s0 */
    register unsigned int v;  /* v0 */
    b_save = b;
    p = ACTGameCollisionOn(a0);
    v = 0;
    if (p == 0) goto out;
    v = (unsigned int)(p[0x8/4] ^ b_save) < 1;
out:
    return (int)v;
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", scpBornSpider);

INCLUDE_ASM("asm/nonmatchings/src/st25a", func_0017E780);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

typedef union { float f[4]; int i[4]; } Vec4u;

void scpSetStreamMotionRootOffset(int a0, float x, float y, float z)
{
    Vec4u v;
    v.f[0] = x;
    v.f[1] = y;
    v.f[2] = z;
    v.i[3] = 0;
    MatrixDrive_TurnObjectMatrix(*(int *)(a0 + 0x15C) + 0x670, &v);
}


INCLUDE_ASM("asm/nonmatchings/src/st25a", scpWakeupItemWithBoundary);

