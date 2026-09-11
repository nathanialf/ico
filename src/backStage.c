#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
extern int D_0063ACF0;
extern int D_0063C350;
extern int D_0063C354;
extern int D_0063C358;
extern int D_0063C35C;
extern int D_0063C360;
extern int D_0063C364;
extern int D_0063C368;
extern int D_0063C36C;
extern int func_001B6CA0(void *, void *, int);
extern int gamesysMemoryHandlerRead(void *, void *, int);
extern int D_0063C370;

/* --- su-b sweep decls --- */
typedef union {
    float f[4];
    long long q[2];
} Vec16;

/* the 0x40-byte gamesys object-info record (src/gamesys.c GamesysObjInfo) */
typedef struct {
    short flag;           /* 0x00 */
    unsigned short no;    /* 0x02 */
    unsigned short stage; /* 0x04 */
    short pad06;          /* 0x06 */
    int time;             /* 0x08 */
    int uniq;             /* 0x0C */
    Vec16 pos;            /* 0x10 */
    Vec16 rot;            /* 0x20 */
    int work[4];          /* 0x30 */
} GamesysObjInfo;

/* the 0x4C-byte generator-geometry record (src/ebrain.c GenGeo) */
typedef struct {
    float scale[3]; /* 0x00 */
    float rot[3];   /* 0x0C */
    char pad18[0x4C - 0x18];
} GenGeoRec;

extern GamesysObjInfo D_004DA980[];
extern GenGeoRec D_002C2DC8[];
extern float D_006FACF0[4];
extern int gamesysAnotherStageTsuresari;
extern int D_0063B60C;
extern int stage_no;
extern int D_0063C374;
extern char D_00619238[];
extern int gflagChk(int flag);
extern void sceVu0CopyVector(void *dst, void *src);
extern void *memset(void *p, int c, int n);
extern GamesysObjInfo *gamesysObjInfoPosNewStageSet(int no, int kind, int stage, float *pos,
                                                    float *rot);
extern void SetInfoSpKidnapGenerator(int *work);
extern void SetInfoSpKidnapEnemy(int *work);
extern int CameraGetMode(void);
extern void SetStatusBoy_OtherStageGirlPinch(void);
extern int eBrainGetTargetGeneratorFromLabel(int label);
extern void RequestStageChangeKidnapEnd(int stage, int gen);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char D_00619260[];
extern char D_00619270[];
extern char D_00619290[];
extern char D_006192A8[];
extern float WayLengthOfGObj_GObj(int gobj0, int gobj1);
extern int NumOfWpPos(void);
extern void CopyWpPos(float *out, int i, int j);
extern void sceVu0SubVector(float *dst, float *a, float *b);
extern float _InnerProduct(float *a, float *b);
extern float FSqrt(float x);

inline void backStageProcessInit(void)
{
    D_0063ACF0 = 0;
    D_0063C35C = -1;
    D_0063C350 = 0;
    D_0063C370 = 0;
}

inline void backStageDebugTimeZero(void)
{
    D_0063C354 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessOutStage);

void backStageProcessMain(void)
{
    Vec16 pos;
    Vec16 rot;
    Vec16 tmp;
    GamesysObjInfo *g1;
    GamesysObjInfo *g2;

    gamesysAnotherStageTsuresari = 0;
    if (gflagChk(0x186) != 0) {
        return;
    }
    if (D_0063B60C != 0x36) {
        return;
    }
    if (stage_no == D_004DA980[1].stage) {
        return;
    }
    switch (D_0063C350) {
    case 1:
        if (D_0063C354-- < 0) {
            D_0063C350 = 2;
            if (D_0063C374 == 0) {
                GamesysObjInfo *s = &D_004DA980[D_0063C35C];
                sceVu0CopyVector(&s->pos, &D_004DA980[1].pos);
                s->work[0] = 4;
            } else {
                memset(&tmp, 0, sizeof(tmp));
                tmp.f[0] = D_002C2DC8[0xEAE].rot[0];
                tmp.f[1] = D_002C2DC8[0xEAE].rot[1];
                tmp.f[2] = D_002C2DC8[0xEAE].rot[2];
                rot = tmp;
                g1 = gamesysObjInfoPosNewStageSet(0xEAD, 4, D_004DA980[1].stage,
                                                  D_004DA980[1].pos.f, D_004DA980[1].rot.f);
                D_0063C35C = (unsigned int)((char *)g1 - (char *)D_004DA980) >> 6;
                pos.f[0] = D_006FACF0[0];
                pos.f[2] = D_006FACF0[2];
                pos.f[1] = D_006FACF0[1] - 10.0f;
                g2 = gamesysObjInfoPosNewStageSet(0xEAE, 0x21, D_004DA980[1].stage, pos.f, rot.f);
                SetInfoSpKidnapGenerator(g2->work);
                SetInfoSpKidnapEnemy(g1->work);
                if (g1 != 0 && g2 != 0) {
                    g1->work[0] = 4;
                } else {
                    debug_StdPrintfDummy(D_00619238);
                    D_0063C350 = 1;
                }
            }
        }
        break;
    case 2:
        if (CameraGetMode() != 4) {
            if (D_0063C370 == 0) {
                SetStatusBoy_OtherStageGirlPinch();
                D_0063C370 = 1;
            }
            gamesysAnotherStageTsuresari = 1;
            if (D_0063C358-- < 0) {
                int st = D_004DA980[1].stage;
                RequestStageChangeKidnapEnd(
                    st, eBrainGetTargetGeneratorFromLabel(D_004DA980[D_0063C35C].no));
            }
        }
        break;
    }
}

void routeSetPos(int gobj0, int gobj1, float *out, float ratio)
{
    Vec16 p0;
    Vec16 cur;
    Vec16 prev;
    Vec16 d;
    float len;
    float target;
    float sum;
    int i;
    int n;

    len = WayLengthOfGObj_GObj(gobj0, gobj1);
    GetRootPosition(p0.f, gobj0);
    if (1.0f <= ratio) {
        GetRootPosition(out, gobj1);
        return;
    }
    n = NumOfWpPos();
    if (n != 0) {
        sum = 0.0f;
        memset(&prev, 0, sizeof(prev));
        target = len * ratio;
        debug_StdPrintfDummy(D_00619260, n);
        for (i = 0; i < n; i++) {
            CopyWpPos(cur.f, i, i);
            if (i == 0) {
                sum = 0.0f;
            } else {
                sceVu0SubVector(d.f, prev.f, cur.f);
                sum += FSqrt(_InnerProduct(d.f, d.f));
            }
            debug_StdPrintfDummy(D_00619270, i, n, target, sum);
            if (target < sum) {
                break;
            }
            sceVu0CopyVector(prev.f, cur.f);
        }
        if (i != 0) {
            i--;
        }
        CopyWpPos(cur.f, i, i);
        sceVu0CopyVector(out, cur.f);
        debug_StdPrintfDummy(D_00619290, out[0], out[1], out[2]);
    } else {
        debug_StdPrintfDummy(D_006192A8);
        sceVu0CopyVector(out, p0.f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/backStage", backStageProcessInStage);

void backStageSave(void *a0)
{
    func_001B6CA0(a0, &D_0063ACF0, 4);
    func_001B6CA0(a0, &D_0063C350, 4);
    func_001B6CA0(a0, &D_0063C354, 4);
    func_001B6CA0(a0, &D_0063C358, 4);
    func_001B6CA0(a0, &D_0063C35C, 4);
    func_001B6CA0(a0, &D_0063C360, 4);
    func_001B6CA0(a0, &D_0063C364, 4);
    func_001B6CA0(a0, &D_0063C368, 4);
    func_001B6CA0(a0, &D_0063C36C, 4);
}

void backStageLoad(void *a0)
{
    gamesysMemoryHandlerRead(a0, &D_0063ACF0, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C350, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C354, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C358, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C35C, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C360, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C364, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C368, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C36C, 4);
}

inline void backStageTsuresariReturn(void) {}
