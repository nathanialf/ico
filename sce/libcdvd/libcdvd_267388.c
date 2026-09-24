/* Vendor SCE library run: libcdvd.a members absent from the January MAIN.MAP
 * link (sceCdStatus, sceCdBreak, sceCdReadClock at 0x267388..0x2675F0).  The
 * retail archive revision, which SRCFILE.TXT's link also carries, added them
 * between cdvd015 and cdvd047; each is referenced from the game, so each
 * could be its own member as cdvd014 and cdvd015 are, but the map names
 * none of them, so the three stay one row named by their address until the
 * ROM forces a split. */
#include "common.h"
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>

extern int SCE_CD_debug;
extern char _sceCd_cd_scmd[];
extern int _sceCd_scmdrdata[];
/* The S-command semaphore handle cmd_sem_init creates at run time (cdvd000
 * defines it), read through a volatile cast as cdvd000's own sites read it.
 * sceCdBreak's two SignalSema reads are volatile loads in the ROM (neither is
 * moved into a delay slot by the compiler, and the success-path read waits on
 * the store to sceCdCbfunc_num). In sceCdStatus and sceCdReadClock a plain
 * read gives the same text (the compiler fills the call's delay slot where
 * the SDK assembler otherwise does) but a different relocation order, so the
 * member keeps every read volatile, as it was. */
extern int _sceCd_scmd_semid;
extern int _sceCd_scmd_prechk(int a0);
extern int sceSifCallRpc();

int sceCdStatus(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(2) == 0) {
        return -1;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 0xC, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        return -1;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(*(volatile int *)&_sceCd_scmd_semid);
    if (SCE_CD_debug > 1) {
        scePrintf("status called\n");
    }
    return v;
}

/* volatile: the pending-callback id the callback thread polls and clears, as
 * cdvd000.c declares it. */
extern volatile int sceCdCbfunc_num;

int sceCdBreak(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(0x1E) == 0) {
        return 0;
    }
    p = _sceCd_scmdrdata;
    sceCdCbfunc_num = 8;
    if (sceSifCallRpc(_sceCd_cd_scmd, 0x16, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        sceCdCbfunc_num = 0;
        return 0;
    }
    sceCdCbfunc_num = 0;
    v = *(int *)((int)p | 0x20000000);
    SignalSema(*(volatile int *)&_sceCd_scmd_semid);
    return v;
}

typedef struct {
    unsigned char b[8];
} CdClock;

int sceCdReadClock(CdClock *clock)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(0xF) == 0) {
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("Libcdvd call Clock read 1\n");
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 1, 0, 0, 0, p, 0x10, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        return 0;
    }
    *clock = *(CdClock *)((int)(p + 1) | 0x20000000);
    if (SCE_CD_debug > 0) {
        scePrintf("Libcdvd call Clock read 2\n");
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(*(volatile int *)&_sceCd_scmd_semid);
    return v;
}
