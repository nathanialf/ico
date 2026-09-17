#include "common.h"
#include "debug.h"
#include "s_init.h"

typedef union {
    long long ll;

    struct {
        int lo, hi;
    } w;
} McHdr;

typedef union {
    long long ll;

    struct {
        int lo, hi;
    } w;
} McTestVal;

#include "mcard.h"
#include <eekernel.h>
#include <libmc.h>
#include <stdlib.h>
#include <stdio.h>
#include "message.h"
#include "typedef.h"

extern int D_006BC8C0[];
extern char D_0063A490[];
extern int D_0063A47C;
extern int D_0063A488;

inline void iosMcMgrSync(void *mp)
{
    D_006BC8C0[4] = 1;
    D_006BC8C0[2] = 0;
    D_006BC8C0[1] = 1;
    D_0063A47C = CreateSema(D_006BC8C0);
    debug_StdPrintfDummy(D_0063A490, D_0063A47C);
    do {
        WaitSema(D_0063A47C);
        D_0063A488++;
    } while (sceMcSync(1, (int *)((char *)mp + 0x30), (int *)((char *)mp + 0x10)) == 0);
    DeleteSema(D_0063A47C);
    D_0063A47C = -1;
}

inline void iosMcTest(void) {}

inline int iosMcSync(unsigned long *a0)
{
    unsigned long x = *a0;
    char y = x;
    unsigned long z = y & 1ul;
    y = z;
    return -((int)y);
}

extern char D_0029B9E8[];

inline int iosMcGetInfo(void *a0)
{
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 0;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcFormat(void *a0)
{
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 3;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcUnformat(void *a0)
{
    McTestVal *v = (McTestVal *)a0;
    v->w.hi = 4;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcGetDir(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 6;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcDelete(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 2;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcSaveIconBlock(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 7;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcSaveProductBlock(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 8;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcLoadProductBlock(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 9;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcSaveGameBlock(void *a0, int a1)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xA;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcLoadGameBlock(void *a0, int a1)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xB;
    *(int *)((char *)a0 + 0x48) = a1;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcChdirProduct(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xC;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

inline int iosMcGetBlockSaveInfo(void *a0)
{
    McHdr *v = (McHdr *)a0;
    v->w.hi = 0xD;
    v->ll = v->ll & -2;
    return iosMsgSend(D_0029B9E8, a0, 0);
}

typedef struct {
    char b[0x40];
} McBlk;

typedef struct {
    char unk0[0x190];
    int soundMode;
    int outputMode;
    int unk198;
    int gobj;
    char blk[0x40];
    char unk1E0[8];
    int cameraMove;
    int unk1EC;
} McSaveRec;

/* defined below, at their ROM slots; the 2001 source called them from here
   without a prototype, so they keep the non-prototype form. */
extern McSaveRec D_0029B5F0[];
extern char D_0029BC00[];
extern int D_0063A538;
extern int CurrentTargetGObj;
extern int D_0028F4C0[];
extern int NonLinearCameraMove;

inline int product_write(int *self)
{
    (D_0029B5F0 + self[2])->soundMode = D_0028F4C0[11];
    (D_0029B5F0 + self[2])->outputMode = soundOutputModeGet();
    (D_0029B5F0 + self[2])->unk198 = D_0063A538;
    (D_0029B5F0 + self[2])->gobj = CurrentTargetGObj;
    (D_0029B5F0 + self[2])->cameraMove = NonLinearCameraMove;
    (D_0029B5F0 + self[2])->unk1EC = D_0028F4C0[0];
    *(McBlk *)(D_0029B5F0 + self[2])->blk = *(McBlk *)D_0029BC00;
    iosMcHandlerWrite((int)self, (int)(D_0029B5F0 + self[2]), 0x1F0);
    return 0;
}

inline int product_read(int *self)
{
    int idx = self[0x8 / 4];
    iosMcHandlerRead((int)self, (int)&D_0029B5F0[idx], 0x1F0);
    return self[0x10 / 4];
}

extern int CurrentTargetGObjSub;
extern int D_00639EA0;

inline int gameblock_write(int self, void *buf)
{
    iosMcHandlerWrite(self, buf, 0x63F4);
    iosMcHandlerWrite(self, &CurrentTargetGObjSub, 4);
    iosMcHandlerWrite(self, &D_00639EA0, 4);
    return 0;
}

extern int D_0028F4EC[];

inline int gameblock_read(int *self, void *buf)
{
    iosMcHandlerRead((int)self, (int)buf, 0x63F4);
    D_0028F4EC[0] = (D_0029B5F0 + self[2])->soundMode;
    soundOutputModeSet((D_0029B5F0 + self[2])->outputMode);
    D_0063A538 = (D_0029B5F0 + self[2])->unk198;
    CurrentTargetGObj = (D_0029B5F0 + self[2])->gobj;
    *(McBlk *)D_0029BC00 = *(McBlk *)(D_0029B5F0 + self[2])->blk;
    iosMcHandlerRead((int)self, (int)&CurrentTargetGObjSub, 4);
    iosMcHandlerRead((int)self, (int)&D_00639EA0, 4);
    return self[4];
}

/* one sceMcTblGetDir record: the file name sits at +0x20 in a 0x40-byte entry
   (the same record src/debug.c spells as McDirEnt). */

typedef struct {
    long long f0;             /* 0x00 -- the iosMc command/flag word, 64-bit */
    int port;                 /* 0x08 */
    int slot;                 /* 0x0C */
    int f10;                  /* 0x10 */
    int f14;                  /* 0x14 */
    int f18;                  /* 0x18 */
    int f1C;                  /* 0x1C */
    int f20;                  /* 0x20 */
    int f24;                  /* 0x24 */
    int fd;                   /* 0x28 */
    int f2C;                  /* 0x2C */
    int f30;                  /* 0x30 */
    int size;                 /* 0x34 */
    int pos;                  /* 0x38 */
    int end;                  /* 0x3C */
    int f40;                  /* 0x40 */
    int f44;                  /* 0x44 -- entries filled in by sceMcGetDir */
    int f48;                  /* 0x48 */
    int sum;                  /* 0x4C */
    int f50;                  /* 0x50 */
    unsigned char buf[0x400]; /* 0x54 -- the one-sector staging cache */
    char name454[0x14];       /* 0x454 */
    char pwd468[0x14];        /* 0x468 */
    char name47C[0x44];       /* 0x47C */
    McDirEnt dir[20];         /* 0x4C0 */
    long long mask;           /* 0x9C0 */
} McMgr;

/* the product directory name, 17 bytes including the terminator: the ROM
   copies it with ldl/ldr + sdl/sdr, so both sides are byte-aligned. */
typedef struct {
    char c[17];
} McName;

extern char D_005511E8[];
extern char D_00551248[];
extern char D_00551268[];
extern char D_00551288[];
extern char D_005512C8[];
extern char D_00551328[];
extern char D_005511C8[];
extern char D_00551208[];
extern char D_00551228[];

/* ios/mcard.c:427-431, 494-495, 512-519, 537-538 and 571-578 in the
   January-2002 listing: the file-static card helpers the manager entry points
   inline. None of them has a ROM symbol of its own. */
static inline void iosMcMgrRead(McMgr *mp, void *p)
{
    while (sceMcRead(mp->fd, p, mp->size) > 0) {
        debug_StdPrintfDummy(D_005511E8);
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrWrite(McMgr *mp, void *p)
{
    while (sceMcWrite(mp->fd, p, mp->size) > 0) {
        debug_StdPrintfDummy(D_005511C8);
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrOpen(McMgr *mp)
{
    while (sceMcOpen(mp->port, mp->slot, mp->name47C, mp->f2C) > 0) {
        debug_StdPrintfDummy(D_00551208);
    }

    iosMcMgrSync(mp);

    if (mp->f10 < 0) {
        return;
    }

    mp->fd = mp->f10;
    mp->sum = 0;
    mp->end = 0;
    mp->pos = 0;
}

static inline void iosMcMgrClose(McMgr *mp)
{
    while (sceMcClose(mp->fd) > 0) {
        debug_StdPrintfDummy(D_00551228);
    }

    iosMcMgrSync(mp);
}

extern char D_00551188[];
extern char D_005511A8[];
extern char D_005512A8[];

static inline void iosMcMgrFormat(McMgr *mp)
{
    while (sceMcFormat(mp->port, mp->slot) > 0) {
        debug_StdPrintfDummy(D_00551188);
    }

    iosMcMgrSync(mp);

    if (mp->f10 == 0) {
        mp->f1C = -1;
    }
}

static inline void iosMcMgrUnformat(McMgr *mp)
{
    while (sceMcUnformat(mp->port, mp->slot) > 0) {
        debug_StdPrintfDummy(D_005511A8);
    }

    iosMcMgrSync(mp);

    if (mp->f10 == 0) {
        mp->f1C = -2;
    }
}

static inline void iosMcMgrDelete(McMgr *mp)
{
    while (sceMcDelete(mp->port, mp->slot, mp->name47C) > 0) {
        debug_StdPrintfDummy(D_005512A8);
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrChdir(McMgr *mp)
{
    while (sceMcChdir(mp->port, mp->slot, mp->name454, mp->pwd468) > 0) {
        debug_StdPrintfDummy(D_00551248);
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrGetDir(McMgr *mp)
{
    while (sceMcGetDir(mp->port, mp->slot, mp->name47C, 0, 20, mp->dir) > 0) {
        debug_StdPrintfDummy(D_00551268);
    }

    iosMcMgrSync(mp);

    if (mp->f10 < 0) {
        mp->f44 = 0;
    } else {
        mp->f44 = mp->f10;
    }
}

static inline void iosMcMgrMkdir(McMgr *mp)
{
    while (sceMcMkdir(mp->port, mp->slot, mp->name47C) > 0) {
        debug_StdPrintfDummy(D_00551288);
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrSum(McMgr *mp, void *q, int n)
{
    unsigned char *p = q;
    int i;

    for (i = 0; i < n; i++) {
        mp->sum += p[i];
    }
}

extern char D_00551140[];
extern char D_00551168[];

void iosMcMgrGetInfo(McMgr *mp)
{
    int r;

    while ((r = sceMcGetInfo(mp->port, mp->slot, &mp->f14, &mp->f18, &mp->f20)) != 0) {
        debug_StdPrintfDummy(D_00551140, r);
    }

    iosMcMgrSync(mp);

    debug_StdPrintfDummy(D_00551168, mp->f10, mp->f14);

    if (mp->f10 != 0 && mp->f10 >= -10) {
        mp->f1C = mp->f10;
    }
}

extern void *memcpy(void *dst, void *src, int n);

int iosMcHandlerWrite(McMgr *mp, unsigned char *buf, int len)
{
    int n;
    int m;

    if (len > 1024) {
        if (mp->pos != 0) {
            mp->size = mp->pos;
            iosMcMgrWrite(mp, mp->buf);

            if (mp->f10 < 0) {
                return;
            }

            mp->pos = 0;
        }

        mp->size = len;
        iosMcMgrWrite(mp, buf);
        iosMcMgrSum(mp, buf, mp->size);

        if (mp->f10 < 0) {
            return;
        }

        len = 0;
    }

    while (len > 0) {
        n = 1024 - mp->pos;

        if (len < n) {
            m = len;
        } else {
            m = n;
        }

        memcpy((unsigned char *)(mp->pos + (int)mp + 0x54), buf, m);
        iosMcMgrSum(mp, (unsigned char *)(mp->pos + (int)mp + 0x54), m);

        buf += m;
        mp->pos += m;
        n -= m;

        if (n == 0) {
            mp->size = 1024;
            iosMcMgrWrite(mp, mp->buf);

            if (mp->f10 < 0) {
                return;
            }

            mp->pos = 0;
        }

        len -= m;
    }

    sceMcFlush(mp->fd);
    iosMcMgrSync(mp);
}

int iosMcHandlerRead(McMgr *mp, unsigned char *buf, int len)
{
    int n;

    if (len > 1024) {
        if (mp->pos != 0) {
            n = mp->end - mp->pos;
            memcpy(buf, (unsigned char *)(mp->pos + (int)mp + 0x54), n);
            iosMcMgrSum(mp, (unsigned char *)(mp->pos + (int)mp + 0x54), n);
            buf += n;
            len -= n;
        }

        mp->size = len;
        iosMcMgrRead(mp, buf);
        iosMcMgrSum(mp, buf, len);

        if (mp->f10 < 0) {
            return;
        }

        mp->end = 0;
        mp->pos = 0;
        len = 0;
    }

    while (len > 0) {
        debug_StdPrintfDummy(D_0063A490, len);

        if (mp->pos == 0) {
            mp->size = 1024;
            iosMcMgrRead(mp, mp->buf);

            if (mp->f10 < 0) {
                return;
            }

            if ((mp->end = mp->f10) == 0) {
                debug_StdPrintfDummy(D_005512C8, mp->pos, len);
                mp->f10 = -15;
                return;
            }
        }

        n = mp->end - mp->pos;

        if (n > len) {
            n = len;
        }

        memcpy(buf, (unsigned char *)(mp->pos + (int)mp + 0x54), n);
        iosMcMgrSum(mp, (unsigned char *)(mp->pos + (int)mp + 0x54), n);

        len -= n;
        mp->pos += n;
        buf += n;

        if (mp->pos >= mp->end) {
            mp->end = 0;
            mp->pos = 0;
        }
    }
}

void iosMcMgrChdirProduct(McMgr *mp)
{
    int r;

retry:
    iosMcMgrGetInfo(mp);

    switch (mp->f10) {
    case 0:
    case -1:
        r = 0;
        break;
    case -2:
        r = mp->f1C;
        break;
    default:
        r = -9;
        break;
    }

    if (r != 0) {
        mp->f10 = r;
        return;
    }

    if (mp->f0 & 2) {
        *(McName *)mp->name47C = *(McName *)D_00551328;
        iosMcMgrMkdir(mp);
        if (mp->f10 != 0 && mp->f10 != -4) {
            return;
        }
    }

    *(McName *)mp->name454 = *(McName *)D_00551328;
    iosMcMgrChdir(mp);

    if (mp->f10 != 0) {
        if (mp->f10 == -4) {
            mp->f10 = -14;
        }
    }

    if (mp->f10 != 0 && mp->f10 != -4 && mp->f10 != -14 && mp->f10 != -2) {
        goto retry;
    }
}

extern char D_00551358[];
extern char D_00551368[];
extern char *D_0029B590[];
extern void strcpy(char *dst, char *src);
extern void strcat(char *dst, char *src);

/* the per-slot segment table: one record per loadable block */
typedef struct {
    int id;                    /* 0x0 */
    int (*load)(McMgr *, int); /* 0x4 */
    int (*save)(McMgr *, int); /* 0x8 */
} McSegEnt;

extern McSegEnt D_0029B5A8[6];
extern char D_00551340[];

void iosMcMgrSaveSeg(McMgr *mp, char *suffix)
{
    int r = 0;
    unsigned int i;
    McSegEnt *e;

    mp->f0 = mp->f0 | 2;
    iosMcMgrChdirProduct(mp);

    if (mp->f10 != 0) {
        return;
    }

    mp->f2C = 0x203;
    strcpy(mp->name47C, D_0029B590[mp->f24]);

    if (suffix != 0) {
        strcat(mp->name47C, suffix);
    }

    iosMcMgrOpen(mp);

    if (mp->f10 < 0) {
        return;
    }

    for (i = 0; i < 6; i++) {
        e = &D_0029B5A8[i];
        if (e->id != mp->f24) {
            continue;
        }
        if (e->save == 0) {
            continue;
        }
        if (e->save(mp, mp->f48) < 0) {
            r = -15;
            break;
        }
    }

    if (r == 0) {
        if (mp->pos != 0) {
            mp->size = mp->pos;
            iosMcMgrWrite(mp, mp->buf);

            if (mp->f10 < 0) {
                return;
            }

            mp->pos = 0;
        }

        if (mp->f24 < 5) {
            if (mp->f24 > 0) {
                goto flush;
            }
        }

        mp->size = 4;
        debug_StdPrintfDummy(D_00551340, mp->sum);
        iosMcMgrWrite(mp, &mp->sum);
    }

flush:
    sceMcFlush(mp->fd);
    iosMcMgrSync(mp);

    iosMcMgrClose(mp);

    if (r != 0) {
        mp->f10 = r;
    }
}

void iosMcMgrLoadSeg(McMgr *mp, char *suffix)
{
    int r = 0;
    unsigned int i;
    McSegEnt *e;

    mp->f0 = mp->f0 & -3;
    iosMcMgrChdirProduct(mp);

    if (mp->f10 != 0) {
        return;
    }

    mp->f2C = 1;
    strcpy(mp->name47C, D_0029B590[mp->f24]);

    if (suffix != 0) {
        strcat(mp->name47C, suffix);
    }

    iosMcMgrOpen(mp);

    if (mp->f10 < 0) {
        return;
    }

    for (i = 0; i < 6; i++) {
        e = &D_0029B5A8[i];
        if (e->id != mp->f24) {
            continue;
        }
        if (e->load == 0) {
            continue;
        }
        debug_StdPrintfDummy(D_00551358);
        if (e->load(mp, mp->f48) < 0) {
            r = -15;
            break;
        }
    }

    if (r == 0) {
        while (sceMcSeek(mp->fd, -4, 2) > 0) {
            debug_StdPrintfDummy(D_00551368);
        }

        iosMcMgrSync(mp);

        mp->size = 4;
        iosMcMgrRead(mp, &mp->f50);

        if (mp->f10 < 0) {
            return;
        }

        if (mp->sum != mp->f50) {
            r = -16;
        }
    }

    iosMcMgrClose(mp);

    if (r != 0) {
        mp->f10 = r;
    }
}

void iosMcMgrSaveProductBlock(void *a0)
{
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrSaveSeg(a0, 0);
}

void iosMcMgrLoadProductBlock(void *a0)
{
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrLoadSeg(a0, 0);
}

extern char D_0063A4A0[];
extern int strlen(char *s);

void iosMcMgrGetBlockSaveInfo(McMgr *mp)
{
    int i;

    mp->mask = 0;
    mp->f0 = mp->f0 & -3;
    mp->f44 = 0;

    iosMcMgrChdirProduct(mp);

    if (mp->f10 == -14) {
        mp->f10 = 0;
        return;
    }

    if (mp->f10 < 0) {
        return;
    }

    strcat(mp->name47C, D_0063A4A0);

    iosMcMgrGetDir(mp);

    if (mp->f10 < 0) {
        return;
    }

    for (i = 0; i < mp->f44; i++) {
        mp->mask |= 1 << atoi(&mp->dir[i].name[strlen(mp->dir[i].name) - 3]);
    }
}

extern char D_00551388[];
extern char D_00551398[];
extern char D_005513A8[];
extern char D_005513B8[];
extern char D_005513D0[];
extern char D_005513E0[];
extern char D_005513F0[];
extern char D_00551400[];
extern char D_0055F70C[];
extern char D_0063A490[];
extern char D_0063A4A8[];
extern char D_0063A4B0[];
extern char D_0063A4B8[];
extern char D_0063A4C0[];
extern char D_0063A4C8[];
extern char D_0063A4D0[];
extern int D_006BC8D8[];

/* ios/mcard.c:1042-1053, 1109-1115 and 1127-1133: the three file-static block
   helpers the manager dispatch inlines. None has a ROM symbol of its own. */
static inline void iosMcMgrSaveIcon(McMgr *mp)
{
    char buf[16];

    mp->f24 = 1;
    mp->f48 = (int)D_0055F70C;
    iosMcMgrSaveSeg(mp, 0);

    if (mp->f10 < 0) {
        return;
    }

    mp->f24 = 2;
    mp->f48 = (int)D_0055F70C + 0x24;
    iosMcMgrSaveSeg(mp, 0);
}

static inline void iosMcMgrSaveGame(McMgr *mp)
{
    char buf[16];

    sprintf(buf, &D_0063A490[8], mp->f40);
    mp->f24 = 5;
    iosMcMgrSaveSeg(mp, buf);
}

static inline void iosMcMgrLoadGame(McMgr *mp)
{
    char buf[16];

    sprintf(buf, &D_0063A490[8], mp->f40);
    mp->f24 = 5;
    iosMcMgrLoadSeg(mp, buf);
}

void iosMcManager(void)
{
    McMgr *mp;
    McMgr **pp;

    sceMcInit();
    iosMsgQueueCreate(D_0029B9E8, D_006BC8D8, 16);
    pp = &mp;

    for (;;) {
        iosMsgRecv(D_0029B9E8, pp, 1);
        debug_StdPrintfDummy(D_00551388, mp);

        mp->f0 = mp->f0 & -2;
        debug_StdPrintfDummy(D_0063A4A8);

        switch (*(int *)((char *)mp + 4)) {
        case 0:
            iosMcMgrGetInfo(mp);
            break;

        case 3:
            debug_StdPrintfDummy(D_0063A4B0);
            iosMcMgrFormat(mp);
            break;

        case 4:
            debug_StdPrintfDummy(D_00551398);
            iosMcMgrUnformat(mp);
            break;

        case 5:
            debug_StdPrintfDummy(D_0063A4B8);
            iosMcMgrChdir(mp);
            break;

        case 6:
            debug_StdPrintfDummy(D_0063A4C0);
            iosMcMgrGetDir(mp);
            break;

        case 2:
            debug_StdPrintfDummy(D_0063A4C8);
            iosMcMgrDelete(mp);
            break;

        case 7:
            debug_StdPrintfDummy(D_005513A8);
            iosMcMgrSaveIcon(mp);
            break;

        case 8:
            debug_StdPrintfDummy(D_005513B8);
            iosMcMgrSaveProductBlock(mp);
            break;

        case 9:
            iosMcMgrLoadProductBlock(mp);
            break;

        case 10:
            debug_StdPrintfDummy(D_005513D0);
            iosMcMgrSaveGame(mp);
            break;

        case 11:
            debug_StdPrintfDummy(D_005513E0);
            iosMcMgrLoadGame(mp);
            break;

        case 12:
            debug_StdPrintfDummy(D_005513F0);
            iosMcMgrChdirProduct(mp);
            break;

        case 13:
            iosMcMgrGetBlockSaveInfo(mp);
            break;

        case 14:
            debug_StdPrintfDummy(D_0063A4D0);
            iosMcMgrMkdir(mp);
            break;

        default:
            debug_StdPrintfDummy(D_00551400, *(int *)((char *)mp + 4));
            break;
        }

        mp->f0 = mp->f0 | 1;
    }
}
