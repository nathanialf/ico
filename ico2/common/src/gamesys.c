#include "typedef.h"
#include "backStage.h"
#include "debug.h"
#include "boyact.h"
#include "generator.h"
#include "gv.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "itou_gflag.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <math.h>
#include "Matrix.h"
#include "gamesys.h"
#include <string.h>
#include "main.h"

typedef struct {
    int start;
    int end;
    int no;
    int stage;
} GamesysObjInfoReq;

typedef union {
    long long flag;
    GamesysObjInfo info;
} GamesysObjInfoFlag;

void gamesysVersionLoad(int *self);
void gamesysVersionSave(int a0);
void gamesysObjInfoLoad(void *h);
void gamesysObjInfoSave(void *h);
void gamesysGeneratorInfoLoad(int *a0);
void gamesysGeneratorInfoSave(int *self);
void gamesysHintInfoLoad(int *a0);
void gamesysHintInfoSave(int *self);
void gamesysCharacterInfoLoad(int *a0);
void gamesysCharacterInfoSave(int *self);

/* .data, owned by gamesys.o in MAIN.MAP's order (all five are the map's
   globals): the build stamp written into the save area and compared against
   the one the card holds; the save area's handler table, a load and a save
   handler per record, which gamesysMemoryLoad and gamesysMemorySave walk to
   the zero pair; the per-stage exit times; the object-info records; the save
   image itself.  The buffers are zero-initialised, so they sit in .data. */
char stamp_str[] = "12/12/01 17:53:37";

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

int gamesysStageExitTime[106] = {0};

/* the save records as gamesys keeps them, on quadword boundaries: pos and rot
   are vectors */
typedef GamesysObjInfo GamesysObjRec __attribute__((aligned(16))); /* derived name */

GamesysObjRec gameSysObjInfo[182] = {0};

char gameSysMainSaveBuff[25596] = {0};

static inline GamesysObjInfo *gamesysObjInfoSearch(GamesysObjInfoReq *req, int no)
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

    for (i = 0; i <= 181; i++) {
        gameSysObjInfo[i].no = 0;
        gameSysObjInfo[i].stage = 0xFFFF;
    }

    memset((char *)gamesysStageExitTime, 0, 0x1A8);
    backStageProcessInit();
}

/* .sdata, owned by gamesys.o (VMA 0x63B414..0x63B428, 0x14 B = MAIN.MAP), in
   the ROM's order: the frame clock the object records are stamped with, the
   stage the heroine's record was last seen in, the other-stage kidnap flag
   backStage keeps, the save-version mismatch flag and the object-buffer
   overflow flag (MAIN.MAP globals, declared in gamesys.h, but the stage). */
int gamesysTimeCount = 0;

void gamesysObjInfoSave(void *h)
{
    char *p;
    int save;

    gamesysMemoryHandlerWrite(h, &gamesysTimeCount, 4);

    p = (char *)gameSysObjInfo;

    save = (int)(*(long long *)(p + 0x40) >> 1) & 1;
    *(long long *)(p + 0x40) = *(long long *)(p + 0x40) | 2;

    gamesysMemoryHandlerWrite(h, p, 0x2D80);

    *(long long *)(p + 0x40) = (*(long long *)(p + 0x40) & -3) | ((long long)save << 1);

    gamesysMemoryHandlerWrite(h, gamesysStageExitTime, 0x1A8);
}

void gamesysObjInfoLoad(void *h)
{
    gamesysMemoryHandlerRead(h, &gamesysTimeCount, 4);
    gamesysMemoryHandlerRead(h, gameSysObjInfo, 0x2D80);
    gamesysMemoryHandlerRead(h, gamesysStageExitTime, 0x1A8);
}

/* unsigned: the ROM reads it with lhu (0x1B6928). */
static unsigned short gamesysGirlStage = 0; /* derived name */

int gamesysAnotherStageTsuresari = 0;

/* RECONSTRUCTION: the January listing's whole gamesysObjInfoEmptyAreaSearch
 * (gamesys.c:356-413: search for an empty record, else the oldest one, clear
 * flag bit 1, return it).  The retail function calls it after a search by
 * number, and its two exits are the ones an inlined return leaves in the ROM
 * (the k < 0 arm's `move $5,$0` then the caller's test at 0x1B6988, and the
 * copy at 0x1B697C).  The ROM carries no name for it; this one is descriptive. */
static inline GamesysObjInfo *gamesysObjInfoOldestSearch(GamesysObjInfoReq *req)
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
            if ((unsigned int)p->time < t && p->stage != stage_no && p->stage != gamesysGirlStage) {
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

GamesysObjInfo *gamesysObjInfoEmptyAreaSearch(GamesysObjInfoReq *req)
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

extern GamesysObjInfo *gamesysObjInfoEmptyAreaSearch(GamesysObjInfoReq *req);

int *gamesysObjInfoBaseSet(int *self, int stage)
{
    GamesysObjInfoReq req;
    float dir[4];
    float m[16];
    float v[4];
    GamesysObjInfo *p;
    /* the default arm writes the range through the record pointer, every other
       arm writes the record directly: the ROM keeps the two spellings apart as
       `daddu $6, $29, $0` plus `sw $2, 0x4($6)` / `sw $3, 0x0($6)` against the
       other arms' plain `sw $2, 0x0($29)` / `sw $3, 0x4($29)` */
    GamesysObjInfoReq *r = &req;

    req.no = self[2];
    req.stage = stage;

    switch (self[3]) {
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
        r->end = 182;
        break;
    }

    p = gamesysObjInfoEmptyAreaSearch(&req);
    if (p != 0 && ((int)(((GamesysObjInfoFlag *)p)->flag >> 1) & 1) == 0) {
        GetRootPosition(p->pos, self);
        _GetMotionDirection(dir, self);
        p->rot[1] =
            -((float)(int)(_GetDirection(dir) / 3.14159274f * 180.0f) * 3.14159274f / 180.0f);
        p->rot[0] = p->rot[2] = 0.0f;
        if (self[3] == 0x11 && stage_no == 0xB) {
            p->rot[1] =
                (float)(int)(_GetDirection(dir) / 3.14159274f * 180.0f) * 3.14159274f / 180.0f;
        }
        if (self[3] == 0xE) {
            memset((char *)v, 0, 0x10);
            v[2] = 1.0f;
            GetRootMatrix(m, self);
            v[3] = 0.0f;
            sceVu0ApplyMatrix(v, m, v);
            p->rot[1] =
                (float)(int)(_GetDirection(v) / 3.14159274f * 180.0f) * 3.14159274f / 180.0f;
            p->rot[0] = -atan2f(v[1], _Sqrt(1.0f - v[1] * v[1]));
        }
    } else {
        debug_StdPrintfDummy("gamesys: gamesysObjInfoPosSet:%d - %d \n", req.start, req.end);
    }
    return (int *)p;
}

void gamesysBackStageProcess(void)
{
    if (gameSysObjInfo[1].no == 148) {
        gamesysGirlStage = gameSysObjInfo[1].stage;
    }
    gamesysTimeCount++;
    backStageProcessMain();
}

/* kept local: declaring it only through string.h moves this TU's bytes */
extern void memcpy();

void gamesysMemoryHandlerWrite(int *self, void *src, int size)
{
    if (src != 0) {
        memcpy(self[0] + self[1], src);
    }
    self[1] += size;
    debug_StdPrintfDummy("write size %d\n", self[1]);
}

void gamesysGeneratorInfoSave(int *self)
{
    int *buf;
    int size;

    MakeGeneratorPacket();
    buf = GetbufpGeneratorPacket();
    size = GetsizeGeneratorPacket();
    gamesysMemoryHandlerWrite(self, buf, size);
}

void gamesysGeneratorInfoLoad(int *a0)
{
    int *s1 = GetbufpGeneratorPacket();
    int s2 = GetsizeGeneratorPacket();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadGeneratorPacket();
}

void gamesysHintInfoSave(int *self)
{
    char *buf;
    int size;

    MakeHintSaveInfo();
    buf = GetBuffHintSaveInfo();
    size = GetSizeHintSaveInfo();
    gamesysMemoryHandlerWrite(self, buf, size);
}

void gamesysHintInfoLoad(int *a0)
{
    char *s1 = GetBuffHintSaveInfo();
    int s2 = GetSizeHintSaveInfo();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadHintSaveInfo();
}

void gamesysCharacterInfoSave(int *self)
{
    int *buf;
    int size;

    MakeCharacterPacket();
    buf = GetbufpCharacterPacket();
    size = GetsizeCharacterPacket();
    gamesysMemoryHandlerWrite(self, buf, size);
}

void gamesysCharacterInfoLoad(int *a0)
{
    int *s1 = GetbufpCharacterPacket();
    int s2 = GetsizeCharacterPacket();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadCharacterPacket();
}

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

void gamesysObjInfoStageInitFlagCls(void)
{
    long long mask = -2LL;
    long long *p = (long long *)gameSysObjInfo;
    int i = 0xB5;
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
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}

int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3)
{
    int *p = gamesysObjInfoBaseSet(self, a3);
    ((GamesysObjInfo *)p)->work[0] = a1;
    ((GamesysObjInfo *)p)->work[1] = a2;
    return p;
}

extern ObjKindEnt objKindData[];

int *gamesysObjInfoUniqDataSet(int a0)
{
    int *p;
    void (*fn)(int *, int);
    ObjKindEnt *elem;
    int idx;

    p = gamesysObjInfoBaseSet((int *)a0, stage_no);
    idx = ((GObj *)a0)->kind;
    elem = (ObjKindEnt *)((char *)objKindData + idx * 0x64);
    fn = elem->uniqDataSet;
    if (fn != 0) {
        fn(p + 12, a0);
    }
    return p;
}

/* Two static helpers the listing inlines into the ObjInfo functions (lines
 * 426-456 and 350-364); neither is emitted out of line, so neither has a
 * MAIN.MAP name and both names here are ours. */
static inline void gamesysObjInfoReqSet(GamesysObjInfoReq *req, int no, int kind)
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
        req->end = 0xB6;
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

int gamesysGetGirlStageIDAndPosition(int *pos)
{
    GamesysObjInfo *girl = &gameSysObjInfo[1];

    if (girl->no != 0) {
        CopyVector(pos, (int *)girl->pos);
        return girl->stage;
    }
    CopyVector(pos, (int *)ZeroPoint);
    return 4;
}

void gamesysStageExitTimeSet(int a0)
{
    gamesysStageExitTime[a0] = gamesysTimeCount;
}

void gamesysMemoryHandlerRead(int *self, void *dst, int size)
{
    if (dst != 0) {
        memcpy(dst, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + size;
}

/* The same table gamesysMemoryLoad walks (both are called with gameSysMemoryFuncList):
   each entry is a load handler and a save handler. */
void gamesysMemorySave(void **tbl, void *a1, void *a2)
{
    int buf[2];
    buf[0] = a1;
    buf[1] = 0;
    while (tbl[1] != 0) {
        ((void (*)(void *, void *))tbl[1])(buf, a2);
        tbl += 2;
    }
}

void gamesysMemoryLoad(void **tbl, void *a1, void *a2)
{
    int buf[2];
    buf[0] = a1;
    buf[1] = 0;
    while (tbl[0] != 0) {
        ((void (*)(void *, void *))tbl[0])(buf, a2);
        tbl += 2;
    }
    gflagOn(394);
}

int gamesysVersionDiff = 0;

int gamesysObjBuffOver = 0;

void gamesysVersionLoad(int *self)
{
    int buf[8];
    gamesysMemoryHandlerRead(self, buf, 18);
    if (strcmp(stamp_str, buf) != 0) {
        gamesysVersionDiff = 1;
    } else {
        gamesysVersionDiff = 0;
    }
}

void gamesysVersionSave(int a0)
{
    if (gamesysVersionDiff == 0) {
        gamesysMemoryHandlerWrite((int *)a0, stamp_str, 18);
        return;
    }
    {
        char buf[32];
        memset(buf, 0, 18);
        gamesysMemoryHandlerWrite((int *)a0, buf, 18);
    }
}
