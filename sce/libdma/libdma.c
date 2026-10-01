/* libdma.a.  The archive's member boundaries in this build are not known,
 * so this file is the archive's whole run. */
#include <stdio.h>
#include <eeregs.h>
#include <libdma.h>
#include <libvu0_internal.h>

/* The member's .data in link order (0xAC): the globals dch and
 * sceDmaDebugMode, the build stamp, sceDmaReset's channel list and
 * sceDmaPutEnv's three D_CTRL code tables, then the global sceDmaCurrentEnv. */
/* The ten channel register blocks, VIF0 to toSPR. */
DmaChan *dch[10] = {
    (DmaChan *)D0_CHCR, (DmaChan *)D1_CHCR, (DmaChan *)D2_CHCR, (DmaChan *)D3_CHCR,
    (DmaChan *)D4_CHCR, (DmaChan *)D5_CHCR, (DmaChan *)D6_CHCR, (DmaChan *)D7_CHCR,
    (DmaChan *)D8_CHCR, (DmaChan *)D9_CHCR,
};

int sceDmaDebugMode = 0;

/* libdma.a's build stamp, exactly sixteen characters with no terminator. */
static char sceDmaVersion[16] = "PsIIlibdma  2200"; /* derived name */

/* Which channels sceDmaReset clears: all but the three SIF channels. */
static int resetChan[10] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1}; /* derived name */

/* sceDmaPutEnv's lookups from the DmaEnv's first three bytes to the D_CTRL
 * MFD, STS and STD field codes. */
static unsigned char mfdCode[16] = {0, 0, 0, 3, 0, 1, 0, 0, 2}; /* derived name */

static unsigned char stsCode[16] = {0, 1, 2, 0, 0, 0, 3}; /* derived name */

static unsigned char stdCode[16] = {0, 2, 3}; /* derived name */

DmaEnv sceDmaCurrentEnv = {0};

DmaChan *sceDmaGetChan(unsigned int a0)
{
    if (a0 < 0xA) {
        return dch[a0];
    }
    return 0;
}

int sceDmaReset(int mode)
{
    DmaEnv env;
    int old;
    int i;

    old = *D_CTRL & 1;
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
    *D_STAT = 0xFF1F;
    *(int *)D_STAT = *D_STAT & 0xFF1F0000;
    memclr(&env, 0x14);
    sceDmaPutEnv(&env);
    if (mode == 1) {
        *D_CTRL = *D_CTRL | 1;
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
    int ctrl = *D_CTRL;
    int pcr = *D_PCR;
    int sqwc = *D_SQWC;
    int rbor = *D_RBOR;
    int rbsr = *D_RBSR;

    if (env->mfd >= 10) {
        return -1;
    }
    if (env->sts >= 10) {
        return -2;
    }
    if (env->std >= 10) {
        return -3;
    }
    if (env->rcyc >= 7) {
        return -4;
    }
    ctrl = (ctrl & 0xFFFFFFCF) | (mfdCode[env->mfd] << 4);
    ctrl = (ctrl & 0xFFFFFF3F) | (stsCode[env->sts] << 6);
    ctrl = (ctrl & 0xFFFFFFF3) | (stdCode[env->std] << 2);
    if (env->rcyc != 0) {
        ctrl |= 2;
        ctrl = (ctrl & 0xFFFFFCFF) | ((env->rcyc - 1) << 8);
    } else {
        ctrl &= 0xFFFFFFFD;
    }
    pcr = (env->cde << 16) | env->cpc;
    sqwc = (env->tqwc << 16) | env->sqwc;
    rbor = (int)env->rbadr;
    rbsr = env->rbsize;
    *D_CTRL = ctrl;
    *D_PCR = pcr;
    *D_SQWC = sqwc;
    *D_RBOR = rbor;
    *D_RBSR = rbsr;
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
    int old = *D_STADR;

    if (addr != 0xFFFFFFFF) {
        *D_STADR = addr;
    }
    return old;
}

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
