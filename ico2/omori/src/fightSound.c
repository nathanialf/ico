#include "fightSound.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "debug_exception.h"
#include "main.h"
#include "gamesys.h"
#include <assert.h>
#include "include_asm.h"

/* set while the fight music is paused */
static int fightSoundPause = 0; /* derived name */

/* the fight loop's ADPCM handle, its volume and the open request */
static struct { /* field names derived */
    SqEntry *handle;
    int volume;
    AdpcmOpenReq req;
} fightSnd; /* derived name */

/* the fight music's step: 1 once the open is requested, 2 after it */
static int fightSoundState = 0; /* derived name */

/* set while the girl is held (status 9) or taken off the stage */
static int fightSoundGirlTaken = 0; /* derived name */

INCLUDE_ASM(fightSoundProcessMain);

INCLUDE_ASM(fightSoundProcess);

void fightSoundProcessRequestPause(void)
{
    fightSoundPause = 1;
}

void fightSoundClose(void)
{
    if (fightSnd.handle != 0) {
        soundDataClose(fightSnd.handle);
        fightSnd.handle = 0;
    }
}

void fightSoundProcessRequestStart(void)
{
    fightSoundPause = 0;
}

int fightSoundProcessRequestStatus(void)
{
    return fightSoundPause;
}

SqEntry *fightSoundPlayChk(void)
{
    return fightSnd.handle;
}
