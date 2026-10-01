/* libcdvd.a: sceCdStatus, sceCdBreak and sceCdReadClock, which this build's
 * archive revision adds between cdvd015 and cdvd047.  Their member names are
 * not known, so the three share one file named by their address. */
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>
#include <libcdvd_internal.h>
#include <libcdvd.h>

/* _sceCd_scmd_semid, the S-command semaphore handle cmd_sem_init creates at
 * run time (cdvd000 defines it), is read through a volatile cast as
 * cdvd000's own sites read it. */

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
