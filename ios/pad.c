#include "common.h"


extern int D_00633C90;
extern int D_00631950;
extern int *D_00632108;
extern void iWakeupThread(int);

int signal_handler(int a0) {
    if (a0 == 2) {
        volatile unsigned long long *reg = (volatile unsigned long long *)0x12001000;
        D_00631950 = (int)(((*reg >> 13) & 1) ^ 1);
        iWakeupThread(D_00632108[12]);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevInit);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevReadFunc);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadRead);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadNormalizeStick);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadGetStick);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadActRequest);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevRead);

extern unsigned char D_00281630[];
extern int iosMsgSend(void *a0, int a1, int a2);

int iosPadGetPort(void) {
    iosMsgSend(D_00281630, 0, 0);
    return 0;
}

extern unsigned char D_002811C0[];

int iosPadGetSlot(int a0, int a1) {
    return *(int *)&D_002811C0[a1 * 0x200];
}

int iosPadGetDevice(int a0, int a1) {
    int *base = (int *)&D_002811C0[a1 * 0x200];
    return base[1];
}

int iosPadConnect(int a, int b)
{
    int *p = D_002811C0;
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

int iosPadStickCameraCoord(void *a0, int a1, int a2, int a3) {
    int *p = (int *)a0;
    p[1] = a3;
    p[0] = (int)&D_002811C0[a2 * 0x200];
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadEnable);

void iosPadDisable(void)
{
    D_00633C90 = 1;
}

void iosPadEnableGet(void) {
    D_00633C90 = 0;
}

int iosPadActInit(void) {
    return D_00633C90;
}

extern int D_00632194;
extern unsigned char D_006A6DB0[];
extern void memset(void *a0, int a1, int a2);
extern void iosThreadDestroy();
extern void Init_Player(void *a0);
extern void iosThreadName(void *a0);
extern int Shock_SetShockVoiceSet(int a0, int a1);

void iosPadActStop(void) {
    unsigned char *base;
    unsigned char *p;
    int i;
    memset(D_006A6DB0, 0, 0x180);
    iosThreadDestroy();
    Shock_SetShockVoiceSet(0, D_00632194);
    base = D_002811C0;
    p = base + 0x1B8;
    i = 1;
    do {
        iosThreadName(p);
        i--;
        Init_Player(p - 0x14);
        p += 0x200;
    } while (i >= 0);
}

