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

inline void TorchDL(void) {}

inline int IsTorchLightOn(GObj *torch)
{
    TorchGeoWork *w = GOBJ_SUB(torch)->work;

    return w->lightOn;
}

GObj *CheckTorchChainReactionReverse(GObj *self, float dist)
{
    float pos[4];
    float pos2[4];
    GObj *o;
    GObj *p;
    int n;
    int lit;

    n = 0;
    GetRootPosition(pos, self);

    o = isysGObjSearchFromObjKindID_begin(10);
    while (o != 0) {
        TorchGeoWork *w = GOBJ_SUB(o)->work;
        if (w->flags == 2) {
            if (IsTorchLightOn(o)) {
                n++;
            }
        }
        o = isysGObjSearchFromObjKindID_next(o);
    }

    dist = dist * dist;
    lit = 0 < n;
    p = isysGObjSearchFromObjKindID_begin(10);
    while (p != 0) {
        if (p != self && IsTorchLightOn(p) == 0 && p->active != 0 &&
            (((TorchGeoWork *)GOBJ_SUB(p)->work)->flags != 2 || lit == 0)) {
            GetRootPosition(pos2, p);
            if (distance_squared(pos2, pos) < dist) {
                return p;
            }
        }
        p = isysGObjSearchFromObjKindID_next(p);
    }
    return 0;
}

inline TorchGeoWork *InitTorchGeo(GObj *self, SObjSimpleSetting *lay)
{
    TorchGeoWork *p = iosMallocDebug(ios_partition_sugipon, sizeof(TorchGeoWork), __FILE__, 196);
    *p = emptyTorchWork;
    /* the display object read through the SubHandle union each time: the
       light store reads the slot again after the work store, which three
       Sub15C * reads of it do not (measured) */
    sceVu0UnitMatrix(&((SubHandle *)&self->dobj)->sub->matrix);
    ((SubHandle *)&self->dobj)->sub->work = p;
    if (lay->obj & 1) {
        LightTorchOn(self);
    } else {
        ((SubHandle *)&self->dobj)->sub->lightId = 0;
    }
    p->flags = lay->obj & ~1;
    return p;
}

inline GObj *CheckTorchChainReaction(GObj *self, float dist)
{
    float pos[4];
    float pos2[4];
    GObj *o;
    float dist2;

    GetRootPosition(pos, self);

    o = isysGObjSearchFromObjKindID_begin(10);
    dist2 = dist * dist;
    while (o != 0) {
        if (o != self && IsTorchLightOn(o) && o->active != 0) {
            GetRootPosition(pos2, o);
            if (distance_squared(pos2, pos) < dist2) {
                return o;
            }
        }
        o = isysGObjSearchFromObjKindID_next(o);
    }
    return 0;
}

inline void SetTorchLife(GObj *torch, int life)
{
    TorchGeoWork *p = GOBJ_SUB(torch)->work;
    p->life = life;
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

static inline void procChainReaction(GObj *gobj)
{
    TorchGeoWork *w;
    GObj *o;

    w = GOBJ_SUB(gobj)->work;
    if (w->chainFlag == 0) {
        return;
    }
    o = CheckTorchChainReaction(gobj, 20.0f);
    if (o != 0 && chainReactionBlocked(gobj, o) == 0) {
        LightTorchOn(gobj);
    }
}

void TorchGeo(GObj *gobj)
{
    TorchGeoWork *w;
    Sub15C *sub;
    GObj *o;

    sub = gobj->dobj;
    o = sub->parent.obj;
    w = sub->work;
    if (o != 0) {
        if (o->active == 0) {
            LightTorchOff(gobj);
            return;
        }
    }
    if (IsTorchLightOn(gobj) == 0) {
        procChainReaction(gobj);
        return;
    }
    if (w->burnTime < 65535) {
        w->burnTime = w->burnTime + 1;
    }
    if (o != 0) {
        float pos[4];

        GetRootPosition(pos, gobj);
        UpdateRealTimeGeometryValue(gobj);
        moveTorch(gobj, pos);
    }
    if (w->life < w->burnTime) {
        LightTorchOff(gobj);
        procChainReaction(gobj);
    }
}
