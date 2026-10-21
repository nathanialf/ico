#include "typedef.h"
#include "particleEffect.h"
#include "particleLayout.h"
#include "ios.h"
#include "memory.h"

inline void DeleteParticleLayout(GObj *self)
{
    int *q = GOBJ_SUB(self)->work;

    DeleteParticleEffect(q[0]);
}

inline int *InitParticleLayoutGeo(GObj *self, int *layout)
{
    int *r;
    r = iosMallocDebug(ios_partition_sugipon, 4, "src/particleLayout.c", 12);
    *r = SetParticleEffect(layout[12], layout, GOBJ_SUB(self)->quat);
    return r;
}

inline void ParticleLayoutGeo(GObj *self) {}

inline void ParticleLayoutDL(void) {}
