#include "particleEffect.h"
#include <libvu0.h>
#include "Matrix.h"
#include <math.h>
#include "gather_effect.h"

inline int GatherEffect_Set(int no, void *pos, void *quat, void *goal, float speed,
                            void (*endFunc)(int))
{
    struct GGeo *geo;
    int i;
    int id;

    id = SetParticleEffect(no, pos, quat);
    if (id >= 0) {
        geo = (struct GGeo *)GetParticleEffectData(id);
        DisableParticleEffectGeometryControl(id);

        sceVu0CopyVector(geo->goal, goal);
        geo->speed = speed;
        geo->proc = GatherEffect_Proc;
        geo->endFunc = endFunc;
        geo->id = id;

        for (i = 0; i < geo->n; i++) {
            geo->parts[i].moving = 1;
        }
    }
    return id;
}

void GatherEffect_SetGoal(int a0, void *a1)
{
    if (a0 >= 0) {
        struct GGeo *geo = (struct GGeo *)GetParticleEffectData(a0);
        sceVu0CopyVector(geo->goal, a1);
    }
}

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

    for (i = 0; i < geo->n; i++) {
        struct GEl *p = &geo->parts[i];
        float spd;
        float d;
        float ang;
        float inner;

        sceVu0SubVector(tmp, geo->goal, p->pos);
        sceVu0Normalize(dir, tmp);
        inner = sceVu0InnerProduct(dir, p->vel);
        spd = geo->speed;
        if (inner < 0.0f) {
            spd = spd * 1.5f;
        }
        sceVu0ScaleVector(add, dir, spd);
        sceVu0AddVector(p->vel, p->vel, add);

        d = sceVu0InnerProduct(dir, p->vel);
        if (0.0f < d) {
            float n = _GetNorm(p->vel);
            float t;
            sceVu0ScaleVector(para, dir, d);
            sceVu0SubVector(perp, p->vel, para);
            t = _GetLength(p->pos, geo->goal) / (n * 30.0f);
            if (0.98f < t) {
                t = 0.98f;
            }
            sceVu0ScaleVector(perp, perp, t);
            sceVu0AddVector(p->vel, para, perp);
        }

        if (p->moving) {
            sceVu0Normalize(nv, p->vel);
            ang = acosf(sceVu0InnerProduct(nv, dir));
            if (_GetLength(p->pos, geo->goal) <= _GetNorm(p->vel) && ang < 0.5235988f) {
                p->moving = 0;
            } else {
                sceVu0AddVector(p->pos, p->pos, p->vel);
            }
        }
        if (p->moving == 0) {
            sceVu0CopyVector(p->pos, geo->goal);
            p->alpha -= 0.02f;
            if (p->alpha < 0.0f) {
                p->alpha = 0.0f;
            }
            p->size -= 2.5f;
            if (p->size < 0.0f) {
                p->size = 0.0f;
            }
        }
        flag |= p->moving;
    }

    end = (flag == 0);

    if (end) {
        if (geo->endFunc != 0) {
            geo->endFunc(geo->id);
        }

        debug_StdPrintfDummy("gather effect end\n");
    }

    /* the loop counter carries the result out */
    i = !end;
    return i;
}

inline int GatherEffect_InqEnd(int a0)
{
    int acc = 0;
    if (a0 >= 0) {
        struct GGeo *geo = (struct GGeo *)GetParticleEffectData(a0);
        if (geo == 0) {
            return 1;
        }
        {
            int n = geo->n;
            int i;
            for (i = 0; i < n; i++) {
                acc |= geo->parts[i].moving;
            }
        }
    }
    return acc == 0;
}
