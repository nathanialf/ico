#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", UpdatePointBlur);

void InitEnemyEye(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[0xE] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", InitEnemyFootPrint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", ExecEnemyFootPrints);

int EntryEnemyFootPrint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[5];
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
    int *q = *(int **)((char *)p + 0x7F0);
    *(float *)((char *)q + 0x44) = a1;
}

typedef struct { int _0, _4; float f8; int _c, _10; } EyeParam;
extern EyeParam D_00617828[];

int DispPointBlur(void *a0) {
    EyeParam *base = D_00617828;
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return base[q[2]]._10 & 3;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", UpdateEnemyEye);

extern EyeParam D_00617828[];

float DispEnemyEye(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int idx = q[2];
    return D_00617828[idx].f8;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", ResetEnemyEye);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", moveDataElements);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCB60);

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
