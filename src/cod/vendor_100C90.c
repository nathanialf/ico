#include "common.h"
#include "r5900.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100C90);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100D68);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100E40);

/* Declared as arrays, not scalars: under -G 8 a 4-byte extern is small data
 * and gcc addresses it $gp-relative, where the ROM uses a far %hi/%lo pair. */
extern int D_00274EB0[];
extern int D_00634550[];
extern void func_00100550(int handle);

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

extern int func_00100460(void);
extern int func_001004A0(void);

/* func_00100F18 / func_00101030 are the same routine with a different
 * fallback callee and a different event code: do the kernel's
 * "current thread id" syscall, and if it is the caller's own id post an
 * event into the ring; otherwise hand off to the fallback. */
int func_00100F18(int id) {
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return func_00100460();
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
    func_00100550(D_00634550[0]);
    return r;
}


/* Post an id into the ring and kick the kernel handle that drains it.
 * Rejects an out-of-range id, and does nothing before the ring is armed. */
int func_00100FB0(int id) {
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
    func_00100550(D_00634550[0]);
    return id;
}

int func_00101030(int id) {
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return func_001004A0();
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
    func_00100550(D_00634550[0]);
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_001010C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101100);

extern void func_001010C8(int c);

/* Newline translation on the way to the byte pusher: LF is sent as CR LF.
 * Both arms END in the call, so both get a tail `j` rather than a jal. */
void func_001011B0(int c) {
    if (c == 0xA) {
        func_001010C8(0xD);
        func_001010C8(0xA);
    } else {
        func_001010C8(c);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_001011E8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101278);

INCLUDE_RODATA("asm/nonmatchings/src/cod/vendor_100C90", D_00553748);
INCLUDE_RODATA("asm/nonmatchings/src/cod/vendor_100C90", D_00553750);
INCLUDE_RODATA("asm/nonmatchings/src/cod/vendor_100C90", D_00553758);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_001013E0);

extern int func_001013E0(int a0, void *va);

/* kprintf-shaped forwarder: home the register arguments and hand the
 * formatter a pointer to them. */
void func_001019A8(int a0, ...) {
    void *va = (char *)__builtin_next_arg(a0) - 0x38;
    func_001013E0(a0, va);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_001019E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101A40);

/* Leave a kernel critical section: re-enable interrupts, reporting whether
 * they had been enabled on entry. */
int func_00101A88(void) {
    int eie;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    EI();
    return eie != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101AA0);

/* libkernl request wrappers: pack the arguments into a small block on the
 * stack and hand it to the kernel entry with a request code.  The block is
 * four words regardless of how many are filled -- that is what makes every
 * one of these frames 0x20 (0x10 of block + the saved $ra). */
extern void func_00100950(int req, void *args);

void func_00101AE8(int a0) {
    int args[4];
    args[0] = a0;
    func_00100950(2, args);
}

void func_00101B10(int a0, signed char a1) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    func_00100950(3, args);
}

void func_00101B40(int a0) {
    int args[4];
    args[0] = a0;
    func_00100950(4, args);
}

void func_00101B68(int a0, int a1, unsigned short a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    func_00100950(-5, args);
}

void func_00101BA0(int a0, int a1, unsigned short a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    func_00100950(-6, args);
}

void func_00101BD8(int a0, signed char a1) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    func_00100950(-7, args);
}

void func_00101C08(int a0) {
    int args[4];
    args[0] = a0;
    func_00100950(-8, args);
}

void func_00101C30(int a0) {
    int args[4];
    args[0] = a0;
    func_00100950(-9, args);
}

void func_00101C58(int a0) {
    int args[4];
    args[0] = a0;
    func_00100950(0x10, args);
}
