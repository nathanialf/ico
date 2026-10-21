#include "clipCollisionManager.h"
#include "GobjProc.h"
#include "debug.h"
#include "matrixDrive.h"
#include "Matrix.h"
#include "main.h"
#include "act.h"

/* the manager thread's idle body, handed to CreateGObjByFuncSet;
   waySystemManager.c has its own thStart */
static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}
