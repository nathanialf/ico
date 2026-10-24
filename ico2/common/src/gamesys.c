#include "typedef.h"
#include "backStage.h"
#include "debug.h"
#include "boyact.h"
#include "generator.h"
#include "gv.h"
#include "lws_kyomi.h"
#include "gflag.h"

#ifndef VERSION_JUN26
#include "itou_gflag.h"
#endif

#include "geometryManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <math.h>
#include "Matrix.h"
#include "gamesys.h"
#include <string.h>
#include "main.h"

typedef struct { /* field names derived */
    int start;
    int end;
    int no;
    int stage;
} GamesysObjInfoReq; /* derived name */

typedef union { /* field names derived */
    long long flag;
    GamesysObjInfo info;
} GamesysObjInfoFlag; /* derived name */

static void gamesysVersionLoad(GamesysMemCursor *self);
static void gamesysVersionSave(GamesysMemCursor *self);
void gamesysObjInfoLoad(GamesysMemCursor *h);
void gamesysObjInfoSave(GamesysMemCursor *h);
static void gamesysGeneratorInfoLoad(GamesysMemCursor *self);
static void gamesysGeneratorInfoSave(GamesysMemCursor *self);

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static void gamesysHintInfoLoad(GamesysMemCursor *self);
static void gamesysHintInfoSave(GamesysMemCursor *self);
#endif

static void gamesysCharacterInfoLoad(GamesysMemCursor *self);
static void gamesysCharacterInfoSave(GamesysMemCursor *self);

/* .data: the build stamp written into the save area and compared against
   the one the card holds; the save area's handler table, a load and a save
   handler per record, which gamesysMemoryLoad and gamesysMemorySave walk to
   the zero pair; the per-stage exit times; the object-info records; the save
   image itself.  The buffers are zero-initialised, so they sit in .data. */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
char stamp_str[] = "06/26/01 20:00:06";

void *gameSysMemoryFuncList[] = {
    gamesysVersionLoad,
    gamesysVersionSave,
    gflagLoad,
    gflagSave,
    gamesysObjInfoLoad,
    gamesysObjInfoSave,
    gamesysGeneratorInfoLoad,
    gamesysGeneratorInfoSave,
    gamesysCharacterInfoLoad,
    gamesysCharacterInfoSave,
    backStageLoad,
    backStageSave,
    0,
    0,
};
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
char stamp_str[] = "08/07/01 14:51:53";
#else
char stamp_str[] = "08/18/01 22:22:20";
#endif

void *gameSysMemoryFuncList[] = {
    gamesysVersionLoad,
    gamesysVersionSave,
    gflagLoad,
    gflagSave,
    gamesysObjInfoLoad,
    gamesysObjInfoSave,
    gamesysGeneratorInfoLoad,
    gamesysGeneratorInfoSave,
    gamesysCharacterInfoLoad,
    gamesysCharacterInfoSave,
    backStageLoad,
    backStageSave,
    itouGflagLoad,
    itouGflagSave,
    0,
    0,
};
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#if defined(VERSION_KOR) || defined(VERSION_CN)
char stamp_str[] = "10/23/01 17:47:13";
#else
char stamp_str[] = "10/23/01 02:02:43";
#endif
#else
char stamp_str[] = "12/12/01 17:53:37";
#endif

void *gameSysMemoryFuncList[] = {
    gamesysVersionLoad,
    gamesysVersionSave,
    gflagLoad,
    gflagSave,
    gamesysObjInfoLoad,
    gamesysObjInfoSave,
    gamesysGeneratorInfoLoad,
    gamesysGeneratorInfoSave,
    gamesysHintInfoLoad,
    gamesysHintInfoSave,
    gamesysCharacterInfoLoad,
    gamesysCharacterInfoSave,
    backStageLoad,
    backStageSave,
    itouGflagLoad,
    itouGflagSave,
    0,
    0,
};
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
int gamesysStageExitTime[104] = {0};
#else
#ifdef VERSION_JUN26
int gamesysStageExitTime[102] = {0};
#else
int gamesysStageExitTime[106] = {0};
#endif
#endif

/* the save records as gamesys keeps them, on quadword boundaries: pos and rot
   are vectors */
typedef GamesysObjInfo GamesysObjRec __attribute__((aligned(16))); /* derived name */

#ifdef VERSION_JUN26
GamesysObjRec gameSysObjInfo[122] = {0};

char gameSysMainSaveBuff[20476] = {0};
#else
GamesysObjRec gameSysObjInfo[182] = {0};

char gameSysMainSaveBuff[25596] = {0};
#endif

static inline GamesysObjInfo *gamesysObjInfoSearch(GamesysObjInfoReq *req,
                                                   int no) /* derived name */
{
    int i;

    for (i = req->start; i < req->end; i++) {
        if (gameSysObjInfo[i].no == no) {
            break;
        }
    }
    if (i == req->end) {
        return 0;
    }
    return &gameSysObjInfo[i];
}

void gamesysObjInfoInit(void)
{
    int i;

#ifdef VERSION_JUN26
    for (i = 0; i <= 121; i++) {
#else
    for (i = 0; i <= 181; i++) {
#endif
        gameSysObjInfo[i].no = 0;
        gameSysObjInfo[i].stage = 0xFFFF;
    }

#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
    memset((char *)gamesysStageExitTime, 0, 0x1A0);
#else
#ifdef VERSION_JUN26
    memset((char *)gamesysStageExitTime, 0, 412);
#else
    memset((char *)gamesysStageExitTime, 0, 0x1A8);
#endif
#endif
    backStageProcessInit();
}

/* .sdata: the frame clock the object records are stamped with, the
   stage the heroine's record was last seen in, the other-stage kidnap flag
   backStage keeps, the save-version mismatch flag and the object-buffer
   overflow flag (declared in gamesys.h, but the stage). */
int gamesysTimeCount = 0;

void gamesysObjInfoSave(GamesysMemCursor *h)
{
    char *p;
    int save;

    gamesysMemoryHandlerWrite(h, &gamesysTimeCount, 4);

    p = (char *)gameSysObjInfo;

    save = (int)(*(long long *)(p + 0x40) >> 1) & 1;
    *(long long *)(p + 0x40) = *(long long *)(p + 0x40) | 2;

#ifdef VERSION_JUN26
    gamesysMemoryHandlerWrite(h, p, 7808);
#else
    gamesysMemoryHandlerWrite(h, p, 0x2D80);
#endif

    *(long long *)(p + 0x40) = (*(long long *)(p + 0x40) & -3) | ((long long)save << 1);

#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
    gamesysMemoryHandlerWrite(h, gamesysStageExitTime, 0x1A0);
#else
#ifdef VERSION_JUN26
    gamesysMemoryHandlerWrite(h, gamesysStageExitTime, 412);
#else
    gamesysMemoryHandlerWrite(h, gamesysStageExitTime, 0x1A8);
#endif
#endif
}

void gamesysObjInfoLoad(GamesysMemCursor *h)
{
    gamesysMemoryHandlerRead(h, &gamesysTimeCount, 4);
#ifdef VERSION_JUN26
    gamesysMemoryHandlerRead(h, gameSysObjInfo, 7808);
    gamesysMemoryHandlerRead(h, gamesysStageExitTime, 412);
#else
    gamesysMemoryHandlerRead(h, gameSysObjInfo, 0x2D80);
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
    gamesysMemoryHandlerRead(h, gamesysStageExitTime, 0x1A0);
#else
    gamesysMemoryHandlerRead(h, gamesysStageExitTime, 0x1A8);
#endif
#endif
}

/* unsigned */
static unsigned short gamesysGirlStage = 0; /* derived name */

int gamesysAnotherStageTsuresari = 0;

/* gamesysObjInfoEmptyAreaSearch's body: search for an empty record, else the
 * oldest one, clear flag bit 1, return it; called after a search by number. */
static inline GamesysObjInfo *gamesysObjInfoOldestSearch(GamesysObjInfoReq *req) /* derived name */
{
    GamesysObjInfo *p;
    int i;
    int k;
    unsigned int t;

    p = gamesysObjInfoSearch(req, 0);
    if (p == 0) {
        k = -1;
        t = 0xFFFFFFFF;
        for (i = req->start; i < req->end; i++) {
            p = &gameSysObjInfo[i];
#ifdef VERSION_JUN26
            if ((unsigned int)p->time < t && req->stage != stage_no &&
                req->stage != gamesysGirlStage) {
#else
            if ((unsigned int)p->time < t && p->stage != stage_no && p->stage != gamesysGirlStage) {
#endif
                t = p->time;
                k = i;
            }
        }
        if (k < 0) {
            debug_StdPrintfDummy("gamesysObjInfoEmptyAreaSearch not area found");
            return 0;
        }
        p = &gameSysObjInfo[k];
    }
    ((GamesysObjInfoFlag *)p)->flag &= ~2;
    return p;
}

static GamesysObjInfo *gamesysObjInfoEmptyAreaSearch(GamesysObjInfoReq *req)
{
    GamesysObjInfo *p;

    p = gamesysObjInfoSearch(req, req->no);
    if (p == 0) {
        p = gamesysObjInfoOldestSearch(req);
        if (p == 0) {
            return 0;
        }
        p->no = req->no;
        p->stage = req->stage;
        p->time = gamesysTimeCount;
    }
    return p;
}

GamesysObjInfo *gamesysObjInfoBaseSet(GObj *self, int stage)
{
    GamesysObjInfoReq req;
    float dir[4];
    float m[16];
    float v[4];
    GamesysObjInfo *p;
    /* the default arm writes the range through the record pointer, every other
       arm writes the record directly */
    GamesysObjInfoReq *r = &req;

    req.no = self->labelId;
    req.stage = stage;

    switch (self->kind) {
    case 1:
        req.start = 0;
        req.end = 1;
        break;
    case 2:
        req.start = 1;
        req.end = 2;
        break;
    case 4:
        req.start = 2;
        req.end = 22;
        break;
    case 15:
        req.start = 22;
        req.end = 42;
        break;
    default:
        r->start = 42;
#ifdef VERSION_JUN26
        r->end = 122;
#else
        r->end = 182;
#endif
        break;
    }

    p = gamesysObjInfoEmptyAreaSearch(&req);
    if (p != 0 && ((int)(((GamesysObjInfoFlag *)p)->flag >> 1) & 1) == 0) {
        GetRootPosition(p->pos, self);
        _GetMotionDirection(dir, self);
        p->rot[1] =
            -((float)(int)(_GetDirection(dir) / 3.14159274f * 180.0f) * 3.14159274f / 180.0f);
        p->rot[0] = p->rot[2] = 0.0f;
#ifndef VERSION_JUN26
        if (self->kind == 0x11 && stage_no == 0xB) {
            p->rot[1] =
                (float)(int)(_GetDirection(dir) / 3.14159274f * 180.0f) * 3.14159274f / 180.0f;
        }
#endif
        if (self->kind == 0xE) {
            memset((char *)v, 0, 0x10);
            v[2] = 1.0f;
            GetRootMatrix(m, self);
            v[3] = 0.0f;
            sceVu0ApplyMatrix(v, m, v);
            p->rot[1] =
                (float)(int)(_GetDirection(v) / 3.14159274f * 180.0f) * 3.14159274f / 180.0f;
#ifndef VERSION_JUN26
            p->rot[0] = -atan2f(v[1], _Sqrt(1.0f - v[1] * v[1]));
#endif
        }
    } else {
        debug_StdPrintfDummy("gamesys: gamesysObjInfoPosSet:%d - %d \n", req.start, req.end);
    }
    return p;
}

#ifdef VERSION_NTSC
void gamesysBackStageProcess(void)
{
    if (gameSysObjInfo[1].no == 131) {
        gamesysGirlStage = gameSysObjInfo[1].stage;
    }
    gamesysTimeCount++;
    backStageProcessMain();
}
#else
void gamesysBackStageProcess(void)
{
#ifndef VERSION_JUN26
#ifdef VERSION_AUG6
    if (gameSysObjInfo[1].no == 130) {
#else
    if (gameSysObjInfo[1].no == 148) {
#endif
        gamesysGirlStage = gameSysObjInfo[1].stage;
    }
#endif
    gamesysTimeCount++;
    backStageProcessMain();
}
#endif

void gamesysMemoryHandlerWrite(GamesysMemCursor *self, void *src, int size)
{
    if (src != 0) {
        memcpy(self->base + self->offset, src, size);
    }
    self->offset += size;
    debug_StdPrintfDummy("write size %d\n", self->offset);
}

static void gamesysGeneratorInfoSave(GamesysMemCursor *self)
{
    int *buf;
    int size;

    MakeGeneratorPacket();
    buf = GetbufpGeneratorPacket();
    size = GetsizeGeneratorPacket();
    gamesysMemoryHandlerWrite(self, buf, size);
}

static void gamesysGeneratorInfoLoad(GamesysMemCursor *self)
{
    int *s1 = GetbufpGeneratorPacket();
    int s2 = GetsizeGeneratorPacket();
    if (s1 != 0) {
        memcpy(s1, self->base + self->offset, s2);
    }
    self->offset += s2;
    return ReadGeneratorPacket();
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
}

static void gamesysHintInfoSave(GamesysMemCursor *self)
{
    char *buf;
    int size;

    MakeHintSaveInfo();
    buf = GetBuffHintSaveInfo();
    size = GetSizeHintSaveInfo();
    gamesysMemoryHandlerWrite(self, buf, size);
}

static void gamesysHintInfoLoad(GamesysMemCursor *self)
{
    char *s1 = GetBuffHintSaveInfo();
    int s2 = GetSizeHintSaveInfo();
    if (s1 != 0) {
        memcpy(s1, self->base + self->offset, s2);
    }
    self->offset += s2;
    return ReadHintSaveInfo();
#endif
}

static void gamesysCharacterInfoSave(GamesysMemCursor *self)
{
    int *buf;
    int size;

    MakeCharacterPacket();
    buf = GetbufpCharacterPacket();
    size = GetsizeCharacterPacket();
    gamesysMemoryHandlerWrite(self, buf, size);
}

static void gamesysCharacterInfoLoad(GamesysMemCursor *self)
{
    int *s1 = GetbufpCharacterPacket();
    int s2 = GetsizeCharacterPacket();
    if (s1 != 0) {
        memcpy(s1, self->base + self->offset, s2);
    }
    self->offset += s2;
    return ReadCharacterPacket();
}

#ifndef VERSION_JUN26
void gamesysNObjInfoInit(void)
{
    int mask = 0xFFFF;
    char *p = (char *)gameSysObjInfo;
    int i = 0x8B;
    p += 0xA80;
    do {
        *(short *)(p + 2) = 0;
        *(short *)(p + 4) = (short)mask;
        p += 0x40;
        i--;
    } while (i >= 0);
}
#endif

void gamesysObjInfoStageInitFlagCls(void)
{
    long long mask = -2LL;
    long long *p = (long long *)gameSysObjInfo;
#ifdef VERSION_JUN26
    int i = 121;
#else
    int i = 0xB5;
#endif
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}

void gamesysObjInfoStageInitPosSaveUnlock(void)
{
    long long mask = -3LL;
    long long *p = (long long *)gameSysObjInfo;
#ifdef VERSION_JUN26
    int i = 121;
#else
    int i = 0xB5;
#endif
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}

GamesysObjInfo *gamesysObjInfoPosSetStage(GObj *self, int infoPos, int work1, int stage)
{
    GamesysObjInfo *p = gamesysObjInfoBaseSet(self, stage);
    p->work[0] = infoPos;
    p->work[1] = work1;
    return p;
}

GamesysObjInfo *gamesysObjInfoUniqDataSet(GObj *self)
{
    GamesysObjInfo *p;
    void (*fn)(int *, GObj *);
    ObjKindEnt *elem;
    int idx;

    p = gamesysObjInfoBaseSet(self, stage_no);
    idx = self->kind;
    elem = &objKindData[idx];
    fn = elem->uniqDataSet;
    if (fn != 0) {
        fn(p->work, self);
    }
    return p;
}

/* inlined into the ObjInfo functions, as gamesysObjInfoSearch is */
static inline void gamesysObjInfoReqSet(GamesysObjInfoReq *req, int no, int kind) /* derived name */
{
    req->no = no;
    req->stage = stage_no;
    switch (kind) {
    case 1:
        req->end = 1;
        req->start = 0;
        break;
    case 2:
        req->end = 2;
        req->start = 1;
        break;
    case 4:
        req->start = 2;
        req->end = 0x16;
        break;
    case 15:
        req->start = 0x16;
        req->end = 0x2A;
        break;
    default:
        req->start = 0x2A;
#ifdef VERSION_JUN26
        req->end = 122;
#else
        req->end = 0xB6;
#endif
        break;
    }
}

GamesysObjInfo *gamesysObjInfoPosNewStageSet(int no, int kind, int stage, float *pos, float *rot)
{
    GamesysObjInfoReq req;
    GamesysObjInfo *p;

    gamesysObjInfoReqSet(&req, no, kind);
    p = gamesysObjInfoEmptyAreaSearch(&req);
    if (p != 0) {
        p->pos[0] = pos[0];
        p->pos[1] = pos[1];
        p->pos[2] = pos[2];
        p->rot[0] = rot[0];
        p->rot[1] = rot[1];
        p->rot[2] = rot[2];
        p->stage = stage;
        ((GamesysObjInfoFlag *)p)->flag |= 2;
    }
    return p;
}

GamesysObjInfo *gamesysObjInfoGet(int kind, int no)
{
    GamesysObjInfoReq req;

    gamesysObjInfoReqSet(&req, no, kind);
    return gamesysObjInfoSearch(&req, no);
}

void gamesysObjInfoCls(int kind, int no)
{
    GamesysObjInfoReq req;
    GamesysObjInfo *p;

    gamesysObjInfoReqSet(&req, no, kind);
    p = gamesysObjInfoSearch(&req, no);
    if (p != 0) {
        p->no = 0;
    }
}

int gamesysGirlStageGet(void)
{
    GamesysObjInfo *girl = &gameSysObjInfo[1];

    if (girl->no)
        return girl->stage;
    return 4;
}

#ifndef VERSION_JUN26
int gamesysGetGirlStageIDAndPosition(float *pos)
{
    GamesysObjInfo *girl = &gameSysObjInfo[1];

    if (girl->no != 0) {
        CopyVector(pos, girl->pos);
        return girl->stage;
    }
    CopyVector(pos, ZeroPoint);
    return 4;
}
#endif

void gamesysStageExitTimeSet(int stage)
{
    gamesysStageExitTime[stage] = gamesysTimeCount;
}

void gamesysMemoryHandlerRead(GamesysMemCursor *self, void *dst, int size)
{
    if (dst != 0) {
        memcpy(dst, self->base + self->offset, size);
    }
    self->offset = self->offset + size;
}

/* The same table gamesysMemoryLoad walks (both are called with gameSysMemoryFuncList):
   each entry is a load handler and a save handler. */
void gamesysMemorySave(void **tbl, void *mem, void *arg)
{
    GamesysMemCursor cur;
    cur.base = mem;
    cur.offset = 0;
    while (tbl[1] != 0) {
        ((void (*)(void *, void *))tbl[1])(&cur, arg);
        tbl += 2;
    }
}

void gamesysMemoryLoad(void **tbl, void *mem, void *arg)
{
    GamesysMemCursor cur;
    cur.base = mem;
    cur.offset = 0;
    while (tbl[0] != 0) {
        ((void (*)(void *, void *))tbl[0])(&cur, arg);
        tbl += 2;
    }
#ifdef VERSION_NTSC
    gflagOn(361);
#else
#ifdef VERSION_AUG6
    gflagOn(360);
#else
#ifdef VERSION_JUN26
    gflagOn(343);
#else
    gflagOn(394);
#endif
#endif
#endif
}

int gamesysVersionDiff = 0;

int gamesysObjBuffOver = 0;

static void gamesysVersionLoad(GamesysMemCursor *self)
{
    char buf[32];
    gamesysMemoryHandlerRead(self, buf, 18);
    if (strcmp(stamp_str, buf) != 0) {
        gamesysVersionDiff = 1;
    } else {
        gamesysVersionDiff = 0;
    }
}

static void gamesysVersionSave(GamesysMemCursor *self)
{
    if (gamesysVersionDiff == 0) {
        gamesysMemoryHandlerWrite(self, stamp_str, 18);
        return;
    }
    {
        char buf[32];
        memset(buf, 0, 18);
        gamesysMemoryHandlerWrite(self, buf, 18);
    }
}
