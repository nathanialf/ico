#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include "lws_kyomi.h"
#include "Basic.h"
#include "Light.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "particleEffect.h"
#include "quaternion.h"
#include "tableSin.h"
#include <stdio.h>
#include <string.h>

/* .data, carved VMA 0x4EE5B0..0x4EE5F0, bytes verified against
   baserom/pal/baseelf.rom.  D_004EE5B0 is the 0x30-byte default record
   bga_InitData block-copies into its mallocseki() allocation (two
   (0,0,0,1.0f) vectors then four words); D_004EE5E0 is the (0,0,0,1.0f)
   position vector bga_ApplyDObject hands to
   SetParticleEffectActiveSensing. */
typedef struct BgaAnimDefault {
    /* 0x00 */ VECTOR pos;
    /* 0x10 */ VECTOR quat;
    /* 0x20 */ int obj;
    /* 0x24 */ int idx;
    /* 0x28 */ int root;
    /* 0x2C */ int f2C;
} BgaAnimDefault;

BgaAnimDefault D_004EE5B0 = {
    {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 0, -1, 1, 0,
};

float D_004EE5E0[4] = {0.0f, 0.0f, 0.0f, 1.0f};

struct BgaLightEnv;

typedef struct BgaEnvEnt {
    /* 0x00 */ unsigned short type;
    /* 0x02 */ short f02;
    /* 0x04 */ unsigned char *data;
} BgaEnvEnt;

typedef struct BgaDObjEnt {
    /* 0x00 */ unsigned short type;
    /* 0x02 */ unsigned short num;
    /* 0x04 */ char name[0x20];
    /* 0x24 */ union {
        void *obj;                 /* particle record, geometry, Kyomi object */
        struct BgaLightEnv *light; /* ambient-light record */
        int next;                  /* the file's flat list, consumed by bga_InitData */
    } u;
    /* 0x28 */ int env;
    /* 0x2C */ struct BgaDObjEnt *f2C;
    /* 0x30 */ struct BgaDObjEnt *f30;
    /* 0x34 */ int f34;
    /* 0x38 */ char pad38[0xC];
    /* 0x44 */ short parent;
    /* 0x46 */ short f46;
} BgaDObjEnt;

typedef struct BgaKey {
    /* 0x00 */ float v[6];
    /* 0x18 */ float f18;
    /* 0x1C */ float f1C;
    /* 0x20 */ int f20;
    /* 0x24 */ int time;
} BgaKey;

typedef struct BgaMotion {
    /* 0x00 */ BgaKey *key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaMotion;

extern char D_00621580[];
extern char D_00621598[];
extern char D_0063BCD0[];
extern char D_0063BCD8[];

/* Listing rows 806-890 of BgAnimation.c: four static helpers the January
   link inlines whole into bga_InitData and that carry no symbol of their
   own.  Their names are ours. */

static inline void bga_addSiblingTail(BgaDObjEnt *c, BgaDObjEnt *d)
{
    while (c->f30 != 0) {
        c = c->f30;
    }
    c->f30 = d;
}

static inline void bga_linkToParent(BgaDObjEnt *q, BgaDObjEnt *d, int no)
{
    do {
        if (q->num == no) {
            if (q->f2C == 0) {
                q->f2C = d;
            } else {
                bga_addSiblingTail(q->f2C, d);
            }
        }
        if (q->u.next == 0) {
            break;
        }
        q = (BgaDObjEnt *)q->u.next;
    } while (1);
}

static inline void bga_linkTree(char *p)
{
    BgaDObjEnt *d;
    int no;

    d = (BgaDObjEnt *)*(int *)(p + 0xC);
    do {
        no = d->parent;
        if (no != -1) {
            bga_linkToParent((BgaDObjEnt *)*(int *)(p + 0xC), d, no);
        }
        if (d->u.next == 0) {
            break;
        }
        d = (BgaDObjEnt *)d->u.next;
    } while (1);
}

static inline void bga_makeRootList(char *p)
{
    BgaDObjEnt *d;
    int n;

    d = (BgaDObjEnt *)*(int *)(p + 0xC);
    n = 0;
    do {
        if (d->parent == -1) {
            n++;
        }
    } while ((d = (BgaDObjEnt *)d->u.next) != 0);

    *(int *)(p + 0x10) = mallocseki((n + 1) * 4);
    ((int *)*(int *)(p + 0x10))[n] = 0;
    d = (BgaDObjEnt *)*(int *)(p + 0xC);
    n = 0;
    do {
        if (d->parent == -1) {
            ((int *)*(int *)(p + 0x10))[n] = (int)d;
            n++;
        }
        if (d->u.next == 0) {
            break;
        }
        d = (BgaDObjEnt *)d->u.next;
    } while (1);
}

char *bga_InitData(char *p)
{
    BgaDObjEnt *d;
    int i;
    unsigned int j;
    int k;

    if (strncmp(p, D_0063BCD0, 3) != 0) {
        debug_StdPrintfDummy(D_00621580);
        debug_assert(D_00621598, 952);
        __assert(D_00621598, 952, D_0063BCD8);
    }
    *(int *)(p + 0xC) += (int)p;
    p[0xA] = -1;
    *(BgaAnimDefault **)(p + 0x24) = (BgaAnimDefault *)mallocseki(sizeof(BgaAnimDefault));
    **(BgaAnimDefault **)(p + 0x24) = D_004EE5B0;
    d = (BgaDObjEnt *)*(int *)(p + 0xC);
    while (1) {
        d->f34 += (int)p;
        if (d->env != 0) {
            i = 0;
            d->env += (int)p;
            while (((BgaEnvEnt *)d->env)[i].data != 0) {
                ((BgaEnvEnt *)d->env)[i].data += (int)p;
                switch (((BgaEnvEnt *)d->env)[i].type) {
                case 0:
                case 1:
                case 2:
                case 3:
                    *(int *)((BgaEnvEnt *)d->env)[i].data += (int)p;
                    break;
                case 6:
                    *(int *)((BgaEnvEnt *)d->env)[i].data += (int)p;
                    for (j = 0; j < ((BgaMotion *)((BgaEnvEnt *)d->env)[i].data)->n; j++) {
                        float sum = 0.0f;
                        float scale = 1.0f;
                        float *v = ((BgaMotion *)((BgaEnvEnt *)d->env)[i].data)->key[j].v;

                        for (k = 0; k < 6; k++) {
                            if (v[k] < 0.0f) {
                                sum -= v[k];
                            } else {
                                sum += v[k];
                            }
                        }
                        if (sum != 0.0f) {
                            scale = 1.0f / sum;
                        }
                        for (k = 0; k < 6; k++) {
                            float t = v[k] * scale;

                            if (t < 0.0f) {
                                v[k] = v[k] * -t;
                            } else {
                                v[k] = v[k] * t;
                            }
                        }
                    }
                    break;
                case 4:
                case 5:
                case 7:
                case 8:
                case 9:
                    break;
                }
                i++;
            }
        }
        if (d->u.next == 0) {
            break;
        }
        d->u.next += (int)p;
        d = (BgaDObjEnt *)d->u.next;
    }
    bga_makeRootList(p);
    bga_linkTree(p);
    return p;
}

typedef struct BgaGeom {
    /* 0x000 */ int f00;
    /* 0x004 */ int f04;
    /* 0x008 */ int f08;
    /* 0x00C */ char pad0C[0x848];
    /* 0x854 */ char *name;
} BgaGeom;

typedef struct BgaGObj {
    /* 0x000 */ char pad00[0x15C];
    /* 0x15C */ void *geom;
} BgaGObj;

/* The particle entry's word at +0x20 packs three fields: the loop flag in
   bits 0-1, the effect handle in bits 2-16 and the particle id in bits
   17-31.  The union with the 8-byte word is what the record is: the ROM
   reads and writes the whole doubleword (ld/sd) at every one of these
   sites, and the int bitfields inside it give the sign-extending 15-bit
   extraction the ROM uses for the id. */
typedef union BgaParticleBits {
    struct {
        int loop : 2;
        int eff : 15;
        int id : 15;
    } b;

    long long w;
} BgaParticleBits;

typedef struct BgaParticleEnt {
    /* 0x00 */ char pad00[0x20];
    /* 0x20 */ BgaParticleBits u;
} BgaParticleEnt;

extern int D_0063A44C;
extern char D_00621638[];
extern char D_00621658[];
extern char D_0063BCF0[];
extern char D_0063BCE8[];

typedef struct BgaLightEnv {
    /* 0x00 */ char pad00[0x20];
    /* 0x20 */ float col[4];
    /* 0x30 */ char pad30[0x10];
    /* 0x40 */ float col2[4];
    /* 0x50 */ float f50;
    /* 0x54 */ float f54;
    /* 0x58 */ float f58;
    /* 0x5C */ int f5C;
    /* 0x60 */ float f60;
    /* 0x64 */ float f64;
    /* 0x68 */ float f68;
} BgaLightEnv;

extern char D_006215F8[];
extern char D_00621618[];

void bga_initLightEnvelope(BgaDObjEnt *p)
{
    BgaEnvEnt *e;
    unsigned char *d;

    e = (BgaEnvEnt *)p->env;
    if (e == 0) {
        return;
    }
    while ((d = e->data) != 0) {
        switch (e->type) {
        case 4:
            switch (p->type) {
            case 6:
            case 11:
                if (p->u.light != 0) {
                    p->u.light->col[0] = (float)d[0] / 255.0f;
                    p->u.light->col[1] = (float)d[1] / 255.0f;
                    p->u.light->col[2] = (float)d[2] / 255.0f;
                    p->u.light->col[3] = 1.0f;
                } else {
                    debug_Assert(D_006215F8);
                    debug_assert(D_00621598, 1089);
                    __assert(D_00621598, 1089, D_0063BCE8);
                }
                break;
            case 7:
            case 8:
            case 9:
                if (p->u.light != 0) {
                    p->u.light->col2[0] = (float)d[0] / 255.0f;
                    p->u.light->col2[1] = (float)d[1] / 255.0f;
                    p->u.light->col2[2] = (float)d[2] / 255.0f;
                    p->u.light->col2[3] = 1.0f;
                } else {
                    debug_Assert(D_00621618);
                    debug_assert(D_00621598, 1109);
                    __assert(D_00621598, 1109, D_0063BCE8);
                }
                break;
            }
            break;
        case 5:
            switch (p->type) {
            case 8:
            case 9:
                if (p->u.light != 0) {
                    p->u.light->f50 = 1.0f / (((float *)d)[0] * 50.0f);
                    p->u.light->f54 = 1.0f / (((float *)d)[1] * 50.0f);
                    p->u.light->f58 = 1.0f / (((float *)d)[2] * 50.0f);
                    p->u.light->f60 = 1.0f / (((float *)d)[3] * 50.0f);
                    p->u.light->f64 = 1.0f / (((float *)d)[4] * 50.0f);
                    p->u.light->f68 = 1.0f / (((float *)d)[5] * 50.0f);
                } else {
                    debug_assert(D_00621598, 1141);
                    __assert(D_00621598, 1141, D_0063BCE8);
                }
                break;
            }
            break;
        /* A third arm above 5 with an empty body: the ROM's dispatch is the
           three-test tree balance_case_nodes only builds for more than two
           case values (== 5, then >= 6 to the default, then == 4), and jump
           optimisation then deletes this arm's own test because its label is
           the switch end.  That makes the value itself unobservable; 6 is the
           next envelope type. */
        case 6:
            break;
        }
        e++;
    }
}

void bga_ApplyDObject(BgaDObjEnt *p, void **objs, int n, int no)
{
    char buf[1024];
    int i;

    switch (p->type) {
    case 13:
        i = GetParticleIDWithName(p->name);
        if (i != -1) {
            p->u.obj = iosMallocDebug(D_0063A44C, 0x30, D_00621598, 1177);
            ((BgaParticleEnt *)p->u.obj)->u.b.id = i;
            ((BgaParticleEnt *)p->u.obj)->u.b.loop =
                GetParticleLoopFlag(((BgaParticleEnt *)p->u.obj)->u.b.id);
            if (((BgaParticleEnt *)p->u.obj)->u.b.loop) {
                ((BgaParticleEnt *)p->u.obj)->u.b.eff = SetParticleEffectActiveSensing(
                    ((BgaParticleEnt *)p->u.obj)->u.b.id, D_004EE5E0, IdentityQuaternion);
            } else {
                ((BgaParticleEnt *)p->u.obj)->u.b.eff = -1;
            }
            break;
        }
    case 1:
    case 2:
    case 5:
        p->u.obj = 0;
        break;
    case 0:
    case 4:
    case 10:
        p->u.obj = 0;
        for (i = 0; i < n; i++) {
            if (((BgaGeom *)((BgaGObj *)objs[i])->geom)->name == 0) {
                sprintf(buf, D_00621638, p->name);
                debug_StdPrintfDummy(D_00621658, p->name);
                debug_assertMessage(D_00621598, 1201, buf);
                __assert(D_00621598, 1201, D_0063BCF0);
            }
            if (strcmp(((BgaGeom *)((BgaGObj *)objs[i])->geom)->name, p->name) == 0) {
                p->u.obj = ((BgaGObj *)objs[i])->geom;
                p->num = ((BgaGeom *)((BgaGObj *)objs[i])->geom)->f08++;
            }
        }
        break;
    case 7:
        p->u.obj = light_AddAmbientObject(0);
        bga_initLightEnvelope(p);
        break;
    case 8:
        p->u.obj = light_AddAmbientObject(2);
        bga_initLightEnvelope(p);
        break;
    case 9:
        p->u.obj = light_AddAmbientObject(1);
        bga_initLightEnvelope(p);
        break;
    case 12:
        p->u.obj = CreateKyomiGObj(no);
        break;
    }
    if (p->f2C) {
        bga_ApplyDObject(p->f2C, objs, n, no);
    }
    if (p->f30) {
        bga_ApplyDObject(p->f30, objs, n, no);
    }
}

extern int D_0028F4C0[];

static inline int bga_findKey(BgaKey *k, int n, float f)
{
    int lo = 0;
    int hi = n - 1;

    if (f < (float)k[0].time) {
        return 0;
    }
    if (hi < 2) {
        return 0;
    }
    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if ((float)k[mid].time <= f && f < (float)k[mid + 1].time) {
            return mid;
        }
        if ((float)k[mid + 1].time <= f) {
            lo = mid + 1;
        } else if (f <= (float)k[mid].time) {
            hi = mid - 1;
        }
        if (lo == hi) {
            return lo;
        }
    }
    return 0;
}

static inline void bga_hermite(float t, float *h0, float *h1, float *h2, float *h3)
{
    float s = t * t;
    float c = t * s;
    float b = s * 3.0f - c - c;

    *h0 = 1.0f - b;
    *h1 = b;
    *h3 = c - s;
    *h2 = *h3 - s + t;
}

/* The particle motion's key: a position, a rotation in degrees, the three
   colour weights, the two tangent weights, the linear flag and the frame the
   key sits on.  Field names are ours.  bga_GetMotion, bga_GetMotionParticle
   and bga_GetMotionLightning all read this 0x34-byte record. */
typedef struct BgaPtKey {
    /* 0x00 */ float pos[3];
    /* 0x0C */ float rot[3];
    /* 0x18 */ float col[3];
    /* 0x24 */ float f24;
    /* 0x28 */ float f28;
    /* 0x2C */ int linear;
    /* 0x30 */ int time;
} BgaPtKey;

typedef struct BgaPtMotion {
    /* 0x00 */ BgaPtKey *key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaPtMotion;

static inline int bga_findPtKey(BgaPtKey *k, int n, float f)
{
    int lo = 0;
    int hi = n - 1;

    if (f < (float)k[0].time) {
        return 0;
    }
    if (hi < 2) {
        return 0;
    }
    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if ((float)k[mid].time <= f && f < (float)k[mid + 1].time) {
            return mid;
        }
        if ((float)k[mid + 1].time <= f) {
            lo = mid + 1;
        } else if (f <= (float)k[mid].time) {
            hi = mid - 1;
        }
        if (lo == hi) {
            return lo;
        }
    }
    return 0;
}

void bga_GetMotion(float *pos, int *rot, float *col, BgaPtMotion *m)
{
    BgaPtKey *k;
    BgaPtKey *k1;
    float f;
    float u;
    float s0;
    float s1;
    float dv;
    float m0;
    float m1;
    int i;
    int d;

    f = m->frame;
    if (D_0028F4C0[0]) {
        f *= 1.2075409f;
    }

    if (m->n == 1) {
        BgaPtKey *p = m->key;

        pos[0] = p->pos[0];
        pos[1] = p->pos[1];
        pos[2] = p->pos[2];
        pos[3] = 1.0f;
        rot[0] = (short)(p->rot[0] * (65536.0f / 360.0f));
        rot[1] = (short)(p->rot[1] * (65536.0f / 360.0f));
        rot[2] = (short)(p->rot[2] * (65536.0f / 360.0f));
        col[0] = p->col[0];
        col[1] = p->col[1];
        col[2] = p->col[2];
        return;
    }

    k = m->key;
    s0 = 0.0f;
    s1 = 0.0f;
    k = &k[bga_findPtKey(k, m->n, f)];
    k1 = k + 1;
    f -= (float)k->time;
    d = k1->time - k->time;
    u = f / (float)d;

    if (k1->linear == 0) {
        float h00;
        float h01;
        float h10;
        float h11;
        float ta;
        float tb;
        float tc;
        float td;

        ta = (1.0f - k->f24) * (k->f28 + 1.0f);
        tb = (1.0f - k->f24) * (1.0f - k->f28);
        tc = (1.0f - k1->f24) * (1.0f - k1->f28);
        td = (1.0f - k1->f24) * (k1->f28 + 1.0f);
        bga_hermite(u, &h00, &h01, &h10, &h11);
        if (k->time != 0) {
            s0 = (float)d / (float)(k1->time - k[-1].time);
        }
        if (k1->time < m->len) {
            s1 = (float)d / (float)(k1[1].time - k->time);
        }

        for (i = 0; i < 3; i++) {
            dv = k1->pos[i] - k->pos[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->pos[i] - k[-1].pos[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].pos[i] - k1->pos[i]));
            }
            pos[i] = k->pos[i] * h00 + k1->pos[i] * h01 + m0 * h10 + m1 * h11;
        }
        for (i = 0; i < 3; i++) {
            dv = k1->rot[i] - k->rot[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->rot[i] - k[-1].rot[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].rot[i] - k1->rot[i]));
            }
            rot[i] = (short)((k->rot[i] * h00 + k1->rot[i] * h01 + m0 * h10 + m1 * h11) *
                             (65536.0f / 360.0f));
        }
        for (i = 0; i < 3; i++) {
            dv = k1->col[i] - k->col[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->col[i] - k[-1].col[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].col[i] - k1->col[i]));
            }
            col[i] = k->col[i] * h00 + k1->col[i] * h01 + m0 * h10 + m1 * h11;
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (k->rot[i] < 0.0f ? -k->rot[i] < 0.1f : k->rot[i] < 0.1f) {
                k->rot[i] = 0.0f;
            }
            if (k1->rot[i] < 0.0f ? -k1->rot[i] < 0.1f : k1->rot[i] < 0.1f) {
                k1->rot[i] = 0.0f;
            }
            dv = k1->pos[i] - k->pos[i];
            pos[i] = k->pos[i] + u * dv;
            dv = k1->rot[i] - k->rot[i];
            rot[i] = (short)((k->rot[i] + (180.0f < u * dv
                                               ? u * dv - 360.0f
                                               : (u * dv < -180.0f ? u * dv + 360.0f : u * dv))) *
                             (65536.0f / 360.0f));
            dv = k1->col[i] - k->col[i];
            col[i] = k->col[i] + u * dv;
        }
    }
    pos[3] = 1.0f;
    col[3] = 1.0f;
}

void bga_GetMotionParticle(float *pos, int *rot, float *col, BgaPtMotion *m)
{
    BgaPtKey *k;
    BgaPtKey *k1;
    float f;
    float u;
    float s0;
    float s1;
    float dv;
    float m0;
    float m1;
    int i;
    int d;
    float w[2][4];

    f = m->frame;
    if (D_0028F4C0[0]) {
        f *= 1.2075409f;
    }

    if (m->n == 1) {
        BgaPtKey *p = m->key;

        pos[0] = p->pos[0];
        pos[1] = p->pos[1];
        pos[2] = p->pos[2];
        pos[3] = 1.0f;
        rot[0] = (short)(p->rot[0] * (65536.0f / 360.0f));
        rot[1] = (short)(p->rot[1] * (65536.0f / 360.0f));
        rot[2] = (short)(p->rot[2] * (65536.0f / 360.0f));
        col[0] = p->col[0];
        col[1] = p->col[1];
        col[2] = p->col[2];
        return;
    }

    k = m->key;
    s0 = 0.0f;
    s1 = 0.0f;
    k = &k[bga_findPtKey(k, m->n, f)];
    k1 = k + 1;
    f -= (float)k->time;
    d = k1->time - k->time;
    u = f / (float)d;

    {
        float *q = &w[0][0];
        BgaPtKey *e = k;

        for (i = 0; i < 2; i++) {
            float s = e->col[0] + e->col[1] + e->col[2];

            if (4.0f < s) {
                q[1] = 1.0f;
                q[0] = q[2] = 0.0f;
            } else if (0.0f < s && s <= 4.0f) {
                q[0] = 1.0f;
                q[2] = 0.0f;
                q[1] = 0.0f;
            } else {
                q[0] = q[1] = q[2] = 0.0f;
            }
            q += 4;
            e++;
        }
    }

    if (k1->linear == 0) {
        float h00;
        float h01;
        float h10;
        float h11;
        float ta;
        float tb;
        float tc;
        float td;

        ta = (1.0f - k->f24) * (k->f28 + 1.0f);
        tb = (1.0f - k->f24) * (1.0f - k->f28);
        tc = (1.0f - k1->f24) * (1.0f - k1->f28);
        td = (1.0f - k1->f24) * (k1->f28 + 1.0f);
        bga_hermite(u, &h00, &h01, &h10, &h11);
        if (k->time != 0) {
            s0 = (float)d / (float)(k1->time - k[-1].time);
        }
        if (k1->time < m->len) {
            s1 = (float)d / (float)(k1[1].time - k->time);
        }

        for (i = 0; i < 3; i++) {
            dv = k1->pos[i] - k->pos[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->pos[i] - k[-1].pos[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].pos[i] - k1->pos[i]));
            }
            pos[i] = k->pos[i] * h00 + k1->pos[i] * h01 + m0 * h10 + m1 * h11;
        }
        for (i = 0; i < 3; i++) {
            dv = k1->rot[i] - k->rot[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->rot[i] - k[-1].rot[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].rot[i] - k1->rot[i]));
            }
            rot[i] = (short)((k->rot[i] * h00 + k1->rot[i] * h01 + m0 * h10 + m1 * h11) *
                             (65536.0f / 360.0f));
        }
        for (i = 0; i < 3; i++) {
            dv = w[1][i] - w[0][i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (w[0][i] - k[-1].col[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].col[i] - w[1][i]));
            }
            col[i] = w[0][i] * h00 + w[1][i] * h01 + m0 * h10 + m1 * h11;
        }
    } else {
        for (i = 0; i < 3; i++) {
            dv = k1->pos[i] - k->pos[i];
            pos[i] = k->pos[i] + u * dv;
            dv = k1->rot[i] - k->rot[i];
            rot[i] = (short)((k->rot[i] + u * dv) * (65536.0f / 360.0f));
            dv = w[1][i] - w[0][i];
            col[i] = w[0][i] + u * dv;
        }
    }
    pos[3] = 1.0f;
    col[3] = 1.0f;
}

void bga_GetMotionLightning(float *pos, int *rot, float *col, BgaPtMotion *m)
{
    BgaPtKey *k;
    BgaPtKey *k1;
    float f;
    float u;
    float s0;
    float s1;
    float dv;
    float m0;
    float m1;
    int i;
    int d;

    f = m->frame;
    if (D_0028F4C0[0]) {
        f *= 1.2075409f;
    }

    if (m->n == 1) {
        BgaPtKey *p = m->key;

        pos[0] = p->pos[0];
        pos[1] = p->pos[1];
        pos[2] = p->pos[2];
        pos[3] = 1.0f;
        rot[0] = (short)(p->rot[0] * (65536.0f / 360.0f));
        rot[1] = (short)(p->rot[1] * (65536.0f / 360.0f));
        rot[2] = (short)(p->rot[2] * (65536.0f / 360.0f));
        col[0] = p->col[0];
        col[1] = p->col[1];
        col[2] = p->col[2];
        return;
    }

    k = m->key;
    s0 = 0.0f;
    s1 = 0.0f;
    k = &k[bga_findPtKey(k, m->n, f)];
    k1 = k + 1;
    f -= (float)k->time;
    d = k1->time - k->time;
    u = f / (float)d;

    if (k1->linear == 0) {
        float h00;
        float h01;
        float h10;
        float h11;
        float ta;
        float tb;
        float tc;
        float td;

        ta = (1.0f - k->f24) * (k->f28 + 1.0f);
        tb = (1.0f - k->f24) * (1.0f - k->f28);
        tc = (1.0f - k1->f24) * (1.0f - k1->f28);
        td = (1.0f - k1->f24) * (k1->f28 + 1.0f);
        bga_hermite(u, &h00, &h01, &h10, &h11);
        if (k->time != 0) {
            s0 = (float)d / (float)(k1->time - k[-1].time);
        }
        if (k1->time < m->len) {
            s1 = (float)d / (float)(k1[1].time - k->time);
        }

        for (i = 0; i < 3; i++) {
            dv = k1->pos[i] - k->pos[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->pos[i] - k[-1].pos[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].pos[i] - k1->pos[i]));
            }
            pos[i] = k->pos[i] * h00 + k1->pos[i] * h01 + m0 * h10 + m1 * h11;
        }
        for (i = 0; i < 3; i++) {
            dv = k1->rot[i] - k->rot[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->rot[i] - k[-1].rot[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].rot[i] - k1->rot[i]));
            }
            rot[i] = (short)((k->rot[i] * h00 + k1->rot[i] * h01 + m0 * h10 + m1 * h11) *
                             (65536.0f / 360.0f));
        }
        for (i = 0; i < 3; i++) {
            dv = k1->col[i] - k->col[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->col[i] - k[-1].col[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].col[i] - k1->col[i]));
            }
            col[i] = k->col[i] * h00 + k1->col[i] * h01 + m0 * h10 + m1 * h11;
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (k->rot[i] < 0.0f ? -k->rot[i] < 0.1f : k->rot[i] < 0.1f) {
                k->rot[i] = 0.0f;
            }
            if (k1->rot[i] < 0.0f ? -k1->rot[i] < 0.1f : k1->rot[i] < 0.1f) {
                k1->rot[i] = 0.0f;
            }
            dv = k1->pos[i] - k->pos[i];
            pos[i] = k->pos[i] + u * dv;
            dv = k1->rot[i] - k->rot[i];
            rot[i] = (short)((k->rot[i] + (180.0f < u * dv
                                               ? u * dv - 360.0f
                                               : (u * dv < -180.0f ? u * dv + 360.0f : u * dv))) *
                             (65536.0f / 360.0f));
            col[i] = k->col[i];
        }
    }
    pos[3] = 1.0f;
    col[3] = 1.0f;
}

typedef struct BgaExtKey {
    /* 0x00 */ float f00;
    /* 0x04 */ float f04;
    /* 0x08 */ float f08;
    /* 0x0C */ int f0C;
    /* 0x10 */ int time;
} BgaExtKey;

typedef struct BgaExtMotion {
    /* 0x00 */ BgaExtKey *key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaExtMotion;

static inline int bga_findExtKey(BgaExtKey *k, int n, float f)
{
    int lo = 0;
    int hi = n - 1;

    if (f < (float)k[0].time) {
        return 0;
    }
    if (hi < 2) {
        return 0;
    }
    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if ((float)k[mid].time <= f && f < (float)k[mid + 1].time) {
            return mid;
        }
        if ((float)k[mid + 1].time <= f) {
            lo = mid + 1;
        } else if (f <= (float)k[mid].time) {
            hi = mid - 1;
        }
        if (lo == hi) {
            return lo;
        }
    }
    return 0;
}

float bga_GetExtMotion(BgaExtMotion *m)
{
    BgaExtKey *k;
    BgaExtKey *k1;
    float f;
    float s0;
    float s1;
    float u;
    float dv;
    float t;
    int i;
    int d;

    f = m->frame;
    if (D_0028F4C0[0]) {
        f *= 1.2075409f;
    }
    if (m->n == 1) {
        return m->key->f00;
    }
    s0 = 0.0f;
    s1 = 0.0f;
    k = m->key;
    i = bga_findExtKey(k, m->n, f);
    k = &k[i];
    k1 = k + 1;
    f -= (float)k->time;
    d = k1->time - k->time;
    u = f / (float)d;
    dv = k1->f00 - k->f00;

    if (k1->f0C == 0) {
        float h00;
        float h01;
        float h10;
        float h11;
        float ta;
        float tb;
        float tc;
        float td;
        float m0;
        float m1;

        ta = (1.0f - k->f04) * (k->f08 + 1.0f);
        tb = (1.0f - k->f04) * (1.0f - k->f08);
        tc = (1.0f - k1->f04) * (1.0f - k1->f08);
        td = (1.0f - k1->f04) * (k1->f08 + 1.0f);
        bga_hermite(u, &h00, &h01, &h10, &h11);
        if (k->time != 0) {
            s0 = (float)d / (float)(k1->time - k[-1].time);
        }
        if (k1->time < m->len) {
            s1 = (float)d / (float)(k1[1].time - k->time);
        }
        if (k->time == 0) {
            m0 = (ta + tb) * dv;
        } else {
            m0 = s0 * (ta * (k->f00 - k[-1].f00) + tb * dv);
        }
        if (k1->time >= m->len) {
            m1 = (tc + td) * dv;
        } else {
            m1 = s1 * (tc * dv + td * (k1[1].f00 - k1->f00));
        }
        return k->f00 * h00 + k1->f00 * h01 + m0 * h10 + m1 * h11;
    }
    t = u * dv;
    return k->f00 + t;
}

void bga_GetGizmoMotion(BgaMotion *m, float *dst)
{
    BgaKey *k;
    BgaKey *k1;
    float f;
    float u;
    float s0;
    float s1;
    float dv;
    float m0;
    float m1;
    int i;
    int d;

    f = m->frame;
    if (D_0028F4C0[0]) {
        f *= 1.2075409f;
    }

    if (m->n == 1) {
        float *src = (float *)m->key;

        for (i = 5; i >= 0; i--, src++, dst++) {
            *dst = *src;
        }
        return;
    }

    k = m->key;
    s0 = 0.0f;
    s1 = 0.0f;
    i = bga_findKey(k, m->n, f);
    k = &k[i];
    k1 = k + 1;
    f -= (float)k->time;
    d = k1->time - k->time;
    u = f / (float)d;

    if (k1->f20 == 0) {
        float h00;
        float h01;
        float h10;
        float h11;
        float ta;
        float tb;
        float tc;
        float td;

        ta = (1.0f - k->f18) * (k->f1C + 1.0f);
        tb = (1.0f - k->f18) * (1.0f - k->f1C);
        tc = (1.0f - k1->f18) * (1.0f - k1->f1C);
        td = (1.0f - k1->f18) * (k1->f1C + 1.0f);
        bga_hermite(u, &h00, &h01, &h10, &h11);
        if (k->time != 0) {
            s0 = (float)d / (float)(k1->time - k[-1].time);
        }
        if (k1->time < m->len) {
            s1 = (float)d / (float)(k1[1].time - k->time);
        }

        for (i = 0; i < 6; i++) {
            dv = k1->v[i] - k->v[i];

            if (k->time == 0) {
                m0 = (ta + tb) * dv;
            } else {
                m0 = s0 * (ta * (k->v[i] - k[-1].v[i]) + tb * dv);
            }
            if (k1->time >= m->len) {
                m1 = (tc + td) * dv;
            } else {
                m1 = s1 * (tc * dv + td * (k1[1].v[i] - k1->v[i]));
            }
            dst[i] = k->v[i] * h00 + k1->v[i] * h01 + m0 * h10 + m1 * h11;
        }
    } else {
        for (i = 0; i < 6; i++) {
            dv = k1->v[i] - k->v[i];
            dst[i] = k->v[i] + u * dv;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_calcEnvelope);

/* kept local: this TU's uses of _Sqrt do not fit the prototype in Matrix.h */
extern float _Sqrt(float x);

/* The rotation is applied Y, then X, then Z, with the three sines derived
   from the cosines (sin = sign(angle) * sqrt(1 - cos^2)) instead of a second
   table lookup.  The VU0 block is the _TransCurrentMatrix body followed by
   the three _RotCurrentMatrix* bodies with the cos/sin pairs already in
   $vf21..$vf26; $vf27..$vf29 hold the vmr32 chain so it is built once. */
void _RotTransCurrentMatrixYXZ(void *t, int *rot)
{
    float cx, cy, cz, sx, sy, sz;

    cx = GetTableCos(rot[0]);
    cy = GetTableCos(rot[1]);
    cz = GetTableCos(rot[2]);
    sx = SIGNF(rot[0]) * _Sqrt(1.0f - cx * cx);
    sy = SIGNF(rot[1]) * _Sqrt(1.0f - cy * cy);
    sz = SIGNF(rot[2]) * _Sqrt(1.0f - cz * cz);

    /* The rotation pairs go into $vf21..$vf26 while the vmr32 chain builds
       the identity rows in $vf14..$vf17.  The sequence is one asm block
       because it is hand scheduled: every mfc1 is separated from the qmtc2
       that consumes its GPR, and the three vmr32 sit in those gaps. */
    __asm__ __volatile__("vmove.xyzw $vf17, $vf0\n\t"
                         "lqc2 $vf8, 0(%6)\n\t"
                         "mfc1 $4, %0\n\t"
                         "mfc1 $5, %1\n\t"
                         "vmr32.xyzw $vf16, $vf17\n\t"
                         "mfc1 $6, %2\n\t"
                         "mfc1 $7, %3\n\t"
                         "mfc1 $8, %4\n\t"
                         "vmr32.xyzw $vf15, $vf16\n\t"
                         "mfc1 $9, %5\n\t"
                         "qmtc2.ni $4, $vf21\n\t"
                         "qmtc2.ni $5, $vf22\n\t"
                         "vmr32.xyzw $vf14, $vf15\n\t"
                         "qmtc2.ni $6, $vf23\n\t"
                         "qmtc2.ni $7, $vf24\n\t"
                         "qmtc2.ni $8, $vf25\n\t"
                         "qmtc2.ni $9, $vf26"
                         :
                         : "f"(cy), "f"(sy), "f"(cx), "f"(sx), "f"(cz), "f"(sz), "r"(t)
                         : "$4", "$5", "$6", "$7", "$8", "$9", "memory");
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V2OP(vmove.xyzw, 27, 14);
    VU0_V2OP(vmove.xyzw, 29, 16);
    VU0_V3OP_BC(vaddx.x, 14, 0, 21, x);
    VU0_V3OP_BC(vaddx.x, 16, 0, 22, x);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 7, 8, w);
    VU0_V2OP(vmove.xyzw, 28, 15);
    VU0_V3OP_BC(vsubx.z, 14, 0, 22, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 21, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 11, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 12, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 13, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 15, 28);
    VU0_V2OP(vmove.xyzw, 16, 29);
    VU0_V2OP(vmove.xyzw, 14, 27);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V3OP_BC(vaddx.y, 15, 0, 23, x);
    VU0_V3OP_BC(vsubx.y, 16, 0, 24, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 14, y);
    VU0_V3OP_BC(vaddx.z, 15, 0, 24, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 23, x);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 4, 13, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 5, 13, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 6, 13, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 10, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 11, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 12, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 13, 17, w);
    VU0_V2OP(vmove.xyzw, 14, 27);
    VU0_V2OP(vmove.xyzw, 15, 28);
    VU0_V2OP(vmove.xyzw, 16, 29);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V3OP_BC(vaddx.x, 14, 0, 25, x);
    VU0_V3OP_BC(vsubx.x, 15, 0, 26, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_BC(vaddx.y, 14, 0, 26, x);
    VU0_V3OP_BC(vaddx.y, 15, 0, 25, x);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 12, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 11, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 13, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 10);
    VU0_V2OP(vmove.xyzw, 5, 11);
    VU0_V2OP(vmove.xyzw, 6, 12);
    VU0_V2OP(vmove.xyzw, 7, 13);
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/BgAnimation", bga_CalcObject);

static inline float bga_palFrame(float f)
{
    if (D_0028F4C0[0]) {
        f *= 0.82812935f;
    }
    return f;
}

typedef struct {
    /* 0x00 */ int f00;
    /* 0x04 */ int f04;
    /* 0x08 */ unsigned int f08;
    /* 0x0C */ float f0C;
} BgaCount;

typedef struct {
    /* 0x00 */ int f00;
    /* 0x04 */ BgaCount *obj;
} BgaCountEnt;

typedef struct BgaCntNode {
    /* 0x00 */ char pad00[0x28];
    /* 0x28 */ BgaCountEnt *ents;
    /* 0x2C */ struct BgaCntNode *f2C;
    /* 0x30 */ struct BgaCntNode *f30;
    /* 0x34 */ BgaCount f34;
} BgaCntNode;

static inline void bga_clampCount(BgaCount *o, float f)
{
    if (f >= 0.0f) {
        float c = (float)o->f08;
        float r;

        if (D_0028F4C0[0] ? c * 0.82812935f < f : c < f) {
            float t = (float)o->f08;

            r = t;
            if (D_0028F4C0[0]) {
                r *= 0.82812935f;
            }
        } else {
            r = f;
        }
        o->f0C = r;
    } else {
        o->f0C = 0.0f;
    }
}

void bga_resetObjectCounter(BgaCntNode *o, float f, int a1)
{
    BgaCountEnt *e;

    e = o->ents;
    if (e != 0) {
        while (e->obj != 0) {
            bga_clampCount(e->obj, f);
            e++;
        }
    }
    if (o->f2C != 0) {
        bga_resetObjectCounter(o->f2C, f, a1);
    }
    if (o->f30 != 0) {
        bga_resetObjectCounter(o->f30, f, a1);
    }
    bga_clampCount(&o->f34, f);
}

extern int D_0063BCB8;
extern int GlobalTimer;
extern float D_00728230[];
extern float D_00728220[];
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *dst, void *src);
extern char D_006217B0[];
extern char D_006217C8[];
extern void bga_CalcAnimation(char *p, int a1, int a2);

void bga_SetFrame(char *p, int frame, int mode, int a3)
{
    float f;

    if (p[0xB]) {
        GlobalTimer = 1;
        D_0063BCB8 = 1;
        _CopyVector(D_00728230, D_00728220);
    }
    switch (frame) {
    case 0:
        *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x14));
        p[0xA] = mode;
        break;
    case -1:
        debug_StdPrintfDummy(D_006217B0, *(char **)(p + 0xC) + 4);
        *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x18));
        p[0xA] = mode;
        break;
    case -2:
        debug_StdPrintfDummy(D_006217C8, *(char **)(p + 0xC) + 4);
        *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x14));
        p[0xA] = -1;
        return;
    default:
        f = (float)frame;
        *(float *)(p + 0x20) = bga_palFrame(f);
        if (f < *(float *)(p + 0x14)) {
            *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x14));
        } else if (*(float *)(p + 0x18) < f) {
            *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x18));
        }
        p[0xA] = mode;
        break;
    }
    bga_CalcAnimation(p, a3, 1);
}

extern int D_0063C4B4;
extern int D_0063BCBC;
/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *m);
/* kept local: this TU's uses of _InitCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InitCurrentMatrix(void);
/* kept local: this TU's uses of _MulCurrentMatrixR do not fit the prototype in Matrix.h */
extern void _MulCurrentMatrixR(void *m);
/* kept local: this TU's uses of _PushCurrentMatrix do not fit the prototype in Matrix.h */
extern void _PushCurrentMatrix(void);
/* kept local: this TU's uses of _PopCurrentMatrix do not fit the prototype in Matrix.h */
extern void _PopCurrentMatrix(void);
extern void bga_CalcObject(BgaCntNode *o, int a1, int a2, int a3, float frame, float end);

typedef struct BgaAnimGeom {
    /* 0x000 */ char pad00[0xC];
    /* 0x00C */ float (*mtx)[4][4];
    /* 0x010 */ float (*quat)[4];
} BgaAnimGeom;

typedef struct BgaAnimObj {
    /* 0x000 */ char pad00[0x15C];
    /* 0x15C */ BgaAnimGeom *geom;
} BgaAnimObj;

typedef struct BgaAnimEnt {
    /* 0x00 */ float pos[4];
    /* 0x10 */ float quat[4];
    /* 0x20 */ BgaAnimObj *obj;
    /* 0x24 */ int idx;
    /* 0x28 */ int root;
} BgaAnimEnt;

#define BGA_ANIM_ENT(p) (*(BgaAnimEnt **)((p) + 0x24))

void bga_CalcAnimation(char *p, int a1, int a2)
{
    float m[4][4];
    float rm[4][4];
    BgaCntNode *o;
    int i;
    int f1;
    int f2;

    if (p[0xA] == -1) {
        return;
    }

    if (p[0xB]) {
        D_0063C4B4 = 1;
    }

    GetMatrixFromQuaternionPos(m, BGA_ANIM_ENT(p)->quat, BGA_ANIM_ENT(p));
    if (BGA_ANIM_ENT(p)->obj) {
        if (BGA_ANIM_ENT(p)->root) {
            _SetCurrentMatrix(BGA_ANIM_ENT(p)->obj->geom->mtx[BGA_ANIM_ENT(p)->idx]);
        } else {
            GetRootMatrix(rm, BGA_ANIM_ENT(p)->obj);
            CopyVector(rm[3], BGA_ANIM_ENT(p)->obj->geom->mtx[BGA_ANIM_ENT(p)->idx][3]);
            _SetCurrentMatrix(rm);
        }
    } else {
        _InitCurrentMatrix();
    }
    _MulCurrentMatrixR(m);

    if (BGA_ANIM_ENT(p)->obj) {
        if (BGA_ANIM_ENT(p)->root) {
            CopyQuaternion(GetCurrentQuaternion(),
                           BGA_ANIM_ENT(p)->obj->geom->quat[BGA_ANIM_ENT(p)->idx]);
        } else {
            GetRootQuaternion(GetCurrentQuaternion(), BGA_ANIM_ENT(p)->obj);
        }
    } else {
        SetIdentityQuaternion(GetCurrentQuaternion());
    }
    MultiQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), BGA_ANIM_ENT(p)->quat);

    for (i = 0;; i++) {
        f2 = (p[0xA] == 1);
        f1 = p[0xB] && f2;
        o = (*(BgaCntNode ***)(p + 0x10))[i];
        if (o == 0) {
            break;
        }
        PushQuaternion();
        _PushCurrentMatrix();
        if (a2 == 1) {
            bga_resetObjectCounter(o, *(float *)(p + 0x20), a1);
        }
        bga_CalcObject(o, f1, f2, a1, *(float *)(p + 0x1C), *(float *)(p + 0x20));
        _PopCurrentMatrix();
        PopQuaternion();
    }

    D_0063BCBC = (int)*(float *)(p + 0x20);
    if (a2) {
        return;
    }

    if (p[0xA] == 1) {
        float end = *(float *)(p + 0x18);

        *(float *)(p + 0x20) += *(float *)(p + 0x1C);
        if (D_0028F4C0[0] ? end * 0.82812935f < *(float *)(p + 0x20) : end < *(float *)(p + 0x20)) {
            if (a1 == 0) {
                *(float *)(p + 0x20) = bga_palFrame(*(float *)(p + 0x18));
                p[0xA] = 0;
            } else {
                *(float *)(p + 0x20) = 0.0f;
            }
        }
    }
}

extern int D_0063BCC0;
extern int D_007281F0[];
extern int D_0063A06C;
/* kept local: this TU's uses of the matrix and vector entry points do not fit
   the prototypes in Matrix.h (the interpolator takes its weight as a float,
   the length returns one and both take two vectors). */
extern void _RotCurrentMatrixZ(short a);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _SetCameraMatrix(void *m, void *pos, void *dir, void *up);
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
extern void _NormalizeVector(void *dst, void *src);
extern float _GetLength(void *a, void *b);
extern float GetTableSin(short a);
extern float GetTableCos(short a);

typedef struct BgaSdfKey {
    /* 0x00 */ int f00;
    /* 0x04 */ float pos[3];
    /* 0x10 */ float at[3];
    /* 0x1C */ float roll;
    /* 0x20 */ float fov;
} BgaSdfKey;

/* The SDF camera record bga_InitSdfCamera checks and bga_SetCamFrame starts:
 * the "SDF" tag, the key count, the running frame, the play mode and the keys. */
typedef struct BgaSdfCam {
    /* 0x00 */ char id[4];
    /* 0x04 */ int num;
    /* 0x08 */ float frame;
    /* 0x0C */ int mode;
    /* 0x10 */ BgaSdfKey key[1];
} BgaSdfCam;

/* the PAL frame counter read back on the 60 Hz timeline: the reciprocal of
   bga_palFrame's 0.82812935f. */
static inline float bga_ntscFrame(float f)
{
    if (D_0028F4C0[0]) {
        f *= 1.2075409f;
    }
    return f;
}

/* Listing rows 2794-2871.  The record is read through its fields: a field
 * read at a varying address is exempt from the fixed-address D_0063C4B4 store
 * (alias.c fixed_scalar_and_varying_struct_p), which is what lets the count
 * load issue ahead of that store as the ROM has it.  Both frame-rate scales are
 * `x * (PAL ? k : 1.0f)`: fold distributes the product over the condition and
 * evaluates x once before the branch (the ROM's shared frame load and the
 * mov.s it copies into the PAL arm).  Rows 2836/2837 read each key's two
 * values into locals of their own, fov first as rows 2841/2842 use them. */
void bga_CalcSdfCamera(char *data, int loop)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    BgaSdfKey *k0;
    BgaSdfKey *k1;
    float fr;
    float t;
    int i;
    int i1;

    if (p->mode == -1) {
        return;
    }
    D_0063C4B4 = 1;
    if ((float)p->num * (D_0028F4C0[0] ? 0.82812935f : 1.0f) < p->frame) {
        if (loop == 0) {
            p->frame = bga_palFrame((float)p->num);
            p->mode = 0;
            return;
        }
        p->frame = 0.0f;
    }

    D_0063BCBC = (int)(p->frame * (D_0028F4C0[0] ? 1.2075409f : 1.0f));
    _PushCurrentMatrix();
    fr = bga_ntscFrame(p->frame);
    i = (int)fr;
    i1 = i + 1;
    if (i > p->num - 1) {
        i = p->num - 1;
    }
    if (i1 > p->num - 1) {
        i1 = p->num - 1;
    }
    k0 = &p->key[i];
    k1 = &p->key[i1];
    t = fr - (float)i;
    {
        VECTOR at;
        VECTOR pos;
        VECTOR pos0 = {k0->pos[0], k0->pos[1], k0->pos[2], 1.0f};
        VECTOR at0 = {k0->at[0], k0->at[1], k0->at[2], 1.0f};
        VECTOR pos1 = {k1->pos[0], k1->pos[1], k1->pos[2], 1.0f};
        VECTOR at1 = {k1->at[0], k1->at[1], k1->at[2], 1.0f};
        VECTOR up;
        VECTOR dir;
        float roll0;
        float fov0;
        float roll1;
        float fov1;
        float roll;
        float fov;
        short a;

        memset(&up, 0, sizeof(up));
        up.y = 1.0f;
        fov0 = k0->fov;
        roll0 = k0->roll;
        fov1 = k1->fov;
        roll1 = k1->roll;
        _InterVectorXYZ(&pos, &pos0, &pos1, 1.0f - t);
        _InterVectorXYZ(&at, &at0, &at1, 1.0f - t);
        fov = fov0 * (1.0f - t) + fov1 * t;
        roll = roll0 * (1.0f - t) + roll1 * t;
        dir.x = at.x - pos.x;
        dir.y = at.y - pos.y;
        dir.z = at.z - pos.z;
        dir.w = 0.0f;
        _NormalizeVector(&dir, &dir);
        _InitCurrentMatrix();
        _RotCurrentMatrixZ((short)(roll * 182.04445f));
        _ApplyCurrentMatrix(&up, &up);
        _SetCameraMatrix(D_007281F0, &pos, &dir, &up);
        if (GlobalTimer != 0) {
            if (_GetLength(&D_007281F0[12], D_00728230) < 100.0f) {
                GlobalTimer = 0;
                D_0063A06C = 0;
            }
        }
        a = (short)(fov * 3.1415927f / 360.0f * 10430.378f);
        *(float *)&D_0063BCC0 = 224.0f / (GetTableSin(a) / GetTableCos(a));
        _PopCurrentMatrix();
    }
    p->frame += 1.0f;
}

extern char *D_0063BCCC;
extern char D_006217E0[];
/* kept local: this TU's uses of _UnitVector do not fit the prototype in
   Matrix.h (_CopyVector is declared above bga_SetFrame) */
extern void _UnitVector(void *v);

void bga_addLightning(int kind, char *a1, float *vec, int id, int t0, float f)
{
    char *p;

    for (p = D_0063BCCC; p != 0; p = *(char **)(p + 0x154)) {
        if (*(int *)(p + 0x144) == id) {
            switch (kind) {
            case 15:
                *(short *)(a1 + 2) = -1;
                /* FALLTHROUGH */
            case 14:
                *(char **)(p + 0x150) = a1;
                *(float *)(p + 0x14C) = f;
                *(int *)(p + 0x148) = t0;
                *(int *)(p + 0x10) = -1;
                _CopyVector(p, vec);
                return;
            case 16: {
                char *e = p + *(int *)(p + 0x140) * 0x20;

                *(int *)(e + 0x10) = *(short *)(a1 + 2);
                _CopyVector(p + *(int *)(p + 0x140) * 0x20, vec);
                *(int *)(p + 0x140) = *(int *)(p + 0x140) + 1;
                return;
            }
            default:
                debug_StdPrintfDummy(D_006217E0);
                debug_assert(D_00621598, 2960);
                __assert(D_00621598, 2960, D_0063BCE8);
                return;
            }
        }
    }
    p = iosMallocDebug(D_0063A44C, 0x160, D_00621598, 2968);
    *(char **)(p + 0x154) = D_0063BCCC;
    *(int *)(p + 0x144) = id;
    *(int *)(p + 0x140) = 1;
    D_0063BCCC = p;
    switch (kind) {
    case 15:
        *(short *)(a1 + 2) = -1;
        /* FALLTHROUGH */
    case 14:
        *(char **)(p + 0x150) = a1;
        *(float *)(p + 0x14C) = f;
        *(int *)(p + 0x148) = t0;
        _CopyVector(p, vec);
        break;
    case 16: {
        char *e = p + *(int *)(p + 0x140) * 0x20;

        *(int *)(e + 0x10) = *(short *)(a1 + 2);
        _CopyVector(p + *(int *)(p + 0x140) * 0x20, vec);
        *(int *)(p + 0x150) = 0;
        _UnitVector(p);
        *(int *)(p + 0x140) = *(int *)(p + 0x140) + 1;
        break;
    }
    default:
        debug_StdPrintfDummy(D_006217E0);
        debug_assert(D_00621598, 2994);
        __assert(D_00621598, 2994, D_0063BCE8);
        break;
    }
}

/* The lightning record bga_addLightning allocates: ten 0x20-byte segments,
   the live segment count, the two flags, the frame, the definition it was
   built from and the list link.  Field names are ours. */
typedef struct BgaLightningSeg {
    /* 0x00 */ float v[4];
    /* 0x10 */ int key;
    /* 0x14 */ int f14;
    /* 0x18 */ int f18;
    /* 0x1C */ int f1C;
} BgaLightningSeg;

/* The lightning definition the BGA file carries: the kind at +0x02 picks the
   object the bolt is drawn against, the four bytes at +0x04 are its colour
   and the ten floats from +0x08 are DrawLightningN's shape parameters. */
typedef struct BgaLightningDef {
    /* 0x00 */ short f00;
    /* 0x02 */ short kind;
    /* 0x04 */ unsigned char col[4];
    /* 0x08 */ float f08;
    /* 0x0C */ float f0C;
    /* 0x10 */ float f10;
    /* 0x14 */ float f14;
    /* 0x18 */ float f18;
    /* 0x1C */ float f1C;
    /* 0x20 */ float f20;
    /* 0x24 */ float f24;
    /* 0x28 */ float f28;
    /* 0x2C */ short f2C;
    /* 0x2E */ short f2E;
} BgaLightningDef;

typedef struct BgaLightning {
    /* 0x000 */ BgaLightningSeg seg[10];
    /* 0x140 */ int n;
    /* 0x144 */ int f144;
    /* 0x148 */ int f148;
    /* 0x14C */ float frame;
    /* 0x150 */ BgaLightningDef *def;
    /* 0x154 */ struct BgaLightning *next;
} BgaLightning;

/* DrawLightningN reads the colour as four words, so it is a 16-byte record
   here and not four separate ints. */
typedef struct BgaLightningCol {
    unsigned int c[4];
} __attribute__((aligned(16))) BgaLightningCol;

/* The kind table isys keeps beside the gobj records: 0x4C bytes each, the
   object kind first. */
typedef struct BgaObjKind {
    /* 0x00 */ int kind;
    /* 0x04 */ char pad04[0x48];
} BgaObjKind;

extern BgaObjKind D_002C2DF4[];
extern char D_00621800[];
/* kept local: this TU does not include gobj.h or enemy_act.h, and its use of
   DrawLightningN does not fit the prototype in lightning.h */
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *g);
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *g);
extern int isEnemyHyde(void *g);

/* Listing line 3069: the definition's four colour bytes widened into the
   16-byte record DrawLightningN reads.  The name is ours. */
static inline BgaLightningCol bga_lightningColor(BgaLightningDef *g)
{
    BgaLightningCol c;

    c.c[0] = g->col[0];
    c.c[1] = g->col[1];
    c.c[2] = g->col[2];
    c.c[3] = g->col[3];
    return c;
}

extern void DrawLightningN(int num, void *v, void *col, float f0, float f1, float f2, float f3,
                           float f4, float f5, float f6, float f7, float f8, float f9, int c);

void bga_DispLightning(void)
{
    BgaLightning *p;
    BgaLightningDef *g;
    void *o;
    int cnt;
    int i;
    int num;
    int k;
    float z;
    BgaLightning *list[100];
    BgaLightningCol col;

    cnt = 0;
    num = 0;
    for (p = (BgaLightning *)D_0063BCCC; p != 0; p = p->next) {
        if (p->def->kind == 0) {
            list[num++] = p;
        }
    }
    if (num > 0) {
        z = 0.0f;
        i = 0;
        for (o = isysGObjSearchFromObjKindID_begin(4); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (isEnemyHyde(o) != 0) {
                continue;
            }
            if (*(int *)((char *)o + 0x16C) == 0) {
                continue;
            }
            cnt++;
            if (cnt >= 5) {
                continue;
            }
            p = list[i++];
            i %= num;
            g = p->def;
            if (D_0028F4C0[5] == 0) {
                k = p->n;
                if (k < 10) {
                    p->n = k + 1;
                    _CopyVector(&p->seg[k], (char *)*(int *)(*(int *)((char *)o + 0x15C) + 0xC) +
                                                (g->f2C << 6) + 0x30);
                }
            }
            col.c[0] = g->col[0];
            col.c[1] = g->col[1];
            col.c[2] = g->col[2];
            col.c[3] = g->col[3];
            DrawLightningN(p->n, p, &col, g->f08, g->f0C, g->f10, g->f14, g->f18, g->f1C, g->f20,
                           g->f24, g->f28, p->frame + z, g->f2E);
            z += 0.01f;
        }
    }
    for (p = (BgaLightning *)D_0063BCCC; p != 0; p = p->next) {
        g = p->def;
        if (g == 0) {
            debug_StdPrintfDummy(D_00621800);
            debug_assert(D_00621598, 3067);
            __assert(D_00621598, 3067, D_0063BCE8);
            continue;
        }
        col = bga_lightningColor(g);
        if (p->f148 != 0) {
            continue;
        }
        switch (g->kind) {
        case 1:
            o = isysGObjSearchFromObjKindID_begin(2);
            if (o == 0) {
                continue;
            }
            if (D_0028F4C0[5] == 0) {
                k = p->n;
                if (k < 10) {
                    p->n = k + 1;
                    _CopyVector(&p->seg[k], (char *)*(int *)(*(int *)((char *)o + 0x15C) + 0xC) +
                                                (g->f2C << 6) + 0x30);
                }
            }
            DrawLightningN(p->n, p, &col, g->f08, g->f0C, g->f10, g->f14, g->f18, g->f1C, g->f20,
                           g->f24, g->f28, p->frame, g->f2E);
            break;
        case 2:
            for (o = isysGObjGetExist_begin(); o != 0; o = isysGObjGetExist_next(o)) {
                if (D_002C2DF4[*(int *)((char *)o + 8)].kind == 71) {
                    if (D_0028F4C0[5] == 0) {
                        k = p->n;
                        if (k < 10) {
                            p->n = k + 1;
                            _CopyVector(&p->seg[k],
                                        (char *)*(int *)(*(int *)((char *)o + 0x15C) + 0xC) +
                                            (g->f2C << 6) + 0x30);
                        }
                    }
                    DrawLightningN(p->n, p, &col, g->f08, g->f0C, g->f10, g->f14, g->f18, g->f1C,
                                   g->f20, g->f24, g->f28, p->frame, g->f2E);
                }
            }
            break;
        case 3:
            for (o = isysGObjGetExist_begin(); o != 0; o = isysGObjGetExist_next(o)) {
                if (D_002C2DF4[*(int *)((char *)o + 8)].kind == 74) {
                    if (D_0028F4C0[5] == 0) {
                        k = p->n;
                        if (k < 10) {
                            p->n = k + 1;
                            _CopyVector(&p->seg[k],
                                        (char *)*(int *)(*(int *)((char *)o + 0x15C) + 0xC) +
                                            (g->f2C << 6) + 0x30);
                        }
                    }
                    DrawLightningN(p->n, p, &col, g->f08, g->f0C, g->f10, g->f14, g->f18, g->f1C,
                                   g->f20, g->f24, g->f28, p->frame, g->f2E);
                }
            }
            break;
        case 0:
            break;
        default:
            DrawLightningN(p->n, p, &col, g->f08, g->f0C, g->f10, g->f14, g->f18, g->f1C, g->f20,
                           g->f24, g->f28, p->frame, g->f2E);
            break;
        }
    }
}

void bga_ResetCamera(void)
{
    D_0063C4B4 = 0;
}

extern int D_0063BCC8;
/* kept local: this TU's uses of _CopyMatrix do not fit the prototype in Matrix.h */
extern void _CopyMatrix(void *dst, void *src);

int bga_GetCameraMatrix(void *p)
{
    int v = D_0063C4B4;
    if (v != 0) {
        _CopyMatrix(p, D_007281F0);
        v = D_0063C4B4;
    } else {
        D_0063BCC0 = 0;
    }
    return v != 0 && D_0063BCC8 == 0;
}

extern char D_0063BCE0[];
extern char D_006215D8[];

char *bga_InitSdfCamera(char *a0)
{
    BgaSdfCam *p = (BgaSdfCam *)a0;

    if (strncmp(p->id, D_0063BCE0, 3) != 0) {
        debug_StdPrintfDummy(D_006215D8);
        debug_assert(D_00621598, 0x415);
        __assert(D_00621598, 0x415, D_0063BCD8);
    }
    return a0;
}

extern int D_0063BCB8;
extern int GlobalTimer;
extern float D_00728230[];
extern float D_00728220[];
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *dst, void *src);

void bga_SetCamFrame(char *data, int frame, int mode)
{
    BgaSdfCam *p = (BgaSdfCam *)data;

    p->mode = mode;
    D_0063C4B4 = 1;
    if (mode == 1) {
        GlobalTimer = mode;
        D_0063BCB8 = mode;
        _CopyVector(D_00728230, D_00728220);
    }
    if (frame == -1) {
        p->frame = bga_palFrame(p->num);
    } else {
        p->frame = bga_palFrame(frame);
    }
}

int bga_CheckAnimationFinish(char *p)
{
    float f = *(float *)(p + 0x18);
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0]) {
        if (f * 0.82812935f <= t || p[0xA] != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p[0xA] != 1) {
            r = 1;
        }
    }
    return r;
}

int bga_CheckAnimationFrame(char *p, int frame, int reset)
{
    float f = frame;
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0]) {
        if (f * 0.82812935f <= t || p[0xA] != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p[0xA] != 1) {
            r = 1;
        }
    }
    if (r && reset) {
        p[0xA] = 0;
    }
    return r;
}

int bga_CheckAnimationFrameIn(char *p, int in, int out)
{
    float a = in;
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (D_0028F4C0[0] ? t < b * 0.82812935f : t < b) {
            r = p[0xA] == 1;
        }
    }
    return r;
}

int bga_CheckSdfCameraFinish(char *data)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float f = p->num;
    float t = p->frame;

    if (D_0028F4C0[0]) {
        return f * 0.82812935f <= t;
    }
    return f <= t;
}

int bga_CheckSdfCameraFrame(char *data, int frame, int reset)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float f = frame;
    float t = p->frame;
    int r;

    if (D_0028F4C0[0]) {
        r = f * 0.82812935f <= t;
    } else {
        r = f <= t;
    }
    if (r && reset) {
        p->mode = 0;
    }
    return r;
}

int bga_CheckSdfCameraFrameIn(char *data, int in, int out)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float t = p->frame;
    float a = in;
    int r = 0;

    if (D_0028F4C0[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (D_0028F4C0[0] ? t < b * 0.82812935f : t < b) {
            r = 1;
        }
    }
    return r;
}

void bga_SetCameraForceOff(void)
{
    D_0063BCC8 = 1;
}

void bga_InitBGA(void)
{
    D_0063BCC8 = 0;
    D_0063BCCC = 0;
}

extern int D_0063BCC4;

void bga_SetUniqAnimationFlag(int val)
{
    D_0063BCC4 = val;
}

extern int D_0028F4D4[];

void bga_ResetAnimation(void)
{
    void *p;
    D_0063C4B4 = 0;
    if (D_0028F4D4[0] != 0) {
        return;
    }
    p = (void *)D_0063BCCC;
    D_0063BCCC = 0;
    if (p == 0) {
        return;
    }
    do {
        void *next = *(void **)((char *)p + 0x154);
        freeseki(p);
        p = next;
    } while (p != 0);
}

float bga_GetZoom(void)
{
    return *(float *)&D_0063BCC0;
}
