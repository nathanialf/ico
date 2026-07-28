#include "common.h"

typedef struct {
    float f0;          /* 0x00 */
    char  pad04[0xC];  /* 0x04 */
    char  m10[0x10];   /* 0x10 */
    char  m20[0x10];   /* 0x20 */
    char  m30[0x10];   /* 0x30 */
    int   obj;         /* 0x40 */
    char  pad44[0xC];  /* 0x44 */
} BgaDisp;


extern void GetInverseQuaternion();
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern char D_00275850[];
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", InitMultiBgaManager);

void EntryMultiBgaManager(char *base, int idx, int v6, char *a7, char *a8)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    MatrixDrive_TurnObjectMatrix(p + 0x10, a7);
    MatrixDrive_TurnObjectMatrix(p + 0x20, D_00275850);
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

extern int D_00274EC0[];
extern void _ApplyCurrentMatrix(void *a0, void *a1, void *a2);
extern float stage_SetParentOfGObj(int obj, void *a1, void *a2, float f);

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
        if (D_00274EC0[5] != 0) {
            continue;
        }
        e->f0 = (float)ri;
        _ApplyCurrentMatrix(e->m10, e->m10, e->m20);
    }
}

