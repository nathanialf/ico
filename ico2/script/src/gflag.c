#include "gflag.h"
#include "gamesys.h"
#include "mcard.h"
#include "boyact.h"
#include "stage_orient.h"
#include "itou_gflag.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "warpGirl.h"
#include <string.h>
#include "main.h"

/* the story flag bitmap, one bit per event flag; saved and restored whole */
static unsigned char gflags[50] = {0}; /* derived name */

/* .sdata: the game-clear state, saved and loaded with the flags, then the
   stage the save was made on. */
int gFlagGameClear = 0; /* derived name */

int gFlagSaveStage = 0;

void gflagInit(void)
{
    int keep = gflagChk(379);

    memset(gflags, 0, sizeof(gflags));
    before_stage_no = 0;
    if (keep != 0) {
        gflagOn(379);
    }
    Boy_Init();
    Hint_Init();
    StageOrientInit();
    gamesysObjInfoInit();
    Generator_Init();
    warpGirlInit();
    systemStatus[3] = 0;
    memset(IosMcPreviewInfo, 0, 20);
    gamesysVersionDiff = 0;
    itouGFlagInit();
}

void gflagSave(GamesysMemCursor *fp)
{
    gFlagSaveStage = stage_no;
    gamesysMemoryHandlerWrite(fp, &gFlagSaveStage, 4);
    gamesysMemoryHandlerWrite(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerWrite(fp, gflags, sizeof(gflags));
}

void gflagLoad(GamesysMemCursor *fp)
{
    gamesysMemoryHandlerRead(fp, &gFlagSaveStage, 4);
    gamesysMemoryHandlerRead(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerRead(fp, gflags, sizeof(gflags));
}

int gflagChk(int bit_idx)
{
    return (gflags[bit_idx >> 3] >> (bit_idx & 7)) & 1;
}

void gflagOn(int bit_idx)
{
    gflags[bit_idx >> 3] |= 1 << (bit_idx & 7);
}

void gflagOff(int bit_idx)
{
    gflags[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}
