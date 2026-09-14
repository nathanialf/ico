#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void warpGirlInit(void);
void warpGirlInit(void);
extern int warpGirlId;

inline void warpGirlInit(void)
{
    warpGirlId = 0;
}

/* one 0x58-byte girl-warp record (MAIN.MAP: girlWarpList, from girl-warp-list.o) */
typedef struct WarpRec {
    float p0[4];         /* 0x00 */
    float p1[4];         /* 0x10 */
    float p2[4];         /* 0x20 */
    int gflag;           /* 0x30 */
    float box0[3];       /* 0x34 */
    float box1[3];       /* 0x40 */
    unsigned short to0;  /* 0x4C */
    unsigned short to1;  /* 0x4E */
    unsigned short to2;  /* 0x50 */
    unsigned short from; /* 0x52 */
    unsigned char kind;  /* 0x54 */
    char _p55[0x58 - 0x55];
} WarpRec;

/* the stage table the trigger scan walks: 0x40 bytes per stage */
typedef struct StageRec {
    char _p00[0x02];
    unsigned short live; /* 0x02 */
    unsigned short to;   /* 0x04 */
    char _p06[0x30 - 0x06];
    int kind; /* 0x30 */
    char _p34[0x40 - 0x34];
} StageRec;

/* the 16-byte vector this file copies whole */
typedef union Vec16 {
    float f[4];
    long long q[2];
} Vec16;

extern StageRec D_004DA980[];
extern WarpRec D_0055EE50[];
extern int stage_no;
extern int D_0063C258;
extern int D_00639EA8;
extern char D_0063AA58[];
extern char D_0063AA60[];
extern char D_005549E8[];
extern int gflagChk(int flag);
extern void *memset(void *p, int c, int n);
extern void GetRootPosition(float *out, int gobj);
extern int scpTriggerPosBox(float *pos, float *box0, float *box1);
extern void debug_StdPrintfDummy();

/* warpGirl.c:75-81 in the listing: the "this record wins" setter.  No MAIN.MAP
   symbol (the listing inlines it), so the name is ours. */
static inline void warpGirlOutSet(int id, int noSet)
{
    if (noSet != 0) {
        return;
    }
    warpGirlId = id;
    D_0063C258 = 1;
}

void warpGirlOutStage(int stage, int noSet)
{
    float b0[4]; /* the trigger box, corner 0 */
    float b1[4]; /* the trigger box, corner 1 */
    float rpos[4];
    int i;
    int j;
    int hit;

    hit = 0;
    if (D_004DA980[1].to != stage) {
        return;
    }
    if (D_00639EA8 == 0) {
        int n = 10;

        debug_StdPrintfDummy(D_0063AA58);
        while (n-- != 0) {
            debug_StdPrintfDummy(D_005549E8);
        }
        debug_StdPrintfDummy(D_0063AA60);
        return;
    }
    warpGirlId = 0;
    for (j = 2; j < 22; j++) {
        if (D_004DA980[j].live != 0 && D_004DA980[j].to == stage_no && D_004DA980[j].kind == 4) {
            hit = 1;
            break;
        }
    }
    if (hit != 0) {
        return;
    }
    D_0063C258 = 0;
    for (i = 1; i < 25 && D_0063C258 == 0; i++) {
        WarpRec *w = &D_0055EE50[i];

        if (w->from != stage) {
            continue;
        }
        switch (w->kind) {
        case 0:
            warpGirlOutSet(i, noSet);
            break;
        case 2:
            if (gflagChk(w->gflag) == 0) {
                continue;
            }
            /* fall through */
        case 1:
            memset(b1, 0, 16);
            b1[0] = w->box1[2];
            b1[1] = w->box1[1];
            b1[2] = w->box1[0];
            *(Vec16 *)b0 = *(Vec16 *)b1;
            memset(rpos, 0, 16);
            rpos[0] = w->box0[2];
            rpos[1] = w->box0[1];
            rpos[2] = w->box0[0];
            *(Vec16 *)b1 = *(Vec16 *)rpos;
            GetRootPosition(rpos, D_00639EA8);
            if (scpTriggerPosBox(rpos, b0, b1) == 0) {
                continue;
            }
            warpGirlOutSet(i, noSet);
            break;
        default:
            __asm__ __volatile__("break");
            break;
        }
    }
}

extern int warpGirlInStageSet;
extern char D_00554A30[];
extern int IsGirlEscortedInNextStage(void);
extern void sceVu0ScaleVector(float *dst, float *src, float s);
extern void debug_StdPrintfDummy();
extern void gamesysObjInfoPosNewStageSet(int a0, int a1, int stage, float *pos, float *rot);

void warpGirlInStage(int stageNo)
{
    float pos[4];
    float rot[4];
    float ry;
    WarpRec *w = &D_0055EE50[warpGirlId];

    warpGirlInStageSet = 0;
    if (IsGirlEscortedInNextStage() != 0) {
        return;
    }
    warpGirlInStageSet = 1;
    if (w->to0 == stageNo) {
        pos[0] = -w->p2[3];
        pos[1] = -w->p2[2];
        pos[2] = -w->p2[1];
        ry = w->p2[0];
    } else if (w->to1 == stageNo) {
        pos[0] = -w->p1[3];
        pos[1] = -w->p1[2];
        pos[2] = -w->p1[1];
        ry = w->p1[0];
    } else if (w->to2 == stageNo) {
        pos[0] = -w->p0[3];
        pos[1] = -w->p0[2];
        pos[2] = -w->p0[1];
        ry = w->p0[0];
    } else {
        warpGirlInStageSet = 0;
        return;
    }
    rot[0] = 0.0f;
    rot[1] = ry;
    rot[2] = 0.0f;
    sceVu0ScaleVector(rot, rot, 0.017453292f);
    debug_StdPrintfDummy(D_00554A30, D_00639EA8);
    gamesysObjInfoPosNewStageSet(0x94, 2, stageNo, pos, rot);
}
