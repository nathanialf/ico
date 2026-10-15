#include "debug.h"
#include "pad.h"
#include "message.h"
#include "shockdriver.h"
#include "Matrix.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "debug_exception.h"
#include "matrixDrive.h"
#include "thread.h"
#include <libpad.h>
#include "gv.h"
#include "main.h"
#include <assert.h>
#include "include_asm.h"

/* the terminal id the reconnect check compares against, which nothing in the
   retail build writes, and the enable flag iosPadEnable and iosPadDisable
   set */
static int padTermId; /* derived name */

static int padEnabled; /* derived name */

/* .data: the default and custom configurations with the scePadGetState name
   table between them, the two device records, the manager thread record and
   its queue.
   .sdata: iosPadActRequestEnable, the state names of five bytes or fewer
   (emitted with the table, last entry first, as are the two longer ones in
   .rodata), the literals of controler_stable_check and the reads in
   first-use order, and the vibration request key. */
PadConf iosPadConfDefault = {
    {{5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120},
     {5, 120}},
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    {{30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5},
     {30, 5}},
    {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800,
     0x1000, 0x2000, 0x4000, 0x8000},
};

int iosPadActRequestEnable = 1;

static char *padStateName[8] = {/* derived name */
                                "DISCONNECT", "FINDPAD", "FINDCTP1", "",
                                "",           "EXECCMD", "STABLE",   "ERROR"};

PadConf iosPadConfCustom = {0};

IosPadDevRec iosPadDev[2] = {0};

IOSThread th_iosPadDevManager = {{0}};

IosMsgQueue padDevMgrMsgQ = {0};

INCLUDE_ASM(controler_stable_check);

static void iosPadDevManager(void);

INCLUDE_ASM(iosPadDevInit);

static void iosPadActTickProc(void);
static int iosPadDevReadFunc(void);

INCLUDE_ASM(iosPadDevReadFunc);

INCLUDE_ASM(iosPadRead);

float iosPadNormalizeStick(IosPadStick *st)
{
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
        int deg = (int)(_GetDirection(v.f) / 3.14159274f * 180.0f);
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

int iosPadGetStick(IosPadCtx *ctx, void *out, int mode, int a3, int a4, int simulate)
{
    IosPadStick *st = out;
    IosPadDevRec *rec = ctx->dev;
    IosPadBuf *buf = &rec->buf[rec->idx];
    float ox;
    float oy;

    if (rec->error == 1) {
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

        if (st->mag == 0.0f && simulate != 0) {
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

/* the device manager's message queue buffer and the sixteen actuator
   requests iosPadActRequest hands out */
static int padDevMgrMsgBuf[8]; /* derived name */

static PadAct padActs[16]; /* derived name */

static int padActKey = 1; /* derived name */

int iosPadActRequest(IosPadCtx *pad, int id)
{
    PadAct *p = padActs;
    PadAct *entry;
    int i = 15;

    while (1) {
        if (p->key == 0) {
            goto found;
        }
        i--;
        if (i == -1) {
            goto notfound;
        }
        p++;
    }
notfound:
    entry = 0;
    goto go;
found:
    entry = p;
go:
    if (pad == 0 || iosPadActRequestEnable == 0 || entry == 0) {
        return 0;
    }
    entry->voice = shockList[id].voice;
    entry->life = shockList[id].life;
    entry->tick = 0;
    entry->box = &pad->dev->shock.box;
    entry->prm.voice = entry->prm.waveId = 0;
    entry->prm.volume = 255;
    entry->volume = 255;
    entry->prm.timeScale = 32;
    if (Shock_Request(entry->box, entry->voice, entry->prm, padActKey, 0) == 0) {
        return 0;
    }
    entry->key = padActKey++;
    if (padActKey == 0) {
        padActKey = 1;
    }
    return entry->key;
}

int iosPadDevRead(void)
{
    iosMsgSend(&padDevMgrMsgQ, 0, 0);
    return 0;
}

int iosPadGetPort(int a0, int dev)
{
    return iosPadDev[dev].port;
}

int iosPadGetSlot(int a0, int dev)
{
    return iosPadDev[dev].slot;
}

int iosPadGetDevice(int port, int slot)
{
    int *p = (int *)iosPadDev;
    int count = 0;
    do {
        count++;
        if (p[0] == port) {
            if (p[1] == slot) {
                return p[2];
            }
        }
        p = (int *)((char *)p + 0x200);
    } while (count < 2);
    return -1;
}

int iosPadConnect(IosPadCtx *ctx, int a1, int port, PadConf *conf)
{
    ctx->conf = conf;
    ctx->dev = &iosPadDev[port];
    return 0;
}

void iosPadStickCameraCoord(void *out, IosPadStick *stick)
{
    Vec4 v = {{stick->dx, 0.0f, -stick->dz, 0.0f}};
    float m[16];
    sceVu0TransposeMatrix(m, (void *)((int)matrixptr + 0x80));
    sceVu0ApplyMatrix(out, m, &v);
}

void iosPadEnable(void)
{
    padEnabled = 1;
}

void iosPadDisable(void)
{
    padEnabled = 0;
}

int iosPadEnableGet(void)
{
    return padEnabled;
}

void iosPadActInit(void)
{
    IosPadDevRec *dev;
    int i;
    memset(padActs, 0, sizeof(padActs));
    Init_Shock();
    Shock_SetShockVoiceSet(0, ShockVoiceSetCommon);
    dev = iosPadDev;
    for (i = 0; i < 2; i++) {
        Init_Controler(&dev[i].shock.motor);
        Init_Player(&dev[i].shock.box);
    }
}

void iosPadActStop(int key)
{
    if (key == 0) {
        return;
    }
    for (;;) {
        PadAct *p = padActs;
        PadAct *entry;
        int i = 15;
        while (1) {
            if (p->key == key) {
                goto found;
            }
            i--;
            if (i == -1) {
                goto notfound;
            }
            p++;
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
        ShockRequestBox_RequestCancel(entry->box, key);
        entry->key = 0;
    }
}

void iosPadActStopAll(void)
{
    PadAct *p = padActs;
    int i;
    for (i = 15; i != -1; i--) {
        int key = p->key;
        if (key != 0) {
            ShockRequestBox_RequestCancel(p->box, key);
            p->key = 0;
        }
        p++;
    }
}

PadAct *iosPadActVolumeSet(int key, unsigned int val)
{
    PadAct *p = padActs;
    PadAct *rv;
    int i;
    val = val & 0xFF;
    i = 15;
    while (1) {
        if (p->key == key)
            goto found;
        i--;
        if (i == -1)
            goto notfound;
        p++;
    }
notfound:
    rv = 0;
    goto end;
found:
    rv = p;
end:
    if (rv != 0) {
        rv->volume = val;
    }
    return rv;
}

static void iosPadDevManager(void)
{
    int local_buf;
    iosMsgQueueCreate(&padDevMgrMsgQ, padDevMgrMsgBuf, 8);
    while (1) {
        iosMsgRecv(&padDevMgrMsgQ, &local_buf, 1);
        iosPadDevReadFunc();
    }
}

static inline void setRequestVolume(SHOCKREQUEST *req, unsigned int volume) /* derived name */
{
    unsigned int v;
    v = volume * req->org->volume / 255;
    if (v > 255) {
        v = 255;
    }
    req->volume = v;
}

static void iosPadActTickProc(void)
{
    PadAct *p = padActs;
    int i;
    for (i = 0xF; i != -1; i--) {
        if (p->key != 0) {
            SHOCKREQUEST *req = ShockRequestBox_GetRequest(p->box, p->key);
            if (req == 0) {
                p->tick++;
                if (p->life == 0 || p->tick < p->life) {
                    Shock_Request(p->box, p->voice, p->prm, p->key, 0);
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
