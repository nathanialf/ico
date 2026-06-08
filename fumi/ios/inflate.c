#include "common.h"

void huft_build(int *a0, int a1) {
    a0[68] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_codes);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_stored);

extern int D_0062BF84;

int inflate_fixed(void) {
    return D_0062BF84;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_dynamic);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", inflate_start);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", close_inflate_handler);

typedef struct { char f0; char pad[0x12B]; } InfEntry;
extern InfEntry D_0069F800[];

void inflate(void) {
    int i;
    for (i = 6; i >= 0; i--) {
        D_0069F800[i].f0 = 0;
    }
    D_0062BF84 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", open_inflate_handler);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", fill_inbuf);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", huft_free);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00134550);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001347B0);

extern void new_segment(void *a0);

void func_001350C8(void *a0)
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
    new_segment((char *) a0 + 0x18098);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135118);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001351E0);

extern int iosFree(int a0, int a1, const char *fmt, int line);
extern void func_001350C8(void *p);
extern void debug_assertMessage();
extern int D_0062A33C;
extern int D_0062A348;

extern char D_00550EA0[];

extern char D_00550EF0[];

extern char D_0062A328[];

/* parked: needs real matching. See tough_nuts/func_001356A8/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_001356A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/inflate", func_00135738);
