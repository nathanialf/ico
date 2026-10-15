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

inline void SetTorchChainReactionFlag(GObj *torch, int flag)
{
    TorchGeoWork *w = GOBJ_SUB(torch)->work;

    w->chainFlag = flag;
}

void torchOffSE(GObj *torch)
{
    StopSEPackage(torch);
    ExecuteSEPackage(torch, 65);
}

void LightTorchOn(GObj *gobj)
{
    float pos[4];
    TorchGeoWork *w;
    GObj *o;
    int n;

    w = GOBJ_SUB(gobj)->work;
    if (w->lightOn != 0) {
        return;
    }
    GetRootPosition(pos, gobj);
    switch (w->flags) {
    case 2:
        n = 0;
        o = isysGObjSearchFromObjKindID_begin(10);
        while (o != 0) {
            TorchGeoWork *ow = GOBJ_SUB(o)->work;
            if (o != gobj && ow->flags == 2) {
                if (IsTorchLightOn(o)) {
                    n++;
                }
            }
            o = isysGObjSearchFromObjKindID_next(o);
        }
        if (n > 0) {
            return;
        }
        w->effect[1] =
            SetParticleEffectByPartition(21, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[4] =
            SetParticleEffectByPartition(19, pos, IdentityQuaternion, ios_partition_seki);
        break;
    case 4:
        w->effect[0] =
            SetParticleEffectByPartition(23, pos, IdentityQuaternion, ios_partition_seki);
        break;
    default:
        w->effect[3] = SetParticleEffectByPartition(7, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[0] = SetParticleEffectByPartition(5, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[1] = SetParticleEffectByPartition(9, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[4] =
            SetParticleEffectByPartition(19, pos, IdentityQuaternion, ios_partition_seki);
        break;
    }
    w->burnTime = 0;
    w->lightOn = 1;
    GOBJ_SUB(gobj)->lightId = 1;
}

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
 * boy's weapon pair */
static inline int chainReactionBlocked(GObj *gobj, GObj *other) /* derived name */
{
    Act *p;
    GObj *a;
    GObj *b;

    b = GOBJ_SUB(gobj)->parent.obj;
    a = GOBJ_SUB(other)->parent.obj;
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
