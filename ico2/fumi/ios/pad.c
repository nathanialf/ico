#include "common.h"
#include "pad.h"
#include "message.h"
#include "shockdriver.h"
#include "Matrix.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"

/* One sampled pad buffer: the two button bytes the device leaves at +2 and
   +3, active low. */
typedef struct {
    unsigned char _0[2];
    unsigned char hi; /* 0x02 */
    unsigned char lo; /* 0x03 */
    unsigned char rx; /* 0x04 */
    unsigned char ry; /* 0x05 */
    unsigned char lx; /* 0x06 */
    unsigned char ly; /* 0x07 */
    unsigned char _8[0x18];
} IosPadBuf;

/* The device record iosPadDev carries one of per port: the buffer the last
   read filled is chosen by the index at +0xC, and +0x194 is set while the
   port has no controller. */
typedef struct {
    char _0[0x10];
    unsigned char motor0; /* 0x10 */
    unsigned char motor1; /* 0x11 */
    char _12[0x2];
    int f14; /* 0x14 */
} IosPadShock;

typedef struct {
    int port;         /* 0x00 */
    int slot;         /* 0x04 */
    int f8;           /* 0x08 */
    int idx;          /* 0x0C */
    IosPadBuf buf[2]; /* 0x10 */
    char _50[0x130];
    int f180; /* 0x180 */
    int f184; /* 0x184 */
    int f188; /* 0x188 */
    int f18C; /* 0x18C */
    int _190;
    unsigned int error;   /* 0x194 */
    unsigned char act[6]; /* 0x198 */
    char _19e[0x6];
    IosPadShock shock; /* 0x1A4 */
    char _1bc[0x4];
    unsigned long long f1C0; /* 0x1C0 */
} IosPadDevRec;

/* The caller's pad handle, the record iosPadConnect fills in. */
typedef struct {
    IosPadDevRec *dev; /* 0x00 */
    char *conf;        /* 0x04 */
    int now;           /* 0x08 */
    int trg;           /* 0x0C */
    int rel;           /* 0x10 */
    int f14;           /* 0x14 */
    int now2;          /* 0x18 */
    int trg2;          /* 0x1C */
    int rel2;          /* 0x20 */
    int f24;           /* 0x24 */
} IosPadCtx;

/* The stick reading iosPadGetStick hands back: the raw pair at +0 and +4 and
   the normalised direction and magnitude the reader wants. */
typedef struct {
    int x;     /* 0x00 */
    int y;     /* 0x04 */
    int _8;    /* 0x08 */
    float dx;  /* 0x0C */
    float dz;  /* 0x10 */
    float mag; /* 0x14 */
    char _18[8];
} IosPadStick;

typedef struct {
    unsigned char mode;
    unsigned char b1;
    unsigned char volume;
    unsigned char b3;
} ShockPrm;

typedef struct {
    int key;              /* 0x00 */
    int box;              /* 0x04 */
    int player;           /* 0x08 */
    ShockPrm prm;         /* 0x0C */
    short life;           /* 0x10 */
    short tick;           /* 0x12 */
    unsigned char volume; /* 0x14 */
    unsigned char pad[3];
} PadAct;

extern int Shock_Request(int box, int player, ShockPrm prm, int key, int a4);

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/ios/pad", controler_stable_check);

/* The pad configuration record: 60 words, the same PadConf src/act.c copies
   into the actor work block. */
typedef struct {
    int w[60];
} PadConf;

extern unsigned char iosPadDev[];
extern PadConf iosPadConfDefault;
extern PadConf iosPadConfCustom;
extern char th_iosPadDevManager[];
extern int D_0063A428;
extern char D_00551BD8[];
extern char D_00551D28[];
extern char D_00551D38[];
extern char D_0063A5B8[];
extern int iosThreadCreateS(void *th, int prio, void *func, int arg, int stack, int size,
                            int flags);
extern void iosThreadStart(void *th);
extern int scePadInit(int mode);
extern int scePadPortOpen(int port, int slot, void *buf);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *msg);
void iosPadDevManager(void);

int iosPadDevInit(void *a0)
{
    int i;

    iosThreadCreateS(th_iosPadDevManager, 10, iosPadDevManager, 0, D_0063A428, 4096, 17);
    iosThreadStart(th_iosPadDevManager);

    if (scePadInit(0) != 1) {
        debug_StdPrintfDummy(D_00551D28);
        debug_assert(D_00551BD8, 553);
        __assert(D_00551BD8, 553, D_0063A5B8);
        return 0;
    }
    for (i = 0; i < 2; i++) {
        IosPadDevRec *dev = (IosPadDevRec *)&iosPadDev[i * 0x200];

        dev->port = i;
        dev->slot = 0;
        dev->f184 = 0;
        dev->error = 0xFFFFFFFFu;
        dev->f180 = 0xFFFF;
        if (scePadPortOpen(i, 0, (char *)dev + 128) == 0) {
            debug_StdPrintfDummy(D_00551D38, i, 0);
            debug_assert(D_00551BD8, 569);
            __assert(D_00551BD8, 569, D_0063A5B8);
        }
    }
    iosPadConfCustom = iosPadConfDefault;
    return 1;
}

/* the frame counter this TU reads unsigned: the ROM divides it with divu */
extern unsigned int frame_count;
extern char D_00551D60[];
extern char D_00551D80[];
extern char D_0063A5C0[];
extern int scePadRead(int port, int slot, void *buf);
extern int scePadGetState(int port, int slot);
extern void Shock_Decode(void *box, unsigned char *pFlags, unsigned char *pLevel);
extern void Shock_SetMotor(int flags, int level, void *box, int port, int slot);
extern int controler_stable_check(void *dev);
void iosPadActTickProc(void);

int iosPadDevReadFunc(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        IosPadDevRec *dev = (IosPadDevRec *)&iosPadDev[i * 0x200];
        IosPadShock *sh;
        int port;

        dev->idx ^= 1;
        if (dev->f184 == 99) {
            dev->error = 0;
        }
        if (dev->error != 0) {
            controler_stable_check(dev);
            if (frame_count % 120 == 0) {
                debug_StdPrintfDummy(D_00551D60);
                debug_StdPrintfDummy(D_00551D80, dev->port, dev->slot);
            }
        } else {
            if (scePadRead(dev->port, dev->slot, &dev->buf[dev->idx]) == 0) {
                debug_StdPrintfDummy(D_0063A5C0, scePadGetState(dev->port, dev->slot));
                if (scePadGetState(dev->port, dev->slot) == 0) {
                    dev->f184 = 0;
                    dev->error = 1;
                }
            } else {
                IosPadBuf *b = &dev->buf[dev->idx];
                unsigned int t = (*(unsigned int *)b >> 12) & 0xF;

                if (t != 7 && t != 5) {
                    b->rx = b->ry = b->lx = b->ly = 127;
                }
            }
        }
        sh = &dev->shock;
        port = dev->port;
        Shock_Decode(sh, &dev->shock.motor0, &dev->shock.motor1);
        if (((*(unsigned int *)((char *)dev + (dev->idx << 5) + 0x10) >> 12) & 0xF) != 7 ||
            dev->error != 0) {
            port = -1;
        }
        Shock_SetMotor(sh->motor0, sh->motor1, &dev->shock.f14, port, dev->slot);
    }
    iosPadActTickProc();
    return 0;
}

extern int D_0063C19C;
extern int D_0063B244;

int iosPadRead(void *pad)
{
    IosPadCtx *ctx = (IosPadCtx *)pad;
    IosPadDevRec *dev = ctx->dev;
    IosPadBuf *prev;
    IosPadBuf *cur;
    int pbits;
    int cbits;
    int old;
    int now;
    int i;

    prev = &dev->buf[dev->idx ^ 1];
    cur = &dev->buf[dev->idx];

    pbits = ((prev->hi << 8) | prev->lo) ^ 0xFFFF;
    cbits = ((cur->hi << 8) | cur->lo) ^ 0xFFFF;

    old = 0;
    now = 0;

    for (i = 0; i < 16; i++) {
        if ((pbits >> i) & 1) {
            old |= *(int *)(ctx->conf + (i << 2) + 0xB0);
        }
        if ((cbits >> i) & 1) {
            now |= *(int *)(ctx->conf + (i << 2) + 0xB0);
        }
    }

    ctx->now = now;
    ctx->trg = (now ^ old) & now;
    ctx->rel = (now ^ old) & old;

    ctx->now2 = now;
    ctx->trg2 = ctx->trg;
    ctx->rel2 = ctx->rel;
    ctx->f24 = ctx->f14;

    if (dev->error != 0) {
        ctx->now = 0;
        ctx->trg = 0;
        ctx->rel = 0;
        ctx->f14 = 0;

        ctx->now2 = 0;
        ctx->trg2 = 0;
        ctx->rel2 = 0;
        ctx->f24 = 0;
        return 0;
    }
    if (D_0063C19C == 0) {
        int mask = D_0063B244 != 0 ? 2 : 0;
        ctx->now &= mask;
        ctx->trg &= mask;
        ctx->rel &= mask;
        ctx->f14 &= mask;
    }
    return 0;
}

extern float FSqrt(float x);
extern void sceVu0Normalize(void *dst, void *src);
extern float _GetDirection(void *v);

float iosPadNormalizeStick(void *p)
{
    IosPadStick *st = (IosPadStick *)p;
    Vec4 v = {{(float)st->x - 127.5f, 0.0f, (float)st->y - 127.5f, 0.0f}};
    float len;

    len = FSqrt(v.f[0] * v.f[0] + v.f[2] * v.f[2]);

    if (len <= 48.0f) {
        st->dx = 0.0f;
        st->dz = 0.0f;
        return st->dx;
    }
    {
        Vec4 n;

        sceVu0Normalize(&n, &v);
        st->dx = n.f[0];
        st->dz = n.f[2];
    }
    if (48.0f < len) {
        int deg = (int)(_GetDirection(&v) / 3.14159274f * 180.0f);
        int m;
        int d;

        m = (deg < 0 ? -deg : deg) % 90;
        d = m < 46 ? m : 90 - m;
        len = len / ((float)d * 0.2f / 45.0f + 1.0f);
        if (len < 48.0f) {
            len = 48.0f;
        }
    }
    if (120.0f <= len) {
        return 1.0f;
    }
    return (len - 48.0f) / 72.0f;
}

int iosPadGetStick_func(void *dev, void *out, int mode, int a3, int a4, int a5)
{
    IosPadCtx *ctx = (IosPadCtx *)dev;
    IosPadStick *st = (IosPadStick *)out;
    IosPadDevRec *rec = ctx->dev;
    IosPadBuf *buf = &rec->buf[rec->idx];
    float ox;
    float oy;

    if (rec->error != 0) {
        st->x = 127;
        st->y = 127;
        st->mag = 0.0f;
        return 0;
    }
    switch (mode) {
    case 1:
        st->x = buf->rx;
        st->y = buf->ry;
        st->mag = iosPadNormalizeStick(st);
        break;
    case 0:
        ox = (float)st->x;
        oy = (float)st->y;

        st->x = buf->lx;
        st->y = buf->ly;
        st->mag = iosPadNormalizeStick(st);

        if (st->mag == 0.0f && a5 != 0) {
            st->x = (int)ox;
            st->y = (int)oy;

            if (ctx->now & 0x2000) {
                st->x = (int)((float)(st->x + 255) * 0.5f);
            } else if (ctx->now & 0x8000) {
                st->x = (int)((float)st->x * 0.5f);
            } else {
                st->x = (int)((float)(st->x + 127) * 0.5f);
            }
            if (ctx->now & 0x1000) {
                st->y = (int)((float)st->y * 0.5f);
            } else if (ctx->now & 0x4000) {
                st->y = (int)((float)(st->y + 255) * 0.5f);
            } else {
                st->y = (int)((float)(st->y + 127) * 0.5f);
            }
            st->mag = iosPadNormalizeStick(st);
        }
        break;
    }
    return 0;
}

/* The act table search the listing inlines into iosPadActRequest,
   iosPadActStop and iosPadActVolumeSet alike (pad.c:1038-1045); here the key
   searched for is 0, so the compare folds to a beqz. */

/* .bss, owned by pad.o (MAIN.MAP sizes the run 0x1A0 and names no symbol
   in it), in the ROM's run order: the device manager's message queue buffer and
   the sixteen actuator requests iosPadActRequest hands out. */
/* */
static int padDevMgrMsgBuf[8];

static PadAct padActs[16];

extern int D_0063A538;
extern int D_0063A5C8;

/* The per-request definition table: eight bytes an entry, read through the
   request index. */
typedef struct {
    int _0;              /* 0x00 */
    short player;        /* 0x04 */
    unsigned short life; /* 0x06 */
} PadActDef;

extern PadActDef D_005F5C70[];

/* the pad device the request hangs off: only the shock box pointer at +0 is read */
typedef struct {
    char *box;
} PadDev;

int iosPadActRequest(int port, int id)
{
    PadAct *p = (PadAct *)padActs;
    PadAct *entry;
    int i = 0xF;

    while (1) {
        if (p->key == 0) {
            goto found;
        }
        i--;
        if (i == -1) {
            goto notfound;
        }
        p = (PadAct *)((char *)p + 0x18);
    }
notfound:
    entry = 0;
    goto go;
found:
    entry = p;
go:
    if (port == 0 || D_0063A538 == 0 || entry == 0) {
        return 0;
    }
    entry->player = D_005F5C70[id].player;
    entry->life = D_005F5C70[id].life;
    entry->tick = 0;
    entry->box = (int)(((PadDev *)port)->box + 0x1A4);
    entry->prm.mode = entry->prm.b1 = 0;
    entry->prm.volume = 255;
    entry->volume = 255;
    entry->prm.b3 = 32;
    if (Shock_Request(entry->box, entry->player, entry->prm, D_0063A5C8, 0) == 0) {
        return 0;
    }
    entry->key = D_0063A5C8++;
    if (D_0063A5C8 == 0) {
        D_0063A5C8 = 1;
    }
    return *(int *)entry;
}

extern unsigned char padDevMgrMsgQ[];

int iosPadDevRead(void)
{
    iosMsgSend(padDevMgrMsgQ, 0, 0);
    return 0;
}

int iosPadGetPort(int a0, int a1)
{
    return *(int *)&iosPadDev[a1 * 0x200];
}

int iosPadGetSlot(int a0, int a1)
{
    int *base = (int *)&iosPadDev[a1 * 0x200];
    return base[1];
}

int iosPadGetDevice(int a, int b)
{
    int *p = iosPadDev;
    int count = 0;
    do {
        count++;
        if (p[0] == a) {
            if (p[1] == b) {
                return p[2];
            }
        }
        p = (int *)((char *)p + 0x200);
    } while (count < 2);
    return -1;
}

int iosPadConnect(void *a0, int a1, int a2, int a3)
{
    int *p = (int *)a0;
    p[1] = a3;
    p[0] = (int)&iosPadDev[a2 * 0x200];
    return 0;
}

int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5)
{
    int rv;
    _PushVu0Registers();
    rv = iosPadGetStick_func(dev, out, mode, a3, a4, a5);
    _PopVu0Registers();
    return rv;
}

extern int matrixptr;

void iosPadStickCameraCoord(void *a0, float *a1)
{
    Vec4 v = {{a1[3], 0.0f, -a1[4], 0.0f}};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    sceVu0ApplyMatrix(a0, m, &v);
}

void iosPadEnable(void)
{
    D_0063C19C = 1;
}

void iosPadDisable(void)
{
    D_0063C19C = 0;
}

int iosPadEnableGet(void)
{
    return D_0063C19C;
}

extern int ShockVoiceSetCommon;

void iosPadActInit(void)
{
    unsigned char *base;
    unsigned char *p;
    int i;
    memset(padActs, 0, sizeof(padActs));
    Init_Shock();
    Shock_SetShockVoiceSet(0, ShockVoiceSetCommon);
    base = iosPadDev;
    p = base + 0x1B8;
    i = 1;
    do {
        Init_Controler(p);
        i--;
        Init_Player(p - 0x14);
        p += 0x200;
    } while (i >= 0);
}

void iosPadActStop(int key)
{
    if (key == 0) {
        return;
    }
    for (;;) {
        int *p = (int *)padActs;
        int *entry;
        int i = 0xF;
        while (1) {
            if (*p == key) {
                goto found;
            }
            i--;
            if (i == -1) {
                goto notfound;
            }
            p = (int *)((char *)p + 0x18);
        }
    notfound:
        entry = 0;
        goto check;
    found:
        entry = p;
    check:
        if (entry == 0) {
            break;
        }
        ShockRequestBox_RequestCancel(entry[0x4 / 4], key);
        entry[0] = 0;
    }
}

void iosPadActStopAll(void)
{
    int *p = (int *)padActs;
    int i;
    for (i = 0xF; i != -1; i--) {
        int x = p[0];
        if (x != 0) {
            ShockRequestBox_RequestCancel(p[1], x);
            p[0] = 0;
        }
        p = (int *)((char *)p + 0x18);
    }
}

int *iosPadActVolumeSet(int key, unsigned int val)
{
    int *p = (int *)padActs;
    int *rv;
    int i;
    val = val & 0xFF;
    i = 0xF;
    while (1) {
        if (*p == key)
            goto found;
        i--;
        if (i == -1)
            goto notfound;
        p = (int *)((char *)p + 0x18);
    }
notfound:
    rv = 0;
    goto end;
found:
    rv = p;
end:
    if (rv != 0) {
        *(unsigned char *)((char *)rv + 0x14) = val;
    }
    return rv;
}

void iosPadDevManager(void)
{
    int local_buf;
    iosMsgQueueCreate(padDevMgrMsgQ, padDevMgrMsgBuf, 8);
    while (1) {
        iosMsgRecv(padDevMgrMsgQ, &local_buf, 1);
        iosPadDevReadFunc();
    }
}

typedef struct ShockRequest {
    ShockPrm prm; /* 0x00 */
    unsigned char pad[0x38];
    struct ShockRequest *org; /* 0x3C */
} ShockRequest;

static inline void setRequestVolume(ShockRequest *req, unsigned int volume)
{
    unsigned int v;
    v = volume * req->org->prm.volume / 255;
    if (v > 255) {
        v = 255;
    }
    req->prm.volume = v;
}

void iosPadActTickProc(void)
{
    PadAct *p = (PadAct *)padActs;
    int i;
    for (i = 0xF; i != -1; i--) {
        if (p->key != 0) {
            ShockRequest *req = ShockRequestBox_GetRequest(p->box, p->key);
            if (req == 0) {
                p->tick++;
                if (p->life == 0 || p->tick < p->life) {
                    Shock_Request(p->box, p->player, p->prm, p->key, 0);
                } else {
                    p->key = 0;
                }
            } else {
                setRequestVolume(req, p->volume);
            }
        }
        p++;
    }
}

void iosPadDisconWait(void) {}

void iosPadErrorWait(void) {}
