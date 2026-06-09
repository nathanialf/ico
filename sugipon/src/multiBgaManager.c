#include "common.h"

extern int D_0062A310;
extern void *iosFree(int handle, int size, char *file, int line);

typedef struct {
    float x;        /* 0x00 */
    float pad0[3];  /* 0x04 */
    float q0[4];    /* 0x10 */
    float q1[4];    /* 0x20 */
    float q2[4];    /* 0x30 */
    int   id;       /* 0x40 */
    int   pad1[3];  /* 0x44 */
} __attribute__((aligned(8))) MultiBga;

MultiBga D_004C1EE0 = {
    -1.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
    -1,
    { 0, 0, 0 },
};

void *InitMultiBgaManager(int n)
{
    MultiBga *base = (MultiBga *)iosFree(D_0062A310, n * 0x50, "src/multiBgaManager.c", 0xB);
    int i;
    for (i = 0; i < n; i++) {
        base[i] = D_004C1EE0;
    }
    return base;
}

extern char D_00271BD0[];
extern void MatrixDrive_TurnObjectMatrix(char *dst, char *src);
extern void GetInverseQuaternion(char *dst, int v);

void EntryMultiBgaManager(char *base, int idx, int v6, char *a7, char *a8)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    MatrixDrive_TurnObjectMatrix(p + 0x10, a7);
    MatrixDrive_TurnObjectMatrix(p + 0x20, D_00271BD0);
    GetInverseQuaternion(p + 0x30, a8);
    *(int *)p = 0;
}


void EntryMultiBgaManagerSensitive(char *base, int idx, int v6, char *a7, char *a8, int a9)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    MatrixDrive_TurnObjectMatrix(p + 0x10, a7);
    MatrixDrive_TurnObjectMatrix(p + 0x20, a9);
    GetInverseQuaternion(p + 0x30, a8);
    *(int *)p = 0;
}

extern int D_00271240[];
extern float stage_SetParentOfGObj(int obj, void *a1, void *a2, float f);
extern void _ApplyCurrentMatrix(void *a0, void *a1, void *a2);

typedef struct {
    float f0;          /* 0x00 */
    char  pad04[0xC];  /* 0x04 */
    char  m10[0x10];   /* 0x10 */
    char  m20[0x10];   /* 0x20 */
    char  m30[0x10];   /* 0x30 */
    int   obj;         /* 0x40 */
    char  pad44[0xC];  /* 0x44 */
} BgaDisp;

void DispMultiBgaManager(BgaDisp *base, int n)
{
    int i;
    int ri;
    float f;
    for (i = 0; i < n; i++) {
        BgaDisp *e = &base[i];
        f = e->f0;
        if (f < 0.0f) {
            continue;
        }
        ri = (int)stage_SetParentOfGObj(e->obj, e->m10, e->m30, f);
        if (D_00271240[5] != 0) {
            continue;
        }
        e->f0 = (float)ri;
        _ApplyCurrentMatrix(e->m10, e->m10, e->m20);
    }
}
