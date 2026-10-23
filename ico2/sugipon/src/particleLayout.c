#include "typedef.h"
#include "particleEffect.h"
#include "particleLayout.h"
#include "ios.h"
#include "memory.h"
#include "include_asm.h"

inline int *InitParticleLayoutGeo(GObj *self, int *layout)
{
    int *r;
    r = iosMallocDebug(ios_partition_sugipon, 4, "src/particleLayout.c", 12);
    *r = SetParticleEffect(layout[12], layout, GOBJ_SUB(self)->quat);
    return r;
}

INCLUDE_ASM(DeleteParticleLayout);

inline void ParticleLayoutGeo(GObj *self) {}

inline void ParticleLayoutDL(void) {}
