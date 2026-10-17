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
#include "include_asm.h"

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
static void gamesysCharacterInfoLoad(GamesysMemCursor *self);
static void gamesysCharacterInfoSave(GamesysMemCursor *self);

/* .data: the build stamp written into the save area and compared against
   the one the card holds; the save area's handler table, a load and a save
   handler per record, which gamesysMemoryLoad and gamesysMemorySave walk to
   the zero pair; the per-stage exit times; the object-info records; the save
   image itself.  The buffers are zero-initialised, so they sit in .data. */
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

int gamesysStageExitTime[102] = {0};

/* the save records as gamesys keeps them, on quadword boundaries: pos and rot
   are vectors */
typedef GamesysObjInfo GamesysObjRec __attribute__((aligned(16))); /* derived name */

GamesysObjRec gameSysObjInfo[122] = {0};

char gameSysMainSaveBuff[20476] = {0};

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

INCLUDE_ASM(gamesysObjInfoInit);

/* .sdata: the frame clock the object records are stamped with, the
   stage the heroine's record was last seen in, the other-stage kidnap flag
   backStage keeps, the save-version mismatch flag and the object-buffer
   overflow flag (declared in gamesys.h, but the stage). */
int gamesysTimeCount = 0;

INCLUDE_ASM(gamesysObjInfoSave);

INCLUDE_ASM(gamesysObjInfoLoad);

/* unsigned */
static unsigned short gamesysGirlStage = 0; /* derived name */

int gamesysAnotherStageTsuresari = 0;

/* gamesysObjInfoEmptyAreaSearch is a stub, and with it the inline search its
   body was built on (PAL's); that helper's message is the stub's string. */
INCLUDE_ASM(gamesysObjInfoEmptyAreaSearch);

GamesysObjInfo *gamesysObjInfoBaseSet(GObj *self, int stage);

INCLUDE_ASM(gamesysObjInfoBaseSet);

INCLUDE_ASM(gamesysBackStageProcess);

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

INCLUDE_ASM(gamesysObjInfoStageInitFlagCls);

INCLUDE_ASM(gamesysObjInfoStageInitPosSaveUnlock);

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
        req->end = 0xB6;
        break;
    }
}

INCLUDE_ASM(gamesysObjInfoPosNewStageSet);

INCLUDE_ASM(gamesysObjInfoGet);

INCLUDE_ASM(gamesysObjInfoCls);

int gamesysGirlStageGet(void)
{
    GamesysObjInfo *girl = &gameSysObjInfo[1];

    if (girl->no)
        return girl->stage;
    return 4;
}

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

INCLUDE_ASM(gamesysMemoryLoad);

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
