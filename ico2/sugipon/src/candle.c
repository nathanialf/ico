#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "memory.h"
#include "gobj.h"
#include "matrixDrive.h"
#include "particleEffect.h"
#include "quaternion.h"

/* kept local: this TU's uses of p2o_DispVU1DObjMulti do not fit the prototype in DisplayP2O.h */
extern int p2o_DispVU1DObjMulti(int a0);
/* kept local: this TU's uses of p2o_SetDefaultEnviroment do not fit the prototype in DisplayP2O.h */
extern int p2o_SetDefaultEnviroment(int a0);

typedef struct CandleFlame {
    int effect; /* 0x0 */
    int off;    /* 0x4 */
} CandleFlame;

typedef struct CandleWork {
    char _pad0[0x8];
    int num;   /* 0x8 , flame count */
    char *mtx; /* 0xC , the per-flame 0x40-byte matrix run */
    char _pad_10[0x74 - 0x10];
    int alive; /* 0x74 */
    char _pad_78[0x830 - 0x78];
    CandleFlame *flame; /* 0x830 */
} CandleWork;

#define CANDLE_WORK(o) ((CandleWork *)*(int *)((char *)(o) + 0x15C))

#include "candle.h"

extern int D_0063A438;
extern char D_0061F198[];
extern char D_0061F1A8[];

int InitCandleGeo(void *self, void *mtx)
{
    CandleWork *w = CANDLE_WORK(self);
    CandleFlame *flame;
    int i;

    if (w->num >= 2) {
        flame = (CandleFlame *)iosMallocDebug(D_0063A438, w->num * 8, D_0061F198, 0x18);
        for (i = 0; i < w->num; i++) {
            CopyMatrix(MatrixDrive_GetMatrix(), w->mtx + i * 0x40);
            MatrixDrive_TransMatrix(0.0f, -40.0f, 0.0f);
            flame[i].effect =
                SetParticleEffect(4, (char *)MatrixDrive_GetMatrix() + 0x30, IdentityQuaternion);
            flame[i].off = 0;
        }
    } else {
        flame = (CandleFlame *)iosMallocDebug(D_0063A438, 8, D_0061F198, 0x23);
        flame->effect = SetParticleEffect(4, mtx, IdentityQuaternion);
        flame->off = 0;
    }
    debug_StdPrintfDummy(D_0061F1A8);
    return (int)flame;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/candle", CandleGeo);

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

void CandleDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
