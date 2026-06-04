#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DispWireLetter);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DispWireString);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DefaultColorWireString);

extern int D_004C36A0[];
extern int D_004C36B0[];

void ChangeColorWireString(void) {
    D_004C36B0[0] = D_004C36A0[0];
    D_004C36B0[1] = D_004C36A0[1];
    D_004C36B0[2] = D_004C36A0[2];
}

extern int D_004C36B0[];

void Draw2DBox(int a0, int a1, int a2) {
    D_004C36B0[0] = a0;
    D_004C36B0[1] = a1;
    D_004C36B0[2] = a2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F2610);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F26F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F2818);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004C36B0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004C36A0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C35E0;  /* stride 0x4 */

/* end struct shapes */
