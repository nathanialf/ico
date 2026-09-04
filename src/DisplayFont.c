#include "common.h"

/* .data — carved VMA 0x4EE5F0..0x4EE6F0 (1 symbols), bytes verified against the target ELF */
/* prototypes: their order is the inline tail's emission order */
int font_GetWidth(void);
int font_GetHeight(void);
void font_Init(void);
unsigned int D_004EE5F0[64] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0B080000, 0x10030C07, 0x11020F04, 0x0C071003,
    0x0D070C06, 0x10030F04, 0x0C070B08, 0x0E050B08,
    0x0C070E04, 0x0E050E05, 0x0E050F05, 0x0E050E05,
    0x0E050E04, 0x0B080B08, 0x0D060E05, 0x0E050E05,
    0x10031201, 0x10040F04, 0x0E040F03, 0x0F030E04,
    0x0B080F04, 0x10040D06, 0x10030F05, 0x10030F04,
    0x10030E04, 0x0F040F04, 0x0F041003, 0x11021003,
    0x10031003, 0x0D070F04, 0x0C061003, 0x0E040D05,
    0x0F050000, 0x0E050E04, 0x0E050F05, 0x0F040D06,
    0x0B080E05, 0x0E050C06, 0x11020B08, 0x0E050E05,
    0x0E050E05, 0x0E060D06, 0x0E050D06, 0x11020E04,
    0x0E040F04, 0x0C060E05, 0x0D070B08, 0x10020F05,
};
extern int D_0063A064;
extern int D_0063BD00;
extern int D_0063BD04;
extern int D_0063BD08;
extern int D_0063BD0C;
extern int D_0063BD10;
inline int font_GetWidth(void)
{
    return 0x14;
}
inline int font_GetHeight(void) {
    return (0x3200 / D_0063A064) / 2;
}
inline void font_Init(void) {
    D_0063BD00 = 0;
    D_0063BD10 = 0x80;
    D_0063BD0C = 0x80;
    D_0063BD08 = 0x80;
    D_0063BD04 = 0x80;
}
INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_CheckAlign);
INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_Print);
