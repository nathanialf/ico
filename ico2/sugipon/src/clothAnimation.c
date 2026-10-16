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
#include "clothAnimation.h"
#include "include_asm.h"

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

void TestDispChainAnimation(ChainSet *sys)
{
    LineColor c0 = chainLineColor0;
    LineColor c1 = chainLineColor1;
    VECTOR mid;
    int i;
    int j;

    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < sys->num; i++) {
        int n = sys->cfg[i].num;
        float (*pts)[4] = sys->nodes[i].pos;
        for (j = 1; j < n; j++) {
            float *p = pts[j];
            float *q = pts[j - 1];
            LineColor *col = (j & 1) ? &c1 : &c0;
            sceVu0AddVector(&mid, p, q);
            DrawLine(p, q, col, 0);
        }
        for (j = 0; j < 5; j++) {
            char *base = (char *)&sys->nodes[i];
            char *w = base + j * 0x50;
            if (0.0f <= *(float *)(w + 0x10)) {
                DrawLine(base + 0x30, base + 0x80, &c0, 0);
            }
        }
    }
    gif_EndPacket();
}

void GetChainExWeightGlobalPos(float *pos, ChainNode *node, int idx)
{
    CopyVector(pos, &node->ex[idx].v1);
}

/* the chain's red debug segment, built only when DEBUG is defined */
static __inline__ void chainDebugOld(VECTOR *old) /* derived name */
{
#ifdef DEBUG
    DrawLine((char *)old[0], (char *)old[1], (LineColor *)&chainLineColor1, 0);
#endif
}

void GetChainAnimation(ChainSet *sys, GObj *obj, float (*mtx)[4])
{
    VECTOR dv;
    VECTOR tv;
    float mm[4][4];
    VECTOR ew[5];
    float (*pm)[4];
    int i;

    pm = mm;
    sceVu0UnitMatrix(pm);
    for (i = 0; i < sys->num; i++) {
        ChainCfg *cf = (ChainCfg *)(i * 0x50 + (int)sys->cfg);
        int n = cf->num;
        float (*pts)[4] = (sys->nodes + i)->pos;
        float (*vel)[4] = (sys->nodes + i)->vel;
        ChainParam *cp = &cf->pm;
        int no;
        int j;
        int k;
        VECTOR old[n];

        if (mtx != 0 && obj != 0 && cf->pm.node != -1) {
            no = GetSkeltonFocusNode(obj, cf->pm.node);
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
                DrawLine(pts[k], pts[j], (LineColor *)&chainLineColor1, 0);
            }
#endif
            k = j;
        }

        for (j = 0; j < n; j++) {
            CopyVector(&dv, pts[j]);
            vel[j][1] += 60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) * 0.5f *
                         (60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]));
            AddVectorXYZ(pts[j], pts[j], vel[j]);
            CopyVector(&old[j], pts[j]);
            sceVu0ScaleVector(vel[j], &dv, -1.0f);
        }

        for (k = 0; k < 5; k++) {
            if (0.0f <= (sys->nodes + i)->ex[k].w) {
                CopyVector(&dv, &(sys->nodes + i)->ex[k].v1);
                (sys->nodes + i)->ex[k].v2.y +=
                    60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) * 0.5f *
                    (60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]));
                CopyVector(&ew[k], &(sys->nodes + i)->ex[k].v2);
                AddVectorXYZ(&(sys->nodes + i)->ex[k].v1, &(sys->nodes + i)->ex[k].v1,
                             &(sys->nodes + i)->ex[k].v2);
                sceVu0ScaleVector(&(sys->nodes + i)->ex[k].v2, &dv, -1.0f);
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
                cl = sys->cfg[i].pm.weight;

                wa = cl;
                wb = *(float *)(ex + 0x44);

                sceVu0InterVector(&vb, pts[id], pts[id1],
                                  1.0f - (*(float *)ex - (float)(int)*(float *)ex));

                sceVu0SubVector(&dv, &vb, ex + 0x20);
                l = VectorLengthSquare(&dv);
                if (ll < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, *(float *)(ex + 0x40) / _Sqrt(l));
                    AddVectorXYZ(ex + 0x10, ex + 0x20, &dv);

                    SubVectorXYZ(&dv, ex + 0x10, pts[id]);
                    l = VectorLengthSquare(&dv);
                    if (ka2 < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                        AddVectorXYZ(&dv, pts[id], &dv);
                    } else {
                        CopyVector(&dv, ex + 0x10);
                        wa = wb;
                    }

                    SubVectorXYZ(&va, ex + 0x10, pts[id1]);
                    l = VectorLengthSquare(&va);
                    if (kb2 < l) {
                        sceVu0ScaleVectorXYZ(&va, &va, kb / _Sqrt(l));
                        AddVectorXYZ(&va, pts[id1], &va);
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

                    SubVectorXYZ(&dv, pts[id], ex + 0x10);
                    l = VectorLengthSquare(&dv);
                    if (ka2 < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                        AddVectorXYZ(pts[id], ex + 0x10, &dv);
                    }

                    SubVectorXYZ(&dv, pts[id1], ex + 0x10);
                    l = VectorLengthSquare(&dv);
                    if (kb2 < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, kb / _Sqrt(l));
                        AddVectorXYZ(pts[id1], ex + 0x10, &dv);
                    }

                    sceVu0SubVector(&dv, ex + 0x20, ex + 0x10);
                    l = VectorLengthSquare(&dv);
                    if (ll < l) {
                        sceVu0ScaleVectorXYZ(&dv, &dv, *(float *)(ex + 0x40) / _Sqrt(l));
                        sceVu0AddVector(ex + 0x20, ex + 0x10, &dv);
                    }
                }
                sceVu0InterVector(ex + 0x10, pts[id], pts[id1],
                                  1.0f - (*(float *)ex - (float)(int)*(float *)ex));
            }

            void bind2(float (*pp)[4], int id, int ip, int in, float t)
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
                cl = sys->cfg[i].pm.weight;

                wa = cl;
                wb = cl;

                SubVectorXYZ(&dv, pp[id], pp[ip]);
                l = VectorLengthSquare(&dv);
                if (ka2 < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                    AddVectorXYZ(&dv, pp[ip], &dv);
                } else {
                    CopyVector(&dv, pp[id]);
                    cl = wb;
                }

                SubVectorXYZ(&tv, pp[id], pp[in]);
                l = VectorLengthSquare(&tv);
                if (kb2 < l) {
                    sceVu0ScaleVectorXYZ(&tv, &tv, kb / _Sqrt(l));
                    AddVectorXYZ(&tv, pp[in], &tv);
                } else {
                    CopyVector(&tv, pp[id]);
                    cl = wb;
                }

                sceVu0ScaleVector(&dv, &dv, wa / (cl + wa));
                sceVu0ScaleVector(&tv, &tv, cl / (cl + wa));
                AddVectorXYZ(&dv, &dv, &tv);

                SubVectorXYZ(&dv, &dv, pp[id]);
                sceVu0ScaleVector(&dv, &dv, 1.0f - wb / (cl + wa + wb));
                AddVectorXYZ(pp[id], pp[id], &dv);

                SubVectorXYZ(&dv, pp[ip], pp[id]);
                l = VectorLengthSquare(&dv);
                if (ka < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, ka / _Sqrt(l));
                }
                AddVectorXYZ(pp[ip], pp[id], &dv);

                SubVectorXYZ(&dv, pp[in], pp[id]);
                l = VectorLengthSquare(&dv);
                if (kb < l) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, kb / _Sqrt(l));
                }
                AddVectorXYZ(pp[in], pp[id], &dv);
            }

            void calc2(float (*pp)[4], int lo, int hi)
            {
                int m;
                int q;

                sceVu0ApplyMatrix(pts, mtx + no * 4, cp->root);
                for (m = 0; m < 5; m++) {
                    if (0.0f <= (sys->nodes + i)->ex[m].w) {
                        bindExWeight((char *)&(sys->nodes + i)->ex[m], &ew[m], cp->step);
                    }
                }
                for (m = 0; m < n; m++) {
                    int mp = m + 1;
                    q = n - mp;
                    bind2(pp, m, m - 1 < 0 ? 0 : m - 1, mp < n ? mp : n - 1, cp->step);
                    bind2(pp, q, q - 1 < 0 ? 0 : q - 1, q + 1 < n ? q + 1 : n - 1, cp->step);
                }
                chainDebugOld(old);
                sceVu0ApplyMatrix(pts, mtx + no * 4, cp->root);
            }

            /* the debug pass pad 2's button 0x20 runs: every segment pulled
               back to the chain's step length */
            inline void keepLength(float (*pp)[4]) /* derived name */
            {
                float len = cp->step;
                float len2 = len * len;
                float l;
                int m;

                for (m = 1; m < n; m++) {
                    SubVectorXYZ(&old[m], pp[m], pp[m - 1]);
                    l = VectorLengthSquare(&old[m]);
                    if (len2 < l) {
                        sceVu0ScaleVectorXYZ(&old[m], &old[m], len / _Sqrt(l));
                    }
                }
                for (m = 1; m < n; m++) {
                    AddVectorXYZ(pp[m], pp[m - 1], &old[m]);
                }
            }

            calc2(pts, 0, n - 1);
            calc2(pts, 0, n - 1);
            calc2(pts, 0, n - 1);
            calc2(pts, 0, n - 1);

            sceVu0ApplyMatrix(pts, mtx + no * 4, cp->root);

            if (pad[1].now & 0x20) {
                keepLength(pts);
            }

            sceVu0ApplyMatrix(pts, mtx + no * 4, cp->root);
        }

        for (j = 0; j < n; j++) {
            AddVectorXYZ(vel[j], vel[j], pts[j]);
            vel[j][3] = 0.0f;
        }

        for (k = 0; k < 5; k++) {
            if (0.0f <= (sys->nodes + i)->ex[k].w) {
                AddVectorXYZ(&(sys->nodes + i)->ex[k].v2, &(sys->nodes + i)->ex[k].v2,
                             &(sys->nodes + i)->ex[k].v1);
            }
        }
    }
    sys->oddFrame = sys->oddFrame == 0;
}

int SetChainExtendedWeight(ChainNode *node, int idx, float w0, float w1)
{
    int i;
    ExW *ex;

    if (node->exNum >= 5) {
        debug_StdPrintfDummy("No more weights... \n");
        return -1;
    }
    for (i = 0; i < 5; i++) {
        if (node->ex[i].w < 0.0f) {
            node->ex[i].w = (float)idx - 1e-6f;
            node->ex[i].len0 = w0;
            node->ex[i].len1 = w1;
            ex = &node->ex[i];
            CopyVector(&ex->v2, ZeroVector);
            CopyVector(&ex->v0, node->pos[idx]);
            CopyVector(&ex->v1, node->pos[idx]);
            node->ex[i].v1.y = node->ex[i].v1.y + w0;
            node->exNum = node->exNum + 1;
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

/* The sixth parameter is the wall count, which the function recomputes from
   the wall owner before any use, so the value passed in is never read.  The
   wall owner is an object handle passed as an int, the form the wall-plane
   query GetGlobalWallPlane takes (fieldCollision.h). */
void GetClothAnimation(VECTOR **pos, VECTOR **vel, GObj *obj, void *m, ClothCfg *cfg, int nwall,
                       int wallOwner, int fixEnd)
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
    char **rowsB = (char **)vel;
    int n0 = cfg->num;
    float seg = cfg->segLength;
    int nx = cfg->div - (fixEnd != 0);
    float rnx = 1.0f / (float)nx;
    char *pts = (char *)cfg->anchors;
    int wrap = cfg->wrap;

    focus = 0;
    if (wallOwner != 0) {
        nwall = *(int *)(GOBJ_SUB(wallOwner)->colData + 8);
    } else {
        nwall = 0;
    }
    if (obj != 0) {
        focus = GOBJ_SUB(obj)->skel;
    }
    for (i = 0; i < n0; i++) {
        float damp = 0.8f;

        for (j = 1; j < nx; j++) {
            sceVu0ScaleVector(&dv, rowsB[i] + j * 16, damp);
            damp = damp * 0.98f;
            sceVu0ScaleVector(rowsB[i] + j * 16, ((char **)pos)[i] + j * 16, -1.0f);
            AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[i] + j * 16, &dv);
        }
    }
    for (i = 0; i < n0; i++) {
        if (focus != 0) {
            node = GetSkeltonFocusNode(obj, *(int *)(pts + i * 48));
            sceVu0ApplyMatrix(((char **)pos)[i], (char *)GOBJ_SUB(obj)->nodeMtx + node * 64,
                              pts + i * 48 + 16);
        } else {
            if (m != 0) {
                _ApplyMatrix(((char **)pos)[i], m, pts + i * 48 + 16);
                if (fixEnd != 0) {
                    _ApplyMatrix(((char **)pos)[i] + nx * 16, m, pts + i * 48 + 32);
                }
            }
        }
        for (j = 1; j < nx; j++) {
            char *p = ((char **)pos)[i] + j * 16;
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
            SubVectorXYZ(&dv, ((char **)pos)[i] + j * 16, ((char **)pos)[i - 1] + j * 16);
            len = VectorLengthSquare(&dv);
            if (lim < len) {
                sceVu0ScaleVectorXYZ(&dv, &dv, t * seg / _Sqrt(len));
                AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[i - 1] + j * 16, &dv);
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
                SubVectorXYZ(&dv, ((char **)pos)[i] + j * 16, ((char **)pos)[q] + j * 16);
                len = VectorLengthSquare(&dv);
                if (lim < len) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, t * seg / _Sqrt(len));
                    AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[q] + j * 16, &dv);
                }
            }
        }
    }
    if (fixEnd == 0) {
        for (i = 0; i < n0; i++) {
            float len = *(float *)(pts + i * 48 + 4);
            float lim = len * len;

            for (j = 1; j < nx; j++) {
                SubVectorXYZ(&dv, ((char **)pos)[i] + j * 16, ((char **)pos)[i] + (j * 16 - 16));
                d2 = VectorLengthSquare(&dv);
                if (lim < d2) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, len / _Sqrt(d2));
                    AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[i] + (j * 16 - 16),
                                 &dv);
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
                SubVectorXYZ(&dv, ((char **)pos)[i] + j * 16, ((char **)pos)[i] + (j * 16 + 16));
                d2 = VectorLengthSquare(&dv);
                if (lim < d2) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, len / _Sqrt(d2));
                    AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[i] + (j * 16 + 16),
                                 &dv);
                }
            }
            for (j = 1; j < nx; j++) {
                SubVectorXYZ(&dv, ((char **)pos)[i] + j * 16, ((char **)pos)[i] + (j * 16 - 16));
                d2 = VectorLengthSquare(&dv);
                if (lim < d2) {
                    sceVu0ScaleVectorXYZ(&dv, &dv, len / _Sqrt(d2));
                    AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[i] + (j * 16 - 16),
                                 &dv);
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

                _SubVector(&va, ((char **)pos)[i] + nx * 16, ((char **)pos)[i]);
                total = VectorLength(&va);
                rtotal = 1.0f / total;
                for (j = 1; j < nx; j++) {
                    float l0;
                    float l1;

                    _SubVector(&vb, ((char **)pos)[i] + j * 16, ((char **)pos)[i]);
                    _SubVector(&vc, ((char **)pos)[i] + j * 16, ((char **)pos)[i] + nx * 16);
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
                        _AddVectorXYZ(((char **)pos)[i] + j * 16, ((char **)pos)[i], &vb);
                    }
                }
#ifdef DEBUG
                _ScaleVector(&ve, &va, 0.5f);
                _AddVectorXYZ(&vf, ((char **)pos)[i], &ve);
                _AddVectorXYZ(&vg, ((char **)pos)[i], &va);
                DrawLine(((char **)pos)[i], (char *)&vf, (LineColor *)&chainLineColor0, 0);
                DrawLine((char *)&vf, (char *)&vg, (LineColor *)&chainLineColor1, 0);
#endif
            }
        }
    }
    for (n = 0; n < nwall; n++) {
        /* the wall owner's sub-record, then the query for its n-th wall
           plane */
        int sub = *(int *)(wallOwner + 0x15C),
            q[3] = {wallOwner, 0, *(int *)(*(int *)(sub + 0x70) + 0x10) + n * 80};
        VECTOR pl;

        GetGlobalWallPlane(&pl.x, q);
        for (i = 0; i < n0; i++) {
            for (j = 1; j < nx; j++) {
                pushInsidePlane(((char **)pos)[i] + j * 16, &pl);
            }
        }
    }
    wind = GetWindVector(&pw, ((char **)pos)[0]);
    pw = pw / 40960.0f;
    for (i = 0; i < n0; i++) {
        for (j = 1; j < nx; j++) {
            AddVectorXYZ(rowsB[i] + j * 16, rowsB[i] + j * 16, ((char **)pos)[i] + j * 16);
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

/* One entry of the four-corner anchor table the cloth is pinned to, the
   48-byte anchor record ClothCfg's anchors point at: the middle vector is the
   local-space anchor position _ApplyMatrix transforms into the corner point. */
typedef struct { /* field names derived */
    VECTOR v0;
    VECTOR v1;
    VECTOR v2;
} ClothFixPoint; /* derived name */

/* the debug draw of a fix point's anchor, built only when DEBUG is defined */
static __inline__ void clothFixDebug(ClothFixPoint *fix) /* derived name */
{
#ifdef DEBUG
    DrawLine((char *)fix->v0, (char *)fix->v1, (LineColor *)&chainLineColor0, 0);
#endif
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
static __inline__ int checkOverThePlane_i(void *pt, const void *plane) /* derived name */
{
    if (0.0f < plane_distance(pt, plane))
        return 1;
    return 0;
}

static __inline__ int checkFrontAcross_i(void *seg, void *plane) /* derived name */
{
    if (0.0f <= plane_distance(seg, plane)) {
        if (plane_distance((char *)seg + 0x10, plane) < 0.0f)
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
static int clipCylinderCollision(char *p, void *pt)
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

ChainSet *InitChains(ChainCfg *cfg)
{
    ChainSet *r;
    int i = 0;
    int j;
    float step;

    r = (ChainSet *)iosMallocDebug(ios_partition_sugipon, 0x10, "src/clothAnimation.c", 1058);
    r->cfg = cfg;
    while (cfg[i].num != -1) {
        i++;
    }
    r->num = i;
    r->nodes = (ChainNode *)iosMallocDebug(ios_partition_sugipon, i * sizeof(ChainNode),
                                           "src/clothAnimation.c", 1064);
    r->oddFrame = 0;
    for (i = 0; i < r->num; i++) {
        r->nodes[i].pos =
            iosMallocDebug(ios_partition_sugipon, cfg[i].num * 16, "src/clothAnimation.c", 1068);
        r->nodes[i].vel =
            iosMallocDebug(ios_partition_sugipon, cfg[i].num * 16, "src/clothAnimation.c", 1069);
        r->nodes[i].len =
            iosMallocDebug(ios_partition_sugipon, cfg[i].num * 4, "src/clothAnimation.c", 1070);
        r->nodes[i].exNum = 0;
        for (j = 0; j < 5; j++) {
            r->nodes[i].ex[j].w = -1.0f;
            CopyVector(&r->nodes[i].ex[j].v0, ZeroPoint);
            CopyVector(&r->nodes[i].ex[j].v1, ZeroPoint);
            CopyVector(&r->nodes[i].ex[j].v2, ZeroVector);
        }
        for (j = 0; j < r->cfg[i].num; j++) {
            CopyVector(r->nodes[i].pos[j], cfg[i].pm.root);
            CopyVector(r->nodes[i].vel[j], ZeroVector);
            step = cfg[i].pm.step;
            r->nodes[i].len[j] = step;
            if (j != 0) {
                r->nodes[i].pos[j][1] = r->nodes[i].pos[j - 1][1] + step;
            }
        }
    }
    return r;
}

ClothSet *InitClothes(ClothCfg *cfg)
{
    ClothSet *r;
    int i = 0;
    int m;
    int q;
    float aa[4];
    float bb[4];

    r = (ClothSet *)iosMallocDebug(ios_partition_sugipon, sizeof(ClothSet), "src/clothAnimation.c",
                                   1101);
    debug_StdPrintfDummy("\x1b[36mALLOC CLOTHES\x1b[m\n");
    while (cfg[i].num != -1) {
        i++;
    }
    r->num = i;
    r->rec = (ClothRec *)iosMallocDebug(ios_partition_sugipon, i * sizeof(ClothRec),
                                        "src/clothAnimation.c", 1106);
    for (i = 0; i < r->num; i++) {
        if (cfg[i].tex != 0) {
            r->rec[i].mesh = prim_InitMesh3D(cfg[i].div, cfg[i].num, 1, 0x5C, 0x80808080, 1);
            r->rec[i].textured = 1;
            r->rec[i].tex = *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(cfg[i].tex));
        } else {
            r->rec[i].mesh = prim_InitMesh3D(cfg[i].div, cfg[i].num, 1, 0x4C, 0xFFFFFF80, 1);
            r->rec[i].textured = 0;
        }
        r->rec[i].pos =
            iosMallocDebug(ios_partition_sugipon, cfg[i].num * 4, "src/clothAnimation.c", 1134);
        r->rec[i].vel =
            iosMallocDebug(ios_partition_sugipon, cfg[i].num * 4, "src/clothAnimation.c", 1135);
        r->rec[i].mark =
            iosMallocDebug(ios_partition_sugipon, cfg[i].num * 4, "src/clothAnimation.c", 1136);
        for (m = 0; m < cfg[i].num; m++) {
            r->rec[i].pos[m] = (VECTOR *)(r->rec[i].mesh->pos + m * cfg[i].div);
            r->rec[i].vel[m] = iosMallocDebug(ios_partition_sugipon, cfg[i].div * 16,
                                              "src/clothAnimation.c", 1141);
            r->rec[i].mark[m] =
                iosMallocDebug(ios_partition_sugipon, cfg[i].div * 4, "src/clothAnimation.c", 1142);
            memset(aa, 0, 16);
            aa[3] = 1.0f;
            memset(bb, 0, 16);
            for (q = 0; q < cfg[i].div; q++) {
                CopyVector(&r->rec[i].pos[m][q], aa);
                CopyVector(&r->rec[i].vel[m][q], bb);
                r->rec[i].mark[m][q] = -1;
            }
        }
    }
    return r;
}

void DispClothMesh(ClothRec *rec, void *la, void *lb)
{
    int t;
    dl_SetDLPriority(2);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(rec->mesh, 5, buffer_ID);
    gif_StartPacketPri(2);
    gif_SetAlpha(1, 7, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    if (rec->textured != 0) {
        t = tex_GetTextureNo((char *)&rec->tex);
    } else {
        t = -1;
    }
    prim_DispMesh3D(rec->mesh, la, lb, t);
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

void DispCloth4D(Cloth4D *c, void *la, void *lb)
{
    int t;
    dl_SetDLPriority(1);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(c->mesh, 3, buffer_ID);
    if (c->cfg->tex != 0) {
        t = tex_GetTextureNo(&c->tex);
    } else {
        t = -1;
    }
    gif_StartPacketPri(1);
    gif_SetAlpha(1, 7, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(c->mesh, la, lb, t);
    if (debug_cloth_info != 0) {
        DispMeshWire(c->pos, c->cfg->nx, c->cfg->ny);
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

static void getCloth4D_preProcess(Cloth4D *c, float g, float damp)
{
    VECTOR dv;
    float work[4][4];
    int i;
    int j;
    Prim3DVec **pos = c->pos;
    Prim3DVec **nrm = c->nrm;
    Prim3DVec **vel = c->vel;
    Cloth4DCfg *cfg = c->cfg;
    int nx = cfg->nx - (cfg->wrap != 0);
    int ny = cfg->ny;
    VECTOR va[nx];
    float rz;
    float t;

    for (i = 0; i < nx; i++) {
        for (j = 1; j < ny; j++) {
            sceVu0ScaleVector(&dv, &vel[i][j], damp);
            CopyVector(&vel[i][j], &pos[i][j]);
            AddVectorXYZ(&pos[i][j], &pos[i][j], &dv);
        }
    }
    for (i = 0; i < nx; i++) {
        for (j = 0; j < 2; j++) {
            int n = cfg->cols[i].link[j].node;
            Cloth4DCol *pt;
            float f;
            Sub15C *sk;

            if (n == -1) {
                break;
            }
            pt = &cfg->cols[i];
            f = pt->link[j].weight;
            sk = GOBJ_SUB(c->gobj);
            _MulMatrix(work, (char *)sk->nodeMtx + n * 64, sk->clusterMtx + n * 64);
            _SetCurrentMatrix(work);
            if (j == 0) {
                clothSetPoint(pos[i], pt->pos, f);
                clothSetPoint(nrm[i], pt->dir, f);
                clothSetPoint(&va[i], pt->restDir, f);
            } else {
                clothAddPoint(pos[i], pt->pos, f);
                clothAddPoint(nrm[i], pt->dir, f);
                clothAddPoint(&va[i], pt->restDir, f);
            }
        }
        pos[i]->w = 1.0f;
        nrm[i]->w = 1.0f;
        va[i].w = 0.0f;
    }
    {
        float *wind;
        float wpow;
        int c;

        c = 0;
        wind = GetWindVector(&wpow, &pos[0]->x);
        wpow = wpow / 40960.0f;
        for (i = 0; i < 11; i++) {
            for (j = 0; j < 3; j++) {
                windNoise[i][j] = wpow * (float)((rand() & 0x7FFF) - 16383);
            }
        }
        rz = 1.0f / (float)(ny - 1);
        for (j = 1; j < ny; j++) {
            t = (float)(ny - j) * rz;
            t = t * t;
            for (i = 0; i < nx; i++) {
                SubVectorXYZ(&work[0], &pos[i][j], &pos[i][j - 1]);
                AddVectorXYZ(&work[0], &work[0], wind);
                AddVectorXYZ(&work[0], &work[0], windNoise[c]);
                c = c + 1;
                if (c == 11) {
                    c = 0;
                }
                _InterVectorXYZ(&work[0], &va[i], &work[0], t);
                work[0][1] = work[0][1] + g;
                AddVectorXYZ(&pos[i][j], &pos[i][j - 1], &work[0]);
            }
        }
    }
}

/* the four procMatrix elements proc writes its Y rotation through */
static float *procCosXX = &procMatrix[0][0]; /* derived name */

static float *procCosZZ = &procMatrix[2][2]; /* derived name */

static float *procSinXZ = &procMatrix[0][2]; /* derived name */

static float *procSinZX = &procMatrix[2][0]; /* derived name */

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
    clipPlane[0][0][3] = pt->bottom;
    clipPlane[1][0][3] = -pt->top;
    cylinderRadiusSq = pt->radius * pt->radius;
}

INCLUDE_ASM(proc_162);

INCLUDE_ASM(getCloth4D);

static void getCloth4D_postProcess(Cloth4D *c, int **rows)
{
    float buf[4];
    int i;
    int j;
    Prim3DVec **pos = c->pos;
    Prim3DVec **nrm = c->nrm;
    Cloth4DCfg *cfg = c->cfg;
    Prim3DVec **vel = c->vel;
    int ny = cfg->ny;
    int nx = cfg->nx - (cfg->wrap != 0);

    for (i = 0; i < nx; i++) {
        for (j = 1; j < ny; j++) {
            if (rows[i][j] == -1) {
                SubVectorXYZ(&vel[i][j], &pos[i][j], &vel[i][j]);
            } else {
                CopyVector(&vel[i][j], ZeroVector);
            }
        }
    }
    if (cfg->wrap != 0) {
        memset(buf, 0, 0x10);
        for (j = 0; j < ny; j++) {
            sceVu0AddVector(&pos[nx][j], &pos[0][j], buf);
        }
        CopyVector(nrm[nx], nrm[0]);
    }
    for (i = 0; i < cfg->nx; i++) {
        for (j = 1; j < ny; j++) {
            CopyVector(&nrm[i][j], nrm[i]);
        }
    }
    for (i = 0; i < c->colNum; i++) {
        CopyMatrix(c->colMtx[i], (char *)GOBJ_SUB(c->gobj)->nodeMtx + c->colNode[i] * 64);
    }
}

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

void GetCloth4D(Cloth4D *c, float x, float y)
{
    float buf[4];
    int i;
    int j;
    int i2;
    int j2;
    int nx = c->cfg->nx;
    int ny = c->cfg->ny;
    int data[nx][ny];
    int *rows[nx];
    Sub15C *obj;
    Cloth4DCfg *cfg;
    int *rows2;
    int nx2;
    int ny2;
    Vec16 *plane;

    for (i = 0; i < nx; i++) {
        rows[i] = data[i];
        for (j = 0; j < ny; j++) {
            rows[i][j] = -1;
        }
    }
    getCloth4D_preProcess(c, x, y);
    getCloth4D(c, rows);
    obj = GOBJ_SUB(c->gobj);
    if (motionKind[obj->ctrl.motion].flags.bits.clothPlane) {
        plane = &obj->root.plane;
        cfg = c->cfg;
        rows2 = (int *)c->pos;
        nx2 = cfg->nx - (cfg->wrap != 0);
        ny2 = cfg->ny;
        for (i2 = 0; i2 < nx2; i2++) {
            for (j2 = 1; j2 < ny2; j2++) {
                char *p = (char *)(j2 * 16 + rows2[i2]);
                float d = plane_distance(p, plane);
                if (d < 0.0f) {
                    _ScaleVector(buf, plane, d);
                    _SubVectorXYZ(p, p, buf);
                }
            }
        }
    }
    getCloth4D_postProcess(c, rows);
}

typedef struct { /* field names derived */
    long long q[8];
} Blob64; /* derived name */

INCLUDE_ASM(InitCloth4D);

void GetChainNodeGlobalQuaternion(void *q, ChainNode *node, int count)
{
    ClothBuf buf;
    SetIdentityQuaternion(q);
    if (count > 0) {
        float (*pts)[4] = node->pos;
        SubVectorXYZ(&buf, pts[count], pts[count - 1]);
        MatrixDrive_GetTurnYAngleXZ(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
        RotQuaternionX(q, (short)-buf.a);
        RotQuaternionZ(q, (short)-buf.b);
    }
}

void MoveChainExtendedWeight(ChainNode *node, int slot, float f)
{
    node->ex[slot].w = f;
}

void InitChainVelocity(ChainSet *sys)
{
    int i;
    int j;
    int k;

    for (i = 0; i < sys->num; i++) {
        int cnt = sys->cfg[i].num;
        for (j = 0; j < cnt; j++) {
            CopyVector(sys->nodes[i].vel[j], ZeroVector);
        }
        for (k = 0; k < 5; k++) {
            ExW *w = &sys->nodes[i].ex[k];
            CopyVector(&w->v2, ZeroVector);
        }
    }
}

void DeleteChainExtendedWeight(ChainNode *node, int slot)
{
    node->ex[slot].w = -1.0f;
    node->exNum = node->exNum - 1;
}

float GetChainNodeID(ChainCfg *cfg, float f)
{
    return f / cfg->pm.step;
}

void ResetClothAnimation(VECTOR **pos, VECTOR **vel, ClothCfg *cfg)
{
    int outer = cfg->num;
    int inner = cfg->div;
    int i = 0;
    int j;

    if (outer > 0) {
        do {
            for (j = 1; j < inner; j++) {
                VECTOR *p = pos[i];
                CopyVector(&p[j], p);
                CopyVector(&vel[i][j], ZeroVector);
            }
            i++;
        } while (i < outer);
    }
}

void GetChainExWeightGlobalQuaternion(float *q, ChainNode *node, int i, int j)
{
    ClothBuf buf;
    SetIdentityQuaternion(q);
    SubVectorXYZ(&buf, &node->ex[j].v1, &node->ex[i].v0);
    buf.v[1] = buf.v[1] + 100.0f;
    MatrixDrive_GetTurnYAngleXZ(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
    RotQuaternionX(q, (short)-buf.a);
    RotQuaternionZ(q, (short)-buf.b);
}

float GetChainCollision(ChainSet *sys, void *pos, float r)
{
    int i;
    int j;

    r = r * r;
    for (i = 0; i < sys->num; i++) {
        float (*pts)[4] = sys->nodes[i].pos;
        for (j = 0; j < sys->cfg[i].num - 1; j++) {
            if (distance_squared(pts[j], pos) < r) {
                return (float)j * sys->cfg[i].pm.step;
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

float getXZLength(void *v)
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

float getXZInvLength(void *v)
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

float getXZLengthSquare(void *v)
{
    VU0_LSV(lqc2, 4, 0x0, 4);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_QMFC2_NI(2, 4);
    VU0_MTC1(2, 0);
}

float subAndGetInvLength(void *d, const void *a, const void *b)
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

void scaleAndAddVectorXYZ(void *d, const void *a, const void *b, float k)
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

void scaleVectorXZ(void *d, const void *s, float k)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void tensionMoveNoReduce(void *out, void *a, void *b, float k)
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

void tensionMove(void *out, void *a, void *b, float k, float lim)
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
    if (inv < lim) {
        scale = k * inv;
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

int checkOverThePlane(void *pt, void *plane)
{
    return checkOverThePlane_i(pt, plane);
}

int checkFrontAcross(void *seg, void *plane)
{
    if (0.0f <= plane_distance(seg, plane)) {
        if (plane_distance((char *)seg + 0x10, plane) < 0.0f)
            return 1;
    }
    return 0;
}

void LockZAnimation(ChainSet *sys)
{
    int i;
    int j;
    int n = sys->num;

    for (i = 0; i < n; i++) {
        int cnt = sys->cfg[i].num;
        for (j = 0; j < cnt; j++) {
            sys->nodes[i].vel[j][2] = 0.0f;
        }
    }
}

void getCloth4D_planeClip(Cloth4D *c, void *plane)
{
    float buf[4];
    int i;
    int j;
    Cloth4DCfg *cfg = c->cfg;
    int *rows = (int *)c->pos;
    int nx = cfg->nx - (cfg->wrap != 0);
    int ny = cfg->ny;

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
