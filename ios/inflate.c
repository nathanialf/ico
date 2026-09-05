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
extern int D_0063A464;
extern void iosFree__pn(void *p) __asm__("iosFree");
extern void iosMallocResetPartition(int a0);
extern void reuse_mblock(void *p);

void close_inflate_handler(void *a0)
{
    char *p;
    if (*(int *)((char *)a0 + 0x18054) != 0) {
        p = *(char **)((char *)a0 + 0x18058);
        if (p != 0) {
            p -= 8;
            for (;;) {
                char *node = p;
                p = *(char **)(p + 4);
                iosFree__pn(node);
                if (p == 0) break;
                p -= 8;
            }
        }
        p = *(char **)((char *)a0 + 0x18054);
        if (p != 0) {
            p -= 8;
            for (;;) {
                char *node = p;
                p = *(char **)(p + 4);
                iosFree__pn(node);
                if (p == 0) break;
                p -= 8;
            }
        }
        *(int *)((char *)a0 + 0x18054) = 0;
        *(int *)((char *)a0 + 0x18058) = 0;
    }
    reuse_mblock((char *)a0 + 0x18098);
    iosFree__pn(a0);
    iosMallocResetPartition(D_0063A464);
}
INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate);
extern char D_00550FF0[];
extern char D_00551040[];
extern int D_0063A450;
extern int D_0063A470;
extern void debug_StdPrintfDummy();
extern int iosMallocDebug(int a0, int a1, const char *fmt, int line);

int open_inflate_handler(int a0, int a1)
{
    int g = D_0063A450;
    int *s1;
    D_0063A464 = g;
    D_0063A470 = 0;
    s1 = (int *) iosMallocDebug(g, 0x180A8, D_00550FF0, 0x2E3);
    inflate_start(s1);
    s1[0] = a1;
    if (a0 == 0)
    {
        debug_StdPrintfDummy(D_00551040);
    }
    else
    {
        s1[0x4 / 4] = a0;
    }
    return (int) s1;
}
/* The inflate handler block carries the gzip-style input buffer at +0x10008
 * and the decoder state at +0x18000 (insize at +0x4C, inptr at +0x50); the
 * read callback and the handle it is given live at +0x4 and +0x0.  The
 * callback's 64-bit size/return are the ones inflate_cd_read_func uses.  */
#define INFLATE_INBUF(p) ((unsigned char *)(p) + 0x10008)
#define INFLATE_STATE(p) ((unsigned int *)((char *)(p) + 0x18000))

typedef long long (*InflateReadFn)(void *buf, long long size, void *handle);

static int fill_inbuf(void *a0)
{
    int len;

    INFLATE_STATE(a0)[0x4C / 4] = 0;
    do {
        len = (*(InflateReadFn *)((char *)a0 + 4))(
                  INFLATE_INBUF(a0) + INFLATE_STATE(a0)[0x4C / 4],
                  0x8000 - INFLATE_STATE(a0)[0x4C / 4],
                  *(void **)a0);
        if (len == 0 || len == -1) break;
        INFLATE_STATE(a0)[0x4C / 4] += len;
    } while (INFLATE_STATE(a0)[0x4C / 4] < 0x8000);
    if (INFLATE_STATE(a0)[0x4C / 4] == 0) return -1;
    INFLATE_STATE(a0)[0x50 / 4] = 1;
    return INFLATE_INBUF(a0)[0];
}
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
