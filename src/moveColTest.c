#include "common.h"

/* prototypes: their order is the inline tail's emission order */
short *InitMoveColTestGeo(int a0, int *self);
extern void p2o_DispVU1();
extern char D_00620898[];
extern int D_0063A438;
extern short *iosMallocDebug(int handle, int size, char *file, int line);
extern int rand(void);

inline short *InitMoveColTestGeo(int a0, int *self)
{
    short *r = iosMallocDebug(D_0063A438, 12, (char *)D_00620898, 0x1C);
    *(int *)r = self[0x30 / 4];
    r[2] = (short)rand();
    r[3] = (short)rand();
    r[4] = (short)rand();
    r[5] = 0;
    return r;
}

/* the 12-byte work block InitMoveColTestGeo allocates, hung at sub+0x830 */
typedef struct MctWork {
    int obj;     /* 0x00 */
    short r1;    /* 0x04 */
    short r2;    /* 0x06 */
    short r3;    /* 0x08 */
    short angle; /* 0x0A */
} MctWork;

typedef struct EditPad {
    int flags;              /* 0x00 */
    int trg;                /* 0x04 */
    char pad08[0x58 - 0x8]; /* 0x08 */
    int mode;               /* 0x58 */
    char pad5C[0xAC - 0x5C];
    unsigned char stick[4]; /* 0xAC */
} EditPad;

extern EditPad D_0028F8F0;
extern unsigned char D_0063BA78;
extern int D_0063BA7C;
extern char D_0063BA80[];
extern char D_006208B0[];
extern int D_00639EA4;
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixZ(int a0);
extern void CopyMatrix(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern void RotQuaternionZ(void *dst, int a1);
extern void UpdateRootMatrix(void *gobj);
extern void GetRootPosition(void *dst, int gobj);
extern void scpBornSpider(int n, float x, float y, float z, float r);
extern void debug_PrintfDummy(int x, int y, unsigned int color, void *fmt);
extern void debug_StdPrintfDummy(void *fmt, int a1);

void MoveColTestGeo(char *self)
{
    float pos[4];
    MctWork *w = *(MctWork **)(*(char **)(self + 0x15C) + 0x830);
    int c;

    CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(self + 0x15C) + 0x20);
    MatrixDrive_RotMatrixZ(w->angle);
    CopyQuaternion(*(char **)(self + 0x15C) + 0xD0, *(char **)(self + 0x15C) + 0x60);
    RotQuaternionZ(*(char **)(self + 0x15C) + 0xD0, w->angle);
    CopyMatrix(*(void **)(*(char **)(self + 0x15C) + 0xC), MatrixDrive_GetMatrix());
    UpdateRootMatrix(self);

    if (D_0028F8F0.mode & 4) {
        if (D_0028F8F0.stick[1] >= 0x81) {
            c = D_0028F8F0.stick[1];
            if (c - 0x80 >= 0x15) {
                w->angle += (c - 0x94) * 3;
            }
        } else {
            c = D_0028F8F0.stick[1];
            if (c - 0x80 < -0x14) {
                w->angle += (c - 0x6C) * 3;
            }
        }
    }
    if ((D_0063BA78++ >> 5) & 1) {
        debug_PrintfDummy(0xA, 0x3C, 0x4080FF00, D_006208B0);
    }

    GetRootPosition(pos, D_00639EA4);
    pos[1] += -500.0f;
    if (D_0028F8F0.trg & 0x400) {
        scpBornSpider(0xA, pos[0], pos[1], pos[2], 300.0f);
        D_0063BA7C += 0xA;
        debug_StdPrintfDummy(D_0063BA80, D_0063BA7C);
    }
    if (D_0028F8F0.trg & 0x200) {
        scpBornSpider(1, pos[0], pos[1], pos[2], 300.0f);
        D_0063BA7C += 1;
        debug_StdPrintfDummy(D_0063BA80, D_0063BA7C);
    }
}

void MoveColTestDL(int a0, int a1, int a2, int a3)
{
    p2o_DispVU1(a0, a1, a2, a3);
}
