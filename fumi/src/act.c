#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actChangeActBrain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actChangeActMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actCreateMotionThread);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", after_func_exec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize_ext_charcter);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", act_check_intr_list);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", act_check_mail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", BeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", ACTDebugMove);

void actInitialize_geo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actInitialize_only_charcter);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", ACTReserveTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", _ACTRun);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", _ACTWait);

extern void *D_0062A4DC;
extern void *isysGObjProcPausePtr(void *a0, void *a1, int a2, void *a3);

void actCreateSubThreadGOppArg(void *a0, void *a1) {
    void *p = isysGObjProcPausePtr(D_0062A4DC, a0, 0, a1);
    *(int *)((char *)p + 0x64) = 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act", actCreateSubThread);

void actSetInterrupt(int *a0, int a1) {
    *a0 = a1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4C;  /* 0x4C */
} S_00557188;  /* stride 0x50 */

/* end struct shapes */
