/* Vendor SCE library member: libcdvd.a(cdvd014).  sceCdGetDiskType.  Rung: MAIN.MAP member
 * sizes tile the retail run (cdvd000 0x1434, cdvd005 0x1E0, cdvd006 0x154,
 * cdvd014 0x98, cdvd015 0x98, cdvd047 0x4E0 up to sceCdStream's end), and
 * SRCFILE.TXT's libcdvd is the retail revision function for function. */
#include "common.h"
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>

extern char _sceCd_cd_scmd[];
extern int _sceCd_scmdrdata[];
extern int _sceCd_scmd_semid;
extern int _sceCd_scmd_prechk(int a0);
extern int sceSifCallRpc();

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
