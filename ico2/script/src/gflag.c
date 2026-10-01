#include "gflag.h"
#include "gamesys.h"
#include "mcard.h"
#include "boyact.h"
#include "stage_orient.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "warpGirl.h"
#include <string.h>

/* the story flag bitmap, one bit per event flag; saved and restored whole */
static unsigned char gflags[50] = {0};

/* kept local: main.c's global; this TU does not include main.h */
extern int systemStatus[];

/* gflag.o's .sdata run (VMA 0x63AA00..0x63AA08; MAIN.MAP's January object
   is the one word gFlagSaveStage): the game-clear state, saved and loaded
   with the flags, then the stage the save was made on (MAIN.MAP global). */
int gFlagGameClear = 0; /* derived name */

int gFlagSaveStage = 0;

extern int before_stage_no;
extern int gamesysVersionDiff;
extern int stage_no;
/* kept local: this TU's uses of itouGFlagInit do not fit the prototype in itou_gflag.h */
extern void itouGFlagInit();
int gflagChk(int bit_idx);
void gflagOn(int bit_idx);

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
    memset(IosMcPreviewInfo, 0, 0x14);
    gamesysVersionDiff = 0;
    itouGFlagInit();
}

void gflagSave(void *fp)
{
    gFlagSaveStage = stage_no;
    gamesysMemoryHandlerWrite(fp, &gFlagSaveStage, 4);
    gamesysMemoryHandlerWrite(fp, &gFlagGameClear, 4);
    gamesysMemoryHandlerWrite(fp, gflags, sizeof(gflags));
}

void gflagLoad(void *fp)
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
