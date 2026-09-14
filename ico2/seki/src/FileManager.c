#include "common.h"
#include "ico/types.h"

extern char D_0054DB30[];
extern char D_0054DB60[];
extern char D_0054DB78[];
extern char D_0054DB90[];
extern char D_0054DBA8[];
extern char D_0054DBC0[];
extern char D_0054DBD8[];
extern char D_0054DBF0[];
extern char D_0054DC08[];
extern char D_0054DC20[];
extern char D_0054DC38[];
extern char D_00639F48[];
extern int D_0063A370;
extern void debug_StdPrintfDummy(const char *fmt, ...);
extern int sceSifInitRpc(int mode);
extern int sceCdInit(int mode);
extern int sceCdMmode(int media);
extern int sceCdDiskReady(int mode);
extern int sceCdStatus(void);
extern int sceSifRebootIop(const char *img);
extern int sceSifSyncIop(void);
extern void sceSifLoadFileReset(void);
extern int sceFsReset(void);
extern int sceSifLoadModule(const char *name, int argc, const char *argv);

typedef struct sceCdlFILE {
    unsigned int lsn;
    unsigned int size;
    char name[32];
    unsigned char date[8];
} sceCdlFILE;

typedef struct sceCdRMode {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} sceCdRMode;

/* ios memory partition; field 0x38 is the partition's base address, which the
   per-area "(%2.1f%%)" prints subtract from the end of the new block. */
typedef struct IosPartition {
    unsigned char unk_00[0x38];
    char *base;
} IosPartition;

extern unsigned char D_00637E69[];
extern char D_00639F50[];
extern char D_00639F58[];
extern char D_0054DC50[];
extern char D_0054DC90[];
extern char D_0054DCC0[];
extern char D_0054DCD8[];
extern char D_0054DCF8[];
extern char D_0054DD20[];
extern char D_0054DD50[];
extern char D_0054DD80[];
extern char D_0054DDA0[];
extern char D_0054DDC0[];
extern char D_0054DDD8[];
extern char D_0054DDF0[];
extern char D_0054DE08[];
extern char D_0054DE30[];
extern char D_0054DE58[];
extern char D_0054DE78[];
extern char D_0054DE98[];
extern char D_0054DEC8[];
extern char D_0054DEF8[];
extern char D_0054DF18[];
extern char D_0054DF38[];
extern char D_0054DF60[];
extern char D_0054DF78[];
extern char D_0054DF98[];
extern IosPartition *D_0063A434;
extern IosPartition *D_0063A438;
extern IosPartition *D_0063A440;
extern IosPartition *D_0063A444;
extern IosPartition *D_0063A44C;
extern IosPartition *D_0063A450;
extern IosPartition *D_0063A454;
extern IosPartition *D_0063A458;
extern IosPartition *D_0063A45C;
extern char *strcat(char *dst, const char *src);
extern int sceCdSearchFile(sceCdlFILE *fp, const char *name);
extern int sceCdRead(unsigned int lsn, unsigned int sectors, void *buf, sceCdRMode *mode);
extern int sceCdSync(int mode);
extern int sceCdGetError(void);
extern void FlushCache(int mode);
extern void *iosMallocDebug(IosPartition *part, int size, char *file, int line);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

/* SRCFILE puts this pair on seki/src/FileManager.c:184-185, above file_Init's
   def line 236, and inlines it at all seven wait sites. */
static inline void file_WaitDisc(void)
{
    sceCdDiskReady(0);
    while (sceCdStatus() != 10)
        ;
}

void file_Init(void)
{
    debug_StdPrintfDummy(D_0054DB30);
    debug_StdPrintfDummy(D_0054DB60);
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(D_0063A370);
    debug_StdPrintfDummy(D_00639F48);
    debug_StdPrintfDummy(D_0054DB78);
    do
        file_WaitDisc();
    while (sceSifRebootIop(D_0054DB90) == 0);
    while (sceSifSyncIop() == 0)
        ;
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    sceCdInit(0);
    sceCdMmode(D_0063A370);
    debug_StdPrintfDummy(D_00639F48);
    debug_StdPrintfDummy(D_0054DBA8);
    do
        file_WaitDisc();
    while (sceSifLoadModule(D_0054DBC0, 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule(D_0054DBD8, 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule(D_0054DBF0, 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule(D_0054DC08, 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule(D_0054DC20, 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule(D_0054DC38, 0, 0) < 0);
    debug_StdPrintfDummy(D_00639F48);
}

/* BSD <ctype.h> table: D_00637E69 is `_ctype_ + 1`, bit 0x02 is _L (lower). */
#define _L 0x02
#define islower(c) (D_00637E69[(int)(c)] & _L)

int file_LoadCDFile(void **adr, char *fname, int area)
{
    char path[256];
    sceCdlFILE fp;
    sceCdRMode mode;
    char *d;
    char *s;
    int c;
    int t;
    int size;
    int asize;
    int sec;
    int err;

    /* SRCFILE puts this printf on seki/src/FileManager.c:322, i.e. INSIDE
       file_LoadCDFile's span but above its first body line (326): a nested
       helper the dev calls from every switch arm.  Capturing fname/adr/size
       is what forces all three into their stack homes. */
    inline void PrintLoad(void)
    {
        debug_StdPrintfDummy(D_0054DC50, fname, *adr, size);
    }

    path[0] = '\\';
    d = &path[1];
    s = fname;
    do {
        c = *s;
        if (c == '/') {
            *d = '\\';
            d++;
            continue;
        }
        t = c - 'a' + 'A';
        if (!islower(c))
            t = c;
        *d = t;
        d++;
    } while (*s++ != 0);
    strcat(path, D_00639F50);

    while (sceCdDiskReady(0) == 6)
        ;
    if (sceCdSearchFile(&fp, path) == 0) {
        debug_StdPrintfDummy(D_0054DC90, fname);
        debug_StdPrintfDummy(D_0054DC90, path);
        return -1;
    }

    size = fp.size;
    asize = (size / 2048 + 1) * 2048;

    switch (area) {
    default:
    case 0:
    case 2:
    case 4:
        *adr = iosMallocDebug(D_0063A44C, asize, D_0054DCC0, 349);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DCD8,
                             ((int)*adr + asize - (int)D_0063A44C->base) * 100.0f / 10059776.0f);
        break;
    case 1:
        *adr = iosMallocDebug(D_0063A438, asize, D_0054DCC0, 357);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DCF8, asize * 100.0f / 524288.0f,
                             ((int)*adr + asize - (int)D_0063A438->base) * 100.0f / 524288.0f);
        break;
    case 3:
        *adr = iosMallocDebug(D_0063A444, asize, D_0054DCC0, 366);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DD20, asize * 100.0f / 1179648.0f,
                             ((int)*adr + asize - (int)D_0063A444->base) * 100.0f / 1179648.0f);
        break;
    case 5:
        *adr = iosMallocDebug(D_0063A440, asize, D_0054DCC0, 375);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DD50, asize * 100.0f / 3670016.0f,
                             ((int)*adr + asize - (int)D_0063A440->base) * 100.0f / 3670016.0f);
        break;
    case 6:
        *adr = iosMallocDebug(D_0063A434, asize, D_0054DCC0, 384);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DD80, ((int)*adr + asize - (int)D_0063A434->base) * 100.0f);
        break;
    case 7:
        *adr = iosMallocDebug(D_0063A450, asize, D_0054DCC0, 392);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DDA0,
                             ((int)*adr + asize - (int)D_0063A450->base) * 100.0f / 327680.0f);
        break;
    case 8:
        *adr = iosMallocDebug(D_0063A454, asize, D_0054DCC0, 400);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DDC0);
        break;
    case 9:
        *adr = iosMallocDebug(D_0063A458, asize, D_0054DCC0, 405);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DDD8);
        break;
    case 10:
        *adr = iosMallocDebug(D_0063A45C, asize, D_0054DCC0, 410);
        PrintLoad();
        debug_StdPrintfDummy(D_0054DDF0);
        break;
    }

    mode.trycount = 0;
    mode.spindlctrl = 1;
    mode.datapattern = 0;
    sec = (size - 1) / 2048 + 1;

    FlushCache(0);
    sceCdRead(fp.lsn, sec, *adr, &mode);
    while (sceCdSync(0))
        ;
    while (sceCdDiskReady(0) == 6)
        ;

    err = sceCdGetError();
    switch (err) {
    case 0x32:
        debug_StdPrintfDummy(D_0054DE08);
        break;
    case 0x31:
        debug_StdPrintfDummy(D_0054DE30);
        break;
    case 0x30:
        debug_StdPrintfDummy(D_0054DE58);
        break;
    case 0x14:
        debug_StdPrintfDummy(D_0054DE78);
        break;
    case 0x21:
        debug_StdPrintfDummy(D_0054DE98);
        break;
    case 0x20:
        debug_StdPrintfDummy(D_0054DEC8);
        break;
    case 0x13:
        debug_StdPrintfDummy(D_0054DEF8);
        break;
    case 0x12:
        debug_StdPrintfDummy(D_0054DF18);
        break;
    case 0x11:
        debug_StdPrintfDummy(D_0054DF38);
        break;
    case 0x10:
        debug_StdPrintfDummy(D_0054DF60);
    case 0x01:
        debug_StdPrintfDummy(D_0054DF78);
        break;
    case -1:
        debug_StdPrintfDummy(D_0054DF98);
    }

    if (err != 0) {
        debug_assert(D_0054DCC0, 440);
        __assert(D_0054DCC0, 440, D_00639F58);
    }
    return size;
}

int file_LoadFile(void **adr, char *fname, int area)
{
    return file_LoadCDFile(adr, fname, area);
}
