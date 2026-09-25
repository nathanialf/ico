/* Vendor SCE library member: libcdvd.a(cdvd005).  sceCdRead.  Rung: MAIN.MAP member
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

/* The EE read-mode word is set by sceCdSetEEReadMode from any thread and is
   read twice here around calls: volatile. WHAT THE BYTES PIN: the second
   read heads the join after the sector-size switch, and reorg leaves the
   tree's last branch slot empty (a nop) because it will not move a volatile
   load into a delay slot. */
extern volatile int _sceCd_ee_read_mode;
extern CdReadCmd _sceCd_ncmdsdata[];
extern int _sceCd_rd_intr_data[];
extern int _sceCd_Read_cur_pos[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_ncmd_semid;
extern int SCE_CD_debug;
/* Shared with the SIF RPC end interrupt and the callback thread (cdvd000),
   as in sceCdReadIOPm (cdvd006): volatile, and the failure arm reads the
   semaphore id per access. */
extern volatile int sceCdCbfunc_num;
extern volatile int _sceCd_c_cb_sem;
extern void _sceCd_cd_read_intr(void);
extern int sceCdNcmdDiskReady(void);
extern int _sceCd_ncmd_prechk(int a0);

int sceCdRead(int lsn, int sectors, void *buf, CdRMode *mode)
{
    CdReadCmd *sd = _sceCd_ncmdsdata;
    int size;

    if ((_sceCd_ee_read_mode & 1) == 0) {
        if (sceCdNcmdDiskReady() == 6) {
            return 0;
        }
    }
    if (_sceCd_ncmd_prechk(4) == 0) {
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
    switch (mode->datapattern) {
    case 1:
        size = sectors * 2328;
        break;
    case 2:
        size = sectors * 2340;
        break;
    case 0:
    default:
        size = sectors * 2048;
        break;
    }
    _sceCd_Read_cur_pos[0] = 0;
    if ((_sceCd_ee_read_mode & 2) == 0) {
        sceSifWriteBackDCache(buf, size);
    }
    sceSifWriteBackDCache(_sceCd_rd_intr_data, 144);
    sceSifWriteBackDCache(sd, 24);
    sceSifWriteBackDCache(_sceCd_Read_cur_pos, 4);
    if (SCE_CD_debug > 0) {
        scePrintf("call cdread cmd\n");
    }
    sceCdCbfunc_num = 1;
    _sceCd_c_cb_sem = 1;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 1, 1, sd, 24, 0, 0, _sceCd_cd_read_intr,
                      _sceCd_rd_intr_data) < 0) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid);
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("cdread end\n");
    }
    return 1;
}
