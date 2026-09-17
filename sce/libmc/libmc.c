/* libmc.a member libmc.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <sifrpc.h>
#include <libmc.h>
#include <string.h>

/* R5900 opcodes with no C spelling.  This member's uses stand for a
   Sony-internal header this tree cannot name: MAIN.MAP attests archives and
   their members, never a header, so the definition is kept per member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")
#define EI() __asm__ __volatile__(".word 0x42000038" : : : "memory")

typedef struct {
    char f0[0x20];
    char name[0x20];
} AuxReq;

typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    char name[0x400];
} NameReq;

INCLUDE_ASM("asm/nonmatchings/sce/libmc/libmc", sceMcInit);

extern char D_0054C010[];
extern int D_0054C014[];
extern char D_0072F5C0[];
extern char D_00730B80[];

void *_lmcGetClientPtr(int *a0, int *a1)
{
    a0[0] = (int)D_00730B80;
    a1[0] = (int)D_0054C010;
    *(int *)(D_00730B80 + 0x3C) = D_0054C014[0];
    return D_0072F5C0;
}

extern char D_0072F640[];
extern int PollSema(int sema);
extern void SignalSema(int sema);

int sceMcChangeThreadPriority(int arg)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    blk = D_0072F640;
    *(int *)(blk + 0x14) = arg;
    r = sceSifCallRpc(dev, 0x14, 1, blk, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0x14;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcGetSlotMax(int arg)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    blk = D_0072F640;
    *(int *)(blk + 4) = arg;
    r = sceSifCallRpc(dev, 0x15, 0, blk, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        SignalSema(D_0054C014[0]);
        return r;
    }
    SignalSema(D_0054C014[0]);
    return *(int *)D_00730B80;
}

extern NameReq D_0072F670;

int sceMcOpen(int a0, int a1, char *name, int flags)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.f0 = a0;
    D_0072F670.f8 = flags;
    D_0072F670.f4 = a1;
    D_0072F670.name[0x3FF] = 0;
    r = sceSifCallRpc(dev, 2, 1, &D_0072F670, 0x414, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 2;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcMkdir(int a0, int a1, char *name)
{
    int ret = sceMcOpen(a0, a1, name, 0x40);
    if (ret == 0) {
        *(int *)D_0054C010 = 0xB;
    }
    return ret;
}

int sceMcClose(int arg)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    *(int *)D_0072F640 = arg;
    r = sceSifCallRpc(dev, 0x3, 1, D_0072F640, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0x3;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcSeek(int a0, int a1, int a2)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    *(int *)D_0072F640 = a0;
    *(int *)(D_0072F640 + 0x10) = a1;
    *(int *)(D_0072F640 + 0x14) = a2;
    r = sceSifCallRpc(dev, 4, 1, D_0072F640, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 4;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

typedef struct {
    int n0;        /* 0x00 */
    int n1;        /* 0x04 */
    char *d0;      /* 0x08 */
    char *d1;      /* 0x0C */
    char b0[0x40]; /* 0x10 */
    char b1[0x70]; /* 0x50 */
} FixAlign;

void mceIntrReadFixAlign(void *arg)
{
    FixAlign *p;
    char *d;
    int i;

    p = (FixAlign *)((unsigned int)arg | 0x20000000);
    if (p->n0 != 0) {
        d = p->d0;
        for (i = 0; i < p->n0; i++) {
            *d++ = p->b0[i];
        }
    }
    if (p->n1 != 0) {
        d = p->d1;
        for (i = 0; i < p->n1; i++) {
            *d++ = p->b1[i];
        }
    }
}

extern char D_0072FAC0[];
extern void mceIntrReadFixAlign();

int sceMcRead(int a0, void *buf, int len)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    *(int *)D_0072F640 = a0;
    *(int *)(D_0072F640 + 0x1C) = (int)D_0072FAC0;
    *(int *)(D_0072F640 + 0x18) = (int)buf;
    *(int *)(D_0072F640 + 0xC) = len;
    sceSifWriteBackDCache(buf, len);
    sceSifWriteBackDCache(D_0072FAC0, 0xC0);
    r = sceSifCallRpc(dev, 5, 1, D_0072F640, 0x30, D_00730B80, 4, mceIntrReadFixAlign, D_0072FAC0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 5;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmc/libmc", sceMcWrite);

extern void iWakeupThread(int a0);

void mcHearAlarm(int a0, int a1, int a2)
{
    iWakeupThread(a2);
    SYNC();
    EI();
}

extern int GetThreadId(void);
extern void SetAlarm(int a0, void *a1, int a2);
extern void SleepThread(void);

void mcDelayThread(int a0)
{
    SetAlarm((unsigned short)a0, mcHearAlarm, GetThreadId());
    SleepThread();
}

extern void SignalSema(int sema);
extern void mcDelayThread(int a0);

int sceMcSync(int a0, int *a1, int *a2)
{
    int r;
    if (*(int *)D_0054C010 == 0) {
        return 0xFFFFFFFF;
    }
    r = sceSifCheckStatRpc(D_0072F5C0);
    if (a0 != 0)
        goto L050;
    if (r == 0)
        goto L050;
    while (sceSifCheckStatRpc(D_0072F5C0) != 0) {
        mcDelayThread(0x3C);
    }
    r = 0;
L050:
    r = (r == 0);
    if (a1 != 0) {
        *a1 = *(int *)D_0054C010;
    }
    if (r != 0) {
        *(int *)D_0054C010 = 0;
        if (a2 != 0) {
            *a2 = *(int *)D_00730B80;
        }
        SignalSema(D_0054C014[0]);
    }
    return r;
}

extern int *D_0072F5E8[];
extern int *D_0072F5EC[];
extern int *D_0072F5F0[];

void mceGetInfoApdx(int a0)
{
    a0 |= 0x20000000;
    if (D_0072F5E8[0])
        *D_0072F5E8[0] = *(int *)a0;
    if (D_0072F5EC[0])
        *D_0072F5EC[0] = *(int *)(a0 + 4);
    if (D_0072F5F0[0])
        *D_0072F5F0[0] = *(int *)(a0 + 0x90);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmc/libmc", sceMcGetInfo);

int sceMcGetDir(int a0, int a1, char *name, int a3, int nblk, void *buf)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    D_0072F670.f0 = a0;
    D_0072F670.f4 = a1;
    D_0072F670.f8 = a3;
    D_0072F670.fC = nblk;
    D_0072F670.f10 = (int)buf;
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.name[0x3FF] = 0;
    if (nblk >= 0) {
        sceSifWriteBackDCache(buf, nblk * 64);
    }
    r = sceSifCallRpc(dev, 0xD, 1, &D_0072F670, 0x414, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0xD;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

extern char D_0072FB80[];

void mceStorePwd(char *a0)
{
    int n;
    if (a0 != 0) {
        if ((unsigned int)strlen((char *)((int)D_0072FB80 | 0x20000000)) < 0x400) {
            n = strlen((char *)((int)D_0072FB80 | 0x20000000));
        } else {
            n = 0x3FF;
        }
        memcpy(a0, (char *)((int)D_0072FB80 | 0x20000000), n);
        a0[n] = 0;
    }
}

int sceMcChdir(int a0, int a1, char *name, char *pwd)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    D_0072F670.f0 = a0;
    D_0072F670.f10 = (int)D_0072FB80;
    D_0072F670.f4 = a1;
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.name[0x3FF] = 0;
    sceSifWriteBackDCache(D_0072FB80, 0x400);
    r = sceSifCallRpc(dev, 0xC, 1, &D_0072F670, 0x414, D_00730B80, 4, mceStorePwd, pwd);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0xC;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcFormat(int a0, int a1)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    blk = D_0072F640;
    *(int *)(blk + 4) = a0;
    *(int *)(blk + 8) = a1;
    r = sceSifCallRpc(dev, 0x10, 1, blk, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0x10;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcDelete(int a0, int a1, char *name)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.f0 = a0;
    D_0072F670.f4 = a1;
    D_0072F670.name[0x3FF] = 0;
    D_0072F670.f8 = 0;
    r = sceSifCallRpc(dev, 0xF, 1, &D_0072F670, 0x414, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0xF;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcFlush(int arg)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    *(int *)D_0072F640 = arg;
    r = sceSifCallRpc(dev, 0xA, 1, D_0072F640, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0xA;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

extern AuxReq D_0072F600;
extern void FlushCache(int a0);

int sceMcSetFileInfo(int a0, int a1, char *name, void *src, int flags)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    flags &= 7;
    D_0072F670.f0 = a0;
    D_0072F670.f4 = a1;
    D_0072F670.f8 = flags;
    D_0072F600 = *(AuxReq *)src;
    D_0072F670.f10 = (int)&D_0072F600;
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.name[0x3FF] = 0;
    FlushCache(0);
    r = sceSifCallRpc(dev, 0xE, 1, &D_0072F670, 0x414, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0xE;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcRename(int a0, int a1, char *name, char *newname)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name == 0) {
        goto badname;
    }
    if (newname != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    D_0072F670.f0 = a0;
    D_0072F670.f4 = a1;
    D_0072F670.f8 = 0x10;
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.name[0x3FF] = 0;
    strncpy(D_0072F600.name, newname, 0x20);
    D_0072F600.name[0x1F] = 0;
    D_0072F670.f10 = (int)&D_0072F600;
    FlushCache(0);
    r = sceSifCallRpc(dev, 0xE, 1, &D_0072F670, 0x414, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0x13;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcUnformat(int a0, int a1)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    blk = D_0072F640;
    *(int *)(blk + 4) = a0;
    *(int *)(blk + 8) = a1;
    r = sceSifCallRpc(dev, 0x11, 1, blk, 0x30, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0x11;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}

int sceMcGetEntSpace(int a0, int a1, char *name)
{
    char *dev;
    int r;
    if (PollSema(D_0054C014[0]) < 0) {
        return -0xC8;
    }
    dev = D_0072F5C0;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(D_0054C014[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(D_0054C014[0]);
    return -0xD2;
ok:
    D_0072F670.f0 = a0;
    D_0072F670.f4 = a1;
    strncpy(D_0072F670.name, name, 0x3FF);
    D_0072F670.name[0x3FF] = 0;
    r = sceSifCallRpc(dev, 0x12, 1, &D_0072F670, 0x414, D_00730B80, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_0054C010 = 0x12;
    goto done;
unlock:
    SignalSema(D_0054C014[0]);
done:
    return r;
}
