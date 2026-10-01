#include "typedef.h"
#include "sugiCommon.h"
#include "debug.h"
#include "memory.h"
#include "DisplayList.h"
#include "DisplayP2O.h"
#include "Primitive.h"
#include "Texture.h"
#include "lineManager.h"
#include "motionManager2.h"
#include "quaternion.h"
#include <libvu0.h>
#include <stdlib.h>
#include "ios.h"
#include "tableSin.h"
#include <string.h>
#include "matrixDrive.h"
#include "main.h"
#include "fieldCollision.h"
#include "GifPacket.h"
#include "Matrix.h"
#include "windField.h"

typedef struct { /* field names derived */
    float v[4];
    unsigned short a;
    unsigned short b;
} ClothBuf; /* derived name */

/* the two line colours the chain debug draw alternates between, as the
   quadword DrawLine takes; constant and quadword aligned, so each copy into a
   local is one quadword load and store */
typedef struct { /* field names derived */
    int r, g, b, a;
} __attribute__((aligned(16))) LineColor; /* derived name */

static const LineColor chainLineColor0 = {255, 255, 255, 128}; /* derived name */

static const LineColor chainLineColor1 = {255, 0, 0, 128}; /* derived name */

void TestDispChainAnimation(int *a0)
{
    LineColor c0 = chainLineColor0;
    LineColor c1 = chainLineColor1;
    VECTOR mid;
    int i;
    int j;

    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < a0[1]; i++) {
        int n = *(int *)((char *)a0[0] + i * 0x50);
        char *pts = *(char **)((char *)a0[2] + i * 0x1A0);
        for (j = 1; j < n; j++) {
            char *p = pts + j * 16;
            char *q = pts + (j * 16 - 16);
            LineColor *col = (j & 1) ? &c1 : &c0;
            sceVu0AddVector(&mid, p, q);
            DrawLine(p, q, col, 0);
        }
        for (j = 0; j < 5; j++) {
            char *base = (char *)a0[2] + i * 0x1A0;
            char *w = base + j * 0x50;
            if (0.0f <= *(float *)(w + 0x10)) {
                DrawLine(base + 0x30, base + 0x80, &c0, 0);
            }
        }
    }
    gif_EndPacket();
}

void GetChainExWeightGlobalPos(float *pos, char *nodes, int idx)
{
    CopyVector(pos, nodes + idx * 0x50 + 0x30);
}

typedef struct { /* field names derived */
    float w;
    char pad[12];
    VECTOR v0;
    VECTOR v1;
    VECTOR v2;
    char pad2[16];
} ExW; /* derived name */

typedef struct { /* field names derived */
    char *pos;   /* 0x0, the chain's points, 16 bytes each */
    char *vel;   /* 0x4, their velocities */
    char *len;   /* 0x8, one float a point, the step down the chain */
    int word0C;  /* 0xC, InitChains clears it; nothing reads it */
    ExW ex[5];
} ChainNode; /* derived name */

typedef struct { /* field names derived */
    char *cfg;
    int num;
    ChainNode *nodes;
    int oddFrame; /* flipped every GetChainAnimation */
} ChainSet;       /* derived name */

/* the chain's red debug segment, built only when DEBUG is defined */
static __inline__ void chainDebugOld(VECTOR *old) /* derived name */
{
#ifdef DEBUG
    DrawLine((char *)old[0], (char *)old[1], (LineColor *)&chainLineColor1, 0);
#endif
}

void GetChainAnimation(ChainSet *sys, GObj *obj, char *mtx)
{
    VECTOR dv;
    VECTOR tv;
    float mm[16];
    VECTOR ew[5];
    char *pm;
    int i;

    pm = (char *)mm;
    sceVu0UnitMatrix(pm);
    for (i = 0; i < sys->num; i++) {
        char *cf = (char *)(i * 0x50 + (int)sys->cfg);
        int n = *(int *)cf;
        char *pts = (sys->nodes + i)->pos;
        char *vel = (sys->nodes + i)->vel;
        char *cp = cf + 0x10;
        int no;
        int j;
        int k;
        VECTOR old[n];

        if (mtx != 0 && obj != 0 && *(int *)(cf + 0x10) != -1) {
            no = GetSkeltonFocusNode(obj, *(int *)(cf + 0x10));
        } else {
            if (mtx == 0) {
                mtx = pm;
            }
            no = 0;
        }

        /* the DEBUG build draws the chain as it stands before this frame's
           step, one red segment from the node drawn last (k) to each next
           one, as TestDispChainAnimation draws it live; without DEBUG the
           loop keeps only `k = j` */
        for (j = 0; j < n; j++) {
#ifdef DEBUG
            if (j > 0) {
                DrawLine(pts + k * 16, pts + j * 16, (LineColor *)&chainLineColor1, 0);
            }
#endif
            k = j;
        }

        for (j = 0; j < n; j++) {
            CopyVector(&dv, pts + j * 16);
            *(float *)(vel + j * 16 + 4) +=
                60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) * 0.5f *
                (60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]));
            AddVectorXYZ(pts + j * 16, pts + j * 16, vel + j * 16);
            CopyVector(&old[j], pts + j * 16);
            sceVu0ScaleVector(vel + j * 16, &dv, -1.0f);
        }

        for (k = 0; k < 5; k++) {
            if (0.0f <= (sys->nodes + i)->ex[k].w) {
                CopyVector(&dv, (char *)&(sys->nodes + i)->ex[k] + 0x20);
                (sys->nodes + i)->ex[k].v2.y +=
                    60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) * 0.5f *
                    (60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]));
                CopyVector(&ew[k], (char *)&(sys->nodes + i)->ex[k] + 0x30);
                AddVectorXYZ((char *)&(sys->nodes + i)->ex[k] + 0x20,
                             (char *)&(sys->nodes + i)->ex[k] + 0x20,
                             (char *)&(sys->nodes + i)->ex[k] + 0x30);
                sceVu0ScaleVector((char *)&(sys->nodes + i)->ex[k] + 0x30, &dv, -1.0f);
            }
        }

        {
            void bindExWeight(char *ex, void *ev, float t)
            {
                VECTOR va;
                VECTOR vb;
                int id;
                int id1;
                float ll;
                float ka;
                float kb;
                float ka2;
                float kb2;
                float cl;
                float wa;
                float wb;
                float l;

                id = (int)*(float *)ex;
                id1 = id + 1;
                ll = *(float *)(ex + 0x40) * *(float *)(ex + 0x40);
                ka = t * (*(float *)ex - (float)(int)*(float *)ex);
                kb = t * (1.0f - (*(float *)ex - (float)(int)*(float *)ex));
                ka2 = ka * ka;
                kb2 = kb * kb;
                cl = *(float *)(sys->cfg + i * 0x50 + 0x40);

                wa = cl;
                wb = *(float *)(ex + 0x44);

                sceVu0InterVector(&vb, pts + id * 16, pts + id1 * 16,
                                  1.0f - (*(float *)ex - (float)(int)*(float *)ex));

                sceVu0SubVector(&dv, &vb, ex + 0x20);
                l = VectorLengthSquare(&dv);
                if (ll < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, *(float *)(ex + 0x40) / _Sqrt(l));
                    AddVectorXYZ(ex + 0x10, ex + 0x20, &dv);

                    SubVectorXYZ(&dv, ex + 0x10, pts + id * 16);
                    l = VectorLengthSquare(&dv);
                    if (ka2 < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                        AddVectorXYZ(&dv, pts + id * 16, &dv);
                    } else {
                        CopyVector(&dv, ex + 0x10);
                        wa = wb;
                    }

                    SubVectorXYZ(&va, ex + 0x10, pts + id1 * 16);
                    l = VectorLengthSquare(&va);
                    if (kb2 < l) {
                        sceVu0ScaleVectorXYZ(&va, &va, kb / _Sqrt(l));
                        AddVectorXYZ(&va, pts + id1 * 16, &va);
                    } else {
                        CopyVector(&va, ex + 0x10);
                        cl = wb;
                    }

                    sceVu0ScaleVector(&dv, &dv, wa / (cl + wa));
                    sceVu0ScaleVector(&va, &va, cl / (cl + wa));
                    AddVectorXYZ(&dv, &dv, &va);

                    SubVectorXYZ(&dv, &dv, ex + 0x10);
                    sceVu0ScaleVector(&dv, &dv, 1.0f - wb / (cl + wa + wb));
                    AddVectorXYZ(ex + 0x10, ex + 0x10, &dv);

                    SubVectorXYZ(&dv, pts + id * 16, ex + 0x10);
                    l = VectorLengthSquare(&dv);
                    if (ka2 < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                        AddVectorXYZ(pts + id * 16, ex + 0x10, &dv);
                    }

                    SubVectorXYZ(&dv, pts + id1 * 16, ex + 0x10);
                    l = VectorLengthSquare(&dv);
                    if (kb2 < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, kb / _Sqrt(l));
                        AddVectorXYZ(pts + id1 * 16, ex + 0x10, &dv);
                    }

                    sceVu0SubVector(&dv, ex + 0x20, ex + 0x10);
                    l = VectorLengthSquare(&dv);
                    if (ll < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, *(float *)(ex + 0x40) / _Sqrt(l));
                        sceVu0AddVector(ex + 0x20, ex + 0x10, &dv);
                    }
                }
                sceVu0InterVector(ex + 0x10, pts + id * 16, pts + id1 * 16,
                                  1.0f - (*(float *)ex - (float)(int)*(float *)ex));
            }

            void bind2(char *pp, int id, int ip, int in, float t)
            {
                float ka;
                float kb;
                float ka2;
                float kb2;
                float cl;
                float wa;
                float wb;
                float l;

                ka = (float)(id - ip < 0 ? -(id - ip) : id - ip) * t;
                kb = (float)(id - in < 0 ? -(id - in) : id - in) * t;
                ka2 = ka * ka;
                kb2 = kb * kb;
                cl = *(float *)(sys->cfg + i * 0x50 + 0x40);

                wa = cl;
                wb = cl;

                SubVectorXYZ(&dv, pp + id * 16, pp + ip * 16);
                l = VectorLengthSquare(&dv);
                if (ka2 < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                    AddVectorXYZ(&dv, pp + ip * 16, &dv);
                } else {
                    CopyVector(&dv, pp + id * 16);
                    cl = wb;
                }

                SubVectorXYZ(&tv, pp + id * 16, pp + in * 16);
                l = VectorLengthSquare(&tv);
                if (kb2 < l) {
                    sceVu0ScaleVectorXYZ(&tv, &tv, kb / _Sqrt(l));
                    AddVectorXYZ(&tv, pp + in * 16, &tv);
                } else {
                    CopyVector(&tv, pp + id * 16);
                    cl = wb;
                }

                sceVu0ScaleVector(&dv, &dv, wa / (cl + wa));
                sceVu0ScaleVector(&tv, &tv, cl / (cl + wa));
                AddVectorXYZ(&dv, &dv, &tv);

                SubVectorXYZ(&dv, &dv, pp + id * 16);
                sceVu0ScaleVector(&dv, &dv, 1.0f - wb / (cl + wa + wb));
                AddVectorXYZ(pp + id * 16, pp + id * 16, &dv);

                SubVectorXYZ(&dv, pp + ip * 16, pp + id * 16);
                l = VectorLengthSquare(&dv);
                if (ka < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                }
                AddVectorXYZ(pp + ip * 16, pp + id * 16, &dv);

                SubVectorXYZ(&dv, pp + in * 16, pp + id * 16);
                l = VectorLengthSquare(&dv);
                if (kb < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, kb / _Sqrt(l));
                }
                AddVectorXYZ(pp + in * 16, pp + id * 16, &dv);
            }

            void calc2(char *pp, int lo, int hi)
            {
                int m;
                int q;

                sceVu0ApplyMatrix(pts, mtx + no * 64, cp + 0x10);
                for (m = 0; m < 5; m++) {
                    if (0.0f <= (sys->nodes + i)->ex[m].w) {
                        bindExWeight((char *)&(sys->nodes + i)->ex[m], &ew[m], *(float *)(cp + 4));
                    }
                }
                for (m = 0; m < n; m++) {
                    int mp = m + 1;
                    q = n - mp;
                    bind2(pp, m, m - 1 < 0 ? 0 : m - 1, mp < n ? mp : n - 1, *(float *)(cp + 4));
                    bind2(pp, q, q - 1 < 0 ? 0 : q - 1, q + 1 < n ? q + 1 : n - 1,
                          *(float *)(cp + 4));
                }
                chainDebugOld(old);
                sceVu0ApplyMatrix(pts, mtx + no * 64, cp + 0x10);
            }

            calc2(pts, 0, n - 1);
            calc2(pts, 0, n - 1);
            calc2(pts, 0, n - 1);
            calc2(pts, 0, n - 1);
        }

        sceVu0ApplyMatrix(pts, mtx + no * 64, cp + 0x10);

        sceVu0ApplyMatrix(pts, mtx + no * 64, cp + 0x10);

        for (j = 0; j < n; j++) {
            AddVectorXYZ(vel + j * 16, vel + j * 16, pts + j * 16);
            *(float *)(vel + j * 16 + 12) = 0.0f;
        }

        for (k = 0; k < 5; k++) {
            if (0.0f <= (sys->nodes + i)->ex[k].w) {
                AddVectorXYZ((char *)&(sys->nodes + i)->ex[k] + 0x30,
                             (char *)&(sys->nodes + i)->ex[k] + 0x30,
                             (char *)&(sys->nodes + i)->ex[k] + 0x20);
            }
        }
    }
    sys->oddFrame = sys->oddFrame == 0;
}

int SetChainExtendedWeight(int *a0, int idx, float w0, float w1)
{
    int i;
    char *ex;

    if (a0[3] >= 5) {
        debug_StdPrintfDummy("No more weights... \n");
        return -1;
    }
    for (i = 0; i < 5; i++) {
        if (*(float *)((char *)a0 + 0x10 + i * 0x50) < 0.0f) {
            *(float *)((char *)a0 + i * 0x50 + 0x10) = (float)idx - 1e-6f;
            *(float *)((char *)a0 + i * 0x50 + 0x50) = w0;
            *(float *)((char *)a0 + i * 0x50 + 0x54) = w1;
            ex = (char *)a0 + 0x10 + i * 0x50;
            CopyVector(ex + 0x30, ZeroVector);
            CopyVector(ex + 0x10, (char *)a0[0] + idx * 16);
            CopyVector(ex + 0x20, (char *)a0[0] + idx * 16);
            *(float *)((char *)a0 + i * 0x50 + 0x34) =
                *(float *)((char *)a0 + i * 0x50 + 0x34) + w0;
            a0[3] = a0[3] + 1;
            return i;
        }
    }
    debug_StdPrintfDummy("Illegal weight number\n");
    return -1;
}

/* push a point back to the inner side of a wall plane */
static __inline__ void pushInsidePlane(void *p, const void *plane) /* derived name */
{
    VECTOR tv;
    float d = plane_distance(p, plane);

    if (d < 0.0f) {
        _ScaleVector(&tv, plane, d);
        _SubVectorXYZ(p, p, &tv);
    }
}

/* The cloth config record, the 0x1C-byte layout clothTest.c and flag.h carry
   (rows, spacing, columns, anchors, texture, weight). */
typedef struct ClothCfg { /* field names derived */
    int num;              /* 0x00  rows, and -1 ends the array */
    float segLength;      /* 0x04  the spacing between rows */
    int div;              /* 0x08  columns */
    int wrap;             /* 0x0C  nonzero when the last column joins the first */
    void *anchors;        /* 0x10 */
    void *tex;            /* 0x14  null means the untextured mesh */
    float weight;         /* 0x18  the fall added to each point a step */
} ClothCfg;               /* derived name */

/* The sixth parameter is the wall count, which the function recomputes from
   the wall owner before any use, so the value passed in is never read.  a6,
   the wall owner, is an object handle passed as an int. */
void GetClothAnimation(int a0, void *a1, GObj *a2, void *m, ClothCfg *cfg, int nwall, int a6,
                       int a7)
{
    VECTOR dv;
    float pw;
    float len;
    float d2;
    void *wind;
    int i;
    int j;
    int n;
    int node;
    SkelNode *focus;
    char **rowsB = (char **)a1;
    int n0 = cfg->num;
    float seg = cfg->segLength;
    int nx = cfg->div - (a7 != 0);
    float rnx = 1.0f / (float)nx;
    char *pts = (char *)cfg->anchors;
    int wrap = cfg->wrap;

    focus = 0;
    if (a6 != 0) {
        nwall = *(int *)(GOBJ_SUB(a6)->colData + 8);
    } else {
        nwall = 0;
    }
    if (a2 != 0) {
        focus = GOBJ_SUB(a2)->skel;
    }
    for (i = 0; i < n0; i++) {
        float damp = 0.8f;

        for (j = 1; j < nx; j++) {
            sceVu0ScaleVector(&dv, rowsB[i] + j * 16, damp);
            damp = damp * 0.98f;
            sceVu0ScaleVector(rowsB[i] + j * 16, ((char **)a0)[i] + j * 16, -1.0f);
            AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[i] + j * 16, &dv);
        }
    }
    for (i = 0; i < n0; i++) {
        if (focus != 0) {
            node = GetSkeltonFocusNode((GObj *)a2, *(int *)(pts + i * 48));
            sceVu0ApplyMatrix(((char **)a0)[i], (char *)GOBJ_SUB(a2)->nodeMtx + node * 64,
                              pts + i * 48 + 16);
        } else {
            if (m != 0) {
                _ApplyMatrix(((char **)a0)[i], m, pts + i * 48 + 16);
                if (a7 != 0) {
                    _ApplyMatrix(((char **)a0)[i] + nx * 16, m, pts + i * 48 + 32);
                }
            }
        }
        for (j = 1; j < nx; j++) {
            char *p = ((char **)a0)[i] + j * 16;
            /* a block-scoped work area with one word cleared that nothing
               reads after the gravity add; its type is box.c's union
               quadword */
            Vec4u work[3];

            work[2].f[1] = 0.0f;
            *(float *)(p + 4) = *(float *)(p + 4) + cfg->weight;
        }
    }
    for (j = 1; j < nx; j++) {
        float t = ((float)nx + (float)j * 0.5f) * rnx;
        float lim = t * t * seg * seg;

        for (i = 1; i < n0 / 2; i++) {
            SubVectorXYZ(&dv, ((char **)a0)[i] + j * 16, ((char **)a0)[i - 1] + j * 16);
            len = VectorLengthSquare(&dv);
            if (lim < len) {
                sceVu0ScaleVectorXYZ(&dv, &dv, t * seg / _Sqrt(len));
                AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[i - 1] + j * 16, &dv);
            }
        }
        if (n0 != 1) {
            for (i = wrap ? n0 - 1 : n0 - 2; i >= n0 / 2 - 1; i--) {
                int q;

                if (wrap != 0) {
                    q = (i + 1) % n0;
                } else {
                    q = i + 1;
                }
                SubVectorXYZ(&dv, ((char **)a0)[i] + j * 16, ((char **)a0)[q] + j * 16);
                len = VectorLengthSquare(&dv);
                if (lim < len) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, t * seg / _Sqrt(len));
                    AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[q] + j * 16, &dv);
                }
            }
        }
    }
    if (a7 == 0) {
        for (i = 0; i < n0; i++) {
            float len = *(float *)(pts + i * 48 + 4);
            float lim = len * len;

            for (j = 1; j < nx; j++) {
                SubVectorXYZ(&dv, ((char **)a0)[i] + j * 16, ((char **)a0)[i] + (j * 16 - 16));
                d2 = VectorLengthSquare(&dv);
                if (lim < d2) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, len / _Sqrt(d2));
                    AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[i] + (j * 16 - 16), &dv);
                }
            }
        }
    } else {
        /* the law of cosines on a triangle whose sides are a, b and c,
           handed straight to the arc-cosine table */
        __inline__ int arcCosOfTriangle(float a, float b, float c) /* derived name */
        {
            float aa = a * a;
            float bb = b * b;
            float cc = c * c;

            return GetTableArcCos((aa + bb - cc) / ((a + a) * b));
        }
        for (i = 0; i < n0; i++) {
            float len = *(float *)(pts + i * 48 + 4);
            float lim = len * len;

            for (j = nx - 1; j > 0; j--) {
                SubVectorXYZ(&dv, ((char **)a0)[i] + j * 16, ((char **)a0)[i] + (j * 16 + 16));
                d2 = VectorLengthSquare(&dv);
                if (lim < d2) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, len / _Sqrt(d2));
                    AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[i] + (j * 16 + 16), &dv);
                }
            }
            for (j = 1; j < nx; j++) {
                SubVectorXYZ(&dv, ((char **)a0)[i] + j * 16, ((char **)a0)[i] + (j * 16 - 16));
                d2 = VectorLengthSquare(&dv);
                if (lim < d2) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, len / _Sqrt(d2));
                    AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[i] + (j * 16 - 16), &dv);
                }
            }
            /* the vectors of the row's rotation, in a block of their own
               inside the row loop, so the wall and wind loops below reuse
               their stack */
            {
                VECTOR va;
                VECTOR vb;
                VECTOR vc;
                VECTOR vd;
                float qt[4];
                float mx[16];
                /* ve, vf and vg are read only by the DEBUG build's drawing
                   of the row's axis after the correction loop */
                VECTOR ve;
                VECTOR vf;
                VECTOR vg;
                float total;
                float rtotal;
                int angle;

                _SubVector(&va, ((char **)a0)[i] + nx * 16, ((char **)a0)[i]);
                total = VectorLength(&va);
                rtotal = 1.0f / total;
                for (j = 1; j < nx; j++) {
                    float l0;
                    float l1;

                    _SubVector(&vb, ((char **)a0)[i] + j * 16, ((char **)a0)[i]);
                    _SubVector(&vc, ((char **)a0)[i] + j * 16, ((char **)a0)[i] + nx * 16);
                    l0 = VectorLengthSquare(&vb);
                    l1 = VectorLengthSquare(&vc);
                    if (lim * (float)j * (float)j < l0 ||
                        lim * (float)(nx - j) * (float)(nx - j) < l1) {
                        _OuterProduct(&vd, &vb, &va);
                        angle = arcCosOfTriangle(total, len * (float)j, len * (float)(nx - j));
                        SetQuaternionByAxisRotateV(qt, angle, (float *)&vd);
                        GetMatrixFromQuaternion((char *)mx, (char *)qt);
                        _ApplyMatrix(&vb, mx, &va);
                        _ScaleVector(&vb, &vb, len * (float)j * rtotal);
                        _AddVectorXYZ(((char **)a0)[i] + j * 16, ((char **)a0)[i], &vb);
                    }
                }
#ifdef DEBUG
                _ScaleVector(&ve, &va, 0.5f);
                _AddVectorXYZ(&vf, ((char **)a0)[i], &ve);
                _AddVectorXYZ(&vg, ((char **)a0)[i], &va);
                DrawLine(((char **)a0)[i], (char *)&vf, (LineColor *)&chainLineColor0, 0);
                DrawLine((char *)&vf, (char *)&vg, (LineColor *)&chainLineColor1, 0);
#endif
            }
        }
    }
    for (n = 0; n < nwall; n++) {
        /* the wall owner's sub-record, then the query for its n-th wall
           plane */
        int sub = *(int *)(a6 + 0x15C),
            q[3] = {a6, 0, *(int *)(*(int *)(sub + 0x70) + 0x10) + n * 80};
        VECTOR pl;

        GetGlobalWallPlane(&pl, q);
        for (i = 0; i < n0; i++) {
            for (j = 1; j < nx; j++) {
                pushInsidePlane(((char **)a0)[i] + j * 16, &pl);
            }
        }
    }
    wind = GetWindVector(&pw, ((char **)a0)[0]);
    pw = pw / 40960.0f;
    for (i = 0; i < n0; i++) {
        for (j = 1; j < nx; j++) {
            AddVectorXYZ(rowsB[i] + j * 16, rowsB[i] + j * 16, ((char **)a0)[i] + j * 16);
            AddVectorXYZ(rowsB[i] + j * 16, rowsB[i] + j * 16, wind);
            {
                VECTOR r = {pw * (float)((rand() & 0x7FFF) - 16383),
                            pw * (float)((rand() & 0x7FFF) - 16383),
                            pw * (float)((rand() & 0x7FFF) - 16383), 0.0f};

                AddVectorXYZ(rowsB[i] + j * 16, rowsB[i] + j * 16, &r);
            }
        }
    }
}

/* One entry of the four-corner anchor table the cloth is pinned to: the
   middle vector is the local-space anchor position _ApplyMatrix transforms
   into the corner point. */
typedef struct { /* field names derived */
    VECTOR v0;
    VECTOR v1;
    VECTOR v2;
} ClothFixPoint; /* derived name */

typedef struct { /* field names derived */
    int nx;
    char pad04[4];
    int ny;
    char pad0C[4];
    ClothFixPoint *fix;
} ClothFixCfg; /* derived name */

/* the debug draw of a fix point's anchor, built only when DEBUG is defined */
static __inline__ void clothFixDebug(ClothFixPoint *fix) /* derived name */
{
#ifdef DEBUG
    DrawLine((char *)fix->v0, (char *)fix->v1, (LineColor *)&chainLineColor0, 0);
#endif
}

void GetClothAnimationFix4Points(VECTOR **pa, VECTOR **pv, ClothFixCfg *cfg, void *mtx)
{
    VECTOR dv;
    int i;
    int j;
    int nx;
    int ny;
    ClothFixPoint *q;

    nx = cfg->nx;
    ny = cfg->ny;
    q = cfg->fix;

    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            _ScaleVector(&dv, &pv[i][j], 0.98f);
            _ScaleVector(&pv[i][j], &pa[i][j], -1.0f);
            pv[i][j].w = 0.0f;
            _AddVectorXYZ(&pa[i][j], &pa[i][j], &dv);
        }
    }

    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {}
    }

    _ApplyMatrix(pa[0], mtx, &q[0].v1);
    _ApplyMatrix(pa[nx - 1], mtx, &q[1].v1);
    _ApplyMatrix(&pa[0][ny - 1], mtx, &q[2].v1);
    _ApplyMatrix(&pa[nx - 1][ny - 1], mtx, &q[3].v1);

    {
        void yTension(int y)
        {
            __inline__ void interHalf(VECTOR * d, VECTOR * a, VECTOR * b) /* derived name */
            {
                _InterVectorXYZ(d, a, b, 0.5f);
            }
            VECTOR *r;
            int x;
            int xp;
            int m;
            int mp;
            int mm;

            r = pa[y];
            clothFixDebug(q);
            for (x = 1; x < ny - 1; x++) {
                xp = x + 1;
                m = ny - xp;
                mp = m + 1;
                mm = m - 1;
                interHalf(&r[x], &r[x + 1], &r[x - 1]);
                interHalf(&r[m], &r[mp], &r[mm]);
            }
        }
        void xTension(int x)
        {
            __inline__ void interHalf(VECTOR * d, VECTOR * a, VECTOR * b) /* derived name */
            {
                _InterVectorXYZ(d, a, b, 0.5f);
            }
            int y;
            int yp;
            int m;
            int mp;
            int mm;

            for (y = 1; y < nx - 1; y++) {
                yp = y + 1;
                m = nx - yp;
                mp = m + 1;
                mm = m - 1;
                interHalf(&pa[y][x], &pa[y + 1][x], &pa[y - 1][x]);
                interHalf(&pa[m][x], &pa[mp][x], &pa[mm][x]);
            }
        }
        VECTOR rv;
        VECTOR rt;
        VECTOR wp;
        VECTOR *wv;
        int n;

        yTension(0);
        yTension(nx - 1);
        xTension(0);
        xTension(ny - 1);
        for (n = 1; n < nx - 1; n++) {
            yTension(n);
        }
        for (n = 1; n < ny - 1; n++) {
            xTension(n);
        }

        wv = (VECTOR *)GetWindVector(&wp, pa[0]);
        wp.x = wp.x / 40960.0f;
        for (i = 0; i < nx; i++) {
            for (j = 0; j < ny; j++) {
                AddVectorXYZ(&pv[i][j], &pv[i][j], &pa[i][j]);
                AddVectorXYZ(&pv[i][j], &pv[i][j], wv);
                rt.x = wp.x * 3.0f * (float)((rand() & 0x7fff) - 16383);
                rt.y = wp.x * 3.0f * (float)((rand() & 0x7fff) - 16383);
                rt.z = wp.x * 3.0f * (float)((rand() & 0x7fff) - 16383);
                rt.w = 0.0f;
                rv = rt;
                AddVectorXYZ(&pv[i][j], &pv[i][j], &rv);
            }
        }
    }
}

/* the two cap planes of the unit cylinder clipCylinderCollision clips
   against, each with a zero vector after it */
static sceVu0FVECTOR clipPlane[2][2] = {
    {{0.0f, -1.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {{0.0f, 1.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
}; /* derived name */

/* the squared radius of the cylinder the cloth is clipped against */
static float cylinderRadiusSq = 1.0f; /* derived name */

/* checkOverThePlane and getCrossPoint, which clipCylinderCollision and
   getCloth4D inline and the exported functions further down call, and a
   file-static copy of checkFrontAcross (a call of the inline would return
   through a temporary) */
static __inline__ int checkOverThePlane_i(void *a0, void *a1) /* derived name */
{
    if (0.0f < plane_distance(a0, a1))
        return 1;
    return 0;
}

static __inline__ int checkFrontAcross_i(void *a0, void *a1) /* derived name */
{
    if (0.0f <= plane_distance(a0, a1)) {
        if (plane_distance((char *)a0 + 0x10, a1) < 0.0f)
            return 1;
    }
    return 0;
}

static __inline__ void getCrossPoint_i(void *out, void *seg, void *plane) /* derived name */
{
    float v[4];
    float d0 = plane_distance(seg, plane);
    float d1 = -plane_distance((char *)seg + 0x10, plane);

    sceVu0SubVector(v, (char *)seg + 0x10, seg);
    sceVu0ScaleVectorXYZ(v, v, d0 / (d0 + d1));
    AddVectorXYZ(out, seg, v);
}

/* the squared XZ length, getXZLengthSquare's sequence */
static __inline__ float xzLengthSquare(const void *p) /* derived name */
{
    float d;
    /* one asm block in plane_distance's style, without a memory clobber */
    __asm__ __volatile__("lqc2 $vf4, 0x0(%1)\n\t"
                         "vmul.xz $vf4, $vf4, $vf4\n\t"
                         "vaddz.x $vf4, $vf4, $vf4z\n\t"
                         "qmfc2.ni $2, $vf4\n\t"
                         "mtc1 $2, %0"
                         : "=f"(d)
                         : "r"(p)
                         : "$2");
    return d;
}

/* bothOverThePlane, nested before `d`, tests both ends of the segment p
   against one plane */
int clipCylinderCollision(char *p, void *pt)
{
    __inline__ int bothOverThePlane(const void *pl) /* derived name */
    {
        if (checkOverThePlane_i(p, pl) && checkOverThePlane_i(p + 0x10, pl))
            return 1;
        return 0;
    }
    float d[4];

    if (bothOverThePlane(clipPlane[0])) {
        return -1;
    }
    if (bothOverThePlane(clipPlane[1])) {
        return -1;
    }
    sceVu0SubVector(d, p, p + 0x10);
    d[1] = 0.0f;
    if (checkFrontAcross_i(p, d)) {
        sceVu0Normalize(d, d);
        getCrossPoint_i(p + 0x20, p, d);
        if (xzLengthSquare(p + 0x20) < cylinderRadiusSq) {
            AddVectorXYZ(p + 0x20, p + 0x20, d);
            return 1;
        }
    }
    return -1;
}

ChainSet *InitChains(char *a0)
{
    ChainSet *r;
    int i = 0;
    int j;
    float step;

    r = (ChainSet *)iosMallocDebug(ios_partition_sugipon, 0x10, "src/clothAnimation.c", 1192);
    r->cfg = a0;
    while (*(int *)(i * 0x50 + (int)a0) != -1) {
        i++;
    }
    r->num = i;
    r->nodes =
        (ChainNode *)iosMallocDebug(ios_partition_sugipon, i * 0x1A0, "src/clothAnimation.c", 1198);
    r->oddFrame = 0;
    for (i = 0; i < r->num; i++) {
        r->nodes[i].pos = iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x50 + (int)a0) * 16,
                                         "src/clothAnimation.c", 1202);
        r->nodes[i].vel = iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x50 + (int)a0) * 16,
                                         "src/clothAnimation.c", 1203);
        r->nodes[i].len = iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x50 + (int)a0) * 4,
                                         "src/clothAnimation.c", 1204);
        r->nodes[i].word0C = 0;
        for (j = 0; j < 5; j++) {
            r->nodes[i].ex[j].w = -1.0f;
            CopyVector(&r->nodes[i].ex[j].v0, ZeroPoint);
            CopyVector(&r->nodes[i].ex[j].v1, ZeroPoint);
            CopyVector(&r->nodes[i].ex[j].v2, ZeroVector);
        }
        for (j = 0; j < *(int *)(i * 0x50 + (int)r->cfg); j++) {
            CopyVector(r->nodes[i].pos + j * 16, a0 + i * 0x50 + 0x20);
            CopyVector(r->nodes[i].vel + j * 16, ZeroVector);
            step = *(float *)(a0 + i * 0x50 + 0x14);
            *(float *)(j * 4 + (int)r->nodes[i].len) = step;
            if (j != 0) {
                *(float *)(j * 16 + (int)r->nodes[i].pos + 4) =
                    *(float *)(j * 16 + (int)r->nodes[i].pos - 0xC) + step;
            }
        }
    }
    return r;
}

typedef struct { /* field names derived */
    long long q[89];
} TexBlob; /* derived name */

/* one cloth InitCloth4D builds: its owner, the mesh it draws and the point
   rows the cloth step walks */
typedef struct Cloth4D { /* field names derived */
    int gobj;
    Mesh3D *mesh;
    Prim3DVec **pos; /* 0x8, one row a column, into the mesh's positions */
    Prim3DVec **vel; /* 0xC, one row a column, the points' velocities */
    Prim3DVec **nrm; /* 0x10, one row a column, into the mesh's normals */
    int pad14;
    TexBlob tex;
    int cfg;
    int colNum;     /* 0x2E4, the count of collision cylinders (ClothHangCfg rows) */
    char **colNode; /* 0x2E8, the focus node each cylinder hangs from */
    char *colMtx;   /* 0x2EC, one matrix a cylinder */
    char *col;      /* 0x2F0, the cylinders, scaled by the actor's scale */
    int word2F4;    /* 0x2F4, InitCloth4D clears it; nothing reads it */
    int collision;  /* 0x2F8, nonzero while the cylinders collide (girl.c's debug_hair_collision) */
} Cloth4D;          /* derived name */

typedef struct { /* field names derived */
    int num;
    int **rec;
} ClothSet; /* derived name */

ClothSet *InitClothes(int cfg)
{
    ClothSet *r;
    int i = 0;
    int m;
    int q;
    float aa[4];
    float bb[4];

    r = (ClothSet *)iosMallocDebug(ios_partition_sugipon, 8, "src/clothAnimation.c", 1235);
    debug_StdPrintfDummy("\x1b[36mALLOC CLOTHES\x1b[m\n");
    while (*(int *)(i * 0x1C + cfg) != -1) {
        i++;
    }
    r->num = i;
    r->rec = (int **)iosMallocDebug(ios_partition_sugipon, i * 0x2E0, "src/clothAnimation.c", 1240);
    for (i = 0; i < r->num; i++) {
        if (*(int *)(i * 0x1C + cfg + 0x14) != 0) {
            *(Mesh3D **)(i * 0x2E0 + (int)r->rec) = prim_InitMesh3D(
                *(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x5C, 0x80808080, 1);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 1;
            *(TexBlob *)(i * 0x2E0 + (int)r->rec + 0x18) =
                *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(*(void **)(i * 0x1C + cfg + 0x14)));
        } else {
            *(Mesh3D **)(i * 0x2E0 + (int)r->rec) = prim_InitMesh3D(
                *(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x4C, 0xFFFFFF80, 1);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 0;
        }
        *(char **)(i * 0x2E0 + (int)r->rec + 4) = iosMallocDebug(
            ios_partition_sugipon, *(int *)(i * 0x1C + cfg) * 4, "src/clothAnimation.c", 1268);
        *(char **)(i * 0x2E0 + (int)r->rec + 8) = iosMallocDebug(
            ios_partition_sugipon, *(int *)(i * 0x1C + cfg) * 4, "src/clothAnimation.c", 1269);
        *(char **)(i * 0x2E0 + (int)r->rec + 0xC) = iosMallocDebug(
            ios_partition_sugipon, *(int *)(i * 0x1C + cfg) * 4, "src/clothAnimation.c", 1270);
        for (m = 0; m < *(int *)(i * 0x1C + cfg); m++) {
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) =
                (char *)(*(int *)(*(char **)(i * 0x2E0 + (int)r->rec) + 0x6C) +
                         m * *(int *)(i * 0x1C + cfg + 8) * 16);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) =
                iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x1C + cfg + 8) * 16,
                               "src/clothAnimation.c", 1275);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC)) =
                iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x1C + cfg + 8) * 4,
                               "src/clothAnimation.c", 1276);
            memset(aa, 0, 16);
            aa[3] = 1.0f;
            memset(bb, 0, 16);
            for (q = 0; q < *(int *)(i * 0x1C + cfg + 8); q++) {
                CopyVector(
                    *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) + q * 16, aa);
                CopyVector(
                    *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) + q * 16, bb);
                *(int *)(q * 4 +
                         (int)*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC))) =
                    -1;
            }
        }
    }
    return r;
}

ClothSet *InitClothesNoShade(int cfg)
{
    ClothSet *r;
    int i = 0;
    int m;
    int q;
    float aa[4];
    float bb[4];

    r = (ClothSet *)iosMallocDebug(ios_partition_sugipon, 8, "src/clothAnimation.c", 1296);
    debug_StdPrintfDummy("\x1b[36mALLOC CLOTHES\x1b[m\n");
    while (*(int *)(i * 0x1C + cfg) != -1) {
        i++;
    }
    r->num = i;
    r->rec = (int **)iosMallocDebug(ios_partition_sugipon, i * 0x2E0, "src/clothAnimation.c", 1301);
    for (i = 0; i < r->num; i++) {
        if (*(int *)(i * 0x1C + cfg + 0x14) != 0) {
            *(Mesh3D **)(i * 0x2E0 + (int)r->rec) = prim_InitMesh3D(
                *(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x5C, 0x80808080, 0);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 1;
            *(TexBlob *)(i * 0x2E0 + (int)r->rec + 0x18) =
                *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(*(void **)(i * 0x1C + cfg + 0x14)));
        } else {
            *(Mesh3D **)(i * 0x2E0 + (int)r->rec) = prim_InitMesh3D(
                *(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x4C, 0xFFFFFF80, 0);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 0;
        }
        *(char **)(i * 0x2E0 + (int)r->rec + 4) = iosMallocDebug(
            ios_partition_sugipon, *(int *)(i * 0x1C + cfg) * 4, "src/clothAnimation.c", 1329);
        *(char **)(i * 0x2E0 + (int)r->rec + 8) = iosMallocDebug(
            ios_partition_sugipon, *(int *)(i * 0x1C + cfg) * 4, "src/clothAnimation.c", 1330);
        *(char **)(i * 0x2E0 + (int)r->rec + 0xC) = iosMallocDebug(
            ios_partition_sugipon, *(int *)(i * 0x1C + cfg) * 4, "src/clothAnimation.c", 1331);
        for (m = 0; m < *(int *)(i * 0x1C + cfg); m++) {
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) =
                (char *)(*(int *)(*(char **)(i * 0x2E0 + (int)r->rec) + 0x6C) +
                         m * *(int *)(i * 0x1C + cfg + 8) * 16);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) =
                iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x1C + cfg + 8) * 16,
                               "src/clothAnimation.c", 1336);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC)) =
                iosMallocDebug(ios_partition_sugipon, *(int *)(i * 0x1C + cfg + 8) * 4,
                               "src/clothAnimation.c", 1337);
            memset(aa, 0, 16);
            aa[3] = 1.0f;
            memset(bb, 0, 16);
            for (q = 0; q < *(int *)(i * 0x1C + cfg + 8); q++) {
                CopyVector(
                    *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) + q * 16, aa);
                CopyVector(
                    *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) + q * 16, bb);
                *(int *)(q * 4 +
                         (int)*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC))) =
                    -1;
            }
        }
    }
    return r;
}

void DispClothMesh(int *a0, void *a1, void *a2)
{
    int t;
    dl_SetDLPriority(2);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(a0[0], 5, buffer_ID);
    gif_StartPacketPri(2);
    gif_SetAlpha(1, 7, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    if (a0[4] != 0) {
        t = tex_GetTextureNo((char *)a0 + 0x18);
    } else {
        t = -1;
    }
    prim_DispMesh3D(a0[0], a1, a2, t);
}

/* the wire mesh's three line colours, one word per channel, RGBA: the cross
   links between rows, the general line, and the seam columns (i == 0 and the
   middle column) */
static int wireCrossColor[4] = {0, 32, 128, 128}; /* derived name */

static int wireColor[4] = {128, 64, 0, 128}; /* derived name */

static int wireSeamColor[4] = {0, 128, 0, 128}; /* derived name */

void DispMeshWire(Prim3DVec **rows, int nx, int ny)
{
    int i;
    int j;

    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < nx; i++) {
        for (j = 1; j < ny; j++) {
            if (i == 0 || i == nx / 2 - 1) {
                DrawLineG(&rows[i][j], wireSeamColor, &rows[i][j - 1], wireSeamColor, 0);
            } else {
                DrawLineG(&rows[i][j], wireColor, &rows[i][j - 1], wireColor, 0);
            }
        }
    }
    for (j = 0; j < ny; j++) {
        if (j == ny - 1) {
            for (i = 1; i < nx; i++) {
                DrawLineG(&rows[i][j], wireColor, &rows[i - 1][j], wireColor, 0);
            }
        } else {
            for (i = 1; i < nx; i++) {
                DrawLineG(&rows[i][j], wireColor, &rows[i - 1][j], wireCrossColor, 0);
            }
        }
    }
    gif_EndPacket();
}

void DispCloth4D(Cloth4D *c, void *a1, void *a2)
{
    int t;
    int *m;
    dl_SetDLPriority(1);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(c->mesh, 3, buffer_ID);
    if (((int *)c->cfg)[8] != 0) {
        t = tex_GetTextureNo(&c->tex);
    } else {
        t = -1;
    }
    gif_StartPacketPri(1);
    gif_SetAlpha(1, 7, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(c->mesh, a1, a2, t);
    if (debug_cloth_info != 0) {
        m = (int *)c->cfg;
        DispMeshWire(c->pos, m[0], m[1]);
    }
}

void DispCloth4DWithAdd(Cloth4D *c, void *a1, void *a2)
{
    int t;
    int *m;
    dl_SetDLPriority(1);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(c->mesh, 3, buffer_ID);
    if (((int *)c->cfg)[8] != 0) {
        t = tex_GetTextureNo(&c->tex);
    } else {
        t = -1;
    }
    gif_StartPacketPri(1);
    gif_SetAlpha(1, 5, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(c->mesh, a1, a2, t);
    if (debug_cloth_info != 0) {
        m = (int *)c->cfg;
        DispMeshWire(c->pos, m[0], m[1]);
    }
}

/* windNoise is the ring of eleven random wind vectors getCloth4D_preProcess
   fills and cycles through, explicitly zeroed; the up and down vectors are
   what getCloth4D applies the node matrix to; cylinderColor is its debug wire
   cylinder's colour; procMatrix is the matrix the nested proc applies */
static sceVu0FVECTOR windNoise[11] = {{0.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

static sceVu0FVECTOR clothUpVector = {0.0f, 1.0f, 0.0f, 0.0f}; /* derived name */

static sceVu0FVECTOR clothDownVector = {0.0f, -1.0f, 0.0f, 0.0f}; /* derived name */

static int cylinderColor[4] = {32, 64, 128, 128}; /* derived name */

static sceVu0FMATRIX procMatrix = {
    {1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}; /* derived name */

/* the two point writers: add, or set, a scaled transformed vector */
static __inline__ void clothAddPoint(void *dst, const void *src, float f) /* derived name */
{
    VECTOR tv;

    _ApplyCurrentMatrix(&tv, src);
    _ScaleVector(&tv, &tv, f);
    _AddVectorXYZ(dst, dst, &tv);
}

static __inline__ void clothSetPoint(void *dst, const void *src, float f) /* derived name */
{
    VECTOR tv;

    _ApplyCurrentMatrix(&tv, src);
    _ScaleVectorXYZ(dst, &tv, f);
}

/* One entry of the Cloth4DCfg point table (clothAnimation.h spells the same
   96 bytes with the two links as named fields): the column loop reads the
   links by index. */
typedef struct { /* field names derived */
    int node;
    float weight;
} Cloth4DLink; /* derived name */

typedef struct {  /* field names derived */
    float length; /* 0x00, the column's length */
    char pad04[12];
    float pos[4];
    float dir[4];
    Cloth4DLink link[2]; /* 0x30 */
    float (*uv)[2];
    char pad44[12];
    float vec50[4];
} Cloth4DCol; /* derived name */

void getCloth4D_preProcess(void *a0, float g, float damp, float z, float w, int tight, void *qa,
                           void *qb)
{
    VECTOR dv;
    float work[4][4];
    int i;
    int j;
    char **rowsB = (char **)((int *)a0)[2];
    char **rowsD = (char **)((int *)a0)[4];
    char **rowsC = (char **)((int *)a0)[3];
    int *cfg = (int *)((int *)a0)[184];
    int nx = cfg[0] - (cfg[2] != 0);
    int ny = cfg[1];
    VECTOR va[nx];
    float rz;
    float t;

    for (i = 0; i < nx; i++) {
        for (j = 1; j < ny; j++) {
            sceVu0ScaleVector(&dv, rowsC[i] + j * 16, damp);
            CopyVector(rowsC[i] + j * 16, rowsB[i] + j * 16);
            AddVectorXYZ(rowsB[i] + j * 16, rowsB[i] + j * 16, &dv);
        }
    }
    for (i = 0; i < nx; i++) {
        for (j = 0; j < 2; j++) {
            int n = ((Cloth4DCol *)cfg[9])[i].link[j].node;
            Cloth4DCol *pt;
            float f;
            void *sk;

            if (n == -1) {
                break;
            }
            pt = &((Cloth4DCol *)cfg[9])[i];
            f = pt->link[j].weight;
            sk = *(void **)(*(int *)a0 + 0x15C);
            _MulMatrix(work, *(char **)((char *)sk + 0xC) + n * 64,
                       *(char **)((char *)sk + 0x90) + n * 64);
            _SetCurrentMatrix(work);
            if (j == 0) {
                clothSetPoint(rowsB[i], pt->pos, f);
                clothSetPoint(rowsD[i], pt->dir, f);
                clothSetPoint(&va[i], pt->vec50, f);
            } else {
                clothAddPoint(rowsB[i], pt->pos, f);
                clothAddPoint(rowsD[i], pt->dir, f);
                clothAddPoint(&va[i], pt->vec50, f);
            }
        }
        ((VECTOR *)rowsB[i])->w = 1.0f;
        ((VECTOR *)rowsD[i])->w = 1.0f;
        va[i].w = 0.0f;
    }
    {
        float mx[16];
        float wpow;
        int c;

        c = 0;
        _ScaleVectorXYZ(&work[0], GetWindVector(&wpow, rowsB[0]), w);
        wpow = wpow * (w * 2.44140625e-05f);
        for (i = 0; i < 11; i++) {
            for (j = 0; j < 3; j++) {
                windNoise[i][j] = wpow * (float)((rand() & 0x7FFF) - 16383);
            }
        }
        rz = 1.0f / (float)(ny - 1);
        GetInverseQuaternion(&work[2], qa);
        MultiQuaternion(&work[1], qa, qb);
        MultiQuaternion(&work[1], &work[1], &work[2]);
        GetMatrixFromQuaternion((char *)mx, (char *)&work[1]);
        for (j = 1; j < ny; j++) {
            t = (float)(ny - j) * rz * z + (1.0f - z);
            t = t * t;
            if (tight) {
                for (i = 0; i < nx; i++) {
                    _ApplyMatrix(&va[i], mx, &va[i]);
                }
            }
            for (i = 0; i < nx; i++) {
                SubVectorXYZ(&work[3], rowsB[i] + j * 16, rowsB[i] + (j * 16 - 16));
                AddVectorXYZ(&work[3], &work[3], &work[0]);
                AddVectorXYZ(&work[3], &work[3], windNoise[c]);
                c = c + 1;
                if (c == 11) {
                    c = 0;
                }
                _InterVectorXYZ(&work[3], &va[i], &work[3], t);
                work[3][1] = work[3][1] + g;
                AddVectorXYZ(rowsB[i] + j * 16, rowsB[i] + (j * 16 - 16), &work[3]);
            }
        }
    }
}

/* the four procMatrix elements proc writes its Y rotation through */
static float *procCosXX = &procMatrix[0][0]; /* derived name */

static float *procCosZZ = &procMatrix[2][2]; /* derived name */

static float *procSinXZ = &procMatrix[0][2]; /* derived name */

static float *procSinZX = &procMatrix[2][0]; /* derived name */

typedef struct { /* field names derived */
    float x;
    float y;
    float z;
    float r;
    char pad10[16];
    float pos[4];      /* 0x20, the cylinder's place in its node's frame */
    float float30;     /* 0x30 */
    float invDiameter; /* 0x34, 1 / (r + r), stored by InitCloth4D */
    char pad38[8];
} ClothPoint; /* derived name */

static __inline__ float fSqrtInv_i(float x) /* derived name */
{
    float r;

    __asm__ __volatile__("mfc1 $8, %1\n\t"
                         "qmtc2.ni $8, $vf4\n\t"
                         "vrsqrt Q, $vf0w, $vf4x\n\t"
                         "vwaitq\n\t"
                         "cfc2.ni $2, $vi22\n\t"
                         "mtc1 $2, %0"
                         : "=f"(r)
                         : "f"(x)
                         : "$2", "$8");
    return r;
}

static __inline__ float xzInvLength_i(const void *v) /* derived name */
{
    float r;

    __asm__ __volatile__("lqc2 $vf4, 0x0(%1)\n\t"
                         "vmul.xz $vf4, $vf4, $vf4\n\t"
                         "vaddz.x $vf4, $vf4, $vf4z\n\t"
                         "vrsqrt Q, $vf0w, $vf4x\n\t"
                         "vwaitq\n\t"
                         "cfc2.ni $2, $vi22\n\t"
                         "mtc1 $2, %0"
                         : "=f"(r)
                         : "r"(v)
                         : "$2");
    return r;
}

static __inline__ void scaleVectorXZ_i(void *d, const void *s, float k) /* derived name */
{
    __asm__ __volatile__("lqc2 $vf4, 0x0(%1)\n\t"
                         "mfc1 $8, %2\n\t"
                         "qmtc2.ni $8, $vf5\n\t"
                         "vmulx.xz $vf4, $vf4, $vf5x\n\t"
                         "sqc2 $vf4, 0x0(%0)"
                         :
                         : "r"(d), "r"(s), "f"(k)
                         : "$8");
}

static __inline__ float subAndGetInvLength_i(void *d, const void *a,
                                             const void *b) /* derived name */
{
    float inv;

    __asm__ __volatile__("lqc2 $vf1, 0x0(%1)\n\t"
                         "lqc2 $vf2, 0x0(%2)\n\t"
                         "vsub.xyzw $vf4, $vf1, $vf2\n\t"
                         "vmul.xyz $vf3, $vf4, $vf4\n\t"
                         "vaddy.x $vf3, $vf3, $vf3y\n\t"
                         "vaddz.x $vf3, $vf3, $vf3z\n\t"
                         "vrsqrt Q, $vf0w, $vf3x\n\t"
                         "sqc2 $vf4, 0x0(%3)\n\t"
                         "vwaitq\n\t"
                         "cfc2.ni $2, $vi22\n\t"
                         "mtc1 $2, %0"
                         : "=f"(inv)
                         : "r"(a), "r"(b), "r"(d)
                         : "$2");
    return inv;
}

static __inline__ void scaleAndAddVectorXYZ_i(void *d, const void *a, const void *b,
                                              float k) /* derived name */
{
    __asm__ __volatile__("lqc2 $vf4, 0x0(%1)\n\t"
                         "lqc2 $vf5, 0x0(%2)\n\t"
                         "mfc1 $8, %3\n\t"
                         "qmtc2.ni $8, $vf6\n\t"
                         "vmulx.xyz $vf5, $vf5, $vf6x\n\t"
                         "vadd.xyz $vf4, $vf4, $vf5\n\t"
                         "sqc2 $vf4, 0x0(%0)"
                         :
                         : "r"(d), "r"(a), "r"(b), "f"(k)
                         : "$8");
}

static __inline__ void tensionMove_i(void *out, const void *a, const void *b, float k,
                                     float lim) /* derived name */
{
    VECTOR buf;
    float inv = subAndGetInvLength_i(&buf, a, b);

    if (inv < lim) {
        scaleAndAddVectorXYZ_i(out, b, &buf, k * inv);
    }
}

/* the cylinder's two cap planes and squared radius, set from one collision
   point */
static __inline__ void setClipCylinder(ClothPoint *pt) /* derived name */
{
    clipPlane[0][0][3] = pt->y;
    clipPlane[1][0][3] = -pt->z;
    cylinderRadiusSq = pt->r * pt->r;
}

void getCloth4D(void *a0, int **rows)
{
    char **rowsB = (char **)((int *)a0)[2];
    char **rowsC = (char **)((int *)a0)[3];
    int *cfg = (int *)((int *)a0)[184];
    int wrap = cfg[2];
    int nx = cfg[0] - (wrap != 0);
    int ny = cfg[1];
    int cnt = ((int *)a0)[190] ? ((int *)a0)[185] : 0;
    ClothPoint *pts = (ClothPoint *)((int *)a0)[188];
    float scale = GOBJ_SUB(*(int *)a0)->nodes->scale[0];
    float inv = 1.0f / scale;
    float tbase = *(float *)&cfg[10] * scale;
    int nyArr[ny];
    int nxArr[nx];
    sceVu0FMATRIX mC[cnt];
    sceVu0FMATRIX mD[cnt];
    sceVu0FMATRIX mE[cnt];
    sceVu0FMATRIX mF[cnt];
    VECTOR vG[cnt];
    VECTOR vH[cnt];
    sceVu0FMATRIX *pD;
    sceVu0FMATRIX *pC;
    sceVu0FMATRIX *pF;
    sceVu0FMATRIX *pE;
    sceVu0FMATRIX mtx;
    VECTOR clip[3];
    /* read only by the DEBUG build's drawing of each cylinder's clip planes
       after the collision pass */
    VECTOR work[9];
    float t1;
    float tk;
    float tlim;
    int i;
    int j;
    int n;

    pD = mD;
    pC = mC;
    pF = mF;
    pE = mE;
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixZ(-0x4000);
    MatrixDrive_ScaleMatrix(inv, inv, inv);
    CopyMatrix(mtx, MatrixDrive_GetMatrix());
    for (i = 0; i < cnt; i++, pD++, pC++, pF++, pE++) {
        CopyVector(mtx[3], pts[i].pos);
        _MulMatrix(
            pD, *(char **)(*(int *)(*(int *)a0 + 0x15C) + 0xC) + ((int *)((int *)a0)[186])[i] * 64,
            mtx);
        _MulMatrix(pC, (char *)((int *)a0)[187] + i * 64, mtx);
        MatrixDrive_SetTransposeMatrix(pE, pC);
        MatrixDrive_SetTransposeMatrix(pF, pD);
        _ApplyMatrix(&vG[i], pD, clothUpVector);
        vG[i].w = -pts[i].z - _InnerProduct(&vG[i], (*pD)[3]);
        _ApplyMatrix(&vH[i], pD, clothDownVector);
        vH[i].w = pts[i].y - _InnerProduct(&vH[i], (*pD)[3]);
    }
    if (debug_cloth_info) {
        gif_StartPacketPri(11);
        gif_SetAlpha(1, 5, 0x80);
        gif_SetZWrite(0);
        gif_SetZTest(1);
        for (i = 0; i < cnt; i++) {
            CopyMatrix(MatrixDrive_GetMatrix(), mD[i]);
            prim_DispWireYCylinder(cylinderColor, 16, 0, pts[i].r, pts[i].y, pts[i].z);
        }
        gif_EndPacket();
    }
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 5, 0x80);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    {
        sceVu0FMATRIX *qF = mF;
        sceVu0FMATRIX *qE = mE;
        sceVu0FMATRIX *qD = mD;

        for (i = 0; i < nx; i++) {
            nxArr[i] = -1;
        }
        for (j = 1; j < ny; j++) {
            nyArr[j] = 0;
        }
        for (n = 0; n < cnt; n++, qF++, qE++, qD++) {
            setClipCylinder(&pts[n]);
            for (i = 0; i < nx; i++) {
                char *pb = rowsB[i] + 16;
                char *pc = rowsC[i] + 16;

                for (j = 1; j < ny; j++, pb += 16, pc += 16) {
                    _ApplyMatrix(&clip[0], qE, pc);
                    _ApplyMatrix(&clip[1], qF, pb);
                    if (clipCylinderCollision((char *)clip, &pts[n]) != -1) {
                        VECTOR tbuf;

                        scaleVectorXZ_i(&tbuf, &clip[2], pts[n].r * xzInvLength_i(&clip[2]));
                        _ApplyMatrix(pb, qD, &tbuf);
                        nyArr[j] = i;
                        nxArr[i] = j;
                        rows[i][j] = n;
                    }
                }
            }
        }
    }
    gif_EndPacket();
#ifdef DEBUG
    for (i = 0; i < cnt; i++) {
        _ScaleVector(&work[0], &vG[i], 100.0f);
        _AddVectorXYZ(&work[1], mD[i][3], &work[0]);
        _ScaleVector(&work[2], &vH[i], 100.0f);
        _AddVectorXYZ(&work[3], mD[i][3], &work[2]);
        DrawLine((char *)mD[i][3], (char *)&work[1], (LineColor *)&chainLineColor0, 0);
        DrawLine((char *)mD[i][3], (char *)&work[3], (LineColor *)&chainLineColor1, 0);
    }
#endif
    {
        /* proc reads only p, q and k.  Each caller also passes own, the
           owner of q's point that its test has just loaded. */
        int proc(VECTOR * p, VECTOR * q, VECTOR * qa, VECTOR * qb, float k, int own)
        {
            __inline__ int hit(int i) /* derived name */
            {
                VECTOR a;
                VECTOR b;
                float r2;
                float r;

                if (checkOverThePlane_i(p, &vG[i]))
                    return 0;
                if (checkOverThePlane_i(p, &vH[i]))
                    return 0;
                r = pts[i].r;
                r2 = r * r;
                if (t1 < distance_squared(p, q)) {
                    tensionMove_i(p, p, q, tk, tlim);
                    _ApplyMatrix(&a, mF[i], p);
                    if (xzLengthSquare(&a) < r2) {
                        float rr = (r + tk) * (r + tk);
                        float len;

                        _ApplyMatrix(&b, mF[i], q);
                        len = xzLengthSquare(&b);
                        if (len < rr) {
                            float d = r2 - t1;
                            float inv;
                            float e;
                            float s;
                            float ir;
                            float sy;
                            float sn;

                            inv = fSqrtInv_i(len);
                            e = (len + d) * pts[i].invDiameter * inv;
                            s = FSqrt(1.0f - e * e);
                            ir = r * inv;
                            sy = a.y;
                            *procCosXX = *procCosZZ = e * ir;
                            sn = k * pts[i].float30 * s * ir;
                            *procSinXZ = sn;
                            *procSinZX = -sn;
                            _ApplyMatrix(&a, procMatrix, &b);
                            a.y = sy;
                            _ApplyMatrix(p, mD[i], &a);
                            return 1;
                        }
                    }
                } else {
                    float len;

                    _ApplyMatrix(&a, mF[i], p);
                    len = xzLengthSquare(&a);
                    if (len < r2) {
                        VECTOR v;

                        scaleVectorXZ_i(&v, &a, r * fSqrtInv_i(len));
                        _ApplyMatrix(p, mD[i], &v);
                        return 1;
                    }
                }
                return 0;
            }
            int i;
            int ret = -1;

            for (i = 0; i < cnt; i++) {
                if (hit(i))
                    ret = i;
            }
            if (ret != -1)
                return ret;
            tensionMove_i(p, p, q, tk, tlim);
            return -1;
        }

        if (wrap) {
            if (((int *)a0)[189]) {
                for (j = 1; j < ny; j++) {
                    int s = nyArr[j];
                    tk = tbase * ((float)j * 0.2f / (float)ny + 1.0f);
                    t1 = tk * tk;
                    tlim = 1.0f / tk;
                    for (i = 1; i < nx + 2; i++) {
                        int x;
                        int y;
                        int xm;
                        int x0;
                        int xp;

                        x = s + i + nx;
                        y = s + nx * 3 - i;
                        xm = (x - 1) % nx;
                        x0 = x % nx;
                        xp = (x + 1) % nx;
                        if (rows[xm][j] != -1 || rows[x0][j] == -1) {
                            rows[x0][j] =
                                proc((VECTOR *)(rowsB[x0] + j * 16), (VECTOR *)(rowsB[xm] + j * 16),
                                     (VECTOR *)(rowsB[xp] + j * 16),
                                     (VECTOR *)(rowsB[x0] + (j * 16 - 16)), -1.0f, rows[xm][j]);
                        }
                        xm = (y + 1) % nx;
                        x0 = y % nx;
                        xp = (y - 1) % nx;
                        if (rows[xm][j] != -1 || rows[x0][j] == -1) {
                            rows[x0][j] =
                                proc((VECTOR *)(rowsB[x0] + j * 16), (VECTOR *)(rowsB[xm] + j * 16),
                                     (VECTOR *)(rowsB[xp] + j * 16),
                                     (VECTOR *)(rowsB[x0] + (j * 16 - 16)), 1.0f, rows[xm][j]);
                        }
                    }
                }
            } else {
                for (j = 1; j < ny; j++) {
                    int s = nyArr[j];
                    tk = tbase * ((float)j * 0.2f / (float)ny + 1.0f);
                    t1 = tk * tk;
                    tlim = 1.0f / tk;
                    for (i = 1; i < nx + 2; i++) {
                        int x;
                        int y;
                        int ym;
                        int y0;
                        int yp;

                        x = s + i + nx;
                        y = s + nx * 3 - i;
                        yp = (y + 1) % nx;
                        y0 = y % nx;
                        ym = (y - 1) % nx;
                        if (rows[yp][j] != -1 || rows[y0][j] == -1) {
                            rows[y0][j] =
                                proc((VECTOR *)(rowsB[y0] + j * 16), (VECTOR *)(rowsB[yp] + j * 16),
                                     (VECTOR *)(rowsB[ym] + j * 16),
                                     (VECTOR *)(rowsB[y0] + (j * 16 - 16)), 1.0f, rows[yp][j]);
                        }
                        yp = (x - 1) % nx;
                        y0 = x % nx;
                        ym = (x + 1) % nx;
                        if (rows[yp][j] != -1 || rows[y0][j] == -1) {
                            rows[y0][j] =
                                proc((VECTOR *)(rowsB[y0] + j * 16), (VECTOR *)(rowsB[yp] + j * 16),
                                     (VECTOR *)(rowsB[ym] + j * 16),
                                     (VECTOR *)(rowsB[y0] + (j * 16 - 16)), -1.0f, rows[yp][j]);
                        }
                    }
                }
            }
        } else {
            tk = tbase;
            t1 = tbase * tbase;
            tlim = 1.0f / tbase;
            if (((int *)a0)[189]) {
                for (j = 1; j < ny; j++) {
                    for (i = 1; i < nx; i++) {
                        int x;
                        int y;
                        int ym;
                        int y0;
                        int yp;

                        x = i;
                        y = nx - 1 - i;
                        yp = y + 1;
                        y0 = y;
                        ym = y - 1;
                        if (rows[yp][j] != -1 || rows[y0][j] == -1) {
                            rows[y0][j] =
                                proc((VECTOR *)(rowsB[y0] + j * 16), (VECTOR *)(rowsB[yp] + j * 16),
                                     (VECTOR *)(rowsB[ym] + j * 16),
                                     (VECTOR *)(rowsB[y0] + (j * 16 - 16)), 1.0f, rows[yp][j]);
                        }
                        yp = x - 1;
                        y0 = x;
                        ym = x + 1;
                        if (rows[yp][j] != -1 || rows[y0][j] == -1) {
                            rows[y0][j] =
                                proc((VECTOR *)(rowsB[y0] + j * 16), (VECTOR *)(rowsB[yp] + j * 16),
                                     (VECTOR *)(rowsB[ym] + j * 16),
                                     (VECTOR *)(rowsB[y0] + (j * 16 - 16)), -1.0f, rows[yp][j]);
                        }
                    }
                }
            } else {
                for (j = 1; j < ny; j++) {
                    for (i = 1; i < nx; i++) {
                        int x;
                        int y;
                        int xm;
                        int x0;
                        int xp;

                        x = i;
                        y = nx - 1 - i;
                        xm = x - 1;
                        x0 = x;
                        xp = x + 1;
                        if (rows[xm][j] != -1 || rows[x0][j] == -1) {
                            rows[x0][j] =
                                proc((VECTOR *)(rowsB[x0] + j * 16), (VECTOR *)(rowsB[xm] + j * 16),
                                     (VECTOR *)(rowsB[xp] + j * 16),
                                     (VECTOR *)(rowsB[x0] + (j * 16 - 16)), -1.0f, rows[xm][j]);
                        }
                        xm = y + 1;
                        x0 = y;
                        xp = y - 1;
                        if (rows[xm][j] != -1 || rows[x0][j] == -1) {
                            rows[x0][j] =
                                proc((VECTOR *)(rowsB[x0] + j * 16), (VECTOR *)(rowsB[xm] + j * 16),
                                     (VECTOR *)(rowsB[xp] + j * 16),
                                     (VECTOR *)(rowsB[x0] + (j * 16 - 16)), 1.0f, rows[xm][j]);
                        }
                    }
                }
            }
        }
        for (i = 0; i < nx; i++) {
            float len = ((Cloth4DCol *)cfg[9])[i].length * scale;
            float linv = 1.0f / len;
            int last = nxArr[i];

            for (j = 1; j < ny; j++) {
                tensionMove_i(rowsB[i] + j * 16, rowsB[i] + j * 16, rowsB[i] + j * 16 - 16, len,
                              linv);
            }
            if (last < 0) {
                for (j = ny - 2; j > 0; j--) {
                    tensionMove_i(rowsB[i] + j * 16, rowsB[i] + j * 16, rowsB[i] + j * 16 + 16, len,
                                  linv);
                }
            } else {
                for (j = last - 1; j > 0; j--) {
                    tensionMove_i(rowsB[i] + j * 16, rowsB[i] + j * 16, rowsB[i] + j * 16 + 16, len,
                                  linv);
                }
            }
        }
    }
}

void getCloth4D_postProcess(int *a0, int **a1)
{
    float buf[4];
    int i;
    int j;
    int *rowsB = (int *)a0[2];
    int *rowsD = (int *)a0[4];
    int *m = (int *)a0[184];
    int *rowsC = (int *)a0[3];
    int ny = m[1];
    int nx = m[0] - (m[2] != 0);

    for (i = 0; i < nx; i++) {
        for (j = 1; j < ny; j++) {
            if (a1[i][j] == -1) {
                SubVectorXYZ((char *)rowsC[i] + j * 16, (char *)rowsB[i] + j * 16,
                             (char *)rowsC[i] + j * 16);
            } else {
                CopyVector((char *)rowsC[i] + j * 16, ZeroVector);
            }
        }
    }
    if (m[2] != 0) {
        memset(buf, 0, 0x10);
        for (j = 0; j < ny; j++) {
            sceVu0AddVector((char *)rowsB[nx] + j * 16, (char *)rowsB[0] + j * 16, buf);
        }
        CopyVector((void *)rowsD[nx], (void *)rowsD[0]);
    }
    for (i = 0; i < m[0]; i++) {
        for (j = 1; j < ny; j++) {
            CopyVector((char *)rowsD[i] + j * 16, (void *)rowsD[i]);
        }
    }
    for (i = 0; i < a0[185]; i++) {
        CopyMatrix((char *)a0[187] + i * 64,
                   (char *)*(int *)(*(int *)((char *)a0[0] + 0x15C) + 0xC) +
                       ((int *)a0[186])[i] * 64);
    }
}

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

void _getCloth4D(int *a0, float x, float y, float z, float w, int tight, void *a6, void *a7)
{
    float buf[4];
    int i;
    int j;
    int i2;
    int j2;
    int ny = ((int *)a0[184])[1];
    int nx = ((int *)a0[184])[0];
    int data[nx][ny];
    int *rows[nx];
    int *obj;
    int *m;
    int *rowsB;
    int nx2;
    int ny2;
    char *plane;

    for (i = 0; i < nx; i++) {
        rows[i] = data[i];
        for (j = 0; j < ny; j++) {
            rows[i][j] = -1;
        }
    }
    getCloth4D_preProcess(a0, x, y, z, w, tight, a6, a7);
    getCloth4D(a0, rows);
    obj = (int *)*(int *)((char *)a0[0] + 0x15C);
    if (motionKind[obj[296]].flags.bits.clothPlane) {
        plane = (char *)obj + 0x1D0;
        m = (int *)a0[184];
        rowsB = (int *)a0[2];
        nx2 = m[0] - (m[2] != 0);
        ny2 = m[1];
        for (i2 = 0; i2 < nx2; i2++) {
            for (j2 = 1; j2 < ny2; j2++) {
                char *p = (char *)(j2 * 16 + rowsB[i2]);
                float d = plane_distance(p, plane);
                if (d < 0.0f) {
                    _ScaleVector(buf, plane, d);
                    _SubVectorXYZ(p, p, buf);
                }
            }
        }
    }
    getCloth4D_postProcess(a0, rows);
}

void GetCloth4D(void *a0, float x, float y)
{
    _getCloth4D(a0, x, y, 1.0f, 1.0f, 0, IdentityQuaternion, IdentityQuaternion);
}

void GetCloth4DWithDetail(void *a0, float x, float y, float z, float w)
{
    _getCloth4D(a0, x, y, z, w, 0, IdentityQuaternion, IdentityQuaternion);
}

/* the two pointers follow the four floats, like _getCloth4D's own tail */
void GetCloth4DWithTight(void *a0, float x, float y, float z, float w, void *a1, void *a2)
{
    _getCloth4D(a0, x, y, z, w, 1, a1, a2);
}

typedef struct { /* field names derived */
    long long q[8];
} Blob64; /* derived name */

typedef struct { /* field names derived */
    int nx;
    int ny;
    int word08; /* 0x08 */
    int word0C; /* 0x0C */
    int r;      /* 0x10, the colour prim_InitMesh3D is given */
    int g;      /* 0x14 */
    int b;      /* 0x18 */
    int a;      /* 0x1C */
    void *tex;
    char *cols;
} Cloth4DCfg; /* derived name */

Cloth4D *InitCloth4D(GObj *a0, Cloth4DCfg *cfg, int tbl)
{
    Cloth4D *r;
    int i;
    int j;
    float sc;

    r = (Cloth4D *)iosMallocDebug(ios_partition_sugipon, 0x300, "src/clothAnimation.c", 2183);
    r->gobj = a0;
    r->cfg = (int)cfg;
    r->word2F4 = 0;
    if (cfg->tex != 0) {
        r->mesh = prim_InitMesh3D(cfg->ny, cfg->nx, 1, 0x5C, 0x80808080, 1);
        r->tex = *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(cfg->tex));
    } else {
        r->mesh = prim_InitMesh3D(cfg->ny, cfg->nx, 1, 0x4C, 0xFFFFFF80, 1);
    }
    r->pos = (Prim3DVec **)iosMallocDebug(ios_partition_sugipon, cfg->nx * 4,
                                          "src/clothAnimation.c", 2218);
    r->vel = (Prim3DVec **)iosMallocDebug(ios_partition_sugipon, cfg->nx * 4,
                                          "src/clothAnimation.c", 2219);
    r->nrm = (Prim3DVec **)iosMallocDebug(ios_partition_sugipon, cfg->nx * 4,
                                          "src/clothAnimation.c", 2220);
    for (i = 0; i < cfg->nx; i++) {
        r->pos[i] = r->mesh->pos + i * cfg->ny;
        r->vel[i] = (Prim3DVec *)iosMallocDebug(ios_partition_sugipon, cfg->ny * 16,
                                                "src/clothAnimation.c", 2224);
        r->nrm[i] = r->mesh->nrm + i * cfg->ny;
        for (j = 0; j < cfg->ny; j++) {
            CopyVector(&r->pos[i][j], ZeroPoint);
            CopyVector(&r->vel[i][j], ZeroVector);
            r->mesh->st[i * cfg->ny + j].x =
                *(float *)(j * 8 + *(int *)(i * 0x60 + (int)cfg->cols + 0x40));
            r->mesh->st[i * cfg->ny + j].y =
                1.0f - *(float *)(j * 8 + *(int *)(i * 0x60 + (int)cfg->cols + 0x40) + 4);
        }
    }
    prim_UpdateMesh3D(r->mesh, 8, buffer_ID);
    prim_UpdateMesh3D(r->mesh, 8, (buffer_ID + 1) & 1);
    if (tbl != 0) {
        i = 0;
        sc = GOBJ_SUB(r->gobj)->nodes->scale[0];
        while (*(int *)(i * 0x40 + tbl) != -1) {
            i++;
        }
        r->colNum = i;
        r->col = iosMallocDebug(ios_partition_sugipon, i * 0x40, "src/clothAnimation.c", 2253);
        r->colMtx =
            iosMallocDebug(ios_partition_sugipon, r->colNum * 0x40, "src/clothAnimation.c", 2254);
        r->colNode = (char **)iosMallocDebug(ios_partition_sugipon, r->colNum * 4,
                                             "src/clothAnimation.c", 2255);
        for (i = 0; *(int *)(i * 0x40 + tbl) != -1; i++) {
            *(Blob64 *)(i * 0x40 + (int)r->col) = *(Blob64 *)(i * 0x40 + tbl);
            *(float *)(i * 0x40 + (int)r->col + 0xC) =
                *(float *)(i * 0x40 + (int)r->col + 0xC) * sc;
            *(float *)(i * 0x40 + (int)r->col + 8) = *(float *)(i * 0x40 + (int)r->col + 8) * sc;
            *(float *)(i * 0x40 + (int)r->col + 4) = *(float *)(i * 0x40 + (int)r->col + 4) * sc;
            *(float *)(i * 0x40 + (int)r->col + 0x34) =
                1.0f / (*(float *)(i * 0x40 + (int)r->col + 0xC) +
                        *(float *)(i * 0x40 + (int)r->col + 0xC));
            sceVu0UnitMatrix(r->colMtx + i * 0x40);
            *(int *)(i * 4 + (int)r->colNode) =
                GetSkeltonFocusNode(a0, *(int *)(i * 0x40 + tbl + 0x10));
        }
        r->collision = 1;
    } else {
        r->colNum = 0;
        r->collision = 0;
    }
    return r;
}

void GetChainNodeGlobalQuaternion(void *a0, int *a1, int count)
{
    ClothBuf buf;
    SetIdentityQuaternion(a0);
    if (count > 0) {
        char *base = *(char **)a1;
        int off = count * 16;
        SubVectorXYZ(&buf, base + off, base + (off - 16));
        MatrixDrive_GetTurnYAngleXZ(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
        RotQuaternionX(a0, (short)-buf.a);
        RotQuaternionZ(a0, (short)-buf.b);
    }
}

void MoveChainExtendedWeight(int a0, int a1, float f)
{
    *(float *)(a0 + a1 * 0x50 + 0x10) = f;
}

void InitChainVelocity(int *a0)
{
    int i;
    int j;
    int k;

    for (i = 0; i < a0[1]; i++) {
        int cnt = *(int *)((char *)a0[0] + i * 0x50);
        for (j = 0; j < cnt; j++) {
            CopyVector(*(char **)((char *)a0[2] + i * 0x1A0 + 4) + j * 16, ZeroVector);
        }
        for (k = 0; k < 5; k++) {
            char *w = (char *)a0[2] + i * 0x1A0 + 0x10 + k * 0x50;
            CopyVector(w + 0x30, ZeroVector);
        }
    }
}

void DeleteChainExtendedWeight(int *a0, int a1)
{
    int *p = (int *)((char *)a0 + a1 * 0x50);
    *(float *)((char *)p + 0x10) = -1.0f;
    a0[3] = a0[3] - 1;
}

float GetChainNodeID(int a0, float f)
{
    return f / *(float *)(a0 + 0x14);
}

void ResetClothAnimation(int *a0, int *a1, int *a2)
{
    int outer = a2[0];
    int inner = a2[2];
    int i = 0;
    int j;

    if (outer > 0) {
        do {
            for (j = 1; j < inner; j++) {
                char *p = (char *)a0[i];
                CopyVector(p + j * 16, p);
                CopyVector((char *)a1[i] + j * 16, ZeroVector);
            }
            i++;
        } while (i < outer);
    }
}

void GetChainExWeightGlobalQuaternion(float *q, int nodes, int i, int j)
{
    ClothBuf buf;
    SetIdentityQuaternion(q);
    SubVectorXYZ(&buf, j * 0x50 + nodes + 0x30, i * 0x50 + nodes + 0x20);
    buf.v[1] = buf.v[1] + 100.0f;
    MatrixDrive_GetTurnYAngleXZ(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
    RotQuaternionX(q, (short)-buf.a);
    RotQuaternionZ(q, (short)-buf.b);
}

float GetChainCollision(int *a0, void *pos, float r)
{
    int i;
    int j;

    r = r * r;
    for (i = 0; i < a0[1]; i++) {
        char *pts = *(char **)(i * 0x1A0 + a0[2]);
        for (j = 0; j < *(int *)(i * 0x50 + a0[0]) - 1; j++) {
            if (distance_squared(pts + j * 16, pos) < r) {
                return (float)j * *(float *)(i * 0x50 + a0[0] + 0x14);
            }
        }
    }
    return -1.0f;
}

void FSqrtInv(void)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 4);
    VU0_NOREORDER_END();
    VU0_REG("vrsqrt Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(2, 22);
    VU0_MTC1(2, 0);
    VU0_NOREORDER_END();
}

float getXZLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, 4);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(2, 22);
    VU0_MTC1(2, 0);
    VU0_NOREORDER_END();
}

float getXZInvLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, 4);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(2, 22);
    VU0_MTC1(2, 0);
    VU0_NOREORDER_END();
}

float getXZLengthSquare(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, 4);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_QMFC2_NI(2, 4);
    VU0_MTC1(2, 0);
}

float subAndGetInvLength(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 4, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, 4);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(2, 22);
    VU0_MTC1(2, 0);
    VU0_NOREORDER_END();
}

void scaleAndAddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 6);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 5, 5, 6, x);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void scaleVectorXZ(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void tensionMoveNoReduce(void *a0, void *a1, void *a2, float f12)
{
    int buf[4];
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    __asm__ __volatile__(".set noreorder\n\tsqc2 $vf4, %0\n\t.set reorder"
                         : "=m"(buf)
                         :
                         : "memory");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(2, 22);
    VU0_MTC1(2, 0);
    VU0_REG("mul.s $f12, $f12, $f0");
    VU0_NOREORDER_END();

    VU0_LSV(lqc2, 4, 0x0, 6);
    __asm__ __volatile__(".set noreorder\n\tlqc2 $vf5, %0\n\t.set reorder"
                         :
                         : "m"(buf[0])
                         : "memory");
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 6);
    VU0_NOREORDER_END();
    VU0_REG("vmulx.xyz $vf5, $vf5, $vf6x");
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void tensionMove(void *a0, void *a1, void *a2, float f12, float f13)
{
    int buf[4];
    float inv;
    float scale;
    VU0_LSV(lqc2, 1, 0x0, 5);
    VU0_LSV(lqc2, 2, 0x0, 6);
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    __asm__ __volatile__(".set noreorder\n\tsqc2 $vf4, %0\n\t.set reorder"
                         : "=m"(buf)
                         :
                         : "memory");
    VU0_WAIT();
    __asm__ __volatile__(".set noreorder\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         ".set reorder\n"
                         : "=f"(inv)::"$2");
    if (inv < f13) {
        scale = f12 * inv;
        VU0_LSV(lqc2, 4, 0x0, 6);
        __asm__ __volatile__(".set noreorder\n\tlqc2 $vf5, %0\n\t.set reorder"
                             :
                             : "m"(buf[0])
                             : "memory");
        __asm__ __volatile__(".set noreorder\n"
                             "mfc1 $8, %0\n"
                             "qmtc2.ni $8, $vf6\n"
                             ".set reorder\n" ::"f"(scale)
                             : "$8");
        VU0_REG("vmulx.xyz $vf5, $vf5, $vf6x");
        VU0_V3OP(vadd.xyz, 4, 4, 5);
        VU0_LSV(sqc2, 4, 0x0, 4);
    }
}

void getCrossPoint(void *out, void *seg, void *plane)
{
    getCrossPoint_i(out, seg, plane);
}

int checkOverThePlane(void *a0, void *a1)
{
    return checkOverThePlane_i(a0, a1);
}

int checkFrontAcross(void *a0, void *a1)
{
    if (0.0f <= plane_distance(a0, a1)) {
        if (plane_distance((char *)a0 + 0x10, a1) < 0.0f)
            return 1;
    }
    return 0;
}

void LockZAnimation(int *a0)
{
    int i;
    int j;
    int n = a0[1];

    for (i = 0; i < n; i++) {
        int cnt = *(int *)((char *)a0[0] + i * 0x50);
        for (j = 0; j < cnt; j++) {
            *(float *)(*(int *)((char *)a0[2] + i * 0x1A0 + 4) + j * 16 + 8) = 0.0f;
        }
    }
}

void getCloth4D_planeClip(int *a0, void *plane)
{
    float buf[4];
    int i;
    int j;
    int *m = (int *)a0[184];
    int *rows = (int *)a0[2];
    int nx = m[0] - (m[2] != 0);
    int ny = m[1];

    for (i = 0; i < nx; i++) {
        for (j = 1; j < ny; j++) {
            char *p = (char *)(j * 16 + rows[i]);
            float d = plane_distance(p, plane);
            if (d < 0.0f) {
                _ScaleVector(buf, plane, d);
                _SubVectorXYZ(p, p, buf);
            }
        }
    }
}
