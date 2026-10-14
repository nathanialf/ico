#include "debug.h"
#include "memory.h"
#include "script.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "moveColTest.h"
#include <stdlib.h>
#include "ios.h"
#include "main.h"
#include "DisplayP2O.h"
#include "include_asm.h"

inline short *InitMoveColTestGeo(int gobj, int *layout)
{
    short *r = iosMallocDebug(ios_partition_sugipon, 12, "src/moveColTest.c", 28);
    *(int *)r = layout[12];
    r[2] = (short)rand();
    r[3] = (short)rand();
    r[4] = (short)rand();
    r[5] = 0;
    return r;
}

/* the 12-byte work block InitMoveColTestGeo allocates, hung at sub+0x830 */
typedef struct MctWork { /* field names derived */
    int obj;             /* 0x00 */
    short r1;            /* 0x04 */
    short r2;            /* 0x06 */
    short r3;            /* 0x08 */
    short angle;         /* 0x0A */
} MctWork;               /* derived name */

/* the blink counter and the test offset */
static unsigned char blinkCount = 0; /* derived name */

static int testOffset = 0; /* derived name */

INCLUDE_ASM(MoveColTestGeo);

void MoveColTestDL(GObj *self)
{
    p2o_DispVU1(self);
}
