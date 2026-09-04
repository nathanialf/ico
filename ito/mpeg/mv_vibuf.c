#include "common.h"

#include "mv_defs.h"

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_00259480);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufCreate);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufReset);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufBeginPut);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufEndPut);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufAddDMA);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufStopDMA);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufRestartDMA);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufFlush);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufModifyPts);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufGetTs);
extern void iosFree();

void func_0025A4A8(int a0)
{
    iosFree(phys_addr(a0));
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufDelete);
extern void SignalSema();
extern void WaitSema();

int viBufCount(int *self)
{
    int ret;
    WaitSema(self[0x40 / 4]);
    ret = (self[0x10 / 4] << 11) + self[0x14 / 4];
    SignalSema(self[0x40 / 4]);
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufPutTs);
