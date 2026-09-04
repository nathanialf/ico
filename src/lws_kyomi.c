#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", CreateKyomiGObj);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", LwsKyomiGeo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", MakeHintSaveInfo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", ReadHintSaveInfo);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", SetParamKyomiGObj);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", FinishHint);
INCLUDE_ASM("asm/nonmatchings/src/lws_kyomi", SleepHint);
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
