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

extern int SCE_CD_debug[];
extern char _sceCd_cd_scmd[];
extern int _sceCd_scmdrdata[];
extern int _sceCd_scmd_semid[];
extern int _sceCd_scmd_prechk(int a0);
extern int sceSifCallRpc();
extern char D_006369C8[];

int sceCdStatus(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(2) == 0) {
        return -1;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 0xC, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return -1;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    if (SCE_CD_debug[0] > 1) {
        scePrintf(D_006369C8);
    }
    return v;
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd_267388", sceCdBreak);

extern char D_006369D8[];
extern char D_006369F8[];

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
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_006369D8);
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 1, 0, 0, 0, p, 0x10, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    *clock = *(CdClock *)((int)(p + 1) | 0x20000000);
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_006369F8);
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}
