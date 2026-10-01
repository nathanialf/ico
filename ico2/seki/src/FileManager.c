#include "debug.h"
#include "cdvd.h"
#include "memory.h"
#include <string.h>
#include <ctype.h>
#include <eekernel.h>
#include "FileManager.h"
#include "debug_exception.h"
#include <libcdvd.h>
#include <assert.h>

/* kept local: agrees with sifrpc.h, which this TU does not include (sceSifLoadFileReset, sceSifLoadModule differ) */
extern void sceSifInitRpc(int mode);
/* kept local: agrees with sifrpc.h, which this TU does not include (sceSifLoadFileReset, sceSifLoadModule differ) */
extern int sceSifRebootIop(const char *img);
/* kept local: agrees with sifrpc.h, which this TU does not include (sceSifLoadFileReset, sceSifLoadModule differ) */
extern int sceSifSyncIop(void);
/* kept local: void (void) here, int (void) in sifrpc.h */
extern void sceSifLoadFileReset(void);
/* kept local: int (const char *, int, const char *) here, void (void *, int, int) in sifrpc.h */
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

/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_hara;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_sugipon;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_dmotion;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_smotion;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_seki;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_oomori;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_horagai;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_sound;
/* kept local: IosPartition * here, int in ios.h */
extern IosPartition *ios_partition_sound_semi;
extern int sceCdSearchFile(sceCdlFILE *fp, const char *name);

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
    debug_StdPrintfDummy("-------------------------------- read from CD\n");
    debug_StdPrintfDummy("initialize CD device.\n");
    sceSifInitRpc(0);
    sceCdInit(0);
    sceCdMmode(iosCdvdMediaType);
    debug_StdPrintfDummy("done.\n");
    debug_StdPrintfDummy("load default module.\n");
    do
        file_WaitDisc();
    while (sceSifRebootIop("cdrom0:\\IOPRP224.IMG;1") == 0);
    while (sceSifSyncIop() == 0)
        ;
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    sceCdInit(0);
    sceCdMmode(iosCdvdMediaType);
    debug_StdPrintfDummy("done.\n");
    debug_StdPrintfDummy("loading iop modules.\n");
    do
        file_WaitDisc();
    while (sceSifLoadModule("cdrom0:\\SIO2MAN.IRX;1", 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule("cdrom0:\\PADMAN.IRX;1", 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule("cdrom0:\\MCMAN.IRX;1", 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule("cdrom0:\\MCSERV.IRX;1", 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule("cdrom0:\\LIBSD.IRX;1", 0, 0) < 0);
    do
        file_WaitDisc();
    while (sceSifLoadModule("cdrom0:\\SNDN2DRV.IRX;1", 0, 0) < 0);
    debug_StdPrintfDummy("done.\n");
}

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
        debug_StdPrintfDummy(
            "loading:\"\033[33m%s\033[m\" (address:\033[35m%p\033[m/size:\033[35m%d\033[m)", fname,
            *adr, size);
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
    strcat(path, ";1");

    while (sceCdDiskReady(0) == 6)
        ;
    if (sceCdSearchFile(&fp, path) == 0) {
        debug_StdPrintfDummy("file_LoadCDFile:file is not exists? (%s)\n", fname);
        debug_StdPrintfDummy("file_LoadCDFile:file is not exists? (%s)\n", path);
        return -1;
    }

    size = fp.size;
    asize = (size / 2048 + 1) * 2048;

    switch (area) {
    default:
    case 0:
    case 2:
    case 4:
        *adr = iosMallocDebug(ios_partition_seki, asize, "src/FileManager.c", 349);
        PrintLoad();
        debug_StdPrintfDummy(" to seki area.(%2.1f%%)\n",
                             ((int)*adr + asize - (int)ios_partition_seki->base) * 100.0f /
                                 10059776.0f);
        break;
    case 1:
        *adr = iosMallocDebug(ios_partition_sugipon, asize, "src/FileManager.c", 357);
        PrintLoad();
        debug_StdPrintfDummy(" to sugi area.(%2.1f%%/%2.1f%%)\n", asize * 100.0f / 524288.0f,
                             ((int)*adr + asize - (int)ios_partition_sugipon->base) * 100.0f /
                                 524288.0f);
        break;
    case 3:
        *adr = iosMallocDebug(ios_partition_smotion, asize, "src/FileManager.c", 366);
        PrintLoad();
        debug_StdPrintfDummy(
            " to static motion area.(%2.1f%%/%2.1f%%)\n", asize * 100.0f / 1179648.0f,
            ((int)*adr + asize - (int)ios_partition_smotion->base) * 100.0f / 1179648.0f);
        break;
    case 5:
        *adr = iosMallocDebug(ios_partition_dmotion, asize, "src/FileManager.c", 375);
        PrintLoad();
        debug_StdPrintfDummy(
            " to dynamic motion area.(%2.1f%%/%2.1f%%)\n", asize * 100.0f / 3670016.0f,
            ((int)*adr + asize - (int)ios_partition_dmotion->base) * 100.0f / 3670016.0f);
        break;
    case 6:
        *adr = iosMallocDebug(ios_partition_hara, asize, "src/FileManager.c", 384);
        PrintLoad();
        debug_StdPrintfDummy(" to hara-area.(%2.1f%%)\n",
                             ((int)*adr + asize - (int)ios_partition_hara->base) * 100.0f);
        break;
    case 7:
        *adr = iosMallocDebug(ios_partition_oomori, asize, "src/FileManager.c", 392);
        PrintLoad();
        debug_StdPrintfDummy(" to oomori area.(%2.1f%%)\n",
                             ((int)*adr + asize - (int)ios_partition_oomori->base) * 100.0f /
                                 327680.0f);
        break;
    case 8:
        *adr = iosMallocDebug(ios_partition_horagai, asize, "src/FileManager.c", 400);
        PrintLoad();
        debug_StdPrintfDummy(" to horagai-area.\n");
        break;
    case 9:
        *adr = iosMallocDebug(ios_partition_sound, asize, "src/FileManager.c", 405);
        PrintLoad();
        debug_StdPrintfDummy(" to sound-area.\n");
        break;
    case 10:
        *adr = iosMallocDebug(ios_partition_sound_semi, asize, "src/FileManager.c", 410);
        PrintLoad();
        debug_StdPrintfDummy(" to sound_semi-area.\n");
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
        debug_StdPrintfDummy("file_LoadCDFile:Reach to CD end.\n");
        break;
    case 0x31:
        debug_StdPrintfDummy("file_LoadCDFile:Open tray at reading.\n");
        break;
    case 0x30:
        debug_StdPrintfDummy("file_LoadCDFile:Read error.\n");
        break;
    case 0x14:
        debug_StdPrintfDummy("file_LoadCDFile:Invalid Disc.\n");
        break;
    case 0x21:
        debug_StdPrintfDummy("file_LoadCDFile:Invalid transfer length.\n");
        break;
    case 0x20:
        debug_StdPrintfDummy("file_LoadCDFile:Invalid transfer address.\n");
        break;
    case 0x13:
        debug_StdPrintfDummy("file_LoadCDFile:Not ready.\n");
        break;
    case 0x12:
        debug_StdPrintfDummy("file_LoadCDFile:No Disc.\n");
        break;
    case 0x11:
        debug_StdPrintfDummy("file_LoadCDFile:Tray is opened.\n");
        break;
    case 0x10:
        debug_StdPrintfDummy("Undefined command.\n");
    case 0x01:
        debug_StdPrintfDummy("file_LoadCDFile:Aborted.\n");
        break;
    case -1:
        debug_StdPrintfDummy("file_LoadCDFile:Fail\n");
    }

    if (err != 0) {
        debug_assert("src/FileManager.c", 440);
        __assert("src/FileManager.c", 440, "FALSE");
    }
    return size;
}

int file_LoadFile(void **adr, char *fname, int area)
{
    return file_LoadCDFile(adr, fname, area);
}
