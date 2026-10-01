/* libcdvd.a(cdvd047): the stream entry points and the IOP stream helper.
 * The member ends at sceCdStream: _send_to_iop after it is libpad.o's first
 * function. */
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>
#include <libcdvd.h>
#include <libcdvd_internal.h>

/* The member's own .data word: set by sceCdStStart and sceCdStResume, cleared
 * by sceCdStInit, sceCdStStop and sceCdStPause, and tested by sceCdStRead
 * (explicit zero initialiser, so it stays in .data). */
static int stStarted = 0; /* derived name */

/* The member's own .bss: the mode record every call but sceCdStStart passes. */
static CdRMode stMode; /* derived name */

int sceCdStInit(int bufmax, int bankmax, void *buf)
{
    stStarted = 0;
    return sceCdStream(bufmax, bankmax, buf, 5, &stMode);
}

int sceCdStStart(int lsn, CdRMode *mode)
{
    stStarted = 1;
    return sceCdStream(lsn, 0, 0, 1, mode);
}

int sceCdStSeekF(int a0)
{
    return sceCdStream(a0, 0, 0, 9, &stMode);
}

int sceCdStSeek(int a0)
{
    return sceCdStream(a0, 0, 0, 4, &stMode);
}

int sceCdStStop(void)
{
    stStarted = 0;
    return sceCdStream(0, 0, 0, 3, &stMode);
}

int sceCdStRead(int sectors, void *buf, int mode, int *err)
{
    int got;
    unsigned int r;
    unsigned int n;
    int e;
    int rerr;

    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStRead call read size= %d mode= %d\n", sectors);
    }
    if (stStarted == 0) {
        return 0;
    }
    rerr = 0;
    got = 0;
    sceSifWriteBackDCache(buf, sectors << 11);
    if (mode != 0) {
        do {
            r = sceCdStream(0, sectors - got, (char *)buf + (got << 11), 2, &stMode);
            n = r & 0xFFFF;
            e = r >> 16;
            got += n;
            if (e != 0) {
                rerr = e;
                if (SCE_CD_debug > 0) {
                    scePrintf(
                        "sceCdStRead BLK Read cur_size= %d read_size= %d req_size= %d err 0x%x\n",
                        got, n, sectors, e);
                }
            } else if (n == 0) {
                sceCdDelayThread(8);
            }
        } while (got != sectors && (e == 0 || n != 0));
        if (SCE_CD_debug > 0) {
            scePrintf("sceCdStRead BLK Read Ended\n");
        }
        *err = rerr;
    } else {
        r = sceCdStream(0, sectors, buf, 2, &stMode);
        e = r >> 16;
        got = r & 0xFFFF;
        *err = e;
    }
    return got;
}

int sceCdStPause(void)
{
    stStarted = 0;
    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStPause call\n");
    }
    return sceCdStream(0, 0, 0, 7, &stMode);
}

int sceCdStResume(void)
{
    stStarted = 1;
    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStResume call\n");
    }
    return sceCdStream(0, 0, 0, 8, &stMode);
}

int sceCdStStat(void)
{
    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStStat call\n");
    }
    return sceCdStream(0, 0, 0, 6, &stMode);
}

typedef struct {
    int lsn;     /* 0x0, the sector, or the buffer size for the init command */
    int sectors; /* 0x4, the count, or the bank count for the init command */
    void *buf;   /* 0x8 */
    int cmd;     /* 0xC */
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdStreamCmd;

int sceCdStream(int lsn, int sectors, void *buf, int cmd, CdRMode *mode)
{
    CdStreamCmd *sd = (CdStreamCmd *)_sceCd_ncmdsdata;
    int *p;
    int v;

    if (_sceCd_ncmd_prechk(0xF) == 0) {
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("call cdreadstm call\n");
    }
    sd->lsn = lsn;
    sd->sectors = sectors;
    sd->buf = buf;
    sd->cmd = cmd;
    if (mode != 0) {
        sd->trycount = mode->trycount;
        sd->spindlctrl = mode->spindlctrl;
        sd->datapattern = mode->datapattern;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("call cdreadstm cmd\n");
    }
    sceSifWriteBackDCache(sd, 0x14);
    p = _sceCd_ncmdrdata;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 9, 0, sd, 0x14, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("cdread end\n");
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_ncmd_semid);
    return v;
}
