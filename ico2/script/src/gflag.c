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
unsigned char gFlag[46] = {0};

/* .sdata: the stage the save was made on, saved and loaded with the flags */
int gFlagSaveStage = 0;

void gflagInit(void)
{
    int keep = gflagChk(345);

    memset(gFlag, 0, sizeof(gFlag));
    before_stage_no = 0;
    if (keep != 0) {
        gflagOn(345);
    }
    Boy_Init();
    StageOrientInit();
    gamesysObjInfoInit();
    Generator_Init();
    warpGirlInit();
    systemStatus[3] = 0;
    memset(IosMcPreviewInfo, 0, 16);
    gamesysVersionDiff = 0;
    itouGFlagInit();
}

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

int gflagChk(int bit_idx)
{
    return (gFlag[bit_idx >> 3] >> (bit_idx & 7)) & 1;
}

void gflagOn(int bit_idx)
{
    gFlag[bit_idx >> 3] |= 1 << (bit_idx & 7);
}

void gflagOff(int bit_idx)
{
    gFlag[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}
