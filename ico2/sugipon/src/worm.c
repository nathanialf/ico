#include "common.h"

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];
extern int D_00639EA4;
extern void GetRootPosition(void *a0, int a1);
extern int GetSkeltonFocusNode(int a0, int a1);
void GetWormCaptureVector(void *out, void *act, void *node, float scale);
extern void SetDirectRootPosition(int a0, void *a1);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern float VectorLengthSquare(void *v);
extern float _Sqrt(float x);
extern float _GetLength(void *a, void *b);
extern float VectorLength(void *v);
extern float _GetRandom(void);
extern char *iosMallocDebug(void *heap, int size, char *file, int line);
extern void iosFree(int p);
extern void *InitChains(char *a0);
extern void *D_0063A438;
extern void *D_0063A44C;
extern int D_0063BC80;

typedef union {
    int i;
    long long ll;
} WormFlag;

extern char D_0028FEF0[];
void disp(void *act);
extern void p2o_SetDefaultEnviroment(void *a0);
extern void p2o_DispVU1DObjMulti(void *a0);
extern float *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(float *m);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void MatrixDrive_GetTurnYAngleXZ(unsigned short *o1, unsigned short *o2, float x, float y,
                                        float z);
extern void MatrixDrive_RotMatrixX(short a0);
extern void MatrixDrive_RotMatrixY(short a0);
extern void MatrixDrive_RotMatrixZ(short a0);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void CopyMatrix(void *dst, void *src);
extern void gif_StartPacketPri(int a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a, int b, int c);
extern void DrawLine(float *from, float *to, float *color, int z);
extern void *memset(void *dst, int c, int n);

typedef union {
    float f[4];
    long long d[2];
} Vec16;

/* A 16-byte GS colour: four 8-bit RGBA components, one per word, handed to
   DrawLine through the float view the call expects. */
typedef union {
    int rgba[4];
    float f[4];
    long long d[2];
} Color16;

/* The worm tip highlight: the line's far endpoint and its colour. */
static const Vec16 tipLineTo = {{0.0f, 10.0f, 0.0f, 1.0f}};

static const Color16 tipLineColor = {{0x80, 0x80, 0x80, 0x80}};

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) WormVec;

typedef struct {
    int f00;    /* 0x00 */
    float rate; /* 0x04 */
    int f08[2]; /* 0x08 */
    float p[4]; /* 0x10 */
    int f20[4]; /* 0x20 */
    float f30;  /* 0x30 */
    int f34[3]; /* 0x34 */
} WormParam;

typedef struct {
    int num;      /* 0x00 */
    int pad04[3]; /* 0x04 */
    WormParam pm; /* 0x10 */
} WormSeg;

typedef struct {
    WormVec *pos;   /* 0x00 */
    WormVec *prev;  /* 0x04 */
    float *len;     /* 0x08 */
    int pad0C[101]; /* 0x0C */
} WormPnt;

typedef struct {
    WormSeg *seg;
    int nseg;
    WormPnt *pnt;
} WormRoute;

typedef struct {
    float pos[3]; /* 0x00 */
    int pad0C;    /* 0x0C */
    float nseg;   /* 0x10 */
    float rate;   /* 0x14 */
    float num;    /* 0x18 */
} WormInit;

typedef struct {
    WormRoute *route;
    WormVec **src;
    float reduce;
    float ratio;
} WormWork;

extern void CopyVector(void *dst, void *src);
void simulate(WormVec *v, int n, float len);
void GetWormRoute(int act, WormVec *target);
extern void sceVu0InterVectorXYZ(void *v0, void *v1, void *v2, float t);
/* prototypes: their order is the inline tail's emission order */
void SetDirectWormTargetPos(int act, void *pos);
void SetWormReduceRatio(int a0, float f12);
void TraceWormRoute(int act, float t);

void outerProcess(int act)
{
    float v[4];
    float p[4];
    int n;

    if ((D_0028F8F0[1].flags & 0x20) != 0) {
        n = GetSkeltonFocusNode(D_00639EA4, 22);
        GetWormRoute(
            act, (WormVec *)(*(char **)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + n * 0x40 + 0x30));
        SetWormReduceRatio(act, 1.0f);
    }

    if ((D_0028F8F0[1].unk00 & 0x40) != 0) {
        n = GetSkeltonFocusNode(D_00639EA4, 22);
        SetDirectWormTargetPos(act,
                               *(char **)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + n * 0x40 + 0x30);
        GetWormCaptureVector(v, (void *)act,
                             *(char **)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + n * 0x40 + 0x30,
                             5.0f);
        GetRootPosition(p, D_00639EA4);
        sceVu0AddVector(p, p, v);
        SetDirectRootPosition(D_00639EA4, p);
        SetWormReduceRatio(act, 0.0f);
    } else {
        SetWormReduceRatio(act, 1.0f);
    }
}

void simulate(WormVec *v, int n, float len)
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
            CopyVector(acc, D_0028FEF0);
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
            CopyVector(acc, D_0028FEF0);
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

void getAnimation(int act)
{
    float tmp[4];
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i, j;

    for (i = 0; i < r->nseg; i++) {
        int num = r->seg[i].num;
        WormVec *pos = r->pnt[i].pos;
        WormVec *prev = r->pnt[i].prev;
        WormParam *pm = &r->seg[i].pm;

        for (j = 1; j < num; j++) {
            CopyVector(tmp, &prev[j]);
            sceVu0ScaleVector(&prev[j], &pos[j], -1.0f);
            sceVu0AddVector(&pos[j], &pos[j], tmp);
        }

        simulate(pos, num - 1, pm->rate * w->reduce);

        for (j = 0; j < num - 1; j++) {
            r->pnt[i].len[j] = _GetLength(&pos[j], &pos[j + 1]);
        }

        for (j = 1; j < num; j++) {
            sceVu0AddVector(&prev[j], &prev[j], &pos[j]);
            sceVu0ScaleVector(&prev[j], &prev[j], 0.8f);
        }
    }
}

void disp(void *act)
{
    unsigned short ax;
    unsigned short az;
    WormWork *w = *(WormWork **)(*(int *)((char *)act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i;
    int j;
    int k;

    p2o_SetDefaultEnviroment(act);

    for (i = 0; i < r->nseg; i++) {
        int num = r->seg[i].num;
        float (*pos)[4] = (float (*)[4])r->pnt[i].pos;
        float *len = r->pnt[i].len;

        for (j = 1; j < num; j++) {
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_TransMatrix(pos[j][0], pos[j][1], pos[j][2]);
            MatrixDrive_GetTurnYAngleXZ(&ax, &az, pos[j][0] - pos[j - 1][0],
                                        pos[j][1] - pos[j - 1][1], pos[j][2] - pos[j - 1][2]);
            MatrixDrive_RotMatrixX(-ax);
            MatrixDrive_RotMatrixZ(-az);
            MatrixDrive_PushMatrix();
            MatrixDrive_ScaleMatrix(2.0f, len[j - 1] * 0.02f, 2.0f);
            MatrixDrive_RotMatrixX(-0x8000);
            CopyMatrix(*(char **)(*(int *)((char *)act + 0x15C) + 0xC) + (j * 0x40 - 0x40),
                       MatrixDrive_GetMatrix());
            MatrixDrive_PopMatrix();

            if (j == num - 1) {
                float col[4];
                Vec16 c1;
                Color16 c2;

                gif_StartPacketPri(2);
                memset(col, 0, 16);
                col[3] = 1.0f;
                c1 = tipLineTo;
                c2 = tipLineColor;
                MatrixDrive_TransMatrix(0.0f, len[num - 2] * 0.02f, 0.0f);
                for (k = 0; k <= 0xFFFF; k += 0x4000) {
                    MatrixDrive_PushMatrix();
                    MatrixDrive_RotMatrixY(k);
                    MatrixDrive_TransMatrix(0.0f, 0.0f, -5.0f);
                    MatrixDrive_RotMatrixX(w->ratio * 32768.0f);
                    gif_SetAlpha(1, 7, 128);
                    DrawLine(col, c1.f, c2.f, 0);
                    MatrixDrive_PopMatrix();
                }
                gif_EndPacket();
            }
        }
        p2o_DispVU1DObjMulti(*(char **)((char *)act + 0x15C));
    }
}

/* the reduce ratio is written through a union view, so the store is a full
   memory barrier: the ROM proves it, because the SetWormReduceRatio +
   TraceWormRoute pair in WormGeo re-derives the work pointer from the actor
   after the store instead of reusing the one the store just computed. */
typedef union {
    float f;
    int i;
} WormFI;

inline void SetWormReduceRatio(int a0, float f12)
{
    ((WormFI *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8))->f = f12;
}

void GetWormRoute(int act, WormVec *target)
{
    WormVec d;
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i;
    int j;
    float len;

    for (i = 0; i < r->nseg; i++) {
        CopyVector(w->src[i], r->pnt[i].pos);
        CopyVector(&w->src[i][9], target);

        for (j = 1; j < 9; j++) {
            sceVu0InterVectorXYZ(&w->src[i][j], &w->src[i][9], &w->src[i][0], j * 0.125f);
            w->src[i][j].w = 1.0f;
        }

        sceVu0SubVector(&d, &w->src[i][1], &w->src[i][0]);
        len = VectorLength(&d);

        for (j = 1; j < 9; j++) {
            WormVec v = {len * (_GetRandom() * 2.0f - 1.0f), len * (_GetRandom() * 2.0f - 1.0f),
                         len * (_GetRandom() * 2.0f - 1.0f), 0.0f};

            sceVu0AddVector(&w->src[i][j], &w->src[i][j], &v);
        }
    }

    w->ratio = 0.0f;
}

inline void SetDirectWormTargetPos(int act, void *pos)
{
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i;

    for (i = 0; i < r->nseg; i++) {
        int n = r->seg[i].num;
        CopyVector(&r->pnt[i].pos[n - 1], pos);
        r->pnt[i].pos[n - 1].w = 1.0f;
    }
    w->ratio = 1.0f;
}

inline void TraceWormRoute(int act, float t)
{
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i, j;
    float step = t * 8.99999f;

    for (i = 0; i < r->nseg; i++) {
        int n = r->seg[i].num;
        for (j = 1; j < n; j++) {
            float f = step * (float)j / (float)(n - 1);
            sceVu0InterVectorXYZ(&r->pnt[i].pos[j], &w->src[i][(int)f + 1], &w->src[i][(int)f],
                                 f - (float)(int)f);
            r->pnt[i].pos[j].w = 1.0f;
        }
    }
}

/* census: the listing inlines this (sugipon/src/worm.c:310-321) into WormGeo
   and nowhere else, so it is a file-static inline with no ROM symbol. */
static inline void ResetWormRoute(int act, WormWork *w)
{
    WormRoute *r = w->route;
    int i;
    int j;

    for (i = 0; i < r->nseg; i++) {
        int num = r->seg[i].num;
        WormVec *pos = r->pnt[i].pos;
        WormVec *prev = r->pnt[i].prev;

        for (j = 0; j < num; j++) {
            CopyVector(&pos[j], r->seg[i].pm.p);
            CopyVector(&prev[j], D_0028FEF0);
        }
    }

    GetWormRoute(act, (WormVec *)r->seg[0].pm.p);
    w->ratio = 0.0f;
}

void *InitWormGeo(int act, WormInit *ini)
{
    char *d = *(char **)(act + 0x15C);
    WormWork *w;
    WormSeg *seg;
    int nseg;
    int num;
    int i;

    w = (WormWork *)iosMallocDebug(D_0063A438, 16, __FILE__, 328);
    seg = (WormSeg *)iosMallocDebug(D_0063A438, 880, __FILE__, 329);

    nseg = (int)ini->nseg;
    if (nseg == 0) {
        nseg = 10;
    }
    num = (int)ini->num;
    if (num == 0) {
        num = 20;
    }

    w->src = (WormVec **)iosMallocDebug(D_0063A438, nseg * 4, __FILE__, 334);

    for (i = 0; i < nseg; i++) {
        WormVec pos = {ini->pos[0] + (_GetRandom() * 2.0f - 1.0f) * 50.0f,
                       ini->pos[1] + (_GetRandom() * 2.0f - 1.0f) * 50.0f,
                       ini->pos[2] + (_GetRandom() * 2.0f - 1.0f) * 50.0f, 1.0f};

        seg[i].num = num;
        seg[i].pm.f00 = -1;
        CopyVector(seg[i].pm.p, &pos);
        seg[i].pm.rate = (int)ini->rate != 0 ? ini->rate : 20.0f;
        seg[i].pm.f30 = 10.0f;

        w->src[i] = (WormVec *)iosMallocDebug(D_0063A438, 160, __FILE__, 350);
    }

    seg[nseg].num = -1;
    w->reduce = 1.0f;
    w->ratio = 1.0f;
    w->route = (WormRoute *)InitChains((char *)seg);

    *(float *)(*(char **)(d + 0x870) + 0x8) = 0.0f;
    *(float *)(*(char **)(d + 0x870) + 0x4) = 0.0f;
    *(float *)(*(char **)(d + 0x870) + 0x0) = 0.0f;

    *(float *)(*(char **)(d + 0x870) + 0x28) = 1.0f;
    *(float *)(*(char **)(d + 0x870) + 0x24) = 1.0f;
    *(float *)(*(char **)(d + 0x870) + 0x20) = 1.0f;

    if (*(int *)(d + 0xC) != 0) {
        iosFree(*(int *)(d + 0xC) & 0xFFFFFFF);
    }
    if (*(int *)(d + 0x10) != 0) {
        iosFree(*(int *)(d + 0x10) & 0xFFFFFFF);
    }
    *(int *)(d + 0xC) = 0;
    *(int *)(d + 0x10) = 0;
    *(int *)(d + 0xC) = (int)iosMallocDebug(D_0063A44C, num * 0x40, __FILE__, 367);
    *(int *)(d + 0x10) = (int)iosMallocDebug(D_0063A44C, num * 0x10, __FILE__, 367);
    *(int *)(d + 0x8) = num;
    if (*(int *)(d + 0x870) != 0) {
        iosFree(*(int *)(d + 0x870) & 0xFFFFFFF);
    }
    *(int *)(d + 0x870) = (int)iosMallocDebug(D_0063A44C, num * 0x50, __FILE__, 367);
    {
        int n;

        for (n = 0; n < num; n++) {
            ((WormFlag *)(*(char **)(d + 0x870) + n * 0x50 + 0x38))->ll &= ~1;
            ((WormFlag *)(*(char **)(d + 0x870) + n * 0x50 + 0x38))->ll &= ~2;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x40) = 0.0f;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x44) = 0.0f;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x48) = 0.0f;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x4C) = 1.0f;
            ((WormFlag *)(*(char **)(d + 0x870) + n * 0x50 + 0x38))->ll &= ~4;
            *(int *)(*(char **)(d + 0x870) + n * 0x50 + 0x30) = 0;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x34) = 1.0f;
            *(short *)(*(char **)(d + 0x870) + n * 0x50 + 0x3A) = 0;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x20) = 1.0f;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x24) = 1.0f;
            *(float *)(*(char **)(d + 0x870) + n * 0x50 + 0x28) = 1.0f;
        }
    }
    *(short *)(d + 0x84C) = 2;

    return w;
}

void GetWormCaptureVector(void *out, void *act, void *node, float scale)
{
    sceVu0SubVector(out, (void *)(*(int *)((char *)act + 0x15C) + 0x50), node);
    sceVu0Normalize(out, out);
    sceVu0ScaleVector(out, out, scale);
}

void WormGeo(int act)
{
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);

    if (D_0063BC80 != 0) {
        ResetWormRoute(act, w);
        D_0063BC80 = 0;
    }

    outerProcess(act);

    if (w->ratio < 1.0f) {
        w->ratio = w->ratio + 0.05f;
        if (1.0f < w->ratio) {
            w->ratio = 1.0f;
        }
        SetWormReduceRatio(act, 1.0f);
        TraceWormRoute(act, w->ratio);
    }

    getAnimation(act);
}

void WormDL(void *act)
{
    disp(act);
}
