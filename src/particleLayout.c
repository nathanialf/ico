#include "common.h"

#include "ico/types.h"

extern char D_006209C0[];
extern int D_0063A438;
extern void DeleteParticleEffect(int a0);
/* prototypes: their order is the inline tail's emission order */
int *InitParticleLayoutGeo(char *self, int *other);
void ParticleLayoutDL(void);
void DeleteParticleLayout(char *a0);
inline int *InitParticleLayoutGeo(char *self, int *other) {
    int *r;
    r = iosMallocDebug(D_0063A438, 4, D_006209C0, 0xC);
    *r = SetParticleEffect(other[0x30 / 4], other, *(char **)(self + 0x15C) + 0x60);
    return r;
}
inline void DeleteParticleLayout(char *a0) {
    int *q = *(int **)(*(char **)(a0 + 0x15C) + 0x830);
    if (q[0] != -1) {
        DeleteParticleEffect(q[0]);
        q[0] = -1;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/particleLayout", ParticleLayoutGeo);
inline void ParticleLayoutDL(void) {}
