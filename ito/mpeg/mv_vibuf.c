#include "common.h"

extern void func_0025A4A8(int a0);

void func_00259480(int *a0) {
    func_0025A4A8(a0[0]);
    func_0025A4A8(a0[1]);
    func_0025A4A8(a0[20]);
}
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
    iosFree(a0 & 0x0FFFFFFF);
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
