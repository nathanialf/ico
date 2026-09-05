#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", UpdatePointBlur);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyEye);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyFootPrint);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", ExecEnemyFootPrints);
extern float D_006394D4;
extern void _CopyVector(void *dst, void *src);

int EntryEnemyFootPrint(char *self, void *pos)
{
    int i = *(int *)(self + 0x8);
    char *fp = (char *)(i * 0x20 + *(int *)(self + 0xC));
    char *vt;

    *(float *)(fp + 0x4) = D_006394D4;
    *(int *)(fp + 0x0) = 0;
    _CopyVector(fp + 0x10, pos);

    *(float *)((char *)(i * 0x20 + *(int *)(self + 0xC)) + 0x14) += -5.0f;
    vt = (char *)(i * 0x50 + *(int *)(*(char **)(self + 0x4) + 0x870));
    *(float *)(vt + 0x20) = *(float *)(vt + 0x24) = *(float *)(vt + 0x28) = 0.0f;

    *(int *)(self + 0x8) = *(int *)(self + 0x8) + 1;
    if (*(int *)(self + 0x8) == *(int *)self) {
        *(int *)(self + 0x8) = 0;
    }
    return 0;
}
extern void p2o_DispVU1DObj();

int DispEnemyFootPrints(int *a0)
{
    p2o_DispVU1DObj(a0[1]);
    return 1;
}
typedef struct PointBlur {
    /* 0x00 */ int   f0;
    /* 0x04 */ int   num;
    /* 0x08 */ void *f8;
    /* 0x0C */ void *fC;
    /* 0x10 */ void *f10;
    /* 0x14 */ unsigned char col[4];
    /* 0x18 */ long long _pad18;   /* ROM proves 8-byte struct alignment: the
                                     0x40-byte template copy is ld/sd, not lw/sw */
    /* 0x20 */ float pos[4];
    /* 0x30 */ char  _pad30[0x10];
} PointBlur;

extern int D_0063A438;
extern const char D_0061F710[];
extern PointBlur D_004E78E0;
extern void *iosMallocDebug(int heap, int size, const char *file, int line);

PointBlur *InitPointBlur(int num, int a1, int *col, void *pos)
{
    PointBlur *p = (PointBlur *)iosMallocDebug(D_0063A438, 0x40, D_0061F710, 16);
    *p = D_004E78E0;

    p->f0 = a1;
    p->fC = iosMallocDebug(D_0063A438, num << 5, D_0061F710, 20);
    p->f8 = iosMallocDebug(D_0063A438, num << 4, D_0061F710, 21);
    p->f10 = iosMallocDebug(D_0063A438, num << 3, D_0061F710, 22);
    p->num = num;
    p->col[0] = col[0];
    p->col[1] = col[1];
    p->col[2] = col[2];
    p->col[3] = col[3];
    _CopyVector(p->pos, pos);
    return p;
}
extern void gif_Draw2DStripG();
extern void gif_EndPacket();
extern void gif_SetAlpha();
extern void gif_StartPacketPri();

int DispPointBlur(int *self)
{
    gif_StartPacketPri(self[0]);
    gif_SetAlpha(1, self[0xD], 0x80);
    gif_Draw2DStripG(self[3], self[4], self[1] * 2, 1);
    gif_EndPacket();
    return 1;
}
extern char D_004E79A0[];
extern char D_004E79E0[];
extern void UpdatePointBlur(int a0, void *a1, void *a2, float a3);
extern void _MulMatrix(void *a0, int a1, void *a2);

int UpdateEnemyEye(char *a0, int a1, float f)
{
    _MulMatrix(a0 + 0x10, a1, D_004E79A0);
    if (*(int *)a0 != 0) {
        UpdatePointBlur(*(int *)(a0 + 0x4), a0 + 0x40, D_004E79E0, f * 3.0f);
    }
    return 1;
}
extern void _CopyMatrix();
extern void reg_DispMultiPri();

int DispEnemyEye(char *a0) {
    _CopyMatrix(*(int *)(*(char **)(a0 + 0x50) + 0xC), a0 + 0x10);
    reg_DispMultiPri(*(int *)(a0 + 0x50), 0xA);
    if (*(int *)a0 != 0) {
        char *fobj = *(char **)(a0 + 0x4);
        gif_StartPacketPri(*(int *)fobj);
        gif_SetAlpha(1, *(int *)(fobj + 0x34), 0x80);
        gif_Draw2DStripG(*(int *)(fobj + 0xC), *(int *)(fobj + 0x10), *(int *)(fobj + 0x4) << 1, 1);
        gif_EndPacket();
    }
    return 1;
}
int ResetEnemyEye(char *self) {
    char *p = *(char **)(self + 0x4);
    *(int *)(p + 0x30) = 1;
    return 1;
}
typedef struct IVec { float x, y, z, w; } IVec;

extern void _CopyIVector(void *dst, void *src);

/* Two strip vertices per footprint: fC holds the IVec positions (2 x 0x10),
 * f10 the packed RGBA words (2 x 4). The alpha lives in byte 3 of the word,
 * so it is reached through a plain unsigned char * -- that char store is what
 * kills the cached p->f10 load for the last statement. */

void moveDataElements(PointBlur *p)
{
    int i;
    float step;
    unsigned char *n;
    float a;

    step = 255.0f / p->num;

    for (i = p->num - 2; i >= 0; i--) {
        _CopyIVector(&((IVec *)p->fC)[i * 2 + 2], &((IVec *)p->fC)[i * 2]);
        _CopyIVector(&((IVec *)p->fC)[i * 2 + 3], &((IVec *)p->fC)[i * 2 + 1]);

        n = (unsigned char *)((unsigned int *)(i * 8 + (int)p->f10) + 2);
        ((unsigned int *)(i * 8 + (int)p->f10))[2] = ((unsigned int *)(i * 8 + (int)p->f10))[0];
        a = (float)((unsigned char *)(i * 8 + (int)p->f10))[3] - step;
        n[3] = (a < 0.0f) ? 0 : (int)a;
        ((unsigned int *)(i * 8 + (int)p->f10))[3] = ((unsigned int *)(i * 8 + (int)p->f10))[2];
    }
    _CopyVector((char *)p->f8 + 0x10, p->f8);
}
