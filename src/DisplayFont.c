#include "common.h"

/* .data — carved VMA 0x4EE5F0..0x4EE6F0 (1 symbols), bytes verified against the target ELF */
/* prototypes: their order is the inline tail's emission order */
int font_GetWidth(void);
int font_GetHeight(void);
void font_Init(void);

unsigned int D_004EE5F0[64] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0B080000, 0x10030C07, 0x11020F04, 0x0C071003, 0x0D070C06, 0x10030F04, 0x0C070B08, 0x0E050B08,
    0x0C070E04, 0x0E050E05, 0x0E050F05, 0x0E050E05, 0x0E050E04, 0x0B080B08, 0x0D060E05, 0x0E050E05,
    0x10031201, 0x10040F04, 0x0E040F03, 0x0F030E04, 0x0B080F04, 0x10040D06, 0x10030F05, 0x10030F04,
    0x10030E04, 0x0F040F04, 0x0F041003, 0x11021003, 0x10031003, 0x0D070F04, 0x0C061003, 0x0E040D05,
    0x0F050000, 0x0E050E04, 0x0E050F05, 0x0F040D06, 0x0B080E05, 0x0E050C06, 0x11020B08, 0x0E050E05,
    0x0E050E05, 0x0E060D06, 0x0E050D06, 0x11020E04, 0x0E040F04, 0x0C060E05, 0x0D070B08, 0x10020F05,
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

inline int font_GetHeight(void)
{
    return (0x3200 / D_0063A064) / 2;
}

inline void font_Init(void)
{
    D_0063BD00 = 0;
    D_0063BD10 = 0x80;
    D_0063BD0C = 0x80;
    D_0063BD08 = 0x80;
    D_0063BD04 = 0x80;
}

extern int strlen(const char *s);

/* SRCFILE places this helper's rows (seki/src/DisplayFont.c:99-103) INSIDE
   font_CheckAlign's own span (def line 95, body 110-143), i.e. it was a
   function-local helper in the 2001 source; it is fully inlined at all
   eight call sites, so the placement emits no bytes of its own. */
static inline int font_HexDigit(char c)
{
    int r = -1;

    if ((unsigned char)(c - '0') < 10)
        r = c - '0';
    else if ((unsigned)(c - 'A') < 6 || (unsigned)(c - 'a') < 6)
        r = (c >= 'a') ? (c - ('a' - 10)) : (c - ('A' - 10));
    return r;
}

int font_CheckAlign(unsigned char *col, unsigned char *str)
{
    unsigned char buf[256];
    unsigned char *p;
    int n;
    int c;

    n = 0;
    p = str;
    while ((c = *p++) != 0) {
        if (c == '{') {
            n = 1;
        } else if (c == '}') {
            buf[n - 1] = 0;
            n = 0;
            switch (buf[0]) {
            case 'L':
                D_0063BD00 = 1;
                break;
            case 'R':
                D_0063BD00 = 2;
                break;
            case 'C':
                D_0063BD00 = 0;
                break;
            case '#':
                if (strlen((const char *)buf) == 9) {
                    D_0063BD04 = font_HexDigit(buf[1]) * 16 + font_HexDigit(buf[2]);
                    D_0063BD08 = font_HexDigit(buf[3]) * 16 + font_HexDigit(buf[4]);
                    D_0063BD0C = font_HexDigit(buf[5]) * 16 + font_HexDigit(buf[6]);
                    D_0063BD10 = font_HexDigit(buf[7]) * 16 + font_HexDigit(buf[8]);
                }
                break;
            }
        } else if (n != 0) {
            buf[n - 1] = c;
            n++;
        }
    }
    col[0] = D_0063BD04;
    col[1] = D_0063BD08;
    col[2] = D_0063BD0C;
    col[3] = D_0063BD10;
    return D_0063BD00;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_Print);
