/* Vendor SCE library member: libcdvd.a(cdvd000).  The callback thread, the power-off callback, the ncmd and scmd
 * pre-checks and the sync, init, disk-ready and media-mode entry points.  Rung: MAIN.MAP member
 * sizes tile the retail run (cdvd000 0x1434, cdvd005 0x1E0, cdvd006 0x154,
 * cdvd014 0x98, cdvd015 0x98, cdvd047 0x4E0 up to sceCdStream's end), and
 * SRCFILE.TXT's libcdvd is the retail revision function for function. */
#include "common.h"
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>

/* RECONSTRUCTION: the search RPC's request record, read off sceCdSearchFile's
   offsets: the 0x24-byte file entry the reply fills, the 256-byte name, then
   the request's own address. */
typedef struct {
    unsigned char file[0x24];
    char name[0x100];
    void *addr;
} CdSearchReq;

/* The member's .data in the ROM's order (VMA 0x54A540..0x54BFB0).  The names
   MAIN.MAP lists for cdvd000.o are globals (the other libcdvd members bind to
   them); the rest are statics named for their role.  Every SIF RPC buffer is
   64-byte aligned, a cache line.  The bind states are -1 until the server is
   bound and 0 after. */
static char sceCdvdVersion[16] = "PsIIlibcdvd 2240";

int SCE_CD_debug = 0;

static int cb_thread_id = 0;

static int scmd_keep_cmd = 0;

static int ncmd_keep_cmd = 0;

static int cb_semid = -1;

static int poff_busy = 0;

int _sceCd_ncmd_semid = -1;

int _sceCd_scmd_semid = -1;

int _sceCd_c_cb_sem = 0;

int _sceCd_ee_read_mode = 0;

static int ncmd_bind = -1;

static int poff_bind = -1;

static int search_bind = -1;

static int diskready_bind = -1;

static int scmd_bind = -1;

static int init_bind = -1;

static int init_count = 0;

/* The command number the SIF RPC end interrupt writes and the callback thread
   polls: read back after every store, in every function of the member. */
volatile int sceCdCbfunc_num = 0;

int sceCdCbfunc_number = 0;

int _sceCd_ncmdrdata[32] __attribute__((aligned(64))) = {0};

int _sceCd_ncmdsdata[1024] __attribute__((aligned(64))) = {0};

int _sceCd_rd_intr_data[48] __attribute__((aligned(64))) = {0};

int _sceCd_Read_cur_pos[4] __attribute__((aligned(64))) = {0};

int _sceCd_cd_ncmd[10] = {0};

int _sceCd_scmdrdata[272] __attribute__((aligned(64))) = {0};

int _sceCd_scmdsdata[258] __attribute__((aligned(64))) = {0};

char _sceCd_cd_scmd[40] = {0};

/* The member's .bss in the ROM's order (VMA 0x72EF00..0x72F1D4), all file
   statics: the callbacks, the callback thread, and each bound server's client
   record and buffers. */
static int cd_cbfunc;

static void (*poff_cbfunc)(int);

static int poff_cbarg;

static int cb_thread_word;

static int cd_thread_id;

static int cd_thread_stat[12];

static int cb_thread_param[12];

static int poff_cd[10];

static int poff_sdata;

static CdSearchReq search_req __attribute__((aligned(64)));

static int search_rdata[16] __attribute__((aligned(64)));

static int search_cd[10];

static int init_cd[10];

static int diskready_cd[10];

static int init_sdata __attribute__((aligned(64)));
static int diskready_sdata __attribute__((aligned(16)));

/* CB_DelayTh is the member's first function; its first word sits in the delay
   slot of the stray jr that ends libkernl.a's sceSifWriteBackDCache, the
   previous input, which is why splat once split it one word late.  The
   SetAlarm callback: signal the semaphore from the handler and re-enable
   interrupts. */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .global CB_DelayTh\n"
        "    .type CB_DelayTh, @function\n"
        "    .align 2\n"
        "CB_DelayTh:\n"
        "    addiu $29, $29, -0x10\n"
        "    sd    $31, 0x0($29)\n"
        "    jal   iSignalSema\n"
        "    daddu $4, $6, $0\n"
        "    sync\n"
        "    ei\n"
        "    ld    $31, 0x0($29)\n"
        "    jr    $31\n"
        "    addiu $29, $29, 0x10\n"
        "    .size CB_DelayTh, . - CB_DelayTh\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

extern void CB_DelayTh(void);

void sceCdDelayThread(unsigned short a0)
{
    int buf[8];
    unsigned short id = a0;
    int r;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    r = CreateSema(buf);
    SetAlarm(id, CB_DelayTh, r);
    WaitSema(r);
    DeleteSema(r);
}

extern void DIntr(int *self);
extern int EIntr(void);
extern int sceCdSync(int a0);

int sceCdCallback(int a0)
{
    int ret;
    if (sceCdSync(1) != 0) {
        return 0;
    }
    (*(int (*)(void))DIntr)();
    ret = cd_cbfunc;
    cd_cbfunc = a0;
    EIntr();
    return ret;
}

/* Runs from the SIF RPC end interrupt. WHAT THE BYTES PIN: four accesses here
 * are volatile accesses to words that are not volatile objects. The number
 * store stays ahead of the third num read, the ==11 arm's flag store stays out
 * of the return branch's slot, and both semaphore-handle loads stay in front of
 * their jal iSignalSema with the slot empty; in this compiler only a volatile
 * MEM does that (reorg.c fill_simple_delay_slots with resource.c
 * resource_conflicts_p; alias.c true_dependence orders two distinct globals
 * only when both are volatile). The same words are plain elsewhere in the
 * member (cbLoop's number argument loads and flag store, cmd_sem_init's and
 * cdvd_exit's handle accesses and sceCdNcmdDiskReady's fill delay slots), and a
 * volatile declaration of any of them, at file or block scope, makes every
 * later access volatile. Sony's member reads these words the same way at its
 * other synchronisation points: _Cdvd_cbLoop's guard read of the number (not
 * merged with the argument load two words later, which fills the jalr slot)
 * and the PollSema and error-path SignalSema handle loads of
 * _sceCd_ncmd_prechk, _sceCd_scmd_prechk, sceCdSearchFile and sceCdDiskReady.
 * WHAT THEY CANNOT PIN: how the volatile accesses were spelled. */
void _sceCd_cd_callback(int *data)
{
    sceCdCbfunc_num = data[0];
    *(volatile int *)&sceCdCbfunc_number = sceCdCbfunc_num;
    if (sceCdCbfunc_num == 11) {
        sceCdCbfunc_num = 0;
        *(volatile int *)&_sceCd_c_cb_sem = 0;
        return;
    }
    iSignalSema(*(volatile int *)&_sceCd_ncmd_semid);
    if (cb_thread_id != 0 && cd_cbfunc != 0) {
        iSignalSema(*(volatile int *)&cb_semid);
    } else {
        _sceCd_c_cb_sem = 0;
    }
    sceCdCbfunc_num = 0;
}

extern void ExitDeleteThread(void);

/* The callback number is written by the interrupt-side _sceCd_cd_callback and
 * the loop reads it per access at the guard and again for the argument; the
 * loop-closing release of _sceCd_c_cb_sem is a per-access store as in the
 * callback. WHAT THE BYTES PIN: the guard and argument loads are separate
 * words (not CSE'd), both beqz slots are bare, and the argument load and the
 * release store sit in the jalr and b slots, which this archive's assembler
 * fills in reorder mode from a volatile access gcc's reorg leaves in place
 * (the plain store is stolen into beqzl slots instead). WHAT THEY CANNOT PIN:
 * how the volatile accesses were spelled. */
void _Cdvd_cbLoop(void)
{
    while (1) {
        WaitSema(cb_semid);
        if (sceCdCbfunc_num == -1) {
            _sceCd_c_cb_sem = 0;
            sceCdCbfunc_num = 0;
            cb_thread_id = 0;
            cb_thread_word = 0;
            ExitDeleteThread();
        }
        if (SCE_CD_debug > 0) {
            scePrintf("sceCdCbfunc= %d sceCdCbfunc_num= %d\n", cd_cbfunc, sceCdCbfunc_number);
        }
        if (cd_cbfunc != 0 && *(volatile int *)&sceCdCbfunc_number != 0) {
            ((void (*)(int))cd_cbfunc)(*(volatile int *)&sceCdCbfunc_number);
        }
        *(volatile int *)&_sceCd_c_cb_sem = 0;
    }
}

extern char D_00640AF0[];
extern void _Cdvd_cbLoop(void);
extern int CreateThread(int *param);

int sceCdInitEeCB(int priority, void *stack, int stackSize)
{
    int r = 1;

    if (cb_thread_id == 0) {
        cd_thread_id = GetThreadId();
        ReferThreadStatus(cd_thread_id, cd_thread_stat);
        cb_thread_param[3] = stackSize;
        cb_thread_param[4] = (int)D_00640AF0;
        cb_thread_param[1] = (int)_Cdvd_cbLoop;
        cb_thread_param[2] = (int)stack;
        cb_thread_param[5] = priority;
        cb_thread_id = CreateThread(cb_thread_param);
        StartThread(cb_thread_id, 0);
    } else {
        ChangeThreadPriority(cb_thread_id, priority);
        r = 0;
    }
    return r;
}

/* RECONSTRUCTION: the read RPC's reply record, read off this function's
   offsets: the byte counts and destinations of the unaligned head and tail
   of a read, then the two 64-byte bounce buffers. */
typedef struct {
    int size1;
    int size2;
    char *dest1;
    char *dest2;
    char buf1[64];
    char buf2[64];
} CdReadEnd;

void _sceCd_cd_read_intr(void *pkt)
{
    CdReadEnd *r = (CdReadEnd *)((int)pkt | 0x20000000);
    char *dst;
    int i;

    if (r->size1 > 0) {
        dst = r->dest1;
        for (i = 0; i < r->size1; i++) {
            dst[i] = r->buf1[i];
        }
    }
    if (r->size2 > 0) {
        dst = r->dest2;
        for (i = 0; i < r->size2; i++) {
            dst[i] = r->buf2[i];
        }
    }
    _sceCd_cd_callback((int *)&sceCdCbfunc_num);
}

void cmd_sem_init(void)
{
    int buf[8];

    if (_sceCd_ncmd_semid == -1 || _sceCd_scmd_semid == -1) {
        buf[5] = 0;
        buf[2] = 1;
        buf[1] = 1;
        /* The handle stores are the member's per-access volatile spelling (the
           form the semaphore reads at the wait sites above use). WHAT THE BYTES
           PIN: with the ncmd store volatile, reorg refuses it for the second
           CreateSema's delay slot (resource.c 708-713, reorg.c 268-271) and
           gcc emits the call in reorder mode; the ROM carries the store in
           that slot, which is the archive assembler's reorder-mode swap of
           the compiler's own output (docs/NOTES.md "Assembler per archive"). */
        *(volatile int *)&_sceCd_ncmd_semid = CreateSema(buf);
        _sceCd_scmd_semid = CreateSema(buf);
        buf[2] = 0;
        *(volatile int *)&cb_semid = CreateSema(buf);
        *(volatile int *)&_sceCd_c_cb_sem = 0;
    }
}

extern void sceSifRemoveCmdHandler(unsigned int cid);

void cdvd_exit(void)
{
    if (cb_thread_id != 0) {
        sceCdCbfunc_num = -1;
        /* The wake-up is written as a do/while(0) statement, the form Sony's
           libmpeg member carries around sceMpegDemuxPss's call. WHAT THE
           BYTES PIN: the ROM stores the -1 (0x265F58-0x265F64) before the
           semaphore handle's lui and loads the handle in SignalSema's delay
           slot; sched2 gives that order only when a loop-note pair sits
           between the store and the handle's set-up (haifa-sched.c
           3702-3724), since no register or alias dependence links two
           distinct symbols (alias.c base_alias_check) and a volatile handle
           load would keep reorg out of the slot. WHAT THEY CANNOT PIN: the
           macro the statement stood for (this member has no listing rows). */
        do {
            SignalSema(cb_semid);
        } while (0);
    }
    DeleteSema(_sceCd_ncmd_semid);
    DeleteSema(_sceCd_scmd_semid);
    DeleteSema(cb_semid);
    (*(int (*)(void))DIntr)();
    sceSifRemoveCmdHandler(0x80000012);
    EIntr();
}

extern int PowerOffCB(void);

int sceCdPOffCallback(int a0, int a1)
{
    int ret;
    if (poff_bind < 0) {
        PowerOffCB();
    }
    (*(int (*)(void))DIntr)();
    ret = (int)poff_cbfunc;
    poff_cbarg = a1;
    poff_cbfunc = (void (*)(int))a0;
    EIntr();
    return ret;
}

void _sceCd_Poff_Intr(void)
{
    if (poff_cbfunc != 0 && poff_busy == 0) {
        poff_cbfunc(poff_cbarg);
    }
}

/* Binds the power-off RPC once and asks the IOP side to arm it. The bound
 * flag is cleared in the serve arm ahead of the break: the loop rotation moves
 * that arm with its exit test to the loop's tail, so the clear sits inside the
 * loop, which is what ranks the flag's %hi first among the three callee-saved
 * %hi values (flow.c recompute_reg_usage weights it by loop depth; a clear
 * after the loop ranks it last). The busy flag poff_busy is read by
 * _sceCd_Poff_Intr from the SIF command interrupt: its three clears are
 * volatile accesses (both return arms keep their clear out of the final
 * bgez delay slot, which reorg refuses only to a volatile store) while the
 * set is plain (it fills the jal DIntr slot). WHAT THE BYTES CANNOT PIN: how
 * the volatile clears were spelled. */
int PowerOffCB(void)
{
    int i;
    int w;

    sceSifInitRpc(0);
    poff_busy = 1;
    (*(int (*)(void))DIntr)();
    sceSifAddCmdHandler(0x80000012, _sceCd_Poff_Intr, 0);
    EIntr();
    if (poff_bind < 0) {
        i = 0;
        while (1) {
            if (sceSifBindRpc(poff_cd, 0x80000596, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err PowerOffCB\n");
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (poff_cd[9] != 0) {
                poff_bind = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
            if (i++ >= 17) {
                *(volatile int *)&poff_busy = 0;
                return 0;
            }
        }
    }
    poff_sdata = 11;
    if (sceSifCallRpc(poff_cd, 1, 1, 0, 0, 0, 0, 0, 0) < 0) {
        *(volatile int *)&poff_busy = 0;
        return 0;
    }
    *(volatile int *)&poff_busy = 0;
    return 1;
}

extern void cmd_sem_init(void);
extern void sceSifWriteBackDCache(void *p, int n);
extern int sceSifCallRpc();

/* RECONSTRUCTION: the 0x24-byte file entry, copied whole (the ROM's ldl/ldr
   and sdl/sdr run). */
typedef struct {
    unsigned char b[0x24];
} CdFileEntry;

/* The bind block is PowerOffCB's (bound flag cleared in the serve arm); the
   semaphore-handle loads are the per-site volatile accesses described above
   _sceCd_cd_callback. */
int sceCdSearchFile(CdFileEntry *fp, const char *name)
{
    char *req;
    int w;
    int i;
    int v;

    cmd_sem_init();
    if (_sceCd_ncmd_semid != PollSema(*(volatile int *)&_sceCd_ncmd_semid)) {
        return 0;
    }
    ncmd_keep_cmd = 1;
    ReferThreadStatus(cd_thread_id, cd_thread_stat);
    if (sceCdSync(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (search_bind < 0) {
        while (1) {
            if (sceSifBindRpc(search_cd, 0x80000597, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err CdSearchFile\n");
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (search_cd[9] != 0) {
                search_bind = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    for (i = 0; i < 0x100; i++) {
        if ((search_req.name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 0x100) {
        search_req.name[i - 1] = 0;
    }
    req = (char *)&search_req;
    *(char **)(req + 0x124) = req;
    if (SCE_CD_debug > 0) {
        scePrintf("ee call cmd search %s\n", req + 0x24);
    }
    sceSifWriteBackDCache(req, 0x128);
    if (sceSifCallRpc(search_cd, 0, 0, req, 0x128, search_rdata, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid);
        return 0;
    }
    *fp = *(CdFileEntry *)((int)req | 0x20000000);
    if (SCE_CD_debug > 0) {
        scePrintf("search name %s\n", (char *)fp + 8);
    }
    if (SCE_CD_debug > 0) {
        scePrintf("search size %d\n", ((int *)fp)[1]);
    }
    if (SCE_CD_debug > 0) {
        scePrintf("search loc lbn %d\n", ((int *)fp)[0]);
    }
    v = *(int *)((int)search_rdata | 0x20000000);
    SignalSema(_sceCd_ncmd_semid);
    return v;
}

/* Same bind block and handle accesses as sceCdSearchFile. */
int _sceCd_ncmd_prechk(int cmd)
{
    int w;

    cmd_sem_init();
    if (_sceCd_ncmd_semid != PollSema(*(volatile int *)&_sceCd_ncmd_semid)) {
        if (SCE_CD_debug > 0) {
            scePrintf("Ncmd fail sema cur_cmd:%d keep_cmd:%d\n", cmd, ncmd_keep_cmd);
        }
        return 0;
    }
    ncmd_keep_cmd = cmd;
    ReferThreadStatus(cd_thread_id, cd_thread_stat);
    if (sceCdSync(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (ncmd_bind < 0) {
        while (1) {
            if (sceSifBindRpc(_sceCd_cd_ncmd, 0x80000595, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err N CMD\n");
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (_sceCd_cd_ncmd[9] != 0) {
                ncmd_bind = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    return 1;
}

extern int _sceCd_ncmd_prechk(int a0);
extern int sceSifCallRpc();

int sceCdNcmdDiskReady(void)
{
    int *p;
    int v;
    if (_sceCd_ncmd_prechk(2) == 0) {
        return 0;
    }
    p = _sceCd_ncmdrdata;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 0xE, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_ncmd_semid);
    return v;
}

extern int sceSifCheckStatRpc(char *a0);

int sceCdSync(int mode)
{
    if (!mode) {
        if (SCE_CD_debug > 0)
            scePrintf("N cmd wait\n");
        while (_sceCd_c_cb_sem != 0 || sceSifCheckStatRpc((char *)_sceCd_cd_ncmd)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    if (_sceCd_c_cb_sem != 0 || sceSifCheckStatRpc((char *)_sceCd_cd_ncmd) != 0) {
        return 1;
    }
    return 0;
}

int sceCdSyncS(int a0)
{
    if (!a0) {
        if (SCE_CD_debug > 0)
            scePrintf("S cmd wait\n");
        while (sceSifCheckStatRpc(_sceCd_cd_scmd)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    return sceSifCheckStatRpc(_sceCd_cd_scmd);
}

extern int sceCdSyncS(int a0);

/* The scmd twin of _sceCd_ncmd_prechk. */
int _sceCd_scmd_prechk(int cmd)
{
    int w;

    cmd_sem_init();
    if (_sceCd_scmd_semid != PollSema(*(volatile int *)&_sceCd_scmd_semid)) {
        if (SCE_CD_debug > 0) {
            scePrintf("Scmd fail sema cur_cmd:%d keep_cmd:%d\n", cmd, scmd_keep_cmd);
        }
        return 0;
    }
    scmd_keep_cmd = cmd;
    ReferThreadStatus(cd_thread_id, cd_thread_stat);
    if (sceCdSyncS(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (scmd_bind < 0) {
        while (1) {
            if (sceSifBindRpc(_sceCd_cd_scmd, 0x80000593, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err S cmd\n");
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (((int *)_sceCd_cd_scmd)[9] != 0) {
                scmd_bind = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    return 1;
}

extern void cdvd_exit(void);

/* Binds the init RPC and reads the IOP module's version reply. The busy flag
 * set and the ee_read_mode reset are volatile accesses: the busy word is read
 * by _sceCd_Poff_Intr from the SIF command interrupt (its clears here and in
 * PowerOffCB are volatile too) and ee_read_mode is shared with sceCdRead and
 * sceCdReadIOPm. WHAT THE BYTES PIN: the busy store has a later volatile
 * dependent in its block (a plain pair swaps the s4/s5 %hi values), and the
 * reset order: the poff_bind reset is the last -1 store and the init_bind
 * reset sits between the diskready_bind and poff_bind resets (sched1 ranks a
 * store that kills the shared -1 ahead of the others, and the order fixes
 * every %hi register of the entry). NOT PINNED: which later access is the
 * busy store's volatile partner. */
int sceCdInit(int mode)
{
    int *p;
    int ver;
    int r;
    int w;
    int type;
    int v1;
    int v2;

    if (sceCdSyncS(1) != 0) {
        return 0;
    }
    sceSifInitRpc(0);
    cd_thread_id = GetThreadId();
    *(volatile int *)&poff_busy = 1;
    search_bind = -1;
    ncmd_bind = -1;
    scmd_bind = -1;
    diskready_bind = -1;
    init_bind = -1;
    poff_bind = -1;
    *(volatile int *)&_sceCd_ee_read_mode = 0;
    init_count++;
    while (1) {
        r = sceSifBindRpc(init_cd, 0x80000592, 0);
        if (r < 0) {
            if (SCE_CD_debug > 0) {
                scePrintf("Libcdvd bind err %d CD_Init %d\n", r, init_count);
            }
            w = 0x100000;
            while (w--) {}
            continue;
        }
        if (init_cd[9] != 0) {
            init_sdata = mode;
            init_bind = 0;
            sceSifWriteBackDCache(&init_sdata, 4);
            p = _sceCd_scmdrdata;
            if (sceSifCallRpc(init_cd, 0, 0, &init_sdata, 4, p, 16, 0, 0) < 0) {
                *(volatile int *)&poff_busy = 0;
                return 0;
            }
            break;
        }
        w = 0x100000;
        while (w--) {}
    }
    v1 = *(int *)((int)(p + 1) | 0x20000000);
    v2 = *(int *)((int)(p + 2) | 0x20000000);
    type = *(int *)((int)(p + 3) | 0x20000000);
    ver = 1;
    if (type == 0xFF) {
    } else if (type == 0xFE) {
        SCE_CD_debug = 1;
    } else if (v1 / 256 < 2 || v2 / 256 < 2) {
        ver = 2;
    }
    *(volatile int *)&poff_busy = 0;
    switch (mode) {
    case 5:
        if (SCE_CD_debug > 0) {
            scePrintf("Libcdvd Exit\n");
        }
        cdvd_exit();
        *(volatile int *)&_sceCd_ncmd_semid = -1;
        *(volatile int *)&_sceCd_scmd_semid = -1;
        *(volatile int *)&cb_semid = -1;
        break;
    case 0:
    case 1:
    default:
        cmd_sem_init();
        PowerOffCB();
        break;
    }
    return ver;
}

int sceCdDiskReady(int mode)
{
    int v;
    int w;

    if (SCE_CD_debug > 0) {
        scePrintf("DiskReady 0\n");
    }
    cmd_sem_init();
    if (_sceCd_scmd_semid != PollSema(*(volatile int *)&_sceCd_scmd_semid)) {
        return 6;
    }
    if (sceCdSyncS(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        return (mode != 8) ? 6 : -1;
    }
    sceSifInitRpc(0);
    if (diskready_bind < 0) {
        while (1) {
            if (sceSifBindRpc(diskready_cd, 0x8000059A, 0) < 0) {
                if (SCE_CD_debug > 0) {
                    scePrintf("Libcdvd bind err CdDiskReady\n");
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (diskready_cd[9] != 0) {
                diskready_bind = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    diskready_sdata = mode;
    sceSifWriteBackDCache(&diskready_sdata, 4);
    if (sceSifCallRpc(diskready_cd, 0, 0, &diskready_sdata, 4, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid);
        return (mode != 8) ? 6 : -1;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("DiskReady ended\n");
    }
    v = *(int *)((int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    return v;
}

extern int _sceCd_scmd_prechk(int a0);
extern void sceSifWriteBackDCache(void *p, int n);

int sceCdMmode(int media)
{
    int *p;
    int *sd;
    int v;
    sd = _sceCd_scmdsdata;
    if (_sceCd_scmd_prechk(0x22) == 0) {
        return 0;
    }
    sd[0] = media;
    sceSifWriteBackDCache(sd, 4);
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 0x22, 0, sd, 4, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    return v;
}
