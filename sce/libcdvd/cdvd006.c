/* Vendor SCE library member: libcdvd.a(cdvd006).  sceCdReadIOPm.  Rung: MAIN.MAP member
 * sizes tile the retail run (cdvd000 0x1434, cdvd005 0x1E0, cdvd006 0x154,
 * cdvd014 0x98, cdvd015 0x98, cdvd047 0x4E0 up to sceCdStream's end), and
 * SRCFILE.TXT's libcdvd is the retail revision function for function. */
#include "common.h"
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>

typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdRMode;

typedef struct {
    int lsn;
    int sectors;
    void *buf;
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
    int *intr_data;
    int *cur_pos;
} CdReadCmd;

extern int _sceCd_ee_read_mode;
extern CdReadCmd _sceCd_ncmdsdata[];
extern int _sceCd_rd_intr_data[];
extern int _sceCd_Read_cur_pos[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_ncmd_semid[];
extern int SCE_CD_debug[];
/* The callback number and the callback-busy word are shared with the SIF RPC
   end interrupt and the callback thread (cdvd000): volatile. WHAT THE BYTES
   PIN: both stores volatile (their output dependence orders the set-up
   block) and the failure arm's semaphore id read per access (its load waits
   for the two clears and leaves the jal slot to the assembler). */
extern volatile int sceCdCbfunc_num;
extern volatile int _sceCd_c_cb_sem;
extern void _sceCd_cd_callback(void);
extern int sceCdNcmdDiskReady(void);
extern int _sceCd_ncmd_prechk(int a0);

int sceCdReadIOPm(int lsn, int sectors, void *buf, CdRMode *mode)
{
    CdReadCmd *sd = _sceCd_ncmdsdata;

    if ((_sceCd_ee_read_mode & 1) == 0) {
        if (sceCdNcmdDiskReady() == 6) {
            return 0;
        }
    }
    if (_sceCd_ncmd_prechk(5) == 0) {
        return 0;
    }
    sd->lsn = lsn;
    sd->sectors = sectors;
    sd->buf = buf;
    sd->trycount = mode->trycount;
    sd->spindlctrl = mode->spindlctrl;
    sd->datapattern = mode->datapattern;
    sd->intr_data = _sceCd_rd_intr_data;
    sd->cur_pos = _sceCd_Read_cur_pos;
    sceSifWriteBackDCache(sd, 24);
    sceCdCbfunc_num = 1;
    _sceCd_c_cb_sem = 1;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 13, 1, sd, 24, 0, 0, _sceCd_cd_callback, &sceCdCbfunc_num) <
        0) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid[0]);
        return 0;
    }
    if (SCE_CD_debug[0] > 0) {
        scePrintf("cdread end\n");
    }
    return 1;
}
