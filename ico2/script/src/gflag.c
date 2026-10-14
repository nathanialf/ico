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
#include "include_asm.h"

/* the story flag bitmap, one bit per event flag; saved and restored whole */
static unsigned char gflags[46] = {0}; /* derived name */

/* .sdata: the game-clear state, saved and loaded with the flags, then the
   stage the save was made on. */
int gFlagGameClear = 0; /* derived name */

int gFlagSaveStage = 0;

INCLUDE_ASM(gflagInit);

INCLUDE_ASM(gflagSave);

INCLUDE_ASM(gflagLoad);

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
