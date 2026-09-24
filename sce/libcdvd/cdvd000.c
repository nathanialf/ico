/* Vendor SCE library member: libcdvd.a(cdvd000).  The callback thread, the power-off callback, the ncmd and scmd
 * pre-checks and the sync, init, disk-ready and media-mode entry points.  Rung: MAIN.MAP member
 * sizes tile the retail run (cdvd000 0x1434, cdvd005 0x1E0, cdvd006 0x154,
 * cdvd014 0x98, cdvd015 0x98, cdvd047 0x4E0 up to sceCdStream's end), and
 * SRCFILE.TXT's libcdvd is the retail revision function for function. */
#include "common.h"
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>

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
extern int D_0072EF00[];
extern int EIntr(void);
extern int sceCdSync(int a0);

int sceCdCallback(int a0)
{
    int ret;
    if (sceCdSync(1) != 0) {
        return 0;
    }
    (*(int (*)(void))DIntr)();
    ret = D_0072EF00[0];
    D_0072EF00[0] = a0;
    EIntr();
    return ret;
}

/* The command number the SIF RPC end interrupt writes and the callback thread
   polls: read back after every store, in every function of the member. */
extern volatile int sceCdCbfunc_num;
extern int sceCdCbfunc_number;
extern int _sceCd_c_cb_sem;
extern int _sceCd_ncmd_semid[];
extern int D_0054A554;
extern int D_0054A560;

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
    iSignalSema(*(volatile int *)&_sceCd_ncmd_semid[0]);
    if (D_0054A554 != 0 && D_0072EF00[0] != 0) {
        iSignalSema(*(volatile int *)&D_0054A560);
    } else {
        _sceCd_c_cb_sem = 0;
    }
    sceCdCbfunc_num = 0;
}

extern int D_0072EF0C;
extern int SCE_CD_debug[];
extern char D_006367C0[];
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
        WaitSema(D_0054A560);
        if (sceCdCbfunc_num == -1) {
            _sceCd_c_cb_sem = 0;
            sceCdCbfunc_num = 0;
            D_0054A554 = 0;
            D_0072EF0C = 0;
            ExitDeleteThread();
        }
        if (SCE_CD_debug[0] > 0) {
            scePrintf(D_006367C0, D_0072EF00[0], sceCdCbfunc_number);
        }
        if (D_0072EF00[0] != 0 && *(volatile int *)&sceCdCbfunc_number != 0) {
            ((void (*)(int))D_0072EF00[0])(*(volatile int *)&sceCdCbfunc_number);
        }
        *(volatile int *)&_sceCd_c_cb_sem = 0;
    }
}

extern int D_0054A554;
extern int D_0072EF10;
extern int D_0072EF18[];
extern int D_0072EF48[];
extern char D_00640AF0[];
extern void _Cdvd_cbLoop(void);
extern int CreateThread(int *param);

int sceCdInitEeCB(int priority, void *stack, int stackSize)
{
    int r = 1;

    if (D_0054A554 == 0) {
        D_0072EF10 = GetThreadId();
        ReferThreadStatus(D_0072EF10, D_0072EF18);
        D_0072EF48[3] = stackSize;
        D_0072EF48[4] = (int)D_00640AF0;
        D_0072EF48[1] = (int)_Cdvd_cbLoop;
        D_0072EF48[2] = (int)stack;
        D_0072EF48[5] = priority;
        D_0054A554 = CreateThread(D_0072EF48);
        StartThread(D_0054A554, 0);
    } else {
        ChangeThreadPriority(D_0054A554, priority);
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

extern int _sceCd_scmd_semid[];

void cmd_sem_init(void)
{
    int buf[8];

    if (_sceCd_ncmd_semid[0] == -1 || _sceCd_scmd_semid[0] == -1) {
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
        *(volatile int *)&_sceCd_ncmd_semid[0] = CreateSema(buf);
        _sceCd_scmd_semid[0] = CreateSema(buf);
        buf[2] = 0;
        *(volatile int *)&D_0054A560 = CreateSema(buf);
        *(volatile int *)&_sceCd_c_cb_sem = 0;
    }
}

extern void sceSifRemoveCmdHandler(unsigned int cid);

void cdvd_exit(void)
{
    if (D_0054A554 != 0) {
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
            SignalSema(D_0054A560);
        } while (0);
    }
    DeleteSema(_sceCd_ncmd_semid[0]);
    DeleteSema(_sceCd_scmd_semid[0]);
    DeleteSema(D_0054A560);
    (*(int (*)(void))DIntr)();
    sceSifRemoveCmdHandler(0x80000012);
    EIntr();
}

extern int D_0054A57C[];
extern void (*D_0072EF04[])(int);
extern int D_0072EF08[];
extern int PowerOffCB(void);

int sceCdPOffCallback(int a0, int a1)
{
    int ret;
    if (D_0054A57C[0] < 0) {
        PowerOffCB();
    }
    (*(int (*)(void))DIntr)();
    ret = (int)D_0072EF04[0];
    D_0072EF08[0] = a1;
    D_0072EF04[0] = (void (*)(int))a0;
    EIntr();
    return ret;
}

extern int D_0054A564[];

void _sceCd_Poff_Intr(void)
{
    if (D_0072EF04[0] != 0 && D_0054A564[0] == 0) {
        D_0072EF04[0](D_0072EF08[0]);
    }
}

extern int D_0072EF78[];
extern int D_0072EFA0;
extern char D_006367E8[];
extern int SCE_CD_debug[];

/* Binds the power-off RPC once and asks the IOP side to arm it. The bound
 * flag is cleared in the serve arm ahead of the break: the loop rotation moves
 * that arm with its exit test to the loop's tail, so the clear sits inside the
 * loop, which is what ranks the flag's %hi first among the three callee-saved
 * %hi values (flow.c recompute_reg_usage weights it by loop depth; a clear
 * after the loop ranks it last). The busy flag D_0054A564 is read by
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
    D_0054A564[0] = 1;
    (*(int (*)(void))DIntr)();
    sceSifAddCmdHandler(0x80000012, _sceCd_Poff_Intr, 0);
    EIntr();
    if (D_0054A57C[0] < 0) {
        i = 0;
        while (1) {
            if (sceSifBindRpc(D_0072EF78, 0x80000596, 0) < 0) {
                if (SCE_CD_debug[0] > 0) {
                    scePrintf(D_006367E8);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (D_0072EF78[9] != 0) {
                D_0054A57C[0] = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
            if (i++ >= 17) {
                *(volatile int *)&D_0054A564[0] = 0;
                return 0;
            }
        }
    }
    D_0072EFA0 = 11;
    if (sceSifCallRpc(D_0072EF78, 1, 1, 0, 0, 0, 0, 0, 0) < 0) {
        *(volatile int *)&D_0054A564[0] = 0;
        return 0;
    }
    *(volatile int *)&D_0054A564[0] = 0;
    return 1;
}

extern int D_0054A55C;
extern int D_0054A580;
extern void cmd_sem_init(void);
extern void sceSifWriteBackDCache(void *p, int n);
extern int D_0072F140[];
extern int D_0072F100[];

/* RECONSTRUCTION: the search RPC's request record, read off this function's
   offsets: the 0x24-byte file entry the reply fills, the 256-byte name, then
   the request's own address. */
typedef struct {
    unsigned char file[0x24];
    char name[0x100];
    void *addr;
} CdSearchReq;

extern CdSearchReq D_0072EFC0;
extern char D_00636808[];
extern char D_00636828[];
extern char D_00636840[];
extern char D_00636850[];
extern char D_00636860[];
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
    if (_sceCd_ncmd_semid[0] != PollSema(*(volatile int *)&_sceCd_ncmd_semid[0])) {
        return 0;
    }
    D_0054A55C = 1;
    ReferThreadStatus(D_0072EF10, D_0072EF18);
    if (sceCdSync(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid[0]);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_0054A580 < 0) {
        while (1) {
            if (sceSifBindRpc(D_0072F140, 0x80000597, 0) < 0) {
                if (SCE_CD_debug[0] > 0) {
                    scePrintf(D_00636808);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (D_0072F140[9] != 0) {
                D_0054A580 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    for (i = 0; i < 0x100; i++) {
        if ((D_0072EFC0.name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 0x100) {
        D_0072EFC0.name[i - 1] = 0;
    }
    req = (char *)&D_0072EFC0;
    *(char **)(req + 0x124) = req;
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636828, req + 0x24);
    }
    sceSifWriteBackDCache(req, 0x128);
    if (sceSifCallRpc(D_0072F140, 0, 0, req, 0x128, D_0072F100, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid[0]);
        return 0;
    }
    *fp = *(CdFileEntry *)((int)req | 0x20000000);
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636840, (char *)fp + 8);
    }
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636850, ((int *)fp)[1]);
    }
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636860, ((int *)fp)[0]);
    }
    v = *(int *)((int)D_0072F100 | 0x20000000);
    SignalSema(_sceCd_ncmd_semid[0]);
    return v;
}

extern int D_0054A578;
extern int _sceCd_cd_ncmd[];
extern char D_00636878[];
extern char D_006368A0[];

/* Same bind block and handle accesses as sceCdSearchFile. */
int _sceCd_ncmd_prechk(int cmd)
{
    int w;

    cmd_sem_init();
    if (_sceCd_ncmd_semid[0] != PollSema(*(volatile int *)&_sceCd_ncmd_semid[0])) {
        if (SCE_CD_debug[0] > 0) {
            scePrintf(D_00636878, cmd, D_0054A55C);
        }
        return 0;
    }
    D_0054A55C = cmd;
    ReferThreadStatus(D_0072EF10, D_0072EF18);
    if (sceCdSync(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_ncmd_semid[0]);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_0054A578 < 0) {
        while (1) {
            if (sceSifBindRpc(_sceCd_cd_ncmd, 0x80000595, 0) < 0) {
                if (SCE_CD_debug[0] > 0) {
                    scePrintf(D_006368A0);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (_sceCd_cd_ncmd[9] != 0) {
                D_0054A578 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    return 1;
}

extern int _sceCd_ncmd_semid[];
extern int _sceCd_ncmdrdata[];
extern int _sceCd_cd_ncmd[];
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
        SignalSema(_sceCd_ncmd_semid[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_ncmd_semid[0]);
    return v;
}

extern int SCE_CD_debug[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_c_cb_sem;
extern char D_006368B8[];
extern int sceSifCheckStatRpc(char *a0);

int sceCdSync(int mode)
{
    if (!mode) {
        if (SCE_CD_debug[0] > 0)
            scePrintf(D_006368B8);
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

extern char _sceCd_cd_scmd[];
extern char D_006368C8[];

int sceCdSyncS(int a0)
{
    if (!a0) {
        if (SCE_CD_debug[0] > 0)
            scePrintf(D_006368C8);
        while (sceSifCheckStatRpc(_sceCd_cd_scmd)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    return sceSifCheckStatRpc(_sceCd_cd_scmd);
}

extern int _sceCd_scmd_semid[];
extern int D_0054A558;
extern int D_0054A588;
extern char D_006368D8[];
extern char D_00636900[];
extern int sceCdSyncS(int a0);

/* The scmd twin of _sceCd_ncmd_prechk. */
int _sceCd_scmd_prechk(int cmd)
{
    int w;

    cmd_sem_init();
    if (_sceCd_scmd_semid[0] != PollSema(*(volatile int *)&_sceCd_scmd_semid[0])) {
        if (SCE_CD_debug[0] > 0) {
            scePrintf(D_006368D8, cmd, D_0054A558);
        }
        return 0;
    }
    D_0054A558 = cmd;
    ReferThreadStatus(D_0072EF10, D_0072EF18);
    if (sceCdSyncS(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid[0]);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_0054A588 < 0) {
        while (1) {
            if (sceSifBindRpc(_sceCd_cd_scmd, 0x80000593, 0) < 0) {
                if (SCE_CD_debug[0] > 0) {
                    scePrintf(D_00636900);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (((int *)_sceCd_cd_scmd)[9] != 0) {
                D_0054A588 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", sceCdInit);

extern int D_0072F190[];
extern int D_0072F1D0;
extern int D_0054A584;
extern char D_00636948[];
extern char D_00636958[];
extern char D_00636978[];
extern int _sceCd_scmdrdata[];

int sceCdDiskReady(int mode)
{
    int v;
    int w;

    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636948);
    }
    cmd_sem_init();
    if (_sceCd_scmd_semid[0] != PollSema(*(volatile int *)&_sceCd_scmd_semid[0])) {
        return 6;
    }
    if (sceCdSyncS(1) != 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid[0]);
        return (mode != 8) ? 6 : -1;
    }
    sceSifInitRpc(0);
    if (D_0054A584 < 0) {
        while (1) {
            if (sceSifBindRpc(D_0072F190, 0x8000059A, 0) < 0) {
                if (SCE_CD_debug[0] > 0) {
                    scePrintf(D_00636958);
                }
                w = 0x100000;
                while (w--) {}
                continue;
            }
            if (D_0072F190[9] != 0) {
                D_0054A584 = 0;
                break;
            }
            w = 0x100000;
            while (w--) {}
        }
    }
    D_0072F1D0 = mode;
    sceSifWriteBackDCache(&D_0072F1D0, 4);
    if (sceSifCallRpc(D_0072F190, 0, 0, &D_0072F1D0, 4, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(*(volatile int *)&_sceCd_scmd_semid[0]);
        return (mode != 8) ? 6 : -1;
    }
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636978);
    }
    v = *(int *)((int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}

extern int _sceCd_scmdsdata[];
extern int _sceCd_scmdrdata[];
extern int _sceCd_scmd_semid[];
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
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}
