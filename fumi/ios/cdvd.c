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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundMgrDelete);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundReadIOPm);
