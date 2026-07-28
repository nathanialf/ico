#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/candle", InitCandleGeo);

int CandleDL(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/candle", CandleGeo);

extern int file_LoadCDFile(int a0);
extern int func_0010ECD8(int a0);

void DeleteLayoutedCandleParticleEffect(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010ECD8(a0);
        return file_LoadCDFile((int)s0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/candle", _deleteLayoutedCandleParticleEffect);

INCLUDE_ASM("asm/nonmatchings/src/candle", func_001C3270);

