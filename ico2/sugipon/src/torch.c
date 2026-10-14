#include "sugiCommon.h"
#include "debug.h"
#include "memory.h"
#include "gobj.h"
#include "act-game.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"

typedef struct TorchGeoWork { /* field names derived */
    /* 0x00 */ int flags;
    /* 0x04 */ int lightOn;
    /* 0x08 */ int burnTime; /* frames the torch has been alight */
    /* 0x0C */ int life;
    /* 0x10 */ int chainFlag;
    /* 0x14 */ int effect[5]; /* the particle effects a lit torch runs, -1 when off */
} TorchGeoWork;               /* derived name */

/* the torch work record InitTorchGeo starts every torch from (0x28 bytes,
   the size it allocates) */
static TorchGeoWork emptyTorchWork = {
    0, 0, 0, 65536, 0, {-1, -1, -1, -1, -1},
}; /* derived name */

#include "torch.h"
#include <libvu0.h>
#include "particleEffect.h"
#include "ios.h"
#include "main.h"
#include "sceneManager.h"
#include "include_asm.h"

INCLUDE_ASM(torchOffSE);

INCLUDE_ASM(LightTorchOn);

INCLUDE_ASM(LightTorchOff);

INCLUDE_ASM(moveTorch);

INCLUDE_ASM(CheckTorchChainReactionReverse);

INCLUDE_ASM(TorchGeo);

INCLUDE_ASM(InitTorchGeo);

inline void UpdateRealTimeGeometryValue(GObj *self)
{
    int buf[4];
    Sub15C *sub;
    GetRootPosition(buf, self);
    sub = self->dobj;
    sceVu0SubVector(sub->root.move, buf, sub->root.last);
    sub = self->dobj;
    CopyVector(sub->root.last, buf);
}

/* nonzero when lighting `other`'s torch from `gobj` must not happen: the
 * heroine's bomb, or the boy's weapon pair */
static inline int chainReactionBlocked(GObj *gobj, GObj *other) /* derived name */
{
    Act *p;
    Act *q;
    GObj *a;
    GObj *b;

    b = GOBJ_SUB(gobj)->parent.obj;
    a = GOBJ_SUB(other)->parent.obj;
    if (girlGObj != 0) {
        q = GOBJ_ACT(girlGObj);
        if (b != 0 && b == q->curItem) {
            /* tried to light the heroine's bomb */
            debug_StdPrintfDummy("ヒロインの爆弾に点火しようとした\n");
            return 1;
        }
    }
    if (b != 0 && a != 0) {
        p = GOBJ_ACT(boyGObj);
        if (ACTGame_NoWeapon(boyGObj) == 0 && a == p->weapon && b == p->curItem) {
            /* an exception came up while lighting */
            debug_StdPrintfDummy("点火の例外処理発生\n");
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM(TorchDL);

INCLUDE_ASM(IsTorchLightOn);

INCLUDE_ASM(CheckTorchChainReaction);

INCLUDE_ASM(SetTorchLife);

INCLUDE_ASM(SetTorchChainReactionFlag);
