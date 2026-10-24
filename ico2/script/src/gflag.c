#include "gflag.h"
#include "gamesys.h"
#include "mcard.h"
#include "boyact.h"
#include "stage_orient.h"

#ifndef VERSION_JUN26
#include "itou_gflag.h"
#endif

#include "generator.h"
#include "lws_kyomi.h"
#include "warpGirl.h"
#include <string.h>
#include "main.h"

/* the story flag bitmap, one bit per event flag; saved and restored whole */
#ifdef VERSION_JUN26
unsigned char gFlag[44] = {0};

/* .sdata: the stage the save was made on, saved and loaded with the flags */
int gFlagSaveStage = 0;

void gflagSave(GamesysMemCursor *fp)
{
    gFlagSaveStage = stage_no;
    gamesysMemoryHandlerWrite(fp, &gFlagSaveStage, 4);
    gamesysMemoryHandlerWrite(fp, gFlag, sizeof(gFlag));
}

void gflagLoad(GamesysMemCursor *fp)
{
    gamesysMemoryHandlerRead(fp, &gFlagSaveStage, 4);
    gamesysMemoryHandlerRead(fp, gFlag, sizeof(gFlag));
}
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
unsigned char gFlag[46] = {0};
#else
static unsigned char gflags[50] = {0}; /* derived name */

/* .sdata: the game-clear state, saved and loaded with the flags, then the
   stage the save was made on. */
int gFlagGameClear = 0; /* derived name */
#endif

int gFlagSaveStage = 0;
#endif

void gflagInit(void)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    int keep = gflagChk(330);
#else
    int keep = gflagChk(345);
#endif
#else
    int keep = gflagChk(346);
#endif

    memset(gFlag, 0, sizeof(gFlag));
    before_stage_no = 0;
    if (keep != 0) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        gflagOn(330);
#else
        gflagOn(345);
#endif
#else
        gflagOn(346);
#endif
    }
    Boy_Init();
#else
    int keep = gflagChk(379);

    memset(gflags, 0, sizeof(gflags));
    before_stage_no = 0;
    if (keep != 0) {
        gflagOn(379);
    }
    Boy_Init();
    Hint_Init();
#endif
    StageOrientInit();
    gamesysObjInfoInit();
    Generator_Init();
    warpGirlInit();
    systemStatus[3] = 0;
#ifdef VERSION_JUN26
    memset(IosMcPreviewInfo, 0, 16);
    gamesysVersionDiff = 0;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    memset(IosMcPreviewInfo, 0, 16);
#else
    memset(IosMcPreviewInfo, 0, 20);
#endif
    gamesysVersionDiff = 0;
    itouGFlagInit();
}

void gflagSave(GamesysMemCursor *fp)
{
    gFlagSaveStage = stage_no;
    gamesysMemoryHandlerWrite(fp, &gFlagSaveStage, 4);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    gamesysMemoryHandlerWrite(fp, gFlag, sizeof(gFlag));
#else
    gamesysMemoryHandlerWrite(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerWrite(fp, gflags, sizeof(gflags));
#endif
}

void gflagLoad(GamesysMemCursor *fp)
{
    gamesysMemoryHandlerRead(fp, &gFlagSaveStage, 4);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    gamesysMemoryHandlerRead(fp, gFlag, sizeof(gFlag));
#else
    gamesysMemoryHandlerRead(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerRead(fp, gflags, sizeof(gflags));
#endif
#endif
}

int gflagChk(int bit_idx)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    return (gFlag[bit_idx >> 3] >> (bit_idx & 7)) & 1;
#else
    return (gflags[bit_idx >> 3] >> (bit_idx & 7)) & 1;
#endif
}

void gflagOn(int bit_idx)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    gFlag[bit_idx >> 3] |= 1 << (bit_idx & 7);
#else
    gflags[bit_idx >> 3] |= 1 << (bit_idx & 7);
#endif
}

void gflagOff(int bit_idx)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    gFlag[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
#else
    gflags[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
#endif
}
