#include "common.h"
#include "typedef.h"
#include "backStage.h"
#include "debug.h"
#include "boyact.h"
#include "generator.h"
#include "gv.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <math.h>

typedef void (*func_001AE8F0_FnPtr)(int *buf, int a2);

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

extern char D_004DA980[];
extern int stage_no;

static inline GamesysObjInfo *gamesysObjInfoSearch(GamesysObjInfoReq *req, int no)
{
    int i;

    for (i = req->start; i < req->end; i++) {
        if (((GamesysObjInfo *)D_004DA980)[i].no == no) {
            break;
        }
    }
    if (i == req->end) {
        return 0;
    }
    return &((GamesysObjInfo *)D_004DA980)[i];
}

extern int D_004DA7D0[];
extern void memset(char *p, int a, int n);

void gamesysObjInfoInit(void)
{
    int i;

    for (i = 0; i <= 181; i++) {
        ((GamesysObjInfo *)D_004DA980)[i].no = 0;
        ((GamesysObjInfo *)D_004DA980)[i].stage = 0xFFFF;
    }

    memset((char *)D_004DA7D0, 0, 0x1A8);
    backStageProcessInit();
}

extern int gamesysTimeCount;
/* kept local: this TU's uses of gamesysMemoryHandlerWrite do not fit the prototype in gamesys.h */
extern void gamesysMemoryHandlerWrite();

void gamesysObjInfoSave(void *h)
{
    char *p;
    int save;

    gamesysMemoryHandlerWrite(h, &gamesysTimeCount, 4);

    p = D_004DA980;

    save = (int)(*(long long *)(p + 0x40) >> 1) & 1;
    *(long long *)(p + 0x40) = *(long long *)(p + 0x40) | 2;

    gamesysMemoryHandlerWrite(h, p, 0x2D80);

    *(long long *)(p + 0x40) = (*(long long *)(p + 0x40) & -3) | ((long long)save << 1);

    gamesysMemoryHandlerWrite(h, D_004DA7D0, 0x1A8);
}

void gamesysObjInfoLoad(void *h)
{
    gamesysMemoryHandlerRead(h, &gamesysTimeCount, 4);
    gamesysMemoryHandlerRead(h, D_004DA980, 0x2D80);
    gamesysMemoryHandlerRead(h, D_004DA7D0, 0x1A8);
}

/* unsigned: the ROM reads it with lhu (0x1B6928). */
extern unsigned short D_0063B418;

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
            p = &((GamesysObjInfo *)D_004DA980)[i];
            if ((unsigned int)p->time < t && p->stage != stage_no && p->stage != D_0063B418) {
                t = p->time;
                k = i;
            }
        }
        if (k < 0) {
            debug_StdPrintfDummy("gamesysObjInfoEmptyAreaSearch not area found");
            return 0;
        }
        p = &((GamesysObjInfo *)D_004DA980)[k];
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
/* kept local: this TU's uses of _Sqrt do not fit the prototype in Matrix.h */
extern float _Sqrt(float x);

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
    unsigned short *h = (unsigned short *)D_004DA980;
    if (h[0x21] == 0x94) {
        D_0063B418 = h[0x22];
    }
    gamesysTimeCount++;
    backStageProcessMain();
}

extern void memcpy();

void gamesysMemoryHandlerWrite(int *self, int n, int a2)
{
    if (n != 0) {
        memcpy(self[0] + self[1], n);
    }
    self[1] += a2;
    debug_StdPrintfDummy("write size %d\n", self[1]);
}

void gamesysGeneratorInfoSave(int *self)
{
    int buf;
    int size;

    MakeGeneratorPacket();
    buf = GetbufpGeneratorPacket();
    size = GetsizeGeneratorPacket();
    gamesysMemoryHandlerWrite(self, buf, size);
}

void gamesysGeneratorInfoLoad(int *a0)
{
    int s1 = GetbufpGeneratorPacket();
    int s2 = GetsizeGeneratorPacket();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadGeneratorPacket();
}

void gamesysHintInfoSave(int *self)
{
    int buf;
    int size;

    MakeHintSaveInfo();
    buf = GetBuffHintSaveInfo();
    size = GetSizeHintSaveInfo();
    gamesysMemoryHandlerWrite(self, buf, size);
}

void gamesysHintInfoLoad(int *a0)
{
    int s1 = GetBuffHintSaveInfo();
    int s2 = GetSizeHintSaveInfo();
    if (s1 != 0) {
        memcpy(s1, a0[0] + a0[1], s2);
    }
    a0[1] += s2;
    return ReadHintSaveInfo();
}

void gamesysCharacterInfoSave(int *self)
{
    int buf;
    int size;

    MakeCharacterPacket();
    buf = GetbufpCharacterPacket();
    size = GetsizeCharacterPacket();
    gamesysMemoryHandlerWrite(self, buf, size);
}

void gamesysCharacterInfoLoad(int *a0)
{
    int s1 = GetbufpCharacterPacket();
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
    char *p = D_004DA980;
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
    long long *p = (long long *)D_004DA980;
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
    long long *p = (long long *)D_004DA980;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}

/* kept local: this TU's uses of gamesysObjInfoBaseSet do not fit the prototype in gamesys.h */
extern int *gamesysObjInfoBaseSet(int *self, int a1);

int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3)
{
    int *p = gamesysObjInfoBaseSet(self, a3);
    p[0xC] = a1;
    p[0xD] = a2;
    return p;
}

extern ObjKindEnt D_002C1270[];

int *gamesysObjInfoUniqDataSet(int a0)
{
    int *p;
    void (*fn)(int *, int);
    ObjKindEnt *elem;
    int idx;

    p = gamesysObjInfoBaseSet((int *)a0, stage_no);
    idx = ((PObjGObj *)a0)->kind;
    elem = (ObjKindEnt *)((char *)D_002C1270 + idx * 0x64);
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

extern unsigned short D_004DA9C0[];

int gamesysGirlStageGet(void)
{
    if (D_004DA9C0[1])
        return D_004DA9C0[2];
    return 4;
}

int gamesysGetGirlStageIDAndPosition(int a0)
{
    if (D_004DA9C0[1] != 0) {
        CopyVector(a0, (int *)((char *)D_004DA9C0 + 0x10));
        return D_004DA9C0[2];
    }
    CopyVector(a0, (int *)ZeroPoint);
    return 4;
}

void gamesysStageExitTimeSet(int a0)
{
    D_004DA7D0[a0] = gamesysTimeCount;
}

void gamesysMemoryHandlerRead(int *self, int a1, int a2)
{
    if (a1 != 0) {
        memcpy(a1, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + a2;
}

void gamesysMemorySave(int *self, int a1, int a2)
{
    func_001AE8F0_FnPtr new_var;
    int buf[2];
    int new_var2;
    func_001AE8F0_FnPtr fn;
    buf[0] = a1;
    buf[1] = 0;
    fn = (func_001AE8F0_FnPtr)self[1];
    new_var2 = fn != 0;
    if (new_var2) {
        do {
            fn(buf, a2);
            self += 2;
            new_var2 = self[1];
            new_var = (func_001AE8F0_FnPtr)new_var2;
            fn = new_var;
        } while (new_var2);
    }
}

void gamesysMemoryLoad(void **tbl, int a1, void *a2)
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

/* .data, owned by gamesys.o and read only here: the build stamp written into
   the save area, compared against the one the card holds. */
static char gamesysVersion[] = "12/12/01 17:53:37";

extern int gamesysVersionDiff;
extern int strcmp(int *p, int *buf);

void gamesysVersionLoad(int *self)
{
    int buf[8];
    gamesysMemoryHandlerRead(self, buf, 18);
    if (strcmp((int *)gamesysVersion, buf) != 0) {
        gamesysVersionDiff = 1;
    } else {
        gamesysVersionDiff = 0;
    }
}

void gamesysVersionSave(int a0)
{
    if (gamesysVersionDiff == 0) {
        gamesysMemoryHandlerWrite((int *)a0, (int)gamesysVersion, 18);
        return;
    }
    {
        char buf[0x20];
        memset(buf, 0, 18);
        gamesysMemoryHandlerWrite((int *)a0, (int)buf, 18);
    }
}
