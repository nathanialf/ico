#include "common.h"











extern int ACTGameCollisionOn();
extern int *D_00631AE4;
extern int checkHit(char *self);
extern float D_0063379C;
extern int D_006337A0;
extern int D_00633798;
extern void ACTGame_BeforeFunc();
extern void func_0014A2C8(char *a0);
extern long long D_0055A1B0[];
extern void GetCylinderCollisionWithExceptOwnCollision();
extern void stgmgrForceSwitch();
extern int D_00631AF0;
extern int D_00633D40;
extern void _ACTWait();
extern int ExecMotionOrient();
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
extern char D_002A4C48[];
extern int isysGObjAddHead();
extern int isysGObjSearchFromObjKindID_begin();
extern int isysGObjSearchFromObjLayoutID();
extern void Generator_Mask(char *self);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenAppear);

void actSt25aQueenAppearChk(void)
{
    int *p = isysGObjSearchFromObjLayoutID(0x21);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_begin(p);
    }
}

void actConte11(void)
{
  char *new_var;
  int *p = isysGObjAddHead();
  if (p != 0)
  {
    iosOmBeforeFuncStandard((int) p, 0x26, (int) p);
    new_var = (char *) D_002A4C48;
    *((unsigned short *) ((new_var + (p[0x8 / 4] * 0x4C)) + 0x42)) = 0;
  }
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenTalkChk);

INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12);

INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12Jimaku);

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDeadChk);

INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte13Jimaku);

void BoySekikaTexScroll(int a0, int a1)
{
    int s0 = *(int *)(a0 + 0x164);
    *(int *)(s0 + 0x120) = ExecMotionOrient(a0, a1, s0 + 0x610);
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aGenerator);

void actSt25aQueenBefore(int *self) {
    int *p = (int *)self[0x164/4];
    while ((((int *)p[0x120/4])[0x5C/4] & 1) == 0) {
        _ACTWait(1);
    }
}

void actSt25aQueenTalk(void) {
    D_00633D40 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDead);

INCLUDE_ASM("asm/nonmatchings/src/st25a", actItouQueenAttack);

int actSwordEff(int a0, int a1, int a2, int a3)
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

void actSwordEffXL(int *self)
{
    long long buf[2];
    ACTGame_BeforeFunc((int)self);
    func_0014A2C8((int)self);
    buf[0] = D_0055A1B0[0];
    buf[1] = D_0055A1B0[1];
    GetCylinderCollisionWithExceptOwnCollision(self, (int *)buf);
    iosOmBeforeFuncStandard((int)self, 0x27, (int)self);
}

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenBeforeChk);

void actConte11Jimaku(float f) {
    D_00633798 = 1;
    D_006337A0 = 0;
    D_0063379C = -f;
}

int actSt25aQueenDeadEvent(void)
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

INCLUDE_ASM("asm/nonmatchings/src/st25a", func_0017E5E0);

int func_0017E600(void) {
    return ACTGameCollisionOn() != 0;
}

int func_0017E620(int a0, int b)
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

INCLUDE_ASM("asm/nonmatchings/src/st25a", func_0017E660);

INCLUDE_ASM("asm/nonmatchings/src/st25a", func_0017E780);

INCLUDE_ASM("asm/nonmatchings/src/st25a", func_0017E838);

INCLUDE_ASM("asm/nonmatchings/src/st25a", func_0017E870);

