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
extern void EIntr(void);
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

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", _Cdvd_cbLoop);

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

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", _sceCd_cd_read_intr);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", cmd_sem_init);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", cdvd_exit);

extern int D_0054A57C[];
extern void (*D_0072EF04[])(int);
extern int D_0072EF08[];
extern void PowerOffCB();

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

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", PowerOffCB);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", sceCdSearchFile);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", _sceCd_ncmd_prechk);

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

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", _sceCd_scmd_prechk);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", sceCdInit);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd000", sceCdDiskReady);

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
