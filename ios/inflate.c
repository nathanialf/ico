#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ios/inflate", huft_build);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate_codes);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate_stored);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate_fixed);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate_dynamic);
extern void init_mblock(int *self);

void inflate_start(void *a0)
{
    int *w = (int *)((char *) a0 + 0x18000);
    w[0x78 / 4] = -1;
    w[0x48 / 4] = 0;
    *(long long *)((char *) w + 0x68) = 0;
    *(long long *)((char *) w + 0x70) = 0;
    w[0x50 / 4] = 0;
    w[0x4C / 4] = 0;
    w[0x54 / 4] = 0;
    w[0x58 / 4] = 0;
    w[0x7C / 4] = 0;
    w[0x84 / 4] = 0;
    w[0x80 / 4] = 0;
    w[0x88 / 4] = 0;
    init_mblock((char *) a0 + 0x18098);
}
INCLUDE_ASM("asm/nonmatchings/ios/inflate", close_inflate_handler);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", open_inflate_handler);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", fill_inbuf);
extern void iosFree();

int huft_free(char *p)
{
    char *next;
    if (p == (char *)0) goto end;
    p -= 8;
    while (1) {
        next = *(char **)(p + 4);
        iosFree(p);
        p = next;
        if (p == (char *)0) break;
        p -= 8;
    }
end:
    return 0;
}
