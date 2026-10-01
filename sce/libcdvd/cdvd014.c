/* libcdvd.a(cdvd014): sceCdGetDiskType. */
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>
#include <libcdvd_internal.h>
#include <libcdvd.h>

int sceCdGetDiskType(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(1) == 0) {
        return 0;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 3, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    return v;
}
