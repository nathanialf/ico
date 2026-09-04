#include "common.h"

#include "ico/types.h"





extern void func_0010F630();
extern void gif_SetAlpha();
extern void gif_Draw2DStripG();
extern void gif_SpriteOffset();
extern void file_Init();
typedef struct { int _0, _4; float f8; int _c, _10; } EyeParam;
extern EyeParam D_0061D560[];
extern void func_001D4B40();
extern void func_001E4798(int *self, int a1, int a2, int a3, int a4, int a5);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", UpdatePointBlur);

/* enemyParts 0x800 view (local) */
typedef struct { int f_0; char _pad4[4]; int f_8; char _pad_c[8]; int f_14; char _pad18[0x20]; int f_38; char _pad3c[8]; float f_44; } EPGeo;

void InitEnemyEye(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x800);
    q->f_38 = a1;
}

int InitEnemyFootPrint(int *self)
{
    func_001E4798(self, 0x71C, 0x839, -1, -1, 0x39A);
    func_001D4B40(self, 0);
    self[0x16C/4] = 0;
    return 0;
}

void ExecEnemyFootPrints(int *self)
{
    func_001E4798((int)self, 0x71C, 0x839, -1, -1, 0x39A);
    func_001D4B40((int)self, 0);
    self[0x16C / 4] = 0;
}

int EntryEnemyFootPrint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x800);
    return q->f_14;
}

extern int EnemyGeo(void *a0, int a1, void *a2);

int DispEnemyFootPrints(void *a0) {
    char *p = *(char **)((char *)a0 + 0x15C);
    int *q = *(int **)(p + 0x800);
    int val = q[0];
    char *r = *(char **)(p + 0x840);
    *(int *)(r + 0x30) = 0;
    return EnemyGeo(a0, val, q + 1);
}

void InitPointBlur(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x800);
    q->f_44 = a1;
}

int DispPointBlur(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  void *q = *((void **) (((char *) p) + 0x800));
  char *new_var;
  int idx = *((int *) (((char *) q) + 0x8));
  new_var = (char *)D_0061D560;
  return (*((int *) ((new_var + (idx * 0x14)) + 0x10))) & 3;
}


int UpdateEnemyEye(void *a0) {
    EyeParam *base = D_0061D560;
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x800);
    return ((unsigned int)base[q->f_8]._10 >> 2) & 3;
}

float DispEnemyEye(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EPGeo *q = *(EPGeo **)((char *)p + 0x800);
    int idx = q->f_8;
    return D_0061D560[idx].f8;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", ResetEnemyEye);

extern void GetRootPosition(void *dst, int *src);
extern void func_00102850(void *dst, int *src);
extern int func_001E8B48(int a, void *b, void *c);

void SetEnemyStonizedVisual(int *self)
{
    int local[8];
    GetRootPosition(local, self);
    func_00102850(&local[4], self);
    func_001E8B48(0x31, local, &local[4]);
    ((GObj *)self)->f_16C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CED80);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CEF90);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF288);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF548);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF6C0);

int func_001CF770(int *a0)
{
    file_Init(a0[1]);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF790);

int func_001CF8D0(int *self)
{
    gif_SpriteOffset(self[0]);
    gif_SetAlpha(1, self[0xD], 0x80);
    gif_Draw2DStripG(self[3], self[4], self[1] * 2, 1);
    func_0010F630();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF930);

