#include "common.h"
#include "ico/types.h"

extern int file_LoadCDFile(void);
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
extern void debug_StdPrintfDummy(const char *fmt);
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

INCLUDE_ASM("asm/nonmatchings/src/FileManager", file_LoadCDFile);

int file_LoadFile(void)
{
    return file_LoadCDFile();
}
