#include "typedef.h"
#include "particleEffect.h"
#include "particleLayout.h"
#include "ios.h"
#include "memory.h"

inline int *InitParticleLayoutGeo(GObj *self, int *other)
{
    int *r;
    r = iosMallocDebug(ios_partition_sugipon, 4, "src/particleLayout.c", 12);
    *r = SetParticleEffect(other[0x30 / 4], other, GOBJ_SUB(self)->quat);
    return r;
}

inline void DeleteParticleLayout(GObj *a0)
{
    int *q = GOBJ_SUB(a0)->work;
    if (q[0] != -1) {
        DeleteParticleEffect(q[0]);
        q[0] = -1;
    }
}

void ParticleLayoutGeo(GObj *self)
{
    int *q = GOBJ_SUB(self)->work;
    if (q[0] == -1) {
        return;
    }
    if (self->drawMask) {
        return SetParticleEffectPauseFlag(q[0], 0);
    } else {
        return SetParticleEffectPauseFlag(q[0], 1);
    }
}

inline void ParticleLayoutDL(void) {}
