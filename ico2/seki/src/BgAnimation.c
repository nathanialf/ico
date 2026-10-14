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
#include "include_asm.h"

/* bgaAnimDefault is the 0x30-byte default record
   bga_InitData block-copies into its mallocseki() allocation (two
   (0,0,0,1.0f) vectors then four words); bgaParticlePos is the (0,0,0,1.0f)
   position vector bga_ApplyDObject hands to
   SetParticleEffectActiveSensing. */
static BgaAnim bgaAnimDefault = {
    /* derived name */
    {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 0, -1, 1, 0,
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

/* The six words the file's functions share.  bgaStreamSync is read and
   cleared by streamMotionManager.c (_infoUpdate), so it is global. */
int bgaStreamSync = 0; /* derived name */

static int bgaFrame = 0; /* derived name */

static float bgaZoom = 0.0f; /* derived name */

static int bgaUniqAnimationFlag = 1; /* derived name */

static int bgaCameraForceOff = 0; /* derived name */

static struct BgaLightning *bgaLightningList = 0; /* derived name */

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

INCLUDE_ASM(bga_InitData);

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
    /* 0x00C */ char pad0C[2120];
    /* 0x854 */ char *name;
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

INCLUDE_ASM(bga_initLightEnvelope);

INCLUDE_ASM(bga_ApplyDObject);

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
   key sits on.  bga_GetMotion reads this 0x34-byte record. */
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

INCLUDE_ASM(bga_GetMotion);

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

INCLUDE_ASM(bga_GetExtMotion);

INCLUDE_ASM(bga_GetGizmoMotion);

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
   accumulated; then the camera matrix, the camera position at the last
   frame jump, the pivot the light-vector objects rotate about and the
   matrix built around it, the position, scale and rotation the motion
   readers fill for the object being walked, and the light record the
   light objects use when the stage has none. */
static int bgaCameraActive; /* derived name */

static short bgaRollZ; /* derived name */

static float bgaCameraMatrix[4][4]; /* derived name */

static float bgaLastCameraPos[4]; /* derived name */

static float bgaPivot[4]; /* derived name */

static float bgaPivotMatrix[4][4]; /* derived name */

static float bgaPos[4]; /* derived name */

static float bgaScale[4]; /* derived name */

static int bgaRot[4]; /* derived name */

static BgaLight bgaDummyLight; /* derived name */

/* a word read either as an int or as a float, the form this programmer
   gives such words (StageAnimation.c's AnimWord, Packet.c's PacketFloat) */
typedef union { /* field names derived */
    int i;
    float f;
} BgaWord; /* derived name */

/* The flag bga_CalcObject tests before translating by the pivot. */
static int bgaPivotFlag = 0; /* derived name */

static inline float bga_palFrame(float f) /* derived name */
{
    if (systemStatus[0]) {
        f *= 0.82812935f;
    }
    return f;
}

/* Step an envelope's motion by dt and, once it runs
   past its length (scaled for PAL, as bga_CalcSdfCamera scales it), wrap it
   to 0 when looping or hold it at the end.  The helper reads the entry's data
   word itself. */
static inline void bga_stepEnvelope(BgaEnvEnt *e, float dt, int loop) /* derived name */
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

INCLUDE_ASM(func_00205718);

/* Apply a node's envelopes: each entry's type says
 * what its motion drives, the node work record's float for the object, the
 * SDF camera zoom, a light's two parameters, the gizmo, the light vector or
 * the node's object pointer; types 4 and 5 (the colour envelopes
 * bga_initLightEnvelope reads) are skipped, and any other type is reported
 * with its entry and type and asserted. */
INCLUDE_ASM(bga_calcEnvelope);

/* The rotation is applied Y, then X, then Z, with the three sines derived
   from the cosines (sin = sign(angle) * sqrt(1 - cos^2)) instead of a second
   table lookup.  The VU0 block is the _TransCurrentMatrix body followed by
   the three _RotCurrentMatrix* bodies with the cos/sin pairs already in
   $vf21..$vf26; $vf27..$vf29 hold the vmr32 chain so it is built once. */
static void _RotTransCurrentMatrixYXZ(void *t, int *rot)
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
       because it is ordered by hand: every mfc1 is separated from the qmtc2
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
    /* 0x7C */ char pad7C[2036];
    /* 0x870 */ BgaNodeBits *work;
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

static inline void bga_checkCameraDistance(void) /* derived name */
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

static inline void bga_stepMotion(BgaExtMotion *m, float dt, int reset) /* derived name */
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

INCLUDE_ASM(bga_CalcObject);

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

static inline void bga_clampCount(BgaCount *o, float f) /* derived name */
{
    if (f >= 0.0f) {
        float c = (float)o->len;
        float r;

        if (systemStatus[0] ? c * 0.82812935f < f : c < f) {
            float t = (float)o->len;

            r = t;
            if (systemStatus[0]) {
                r *= 0.82812935f;
            }
        } else {
            r = f;
        }
        o->frame = r;
    } else {
        o->frame = 0.0f;
    }
}

INCLUDE_ASM(bga_resetObjectCounter);

INCLUDE_ASM(bga_SetFrame);

typedef struct BgaAnimGeom { /* field names derived */
    /* 0x000 */ char pad00[12];
    /* 0x00C */ float (*mtx)[4][4];
    /* 0x010 */ float (*quat)[4];
} BgaAnimGeom; /* derived name */

typedef struct BgaAnimObj { /* field names derived */
    /* 0x000 */ char pad00[348];
    /* 0x15C */ BgaAnimGeom *geom;
} BgaAnimObj; /* derived name */

INCLUDE_ASM(bga_CalcAnimation);

/* the PAL frame counter read back on the 60 Hz timeline: the reciprocal of
   bga_palFrame's 0.82812935f. */
static inline float bga_ntscFrame(float f) /* derived name */
{
    if (systemStatus[0]) {
        f *= 1.2075409f;
    }
    return f;
}

/* The record is read through its fields.  Both frame-rate scales are
 * `x * (PAL ? k : 1.0f)`, and each key's two values are read into locals of
 * their own, fov first. */
INCLUDE_ASM(bga_CalcSdfCamera);

INCLUDE_ASM(bga_addLightning);

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

INCLUDE_ASM(bga_DispLightning);

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

INCLUDE_ASM(bga_InitSdfCamera);

INCLUDE_ASM(bga_SetCamFrame);

INCLUDE_ASM(bga_CheckAnimationFinish);

INCLUDE_ASM(bga_CheckAnimationFrame);

INCLUDE_ASM(bga_CheckAnimationFrameIn);

INCLUDE_ASM(bga_CheckSdfCameraFinish);

INCLUDE_ASM(bga_CheckSdfCameraFrame);

INCLUDE_ASM(bga_CheckSdfCameraFrameIn);
