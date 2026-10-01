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
#include "GsBase.h"
#include "ios.h"
#include "main.h"
#include "Matrix.h"
#include "enemy_act.h"
#include "gobj.h"

/* .data, carved VMA 0x4EE5B0..0x4EE5F0, bytes verified against
   baserom/pal/baseelf.rom.  bgaAnimDefault is the 0x30-byte default record
   bga_InitData block-copies into its mallocseki() allocation (two
   (0,0,0,1.0f) vectors then four words); bgaParticlePos is the (0,0,0,1.0f)
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

static BgaAnimDefault bgaAnimDefault = {
    /* derived name */
    {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 0, -1, 1, 0,
};

/* RECONSTRUCTION, read from the ROM: the head of a BGA file, its "BGA"
   magic, the play state (-1 off, 0 held, 1 playing), the camera-cut flag, the
   DObj list and the root list bga_InitData builds from it, the frame range,
   the step and the current frame, and the animation record it allocates. */
typedef struct BgaHeader { /* field names derived */
    char magic[10];
    signed char mode;     /* 0x0A */
    char cut;             /* 0x0B */
    int dobjs;            /* 0x0C */
    int roots;            /* 0x10 */
    float start;          /* 0x14 */
    float end;            /* 0x18 */
    float step;           /* 0x1C */
    float frame;          /* 0x20 */
    BgaAnimDefault *anim; /* 0x24 */
} BgaHeader;

static float bgaParticlePos[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

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

/* The .sdata run, in the ROM's order: the six words the file's functions
   share, then the short literals at their uses.  bgaStreamSync is read and
   cleared by streamMotionManager.c (_infoUpdate), so it is global; MAIN.MAP
   lists no .sdata symbol for BgAnimation.o, whose January run is 8 bytes
   larger than the retail one. */
int bgaStreamSync = 0; /* derived name */

static int bgaFrame = 0; /* derived name */

static float bgaZoom = 0.0f; /* derived name */

static int bgaUniqAnimationFlag = 1; /* derived name */

static int bgaCameraForceOff = 0; /* derived name */

static struct BgaLightning *bgaLightningList = 0; /* derived name */

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

static inline void bga_linkTree(BgaHeader *p)
{
    BgaDObjEnt *d;
    int no;

    d = (BgaDObjEnt *)p->dobjs;
    do {
        no = d->parent;
        if (no != -1) {
            bga_linkToParent((BgaDObjEnt *)p->dobjs, d, no);
        }
        if (d->u.next == 0) {
            break;
        }
        d = (BgaDObjEnt *)d->u.next;
    } while (1);
}

static inline void bga_makeRootList(BgaHeader *p)
{
    BgaDObjEnt *d;
    int n;

    d = (BgaDObjEnt *)p->dobjs;
    n = 0;
    do {
        if (d->parent == -1) {
            n++;
        }
    } while ((d = (BgaDObjEnt *)d->u.next) != 0);

    p->roots = mallocseki((n + 1) * 4);
    ((int *)p->roots)[n] = 0;
    d = (BgaDObjEnt *)p->dobjs;
    n = 0;
    do {
        if (d->parent == -1) {
            ((int *)p->roots)[n] = (int)d;
            n++;
        }
        if (d->u.next == 0) {
            break;
        }
        d = (BgaDObjEnt *)d->u.next;
    } while (1);
}

/* The functions the ROM places after bga_DispLightning, in that order: the
   file defines them inline, so gcc defers each out-of-line copy to the end of
   the file in first-declaration order, which these prototypes fix. */
void bga_ResetCamera(void);
int bga_GetCameraMatrix(void *p);
char *bga_InitSdfCamera(char *a0);
void bga_SetCamFrame(char *data, int frame, int mode);
int bga_CheckAnimationFinish(BgaHeader *p);
int bga_CheckAnimationFrame(BgaHeader *p, int frame, int reset);
int bga_CheckAnimationFrameIn(BgaHeader *p, int in, int out);
int bga_CheckSdfCameraFinish(char *data);
int bga_CheckSdfCameraFrame(char *data, int frame, int reset);
int bga_CheckSdfCameraFrameIn(char *data, int in, int out);
void bga_SetCameraForceOff(void);
void bga_InitBGA(void);
void bga_SetUniqAnimationFlag(int val);
void bga_ResetAnimation(void);
float bga_GetZoom(void);

char *bga_InitData(BgaHeader *p)
{
    BgaDObjEnt *d;
    int i;
    unsigned int j;
    int k;

    if (strncmp(p->magic, "BGA", 3) != 0) {
        debug_StdPrintfDummy("this is not bga file.\n");
        debug_assert(__FILE__, 952);
        __assert(__FILE__, 952, "FALSE");
    }
    p->dobjs += (int)p;
    p->mode = -1;
    p->anim = (BgaAnimDefault *)mallocseki(sizeof(BgaAnimDefault));
    *p->anim = bgaAnimDefault;
    d = (BgaDObjEnt *)p->dobjs;
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
    return (char *)p;
}

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

inline char *bga_InitSdfCamera(char *a0)
{
    BgaSdfCam *p = (BgaSdfCam *)a0;

    if (strncmp(p->id, "SDF", 3) != 0) {
        debug_StdPrintfDummy("this is not sdf camera file.\n");
        debug_assert(__FILE__, 1045);
        __assert(__FILE__, 1045, "FALSE");
    }
    return a0;
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
    /* 0x00 */ float pos[4];
    /* 0x10 */ int quat[4];
    /* 0x20 */ BgaParticleBits u;
} BgaParticleEnt;

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
                    debug_Assert("Light Object not exists.\n");
                    debug_assert(__FILE__, 1089);
                    __assert(__FILE__, 1089, "0");
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
                    debug_Assert("Shadow Object not exists.\n");
                    debug_assert(__FILE__, 1109);
                    __assert(__FILE__, 1109, "0");
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
                    debug_assert(__FILE__, 1141);
                    __assert(__FILE__, 1141, "0");
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
            p->u.obj = iosMallocDebug(ios_partition_seki, 0x30, __FILE__, 1177);
            ((BgaParticleEnt *)p->u.obj)->u.b.id = i;
            ((BgaParticleEnt *)p->u.obj)->u.b.loop =
                GetParticleLoopFlag(((BgaParticleEnt *)p->u.obj)->u.b.id);
            if (((BgaParticleEnt *)p->u.obj)->u.b.loop) {
                ((BgaParticleEnt *)p->u.obj)->u.b.eff = SetParticleEffectActiveSensing(
                    ((BgaParticleEnt *)p->u.obj)->u.b.id, bgaParticlePos, IdentityQuaternion);
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
                sprintf(buf, "OBJECT FILE \"%s\" NOT EXISTS.\n", p->name);
                /* "model data file [%s] does not exist" */
                debug_StdPrintfDummy("モデルデータファイル[%s]がありません.\n\n", p->name);
                debug_assertMessage(__FILE__, 1201, buf);
                __assert(__FILE__, 1201, "e");
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
    if (systemStatus[0]) {
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
    if (systemStatus[0]) {
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
    if (systemStatus[0]) {
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
    if (systemStatus[0]) {
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
    if (systemStatus[0]) {
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

/* Light.c's 0x50-byte light record as this file uses it: bga_CalcObject
   hands its own instance to the light objects when the stage is not lit
   through Light.c, and bga_initLightEnvelope writes only the colour at 0x20.
   The size is the record's (light_AddLight allocates 0x50). */
typedef struct BgaLight {
    /* 0x00 */ char pad00[0x20];
    /* 0x20 */ float col[4];
    /* 0x30 */ char pad30[0x20];
} BgaLight;

/* .sbss and .bss, owned by BgAnimation.o and reached only from this file
   (MAIN.MAP names no symbol in either run), each in the ROM's run order:
   whether an SDF camera is running and the Z roll the object walk has
   accumulated; then the camera matrix, the camera position at the last
   frame jump, the pivot the light-vector objects rotate about and the
   matrix built around it, the position, scale and rotation the motion
   readers fill for the object being walked, and the light record the
   light objects use when the stage has none. */
static int bgaCameraActive;

static short bgaRollZ;

static float bgaCameraMatrix[4][4];

static float bgaLastCameraPos[4];

static float bgaPivot[4];

static float bgaPivotMatrix[4][4];

static float bgaPos[4];

static float bgaScale[4];

static int bgaRot[4];

static BgaLight bgaDummyLight;

/* RECONSTRUCTION: a word read either as an int or as a float, the form this
   programmer gives such words (StageAnimation.c's AnimWord, Packet.c's
   PacketFloat).  What the bytes pin: one side of bga_calcEnvelope's pivot
   case is an alias-set-0 reference, which is what keeps the flag's store
   behind the pivot's source loads as the ROM has it; the flag itself is a
   4-aligned word in .sdata, which a union object (8-aligned under
   DATA_ALIGNMENT) cannot be, so the union is on the envelope data's side.
   What they cannot pin: the other member, the name, or whether the entry's
   data pointer carried this type rather than a cast. */
typedef union {
    int i;
    float f;
} BgaWord;

/* The flag bga_CalcObject tests before translating by the pivot. */
static int bgaPivotFlag = 0; /* derived name */

static inline float bga_palFrame(float f)
{
    if (systemStatus[0]) {
        f *= 0.82812935f;
    }
    return f;
}

/* Listing rows 1991-2001: step an envelope's motion by dt and, once it runs
   past its length (scaled for PAL, as bga_CalcSdfCamera scales it), wrap it
   to 0 when looping or hold it at the end.  The helper reads the entry's data
   word itself (row 1991).  The name is ours. */
static inline void bga_stepEnvelope(BgaEnvEnt *e, float dt, int loop)
{
    BgaExtMotion *m = (BgaExtMotion *)e->data;

    m->frame += dt;
    if ((float)m->len * (systemStatus[0] ? 0.82812935f : 1.0f) < m->frame) {
        if (loop) {
            m->frame = 0.0f;
        } else {
            m->frame = bga_palFrame((float)m->len);
        }
    }
}

/* Apply a node's envelopes (listing rows 2034-2121): each entry's type says
 * what its motion drives, the node work record's float for the object, the
 * SDF camera zoom, a light's two parameters, the gizmo, the light vector or
 * the node's object pointer; types 4 and 5 (the colour envelopes
 * bga_initLightEnvelope reads) are skipped, and any other type is reported
 * with its entry and type and asserted. */
void bga_calcEnvelope(BgaDObjEnt *p, float dt, float w, int a1, int a2)
{
    BgaEnvEnt *e;
    float v;

    e = (BgaEnvEnt *)p->env;
    if (e == 0) {
        return;
    }
    for (; e->data != 0; e++) {
        switch (e->type) {
        case 0:
            if (p->u.obj != 0) {
                ((Sub15C *)p->u.obj)->nodes[p->num].fade =
                    bga_GetExtMotion((BgaExtMotion *)e->data);
                ((Sub15C *)p->u.obj)->nodes[p->num].flags.ll |= 1;
                bga_stepEnvelope(e, dt, a2);
            }
            break;
        case 1:
            if (bgaCameraActive != 0) {
                if (a1 != 0) {
                    bgaZoom =
                        bga_GetExtMotion((BgaExtMotion *)e->data) * (float)ScreenWidth / 2.66f;
                }
            }
            bga_stepEnvelope(e, dt, a2);
            break;
        case 2:
            v = bga_GetExtMotion((BgaExtMotion *)e->data);
            switch (p->type) {
            case 6:
            case 11:
                *(float *)((char *)p->u.obj + 0x30) = v;
                bga_stepEnvelope(e, dt, a2);
                break;
            case 8:
            case 9:
                *(float *)((char *)p->u.obj + 0x80) = v;
                bga_stepEnvelope(e, dt, a2);
                break;
            }
            break;
        case 3:
            v = bga_GetExtMotion((BgaExtMotion *)e->data);
            switch (p->type) {
            case 6:
            case 11:
                *(float *)((char *)p->u.obj + 0x34) = v;
                bga_stepEnvelope(e, dt, a2);
                break;
            }
            break;
        case 4:
        case 5:
            break;
        case 6:
            if (p->u.obj != 0) {
                bga_GetGizmoMotion((BgaMotion *)e->data, ((Sub15C *)p->u.obj)->morphWeight);
                bga_stepEnvelope(e, dt, a2);
            }
            break;
        case 7:
            bgaPivot[0] = ((BgaWord *)e->data)[0].f;
            bgaPivot[1] = -((BgaWord *)e->data)[1].f;
            bgaPivot[2] = ((BgaWord *)e->data)[2].f;
            bgaPivot[3] = 1.0f;
            bgaPivotFlag = 1;
            break;
        case 8:
        case 9:
            p->u.obj = e->data;
            break;
        default:
            debug_StdPrintfDummy("Illegal Envelope Type : %p(%d)\n", e, e->type);
            debug_assert(__FILE__, 2116);
            __assert(__FILE__, 2116, "0");
            break;
        }
    }
}

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

/* Externs and record views bga_CalcObject uses (field names are ours). */

typedef struct BgaNodeBits {
    /* 0x00 */ char pad00[0x30];
    /* 0x30 */ float f30;
    /* 0x34 */ int f34;
    /* 0x38 */ union {
        struct {
            int b0 : 1;
            int b1 : 1;
            int b2 : 1;
            short f3A;
        } b;

        long long w;
    } f38;

    /* 0x40 */ float f40[4];
} BgaNodeBits;

typedef struct BgaObj {
    /* 0x00 */ short id;
    /* 0x02 */ char pad02[0xA];
    /* 0x0C */ float (*mtx)[16];
    /* 0x10 */ float (*quat)[4];
    /* 0x14 */ char pad14[0xC];
    /* 0x20 */ char pad20[0x8];
    /* 0x28 */ char pad28[0x48];
    /* 0x70 */ float rscale[3];
    /* 0x7C */ char pad7C[0x7F4];
    /* 0x870 */ BgaNodeBits *work;
} BgaObj;

extern void SetParamKyomiGObj(void *o, float *pos, float *scale);
extern void RotCurrentQuaternionX(int a);
extern void RotCurrentQuaternionY(int a);
extern void RotCurrentQuaternionZ(int a);

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

typedef struct BgaLightning { /* field names derived */
    /* 0x000 */ BgaLightningSeg seg[10];
    /* 0x140 */ int n;
    /* 0x144 */ int id;
    /* 0x148 */ int t0;
    /* 0x14C */ float frame;
    /* 0x150 */ BgaLightningDef *def;
    /* 0x154 */ struct BgaLightning *next;
} BgaLightning;

/* kept local: BgAnimation.h does not compile in this TU (conflicting types for `bga_InitData') */
extern void bga_addLightning(int kind, BgaLightningDef *a1, float *vec, int id, int t0, float f);

static inline void bga_checkCameraDistance(void)
{
    if (bgaCameraActive != 0) {
        _InverseCurrentMatrix();
        _GetCurrentMatrix(bgaCameraMatrix);
        if (GlobalTimer != 0) {
            if (_GetLength(bgaCameraMatrix[3], bgaLastCameraPos) < 100.0f) {
                GlobalTimer = 0;
                currentScreenWidth = 0;
            }
        }
    }
}

static inline void bga_stepMotion(BgaExtMotion *m, float dt, int reset)
{
    m->frame += dt;
    if ((float)m->len * (systemStatus[0] ? 0.82812935f : 1.0f) < m->frame) {
        if (reset) {
            m->frame = 0.0f;
        } else {
            m->frame = bga_palFrame((float)m->len);
        }
    }
}

void bga_CalcObject(BgaDObjEnt *d, float dt, float f13, int a1, int a2, int a3)
{
    int save;
    float *pos;

    switch (d->type) {
    case 13:
        bga_GetMotionParticle(bgaPos, bgaRot, bgaScale, (BgaPtMotion *)&d->f34);
        break;
    case 14:
    case 15:
    case 16:
        bga_GetMotionLightning(bgaPos, bgaRot, bgaScale, (BgaPtMotion *)&d->f34);
        break;
    default:
        bga_GetMotion(bgaPos, bgaRot, bgaScale, (BgaPtMotion *)&d->f34);
        break;
    }

    switch (d->type) {
    case 6:
        d->u.obj =
            (systemStatus[5] == 0) ? (void *)light_AddLight(0, 0, 2) : (void *)&bgaDummyLight;
        bga_initLightEnvelope(d);
        break;
    case 11:
        d->u.obj =
            (systemStatus[5] == 0) ? (void *)light_AddLight(0, 0, 3) : (void *)&bgaDummyLight;
        bga_initLightEnvelope(d);
        break;
    }
    bgaPivotFlag = 0;

    bga_calcEnvelope(d, dt, f13, a1, a3);
    PushQuaternion();
    _PushCurrentMatrix();
    save = bgaRollZ;
    if (bgaPivotFlag != 0) {
        _PushCurrentMatrix();
        _TransCurrentMatrix(bgaPivot);
        _RotTransCurrentMatrixYXZ(bgaPos, bgaRot);
        _ScaleVectorXYZ(bgaPivot, bgaPivot, -1.0f);
        _TransCurrentMatrix(bgaPivot);
        _ScaleCurrentMatrix(bgaScale[0], bgaScale[1], bgaScale[2]);
        _GetCurrentMatrix(bgaPivotMatrix);
        _PopCurrentMatrix();
    }
    _RotTransCurrentMatrixYXZ(bgaPos, bgaRot);
    RotCurrentQuaternionY((short)bgaRot[1]);
    RotCurrentQuaternionX((short)bgaRot[0]);
    RotCurrentQuaternionZ((short)bgaRot[2]);
    bgaRollZ -= (unsigned short)bgaRot[2];

    switch (d->type) {
    case 8:
    case 9:
        if (d->u.obj != 0) {
            ((BgaObj *)d->u.obj)->rscale[0] = 1.0f / bgaScale[0];
            ((BgaObj *)d->u.obj)->rscale[1] = 1.0f / bgaScale[1];
            ((BgaObj *)d->u.obj)->rscale[2] = 1.0f / bgaScale[2];
            _GetCurrentMatrix(d->u.obj);
        }
        break;
    case 6:
    case 11:
        if (d->u.obj != 0) {
            _GetCurrentMatrixTrans(d->u.obj);
        }
        break;
    case 12:
        _GetCurrentMatrixTrans(bgaPos);
        SetParamKyomiGObj(d->u.obj, bgaPos, bgaScale);
        break;
    case 13:
        if (d->u.obj == 0) {
            /* "unknown particle" */
            debug_StdPrintfDummy("不明なパーティクル\n");
            break;
        }
        /* RECONSTRUCTION: the bytes pin one register holding &bgaPos, set before
           the loop test's join and read by GetCurrentMatrixTrans, _CopyVector and
           the NTSC SetParticleEffect, while the PAL SetParticleEffect computes the
           address itself (cse cannot see the value across that join); a local set
           here and the static spelled in the PAL call is the text that gives it.
           The local's name is ours. */
        pos = bgaPos;
        if (bgaUniqAnimationFlag == 0 && ((BgaParticleEnt *)d->u.obj)->u.b.loop) {
            /* "a PBGA-type animation cannot use looping particles" */
            debug_StdPrintfDummy(
                "PBGAタイプのアニメーションではループのパーティクルは使用できません.\n");
            break;
        }
        _GetCurrentMatrixTrans(pos);
        if (systemStatus[5] != 0) {
            break;
        }
        CopyQuaternion(((BgaParticleEnt *)d->u.obj)->quat, GetCurrentQuaternion());
        _CopyVector(((BgaParticleEnt *)d->u.obj)->pos, pos);
        if (systemStatus[0] == 0) {
            if (0.0f < bgaScale[1]) {
                ((BgaParticleEnt *)d->u.obj)->u.b.eff = SetParticleEffectActiveSensing(
                    ((BgaParticleEnt *)d->u.obj)->u.b.id, ((BgaParticleEnt *)d->u.obj)->pos,
                    ((BgaParticleEnt *)d->u.obj)->quat);
            } else if (0.0f < bgaScale[0]) {
                ((BgaParticleEnt *)d->u.obj)->u.b.eff = SetParticleEffect(
                    ((BgaParticleEnt *)d->u.obj)->u.b.id, pos, GetCurrentQuaternion());
            }
        } else {
            if (0.41406468f <= bgaScale[1]) {
                ((BgaParticleEnt *)d->u.obj)->u.b.eff = SetParticleEffectActiveSensing(
                    ((BgaParticleEnt *)d->u.obj)->u.b.id, ((BgaParticleEnt *)d->u.obj)->pos,
                    ((BgaParticleEnt *)d->u.obj)->quat);
            } else if (0.41406468f <= bgaScale[0]) {
                ((BgaParticleEnt *)d->u.obj)->u.b.eff = SetParticleEffect(
                    ((BgaParticleEnt *)d->u.obj)->u.b.id, bgaPos, GetCurrentQuaternion());
            }
        }
        break;
    case 14:
    case 15:
        if (a2 != 0 && systemStatus[5] == 0) {
            _GetCurrentMatrixTrans(bgaPos);
            bga_addLightning(d->type, d->u.obj, bgaPos, ((BgaObj *)d->u.obj)->id,
                             bgaScale[1] == 0.0f, bgaScale[0]);
        }
        break;
    case 16:
        if (a2 != 0 && systemStatus[5] == 0) {
            _GetCurrentMatrixTrans(bgaPos);
            bga_addLightning(d->type, d->u.obj, bgaPos, ((BgaObj *)d->u.obj)->id, 0, 0.0f);
        }
        break;
    case 1:
        _ScaleCurrentMatrix(bgaScale[0], bgaScale[1], bgaScale[2]);
        break;
    case 7:
        break;
    default:
        _ScaleCurrentMatrix(bgaScale[0], bgaScale[1], bgaScale[2]);
        if (d->u.obj != 0) {
            RegularizeQuaternion(GetCurrentQuaternion());
            CopyQuaternion(((BgaObj *)d->u.obj)->quat[d->num], GetCurrentQuaternion());
            if (bgaPivotFlag != 0) {
                _CopyMatrix(&((BgaObj *)d->u.obj)->mtx[d->num], bgaPivotMatrix);
            } else {
                _GetCurrentMatrix(&((BgaObj *)d->u.obj)->mtx[d->num]);
            }
            ((BgaObj *)d->u.obj)->work[d->num].f38.b.b1 = (d->type == 10);
            if (((BgaObj *)d->u.obj)->work[d->num].f38.b.b1) {
                _CopyVector(((BgaObj *)d->u.obj)->work[d->num].f40, bgaPos);
            }
            ((BgaObj *)d->u.obj)->work[d->num].f38.b.b2 = (d->type == 4);
            ((BgaObj *)d->u.obj)->work[d->num].f38.b.f3A = bgaRollZ;
        }
        if (a1 != 0 && d->type == 2) {
            if (debug_font_flag & 1) {
                debug_Printf(600, ScreenHeight / 2 - 8, 0xCCCCCC00, (int)"LWS");
            }
            bga_checkCameraDistance();
        }
        break;
    }

    if (d->f2C != 0) {
        bga_CalcObject(d->f2C, dt, f13, a1, a2, a3);
    }
    bgaRollZ = save;
    _PopCurrentMatrix();
    PopQuaternion();
    if (d->f30 != 0) {
        bga_CalcObject(d->f30, dt, f13, a1, a2, a3);
    }
    bga_stepMotion((BgaExtMotion *)&d->f34, dt, a3);
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

        if (systemStatus[0] ? c * 0.82812935f < f : c < f) {
            float t = (float)o->f08;

            r = t;
            if (systemStatus[0]) {
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

/* kept local: BgAnimation.h does not compile in this TU (conflicting types for `bga_InitData') */
extern void bga_CalcAnimation(BgaHeader *p, int a1, int a2);

void bga_SetFrame(BgaHeader *p, int frame, int mode, int a3)
{
    float f;

    if (p->cut) {
        GlobalTimer = 1;
        bgaStreamSync = 1;
        _CopyVector(bgaLastCameraPos, bgaCameraMatrix[3]);
    }
    switch (frame) {
    case 0:
        p->frame = bga_palFrame(p->start);
        p->mode = mode;
        break;
    case -1:
        debug_StdPrintfDummy("lws animation last %s\n", (char *)p->dobjs + 4);
        p->frame = bga_palFrame(p->end);
        p->mode = mode;
        break;
    case -2:
        debug_StdPrintfDummy("lws animation off %s\n", (char *)p->dobjs + 4);
        p->frame = bga_palFrame(p->start);
        p->mode = -1;
        return;
    default:
        f = (float)frame;
        p->frame = bga_palFrame(f);
        if (f < p->start) {
            p->frame = bga_palFrame(p->start);
        } else if (p->end < f) {
            p->frame = bga_palFrame(p->end);
        }
        p->mode = mode;
        break;
    }
    bga_CalcAnimation(p, a3, 1);
}

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

#define BGA_ANIM_ENT(p) ((BgaAnimEnt *)(p)->anim)

void bga_CalcAnimation(BgaHeader *p, int a1, int a2)
{
    float m[4][4];
    float rm[4][4];
    BgaCntNode *o;
    int i;
    int f1;
    int f2;

    if (p->mode == -1) {
        return;
    }

    if (p->cut) {
        bgaCameraActive = 1;
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
        f2 = (p->mode == 1);
        f1 = p->cut && f2;
        o = ((BgaCntNode **)p->roots)[i];
        if (o == 0) {
            break;
        }
        PushQuaternion();
        _PushCurrentMatrix();
        if (a2 == 1) {
            bga_resetObjectCounter(o, p->frame, a1);
        }
        bga_CalcObject((BgaDObjEnt *)o, p->step, p->frame, f1, f2, a1);
        _PopCurrentMatrix();
        PopQuaternion();
    }

    bgaFrame = (int)p->frame;
    if (a2) {
        return;
    }

    if (p->mode == 1) {
        float end = p->end;

        p->frame += p->step;
        if (systemStatus[0] ? end * 0.82812935f < p->frame : end < p->frame) {
            if (a1 == 0) {
                p->frame = bga_palFrame(p->end);
                p->mode = 0;
            } else {
                p->frame = 0.0f;
            }
        }
    }
}

/* the PAL frame counter read back on the 60 Hz timeline: the reciprocal of
   bga_palFrame's 0.82812935f. */
static inline float bga_ntscFrame(float f)
{
    if (systemStatus[0]) {
        f *= 1.2075409f;
    }
    return f;
}

/* Listing rows 2794-2871.  The record is read through its fields: a field
 * read at a varying address is exempt from the fixed-address bgaCameraActive store
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
    bgaCameraActive = 1;
    if ((float)p->num * (systemStatus[0] ? 0.82812935f : 1.0f) < p->frame) {
        if (loop == 0) {
            p->frame = bga_palFrame((float)p->num);
            p->mode = 0;
            return;
        }
        p->frame = 0.0f;
    }

    bgaFrame = (int)(p->frame * (systemStatus[0] ? 1.2075409f : 1.0f));
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
        _SetCameraMatrix(bgaCameraMatrix, &pos, &dir, &up);
        if (GlobalTimer != 0) {
            if (_GetLength(bgaCameraMatrix[3], bgaLastCameraPos) < 100.0f) {
                GlobalTimer = 0;
                currentScreenWidth = 0;
            }
        }
        a = (short)(fov * 3.1415927f / 360.0f * 10430.378f);
        bgaZoom = 224.0f / (GetTableSin(a) / GetTableCos(a));
        _PopCurrentMatrix();
    }
    p->frame += 1.0f;
}

void bga_addLightning(int kind, BgaLightningDef *a1, float *vec, int id, int t0, float f)
{
    BgaLightning *p;

    for (p = bgaLightningList; p != 0; p = p->next) {
        if (p->id == id) {
            switch (kind) {
            case 15:
                a1->kind = -1;
                /* FALLTHROUGH */
            case 14:
                p->def = a1;
                p->frame = f;
                p->t0 = t0;
                p->seg[0].key = -1;
                _CopyVector(p->seg[0].v, vec);
                return;
            case 16: {
                BgaLightningSeg *e = &p->seg[p->n];

                e->key = a1->kind;
                _CopyVector(p->seg[p->n].v, vec);
                p->n = p->n + 1;
                return;
            }
            default:
                debug_StdPrintfDummy("illegal lightning data set.\n");
                debug_assert(__FILE__, 2960);
                __assert(__FILE__, 2960, "0");
                return;
            }
        }
    }
    p = iosMallocDebug(ios_partition_seki, 352, __FILE__, 2968);
    p->next = bgaLightningList;
    p->id = id;
    p->n = 1;
    bgaLightningList = p;
    switch (kind) {
    case 15:
        a1->kind = -1;
        /* FALLTHROUGH */
    case 14:
        p->def = a1;
        p->frame = f;
        p->t0 = t0;
        _CopyVector(p->seg[0].v, vec);
        break;
    case 16: {
        BgaLightningSeg *e = &p->seg[p->n];

        e->key = a1->kind;
        _CopyVector(p->seg[p->n].v, vec);
        p->def = 0;
        _UnitVector(p->seg[0].v);
        p->n = p->n + 1;
        break;
    }
    default:
        debug_StdPrintfDummy("illegal lightning data set.\n");
        debug_assert(__FILE__, 2994);
        __assert(__FILE__, 2994, "0");
        break;
    }
}

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

/* kept local: this TU does not include gobj.h or enemy_act.h, and its use of
   DrawLightningN does not fit the prototype in lightning.h */

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
    for (p = bgaLightningList; p != 0; p = p->next) {
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
            if (((GObj *)o)->active == 0) {
                continue;
            }
            cnt++;
            if (cnt >= 5) {
                continue;
            }
            p = list[i++];
            i %= num;
            g = p->def;
            if (systemStatus[5] == 0) {
                k = p->n;
                if (k < 10) {
                    p->n = k + 1;
                    _CopyVector(&p->seg[k], (char *)GOBJ_SUB(o)->nodeMtx + (g->f2C << 6) + 0x30);
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
    for (p = bgaLightningList; p != 0; p = p->next) {
        g = p->def;
        if (g == 0) {
            debug_StdPrintfDummy(
                "Lightning data does not found! maybe, start point < end point.\n");
            debug_assert(__FILE__, 3067);
            __assert(__FILE__, 3067, "0");
            continue;
        }
        col = bga_lightningColor(g);
        if (p->t0 != 0) {
            continue;
        }
        switch (g->kind) {
        case 1:
            o = isysGObjSearchFromObjKindID_begin(2);
            if (o == 0) {
                continue;
            }
            if (systemStatus[5] == 0) {
                k = p->n;
                if (k < 10) {
                    p->n = k + 1;
                    _CopyVector(&p->seg[k], (char *)GOBJ_SUB(o)->nodeMtx + (g->f2C << 6) + 0x30);
                }
            }
            DrawLightningN(p->n, p, &col, g->f08, g->f0C, g->f10, g->f14, g->f18, g->f1C, g->f20,
                           g->f24, g->f28, p->frame, g->f2E);
            break;
        case 2:
            for (o = isysGObjGetExist_begin(); o != 0; o = isysGObjGetExist_next(o)) {
                if (D_002C2DF4[*(int *)((char *)o + 8)].kind == 71) {
                    if (systemStatus[5] == 0) {
                        k = p->n;
                        if (k < 10) {
                            p->n = k + 1;
                            _CopyVector(&p->seg[k],
                                        (char *)GOBJ_SUB(o)->nodeMtx + (g->f2C << 6) + 0x30);
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
                    if (systemStatus[5] == 0) {
                        k = p->n;
                        if (k < 10) {
                            p->n = k + 1;
                            _CopyVector(&p->seg[k],
                                        (char *)GOBJ_SUB(o)->nodeMtx + (g->f2C << 6) + 0x30);
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

inline void bga_ResetCamera(void)
{
    bgaCameraActive = 0;
}

inline int bga_GetCameraMatrix(void *p)
{
    int v = bgaCameraActive;
    if (v != 0) {
        _CopyMatrix(p, bgaCameraMatrix);
        v = bgaCameraActive;
    } else {
        bgaZoom = 0;
    }
    return v != 0 && bgaCameraForceOff == 0;
}

inline void bga_SetCamFrame(char *data, int frame, int mode)
{
    BgaSdfCam *p = (BgaSdfCam *)data;

    p->mode = mode;
    bgaCameraActive = 1;
    if (mode == 1) {
        GlobalTimer = mode;
        bgaStreamSync = mode;
        _CopyVector(bgaLastCameraPos, bgaCameraMatrix[3]);
    }
    if (frame == -1) {
        p->frame = bga_palFrame(p->num);
    } else {
        p->frame = bga_palFrame(frame);
    }
}

inline int bga_CheckAnimationFinish(BgaHeader *p)
{
    float f = p->end;
    float t = p->frame;
    int r = 0;

    if (systemStatus[0]) {
        if (f * 0.82812935f <= t || p->mode != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p->mode != 1) {
            r = 1;
        }
    }
    return r;
}

inline int bga_CheckAnimationFrame(BgaHeader *p, int frame, int reset)
{
    float f = frame;
    float t = p->frame;
    int r = 0;

    if (systemStatus[0]) {
        if (f * 0.82812935f <= t || p->mode != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p->mode != 1) {
            r = 1;
        }
    }
    if (r && reset) {
        p->mode = 0;
    }
    return r;
}

inline int bga_CheckAnimationFrameIn(BgaHeader *p, int in, int out)
{
    float a = in;
    float t = p->frame;
    int r = 0;

    if (systemStatus[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (systemStatus[0] ? t < b * 0.82812935f : t < b) {
            r = p->mode == 1;
        }
    }
    return r;
}

inline int bga_CheckSdfCameraFinish(char *data)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float f = p->num;
    float t = p->frame;

    if (systemStatus[0]) {
        return f * 0.82812935f <= t;
    }
    return f <= t;
}

inline int bga_CheckSdfCameraFrame(char *data, int frame, int reset)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float f = frame;
    float t = p->frame;
    int r;

    if (systemStatus[0]) {
        r = f * 0.82812935f <= t;
    } else {
        r = f <= t;
    }
    if (r && reset) {
        p->mode = 0;
    }
    return r;
}

inline int bga_CheckSdfCameraFrameIn(char *data, int in, int out)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float t = p->frame;
    float a = in;
    int r = 0;

    if (systemStatus[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (systemStatus[0] ? t < b * 0.82812935f : t < b) {
            r = 1;
        }
    }
    return r;
}

inline void bga_SetCameraForceOff(void)
{
    bgaCameraForceOff = 1;
}

inline void bga_InitBGA(void)
{
    bgaCameraForceOff = 0;
    bgaLightningList = 0;
}

inline void bga_SetUniqAnimationFlag(int val)
{
    bgaUniqAnimationFlag = val;
}

inline void bga_ResetAnimation(void)
{
    BgaLightning *p;
    bgaCameraActive = 0;
    if (systemStatus[5] != 0) {
        return;
    }
    p = bgaLightningList;
    bgaLightningList = 0;
    if (p == 0) {
        return;
    }
    do {
        BgaLightning *next = p->next;
        freeseki(p);
        p = next;
    } while (p != 0);
}

inline float bga_GetZoom(void)
{
    return bgaZoom;
}
