#include "common.h"



extern char *D_006321DC;
extern int isysGObjProcPausePtr();
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
INCLUDE_ASM("asm/nonmatchings/src/act", actChangeActBrain);

INCLUDE_ASM("asm/nonmatchings/src/act", actChangeActMain);

INCLUDE_ASM("asm/nonmatchings/src/act", actCreateMotionThread);

INCLUDE_ASM("asm/nonmatchings/src/act", after_func_exec);

INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize_ext_charcter);

INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize);

INCLUDE_ASM("asm/nonmatchings/src/act", act_check_intr_list);

INCLUDE_ASM("asm/nonmatchings/src/act", act_check_mail);

INCLUDE_ASM("asm/nonmatchings/src/act", BeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/act", ACTDebugMove);

void actInitialize_geo(void) {}

INCLUDE_ASM("asm/nonmatchings/src/act", actInitialize_only_charcter);

int ACTReserveTarget(int *self, int a1, int a2)
{
    int *p = (int *)self[0x164 / 4];
    if (p[0x12C / 4] != 0)
        goto ret0;
    p[0x12C / 4] = (int)self;
    p[0x130 / 4] = a2;
    iosOmBeforeFuncStandard(self, a2, a1);
    return 1;
ret0:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act", _ACTRun);

INCLUDE_ASM("asm/nonmatchings/src/act", _ACTWait);

void actCreateSubThreadGOppArg(int a0, int a1)
{
    *(int *)((char *)isysGObjProcPausePtr(D_006321DC, a0, 0, a1) + 0x64) = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/act", actCreateSubThread);

void actSetInterrupt(char *self, int val) {
    *(int *)(self + 0x0) = val;
}

