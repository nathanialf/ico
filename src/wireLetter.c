#include "common.h"

typedef struct { float x; float y; int z; } WLPnt;

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
extern void DrawLineG(void *a0, void *a1, void *a2, void *a3, int a4);
extern void gif_EndPacket(void);
extern void gif_StartPacketPri(int a0);

void Draw2DBox(float x0, float y0, float x1, float y1) {
    WLPnt a __attribute__((aligned(16))) = {x0, y0, 0};
    WLPnt b __attribute__((aligned(16))) = {x0, y1, 0};
    WLPnt c __attribute__((aligned(16))) = {x1, y1, 0};
    WLPnt d __attribute__((aligned(16))) = {x1, y0, 0};
    gif_StartPacketPri(0xB);
    DrawLineG(&a, D_004EE5A0, &b, D_004EE5A0, -1);
    DrawLineG(&b, D_004EE5A0, &c, D_004EE5A0, -1);
    DrawLineG(&c, D_004EE5A0, &d, D_004EE5A0, -1);
    DrawLineG(&d, D_004EE5A0, &a, D_004EE5A0, -1);
    gif_EndPacket();
}
