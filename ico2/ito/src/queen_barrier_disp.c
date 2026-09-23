#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "GifPacket.h"
#include "Primitive.h"
#include "tableSin.h"

/* header prototypes (order fixes the inline tail) */
extern int D_00556E10[];
extern int D_0063C308;
extern unsigned short D_0063AC64;
extern int D_0063C30C;

#include "queen_barrier_disp.h"
#include <string.h>
#include <libvu0.h>

typedef struct MeshST { /* the 0x10 stride texture coordinate record */
    float s;            /* 0x0 */
    float t;            /* 0x4 */
    char _8[8];
} MeshST;

typedef struct Mesh3D {
    char _0[0x68];
    int col;    /* 0x68 */
    QVec *pos;  /* 0x6C */
    QVec *nrm;  /* 0x70 */
    MeshST *st; /* 0x74 */
} Mesh3D;

extern Mesh3D *D_0063C304;
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(QVec *dst, QVec *src, float k);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(QVec *dst, QVec *src);

/* The screen rectangle and the texture rectangle this packet draws, in the
   1/16-unit form the GS registers take. */
typedef struct {
    int x0, y0, x1, y1;
} GifRect;

typedef struct {
    int u0, v0, u1, v1;
} GifUvRect;

#define GIF_RGBA(c)                                                                                \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
#define GIF_UV(u, v) ((long long)(u) | ((long long)(v) << 16))
#define GIF_XY(x, y) ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16))
#define GIF_XY0(x, y) ((long long)(x) | ((long long)(y) << 16))

typedef struct {
    unsigned char c[4];
} GifCol;

extern GifCol D_0063AC60[];
extern int D_0063A064;
extern int D_0063A068;
extern GifRect D_00556E00;
extern GifDpk D_004EE6F0;

/* INTERIM: the listing inlines gif_SetGsReg here the same way it does across
   GifPacket.c; while that TU's own out-of-line copy is still asm the callers
   the listing shows inlining it call this static stand-in. */
static inline void setGsReg(long long a0, long long a1)
{
    *D_004EE6F0.ptr++ = a1;
    *D_004EE6F0.ptr++ = a0;
}

void MakeRefractTexture(int frame)
{
    GifCol col = D_0063AC60[0];
    GifRect r = D_00556E00;
    GifUvRect uv = {8, 8, D_0063A064 * 16, D_0063A068 * 16};
    int fx;
    int fy;

    gif_SetGsReg(0x47, 0x30000);

    gif_SetGsReg(0x4E, 0x1300000C0LL);

    gif_SetGsReg(0x06, ((long long)(D_0063A064 / 64) << 14) | 0x664000800LL);

    setGsReg(0x4C, frame | 0x80000);
    setGsReg(0x40, 0xFF000001FF0000LL);
    setGsReg(0x18, 0x780000007000LL);
    setGsReg(0x00, 0x116);
    setGsReg(0x01, GIF_RGBA(col.c));
    setGsReg(0x03, GIF_UV(uv.u0, uv.v0));
    setGsReg(0x05, GIF_XY(r.x0, r.y0));
    /* the far corner is offset once and the near corner added to it, the
       gif_MakeSprite idiom: the ROM adds 0x8000 to the size, not to the sum */
    fx = r.x1 + 0x8000;
    fy = r.y1 + 0x8000;
    setGsReg(0x03, GIF_UV(uv.u0 + uv.u1, uv.v0 + uv.v1));
    setGsReg(0x05, GIF_XY0(r.x0 + fx, r.y0 + fy));
}

void queen_barrier_set_damage(void)
{
    D_0063C308 = 0x3C;
    debug_StdPrintfDummy(D_00556E10);
}

inline void queen_barrier_anim(void)
{
    D_0063AC64 += 0x7D0;
    D_0063C30C += 0x1000;
    if (D_0063C308 > 0) {
        if (--D_0063C308 < 0) {
            D_0063C308 = 0;
        }
    }
}

extern int D_0063A064;
extern int D_0063A068;
/* kept local: this TU's uses of _GetNorm do not fit the prototype in Matrix.h */
extern float _GetNorm(QVec *v);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(QVec *dst, QVec *a, QVec *b);
/* kept local: this TU's uses of _RotTransPersCurrentMatrix do not fit the prototype in Matrix.h */
extern void _RotTransPersCurrentMatrix(QVec *dst, QVec *src);

void makeRefractST(float k)
{
    QVec v;
    QVec w;
    float t;
    float f;
    int ang;
    int i;
    int j;
    int idx;

    memset(&v, 0, sizeof(v));
    v.f[3] = 1.0f;

    t = (float)D_0063C308 / 60.0f;

    ang = (short)D_0063AC64;

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            idx = i * 15 + j;

            sceVu0CopyVector(&v, &D_0063C304->nrm[idx]);
            v.f[2] = 0.0f;
            f = GetTableSin((short)(_GetNorm(&v) * 4.0f * 65536.0f + (float)D_0063C30C)) * 60.0f;

            _ScaleVectorXYZ(&w, &D_0063C304->nrm[idx], f * t);

            f = GetTableSin((short)ang) * 18.0f;
            ang += 0x4000;

            _ScaleVectorXYZ(&v, &D_0063C304->nrm[idx], f * k);

            _AddVectorXYZ(&v, &D_0063C304->pos[idx], &v);
            _AddVectorXYZ(&v, &v, &w);
            v.f[3] = 1.0f;
            _RotTransPersCurrentMatrix(&v, &v);
            D_0063C304->st[idx].s =
                ((v.f[0] - 2048.0f) + (float)(D_0063A064 >> 1)) * (1.0f / (float)D_0063A064);
            D_0063C304->st[idx].t =
                ((v.f[1] - 2048.0f) + (float)(D_0063A068 >> 1)) * (1.0f / (float)D_0063A068);
        }
    }
}

extern int D_0063A074;
extern int D_0063A078;
extern QVec D_00556E30;
extern QVec D_00556E40;
extern int matrixptr;
extern int buffer_ID;
extern void tex_ResetVramPri(int pri);
extern int tex_AllocVramAuto(int a0, int a1);
extern void GetRootMatrix(void *dst, char *outer);
extern void _SetCurrentMatrix(void *m);

/* rows 86 and 93 to 105: the barrier tint, faded from D_00556E30 to
   D_00556E40 across the damage timer and packed into the mesh colour word.
   Row 105 carries the three float-to-int conversions and the mesh pointer
   load and row 86 only the masks, shifts and ors, so the packing helper
   takes ints converted at its call (names ours). */
static __inline__ int packBarrierColor(int r, int g, int b)
{
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0x80;
}

static __inline__ void updateBarrierColor(void)
{
    QVec c;
    QVec a = D_00556E30;
    QVec b = D_00556E40;

    sceVu0InterVector(&c, &a, &b, (float)D_0063C308 / 60.0f);
    D_0063C304->col = packBarrierColor(c.f[0], c.f[1], c.f[2]);
}

void queen_barrier_disp_proc(char *g, float k)
{
    int vram;

    gif_StartPacketPriPath1(10);
    tex_ResetVramPri(10);
    vram = tex_AllocVramAuto(0, 2048);
    MakeRefractTexture(vram >> 5);

    setGsReg(0x4C, ((long long)((D_0063A064 >> 6) & 0x3F) << 16) | 64);
    setGsReg(0x40, ((long long)(D_0063A064 - 1) << 16) | ((long long)(D_0063A068 - 1) << 48));
    setGsReg(0x18, (((long long)(2048 - D_0063A064 / 2) << 4) + D_0063A074) |
                       ((((long long)(2048 - D_0063A068 / 2) << 4) + D_0063A078) << 32));

    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x06, (vram | 0x24020000) | 0x600000000LL);
    gif_SetGsReg(0x14, 0x60);

    setGsReg(0x49, 1);
    setGsReg(0x42, ((long long)128 << 32) | 0x44);

    gif_EndPacketPath1();

    updateBarrierColor();

    {
        QVec m1[4];
        QVec root[4];
        QVec m2[4];

        sceVu0InversMatrix(m1, (char *)matrixptr + 0x80);
        GetRootMatrix(root, g);
        sceVu0CopyVector(&m1[3], &root[3]);
        sceVu0MulMatrix(m2, (char *)matrixptr + 0x100, m1);
        _SetCurrentMatrix(m2);
    }

    makeRefractST(k);

    prim_UpdateMesh3D(D_0063C304, 24, buffer_ID);
    prim_DispMesh3D((int)D_0063C304, 0, 0, -1);
}

void queen_barrier_disp_init(void)
{
    QVec *pos;
    QVec *nrm;
    int i;
    int j;
    int idx;
    float x;
    float y;
    float step;

    /* The 14-step angular increment. It is a local, not a repeated literal:
       the listing carries its .lit4 load on row 215, ahead of every other
       hoisted constant, which is where a declaration puts it. */
    step = 32768.0f / 14.0f;

    D_0063C304 = prim_InitMesh3D(15, 15, 1, 0x1C, 0x64787380, 0);

    for (i = 0, x = -16384.0f; x < 16384.0f; i++, x += step) {
        for (j = 0, y = 16384.0f; y < 49152.0f; j++, y += step) {
            QVec v = {{GetTableSin((short)y) * GetTableCos((short)x), GetTableSin((short)x),
                       GetTableCos((short)y) * GetTableCos((short)x), 1.0f}};

            pos = D_0063C304->pos;
            nrm = D_0063C304->nrm;
            idx = i * 15 + j;
            _ScaleVectorXYZ(&pos[idx], &v, 300.0f);
            _NormalizeVector(&nrm[idx], &pos[idx]);
            D_0063C304->st[idx].s = (float)j / 14.0f;
            D_0063C304->st[idx].t = (float)i / 14.0f;
        }
    }
    prim_UpdateMesh3D(D_0063C304, 11, 0);
    prim_UpdateMesh3D(D_0063C304, 11, 1);
    D_0063C308 = 0;
}
