/* Vendor SCE library run.  The archive attribution (libdma.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"

extern int D_0054A320[];

int sceDmaGetChan(unsigned int a0)
{
    if (a0 < 0xA) {
        return D_0054A320[a0];
    }
    return 0;
}

typedef struct {
    int w[5];
} DmaEnv;

extern int D_0054A360[];
extern void memclr(void *p, int n);
extern int sceDmaPutEnv(DmaEnv *env);

int sceDmaReset(int mode)
{
    DmaEnv env;
    int old;
    int i;

    old = *(volatile int *)0x1000E000 & 1;
    for (i = 0; i < 10; i++) {
        if (D_0054A360[i] != 0) {
            int *ch = (int *)D_0054A320[i];
            ch[0x00 / 4] = 0;
            ch[0x30 / 4] = 0;
            ch[0x10 / 4] = 0;
            ch[0x50 / 4] = 0;
            ch[0x40 / 4] = 0;
            ch[0x80 / 4] = 0;
        }
    }
    *(volatile int *)0x1000E010 = 0xFF1F;
    *(int *)0x1000E010 = *(volatile int *)0x1000E010 & 0xFF1F0000;
    memclr(&env, 0x14);
    sceDmaPutEnv(&env);
    if (mode == 1) {
        *(volatile int *)0x1000E000 = *(volatile int *)0x1000E000 | 1;
    }
    return old;
}

extern int D_0054A348[];

int sceDmaDebug(int a0)
{
    int old = D_0054A348[0];
    D_0054A348[0] = a0;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaPutEnv);

extern DmaEnv D_0054A3B8;

DmaEnv *sceDmaGetEnv(DmaEnv *a0)
{
    *a0 = D_0054A3B8;
    return a0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libdma/libdma", sceDmaPutStallAddr);

typedef struct DmaChan {
    volatile int chcr; /* 0x00 */
    int pad0[3];
    int madr; /* 0x10 */
    int pad1[3];
    int qwc; /* 0x20 */
    int pad2[3];
    int tadr; /* 0x30 */
} DmaChan;

extern int printf(const char *fmt, ...);

void sceDmaSend(DmaChan *ch, unsigned int addr)
{
    int n = 0x1000000;
    int v;
    int t;

    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    if ((unsigned int)ch->tadr != 0xFFFFFFFF) {
        ch->tadr = addr;
    }
    ch->qwc = 0;
    ch->chcr = (ch->chcr & ~0xC) | 0x105;
}

void sceDmaSendN(DmaChan *ch, unsigned int addr, int size)
{
    int n = 0x1000000;
    int v;
    int t;

    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    if ((unsigned int)ch->madr != 0xFFFFFFFF) {
        ch->madr = addr;
    }
    ch->qwc = size;
    ch->chcr = (ch->chcr & ~0xC) | 0x101;
}

void sceDmaSendI(DmaChan *ch, unsigned int addr, int size)
{
    int n = 0x1000000;
    int v;
    int t;

    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    if ((unsigned int)ch->madr != 0xFFFFFFFF) {
        ch->madr = addr;
    }
    ch->qwc = size;
    ch->chcr = (ch->chcr & ~0xC) | 0x109;
}

void sceDmaRecv(DmaChan *ch)
{
    int n = 0x1000000;
    int v;
    int t;

    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    ch->qwc = 0;
    ch->chcr = ((((ch->chcr & ~0xC) | 4) & ~1) | 0x100);
}

void sceDmaRecvN(DmaChan *ch, unsigned int addr, int size)
{
    int n = 0x1000000;
    int v;
    int t;
    int c;

    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    if ((unsigned int)ch->madr != 0xFFFFFFFF) {
        ch->madr = addr;
    }
    ch->qwc = size;
    c = ch->chcr;
    c &= ~0xC;
    c &= ~1;
    c |= 0x100;
    ch->chcr = c;
}

void sceDmaRecvI(DmaChan *ch, unsigned int addr, int size)
{
    int n = 0x1000000;
    int v;
    int t;

    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    if ((unsigned int)ch->madr != 0xFFFFFFFF) {
        ch->madr = addr;
    }
    ch->qwc = size;
    ch->chcr = (((ch->chcr & ~0xC) | 8) & ~1) | 0x100;
}

int sceDmaSync(DmaChan *ch, int mode, int n)
{
    int v;
    int t;

    if (mode == 1) {
        return ((unsigned int)ch->chcr >> 8) & 1;
    }
    if (n == 0) {
        n = 0x1000000;
    }
    while (ch->chcr & 0x100) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    return 0;
}

int sceDmaWatch(DmaChan *ch, unsigned int addr, int mode, int n)
{
    int v;
    int t;

    if (mode == 1) {
        return *(volatile unsigned int *)&ch->madr < addr;
    }
    if (n == 0) {
        n = 0x1000000;
    }
    while (*(volatile unsigned int *)&ch->madr < addr) {
        if (--n < 0) {
            printf("libdma: sync timeout\n");
            v = ch->chcr;
            if (((unsigned int)v >> 8) & 1) {
                do {
                    t = v & ~0x100;
                    v = t;
                } while (((unsigned int)v >> 8) & 1);
                ch->chcr = t;
            }
        }
    }
    return 0;
}

int sceDmaPause(void *a0)
{
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

int sceDmaRestart(void *a0)
{
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}
