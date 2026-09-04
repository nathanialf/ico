#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcInit);
extern char D_0054C010[];
extern int D_0054C014[];
extern char D_0072F5C0[];
extern char D_00730B80[];

void *_lmcGetClientPtr(int *a0, int *a1) {
    a0[0] = (int)D_00730B80;
    a1[0] = (int)D_0054C010;
    *(int *)(D_00730B80 + 0x3C) = D_0054C014[0];
    return D_0072F5C0;
}
extern char D_0072F640[];
extern int PollSema(int sema);
extern void SignalSema(int sema);
extern int sceSifCallRpc();

int sceMcChangeThreadPriority(int arg) {
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
int sceMcGetSlotMax(int arg) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcOpen);
extern int sceMcOpen(int a0, int a1, int a2, int a3);

int sceMcMkdir(int a0, int a1, int a2) {
    int ret = sceMcOpen(a0, a1, a2, 0x40);
    if (ret == 0) {
        *(int *)D_0054C010 = 0xB;
    }
    return ret;
}
int sceMcClose(int arg) {
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
int sceMcSeek(int a0, int a1, int a2) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", mceIntrReadFixAlign);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcRead);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcWrite);
extern void iWakeupThread(int a0);

void mcHearAlarm(int a0, int a1, int a2) {
    iWakeupThread(a2);
    SYNC();
    EI();
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", mcDelayThread);
extern void SignalSema(int sema);
extern void mcDelayThread(int a0);
extern int sceSifCheckStatRpc(char *a0);

int sceMcSync(int a0, int *a1, int *a2) {
    int r;
    if (*(int *)D_0054C010 == 0) {
        return 0xFFFFFFFF;
    }
    r = sceSifCheckStatRpc(D_0072F5C0);
    if (a0 != 0) goto L050;
    if (r == 0) goto L050;
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

void mceGetInfoApdx(int a0) {
    a0 |= 0x20000000;
    if (D_0072F5E8[0]) *D_0072F5E8[0] = *(int *)a0;
    if (D_0072F5EC[0]) *D_0072F5EC[0] = *(int *)(a0 + 4);
    if (D_0072F5F0[0]) *D_0072F5F0[0] = *(int *)(a0 + 0x90);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcGetInfo);
extern NameReq D_0072F670;
extern void func_00265A38(void *addr, int len);
extern char *strncpy(char *dst, const char *src, int n);

int sceMcGetDir(int a0, int a1, char *name, int a3, int nblk, void *buf) {
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
        func_00265A38(buf, nblk * 64);
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
extern int memcpy(char *a0, char *a1, int a2);
extern int strlen(char *a0);

void mceStorePwd(char *a0) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcChdir);
int sceMcFormat(int a0, int a1) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcDelete);
int sceMcFlush(int arg) {
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

int sceMcSetFileInfo(int a0, int a1, char *name, void *src, int flags) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_268E78", sceMcRename);
int sceMcUnformat(int a0, int a1) {
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
int sceMcGetEntSpace(int a0, int a1, char *name) {
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
