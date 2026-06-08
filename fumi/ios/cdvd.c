#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrSearchFile);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrStStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdMgrLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", temp_loadfunc);

/* 0x30-stride record at the far .sdata table D_0027A8A0 (file id / size + a
 * 0x28-byte name). */
struct E001332B8
{
    int f0;
    int f1;
    unsigned char pad[0x28];
};
/* D_0027A8A0 is an 8-byte .sdata symbol at a FAR VMA — a gp_rel C ref
 * truncates at link. Alias it as an incomplete struct array so ee-gcc emits
 * %hi/%lo absolute addressing (matches the ROM), with no .data shift. */
extern struct E001332B8 D_tbl_0027E520[] __asm__("D_0027A8A0");
extern unsigned char D_0027A8A8[];
extern char D_00550BD8[];
extern char D_00550C10[];

/* request object: name string at 0x34, recovered id/size at 0x134/0x138. */
typedef struct
{
    unsigned char _pad0[0xC];
    int unk_C;          /* 0xC */
    unsigned char _pad10[0x24];
    char name[0x28];    /* 0x34 */
    unsigned char _pad5C[0xD8];
    int fileId;         /* 0x134 */
    int fileSize;       /* 0x138 */
} CdvdReq;

extern int D_0062A25C;
extern void debug_assertMessage();
extern int func_0026160C(int *name);
extern int func_002613B4(int *name, const char *entry);
extern int func_00248BB8(int *dst, int *name);
extern int func_00261900(void *dst, int *src, int n);

void iosCdvdMgrPackLoad(int *self)
{
    CdvdReq *req = (CdvdReq *) self;
    int found = 1;
    volatile int i; /* the loop index lives on the stack (reloaded each pass) */

    if ((unsigned int) func_0026160C((int *) req->name) < 0x28)
    {
        for (i = 0; i < D_0062A25C; i++)
        {
            found = func_002613B4((int *) req->name, (const char *) &D_0027A8A8[i * 0x30]);
            if (found == 0)
            {
                break;
            }
        }
    }
    else
    {
        debug_assertMessage(D_00550BD8);
    }

    if (found == 0)
    {
        req->fileId = D_tbl_0027E520[i].f0;
        req->fileSize = D_tbl_0027E520[i].f1;
    }
    else
    {
        req->unk_C = 0;
        if (func_00248BB8(&req->fileId, (int *) req->name) == 0)
        {
            req->unk_C = 0x64;
        }
        if (D_0062A25C < 0xC8)
        {
            int n = D_0062A25C;
            D_tbl_0027E520[n].f0 = req->fileId;
            D_tbl_0027E520[n].f1 = req->fileSize;
            func_00261900(D_tbl_0027E520[n].pad, (int *) req->name, 0x28);
            D_0062A25C = D_0062A25C + 1;
        }
        else
        {
            debug_assertMessage(D_00550C10);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdHandlerReadNoInflate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdHandlerReadInflate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", unifile_read_func);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdManager);

extern int func_001351E0(int a0, void *buf, int n);
extern char D_00550D58[];
extern char D_00550D80[];

void iosCdvdDiskReady(int *a0, void *buf, int n)
{
    char *p = (char *) buf;
    long long ret;
    for (;;)
    {
        ret = func_001351E0(a0[0x15C / 4], p, n);
        if (ret <= 0)
        {
            break;
        }
        p += ret;
        n -= ret;
    }
    debug_assertMessage(D_00550D58, a0[0x24 / 4]);
    if (ret < 0)
    {
        debug_assertMessage(D_00550D80);
    }
}

extern void iosCdvdManager(int *a0, void *buf, int n);
extern unsigned char D_006A0038[];

void iosCdvdLoad(int *a0, void *a1, int a2)
{
    if (a1 != 0)
    {
        if ((*(long long *) a0 & 1) == 1)
        {
            iosCdvdDiskReady(a0, a1, a2);
        }
        else
        {
            iosCdvdManager(a0, a1, a2);
        }
        return;
    }
    while (a2 > 0)
    {
        int n = (a2 < 0x401) ? a2 : 0x400;
        void *buf = D_006A0038;
        if ((*(long long *) a0 & 1) == 1)
        {
            iosCdvdDiskReady(a0, buf, n);
        }
        else
        {
            iosCdvdManager(a0, buf, n);
        }
        a2 -= n;
    }
}

extern void func_00261188(unsigned char *buf, const char *fmt, int a0);
extern int func_002614F8(int a0, unsigned char *buf);
extern char D_00550D98[];

/* NOTE: the retail-branch C for the retail twin (func_001321C8) is a silent
 * regression there — the binary (both versions, hash-equal) has a 0x1D0
 * frame, two func_00261188 sprintf calls (D_00550D98 + D_0062C0F8) and an
 * inline D_00629E39-table normpath; the retail source has none of that.
 * Needs real matching work, not a port. */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdPackLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdBackGroundMgrAdd);

extern void iosMsgSend(void *a0, void *a1, int a2);
extern unsigned char D_0027A840[];

union U001325D8
{
    long long ll;
    int i[2];
};

void iosCdvdBackGroundMgr(int a0, int a1)
{
    union U001325D8 *p = (union U001325D8 *) a0;
    p->i[1] = 1;
    p->ll = (p->ll & ~1LL) | (a1 & 1);
    iosMsgSend(D_0027A840, (void *) a0, 0);
}

void iosCdvdDirectStOpen(void *a0) {
    *(int *)((char *)a0 + 4) = 2;
    iosMsgSend(D_0027A840, a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdChgFileName);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdGetFileLsn);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/cdvd", iosCdvdSync);

extern char D_00629E39[];
extern char D_0062C0F8[];

int iosCdvdLoadPackFile(int a0)
{
    unsigned char buf[0x100];
    unsigned char *p = buf;
    unsigned char c;
    unsigned char nc;
    func_00261188(buf, D_0062C0F8, a0);
    c = buf[0];
    do
    {
        /* `nc = 24` (the sign-extend shift count) writes the next-char temp at
         * the loop top, splitting its live range from `c` so the carried byte
         * keeps its own register with the copy in the bnez delay slot. */
        int t = ((int) c) << (nc = 24);
        int sc = t >> 24;
        if (sc == '/')
        {
            *p = '\\';
        }
        else
        {
            int r = sc - 0x20;
            if ((D_00629E39[sc] & 2) == 0)
            {
                r = sc;
            }
            *p = r;
        }
        p++;
        nc = *p;
        c = nc;
    } while (nc != 0);
    return func_002614F8(a0, buf);
}

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

typedef struct { char f0; char pad[0x12B]; } CdEntry;
extern CdEntry D_0069F800[];

int iosCdvdBackGroundRead(void)
{
    char *p = (char *) D_0069F800;
    char *limit = p + 0x834;
    int count = 0;
    do {
        if (*p != 0) {
            count += (*(unsigned int *)(p + 0x108) >> 1) & 1;
        }
        p += 0x12C;
    } while ((int)p < (int)limit);
    return count;
}

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
