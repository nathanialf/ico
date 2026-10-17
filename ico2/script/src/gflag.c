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
static unsigned char gflags[48] = {0}; /* derived name */

/* .sdata: the game-clear state, saved and loaded with the flags (this build
   has no saved-stage word after it: the demo's .sdata of the TU is this one
   word) */
int gFlagGameClear = 0; /* derived name */

INCLUDE_ASM(gflagSave);

INCLUDE_ASM(gflagLoad);

INCLUDE_ASM(gflagInit);

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
