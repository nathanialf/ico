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
#include "include_asm.h"

struct HintInfo { /* field names derived */
    int anim;     /* the stage animation the hint plays */
    int no;
    int time;
    int flags;
};

/* the record a new hint GObj starts from: no stage, no hint, no time, no
   flags */
static struct HintInfo hintDefault = {-1, -1, -1, 0}; /* derived name */

INCLUDE_ASM(LwsKyomiGeo);

INCLUDE_ASM(CreateKyomiGObj);

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
    if (debug_lwskyomi_lookonly != 0) {
        if (on2 != 0) {
            on1 = 1;
        }
    }
    SetDirectRootPosition(gobj, root);
    UpdateRootMatrix(gobj);
    GetRootPosition(pos, gobj);
    brainSetLevelGop(gobj, lv, on1, on2);
}
