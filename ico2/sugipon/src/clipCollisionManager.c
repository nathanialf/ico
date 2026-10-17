#include "clipCollisionManager.h"
#include "GobjProc.h"
#include "debug.h"
#include "matrixDrive.h"
#include "Matrix.h"
#include "main.h"
#include "act.h"

/* PAL's manager object word is not in this build: the TU has no .sdata in
   the demo */

/* `self` is volatile: the thread yields in _ACTWait below, and the entry
   argument is read back from its stack home after each resume. */
/* the manager thread's idle body, handed to CreateGObjByFuncSet;
   waySystemManager.c has its own thStart */
static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}
