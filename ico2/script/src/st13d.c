#include "common.h"
#include "act.h"
#include "gflag.h"
#include "script.h"
#include "geometryManager.h"
#include "st13d.h"

inline void actSt13dInit(void) {}

/* A 16-byte constant vector: the float view carries the values, the long
   long view is the one the whole-object copy reads. */
typedef union PosBox {
    float f[4];
    long long lo[2];
} PosBox;

typedef struct Act Act;

extern void *D_00639EA4;

static const PosBox exitPos = {{854.0f, -156.0f, 0.0f, 0.0f}};

static const PosBox exit2Pos = {{330.0f, 200.0f, 200.0f, 0.0f}};

static const PosBox exitRPos = {{854.0f, -156.0f, -400.0f, 0.0f}};

static const PosBox exitLPos = {{854.0f, -156.0f, 400.0f, 0.0f}};

void actSt13dExit(volatile int a0)
{
    int x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12) == 0) {
        ScpCallCameraOff();
    }

    pos = exitPos;
    size = exit2Pos;

    GetRootPosition(&p, D_00639EA4);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(2, D_00639EA4, 0, 16.0f, 16.0f);
}

void actSt13dExitR(volatile int a0)
{
    int x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    pos = exitRPos;
    size = exit2Pos;

    GetRootPosition(&p, D_00639EA4);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(7, D_00639EA4, 0, 16.0f, 16.0f);
}

void actSt13dExitL(volatile int a0)
{
    int x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    pos = exitLPos;
    size = exit2Pos;

    GetRootPosition(&p, D_00639EA4);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, D_00639EA4, 0, 16.0f, 16.0f);
}
