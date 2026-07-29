#include "common.h"
#include "r5900.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100C90);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100D68);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100E40);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100F18);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00100FB0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101030);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101B68);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100C90", func_00101BA0);

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
