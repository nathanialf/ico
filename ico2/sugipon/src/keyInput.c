#include "common.h"

/* one 0x58-byte pad record; the engine keeps two of them */
typedef struct Pad {
    int now;               /* 0x00 — buttons this frame */
    int f04;               /* 0x04 */
    int f08;               /* 0x08 */
    int trg;               /* 0x0C — repeat/edge mask built below */
    int old;               /* 0x10 — buttons last frame */
    unsigned int hist[16]; /* 0x14 — per-button held-frame counter */
    unsigned char lx;      /* 0x54 */
    unsigned char ly;      /* 0x55 */
    unsigned char rx;      /* 0x56 */
    unsigned char ry;      /* 0x57 */
} Pad;

extern Pad D_0028F8F0[];
extern char D_0028FED0[];
extern char D_0054D7F8[];
extern char D_0054D810[];
extern char D_0054D820[];
extern char D_0054D838[];
extern int IosCdLock;
extern void debug_StdPrintfDummy();
extern void iosPadDevInit(void *a0);
extern void SignalSema(int sema);

void InitKeyInput(void)
{
    int i;
    int j;

    debug_StdPrintfDummy(D_0054D7F8);
    debug_StdPrintfDummy(D_0054D810);
    iosPadDevInit(D_0028FED0);
    for (i = 0; i < 2; i++) {
        D_0028F8F0[i].old = 0;
        D_0028F8F0[i].f04 = 0;
        D_0028F8F0[i].f08 = 0;
        D_0028F8F0[i].trg = 0;
        for (j = 15; j >= 0; j--) {
            D_0028F8F0[i].hist[j] = 0;
        }
    }
    debug_StdPrintfDummy(D_0054D820);
    debug_StdPrintfDummy(D_0054D838);
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
extern void iosPadDevRead(void);
extern void iosPadConnect(void *buf, int a1, int port, void *conf);
extern int iosPadRead(void *buf);
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
