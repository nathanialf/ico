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

extern int *D_0062A490;

int iosThreadSetPri(int a0, int a1) {
    int *p = D_0062A490;
    if ((unsigned int)a0 < (unsigned int)p[0]) goto store;
    a0 = -1;
    goto end;
store:
    ((int *)p[1])[a0] = a1;
end:
    return a0;
}

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

void iosThreadCreate(unsigned char *a0, int a1, int a2) {
    if (a1) {
        a0[0] &= 0xFE;
    }
    if (a2) {
        a0[0] &= 0xEF;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadGetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosGetIOSThreadFromId);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", iosThreadWakeup);

extern void func_00100340(void *a0, int a1);

void iosThreadJoin(int *a0) {
    func_00100340((void *)a0[0xC], a0[0xD]);
}

extern void func_00100350(void);
extern void func_00100370(void *a0);

void iosThreadCancelWakeup(void *a0) {
    if (a0 == 0) {
        func_00100350();
        return;
    }
    func_00100370(*(void **)((char *)a0 + 0x30));
}

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

extern int func_00100450(void *a0);

int func_0013D410(void *a0) {
    return func_00100450(*(void **)((char *)a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D430);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D4B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D570);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D5E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D648);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D698);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/thread", func_0013D718);

extern unsigned char D_006A2F50[];
extern void func_00260568(void *a0, int a1, int a2);

void func_0013D870(void) {
    func_00260568(D_006A2F50, 0, 0x10C);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_30;  /* 0x30 */
    unsigned int       f_34;  /* 0x34 */
    unsigned int       f_38;  /* 0x38 */
    unsigned int       f_40;  /* 0x40 */
} S_006A0EE0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A0AB0;  /* stride 0x4 */

/* end struct shapes */
