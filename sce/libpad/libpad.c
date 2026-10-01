/* libpad.a.  The archive's member boundaries in this build are not known,
 * so this file is the archive's whole run. */
#include <sifrpc.h>
#include <sifcmd.h>
#include <libpad.h>
#include <stdio.h>
#include <eekernel.h>
#include <string.h>

#define PAD_DEBUG 0 /* derived name */

struct S12 {
    char b[12];
};

/* The per-port, per-slot state record (0x1C bytes, padSlot[2][4]).  The
 * pointer fields are typed by what scePadPortOpen stores in them: the EE pad
 * DMA area the caller passes, this slot's command buffer (read back as an int
 * pointer by scePadSetActDirect), and the IOP-side buffer address the open
 * RPC returns, with the command buffer's type.  scePadInit clears the two
 * words at 0x14 and 0x18, which nothing else in the run reads. */
typedef struct {   /* derived name */
    void *dmaArea; /* 0x00 */
    int *cmdBuf;   /* 0x04 */
    int *iopBuf;   /* 0x08 */
    int dmaId;     /* 0x0C, the sceSifSetDma id _send_to_iop polls */
    int opened;    /* 0x10 */
    int word14;    /* 0x14 */
    int word18;    /* 0x18 */
} PadSlot;

/* the member's .data: the build stamp, the init flag scePadInit sets and
   scePadEnd clears, the flag every diagnostic print tests, and the names
   scePadStateIntToStr and scePadReqIntToStr copy out */
static char scePadVersion[16] = "PsIIlibpad  2200"; /* derived name */

static int padInited = 0; /* derived name */

static int padDebug = 1; /* derived name */

/* the member's .bss: the two RPC clients (padman's two servers), the slot
   records, each slot's 64-byte command buffer and the RPC buffer */
static sceSifRpcClientData padClient[2]; /* derived name */

static PadSlot padSlot[2][4]; /* derived name */

static int padCmd[2][4][16] __attribute__((aligned(64))); /* derived name */

static int padRpcBuf[32] __attribute__((aligned(64))); /* derived name */

/* The IOP send helper, libpad.o's first function (its first string is the
   member's first .rodata entry). */
void _send_to_iop(int a0, int a1)
{
    sceSifDmaData dma[16]; /* the frame holds sixteen transfer records; one is sent */

    int *cmd = padSlot[a0][a1].cmdBuf;
    int ret = sceSifDmaStat(padSlot[a0][a1].dmaId);

    if (ret >= 0) {
        if (padDebug != 0) {
            printf("libpad: sceSifSetDma faild\n");
        }
    } else {
        int n = *cmd + 1;
        int *v = padSlot[a0][a1].iopBuf + ((n & 1) << 3); /* the 32-byte half, iopBuf is int * */
        int r;
        if (PAD_DEBUG) {
            printf("libpad: tPadDma Structure Invalid\n");
        }
        *cmd = n;
        SyncDCache(cmd, (char *)cmd + 0x20);
        dma[0].src = (unsigned int)cmd;
        dma[0].dest = (unsigned int)v;
        dma[0].size = 0x20;
        dma[0].u.attr = 0;
        r = sceSifSetDma(dma, 1);
        if (r == 0) {
            if (padDebug != 0) {
                printf("libpad: sceSifSetDma faild\n");
            }
        }
        padSlot[a0][a1].dmaId = r;
    }
}

int scePadInit(int a0)
{
    int ver;
    int major;
    int i;

    padInited = 1;
    while (1) {
        sceSifBindRpc(&padClient[0], 0x80000100, 0);
        if (padClient[0].serve != 0) {
            break;
        }
        for (i = 0x10000; i != -1; i--) {}
    }
    while (1) {
        sceSifBindRpc(&padClient[1], 0x80000101, 0);
        if (padClient[1].serve != 0) {
            break;
        }
        for (i = 0x10000; i != -1; i--) {}
    }
    ver = scePadGetModVersion();
    major = ver >> 8;
    if (major != 4) {
        if (padDebug != 0) {
            printf("libpad: Module version mismatch ");
            printf("[libpad.a = %d.%d, padman.irx = %d.%d]\n", 4, 0, major, ver & 0xFF);
        }
        return 0;
    }
    return scePadInit2(a0);
}

int scePadInit2(int a0)
{
    int ret;
    int i;

    for (i = 0; i < 4; i++) {
        padSlot[0][i].opened = 0;
        padSlot[0][i].word18 = 0;
        padSlot[0][i].word14 = 0;
        padSlot[1][i].opened = 0;
        padSlot[1][i].word18 = 0;
        padSlot[1][i].word14 = 0;
    }
    padRpcBuf[0] = 0x10;
    padRpcBuf[4] = 0;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return padRpcBuf[3];
}

int scePadEnd(void)
{
    int ret;
    int val;
    padRpcBuf[0] = 0xF;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = padRpcBuf[3];
    if (val == 1) {
        padInited = 0;
    }
    return val;
}

int scePadPortOpen(int a0, int a1, void *a2)
{
    int ret;
    int val;
    int i;
    char *p;
    int *q;

    if (((unsigned int)a2 & 0x3F) != 0) {
        if (padDebug != 0) {
            printf("libpad: buffer addr is not 64 byte align. %08x\n", a2);
        }
        return 0;
    }
    if (padSlot[a0][a1].opened == 1) {
        if (padDebug != 0) {
            printf("libpad: pad port is already open [%d][%d]\n", a0, a1);
        }
        return 0;
    }
    p = (char *)a2;
    for (i = 0; i < 2; i++) {
        *(int *)(p + 0x58) = 0;
        p[0x70] = 5;
        p[0x71] = 2;
        p[0x67] = 0;
        memset(p, 0xFF, 0x20);
        *(int *)(p + 0x60) = 0;
        p += 0x80;
    }
    padRpcBuf[0] = 1;
    padRpcBuf[1] = a0;
    padRpcBuf[2] = a1;
    padRpcBuf[4] = (int)a2;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    /* q is this slot's command buffer, padCmd[2][4][16]; reply word 5 is
     * the IOP buffer address, read as a pointer. */
    q = padCmd[a0][a1];
    val = (int)*(void **)&padRpcBuf[5];
    padSlot[a0][a1].opened = 1;
    padSlot[a0][a1].iopBuf = (int *)val;
    padSlot[a0][a1].dmaArea = a2;
    padSlot[a0][a1].cmdBuf = q;
    q[0] = 0;
    padSlot[a0][a1].dmaId = 0;
    return padRpcBuf[3];
}

int scePadPortClose(int a0, int a1)
{
    int ret;

    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    padRpcBuf[0] = 0xE;
    padRpcBuf[1] = a0;
    padRpcBuf[2] = a1;
    padRpcBuf[4] = 1;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    padSlot[a0][a1].opened = 0;
    return padRpcBuf[3];
}

int scePadGetDmaStr(int a0, int a1)
{
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)padSlot + a1 * 0x1C + a0 * 0x70);
    SyncDCache((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}

int scePadGetFrameCount(int a0, int a1)
{
    int ret = 0;
    if (padSlot[a0][a1].opened == 0) {
        return ret;
    }
    return *(int *)(scePadGetDmaStr(a0, a1) + 0x58);
}

int scePadRead(int a0, int a1, int a2)
{
    int s0;
    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    s0 = scePadGetDmaStr(a0, a1);
    memcpy(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}

int scePadGetState(int a0, int a1)
{
    unsigned char *p;
    if (padSlot[a0][a1].opened == 0)
        return 0x63;
    p = (unsigned char *)scePadGetDmaStr(a0, a1);
    if (p[0x70] != 6)
        return p[0x70];
    if (p[0x71] == 2)
        return 5;
    return p[0x70];
}

static char *padStateStr[8] = {"DISCONNECT", "",        "FINDCTP1", "",
                               "",           "EXECCMD", "STABLE",   "ERROR"}; /* derived name */

void scePadStateIntToStr(unsigned int a0, char *a1)
{
    if (a0 < 8) {
        strcpy(a1, padStateStr[a0]);
    } else {
        strcpy(a1, "");
    }
}

int scePadSetReqState(int a0, int a1, int a2)
{
    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71] = a2;
    return 1;
}

int scePadGetReqState(int a0, int a1)
{
    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    return ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71];
}

static char *padReqStr[3] = {"COMPLETE", "FAILED", "BUSY"}; /* derived name */

void scePadReqIntToStr(unsigned int a0, char *a1)
{
    if (a0 < 4) {
        strcpy(a1, padReqStr[a0]);
    } else {
        strcpy(a1, "");
    }
}

/* the pad DMA buffer scePadGetDmaStr hands back, laid out from the offsets
   this TU's members use.  The actuator and combination tables are arrays of
   four-byte records.  Only the members these functions touch are named; the
   rest is padding. */
typedef struct {
    unsigned char f00[48];
    unsigned char act[4][4];  /* 0x30 */
    unsigned char comb[4][4]; /* 0x40 */
    unsigned char f50[20];
    unsigned char f64;
    unsigned char f65[5];
    unsigned char nact;  /* 0x6A */
    unsigned char ncomb; /* 0x6B */
    unsigned char f6C[6];
    unsigned char f72;
} PadDmaStr;

int scePadInfoAct(int a0, int a1, int a2, int a3)
{
    PadDmaStr *p;

    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    p = (PadDmaStr *)scePadGetDmaStr(a0, a1);
    if (p->f72 != 1) {
        return 0;
    }
    if (p->f64 < 2) {
        return 0;
    }
    if (a2 >= p->nact) {
        return 0;
    }
    if (a2 == -1) {
        return p->nact;
    }
    switch (a3) {
    case 1:
        return p->act[a2][0];
    case 2:
        return p->act[a2][1];
    case 3:
        return p->act[a2][2];
    case 4:
        return p->act[a2][3];
    }
    return 0;
}

int scePadInfoComb(int a0, int a1, int a2, int a3)
{
    PadDmaStr *p;

    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    p = (PadDmaStr *)scePadGetDmaStr(a0, a1);
    if (p->f72 != 1) {
        return 0;
    }
    if (p->f64 < 2) {
        return 0;
    }
    if (a2 == -1) {
        return p->ncomb;
    }
    if (a2 >= p->ncomb) {
        return 0;
    }
    switch (a3) {
    case -1:
        return p->comb[a2][0];
    case 0:
        return p->comb[a2][1];
    case 1:
        return p->comb[a2][2];
    case 2:
        return p->comb[a2][3];
    }
    return 0;
}

int scePadInfoMode(int a0, int a1, int a2, int a3)
{
    int q;
    int t72;
    int v;

    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    q = scePadGetDmaStr(a0, a1);
    t72 = *(unsigned char *)(q + 0x72);
    if (t72 == 1 && *(unsigned char *)(q + 0x71) != 2) {
        if (a2 == 2) {
            goto case2;
        }
        if (a2 >= 3) {
            goto ge3;
        }
        if (a2 == t72) {
            goto case1;
        }
        return 0;
    ge3:
        if (a2 == 3) {
            goto case3;
        }
        if (a2 == 4) {
            goto case4;
        }
        return 0;
    case1:
        v = *(unsigned char *)(q + 0x65);
        if (v == 0xF3) {
            return 0;
        }
        return v >> 4;
    case2:
        if (*(unsigned char *)(q + 0x64) == t72) {
            return 0;
        }
        return *(unsigned short *)(q + (*(unsigned char *)(q + 0x69) << 1) + 0x50);
    case3:
        if (*(unsigned char *)(q + 0x64) == t72) {
            return 0;
        }
        return *(unsigned char *)(q + 0x69);
    case4:
        if (*(unsigned char *)(q + 0x64) == t72) {
            return 0;
        }
        if (a3 == -1) {
            return *(unsigned char *)(q + 0x68);
        }
        if (a3 >= (int)*(unsigned char *)(q + 0x68)) {
            return 0;
        }
        return *(unsigned short *)(q + (a3 << 1) + 0x50);
    }
    return 0;
}

int scePadSetMainMode(int a0, int a1, int a2, int a3)
{
    int *s0 = padRpcBuf;
    void *local = 0;
    int ret;
    int s;
    padRpcBuf[0] = 6;
    s0[1] = a0;
    s0[2] = a1;
    s0[3] = a2;
    s0[4] = a3;
    ret = sceSifCallRpc(&padClient[0], 1, 0, s0, 0x80, s0, 0x80, 0, local);
    if (ret < 0) {
        return 0;
    }
    s = s0[5];
    if (s == 1) {
        scePadSetReqState(a0, a1, 2);
        s = s0[5];
    }
    return s;
}

int scePadSetActDirect(int a0, int a1, unsigned char *a2)
{
    int *p;
    unsigned char *q;
    int i;

    if (((unsigned char *)scePadGetDmaStr(a0, a1))[0x72] != 1) {
        return 0;
    }
    p = padSlot[a0][a1].cmdBuf;
    q = (unsigned char *)p + 0xC;
    for (i = 0; i < 6; i++) {
        q[i] = a2[i];
    }
    p[2] = 6;
    p[1] = 1;
    _send_to_iop(a0, a1);
    return 1;
}

int scePadSetActAlign(int a0, int a1, char *a2)
{
    int *buf = padRpcBuf;
    int i;
    int val;
    int ret;
    char *dst;
    padRpcBuf[0] = 8;
    buf[1] = a0;
    buf[2] = a1;
    dst = (char *)buf + 0xC;
    for (i = 0; i < 6; i++) {
        dst[i] = a2[i];
    }
    ret = sceSifCallRpc(&padClient[0], 1, 0, buf, 0x80, buf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = buf[5];
    if (val == 1) {
        scePadSetReqState(a0, a1, 2);
        val = buf[5];
    }
    return val;
}

int scePadGetButtonMask(int a0, int a1)
{
    unsigned char *p;

    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    p = (unsigned char *)scePadGetDmaStr(a0, a1);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x64] < 2) {
        return 0;
    }
    if (p[0x66] < 2) {
        return 0;
    }
    return (long long)p[0x79] + ((long long)p[0x7A] << 8) + ((long long)p[0x7B] << 16) +
           ((long long)p[0x7C] << 24);
}

int scePadSetButtonInfo(int a0, int a1, int a2)
{
    int ret;
    padRpcBuf[3] = a2;
    padRpcBuf[0] = 0xA;
    padRpcBuf[1] = a0;
    padRpcBuf[2] = a1;
    if (sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0) < 0) {
        return 0;
    }
    ret = padRpcBuf[4];
    if (ret == 1) {
        scePadSetReqState(a0, a1, 2);
        ret = padRpcBuf[4];
    }
    return ret;
}

int scePadInfoPressMode(int a0, int a1)
{
    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    return scePadGetButtonMask(a0, a1) == 0x3FFFF;
}

int scePadEnterPressMode(int a0, int a1)
{
    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0xFFF);
}

int scePadExitPressMode(int a0, int a1)
{
    if (padSlot[a0][a1].opened == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0);
}

int scePadSetVrefParam(int a0, int a1, void *a2)
{
    int r;
    padRpcBuf[1] = a0;
    padRpcBuf[0] = 0xB;
    padRpcBuf[2] = a1;
    *(struct S12 *)((char *)padRpcBuf + 0xC) = *(struct S12 *)a2;
    r = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    if (padRpcBuf[7] == 1) {
        scePadSetReqState(a0, a1, 2);
    }
    return padRpcBuf[7];
}

int scePadGetPortMax(void)
{
    int ret;
    padRpcBuf[0] = 0xC;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return padRpcBuf[3];
}

int scePadGetSlotMax(int a0)
{
    int ret;
    padRpcBuf[0] = 0xD;
    padRpcBuf[1] = a0;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return padRpcBuf[3];
}

int scePadGetModVersion(void)
{
    int ret;
    padRpcBuf[0] = 0x12;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return padRpcBuf[3];
}

int scePadSetWarningLevel(int a0)
{
    int ret;
    padRpcBuf[0] = 0x14;
    padRpcBuf[1] = a0;
    ret = sceSifCallRpc(&padClient[0], 1, 0, padRpcBuf, 0x80, padRpcBuf, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return padRpcBuf[2];
}
