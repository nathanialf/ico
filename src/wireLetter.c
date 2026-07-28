#include "common.h"


extern int D_004C75C0[];
extern int D_004C75B0[];
INCLUDE_ASM("asm/nonmatchings/src/wireLetter", DispWireLetter);

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", DispWireString);

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", DefaultColorWireString);

void ChangeColorWireString(void)
{
  int new_var;
  new_var = D_004C75B0[1];
  D_004C75C0[0] = D_004C75B0[0];
  D_004C75C0[1] = new_var;
  D_004C75C0[2] = D_004C75B0[2];
}

void Draw2DBox(int a0, int a1, int a2)
{
    D_004C75C0[0] = a0;
    D_004C75C0[1] = a1;
    D_004C75C0[2] = a2;
}

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", func_001F5620);

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", func_001F5700);

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", func_001F5828);

