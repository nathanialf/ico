#include "common.h"
#include "debug.h"
#include <eekernel.h>

/* one 0x58-byte pad record; the engine keeps two of them */
/* kept local: this TU's bytes only come out with its own view of Pad. */
typedef struct Pad {
    int now;               /* 0x00  buttons this frame */
    int f04;               /* 0x04 */
    int f08;               /* 0x08 */
    int trg;               /* 0x0C  repeat/edge mask built below */
    int old;               /* 0x10  buttons last frame */
    unsigned int hist[16]; /* 0x14  per-button held-frame counter */
    unsigned char lx;      /* 0x54 */
    unsigned char ly;      /* 0x55 */
    unsigned char rx;      /* 0x56 */
    unsigned char ry;      /* 0x57 */
} Pad;

extern Pad D_0028F8F0[];

/* the pad device descriptor InitKeyInput hands to iosPadDevInit */
static int keyInputPadDev[6] = {7, 2, 0, 0, 0, 0};

extern int IosCdLock;
/* kept local: this TU's uses of iosPadDevInit do not fit the prototype in pad.h */
extern void iosPadDevInit(void *a0);

void InitKeyInput(void)
{
    int i;
    int j;

    debug_StdPrintfDummy("InitKeyInput2() in\n");
    debug_StdPrintfDummy("PadInit\n");
    iosPadDevInit(keyInputPadDev);
    for (i = 0; i < 2; i++) {
        D_0028F8F0[i].old = 0;
        D_0028F8F0[i].f04 = 0;
        D_0028F8F0[i].f08 = 0;
        D_0028F8F0[i].trg = 0;
        for (j = 15; j >= 0; j--) {
            D_0028F8F0[i].hist[j] = 0;
        }
    }
    debug_StdPrintfDummy("InitKeyInput2() out\n");
    debug_StdPrintfDummy("signal to main\n");
    SignalSema(IosCdLock);
}

typedef struct PadBuf {
    char _p0[0x18];
    int f18; /* 0x18 */
    int f1C; /* 0x1C */
    int f20; /* 0x20 */
    char _p24[0x60 - 0x24];
} PadBuf;

extern int D_0028F4C0[];
extern char iosPadConfDefault[];
/* kept local: this TU's uses of iosPadDevRead do not fit the prototype in pad.h */
extern void iosPadDevRead(void);
/* kept local: this TU's uses of iosPadConnect do not fit the prototype in pad.h */
extern void iosPadConnect(void *buf, int a1, int port, void *conf);
/* kept local: this TU's uses of iosPadRead do not fit the prototype in pad.h */
extern int iosPadRead(void *buf);
/* kept local: this TU's uses of iosPadGetStick do not fit the prototype in pad.h */
extern int iosPadGetStick(void *buf, void *dst, int which, int cx, int cy, int a5);

void ExecKeyInput(void)
{
    PadBuf buf;
    unsigned char stR[0x20];
    unsigned char stL[0x20];
    int i;
    unsigned int j;

    iosPadDevRead();
    for (i = 0; i < 2; i++) {
        D_0028F8F0[i].old = D_0028F8F0[i].now;
        iosPadConnect(&buf, 7, i, iosPadConfDefault);
        iosPadRead(&buf);
        D_0028F8F0[i].now = buf.f18;
        D_0028F8F0[i].f04 = buf.f1C;
        D_0028F8F0[i].f08 = buf.f20;
        D_0028F8F0[i].trg = 0;
        iosPadGetStick(&buf, stL, 1, 127, 127, 0);
        D_0028F8F0[i].lx = stL[0];
        D_0028F8F0[i].ly = stL[4];
        iosPadGetStick(&buf, stR, 0, 127, 127, 0);
        D_0028F8F0[i].rx = stR[0];
        D_0028F8F0[i].ry = stR[4];
        for (j = 0; j < 16; j++) {
            if ((D_0028F8F0[i].now >> j) & 1) {
                D_0028F8F0[i].hist[j]++;
            } else {
                D_0028F8F0[i].hist[j] = 0;
            }
            if (D_0028F8F0[i].hist[j] == 1 ||
                (float)D_0028F8F0[i].hist[j] >
                    (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f * 20.0f) {
                D_0028F8F0[i].trg |= 1 << j;
            } else {
                D_0028F8F0[i].trg &= ~(1 << j);
            }
        }
    }
}
