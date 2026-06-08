#include "common.h"
#include "ico/types.h"

extern int func_0010F068(int a0);
extern int file_LoadCDFile(int a0);

void InitCandleGeo(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

int CandleDL(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/candle", CandleGeo);

void DeleteLayoutedCandleParticleEffect(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/candle", _deleteLayoutedCandleParticleEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/candle", func_001C04E0);
