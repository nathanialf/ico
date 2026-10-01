/* libcdvd.a(cdvd015): sceCdGetError. */
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>
#include <libcdvd_internal.h>
#include <libcdvd.h>

int sceCdGetError(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(3) == 0) {
        return -1;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 4, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return -1;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    return v;
}
