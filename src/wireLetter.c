#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", DispWireLetter);
INCLUDE_ASM("asm/nonmatchings/src/wireLetter", DispWireString);
extern int D_004EE590[];
extern int D_004EE5A0[];

void DefaultColorWireString(void)
{
  int new_var;
  new_var = D_004EE590[1];
  D_004EE5A0[0] = D_004EE590[0];
  D_004EE5A0[1] = new_var;
  D_004EE5A0[2] = D_004EE590[2];
}
void ChangeColorWireString(int a0, int a1, int a2)
{
    D_004EE5A0[0] = a0;
    D_004EE5A0[1] = a1;
    D_004EE5A0[2] = a2;
}
INCLUDE_ASM("asm/nonmatchings/src/wireLetter", Draw2DBox);
