#include "debug.h"
#include "Basic.h"
#include "memory.h"
#include "DisplayList.h"
#include "MicroCode.h"
#include "RegistPacket.h"
#include "Texture.h"
#include "delayFreeManager.h"
#include "lineManager.h"
#include "tableSin.h"
#include <string.h>
#include <stdio.h>
#include "GsBase.h"
#include "Matrix.h"
#include "main.h"
#include "debug_exception.h"
#include "GifPacket.h"
#include "Primitive.h"
#include "DmaPacket.h"
#include "ios.h"
#include <assert.h>
#include "include_asm.h"

INCLUDE_ASM(prim_InitFan2D);

void prim_SetFan2D(Fan2D *f, float r, float *pos, unsigned int cc, unsigned int rc)
{
    Fan2DVtx *q;
    Fan2DVtx *first;
    int i;

    q = f->buf;
    q->cr = cc >> 24;
    q->cg = (cc >> 16) & 0xFF;
    q->cb = (cc >> 8) & 0xFF;
    q->ca = cc & 0xFF;
    q->x = pos[0] + center_X;
    q->y = pos[1] + center_Y;
    q->z = -pos[2];
    q->w = 1.0f;
    q++;

    first = q;
    for (i = 0; i < f->n; i++) {
        q->x = r * GetTableCos((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) +
               pos[0] + center_X;
        q->y = r * GetTableSin((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) *
                   ((float)ScreenHeight * 4.0f / ((float)ScreenWidth * 3.0f)) +
               pos[1] + center_Y;
        q->z = -pos[2];
        q->w = 1.0f;
        q->cr = rc >> 24;
        q->cg = (rc >> 16) & 0xFF;
        q->cb = (rc >> 8) & 0xFF;
        q->ca = rc & 0xFF;
        q++;
    }
    *q = *first;
}

INCLUDE_ASM(prim_DispFan2D);

typedef int Qw128 __attribute__((mode(TI))); /* derived name */

/* The mesh strip's GIF tag template: NLOOP and PRIM are ORed in per strip.
   prim_makePacketMesh3D reads it by pointer dereference. */
static const long long meshGifTag[2] = {0x3000400000008000LL, 0x512}; /* derived name */

INCLUDE_ASM(prim_makePacketMesh3D);

INCLUDE_ASM(prim_InitMesh3D);

/* prim_makeNormal fills the per-vertex normal buffer at Mesh3D+0x70.  The
   four neighbours of a vertex are walked with one pair of indices, x and y,
   reassigned for each neighbour and wrapped when the mesh is closed in that
   direction. */

static void prim_makeNormal(Mesh3D *m)
{
    int f[4];
    Prim3DVec n;
    Prim3DVec a;
    Prim3DVec b;
    Prim3DVec c;
    Prim3DVec d;
    Prim3DVec e0;
    Prim3DVec e1;
    Prim3DVec e2;
    Prim3DVec e3;
    int i;
    int j;
    int x;
    int y;
    int cnt;
    float s;

    _PushCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x80);
    for (i = 0; i < m->ny; i++) {
        for (j = 0; j < m->nx; j++) {
            f[0] = f[1] = f[2] = f[3] = 0;
            x = j - 1;
            y = i;
            if (x < 0) {
                if (m->wrapX != 0) {
                    x = m->nx - 1;
                }
            }
            if (x >= 0) {
                _SubVector(&e0, &m->pos[y * m->nx + x], &m->pos[i * m->nx + j]);
                f[0] = 1;
            }
            x = j;
            y = i - 1;
            if (y < 0) {
                if (m->wrapY != 0) {
                    y = m->ny - 1;
                }
            }
            if (y >= 0) {
                _SubVector(&e1, &m->pos[y * m->nx + x], &m->pos[i * m->nx + j]);
                f[1] = 1;
            }
            x = j + 1;
            y = i;
            if (x >= m->nx) {
                if (m->wrapX != 0) {
                    x = 0;
                }
            }
            if (x < m->nx) {
                _SubVector(&e2, &m->pos[y * m->nx + x], &m->pos[i * m->nx + j]);
                f[2] = 1;
            }
            x = j;
            y = i + 1;
            if (y >= m->ny) {
                if (m->wrapY != 0) {
                    y = 0;
                }
            }
            if (y < m->ny) {
                _SubVector(&e3, &m->pos[y * m->nx + x], &m->pos[i * m->nx + j]);
                f[3] = 1;
            }
            n.x = n.y = n.z = n.w = 0.0f;
            cnt = 0;
            if (f[0] != 0 && f[1] != 0) {
                _OuterProduct(&a, &e0, &e1);
                _AddVector(&n, &n, &a);
                cnt++;
            }
            if (f[1] != 0 && f[2] != 0) {
                _OuterProduct(&b, &e1, &e2);
                _AddVector(&n, &n, &b);
                cnt++;
            }
            if (f[2] != 0 && f[3] != 0) {
                _OuterProduct(&c, &e2, &e3);
                _AddVector(&n, &n, &c);
                cnt++;
            }
            if (f[3] != 0 && f[0] != 0) {
                _OuterProduct(&d, &e3, &e0);
                _AddVector(&n, &n, &d);
                cnt++;
            }
            s = 1.0f / cnt;
            m->nrm[i * m->nx + j].x = n.x * s;
            m->nrm[i * m->nx + j].y = n.y * s;
            m->nrm[i * m->nx + j].z = n.z * s;
            m->nrm[i * m->nx + j].w = 0.0f;
            _NormalizeVector(&m->nrm[i * m->nx + j], &m->nrm[i * m->nx + j]);
            _ApplyCurrentMatrix(&a, &m->nrm[i * m->nx + j]);
            b.x = b.y = 0.0f;
            b.z = b.w = 1.0f;
            a.z = _InnerProduct(&b, &a);
            if (a.z > 0.0f) {
                _ScaleVector(&m->nrm[i * m->nx + j], &m->nrm[i * m->nx + j], -1.0f);
            }
            m->nrm[i * m->nx + j].w = 0.0f;
        }
    }
    _PopCurrentMatrix();
}

void prim_UpdateMesh3D(Mesh3D *m, int flags, int idx)
{
    Qw128 *p;
    int i;
    int j;

    if (m->lit != 0 && (flags & 4) != 0) {
        prim_makeNormal(m);
    }
    p = (Qw128 *)m->bufs[idx];
    for (i = 0; i < m->strips; i++) {
        p += 2;
        if (flags & 0x10) {
            Prim3DVec c = {(float)((m->col >> 24) & 0xFF), (float)((m->col >> 16) & 0xFF),
                           (float)((m->col >> 8) & 0xFF), (float)(m->col & 0xFF)};

            if (c.w < 0.0f) {
                c.w = 0.0f;
            }
            if (c.w >= 128.0f) {
                c.w = 127.0f;
            }
            *p = *(Qw128 *)&c;
        }
        p++;
        for (j = 0; j < m->stripLen; j++) {
            if (flags & 1) {
                *p = *(Qw128 *)&m->pos[(i + (j & 1)) * m->nx + (j >> 1)];
            }
            p++;
            if (m->lit != 0) {
                if (flags & 6) {
                    *p = *(Qw128 *)&m->nrm[(i + (j & 1)) * m->nx + (j >> 1)];
                }
                p++;
            }
            if (flags & 8) {
                *p = *(Qw128 *)&m->st[(i + (j & 1)) * m->nx + (j >> 1)];
            }
            p++;
        }
        p++;
    }
}

INCLUDE_ASM(setMatrix_27_Primitive);

INCLUDE_ASM(setLight_31_Primitive);

INCLUDE_ASM(clearUVOffset_35_Primitive);

/* setMatrix, setLight and clearUVOffset are GNU nested functions of
   prim_DispMesh3D; setLight reads the parent's two light arguments.  A matrix
   or vector copied into the packet takes the cursor post-incremented as its
   destination, `_CopyMatrix(((float (*)[16])dd->ptr.c)++, m)`, and every
   packet copy here is spelled the same way. */

INCLUDE_ASM(prim_DispMesh3D);

/* One 16-byte constant packet template, copied to the stack. */
typedef struct { /* field names derived */
    long long d[2];
} PrimQw; /* derived name */

INCLUDE_ASM(prim_InitParticleByPartition);

INCLUDE_ASM(prim_DispParticle);

void prim_DeleteParticle(PrimParticle *p)
{
    EntryDelayFree(p->objs[1]);
    EntryDelayFree(p->objs[0]);
    EntryDelayFree(p);
}

INCLUDE_ASM(drawDisc_51_Primitive);

INCLUDE_ASM(prim_DispWireYCylinder);

void prim_DispWireSphere(float r, void *col, int nu, int nv)
{
    float us = 65536.0f / (float)nu;
    float vs = 32768.0f / (float)nv;
    float u;
    float v;

    for (v = -16384.0f; v < 16384.0f; v += vs) {
        for (u = 0.0f; u < 65536.0f; u += us) {
            Prim3DVec p0 = {GetTableSin((short)u) * GetTableCos((short)v), GetTableSin((short)v),
                            GetTableCos((short)u) * GetTableCos((short)v), 1.0f};
            Prim3DVec p1 = {GetTableSin((short)(u + us)) * GetTableCos((short)v),
                            GetTableSin((short)v),
                            GetTableCos((short)(u + us)) * GetTableCos((short)v), 1.0f};
            Prim3DVec p2 = {GetTableSin((short)u) * GetTableCos((short)(v + vs)),
                            GetTableSin((short)(v + vs)),
                            GetTableCos((short)u) * GetTableCos((short)(v + vs)), 1.0f};

            _ScaleVectorXYZ(&p0, &p0, r);
            _ScaleVectorXYZ(&p1, &p1, r);
            _ScaleVectorXYZ(&p2, &p2, r);
            DrawLineG(&p0, col, &p1, col, 0);
            DrawLineG(&p0, col, &p2, col, 0);
        }
    }
}

/* Box corner, a VU0 quadword: DrawLineG takes 16-byte aligned vectors. */
typedef struct { /* field names derived */
    float x, y, z, w;
} PrimVtx __attribute__((aligned(16))); /* derived name */

void prim_DispWireBox(float *sz, void *col)
{
    PrimVtx bmin = {-sz[0], -sz[1], -sz[2], 1.0f};
    PrimVtx bmax = {sz[0], sz[1], sz[2], 1.0f};
    PrimVtx v[8];
    int e[12][2] = {{0, 1}, {1, 3}, {3, 2}, {2, 0}, {4, 5}, {5, 7},
                    {7, 6}, {6, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
    int i;

    for (i = 0; i < 8; i++) {
        v[i].x = (i & 1) ? bmax.x : bmin.x;
        v[i].y = (i & 2) ? bmax.y : bmin.y;
        v[i].z = (i & 4) ? bmax.z : bmin.z;
        v[i].w = 1.0f;
    }
    for (i = 0; i < 12; i++) {
        DrawLineG(&v[e[i][0]], col, &v[e[i][1]], col, 0);
    }
}
