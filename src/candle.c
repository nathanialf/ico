#include "common.h"

#include "ico/types.h"

extern int p2o_DispVU1DObjMulti(int a0);
extern int p2o_SetDefaultEnviroment(int a0);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void DeleteParticleEffect(int id);
typedef struct CandleFlame {
    int effect;  /* 0x0 */
    int off;     /* 0x4 */
} CandleFlame;
typedef struct CandleWork {
    char _pad0[0x8];
    int num;                    /* 0x8  — flame count */
    char _pad_c[0x830 - 0xC];
    CandleFlame *flame;         /* 0x830 */
} CandleWork;
#define CANDLE_WORK(o) ((CandleWork *)*(int *)((char *)(o) + 0x15C))
/* prototypes: their order is the inline tail's emission order */
void DeleteLayoutedCandleParticleEffect(void);
void _deleteLayoutedCandleParticleEffect(void *gobj);
INCLUDE_ASM("asm/nonmatchings/src/candle", InitCandleGeo);
INCLUDE_ASM("asm/nonmatchings/src/candle", CandleGeo);
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

    gobj = isysGObjSearchFromObjKindID_begin(0x22);
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
