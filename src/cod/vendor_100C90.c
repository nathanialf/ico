#include "common.h"
#include "r5900.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", InitAlarm);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100D68);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100E40);

/* Declared as arrays, not scalars: under -G 8 a 4-byte extern is small data
 * and gcc addresses it $gp-relative, where the ROM uses a far %hi/%lo pair. */
extern int D_00274EB0[];
extern int D_00634550[];
extern void iSignalSema(int handle);

/* The ring: an 8-byte header whose second word is the write index, followed
 * by 512 two-byte records (a code and an id). */
typedef struct {
    unsigned char code;
    unsigned char id;
} KernEvent;

typedef struct {
    int f0;
    int widx;
    KernEvent ent[512];
} KernEventRing;

extern KernEventRing D_00634558;
#include "syscall.h"

extern int _iWakeupThread(void);
extern int _iSuspendThread(void);

/* iWakeupThread / iSuspendThread are the same routine with a different
 * fallback callee and a different event code: do the kernel's
 * "current thread id" syscall, and if it is the caller's own id post an
 * event into the ring; otherwise hand off to the fallback. */
int iWakeupThread(int id) {
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iWakeupThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (D_00274EB0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_00634558.widx & 0x1FF;
    D_00634558.widx = i + 1;
    D_00634558.ent[i].code = 0;
    D_00634558.ent[i].id = r;
    iSignalSema(D_00634550[0]);
    return r;
}


/* Post an id into the ring and kick the kernel handle that drains it.
 * Rejects an out-of-range id, and does nothing before the ring is armed. */
int iRotateThreadReadyQueue(int id) {
    int i;
    if ((unsigned int)id >= 0x80) {
        goto fail;
    }
    if (D_00274EB0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_00634558.widx & 0x1FF;
    D_00634558.widx = i + 1;
    D_00634558.ent[i].code = 1;
    D_00634558.ent[i].id = id;
    iSignalSema(D_00634550[0]);
    return id;
}

int iSuspendThread(int id) {
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iSuspendThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (D_00274EB0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_00634558.widx & 0x1FF;
    D_00634558.widx = i + 1;
    D_00634558.ent[i].code = 2;
    D_00634558.ent[i].id = r;
    iSignalSema(D_00634550[0]);
    return r;
}

/* EE SIO byte pusher, putchar-style. 0x1000F130 is the SIO ISR (bit 15 =
 * TX FIFO full), 0x1000F180 the write-only TX FIFO byte port; both are
 * addressed off the I/O segment base held in `base`. The poll re-forms
 * the base each pass and spins while the FIFO is full, then pushes the
 * byte and returns it.
 *
 * Shape note (why the base variable and the do-while): both port
 * addresses must reach codegen as `base | offset` with the base formed
 * inside the loop. cse rewrites each ior to its constant WITH a
 * REG_EQUAL note, loop.c hoists both constants above the loop (which
 * keeps combine from folding the store address into the sb — the fold
 * that otherwise costs the register form), and reload then uses the
 * REG_EQUAL equivalence to rematerialise the TXFIFO constant at its
 * single use, back in the exit block reusing $3 — leaving a plain
 * (non-volatile) sb that gcc's own reorg can move into the jr delay
 * slot. Spelling either address as a bare constant, or latching the
 * base before the loop, loses one of those steps (measured:
 * scratchpad/func_001010C8_r5_notes.md). */
int kputchar(int c) {
    unsigned int base;

    do {
        base = 0x10000000;
    } while (*(volatile unsigned int *)(base | 0xF130) & 0x8000);

    *(unsigned char *)(base | 0xF180) = c;
    return c;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101100);

/* Newline translation on the way to the byte pusher: LF is sent as CR LF.
 * Both arms END in the call, so both get a tail `j` rather than a jal. */
void serialPutchar(int c) {
    if (c == 0xA) {
        kputchar(0xD);
        kputchar(0xA);
    } else {
        kputchar(c);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", ftoi);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", printfloat);

INCLUDE_RODATA("asm/nonmatchings/src/cod/vendor_100C90", D_00553748);
INCLUDE_RODATA("asm/nonmatchings/src/cod/vendor_100C90", D_00553750);
INCLUDE_RODATA("asm/nonmatchings/src/cod/vendor_100C90", D_00553758);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", _printf);

extern int _printf(int a0, void *va);

/* kprintf-shaped forwarder: home the register arguments and hand the
 * formatter a pointer to them. */
void kprintf(int a0, ...) {
    void *va = (char *)__builtin_next_arg(a0) - 0x38;
    _printf(a0, va);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", scePrintf);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", DIntr);

/* Leave a kernel critical section: re-enable interrupts, reporting whether
 * they had been enabled on entry. */
int EIntr(void) {
    int eie;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    EI();
    return eie != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", sceDeci2Open);

/* libkernl request wrappers: pack the arguments into a small block on the
 * stack and hand it to the kernel entry with a request code.  The block is
 * four words regardless of how many are filled -- that is what makes every
 * one of these frames 0x20 (0x10 of block + the saved $ra). */
extern void Deci2Call(int req, void *args);

void sceDeci2Close(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(2, args);
}

void sceDeci2ReqSend(int a0, signed char a1) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    Deci2Call(3, args);
}

void sceDeci2Poll(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(4, args);
}

void sceDeci2ExRecv(int a0, int a1, unsigned short a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    Deci2Call(-5, args);
}

void sceDeci2ExSend(int a0, int a1, unsigned short a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    Deci2Call(-6, args);
}

void sceDeci2ExReqSend(int a0, signed char a1) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    Deci2Call(-7, args);
}

void sceDeci2ExLock(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(-8, args);
}

void sceDeci2ExUnLock(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(-9, args);
}

void kputs(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(0x10, args);
}
