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

void LightTorchOff(GObj *gobj)
{
    TorchGeoWork *w = GOBJ_SUB(gobj)->work;

    if (w->lightOn != 0) {
        if (w->effect[3] != -1) {
            DeleteParticleEffect(w->effect[3]);
        }
        if (w->effect[2] != -1) {
            DeleteParticleEffect(w->effect[2]);
        }
        if (w->effect[0] != -1) {
            DeleteParticleEffect(w->effect[0]);
        }
        if (w->effect[1] != -1) {
            DeleteParticleEffect(w->effect[1]);
        }
        if (w->effect[4] != -1) {
            DeleteParticleEffect(w->effect[4]);
        }
        w->effect[2] = w->effect[3] = w->effect[0] = w->effect[1] = w->effect[4] = -1;
        w->burnTime = 0;
        w->lightOn = 0;
        GOBJ_SUB(gobj)->lightId = 0;
        torchOffSE(gobj);
    }
}

static void torchDrainControl(GObj *gobj, float level);

static void moveTorch(GObj *gobj, void *mtx)
{
    TorchGeoWork *w = GOBJ_SUB(gobj)->work;

    if (w->effect[3] != -1) {
        SetParticleEffectGeometry(w->effect[3], mtx, IdentityQuaternion);
    }
    if (w->effect[2] != -1) {
        SetParticleEffectGeometry(w->effect[2], mtx, IdentityQuaternion);
    }
    if (w->effect[0] != -1) {
        SetParticleEffectGeometry(w->effect[0], mtx, IdentityQuaternion);
    }
    if (w->effect[1] != -1) {
        SetParticleEffectGeometry(w->effect[1], mtx, IdentityQuaternion);
    }
    if (w->effect[4] != -1) {
        SetParticleEffectGeometry(w->effect[4], mtx, IdentityQuaternion);
    }
}

static void setPauseFlag(GObj *gobj, int flag);

INCLUDE_ASM(CheckTorchChainReactionReverse);

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
            /* tried to light the heroine's bomb (no print in August) */
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

static void procChainReaction(GObj *gobj);

INCLUDE_ASM(TorchGeo);

INCLUDE_ASM(InitTorchGeo);

INCLUDE_ASM(TorchDL);

INCLUDE_ASM(IsTorchLightOn);

INCLUDE_ASM(CheckTorchChainReaction);

INCLUDE_ASM(SetTorchLife);

INCLUDE_ASM(SetTorchChainReactionFlag);
