#include "memory.h"
#include "clothAnimation.h"
#include "geometryManager.h"
#include "lineManager.h"
#include "motionManager2.h"
#include "Matrix.h"
#include "DisplayP2O.h"

void GetWormCaptureVector(void *out, GObj *act, void *node, float scale);

/* nonzero until the first worm has been set up */
static int wormFirst = 1; /* derived name */

static void disp(GObj *act);

/* A 16-byte GS colour: four 8-bit RGBA components, one per word, handed to
   DrawLine through the float view the call expects. */
typedef union { /* field names derived */
    int rgba[4];
    float f[4];
    long long d[2];
} Color16; /* derived name */

/* The worm tip highlight: the line's far endpoint and its colour. */
static const Vec16 tipLineTo = {{0.0f, 10.0f, 0.0f, 1.0f}}; /* derived name */

static const Color16 tipLineColor = {{128, 128, 128, 128}}; /* derived name */

typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) WormVec; /* derived name */

typedef struct WormInit { /* field names derived */
    float pos[3];         /* 0x00 */
    int pad0C;            /* 0x0C */
    float nseg;           /* 0x10 */
    float rate;           /* 0x14 */
    float num;            /* 0x18 */
} WormInit;               /* derived name */

typedef struct {     /* field names derived */
    ChainSet *route; /* the worm's chains (InitChains) */
    WormVec **src;
    float reduce;
    float ratio;
} WormWork; /* derived name */

static void simulate(float (*v)[4], int n, float len);
void GetWormRoute(GObj *act, void *target);

#include "worm.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"
#include "matrixDrive.h"
#include "main.h"
#include "GifPacket.h"
#include "ios.h"
#include "include_asm.h"

static void outerProcess(GObj *act)
{
    float v[4];
    float p[4];
    int n;

    if ((pad[1].flags & 0x20) != 0) {
        n = GetSkeltonFocusNode(boyGObj, 22);
        GetWormRoute(act, (char *)GOBJ_SUB(boyGObj)->nodeMtx + n * 64 + 48);
        SetWormReduceRatio(act, 1.0f);
    }

    if ((pad[1].now & 0x40) != 0) {
        n = GetSkeltonFocusNode(boyGObj, 22);
        SetDirectWormTargetPos(act, (char *)GOBJ_SUB(boyGObj)->nodeMtx + n * 64 + 48);
        GetWormCaptureVector(v, act, (char *)GOBJ_SUB(boyGObj)->nodeMtx + n * 64 + 48, 5.0f);
        GetRootPosition(p, boyGObj);
        sceVu0AddVector(p, p, v);
        SetDirectRootPosition(boyGObj, p);
        SetWormReduceRatio(act, 0.0f);
    } else {
        SetWormReduceRatio(act, 1.0f);
    }
}

static void simulate(float (*v)[4], int n, float len)
{
    float d[4];
    float acc[4];
    int i;
    int c;
    float l;
    float len2 = len * len;

    for (i = 1; i < n; i++) {
        c = 0;
        sceVu0SubVector(d, &v[i - 1], &v[i]);
        l = VectorLengthSquare(d);
        if (len2 <= l) {
            c = 1;
            sceVu0ScaleVector(acc, d, 1.0f - len / _Sqrt(l));
        } else {
            CopyVector(acc, ZeroVector);
        }
        sceVu0SubVector(d, &v[i + 1], &v[i]);
        l = VectorLengthSquare(d);
        if (len2 <= l) {
            c++;
            sceVu0ScaleVector(d, d, 1.0f - len / _Sqrt(l));
            sceVu0AddVector(acc, acc, d);
        }
        if (c == 2) {
            sceVu0ScaleVector(acc, acc, 0.5f);
        }
        sceVu0ScaleVector(acc, acc, 1.0f / (float)c);
        sceVu0AddVector(&v[i], &v[i], acc);
    }

    for (i = n - 1; i > 0; i--) {
        c = 0;
        sceVu0SubVector(d, &v[i - 1], &v[i]);
        l = VectorLengthSquare(d);
        if (len2 <= l) {
            c = 1;
            sceVu0ScaleVector(acc, d, 1.0f - len / _Sqrt(l));
        } else {
            CopyVector(acc, ZeroVector);
        }
        sceVu0SubVector(d, &v[i + 1], &v[i]);
        l = VectorLengthSquare(d);
        if (len2 <= l) {
            c++;
            sceVu0ScaleVector(d, d, 1.0f - len / _Sqrt(l));
            sceVu0AddVector(acc, acc, d);
        }
        if (c == 2) {
            sceVu0ScaleVector(acc, acc, 0.5f);
        }
        sceVu0ScaleVector(acc, acc, 1.0f / (float)c);
        sceVu0AddVector(&v[i], &v[i], acc);
    }
}

static void getAnimation(GObj *act)
{
    float tmp[4];
    WormWork *w = GOBJ_SUB(act)->work;
    ChainSet *r = w->route;
    int i, j;

    for (i = 0; i < r->num; i++) {
        int num = r->cfg[i].num;
        float (*pos)[4] = r->nodes[i].pos;
        float (*vel)[4] = r->nodes[i].vel;
        ChainParam *pm = &r->cfg[i].pm;

        for (j = 1; j < num; j++) {
            CopyVector(tmp, &vel[j]);
            sceVu0ScaleVector(&vel[j], &pos[j], -1.0f);
            sceVu0AddVector(&pos[j], &pos[j], tmp);
        }

        simulate(pos, num - 1, pm->step * w->reduce);

        for (j = 0; j < num - 1; j++) {
            r->nodes[i].len[j] = _GetLength(&pos[j], &pos[j + 1]);
        }

        for (j = 1; j < num; j++) {
            sceVu0AddVector(&vel[j], &vel[j], &pos[j]);
            sceVu0ScaleVector(&vel[j], &vel[j], 0.8f);
        }
    }
}

INCLUDE_ASM(disp);

/* the work record's reduce word as SetWormReduceRatio stores it; a store
   through WormWork moves WormGeo's reload of the work pointer (measured) */
typedef union { /* field names derived */
    float f;
    int i;
} WormFI; /* derived name */

INCLUDE_ASM(GetWormRoute);

inline void TraceWormRoute(GObj *act, float t)
{
    WormWork *w = GOBJ_SUB(act)->work;
    ChainSet *r = w->route;
    int i, j;
    float step = t * 8.99999f;

    for (i = 0; i < r->num; i++) {
        int n = r->cfg[i].num;
        for (j = 1; j < n; j++) {
            float f = step * (float)j / (float)(n - 1);
            sceVu0InterVectorXYZ(&r->nodes[i].pos[j], &w->src[i][(int)f + 1], &w->src[i][(int)f],
                                 f - (float)(int)f);
            r->nodes[i].pos[j][3] = 1.0f;
        }
    }
}

/* restart the worm's route; used only by WormGeo */
static inline void ResetWormRoute(GObj *act, WormWork *w) /* derived name */
{
    ChainSet *r = w->route;
    int i;
    int j;

    for (i = 0; i < r->num; i++) {
        int num = r->cfg[i].num;
        float (*pos)[4] = r->nodes[i].pos;
        float (*vel)[4] = r->nodes[i].vel;

        for (j = 0; j < num; j++) {
            CopyVector(&pos[j], r->cfg[i].pm.root);
            CopyVector(&vel[j], ZeroVector);
        }
    }

    GetWormRoute(act, r->cfg[0].pm.root);
    w->ratio = 0.0f;
}

INCLUDE_ASM(InitWormGeo);

void GetWormCaptureVector(void *out, GObj *act, void *node, float scale)
{
    sceVu0SubVector(out, (void *)((int)GOBJ_SUB(act) + 0x50), node);
    sceVu0Normalize(out, out);
    sceVu0ScaleVector(out, out, scale);
}

INCLUDE_ASM(WormGeo);

void WormDL(GObj *act)
{
    disp(act);
}

INCLUDE_ASM(SetDirectWormTargetPos);

INCLUDE_ASM(SetWormReduceRatio);
