#include "common.h"

extern int *D_0062A408;
extern int D_00629C50;
extern void iWakeupThread(int);

int signal_handler(int a0) {
    if (a0 == 2) {
        volatile unsigned long long *reg = (volatile unsigned long long *)0x12001000;
        D_00629C50 = (int)(((*reg >> 13) & 1) ^ 1);
        iWakeupThread(D_0062A408[12]);
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevReadFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadNormalizeStick);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadGetStick);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadActRequest);

typedef struct {
    int f0;
    int f4;
    int f8;
    char fC;
    char fD;
    char fE;
    char fF;
    short f10;
    short f12;
    char f14;
} PadDev;

typedef struct {
    char pad[4];
    short f4;
    unsigned short f6;
} StickCfg;

struct __attribute__((packed)) PkU { unsigned int v; };

extern int Shock_Request(int, int, unsigned int, int);
extern int D_005EBB90;
extern int D_0062A410;
extern int D_0062A48C;
extern unsigned char D_006A0930[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevRead);


extern int iosMsgSend(void *a0, int a1, int a2);
extern unsigned char D_0027D9B0[];

int iosPadGetPort(void) {
    iosMsgSend(D_0027D9B0, 0, 0);
    return 0;
}

extern unsigned char D_0027D540[];

int iosPadGetSlot(int a0, int a1) {
    return *(int *)&D_0027D540[a1 * 0x200];
}

int iosPadGetDevice(int a0, int a1) {
    int *base = (int *)&D_0027D540[a1 * 0x200];
    return base[1];
}

int iosPadConnect(int a, int b)
{
    int *p = D_0027D540;
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
    p[0] = (int)&D_0027D540[a2 * 0x200];
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadEnable);

extern int D_0062BF98;

void iosPadDisable(void) {
    D_0062BF98 = 1;
}


void iosPadEnableGet(void) {
    D_0062BF98 = 0;
}

int iosPadActInit(void) {
    return D_0062BF98;
}

extern void memset(void *a0, int a1, int a2);
extern void iosThreadDestroy();
extern void Init_Player(void *a0);
extern void iosThreadName(void *a0);
extern int Shock_SetShockVoiceSet(int a0, int a1);
extern int D_0062A494;
extern unsigned char D_006A0930[];

void iosPadActStop(void) {
    unsigned char *base;
    unsigned char *p;
    int i;
    memset(D_006A0930, 0, 0x180);
    iosThreadDestroy();
    Shock_SetShockVoiceSet(0, D_0062A494);
    base = D_0027D540;
    p = base + 0x1B8;
    i = 1;
    do {
        iosThreadName(p);
        i--;
        Init_Player(p - 0x14);
        p += 0x200;
    } while (i >= 0);
}



/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_0027D540;  /* stride 0x200 */

typedef struct {
    short              f_4;  /* 0x04 */
    unsigned short     f_6;  /* 0x06 */
} S_005EBB90;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027D430;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00551AA0;  /* stride 0x4 */

/* end struct shapes */
