#include "common.h"

#include "vu0.h"

#include "sugiCommon.h"

typedef struct {
    float v[4];
    unsigned short a;
    unsigned short b;
} ClothBuf;

extern void CopyVector(void *dst, void *src);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", TestDispChainAnimation);
void GetChainExWeightGlobalPos(int a0, int a1, int a2)
{
    CopyVector(a0, a1 + a2 * 0x50 + 0x30);
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bindExWeight);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bind2);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", calc2);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainAnimation);
extern void debug_StdPrintfDummy();
extern char D_0061F240[];
extern char D_0061F258[];
extern char D_0028FEF0[];

int SetChainExtendedWeight(int *a0, int idx, float w0, float w1)
{
    int i;
    char *ex;

    if (a0[3] >= 5) {
        debug_StdPrintfDummy(D_0061F240);
        return -1;
    }
    for (i = 0; i < 5; i++) {
        if (*(float *)((char *)a0 + 0x10 + i * 0x50) < 0.0f) {
            *(float *)((char *)a0 + i * 0x50 + 0x10) = (float)idx - 1e-6f;
            *(float *)((char *)a0 + i * 0x50 + 0x50) = w0;
            *(float *)((char *)a0 + i * 0x50 + 0x54) = w1;
            ex = (char *)a0 + 0x10 + i * 0x50;
            CopyVector(ex + 0x30, D_0028FEF0);
            CopyVector(ex + 0x10, (char *)a0[0] + idx * 16);
            CopyVector(ex + 0x20, (char *)a0[0] + idx * 16);
            *(float *)((char *)a0 + i * 0x50 + 0x34) = *(float *)((char *)a0 + i * 0x50 + 0x34) + w0;
            a0[3] = a0[3] + 1;
            return i;
        }
    }
    debug_StdPrintfDummy(D_0061F258);
    return -1;
}
ASM_LIT4_SLOT(D_00639478, 0.8f);
ASM_LIT4_SLOT(D_0063947C, 0.98f);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetClothAnimation);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", yTension);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", xTension);
ASM_LIT4_SLOT(D_00639480, 0.98f);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetClothAnimationFix4Points);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", clipCylinderCollision);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitChains);
typedef struct {
    long long q[89];
} TexBlob;

typedef struct {
    int num;
    int **rec;
} ClothSet;

extern char *iosMallocDebug(int heap, int size, char *file, int line);
extern char *prim_InitMesh3D(int a0, int a1, int a2, int a3, unsigned int a4, int a5);
extern int tex_GetTextureNo(void *a0);
extern void *tex_GetTextureData(int a0);
extern void *memset(void *a0, int a1, int a2);
extern int D_0063A438;
extern char D_0061F270[];
extern char D_0061F288[];

ClothSet *InitClothes(int cfg)
{
    ClothSet *r;
    int i = 0;
    int m;
    int q;
    float aa[4];
    float bb[4];

    r = (ClothSet *)iosMallocDebug(D_0063A438, 8, D_0061F270, 1235);
    debug_StdPrintfDummy(D_0061F288);
    while (*(int *)(i * 0x1C + cfg) != -1) {
        i++;
    }
    r->num = i;
    r->rec = (int **)iosMallocDebug(D_0063A438, i * 0x2E0, D_0061F270, 1240);
    for (i = 0; i < r->num; i++) {
        if (*(int *)(i * 0x1C + cfg + 0x14) != 0) {
            *(char **)(i * 0x2E0 + (int)r->rec) =
                prim_InitMesh3D(*(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x5C,
                                0x80808080, 1);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 1;
            *(TexBlob *)(i * 0x2E0 + (int)r->rec + 0x18) =
                *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(*(void **)(i * 0x1C + cfg + 0x14)));
        } else {
            *(char **)(i * 0x2E0 + (int)r->rec) =
                prim_InitMesh3D(*(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x4C,
                                0xFFFFFF80, 1);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 0;
        }
        *(char **)(i * 0x2E0 + (int)r->rec + 4) =
            iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg) * 4, D_0061F270, 1268);
        *(char **)(i * 0x2E0 + (int)r->rec + 8) =
            iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg) * 4, D_0061F270, 1269);
        *(char **)(i * 0x2E0 + (int)r->rec + 0xC) =
            iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg) * 4, D_0061F270, 1270);
        for (m = 0; m < *(int *)(i * 0x1C + cfg); m++) {
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) =
                (char *)(*(int *)(*(char **)(i * 0x2E0 + (int)r->rec) + 0x6C) +
                         m * *(int *)(i * 0x1C + cfg + 8) * 16);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) =
                iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg + 8) * 16, D_0061F270, 1275);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC)) =
                iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg + 8) * 4, D_0061F270, 1276);
            memset(aa, 0, 16);
            aa[3] = 1.0f;
            memset(bb, 0, 16);
            for (q = 0; q < *(int *)(i * 0x1C + cfg + 8); q++) {
                CopyVector(*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) + q * 16, aa);
                CopyVector(*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) + q * 16, bb);
                *(int *)(q * 4 + (int)*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC))) = -1;
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

    r = (ClothSet *)iosMallocDebug(D_0063A438, 8, D_0061F270, 1296);
    debug_StdPrintfDummy(D_0061F288);
    while (*(int *)(i * 0x1C + cfg) != -1) {
        i++;
    }
    r->num = i;
    r->rec = (int **)iosMallocDebug(D_0063A438, i * 0x2E0, D_0061F270, 1301);
    for (i = 0; i < r->num; i++) {
        if (*(int *)(i * 0x1C + cfg + 0x14) != 0) {
            *(char **)(i * 0x2E0 + (int)r->rec) =
                prim_InitMesh3D(*(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x5C,
                                0x80808080, 0);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 1;
            *(TexBlob *)(i * 0x2E0 + (int)r->rec + 0x18) =
                *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(*(void **)(i * 0x1C + cfg + 0x14)));
        } else {
            *(char **)(i * 0x2E0 + (int)r->rec) =
                prim_InitMesh3D(*(int *)(i * 0x1C + cfg + 8), *(int *)(i * 0x1C + cfg), 1, 0x4C,
                                0xFFFFFF80, 0);
            *(int *)(i * 0x2E0 + (int)r->rec + 0x10) = 0;
        }
        *(char **)(i * 0x2E0 + (int)r->rec + 4) =
            iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg) * 4, D_0061F270, 1329);
        *(char **)(i * 0x2E0 + (int)r->rec + 8) =
            iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg) * 4, D_0061F270, 1330);
        *(char **)(i * 0x2E0 + (int)r->rec + 0xC) =
            iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg) * 4, D_0061F270, 1331);
        for (m = 0; m < *(int *)(i * 0x1C + cfg); m++) {
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) =
                (char *)(*(int *)(*(char **)(i * 0x2E0 + (int)r->rec) + 0x6C) +
                         m * *(int *)(i * 0x1C + cfg + 8) * 16);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) =
                iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg + 8) * 16, D_0061F270, 1336);
            *(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC)) =
                iosMallocDebug(D_0063A438, *(int *)(i * 0x1C + cfg + 8) * 4, D_0061F270, 1337);
            memset(aa, 0, 16);
            aa[3] = 1.0f;
            memset(bb, 0, 16);
            for (q = 0; q < *(int *)(i * 0x1C + cfg + 8); q++) {
                CopyVector(*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 4)) + q * 16, aa);
                CopyVector(*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 8)) + q * 16, bb);
                *(int *)(q * 4 + (int)*(char **)(m * 4 + (int)*(char **)(i * 0x2E0 + (int)r->rec + 0xC))) = -1;
            }
        }
    }
    return r;
}
extern int buffer_ID;
extern int matrixptr;
extern void _SetCurrentMatrix(int a0);
extern void dl_SetDLPriority(int a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetGsReg(int a0, int a1);
extern void gif_StartPacketPri(int a0);
extern void p2o_SetDefaultEnviroment(void);
extern void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
extern void prim_UpdateMesh3D(int a0, int a1, int a2);
extern int tex_GetTextureNo(void *a0);

void DispClothMesh(int *a0, void *a1, void *a2) {
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
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);
extern char D_004E6F10[];
extern char D_004E6F20[];
extern char D_004E6F30[];

void DispMeshWire(int *rows, int nx, int ny)
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
                DrawLineG((char *)rows[i] + j * 16, D_004E6F30,
                          (char *)rows[i] + (j * 16 - 16), D_004E6F30, 0);
            } else {
                DrawLineG((char *)rows[i] + j * 16, D_004E6F20,
                          (char *)rows[i] + (j * 16 - 16), D_004E6F20, 0);
            }
        }
    }
    for (j = 0; j < ny; j++) {
        if (j == ny - 1) {
            for (i = 1; i < nx; i++) {
                DrawLineG((char *)rows[i] + j * 16, D_004E6F20,
                          (char *)rows[i - 1] + j * 16, D_004E6F20, 0);
            }
        } else {
            for (i = 1; i < nx; i++) {
                DrawLineG((char *)rows[i] + j * 16, D_004E6F20,
                          (char *)rows[i - 1] + j * 16, D_004E6F10, 0);
            }
        }
    }
    gif_EndPacket();
}
extern int D_0063B1D8;

void DispCloth4D(int *a0, void *a1, void *a2) {
    int t;
    int *m;
    dl_SetDLPriority(1);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(a0[1], 3, buffer_ID);
    if (((int *)a0[184])[8] != 0) {
        t = tex_GetTextureNo((char *)a0 + 0x18);
    } else {
        t = -1;
    }
    gif_StartPacketPri(1);
    gif_SetAlpha(1, 7, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(a0[1], a1, a2, t);
    if (D_0063B1D8 != 0) {
        m = (int *)a0[184];
        DispMeshWire((int *)a0[2], m[0], m[1]);
    }
}
void DispCloth4DWithAdd(int *a0, void *a1, void *a2) {
    int t;
    int *m;
    dl_SetDLPriority(1);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(a0[1], 3, buffer_ID);
    if (((int *)a0[184])[8] != 0) {
        t = tex_GetTextureNo((char *)a0 + 0x18);
    } else {
        t = -1;
    }
    gif_StartPacketPri(1);
    gif_SetAlpha(1, 5, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(a0[1], a1, a2, t);
    if (D_0063B1D8 != 0) {
        m = (int *)a0[184];
        DispMeshWire((int *)a0[2], m[0], m[1]);
    }
}
ASM_LIT4_SLOT(D_00639484, 2.44140625e-05f);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D_preProcess);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", proc);
ASM_LIT4_SLOT(D_00639488, 0.2f);
ASM_LIT4_SLOT(D_0063948C, 0.2f);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D);
extern void CopyMatrix(void *dst, void *src);
extern void SubVectorXYZ(void *a0, void *a1, void *a2);
extern void *memset(void *a0, int a1, int a2);
extern void sceVu0AddVector(void *dst, void *a, void *b);

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
                CopyVector((char *)rowsC[i] + j * 16, D_0028FEF0);
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
extern void getCloth4D_preProcess(void *a0, int tight, void *a6, void *a7, float x, float y, float z, float w);
extern void getCloth4D(void *a0, int **rows);
extern char D_0055FE58[];
extern void _ScaleVector(void *dst, void *src, float k);
extern void _SubVectorXYZ(void *dst, void *a, void *b);

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
    char *ent;

    for (i = 0; i < nx; i++) {
        rows[i] = data[i];
        for (j = 0; j < ny; j++) {
            rows[i][j] = -1;
        }
    }
    getCloth4D_preProcess(a0, tight, a6, a7, x, y, z, w);
    getCloth4D(a0, rows);
    obj = (int *)*(int *)((char *)a0[0] + 0x15C);
    ent = D_0055FE58 + obj[296] * 0x194;
    if ((*(unsigned int *)(ent + 0x18C) >> 21) & 1) {
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
extern char D_002907E0[];

void GetCloth4D(void *a0, float x, float y) {
    _getCloth4D(a0, x, y, 1.0f, 1.0f, 0, D_002907E0, D_002907E0);
}
void GetCloth4DWithDetail(void *a0, float x, float y, float z, float w) {
    _getCloth4D(a0, x, y, z, w, 0, D_002907E0, D_002907E0);
}
void GetCloth4DWithTight(void *a0, void *a1, void *a2, float x, float y, float z, float w) {
    _getCloth4D(a0, x, y, z, w, 1, a1, a2);
}
typedef struct {
    long long q[8];
} Blob64;

typedef struct {
    char pad[0x6C];
    char *p6C;
    char *p70;
    char *p74;
} Mesh3D;

typedef struct {
    int gobj;
    Mesh3D *mesh;
    char **p8;
    char **pC;
    char **p10;
    int pad14;
    TexBlob tex;
    int cfg;
    int n2E4;
    char **p2E8;
    char *p2EC;
    char *p2F0;
    int f2F4;
    int f2F8;
} Cloth4D;

typedef struct {
    int nx;
    int ny;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    void *tex;
    char *p24;
} Cloth4DCfg;

extern void prim_UpdateMesh3D(int a0, int a1, int a2);
extern int buffer_ID;
extern void sceVu0UnitMatrix(void *m);
extern int GetSkeltonFocusNode(int a0, int a1);
extern char D_0028FF00[];
extern char D_0028FEF0[];

Cloth4D *InitCloth4D(int a0, Cloth4DCfg *cfg, int tbl)
{
    Cloth4D *r;
    int i;
    int j;
    float sc;

    r = (Cloth4D *)iosMallocDebug(D_0063A438, 0x300, D_0061F270, 2183);
    r->gobj = a0;
    r->cfg = (int)cfg;
    r->f2F4 = 0;
    if (cfg->tex != 0) {
        r->mesh = (Mesh3D *)prim_InitMesh3D(cfg->ny, cfg->nx, 1, 0x5C, 0x80808080, 1);
        r->tex = *(TexBlob *)tex_GetTextureData(tex_GetTextureNo(cfg->tex));
    } else {
        r->mesh = (Mesh3D *)prim_InitMesh3D(cfg->ny, cfg->nx, 1, 0x4C, 0xFFFFFF80, 1);
    }
    r->p8 = (char **)iosMallocDebug(D_0063A438, cfg->nx * 4, D_0061F270, 2218);
    r->pC = (char **)iosMallocDebug(D_0063A438, cfg->nx * 4, D_0061F270, 2219);
    r->p10 = (char **)iosMallocDebug(D_0063A438, cfg->nx * 4, D_0061F270, 2220);
    for (i = 0; i < cfg->nx; i++) {
        *(char **)(i * 4 + (int)r->p8) =
            (char *)((int)r->mesh->p6C + i * cfg->ny * 16);
        *(char **)(i * 4 + (int)r->pC) =
            iosMallocDebug(D_0063A438, cfg->ny * 16, D_0061F270, 2224);
        *(char **)(i * 4 + (int)r->p10) =
            (char *)((int)r->mesh->p70 + i * cfg->ny * 16);
        for (j = 0; j < cfg->ny; j++) {
            CopyVector(*(char **)(i * 4 + (int)r->p8) + j * 16, D_0028FF00);
            CopyVector(*(char **)(i * 4 + (int)r->pC) + j * 16, D_0028FEF0);
            *(float *)((i * cfg->ny + j) * 16 + (int)r->mesh->p74) =
                *(float *)(j * 8 + *(int *)(i * 0x60 + (int)cfg->p24 + 0x40));
            *(float *)((i * cfg->ny + j) * 16 + (int)r->mesh->p74 + 4) =
                1.0f - *(float *)(j * 8 + *(int *)(i * 0x60 + (int)cfg->p24 + 0x40) + 4);
        }
    }
    prim_UpdateMesh3D((int)r->mesh, 8, buffer_ID);
    prim_UpdateMesh3D((int)r->mesh, 8, (buffer_ID + 1) & 1);
    if (tbl != 0) {
        i = 0;
        sc = *(float *)(*(int *)(*(int *)(r->gobj + 0x15C) + 0x870) + 0x20);
        while (*(int *)(i * 0x40 + tbl) != -1) {
            i++;
        }
        r->n2E4 = i;
        r->p2F0 = iosMallocDebug(D_0063A438, i * 0x40, D_0061F270, 2253);
        r->p2EC = iosMallocDebug(D_0063A438, r->n2E4 * 0x40, D_0061F270, 2254);
        r->p2E8 = (char **)iosMallocDebug(D_0063A438, r->n2E4 * 4, D_0061F270, 2255);
        for (i = 0; *(int *)(i * 0x40 + tbl) != -1; i++) {
            *(Blob64 *)(i * 0x40 + (int)r->p2F0) = *(Blob64 *)(i * 0x40 + tbl);
            *(float *)(i * 0x40 + (int)r->p2F0 + 0xC) =
                *(float *)(i * 0x40 + (int)r->p2F0 + 0xC) * sc;
            *(float *)(i * 0x40 + (int)r->p2F0 + 8) =
                *(float *)(i * 0x40 + (int)r->p2F0 + 8) * sc;
            *(float *)(i * 0x40 + (int)r->p2F0 + 4) =
                *(float *)(i * 0x40 + (int)r->p2F0 + 4) * sc;
            *(float *)(i * 0x40 + (int)r->p2F0 + 0x34) =
                1.0f / (*(float *)(i * 0x40 + (int)r->p2F0 + 0xC) +
                        *(float *)(i * 0x40 + (int)r->p2F0 + 0xC));
            sceVu0UnitMatrix(r->p2EC + i * 0x40);
            *(int *)(i * 4 + (int)r->p2E8) =
                GetSkeltonFocusNode(a0, *(int *)(i * 0x40 + tbl + 0x10));
        }
        r->f2F8 = 1;
    } else {
        r->n2E4 = 0;
        r->f2F8 = 0;
    }
    return r;
}
extern void MatrixDrive_GetTurnYAngleXZ(unsigned short *o1, unsigned short *o2, float x, float y, float z);
extern void RotQuaternionX(void *a0, int a1);
extern void RotQuaternionZ(void *a0, int a1);
extern void SetIdentityQuaternion(void *a0);
extern void SubVectorXYZ(void *a0, void *a1, void *a2);

void GetChainNodeGlobalQuaternion(void *a0, int *a1, int count) {
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
extern char D_0028FEF0[];

void InitChainVelocity(int *a0)
{
    int i;
    int j;
    int k;

    for (i = 0; i < a0[1]; i++) {
        int cnt = *(int *)((char *)a0[0] + i * 0x50);
        for (j = 0; j < cnt; j++) {
            CopyVector(*(char **)((char *)a0[2] + i * 0x1A0 + 4) + j * 16, D_0028FEF0);
        }
        for (k = 0; k < 5; k++) {
            char *w = (char *)a0[2] + i * 0x1A0 + 0x10 + k * 0x50;
            CopyVector(w + 0x30, D_0028FEF0);
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
extern void CopyVector(void *a0, void *a1);
extern char D_0028FEF0[];

void ResetClothAnimation(int *a0, int *a1, int *a2) {
    int outer = a2[0];
    int inner = a2[2];
    int i = 0;
    int j;

    if (outer > 0) {
        do {
            for (j = 1; j < inner; j++) {
                char *p = (char *)a0[i];
                CopyVector(p + j * 16, p);
                CopyVector((char *)a1[i] + j * 16, D_0028FEF0);
            }
            i++;
        } while (i < outer);
    }
}
void GetChainExWeightGlobalQuaternion(int a0, int a1, int i, int j)
{
    ClothBuf buf;
    SetIdentityQuaternion(a0);
    SubVectorXYZ(&buf, j * 0x50 + a1 + 0x30, i * 0x50 + a1 + 0x20);
    buf.v[1] = buf.v[1] + 100.0f;
    MatrixDrive_GetTurnYAngleXZ(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
    RotQuaternionX(a0, (short)-buf.a);
    RotQuaternionZ(a0, (short)-buf.b);
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
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 4);
    VU0_NOREORDER_END();
    VU0_REG("vrsqrt Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void getXZLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void getXZInvLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void getXZLengthSquare(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_QMFC2_NI(v0, 4);
    VU0_MTC1(v0, 0);
}
void subAndGetInvLength(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyzw, 4, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void scaleAndAddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 5, 5, 6, x);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
}
void scaleVectorXZ(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 5);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, a0);
}
void tensionMoveNoReduce(void *a0, void *a1, void *a2, float f12)
{
    int sp_buf[4];
    register float q __asm__("$f0");
    register float scaled __asm__("$f12") = f12;
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, sp);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_REG("mul.s $f12, $f12, $f0");
    VU0_NOREORDER_END();

    VU0_LSV(lqc2, 4, 0x0, a2);
    VU0_LSV(lqc2, 5, 0x0, sp);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_REG("vmulx.xyz $vf5, $vf5, $vf6x");
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
}
void tensionMove(void *a0, void *a1, void *a2, float f12, float f13)
{
    int sp_buf[4];
    float inv;
    float scale;
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, sp);
    VU0_WAIT();
    __asm__ __volatile__(
        ".set noreorder\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, %0\n"
        ".set reorder\n"
        : "=f"(inv) :: "$2");
    if (inv < f13) {
        scale = f12 * inv;
        VU0_LSV(lqc2, 4, 0x0, a2);
        VU0_LSV(lqc2, 5, 0x0, sp);
        __asm__ __volatile__(
            ".set noreorder\n"
            "mfc1 $8, %0\n"
            "qmtc2.ni $8, $vf6\n"
            ".set reorder\n"
            :: "f"(scale) : "$8");
        VU0_REG("vmulx.xyz $vf5, $vf5, $vf6x");
        VU0_V3OP(vadd.xyz, 4, 4, 5);
        VU0_LSV(sqc2, 4, 0x0, a0);
    }
}
extern void AddVectorXYZ(void *dst, void *a, void *b);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float s);
extern void sceVu0SubVector(void *dst, void *a, void *b);

void getCrossPoint(void *out, void *seg, void *plane)
{
    float v[4];
    float d0 = plane_distance(seg, plane);
    float d1 = -plane_distance((char *)seg + 0x10, plane);

    sceVu0SubVector(v, (char *)seg + 0x10, seg);
    sceVu0ScaleVectorXYZ(v, v, d0 / (d0 + d1));
    AddVectorXYZ(out, seg, v);
}
int checkOverThePlane(void *a0, void *a1)
{
    if (0.0f < plane_distance(a0, a1)) return 1;
    return 0;
}
int checkFrontAcross(void *a0, void *a1)
{
    if (0.0f <= plane_distance(a0, a1)) {
        if (plane_distance((char *)a0 + 0x10, a1) < 0.0f) return 1;
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
extern void _ScaleVector(void *dst, void *src, float k);
extern void _SubVectorXYZ(void *dst, void *a, void *b);

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
