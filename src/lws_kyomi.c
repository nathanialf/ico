#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", CreateKyomiGObj);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", LwsKyomiGeo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", MakeHintSaveInfo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", ReadHintSaveInfo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", SetParamKyomiGObj);
struct HintInfo {
    char _0[0xC];
    int  flags;
};
extern struct HintInfo D_002ADBA0[];

void FinishHint(int no)
{
    (D_002ADBA0 + no)->flags |= 1;
}

void SleepHint(int no)
{
    (D_002ADBA0 + no)->flags |= 2;
}
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", WakeupHint);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", IsTopHint);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", DebugHintStart);
int GetSizeHintSaveInfo(void) {
    return 0x78;
}
extern char D_006E99B0[];
char *GetBuffHintSaveInfo(void) {
    return D_006E99B0;
}
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", Hint_Init);
