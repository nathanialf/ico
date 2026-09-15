/* Vendor SCE library member: libkernl.a(thread.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100D68..0x1010C8, 5 functions. */
#include "common.h"
#include "syscall.h"
#include "r5900.h"

typedef struct {
    unsigned char code;
    unsigned char id;
} KernEvent;

typedef struct {
    int f0;
    int widx;
    KernEvent ent[512];
} KernEventRing;

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/thread", topThread);
INCLUDE_ASM("asm/nonmatchings/sce/libkernl/thread", InitThread);

extern int D_0028F4B0[];
extern int D_0063CB50[];
extern KernEventRing D_0063CB58;
extern int _iWakeupThread(void);
extern void iSignalSema(int handle);

int iWakeupThread(int id)
{
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iWakeupThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (D_0028F4B0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_0063CB58.widx & 0x1FF;
    D_0063CB58.widx = i + 1;
    D_0063CB58.ent[i].code = 0;
    D_0063CB58.ent[i].id = r;
    iSignalSema(D_0063CB50[0]);
    return r;
}

int iRotateThreadReadyQueue(int id)
{
    int i;
    if ((unsigned int)id >= 0x80) {
        goto fail;
    }
    if (D_0028F4B0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_0063CB58.widx & 0x1FF;
    D_0063CB58.widx = i + 1;
    D_0063CB58.ent[i].code = 1;
    D_0063CB58.ent[i].id = id;
    iSignalSema(D_0063CB50[0]);
    return id;
}

extern int _iSuspendThread(void);

int iSuspendThread(int id)
{
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iSuspendThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (D_0028F4B0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_0063CB58.widx & 0x1FF;
    D_0063CB58.widx = i + 1;
    D_0063CB58.ent[i].code = 2;
    D_0063CB58.ent[i].id = r;
    iSignalSema(D_0063CB50[0]);
    return r;
}
