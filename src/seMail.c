#include "common.h"

extern char D_00621D40[];
extern void debug_StdPrintfDummy();

INCLUDE_ASM("asm/nonmatchings/src/seMail", setMailTarget);
INCLUDE_ASM("asm/nonmatchings/src/seMail", seMail);
INCLUDE_ASM("asm/nonmatchings/src/seMail", seMailTargetDistCheck);
