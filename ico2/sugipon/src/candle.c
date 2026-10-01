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

typedef struct CandleWork { /* field names derived */
    char _pad0[8];
    int num;   /* 0x8 , flame count */
    char *mtx; /* 0xC , the per-flame 0x40-byte matrix run */
    char _pad_10[100];
    int alive; /* 0x74 */
    char _pad_78[1976];
    CandleFlame *flame; /* 0x830 */
} CandleWork;           /* derived name */

#define CANDLE_WORK(o) ((CandleWork *)*(int *)((char *)(o) + 0x15C)) /* derived name */

#include "candle.h"
#include "ios.h"

int InitCandleGeo(void *self, void *mtx)
{
    CandleWork *w = CANDLE_WORK(self);
    CandleFlame *flame;
    int i;

    if (w->num >= 2) {
        flame =
            (CandleFlame *)iosMallocDebug(ios_partition_sugipon, w->num * 8, "src/candle.c", 24);
        for (i = 0; i < w->num; i++) {
            CopyMatrix(MatrixDrive_GetMatrix(), w->mtx + i * 0x40);
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

void CandleGeo(void *self)
{
    CandleWork *w = CANDLE_WORK(self);
    CandleFlame *flame = w->flame;
    /* the release pass reads the work block through its own handle */
    CandleWork *cw = CANDLE_WORK(self);
    int i;

    if (w->num >= 2) {
        for (i = 0; i < w->num; i++) {
            CopyMatrix(MatrixDrive_GetMatrix(), CANDLE_WORK(self)->mtx + i * 0x40);
            MatrixDrive_TransMatrix(0.0f, -40.0f, 0.0f);
            if (flame[i].effect != -1) {
                SetParticleEffectGeometry(flame[i].effect, MatrixDrive_GetMatrix()[3],
                                          IdentityQuaternion);
            }
        }
        if (cw->alive == 0) {
            for (i = 0; i < cw->num; i++) {
                if (flame[i].effect != -1) {
                    DeleteParticleEffect(flame[i].effect);
                    flame[i].effect = -1;
                    flame[i].off = 1;
                }
            }
        }
    }
}

inline void _deleteLayoutedCandleParticleEffect(void *gobj)
{
    CandleFlame *flame;
    int i;

    flame = CANDLE_WORK(gobj)->flame;
    if (CANDLE_WORK(gobj)->num >= 2) {
        for (i = 0; i < CANDLE_WORK(gobj)->num; i++) {
            if (flame[i].off == 0) {
                DeleteParticleEffect(flame[i].effect);
                flame[i].effect = -1;
                flame[i].off = 1;
            }
        }
    }
}

inline void DeleteLayoutedCandleParticleEffect(void)
{
    void *gobj;

    gobj = isysGObjSearchFromObjKindID_begin(34);
    while (gobj != 0) {
        _deleteLayoutedCandleParticleEffect(gobj);
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}

void CandleDL(GObj *a0)
{
    int *s0 = a0->dobj;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment();
        return p2o_DispVU1DObjMulti(s0);
    }
}
