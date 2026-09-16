/* libc.a member mbtowc_r.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* MAIN.MAP member memchr.o starts at 0x002862EC inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
/* MAIN.MAP member memmove.o starts at 0x002863CC inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
#include "common.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern void fiprintf();
extern void abort(void);
extern long long strtol(void *a0, int a1, int a2);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);
extern void _fwalk(int a0, void *a1);
extern int memcpy(char *a0, char *a1, int a2);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int strcmp(int *p, int *buf);

int _mbtowc_r(int a0, int *a1, unsigned char *a2, int a3)
{
    int local;
    int *p = &local;
    if (a1 != 0)
        p = a1;
    if (a2 == 0)
        goto zero;
    if (a3 != 0)
        goto store;
    return -1;
zero:
    return 0;
store:
    *p = *a2;
    return *a2 != 0;
}

/* libc.a members memchr.o and memmove.o: hand-written R5900 assembly.
 * Both bodies use MMI (pcpyh, pcpyld, pnor, psubb, pand, pcpyud) and the
 * 128-bit lq/sq, which ee-gcc 2.9 has no C spelling for, so they are kept
 * as whole-function assembly, the same way this tree already keeps
 * sce/libc/machine/r5900/memset.c and strcat.c. */
__asm__("    .section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global memchr\n"
        "    .type memchr, @function\n"
        "memchr:\n"
        "    sltiu   $2, $6, 0x10\n"
        "    bnez    $2, .Lmemchr0028638C\n"
        "    andi    $5, $5, 0xFF\n"
        "    andi    $2, $4, 0xF\n"
        "    bnez    $2, .Lmemchr0028638C\n"
        "    daddu   $7, $4, $0\n"
        "    dsll    $3, $5, 8\n"
        "    lui     $2, (0x1010101 >> 16)\n"
        "    ori     $2, $2, (0x1010101 & 0xFFFF)\n"
        "    dsll    $2, $2, 16\n"
        "    ori     $2, $2, 0x101\n"
        "    dsll    $2, $2, 16\n"
        "    ori     $2, $2, 0x101\n"
        "    daddu   $10, $3, $5\n"
        "    lui     $3, (0x80808080 >> 16)\n"
        "    ori     $3, $3, (0x80808080 & 0xFFFF)\n"
        "    dsll    $3, $3, 16\n"
        "    ori     $3, $3, 0x8080\n"
        "    dsll    $3, $3, 16\n"
        "    ori     $3, $3, 0x8080\n"
        "    pcpyh   $8, $10\n"
        "    pcpyld  $9, $8, $8\n"
        "    daddu   $4, $2, $0\n"
        "    pcpyld  $8, $3, $3\n"
        "    .align 2\n"
        ".Lmemchr0028634C:\n"
        "    lq      $2, 0x0($7)\n"
        "    pxor    $2, $2, $9\n"
        "    pcpyld  $10, $4, $4\n"
        "    pnor    $3, $0, $2\n"
        "    psubb   $2, $2, $10\n"
        "    pand    $2, $2, $3\n"
        "    pand    $2, $2, $8\n"
        "    pcpyud  $3, $2, $9\n"
        "    or      $2, $2, $3\n"
        "    bnel    $2, $0, .Lmemchr0028638C\n"
        "    daddu   $4, $7, $0\n"
        "    addiu   $6, $6, -0x10\n"
        "    sltiu   $2, $6, 0x10\n"
        "    beqz    $2, .Lmemchr0028634C\n"
        "    addiu   $7, $7, 0x10\n"
        "    daddu   $4, $7, $0\n"
        "    .align 2\n"
        ".Lmemchr0028638C:\n"
        "    lui     $2, (0xFFFFFFFF >> 16)\n"
        "    addiu   $6, $6, -0x1\n"
        "    ori     $2, $2, (0xFFFFFFFF & 0xFFFF)\n"
        "    beq     $6, $2, .Lmemchr002863BC\n"
        "    nop\n"
        "    lui     $3, (0xFFFFFFFF >> 16)\n"
        "    ori     $3, $3, (0xFFFFFFFF & 0xFFFF)\n"
        "    .align 2\n"
        ".Lmemchr002863A8:\n"
        "    lbu     $2, 0x0($4)\n"
        "    beq     $2, $5, .Lmemchr002863C4\n"
        "    addiu   $6, $6, -0x1\n"
        "    bne     $6, $3, .Lmemchr002863A8\n"
        "    addiu   $4, $4, 0x1\n"
        "    .align 2\n"
        ".Lmemchr002863BC:\n"
        "    jr      $31\n"
        "    daddu   $2, $0, $0\n"
        "    .align 2\n"
        ".Lmemchr002863C4:\n"
        "    jr      $31\n"
        "    daddu   $2, $4, $0\n"
        "    .size memchr, . - memchr\n"
        "    .global memmove\n"
        "    .type memmove, @function\n"
        "memmove:\n"
        "    daddu   $8, $4, $0\n"
        "    sltu    $2, $5, $8\n"
        "    beqz    $2, .Lmemmove00286424\n"
        "    daddu   $3, $8, $0\n"
        "    addu    $7, $5, $6\n"
        "    sltu    $2, $8, $7\n"
        "    beqz    $2, .Lmemmove00286424\n"
        "    addiu   $2, $0, -0x1\n"
        "    addu    $3, $8, $6\n"
        "    addiu   $6, $6, -0x1\n"
        "    beq     $6, $2, .Lmemmove002864C8\n"
        "    daddu   $5, $7, $0\n"
        "    daddu   $4, $2, $0\n"
        "    .align 2\n"
        ".Lmemmove00286400:\n"
        "    addiu   $5, $5, -0x1\n"
        "    addiu   $3, $3, -0x1\n"
        "    lbu     $2, 0x0($5)\n"
        "    addiu   $6, $6, -0x1\n"
        "    nop\n"
        "    bne     $6, $4, .Lmemmove00286400\n"
        "    sb      $2, 0x0($3)\n"
        "    jr      $31\n"
        "    daddu   $2, $8, $0\n"
        "    .align 2\n"
        ".Lmemmove00286424:\n"
        "    sltiu   $2, $6, 0x20\n"
        "    bnel    $2, $0, .Lmemmove002864A0\n"
        "    addiu   $6, $6, -0x1\n"
        "    or      $2, $5, $3\n"
        "    andi    $2, $2, 0xF\n"
        "    bnel    $2, $0, .Lmemmove002864A0\n"
        "    addiu   $6, $6, -0x1\n"
        "    daddu   $7, $3, $0\n"
        "    .align 2\n"
        ".Lmemmove00286444:\n"
        "    lq      $3, 0x0($5)\n"
        "    addiu   $6, $6, -0x20\n"
        "    addiu   $5, $5, 0x10\n"
        "    sltiu   $4, $6, 0x20\n"
        "    sq      $3, 0x0($7)\n"
        "    addiu   $7, $7, 0x10\n"
        "    lq      $2, 0x0($5)\n"
        "    addiu   $5, $5, 0x10\n"
        "    sq      $2, 0x0($7)\n"
        "    beqz    $4, .Lmemmove00286444\n"
        "    addiu   $7, $7, 0x10\n"
        "    sltiu   $2, $6, 0x8\n"
        "    bnez    $2, .Lmemmove0028649C\n"
        "    daddu   $3, $7, $0\n"
        "    .align 2\n"
        ".Lmemmove0028647C:\n"
        "    ld      $3, 0x0($5)\n"
        "    addiu   $6, $6, -0x8\n"
        "    addiu   $5, $5, 0x8\n"
        "    sltiu   $2, $6, 0x8\n"
        "    sd      $3, 0x0($7)\n"
        "    beqz    $2, .Lmemmove0028647C\n"
        "    addiu   $7, $7, 0x8\n"
        "    daddu   $3, $7, $0\n"
        "    .align 2\n"
        ".Lmemmove0028649C:\n"
        "    addiu   $6, $6, -0x1\n"
        "    .align 2\n"
        ".Lmemmove002864A0:\n"
        "    addiu   $2, $0, -0x1\n"
        "    beq     $6, $2, .Lmemmove002864C8\n"
        "    daddu   $4, $2, $0\n"
        "    .align 2\n"
        ".Lmemmove002864AC:\n"
        "    lbu     $2, 0x0($5)\n"
        "    addiu   $6, $6, -0x1\n"
        "    addiu   $5, $5, 0x1\n"
        "    sb      $2, 0x0($3)\n"
        "    nop\n"
        "    bne     $6, $4, .Lmemmove002864AC\n"
        "    addiu   $3, $3, 0x1\n"
        "    .align 2\n"
        ".Lmemmove002864C8:\n"
        "    jr      $31\n"
        "    daddu   $2, $8, $0\n"
        "    .size memmove, . - memmove\n"
        "    .set reorder\n"
        "    .set at\n");

extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
