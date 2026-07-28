#include "common.h"


extern int D_0063330C;
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern float D_0063331C;
extern int D_00633314;
extern void *D_00631AE8;
extern int D_004C09A0[];
extern int D_00633310;
extern void playSEConditionID(int a0, int a1);
extern int D_00633318;
void _dispParam(int a0, float t)
{
  int new_var;
  if (D_00631AE8 != 0)
  {
    playSEConditionID(D_00631AE8, 0x75);
    playSEConditionID(D_00631AE8, 0x76);
    playSEConditionID(D_00631AE8, 0x77);
    playSEConditionID(D_00631AE8, 0x78);
    playSEConditionID(D_00631AE8, 0x79);
  }
  D_0063330C = (new_var = 1);
  new_var = (D_00633314 = new_var);
  D_00633318 = (D_00633310 = 0);
  MatrixDrive_TurnObjectMatrix((int) D_004C09A0, a0);
  D_0063331C = t;
}

void editParam(int a0, float t)
{
    D_0063330C = 1;
    D_00633314 = 1;
    D_00633310 = 0;
    D_00633318 = 0;
    MatrixDrive_TurnObjectMatrix((int) D_004C09A0, a0);
    D_0063331C = t;
    D_00633318 = 1;
    D_00633314 = 0;
}

void dispXZYZCircle(void) {
    D_0063330C = 0;
    D_00633314 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispCircle2);

INCLUDE_ASM("asm/nonmatchings/src/effectTool", setQ);

INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispEffectToolField);

INCLUDE_ASM("asm/nonmatchings/src/effectTool", EditTarget);

extern unsigned short D_00633398;
extern unsigned short D_0063339A;
extern void GetMatrixFromQuaternion(int *self);
extern void func_0010E0B8(int *self, short y);
extern void func_0010E158(int *self, short y);

void saveEffectData(int *self)
{
    GetMatrixFromQuaternion(self);
    func_0010E158(self, -D_00633398);
    func_0010E0B8(self, -D_0063339A);
}

INCLUDE_ASM("asm/nonmatchings/src/effectTool", moveEffectToolGeometry);

INCLUDE_ASM("asm/nonmatchings/src/effectTool", execEffectTool);

