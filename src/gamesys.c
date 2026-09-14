#include "common.h"

typedef void (*func_001AE8F0_FnPtr)(int *buf, int a2);

typedef struct {
    int start;
    int end;
    int no;
    int stage;
} GamesysObjInfoReq;

typedef struct {
    short flag;
    unsigned short no;
    unsigned short stage;
    short pad06;
    int time;
    int uniq;
    float pos[3];
    float pad1C;
    float rot[3];
    float pad2C;
    int work[4];
} GamesysObjInfo;

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

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoInit);

extern char D_004DA980[];
extern int D_004DA7D0[];
extern int gamesysTimeCount;
extern void func_001B6CA0();

void gamesysObjInfoSave(void *h)
{
    char *p;
    int save;

    func_001B6CA0(h, &gamesysTimeCount, 4);

    p = D_004DA980;

    save = (int)(*(long long *)(p + 0x40) >> 1) & 1;
    *(long long *)(p + 0x40) = *(long long *)(p + 0x40) | 2;

    func_001B6CA0(h, p, 0x2D80);

    *(long long *)(p + 0x40) = (*(long long *)(p + 0x40) & -3) | ((long long)save << 1);

    func_001B6CA0(h, D_004DA7D0, 0x1A8);
}

extern char D_004DA980[];
extern int D_004DA7D0[];
extern int gamesysTimeCount;

void gamesysObjInfoLoad(void *h)
{
    gamesysMemoryHandlerRead(h, &gamesysTimeCount, 4);
    gamesysMemoryHandlerRead(h, D_004DA980, 0x2D80);
    gamesysMemoryHandlerRead(h, D_004DA7D0, 0x1A8);
}

INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoEmptyAreaSearch);
INCLUDE_ASM("asm/nonmatchings/src/gamesys", gamesysObjInfoBaseSet);

extern char D_004DA980[];
extern short D_0063B418;
extern int gamesysTimeCount;

void gamesysBackStageProcess(void)
{
    unsigned short *h = (unsigned short *)D_004DA980;
    if (h[0x21] == 0x94) {
        D_0063B418 = h[0x22];
    }
    gamesysTimeCount++;
    backStageProcessMain();
}

extern char D_0061D328[];
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void memcpy();

void func_001B6CA0(int *self, int n, int a2)
{
    if (n != 0) {
        memcpy(self[0] + self[1], n);
    }
    self[1] += a2;
    debug_StdPrintfDummy(D_0061D328, self[1]);
}

extern void MakeGeneratorPacket(void);

void func_001B6CF8(int *self)
{
    int buf;
    int size;

    MakeGeneratorPacket();
    buf = GetbufpGeneratorPacket();
    size = GetsizeGeneratorPacket();
    func_001B6CA0(self, buf, size);
}

extern int *GetbufpGeneratorPacket(void);
extern int GetsizeGeneratorPacket(void);
extern int ReadGeneratorPacket();

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

extern void MakeHintSaveInfo(void);

void func_001B6DA8(int *self)
{
    int buf;
    int size;

    MakeHintSaveInfo();
    buf = GetBuffHintSaveInfo();
    size = GetSizeHintSaveInfo();
    func_001B6CA0(self, buf, size);
}

extern int *GetBuffHintSaveInfo(void);
extern int GetSizeHintSaveInfo(void);
extern int ReadHintSaveInfo();

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

extern void MakeCharacterPacket(void);

void func_001B6E58(int *self)
{
    int buf;
    int size;

    MakeCharacterPacket();
    buf = GetbufpCharacterPacket();
    size = GetsizeCharacterPacket();
    func_001B6CA0(self, buf, size);
}

extern int *GetbufpCharacterPacket(void);
extern int GetsizeCharacterPacket(void);
extern int ReadCharacterPacket();

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

extern char D_004DA980[];

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

extern int *gamesysObjInfoBaseSet(int *self, int a1);

int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3)
{
    int *p = gamesysObjInfoBaseSet(self, a3);
    p[0xC] = a1;
    p[0xD] = a2;
    return p;
}

extern char D_002C1270[];
extern int stage_no;

int *gamesysObjInfoUniqDataSet(int a0)
{
    int *p;
    void (*fn)(int *, int);
    char *elem;
    int idx;

    p = gamesysObjInfoBaseSet((int *)a0, stage_no);
    idx = *(int *)((char *)a0 + 0xC);
    elem = D_002C1270 + idx * 0x64;
    fn = *(void (**)(int *, int))(elem + 0x3C);
    if (fn != 0) {
        fn(p + 12, a0);
    }
    return p;
}

extern int stage_no;
extern GamesysObjInfo *gamesysObjInfoEmptyAreaSearch(GamesysObjInfoReq *req);

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

extern void CopyVector(void *dst, void *src);
extern int D_0028FF00[4];

int gamesysGetGirlStageIDAndPosition(int a0)
{
    if (D_004DA9C0[1] != 0) {
        CopyVector(a0, (int *)((char *)D_004DA9C0 + 0x10));
        return D_004DA9C0[2];
    }
    CopyVector(a0, (int *)D_0028FF00);
    return 4;
}

extern int D_004DA7D0[];
extern int gamesysTimeCount;

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

extern void gflagOn(int a0);

void gamesysMemoryLoad(void **tbl, int a1, void *a2)
{
    int buf[2];
    buf[0] = a1;
    buf[1] = 0;
    while (tbl[0] != 0) {
        ((void (*)(void *, void *))tbl[0])(buf, a2);
        tbl += 2;
    }
    gflagOn(0x18A);
}

extern int D_004DA770[];
extern int gamesysVersionDiff;
extern int strcmp(int *p, int *buf);

void gamesysVersionLoad(int *self)
{
    int buf[8];
    gamesysMemoryHandlerRead(self, buf, 0x12);
    if (strcmp(D_004DA770, buf) != 0) {
        gamesysVersionDiff = 1;
    } else {
        gamesysVersionDiff = 0;
    }
}

extern void memset(char *p, int a, int n);

void gamesysVersionSave(int a0)
{
    if (gamesysVersionDiff == 0) {
        func_001B6CA0((int *)a0, (int)D_004DA770, 0x12);
        return;
    }
    {
        char buf[0x20];
        memset(buf, 0, 0x12);
        func_001B6CA0((int *)a0, (int)buf, 0x12);
    }
}
