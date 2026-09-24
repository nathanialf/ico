#include "common.h"
#include "cdvd.h"
#include "debug.h"
#include "debug_exception.h"
#include "inflate.h"
#include "memory.h"
#include "message.h"
#include "pad.h"

union U001325D8 {
    long long ll;
    int i[2];
};

/* The cdvd handle the streaming request reads through: the sector cursor and
 * the remaining count the manager advances, and the sceCdRead mode word the
 * handle carries at 0x15C. */
typedef struct {
    char _0[0x14];
    int lsn;  /* 0x14 */
    int left; /* 0x18 */
    char _1C[0x140];
    int mode; /* 0x15C */
} CdStOwner;

/* The streaming request iosCdvdMgrStStart hands to the cdvd thread: the
 * request record at D_0029B410 and the preload window it describes. */
typedef struct {
    CdStOwner *owner; /* 0x00 */
    int f_4;
    int f_8;
    char *buf; /* 0x0C */
    int size;  /* 0x10 */
    int f_14;
    int f_18;
    int f_1C;
} CdStReq;

extern CdStReq D_0029B410;
extern char D_0029B3E0[];

/* .bss, owned by cdvd.o and reached only from this file (MAIN.MAP line 7688
   gives the member, 0xC38 in its January link, and names no symbol in it), in
   the ROM's run order, 0x6AF9C0..0x6BC860.  The names are ours.
   unifileHandle is the cdvd handle iosCdvdUnifileInfoGet loads the unifile
   through (a handle is 33216 bytes: the 0x180 header, the 32 KB sector
   buffer and the size word at 0x8180, the same size iosCdvdManager's reply
   buffer and mv_main's stream file take); bgReqTable the seven 300-byte
   background requests; skipBuf the 1 KB sink iosCdvdHandlerRead reads into
   when the caller passes no buffer; stThread, stStack and stReqQ the stream
   manager's thread record, its 16 KB stack and its request queue. */
static char unifileHandle[33216];

static char bgReqTable[7 * 300];

static unsigned char skipBuf[1024];

static char stThread[120];

static char stStack[16384];

static char stReqQ[48];

/* .sbss, owned by cdvd.o and reached only from this file (MAIN.MAP names no
   symbol in the run; its 0x18 is the January object), in the ROM's run order,
   0x63C168..0x63C18C.  The names are ours.  cdvdMsgRing and cdvdLoadEndRing
   are the two-slot rings of the manager's request queue and its load-end
   queue, stPreLoadCnt the preloaded sector count iosCdvdMgrStStart hands the
   stream, bgRunning the background request iosCdvdBackGroundMgr is running,
   stReqRing and stAckRing the rings of the stream manager's request and
   acknowledge queues.  WHAT THE BYTES PIN: stReqRing's queue is created with
   one slot, yet the ROM keeps eight bytes between it and stAckRing and no
   instruction reaches the second word; they cannot say whether that word is
   the ring's or an object of its own. */
static int cdvdMsgRing[2];

static int cdvdLoadEndRing[2];

static int stPreLoadCnt;

static int bgRunning;

static int stReqRing[2];

static int stAckRing[1];

extern char D_00550C40[];
extern char D_00550C58[];
extern char D_00550C68[];
extern char D_00550C88[];
extern char D_0063A390[];
extern int D_0063A370;
extern int D_0063A388;
extern void sprintf();
extern void __assert(const char *file, int line, char *expr);
extern int sceCdRead(int lsn, int sectors, void *buf, int *mode);
extern int sceCdSync(int mode);
extern int sceCdGetError(void);
extern int sceCdInit(int mode);
extern int sceCdMmode(int media);
extern void iosCdvdDiskReadyBlock(void);

/* Compiled-out debug print (our name), the empty-body construct main.c's
   mainDebugBar and debug_exception.c's debugExcDebugDisp carry: it inlines to
   nothing and emits no byte, but each call leaves one (use (const_int 0))
   until flow.  WHAT THE BYTES PIN: the January listing prints at rows 577
   (puts, in the err == -1 block) and 582 (printf of err), and retail keeps
   both strings ("get error fail", "st cd read error %d\n") in this member's
   .rodata but has no call; retail's n in $s0 and err in $s1, the reverse of
   January's, need err's live length at 9 or more, which three such insns in
   the err == -1 block give and two do not (complete56: deleted lines, if (0),
   a string-argument or an err-argument empty inline all 16 words, a
   do-while(0) 63).  WHAT THEY CANNOT PIN: the construct the retail source
   used for those prints, or why it left three zero-code insns here. */
static __inline__ void stDebugPrint(void) {}

void iosCdvdStManager(void)
{
    char buf[128];
    char buf2[256];
    CdStReq *req;
    char *p;
    int n;
    unsigned int err;
    int mode;

    D_0029B410.f_4 = 0;
    iosMsgQueueCreate(stReqQ, stReqRing, 1);
    iosMsgQueueCreate(D_0029B3E0, stAckRing, 1);

    while (1) {
        req = &D_0029B410;
        mode = 0;
        if (req->f_4 != 1) {
            mode = 1;
        }
        if (iosMsgRecv(stReqQ, (int *)&req, mode) == -1) {
            if (req->f_4 != 1) {
                sprintf(buf, D_00550C40, req->f_4);
                debug_assertMessage(D_00550C58, 518, buf);
                __assert(D_00550C58, 518, D_0063A390);
            }
            if (req->f_1C > req->f_14) {
                n = req->f_1C - req->f_14;
            } else if (req->f_1C < req->f_14 || req->f_18 == 0) {
                n = req->size - req->f_14;
            } else {
                n = 0;
                if (req->f_18 != req->size) {
                    sprintf(buf2, D_00550C68, req->f_18);
                    debug_assertMessage(D_00550C58, 546, buf2);
                    __assert(D_00550C58, 546, D_0063A390);
                }
            }
            if (n > 16) {
                n = 16;
            }
            if (req->owner->left < n) {
                n = req->owner->left;
            }
            if (n != 0) {
                p = req->buf + (req->f_14 << 11);
            retry:
                if (sceCdRead(req->owner->lsn, n, p, &req->owner->mode) == 0) {
                    sprintf(buf2, D_00550C88);
                    debug_assertMessage(D_00550C58, 569, buf2);
                    __assert(D_00550C58, 569, D_0063A390);
                }
                sceCdSync(0);
                err = sceCdGetError();
                if ((int)err == -1) {
                    sceCdInit(0);
                    sceCdMmode(D_0063A370);
                    stDebugPrint();
                    stDebugPrint();
                    stDebugPrint();
                }
                if (err >= 2) {
                    iosCdvdDiskReadyBlock();
                    goto retry;
                }
                if (D_0063A388 != 0) {
                    iosMsgSend(D_0029B3E0, 1, 0);
                    D_0063A388 = 0;
                }
                req->owner->lsn += n;
                req->owner->left -= n;
                req->f_14 += n;
                req->f_18 += n;
                if (req->f_14 >= req->size) {
                    req->f_14 = 0;
                }
            } else {
                req->f_4 = 2;
            }
        } else {
            switch (req->f_8) {
            case 0:
            case 2:
                req->f_4 = 1;
                break;
            case 1:
                iosMsgSend(D_0029B3E0, 2, 0);
                req->f_4 = 0;
                break;
            }
        }
    }
}

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
extern char stagePreLoadBuff[];

void iosCdvdMgrStStart(char *self)
{
    int total;
    int rest;
    int cnt = stagePreLoadSectorCnt;
    int prelsn = stagePreLoadLsn;
    int lsn = *(int *)(self + 0x138);

    stPreLoadCnt = cnt;
    *(int *)(self + 0x34) = 0;
    *(int *)(self + 0xC) = 0;
    if (lsn == prelsn) {
        lsn += cnt;
    } else {
        stagePreLoadSectorCnt = 0;
        stPreLoadCnt = 0;
    }
    D_0029B410.owner = (CdStOwner *)self;
    D_0029B410.buf = stagePreLoadBuff;
    D_0029B410.size = 0x380;
    D_0029B410.f_18 = stPreLoadCnt;
    D_0029B410.f_14 = stPreLoadCnt;
    if (stPreLoadCnt >= 0x380) {
        D_0029B410.f_14 = 0;
    }
    D_0029B410.f_1C = 0;
    *(int *)(self + 0x14) = lsn;
    total = (*(unsigned int *)(self + 0x13C) - 1) >> 11;
    rest = lsn - *(int *)(self + 0x138) - 1;
    *(int *)(self + 0x18) = total - rest;
    D_0029B410.f_8 = 0;
    iosMsgSend(stReqQ, &D_0029B410, 1);
    *(int *)(self + 0x160) = open_inflate_handler(inflate_cd_read_func, self);
}

extern char D_0029B3E0[];
extern char D_00550C58[];
extern char D_00550D68[];
extern char D_0063A390[];
/* kept local: this TU's uses of iosThreadGetPri do not fit the prototype in thread.h */
extern int iosThreadGetPri(int tid);
/* kept local: this TU's uses of iosThreadSetPri do not fit the prototype in thread.h */
extern void iosThreadSetPri(int tid, int pri);
extern int sceCdBreak(void);
extern void sprintf();
extern void __assert(const char *file, int line, char *expr);

void iosCdvdMgrStStop(char *self)
{
    char buf[128];
    int msg;
    int pri;

    pri = iosThreadGetPri(0);
    iosThreadSetPri(0, 27);
    D_0029B410.f_8 = 1;
    iosMsgSend(stReqQ, &D_0029B410, 1);
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

/* newlib <ctype.h> (reconstruction): D_00637E69 is `_ctype_ + 1`, bit 0x02 is
 * _L (lower); the GNU C toupper macro reads its argument once. */
#define _L 0x02
#define islower(c) (D_00637E69[(int)(c)] & _L)
#define toupper(c)                                                                                 \
    ({                                                                                             \
        int __x = (c);                                                                             \
        islower(__x) ? (__x - 'a' + 'A') : __x;                                                    \
    })

extern int strcpy();

/* INTERIM: the January-2002 listing expands iosCdvdChgFileName (cdvd.c rows
 * 958-967) inside unifile_read_func, so the 2001 source declared it `inline`
 * and the compiler emitted both the inlined copy and the out-of-line body.
 * While this TU still carries asm members the out-of-line body has to stay at
 * its own ROM slot below, so the inlined copy is spelled here as a static
 * stand-in.  Delete this once the TU is C-complete and mark the real
 * definition `inline`.  */
static inline int chgFileNameInlined(int a0)
{
    char buf[256];
    char *p = buf;
    char c;

    sprintf(buf, D_0063A3A0, a0);

    do {
        if ((c = *p) == '/') {
            *p = '\\';
        } else {
            *p = toupper(c);
        }
        p++;
    } while (*p != 0);
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

extern void *D_0063A44C;
extern char D_00550DB8[];

void temp_loadfunc(int *self, int name, int size, int a3, int a4, int a5, int seg)
{
    void *p = (void *)iosMallocDebug(D_0063A44C, size, D_00550C58, 1102);

    iosCdvdHandlerRead(self, p, size);
    debug_StdPrintfDummy(D_00550DB8, name, size, seg);
    iosFree(p);
}

/* One entry of a .PAK archive's directory: the four words the loader passes
 * on and the member's name, 0x224 bytes per entry. */
typedef struct PackEnt {
    int f00;        /* 0x00 */
    int f04;        /* 0x04 */
    int f08;        /* 0x08 */
    int size;       /* 0x0C */
    char name[532]; /* 0x10 */
} PackEnt;

typedef void (*PackFunc)(char *self, char *name, int size, int a3, int a4, int a5, int seg);

/* The extension table: 26 rows of a 0x20-byte suffix and the loader that
 * handles it. */
typedef struct PackKind {
    char ext[0x20]; /* 0x00 */
    PackFunc func;  /* 0x20 */
} PackKind;

extern PackKind D_0055F828[];
extern int D_0028F4C0[];
extern int D_0063A3DC;
extern char D_00550DE0[];
extern char D_0063A3B0[];
extern int SgGetDmaTransferStatus(int ch);

/* INTERIM: the listing expands the extension lookup (cdvd.c rows 1043-1050)
 * inside the scan below, so the 2001 source declared it `inline`. */
static inline PackFunc findPackKind(char *ext, int *kind)
{
    int i;

    for (i = 0; i < 26; i++) {
        if (strcmp(ext, D_0055F828[i].ext) == 0) {
            *kind = i;
            return D_0055F828[i].func;
        }
    }
    *kind = -1;
    return 0;
}

/* INTERIM: the listing expands the loader lookup (cdvd.c rows 1063-1078)
 * inside iosCdvdMgrPackLoad, so the 2001 source declared it `inline` too. */
static inline PackFunc getPackLoader(char *name, int *kind)
{
    int len;
    char *p;
    int i;

    D_0063A3DC = 0;
    len = strlen(name);
    p = name + (len - 1);
    for (i = 0; i < len; i++, p--) {
        if (*p == '.') {
            p++;
            return findPackKind(p, kind);
        }
    }
    return 0;
}

void iosCdvdMgrPackLoad(char *self)
{
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
    /* The pack pass runs in its own scope: the two inlined helpers above have
     * released their stack buffers by here, so the header lands in the slot
     * the sprintf buffer used. */
    {
        int hdr[4];
        PackEnt *ent;
        int *num;
        PackEnt *pk;
        PackFunc f;
        int kind;
        int seg;
        int size;

        debug_StdPrintfDummy(D_00550DE0, self + 0x38);
        iosCdvdHandlerRead((int *)self, hdr, 16);
        /* The entry count is the header's first word; the loop re-reads it
         * through this view after every member call. */
        num = hdr;
        debug_StdPrintfDummy(D_0063A3B0, *num);
        D_0028F4C0[7] = *num;
        D_0028F4C0[8] = 0;
        size = *num * sizeof(PackEnt);
        ent = (PackEnt *)iosMallocDebug(D_0063A44C, size, D_00550C58, 1174);
        iosCdvdHandlerRead((int *)self, ent, size);
        pk = ent;
        for (seg = 0; seg < *num; seg++, pk++) {
            debug_BeginTimer(3);
            f = getPackLoader(pk->name, &kind);
            if (f != 0) {
                f(self, pk->name, pk->size, pk->f00, pk->f04, pk->f08, *(int *)(self + 0x24));
            } else {
                temp_loadfunc((int *)self, (int)pk->name, pk->size, pk->f00, pk->f04, pk->f08,
                              *(int *)(self + 0x24));
            }
            debugCdvdLoadInfoSegAdd(*(int *)(self + 0x24), kind, pk->size);
        }
        iosFree(ent);
    }
    debug_GetTimerSec();
    SgGetDmaTransferStatus(1);
    debug_StdPrintfDummy(D_00550DA8);
    iosCdvdMgrStStop(self);
    iosCdvdBackGroundMgr();
    if (*(int *)(self + 0xC) == 0) {
        *(int *)(self + 0xC) = 0;
    }
}

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
                iosMsgSend(stReqQ, &D_0029B410, 1);
            }
        }
        iosThreadSetPri(0, pri);
    }
    return total;
}

extern char D_00550E88[];
extern int D_0063A368;
extern void iosThreadSleep(void);

/* The read-retry sleep (our name): the listing attributes its statements to
   cdvd.c:679-680, a static inline between iosCdvdStManager and
   iosCdvdDiskReadyBlock that is never emitted out of line.  D_0063A368 marks
   the cdvd thread asleep, as cdWait and iosCdvdManager set it around their
   own sleeps. */
static inline void cdvdSleep(void)
{
    D_0063A368 = 1;
    iosThreadSleep();
    D_0063A368 = 0;
}

/* cdvd.c:1365-1501 in the listing.  self is the cdvd handle: 0x0C the result
   word iosCdStRead is handed, 0x28 the bytes consumed, 0x2C readSectorCnt and
   0x34 buffCnt (the assert format names both), 0x30 the sectors still to
   stream, 0x180 the 32 KB sector buffer.  buf is advanced in place (the
   listing puts its only copy on the brace row) and left = n is row 1366.
   ofs is the byte offset in the buffer the sectors are read to, zero because
   a read only happens once the buffer is drained.  WHAT THE BYTES PIN: the
   read's buffer argument is recomputed at the call inside the wait loop
   (addiu $a1,$s0,0x180 at row 1394) while the result argument is hoisted to
   the loop entry (row 1391); a plain self + 0x180 is hoisted by gcse's PRE
   like the result pointer (108 words, strict 86); with a zero addend whose
   constant set reaches the call, gcse's const propagation rewrites
   (plus self ofs) into a copy of self (validate_replace_rtx_1's plus_constant
   case), the + 0x180 that follows is no longer locally anticipatable, and
   the three string addresses keep their callee-saved registers.  WHAT THEY
   CANNOT PIN: the name and row of the offset (rows 1376-1390 are code-free)
   or why the developer kept a zero offset. */
void iosCdvdHandlerReadNoInflate(int *self, void *buf, int n)
{
    int left = n;
    char msg[256];
    int sz;
    int r;
    int cnt;

    while (left > 0) {
        self[0x2C / 4] = 0;
        if (self[0x34 / 4] == 0) {
            cnt = ((unsigned int)self[0x30 / 4] > 15) ? 16 : self[0x30 / 4];
            if (cnt != 0) {
                int ofs = 0;

                while ((r = iosCdStRead(cnt, (int *)((char *)self + ofs + 0x180), 1, &self[0xC / 4],
                                        (char *)self)) == 0) {
                    cdvdSleep();
                }
                self[0x2C / 4] = self[0x2C / 4] + r;
                self[0x30 / 4] = self[0x30 / 4] - self[0x2C / 4];
            }
        }
        if (self[0x34 / 4] != 0) {
            sz = 32768 - self[0x34 / 4];
        } else {
            sz = self[0x2C / 4] << 11;
        }
        if (sz == 0) {
            sprintf(msg, D_00550E88, self[0x2C / 4], self[0x34 / 4]);
            debug_assertMessage(D_00550C58, 1417, msg);
            __assert(D_00550C58, 1417, D_0063A390);
        }
        if (sz >= left) {
            sz = left;
        }
        memcpy(buf, (char *)(self[0x34 / 4] + (int)self + 0x180), sz);
        self[0x34 / 4] = self[0x34 / 4] + sz;
        if ((unsigned int)self[0x34 / 4] > 32767) {
            self[0x34 / 4] = 0;
        }
        left -= sz;
        buf += sz;
    }
    self[0x28 / 4] = self[0x28 / 4] + n;
}

extern char D_00550EC0[];

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
        void *buf = skipBuf;
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

void iosCdvdUnifileInfoGet(void)
{
    *(long long *)unifileHandle &= ~1LL;
    *(CdvdName16 *)(unifileHandle + 0x38) = D_00550EE8;
    *(int (**)())(unifileHandle + 0x1C) = unifile_read_func;
    iosCdvdMgrLoad(unifileHandle);
}

extern unsigned char CdvdMsgQ[];
extern int CdvdMsgQ_LoadEnd[];
extern int IosSndLock;
extern int D_0063A3B8;
extern char D_00550F10[];
extern void sceFsReset(void);
/* kept local: this TU does not include thread.h, whose iosThreadStart and
   iosThreadCreate take the thread record as an int and a void pointer */
extern void iosThreadCreate(char *th, int prio, void *entry, int arg, char *stack, int stacksize,
                            int a6);
extern void iosThreadStart(char *th);
extern void iosCdvdBackGroundMgrInit(void);
extern void SignalSema(int sema);

/* cdvd.c:1665-1724 in the listing, with iosCdvdDiskReadyBlock (rows
   701-708) expanded in case 0.  The frame is the ROM's: the inlined block's
   fp and file at sp+0 and sp+0x30 (its frame is taken when case 0 is
   expanded), the reply buffer at sp+0x50, msg at sp+0x8210 (an address-taken
   local gets its slot last).  The buffer's block opens after the switch: a
   block's locals take their slot when the block is entered, so declared at
   the top the buffer takes sp+0 and every later slot moves (measured, 87
   words).  Its size is what puts msg at 0x8210.  What the bytes cannot pin:
   the buffer's type and name, or what the developers kept in it (the
   LoadEnd receivers never read the value).  req is the request the switch
   dispatches on, held across case 0's calls; the default arm reads msg
   again, which is the ROM's reload. */
void iosCdvdManager(void)
{
    int *msg;
    int *req;

    sceCdInit(0);
    sceCdMmode(D_0063A370);
    sceFsReset();

    iosThreadCreate(stThread, 6, iosCdvdStManager, 0, stStack, 16384, 27);
    iosThreadStart(stThread);

    iosCdvdBackGroundMgrInit();

    iosMsgQueueCreate(CdvdMsgQ, cdvdMsgRing, 2);
    iosMsgQueueCreate(CdvdMsgQ_LoadEnd, cdvdLoadEndRing, 2);

    iosCdvdUnifileInfoGet();

    SignalSema(IosSndLock);

    while (1) {
        while (iosMsgRecv(CdvdMsgQ, &msg, 0) == -1) {
            D_0063A3B8 = 1;
            iosCdvdBackGroundMgr();
            D_0063A3B8 = 0;
            D_0063A368 = 1;
            iosThreadSleep();
            D_0063A368 = 0;
        }
        req = msg;
        switch (req[1]) {
        case 0:
            diskReadyBlockInlined();
            req[3] = 0;
            break;
        case 1:
            iosCdvdMgrLoad((char *)req);
            break;
        case 2:
            iosCdvdMgrPackLoad((char *)req);
            break;
        default:
            debug_StdPrintfDummy(D_00550F10, msg[1]);
            break;
        }
        {
            char reply[33216];
            iosMsgSend(CdvdMsgQ_LoadEnd, reply, 0);
        }
    }
}

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

extern char D_0063A398[];
extern void debug_assert();
extern char *strrchr(const char *s, int c);

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
        if (bgReqTable[i * 0x12C] == 0)
            goto found;
    }
    for (i = 0; i < 7; i++) {
        /* the January-2002 listing prints the whole table here; the retail
         * build compiles the printf out and leaves the empty countdown */
    }
    debug_assert(D_00550C58, 1890);
    __assert(D_00550C58, 1890, D_0063A398);
found:
    bg = bgReqTable + i * 0x12C;
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

extern int D_0063A384;
extern int D_0063A3C8;
extern int D_0063A3CC;
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
        self = (char *)bgRunning;
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

extern int iosSifAllocIopHeapDebug(int size, char *file, int line);
extern void sceCdStInit(int bufmax, int bansu, void *buf);
extern void sceCdStStart(int lsn, void *mode);

void iosCdvdDirectStOpen(char *self)
{
    char buf[256];
    char *name;
    int mem;

    name = strrchr(self + 0x38, '/');
    if (name == 0) {
        name = self + 0x38;
    } else {
        name = name + 1;
    }
    sprintf(buf, D_00550ED8, name);
    strcpy(self + 0x38, buf);
    chgFileNameInlined((int)(self + 0x38));
    *(char *)(self + 0x15C) = 0;
    *(char *)(self + 0x15D) = 0;
    *(char *)(self + 0x15E) = 0;
    *(int *)(self + 0x28) = 0;
    diskReadyBlockInlined();
    *(int *)(self + 0xC) = 0;
    iosCdvdMgrSearchFile(self);
    *(int *)(self + 0x30) = ((unsigned int)(*(int *)(self + 0x13C) - 1) >> 11) + 1;
    mem = iosSifAllocIopHeapDebug(576 * 2048 + 16, D_00550C58, 2472);
    *(int *)(self + 0x164) = mem;
    *(int *)(self + 0x168) = (mem + 15) & 0xFFFFFFF0;
    sceCdStInit(576, 36, (void *)((mem + 15) & 0xFFFFFFF0));
    sceCdStStart(*(int *)(self + 0x138), self + 0x15C);
    *(int *)(self + 0x8180) = *(int *)(self + 0x13C);
}

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

/* Listing rows 953-967: the first character load sits on the sprintf row and
 * the loop carries the next character in a register (gcse PRE of `*p` across
 * the back edge, the copy in the bnez delay slot), so the loop reads `*p`
 * directly.  WHAT THE BYTES PIN: this body is the same with `*p` read three
 * times; the inlined copy in iosCdvdMgrPackLoad is not, since three more
 * pseudos move two of that function's gcse pseudos across a hash bucket and
 * swap their spill slots (268/272), which the one `c` the test assigns and
 * toupper reads removes.  WHAT THEY CANNOT PIN: whether `c` was declared
 * here or at the test's line.  */
int iosCdvdChgFileName(int a0)
{
    char buf[256];
    char *p = buf;
    char c;

    sprintf(buf, D_0063A3A0, a0);

    do {
        if ((c = *p) == '/') {
            *p = '\\';
        } else {
            *p = toupper(c);
        }
        p++;
    } while (*p != 0);
    return strcpy(a0, buf);
}

extern int strcmp();
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

int iosCdvdBackGroundMgrDeleteRequestGet(void)
{
    char *p = bgReqTable;
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
    char *p = bgReqTable;
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

int iosCdvdBackGroundMgrGetRunning(void)
{
    return bgRunning;
}

extern char D_00550FD8[];
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

void iosCdvdBackGroundMgrInit(void)
{
    char *p = bgReqTable;
    int i;
    p += 0x708;
    for (i = 6; i >= 0; i--) {
        *p = 0;
        p -= 0x12C;
    }
    bgRunning = 0;
}

typedef int (*BgFunc)(char *self, int arg);

void iosCdvdBackGroundMgr(void)
{
    char *bg = bgReqTable;
    int i;
    unsigned int flag;
    BgFunc func;

    for (i = 6; i >= 0; i--, bg += 0x12C) {
        if (*bg == 0 || ((flag = *(unsigned int *)(bg + 0x108)) & 1) != 0)
            continue;
        bgRunning = (int)bg;
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
        bgRunning = 0;
    }
}

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
