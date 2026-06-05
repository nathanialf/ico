#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrSearchFile);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrStStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", temp_loadfunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrPackLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdHandlerReadNoInflate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdHandlerReadInflate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", unifile_read_func);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdManager);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdDiskReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdPackLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundMgrAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundMgr);

extern void iosMsgSend(void *a0, void *a1, int a2);
extern unsigned char D_0027A840[];

void iosCdvdDirectStOpen(void *a0) {
    *(int *)((char *)a0 + 4) = 2;
    iosMsgSend(D_0027A840, a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdChgFileName);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdGetFileLsn);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdSync);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdLoadPackFile);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdDiskStatusGet);

extern int iosMsgRecv(void *a0, void *a1, int a2);
extern unsigned char D_0027A870[];

int iosCdvdBackGroundMgrDelete(int a0) {
    int buf[4];
    buf[0] = a0;
    iosMsgRecv(D_0027A870, buf, 1);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundMgrNotDiskReadyPauseSet);

extern int D_0062A26C;

int iosCdvdBackGroundMgrDeleteRequestGet(void) {
    return D_0062A26C;
}

int iosCdvdBackGroundMgrEntryNum(void *a0) {
    int *p = (int *)((char *)a0 + 0x108);
    return *p |= 2;
}

int iosCdvdBackGroundMgrSeek(void *a0, int a1) {
    int *p = (int *)((char *)a0 + 0x108);
    return *p = (*p & ~0x10) | ((a1 & 1) << 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundRead);

typedef struct { char f0; char pad[0x12B]; } CdEntry;
extern CdEntry D_0069F800[];

int iosCdvdBackGroundReadIOPm(void) {
    int count = 0;
    int i;
    for (i = 0; i < 7; i++) {
        if (D_0069F800[i].f0) {
            count++;
        }
    }
    return count;
}


/* recovered struct shapes */
typedef struct {
    char               f_0;  /* 0x00 */
    unsigned int       f_100;  /* 0x100 */
    unsigned int       f_104;  /* 0x104 */
    unsigned int       f_108;  /* 0x108 */
    unsigned int       f_118;  /* 0x118 */
    unsigned int       f_11C;  /* 0x11C */
    unsigned int       f_120;  /* 0x120 */
    unsigned int       f_124;  /* 0x124 */
    unsigned int       f_128;  /* 0x128 */
} S_0069F800;

typedef struct {
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_160;  /* 0x160 */
} S_00272680;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_0027A8A0;  /* stride 0x30 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00272668;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00550A54;  /* stride 0x10 */

/* end struct shapes */
