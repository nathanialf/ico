#include "debug.h"
#include "memory.h"
#include "script.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "moveColTest.h"
#include <stdlib.h>
#include "ios.h"

/* kept local: DisplayP2O.h does not compile in this TU (too many arguments to function `p2o_DispVU1') */
extern void p2o_DispVU1();

inline short *InitMoveColTestGeo(int a0, int *self)
{
    short *r = iosMallocDebug(ios_partition_sugipon, 12, "src/moveColTest.c", 28);
    *(int *)r = self[0x30 / 4];
    r[2] = (short)rand();
    r[3] = (short)rand();
    r[4] = (short)rand();
    r[5] = 0;
    return r;
}

/* the 12-byte work block InitMoveColTestGeo allocates, hung at sub+0x830 */
typedef struct MctWork {
    int obj;     /* 0x00 */
    short r1;    /* 0x04 */
    short r2;    /* 0x06 */
    short r3;    /* 0x08 */
    short angle; /* 0x0A */
} MctWork;

typedef struct EditPad {
    int flags;              /* 0x00 */
    int trg;                /* 0x04 */
    char pad08[0x58 - 0x8]; /* 0x08 */
    int mode;               /* 0x58 */
    char pad5C[0xAC - 0x5C];
    unsigned char stick[4]; /* 0xAC */
} EditPad;

/* kept local: main.c's global; this TU does not include main.h */
extern EditPad pad;

/* the TU's .sdata (MAIN.MAP moveColTest.o .sdata 0xC, no symbol): the blink
   counter and the test offset, then MoveColTestGeo's "%d\n" */
static unsigned char blinkCount = 0; /* derived name */

static int testOffset = 0; /* derived name */

/* kept local: main.c's global; this TU does not include main.h */
extern int boyGObj;

void MoveColTestGeo(char *self)
{
    float pos[4];
    MctWork *w = *(MctWork **)(*(char **)(self + 0x15C) + 0x830);
    int c;

    CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(self + 0x15C) + 0x20);
    MatrixDrive_RotMatrixZ(w->angle);
    CopyQuaternion(*(char **)(self + 0x15C) + 0xD0, *(char **)(self + 0x15C) + 0x60);
    RotQuaternionZ(*(char **)(self + 0x15C) + 0xD0, w->angle);
    CopyMatrix(*(void **)(*(char **)(self + 0x15C) + 0xC), MatrixDrive_GetMatrix());
    UpdateRootMatrix(self);

    if (pad.mode & 4) {
        if (pad.stick[1] >= 0x81) {
            c = pad.stick[1];
            if (c - 0x80 >= 0x15) {
                w->angle += (c - 0x94) * 3;
            }
        } else {
            c = pad.stick[1];
            if (c - 0x80 < -0x14) {
                w->angle += (c - 0x6C) * 3;
            }
        }
    }
    if ((blinkCount++ >> 5) & 1) {
        debug_PrintfDummy(10, 60, 0x4080FF00, "PUSH R3 TO BORN SPIDER.");
    }

    GetRootPosition(pos, boyGObj);
    pos[1] += -500.0f;
    if (pad.trg & 0x400) {
        scpBornSpider(0xA, pos[0], pos[1], pos[2], 300.0f);
        testOffset += 0xA;
        debug_StdPrintfDummy("%d\n", testOffset);
    }
    if (pad.trg & 0x200) {
        scpBornSpider(1, pos[0], pos[1], pos[2], 300.0f);
        testOffset += 1;
        debug_StdPrintfDummy("%d\n", testOffset);
    }
}

void MoveColTestDL(int a0, int a1, int a2, int a3)
{
    p2o_DispVU1(a0, a1, a2, a3);
}
