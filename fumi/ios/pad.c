#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", controler_stable_check);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevReadFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadNormalizeStick);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadGetStick);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadActRequest);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadConnect);

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

extern int D_0062BF98;

void iosPadEnableGet(void) {
    D_0062BF98 = 0;
}

int iosPadActInit(void) {
    return D_0062BF98;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadActStop);


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
