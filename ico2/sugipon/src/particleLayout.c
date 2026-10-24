#include "typedef.h"
#include "particleEffect.h"
#include "particleLayout.h"
#include "ios.h"
#include "memory.h"

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void DeleteParticleLayout(GObj *self)
{
    int *q = GOBJ_SUB(self)->work;

    DeleteParticleEffect(q[0]);
}
#endif

inline int *InitParticleLayoutGeo(GObj *self, int *layout)
{
    int *r;
    r = iosMallocDebug(ios_partition_sugipon, 4, "src/particleLayout.c", 12);
    *r = SetParticleEffect(layout[12], layout, GOBJ_SUB(self)->quat);
    return r;
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void ParticleLayoutGeo(GObj *self) {}
#else
inline void DeleteParticleLayout(GObj *self)
{
    int *q = GOBJ_SUB(self)->work;
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
#endif

inline void ParticleLayoutDL(void) {}
