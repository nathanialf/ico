#include "act.h"
#include "gflag.h"
#include "script.h"
#include "geometryManager.h"
#include "st13d.h"
#include "main.h"

inline void actSt13dInit(void) {}

/* A 16-byte constant vector: the float view carries the values, the long
   long view is the one the whole-object copy reads. */
typedef union PosBox {
    float f[4];
    long long lo[2];
} PosBox;

static const PosBox exitPos = {{854.0f, -156.0f, 0.0f, 0.0f}};

static const PosBox exit2Pos = {{330.0f, 200.0f, 200.0f, 0.0f}};

static const PosBox exitRPos = {{854.0f, -156.0f, -400.0f, 0.0f}};

static const PosBox exitLPos = {{854.0f, -156.0f, 400.0f, 0.0f}};

void actSt13dExit(GObj *volatile a0)
{
    GObj *x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(18) == 0) {
        ScpCallCameraOff();
    }

    pos = exitPos;
    size = exit2Pos;

    GetRootPosition(&p, boyGObj);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(2, boyGObj, 0, 16.0f, 16.0f);
}

void actSt13dExitR(GObj *volatile a0)
{
    GObj *x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    pos = exitRPos;
    size = exit2Pos;

    GetRootPosition(&p, boyGObj);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(7, boyGObj, 0, 16.0f, 16.0f);
}

void actSt13dExitL(GObj *volatile a0)
{
    GObj *x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    pos = exitLPos;
    size = exit2Pos;

    GetRootPosition(&p, boyGObj);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, boyGObj, 0, 16.0f, 16.0f);
}
