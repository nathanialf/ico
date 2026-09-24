/* Vendor SCE library run.  The archive attribution (libdma.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"
#include <stdio.h>

typedef struct {
    unsigned char chan; /* 0x00 channel number */
    unsigned char b01;  /* 0x01 */
    unsigned char b02;  /* 0x02 */
    unsigned char b03;  /* 0x03 release level, 0 = off */
    unsigned short h04; /* 0x04 */
    unsigned short h06; /* 0x06 */
    unsigned short h08; /* 0x08 */
    unsigned short h0A; /* 0x0A */
    void *rbadr;        /* 0x0C ring buffer address, to D_RBOR */
    int rbsize;         /* 0x10 ring buffer size, to D_RBSR */
} DmaEnv;

/* The member's .data in ROM order (= MAIN.MAP libdma.o .data 0xAC, which
 * names the three globals dch, sceDmaDebugMode and sceDmaCurrentEnv). */
/* The ten channel register blocks, VIF0 to toSPR. */
int dch[10] = {
    0x10008000, 0x10009000, 0x1000A000, 0x1000B000, 0x1000B400,
    0x1000C000, 0x1000C400, 0x1000C800, 0x1000D000, 0x1000D400,
};

int sceDmaDebugMode = 0;

/* libdma.a's build stamp, exactly sixteen characters with no terminator. */
static char sceDmaVersion[16] = "PsIIlibdma  2200";

/* Which channels sceDmaReset clears: all but the three SIF channels. */
static int resetChan[10] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1};

/* sceDmaPutEnv's lookups from the DmaEnv's first three bytes to the D_CTRL
 * MFD, STS and STD field codes. */
static unsigned char mfdCode[16] = {0, 0, 0, 3, 0, 1, 0, 0, 2};

static unsigned char stsCode[16] = {0, 1, 2, 0, 0, 0, 3};

static unsigned char stdCode[16] = {0, 2, 3};

DmaEnv sceDmaCurrentEnv = {0};

int sceDmaGetChan(unsigned int a0)
{
    if (a0 < 0xA) {
        return dch[a0];
    }
    return 0;
}

extern void memclr(void *p, int n);
extern int sceDmaPutEnv(DmaEnv *env);

int sceDmaReset(int mode)
{
    DmaEnv env;
    int old;
    int i;

    old = *(volatile int *)0x1000E000 & 1;
    for (i = 0; i < 10; i++) {
        if (resetChan[i] != 0) {
            int *ch = (int *)dch[i];
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

int sceDmaDebug(int a0)
{
    int old = sceDmaDebugMode;
    sceDmaDebugMode = a0;
    return old;
}

int sceDmaPutEnv(DmaEnv *env)
{
    int ctrl = *(volatile int *)0x1000E000;
    int pcr = *(volatile int *)0x1000E020;
    int sqwc = *(volatile int *)0x1000E030;
    int rbor = *(volatile int *)0x1000E050;
    int rbsr = *(volatile int *)0x1000E040;

    if (env->chan >= 10) {
        return -1;
    }
    if (env->b01 >= 10) {
        return -2;
    }
    if (env->b02 >= 10) {
        return -3;
    }
    if (env->b03 >= 7) {
        return -4;
    }
    ctrl = (ctrl & 0xFFFFFFCF) | (mfdCode[env->chan] << 4);
    ctrl = (ctrl & 0xFFFFFF3F) | (stsCode[env->b01] << 6);
    ctrl = (ctrl & 0xFFFFFFF3) | (stdCode[env->b02] << 2);
    if (env->b03 != 0) {
        ctrl |= 2;
        ctrl = (ctrl & 0xFFFFFCFF) | ((env->b03 - 1) << 8);
    } else {
        ctrl &= 0xFFFFFFFD;
    }
    pcr = (env->h04 << 16) | env->h06;
    sqwc = (env->h0A << 16) | env->h08;
    rbor = (int)env->rbadr;
    rbsr = env->rbsize;
    *(volatile int *)0x1000E000 = ctrl;
    *(volatile int *)0x1000E020 = pcr;
    *(volatile int *)0x1000E030 = sqwc;
    *(volatile int *)0x1000E050 = rbor;
    *(volatile int *)0x1000E040 = rbsr;
    sceDmaCurrentEnv = *env;
    return 0;
}

DmaEnv *sceDmaGetEnv(DmaEnv *a0)
{
    *a0 = sceDmaCurrentEnv;
    return a0;
}

/* 0x1000E060 is the DMAC stall address register (D_STADR). */
int sceDmaPutStallAddr(unsigned int addr)
{
    int old = *(volatile int *)0x1000E060;

    if (addr != 0xFFFFFFFF) {
        *(volatile int *)0x1000E060 = addr;
    }
    return old;
}

typedef struct DmaChan {
    volatile int chcr; /* 0x00 */
    int pad0[3];
    int madr; /* 0x10 */
    int pad1[3];
    int qwc; /* 0x20 */
    int pad2[3];
    int tadr; /* 0x30 */
} DmaChan;

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
