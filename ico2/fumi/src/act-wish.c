#include "typedef.h"
#include "debug.h"
#include "commonact.h"
#include "gv.h"
#include "item.h"
#include <libvu0.h>
#include "act-wish.h"
#include "act-game.h"
#include "boyact.h"
#include "main.h"
#include "include_asm.h"

static inline unsigned char chkOrient(char *s, float *dir, float *w, float deg) /* derived name */
{
    float *q = (float *)(s + 0x4B0);

    if (q[0] == 0.0f && q[1] == 0.0f && q[2] == 0.0f && q[3] == 0.0f) {
        debug_StdPrintfDummy("orient null");
        return 0;
    }
    sceVu0ScaleVector(w, q, -1.0f);
    if ((float)(_RotyGV(dir, w) < 0 ? -_RotyGV(dir, w) : _RotyGV(dir, w)) < deg) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM(ACTGetWish_FromPad);
