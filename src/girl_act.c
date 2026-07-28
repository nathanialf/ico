#include "common.h"






extern int D_0028829C;
extern void *D_00631AE8;
extern int *D_00631AE4;
extern int D_006ABDE0[100];
extern void func_0014B330(char *self, unsigned int a1, float v);
extern int D_0028A890[];
extern void brainLevelProcess();
extern void ACTLookTargetSystem_Exec(void);
extern int D_00559430[];
extern void debug_assertMessage();
INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetEyeDirection);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", funcGirlHandDisconnect);

void GirlBrainClearTarget(void) {
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_00559430);
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_DecideMode);

void func_0016AC10(void)
{
    brainLevelProcess(D_0028A890);
}

void subGirlBrainMain(int *self) {
    int v = ((int *)self[0x164/4])[0x30/4];
    if (v == 10) {
        func_0014B330(self, 5, 1.5f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Pulledup);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", ATGoalTurnMail);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Attract);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", WayTest);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlControl);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlCollision);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetBoyMode);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016D330);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledReady);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledGo);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016E910);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlDitch3mReady);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlReadyMove);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRescueDst);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016F2A8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportBGBegin);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlStart);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GirlAct_BoyAndMeCollisionMail);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", IsGirlStatusEscortEnable);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", DebugDispAutoEscort);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170950);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", ACTGame_GirlBeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170ED8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBBegin);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001718F0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBLoop);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBEnd);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHangG3M);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00173060);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlDitch3mExec);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlStand);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlWalk);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRun);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHang);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBHang);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlAttack);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBecall);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBehanged);

void func_001752D0(int *self)
{
    int *p;
    p = (int *)self[0x59];
    D_006ABDE0[0] = 0;
    D_006ABDE0[1] = 0;
    if (p[0xC] != 0x45) {
        *(long long *)((char *)p + 0x20) &= ~0x200LL;
    }
}

int func_00175308(void)
{
    extern unsigned int D_0028829C_far[] __asm__("D_0028829C");
    int *a, *b, *sub, *sub2, *p;
    b = D_00631AE8;
    if (D_0028829C_far[0] != 7) goto ret0;
    a = D_00631AE4;
    sub = (int *)a[0x164 / 4];
    if (sub[0x30 / 4] != 0x4B) goto ret0;
    sub2 = (int *)b[0x164 / 4];
    p = (int *)sub2[0x678 / 4];
    return p[0x374 / 4];
ret0:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00175350);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", afterGirlHand);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", afterGirlPulledGo);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlJump);

