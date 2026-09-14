#include "common.h"

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
extern float D_0063A05C;
extern float D_0063A060;
extern int D_0063A064;
extern int D_0063A068;
extern void *iosMallocDebug(void *heap, int size, char *file, int line);
extern float GetTableCos(short a);
extern float GetTableSin(short a);

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
    q->x = pos[0] + D_0063A05C;
    q->y = pos[1] + D_0063A060;
    q->z = -pos[2];
    q->w = 1.0f;
    q++;

    first = q;
    for (i = 0; i < n; i++) {
        q->x = r * GetTableCos((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) +
               pos[0] + D_0063A05C;
        q->y = r * GetTableSin((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) * 0.5f +
               pos[1] + D_0063A060;
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
    q->x = pos[0] + D_0063A05C;
    q->y = pos[1] + D_0063A060;
    q->z = -pos[2];
    q->w = 1.0f;
    q++;

    first = q;
    for (i = 0; i < f->n; i++) {
        q->x = r * GetTableCos((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) +
               pos[0] + D_0063A05C;
        q->y = r * GetTableSin((short)((float)i * 6.2831855f / (float)f->n * 10430.3779f)) *
                   ((float)D_0063A068 * 4.0f / ((float)D_0063A064 * 3.0f)) +
               pos[1] + D_0063A060;
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

ASM_LIT4_SLOT(D_00638C68, 4095.0f);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispFan2D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_makePacketMesh3D);

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

extern void _InitCurrentMatrix(void);
extern void _RotCurrentMatrixZ(short a);
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

INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_makeNormal);

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

INCLUDE_ASM("asm/nonmatchings/src/Primitive", setMatrix);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", setLight);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", clearUVOffset);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_DispMesh3D);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", prim_InitParticleByPartition);

typedef struct {
    /* 0x00 */ char head[0x10];
    /* 0x10 */ float mtx[4][4];
    /* 0x50 */ float lmtx[4][4];
    /* 0x90 */ char tail[0x10];
} PrimParticleBuf;

typedef struct {
    /* 0x000 */ PrimParticleBuf buf[2];
    /* 0x140 */ int f140;
    /* 0x144 */ int f144;
    /* 0x148 */ int num;
    /* 0x14C */ char pad14C[0x10];
    /* 0x15C */ char name[0x20];
    /* 0x17C */ int tex;
    /* 0x180 */ int cur;
    /* 0x184 */ int f184;
    /* 0x188 */ char *objs[2];
    /* 0x190 */ int f190;
    /* 0x194 */ int f194;
} PrimParticle;

extern char *matrixptr;
extern char D_0054F8C0[];
extern char D_0054F9A8[];
extern int D_0028F4D4[];
extern int D_0063A160[];
extern int D_0063B124;
extern int D_0063B200;
extern int dl_GetPri(void);
extern int tex_GetTextureNum(void);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int tex_TransTexture(int no, int pri);
extern void _CopyMatrix(void *dst, void *src);
extern void mc_TransMicroCode(int a0, int a1);
extern void dl_OpenDma(int a0, int a1, int a2);
extern void dl_CloseDma(void);
extern void mc_SetMicroCode();

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

extern void EntryDelayFree(int a0);

void prim_DeleteParticle(int a0)
{
    EntryDelayFree(*(int *)(a0 + 0x18C));
    EntryDelayFree(*(int *)(a0 + 0x188));
    EntryDelayFree(a0);
}

extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);

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

extern void _ScaleVectorXYZ(void *dst, void *src, float s);

void prim_DispWireSphere(void *col, int nu, int nv, float r)
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

extern int D_0063A450;
extern int prim_InitParticleByPartition();

int prim_InitParticle(int a0, int a1, int a2, int a3)
{
    return prim_InitParticleByPartition(a0, a1, a2, a3, D_0063A450);
}
