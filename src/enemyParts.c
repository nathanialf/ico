#include "common.h"

#include "ico/types.h"





extern void func_0010F630();
extern void gsb_SetFrame();
extern void gif_Line();
extern void gif_SpriteOffset();
extern void file_Init();
extern char D_0061D560[];
extern void func_001D4B40();
extern void func_001E4798(int *self, int a1, int a2, int a3, int a4, int a5);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", UpdatePointBlur);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyEye);

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

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", EntryEnemyFootPrint);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", DispEnemyFootPrints);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitPointBlur);

int DispPointBlur(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  void *q = *((void **) (((char *) p) + 0x800));
  char *new_var;
  int idx = *((int *) (((char *) q) + 0x8));
  new_var = D_0061D560;
  return (*((int *) ((new_var + (idx * 0x14)) + 0x10))) & 3;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", UpdateEnemyEye);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", DispEnemyEye);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", ResetEnemyEye);

extern void GetRootMatrixByDObj(void *dst, int *src);
extern void func_00102850(void *dst, int *src);
extern int func_001E8B48(int a, void *b, void *c);

void moveDataElements(int *self)
{
    int local[8];
    GetRootMatrixByDObj(local, self);
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
    gsb_SetFrame(1, self[0xD], 0x80);
    gif_Line(self[3], self[4], self[1] * 2, 1);
    func_0010F630();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF930);

