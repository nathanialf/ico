/* Vendor TU: libmpeg.a(mpc.o) - 0x2517D0..0x2564E0 (member attribution:
 * aug6-twin instruction hashing; boundary = first function of the member). */
#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002517D0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00251870);

int func_00251AB0(void) {
    return 1;
}

extern int D_005524A8[];
extern int D_005525C0[];
extern void func_002525E8(int a0, int a1);

void func_00251AB8(int a0, int a1, int a2) {
    int rounded = (a2 + 0x13) / 16 * 16;
    D_005524A8[0] = a1;
    D_005525C0[0] = rounded;
    func_002525E8(a1, rounded);
}

extern int func_00251ED0(int self);

int func_00251AF0(int *a0, unsigned int a1, int a2) {
    int *p = (int *)a0[0x40/4];
    a1 = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xB0/4] = 1;
    p[0xD8/4] = a1;
    p[0xE4/4] = a2;
    p[0xE0/4] = 0;
    p[0xDC/4] = 0;
    return func_00251ED0((int)a0);
}

void func_00251B38(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int new_var;
  p[0xE4 / 4] = a2;
  new_var = 0xD8;
  p[new_var / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  p[0xDC / 4] = 0;
 do { } while (0);
  p[0xB0 / 4] = 0;
  p[0xE0 / 4] = 0;
  func_00251ED0((int) self);
  asm __volatile__("" : : : "memory");
}

void func_00251B80(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int prod;
  p[0xE0 / 4] = a3 << 4;
  p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  prod = a2 * a3;
  p[0xE4 / 4] = prod;
  p[0xDC / 4] = a2 << 4;
  p[0xB0 / 4] = 0;
  func_00251ED0((int) self);
  asm __volatile__("" : : : "memory");
}

void func_00251BD0(void *a0, int a1, int a2, int a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x25] = a1;
    p[0x26] = a2;
    p[0x27] = a3;
}

void func_00251BE8(void *a0, int *a1, int *a2, int *a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    *a1 = *(int *)((char *)p + 0x94);
    *a2 = *(int *)((char *)p + 0x98);
    *a3 = *(int *)((char *)p + 0x9C);
}

int func_00251C08(int **a0) {
    return a0[0x10][0];
}

int func_00251C18(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    return *(int *)((char *)p + 0x4) == 0;
}

extern int D_005525C4[];
extern void func_002523A0(void);
extern void func_00252488(void);

void func_00251C28(int *a0) {
    int *p = (int *)a0[0x10];
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    a0[2] = 0;
    p[0x20] = -1;
    p[0x2B] = 0;
    func_00252488();
    D_005525C4[0] = 0;
    func_002523A0();
}

extern int D_005524C0[];
extern int D_005524C4[];
extern int D_005524CC[];
extern int D_005524D0[];
extern int D_005524D8[];
extern int D_005524DC[];

int func_00251C68(void) {
    if (D_005524C0[0] != 0) *(int *)(D_005524C0[0] + 0x28) = 0;
    if (D_005524CC[0] != 0) *(int *)(D_005524CC[0] + 0x28) = 0;
    if (D_005524D8[0] != 0) *(int *)(D_005524D8[0] + 0x28) = 0;
    if (D_005524C4[0] != 0) *(int *)(D_005524C4[0] + 0x28) = 0;
    if (D_005524D0[0] != 0) *(int *)(D_005524D0[0] + 0x28) = 0;
    if (D_005524DC[0] != 0) *(int *)(D_005524DC[0] + 0x28) = 0;
    return 1;
}

int func_00251CD0(void *a0, int a1, int a2, int a3) {
    char *p = *(char **)((char *)a0 + 0x40);
    char *q0 = p + 0xC;
    int *q = (int *)(q0 + a1 * 8);
    int old;
    p += a1 * 8;
    ((int *)p)[4] = a3;
    old = *q;
    *q = a2;
    return old;
}

void *func_00251CF8(void *a0, void *a1) {
    void *rv = 0;
    if (a0 != 0) {
        char *p = *(char **)((char *)a0 + 0x40);
        if (p != 0) {
            char *q0 = p + 0xC;
            int off = *(int *)a1 * 8;
            void *(*fn)(void *, void *, int) = *(void *(**)(void *, void *, int))(q0 + off);
            if (fn != 0) {
                char *e2 = p + off;
                rv = fn(a0, a1, *(int *)(e2 + 0x10));
            }
        }
    }
    return rv;
}

void func_00251D48(void *a0) {
    int buf[8];
    buf[0] = 1;
    func_00251CF8(a0, buf);
}

void func_00251D70(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x1C] = 1;
    *(long long *)((char *)p + 0x78) = a1;
}

void func_00251D88(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    *(int *)((char *)p + 0x70) = 0;
    *(long long *)((char *)p + 0x78) = 0;
}

extern void *D_005524A4[];

void func_00251D98(int a0) {
    int *q = *(int **)((char *)D_005524A4[0] + 0x40);
    q[0x36] = a0;
}

int func_00251DB0(int **a0) {
    return a0[0x10][0x33];
}

int func_00251DC0(int **a0) {
    return a0[0x10][0x34];
}

void *func_00251DD0(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

void *func_00251DE0(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

int func_00251DF0(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x40);
    int old = *(int *)((char *)p + 0xE8);
    *(int *)((char *)p + 0xE8) = a1;
    return old;
}

void func_00251E00(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    *(long long *)((char *)p + 0xF0) = a1;
    p[0x3E] = 1;
}

void func_00251E18(int *a0, int a1, int a2) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a1;
    a0[3] = a1;
}

void func_00251E30(int *a0) {
    a0[3] = a0[2];
}

void func_00251E40(int *a0) {
    a0[2] = a0[3];
}

extern int D_0062EC68[];
extern void func_00252590(void *a0);

int func_00251E50(unsigned int *a0, int a1, unsigned int a2) {
    unsigned int rounded;
    unsigned int total;
    rounded = ((a0[2] + a2 - 1) / a2) * a2;
    total = rounded + a1;
    if (a0[0] + a0[1] >= total) {
        a0[2] = total;
        return rounded;
    }
    func_00252590(D_0062EC68);
    return 0;
}

int func_00251EB8(int *a0) {
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00251ED0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252058);

extern int D_0055266C[];
extern int func_00252058(int a0, int a1, int a2);
extern int func_002521C0(int a0, int a1, int a2);

int func_00252180(int a0, int a1, int a2) {
    if (D_0055266C[0] != 3) {
        return func_002521C0(a0, a1, a2);
    }
    return func_00252058(a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002521C0);

extern void func_002523B0(int a0);
extern int D_005525C4[];

int func_00252330(int *self) {
    int *p = (int *)self[0x40 / 4];
    int ret = 0;
    if (p[1] != 0 && p[2] != 0) {
        func_002523B0(D_005525C4[0]);
        self[2] = D_005525C4[0] - p[0xAC / 4];
        p[1] = 0;
        ret = 1;
    }
    return ret;
}

extern int D_00552D70[];
extern void func_00254CF8(int a0);

void func_002523A0(void) {
    D_00552D70[0] = 0;
    func_00254CF8(1);
}

extern int D_005525DC[];
extern char D_0062ECE8[];
extern void func_00257A20();
extern void func_00257B38();

void func_002523B0(int a0) {
    int t;
    int d;
    int c;
    if (D_005525DC[0]) {
        func_00252590(D_0062ECE8);
        D_005525DC[0] = 0;
        return;
    }
    t = D_0055266C[0];
    if (t == 3) {
        func_00257A20(D_005524C4[0], a0 - 1);
    } else {
        func_00257B38(D_005524D0[0], D_005524DC[0], a0 - 1);
    }
    D_005525DC[0] = 0;
}

extern int D_00552498[];
extern int D_00552AB8[];

void func_00252438(void) {
    int v;
    func_00254CF8(1);
    v = D_00552498[0];
    D_00552AB8[0] = v;
    D_00552AB8[1] = v + 0x1800;
    *(void **)&D_00552AB8[0x50] = (void *)(v + 0x1B00);
    *(void **)&D_00552AB8[0x51] = (void *)(v + 0x3300);
    *(float *)((char *)D_00552AB8 + 0x280) = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252488);

extern int D_0062ED08[];
extern void func_002642D8(void *a0, ...);

void func_00252550(int a0) {
    func_002642D8(D_0062ED08, a0);
}

extern void func_00264DF8(void *a0, int a1, ...);

void func_00252560(int a0, int a1) {
    char buf[0x100];
    func_00264DF8(buf, a0, a1);
    func_00252590(buf);
}

void func_00252590(void *a0)
{
    char *p = D_005524A4[0];
    if (p != 0) {
        register int q = *(int *)(p + 0x40);
        if (q != 0) {
            register int r = *(int *)(q + 0xC);
            if (r != 0) {
                int local[2];
                local[0] = 0;
                local[1] = (int)a0;
                func_00251CF8((int)p, local);
                return;
            }
        }
    }
    func_00252550(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002525E8);

int func_002526C0(int *a0, int a1, int a2) {
    a0[0x4 / 4] = a1;
    a0[0x8 / 4] = a2;
    a0[0xC / 4] = a1 >> 4;
    a0[0x10 / 4] = a2 >> 4;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002526E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252838);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252B80);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252C68);


INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252D28);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252E90);

extern int D_0062ED78[];
extern void func_00252590(void *a0);

void func_00252F30(void) {
    func_00252590(D_0062ED78);
}

extern int D_0062EDA8[];

void func_00252F40(void) {
    func_00252590(D_0062EDA8);
}

extern int D_0062EDC0[];

void func_00252F50(void) {
    func_00252590(D_0062EDC0);
}

extern int D_0062EDF8[];

void func_00252F60(void) {
    func_00252590(D_0062EDF8);
}

extern void func_002586F8(void *a0);

void func_00252F70(int **a0) {
    func_002586F8((char *)a0[0x10] + 0x4C);
}

extern void func_002587E0(void *a0);

void func_00252F80(int **a0) {
    func_002587E0((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00252F90);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002532C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00253978);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00253D98);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00253F28\n"
    "    .type func_00253F28, @function\n"
    "    .align 3\n"
    "func_00253F28:\n"
    "    lw    $5, 0x14($4)\n"
    "    lw    $6, 0x18($4)\n"
    "    lw    $7, 0x8($4)\n"
    "    lw    $14, 0x0($4)\n"
    "    lw    $13, 0x4($4)\n"
    "    lw    $12, 0x10($4)\n"
    "    sll   $11, $12, 1\n"
    "    addiu $15, $0, -0x1\n"
    "    mtsab $13, 0x0\n"
    "1:\n"
    "    lq    $8, 0x0($5)\n"
    "    addi  $7, $7, -0x1\n"
    "    lq    $9, 0x0($6)\n"
    "    addu  $5, $5, $12\n"
    "    qfsrv $10, $9, $8\n"
    "    pextlb $8, $0, $10\n"
    "    pextub $9, $0, $10\n"
    "    sq    $8, 0x0($14)\n"
    "    addu  $6, $6, $12\n"
    "    sq    $9, 0x10($14)\n"
    "    bgtz  $7, 1b\n"
    "    addu  $14, $14, $11\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw    $7, 0xC($4)\n"
    "    and   $10, $15, $7\n"
    "    bnez  $10, 1b\n"
    "    daddu $15, $0, $0\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00253F28, . - func_00253F28\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00253FA0\n"
    ".type func_00253FA0, @function\n"
    "    .align 3\n"
    "func_00253FA0:\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    sll $11, $12, 1\n"
    "    mtsab $13, 0x0\n"
    "    addiu $24, $0, -0x1\n"
    ".L00250350:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $15, $0, -0x1\n"
    ".L00250358:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $9, $8, $8\n"
    "    pextlb $8, $0, $9\n"
    "    sq $8, 0x0($14)\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $12\n"
    "    addu $14, $14, $11\n"
    "    bgtz $7, .L00250358\n"
    "    addu $6, $6, $12\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $15, $7\n"
    "    bnez $10, .L00250358\n"
    "    daddu $15, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $24, .L00250350\n"
    "    daddu $24, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00253FA0, . - func_00253FA0\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254038\n"
    ".type func_00254038, @function\n"
    "    .align 3\n"
    "func_00254038:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $24, 0x10($4)\n"
    "    lq $8, 0x0($5)\n"
    "    sll $12, $24, 1\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    pextlb $8, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    beqz $7, .L0025045C\n"
    "    pextub $9, $0, $10\n"
    ".L0025040C:\n"
    "    addu $5, $5, $24\n"
    "    addu $6, $6, $24\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    qfsrv $2, $15, $10\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L0025040C\n"
    "    addu $14, $14, $12\n"
    ".L0025045C:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L0025040C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254038, . - func_00254038\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002540F0\n"
    ".type func_002540F0, @function\n"
    "    .align 3\n"
    "func_002540F0:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $11, $0, 0x1\n"
    "    sll $24, $12, 1\n"
    "    mtsab $13, 0x0\n"
    ".L002504A8:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    ori $11, $11, 0x8000\n"
    "    beqz $7, .L00250504\n"
    "    pextlb $15, $0, $8\n"
    ".L002504C8:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $10, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L002504C8\n"
    "    addu $14, $14, $24\n"
    ".L00250504:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L002504C8\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L002504A8\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_002540F0, . - func_002540F0\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002541C0\n"
    ".type func_002541C0, @function\n"
    "    .align 3\n"
    "func_002541C0:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    lw $9, 0x10($4)\n"
    "    sll $8, $9, 1\n"
    "    addiu $11, $0, -0x1\n"
    ".L0025057C:\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $10, $25\n"
    "    paddh $3, $15, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    addu $5, $5, $9\n"
    "    addu $6, $6, $9\n"
    "    bgtz $7, .L0025057C\n"
    "    addu $14, $14, $8\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $12, $11, $7\n"
    "    bnez $12, .L0025057C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_002541C0, . - func_002541C0\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254270\n"
    ".type func_00254270, @function\n"
    "    .align 3\n"
    "func_00254270:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $12, $0, -0x1\n"
    "    lw $3, 0x10($4)\n"
    "    sll $2, $3, 1\n"
    ".L00250628:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250630:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $3\n"
    "    addu $6, $6, $3\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $10, $10, $25\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250630\n"
    "    addu $14, $14, $2\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250630\n"
    "    daddu $11, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $12, .L00250628\n"
    "    daddu $12, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254270, . - func_00254270\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254328\n"
    ".type func_00254328, @function\n"
    "    .align 3\n"
    "func_00254328:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    lq $8, 0x0($5)\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    qfsrv $15, $8, $9\n"
    "    pextlb $8, $0, $10\n"
    "    pextub $9, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $15, $15, $10\n"
    "    pextlb $10, $0, $15\n"
    "    pextub $15, $0, $15\n"
    "    paddh $8, $8, $10\n"
    "    beqz $7, .L00250790\n"
    "    paddh $9, $9, $15\n"
    ".L0025071C:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 2\n"
    "    psrlh $3, $3, 2\n"
    "    sq $2, 0x0($14)\n"
    "    sll $10, $12, 1\n"
    "    sq $3, 0x10($14)\n"
    /* HISTORY: while this function lived in the old 96-function
     * vendor_252D28 chunk carve (TU stream starting at 0x252D28, mid-mpc.o),
     * ee-as 2.9-991111's R5900 short-loop-erratum pass mis-measured this
     * ~26-insn loop as 1 insn long and padded both backward branches with
     * 5 nops each, diverging from the ROM; a forward-defined label alias
     * kept the pass from seeing the (already-defined) target. The trigger
     * is a whole-stream configuration artifact, not simple stream position:
     * the loop assembles clean standalone, clean behind >12KB of synthetic
     * instruction/label/reloc filler, and clean in THIS TU (the true
     * libmpeg.a(mpc.o) span 0x2517D0..0x2564E0, which puts MORE content
     * before the loop than the old carve did) - yet 10 nops appeared under
     * the old carve's exact stream, and removing almost any single
     * preceding function from that stream made them vanish. With the carve
     * at the true member boundary the direct labels below assemble
     * byte-identical, so the alias is retired. If a future carve change
     * resurrects spurious nops here, the forward-defined-alias trick is in
     * git history (commit b5788929) as the workaround of last resort. */
    "    bgtz $7, .L0025071C\n"
    "    addu $14, $14, $10\n"
    ".L00250790:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L0025071C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254328, . - func_00254328\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254420\n"
    ".type func_00254420, @function\n"
    "    .align 3\n"
    "func_00254420:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $11, $0, 0x1\n"
    ".L002507D8:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addu $5, $5, $12\n"
    "    ori $11, $11, 0x8000\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    beqz $7, .L00250864\n"
    "    paddh $15, $9, $8\n"
    ".L00250810:\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $12\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    sll $8, $12, 1\n"
    "    psrlh $10, $10, 2\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250810\n"
    "    addu $14, $14, $8\n"
    ".L00250864:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L00250810\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L002507D8\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254420, . - func_00254420\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00254520\n"
    "    .type func_00254520, @function\n"
    "    .align 3\n"
    "func_00254520:\n"
    "    lw    $5, 0x14($4)\n"
    "    lw    $6, 0x18($4)\n"
    "    lw    $7, 0x8($4)\n"
    "    lw    $14, 0x0($4)\n"
    "    lw    $13, 0x4($4)\n"
    "    lw    $9, 0x10($4)\n"
    "    sll   $8, $9, 1\n"
    "    addiu $11, $0, -0x1\n"
    "    mtsab $13, 0x0\n"
    "1:\n"
    "    lq    $10, 0x0($5)\n"
    "    lq    $15, 0x0($6)\n"
    "    qfsrv $2, $15, $10\n"
    "    pextlb $10, $0, $2\n"
    "    pextub $15, $0, $2\n"
    "    lq    $2, 0x0($14)\n"
    "    lq    $3, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq    $2, 0x0($14)\n"
    "    sq    $3, 0x10($14)\n"
    "    addi  $7, $7, -0x1\n"
    "    addu  $5, $5, $9\n"
    "    addu  $14, $14, $8\n"
    "    bgtz  $7, 1b\n"
    "    addu  $6, $6, $9\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw    $7, 0xC($4)\n"
    "    and   $12, $11, $7\n"
    "    bnez  $12, 1b\n"
    "    daddu $11, $0, $0\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00254520, . - func_00254520\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002545C8\n"
    ".type func_002545C8, @function\n"
    "    .align 3\n"
    "func_002545C8:\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $12, $0, -0x1\n"
    "    lw $3, 0x10($4)\n"
    "    sll $2, $3, 1\n"
    "    mtsab $13, 0x0\n"
    ".L00250978:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250980:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $3\n"
    "    addu $6, $6, $3\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $9, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250980\n"
    "    addu $14, $14, $2\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250980\n"
    "    daddu $11, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $12, .L00250978\n"
    "    daddu $12, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_002545C8, . - func_002545C8\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254678\n"
    ".type func_00254678, @function\n"
    "    .align 3\n"
    "func_00254678:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    lq $8, 0x0($5)\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    sll $24, $12, 1\n"
    "    pextlb $8, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    beqz $7, .L00250ACC\n"
    "    pextub $9, $0, $10\n"
    ".L00250A4C:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    qfsrv $2, $15, $10\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    lq $10, 0x0($14)\n"
    "    lq $15, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L00250A4C\n"
    "    addu $14, $14, $24\n"
    ".L00250ACC:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250A4C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254678, . - func_00254678\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254760\n"
    ".type func_00254760, @function\n"
    "    .align 3\n"
    "func_00254760:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $11, $0, 0x1\n"
    "    sll $24, $12, 1\n"
    "    mtsab $13, 0x0\n"
    ".L00250B18:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    ori $11, $11, 0x8000\n"
    "    beqz $7, .L00250B8C\n"
    "    pextlb $15, $0, $8\n"
    ".L00250B38:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $10, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    psrlh $10, $10, 1\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $10, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250B38\n"
    "    addu $14, $14, $24\n"
    ".L00250B8C:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L00250B38\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L00250B18\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254760, . - func_00254760\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254848\n"
    ".type func_00254848, @function\n"
    "    .align 3\n"
    "func_00254848:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    lw $9, 0x10($4)\n"
    "    sll $8, $9, 1\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250C04:\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $10, $25\n"
    "    paddh $3, $15, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    lq $10, 0x0($14)\n"
    "    lq $15, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    addu $5, $5, $9\n"
    "    addu $6, $6, $9\n"
    "    bgtz $7, .L00250C04\n"
    "    addu $14, $14, $8\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $12, $11, $7\n"
    "    bnez $12, .L00250C04\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254848, . - func_00254848\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254928\n"
    ".type func_00254928, @function\n"
    "    .align 3\n"
    "func_00254928:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $12, $0, -0x1\n"
    "    lw $3, 0x10($4)\n"
    "    sll $2, $3, 1\n"
    ".L00250CE0:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250CE8:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $3\n"
    "    addu $6, $6, $3\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $10, $10, $25\n"
    "    psrlh $10, $10, 1\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $10, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250CE8\n"
    "    addu $14, $14, $2\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250CE8\n"
    "    daddu $11, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $12, .L00250CE0\n"
    "    daddu $12, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254928, . - func_00254928\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002549F8\n"
    ".type func_002549F8, @function\n"
    "    .align 3\n"
    "func_002549F8:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $24, 0x10($4)\n"
    "    addiu $12, $0, 0x1\n"
    "    lq $8, 0x0($5)\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    qfsrv $15, $8, $9\n"
    "    pextlb $8, $0, $10\n"
    "    pextub $9, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    mtsab $12, 0x0\n"
    "    qfsrv $15, $15, $10\n"
    "    pextlb $10, $0, $15\n"
    "    pextub $15, $0, $15\n"
    "    paddh $8, $8, $10\n"
    "    beqz $7, .L00250E90\n"
    "    paddh $9, $9, $15\n"
    ".L00250DEC:\n"
    "    addu $5, $5, $24\n"
    "    addu $6, $6, $24\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $12, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 2\n"
    "    psrlh $3, $3, 2\n"
    "    lq $10, 0x0($14)\n"
    "    lq $15, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sll $10, $24, 1\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L00250DEC\n"
    "    addu $14, $14, $10\n"
    ".L00250E90:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250DEC\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_002549F8, . - func_002549F8\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254B20\n"
    ".type func_00254B20, @function\n"
    "    .align 3\n"
    "func_00254B20:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $11, $0, 0x1\n"
    ".L00250ED8:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addu $5, $5, $12\n"
    "    ori $11, $11, 0x8000\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    beqz $7, .L00250F7C\n"
    "    paddh $15, $9, $8\n"
    ".L00250F10:\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $12\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    psrlh $10, $10, 2\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $10, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    sll $8, $12, 1\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250F10\n"
    "    addu $14, $14, $8\n"
    ".L00250F7C:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L00250F10\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L00250ED8\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00254B20, . - func_00254B20\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_00254CE0;

void func_00254C38(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $12, $0, 0x18\n"
        "lui $10, %%hi(D_00254CE0)\n"
        "addiu $10, $10, %%lo(D_00254CE0)\n"
        "lq $11, 0x0($10)\n"
        "1:\n"
        "lq $8, 0x0($5)\n"
        "addi $12, $12, -0x1\n"
        "lq $13, 0x0($6)\n"
        "addiu $4, $4, 0x10\n"
        "lq $9, 0x10($5)\n"
        "paddh $8, $8, $13\n"
        "lq $2, 0x10($6)\n"
        "pminh $8, $8, $11\n"
        "paddh $9, $9, $2\n"
        "pmaxh $8, $8, $0\n"
        "pminh $9, $9, $11\n"
        "addiu $5, $5, 0x20\n"
        "pmaxh $9, $9, $0\n"
        "addiu $6, $6, 0x20\n"
        "ppacb $10, $9, $8\n"
        "bnez $12, 1b\n"
        "sq $10, -0x10($4)\n"
        ".set reorder\n"
        ::: "$2","$8","$9","$10","$11","$12","$13","memory");
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00254C98);

/* No volatile here: the ROM has the sw in the jr delay slot, and ee-gcc only
 * fills a delay slot with a NON-volatile memref (with volatile it emits a bare
 * reorder-mode `j $31`, and the period assembler ee-as 2.9-991111 never fills
 * delay slots — the old "match" relied on modern gas doing the fill). */
void func_00254CF8(int a0) {
    int *reg = (int *)0x10002010;
    *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00254D20);

extern int func_002560D8(int a0);

int func_00254F08(void) {
    return func_002560D8(3);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00254F28);

extern int D_005525C8[];
extern int D_00552D70[];
extern int D_0062EEF0[];
extern void func_00252560(int a0, int a1);
extern int func_00256290(int a0);
extern void func_002563C8(int a0);

int func_002550B0(void) {
    int cont;
    int sum;
    unsigned int v;

    sum = 0;
    do {
        v = func_002560D8(0);
        switch (v) {
        case 0x22:
            cont = 1;
            break;
        case 0x23:
            cont = 1;
            sum += 0x21;
            break;
        case 0:
            {
                int r = func_00256290(0xB);
                if ((D_00552D70[0] != 0) && (r == 0xF)) {
                    func_002563C8(0xB);
                    cont = 1;
                } else {
                    func_00252560((int) D_0062EEF0, v);
                    D_005525C8[0] = 1;
                    return 1;
                }
            }
            break;
        default:
            sum += v;
            cont = 0;
            break;
        }
    } while (cont);
    return sum;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002551C0);

extern int D_005525E8[];
extern int D_005526FC[];
extern int D_0062EF48[];
extern int D_0062EF70[];
extern void func_00256648(void);
extern int func_002566B0(void);

int func_002552E8(int a0, int *a1, int *a2, int *a3) {
    int id;
    int m;
    int n;

    D_005525C8[0] = 0;
    func_00256648();
    id = func_00256290(0x20);
    if ((unsigned int) (id - 0x101) >= 0xAF) {
        func_00252560((int) D_0062EF48, id);
        return 2;
    }
    func_002563C8(0x20);
    m = func_002566B0();
    n = func_002550B0();
    *a2 = n;
    if (D_005525C8[0] != 0) {
        func_00252590(D_0062EF70);
        return 1;
    }
    *a1 = ((((m << 7) + (id & 0xFF)) - 1) * D_005525E8[0] + n) - 1;
    *a2 = 1;
    D_005526FC[0] = 1;
    a3[5] = 0;
    a3[4] = 0;
    a3[1] = 0;
    a3[0] = 0;
    a3[7] = 0;
    a3[6] = 0;
    a3[3] = 0;
    a3[2] = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00255410);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00255610);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002556E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00255C08);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00255C90);

extern void func_00255C08();
extern int func_002564E0(int a0);

void func_00255E10(char *a0, char *a1, void *a2, void *a3, int a4, int a5, int a6) {
    void *r;
    int r2;

    r = (void *)func_002560D8(2);
    if (a2 == 0) goto c1z;
    if (r == 0) { r2 = 0; goto c1c; }
    r2 = func_002564E0(a2);
    goto c1c;
c1z:
    r2 = 0;
c1c:
    func_00255C08(a0, a2, r, r2, a6);
    if (a4 != 0) {
        *(int *)a1 = func_00254F08();
    }
    r = (void *)func_002560D8(2);
    if (a3 == 0) goto c2z;
    if (r == 0) { r2 = 0; goto c2c; }
    r2 = func_002564E0(a3);
    goto c2c;
c2z:
    r2 = 0;
c2c:
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) >> 1;
    }
    func_00255C08(a0 + 4, a3, r, r2, a6);
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) * 2;
    }
    if (a4 != 0) {
        *(int *)(a1 + 4) = func_00254F08();
    }
}

extern int D_005524E4[];
extern int D_00552DC8[];

void func_00255F50(unsigned int a0) {
    *(volatile unsigned int *)0x10002000 = a0;
    D_005524E4[0] = D_00552DC8[a0 >> 28];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00255F80);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00256028);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002560D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_00256290);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2517D0", func_002563C8);

