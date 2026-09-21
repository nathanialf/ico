#include "common.h"
#include "particleEffect.h"
#include <libvu0.h>

struct GEl {
    int f0;         /* 0x00 */
    char _4[0xC];   /* 0x04 */
    float f10[4];   /* 0x10 */
    float f20[4];   /* 0x20 */
    char _30[4];    /* 0x30 */
    float f34;      /* 0x34 */
    char _38[4];    /* 0x38 */
    float f3C;      /* 0x3C */
    char _40[0x30]; /* 0x40 */
};

struct GGeo {
    char _0[0x24];
    struct GEl *f24;
    char _28[8];
    int f30;
    char _34[0x1C];
    float f50[4];
    float f60;
    int (*f64)(struct GGeo *);
    void (*f68)(int);
    int f6C;
};

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

void GatherEffect_SetGoal(int a0, void *a1)
{
    if (a0 >= 0) {
        char *v = (char *)GetParticleEffectData(a0);
        sceVu0CopyVector(v + 0x50, a1);
    }
}

/* kept local: ico2/seki/include/Matrix.h carries reconstructed prototypes for
   these two (void return, three arguments) that the call sites refute; the ROM
   here reads a float back from each and passes _GetLength two vectors, the
   same spelling ico2/seki/src/Light.c and ico2/ito/src/queen_barrier_disp.c
   already keep local. */
extern float _GetNorm(void *p);
extern float _GetLength(void *a, void *b);
extern float acosf(float x);

int GatherEffect_Proc(struct GGeo *geo)
{
    float tmp[4];
    float dir[4];
    float add[4];
    float para[4];
    float perp[4];
    float nv[4];
    int flag;
    int i;
    int end;

    flag = 0;

    for (i = 0; i < geo->f30; i++) {
        struct GEl *p = &geo->f24[i];
        float spd;
        float d;
        float ang;
        float inner;

        sceVu0SubVector(tmp, geo->f50, p->f10);
        sceVu0Normalize(dir, tmp);
        inner = sceVu0InnerProduct(dir, p->f20);
        spd = geo->f60;
        if (inner < 0.0f) {
            spd = spd * 1.5f;
        }
        sceVu0ScaleVector(add, dir, spd);
        sceVu0AddVector(p->f20, p->f20, add);

        d = sceVu0InnerProduct(dir, p->f20);
        if (0.0f < d) {
            float n = _GetNorm(p->f20);
            float t;
            sceVu0ScaleVector(para, dir, d);
            sceVu0SubVector(perp, p->f20, para);
            t = _GetLength(p->f10, geo->f50) / (n * 30.0f);
            if (0.98f < t) {
                t = 0.98f;
            }
            sceVu0ScaleVector(perp, perp, t);
            sceVu0AddVector(p->f20, para, perp);
        }

        if (p->f0) {
            sceVu0Normalize(nv, p->f20);
            ang = acosf(sceVu0InnerProduct(nv, dir));
            if (_GetLength(p->f10, geo->f50) <= _GetNorm(p->f20) && ang < 0.5235988f) {
                p->f0 = 0;
            } else {
                sceVu0AddVector(p->f10, p->f10, p->f20);
            }
        }
        if (p->f0 == 0) {
            sceVu0CopyVector(p->f10, geo->f50);
            p->f3C -= 0.02f;
            if (p->f3C < 0.0f) {
                p->f3C = 0.0f;
            }
            p->f34 -= 2.5f;
            if (p->f34 < 0.0f) {
                p->f34 = 0.0f;
            }
        }
        flag |= p->f0;
    }

    end = (flag == 0);
    i = 0; /* RULING-VESTIGIAL-EXCEPTION instance (user-approved 2026-09-21):
              a dead assignment the 2001 source carried. It emits no bytes and
              is the only construct that gives i a later last mention than
              flag, so cse keeps i in the duplicated loop guard, combine
              re-emits the zero at the compare slot and reorg takes it for the
              blez delay slot, as the ROM has it. The same rule (the const-0
              pseudo with the later last mention wins the slot) holds at four
              other ROM sites, and this instruction order is in the August
              2001 prototype, the USA and the PAL builds alike. */

    if (end) {
        if (geo->f68 != 0) {
            geo->f68(geo->f6C);
        }

        debug_StdPrintfDummy("gather effect end\n");
    }

    return !end;
}

inline int GatherEffect_InqEnd(int a0)
{
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
