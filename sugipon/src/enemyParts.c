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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", InitEnemyFootPrint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", ExecEnemyFootPrints);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC7D8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC950);

extern void file_Init(void *a0);
int func_001CCA00(void *a0) {
    file_Init(*(void **)((char *)a0 + 4));
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCA20);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCBC0);


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
