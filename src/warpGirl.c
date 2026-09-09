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

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlOutStage);

/* one 0x58-byte girl-warp record (MAIN.MAP: girlWarpList, from girl-warp-list.o) */
typedef struct WarpRec {
    float p0[4]; /* 0x00 */
    float p1[4]; /* 0x10 */
    float p2[4]; /* 0x20 */
    char _p30[0x4C - 0x30];
    unsigned short to0; /* 0x4C */
    unsigned short to1; /* 0x4E */
    unsigned short to2; /* 0x50 */
    char _p52[0x58 - 0x52];
} WarpRec;

extern WarpRec D_0055EE50[];
extern int warpGirlInStageSet;
extern int D_00639EA8;
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
