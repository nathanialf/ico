#include "common.h"
#include "debug.h"
#include "Primitive.h"
#include "tableSin.h"

/* header prototypes (order fixes the inline tail) */
extern int D_00556E10[];
extern int D_0063C308;
extern unsigned short D_0063AC64;
extern int D_0063C30C;
/* prototypes: their order is the inline tail's emission order */
void queen_barrier_anim(void);

typedef union {
    float f[4];
    long long ll[2];
} QVec;

typedef struct MeshST { /* the 0x10 stride texture coordinate record */
    float s;            /* 0x0 */
    float t;            /* 0x4 */
    char _8[8];
} MeshST;

typedef struct Mesh3D {
    char _0[0x6C];
    QVec *pos;  /* 0x6C */
    QVec *nrm;  /* 0x70 */
    MeshST *st; /* 0x74 */
} Mesh3D;

extern Mesh3D *D_0063C304;
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(QVec *dst, QVec *src, float k);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(QVec *dst, QVec *src);

INCLUDE_ASM("asm/nonmatchings/ico2/ito/src/queen_barrier_disp", MakeRefractTexture);

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
extern void *memset(void *p, int c, int n);
extern void sceVu0CopyVector(QVec *dst, QVec *src);
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

INCLUDE_ASM("asm/nonmatchings/ico2/ito/src/queen_barrier_disp", queen_barrier_disp_proc);

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
