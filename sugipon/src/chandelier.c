#include "common.h"
#include "ico/types.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/chandelier", ChandelierGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/chandelier", ChandelierDL);

extern int func_0010F068(int a0);
extern int file_LoadCDFile(int a0);

void InitChandelierGeo(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

int func_001C0728(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/chandelier", func_001C0730);

extern int func_0023D3C0(int a, int b, int c, int d, int e, int f, int g);
extern void actClipCollisionCore(void);
extern int D_0062B564;

int func_001C0950(void) {
    int v = func_0023D3C0(0, 0, 0, 0, (int)&actClipCollisionCore, 0, 0);
    D_0062B564 = v;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/chandelier", func_001C0990);
