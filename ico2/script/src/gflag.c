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
#ifdef VERSION_NTSC
unsigned char gFlag[46] = {0};
#else
static unsigned char gflags[50] = {0}; /* derived name */

/* .sdata: the game-clear state, saved and loaded with the flags, then the
   stage the save was made on. */
int gFlagGameClear = 0; /* derived name */
#endif

int gFlagSaveStage = 0;

void gflagInit(void)
{
#ifdef VERSION_NTSC
    int keep = gflagChk(346);

    memset(gFlag, 0, sizeof(gFlag));
    before_stage_no = 0;
    if (keep != 0) {
        gflagOn(346);
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
#ifdef VERSION_NTSC
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
#ifdef VERSION_NTSC
    gamesysMemoryHandlerWrite(fp, gFlag, sizeof(gFlag));
#else
    gamesysMemoryHandlerWrite(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerWrite(fp, gflags, sizeof(gflags));
#endif
}

void gflagLoad(GamesysMemCursor *fp)
{
    gamesysMemoryHandlerRead(fp, &gFlagSaveStage, 4);
#ifdef VERSION_NTSC
    gamesysMemoryHandlerRead(fp, gFlag, sizeof(gFlag));
#else
    gamesysMemoryHandlerRead(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerRead(fp, gflags, sizeof(gflags));
#endif
}

int gflagChk(int bit_idx)
{
#ifdef VERSION_NTSC
    return (gFlag[bit_idx >> 3] >> (bit_idx & 7)) & 1;
#else
    return (gflags[bit_idx >> 3] >> (bit_idx & 7)) & 1;
#endif
}

void gflagOn(int bit_idx)
{
#ifdef VERSION_NTSC
    gFlag[bit_idx >> 3] |= 1 << (bit_idx & 7);
#else
    gflags[bit_idx >> 3] |= 1 << (bit_idx & 7);
#endif
}

void gflagOff(int bit_idx)
{
#ifdef VERSION_NTSC
    gFlag[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
#else
    gflags[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
#endif
}
