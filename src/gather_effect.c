#include "common.h"

#include "ico/types.h"
struct GEl { int f0; char _4[0x6C]; };
struct GGeo { char _0[0x24]; struct GEl *f24; char _28[8]; int f30; char _34[0x1C]; float f50[4]; float f60; int (*f64)(struct GGeo *); void (*f68)(int); int f6C; };
extern void sceVu0CopyVector(void *dst, void *src);
extern int SetParticleEffect(int no, void *a1, int a2);
extern void *GetParticleEffectData(void *a0);
extern void DisableParticleEffectGeometryControl(int no);
extern int GatherEffect_Proc(struct GGeo *geo);
/* prototypes: their order is the inline tail's emission order */
int GatherEffect_Set(int no, void *a1, int a2, void *goal, void (*endFunc)(int), float speed);
int GatherEffect_InqEnd(int a0);
inline int GatherEffect_Set(int no, void *a1, int a2, void *goal, void (*endFunc)(int), float speed)
{
    struct GGeo *geo;
    int i;
    int id;

    id = SetParticleEffect(no, a1, a2);
    if (id >= 0) {
        geo = (struct GGeo *)GetParticleEffectData((void *)id);
        DisableParticleEffectGeometryControl(id);

        sceVu0CopyVector(geo->f50, goal);
        geo->f60 = speed;
        geo->f64 = GatherEffect_Proc;
        geo->f68 = endFunc;
        geo->f6C = id;

        for (i = 0; i < geo->f30; i++) {
            geo->f24[i].f0 = 1;
        }
    }
    return id;
}
void GatherEffect_SetGoal(int a0, void *a1) {
    if (a0 >= 0) {
        char *v = (char *)GetParticleEffectData(a0);
        sceVu0CopyVector(v + 0x50, a1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/gather_effect", GatherEffect_Proc);
inline int GatherEffect_InqEnd(int a0) {
    int acc = 0;
    if (a0 >= 0) {
        struct GGeo *geo = (struct GGeo *)GetParticleEffectData((void *)a0);
        if (geo == 0) {
            return 1;
        }
        {
            int n = geo->f30;
            int i;
            for (i = 0; i < n; i++) {
                acc |= geo->f24[i].f0;
            }
        }
    }
    return acc == 0;
}
