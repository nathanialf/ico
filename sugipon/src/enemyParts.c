#include "common.h"
#include "ico/types.h"

/* enemyParts 0x7F0 view (local) */
typedef struct { int f_0; char _pad4[4]; int f_8; char _pad_c[8]; int f_14; char _pad18[0x20]; int f_38; char _pad3c[8]; float f_44; } EPGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", UpdatePointBlur);

void InitEnemyEye(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x7F0);
    q->f_38 = a1;
}

int InitEnemyFootPrint(void *a0) {
    func_001E1A18(a0, 0x705, 0x820, -1, -1, 0x39C);
    func_001D1ED8(a0, 0);
    *(int *)((char *)a0 + 0x16C) = 0;
    return 0;
}

extern void func_001E1A18(void *a0, int a1, int a2, int a3, int a4, int a5);
extern void func_001D1ED8(void *a0, int a1);

void ExecEnemyFootPrints(void *a0)
{
    func_001E1A18(a0, 0x705, 0x820, -1, -1, 0x39C);
    func_001D1ED8(a0, 0);
    *(int *)((char *)a0 + 0x16C) = 0;
}

int EntryEnemyFootPrint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x7F0);
    return q->f_14;
}

extern int EnemyGeo(void *a0, int a1, void *a2);

int DispEnemyFootPrints(void *a0) {
    char *p = *(char **)((char *)a0 + 0x15C);
    int *q = *(int **)(p + 0x7F0);
    int val = q[0];
    char *r = *(char **)(p + 0x830);
    *(int *)(r + 0x30) = 0;
    return EnemyGeo(a0, val, q + 1);
}

void InitPointBlur(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x7F0);
    q->f_44 = a1;
}

typedef struct { int _0, _4; float f8; int _c, _10; } EyeParam;
extern EyeParam D_00617828[];

int DispPointBlur(void *a0) {
    EyeParam *base = D_00617828;
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x7F0);
    return base[q->f_8]._10 & 3;
}

int UpdateEnemyEye(void *a0) {
    EyeParam *base = D_00617828;
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x7F0);
    return ((unsigned int)base[q->f_8]._10 >> 2) & 3;
}


float DispEnemyEye(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x7F0);
    int idx = q->f_8;
    return D_00617828[idx].f8;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", ResetEnemyEye);

extern void GetRootMatrixByDObj(void *dst, int *src);
extern void func_00102820(void *dst, int *src);
extern int SetParticleEffectUpperLimit(int a, void *b, void *c);

void moveDataElements(int *self)
{
    int local[8];
    GetRootMatrixByDObj(local, self);
    func_00102820(&local[4], self);
    SetParticleEffectUpperLimit(0x31, local, &local[4]);
    ((GObj *)self)->f_16C = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC020);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC220);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC518);

extern int func_002610F0(void);
extern void func_0010E0E8(int *self, int a1, int *param);
extern void func_0010E250(void *a0, void *a1, void *a2);
extern int D_00271C00[];
extern const float D_0062953C;

typedef struct {
    char _pad0[0x20];
    float f20, f24, f28;
    char _pad2c[4];
    float f30;
    char _pad34[0x1C];
} Emit;

int func_001CC7D8(void *a0) {
    int local[4];
    char *base;
    char *w;
    char *cur;
    int i;

    i = 0;
    base = *(char **)((char *)a0 + 0xC);
    if (*(int *)a0 > 0) {
        w = base + 0x10;
        cur = base;
        do {
            int id = *(int *)cur;
            if (id < 0) goto next;
            {
                Emit *e = (Emit *)(i * 0x50 + (int)*(char **)(*(char **)((char *)a0 + 4) + 0x830));
                int cnt;
                int neg1 = -1;
                e->f30 = -(float)(id + 1) / 30.0f;
                e->f20 = e->f20 + *(float *)(cur + 4);
                *(float *)(cur + 4) = *(float *)(cur + 4) * D_0062953C;
                e->f28 = e->f20;
                e->f24 = e->f20;
                func_0010E0E8(local, (short)func_002610F0(), D_00271C00);
                func_0010E250(*(char **)(*(char **)((char *)a0 + 4) + 0xC) + i * 0x40,
                              local, w);
                cnt = *(int *)(w - 0x10) + 1;
                *(int *)(w - 0x10) = cnt;
                if (cnt == 0x1E) {
                    *(int *)(w - 0x10) = neg1;
                    *(float *)(*(char **)(*(char **)((char *)a0 + 4) + 0x830) + 0x80) = 1.0f;
                }
            }
        next:
            w += 0x20;
            i++;
            cur += 0x20;
        } while (i < *(int *)a0);
    }
    return 1;
}


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC950);

extern void file_Init(void *a0);
int func_001CCA00(void *a0) {
    file_Init(*(void **)((char *)a0 + 4));
    return 1;
}

extern void *iosFree(void *a0, int a1, void *a2, int a3);
extern void mc_TransMicroCode(void *a0, int a1);
extern void *D_0062A310;
extern char D_006116B0[];
extern char D_004BC0C0[];

typedef struct { long long w[8]; } Blob40;

void *func_001CCA20(int a0, int a1, char *a2, int a3) {
    char *p = (char *)iosFree(D_0062A310, 0x40, D_006116B0, 0xF);
    *(Blob40 *)p = *(Blob40 *)D_004BC0C0;
    *(int *)(p + 0x0) = a1;
    *(int *)(p + 0xC) = (int)iosFree(D_0062A310, a0 << 5, D_006116B0, 0x13);
    *(int *)(p + 0x8) = (int)iosFree(D_0062A310, a0 << 4, D_006116B0, 0x14);
    *(int *)(p + 0x10) = (int)iosFree(D_0062A310, a0 << 3, D_006116B0, 0x15);
    *(int *)(p + 0x4) = a0;
    *(char *)(p + 0x14) = *(char *)(a2 + 0);
    *(char *)(p + 0x15) = *(char *)(a2 + 4);
    *(char *)(p + 0x16) = *(char *)(a2 + 8);
    *(char *)(p + 0x17) = *(char *)(a2 + 0xC);
    mc_TransMicroCode(p + 0x20, a3);
    return p;
}

extern void gif_SpriteOffset(int x);
extern void gsb_SetFrame(int x, int y, int z);
extern void gif_Line(int a, int b, int c, int d);
extern void func_0010F9D0(void);

int func_001CCB60(int *self)
{
    gif_SpriteOffset(self[0]);
    gsb_SetFrame(1, self[0xD], 0x80);
    gif_Line(self[3], self[4], self[1] * 2, 1);
    func_0010F9D0();
    return 1;
}

extern void func_001189F8(void *a0, int a1, void *a2);
extern void func_001CC020(int a0, void *a1, void *a2, float a3);
extern char D_004BC180[];
extern char D_004BC1C0[];

int func_001CCBC0(char *a0, int a1, float f)
{
    func_001189F8(a0 + 0x10, a1, D_004BC180);
    if (*(int *)a0 != 0) {
        func_001CC020(*(int *)(a0 + 0x4), a0 + 0x40, D_004BC1C0, f * 3.0f);
    }
    return 1;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_004BC0C0;

typedef struct {
    unsigned char      f_4;  /* 0x04 */
    unsigned char      f_8;  /* 0x08 */
    unsigned char      f_C;  /* 0x0C */
} S_004BC160;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_10;  /* 0x10 */
} S_00617828;  /* stride 0x14 */

/* end struct shapes */
