#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { int f0; int *f4; int f8; int fC; int f10; char pad14[0x8]; } PObjA8B8Ent;

extern int func_0024A9C0(void *a0, int a1, int a2, int a3);

int func_0024AAC8(void *a0, int a1, int a2) {
    return func_0024A9C0(a0, a1, a2, 1);
}

extern char D_0062E668[];

int func_0024AAE8(void *a0, int a1) {
    return func_0024A9C0(a0, (int)D_0062E668, a1, 1);
}

extern char D_00716180[];
extern char D_00716380[];
extern int func_00246458();
extern int func_0024A348(void);

int func_0024AB10(int a0, void *a1, int a2) {
    int r;
    if (func_0024A348() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_00716180 + 0) = a0;
    *(int *)(D_00716180 + 4) = a2;
    r = func_00246458(D_00716380, 3, 0, D_00716180, 0x20, D_00716180, 0x20, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (a2 == 0) {
        *(unsigned char *)a1 = *(unsigned char *)D_00716180;
    } else if (a2 == 1) {
        *(unsigned short *)a1 = *(unsigned short *)D_00716180;
    } else if (a2 == 2) {
        *(int *)a1 = *(int *)D_00716180;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024AC00);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024ACE0);

extern int func_00100930(int a0);

int func_0024AE10(void) {
    int t = func_00100930(4) & 0x10000;
    return t != 0;
}

extern void func_00100920(int a0, int a1);
extern void func_002453C0();

int func_0024AE38(void) {
    if (func_00100930(4) & 0x40000) {
        func_00100920(4, 0x40000);
        ((void (*)(void))func_002453C0)();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024AE80);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0024AF90\n"
    ".type func_0024AF90, @function\n"
    "    .align 3\n"
    "func_0024AF90:\n"
    "    addiu $29, $29, -0x50\n"
    "    sd $31, 0x40($29)\n"
    "    sd $19, 0x30($29)\n"
    "    sd $18, 0x20($29)\n"
    "    sd $17, 0x10($29)\n"
    "    sd $16, 0x0($29)\n"
    "    mfc0 $17, $6\n"
    "    lui $19, %hi(D_0062E6A0)\n"
    "    lui $18, %hi(D_0062E6E0)\n"
    "    daddu $16, $0, $0\n"
    "    addiu $4, $19, %lo(D_0062E6A0)\n"
    "    nop\n"
    ".L002474E0:\n"
    "    bne $16, $17, .L002474F0\n"
    "    daddu $5, $16, $0\n"
    "    jal func_001019E0\n"
    "    nop\n"
    ".L002474F0:\n"
    "    mtc0 $16, $0\n"
    "    sync.p\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0 $8, $2\n"
    "    mfc0 $9, $3\n"
    "    mfc0 $6, $5\n"
    "    mfc0 $7, $10\n"
    "    daddu $5, $16, $0\n"
    "    jal func_001019E0\n"
    "    addiu $4, $18, %lo(D_0062E6E0)\n"
    "    addiu $16, $16, 0x1\n"
    "    slti $2, $16, 0x30\n"
    "    bnel $2, $0, .L002474E0\n"
    "    addiu $4, $19, %lo(D_0062E6A0)\n"
    "    ld $31, 0x40($29)\n"
    "    ld $19, 0x30($29)\n"
    "    ld $18, 0x20($29)\n"
    "    ld $17, 0x10($29)\n"
    "    ld $16, 0x0($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x50\n"
    ".size func_0024AF90, . - func_0024AF90\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0024B028\n"
    ".type func_0024B028, @function\n"
    "    .align 3\n"
    "func_0024B028:\n"
    "    srl $3, $5, 24\n"
    "    addiu $2, $0, 0x30\n"
    "    beq $3, $2, .L002475BC\n"
    "    sltiu $2, $3, 0x31\n"
    "    beqz $2, .L00247590\n"
    "    addiu $2, $0, 0x10\n"
    "    beq $3, $2, .L002475CC\n"
    "    sltiu $2, $3, 0x11\n"
    "    beqz $2, .L00247580\n"
    "    addiu $2, $0, 0x20\n"
    "    beqz $3, .L002475C0\n"
    "    andi $2, $3, 0xF\n"
    "    b .L002475D4\n"
    "    nop\n"
    ".L00247580:\n"
    "    beq $3, $2, .L002475C0\n"
    "    andi $2, $3, 0xF\n"
    "    b .L002475D4\n"
    "    nop\n"
    ".L00247590:\n"
    "    addiu $2, $0, 0x50\n"
    "    beq $3, $2, .L002475CC\n"
    "    sltiu $2, $3, 0x51\n"
    "    bnez $2, .L002475D4\n"
    "    addiu $2, $0, 0x60\n"
    "    beq $3, $2, .L002475CC\n"
    "    addiu $2, $0, 0x70\n"
    "    beq $3, $2, .L002475CC\n"
    "    nop\n"
    "    b .L002475D4\n"
    "    nop\n"
    ".L002475BC:\n"
    "    andi $2, $3, 0xF\n"
    ".L002475C0:\n"
    "    sltiu $2, $2, 0x8\n"
    "    beqz $2, .L002475D4\n"
    "    nop\n"
    ".L002475CC:\n"
    "    jr $31\n"
    "    addiu $2, $0, -0x1\n"
    ".L002475D4:\n"
    "    mtc0 $4, $5\n"
    "    mtc0 $5, $10\n"
    "    mtc0 $6, $2\n"
    "    mtc0 $7, $3\n"
    "    sync.p\n"
    "    tlbwr\n"
    "    sync.p\n"
    "    tlbp\n"
    "    sync.p\n"
    "    mfc0 $2, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_0024B028, . - func_0024B028\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0024B0E8\n"
    "    .type func_0024B0E8, @function\n"
    "    .align 3\n"
    "func_0024B0E8:\n"
    "    mfc0  $2, $6\n"
    "    slt   $2, $4, $2\n"
    "    bnez  $2, 1f\n"
    "    slti  $2, $4, 0x30\n"
    "    bnez  $2, 2f\n"
    "    nop\n"
    "1:\n"
    "    jr    $31\n"
    "    addiu $2, $0, -0x1\n"
    "2:\n"
    "    mtc0  $4, $0\n"
    "    mtc0  $5, $5\n"
    "    mtc0  $6, $10\n"
    "    mtc0  $7, $2\n"
    "    mtc0  $8, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    jr    $31\n"
    "    daddu $2, $4, $0\n"
    "    .size func_0024B0E8, . - func_0024B0E8\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0024B130\n"
    "    .type func_0024B130, @function\n"
    "    .align 3\n"
    "func_0024B130:\n"
    "    sltiu $2, $4, 0x30\n"
    "    bnez  $2, 1f\n"
    "    nop\n"
    "    jr    $31\n"
    "    addiu $2, $0, -0x1\n"
    "1:\n"
    "    mtc0  $4, $0\n"
    "    sync.p\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0  $2, $5\n"
    "    sw    $2, 0x0($5)\n"
    "    mfc0  $3, $10\n"
    "    sw    $3, 0x0($6)\n"
    "    mfc0  $2, $2\n"
    "    sw    $2, 0x0($7)\n"
    "    mfc0  $3, $3\n"
    "    sw    $3, 0x0($8)\n"
    "    jr    $31\n"
    "    daddu $2, $4, $0\n"
    "    .size func_0024B130, . - func_0024B130\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0024B180\n"
    "    .type func_0024B180, @function\n"
    "    .align 3\n"
    "func_0024B180:\n"
    "    mtc0  $4, $10\n"
    "    sync.p\n"
    "    tlbp\n"
    "    sync.p\n"
    "    mfc0  $4, $0\n"
    "    bgez  $4, 1f\n"
    "    nop\n"
    "    b     2f\n"
    "    addiu $4, $0, -0x1\n"
    "1:\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0  $2, $5\n"
    "    sw    $2, 0x0($5)\n"
    "    mfc0  $3, $2\n"
    "    sw    $3, 0x0($6)\n"
    "    mfc0  $2, $3\n"
    "    sw    $2, 0x0($7)\n"
    "2:\n"
    "    jr    $31\n"
    "    daddu $2, $4, $0\n"
    "    .size func_0024B180, . - func_0024B180\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0024B1D0\n"
    ".type func_0024B1D0, @function\n"
    "    .align 3\n"
    "func_0024B1D0:\n"
    "    addiu $29, $29, -0x30\n"
    "    sd $16, 0x10($29)\n"
    "    daddu $16, $4, $0\n"
    "    andi $2, $16, 0xFFF\n"
    "    bnez $2, .L00247720\n"
    "    sd $31, 0x20($29)\n"
    "    lui $2, (0xFFFFE >> 16)\n"
    "    addiu $3, $16, -0x1\n"
    "    ori $2, $2, (0xFFFFE & 0xFFFF)\n"
    "    sltu $2, $2, $3\n"
    "    bnez $2, .L00247728\n"
    "    lui $4, (0x70004000 >> 16)\n"
    ".L00247720:\n"
    "    b .L00247810\n"
    "    addiu $2, $0, -0x1\n"
    ".L00247728:\n"
    "    daddu $5, $29, $0\n"
    "    ori $4, $4, (0x70004000 & 0xFFFF)\n"
    "    ori $6, $29, 0x4\n"
    "    jal func_0024B180\n"
    "    ori $7, $29, 0x8\n"
    "    daddu $5, $2, $0\n"
    "    bgez $5, .L00247768\n"
    "    nop\n"
    "    beqz $16, .L00247810\n"
    "    daddu $2, $0, $0\n"
    "    mfc0 $5, $6\n"
    "    addiu $2, $5, 0x1\n"
    "    mtc0 $2, $6\n"
    "    sync.p\n"
    "    b .L002477B0\n"
    "    nop\n"
    ".L00247768:\n"
    "    bnez $16, .L002477B0\n"
    "    addiu $2, $5, -0x1\n"
    "    lui $3, (0xE0010000 >> 16)\n"
    "    sll $2, $2, 13\n"
    "    addu $6, $2, $3\n"
    "    mfc0 $2, $6\n"
    "    addiu $2, $2, -0x1\n"
    "    mtc0 $2, $6\n"
    "    mtc0 $5, $0\n"
    "    mtc0 $0, $5\n"
    "    mtc0 $6, $10\n"
    "    mtc0 $0, $2\n"
    "    mtc0 $0, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    b .L00247810\n"
    "    daddu $2, $0, $0\n"
    ".L002477B0:\n"
    "    lui $2, (0xFFFFF000 >> 16)\n"
    "    addiu $4, $16, 0x1000\n"
    "    ori $2, $2, (0xFFFFF000 & 0xFFFF)\n"
    "    lui $6, (0x70004000 >> 16)\n"
    "    and $4, $4, $2\n"
    "    sw $0, 0x0($29)\n"
    "    and $2, $16, $2\n"
    "    srl $4, $4, 6\n"
    "    srl $2, $2, 6\n"
    "    ori $4, $4, 0x1F\n"
    "    ori $2, $2, 0x1F\n"
    "    ori $6, $6, (0x70004000 & 0xFFFF)\n"
    "    sw $2, 0x4($29)\n"
    "    sw $4, 0x8($29)\n"
    "    mtc0 $5, $0\n"
    "    daddu $3, $0, $0\n"
    "    mtc0 $3, $5\n"
    "    mtc0 $6, $10\n"
    "    mtc0 $2, $2\n"
    "    mtc0 $4, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    daddu $2, $5, $0\n"
    ".L00247810:\n"
    "    ld $31, 0x20($29)\n"
    "    ld $16, 0x10($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x30\n"
    ".size func_0024B1D0, . - func_0024B1D0\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_00550880[];
extern void func_001001D0();
extern void func_0024B500(void);

void *func_0024B300(void *a0) {
    D_00550880[0] = (int)a0;
    func_001001D0(1, func_0024B500);
    func_001001D0(2, func_0024B500);
    func_001001D0(3, func_0024B500);
    return a0;
}

extern char D_0024B740[];
extern int D_00550888[];
extern void func_001001D0();
extern void func_001001E0();

int func_0024B360(int a0, int a1) {
    int old;
    int orig = a0;
    unsigned int err = 0xFFFFFFFF;
    if ((unsigned)(a0 - 1) >= 13) {
        return (int)err;
    }
    old = D_00550888[orig];
    D_00550888[orig] = a1;
    if ((unsigned)(a0 - 1) < 3) {
        func_001001D0(orig, (void *)D_0024B740);
    } else {
        func_001001E0(orig, (void *)D_0024B740);
    }
    return old;
}

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .align 3\n"
    "glabel func_0024B3E8\n"
    "    addiu      $3, $0, 0x74\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B3E8\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_005508C8[];
extern void func_0024B3E8(int x, int y);

void func_0024B3F8(void)
{
  int *p = D_005508C8;
  unsigned int i = 0;
  do
  {
    i++;
    func_0024B3E8(p[0], p[1]);
    p += 2;
  }
  while (i < 6);
}

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B448\n"
    "    addiu      $3, $0, 0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B448\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B458\n"
    "    addiu      $3, $0, -0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B458\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B468\n"
    "    addiu      $3, $0, 0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B468\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B478\n"
    "    addiu      $3, $0, -0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B478\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B488\n"
    "    addiu      $3, $0, 0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B488\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B498\n"
    "    addiu      $3, $0, -0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B498\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B4A8\n"
    "    addiu      $3, $0, 0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B4A8\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B4B8\n"
    "    addiu      $3, $0, -0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B4B8\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024B4C8\n"
    "    addiu      $3, $0, 0x59\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_0024B4C8\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B500);

void func_0024B880(int *a0, int *a1) {
    a1[2] = a0[4];
}

extern int D_00717880[];

int func_0024B890(int a0) {
    return D_00717880[a0];
}

int func_0024B8A8(int a0, int a1) {
    D_00717880[a0] = a1;
    return a1;
}

extern int D_00717758[];

void *func_0024B8C8(void) {
    return D_00717758;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B8D8);

extern int D_005508F8[];
extern int D_00717754[];
extern int func_00100250(int a0, int a1);
extern int func_00100AD8(int a0);

void func_0024BB58(void) {
    func_00100AD8(5);
    func_00100250(5, D_00717754[0]);
    D_005508F8[0] = 0;
}

int func_0024BB90(int a0, int a1) {
    int old = D_00717758[5];
    D_00717758[5] = a0;
    D_00717758[6] = a1;
    return old;
}

int func_0024BBA8(int a0, int a1) {
    int old = D_00717758[3];
    D_00717758[3] = a0;
    D_00717758[4] = a1;
    return old;
}

extern int D_00717764[];
extern int D_0071776C[];

int func_0024BBC0(int a0, int a1, int a2) {
    int off = a0 * 8;
    int *p;
    if (a0 >= 0) goto pos;
    a0 = D_00717764[0];
    goto done;
pos:
    a0 = D_0071776C[0];
done:
    off += a0;
    p = (int *)off;
    p[0] = a1;
    p[1] = a2;
}

void func_0024BBF0(int a0) {
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_00717764[0];
    } else {
        a0 = D_0071776C[0];
    }
    off += a0;
    *(int *)off = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BC18);

extern int func_0024BC18(int a0, int a1, int a2, int a3, int t0, int t1, int t2);

int func_0024BD50(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = func_0024BC18(a0, 0, a1, a2, a3, t0, t1);
  return v;
  asm __volatile__("" : : : "memory");
}

int func_0024BD90(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = func_0024BC18(a0, 1, a1, a2, a3, t0, t1);
  int new_var;
  new_var = v;
  return new_var;
  asm __volatile__("" : : : "memory");
}

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0024BDD0\n"
    ".type func_0024BDD0, @function\n"
    "    .align 3\n"
    "func_0024BDD0:\n"
    "    addiu $29, $29, -0x90\n"
    "    sd $16, 0x70($29)\n"
    "    sd $31, 0x80($29)\n"
    "    jal func_00101A88\n"
    "    nop\n"
    "    lui $3, %hi(D_00717758)\n"
    "    lw $7, %lo(D_00717758)($3)\n"
    "    addiu $16, $3, %lo(D_00717758)\n"
    "    lbu $2, 0x0($7)\n"
    "    andi $5, $2, 0xFF\n"
    "    beqz $5, .L002483E8\n"
    "    daddu $2, $0, $0\n"
    "    addiu $2, $5, 0xF\n"
    "    addiu $3, $0, -0x1\n"
    "    addiu $4, $5, 0x1E\n"
    "    slt $3, $3, $2\n"
    "    movn $4, $2, $3\n"
    "    daddu $6, $7, $0\n"
    "    sra $5, $4, 4\n"
    "    sb $0, 0x0($7)\n"
    "    blez $5, .L0024834C\n"
    "    daddu $4, $5, $0\n"
    "    daddu $3, $29, $0\n"
    "    nop\n"
    ".L00248330:\n"
    "    lq $2, 0x0($6)\n"
    "    addiu $4, $4, -0x1\n"
    "    addiu $6, $6, 0x10\n"
    "    sq $2, 0x0($3)\n"
    "    addiu $3, $3, 0x10\n"
    "    bnez $4, .L00248330\n"
    "    nop\n"
    ".L0024834C:\n"
    "    jal func_00100910\n"
    "    nop\n"
    "    lw $3, 0x8($29)\n"
    "    bgez $3, .L002483A8\n"
    "    nop\n"
    "    lw $2, 0x8($29)\n"
    "    lui $3, (0x7FFFFFFF >> 16)\n"
    "    ori $3, $3, (0x7FFFFFFF & 0xFFFF)\n"
    "    lw $4, 0x10($16)\n"
    "    and $5, $2, $3\n"
    "    slt $4, $5, $4\n"
    "    beqz $4, .L002483DC\n"
    "    sll $2, $5, 3\n"
    "    lw $3, 0xC($16)\n"
    "    addu $2, $2, $3\n"
    "    lw $6, 0x0($2)\n"
    "    beqz $6, .L002483DC\n"
    "    nop\n"
    "    lw $5, 0x4($2)\n"
    "    jalr $6\n"
    "    daddu $4, $29, $0\n"
    "    b .L002483DC\n"
    "    nop\n"
    ".L002483A8:\n"
    "    lw $5, 0x8($29)\n"
    "    lw $2, 0x18($16)\n"
    "    slt $2, $5, $2\n"
    "    beqz $2, .L002483DC\n"
    "    sll $2, $5, 3\n"
    "    lw $3, 0x14($16)\n"
    "    addu $2, $2, $3\n"
    "    lw $6, 0x0($2)\n"
    "    beqz $6, .L002483DC\n"
    "    nop\n"
    "    lw $5, 0x4($2)\n"
    "    jalr $6\n"
    "    daddu $4, $29, $0\n"
    ".L002483DC:\n"
    "    sync\n"
    "    ei\n"
    "    daddu $2, $0, $0\n"
    ".L002483E8:\n"
    "    ld $31, 0x80($29)\n"
    "    ld $16, 0x70($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x90\n"
    ".size func_0024BDD0, . - func_0024BDD0\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0024BEF8\n"
    ".type func_0024BEF8, @function\n"
    "    .align 3\n"
    "func_0024BEF8:\n"
    "    lui $25, (0xFFFFFFC0 >> 16)\n"
    "    ori $25, $25, (0xFFFFFFC0 & 0xFFFF)\n"
    "    blez $5, .L0024849C\n"
    "    addu $10, $4, $5\n"
    "    and $8, $4, $25\n"
    "    addiu $10, $10, -0x1\n"
    "    and $9, $10, $25\n"
    "    subu $10, $9, $8\n"
    "    srl $11, $10, 6\n"
    "    addiu $11, $11, 0x1\n"
    "    andi $9, $11, 0x7\n"
    "    beqz $9, .L00248448\n"
    "    srl $10, $11, 3\n"
    ".L0024842C:\n"
    "    sync\n"
    "    cache 0x18, 0x0($8)\n"
    "    sync\n"
    "    addiu $9, $9, -0x1\n"
    "    nop\n"
    "    bgtz $9, .L0024842C\n"
    "    addiu $8, $8, 0x40\n"
    ".L00248448:\n"
    "    beqz $10, .L0024849C\n"
    ".L0024844C:\n"
    "    addiu $10, $10, -0x1\n"
    "    sync\n"
    "    cache 0x18, 0x0($8)\n"
    "    sync\n"
    "    cache 0x18, 0x40($8)\n"
    "    sync\n"
    "    cache 0x18, 0x80($8)\n"
    "    sync\n"
    "    cache 0x18, 0xC0($8)\n"
    "    sync\n"
    "    cache 0x18, 0x100($8)\n"
    "    sync\n"
    "    cache 0x18, 0x140($8)\n"
    "    sync\n"
    "    cache 0x18, 0x180($8)\n"
    "    sync\n"
    "    cache 0x18, 0x1C0($8)\n"
    "    sync\n"
    "    bgtz $10, .L0024844C\n"
    "    addiu $8, $8, 0x200\n"
    ".L0024849C:\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_0024BEF8, . - func_0024BEF8\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_0024BFA4\n"
    "    jr         $31\n"
    "    addiu      $29, $29, -0x10\n"
    "endlabel func_0024BFA4\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    .global func_0024BFAC\n"
    "    .type func_0024BFAC, @function\n"
    "func_0024BFAC:\n"
    "    sd    $31, 0x0($29)\n"
    "    jal   func_00100550\n"
    "    daddu $4, $6, $0\n"
    "    sync\n"
    "    ei\n"
    "    ld    $31, 0x0($29)\n"
    "    jr    $31\n"
    "    addiu $29, $29, 0x10\n"
    "    .size func_0024BFAC, . - func_0024BFAC\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int func_001002A0(int a0, void *a1, int a2);
extern int func_00100520(int *self);
extern int func_00100530(int a0);
extern int func_00100560(int a0);
extern void func_0024BFA4(void);

void func_0024BFD0(unsigned short a0) {
    int buf[8];
    unsigned short id = a0;
    int r;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    r = func_00100520(buf);
    func_001002A0(id, (char *)func_0024BFA4 + 4, r);
    func_00100560(r);
    func_00100530(r);
}

extern int D_00717900[];
extern void func_00101A40(int *self);
extern void func_00101A88(void);
extern int func_0024CBC0(int a0);

int func_0024C038(int a0) {
    int ret;
    if (func_0024CBC0(1) != 0) {
        return 0;
    }
    (*(int (*)(void))func_00101A40)();
    ret = D_00717900[0];
    D_00717900[0] = a0;
    func_00101A88();
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C090);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C130);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C2C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C368);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C400);

extern int D_0055093C[];
extern void (*D_00717904[])(int);
extern int D_00717908[];
extern void func_0024C530();

int func_0024C480(int a0, int a1) {
    int ret;
    if (D_0055093C[0] < 0) {
        func_0024C530();
    }
    (*(int (*)(void))func_00101A40)();
    ret = (int)D_00717904[0];
    D_00717908[0] = a1;
    D_00717904[0] = (void (*)(int))a0;
    func_00101A88();
    return ret;
}

extern int D_00550924[];

void func_0024C4F0(void) {
    if (D_00717904[0] != 0 && D_00550924[0] == 0) {
        D_00717904[0](D_00717908[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C530);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C6B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C9B8);

extern int D_00550928[];
extern int D_00550980[];
extern int D_00551AD0[];
extern int func_0024C9B8(int a0);
extern void func_00100540(int sema);

/* Register the port, then read its first word back through uncached
 * space (bit 29) -- the peer writes it by DMA, so the cached copy is
 * stale. */
int func_0024CB28(void) {
    int *p;
    int v;
    if (func_0024C9B8(2) == 0) {
        return 0;
    }
    p = D_00550980;
    if (func_00246458(D_00551AD0, 0xE, 0, 0, 0, p, 4, 0, 0) < 0) {
        func_00100540(D_00550928[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    func_00100540(D_00550928[0]);
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CBC0);

extern int D_00550910[];
extern char D_00552348[];
extern char D_0062E818[];
extern void func_001019E0();
extern int func_00246648(char *a0);
extern void func_0024BFD0(unsigned short a0);

int func_0024CC60(int a0) {
    if (!a0) {
        if (D_00550910[0] > 0) func_001019E0(D_0062E818);
        while (func_00246648(D_00552348)) {
            func_0024BFD0(0x3C);
        }
        return 0;
    }
    return func_00246648(D_00552348);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CCD0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CE40);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D120);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D318);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D3E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D5C0);

extern int D_0055092C[];
extern int D_00551B00[];
extern int func_0024CCD0(int a0);

int func_0024D718(void) {
    int *p;
    int v;
    if (func_0024CCD0(1) == 0) {
        return 0;
    }
    p = D_00551B00;
    if (func_00246458(D_00552348, 3, 0, 0, 0, p, 4, 0, 0) < 0) {
        func_00100540(D_0055092C[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    func_00100540(D_0055092C[0]);
    return v;
}

int func_0024D7B0(void) {
    int *p;
    int v;
    if (func_0024CCD0(3) == 0) {
        return -1;
    }
    p = D_00551B00;
    if (func_00246458(D_00552348, 4, 0, 0, 0, p, 4, 0, 0) < 0) {
        func_00100540(D_0055092C[0]);
        return -1;
    }
    v = *(int *)((int)p | 0x20000000);
    func_00100540(D_0055092C[0]);
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D848);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D900);

extern int D_00552370[];
extern int D_00717BD8[];
extern int func_0024DD30(int a0, int a1, int a2, int a3, void *a4);

int func_0024D9B8(int a0, int a1, int a2) {
    D_00552370[0] = 0;
    return func_0024DD30(a0, a1, a2, 5, D_00717BD8);
}

int func_0024D9E8(int a0, void *a1) {
    D_00552370[0] = 1;
    return func_0024DD30(a0, 0, 0, 1, a1);
}

int func_0024DA20(int a0) {
    return func_0024DD30(a0, 0, 0, 9, D_00717BD8);
}

int func_0024DA50(int a0) {
    return func_0024DD30(a0, 0, 0, 4, D_00717BD8);
}

int func_0024DA80(void) {
    D_00552370[0] = 0;
    return func_0024DD30(0, 0, 0, 3, D_00717BD8);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024DAB8);

extern char D_0062E9C0[];

int func_0024DC40(void) {
    D_00552370[0] = 0;
    if (D_00550910[0] > 0) {
        func_001019E0(D_0062E9C0);
    }
    return func_0024DD30(0, 0, 0, 7, D_00717BD8);
}

extern char D_0062E9D8[];

int func_0024DC90(void) {
    D_00552370[0] = 1;
    if (D_00550910[0] > 0) {
        func_001019E0(D_0062E9D8);
    }
    return func_0024DD30(0, 0, 0, 8, D_00717BD8);
}

extern int D_0062E9F0[];

int func_0024DCE8(void) {
    if (D_00550910[0] > 0) {
        func_001019E0(D_0062E9F0);
    }
    return func_0024DD30(0, 0, 0, 6, D_00717BD8);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024DD30);

extern int D_0055238C[];
extern char D_0062EA48[];
extern PObjA8B8Ent D_00717C50[][4];
extern int func_001008C0(int a0);
extern int func_001008E0(void *a0, int a1);
extern void func_002642D8();
extern void func_0026F3A0(void *a0, void *a1);

void func_0024DE98(int a0, int a1) {
    struct { int *f0; int f4; int f8; int fC; char rest[0xF0]; } buf;
    int *p17 = D_00717C50[a0][a1].f4;
    int ret = func_001008C0(D_00717C50[a0][a1].fC);

    if (ret >= 0) {
        if (D_0055238C[0] != 0) {
            func_002642D8(D_0062EA48);
        }
    } else {
        int n = *p17 + 1;
        int v = D_00717C50[a0][a1].f8 + ((n & 1) << 5);
        int r;
        *p17 = n;
        func_0026F3A0(p17, (char *) p17 + 0x20);
        buf.f0 = p17;
        buf.f4 = v;
        buf.f8 = 0x20;
        buf.fC = 0;
        r = func_001008E0(&buf, 1);
        if (r == 0) {
            if (D_0055238C[0] != 0) {
                func_002642D8(D_0062EA48);
            }
        }
        D_00717C50[a0][a1].fC = r;
    }
}

extern int D_00552388[];
extern char D_0062EA90[];
extern char D_0062EAB8[];
extern int D_00717C00[];
extern char D_FFFF[];
extern int func_00246288();
extern int func_0024E108(int a0);
extern int func_0024F170(void);

int func_0024DFC8(int a0) {
    char *p;
    char *q;
    int i;
    int v;
    int hi;

    *(volatile int *)D_00552388 = 1;
    for (;;) {
        p = (char *)D_00717C00;
        func_00246288(p, 0x80000100, 0);
        if (*(int *)(p + 0x24) != 0) {
            break;
        }
        i = 0x10000;
        do {
            __asm__ volatile ("addiu %0,%0,%%lo(D_FFFF)" : "+r"(i));
        } while (i != -1);
    }
    {
        char *t = p + 0x28;
        q = p;
        p = t;
    }
    for (;;) {
        func_00246288(p, 0x80000101, 0);
        if (*(int *)(q + 0x4C) != 0) {
            break;
        }
        i = 0x10000;
        do {
            __asm__ volatile ("addiu %0,%0,%%lo(D_FFFF)" : "+r"(i));
        } while (i != -1);
    }
    v = func_0024F170();
    hi = v >> 8;
    if (hi != 4) {
        if (D_0055238C[0] != 0) {
            func_002642D8(D_0062EA90);
            func_002642D8(D_0062EAB8, 4, 0, hi, v & 0xFF);
        }
        return 0;
    }
    return func_0024E108(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E108);

extern int D_00552388[];
extern int D_00717C00[];
extern int D_00717F40[];

int func_0024E1A8(void) {
    int ret;
    int val;
    D_00717F40[0] = 0xF;
    ret = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_00717F40[3];
    if (val == 1) {
        D_00552388[0] = 0;
    }
    return val;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E228);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E410);

int func_0024E4C8(int a0, int a1) {
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_00717C50 + a1 * 0x1C + a0 * 0x70);
    func_0026F3A0((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}

int func_0024E528(int a0, int a1) {
    int ret = 0;
    if (D_00717C50[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(func_0024E4C8(a0, a1) + 0x58);
}

extern int func_00264128(char *a0, char *a1, int a2);

int func_0024E578(int a0, int a1, int a2) {
    int s0;
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    s0 = func_0024E4C8(a0, a1);
    func_00264128(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}

int func_0024E5F8(int a0, int a1) {
    unsigned char *p;
    if (D_00717C50[a0][a1].f10 == 0) return 0x63;
    p = (unsigned char *)func_0024E4C8(a0, a1);
    if (p[0x70] != 6) return p[0x70];
    if (p[0x71] == 2) return 5;
    return p[0x70];
}

/* Incomplete array, not a scalar: -G 8 would make a 1-byte extern
 * $gp-relative, where the ROM uses a far %hi/%lo pair. */
extern unsigned char D_0062EB68[];
extern void func_00265168(char *out, int v);

extern int D_00552390[];

void func_0024E670(unsigned int i, char *out) {
    if (i < 8) {
        func_00265168(out, D_00552390[i]);
        return;
    }
    *out = D_0062EB68[0];
}

int func_0024E6A8(int a0, int a1, int a2) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    ((unsigned char *)func_0024E4C8(a0, a1))[0x71] = a2;
    return 1;
}

int func_0024E710(int a0, int a1) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    return ((unsigned char *)func_0024E4C8(a0, a1))[0x71];
}

extern int D_005523B0[];

void func_0024E760(unsigned int i, char *out) {
    if (i < 4) {
        func_00265168(out, D_005523B0[i]);
        return;
    }
    *out = D_0062EB68[0];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E798);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E8B8);
