#include "common.h"

extern void func_00100440(void);
extern void func_00100490(void *a0);
extern void func_001004B0(void *a0);
extern void func_002614F8(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadCreateS);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadStart);

void iosThreadStop(unsigned char *a0) {
    *a0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadSleep);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadDestroy);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadSetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadMessage);

void iosThreadName(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadSuspend);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadResume);

int iosThreadInit(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadGetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosGetIOSThreadFromId);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadWakeup);

extern void func_00100340(void *a0, int a1);

void iosThreadJoin(int *a0) {
    func_00100340((void *)a0[0xC], a0[0xD]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadCancelWakeup);

void iosSemaCreate(void) {
    func_00100440();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosSemaDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosSemaWait);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosSemaSignal);

void iosSemaReferStatus(void *a0) {
    func_002614F8((char *)a0 + 0x50);
}

void iosThreadDestroyMgr(void *a0) {
    func_00100490(*(void **)((char *)a0 + 0x30));
}

void iosThreadAllQuit(void *a0) {
    func_001004B0(*(void **)((char *)a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D038);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D1E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D388);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D3C8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D410);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D430);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D4B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D570);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D5E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D648);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D698);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D718);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D870);
