#include "sceneManager.h"
#include "memory.h"
#include "StageAnimation.h"
#include "debug.h"
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "lws_kyomi.h"
#include "main.h"
#include "geometryManager.h"
#include "brain.h"

struct HintInfo { /* field names derived */
    int anim;     /* the stage animation the hint plays */
    int no;
    int time;
    int flags;
};

/* This build has no hint system here: no hint record in .bss and no save-bit
   packers (no function of the demo addresses one). */

/* (this build keeps no hint template in .data) */

void LwsKyomiGeo(GObj *gobj)
{
    brainSubLevelGop(gobj, 0.1f);
}

GObj *CreateKyomiGObj(void)
{
    float lay[16];
    GObj *gobj;

    memset(lay, 0, 64);
    lay[8] = 1.0f;
    lay[9] = 1.0f;
    lay[10] = 1.0f;
    gobj = CreateLayoutedGObj(58, 51, -1, 0, lay, 1, 7, 0);
    brainStatusDefaultSet(&brainGirl, gobj, 1);
    return gobj;
}

/* This build keeps no hint-timer window in .sbss (no function of the demo
   addresses one). */

void SetParamKyomiGObj(GObj *gobj, float *root, float *param)
{
    float pos[4];
    float lv;
    int on1;
    int on2;

    on1 = 1;
    lv = param[0];
    if (param[1] < 0.5f) {
        on1 = 0;
    }
    on2 = 1;
    if (param[2] < 0.5f) {
        on2 = 0;
    }
    if (on2 != 0) {
        on1 = 1;
    }
    SetDirectRootPosition(gobj, root);
    UpdateRootMatrix(gobj);
    GetRootPosition(pos, gobj);
    brainSetLevelGop(gobj, lv, on1, on2);
}
