#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/candle", InitCandleGeo);
INCLUDE_ASM("asm/nonmatchings/src/candle", CandleGeo);
extern int p2o_DispVU1DObjMulti(int a0);
extern int p2o_SetDefaultEnviroment(int a0);

void CandleDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/candle", DeleteLayoutedCandleParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/candle", _deleteLayoutedCandleParticleEffect);
