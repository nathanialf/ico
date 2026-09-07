#include "common.h"

#include "ico/types.h"

typedef struct {
    char _0[0x10];
    int unk10;
    int unk14;
    short **unk18;
    short **unk1C;
    float *unk20;
} FuzioCtx;

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;
typedef union { unsigned char rgba[4]; long long ll[2]; } FcColor;

typedef int (*FcFunc)(void *a0, int a1);

extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void);
extern void debug_assertMessage(char *file, int line, char *mes);
extern void __assert(char *file, int line, char *expr);
extern char D_00553750[];
extern char D_00553768[];
extern char D_0063A820[];
extern int D_0063A818;
extern void *D_006C0CC0[];

void MakeCollisionDependGObjList(void)
{
    char *g;
    char *sub;
    /* ROM frame is 0x60 with only 0x30 of register saves, so the function
     * declares a ~0x30-byte buffer; the listing shows lines 534..579 of this
     * function emit no code at all (a compiled-out debug block), which is
     * where it was used.  Any size in 33..48 rounds to the same frame. */
    char buf[0x30];

    D_0063A818 = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next()) {
        sub = *(char **)(g + 0x15C);
        if (sub != 0 && *(int *)(sub + 0x70) != 0 && *(int *)(g + 0x16C) != 0 &&
            *(int *)(g + 0x4) == 1 && *(int *)(g + 0x8) >= 0 &&
            *(int *)(sub + 0x74) != 0) {
            D_006C0CC0[D_0063A818] = g;
            D_0063A818 = D_0063A818 + 1;
        }
    }
    if (D_0063A818 >= 0x100) {
        debug_assertMessage(D_00553750, 533, D_00553768);
        __assert(D_00553750, 533, D_0063A820);
    }
}
extern void CopyVector(void *a0, void *a1);
extern float GetDistanceFromPlane(void *a0, void *a1);
extern float GetPointDistance(void *a0, void *a1);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);

void GetReflectionElement(char *a0, float arg0, float arg1) {
    float buf0[4];
    float L10[4];
    float L20[4];
    float z;

    CopyVector(L10, a0 + 0xA0);
    *(int *) &L10[3] = 0;
    sceVu0SubVector(buf0, a0 + 0x10, a0);
    sceVu0ScaleVector(a0 + 0x30, L10, -GetDistanceFromPlane(L10, buf0));
    sceVu0AddVector(a0 + 0x40, buf0, a0 + 0x30);
    sceVu0ScaleVectorXYZ(a0 + 0x30, a0 + 0x30, arg1);
    sceVu0ScaleVectorXYZ(a0 + 0x40, a0 + 0x40, arg0);
    sceVu0AddVector(a0 + 0x60, a0 + 0x40, a0 + 0x30);
    {
        float *p20 = L20;
        z = GetPointDistance(a0 + 0x20, a0 + 0x10);
        sceVu0ScaleVector(p20, a0 + 0x60, z / GetPointDistance(a0, a0 + 0x10));
        sceVu0AddVector(a0 + 0x50, a0 + 0x20, p20);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", clip_wall_1);
extern void sceVu0CopyVector(int *dst, int *src);

typedef struct { float x, y, z, w; } FcVec4;

typedef struct {
    FcVec4 v[4];             /* 0x00: polygon vertices */
    float nx, ny, nz, npad;  /* 0x40: plane normal */
    float d;                 /* 0x50: plane distance */
    int nex;                 /* 0x54: vertices past the first three */
} FcFloorEnt;

static __inline__ int FloorPointInside(FcFloorEnt *e, float *pt)
{
    FcVec4 *v;
    FcVec4 *p2;
    float cp[4];
    float vx;
    int cross;
    int i;
    int n;

    cross = 0;
    n = e->nex + 2;
    v = e->v;
    p2 = v + n;
    for (i = 0; i <= n; i++) {
        vx = v->x;
        if ((vx < pt[0] && pt[0] <= p2->x) || (p2->x < pt[0] && pt[0] <= vx)) {
            cp[0] = pt[0];
            cp[2] = (v->z - p2->z) * (pt[0] - p2->x) / (vx - p2->x) + p2->z;
            if (pt[2] < cp[2]) {
                cross++;
            } else if (cp[0] == pt[0] && cp[2] == pt[2]) {
                return 1;
            }
        }
        p2 = v;
        v++;
    }

    return cross & 1;
}

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", clip_floor_1);
extern int game_pause;
extern int D_0063B13C;
extern int D_0063A064;
extern int D_0063A068;
extern int D_0063C210;
extern int D_0063C214;
extern int D_0063C218;
extern int D_0063C21C;
extern int D_0063C220;
extern int D_0063C224;
extern int D_0063C228;
extern int D_0063C22C;
extern int D_0063C230;
extern char D_005537A0[];
extern char D_005537B0[];
extern char D_005537C0[];
extern char D_005537D0[];
extern char D_006C0BC0[];
extern int sprintf(char *buf, char *fmt, ...);
extern int debug_Printf(int x, int y, unsigned int col, char *s, ...);

void DispCollisionPC(void)
{
    if (game_pause == 0) {
        return;
    }
    D_0063C220 = *(volatile int *) 0x10000000 - D_0063C220;
    sprintf(D_006C0BC0, D_005537A0, D_0063C210, D_0063C224);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2, 0xFFFFFF00, D_006C0BC0);
    }
    sprintf(D_006C0BC0, D_005537B0, D_0063C214, D_0063C228);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2 + 8, 0xFFFFFF00, D_006C0BC0);
    }
    sprintf(D_006C0BC0, D_005537C0, D_0063C218, D_0063C22C);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2 + 0x10, 0xFFFFFF00, D_006C0BC0);
    }
    sprintf(D_006C0BC0, D_005537D0, D_0063C21C, D_0063C230);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2 + 0x18, 0xFFFFFF00, D_006C0BC0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", makeCollisionBlockTable);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _Clip);
extern FcBlk8 D_0063A810;
extern void _Clip(char *a0, int a1);

void __ClipWall(char *a0, int a1) {
    *(int *)(a0 + 0xB0) = 0;
    *(int *)(a0 + 0x94) = 0;
    *(int *)(a0 + 0x88) = 0;
    *(FcBlk8 *)(a0 + 0x80) = D_0063A810;
    _Clip(a0, a1);
}
void __ClipFloor(void *a0, int a1) {
    *(int *)((char *)a0 + 0x94) = 0;
    *(FcBlk8 *)((char *)a0 + 0x8C) = D_0063A810;
    _Clip(a0, a1);
}
extern void gif_StartPacketPri(int a0);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void gif_EndPacket(void);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern void CopyMatrix(void *dst, void *src);
extern void UnitRotation(void *m);
extern int D_0063A848;
extern const FcColor D_0029D360;
extern const FcColor D_0029D370;
extern const FcColor D_0029D380;
extern const FcColor D_0029D390;
extern const FcColor D_0029D3A0;
extern const FcColor D_0029D3B0;
extern const FcColor D_0029D3C0;
extern const FcColor D_0029D3D0;

typedef struct {
    char _0[0x8];
    int nobj;           /* 0x8  */
    char *mtx;          /* 0xC  */
    char _10[0x60];
    char *coll;         /* 0x70 */
    char _74[0x4];
    int norot;          /* 0x78 */
    char _7C[0x4];
    int multi;          /* 0x80 */
} FcWallSub;

typedef struct {
    char _0[0x15C];
    FcWallSub *sub;     /* 0x15C */
} FcWallObj;

typedef struct {
    char _0[0x8];
    int nwall;          /* 0x8  */
    char _c[0x4];
    char *walls;        /* 0x10 */
} FcWallSet;

void DrawGObjWallCollision(char *gobj, int col)
{
    FcWallObj *g = (FcWallObj *) gobj;
    FcWallSet *cd;
    char *e;
    const FcColor *c0;
    const FcColor *c1;
    int n;
    int i;
    int j;
    int attr;

    D_0063A848 = D_0063A848 + 1;
    n = 1;
    if (g->sub->multi != 0) {
        n = g->sub->nobj;
    }
    cd = (FcWallSet *) g->sub->coll;
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    gif_SetAlpha(1, 5, 0);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < n; i++) {
        CopyMatrix(MatrixDrive_GetMatrix(), g->sub->mtx + (i << 6));
        if (g->sub->norot == 0) {
            UnitRotation(MatrixDrive_GetMatrix());
        }
        for (j = 0; j < cd->nwall; j++) {
            e = cd->walls + j * 0x50;
            c0 = &D_0029D360; c1 = &D_0029D3A0;
            attr = *(int *)(e + 0x48);
            if ((attr & 0xF0000000) != 0) {
                c0 = &D_0029D380; c1 = &D_0029D3C0;
                if ((attr & 0x10000000) != 0) {
                    c0 = &D_0029D390;
                    c1 = &D_0029D3D0;
                }
            } else if (attr != 0) {
                c0 = &D_0029D370; c1 = &D_0029D3B0;
            }
            DrawLineG(e, (void *) c0, e + 0x10, (void *) c0, col);
            DrawLineG(e + 0x10, (void *) c0, e + 0x30, (void *) c0, col);
            DrawLineG(e + 0x30, (void *) c0, e + 0x20, (void *) c0, col);
            DrawLineG(e + 0x20, (void *) c0, e, (void *) c0, col);
            DrawLineG(e, (void *) c1, e + 0x10, (void *) c1, -1);
            DrawLineG(e + 0x10, (void *) c1, e + 0x30, (void *) c1, -1);
            DrawLineG(e + 0x30, (void *) c1, e + 0x20, (void *) c1, -1);
            DrawLineG(e + 0x20, (void *) c1, e, (void *) c1, -1);
        }
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
extern void gif_StartPacketPri(int a0);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void gif_EndPacket(void);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern void CopyMatrix(void *dst, void *src);
extern void UnitRotation(void *m);
extern const FcColor D_00553820;

void DrawGObjFloorCollision(char *gobj, int col)
{
    FcColor c;
    int n;
    char *cd;
    char *e;
    int i;
    int j;

    n = 1;
    if (*(int *)(*(char **)(gobj + 0x15C) + 0x80) != 0) {
        n = *(int *)(*(char **)(gobj + 0x15C) + 0x8);
    }
    cd = *(char **)(*(char **)(gobj + 0x15C) + 0x70);
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    gif_SetAlpha(1, 5, 0);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < n; i++) {
        CopyMatrix(MatrixDrive_GetMatrix(),
                   *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (i << 6));
        if (*(int *)(*(char **)(gobj + 0x15C) + 0x78) == 0) {
            UnitRotation(MatrixDrive_GetMatrix());
        }
        for (j = 0; j < *(int *)(cd + 0xC); j++) {
            e = *(char **)(cd + 0x14) + j * 0x70;
            c = D_00553820;
            DrawLineG(e, &c, e + 0x10, &c, col);
            if (*(int *)(e + 0x54) == 0) {
                DrawLineG(e + 0x10, &c, e + 0x20, &c, col);
                DrawLineG(e + 0x20, &c, e, &c, col);
            } else {
                DrawLineG(e + 0x10, &c, e + 0x20, &c, col);
                DrawLineG(e + 0x20, &c, e + 0x30, &c, col);
                DrawLineG(e + 0x30, &c, e, &c, col);
            }
        }
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
extern char D_00553830[];
extern void debug_StdPrintfDummy();
extern int fptodp(float f);

void DBG_VECTOR(float *vec)
{
    return debug_StdPrintfDummy(D_00553830, fptodp(vec[0]),
                         fptodp(vec[1]), fptodp(vec[2]));
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetEdgeOfFloor);
extern void memset(void *p, int c, int n);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void MatrixDrive_TransMatrixV(void *v);
extern void MatrixDrive_TurnYObjectMatrixXZ(float x, float y, float z);
extern float FSqrt(float x);
extern float sceVu0InnerProduct(int a0, int a1);
extern void gif_SetZTest(int a0);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern const FcColor D_00553940;
extern const FcColor D_00553950;

void DrawCollisionRay(char *ray)
{
    FcColor c0;
    FcColor c1;
    float d[4];
    float p1[4];
    float p0[4];
    float v[4];
    float len;

    c0 = D_00553940;
    c1 = D_00553950;
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    memset(v, 0, 16);
    v[3] = 1.0f;
    gif_SetAlpha(1, 5, 128);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(ray, &c0, ray + 0x10, &c0, 0);
    DrawLineG(ray, &c1, ray + 0x10, &c1, -1);
    sceVu0SubVector(d, ray + 0x10, ray);
    MatrixDrive_TransMatrixV(ray + 0x10);
    MatrixDrive_TurnYObjectMatrixXZ(d[0], d[1], d[2]);
    len = FSqrt(sceVu0InnerProduct((int) d, (int) d));
    v[0] = len * 0.05f;
    v[1] = len * 0.3f;
    sceVu0ApplyMatrix(p0, MatrixDrive_GetMatrix(), v);
    v[0] = -len * 0.05f;
    sceVu0ApplyMatrix(p1, MatrixDrive_GetMatrix(), v);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(p0, &c0, ray + 0x10, &c0, 0);
    DrawLineG(p1, &c0, ray + 0x10, &c0, 0);
    DrawLineG(p0, &c1, ray + 0x10, &c1, -1);
    DrawLineG(p1, &c1, ray + 0x10, &c1, -1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(ray + 0x20);
    MatrixDrive_TurnYObjectMatrixXZ(d[0], d[1], d[2]);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
extern char D_00553960[];
extern char D_00553980[];
extern int frame_count;
extern int D_0063A818;
extern int D_0063C20C;
extern int D_0063C240;
extern void *D_006C0CC0[];
extern void *D_006C1140[];

void MakeExitAttributeIndex(void) {
    int i;
    char *entry;
    int j;
    int n;
    int *p70;
    void *obj;
    int slot;

    debug_StdPrintfDummy(D_00553960, frame_count);
    D_0063C240 = 0;
    i = 0xF;
    do {
        D_006C1140[i] = 0;
        i--;
    } while (i >= 0);
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            p70 = (int *)GOBJ_SUB(obj)->f_70;
            for (j = 0; j < p70[0xC / 4]; j++) {
                entry = (char *)p70[0x14 / 4] + j * 0x70;
                slot = *(int *)(entry + 0x60) & 0xF;
                if (slot != 0) {
                    if (D_006C1140[slot] == 0) {
                        debug_StdPrintfDummy(D_00553980, slot);
                        D_0063C240 = D_0063C240 + 1;
                        D_006C1140[slot] = entry;
                    }
                }
            }
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorByGObj);
extern int (*D_0063A840)(void *a0, int a1);

int ClipWallDebug(void *a0) {
    return D_0063A840(a0, 0);
}
int ClipWall(void *a0) {
    return D_0063A840(a0, 0x1);
}
int ClipWallR(void *a0) {
    return D_0063A840(a0, 0x2);
}
int ClipWallWaveForce(void *a0) {
    return D_0063A840(a0, 0x6);
}
int ClipWallFuchiHangWalkStop(void *a0) {
    return D_0063A840(a0, 0x7);
}
int ClipWallField(void *a0) {
    return D_0063A840(a0, 0x3);
}
int ClipWallEField(void *a0) {
    return D_0063A840(a0, 0x5);
}
int ClipWallBoxStop(void *a0) {
    return D_0063A840(a0, 0xA);
}
int ClipWallAdjustPos(void *a0) {
    return D_0063A840(a0, 0xB);
}
int ClipWallE(void *a0) {
    return D_0063A840(a0, 0x4);
}
extern int (*D_0063C23C)(void *obj);

void ClipWallCheckCB(void *a0, int a1) {
    D_0063C23C = (int (*)(void *)) a1;
    D_0063A840(a0, 8);
}
void ClipWallFieldCheckCB(void *a0, int a1) {
    D_0063C23C = (int (*)(void *)) a1;
    D_0063A840(a0, 9);
}
extern int (*D_0063A844)(void *a0, int a1);

int ClipFloor(void *a0) {
    return D_0063A844(a0, 0xC);
}
int ClipFloorE(void *a0) {
    return D_0063A844(a0, 0xD);
}
int ClipFloorR(void *a0) {
    return D_0063A844(a0, 0xE);
}
int ClipFloorIH(void *a0) {
    return D_0063A844(a0, 0xF);
}
void ClipFloorCheckCB(void *a0, int a1) {
    D_0063C23C = (int (*)(void *)) a1;
    D_0063A844(a0, 0x10);
}
extern void sceVu0CopyVector(int *dst, int *src);

void ClipCollision(int *self)
{
    int buf[4];
    int *p10 = self + 4;
    sceVu0CopyVector(buf, p10);
    D_0063A840((int)self, 1);
    sceVu0CopyVector(p10, self + 8);
    D_0063A844((int)self, 0xC);
    sceVu0CopyVector(p10, buf);
}
extern void __ClipWallWithDrawRay();
extern void __ClipFloorWithDrawRay();
int ChangeFieldCollisionDebugMode(int a0) {
    D_0063A840 = (int (*)(void *, int))__ClipWall;
    D_0063A844 = (int (*)(void *, int))__ClipFloor;
    if (a0 != 0) {
        D_0063A840 = (int (*)(void *, int))__ClipWallWithDrawRay;
        D_0063A844 = (int (*)(void *, int))__ClipFloorWithDrawRay;
    }
    return 0;
}
extern int file_LoadFile(int a0, int a1, int a2);

void LoadCollision(int *self, int a1)
{
    int new_var;
    int *p;
    file_LoadFile((int) self, a1, 0);
    p = (int *) self[0];
    new_var = 0x14 / 4;
    p[0x10 / 4] = (int) (((char *) p) + p[0x10 / 4]);
    p[0x14 / 4] = (int) (((char *) p) + p[new_var]);
}
extern void DrawGObjWallCollision(char *a0, int a1);
extern void DrawGObjFloorCollision(char *a0, int a1);
extern void gif_StartPacketPri(int a0);
extern void gif_SetZTest(int a0);
extern void gif_EndPacket(void);

void DrawCollision(int a0)
{
    int n = a0;
    void *obj;

    if (n > 0) {
        n = -1;
    }
    gif_StartPacketPri(11);
    gif_SetZTest(1);
    gif_EndPacket();
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            DrawGObjWallCollision(obj, n);
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            DrawGObjFloorCollision(obj, n);
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
}
extern float sceVu0InnerProduct(int a0, int a1);

int ClipPlane(int a0) {
    float *p = (float *)a0;
    char *q = (char *)(a0 + 0xA0);
    float t0, t1, d;

    sceVu0CopyVector((int *)(a0 + 0x20), (int *)(a0 + 0x10));
    t0 = sceVu0InnerProduct((int)q, a0 + 0x10) + *(float *)(q + 0xC);
    if (t0 >= 0.0f) {
        return 0;
    }
    t1 = sceVu0InnerProduct((int)q, a0) + *(float *)(q + 0xC);
    if (t1 < 0.0f) {
        if (t0 < 0.0f) {
            return 0;
        }
    }
    d = t1 - t0;
    p[8] = (p[4] * t1 - p[0] * t0) / d;
    p[9] = (p[5] * t1 - p[1] * t0) / d;
    p[10] = (p[6] * t1 - p[2] * t0) / d;
    return 1;
}
extern char D_005538C8[];
extern char D_005538F8[];
extern float GetTableCos(short a0);
extern float GetTableSin(short a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *buf);

void GetOrientOfWall(void *a0, void *a1, int *a2)
{
    float buf[4];
    int *var_19;
    void *obj = (void *)a2[0];

    if (a1 == 0) {
        buf[1] = 0.0f;
        buf[2] = 1.0f;
        var_19 = 0;
        buf[0] = 0.0f;
        debug_StdPrintfDummy(D_005538C8);
    } else {
        var_19 = (int *)1;
        buf[0] = -GetTableSin((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[1] = 0.0f;
        buf[2] = GetTableCos((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[3] = 1.0f;
    }
    if (var_19 == 0) {
        CopyVector((void *)a0, (void *)buf);
        *var_19 = 0;
        return;
    }
    *(int *)&buf[3] = 0;
    {
        int *temp_3 = (int *)*(int *)((char *)obj + 0x15C);
        if (temp_3 != 0 && *(int *)((char *)temp_3 + 0xC) != 0) {
            if (*(int *)((char *)temp_3 + 0x78) != 0) {
                int *p5 = (int *)a2[0];
                int idx = a2[1];
                int *o3 = (int *)*(int *)((char *)p5 + 0x15C);
                sceVu0ApplyMatrix(a0, (void *)(*(int *)((char *)o3 + 0xC) + (idx << 6)), buf);
                return;
            }
            CopyVector((void *)a0, (void *)buf);
            return;
        }
        debug_StdPrintfDummy(D_005538F8);
    }
}
void SetSimplePlane(float *self, float a, float b, float c, float d) {
    self[0] = a; self[1] = b; self[2] = c; self[3] = d;
}
int GetWallAttribute(int a0) {
    if (*(int *)(a0 + 0x88) == 0) return 0;
    return *(int *)(a0 + 0x98);
}
int GetFloorAttribute(int a0) {
    if (*(int *)(a0 + 0x94) == 0) return 0;
    return *(int *)(a0 + 0x98);
}
int CompareAttribute(unsigned int a, unsigned int b)
{
    int i;
    if ((a & b) == 0) return 0;
    for (i = 0; i < 8; i++) {
        unsigned int da = (a >> (i * 4)) & 0xF;
        unsigned int db = (b >> (i * 4)) & 0xF;
        if (da != 0 && db != 0 && da == db) return 1;
    }
    return 0;
}
typedef union { float f[4]; long long ll[2]; } FcVec;

static inline void getWallGlobalInfo(char *pts, void *nrm, char *w, void *m)
{
    FcVec vec = {{ GetTableSin(*(short *)(w + 0x44)), 0.0f,
                   GetTableCos(*(short *)(w + 0x44)), 0.0f }};
    int i;

    if (pts != 0) {
        char *src = w;
        char *dst = pts;
        for (i = 3; i >= 0; i--) {
            sceVu0ApplyMatrix(dst, m, src);
            src += 0x10;
            dst += 0x10;
        }
    }
    sceVu0ApplyMatrix(nrm, m, &vec);
}
/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
   GetWallGlobalInfo into DrawGObjWallCollision, so it is `inline` in the dev's TU;
   while this tail still has asm members the public body stays a plain definition
   at its ROM slot (before GetDistanceFromPlane) and the caller uses the static
   stand-in getWallGlobalInfo. Collapses to one `inline` definition at layout. */
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m)
{
    FcVec vec = {{ GetTableSin(*(short *)(w + 0x44)), 0.0f,
                   GetTableCos(*(short *)(w + 0x44)), 0.0f }};
    int i;

    if (pts != 0) {
        char *src = w;
        char *dst = pts;
        for (i = 3; i >= 0; i--) {
            sceVu0ApplyMatrix(dst, m, src);
            src += 0x10;
            dst += 0x10;
        }
    }
    sceVu0ApplyMatrix(nrm, m, &vec);
}
float GetDistanceFromPlane(void *a0, void *a1) {
    return sceVu0InnerProduct((int)a0, (int)a1) + ((float *)a0)[3];
}
float GetYDistanceFromPlane(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}
float GetYProjectionOfPlane(float *a0, float *a1) {
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}
extern int D_0063C210;
extern int D_0063C214;
extern int D_0063C218;
extern int D_0063C21C;
extern int D_0063C220;
extern int D_0063C224;
extern int D_0063C228;
extern int D_0063C22C;
extern int D_0063C230;

void ResetCollisionPC(void) {
    int tmp;
    D_0063C210 = 0;
    tmp = *(volatile int *)0x10000000;
    D_0063C214 = 0;
    D_0063C220 = tmp;

    D_0063C218 = 0;
    D_0063C21C = 0;
    D_0063C224 = 0;
    D_0063C228 = 0;
    D_0063C22C = 0;
    D_0063C230 = 0;
}

int PositionOfExit(int a0, int a1) {
    int v = (int) D_006C1140[a1 & 0xF];
    if (v != 0) { CopyVector(a0, v); return 0; }
    return 1;
}
void GetGlobalWallPlane(float *plane, int *r)
{
    FcVec pts[4];

    getWallGlobalInfo((char *)pts, plane, (char *)r[2],
                      (void *)((r[1] << 6) + *(int *)(*(int *)(r[0] + 0x15C) + 0xC)));
    plane[3] = -sceVu0InnerProduct((int)plane, (int)pts);
}
extern int D_0063C234;
extern FuzioCtx *D_0063C238;
extern short D_006C10C0[];
extern int clip_wall_1(void *a0, int a1, int a2, int a3);

int _clipWDebug(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                if (clip_wall_1(arg0, e, 0, 1) != 0) {
                    *(int *)((char *)arg0 + 0x88) = e;
                    ret = 1;
                    *(int *)((char *)arg0 + 0x80) = arg1;
                    *(int *)((char *)arg0 + 0x84) = arg2;
                }
                p++;
            }
        }
    }
    return ret;
}
extern int D_0063C234;
extern FuzioCtx *D_0063C238;
extern short D_006C10C0[];
extern int clip_wall_1(void *a0, int a1, int a2, int a3);

int _clipW(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (clip_wall_1(arg0, e, 0, 1) != 0) {
                            *(int *)((char *)arg0 + 0x88) = e;
                            ret = 1;
                            *(int *)((char *)arg0 + 0x80) = arg1;
                            *(int *)((char *)arg0 + 0x84) = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWE(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (arg1 != *(int *)((char *)arg0 + 0x74) ||
                            arg2 != *(int *)((char *)arg0 + 0x78) ||
                            e != *(int *)((char *)arg0 + 0x7C)) {
                            if (clip_wall_1(arg0, e, 0, 0) != 0) {
                                *(int *)((char *)arg0 + 0x88) = e;
                                ret = 1;
                                *(int *)((char *)arg0 + 0x80) = arg1;
                                *(int *)((char *)arg0 + 0x84) = arg2;
                            }
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWEField(void *arg0, int arg1, int arg2) {
    int found = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                if ((*(int *)(e + 0x48) & 0xF0000000) == 0) {
                    if (arg1 != *(int *)((char *)arg0 + 0x74) ||
                        arg2 != *(int *)((char *)arg0 + 0x78) ||
                        e != *(int *)((char *)arg0 + 0x7C)) {
                        if (clip_wall_1(arg0, e, 0, 0) != 0) {
                            *(int *)((char *)arg0 + 0x88) = e;
                            found = 1;
                            *(int *)((char *)arg0 + 0x80) = arg1;
                            *(int *)((char *)arg0 + 0x84) = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return found;
}
int _clipWR(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (clip_wall_1(arg0, e, 1, 1) != 0) {
                            *(int *)((char *)arg0 + 0x88) = e;
                            ret = 1;
                            *(int *)((char *)arg0 + 0x80) = arg1;
                            *(int *)((char *)arg0 + 0x84) = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWField(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                if ((*(int *)(e + 0x48) & 0xF0000000) == 0) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        *(int *)((char *)arg0 + 0x88) = e;
                        ret = 1;
                        *(int *)((char *)arg0 + 0x80) = arg1;
                        *(int *)((char *)arg0 + 0x84) = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWDitchHangWalkStop(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                if ((*(int *)(e + 0x48) & 0x30000000) != 0) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        *(int *)((char *)arg0 + 0x88) = e;
                        ret = 1;
                        *(int *)((char *)arg0 + 0x80) = arg1;
                        *(int *)((char *)arg0 + 0x84) = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWWaveForce(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                if ((*(int *)(e + 0x48) & 0xC0000000) == 0x40000000) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        *(int *)((char *)arg0 + 0x88) = e;
                        ret = 1;
                        *(int *)((char *)arg0 + 0x80) = arg1;
                        *(int *)((char *)arg0 + 0x84) = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWBoxStop(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0x70000000) == 0) {
                    if ((val & 0xF0000) != 0x10000 || (val & 0xC0000000) == 0x80000000) {
                        if (clip_wall_1(arg0, e, 0, 1) != 0) {
                            *(int *)((char *)arg0 + 0x88) = e;
                            ret = 1;
                            *(int *)((char *)arg0 + 0x80) = arg1;
                            *(int *)((char *)arg0 + 0x84) = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipWAdjustPos(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int) *p * 0x50;
                if ((*(int *)(e + 0x48) & 0xC0000000) == 0xC0000000) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        *(int *)((char *)arg0 + 0x88) = e;
                        ret = 1;
                        *(int *)((char *)arg0 + 0x80) = arg1;
                        *(int *)((char *)arg0 + 0x84) = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
extern int clip_floor_1(void *a0, int a1, int a2);

int _clipF(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int) *p * 0x70;
                if (clip_floor_1(arg0, e, 0) != 0) {
                    *(int *)((char *)arg0 + 0x94) = e;
                    ret = 1;
                    *(int *)((char *)arg0 + 0x8C) = arg1;
                    *(int *)((char *)arg0 + 0x90) = arg2;
                    *(int *)((char *)arg0 + 0x88) = 0;
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipFE(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int) *p * 0x70;
                if (arg1 != *(int *)((char *)arg0 + 0x74) ||
                    arg2 != *(int *)((char *)arg0 + 0x78) ||
                    e != *(int *)((char *)arg0 + 0x7C)) {
                    if (clip_floor_1(arg0, e, 0) != 0) {
                        *(int *)((char *)arg0 + 0x94) = e;
                        ret = 1;
                        *(int *)((char *)arg0 + 0x8C) = arg1;
                        *(int *)((char *)arg0 + 0x90) = arg2;
                        *(int *)((char *)arg0 + 0x88) = 0;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipFIH(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int) *p * 0x70;
                if ((*(int *)(e + 0x60) & 0xF0000) != 0x20000) {
                    if (clip_floor_1(arg0, e, 0) != 0) {
                        *(int *)((char *)arg0 + 0x94) = e;
                        ret = 1;
                        *(int *)((char *)arg0 + 0x8C) = arg1;
                        *(int *)((char *)arg0 + 0x90) = arg2;
                        *(int *)((char *)arg0 + 0x88) = 0;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}
int _clipFR(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int) *p * 0x70;
                if (clip_floor_1(arg0, e, 1) != 0) {
                    *(int *)((char *)arg0 + 0x94) = e;
                    ret = 1;
                    *(int *)((char *)arg0 + 0x8C) = arg1;
                    *(int *)((char *)arg0 + 0x90) = arg2;
                    *(int *)((char *)arg0 + 0x88) = 0;
                }
                p++;
            }
        }
    }
    return ret;
}
extern void gif_StartPacketPri(int a0);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void gif_EndPacket(void);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);
extern const FcColor D_005537E0;
extern const FcColor D_005537F0;

void __ClipWallWithDrawRay(char *w, int a1)
{
    FcColor c0;
    FcColor c1;

    __ClipWall(w, a1);
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    c0 = D_005537E0;
    c1 = D_005537F0;
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(w, &c0, w + 0x10, &c0, 0);
    DrawLineG(w, &c1, w + 0x10, &c1, -1);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
extern const FcColor D_00553800;
extern const FcColor D_00553810;

void __ClipFloorWithDrawRay(char *w, int a1)
{
    FcColor c0;
    FcColor c1;

    __ClipFloor(w, a1);
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    c0 = D_00553800;
    c1 = D_00553810;
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(w, &c0, w + 0x10, &c0, 0);
    DrawLineG(w, &c1, w + 0x10, &c1, -1);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
extern int collision_pick;

void ClipWallRD(void) {
    collision_pick = 1;
    /* Cast away the (int) prototype so gcc doesn't emit `daddu $a0,$0,$0`
     * to set up an arg the original call didn't pass. The implementation
     * happens to read $a0 but the original cross-TU caller didn't bother
     * to clear it. */
    ((void (*)(void)) ClipWall)();
    collision_pick = 0;
}

int ClipWallVector(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 4, a1);
    D_0063A840(buf, 1);
    return buf[34];
}
void MapCollisionData(void *a0) {
    int *p = (int *)a0;
    p[4] = (int)a0 + p[4];
    p[5] = (int)a0 + p[5];
}
