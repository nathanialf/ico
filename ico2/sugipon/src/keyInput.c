#include "debug.h"
#include <eekernel.h>
#include "keyInput.h"
#include "main.h"
#include "pad.h"

/* the pad device descriptor InitKeyInput hands to iosPadDevInit */
static int keyInputPadDev[6] = {7, 2, 0, 0, 0, 0}; /* derived name */

void InitKeyInput(void)
{
    int i;
    int j;

    debug_StdPrintfDummy("InitKeyInput2() in\n");
    debug_StdPrintfDummy("PadInit\n");
    iosPadDevInit(keyInputPadDev);
    for (i = 0; i < 2; i++) {
        pad[i].old = 0;
        pad[i].flags = 0;
        pad[i].rel = 0;
        pad[i].rep = 0;
        for (j = 15; j >= 0; j--) {
            pad[i].hist[j] = 0;
        }
    }
    debug_StdPrintfDummy("InitKeyInput2() out\n");
    debug_StdPrintfDummy("signal to main\n");
    SignalSema(IosPadLock);
}

/* the pad context iosPadConnect fills and iosPadRead updates (pad.c's
   IosPadCtx): the second copy of the held, triggered and released bits */
typedef struct PadBuf { /* field names derived */
    char pad0[24];
    int now2; /* 0x18 */
    int trg2; /* 0x1C */
    int rel2; /* 0x20 */
    char pad24[60];
} PadBuf; /* derived name */

extern PadConf iosPadConfDefault;

void ExecKeyInput(void)
{
    PadBuf buf;
    unsigned char stR[32];
    unsigned char stL[32];
    int i;
    unsigned int j;

    iosPadDevRead();
    for (i = 0; i < 2; i++) {
        pad[i].old = pad[i].now;
        iosPadConnect(&buf, 7, i, &iosPadConfDefault);
        iosPadRead(&buf);
        pad[i].now = buf.now2;
        pad[i].flags = buf.trg2;
        pad[i].rel = buf.rel2;
        pad[i].rep = 0;
        iosPadGetStick(&buf, stL, 1, 127, 127, 0);
        pad[i].ana[0] = stL[0];
        pad[i].ana[1] = stL[4];
        iosPadGetStick(&buf, stR, 0, 127, 127, 0);
        pad[i].ana[2] = stR[0];
        pad[i].ana[3] = stR[4];
        for (j = 0; j < 16; j++) {
            if ((pad[i].now >> j) & 1) {
                pad[i].hist[j]++;
            } else {
                pad[i].hist[j] = 0;
            }
            if (pad[i].hist[j] == 1 ||
                (float)pad[i].hist[j] >
                    (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 20.0f) {
                pad[i].rep |= 1 << j;
            } else {
                pad[i].rep &= ~(1 << j);
            }
        }
    }
}
