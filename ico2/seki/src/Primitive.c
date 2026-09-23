#include "common.h"
#include "debug.h"
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

typedef struct {
    /* 0x00 */ int cr;
    /* 0x04 */ int cg;
    /* 0x08 */ int cb;
    /* 0x0C */ int ca;
    /* 0x10 */ float x;
    /* 0x14 */ float y;
    /* 0x18 */ float z;
    /* 0x1C */ float w;
} Fan2DVtx __attribute__((aligned(16)));

typedef struct {
    /* 0x00 */ int n;
    /* 0x04 */ int f04;
    /* 0x08 */ Fan2DVtx *buf;
} Fan2D;

extern void *D_0063A44C;
extern char D_0054F8C0[];
extern float center_X;
extern float center_Y;
extern int ScreenWidth;
extern int ScreenHeight;

Fan2D *prim_InitFan2D(int n, float *pos, unsigned int cc, unsigned int rc, float r)
{
    Fan2D *f;
    Fan2DVtx *q;
    Fan2DVtx *first;
    int i;

    f = (Fan2D *)iosMallocDebug(D_0063A44C, 12, D_0054F8C0, 318);
    f->buf = (Fan2DVtx *)iosMallocDebug(D_0063A44C, (n + 2) * 32, D_0054F8C0, 319);
    q = f->buf;

    f->n = n;
    f->f04 = 0;
    q->cr = cc >> 24;
    q->cg = (cc >> 16) & 0xFF;
    q->cb = (cc >> 8) & 0xFF;
    q->ca = cc & 0xFF;
    if ((cc & 0xFF) != 128) {
        f->f04 = 1;
    }
    q->x = pos[0] + center_X;
    q->y = pos[1] + center_Y;
    q->z = -pos[2];
    q->w = 1.0f;
    q++;

    first = q;
    for (i = 0; i < n; i++) {
        q->x = r * GetTableCos((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) +
               pos[0] + center_X;
        q->y = r * GetTableSin((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) * 0.5f +
               pos[1] + center_Y;
        q->z = -pos[2];
        q->w = 1.0f;
        q->cr = rc >> 24;
        q->cg = (rc >> 16) & 0xFF;
        q->cb = (rc >> 8) & 0xFF;
        q->ca = rc & 0xFF;
        if ((rc & 0xFF) != 128) {
            f->f04 = 1;
        }
        q++;
    }
    *q = *first;
    return f;
}

void prim_SetFan2D(Fan2D *f, float *pos, unsigned int cc, unsigned int rc, float r)
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

/* One 64-bit slot of a DMA/GIF packet, written either whole or as its two
   32-bit halves. */
typedef union {
    long long d;
    int w[2];
} PrimPkWord;

typedef struct {
    /* 0x00 */ int cur;
    /* 0x04 */ int *buf[2];
    /* 0x0C */ char *dma;
    /* 0x10 */ char *ptr;
    /* 0x14 */ char *tail;
    /* 0x18 */ char *gif;
    /* 0x1C */ char *end;
} PrimDpk;

extern PrimDpk PacketBufferStruct;
/* kept local: this TU's uses of _FTOI4Vector do not fit the prototype in Matrix.h */
extern void _FTOI4Vector(void *dst, void *src);

void prim_DispFan2D(Fan2D *f, int mode)
{
    int v[4];
    Fan2DVtx *q;
    char *p;
    char *pp;
    char *n;
    char *m;
    char *end;
    char *gif;
    char *tail;
    int i;
    int kick = 3;

    q = f->buf;
    for (i = 0; i < f->n + 2; i++) {
        if (q->x < 0.0f) {
            return;
        }
        if (q->x > 4095.0f) {
            return;
        }
        if (q->y < 0.0f) {
            return;
        }
        if (q->y > 4095.0f) {
            return;
        }
        if (q->z < 0.0f) {
            return;
        }
        q++;
    }

    q = f->buf;
    {
        /* The header is written through a block-scoped handle on the packet
           context: one address materialisation covers the whole region,
           including the tag if/else. */
        PrimDpk *d = &PacketBufferStruct;

        p = d->ptr;
        d->dma = p;
        d->tail = p;
        d->gif = 0;
        d->end = 0;
        d->ptr = p + 8;
        ((PrimPkWord *)(p + 8))->w[0] = 0x11000000;
        d->gif = p + 0xC;
        d->end = p + 0x10;
        d->ptr = p + 0x18;
        ((PrimPkWord *)(p + 0x18))->d = 0xE;
        d->ptr = p + 0x20;
        if (mode == 0) {
            ((PrimPkWord *)(p + 0x20))->d = ((long long)f->f04 << 6) | 0x10D;
            d->ptr = p + 0x28;
            ((PrimPkWord *)(p + 0x28))->d = 0;
            d->ptr = p + 0x30;
        } else {
            ((PrimPkWord *)(p + 0x20))->d = ((long long)f->f04 << 6) | 0x10A;
            d->ptr = p + 0x28;
            ((PrimPkWord *)(p + 0x28))->d = 0;
            d->ptr = p + 0x30;
        }
    }

    for (i = 0; i < f->n + 2; i++) {
        _FTOI4Vector(v, &q->x);
        pp = PacketBufferStruct.ptr;
        ((PrimPkWord *)pp)->d = ((long long)q->cr | ((long long)q->cg << 8) |
                                 ((long long)q->cb << 16) | ((long long)q->ca << 24)) |
                                ((long long)0x3F800000 << 32);
        pp += 8;
        PacketBufferStruct.ptr = pp;
        ((PrimPkWord *)pp)->d = 1;
        PacketBufferStruct.ptr = pp + 8;
        if (q->z < 0.0f) {
            kick = 3;
        }
        kick--;
        if (kick > 0) {
            ((PrimPkWord *)(pp + 8))->d =
                (long long)v[0] | ((long long)v[1] << 16) | ((long long)v[2] << 32);
            PacketBufferStruct.ptr = pp + 0x10;
            ((PrimPkWord *)(pp + 0x10))->d = 0xD;
            PacketBufferStruct.ptr = pp + 0x18;
        } else {
            ((PrimPkWord *)(pp + 8))->d =
                (long long)v[0] | ((long long)v[1] << 16) | ((long long)v[2] << 32);
            PacketBufferStruct.ptr = pp + 0x10;
            ((PrimPkWord *)(pp + 0x10))->d = 5;
            PacketBufferStruct.ptr = pp + 0x18;
        }
        q++;
    }

    end = PacketBufferStruct.end;
    ((PrimPkWord *)end)->d =
        (unsigned int)(((unsigned int)(PacketBufferStruct.ptr - end) >> 4) - 1) |
        0x1000000000008000LL;
    gif = PacketBufferStruct.gif;
    ((PrimPkWord *)gif)->w[0] =
        (((unsigned int)(PacketBufferStruct.ptr - gif) >> 4) << 16) | 0x6C008000;

    n = PacketBufferStruct.ptr;
    ((PrimPkWord *)n)->w[0] = 0x15000000;
    n += 4;
    PacketBufferStruct.ptr = n;
    ((PrimPkWord *)n)->w[0] = 0;
    PacketBufferStruct.ptr = n + 4;
    ((PrimPkWord *)n)->w[1] = 0;
    PacketBufferStruct.ptr = n + 8;
    ((PrimPkWord *)(n + 8))->w[0] = 0;
    PacketBufferStruct.ptr = n + 0xC;

    tail = PacketBufferStruct.tail;
    ((PrimPkWord *)tail)->d =
        (unsigned int)(((unsigned int)(PacketBufferStruct.ptr - tail) >> 4) - 1) | 0x10000000;

    m = PacketBufferStruct.ptr;
    PacketBufferStruct.tail = m;
    ((PrimPkWord *)m)->d = 0x60000000;
    PacketBufferStruct.ptr = m + 8;
    ((PrimPkWord *)(m + 8))->w[0] = 0;
    PacketBufferStruct.ptr = m + 0xC;
    ((PrimPkWord *)(m + 8))->w[1] = 0;
    PacketBufferStruct.ptr = m + 0x10;

    dl_OpenDma(5, (int)PacketBufferStruct.dma, 0);
    dl_CloseDma();
}

typedef int Qw128 __attribute__((mode(TI)));

typedef struct {
    float x, y, z, w;
} Prim3DVec __attribute__((aligned(16)));

typedef struct {
    /* 0x00 */ int nx;
    /* 0x04 */ int ny;
    /* 0x08 */ int f08;
    /* 0x0C */ int f0C;
    /* 0x10 */ float mtx[4][4];
    /* 0x50 */ int f50;
    /* 0x54 */ int f54;
    /* 0x58 */ int f58;
    /* 0x5C */ int f5C;
    /* 0x60 */ long long f60;
    /* 0x68 */ unsigned int col;
    /* 0x6C */ Prim3DVec *pos;
    /* 0x70 */ Prim3DVec *uv;
    /* 0x74 */ Prim3DVec *nrm;
    /* 0x78 */ int f78;
    /* 0x7C */ void *bufs[2];
    /* 0x84 */ int f84[3];
} Mesh3D;

/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *mtx);
/* kept local: this TU's uses of _ApplyCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern long long D_0054F8D0[];
extern char D_0054F8E0[];
extern int D_0063A150[];

void prim_makePacketMesh3D(Mesh3D *m, void *pkt, int uv)
{
    Prim3DVec t;
    Prim3DVec nv = {0.0f, 0.0f, 0.0f, 1.0f};
    Prim3DVec tv = {0.0f, 0.0f, 0.0f, 1.0f};
    Prim3DVec c = {(float)((m->col >> 24) & 0xFF), (float)((m->col >> 16) & 0xFF),
                   (float)((m->col >> 8) & 0xFF), (float)(m->col & 0xFF)};
    char *p;
    int i;
    int k;

    p = (char *)pkt;
    if (c.w == 128.0f) {
        c.w = 127.0f;
    }
    _SetCurrentMatrix(m->mtx);
    for (i = 0; i < m->f54; i++) {
        int w = m->f50;
        int n = w * (m->f58 + 2) + 2;
        long long reg = m->f60;

        if (n >= 0xFD) {
            debug_StdPrintfDummy(D_0054F8E0, w);
            debug_assert(D_0054F8C0, 0x1D9);
            __assert(D_0054F8C0, 0x1D9, (char *)D_0063A150);
        }
        *(int *)(p + 0x0) = 0;
        *(int *)(p + 0x4) = 0;
        *(int *)(p + 0x8) = 0;
        *(int *)(p + 0xC) = (n << 16) | 0x6C008000;
        *(long long *)(p + 0x10) = w | (D_0054F8D0[0] | (reg << 47));
        *(long long *)(p + 0x18) = D_0054F8D0[1];
        p += 0x20;
        *(Qw128 *)p = *(Qw128 *)&c;
        p += 0x10;
        for (k = 0; k < m->f50; k++) {
            *(Qw128 *)p = *(Qw128 *)&nv;
            p += 0x10;
            if (uv != 0) {
                *(Qw128 *)p = *(Qw128 *)&tv;
                p += 0x10;
            }
            {
                int nx = m->nx;
                int idx = (i + (k & 1)) * nx + (k >> 1);
                int u = idx / nx;
                int v = idx % nx;

                t.z = 1.0f;
                t.w = 0.0f;
                t.x = (float)v / (float)(nx - 1);
                t.y = (float)u / (float)(m->ny - 1);
                _ApplyCurrentMatrix(&t, &t);
                *(Qw128 *)p = *(Qw128 *)&t;
                p += 0x10;
            }
        }
        *(int *)(p + 0x0) = 0x17000000;
        *(int *)(p + 0x4) = 0;
        *(int *)(p + 0x8) = 0;
        *(int *)(p + 0xC) = 0;
        p += 0x10;
    }
}

/* kept local: this TU's uses of _InitCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InitCurrentMatrix(void);
/* kept local: this TU's uses of _RotCurrentMatrixZ do not fit the prototype in Matrix.h */
extern void _RotCurrentMatrixZ(short a);
/* kept local: this TU's uses of _GetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _GetCurrentMatrix(void *dst);
extern void prim_makePacketMesh3D(Mesh3D *m, void *pkt, int n);

Mesh3D *prim_InitMesh3D(int nx, int ny, int rot, long long col, unsigned int col2, int f58)
{
    Mesh3D *m;
    int i;

    m = (Mesh3D *)iosMallocDebug(D_0063A44C, 144, D_0054F8C0, 576);
    m->nx = nx;
    m->ny = ny;
    m->pos = (Prim3DVec *)iosMallocDebug(D_0063A44C, m->nx * 16 * m->ny, D_0054F8C0, 579);
    m->uv = (Prim3DVec *)iosMallocDebug(D_0063A44C, m->nx * 16 * m->ny, D_0054F8C0, 580);
    m->nrm = (Prim3DVec *)iosMallocDebug(D_0063A44C, m->nx * 16 * m->ny, D_0054F8C0, 581);
    for (i = 0; i < m->nx * m->ny; i++) {
        m->pos[i].x = m->pos[i].y = m->pos[i].z = 0.0f;
        m->pos[i].w = 1.0f;
        m->uv[i].x = m->uv[i].y = m->uv[i].z = 0.0f;
        m->uv[i].w = 0.0f;
        m->nrm[i].x = m->nrm[i].y = m->nrm[i].w = 0.0f;
        m->nrm[i].z = 1.0f;
    }
    m->f50 = m->nx * 2;
    m->f54 = m->ny - 1;

    m->f58 = f58;

    m->f78 = m->f54 * (m->f50 * (f58 + 2) + 4);

    m->bufs[0] = iosMallocDebug(D_0063A44C, m->f78 * 16, D_0054F8C0, 597);
    m->bufs[1] = iosMallocDebug(D_0063A44C, m->f78 * 16, D_0054F8C0, 598);

    _InitCurrentMatrix();
    _RotCurrentMatrixZ((short)((float)(rot % 4) * 3.1415927f * 0.5f * 10430.3779f));
    _GetCurrentMatrix(m->mtx);

    m->f60 = col;
    m->col = col2;
    prim_makePacketMesh3D(m, m->bufs[0], m->f58);
    prim_makePacketMesh3D(m, m->bufs[1], m->f58);
    return m;
}

/* Primitive.c lines 635-706.  prim_makeNormal fills the per-vertex normal
   buffer at Mesh3D+0x70 (the field the other members of this TU call `uv`;
   the names in the typedef are placeholders and 0x70 is the normal buffer
   here).  The four neighbours of a vertex are walked with one pair of
   indices, x and y, reassigned for each neighbour (listing rows 645, 651,
   657 and 663) and wrapped when the mesh is closed in that direction. */
extern char *matrixptr;
extern void _PushCurrentMatrix(void);
extern void _PopCurrentMatrix(void);
extern void _SubVector(void *d, void *a, void *b);
extern void _OuterProduct(void *d, void *a, void *b);
extern void _AddVector(void *d, void *a, void *b);
extern void _NormalizeVector(void *d, void *s);
extern float _InnerProduct(void *a, void *b);
extern void _ScaleVector(void *d, void *s, float k);

void prim_makeNormal(Mesh3D *m)
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
                if (m->f08 != 0) {
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
                if (m->f0C != 0) {
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
                if (m->f08 != 0) {
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
                if (m->f0C != 0) {
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
            m->uv[i * m->nx + j].x = n.x * s;
            m->uv[i * m->nx + j].y = n.y * s;
            m->uv[i * m->nx + j].z = n.z * s;
            m->uv[i * m->nx + j].w = 0.0f;
            _NormalizeVector(&m->uv[i * m->nx + j], &m->uv[i * m->nx + j]);
            _ApplyCurrentMatrix(&a, &m->uv[i * m->nx + j]);
            b.x = b.y = 0.0f;
            b.z = b.w = 1.0f;
            a.z = _InnerProduct(&b, &a);
            if (a.z > 0.0f) {
                _ScaleVector(&m->uv[i * m->nx + j], &m->uv[i * m->nx + j], -1.0f);
            }
            m->uv[i * m->nx + j].w = 0.0f;
        }
    }
    _PopCurrentMatrix();
}

extern void prim_makeNormal(Mesh3D *m);

void prim_UpdateMesh3D(Mesh3D *m, int flags, int idx)
{
    Qw128 *p;
    int i;
    int j;

    if (m->f58 != 0 && (flags & 4) != 0) {
        prim_makeNormal(m);
    }
    p = (Qw128 *)m->bufs[idx];
    for (i = 0; i < m->f54; i++) {
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
        for (j = 0; j < m->f50; j++) {
            if (flags & 1) {
                *p = *(Qw128 *)&m->pos[(i + (j & 1)) * m->nx + (j >> 1)];
            }
            p++;
            if (m->f58 != 0) {
                if (flags & 6) {
                    *p = *(Qw128 *)&m->uv[(i + (j & 1)) * m->nx + (j >> 1)];
                }
                p++;
            }
            if (flags & 8) {
                *p = *(Qw128 *)&m->nrm[(i + (j & 1)) * m->nx + (j >> 1)];
            }
            p++;
        }
        p++;
    }
}

/* Primitive.c lines 785-868.  setMatrix, setLight and clearUVOffset are GNU
   nested functions of prim_DispMesh3D: each consumes the static chain in $2 on
   entry (the ROM stores it at the top of the frame, and setLight reads the
   parent's two light arguments through it), and the January-2002 listing names
   them setMatrix.100, setLight.104 and clearUVOffset.108, gcc's own labels for
   a nested body.  The retail build drops the three primitive counters the
   listing carries at rows 860-862.
   A matrix or vector copied into the packet takes the cursor post-incremented
   as its destination, `_CopyMatrix(((float (*)[16])dd->ptr)++, m)`: the
   increment is queued (expr.c expand_increment, the MEM path), so the old
   cursor is copied out first and the add is done in place on the loaded
   register before the store and the call, which is setLight's second copy in
   the ROM (listing row 810: move $a0,$v0 then addiu $v0,$v0,64, the store in
   the call's slot).  A cursor local assigned `r + 0x40` schedules the add
   before the argument copy and ties the pointer to $a0 (measured, 52 of 53
   or 16 words).  Rows 809 and 810 are the same statement, so every packet
   copy here is spelled the same way. */
extern int D_0063B124;
extern int D_0063B204;
extern int buffer_ID;
extern void mc_SetMicroCode(int a, int b, int c, int d, int e);
/* kept local: this TU's uses of the gif packet calls do not fit GifPacket.h
   (gif_StartPacketPri takes the priority, gif_SetGsReg two ints here) */
extern void gif_SetGsReg(int reg, int val);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
/* kept local: this TU's uses of _CopyMatrix do not fit the prototype in Matrix.h */
extern void _CopyMatrix(void *dst, void *src);
extern void _CopyVector(void *dst, void *src);

void prim_DispMesh3D(Mesh3D *m, void *la, void *lb, int tex)
{
    PrimDpk *d;
    char *p;
    char *q;
    char *ext;
    int pri;

    void setMatrix(void)
    {
        float mtx[16];
        PrimDpk *dd;
        char *q;
        char *r;

        _GetCurrentMatrix(mtx);
        dd = &PacketBufferStruct;
        q = dd->ptr;
        dd->tail = q;
        ((PrimPkWord *)q)->d = 0x10000005;
        dd->ptr = q + 8;
        ((PrimPkWord *)(q + 8))->w[0] = 0;
        dd->ptr = q + 0xC;
        dd->gif = q + 0xC;
        ((PrimPkWord *)(q + 0xC))->w[0] = 0x6C048000;
        dd->ptr = q + 0x10;
        _CopyMatrix(((float (*)[16])dd->ptr)++, mtx);
        r = dd->ptr;
        ((PrimPkWord *)r)->w[0] = 0x15000010;
        r += 4;
        dd->ptr = r;
        ((PrimPkWord *)r)->w[0] = 0;
        dd->ptr = r + 4;
        ((PrimPkWord *)(r + 4))->w[0] = 0;
        dd->ptr = r + 8;
        ((PrimPkWord *)(r + 8))->w[0] = 0;
        dd->ptr = r + 0xC;
    }

    void setLight(void)
    {
        PrimDpk *dd;
        char *q;
        char *r;

        dd = &PacketBufferStruct;
        q = dd->ptr;
        dd->tail = q;
        ((PrimPkWord *)q)->d = 0x10000009;
        dd->ptr = q + 8;
        ((PrimPkWord *)(q + 8))->w[0] = 0;
        dd->ptr = q + 0xC;
        dd->gif = q + 0xC;
        ((PrimPkWord *)(q + 0xC))->w[0] = 0x6C088000;
        dd->ptr = q + 0x10;
        _CopyMatrix(((float (*)[16])dd->ptr)++, lb);
        _CopyMatrix(((float (*)[16])dd->ptr)++, la);
        r = dd->ptr;
        ((PrimPkWord *)r)->w[0] = 0x15000012;
        r += 4;
        dd->ptr = r;
        ((PrimPkWord *)r)->w[0] = 0;
        dd->ptr = r + 4;
        ((PrimPkWord *)(r + 4))->w[0] = 0;
        dd->ptr = r + 8;
        ((PrimPkWord *)(r + 8))->w[0] = 0;
        dd->ptr = r + 0xC;
    }

    void clearUVOffset(void)
    {
        float v[4];
        PrimDpk *dd;
        char *q;
        char *r;

        memset(v, 0, 16);
        dd = &PacketBufferStruct;
        q = dd->ptr;
        dd->tail = q;
        ((PrimPkWord *)q)->d = 0x10000002;
        dd->ptr = q + 8;
        ((PrimPkWord *)(q + 8))->w[0] = 0;
        dd->ptr = q + 0xC;
        dd->gif = q + 0xC;
        ((PrimPkWord *)(q + 0xC))->w[0] = 0x6C018000;
        dd->ptr = q + 0x10;
        _CopyVector(((float (*)[4])dd->ptr)++, v);
        r = dd->ptr;
        ((PrimPkWord *)r)->w[0] = 0x15000002;
        r += 4;
        dd->ptr = r;
        ((PrimPkWord *)r)->w[0] = 0;
        dd->ptr = r + 4;
        ((PrimPkWord *)(r + 4))->w[0] = 0;
        dd->ptr = r + 8;
        ((PrimPkWord *)(r + 8))->w[0] = 0;
        dd->ptr = r + 0xC;
    }

    pri = dl_GetPri();
    if (D_0063B204 == 0) {
        return;
    }
    ext = (char *)tex_GetTexExtData(tex);
    if (*(int *)(ext + 0x40) != 0) {
        if (*(int *)(ext + 0x24) != 0) {
            pri = reg_GetShinePri(*(int *)(ext + 0x24));
        }
    }
    if (tex != -1) {
        D_0063B124 += tex_TransTexture(tex, pri);
    }
    mc_TransMicroCode(4, 1 << pri);
    d = &PacketBufferStruct;
    p = d->ptr;
    d->tail = 0;
    d->dma = p;
    d->gif = 0;
    d->end = 0;
    setMatrix();
    if (m->f58 != 0) {
        setLight();
    }
    if (tex == -1) {
        clearUVOffset();
    }
    q = d->ptr;
    d->tail = q;
    ((PrimPkWord *)q)->d = 0x60000000;
    d->ptr = q + 8;
    ((PrimPkWord *)(q + 8))->w[0] = 0;
    d->ptr = q + 0xC;
    ((PrimPkWord *)(q + 0xC))->w[0] = 0;
    d->ptr = q + 0x10;
    dl_OpenDma(5, (int)d->dma, 0);
    dl_CloseDma();
    gif_StartPacketPri(pri);
    gif_SetGsReg(0x4A, 0);
    gif_EndPacket();
    mc_SetMicroCode(2, m->f58, 0, 1, pri);
    dl_OpenDma(2, (int)m->bufs[buffer_ID], m->f78);
    dl_CloseDma();
}

typedef struct {
    /* 0x00 */ int head[4];
    /* 0x10 */ float mtx[4][4];
    /* 0x50 */ float lmtx[4][4];
    /* 0x90 */ int tail[4];
} PrimParticleBuf;

typedef struct {
    /* 0x000 */ PrimParticleBuf buf[2];
    /* 0x140 */ int f140;
    /* 0x144 */ int f144;
    /* 0x148 */ int num;
    /* 0x14C */ float x;
    /* 0x150 */ float y;
    /* 0x154 */ float z;
    /* 0x158 */ int f158;
    /* 0x15C */ char name[0x20];
    /* 0x17C */ int tex;
    /* 0x180 */ int cur;
    /* 0x184 */ int f184;
    /* 0x188 */ char *objs[2];
    /* 0x190 */ int f190;
    /* 0x194 */ int f194;
} PrimParticle;

extern char D_0054F9A8[];
extern int D_0028F4D4[];
extern int D_0063A160[];
extern int D_0063B200;

/* One 16-byte constant packet template, copied to the stack. */
typedef struct {
    long long d[2];
} PrimQw;

extern const PrimQw D_0054F900;
extern const Prim3DVec D_0054F910;
extern const Prim3DVec D_0054F920;
extern char D_0054F930[];
extern char D_0054F978[];
extern char D_0063A158[];
extern void _UnitMatrix(void *m);
extern void malloc_MemCpy(void *dst, void *src, int n);

PrimParticle *prim_InitParticleByPartition(int num, float x, float y, float z, int a1, char *name,
                                           int a3, void *heap)
{
    PrimQw hd = D_0054F900;
    Prim3DVec cl0 = D_0054F910;
    Prim3DVec cl1 = D_0054F920;
    PrimParticle *p;
    char *q;
    char *r;
    /* the GIF tag's PRIM field: sprite, TME, ABE, AA1 */
    long long prim = 214;

    if (num > 80) {
        debug_StdPrintfDummy(D_0054F930, num, 80);
        return 0;
    }
    p = (PrimParticle *)iosMallocDebugNoAssert(heap, 0x1A0, D_0054F8C0, 911);
    if (p == 0) {
        return 0;
    }
    p->buf[0].head[0] = 0;
    p->buf[0].head[1] = 0;
    p->buf[0].head[2] = 0;
    p->buf[0].head[3] = 0x6C088000;
    _UnitMatrix(p->buf[0].mtx);
    _UnitMatrix(p->buf[0].lmtx);
    p->buf[0].tail[0] = 0x15000010;
    p->buf[0].tail[1] = 0;
    p->buf[0].tail[2] = 0;
    p->buf[0].tail[3] = 0;
    p->f140 = 10;
    malloc_MemCpy(&p->buf[1], &p->buf[0], 160);
    p->f144 = 0;
    p->num = num;
    p->x = x;
    p->y = y;
    p->z = z;
    p->f158 = a1;
    sprintf(p->name, D_0063A158, name);
    p->tex = tex_GetTextureNo(p->name);
    if (p->tex < 0 || p->tex >= tex_GetTextureNum()) {
        debug_StdPrintfDummy(D_0054F978, p->name, p->tex);
        debug_assert(D_0054F8C0, 0x3AA);
        __assert(D_0054F8C0, 0x3AA, (char *)D_0063A160);
    }
    p->f184 = num * 32 + 128;
    p->objs[0] = (char *)iosMallocDebugNoAssert(heap, p->f184, D_0054F8C0, 944);
    if (p->objs[0] == 0) {
        iosFree(p);
        return 0;
    }
    p->objs[1] = (char *)iosMallocDebugNoAssert(heap, p->f184, D_0054F8C0, 949);
    if (p->objs[1] == 0) {
        iosFree(p->objs[0]);
        iosFree(p);
        return 0;
    }
    q = p->objs[0];
    p->f184 = p->f184 >> 4;
    *(int *)(q + 0x0) = 0;
    *(int *)(q + 0x4) = 0;
    *(int *)(q + 0x8) = 0;
    *(int *)(q + 0xC) = ((p->f184 - 2) << 16) | 0x6C008000;
    *(int *)(q + 0x10) = num;
    *(int *)(q + 0x14) = 0;
    *(int *)(q + 0x18) = 0;
    *(int *)(q + 0x1C) = 0;
    *(long long *)(q + 0x20) = hd.d[0] | (prim << 47) | 1;
    *(long long *)(q + 0x28) = hd.d[1];
    *(long long *)(q + 0x30) = hd.d[0] | (prim << 47) | 0x8001;
    *(long long *)(q + 0x38) = hd.d[1];
    _CopyVector(q + 0x40, &cl0);
    _CopyVector(q + 0x50, &cl1);
    r = q + (num * 32 + 0x70);
    *(int *)(r + 0x0) = 0x13000000;
    *(int *)(r + 0x4) = 0x17000000;
    *(int *)(r + 0x8) = 0;
    *(int *)(r + 0xC) = 0;
    *(float *)(q + 0x60) = x;
    *(float *)(q + 0x64) = y;
    *(float *)(q + 0x68) = z;
    *(float *)(q + 0x6C) = 0.0f;
    malloc_MemCpy(p->objs[1], p->objs[0], p->f184 * 16);
    p->cur = 0;
    p->f190 = (int)(p->objs[0] + 0x70);
    p->f194 = (int)(p->objs[1] + 0x70);
    return p;
}

void prim_DispParticle(PrimParticle *p, void *mtx)
{
    int pri = dl_GetPri();

    if (D_0063B200 != 0) {
        if (p->tex < 0 || p->tex >= tex_GetTextureNum()) {
            debug_StdPrintfDummy(D_0054F9A8, p->name, p->tex);
            debug_assert(D_0054F8C0, 0x3FC);
            __assert(D_0054F8C0, 0x3FC, (char *)D_0063A160);
            return;
        }
        if (p->num < 0x51) {
            D_0063B124 += tex_TransTexture(p->tex, pri);
            _CopyMatrix(p->buf[p->cur].mtx, mtx);
            _CopyMatrix(p->buf[p->cur].lmtx, matrixptr + 0xC0);
            mc_TransMicroCode(5, 1 << pri);
            dl_OpenDma(2, (int)&p->buf[p->cur], p->f140);
            dl_CloseDma();
            mc_SetMicroCode(3, 0, 0, 0, pri);
            dl_OpenDma(2, (int)p->objs[p->cur], p->f184);
            dl_CloseDma();
            if (D_0028F4D4[0] == 0) {
                p->cur ^= 1;
            }
            p->f190 = (int)(p->objs[p->cur] + 112);
            p->f194 = (int)(p->objs[p->cur ? 0 : 1] + 112);
        }
    }
}

void prim_DeleteParticle(int a0)
{
    EntryDelayFree(*(int *)(a0 + 0x18C));
    EntryDelayFree(*(int *)(a0 + 0x188));
    EntryDelayFree(a0);
}

void prim_DispWireYCylinder(void *col, int n, int flag, float r, float y0, float y1)
{
    float a;
    float st = 65536.0f / (float)n;

    void drawDisc(float rr, float yy)
    {
        Prim3DVec c = {0.0f, yy, 0.0f, 1.0f};

        for (a = 0.0f; a < 65536.0f; a += st) {
            Prim3DVec q0 = {rr * GetTableSin((short)a), yy, rr * GetTableCos((short)a), 1.0f};
            Prim3DVec q1 = {rr * GetTableSin((short)(a + st)), yy,
                            rr * GetTableCos((short)(a + st)), 1.0f};

            DrawLineG(&q0, col, &q1, col, flag);
            DrawLineG(&q0, col, &c, col, flag);
        }
    }

    inline void drawSide(float rr, float ya, float yb)
    {
        for (a = 0.0f; a < 65536.0f; a += st) {
            Prim3DVec p0 = {rr * GetTableSin((short)a), ya, rr * GetTableCos((short)a), 1.0f};
            Prim3DVec p1 = {p0.x, yb, p0.z, 1.0f};

            DrawLineG(&p0, col, &p1, col, flag);
        }
    }

    drawDisc(r, y0);
    drawDisc(r, y1);
    drawSide(r, y0, y1);
}

/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float s);

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
typedef struct {
    float x, y, z, w;
} PrimVtx __attribute__((aligned(16)));

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

extern void *D_0063A450;

PrimParticle *prim_InitParticle(int num, float x, float y, float z, int a1, char *name, int a3)
{
    return prim_InitParticleByPartition(num, x, y, z, a1, name, a3, D_0063A450);
}
