#include "typedef.h"
#include "debug.h"
#include "memory.h"
#include "gobj.h"
#include "matrixDrive.h"
#include "particleEffect.h"
#include "quaternion.h"
#include "DisplayP2O.h"

typedef struct CandleFlame { /* field names derived */
    int effect;              /* 0x0 */
    int off;                 /* 0x4 */
} CandleFlame;               /* derived name */

#include "candle.h"
#include "ios.h"
#include "include_asm.h"

int InitCandleGeo(void *self, void *mtx)
{
    Sub15C *w = GOBJ_SUB(self);
    CandleFlame *flame;
    int i;

    if (w->nodeNum >= 2) {
        flame = (CandleFlame *)iosMallocDebug(ios_partition_sugipon, w->nodeNum * 8, "src/candle.c",
                                              24);
        for (i = 0; i < w->nodeNum; i++) {
            CopyMatrix(MatrixDrive_GetMatrix(), (char *)w->nodeMtx + i * 64);
            MatrixDrive_TransMatrix(0.0f, -40.0f, 0.0f);
            flame[i].effect = SetParticleEffect(4, MatrixDrive_GetMatrix()[3], IdentityQuaternion);
            flame[i].off = 0;
        }
    } else {
        flame = (CandleFlame *)iosMallocDebug(ios_partition_sugipon, 8, "src/candle.c", 35);
        flame->effect = SetParticleEffect(4, mtx, IdentityQuaternion);
        flame->off = 0;
    }
    debug_StdPrintfDummy("\x1b[33mInitialize candle geometries.\x1b[m\n");
    return (int)flame;
}

void CandleDL(GObj *self)
{
    Sub15C *d = self->dobj;
    if (d->disp != 0) {
        p2o_SetDefaultEnviroment();
        p2o_DispVU1DObjMulti(d);
    }
}

inline void _deleteLayoutedCandleParticleEffect(void *gobj)
{
    CandleFlame *flame;
    int i;

    flame = GOBJ_SUB(gobj)->work;
    if (GOBJ_SUB(gobj)->nodeNum >= 2) {
        for (i = 0; i < GOBJ_SUB(gobj)->nodeNum; i++) {
            if (flame[i].off == 0) {
                DeleteParticleEffect(flame[i].effect);
                flame[i].effect = -1;
                flame[i].off = 1;
            }
        }
    }
}

INCLUDE_ASM(CandleGeo);

INCLUDE_ASM(DeleteLayoutedCandleParticleEffect);
