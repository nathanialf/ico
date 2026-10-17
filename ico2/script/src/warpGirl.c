#include "debug.h"
#include "gamesys.h"
#include "boyact.h"
#include "gflag.h"
#include "script.h"
#include "geometryManager.h"
/* header prototypes (order fixes the inline tail) */
#include "warpGirl.h"
#include <string.h>
#include <libvu0.h>
#include "main.h"
#include "include_asm.h"

/* the warp destination; this build has no warpGirlInStageSet word (the
   demo's .sdata of the TU is warpGirlOutStage's two strings and this word) */
int warpGirlId;

inline void warpGirlInit(void)
{
    warpGirlId = 0;
}

/* the 16-byte vector this file copies whole */
typedef union WarpVec { /* derived name */ /* field names derived */
    float f[4];
    long long q[2];
} WarpVec; /* derived name */

/* .sbss: set when a warp destination has been found. */
static int warpFound; /* derived name */

/* the "this record wins" setter */
static inline void warpGirlOutSet(int id, int noSet) /* derived name */
{
    if (noSet != 0) {
        return;
    }
    warpGirlId = id;
    warpFound = 1;
}

INCLUDE_ASM(warpGirlOutStage);

INCLUDE_ASM(warpGirlInStage);
