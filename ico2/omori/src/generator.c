#include "typedef.h"
#include "debug.h"
#include "gamesys.h"
#include "memory.h"
#include "obj_manager.h"
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

typedef struct GVGeo2 { /* field names derived */
    char pad0[12];
    float rot[3]; /* 0x0C */
    char pad18[24];
    int enemyKind; /* 0x30, the enemy kind a generator calls */
    char pad34[14];
    short reviveCount;          /* 0x42, enemies left to revive, -1 for unlimited */
    unsigned short motherLabel; /* 0x44, the label of the generator the enemy belongs to */
    unsigned char kind;         /* 0x46, the object kind (33 for a generator) */
    char pad47[1];
    unsigned int flags; /* 0x48 */
} GVGeo2;

typedef struct GenBga { /* field names derived */
    BgaDisp *p;         /* the multi-BGA manager */
    char active;        /* set while the manager plays */
    char pad5[3];
} GenBga;

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
} GenWork;

extern StgPre stageData[];
extern GVGeo2 objLayout[];

/* the generator packet: 11277 bytes are read into it, which is what
   GetsizeGeneratorPacket returns, three under the buffer */
static int generatorPacket[2820]; /* derived name */

#include "generator.h"
#include <string.h>
#include "ios.h"
#include "main.h"

inline int SearchActiveGenerator(void)
{
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(33);
    while (g != 0) {
        GenWork *w = GOBJ_SUB(g)->work;

        if (((GObj *)g)->active != 0) {
            if (w->status == 1) {
                return 1;
            }
        }
        g = (char *)isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}

int CheckGeneratorCollision(char *gobj, float *dir)
{
    float pos[4];
    float tmp[4];
    float p[4];
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(33);
    GetRootPosition(pos, gobj);
    sceVu0ScaleVector(tmp, dir, 100.0f);
    sceVu0AddVector(pos, pos, tmp);

    for (; g != 0; g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        GenWork *w = GOBJ_SUB(g)->work;

        if (((GObj *)g)->active == 0) {
            continue;
        }
        if (w->status != 1) {
            continue;
        }
        GetRootPosition(p, g);
        if (_DistxzSqGV(p, pos) < 22500.0f) {
            float d = p[1] - 50.0f - pos[1];

            if ((d < 0.0f ? -d : d) < 100.0f) {
                return 0;
            }
        }
    }
    return 1;
}

/* the offsets GetGeneratorSafePosition tries around a generator */
typedef struct SafePosOffset { /* field names derived */
    float x;
    float y;
    float z;
    int kind;
} SafePosOffset;

extern SafePosOffset generatorSubPosition[];

/* whether no live enemy stands close to pos; GetGeneratorSafePosition uses it
   twice and reads the result as a byte */
static inline unsigned char IsGeneratorSafePosition(float *pos) /* derived name */
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(17); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        float p[4];

        if (((GObj *)g)->active == 0) {
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

void GetGeneratorSafePosition(float *dst, char *gobj)
{
    float pos[4];
    int i;

    GetRootPosition(pos, gobj);
    if (IsGeneratorSafePosition(pos)) {
        dst[0] = pos[0];
        dst[1] = pos[1];
        dst[2] = pos[2];
        return;
    }

    {
        float probe[4];

        for (i = 0; i < 7; i++) {
            SafePosOffset *e = &generatorSubPosition[i];

            if (e->kind != ((GObj *)gobj)->labelId) {
                continue;
            }
            probe[0] = -e->x;
            probe[1] = -e->y;
            probe[2] = -e->z;
            if (IsGeneratorSafePosition(probe)) {
                dst[0] = probe[0];
                dst[1] = probe[1];
                dst[2] = probe[2];
                return;
            }
        }
        GetRootPosition(probe, gobj);
        dst[0] = probe[0];
        dst[1] = probe[1];
        dst[2] = probe[2];
    }
}

void switch_MainStatus(char *gobj, unsigned char st)
{
    float pos[4];
    GenWork *w = GOBJ_SUB(gobj)->work;

    if (st == w->status) {
        return;
    }

    switch (w->status) {
    case 0:
        if (!IsNeedGeneratorHard()) {
            w->status = 2;
            gamesysObjInfoUniqDataSet(gobj);
            break;
        }
        iosOmSendMail(gobj, 0, gobj);
        w->status = 1;
        w->timer = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 4;
        GetGeneratorSafePosition(pos, gobj);
        SetRootPosition(gobj, pos);
        gamesysObjInfoUniqDataSet(gobj);
        break;

    case 1:
        iosOmSendMail(gobj, 2, gobj);
        w->status = 2;
        gamesysObjInfoUniqDataSet(gobj);
        break;

    case 2:
        break;
    }
}

extern void __assert(char *file, int line, char *expr);

/* stop the current animation slot's manager (ResetCurrentBga) and start the
   manager of a slot (EntryBga), for endfunc_BGA and GeneratorGeo */
static inline char *ResetCurrentBga(char *gobj) /* derived name */
{
    GenWork *w = GOBJ_SUB(gobj)->work;

    if (w->cur != -1) {
        /* the slot, as a byte offset from the record */
        char *e = (char *)w + w->cur * 8;
        char *q;

        *(char *)(e + 0x34) = 0;
        q = (char *)w + w->cur * 8;
        **(float **)(q + 0x30) = -1.0f;
    }
    return (char *)w;
}

static inline void EntryBga(char *gobj, GenWork *w, int slot) /* derived name */
{
    float mtx[4];

    memset(mtx, 0, 16);
    mtx[3] = 1.0f;
    EntryMultiBgaManager(w->bga[slot].p, 0, -1, (void *)test_CURRENTROOT(gobj), mtx);
}

void endfunc_BGA(char *gobj)
{
    GenWork *w = GOBJ_SUB(gobj)->work;

    switch (w->cur) {
    case 0: {
        GenWork *cur;

        w->bga[1].active = 1;
        cur = (GenWork *)ResetCurrentBga(gobj);
        EntryBga(gobj, cur, 1);
        cur->cur = 1;
        break;
    }

    case 1:
        *(int *)w->bga[1].p = 0;
        break;

    case 2: {
        GenWork *cur;

        w->bgaDone = 1;
        cur = (GenWork *)ResetCurrentBga(gobj);
        cur->cur = -1;
        break;
    }

    default:
        debug_assert(__FILE__, 504);
        __assert(__FILE__, 504, "0");
        break;
    }
}

char *IsNeedGeneratorHard(char *mother)
{
    GenWork *w = GOBJ_SUB(mother)->work;
    char *g;
    int count = 0;
    int isCalling = (w->status == 1);

    if (mother != 0 && ((GObj *)mother)->labelId == 3758) {
        int found = 0;

        g = (char *)isysGObjSearchFromObjLayoutID(3757);
        if (g != 0) {
            GVGeo2 *gv = &objLayout[((GObj *)g)->labelId];

            if (gv->reviveCount == -1 || gv->reviveCount > 0) {
                found = 1;
            }
            if (isEnemyActive(g)) {
                found = 1;
            }
        }
        return found ? g : 0;
    }

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        Act *p = GOBJ_ACT(g);

        if ((unsigned int)(p->flags18.ll >> 34) & 1) {
            continue;
        }
        if (mother == 0 ||
            (((GObj *)mother)->labelId != GetMotherGeneratorLabelAskEnemy(g) &&
             objLayout[((GObj *)g)->labelId].motherLabel != ((GObj *)mother)->labelId)) {
            continue;
        }
        if (objLayout[((GObj *)g)->labelId].reviveCount == -1 ||
            objLayout[((GObj *)g)->labelId].reviveCount > 0) {
            return g;
        }
        if (isEnemyActive(g)) {
            return g;
        }
    }

    for (g = (char *)isysGObjSearchFromObjKindID_begin(33); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {}

    for (g = (char *)isysGObjSearchFromObjKindID_begin(62); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        Act *p = GOBJ_ACT(g);

        count += (int)(p->flags18.ll >> 32) & 1;
    }

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        Act *p = GOBJ_ACT(g);
        GVGeo2 *gv = &objLayout[((GObj *)g)->labelId];

        if (((GObj *)g)->labelId == 3757) {
            continue;
        }
        if ((unsigned int)(p->flags18.ll >> 34) & 1) {
            if (count < 5) {
                continue;
            }
            return g;
        }
        if (mother != 0) {
            if (((GObj *)mother)->labelId == GetMotherGeneratorLabelAskEnemy(g)) {
                continue;
            }
            if (objLayout[((GObj *)g)->labelId].motherLabel == ((GObj *)mother)->labelId) {
                continue;
            }
        }
        if (isEnemyActive(g)) {
            return g;
        }
        if (gv->reviveCount == -1 || gv->reviveCount > 0) {
            if (!isCalling) {
                return g;
            }
            {
                char *m = GetMotherGeneratorGObjAskEnemy(g);

                if (m != 0 && IsOpenGenerator(m)) {
                    return g;
                }
            }
        }
    }
    return 0;
}

inline int IsEnableCallEnemyByTargetGObj(void *a0)
{
    GVGeo2 *g = &objLayout[((GObj *)a0)->labelId];
    Act *p = GOBJ_ACT(a0);
    if (g->motherLabel != 0) {
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

inline void *IsEnableCallEnemy(char *self)
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        Act *p = GOBJ_ACT(g);
        int no = ((GObj *)g)->labelId;
        GVGeo2 *gg = &objLayout[no];

        if (self != 0 && ((GObj *)self)->labelId == 3758 && no != 3757) {
            continue;
        }
        if (objLayout[no].motherLabel != 0 && self != 0 &&
            objLayout[no].motherLabel != ((GObj *)self)->labelId) {
            continue;
        }
        if ((unsigned int)(p->flags18.ll >> 34) & 1) {
            continue;
        }
        if ((gg->flags >> 21) & 1) {
            continue;
        }
        if (gg->reviveCount == -1 || gg->reviveCount > 0) {
            return g;
        }
    }
    return 0;
}

inline char *DirectCallEnemy(char *gobj, char *mother, float *pos, float *dir, int a4)
{
    GVGeo2 *gg = &objLayout[((GObj *)gobj)->labelId];

    gg->flags = (gg->flags | 0x200000) & 0xFFFBFFFF;

    debug_StdPrintfDummy("call enemy! = %d (%p : %d)\n", ((GObj *)gobj)->labelId, mother,
                         (mother != 0) ? ((GObj *)mother)->labelId : -1);
    debug_StdPrintfDummy("[%8s] %8f %8f %8f %8f\n", "revive", pos[0], pos[1], pos[2], pos[3]);
    if (mother != 0) {
        SetMotherGenerator(((GObj *)gobj)->labelId, ((GObj *)mother)->labelId);
    }
    if (gg->reviveCount != -1) {
        gg->reviveCount--;
    }
    actEnemyRestart(gobj, pos, dir, a4, mother);
    ACTGame_SaveActorInformation(gobj);
    return gobj;
}

char *CallEnemy(char *mother, float *pos, float *dir, int a4)
{
    char *gobj = (char *)IsEnableCallEnemy(mother);

    if (gobj != 0) {
        return DirectCallEnemy(gobj, mother, pos, dir, a4);
    }
    return 0;
}

inline void LockEnemyGenerate(int *self)
{
    Act *p;
    p = GOBJ_ACT(self);
    debug_StdPrintfDummy("lock! = %d\n", ((GObj *)self)->labelId);
    p->flags18.ll = p->flags18.ll | 0x400000000LL;
}

inline void UnlockEnemyGenerate(void *a0)
{
    Act *p = GOBJ_ACT(a0);
    GVGeo2 *g = &objLayout[((GObj *)a0)->labelId];
    debug_StdPrintfDummy("unlock! = %d\n", ((GObj *)a0)->labelId);
    p->flags18.ll &= ~((unsigned long)0x8000 << 19);
    g->flags = (g->flags | 0x200000) & 0xFFFBFFFF;
}

inline void RestoreReviveCount(char *gobj)
{
    GVGeo2 *g = (GVGeo2 *)((char *)objLayout + ((GObj *)gobj)->labelId * 0x4C);
    if (g->reviveCount != -1) {
        int n = (short)(g->reviveCount + 1);
        int lim = ((g->flags >> 5) & 0x1F) + 1;
        n = (lim < n) ? lim : n;
        g->reviveCount = n;
        if (((GObj *)gobj)->labelId == 3757) {
            g->reviveCount = (g->reviveCount < 0) ? 0 : ((g->reviveCount > 1) ? 1 : g->reviveCount);
        }
    }
}

void Generator_QuickCall(char *gobj)
{
    GenWork *w = GOBJ_SUB(gobj)->work;

    w->status = 1;
    gamesysObjInfoUniqDataSet(gobj);
    iosOmSendMail(gobj, 1, gobj);
}

inline void Generator_Call(char *a0)
{
    GenWork *w = GOBJ_SUB(a0)->work;

    w->callRequests += 1;
}

inline void Generator_ResetCount(char *a0)
{
    GenWork *w = GOBJ_SUB(a0)->work;

    w->resetRequest = 1;
}

inline void Generator_Mask(char *a0)
{
    GenWork *w = GOBJ_SUB(a0)->work;

    w->masked = 1;
}

inline void Generator_MaskOff(char *a0)
{
    GenWork *w = GOBJ_SUB(a0)->work;

    w->masked = 0;
}

void Generator_Delete(void *a0)
{
    switch_MainStatus(a0, 0);
}

int GetMotherGenerator(int label)
{
    int info[2];
    int x;
    int st;
    int i;
    int j;
    int best;
    int ret;

    if (label == 3757) {
        return 3758;
    }

    GetKidnapInfo(&info[0], &info[1]);
    if (info[0] != -1 && info[0] == label) {
        return info[1];
    }

    x = (int)((objLayout + label)->flags << 27) >> 27;
    if (x != -1) {
        st = GetStageFromLabel(label);
        for (i = stageData[st].labelTop; i < stageData[st].labelEnd; i++) {
            GVGeo2 *g = &objLayout[i];

            if (g->kind == 33) {
                if (((int)(g->flags << 27) >> 27) == x) {
                    return i;
                }
            }
        }
    }

    best = 0;
    ret = -1;
    st = GetStageFromLabel(label);
    for (j = stageData[st].labelTop; j < stageData[st].labelEnd; j++) {
        GVGeo2 *g = &objLayout[j];

        if (g->kind == 33) {
            int v = (g->flags >> 17) & 1;

            if (best < v) {
                best = v;
                ret = j;
            }
        }
    }
    return ret;
}

inline void SetMotherGenerator(int no, int label)
{
    int i;
    int cnt;

    if (no == 3757) {
        return;
    }
    cnt = 0;
    for (i = stageData[stage_no].labelTop; i < stageData[stage_no].labelEnd; i++) {
        GVGeo2 *g = &objLayout[i];
        if (g->kind == 33) {
            if (i == label) {
                GVGeo2 *m = &objLayout[no];
                m->flags = ((int)m->flags & ~0x3C00) | ((cnt & 0xF) << 10);
                return;
            }
            cnt++;
        }
    }
}

inline void Generator_Init(void)
{
    int i;

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &objLayout[i];
        unsigned int x = g->flags & 0xFFDFFFFF;
        unsigned int y = x & 0xFFFBFFFF;

        y |= ((x >> 19) & 1) << 18;
        g->flags = y;
        g->reviveCount = (y >> 5) & 0x1F;
        if ((y >> 19) & 1) {
            unsigned int z = y | 0x40000;
            g->flags = z;
            if ((int)((z >> 5) & 0x1F) != -1) {
                g->reviveCount++;
            }
        }
    }
}

inline void ReturnEnemyToGenerator(int a0)
{
    GVGeo2 *g = &objLayout[a0];
    unsigned int x = g->flags & 0xFFDFFFFF;
    unsigned int y = x & 0xFFFBFFFF;
    y |= ((x >> 19) & 1) << 18;
    g->flags = y;
    if ((y >> 19) & 1) {
        unsigned int z = y | 0x40000;
        g->flags = z;
        if ((int)((z >> 5) & 0x1F) != -1) {
            g->reviveCount++;
        }
    }
}

inline int *GetbufpGeneratorPacket(void)
{
    return generatorPacket;
}

inline int GetsizeGeneratorPacket(void)
{
    return 11277;
}

void ReadGeneratorPacket(void)
{
    unsigned char *p = (unsigned char *)GetbufpGeneratorPacket();
    int i;

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &objLayout[i];
        unsigned int b = *p++;
        unsigned int x = (b >> 4) << 10;

        g->flags = ((int)g->flags & ~0x3C00) | x;
        g->flags = (g->flags & ~0x200000) | ((b & 1) << 21);
    }

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &objLayout[i];
        char c = *(char *)p++;

        g->flags = (g->flags & ~0x40000) | ((c & 1) << 18);
    }

    for (i = 0; i < 3759; i++) {
        objLayout[i].reviveCount = (char)*p;
        p++;
    }
}

void MakeGeneratorPacket(void)
{
    char *p = (char *)GetbufpGeneratorPacket();
    int i;

    for (i = 0; i < 3759; i++) {
        *p++ = (((int)(objLayout[i].flags << 18) >> 28) << 4) | ((objLayout[i].flags >> 21) & 1);
    }

    for (i = 0; i < 3759; i++) {
        *p++ = (objLayout[i].flags >> 18) & 1;
    }

    for (i = 0; i < 3759; i++) {
        *p++ = objLayout[i].reviveCount;
    }
}

inline void ResetReviveCountEnemy(int a0)
{
    objLayout[((GObj *)a0)->labelId].reviveCount = 0;
}

inline void SetInfoSpKidnapEnemy(void)
{
    GVGeo2 *info = &objLayout[3757]; /* the kidnap enemy's layout record */
    info->flags |= 0x200000;
    info->flags &= ~0x40000;
    info->reviveCount = 0;
}

inline void SetInfoSpKidnapGenerator(short *a0)
{
    a0[0] = 1;
    a0[1] = 1;
}

inline int RestoreGeneratorGeo(float *dst, float *src)
{
    dst[0] = src[4];
    dst[1] = src[5];
    dst[2] = src[6];
    return 1;
}

inline int RestoreGeneratorExtGeo(char *a0, short *a1)
{
    GenWork *p = GOBJ_SUB(a0)->work;
    p->status = a1[24];
    p->callRequests = a1[25];
    if (a1[24] == 1) {
        p->callState = 2;
        iosOmSendMail(a0, 1, a0);
    }
    return 1;
}

inline int MemoryGenerator(short *a0, char *a1)
{
    GenWork *p = GOBJ_SUB(a1)->work;
    a0[0] = p->status;
    a0[1] = p->callRequests;
    return 1;
}

/* The pending-BGA request queue of the generator actor: the count lives at
   gobj+0x58 and the entries run from gobj+0x5C. */
typedef struct GenReqEntry { /* field names derived */
    unsigned int kind;
    int f4;
} GenReqEntry;

typedef struct GenReq {
    int f0;
    int count;
} GenReq;

void generatorBeforeFunc(char *gobj)
{
    GenWork *w = GOBJ_SUB(gobj)->work;
    GenReq *q = (GenReq *)(gobj + 0x54);
    int i;

    for (i = 0; i < q->count; i++) {
        switch (((GenReqEntry *)(gobj + 0x5C))[i].kind) {
        case 0: {
            GenWork *cur;

            w->bga[0].active = 1;
            cur = (GenWork *)ResetCurrentBga(gobj);
            EntryBga(gobj, cur, 0);
            cur->cur = 0;
            break;
        }

        case 1: {
            GenWork *cur;

            w->bga[1].active = 1;
            cur = (GenWork *)ResetCurrentBga(gobj);
            EntryBga(gobj, cur, 1);
            cur->cur = 1;
            break;
        }

        case 2:
            w->bgaDelay = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 4;
            break;
        }
    }
    q->count = 0;
}

inline GenWork *InitGeneratorGeo(char *gobj, GVGeo2 *src)
{
    GenWork *p = iosMallocDebug(ios_partition_sugipon, 112, __FILE__, 1230);
    int i;

    p->count = 0;
    p->autoCallTimer = 0;
    p->callRequests = 0;
    p->masked = 0;
    p->resetRequest = 0;
    p->kind = src->enemyKind;
    p->hard = 0;

    p->status = 0;
    p->callState = 0;
    p->cur = -1;
    p->callDelay = -1;
    p->bgaDelay = -1;
    p->timer = 0;

    p->dir[0] = 0.0f;
    p->dir[1] = 0.0f;
    p->dir[2] = 1.0f;
    /* the direction is a quadword whose fourth word holds the bgaDone byte */
    *(float *)((char *)p + 0x2C) = 0.0f;
    _ApplyRyGV(p->dir, src->rot[2]);

    {
        char *r = &p->bga[0].active;
        BgaDisp **q = &p->bga[0].p;

        for (i = 0; i < 4; i++) {
            *q = InitMultiBgaManager(1);
            *r = 0;
            q += 2;
            r += 8;
        }
    }

    return p;
}

/* for GeneratorGeo: the generator's forward axis, the direction it sends
   enemies off in */
static inline void SetGeneratorAimVector(char *gobj) /* derived name */
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
static inline void EntryGeneratorBga2(char *gobj) /* derived name */
{
    GenWork *cur = (GenWork *)ResetCurrentBga(gobj);

    EntryBga(gobj, cur, 2);
    cur->cur = 2;
}

/* whether any live hard-stage generator is calling, for GeneratorGeo, which
   reads the result as a byte */
static inline unsigned char IsGeneratorCalling(void) /* derived name */
{
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(33);
    while (g != 0) {
        GenWork *w = GOBJ_SUB(g)->work;

        if (((GObj *)g)->active != 0) {
            if (w->hard != 0) {
                if (w->status == 1) {
                    return 1;
                }
            }
        }
        g = (char *)isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}

/* call an enemy out of the generator and start its call animation, for
   GeneratorGeo */
static inline void CallEnemyFromGenerator(char *gobj, float *pos, float *dir) /* derived name */
{
    GenWork *w = GOBJ_SUB(gobj)->work;

    if (CallEnemy(gobj, pos, dir, w->kind) != 0) {
        float mtx[4];

        memset(mtx, 0, 16);
        mtx[3] = 1.0f;
        EntryMultiBgaManager(w->bga[3].p, 0, -1, (void *)test_CURRENTROOT(gobj), mtx);
    }
}

void GeneratorGeo(char *gobj)
{
    GenWork *w = GOBJ_SUB(gobj)->work;
    int hard = 0;
    StgPre *sd = &stageData[stage_no];
    int noBoy = sd->flag1 && girlGObj == 0;

    w->hard = (int)IsNeedGeneratorHard(gobj);
    if (w->hard != 0) {
        if (w->timer < 30) {
            w->timer = 30;
        }
    }

    if (w->count >= 12) {
        if (w->resetRequest != 0) {
            w->callRequests = 0;
            w->resetRequest = 0;
        }

        if (isysGObjSearchFromObjKindID_begin(47) != 0) {
            w->active = 1;
        } else {
            w->active = 0;
        }

        SetGeneratorAimVector(gobj);

        if (noBoy) {
            w->callRequests = 0;
        }

        if (w->callRequests == 0) {
            if (w->masked == 0) {
                if (!noBoy) {
                    w->autoCallTimer = w->autoCallTimer + 1;
                    if (w->autoCallTimer >= 11) {
                        Generator_Call(gobj);
                        w->autoCallTimer = 0;
                    }
                }
            }
        }

        switch (w->callState) {
        case 0:
            if (w->callRequests != 0) {
                w->callState = 1;
                w->callDelay = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 2;
                switch_MainStatus(gobj, 1);
            }
            break;

        case 1:
            w->callDelay = w->callDelay - 1;
            if (w->callDelay < 0) {
                w->callState = 2;
            }
            break;

        case 2:
            hard = 1;
            break;

        default:
            debug_assert(__FILE__, 1371);
            __assert(__FILE__, 1371, "0");
            break;
        }

        if (w->active != 0) {
            hard = 1;
        }

        {
            float pos[4];
            int i;

            if (hard) {
                if (((60 - systemStatus[0] * 10) / systemStatus[1]) / 2 < w->count) {
                    if (w->callRequests != 0) {
                        GetRootPosition(pos, gobj);
                        for (i = 0; i < w->callRequests; i++) {
                            CallEnemyFromGenerator(gobj, pos, w->dir);
                        }
                        w->callRequests = 0;
                    }
                }
            }

            if (!IsGeneratorCalling()) {
                if (w->timer == 0) {
                    switch_MainStatus(gobj, 0);
                }
            }

            if (w->bgaDelay != -1) {
                if (w->bgaDelay == 0) {
                    w->bga[2].active = 1;
                    EntryGeneratorBga2(gobj);
                    w->bgaDelay = -1;
                } else {
                    w->bgaDelay = w->bgaDelay - 1;
                }
            }

            debug_Arrow(100.0f, (void *)test_CURRENTROOT(gobj), w->dir, 0xFF, 0, 0xFF);
        }
    }

    if (w->timer != 0) {
        w->timer = w->timer - 1;
    }
    w->count = w->count + 1;
}

/* for GeneratorDL: put the animation managers at the generator's root */
static inline void SetGeneratorBgaRootPosition(char *gobj, GenBga *tbl) /* derived name */
{
    float pos[3];
    int i;

    /* test_CURRENTROOT is unprototyped in this TU (C89 default int), as its
       earlier call sites need; the root matrix is read through a float view. */
    pos[0] = ((float *)test_CURRENTROOT(gobj))[0];
    pos[1] = ((float *)test_CURRENTROOT(gobj))[1];
    pos[2] = ((float *)test_CURRENTROOT(gobj))[2];

    for (i = 0; i < 4; i++) {
        char *p = (char *)tbl[i].p;

        *(float *)(p + 0x10) = pos[0];
        *(float *)(p + 0x14) = pos[1];
        *(float *)(p + 0x18) = pos[2];
    }
}

void GeneratorDL(char *gobj)
{
    GenWork *w = GOBJ_SUB(gobj)->work;
    GenBga *tbl = w->bga;
    int idx;

    SetGeneratorBgaRootPosition(gobj, tbl);

    if (w->active) {
        DispMultiBgaManagerWithKind(508, w->bga[1].p, 1);
    } else {
        DispMultiBgaManagerWithKind(507, w->bga[0].p, 1);
        DispMultiBgaManagerWithKind(508, w->bga[1].p, 1);
        DispMultiBgaManagerWithKind(509, w->bga[2].p, 1);
        DispMultiBgaManagerWithKind(506, w->bga[3].p, 1);
    }

    idx = w->cur;
    if (idx != -1) {
        GenBga *e = &tbl[idx];

        if (*(float *)e->p < 0.0f) {
            endfunc_BGA(gobj);
        }
    }
}

inline int GeneratorWorkEnd(char *a0)
{
    return *(int *)((char *)GOBJ_SUB(a0)->work + 8) == 0;
}

inline int IsOpenGenerator(char *gobj)
{
    GenWork *w = GOBJ_SUB(gobj)->work;
    int ret = 0;
    if (w->status == 1) {
        GVGeo2 *g = (GVGeo2 *)(((GObj *)gobj)->labelId * sizeof(GVGeo2) + (char *)objLayout);
        ret = (((int)(g->flags << 27) >> 27) == -2) ? 0 : w->status;
    }
    return ret;
}
