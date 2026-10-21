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
#include "BgAnimation.h"
#include "lightning.h"
#include "gamesys.h"
#include <assert.h>

/* the bga object kinds' names, in kind order, for the debug display */
static char *bgaObjKindName[17] = {
    /* derived name */
    "ID_OBJECT",          "ID_NULLOBJECT", "ID_CAMERA",           "ID_ZOOM",
    "ID_3D_SPRITE",       "ID_LIGHT",      "ID_STAGE_LIGHT",      "ID_AMBIENT_LIGHT",
    "ID_SHADOW_BALL",     "ID_SHADOW_BOX", "ID_CAMERA_PARENT",    "ID_STAGE_LIGHT_NO_SHADOW",
    "ID_KYOMI_NULL",      "ID_PARTICLE",   "ID_LIGHTNING_TARGET", "ID_LIGHTNING_START",
    "ID_LIGHTNING_POINT",
};

/* bgaAnimDefault is the 0x30-byte default record
   bga_InitData block-copies into its mallocseki() allocation (two
   (0,0,0,1.0f) vectors then four words); bgaParticlePos is the (0,0,0,1.0f)
   position vector bga_ApplyDObject hands to
   SetParticleEffectActiveSensing. */
static BgaAnim bgaAnimDefault = {
    /* derived name */
    {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 0, -1, 0, 0,
};

static float bgaParticlePos[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

struct BgaLightEnv;

typedef struct BgaEnvEnt { /* field names derived */
    /* 0x00 */ unsigned short type;
    /* 0x02 */ char pad02[2];
    /* 0x04 */ unsigned char *data;
} BgaEnvEnt; /* derived name */

typedef struct BgaDObjEnt { /* field names derived */

    /* 0x00 */ unsigned short type;
    /* 0x02 */ unsigned short num;
    /* 0x04 */ char name[32];
    /* 0x24 */ union {
        void *obj;                 /* particle record, geometry, Kyomi object */
        struct BgaLightEnv *light; /* ambient-light record */
        int next;                  /* the file's flat list, consumed by bga_InitData */
    } u;
    /* 0x28 */ int env;
    /* 0x2C */ struct BgaDObjEnt *child;
    /* 0x30 */ struct BgaDObjEnt *sibling;
    /* 0x34 */ int motion;
    /* 0x38 */ char pad38[12];
    /* 0x44 */ short parent;
    /* 0x46 */ char pad46[2];
} BgaDObjEnt; /* derived name */

typedef struct BgaKey { /* field names derived */
    /* 0x00 */ float v[6];
    /* 0x18 */ float tension;
    /* 0x1C */ float bias;
    /* 0x20 */ int linear;
    /* 0x24 */ int time;
} BgaKey; /* derived name */

typedef struct BgaMotion { /* field names derived */
    /* 0x00 */ BgaKey *key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaMotion; /* derived name */

/* The four words the file's functions share; nothing in this build reads
   bgaCameraForceOff. */
static float bgaZoom = 0.0f; /* derived name */

static int bgaUniqAnimationFlag = 1; /* derived name */

static struct BgaLightning *bgaLightningList = 0; /* derived name */

static int bgaCameraForceOff = 0; /* derived name */

/* Light.c's 0x50-byte light record as this file uses it: bga_CalcObject
   hands its own instance to the light objects when the stage is not lit
   through Light.c, and bga_initLightEnvelope writes only the colour at 0x20.
   The size is the record's (light_AddLight allocates 0x50). */
typedef struct BgaLight { /* field names derived */
    /* 0x00 */ char pad00[32];
    /* 0x20 */ float col[4];
    /* 0x30 */ char pad30[32];
} BgaLight; /* derived name */

/* Whether an SDF camera is running and the Z roll the object walk has
   accumulated; then the camera matrix, the pivot the light-vector objects
   rotate about and the matrix built around it, the position, scale and rotation the motion
   readers fill for the object being walked, and the light record the
   light objects use when the stage has none. */
static int bgaCameraActive; /* derived name */

static short bgaRollZ; /* derived name */

/* the walked object's depth (its position's z), which bga_CalcObject stores
   per object and no function reads */
static float bgaObjectWork; /* derived name */

static float bgaCameraMatrix[4][4]; /* derived name */

static float bgaPivot[4]; /* derived name */

static float bgaPivotMatrix[4][4]; /* derived name */

static float bgaPos[4]; /* derived name */

static float bgaScale[4]; /* derived name */

static int bgaRot[4]; /* derived name */

static BgaLight bgaDummyLight; /* derived name */

static void bga_SetCameraMatrix(void)
{
    if (bgaCameraActive != 0) {
        _InverseCurrentMatrix();
        _GetCurrentMatrix(bgaCameraMatrix);
    }
}

/* Four static helpers bga_InitData inlines. */

static inline void bga_addSiblingTail(BgaDObjEnt *c, BgaDObjEnt *d) /* derived name */
{
    while (c->sibling != 0) {
        c = c->sibling;
    }
    c->sibling = d;
}

static inline void bga_linkToParent(BgaDObjEnt *q, BgaDObjEnt *d, int no) /* derived name */
{
    do {
        if (q->num == no) {
            if (q->child == 0) {
                q->child = d;
            } else {
                bga_addSiblingTail(q->child, d);
            }
        }
        if (q->u.next == 0) {
            break;
        }
        q = (BgaDObjEnt *)q->u.next;
    } while (1);
}

static inline void bga_linkTree(BgaHeader *p) /* derived name */
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

static inline void bga_makeRootList(BgaHeader *p) /* derived name */
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

    /* the list is written as int words, which may alias the int p->dobjs, so
       the ROM reloads it after them; pointer stores would not (measured) */
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

char *bga_InitData(char *data)
{
    BgaHeader *p = (BgaHeader *)data;
    BgaDObjEnt *d;
    int i;
    unsigned int j;
    int k;

    if (strncmp(p->magic, "BGA", 3) != 0) {
        debug_StdPrintfDummy("this is not bga file.\n");
        debug_assert(__FILE__, 711);
        __assert(__FILE__, 711, "FALSE");
    }
    p->dobjs += (int)p;
    p->mode = -1;
    p->anim = mallocseki(sizeof(BgaAnim));
    *p->anim = bgaAnimDefault;
    d = (BgaDObjEnt *)p->dobjs;
    while (1) {
        d->motion += (int)p;
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
    return data;
}

typedef struct BgaSdfKey { /* field names derived */
    /* 0x00 */ char pad00[4];
    /* 0x04 */ float pos[3];
    /* 0x10 */ float at[3];
    /* 0x1C */ float roll;
    /* 0x20 */ float fov;
} BgaSdfKey; /* derived name */

/* The SDF camera record bga_InitSdfCamera checks and bga_SetCamFrame starts:
 * the "SDF" tag, the key count, the running frame, the play mode and the keys. */
typedef struct BgaSdfCam { /* field names derived */
    /* 0x00 */ char id[4];
    /* 0x04 */ int num;
    /* 0x08 */ float frame;
    /* 0x0C */ int mode;
    /* 0x10 */ BgaSdfKey key[1];
} BgaSdfCam; /* derived name */

/* an object's display object (typedef.h's Sub15C) as bga_ApplyDObject reads
   it: the node count it hands out node numbers from and the model's name */
typedef struct BgaGeom { /* field names derived */
    /* 0x000 */ char pad00[4];
    /* 0x004 */ int parentNode;
    /* 0x008 */ int nodeNum;
    /* 0x00C */ char pad0C[2020];
    /* 0x7F0 */ char *name;
} BgaGeom; /* derived name */

typedef struct BgaGObj { /* field names derived */
    /* 0x000 */ char pad00[348];
    /* 0x15C */ void *geom;
} BgaGObj; /* derived name */

/* The particle entry's word at +0x20 packs three fields: the loop flag in
   bits 0-1, the effect handle in bits 2-16 and the particle id in bits
   17-31, read and written as the whole doubleword. */
typedef union BgaParticleBits { /* field names derived */

    struct {
        int loop : 2;
        int eff : 15;
        int id : 15;
    } b;

    long long w;
} BgaParticleBits; /* derived name */

typedef struct BgaParticleEnt { /* field names derived */
    /* 0x00 */ float pos[4];
    /* 0x10 */ int quat[4];
    /* 0x20 */ BgaParticleBits u;
} BgaParticleEnt; /* derived name */

/* the fields the light envelopes write: a light's colour at 0x20 (Light.c's
   Light), an ambient volume's colour at 0x40 and the inverse extents of its
   inner and outer shells (Light.c's AmbientVolume) */
typedef struct BgaLightEnv { /* field names derived */
    /* 0x00 */ char pad00[32];
    /* 0x20 */ float col[4];
    /* 0x30 */ char pad30[16];
    /* 0x40 */ float col2[4];
    /* 0x50 */ float inner[4];
    /* 0x60 */ float outer[3];
} BgaLightEnv; /* derived name */

inline char *bga_InitSdfCamera(char *data)
{
    BgaSdfCam *p = (BgaSdfCam *)data;

    if (strncmp(p->id, "SDF", 3) != 0) {
        debug_StdPrintfDummy("this is not sdf camera file.\n");
        debug_assert(__FILE__, 803);
        __assert(__FILE__, 803, "FALSE");
    }
    return data;
}

static void bga_initLightEnvelope(BgaDObjEnt *p)
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
                    debug_assert(__FILE__, 847);
                    __assert(__FILE__, 847, "0");
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
                    debug_assert(__FILE__, 867);
                    __assert(__FILE__, 867, "0");
                }
                break;
            }
            break;
        case 5:
            switch (p->type) {
            case 8:
            case 9:
                if (p->u.light != 0) {
                    p->u.light->inner[0] = 1.0f / (((float *)d)[0] * 50.0f);
                    p->u.light->inner[1] = 1.0f / (((float *)d)[1] * 50.0f);
                    p->u.light->inner[2] = 1.0f / (((float *)d)[2] * 50.0f);
                    p->u.light->outer[0] = 1.0f / (((float *)d)[3] * 50.0f);
                    p->u.light->outer[1] = 1.0f / (((float *)d)[4] * 50.0f);
                    p->u.light->outer[2] = 1.0f / (((float *)d)[5] * 50.0f);
                } else {
                    debug_assert(__FILE__, 899);
                    __assert(__FILE__, 899, "0");
                }
                break;
            }
            break;
        /* the next envelope type, nothing to do */
        case 6:
            break;
        }
        e++;
    }
}

void bga_ApplyDObject(BgaDObjEnt *p, GObj **objs, int n)
{
    char buf[1024];
    int i;

    switch (p->type) {
    case 13:
        i = GetParticleIDWithName(p->name);
        if (i != -1) {
            p->u.obj = iosMallocDebug(ios_partition_seki, 48, __FILE__, 935);
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
                debug_assertMessage(__FILE__, 959, buf);
                __assert(__FILE__, 959, "e");
            }
            if (strcmp(((BgaGeom *)((BgaGObj *)objs[i])->geom)->name, p->name) == 0) {
                p->u.obj = ((BgaGObj *)objs[i])->geom;
                p->num = ((BgaGeom *)((BgaGObj *)objs[i])->geom)->nodeNum++;
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
        p->u.obj = CreateKyomiGObj();
        break;
    }
    if (p->child) {
        bga_ApplyDObject(p->child, objs, n);
    }
    if (p->sibling) {
        bga_ApplyDObject(p->sibling, objs, n);
    }
}

static inline int bga_findKey(BgaKey *k, int n, float f) /* derived name */
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

static inline void bga_hermite(float t, float *h0, float *h1, float *h2,
                               float *h3) /* derived name */
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
   key sits on.  bga_GetMotion, bga_GetMotionParticle
   and bga_GetMotionLightning all read this 0x34-byte record. */
typedef struct BgaPtKey { /* field names derived */
    /* 0x00 */ float pos[3];
    /* 0x0C */ float rot[3];
    /* 0x18 */ float col[3];
    /* 0x24 */ float tension;
    /* 0x28 */ float bias;
    /* 0x2C */ int linear;
    /* 0x30 */ int time;
} BgaPtKey; /* derived name */

typedef struct BgaPtMotion { /* field names derived */
    /* 0x00 */ BgaPtKey *key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaPtMotion; /* derived name */

static inline int bga_findPtKey(BgaPtKey *k, int n, float f) /* derived name */
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

typedef struct BgaExtKey { /* field names derived */
    /* 0x00 */ float value;
    /* 0x04 */ float tension;
    /* 0x08 */ float bias;
    /* 0x0C */ int linear;
    /* 0x10 */ int time;
} BgaExtKey; /* derived name */

typedef struct BgaExtMotion { /* field names derived */
    /* 0x00 */ BgaExtKey *key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaExtMotion; /* derived name */

static inline int bga_findExtKey(BgaExtKey *k, int n, float f) /* derived name */
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

static void bga_GetMotion(float *pos, int *rot, float *col, BgaPtMotion *m)
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

    f = m->frame * (30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));

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

        ta = (1.0f - k->tension) * (k->bias + 1.0f);
        tb = (1.0f - k->tension) * (1.0f - k->bias);
        tc = (1.0f - k1->tension) * (1.0f - k1->bias);
        td = (1.0f - k1->tension) * (k1->bias + 1.0f);
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
            dv = k1->pos[i] - k->pos[i];
            pos[i] = k->pos[i] + u * dv;
            dv = k1->rot[i] - k->rot[i];
            rot[i] = (short)((k->rot[i] + u * dv) * (65536.0f / 360.0f));
            dv = k1->col[i] - k->col[i];
            col[i] = k->col[i] + u * dv;
        }
    }
    pos[3] = 1.0f;
    col[3] = 1.0f;
}

static float bga_GetExtMotion(BgaExtMotion *m)
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

    f = m->frame * (30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
    if (m->n == 1) {
        return m->key->value;
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
    dv = k1->value - k->value;

    if (k1->linear == 0) {
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

        ta = (1.0f - k->tension) * (k->bias + 1.0f);
        tb = (1.0f - k->tension) * (1.0f - k->bias);
        tc = (1.0f - k1->tension) * (1.0f - k1->bias);
        td = (1.0f - k1->tension) * (k1->bias + 1.0f);
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
            m0 = s0 * (ta * (k->value - k[-1].value) + tb * dv);
        }
        if (k1->time >= m->len) {
            m1 = (tc + td) * dv;
        } else {
            m1 = s1 * (tc * dv + td * (k1[1].value - k1->value));
        }
        return k->value * h00 + k1->value * h01 + m0 * h10 + m1 * h11;
    }
    t = u * dv;
    return k->value + t;
}

static void bga_GetGizmoMotion(BgaMotion *m, float *dst)
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

    f = m->frame * (30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));

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

    if (k1->linear == 0) {
        float h00;
        float h01;
        float h10;
        float h11;
        float ta;
        float tb;
        float tc;
        float td;

        ta = (1.0f - k->tension) * (k->bias + 1.0f);
        tb = (1.0f - k->tension) * (1.0f - k->bias);
        tc = (1.0f - k1->tension) * (1.0f - k1->bias);
        td = (1.0f - k1->tension) * (k1->bias + 1.0f);
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

/* a word read either as an int or as a float, the form this programmer
   gives such words (StageAnimation.c's AnimWord, Packet.c's PacketFloat) */
typedef union { /* field names derived */
    int i;
    float f;
} BgaWord; /* derived name */

/* The flag bga_CalcObject tests before translating by the pivot. */
static int bgaPivotFlag = 0; /* derived name */

/* Set a motion's frame (set 1: to f, held between 0 and the motion's length)
   or step it by dt and, once it runs past the length, wrap it to 0 when
   looping or hold it at the end; the length is in 30 Hz frames, scaled to
   the display rate. */
static void bga_setCounter(BgaExtMotion *m, float dt, int set, float f, int loop)
{
    if (set == 1) {
        if (f >= 0.0f) {
            float r;

            if ((float)m->len * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) <
                f) {
                r = (float)m->len *
                    ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
            } else {
                r = f;
            }
            m->frame = r;
        } else {
            m->frame = 0.0f;
        }
    } else {
        m->frame += dt;
        if ((float)m->len * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) <
            m->frame) {
            if (loop) {
                m->frame = 0.0f;
            } else {
                m->frame = (float)m->len *
                           ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
            }
        }
    }
}

/* Apply a node's envelopes: each entry's type says
 * what its motion drives, the node work record's float for the object, the
 * SDF camera zoom, a light's two parameters, the gizmo, the light vector or
 * the node's object pointer; types 4 and 5 (the colour envelopes
 * bga_initLightEnvelope reads) are skipped, and any other type is reported
 * with its entry and type and asserted. */
static void bga_calcEnvelope(BgaDObjEnt *p, float dt, float w, int cut, int loop)
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
                bga_setCounter((BgaExtMotion *)e->data, dt, 0, w, loop);
            }
            break;
        case 1:
            if (bgaCameraActive != 0) {
                if (cut != 0) {
                    bgaZoom =
                        bga_GetExtMotion((BgaExtMotion *)e->data) * (float)ScreenWidth / 2.66f;
                }
            }
            bga_setCounter((BgaExtMotion *)e->data, dt, 0, w, loop);
            break;
        case 2:
            v = bga_GetExtMotion((BgaExtMotion *)e->data);
            switch (p->type) {
            case 6:
            case 11:
                *(float *)((char *)p->u.obj + 0x30) = v;
                bga_setCounter((BgaExtMotion *)e->data, dt, 0, w, loop);
                break;
            case 8:
            case 9:
                *(float *)((char *)p->u.obj + 0x80) = v;
                bga_setCounter((BgaExtMotion *)e->data, dt, 0, w, loop);
                break;
            }
            break;
        case 3:
            v = bga_GetExtMotion((BgaExtMotion *)e->data);
            switch (p->type) {
            case 6:
            case 11:
                *(float *)((char *)p->u.obj + 0x34) = v;
                bga_setCounter((BgaExtMotion *)e->data, dt, 0, w, loop);
                break;
            }
            break;
        case 4:
        case 5:
            break;
        case 6:
            if (p->u.obj != 0) {
                bga_GetGizmoMotion((BgaMotion *)e->data, ((Sub15C *)p->u.obj)->morphWeight);
                bga_setCounter((BgaExtMotion *)e->data, dt, 0, w, loop);
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
            debug_assert(__FILE__, 1496);
            __assert(__FILE__, 1496, "0");
            break;
        }
    }
}

/* The rotation is applied Y, then X, then Z. */
static void _RotTransCurrentMatrixYXZ(void *t, int *rot)
{
    _TransCurrentMatrix(t);
    _RotCurrentMatrixY(rot[1]);
    _RotCurrentMatrixX(rot[0]);
    _RotCurrentMatrixZ(rot[2]);
}

/* Externs and record views bga_CalcObject uses.  BgaNodeBits is typedef.h's
   DObjNode with its flag bits named as RegistPacket.c reads them. */

typedef struct BgaNodeBits { /* field names derived */

    /* 0x00 */ char pad00[48];
    /* 0x30 */ float fade;
    /* 0x34 */ int alpha;
    /* 0x38 */ union {
        struct {
            int fade : 1;      /* the node fades by fade and alpha */
            int screenPos : 1; /* drawn unrotated at pos in view space (type 10) */
            int billboard : 1; /* faces the camera, turned only by rotZ (type 4) */
            short rotZ;
        } b;

        long long w;
    } flags;

    /* 0x40 */ float pos[4];
} BgaNodeBits; /* derived name */

typedef struct BgaObj { /* field names derived */
    /* 0x00 */ short id;
    /* 0x02 */ char pad02[10];
    /* 0x0C */ float (*mtx)[16];
    /* 0x10 */ float (*quat)[4];
    /* 0x14 */ char pad14[12];
    /* 0x20 */ char pad20[8];
    /* 0x28 */ char pad28[72];
    /* 0x70 */ float rscale[3];
    /* 0x7C */ char pad7C[1940];
    /* 0x810 */ BgaNodeBits *work;
} BgaObj; /* derived name */

/* The lightning record bga_addLightning allocates: ten of lightning.h's
   0x20-byte nodes, the live node count, the two flags, the frame, the
   definition it was built from and the list link. */
/* The lightning definition the BGA file carries: the kind at +0x02 picks the
   object the bolt is drawn against, the four bytes at +0x04 are its colour,
   and the nine floats from +0x08 and the short at +0x2E are DrawLightningN's
   parameters, named as lightning.c names them, and the short at +0x2C is the
   node the bolt starts from. */
typedef struct BgaLightningDef { /* field names derived */
    /* 0x00 */ char pad00[2];
    /* 0x02 */ short kind;
    /* 0x04 */ unsigned char col[4];
    /* 0x08 */ float stepMin;
    /* 0x0C */ float stepMax;
    /* 0x10 */ float swayStepMin;
    /* 0x14 */ float swayStepMax;
    /* 0x18 */ float turnMin;
    /* 0x1C */ float turnMax;
    /* 0x20 */ float swayLimit;
    /* 0x24 */ float width;
    /* 0x28 */ float texLen;
    /* 0x2C */ short node;
    /* 0x2E */ short c;
} BgaLightningDef; /* derived name */

typedef struct BgaLightning { /* field names derived */
    /* 0x000 */ LightningNode seg[10];
    /* 0x140 */ int n;
    /* 0x144 */ int id;
    /* 0x148 */ int t0;
    /* 0x14C */ float frame;
    /* 0x150 */ BgaLightningDef *def;
    /* 0x154 */ struct BgaLightning *next;
} BgaLightning; /* derived name */

static void bga_addLightning(int kind, BgaLightningDef *def, float *vec, int id, int t0, float f);

static void bga_CalcObject(BgaDObjEnt *d, float dt, float frame, int cut, int play, int loop)
{
    BgaPtMotion *m = (BgaPtMotion *)&d->motion;
    int save;
    float s;

    bga_GetMotion(bgaPos, bgaRot, bgaScale, m);

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

    bga_calcEnvelope(d, dt, frame, cut, loop);
    PushQuaternion();
    _PushCurrentMatrix();
    save = bgaRollZ;
    if (bgaPivotFlag != 0) {
        _PushCurrentMatrix();
        _TransCurrentMatrix(bgaPivot);
        _TransCurrentMatrix(bgaPos);
        _RotCurrentMatrixY(bgaRot[1]);
        _RotCurrentMatrixX(bgaRot[0]);
        _RotCurrentMatrixZ(bgaRot[2]);
        _ScaleVectorXYZ(bgaPivot, bgaPivot, -1.0f);
        _TransCurrentMatrix(bgaPivot);
        _ScaleCurrentMatrix(bgaScale[0], bgaScale[1], bgaScale[2]);
        _GetCurrentMatrix(bgaPivotMatrix);
        _PopCurrentMatrix();
    }
    _RotTransCurrentMatrixYXZ(bgaPos, bgaRot);
    RotCurrentQuaternionY(bgaRot[1]);
    RotCurrentQuaternionX(bgaRot[0]);
    RotCurrentQuaternionZ(bgaRot[2]);
    bgaRollZ -= (unsigned short)bgaRot[2];
    bgaObjectWork = bgaPos[2];

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
        if (bgaUniqAnimationFlag == 0 && ((BgaParticleEnt *)d->u.obj)->u.b.loop) {
            /* "a PBGA-type animation cannot use looping particles" */
            debug_StdPrintfDummy(
                "PBGAタイプのアニメーションではループのパーティクルは使用できません.\n");
            break;
        }
        _GetCurrentMatrixTrans(bgaPos);
        s = bgaScale[0] + bgaScale[1] + bgaScale[2];
        if (4.0f < s) {
            ((BgaParticleEnt *)d->u.obj)->u.b.eff = SetParticleEffectActiveSensing(
                ((BgaParticleEnt *)d->u.obj)->u.b.id, ((BgaParticleEnt *)d->u.obj)->pos,
                ((BgaParticleEnt *)d->u.obj)->quat);
        } else if (0.0f < s) {
            ((BgaParticleEnt *)d->u.obj)->u.b.eff = SetParticleEffect(
                ((BgaParticleEnt *)d->u.obj)->u.b.id, bgaPos, GetCurrentQuaternion());
        }
        if (((BgaParticleEnt *)d->u.obj)->u.b.eff != -1) {
            CopyQuaternion(((BgaParticleEnt *)d->u.obj)->quat, GetCurrentQuaternion());
            _CopyVector(((BgaParticleEnt *)d->u.obj)->pos, bgaPos);
        }
        break;
    case 14:
    case 15:
        if (play != 0) {
            _GetCurrentMatrixTrans(bgaPos);
            bga_addLightning(d->type, d->u.obj, bgaPos, ((BgaObj *)d->u.obj)->id,
                             bgaScale[1] == 0.0f, bgaScale[0]);
        }
        break;
    case 16:
        if (play != 0) {
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
            if (bgaPivotFlag != 0) {
                _CopyMatrix(&((BgaObj *)d->u.obj)->mtx[d->num], bgaPivotMatrix);
            } else {
                _GetCurrentMatrix(&((BgaObj *)d->u.obj)->mtx[d->num]);
            }
            ((BgaObj *)d->u.obj)->work[d->num].flags.b.screenPos = (d->type == 10);
            if (((BgaObj *)d->u.obj)->work[d->num].flags.b.screenPos) {
                _GetCurrentMatrixTrans(((BgaObj *)d->u.obj)->work[d->num].pos);
            }
            ((BgaObj *)d->u.obj)->work[d->num].flags.b.billboard = (d->type == 4);
            ((BgaObj *)d->u.obj)->work[d->num].flags.b.rotZ = bgaRollZ;
            CopyQuaternion(((BgaObj *)d->u.obj)->quat[d->num], GetCurrentQuaternion());
        }
        if (cut != 0 && d->type == 2) {
            if (debug_font_flag & 1) {
                debug_Printf(600, ScreenHeight / 2 - 8, 0xCCCCCC00, "LWS");
            }
            bga_SetCameraMatrix();
        }
        break;
    }

    if (d->child != 0) {
        bga_CalcObject(d->child, dt, frame, cut, play, loop);
    }
    bgaRollZ = save;
    _PopCurrentMatrix();
    PopQuaternion();
    if (d->sibling != 0) {
        bga_CalcObject(d->sibling, dt, frame, cut, play, loop);
    }
    bga_setCounter((BgaExtMotion *)m, dt, 0, frame, loop);
}

typedef struct { /* field names derived */
    /* 0x00 */ int key;
    /* 0x04 */ int n;
    /* 0x08 */ unsigned int len;
    /* 0x0C */ float frame;
} BgaCount; /* derived name */

typedef struct { /* field names derived */
    /* 0x00 */ char pad00[4];
    /* 0x04 */ BgaCount *obj;
} BgaCountEnt; /* derived name */

typedef struct BgaCntNode { /* field names derived */
    /* 0x00 */ char pad00[40];
    /* 0x28 */ BgaCountEnt *ents;
    /* 0x2C */ struct BgaCntNode *child;
    /* 0x30 */ struct BgaCntNode *sibling;
    /* 0x34 */ BgaCount count;
} BgaCntNode; /* derived name */

static void bga_resetObjectCounter(BgaCntNode *o, float f)
{
    BgaCountEnt *e;

    e = o->ents;
    if (e != 0) {
        while (e->obj != 0) {
            bga_setCounter((BgaExtMotion *)e->obj, 0.0f, 1, f, 0);
            e++;
        }
    }
    if (o->child != 0) {
        bga_resetObjectCounter(o->child, f);
    }
    if (o->sibling != 0) {
        bga_resetObjectCounter(o->sibling, f);
    }
    bga_setCounter((BgaExtMotion *)&o->count, 0.0f, 1, f, 0);
}

void bga_SetFrame(BgaHeader *p, int frame, int mode, int loop)
{
    float f;
    int start;

    if (p->cut) {
        bgaCameraActive = mode;
    }
    start = p->start;
    if (start < 0) {
        start = 0;
    }
    switch (frame) {
    case 0:
        p->frame = (float)start * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
        p->mode = mode;
        break;
    case -1:
        p->frame = p->end * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
        p->mode = mode;
        break;
    case -2:
        p->frame = (float)start * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
        p->mode = -1;
        return;
    default:
        f = (float)frame;
        p->frame = f * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
        if (frame < start) {
            p->frame =
                (float)start * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
        } else if (p->end < f) {
            p->frame = p->end * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
        }
        p->mode = mode;
        break;
    }
    bga_CalcAnimation(p, loop, 1);
}

typedef struct BgaAnimGeom { /* field names derived */
    /* 0x000 */ char pad00[12];
    /* 0x00C */ float (*mtx)[4][4];
    /* 0x010 */ float (*quat)[4];
} BgaAnimGeom; /* derived name */

typedef struct BgaAnimObj { /* field names derived */
    /* 0x000 */ char pad00[348];
    /* 0x15C */ BgaAnimGeom *geom;
} BgaAnimObj; /* derived name */

void bga_CalcAnimation(BgaHeader *p, int loop, int reset)
{
    float m[4][4];
    BgaCntNode *o;
    int i;
    int f1;
    int f2;

    if (p->mode == -1) {
        return;
    }

    GetMatrixFromQuaternionPos(m, p->anim->quat, p->anim->pos);
    if (p->anim->obj) {
        _SetCurrentMatrix(p->anim->obj->geom->mtx[p->anim->idx]);
    } else {
        _InitCurrentMatrix();
    }
    _MulCurrentMatrixR(m);

    if (p->anim->obj) {
        CopyQuaternion(GetCurrentQuaternion(), p->anim->obj->geom->quat[p->anim->idx]);
    } else {
        SetIdentityQuaternion(GetCurrentQuaternion());
    }
    MultiQuaternion(GetCurrentQuaternion(), GetCurrentQuaternion(), p->anim->quat);

    for (i = 0;; i++) {
        f2 = (p->mode == 1);
        f1 = p->cut && f2;
        o = ((BgaCntNode **)p->roots)[i];
        if (o == 0) {
            break;
        }
        PushQuaternion();
        _PushCurrentMatrix();
        if (reset) {
            bga_resetObjectCounter(o, p->frame);
        }
        bga_CalcObject((BgaDObjEnt *)o, p->step, p->frame, f1, f2, loop);
        _PopCurrentMatrix();
        PopQuaternion();
    }

    if (reset) {
        return;
    }

    if (p->mode == 1) {
        p->frame += p->step;
        if (p->end * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) < p->frame) {
            if (loop == 0) {
                p->frame =
                    p->end * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
                p->mode = 0;
                if (p->cut) {
                    bgaCameraActive = 0;
                }
            } else {
                p->frame = 0.0f;
            }
        }
    }
}

/* The record is read through its fields.  Both frame-rate scales are the
 * display rate over 30, and each key's two values are read into locals of
 * their own, fov first. */
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
    if (p->frame * (30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1])) >=
        (float)p->num) {
        if (loop == 0) {
            p->frame =
                (float)p->num * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f);
            p->mode = 0;
            if (bgaCameraActive != 0) {
                bgaCameraActive = 0;
            }
            return;
        }
        p->frame = 0.0f;
    }
    if (debug_font_flag & 1) {
        debug_Printf(
            550, ScreenHeight / 2 - 8, 0xCCCCCC00, "%d/%d",
            (int)(p->frame * (30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]))),
            p->num);
    }

    _PushCurrentMatrix();
    fr = p->frame * (30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
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
        a = (short)(fov * 3.1415927f / 360.0f * 10430.378f);
        bgaZoom = 224.0f / (GetTableSin(a) / GetTableCos(a));
        _PopCurrentMatrix();
    }
    p->frame += 1.0f;
}

inline void bga_InitBGA(void)
{
    BgaLightning *p;

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

static void bga_addLightning(int kind, BgaLightningDef *def, float *vec, int id, int t0, float f)
{
    BgaLightning *p;

    for (p = bgaLightningList; p != 0; p = p->next) {
        if (p->id == id) {
            switch (kind) {
            case 15:
                def->kind = -1;
                /* FALLTHROUGH */
            case 14:
                p->def = def;
                p->frame = f;
                p->t0 = t0;
                p->seg[0].key = -1;
                _CopyVector(p->seg[0].pos.f, vec);
                return;
            case 16: {
                LightningNode *e = &p->seg[p->n];

                e->key = def->kind;
                _CopyVector(p->seg[p->n].pos.f, vec);
                p->n = p->n + 1;
                return;
            }
            default:
                debug_StdPrintfDummy("illegal lightning data set.\n");
                debug_assert(__FILE__, 2092);
                __assert(__FILE__, 2092, "0");
                return;
            }
        }
    }
    p = iosMallocDebug(ios_partition_seki, 352, __FILE__, 2100);
    p->next = bgaLightningList;
    p->id = id;
    p->n = 1;
    bgaLightningList = p;
    switch (kind) {
    case 15:
        def->kind = -1;
        /* FALLTHROUGH */
    case 14:
        p->def = def;
        p->frame = f;
        p->t0 = t0;
        _CopyVector(p->seg[0].pos.f, vec);
        break;
    case 16: {
        LightningNode *e = &p->seg[p->n];

        e->key = def->kind;
        _CopyVector(p->seg[p->n].pos.f, vec);
        p->def = 0;
        _UnitVector(p->seg[0].pos.f);
        p->n = p->n + 1;
        break;
    }
    default:
        debug_StdPrintfDummy("illegal lightning data set.\n");
        debug_assert(__FILE__, 2125);
        __assert(__FILE__, 2125, "0");
        break;
    }
}

/* DrawLightningN reads the colour as four words, so it is a 16-byte record
   here and not four separate ints. */
typedef struct BgaLightningCol { /* field names derived */
    unsigned int c[4];
} __attribute__((aligned(16))) BgaLightningCol; /* derived name */

/* the definition's four colour bytes widened into the 16-byte record
   DrawLightningN reads */
static inline BgaLightningCol bga_lightningColor(BgaLightningDef *g) /* derived name */
{
    BgaLightningCol c;

    c.c[0] = g->col[0];
    c.c[1] = g->col[1];
    c.c[2] = g->col[2];
    c.c[3] = g->col[3];
    return c;
}

void bga_DispLightning(void)
{
    BgaLightning *p;
    BgaLightningDef *g;
    GObj *o;
    int cnt;
    BgaLightningCol col;

    cnt = 0;
    for (p = bgaLightningList; p != 0; p = p->next) {
        g = p->def;
        if (g == 0) {
            debug_StdPrintfDummy(
                "Lightning data does not found! maybe, start point < end point.\n");
            debug_assert(__FILE__, 2155);
            __assert(__FILE__, 2155, "0");
            continue;
        }
        col = bga_lightningColor(g);
        if (p->t0 != 0) {
            continue;
        }
        switch (g->kind) {
        case 1:
            o = isysGObjSearchFromObjKindID_begin(2);
            _CopyVector(&p->seg[p->n++], (char *)GOBJ_SUB(o)->nodeMtx + (g->node << 6) + 0x30);
            DrawLightningN(p->n, p->seg, &col, g->stepMin, g->stepMax, g->swayStepMin,
                           g->swayStepMax, g->turnMin, g->turnMax, g->swayLimit, g->width,
                           g->texLen, p->frame, g->c);
            break;
        case 2:
            o = isysGObjSearchFromObjKindID_begin(45);
            _CopyVector(&p->seg[p->n++], (char *)GOBJ_SUB(o)->nodeMtx + (g->node << 6) + 0x30);
            DrawLightningN(p->n, p->seg, &col, g->stepMin, g->stepMax, g->swayStepMin,
                           g->swayStepMax, g->turnMin, g->turnMax, g->swayLimit, g->width,
                           g->texLen, p->frame, g->c);
            break;
        case 0:
            for (o = isysGObjSearchFromObjKindID_begin(4); o != 0;
                 o = isysGObjSearchFromObjKindID_next(o)) {
                cnt++;
                if (cnt >= 9) {
                    break;
                }
                if (isEnemyHyde(o) == 0 && ((GObj *)o)->active != 0) {
                    _CopyVector(&p->seg[p->n++],
                                (char *)GOBJ_SUB(o)->nodeMtx + (g->node << 6) + 0x30);
                    DrawLightningN(p->n, p->seg, &col, g->stepMin, g->stepMax, g->swayStepMin,
                                   g->swayStepMax, g->turnMin, g->turnMax, g->swayLimit, g->width,
                                   g->texLen, p->frame, g->c);
                }
            }
            break;
        default:
            DrawLightningN(p->n, p->seg, &col, g->stepMin, g->stepMax, g->swayStepMin,
                           g->swayStepMax, g->turnMin, g->turnMax, g->swayLimit, g->width,
                           g->texLen, p->frame, g->c);
            break;
        }
    }
    bga_InitBGA();
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
    return v;
}

inline void bga_SetCamFrame(char *data, int frame, int mode, int loop)
{
    BgaSdfCam *p = (BgaSdfCam *)data;

    p->mode = mode;
    bgaCameraActive = 1;
    if (frame == -1) {
        p->frame = p->num;
    } else {
        p->frame = frame;
    }
}

inline int bga_CheckAnimationFinish(BgaHeader *p)
{
    float f = p->end;
    int r = 0;

    if (f * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) < p->frame ||
        p->mode != 1) {
        r = 1;
    }
    return r;
}

inline int bga_CheckAnimationFrame(BgaHeader *p, int frame, int reset)
{
    float f = frame;
    int r = 0;

    if (f * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) < p->frame ||
        p->mode != 1) {
        r = 1;
    }
    if (r && reset) {
        if (p->cut) {
            bgaCameraActive = 0;
            bgaZoom = 0;
        }
        p->mode = 0;
    }
    return r;
}

inline int bga_CheckAnimationFrameIn(BgaHeader *p, int in, int out)
{
    float a = in;
    int r = 0;

    if (a * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) < p->frame) {
        float b = out;

        if (p->frame < b * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f)) {
            r = p->mode == 1;
        }
    }
    return r;
}

inline int bga_CheckSdfCameraFinish(char *data)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float f = p->num;

    return f * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) <= p->frame;
}

inline int bga_CheckSdfCameraFrame(char *data, int frame, int reset)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float f = frame;
    int r;

    r = f * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) <= p->frame;
    if (r && reset) {
        bgaCameraActive = 0;
        p->mode = 0;
        bgaZoom = 0;
    }
    return r;
}

inline int bga_CheckSdfCameraFrameIn(char *data, int in, int out)
{
    BgaSdfCam *p = (BgaSdfCam *)data;
    float a = in;
    int r = 0;

    if (a * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f) <= p->frame) {
        float b = out;

        if (p->frame < b * ((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f)) {
            r = 1;
        }
    }
    return r;
}

inline void bga_SetUniqAnimationFlag(int val)
{
    bgaUniqAnimationFlag = val;
}

inline float bga_GetZoom(void)
{
    return bgaZoom;
}
