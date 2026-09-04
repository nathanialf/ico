#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { int f0; int f4; char *f8; } RingBuf_241C80;

typedef struct { int f0; int f4; char *f8; char *fC; char buf[1]; } PrintSink;

extern int D_0054A3E0[];
extern void sceTtyInit(int a0);

void sceResetttyinit(int a0) {
    D_0054A3E0[0] = 0;
    sceTtyInit(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", VSync);
extern void SetVSyncFlag(void *a0, void *a1);

long long VSync2(void) {
    volatile int flag;
    volatile long long val;
    volatile int *p;
    flag = 0;
    SetVSyncFlag((void*)&flag, (void*)&val);
    p = (volatile int *)0x1000F000;
    *p = 4;
    while ((*p & 4) == 0 && flag == 0) {
    }
    *p = 4;
    return val;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", write);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", read);
extern int __errno(void);

int open(void) {
    *(int *)__errno() = 5;
    return -1;
}
int close(int a1) {
    return -1;
}
int ioctl(void) {
    return -1;
}
int lseek(int a1, int a2, int a3) {
    return -1;
}
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global sbrk\n"
    ".type sbrk, @function\n"
    "    .align 3\n"
    "sbrk:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd $31, 0x30($29)\n"
    "    sd $18, 0x20($29)\n"
    "    sd $17, 0x10($29)\n"
    "    sd $16, 0x0($29)\n"
    "    mfc0 $17, $12\n"
    "    lui $2, (0x10000 >> 16)\n"
    "    and $17, $17, $2\n"
    "    beqz $17, .Lsbrk00241B14\n"
    "    lui $18, %hi(D_0054A3E4)\n"
    ".Lsbrk00241AF0:\n"
    "    di\n"
    "    sync.p\n"
    "    mfc0 $2, $12\n"
    "    lui $3, (0x10000 >> 16)\n"
    "    and $2, $2, $3\n"
    "    bnez $2, .Lsbrk00241AF0\n"
    "    nop\n"
    "    b .Lsbrk00241B18\n"
    "    lw $2, %lo(D_0054A3E4)($18)\n"
    ".Lsbrk00241B14:\n"
    "    lw $2, %lo(D_0054A3E4)($18)\n"
    ".Lsbrk00241B18:\n"
    "    jal EndOfHeap\n"
    "    addu $16, $2, $4\n"
    "    sltu $2, $2, $16\n"
    "    beqz $2, .Lsbrk00241B50\n"
    "    lw $2, %lo(D_0054A3E4)($18)\n"
    "    jal __errno\n"
    "    nop\n"
    "    addiu $3, $0, 0xC\n"
    "    beqz $17, .Lsbrk00241B44\n"
    "    sw $3, 0x0($2)\n"
    "    ei\n"
    ".Lsbrk00241B44:\n"
    "    lui $2, (0xFFFFFFFF >> 16)\n"
    "    b .Lsbrk00241B5C\n"
    "    ori $2, $2, (0xFFFFFFFF & 0xFFFF)\n"
    ".Lsbrk00241B50:\n"
    "    beqz $17, .Lsbrk00241B5C\n"
    "    sw $16, %lo(D_0054A3E4)($18)\n"
    "    ei\n"
    ".Lsbrk00241B5C:\n"
    "    ld $31, 0x30($29)\n"
    "    ld $18, 0x20($29)\n"
    "    ld $17, 0x10($29)\n"
    "    ld $16, 0x0($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x40\n"
    ".size sbrk, . - sbrk\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);
int isatty(void) {
    return 1;
}
int fstat(void *a0, void *a1) {
    *(long long *)((char *)a1 + 0x48) = 0;
    *(int *)((char *)a1 + 0x4) = 0x2000;
    return 0;
}
int getpid(void) {
    return 1;
}
extern void Exit(void *a0);

int kill(int a0, void *a1) {
    if (a0 == 1) {
        Exit(a1);
    }
    return 0;
}
int stat(void) {
    *(int *)__errno() = 5;
    return -1;
}
int unlink(void) {
    *(int *)__errno() = 5;
    return -1;
}
extern PrintSink D_0072A600;

void *QueueInit(int a0) {
    D_0072A600.f0 = a0;
    D_0072A600.f4 = 0;
    D_0072A600.fC = D_0072A600.buf;
    D_0072A600.f8 = D_0072A600.buf;
    return &D_0072A600;
}
void QueuePeekWriteDone(int *q)
{
    int count = q[1] + 1;
    char *wp = (char *)q[3] + 1;
    int cap = q[0];
    q[1] = count;
    cap += 0x10;
    {
        char *end = (char *)q + cap;
        q[3] = (int)wp;
        if (wp == end) {
            q[3] = (int)q + 0x10;
        }
    }
}
void QueuePeekReadDone(RingBuf_241C80 *a0) {
    a0->f4--;
    a0->f8++;
    if (a0->f8 == (char *)a0 + (a0->f0 + 0x10)) {
        a0->f8 = (char *)a0 + 0x10;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceTtyHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceTtyWrite);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceTtyRead);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceTtyInit);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifInitRpc);
extern int D_0054A3E8[];
extern void sceSifExitCmd(void);

void sceSifExitRpc(void) {
    sceSifExitCmd();
    D_0054A3E8[0] = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceRpcGetPacket);
void _sceRpcFreePacket(void *a0) {
    int *p = (int *)a0;
    p[6] = 0;
    p[4] &= 0xFFFFFFFE;
}
int _sceRpcGetFPacket(int *a0) {
    int rem = a0[9] % a0[6];
    int ret = a0[5] + rem * 64;
    a0[9] = rem + 1;
    return ret;
}
int _sceRpcGetFPacket2(int *a0, int a1) {
    if (a1 < 0) {
        goto err;
    }
    if (a1 < a0[8]) {
        goto elem;
    }
err:
    return _sceRpcGetFPacket(a0);
elem:
    return a0[7] + a1 * 64;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _request_end);
extern int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);

void _request_rdata(int *a0, int *a1) {
    int *ret = (int *)_sceRpcGetFPacket(a1);
    int f14 = a0[5], f1c = a0[7];
    ret[5] = f14;
    ret[7] = f1c;
    ret[8] = 0x8000000C;
    isceSifSendCmd(0x80000008, (int)ret, 0x40, a0[8], a0[9], a0[10]);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifGetOtherData);
void *_search_svdata(int a0, void *a1) {
    void *n5;
    void *n3;
    for (n5 = *(void **)((char *)a1 + 0x28); n5 != 0; n5 = *(void **)((char *)n5 + 0x14)) {
        for (n3 = *(void **)((char *)n5 + 0x8); n3 != 0; n3 = *(void **)((char *)n3 + 0x38)) {
            if (*(int *)n3 == a0) {
                return n3;
            }
        }
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _request_bind);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifBindRpc);
extern void iWakeupThread(int a0);

void _request_call(int *a0) {
    int *a5 = (int *)a0[13];
    int *a6 = (int *)a5[16];
    int *a2 = (int *)a6[3];
    if (a2 == 0) {
        a6[3] = (int)a5;
    } else {
        ((int *)a6[4])[15] = (int)a5;
    }
    a6[4] = (int)a5;
    {
        int t5 = a0[5], t7 = a0[7];
        a5[8] = t5;
        a5[7] = t7;
    }
    a5[9] = a0[8];
    a5[3] = a0[9];
    a5[10] = a0[10];
    a5[11] = a0[11];
    a5[12] = a0[12];
    a5[13] = a0[4];
    if ((int)a6[0] < 0) {
        return;
    }
    if (a6[1] != 0) {
        return;
    }
    iWakeupThread(a6[0]);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifCallRpc);
int sceSifCheckStatRpc(char *a0) {
    char *p = *(char **)a0;
    if (p == 0) goto ret0;
    if (*(int *)(a0 + 4) != *(int *)(p + 0x18)) goto ret0;
    if (*(int *)(p + 0x10) & 1) goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifSetRpcQueue);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifRegisterRpc);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifRemoveRpc);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifRemoveRpcQueue);
extern void DIntr(int *self);
extern void EIntr(void);

int *sceSifGetNextRequest(int *self)
{
    int *p;
    int v;
    DIntr(self);
    p = (int *)self[0xC/4];
    if (p == 0) {
        self[0x4/4] = 0;
        goto after;
    }
    v = p[0x3C/4];
    self[0x4/4] = 1;
    self[0xC/4] = v;
after:
    EIntr();
    return p;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifExecRequest);
extern void SleepThread(void);
extern void sceSifExecRequest(int *item);

void func_00260690(int *self) {
    int *item;
    for (;;) {
        while ((item = sceSifGetNextRequest(self)) != 0) {
            sceSifExecRequest(item);
        }
        SleepThread();
    }
}
extern int CreateSema(int *self);
extern int D_0054A478[];
extern int D_0054A47C[];

void func_002606D0(void) {
    extern int CreateSema(int *a0);
    int args[8];
    if (D_0054A478[0] == -1) {
        args[5] = 0;
        args[2] = 1;
        args[1] = 1;
        D_0054A478[0] = CreateSema(args);
        D_0054A47C[0] = CreateSema(args);
    }
}
extern char D_0072D300[];
extern void SignalSema(int a0);
extern int WaitSema(int a0);

int new_iob(void) {
    char *p;
    char *end;
    func_002606D0();
    WaitSema(D_0054A478[0]);
    p = D_0072D300;
    end = p + 0x200;
    while (p < end) {
        if (*(int *)(p + 4) == 0) {
            *(int *)(p + 4) = 0x10000000;
            SignalSema(D_0054A478[0]);
            return (int)p;
        }
        p += 0x10;
    }
    SignalSema(D_0054A478[0]);
    return 0;
}
void *get_iob(unsigned int i) {
    char *p;
    func_002606D0();
    WaitSema(D_0054A478[0]);
    if (i < 0x20) {
        goto ok;
    }
    SignalSema(D_0054A478[0]);
    return 0;
ok:
    p = &D_0072D300[i * 16];
    SignalSema(D_0054A478[0]);
    return p;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceFs_Rcv_Intr);
extern int D_0054A474[];

void _sceFsSemInit(void) {
    int self[8];
    if (D_0054A474[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_0054A474[0] = CreateSema(self);
    }
}
int _sceFsWaitS(int arg) {
    _sceFsSemInit();
    WaitSema(D_0054A474[0]);
    return 0;
}
void _sceFsSigSema(void) {
    SignalSema(D_0054A474[0]);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceFsInit);
extern char D_0028ED0C[];
extern int D_0054A480[];
extern char D_0072D528[];
extern int memcmp();

int _fs_version(void) {
    char *s3 = D_0028ED0C;
    char *s1 = D_0072D528;
    int s2 = 0;
    int v0;
    v0 = memcmp(s1, s3, 4);
    if (v0 == 0) goto done;
    v0 = memcmp(s1, (char *)D_0054A480[0], 4);
    if (v0 == 0) goto done;
    v0 = memcmp(s3, (char *)D_0054A480[0], 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}
extern int D_0054A470[];
extern char D_0072D528[];
extern void memset(void *a0, int a1, int a2);

int sceFsReset(void) {
    D_0054A470[0] = 0;
    memset(D_0072D528, 0, 4);
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceOpen);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceClose);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceLseek);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceRead);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceWrite);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceIoctl);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceIoctl2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceCallCode);
extern int _sceCallCode(void *a0, int a1);

int sceRemove(void *a0) {
    return _sceCallCode(a0, 6);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceMkdir);
int sceRmdir(void *a0) {
    return _sceCallCode(a0, 8);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceFormat);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceAddDrv);
int sceDelDrv(void *a0) {
    return _sceCallCode(a0, 0x10);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceDopen);
extern int D_0072C240[];
extern int D_0072CE80[];
extern int D_0072D500[];
extern int DeleteSema(int a0);
extern void _sceFsSigSema(void);
extern void *get_iob(unsigned int a0);
extern int sceSifCallRpc();

int sceDclose(unsigned int a0) {
    extern int CreateSema(int *a0);
    extern int WaitSema(int a0);
    int *g = D_0072C240;
    void *obj;
    int f0;
    int uv;
    int h;
    int rc;
    int result;
    int buf[8];

    obj = get_iob(a0);
    _sceFsWaitS(0xA);
    if (D_0054A470[0] == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        _sceFsSigSema();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[3] = f0;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0xA, 0, g, 0x14, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    ((int *)obj)[1] = 0;
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        return result;
    }
    return 0;
}
int sceDread(unsigned int a0, int a1) {
    extern int CreateSema(int *a0);
    extern int WaitSema(int a0);
    int *g = D_0072C240;
    void *obj;
    int f0;
    int uv;
    int rc;
    int result;
    int buf[8];

    obj = get_iob(a0);
    _sceFsWaitS(0xB);
    if (D_0054A470[0] == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        _sceFsSigSema();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[4] = a1;
    g[3] = f0;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = a1 = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0xB, 0, g, 0x20, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        WaitSema(a1);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(a1);
        return -0xB;
    }
    WaitSema(a1);
    DeleteSema(a1);
    return result;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceGetstat);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceChstat);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceRename);
int sceChdir(void *a0) {
    return _sceCallCode(a0, 0x12);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSync);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceMount);
int sceUmount(void *a0) {
    return _sceCallCode(a0, 0x15);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceLseek64);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceDevctl);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSymlink);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceReadlink);
extern int D_0054A484[];
extern int D_0072D580[];
extern char D_FFFFF[];
extern int sceSifBindRpc();

int sceSifInitIopHeap(void)
{
    int i;
    int ret;
    int val;
    for (;;) {
        ret = sceSifBindRpc(D_0072D580, 0x80000003, 0);
        if (ret < 0) return -1;
        val = D_0072D580[0x24 / 4];
        if (val != 0) {
            D_0054A484[0] = 0;
            break;
        }
        __asm__ volatile ("lui %0,%%hi(D_FFFFF)" : "=r"(i));
        do {
            __asm__ volatile ("addiu %0,%0,%%lo(D_FFFFF)" : "+r"(i));
        } while (i != -1);
    }
    return 0;
}
extern int D_0072D5C0[];
extern int D_0072D600[];

int sceSifAllocIopHeap(int a0) {
    int ret = D_0054A484[0];
    if (ret < 0) return 0;
    D_0072D600[0] = a0;
    ret = sceSifCallRpc(D_0072D580, 1, 0, D_0072D600, 4, D_0072D5C0, 4, 0, 0);
    if (ret >= 0) return D_0072D5C0[0];
    return 0;
}
extern int D_0072D640[];

int sceSifFreeIopHeap(int a0) {
    int v2 = D_0054A484[0];
    if (v2 < 0) return 0;
    D_0072D640[0] = a0;
    v2 = sceSifCallRpc(D_0072D580, 2, 0, D_0072D640, 4, D_0072D5C0, 4, 0, 0);
    if (v2 < 0) return -1;
    return D_0072D5C0[0];
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifLoadIopHeap);
extern int D_0054A488[];
extern char D_0072D780[];
extern char D_0072D980[];
extern char D_0072D9A8[];

int _lf_bind(void) {
    int i;
    int r;
    int val;
    if (D_0054A488[0] >= 0) goto ret0;
loop:
    r = sceSifBindRpc(D_0072D980, 0x80000006, 0);
    if (r < 0) return -1;
    val = *(int *)(D_0072D980 + 0x24);
    if (val == 0) goto delay;
    D_0054A488[0] = 0;
    r = sceSifCallRpc(D_0072D980, 0xFF, 0, 0, 0, D_0072D780, 4, 0, 0);
    if (r < 0) return 0xFFFEFFFF;
    __builtin_memcpy(D_0072D9A8, D_0072D780, 4);
    return 0;
delay:
    __asm__ volatile ("lui %0,%%hi(D_FFFFF)" : "=r"(i));
    do {
        __asm__ volatile ("addiu %0,%0,%%lo(D_FFFFF)" : "+r"(i));
    } while (i != -1);
    goto loop;
ret0:
    return 0;
}
extern int D_0054A48C[];

int _lf_version(void) {
    void *s3 = D_0028ED0C;
    void *s1 = D_0072D9A8;
    int s2 = 0;
    int v;
    if (memcmp(s1, (int)s3, 4) == 0) goto done;
    v = D_0054A48C[0];
    if (memcmp(s1, v, 4) == 0) goto done;
    v = D_0054A48C[0];
    s2 = (0 < (unsigned int)memcmp(s3, v, 4));
done:
    return s2;
}
int sceSifLoadFileReset(void) {
    D_0054A488[0] = -1;
    memset(D_0072D9A8, 0, 4);
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceSifLoadModuleBuffer);
extern int _sceSifLoadModuleBuffer(void *a0, int a1, int a2, void *a3);

void sceSifLoadModuleBuffer(void *a0, int a1, int a2) {
    int local[4];
    _sceSifLoadModuleBuffer(a0, a1, a2, &local);
}
int sceSifLoadStartModuleBuffer(void *a0, int a1, int a2, void *a3) {
    return _sceSifLoadModuleBuffer(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceSifLoadModule);
extern void _sceSifLoadModule(void *a0, int a1, int a2, int a3, int a4);

void sceSifLoadModule(void *a0, int a1, int a2) {
    int local;
    _sceSifLoadModule(a0, a1, a2, (int)&local, 0);
}
void sceSifLoadStartModule(void *a0, int a1, int a2, int a3) {
    do {
        _sceSifLoadModule(a0, a1, a2, a3, 0);
    } while (0);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceSifLoadElfPart);
extern int _sceSifLoadElfPart(void *a0, int a1, int a2, int a3);

int sceSifLoadElfPart(void *a0, int a1, int a2) {
    return _sceSifLoadElfPart(a0, a1, a2, 1);
}
extern char D_00636718[];

int sceSifLoadElf(void *a0, int a1) {
    return _sceSifLoadElfPart(a0, (int)D_00636718, a1, 1);
}
int sceSifGetIopAddr(int a0, void *a1, int a2) {
    int r;
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_0072D780 + 0) = a0;
    *(int *)(D_0072D780 + 4) = a2;
    r = sceSifCallRpc(D_0072D980, 3, 0, D_0072D780, 0x20, D_0072D780, 0x20, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (a2 == 0) {
        *(unsigned char *)a1 = *(unsigned char *)D_0072D780;
    } else if (a2 == 1) {
        *(unsigned short *)a1 = *(unsigned short *)D_0072D780;
    } else if (a2 == 2) {
        *(int *)a1 = *(int *)D_0072D780;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifSetIopAddr);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifResetIop);
extern int sceSifGetReg(int a0);

int sceSifIsAliveIop(void) {
    int t = sceSifGetReg(4) & 0x10000;
    return t != 0;
}
extern void sceResetttyinit();
extern void sceSifSetReg(int a0, int a1);

int sceSifSyncIop(void) {
    if (sceSifGetReg(4) & 0x40000) {
        sceSifSetReg(4, 0x40000);
        ((void (*)(void))sceResetttyinit)();
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifRebootIop);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _DumpTLB\n"
    ".type _DumpTLB, @function\n"
    "    .align 3\n"
    "_DumpTLB:\n"
    "    addiu $29, $29, -0x50\n"
    "    sd $31, 0x40($29)\n"
    "    sd $19, 0x30($29)\n"
    "    sd $18, 0x20($29)\n"
    "    sd $17, 0x10($29)\n"
    "    sd $16, 0x0($29)\n"
    "    mfc0 $17, $6\n"
    "    lui $19, %hi(D_00636750)\n"
    "    lui $18, %hi(D_00636790)\n"
    "    daddu $16, $0, $0\n"
    "    addiu $4, $19, %lo(D_00636750)\n"
    "    nop\n"
    ".L_DumpTLB002474E0:\n"
    "    bne $16, $17, .L_DumpTLB002474F0\n"
    "    daddu $5, $16, $0\n"
    "    jal scePrintf\n"
    "    nop\n"
    ".L_DumpTLB002474F0:\n"
    "    mtc0 $16, $0\n"
    "    sync.p\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0 $8, $2\n"
    "    mfc0 $9, $3\n"
    "    mfc0 $6, $5\n"
    "    mfc0 $7, $10\n"
    "    daddu $5, $16, $0\n"
    "    jal scePrintf\n"
    "    addiu $4, $18, %lo(D_00636790)\n"
    "    addiu $16, $16, 0x1\n"
    "    slti $2, $16, 0x30\n"
    "    bnel $2, $0, .L_DumpTLB002474E0\n"
    "    addiu $4, $19, %lo(D_00636750)\n"
    "    ld $31, 0x40($29)\n"
    "    ld $19, 0x30($29)\n"
    "    ld $18, 0x20($29)\n"
    "    ld $17, 0x10($29)\n"
    "    ld $16, 0x0($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x50\n"
    ".size _DumpTLB, . - _DumpTLB\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global kPutTLBEntry\n"
    ".type kPutTLBEntry, @function\n"
    "    .align 3\n"
    "kPutTLBEntry:\n"
    "    srl $3, $5, 24\n"
    "    addiu $2, $0, 0x30\n"
    "    beq $3, $2, .LTLBEntry002475BC\n"
    "    sltiu $2, $3, 0x31\n"
    "    beqz $2, .LTLBEntry00247590\n"
    "    addiu $2, $0, 0x10\n"
    "    beq $3, $2, .LTLBEntry002475CC\n"
    "    sltiu $2, $3, 0x11\n"
    "    beqz $2, .LTLBEntry00247580\n"
    "    addiu $2, $0, 0x20\n"
    "    beqz $3, .LTLBEntry002475C0\n"
    "    andi $2, $3, 0xF\n"
    "    b .LTLBEntry002475D4\n"
    "    nop\n"
    ".LTLBEntry00247580:\n"
    "    beq $3, $2, .LTLBEntry002475C0\n"
    "    andi $2, $3, 0xF\n"
    "    b .LTLBEntry002475D4\n"
    "    nop\n"
    ".LTLBEntry00247590:\n"
    "    addiu $2, $0, 0x50\n"
    "    beq $3, $2, .LTLBEntry002475CC\n"
    "    sltiu $2, $3, 0x51\n"
    "    bnez $2, .LTLBEntry002475D4\n"
    "    addiu $2, $0, 0x60\n"
    "    beq $3, $2, .LTLBEntry002475CC\n"
    "    addiu $2, $0, 0x70\n"
    "    beq $3, $2, .LTLBEntry002475CC\n"
    "    nop\n"
    "    b .LTLBEntry002475D4\n"
    "    nop\n"
    ".LTLBEntry002475BC:\n"
    "    andi $2, $3, 0xF\n"
    ".LTLBEntry002475C0:\n"
    "    sltiu $2, $2, 0x8\n"
    "    beqz $2, .LTLBEntry002475D4\n"
    "    nop\n"
    ".LTLBEntry002475CC:\n"
    "    jr $31\n"
    "    addiu $2, $0, -0x1\n"
    ".LTLBEntry002475D4:\n"
    "    mtc0 $4, $5\n"
    "    mtc0 $5, $10\n"
    "    mtc0 $6, $2\n"
    "    mtc0 $7, $3\n"
    "    sync.p\n"
    "    tlbwr\n"
    "    sync.p\n"
    "    tlbp\n"
    "    sync.p\n"
    "    mfc0 $2, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size kPutTLBEntry, . - kPutTLBEntry\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global kSetTLBEntry\n"
    "    .type kSetTLBEntry, @function\n"
    "    .align 3\n"
    "kSetTLBEntry:\n"
    "    mfc0  $2, $6\n"
    "    slt   $2, $4, $2\n"
    "    bnez  $2, 1f\n"
    "    slti  $2, $4, 0x30\n"
    "    bnez  $2, 2f\n"
    "    nop\n"
    "1:\n"
    "    jr    $31\n"
    "    addiu $2, $0, -0x1\n"
    "2:\n"
    "    mtc0  $4, $0\n"
    "    mtc0  $5, $5\n"
    "    mtc0  $6, $10\n"
    "    mtc0  $7, $2\n"
    "    mtc0  $8, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    jr    $31\n"
    "    daddu $2, $4, $0\n"
    "    .size kSetTLBEntry, . - kSetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global kGetTLBEntry\n"
    "    .type kGetTLBEntry, @function\n"
    "    .align 3\n"
    "kGetTLBEntry:\n"
    "    sltiu $2, $4, 0x30\n"
    "    bnez  $2, 1f\n"
    "    nop\n"
    "    jr    $31\n"
    "    addiu $2, $0, -0x1\n"
    "1:\n"
    "    mtc0  $4, $0\n"
    "    sync.p\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0  $2, $5\n"
    "    sw    $2, 0x0($5)\n"
    "    mfc0  $3, $10\n"
    "    sw    $3, 0x0($6)\n"
    "    mfc0  $2, $2\n"
    "    sw    $2, 0x0($7)\n"
    "    mfc0  $3, $3\n"
    "    sw    $3, 0x0($8)\n"
    "    jr    $31\n"
    "    daddu $2, $4, $0\n"
    "    .size kGetTLBEntry, . - kGetTLBEntry\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global kProbeTLBEntry\n"
    "    .type kProbeTLBEntry, @function\n"
    "    .align 3\n"
    "kProbeTLBEntry:\n"
    "    mtc0  $4, $10\n"
    "    sync.p\n"
    "    tlbp\n"
    "    sync.p\n"
    "    mfc0  $4, $0\n"
    "    bgez  $4, 1f\n"
    "    nop\n"
    "    b     2f\n"
    "    addiu $4, $0, -0x1\n"
    "1:\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0  $2, $5\n"
    "    sw    $2, 0x0($5)\n"
    "    mfc0  $3, $2\n"
    "    sw    $3, 0x0($6)\n"
    "    mfc0  $2, $3\n"
    "    sw    $2, 0x0($7)\n"
    "2:\n"
    "    jr    $31\n"
    "    daddu $2, $4, $0\n"
    "    .size kProbeTLBEntry, . - kProbeTLBEntry\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global kExpandScratchPad\n"
    ".type kExpandScratchPad, @function\n"
    "    .align 3\n"
    "kExpandScratchPad:\n"
    "    addiu $29, $29, -0x30\n"
    "    sd $16, 0x10($29)\n"
    "    daddu $16, $4, $0\n"
    "    andi $2, $16, 0xFFF\n"
    "    bnez $2, .LratchPad00247720\n"
    "    sd $31, 0x20($29)\n"
    "    lui $2, (0xFFFFE >> 16)\n"
    "    addiu $3, $16, -0x1\n"
    "    ori $2, $2, (0xFFFFE & 0xFFFF)\n"
    "    sltu $2, $2, $3\n"
    "    bnez $2, .LratchPad00247728\n"
    "    lui $4, (0x70004000 >> 16)\n"
    ".LratchPad00247720:\n"
    "    b .LratchPad00247810\n"
    "    addiu $2, $0, -0x1\n"
    ".LratchPad00247728:\n"
    "    daddu $5, $29, $0\n"
    "    ori $4, $4, (0x70004000 & 0xFFFF)\n"
    "    ori $6, $29, 0x4\n"
    "    jal kProbeTLBEntry\n"
    "    ori $7, $29, 0x8\n"
    "    daddu $5, $2, $0\n"
    "    bgez $5, .LratchPad00247768\n"
    "    nop\n"
    "    beqz $16, .LratchPad00247810\n"
    "    daddu $2, $0, $0\n"
    "    mfc0 $5, $6\n"
    "    addiu $2, $5, 0x1\n"
    "    mtc0 $2, $6\n"
    "    sync.p\n"
    "    b .LratchPad002477B0\n"
    "    nop\n"
    ".LratchPad00247768:\n"
    "    bnez $16, .LratchPad002477B0\n"
    "    addiu $2, $5, -0x1\n"
    "    lui $3, (0xE0010000 >> 16)\n"
    "    sll $2, $2, 13\n"
    "    addu $6, $2, $3\n"
    "    mfc0 $2, $6\n"
    "    addiu $2, $2, -0x1\n"
    "    mtc0 $2, $6\n"
    "    mtc0 $5, $0\n"
    "    mtc0 $0, $5\n"
    "    mtc0 $6, $10\n"
    "    mtc0 $0, $2\n"
    "    mtc0 $0, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    b .LratchPad00247810\n"
    "    daddu $2, $0, $0\n"
    ".LratchPad002477B0:\n"
    "    lui $2, (0xFFFFF000 >> 16)\n"
    "    addiu $4, $16, 0x1000\n"
    "    ori $2, $2, (0xFFFFF000 & 0xFFFF)\n"
    "    lui $6, (0x70004000 >> 16)\n"
    "    and $4, $4, $2\n"
    "    sw $0, 0x0($29)\n"
    "    and $2, $16, $2\n"
    "    srl $4, $4, 6\n"
    "    srl $2, $2, 6\n"
    "    ori $4, $4, 0x1F\n"
    "    ori $2, $2, 0x1F\n"
    "    ori $6, $6, (0x70004000 & 0xFFFF)\n"
    "    sw $2, 0x4($29)\n"
    "    sw $4, 0x8($29)\n"
    "    mtc0 $5, $0\n"
    "    daddu $3, $0, $0\n"
    "    mtc0 $3, $5\n"
    "    mtc0 $6, $10\n"
    "    mtc0 $2, $2\n"
    "    mtc0 $4, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    daddu $2, $5, $0\n"
    ".LratchPad00247810:\n"
    "    ld $31, 0x20($29)\n"
    "    ld $16, 0x10($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x30\n"
    ".size kExpandScratchPad, . - kExpandScratchPad\n"
    "    .set reorder\n"
    "    .set at\n"
);
extern int D_0054A490[];
extern void SetVTLBRefillHandler();
extern void func_00265040(void);

void *SetTLBHandler(void *a0) {
    D_0054A490[0] = (int)a0;
    SetVTLBRefillHandler(1, func_00265040);
    SetVTLBRefillHandler(2, func_00265040);
    SetVTLBRefillHandler(3, func_00265040);
    return a0;
}
extern char D_00265280[];
extern int D_0054A498[];
extern void SetVCommonHandler();

int SetDebugHandler(int a0, int a1) {
    int old;
    int orig = a0;
    unsigned int err = 0xFFFFFFFF;
    if ((unsigned)(a0 - 1) >= 13) {
        return (int)err;
    }
    old = D_0054A498[orig];
    D_0054A498[orig] = a1;
    if ((unsigned)(a0 - 1) < 3) {
        SetVTLBRefillHandler(orig, (void *)D_00265280);
    } else {
        SetVCommonHandler(orig, (void *)D_00265280);
    }
    return old;
}
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel func_00264F40\n"
    "    addiu      $3, $0, 0x74\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00264F40\n"
    "    .set reorder\n"
    "    .set at\n"
);
extern int D_0054A4D8[];
extern void func_00264F40(int x, int y);

void InitTLBFunctions(void)
{
  int *p = D_0054A4D8;
  unsigned int i = 0;
  do
  {
    i++;
    func_00264F40(p[0], p[1]);
    p += 2;
  }
  while (i < 6);
}
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel PutTLBEntry\n"
    "    addiu      $3, $0, 0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel PutTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel iPutTLBEntry\n"
    "    addiu      $3, $0, -0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iPutTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel SetTLBEntry\n"
    "    addiu      $3, $0, 0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel SetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel iSetTLBEntry\n"
    "    addiu      $3, $0, -0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iSetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel GetTLBEntry\n"
    "    addiu      $3, $0, 0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel GetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel iGetTLBEntry\n"
    "    addiu      $3, $0, -0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iGetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel ProbeTLBEntry\n"
    "    addiu      $3, $0, 0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel ProbeTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel iProbeTLBEntry\n"
    "    addiu      $3, $0, -0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iProbeTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel ExpandScratchPad\n"
    "    addiu      $3, $0, 0x59\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel ExpandScratchPad\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", func_00265040);
void _change_addr(int *a0, int *a1) {
    a1[2] = a0[4];
}
extern int D_0072EE80[];

int sceSifGetSreg(int a0) {
    return D_0072EE80[a0];
}
extern int D_0072EE80[];

int sceSifSetSreg(int a0, int a1) {
    D_0072EE80[a0] = a1;
    return a1;
}
extern int D_0072ED58[];

void *sceSifGetDataTable(void) {
    return D_0072ED58;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", sceSifInitCmd);
extern int D_0054A508[];
extern int D_0072ED54[];
extern int DisableDmac(int a0);
extern int RemoveDmacHandler(int a0, int a1);

void sceSifExitCmd(void) {
    DisableDmac(5);
    RemoveDmacHandler(5, D_0072ED54[0]);
    D_0054A508[0] = 0;
}
extern int D_0072ED58[];

int sceSifSetCmdBuffer(int a0, int a1) {
    int old = D_0072ED58[5];
    D_0072ED58[5] = a0;
    D_0072ED58[6] = a1;
    return old;
}
int sceSifSetSysCmdBuffer(int a0, int a1) {
    int old = D_0072ED58[3];
    D_0072ED58[3] = a0;
    D_0072ED58[4] = a1;
    return old;
}
extern int D_0072ED64[];
extern int D_0072ED6C[];

int sceSifAddCmdHandler(int a0, int a1, int a2) {
    int off = a0 * 8;
    int *p;
    if (a0 >= 0) goto pos;
    a0 = D_0072ED64[0];
    goto done;
pos:
    a0 = D_0072ED6C[0];
done:
    off += a0;
    p = (int *)off;
    p[0] = a1;
    p[1] = a2;
}
void sceSifRemoveCmdHandler(int a0) {
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_0072ED64[0];
    } else {
        a0 = D_0072ED6C[0];
    }
    off += a0;
    *(int *)off = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EF18", _sceSifSendCmd);
extern int _sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1, int t2);

int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
  return _sceSifSendCmd(a0, 0, a1, a2, a3, t0, t1);
}
int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
  return _sceSifSendCmd(a0, 1, a1, a2, a3, t0, t1);
}
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _sceSifCmdIntrHdlr\n"
    ".type _sceSifCmdIntrHdlr, @function\n"
    "    .align 3\n"
    "_sceSifCmdIntrHdlr:\n"
    "    addiu $29, $29, -0x90\n"
    "    sd $16, 0x70($29)\n"
    "    sd $31, 0x80($29)\n"
    "    jal EIntr\n"
    "    nop\n"
    "    lui $3, %hi(D_0072ED58)\n"
    "    lw $7, %lo(D_0072ED58)($3)\n"
    "    addiu $16, $3, %lo(D_0072ED58)\n"
    "    lbu $2, 0x0($7)\n"
    "    andi $5, $2, 0xFF\n"
    "    beqz $5, .LIntrHdlr002483E8\n"
    "    daddu $2, $0, $0\n"
    "    addiu $2, $5, 0xF\n"
    "    addiu $3, $0, -0x1\n"
    "    addiu $4, $5, 0x1E\n"
    "    slt $3, $3, $2\n"
    "    movn $4, $2, $3\n"
    "    daddu $6, $7, $0\n"
    "    sra $5, $4, 4\n"
    "    sb $0, 0x0($7)\n"
    "    blez $5, .LIntrHdlr0024834C\n"
    "    daddu $4, $5, $0\n"
    "    daddu $3, $29, $0\n"
    "    nop\n"
    ".LIntrHdlr00248330:\n"
    "    lq $2, 0x0($6)\n"
    "    addiu $4, $4, -0x1\n"
    "    addiu $6, $6, 0x10\n"
    "    sq $2, 0x0($3)\n"
    "    addiu $3, $3, 0x10\n"
    "    bnez $4, .LIntrHdlr00248330\n"
    "    nop\n"
    ".LIntrHdlr0024834C:\n"
    "    jal isceSifSetDChain\n"
    "    nop\n"
    "    lw $3, 0x8($29)\n"
    "    bgez $3, .LIntrHdlr002483A8\n"
    "    nop\n"
    "    lw $2, 0x8($29)\n"
    "    lui $3, (0x7FFFFFFF >> 16)\n"
    "    ori $3, $3, (0x7FFFFFFF & 0xFFFF)\n"
    "    lw $4, 0x10($16)\n"
    "    and $5, $2, $3\n"
    "    slt $4, $5, $4\n"
    "    beqz $4, .LIntrHdlr002483DC\n"
    "    sll $2, $5, 3\n"
    "    lw $3, 0xC($16)\n"
    "    addu $2, $2, $3\n"
    "    lw $6, 0x0($2)\n"
    "    beqz $6, .LIntrHdlr002483DC\n"
    "    nop\n"
    "    lw $5, 0x4($2)\n"
    "    jalr $6\n"
    "    daddu $4, $29, $0\n"
    "    b .LIntrHdlr002483DC\n"
    "    nop\n"
    ".LIntrHdlr002483A8:\n"
    "    lw $5, 0x8($29)\n"
    "    lw $2, 0x18($16)\n"
    "    slt $2, $5, $2\n"
    "    beqz $2, .LIntrHdlr002483DC\n"
    "    sll $2, $5, 3\n"
    "    lw $3, 0x14($16)\n"
    "    addu $2, $2, $3\n"
    "    lw $6, 0x0($2)\n"
    "    beqz $6, .LIntrHdlr002483DC\n"
    "    nop\n"
    "    lw $5, 0x4($2)\n"
    "    jalr $6\n"
    "    daddu $4, $29, $0\n"
    ".LIntrHdlr002483DC:\n"
    "    sync\n"
    "    ei\n"
    "    daddu $2, $0, $0\n"
    ".LIntrHdlr002483E8:\n"
    "    ld $31, 0x80($29)\n"
    "    ld $16, 0x70($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x90\n"
    ".size _sceSifCmdIntrHdlr, . - _sceSifCmdIntrHdlr\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00265A38\n"
    ".type func_00265A38, @function\n"
    "    .align 3\n"
    "func_00265A38:\n"
    "    lui $25, (0xFFFFFFC0 >> 16)\n"
    "    ori $25, $25, (0xFFFFFFC0 & 0xFFFF)\n"
    "    blez $5, .L00265A380024849C\n"
    "    addu $10, $4, $5\n"
    "    and $8, $4, $25\n"
    "    addiu $10, $10, -0x1\n"
    "    and $9, $10, $25\n"
    "    subu $10, $9, $8\n"
    "    srl $11, $10, 6\n"
    "    addiu $11, $11, 0x1\n"
    "    andi $9, $11, 0x7\n"
    "    beqz $9, .L00265A3800248448\n"
    "    srl $10, $11, 3\n"
    ".L00265A380024842C:\n"
    "    sync\n"
    "    cache 0x18, 0x0($8)\n"
    "    sync\n"
    "    addiu $9, $9, -0x1\n"
    "    nop\n"
    "    bgtz $9, .L00265A380024842C\n"
    "    addiu $8, $8, 0x40\n"
    ".L00265A3800248448:\n"
    "    beqz $10, .L00265A380024849C\n"
    ".L00265A380024844C:\n"
    "    addiu $10, $10, -0x1\n"
    "    sync\n"
    "    cache 0x18, 0x0($8)\n"
    "    sync\n"
    "    cache 0x18, 0x40($8)\n"
    "    sync\n"
    "    cache 0x18, 0x80($8)\n"
    "    sync\n"
    "    cache 0x18, 0xC0($8)\n"
    "    sync\n"
    "    cache 0x18, 0x100($8)\n"
    "    sync\n"
    "    cache 0x18, 0x140($8)\n"
    "    sync\n"
    "    cache 0x18, 0x180($8)\n"
    "    sync\n"
    "    cache 0x18, 0x1C0($8)\n"
    "    sync\n"
    "    bgtz $10, .L00265A380024844C\n"
    "    addiu $8, $8, 0x200\n"
    ".L00265A380024849C:\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00265A38, . - func_00265A38\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 2\n"
    "glabel func_00265AE4\n"
    "    jr         $31\n"
    "    addiu      $29, $29, -0x10\n"
    "endlabel func_00265AE4\n"
    "    .set reorder\n"
    "    .set at\n"
);
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .global func_00265AEC\n"
    "    .type func_00265AEC, @function\n"
    "    .align 2\n"
    "func_00265AEC:\n"
    "    sd    $31, 0x0($29)\n"
    "    jal   iSignalSema\n"
    "    daddu $4, $6, $0\n"
    "    sync\n"
    "    ei\n"
    "    ld    $31, 0x0($29)\n"
    "    jr    $31\n"
    "    addiu $29, $29, 0x10\n"
    "    .size func_00265AEC, . - func_00265AEC\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);
