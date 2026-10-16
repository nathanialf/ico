/* libcdvd.a: sceCdStatus and sceCdBreak, which this build's archive revision
 * adds between cdvd015 and cdvd047 (the PAL build's revision has
 * sceCdReadClock after them; this one does not).  Their member names are not
 * known, so the two share one file named by sceCdStatus's address in the PAL
 * build, 0x267388 (0x24D848 in this one). */
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
    if (sceSifCallRpc(&_sceCd_cd_scmd, 0xC, 0, 0, 0, p, 4, 0, 0) < 0) {
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
    if (sceSifCallRpc(&_sceCd_cd_scmd, 0x16, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        sceCdCbfunc_num = 0;
        return 0;
    }
    sceCdCbfunc_num = 0;
    v = *(int *)((int)p | 0x20000000);
    SignalSema(*(volatile int *)&_sceCd_scmd_semid);
    return v;
}
