#include "common.h"

union U001325D8 {
    long long ll;
    int i[2];
};

/* The streaming request iosCdvdMgrStStart hands to the cdvd thread: the
 * request record at D_0029B410 and the preload window it describes. */
typedef struct {
    char *owner; /* 0x00 */
    int f_4;
    int f_8;
    char *buf; /* 0x0C */
    int size;  /* 0x10 */
    int f_14;
    int f_18;
    int f_1C;
} CdStReq;

extern CdStReq D_0029B410;

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdStManager);

/* The record sceCdSearchFile fills in: it writes 0x24 bytes of it (lsn, size,
 * the name column and the date), and the stack slot it is given is 0x30.  */
typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int reserved;
} CdlFILE;

/* iosCdvdSrhBuff is the directory cache: D_0063A36C records of 0x30 bytes,
 * and D_00298E68 is iosCdvdSrhBuff[0].name (the ROM addresses the name column
 * through its own symbol).  */
typedef struct {
    int lsn;
    int size;
    char name[0x28];
} CdSrhEnt;

extern CdSrhEnt iosCdvdSrhBuff[];
extern char D_00298E68[];
extern int D_0063A36C;
extern char D_00550CF8[];
extern char D_00550D30[];
extern unsigned int strlen(const char *s);
extern int strcmp(const char *a, const char *b);
extern char *strncpy(char *d, const char *s, int n);
extern int sceCdSearchFile(CdlFILE *fp, const char *name);
extern void debug_StdPrintfDummy();

void iosCdvdMgrSearchFile(char *self)
{
    /* The walk index stays in its stack slot and is re-read after every
     * strcmp: the directory cache it indexes is the table the cdvd thread
     * also fills, so the counter is volatile. */
    volatile int i;
    int r = 1;

    if (strlen(self + 0x38) < 0x28) {
        for (i = 0; i < D_0063A36C; i++) {
            r = strcmp(self + 0x38, D_00298E68 + i * 0x30);
            if (r == 0) {
                break;
            }
        }
    } else {
        debug_StdPrintfDummy(D_00550CF8);
    }
    if (r == 0) {
        *(int *)(self + 0x138) = iosCdvdSrhBuff[i].lsn;
        *(int *)(self + 0x13C) = iosCdvdSrhBuff[i].size;
    } else {
        *(int *)(self + 0xC) = 0;
        if (sceCdSearchFile((CdlFILE *)(self + 0x138), self + 0x38) == 0) {
            *(int *)(self + 0xC) = 100;
        }
        if (D_0063A36C < 200) {
            iosCdvdSrhBuff[D_0063A36C].lsn = *(int *)(self + 0x138);
            iosCdvdSrhBuff[D_0063A36C].size = *(int *)(self + 0x13C);
            strncpy(iosCdvdSrhBuff[D_0063A36C].name, self + 0x38, 0x28);
            D_0063A36C++;
        } else {
            debug_StdPrintfDummy(D_00550D30);
        }
    }
}

extern int stagePreLoadSectorCnt;
extern int stagePreLoadLsn;
extern int D_0063C178;
extern char stagePreLoadBuff[];
extern char D_006BC830[];
extern int iosMsgSend(void *a0, void *a1, int a2);
extern long long inflate_cd_read_func(void *buf, long long size, int *self);
extern int open_inflate_handler(void *readfunc, void *arg);

void iosCdvdMgrStStart(char *self)
{
    int total;
    int rest;
    int cnt = stagePreLoadSectorCnt;
    int prelsn = stagePreLoadLsn;
    int lsn = *(int *)(self + 0x138);

    D_0063C178 = cnt;
    *(int *)(self + 0x34) = 0;
    *(int *)(self + 0xC) = 0;
    if (lsn == prelsn) {
        lsn += cnt;
    } else {
        stagePreLoadSectorCnt = 0;
        D_0063C178 = 0;
    }
    D_0029B410.owner = self;
    D_0029B410.buf = stagePreLoadBuff;
    D_0029B410.size = 0x380;
    D_0029B410.f_18 = D_0063C178;
    D_0029B410.f_14 = D_0063C178;
    if (D_0063C178 >= 0x380) {
        D_0029B410.f_14 = 0;
    }
    D_0029B410.f_1C = 0;
    *(int *)(self + 0x14) = lsn;
    total = (*(unsigned int *)(self + 0x13C) - 1) >> 11;
    rest = lsn - *(int *)(self + 0x138) - 1;
    *(int *)(self + 0x18) = total - rest;
    D_0029B410.f_8 = 0;
    iosMsgSend(D_006BC830, &D_0029B410, 1);
    *(int *)(self + 0x160) = open_inflate_handler(inflate_cd_read_func, self);
}

extern char D_0029B3E0[];
extern char D_00550C58[];
extern char D_00550D68[];
extern char D_0063A390[];
extern int iosThreadGetPri(int tid);
extern void iosThreadSetPri(int tid, int pri);
extern int sceCdBreak(void);
extern int iosMsgRecv(void *q, void *buf, int mode);
extern void sprintf();
extern void debug_assertMessage(const char *file, int line, const char *msg);
extern void __assert(const char *file, int line, char *expr);
extern int close_inflate_handler(int handle);

void iosCdvdMgrStStop(char *self)
{
    char buf[128];
    int msg;
    int pri;

    pri = iosThreadGetPri(0);
    iosThreadSetPri(0, 27);
    D_0029B410.f_8 = 1;
    iosMsgSend(D_006BC830, &D_0029B410, 1);
    if (D_0029B410.f_4 == 1) {
        sceCdBreak();
    }
    iosThreadSetPri(0, pri);
    iosMsgRecv(D_0029B3E0, &msg, 1);
    if (msg != 2) {
        sprintf(buf, D_00550D68, msg);
        debug_assertMessage(D_00550C58, 906, buf);
        __assert(D_00550C58, 906, D_0063A390);
    }
    *(int *)(self + 0xC) = 0;
    close_inflate_handler(*(int *)(self + 0x160));
}

extern char D_00637E69[];
extern char D_0063A3A0[];
extern int strcpy();
extern int iosCdvdChgFileName(int a0);

/* INTERIM: the January-2002 listing expands iosCdvdChgFileName (cdvd.c rows
 * 958-967) inside unifile_read_func, so the 2001 source declared it `inline`
 * and the compiler emitted both the inlined copy and the out-of-line body.
 * While this TU still carries asm members the out-of-line body has to stay at
 * its own ROM slot below, so the inlined copy is spelled here as a static
 * stand-in.  Delete this once the TU is C-complete and mark the real
 * definition `inline`.  */
static inline int chgFileNameInlined(int a0)
{
    unsigned char buf[0x100];
    unsigned char *p = buf;
    unsigned char c;
    unsigned char nc;
    sprintf(buf, D_0063A3A0, a0);
    c = buf[0];
    do {
        int t = ((int)c) << (nc = 24);
        int sc = t >> 24;
        if (sc == '/') {
            *p = '\\';
        } else {
            int r = sc - 0x20;
            if ((D_00637E69[sc] & 2) == 0) {
                r = sc;
            }
            *p = r;
        }
        p++;
        nc = *p;
        c = nc;
    } while (nc != 0);
    return strcpy(a0, buf);
}

extern char D_00550CC8[];
extern char D_00550CD8[];
extern char D_00550D90[];
extern char D_00550DA8[];
extern unsigned char D_0063A378;
extern int D_0063A374;
extern int sceCdDiskReady(int mode);
extern int sceCdGetDiskType(void);
extern int sceCdSearchFile(CdlFILE *fp, const char *name);
extern void debug_StdPrintfDummy();
extern void iosCdvdMgrSearchFile(char *self);
extern void iosCdvdMgrStStart(char *self);
extern void iosCdvdMgrStStop(char *self);

/* INTERIM: the listing expands iosCdvdDiskReadyBlock (cdvd.c rows 701-720)
 * here too, so the 2001 source declared it `inline` as well.  Same treatment
 * as chgFileNameInlined above: a static stand-in until the TU is C-complete.  */
static inline void diskReadyBlockInlined(void)
{
    if (sceCdDiskReady(1) != 2) {
        CdlFILE fp;
        char file[32];
        *(long long *)file = *(long long *)D_00550CC8;
        *(int *)(file + 8) = *(int *)(D_00550CC8 + 8);
        iosCdvdChgFileName((int)file);
        debug_StdPrintfDummy(D_00550CD8, D_00550CC8, file);
        do {
            sceCdDiskReady(0);
        } while (sceCdGetDiskType() != D_0063A374 || sceCdSearchFile(&fp, file) == 0);
    }
}

void iosCdvdMgrLoad(char *self)
{
    int rv;

    chgFileNameInlined((int)(self + 0x38));
    *(char *)(self + 0x15C) = 0;
    *(unsigned char *)(self + 0x15D) = D_0063A378;
    *(char *)(self + 0x15E) = 0;
    *(int *)(self + 0x28) = 0;
    diskReadyBlockInlined();
    *(int *)(self + 0xC) = 0;
    iosCdvdMgrSearchFile(self);
    if (*(int *)(self + 0xC) != 0) {
        debug_StdPrintfDummy(D_00550D90, self + 0x38);
        return;
    }
    *(int *)(self + 0x30) = ((unsigned int)(*(int *)(self + 0x13C) - 1) >> 11) + 1;
    iosCdvdMgrStStart(self);
    if (*(int *)(self + 0xC) != 0) {
        return;
    }
    if (*(int (**)(char *, int))(self + 0x1C) != 0) {
        rv = (*(int (**)(char *, int))(self + 0x1C))(self, *(int *)(self + 0x20));
        if (rv != 0) {
            *(int *)(self + 0xC) = 102;
        }
    }
    debug_StdPrintfDummy(D_00550DA8);
    iosCdvdMgrStStop(self);
    if (*(int *)(self + 0xC) == 0) {
        *(int *)(self + 0xC) = 0;
    }
}

extern int D_0063A44C;
extern char D_00550DB8[];
extern void debug_StdPrintfDummy();
extern int iosMallocDebug(int heap, int size, const char *file, int line);
extern void iosFree(void *p);
extern void iosCdvdHandlerRead(int *self, void *buf, int n);

void temp_loadfunc(int *self, int name, int size, int a3, int a4, int a5, int seg)
{
    void *p = (void *)iosMallocDebug(D_0063A44C, size, D_00550C58, 1102);

    iosCdvdHandlerRead(self, p, size);
    debug_StdPrintfDummy(D_00550DB8, name, size, seg);
    iosFree(p);
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdMgrPackLoad);

extern char D_00550E58[];
extern int D_0063A388;
extern char *memcpy(char *d, const char *s, int n);

int iosCdStRead(unsigned int n, int *buf, int flag, int *result, char *self)
{
    char msgbuf[128];
    int msg;
    CdStReq *req = &D_0029B410;
    int pri = iosThreadGetPri(0);
    int total = 0;
    int size;
    int bytes;

    while (n != 0) {
        iosThreadSetPri(0, 27);
        if (req->f_1C + n > req->size) {
            size = req->size - req->f_1C;
        } else {
            size = n;
        }
        if (flag == 0) {
            size = req->f_18;
        } else {
            while (req->f_18 < size) {
                D_0063A388 = 1;
                iosMsgRecv(D_0029B3E0, &msg, 1);
                if (msg != 1) {
                    sprintf(msgbuf, D_00550E58, msg);
                    debug_assertMessage(D_00550C58, 1304, msgbuf);
                    __assert(D_00550C58, 1304, D_0063A390);
                }
            }
        }
        if (size != 0) {
            bytes = size << 11;
            memcpy((char *)buf, (char *)((req->f_1C << 11) + (int)req->buf), bytes);
            if (req->f_1C + size >= req->size) {
                req->f_1C = 0;
            } else {
                req->f_1C = req->f_1C + size;
            }
            req->f_18 -= size;
            buf += bytes;
            n -= size;
            total += size;
            if (D_0029B410.f_4 == 2) {
                D_0029B410.f_8 = 2;
                iosMsgSend(D_006BC830, &D_0029B410, 1);
            }
        }
        iosThreadSetPri(0, pri);
    }
    return total;
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdHandlerReadNoInflate);

extern char D_00550EC0[];
extern void debug_StdPrintfDummy();
extern long long inflate(void *state, void *buf, int n);

void iosCdvdHandlerReadInflate(int *self, void *buf, int n)
{
    char *p;
    long long len;

    p = buf;
    while ((len = inflate((void *)self[0x160 / 4], p, n)) > 0) {
        p += (int)len;
        n -= (int)len;
    }
    if (len < 0) {
        debug_StdPrintfDummy(D_00550EC0);
    }
}

extern unsigned char D_006B83B8[];
extern void iosCdvdHandlerReadInflate(int *a0, void *buf, int n);
extern void iosCdvdHandlerReadNoInflate(int *a0, void *buf, int n);

void iosCdvdHandlerRead(int *a0, void *a1, int a2)
{
    if (a1 != 0) {
        if ((*(long long *)a0 & 1) == 1) {
            iosCdvdHandlerReadInflate(a0, a1, a2);
        } else {
            iosCdvdHandlerReadNoInflate(a0, a1, a2);
        }
        return;
    }
    while (a2 > 0) {
        int n = (a2 < 0x401) ? a2 : 0x400;
        void *buf = D_006B83B8;
        if ((*(long long *)a0 & 1) == 1) {
            iosCdvdHandlerReadInflate(a0, buf, n);
        } else {
            iosCdvdHandlerReadNoInflate(a0, buf, n);
        }
        a2 -= n;
    }
}

extern char D_00550ED8[];

int unifile_read_func(int *self)
{
    char work[32];
    int cnt;
    int lsn;

    iosCdvdHandlerRead(self, &cnt, 4);
    while (cnt-- > 0) {
        iosCdvdHandlerRead(self, work, 32);
        sprintf((char *)self + 0x38, D_00550ED8, work);
        chgFileNameInlined((int)((char *)self + 0x38));
        strcpy(D_00298E68 + D_0063A36C * 0x30, (char *)self + 0x38);
        iosCdvdHandlerRead(self, &lsn, 4);
        *(int *)(D_00298E68 + D_0063A36C * 0x30 - 8) = lsn / 2048 + self[0x138 / 4];
        iosCdvdHandlerRead(self, D_00298E68 + D_0063A36C * 0x30 - 4, 4);
        D_0063A36C++;
    }
    return 1;
}

/* The 0x38 name column of a cdvd request is written 16 bytes at a time, so it
 * is typed as an 8-byte-aligned pair; D_00550EE8 is the fixed disc path the
 * unifile request always loads. */
typedef struct {
    long long lo;
    long long hi;
} CdvdName16;

extern CdvdName16 D_00550EE8;
extern char D_006AF9C0[];

void iosCdvdUnifileInfoGet(void)
{
    *(long long *)D_006AF9C0 &= ~1LL;
    *(CdvdName16 *)(D_006AF9C0 + 0x38) = D_00550EE8;
    *(int (**)())(D_006AF9C0 + 0x1C) = unifile_read_func;
    iosCdvdMgrLoad(D_006AF9C0);
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdManager);

extern unsigned char CdvdMsgQ[];
extern int iosMsgSend(void *a0, void *a1, int a2);

void iosCdvdDiskReady(int a0)
{
    union U001325D8 *p = (union U001325D8 *)a0;
    p->i[1] = 0;
    iosMsgSend(CdvdMsgQ, (void *)a0, 0);
}

void iosCdvdLoad(int a0, int a1)
{
    union U001325D8 *p = (union U001325D8 *)a0;
    p->i[1] = 1;
    p->ll = (p->ll & ~1LL) | (a1 & 1);
    iosMsgSend(CdvdMsgQ, (void *)a0, 0);
}

void iosCdvdPackLoad(void *a0)
{
    *(int *)((char *)a0 + 4) = 2;
    iosMsgSend(CdvdMsgQ, a0, 0);
}

extern char D_006B7B80[];
extern char D_00550ED8[];
extern char D_0063A398[];
extern void debug_assert();
extern char *strrchr(const char *s, int c);
extern int strcmp(const char *a, const char *b);

/* INTERIM: the January-2002 listing expands iosCdvdGetFileLsn (cdvd.c rows
 * 739-753) inside iosCdvdBackGroundMgrAdd, so the 2001 source declared it
 * `inline` and the compiler emitted both the inlined copy and the out-of-line
 * body.  While this TU still carries asm members the out-of-line body has to
 * stay at its own ROM slot below, so the inlined copy is spelled here as a
 * static stand-in.  Delete this once the TU is C-complete and mark the real
 * definition `inline`.  */
static inline int getFileLsnInlined(char *name, int *size)
{
    int i;

    for (i = 0; i < D_0063A36C; i++) {
        if (strcmp(name, D_00298E68 + i * 0x30) == 0)
            goto found;
    }
    debug_assert(D_00550C58, 749);
    __assert(D_00550C58, 749, D_0063A398);
found:
    *size = iosCdvdSrhBuff[i].size;
    return iosCdvdSrhBuff[i].lsn;
}

char *iosCdvdBackGroundMgrAdd(char *name, void *readFunc, int readArg, void *readyFunc,
                              void *resumeFunc, int cbArg, void *closeFunc, int closeArg)
{
    char buf[0x100];
    int size;
    int i;
    char *bg;
    char *p;

    for (i = 0; i < 7; i++) {
        if (D_006B7B80[i * 0x12C] == 0)
            goto found;
    }
    for (i = 0; i < 7; i++) {
        /* the January-2002 listing prints the whole table here; the retail
         * build compiles the printf out and leaves the empty countdown */
    }
    debug_assert(D_00550C58, 1890);
    __assert(D_00550C58, 1890, D_0063A398);
found:
    bg = D_006B7B80 + i * 0x12C;
    *(int *)(bg + 0x108) |= 1;
    *(int *)(bg + 0x108) &= ~2;
    *(int *)(bg + 0x108) &= ~0x10;
    *(int *)(bg + 0x108) |= 4;
    strcpy(bg, name);
    *(void **)(bg + 0x100) = readFunc;
    *(int *)(bg + 0x104) = readArg;
    *(void **)(bg + 0x118) = readyFunc;
    *(void **)(bg + 0x11C) = resumeFunc;
    *(int *)(bg + 0x120) = cbArg;
    *(void **)(bg + 0x124) = closeFunc;
    *(int *)(bg + 0x128) = closeArg;
    p = strrchr(bg, '/');
    if (p != 0) {
        p = p + 1;
    } else {
        p = bg;
    }
    sprintf(buf, D_00550ED8, p);
    chgFileNameInlined((int)buf);
    *(int *)(bg + 0x114) = getFileLsnInlined(buf, &size);
    *(int *)(bg + 0x10C) = size;
    *(int *)(bg + 0x110) = 0;
    *(int *)(bg + 0x108) &= ~1;
    return bg;
}

extern int D_0028F4C0[];
extern int D_0063C17C;
extern int D_0063A368;
extern int D_0063A384;
extern int D_0063A3C8;
extern int D_0063A3CC;
extern void iosThreadSleep(void);
extern void iosPadDisable(void);
extern void iosPadEnable(void);
extern int sceCdStatus(void);
typedef void (*BgReadyFunc)(char *self, int arg, int flag);
typedef void (*BgResumeFunc)(char *self, int arg);

void cdWait(int *busy)
{
    CdlFILE fp;
    char file[32];
    char *self;
    int r;

    D_0063A368 = 1;
    iosThreadSleep();
    D_0063A368 = 0;
    while (1) {
        self = (char *)D_0063C17C;
        switch (D_0063A384) {
        case 0:
            if (sceCdStatus() != 1) {
                break;
            }
            D_0063A384 = 1;
            D_0063A3CC = D_0028F4C0[0x14 / 4];
        case 1:
            if (*(BgReadyFunc *)(self + 0x118) != 0) {
                (*(BgReadyFunc *)(self + 0x118))(self, *(int *)(self + 0x120),
                                                 (*(unsigned int *)(self + 0x108) >> 2) & 1);
                *(int *)(self + 0x108) &= ~4;
            }
            if (((*(unsigned int *)(self + 0x108) >> 4) & 1) == 0) {
                iosPadDisable();
                D_0028F4C0[0x14 / 4] = 1;
                D_0063A3C8 = 1;
            }
            *(long long *)file = *(long long *)D_00550CC8;
            *(int *)(file + 8) = *(int *)(D_00550CC8 + 8);
            chgFileNameInlined((int)file);
            r = sceCdDiskReady(1);
            if (r == 2 && sceCdGetDiskType() == D_0063A374 && sceCdSearchFile(&fp, file) != 0) {
                *(int *)(self + 0x108) |= 4;
                if (*(BgResumeFunc *)(self + 0x11C) != 0) {
                    (*(BgResumeFunc *)(self + 0x11C))(self, *(int *)(self + 0x120));
                }
                D_0063A384 = r;
                if (D_0063A3C8 != 0) {
                    iosPadEnable();
                    D_0063A3C8 = 0;
                    D_0028F4C0[0x14 / 4] = D_0063A3CC;
                }
            }
            break;
        case 2:
            D_0063A384 = 0;
            break;
        }
        if (D_0063A384 == 0) {
            break;
        }
        *busy = 1;
        D_0063A368 = 1;
        iosThreadSleep();
        D_0063A368 = 0;
    }
}

extern int D_0063A370;
extern int D_0063A380;
extern int D_0063A3D0;
extern int D_0063A3D4;
extern void cdWait(int *flag);
extern int sceCdStatus(void);
extern int sceCdSync(int mode);
extern int sceCdGetError(void);
extern int sceCdReadIOPm(int lsn, int sectors, void *buf, int *mode);
extern int sceCdRead(int lsn, int sectors, void *buf, int *mode);

int iosCdvdBackGroundRead(char *self, void *buf, int size)
{
    int flag;

    D_0063A3D0++;
    while (1) {
        flag = 0;
        while ((D_0063A370 == 1 && sceCdStatus() != 10) || sceCdDiskReady(1) != 2) {
            cdWait(&flag);
        }
        while (sceCdRead(*(int *)(self + 0x114) + *(int *)(self + 0x110) / 2048, size / 2048, buf,
                         &D_0063A380) == 0) {
            cdWait(&flag);
        }
        while (sceCdSync(1) != 0) {
            cdWait(&flag);
        }
        if (flag != 0) {
            D_0063A3D4++;
            while (sceCdBreak() == 0) {
                cdWait(&flag);
            }
        } else {
            if (sceCdGetError() != 0 && ((*(unsigned int *)(self + 0x108) >> 4) & 1) == 0) {
                while (sceCdBreak() == 0) {
                    cdWait(&flag);
                }
            } else {
                break;
            }
        }
        cdWait(&flag);
    }
    *(int *)(self + 0x110) += size;
    return !(*(int *)(self + 0x110) < *(int *)(self + 0x10C));
}

int iosCdvdBackGroundReadIOPm(char *self, void *buf, int size)
{
    int flag;

    D_0063A3D0++;
    while (1) {
        flag = 0;
        while ((D_0063A370 == 1 && sceCdStatus() != 10) || sceCdDiskReady(1) != 2) {
            cdWait(&flag);
        }
        while (sceCdReadIOPm(*(int *)(self + 0x114) + *(int *)(self + 0x110) / 2048, size / 2048,
                             buf, &D_0063A380) == 0) {
            cdWait(&flag);
        }
        while (sceCdSync(1) != 0) {
            cdWait(&flag);
        }
        if (flag != 0) {
            D_0063A3D4++;
            while (sceCdBreak() == 0) {
                cdWait(&flag);
            }
        } else {
            if (sceCdGetError() != 0 && ((*(unsigned int *)(self + 0x108) >> 4) & 1) == 0) {
                while (sceCdBreak() == 0) {
                    cdWait(&flag);
                }
            } else {
                break;
            }
        }
        cdWait(&flag);
    }
    *(int *)(self + 0x110) += size;
    return !(*(int *)(self + 0x110) < *(int *)(self + 0x10C));
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", iosCdvdDirectStOpen);

void iosCdvdDirectStClose(int *self)
{
    int err;
    self[0xC / 4] = 0;
    err = sceCdStStop();
    if (err == 0) {
        self[0xC / 4] = sceCdGetError();
    }
    sceSifFreeIopHeap(self[0x164 / 4]);
}

extern char D_00637E69[];
extern char D_0063A3A0[];
extern void sprintf();
extern int strcpy();

int iosCdvdChgFileName(int a0)
{
    unsigned char buf[0x100];
    unsigned char *p = buf;
    unsigned char c;
    unsigned char nc;
    sprintf(buf, D_0063A3A0, a0);
    c = buf[0];
    do {
        /* `nc = 24` (the sign-extend shift count) writes the next-char temp at
         * the loop top, splitting its live range from `c` so the carried byte
         * keeps its own register with the copy in the bnez delay slot. */
        int t = ((int)c) << (nc = 24);
        int sc = t >> 24;
        if (sc == '/') {
            *p = '\\';
        } else {
            int r = sc - 0x20;
            if ((D_00637E69[sc] & 2) == 0) {
                r = sc;
            }
            *p = r;
        }
        p++;
        nc = *p;
        c = nc;
    } while (nc != 0);
    return strcpy(a0, buf);
}

extern char D_0063A398[];
extern int strcmp();
extern void debug_assert();
extern void __assert();

int iosCdvdGetFileLsn(char *name, int *size)
{
    int i;

    for (i = 0; i < D_0063A36C; i++) {
        if (strcmp(name, D_00298E68 + i * 0x30) == 0)
            goto found;
    }
    debug_assert(D_00550C58, 749);
    __assert(D_00550C58, 749, D_0063A398);
found:
    *size = iosCdvdSrhBuff[i].size;
    return iosCdvdSrhBuff[i].lsn;
}

extern int CdvdMsgQ_LoadEnd[];
extern int iosMsgRecv(void *q, void *buf, int mode);

int iosCdvdSync(int a0)
{
    int local = a0;
    iosMsgRecv(CdvdMsgQ_LoadEnd, &local, 1);
    return 1;
}

extern char iosCdvd[];

void iosCdvdLoadPackFile(int a0, char *name, int a2)
{
    int buf[4];
    *(long long *)iosCdvd = (*(long long *)iosCdvd & ~1LL) | (a0 & 1);
    strcpy(iosCdvd + 0x38, name);
    *(int *)(iosCdvd + 0x24) = a2;
    *(int *)(iosCdvd + 0x1C) = 0;
    *(int *)(iosCdvd + 0x20) = 0;
    iosCdvdPackLoad(iosCdvd);
    buf[0] = (int)iosCdvd;
    iosMsgRecv(CdvdMsgQ_LoadEnd, buf, 1);
}

extern int D_0063A384;

int iosCdvdDiskStatusGet(void)
{
    return D_0063A384;
}

void iosCdvdBackGroundMgrDelete(char *self)
{
    *(int *)(self + 0x108) |= 2;
}

int iosCdvdBackGroundMgrNotDiskReadyPauseSet(void *a0, int a1)
{
    int *p = (int *)((char *)a0 + 0x108);
    return *p = (*p & ~0x10) | ((a1 & 1) << 4);
}

extern char D_006B7B80[];

int iosCdvdBackGroundMgrDeleteRequestGet(void)
{
    char *p = D_006B7B80;
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

int iosCdvdBackGroundMgrEntryNum(void)
{
    char *p = D_006B7B80;
    char *limit = p + 0x834;
    int count = 0;
    do {
        char b = *p;
        int new_count = count + 1;
        p += 0x12C;
        if (b != 0) {
            count = new_count;
        }
    } while ((int)p < (int)limit);
    return count;
}

void iosCdvdBackGroundMgrSeek(char *self, int val)
{
    *(int *)(self + 0x110) = val;
}

extern int D_0063C17C;

int iosCdvdBackGroundMgrGetRunning(void)
{
    return D_0063C17C;
}

extern char D_00550FD8[];
extern void debug_StdPrintfDummy();
extern int sceCdStRead(int a0, int a1, int a2, void *a3);

int iosCdvdDirectStRead(int a0, int a1, int a2, int *a3)
{
    int local, result;
    *a3 = 0;
    result = sceCdStRead(a2 >> 11, a1, 1, &local) << 11;
    if (local != 0) {
        debug_StdPrintfDummy(D_00550FD8, local);
        *a3 = 1;
    }
    return result;
}

/* The inflate handler's read callback (installed by iosCdvdMgrStStart): hand
 * the decoder at most as many bytes as are still left in the streamed file --
 * its total length at +0x13C minus the bytes already consumed at +0x28.  */
long long inflate_cd_read_func(void *buf, long long size, int *self)
{
    long long rest;
    long long len;

    rest = (unsigned int)(self[0x13C / 4] - self[0x28 / 4]);

    if (rest < size)
        len = rest;
    else
        len = size;

    if (len != 0)
        iosCdvdHandlerReadNoInflate(self, buf, len);

    return len;
}

extern int D_0063C17C;

void iosCdvdBackGroundMgrInit(void)
{
    char *p = D_006B7B80;
    int i;
    p += 0x708;
    for (i = 6; i >= 0; i--) {
        *p = 0;
        p -= 0x12C;
    }
    D_0063C17C = 0;
}

typedef int (*BgFunc)(char *self, int arg);

void iosCdvdBackGroundMgr(void)
{
    char *bg = D_006B7B80;
    int i;
    unsigned int flag;
    BgFunc func;

    for (i = 6; i >= 0; i--, bg += 0x12C) {
        if (*bg == 0 || ((flag = *(unsigned int *)(bg + 0x108)) & 1) != 0)
            continue;
        D_0063C17C = (int)bg;
        if (((flag >> 1) & 1) == 0) {
            if ((func = *(BgFunc *)(bg + 0x100)) != 0) {
                if (func(bg, *(int *)(bg + 0x104)) > 0)
                    *(int *)(bg + 0x100) = 0;
            }
        } else {
            if ((func = *(BgFunc *)(bg + 0x124)) != 0)
                func(bg, *(int *)(bg + 0x128));
            *bg = 0;
        }
        D_0063C17C = 0;
    }
}

extern char D_00550CC8[];
extern char D_00550CD8[];
extern int D_0063A374;
extern int sceCdDiskReady(int mode);
extern int sceCdGetDiskType(void);
extern int sceCdSearchFile(CdlFILE *fp, const char *name);

void iosCdvdDiskReadyBlock(void)
{
    if (sceCdDiskReady(1) != 2) {
        CdlFILE fp;
        char file[32];
        *(long long *)file = *(long long *)D_00550CC8;
        *(int *)(file + 8) = *(int *)(D_00550CC8 + 8);
        iosCdvdChgFileName((int)file);
        debug_StdPrintfDummy(D_00550CD8, D_00550CC8, file);
        do {
            sceCdDiskReady(0);
        } while (sceCdGetDiskType() != D_0063A374 || sceCdSearchFile(&fp, file) == 0);
    }
}
