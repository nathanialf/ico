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
    /* 0x04 */ int pad04[3];
    /* 0x10 */ float pos[4];
    /* 0x20 */ int lightOn;
    /* 0x24 */ int burnTime; /* frames the torch has been alight */
    /* 0x28 */ int life;
    /* 0x2C */ int lifeMax;
    /* 0x30 */ int chainFlag;
    /* 0x34 */ int effect[5]; /* the particle effects a lit torch runs, -1 when off */
    /* 0x48 */ int pad48[2];
} __attribute__((aligned(16))) TorchGeoWork;

/* torch.o's whole .data run: the torch work record InitTorchGeo starts every
   torch from.  The 0x50 malloc right above the copy proves the size. */
static TorchGeoWork emptyTorchWork = {
    0, {0}, {0.0f, 0.0f, 0.0f, 1.0f}, 0, 0, 65536, 65536, 0, {-1, -1, -1, -1, -1}, {0},
};

#include "torch.h"
#include <libvu0.h>
#include "particleEffect.h"
#include "ios.h"
#include "main.h"
#include "sceneManager.h"

inline void SetTorchChainReactionFlag(GObj *a0, int a1)
{
    TorchGeoWork *w = GOBJ_SUB(a0)->work;

    w->chainFlag = a1;
}

void torchOffSE(GObj *a0)
{
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x43);
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
        o = (char *)isysGObjSearchFromObjKindID_begin(10);
        while (o != 0) {
            TorchGeoWork *ow = GOBJ_SUB(o)->work;
            if (o != gobj && ow->flags == 2) {
                if (IsTorchLightOn(o)) {
                    n++;
                }
            }
            o = (char *)isysGObjSearchFromObjKindID_next(o);
        }
        if (n > 0) {
            return;
        }
        w->effect[1] =
            SetParticleEffectByPartition(0x15, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[4] =
            SetParticleEffectByPartition(0x13, pos, IdentityQuaternion, ios_partition_seki);
        break;
    case 4:
        w->effect[0] =
            SetParticleEffectByPartition(0x17, pos, IdentityQuaternion, ios_partition_seki);
        break;
    default:
        w->effect[3] = SetParticleEffectByPartition(7, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[0] = SetParticleEffectByPartition(5, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[1] = SetParticleEffectByPartition(9, pos, IdentityQuaternion, ios_partition_seki);
        w->effect[4] =
            SetParticleEffectByPartition(0x13, pos, IdentityQuaternion, ios_partition_seki);
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

void torchDrainControl(GObj *gobj, float level)
{
    TorchGeoWork *w = GOBJ_SUB(gobj)->work;

    if (w->effect[3] != -1) {
        SetParticleEffectDrainLevel(w->effect[3], level);
    }
    if (w->effect[2] != -1) {
        SetParticleEffectDrainLevel(w->effect[2], level);
    }
    if (w->effect[0] != -1) {
        SetParticleEffectDrainLevel(w->effect[0], level);
    }
    if (w->effect[1] != -1) {
        SetParticleEffectDrainLevel(w->effect[1], level);
    }
    if (w->effect[4] != -1) {
        SetParticleEffectDrainLevel(w->effect[4], level);
    }
}

void moveTorch(GObj *gobj, void *mtx)
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

void setPauseFlag(GObj *gobj, int flag)
{
    TorchGeoWork *w = GOBJ_SUB(gobj)->work;

    if (w->effect[3] != -1) {
        SetParticleEffectPauseFlag(w->effect[3], flag);
    }
    if (w->effect[2] != -1) {
        SetParticleEffectPauseFlag(w->effect[2], flag);
    }
    if (w->effect[0] != -1) {
        SetParticleEffectPauseFlag(w->effect[0], flag);
    }
    if (w->effect[1] != -1) {
        SetParticleEffectPauseFlag(w->effect[1], flag);
    }
    if (w->effect[4] != -1) {
        SetParticleEffectPauseFlag(w->effect[4], flag);
    }
}

inline int IsTorchLightOn(GObj *a0)
{
    return *(int *)((char *)GOBJ_SUB(a0)->work + 0x20);
}

inline void SetTorchLife(GObj *a0, int a1, int a2)
{
    char *p = GOBJ_SUB(a0)->work;
    *(int *)(p + 0x28) = a1;
    *(int *)(p + 0x2C) = a1 - a2;
}

inline char *InitTorchGeo(GObj *a0, SObjSimpleSetting *a1)
{
    TorchGeoWork *p = (TorchGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x50, __FILE__, 232);
    *p = emptyTorchWork;
    sceVu0UnitMatrix((char *)*(void **)(((char *)a0) + 0x15C) + 0x20);
    *(void **)((char *)*(void **)(((char *)a0) + 0x15C) + 0x830) = p;
    if (a1->obj & 1) {
        LightTorchOn(a0);
    } else {
        *(int *)((char *)*(void **)(((char *)a0) + 0x15C) + 0x83C) = 0;
    }
    p->flags = a1->obj & ~1;
    GetRootPosition(p->pos, a0);
    return (char *)p;
}

inline char *CheckTorchChainReaction(GObj *a0, float dist)
{
    float pos[4];
    float pos2[4];
    char *o;
    float dist2;

    GetRootPosition(pos, a0);

    o = (char *)isysGObjSearchFromObjKindID_begin(10);
    dist2 = dist * dist;
    while (o != 0) {
        TorchGeoWork *w = GOBJ_SUB(o)->work;
        if (o != a0 && IsTorchLightOn(o) && *(int *)(o + 0x16C) != 0 && w->flags != 2) {
            GetRootPosition(pos2, o);
            if (distance_squared(pos2, pos) < dist2) {
                return o;
            }
        }
        o = (char *)isysGObjSearchFromObjKindID_next(o);
    }
    return 0;
}

char *CheckTorchChainReactionReverse(GObj *a0, float dist)
{
    float pos[4];
    float pos2[4];
    GObj *o;
    char *p;
    int n;
    int lit;

    n = 0;
    GetRootPosition(pos, a0);

    o = (char *)isysGObjSearchFromObjKindID_begin(10);
    while (o != 0) {
        TorchGeoWork *w = GOBJ_SUB(o)->work;
        if (w->flags == 2) {
            if (IsTorchLightOn(o)) {
                n++;
            }
        }
        o = (char *)isysGObjSearchFromObjKindID_next(o);
    }

    dist = dist * dist;
    lit = 0 < n;
    p = (char *)isysGObjSearchFromObjKindID_begin(10);
    while (p != 0) {
        if (p != a0 && IsTorchLightOn(p) == 0 && *(int *)(p + 0x16C) != 0 &&
            (((TorchGeoWork *)(char *)GOBJ_SUB(p)->work)->flags != 2 || lit == 0)) {
            GetRootPosition(pos2, p);
            if (distance_squared(pos2, pos) < dist) {
                return p;
            }
        }
        p = (char *)isysGObjSearchFromObjKindID_next(p);
    }
    return 0;
}

inline void UpdateRealTimeGeometryValue(GObj *a0)
{
    int buf[4];
    char *sub;
    GetRootPosition(buf, a0);
    sub = *(char **)(((char *)a0) + 0x15C);
    sceVu0SubVector(sub + 0x130, buf, sub + 0x1F0);
    sub = *(char **)(((char *)a0) + 0x15C);
    CopyVector(sub + 0x1F0, buf);
}

/* static helper the listing places at torch.c lines 347-374; never emitted out
 * of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int chainReactionBlocked(char *gobj, char *other)
{
    char *p;
    char *q;
    int a;
    int b;

    b = *(int *)*(char **)(gobj + 0x15C);
    a = *(int *)*(char **)(other + 0x15C);
    if (girlGObj != 0) {
        q = *(char **)((char *)girlGObj + 0x164);
        if (b != 0 && b == *(int *)(q + 0x154)) {
            /* tried to light the heroine's bomb */
            debug_StdPrintfDummy("ヒロインの爆弾に点火しようとした\n");
            return 1;
        }
    }
    if (b != 0 && a != 0) {
        p = *(char **)((char *)boyGObj + 0x164);
        if (ACTGame_NoWeapon(boyGObj) == 0 && a == *(int *)(p + 0x150) &&
            b == *(int *)(p + 0x154)) {
            /* an exception came up while lighting */
            debug_StdPrintfDummy("点火の例外処理発生\n");
            return 1;
        }
    }
    return 0;
}

void procChainReaction(GObj *gobj)
{
    TorchGeoWork *w;
    char *o;

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
    char *sub;
    char *o;
    float drain;
    int id;

    sub = *(char **)(((char *)gobj) + 0x15C);
    o = *(char **)sub;
    w = *(TorchGeoWork **)(sub + 0x830);
    if (o != 0) {
        if (*(int *)(o + 0x16C) == 0) {
            LightTorchOff(gobj);
            return;
        }
        GetRootPosition(w->pos, gobj);
    }
    if (IsTorchLightOn(gobj) == 0) {
        procChainReaction(gobj);
        return;
    }
    if (*(int *)(((char *)gobj) + 0x50) != 0) {
        setPauseFlag(gobj, 0);
    } else {
        setPauseFlag(gobj, 1);
    }
    if (w->burnTime < 0xFFFF) {
        w->burnTime = w->burnTime + 1;
    }
    if (o != 0) {
        UpdateRealTimeGeometryValue(gobj);
        moveTorch(gobj, w->pos);
    }
    if (w->life < w->burnTime) {
        LightTorchOff(gobj);
        procChainReaction(gobj);
        return;
    }
    if (w->chainFlag == 0 && w->lifeMax < w->burnTime) {
        drain = (float)(w->burnTime - w->lifeMax) / (float)(w->life - w->lifeMax);
        torchDrainControl(gobj, 1.0f - drain);
        if (w->burnTime == w->life - 1) {
            id = SetParticleEffectActiveSensing(0x36, w->pos, IdentityQuaternion);
            if (id != -1) {
                ExecParticleEffect(id);
            }
        }
    }
}

inline void TorchDL(void) {}
