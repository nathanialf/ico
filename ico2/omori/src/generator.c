#include "typedef.h"
#include "debug.h"
#include "gamesys.h"
#include "memory.h"
#include "obj_manager.h"
#include "gobj.h"
#include "commonact.h"
#include "act-game.h"
#include "boyact.h"
#include "enemy_act.h"
#include "ebrain.h"
#include "geometryManager.h"
#include "multiBgaManager.h"
#include "debug_exception.h"
#include "gv.h"
#include <libvu0.h>
#include "camera-editor.h"
#include "sceneManager.h"
#include <assert.h>

typedef struct GenBga { /* field names derived */
    BgaDisp *p;         /* the multi-BGA manager */
    char active;        /* set while the manager plays */
    char pad5[3];
} GenBga; /* derived name */

/* The generator's work record: whether the stage needs it hard, three state
   bytes, the enemy kind it calls, the direction it sends enemies off in, its
   four multi-BGA managers (each with its active byte), the main status, the
   current animation slot and the timers.  The direction is three floats: the byte at 0x2C follows it, and
   sceVu0ApplyMatrix writes a whole quadword there. */
typedef struct GenWork {        /* field names derived */
    int count;                  /* 0x00, frames since the generator started */
    int autoCallTimer;          /* 0x04, counts up to the automatic call */
    int callRequests;           /* 0x08, enemy calls waiting to be served */
    int hard;                   /* 0x0C */
    unsigned char masked;       /* 0x10, Generator_Mask */
    unsigned char active;       /* 0x11 */
    unsigned char resetRequest; /* 0x12, Generator_ResetCount */
    char pad13[1];
    int kind;              /* 0x14 */
    int pad18[2];          /* 0x18 */
    float dir[3];          /* 0x20 */
    unsigned char bgaDone; /* 0x2C, set when the BGA run ends */
    char pad2D[3];
    GenBga bga[4]; /* 0x30 */
    int status;    /* 0x50 */
    int callState; /* 0x54, 0 idle, 1 waiting out callDelay, 2 calling */
    int cur;       /* 0x58 */
    int callDelay; /* 0x5C */
    int bgaDelay;  /* 0x60, frames until the second BGA starts, -1 for none */
    int timer;     /* 0x64 */
} GenWork;         /* derived name */

/* the generator packet: 10365 bytes are read into it, which is what
   GetsizeGeneratorPacket returns, three under the buffer */
static int generatorPacket[2592]; /* derived name */

#include "generator.h"
#include <string.h>
#include "ios.h"
#include "main.h"
#include "include_asm.h"

static GObj *IsNeedGeneratorHard(GObj *mother);

INCLUDE_ASM(CheckGeneratorCollision);

/* whether no live enemy stands close to pos; GetGeneratorSafePosition uses it
   twice and reads the result as a byte */
static inline unsigned char IsGeneratorSafePosition(float *pos) /* derived name */
{
    GObj *g;

    for (g = isysGObjSearchFromObjKindID_begin(17); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        float p[4];

        if (g->active == 0) {
            continue;
        }
        GetRootPosition(p, g);
        if (_DistxzSqGV(pos, p) < 22500.0f) {
            float d = pos[1] - 50.0f - p[1];

            if ((d < 0.0f ? -d : d) < 100.0f) {
                return 0;
            }
        }
    }
    return 1;
}

INCLUDE_ASM(GetGeneratorSafePosition);

/* stop the current animation slot's manager (ResetCurrentBga) and start the
   manager of a slot (EntryBga), for endfunc_BGA and GeneratorGeo */
static inline char *ResetCurrentBga(GObj *gobj) /* derived name */
{
    GenWork *w = GOBJ_SUB(gobj)->work;

    if (w->cur != -1) {
        w->bga[w->cur].active = 0;
        w->bga[w->cur].p->frame = -1.0f;
    }
    return (char *)w;
}

static inline void EntryBga(GObj *gobj, GenWork *w, int slot) /* derived name */
{
    float mtx[4];

    memset(mtx, 0, 16);
    mtx[3] = 1.0f;
    EntryMultiBgaManager(w->bga[slot].p, 0, -1, (void *)test_CURRENTROOT(gobj), mtx);
}

INCLUDE_ASM(endfunc_BGA);

INCLUDE_ASM(IsNeedGeneratorHard);

inline int IsEnableCallEnemyByTargetGObj(GObj *gobj)
{
    GenGeo *g = &objLayout[gobj->labelId];
    Act *p = GOBJ_ACT(gobj);
    if (g->parent != 0) {
        return 0;
    }
    if ((unsigned int)(p->flags18.ll >> 34) & 1) {
        return 0;
    }
    if (((g->flags >> 21) & 1) == 0 && (g->reviveCount == -1 || g->reviveCount > 0)) {
        return 1;
    }
    return 0;
}

GObj *CallEnemy(GObj *mother, float *pos, float *dir, int kind);

INCLUDE_ASM_LIT(DirectCallEnemy);

INCLUDE_ASM(CallEnemy);

INCLUDE_ASM_LIT(LockEnemyGenerate);

INCLUDE_ASM_LIT(UnlockEnemyGenerate);

INCLUDE_ASM(Generator_QuickCall);

INCLUDE_ASM(GetMotherGenerator);

INCLUDE_ASM(ReadGeneratorPacket);

INCLUDE_ASM(MakeGeneratorPacket);

inline void ResetReviveCountEnemy(GObj *gobj)
{
    objLayout[gobj->labelId].reviveCount = 0;
}

inline void SetInfoSpKidnapEnemy(short *work)
{
    GenGeo *info = &objLayout[3453]; /* the kidnap enemy's layout record */
    info->flags |= 0x200000;
    info->flags &= ~0x40000;
    info->reviveCount = 0;
}

inline void SetInfoSpKidnapGenerator(short *info)
{
    info[0] = 1;
    info[1] = 1;
}

/* The generator's view of its object's mail box (GObj 0x54, typedef.h's
   IosMailBox): the count, and the queued mails with an unsigned kind. */
typedef struct GenReqEntry { /* field names derived */
    unsigned int kind;
    int arg;
} GenReqEntry; /* derived name */

typedef struct GenReq { /* field names derived */
    int queue;
    int count;
} GenReq; /* derived name */

INCLUDE_ASM(generatorBeforeFunc);

/* The kind's constructor: CreateLayoutedGObj hands it the scene object's
   SObjSimpleSetting, not the layout row.  The enemy kind is the setting's
   object word (initSceneGObj fills it from the row's initArg) and the aim
   angle its Y rotation. */
/* for GeneratorGeo: the generator's forward axis, the direction it sends
   enemies off in */
static inline void SetGeneratorAimVector(GObj *gobj) /* derived name */
{
    GenWork *w = GOBJ_SUB(gobj)->work;
    float m[16];
    float v[4];

    UpdateRootMatrix(gobj);

    memset(v, 0, 16);
    v[2] = 1.0f;
    GetRootMatrix(m, gobj);
    v[3] = 0.0f;
    sceVu0ApplyMatrix(w->dir, m, v);
}

/* for GeneratorGeo: reset the current slot and start slot 2 */
static inline void EntryGeneratorBga2(GObj *gobj) /* derived name */
{
    GenWork *cur = (GenWork *)ResetCurrentBga(gobj);

    EntryBga(gobj, cur, 2);
    cur->cur = 2;
}

/* whether any live hard-stage generator is calling, for GeneratorGeo, which
   reads the result as a byte */
static inline unsigned char IsGeneratorCalling(void) /* derived name */
{
    GObj *g;

    g = isysGObjSearchFromObjKindID_begin(33);
    while (g != 0) {
        GenWork *w = GOBJ_SUB(g)->work;

        if (g->active != 0) {
            if (w->hard != 0) {
                if (w->status == 1) {
                    return 1;
                }
            }
        }
        g = isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}

/* call an enemy out of the generator and start its call animation, for
   GeneratorGeo */
static inline void CallEnemyFromGenerator(GObj *gobj, float *pos, float *dir) /* derived name */
{
    GenWork *w = GOBJ_SUB(gobj)->work;

    if (CallEnemy(gobj, pos, dir, w->kind) != 0) {
        float mtx[4];

        memset(mtx, 0, 16);
        mtx[3] = 1.0f;
        EntryMultiBgaManager(w->bga[3].p, 0, -1, (void *)test_CURRENTROOT(gobj), mtx);
    }
}

INCLUDE_ASM(GeneratorGeo);

/* for GeneratorDL: put the animation managers at the generator's root */
static inline void SetGeneratorBgaRootPosition(GObj *gobj, GenBga *tbl) /* derived name */
{
    float pos[3];
    int i;

    pos[0] = test_CURRENTROOT(gobj)[0];
    pos[1] = test_CURRENTROOT(gobj)[1];
    pos[2] = test_CURRENTROOT(gobj)[2];

    for (i = 0; i < 4; i++) {
        BgaDisp *p = tbl[i].p;

        p->pos[0] = pos[0];
        p->pos[1] = pos[1];
        p->pos[2] = pos[2];
    }
}

INCLUDE_ASM(GeneratorDL);

INCLUDE_ASM(InitGeneratorGeo);

INCLUDE_ASM(Generator_Call);

INCLUDE_ASM(Generator_ResetCount);

INCLUDE_ASM(Generator_Mask);

INCLUDE_ASM(Generator_MaskOff);

INCLUDE_ASM(SetMotherGenerator);

INCLUDE_ASM(Generator_Init);

INCLUDE_ASM(GetbufpGeneratorPacket);

INCLUDE_ASM(GetsizeGeneratorPacket);

INCLUDE_ASM(RestoreGeneratorGeo);

INCLUDE_ASM(RestoreGeneratorExtGeo);

INCLUDE_ASM(MemoryGenerator);

INCLUDE_ASM(IsEnableCallEnemy);

INCLUDE_ASM(DirectCallEnemy);

INCLUDE_ASM(LockEnemyGenerate);

INCLUDE_ASM(UnlockEnemyGenerate);

INCLUDE_ASM(RestoreReviveCount);

INCLUDE_ASM(ReturnEnemyToGenerator);

INCLUDE_ASM(GeneratorWorkEnd);

INCLUDE_ASM(SearchActiveGenerator);
