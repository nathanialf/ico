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

INCLUDE_ASM(func_0023D518);

INCLUDE_ASM(func_0023D528);

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
