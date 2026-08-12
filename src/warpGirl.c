#include "common.h"

extern void _ACTWait(int a0);





extern void Generator_Mask(char *self);
extern int *D_00631AE4;
extern float D_006CF940[];
extern int func_001BC870();
int warpGirlOutStage(void) {
    return func_001BC870() != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlInStage);

void warpGirlInit(float *dst)
{
    dst[0] = D_006CF940[0];
    dst[1] = D_006CF940[1];
    dst[2] = D_006CF940[2];
}

void func_0017E9D8(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) &= ~0x1000LL;
    }
}

void func_0017EA00(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) |= 0x1000LL;
    }
}

void func_0017EA28(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) &= ~0x2000LL;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EA50);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EAD0);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EB50);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EBD0);

void func_0017EC50(void *a0, float f)
{
  long * volatile *pp = (long * volatile *) (((char *) a0) + 0x164);
  int new_var;
  long *p = *pp;
  char *new_var2;
  new_var2 = ((char *) p) + 0x20;
  new_var = 0x678;
  *((long *) new_var2) = (*((long *) new_var2)) | 0x100000;
 do { } while (0);
  {
    int **q = (int **) (*pp);
    int *r = *((int **) (((char *) q) + new_var));
    *((float *) (((char *) r) + 0x340)) = f;
  }
}

void func_0017EC78(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(long long *)(sub + 0x20) &= ~0x100000LL;
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EC98);

typedef struct WgSub_ed70 {
    char pad[0xC0];
    int unkC0;
    char pad2[0x450 - 0xC4];
    int unk450;
} WgSub_ed70;


void func_0017ED70(volatile int a0) {
    WgSub_ed70 *s = *(WgSub_ed70 **)(a0 + 0x164);
    s->unkC0 = s->unk450;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EDA0);
ASM_LIT4_SLOT(D_00630E7C, 3834.0f);
ASM_LIT4_SLOT(D_00630E80, 0.8f);
ASM_LIT4_SLOT(D_00630E84, 0.45f);
ASM_LIT4_SLOT(D_00630E88, 3834.0f);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EF30);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017F028);
ASM_LIT4_SLOT(D_00630E8C, 0.99f);
ASM_LIT4_SLOT(D_00630E90, 0.1f);
ASM_LIT4_SLOT(D_00630E94, 0.8f);
ASM_LIT4_SLOT(D_00630E98, 0.45f);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017F2E8);
ASM_LIT4_SLOT(D_00630E9C, 625.0f);
ASM_LIT4_SLOT(D_00630EA0, 1650.0f);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017F810);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017FCF8);
ASM_LIT4_SLOT(D_00630EA4, 4200.0f);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017FF40);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_001803A8);
ASM_LIT4_SLOT(D_00630EA8, 3100.0f);

extern char D_0055A380[];
extern void func_0012FFF0(void *a0, float f12, float f13, float f14, float f15,
                          float f16, float f17, int a1);

void func_00180550(void) {
    func_0012FFF0(D_0055A380, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}

void func_00180580(volatile unsigned int a0)
{
    volatile int local;
    Generator_Mask(a0);
}

typedef struct GObjC4 { char pad[0xC4]; int *unkC4; } GObjC4;

extern int actInitialize(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_0017B230(int a0);
extern void func_001F0DA8(void);
extern int D_0028A7D0[];
extern void func_00180898(volatile int a0);

void func_001805A8(volatile int a0) {
    int x = a0;
    GObjC4 *gobj = (GObjC4 *)actInitialize(a0);
    _ACTWait(1);
    func_001F0DA8();
    if (func_0017B230(0x12D) == 0) {
        D_0028A7D0[1] = (int)func_00180898;
        gobj->unkC4 = D_0028A7D0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern void func_00192040(void);
extern void *actSt25aQueenDeadChk(int a0);
extern int D_0028A810[];
extern void func_0017F2E8(volatile int a0);

typedef struct QueenObj { char pad[0x16C]; void *unk16C; } QueenObj;

void func_00180628(volatile int a0) {
    int x = a0;
    GObjC4 *gobj = (GObjC4 *)actInitialize(a0);
    _ACTWait(1);
    func_00192040();
    if (func_0017B230(0x12F) == 0) {
        QueenObj *queen = (QueenObj *)actSt25aQueenDeadChk(0x7B7);
        queen->unk16C = 0;
        D_0028A810[1] = (int)func_0017F2E8;
        gobj->unkC4 = D_0028A810;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_0028A830[];
extern void func_00180A78(volatile int a0);

void func_001806B8(volatile int a0) {
    int x = a0;
    GObjC4 *gobj = (GObjC4 *)actInitialize(a0);
    _ACTWait(1);
    D_0028A830[1] = (int)func_00180A78;
    gobj->unkC4 = D_0028A830;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_0028A850[];
extern void func_0017FF40(volatile int a0);

void func_00180720(volatile int a0) {
    int x = a0;
    GObjC4 *gobj = (GObjC4 *)actInitialize(a0);
    _ACTWait(1);
    D_0028A850[1] = (int)func_0017FF40;
    gobj->unkC4 = D_0028A850;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_0028A870[];
extern void AttackMail(volatile int a0);

void func_00180788(volatile int a0) {
    int x = a0;
    GObjC4 *gobj = (GObjC4 *)actInitialize(a0);
    _ACTWait(1);
    D_0028A870[1] = (int)AttackMail;
    gobj->unkC4 = D_0028A870;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int actInitialize(int a0);
extern void scpTorchLightOn(int a0, int a1);

void func_001807F0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpTorchLightOn(0x786, 0x1A7);
}

extern int actItouQueenAttackChk(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00180830(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (actItouQueenAttackChk() == 5) {
        scpTorchLightOn(0x786, 0x1A7);
    } else {
        stage_KillPlayBgAnimation(0x1A7, -1, -2);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180898);

