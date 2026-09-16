#include "common.h"
#include "sugiCommon.h"

typedef struct {
    char c[16];
} Blob16;

typedef struct {
    char c[4];
} Blob4;

typedef struct {
    long long c[2];
} Blob16L;

extern void ExecuteSEPackage(int a0, int a1);

void falldownSE(int a0)
{
    ExecuteSEPackage(a0, 0x56);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", copyToWork);

extern char D_0054DA50[];
extern int D_00639F28;
extern int D_00639F2C;
extern char D_00639F38[];
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetDrawEnviroment(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_SetZTest(int a0);
extern void gif_SpriteSensitiveOrg(void *a0, int a1, void *a2, void *a3, int a4);
extern int tex_AllocVramAuto(int a0, int a1);
extern void tex_ResetVramPri(void);

void flushWork(int pri)
{
    char buf[0x20];

    tex_ResetVramPri();
    D_00639F28 = tex_AllocVramAuto(0, 0x400);
    D_00639F2C = tex_AllocVramAuto(0, 0x400);
    gif_SetDrawEnviroment(D_00639F28, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (D_00639F2C / 32));
    gif_SetAlpha(0, 4, 0);
    *(Blob16 *)buf = *(Blob16 *)D_0054DA50;
    *(Blob4 *)(buf + 0x10) = *(Blob4 *)D_00639F38;
    gif_SpriteSensitiveOrg(buf, 0, 0, buf + 0x10, 0);
    gif_SetZTest(1);
}

extern char D_002907E0[];
extern int GetSkeltonFocusNode(char *a0, int a1);
extern int SetParticleEffectActiveSensing(int a0, int a1, int a2);
extern void SetParticleEffectUpperLimit(int a0, float f);

void setNodePursueParticleEffectWithUpperLimit(char *a0, char *a1, int a2, float f)
{
    int ret = GetSkeltonFocusNode(a1, a2);
    if (ret != -1) {
        char *p = *(char **)(a1 + 0x15C);
        int r = SetParticleEffectActiveSensing((int)a0, *(int *)(p + 0xC) + ret * 0x40 + 0x30,
                                               (int)D_002907E0);
        SetParticleEffectUpperLimit(r, f);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", SetFallDownSplash);

extern void CopyVector(void *a0, void *a1);

void GetPoolGlobalDrainVector(void *dst, char *a0)
{
    CopyVector(dst, *(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", InitPoolGeo);

extern int D_0028F4C0[];
extern float GetTableCos(short a);
extern float GetTableSin(short a);

static inline void decayRipple(char *c)
{
    if (*(float *)(c + 0x10) < 0.0f) {
        return;
    }
    *(float *)(c + 0x14) += 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    *(float *)(c + 0x10) -= 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.0005f;
}

static inline void addRippleToGrid(char *w, char *c, float **grid)
{
    float step = *(float *)(w + 0x3C);
    int nx = *(int *)(w + 0x34);
    int ny = *(int *)(w + 0x38);
    float r;
    float inv;
    float dx;
    float dy;
    float t;
    float *row;
    int n;
    int x;
    int y;
    int ix;
    int iz;

    if (*(float *)(c + 0x10) < 0.0f) {
        return;
    }

    {
        r = *(float *)(c + 0x14) * 3.0f;
        inv = 1.0f / r;
        n = (int)(r / step);

        for (x = -n; x <= n; x++) {
            dx = (float)x * step - *(float *)(c + 0x4);
            if (dx < 0.0f) {
                dx = -dx;
            }
            ix = *(int *)(c + 0x0) + x;

            if (ix < 0) {
                continue;
            }
            if (ix >= nx) {
                continue;
            }
            row = grid[ix];

            for (y = -n; y <= n; y++) {
                dy = (float)y * step - *(float *)(c + 0xC);
                if (dy < 0.0f) {
                    dy = -dy;
                }
                iz = *(int *)(c + 0x8) + y;
                if (dx < dy) {
                    t = dy * 0.9375f + dx * 0.359375f;
                } else {
                    t = dx * 0.9375f + dy * 0.359375f;
                }
                t = t * inv;
                if (t <= 1.0f) {
                    if (iz < 0) {
                        continue;
                    }
                    if (iz >= ny) {
                        continue;
                    }

                    row[iz] += GetTableCos((t - 1.0f) * r * 512.0f) * 80.0f /
                               (*(float *)(c + 0x14) * 2.0f + 10.0f);
                }
            }
        }
    }
}

static inline void makeWaveGrid(char *w, float **grid, int ang)
{
    int i;
    int j;
    int nx = *(int *)(w + 0x34);
    int ny = *(int *)(w + 0x38);
    int nn = (int)*(float *)(w + 0x3C);
    float *row;

    for (i = 0; i < nx; i++) {
        row = grid[i];
        for (j = 0; j < ny; j++) {
            *row++ = GetTableSin((i * ny + j) * nn * 1000 + ang) * 0.05f;
        }
    }
}

extern char ZeroVector[];
extern const Blob16L D_0054DA70;
extern int D_0063A064;
extern int D_0063A068;
extern int buffer_ID;
extern int matrixptr;
extern float _InnerProduct(void *a, void *b);
extern void CopyVector(void *dst, void *src);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
extern void _AddVector(void *dst, void *a, void *b);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _InitCurrentMatrix(void);
extern void _NormalizeVector(void *dst, void *src);
extern void _ScaleVector(void *dst, void *src, float k);
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
extern void _SetCurrentMatrix(int m);
extern void _SubVector(void *dst, void *a, void *b);
extern void memset(void *dst, int c, int n);
extern void prim_UpdateMesh3D(void *mesh, int a1, int a2);

void updatePoolGeo(char *self)
{
    Blob16L org;
    float out[4];
    float nrm[4];
    float eye[4];
    char mat[0x40];
    float ref[4];
    float dir[4];
    float tmp[4];
    float pos[4];
    float sub[4];
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    char *mesh0 = *(char **)(w + 0x40);
    char *mesh1 = *(char **)(w + 0x44);
    float step = *(float *)(w + 0x3C);
    float **grid = *(float ***)(w + 0x4C);
    float sx;
    float sy;
    float *pc;
    float *pa;
    float *pb;
    float *pd;
    int ang;
    float *row;
    char *q;
    char *uv;
    char *q2;
    float *row2;
    char *uv2;
    char *qq;
    float h;
    float iw;
    float usc;
    float vsc;
    int k;
    int i;
    int j;

    org = D_0054DA70;
    sx = 1.0f / (float)D_0063A064;
    sy = 1.0f / (float)D_0063A068;

    pc = (float *)(matrixptr + 0x4C0);
    pa = (float *)(matrixptr + 0x400);
    pb = (float *)(matrixptr + 0x440);
    pd = (float *)(matrixptr + 0x480);

    CopyVector(pa, w);
    CopyVector(pb, &org);
    CopyVector(pd, ZeroVector);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    if (D_0028F4C0[5] == 0) {
        for (k = 0; k < 5; k++) {
            decayRipple(w + k * 24 + 0x50);
        }
    }

    ang = (short)*(unsigned short *)(w + 0xCC);

    makeWaveGrid(w, grid, ang);

    for (k = 0; k < 5; k++) {
        addRippleToGrid(w, w + k * 24 + 0x50, grid);
    }

    for (i = 0; i < *(int *)(w + 0x34); i++) {
        q = *(char **)(mesh1 + 0x6C) + i * *(int *)(w + 0x38) * 16;
        uv = *(char **)(mesh1 + 0x74) + i * *(int *)(w + 0x38) * 16;
        row = grid[i];

        pd[0] = (float)(((1 - *(int *)(w + 0x34)) >> 1) + i) * step;

        j = 0;

        for (; j < *(int *)(w + 0x38); j++, row++, q += 16, uv += 16) {
            h = *row;

            pd[1] = h * 30.0f;
            pd[2] = (float)(((1 - *(int *)(w + 0x38)) >> 1) + j) * step;
            _AddVector(q, pa, pd);

            _ApplyCurrentMatrix(out, q);
            iw = 1.0f / out[3];
            _ScaleVector(pc, out, iw);
            _SubVector(out, pc, pb);
            *(float *)(uv + 0x0) = out[0] * sx + 0.5f + h * 30.0f * iw;
            *(float *)(uv + 0x4) = out[1] * sy + 0.5f + h * 30.0f * iw;
        }
    }

    memset(nrm, 0, 16);
    nrm[1] = -1.0f;

    usc = 1.0f / (float)D_0063A064 * 0.8f;
    vsc = 1.0f / (float)D_0063A068 * 0.8f;

    MatrixDrive_SetTransposeMatrix(mat, (char *)(matrixptr + 0x80));
    CopyVector(eye, mat + 0x30);

    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < *(int *)(w + 0x34); i++) {
        q2 = *(char **)(mesh1 + 0x6C) + i * *(int *)(w + 0x38) * 16;
        qq = *(char **)(mesh0 + 0x6C) + i * *(int *)(w + 0x38) * 16;
        uv2 = *(char **)(mesh0 + 0x74) + i * *(int *)(w + 0x38) * 16;
        row2 = grid[i];

        for (j = 0; j < *(int *)(w + 0x38); j++, row2++, q2 += 16, uv2 += 16) {
            nrm[0] = nrm[2] = *row2 * 0.1f;

            CopyVector(qq, q2);

            _SubVector(dir, qq, eye);

            _NormalizeVector(dir, dir);
            _ScaleVector(tmp, nrm, _InnerProduct(dir, nrm) * -2.0f);

            _AddVectorXYZ(ref, dir, tmp);

            ref[1] = -ref[1];

            _ApplyCurrentMatrix(out, qq);
            _ScaleVectorXYZ(pc, out, 1.0f / out[3]);

            _AddVector(pos, qq, ref);
            qq += 16;
            _ApplyCurrentMatrix(pos, pos);
            _ScaleVectorXYZ(pos, pos, 1.0f / pos[3]);

            _SubVector(sub, pos, pc);

            _SubVector(out, pc, pb);

            *(float *)(uv2 + 0x0) = (out[0] + sub[0] * 1000.0f) * usc + 0.5f;
            *(float *)(uv2 + 0x4) = (out[1] + sub[1] * 1000.0f) * vsc + 0.5f;
        }
    }

    prim_UpdateMesh3D(mesh1, 9, buffer_ID);

    prim_UpdateMesh3D(mesh0, 9, buffer_ID);
}

extern char D_00290760[];
extern char D_002907A0[];
extern char D_002906E0[];
extern char D_00290720[];
extern int D_0028F4D4[];
extern int D_00639F94;
extern int D_0063A064;
extern int D_0063A068;
extern int D_0063A07C;
extern int D_0063A080;
extern int D_0063B148;
extern int matrixptr;
extern int stage_no;
extern void CopyMatrix(void *dst, void *src);
extern void DispMeshWire(int *rows, int nx, int ny);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixZ(short a);
extern void _MulMatrix(void *dst, void *a, void *b);
extern void _SetCurrentMatrix(int m);
extern void _UnitMatrix(void *m);
extern void copyToWork(int pri);
extern void gif_EndPacket(void);
extern void gif_SetZWrite(int a0);
extern void gif_StartPacketPri(int pri);
extern void gsb_SetVSMatrix(int a0, int a1, float f);
extern void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
extern void reg_RenderReflection(void *a0, int a1);

void dispPool(char *self)
{
    char m0[0x40];
    char m1[0x40];
    char m2[0x40];
    char m3[0x40];
    char m4[0x40];
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    gif_StartPacketPri(4);
    copyToWork(4);
    gif_SetGsReg(6, D_00639F28 | 0x20010000 | 0x600000000LL);

    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);

    gif_EndPacket();

    _SetCurrentMatrix(matrixptr + 0x100);

    prim_DispMesh3D(*(int *)(w + 0x44), D_002906E0, D_00290720, -1);

    CopyMatrix(*(char **)(*(char **)(self + 0x15C) + 0x874) + 0x40, D_00290760);
    CopyMatrix(*(char **)(*(char **)(self + 0x15C) + 0x874), D_002907A0);

    gif_StartPacketPri(4);
    flushWork(4);

    CopyMatrix(m0, (char *)(matrixptr + 0xC0));

    CopyMatrix(m1, (char *)(matrixptr + 0x1C0));
    CopyMatrix(m2, (char *)(matrixptr + 0x100));
    CopyMatrix(m3, (char *)(matrixptr + 0x200));
    CopyMatrix(m4, (char *)(matrixptr + 0x340));

    gsb_SetVSMatrix(0xCC, 0xCC, (float)D_00639F94);

    _MulMatrix((char *)(matrixptr + 0x100), (char *)(matrixptr + 0xC0), (char *)(matrixptr + 0x80));
    _MulMatrix((char *)(matrixptr + 0x200), (char *)(matrixptr + 0x1C0),
               (char *)(matrixptr + 0x80));

    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();

    _UnitMatrix(MatrixDrive_GetMatrix());
    CopyMatrix(*(char **)(*(char **)(self + 0x15C) + 0xC), MatrixDrive_GetMatrix());
    reg_RenderReflection(*(char **)(self + 0x15C), 4);

    if (*(int *)(w + 0xD0) != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(w + 0xD0) + 0x20);
        switch (stage_no) {
        case 101:
            MatrixDrive_RotMatrixZ((*(int *)(w + 0xD4) << 16) / 1600);
            break;
        case 15:
            MatrixDrive_RotMatrixZ(-(*(int *)(w + 0xD4) << 16) / 1600);
        }

        CopyMatrix(*(char **)(*(char **)(w + 0xD0) + 0xC), MatrixDrive_GetMatrix());

        reg_RenderReflection(*(char **)(w + 0xD0), 4);

        if (D_0028F4D4[0] == 0) {
            if (++*(int *)(w + 0xD4) > 1600) {
                *(int *)(w + 0xD4) = 0;
            }
        }
    }

    gif_StartPacketPri(4);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    gif_SetAlpha(0, 4, 0x80);

    CopyMatrix((char *)(matrixptr + 0xC0), m0);
    CopyMatrix((char *)(matrixptr + 0x1C0), m1);
    CopyMatrix((char *)(matrixptr + 0x340), m4);
    CopyMatrix((char *)(matrixptr + 0x100), m2);
    CopyMatrix((char *)(matrixptr + 0x200), m3);
    D_0063A07C = D_0063A064;
    D_0063A080 = D_0063A068;

    gif_SetGsReg(6, D_00639F28 | 0x20010000 | 0x600000000LL);

    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(1, 0, 0x40);

    gif_EndPacket();

    _SetCurrentMatrix(matrixptr + 0x100);

    prim_DispMesh3D(*(int *)(w + 0x40), D_002906E0, D_00290720, -1);

    gif_StartPacketPri(4);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(1, 0, 0x40);

    gif_EndPacket();

    if (D_0063B148 != 0) {
        DispMeshWire((int *)*(int *)(w + 0x48), *(int *)(w + 0x34), *(int *)(w + 0x38));
    }
}

extern int D_0028F4C0[];
extern void DispMultiBgaManagerWithKind(int kind, int a1, int a2);
extern void updatePoolGeo(char *self);
extern void dispPool(char *self);
extern void p2o_DispVU1(char *self);

void PoolDL(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    DispMultiBgaManagerWithKind(0x1F2, *(int *)(w + 0x2C), 10);
    DispMultiBgaManagerWithKind(0x1F3, *(int *)(w + 0x24), 2);
    if (D_0028F4C0[5] == 0) {
        *(short *)(w + 0xCC) =
            (short)((float)*(short *)(w + 0xCC) +
                    60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 2000.0f);
    }
    if (*(int *)(w + 0x30) != 0) {
        updatePoolGeo(self);
        dispPool(self);
    } else {
        p2o_DispVU1(self);
    }
}

extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern char *prim_InitMesh3D(int nx, int ny, int rot, long long col, unsigned int col2, int f58);
extern char D_0054DA60[];
extern int D_0063A438;

void InitLimitedPoolReflactionMesh(char *a0)
{
    int i;
    int j;

    *(char **)(a0 + 0x10) = prim_InitMesh3D(*(int *)(a0 + 0x4), *(int *)(a0 + 0x0), 1, 0x1C,
                                            *(unsigned int *)(a0 + 0x1C), 1);
    *(char ****)(a0 + 0x14) =
        (char ***)iosMallocDebug(D_0063A438, *(int *)(a0 + 0x0) * 4, D_0054DA60, 884);
    *(char **)(a0 + 0x18) = iosMallocDebug(D_0063A438, *(int *)(a0 + 0x0) * 4, D_0054DA60, 885);
    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        *(char **)(*(char **)(a0 + 0x18) + i * 4) =
            *(char **)(*(char **)(a0 + 0x10) + 0x6C) + i * *(int *)(a0 + 0x4) * 16;
        (*(char ****)(a0 + 0x14))[i] =
            (char **)iosMallocDebug(D_0063A438, *(int *)(a0 + 0x4) * 4, D_0054DA60, 890);
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            (*(char ****)(a0 + 0x14))[i][j] = 0;
        }
    }
}

void SetLayoutedPoolReflactionMesh(char *a0)
{
    Blob16L vec;
    float out[4];
    char *mesh;
    char *tmp;
    char *base;
    char *q;
    char *uv;
    float sx;
    float sy;
    float iw;
    float h;
    float t;
    int i;
    int j;

    if (D_0028F4D4[0] == 0) {
        for (i = 0; i < *(int *)(a0 + 0x0); i++) {
            (*(float ***)(a0 + 0x14))[i][0] -=
                ((*(float ***)(a0 + 0x14))[i][0] - random_signed() * 0.1f) * 0.8f;
            for (j = *(int *)(a0 + 0x4) - 1; j > 0; j--) {
                (*(float ***)(a0 + 0x14))[i][j] -= ((*(float ***)(a0 + 0x14))[i][j] -
                                                    (*(float ***)(a0 + 0x14))[i][j - 1] * 1.15f) *
                                                   0.8f;
            }
        }
    }

    mesh = *(char **)(a0 + 0x10);
    vec = D_0054DA70;
    sx = 1.0f / (float)D_0063A064;
    sy = 1.0f / (float)D_0063A068;
    tmp = (char *)(matrixptr + 0x4C0);
    base = (char *)(matrixptr + 0x440);

    CopyVector(base, &vec);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        q = *(char **)(mesh + 0x6C) + i * *(int *)(a0 + 0x4) * 16;
        uv = *(char **)(mesh + 0x74) + i * *(int *)(a0 + 0x4) * 16;
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            h = (*(float ***)(a0 + 0x14))[i][j];
            _ApplyCurrentMatrix(out, q);
            iw = 1.0f / out[3];
            _ScaleVector(tmp, out, iw);
            _SubVector(out, tmp, base);
            t = out[0] * sx + 0.5f + h * 50.0f * iw;
            *(float *)(uv + 0x0) = t < 0.0f ? 0.0f : t;
            t = out[1] * sy + 0.5f + h * 50.0f * iw;
            *(float *)(uv + 0x4) = 1.0f < t ? 1.0f : t;
            q += 16;
            uv += 16;
        }
    }
    prim_UpdateMesh3D(mesh, 9, buffer_ID);
}

extern int D_0028F4D4[];
extern const Blob16L D_0054DA70;
extern int D_0063A064;
extern int D_0063A068;
extern int buffer_ID;
extern int matrixptr;
extern void GetRootPosition(void *dst, char *self);
extern float GetPointDistance(void *a, void *b);
extern void _InterVectorXYZ(void *dst, void *p0, void *p1, float t);
extern void _InitCurrentMatrix(void);
extern void _SetCurrentMatrix(int m);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _ScaleVector(void *dst, void *src, float k);
extern void _SubVector(void *dst, void *a, void *b);
extern void prim_UpdateMesh3D(void *mesh, int a1, int a2);

void SetLimitedPoolReflactionMesh(char *a0, char *a1, char *a2)
{
    char *w = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    float pos[4];
    float v1[4];
    float v2[4];
    Blob16L vec;
    float out[4];
    char *mesh;
    char *tmp;
    char *base;
    char *q;
    char *uv;
    float dist;
    float dz;
    float sx;
    float sy;
    float iw;
    float h;
    int i;
    int j;

    if (D_0028F4D4[0] == 0) {
        for (i = 0; i < *(int *)(a0 + 0x0); i++) {
            for (j = 0; j < *(int *)(a0 + 0x4); j++) {
                (*(float ***)(a0 + 0x14))[i][j] -=
                    ((*(float ***)(a0 + 0x14))[i][j] - random_signed() * 0.3f) * 0.5f;
            }
        }
    }
    GetRootPosition(pos, a2);
    CopyVector(v1, pos);
    v1[1] = *(float *)(w + 4);
    CopyVector(v2, pos);
    v2[1] += *(float *)(*(char **)(a2 + 0x15C) + 0x270);

    pos[1] = (v1[1] + v2[1]) * 0.5f;
    _InterVectorXYZ(pos, pos, (char *)(matrixptr + 944),
                    (v1[1] - *(float *)(matrixptr + 948)) / (pos[1] - *(float *)(matrixptr + 948)));

    _InterVectorXYZ(v2, v2, (char *)(matrixptr + 944),
                    (v1[1] - *(float *)(matrixptr + 948)) / (v2[1] - *(float *)(matrixptr + 948)));

    dist = GetPointDistance(v1, v2) + 100.0f;

    pos[0] -= dist * 0.5f;
    pos[2] -= dist * 0.5f;

    mesh = *(char **)(a0 + 0x10);
    vec = D_0054DA70;
    sx = 1.0f / (float)D_0063A064;
    sy = 1.0f / (float)D_0063A068;
    tmp = (char *)(matrixptr + 0x4C0);
    base = (char *)(matrixptr + 0x440);

    dz = dist / (float)*(int *)(a0 + 0x0);

    CopyVector(base, &vec);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        q = *(char **)(mesh + 0x6C) + i * *(int *)(a0 + 0x4) * 16;
        uv = *(char **)(mesh + 0x74) + i * *(int *)(a0 + 0x4) * 16;
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            h = (*(float ***)(a0 + 0x14))[i][j];
            *(float *)(q + 0x0) = pos[0] + (float)i * dz;
            *(float *)(q + 0x4) = pos[1];
            *(float *)(q + 0x8) = pos[2] + (float)j * dz;
            *(float *)(q + 0xC) = 1.0f;
            _ApplyCurrentMatrix(out, q);
            iw = 1.0f / out[3];
            _ScaleVector(tmp, out, iw);
            _SubVector(out, tmp, base);
            *(float *)(uv + 0x0) = out[0] * sx + 0.5f + h * 50.0f * iw;
            *(float *)(uv + 0x4) = out[1] * sy + 0.5f + h * 50.0f * iw;
            q += 16;
            uv += 16;
        }
    }
    prim_UpdateMesh3D(mesh, 9, buffer_ID);
}

extern int D_0063A064;
extern int D_0063A068;
extern int D_0063B148;
extern char D_002906E0[];
extern char D_00290720[];
extern int matrixptr;
extern void gif_StartPacketPri(int pri);
extern void copyToWork(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_EndPacket(void);
extern void _SetCurrentMatrix(int m);
extern void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
extern void DispMeshWire(int *rows, int nx, int ny);

void DispLimitedPoolReflactionMesh(int *a0)
{
    gif_StartPacketPri(4);
    copyToWork(4);
    gif_SetGsReg(6, D_00639F28 | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(a0[4], D_002906E0, D_00290720, -1);
    if (D_0063B148 != 0) {
        DispMeshWire((int *)a0[6], a0[0], a0[1]);
    }
}

void PoolGeo(void) {}

float GetPoolGlobalHeight(char *a0)
{
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4);
}

float GetPoolGlobalHeightDetail(char *a0, float *pos)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    float inv;
    int ix;
    int iz;

    if (*(int *)(p + 0x30) != 0) {
        inv = 1.0f / *(float *)(p + 0x3C);
        ix = (int)((pos[0] - *(float *)(p + 0x0)) * inv + (float)(*(int *)(p + 0x34) >> 1));
        iz = (int)((pos[2] - *(float *)(p + 0x8)) * inv + (float)(*(int *)(p + 0x38) >> 1));
        ix = ix >= 0 ? (ix < *(int *)(p + 0x34) ? ix : *(int *)(p + 0x34) - 1) : 0;
        iz = iz >= 0 ? (iz < *(int *)(p + 0x38) ? iz : *(int *)(p + 0x38) - 1) : 0;
        return *(float *)(*(char **)(*(char **)(p + 0x4C) + ix * 4) + iz * 4) * 100.0f +
               *(float *)(p + 0x4);
    }
    return *(float *)(p + 0x4);
}

int CheckPoolHasGridMesh(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x30) != 0;
}

extern void InitLimitedPoolReflactionMesh(char *a0);
extern void _InterVectorXYZ(void *p0, void *p1, void *p2, float t);

void InitLayoutedPoolReflactionMesh(char *a0, char *a1)
{
    float v0[4];
    float v1[4];
    int i;
    int j;

    InitLimitedPoolReflactionMesh(a0);
    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        _InterVectorXYZ(v0, a1 + 0x0, a1 + 0x20, (float)i / (float)(*(int *)(a0 + 0x0) - 1));
        _InterVectorXYZ(v1, a1 + 0x10, a1 + 0x30, (float)i / (float)(*(int *)(a0 + 0x0) - 1));
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            _InterVectorXYZ(*(char **)(*(char **)(a0 + 0x10) + 0x6C) +
                                (i * *(int *)(a0 + 0x4) + j) * 0x10,
                            v0, v1, (float)j / (float)(*(int *)(a0 + 0x4) - 1));
            *(float *)(*(char **)(*(char **)(a0 + 0x10) + 0x6C) +
                       (i * *(int *)(a0 + 0x4) + j) * 0x10 + 0xC) = 1.0f;
        }
    }
}

int poolRideFunc(char **a0, char *a1)
{
    char *e = *(char **)(a1 + 0x15C);
    char *p = *(char **)(*(char **)(a0[0] + 0x15C) + 0x830);
    *(float *)(e + 0x644) = *(float *)(e + 0xA4) - *(float *)(p + 4);
    return 1;
}

float getWave(float t)
{
    t += 50.0f;
    t -= (float)(int)(t * 0.005f) * 200.0f;
    if (t < 100.0f) {
        return t * 0.01f - 0.5f;
    }
    return -(t - 100.0f) * 0.01f + 0.5f;
}
