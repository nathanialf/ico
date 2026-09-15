/* libc.a member memset.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global memset\n"
        "    .type memset, @function\n"
        "    .align 3\n"
        "memset:\n"
        "    sltiu  $2, $6, 0x8\n"
        "    bnez   $2, .Lmemset002641D8002605E8\n"
        "    daddu  $3, $4, $0\n"
        "    andi   $2, $4, 0xF\n"
        "    bnez   $2, .Lmemset002641D8002605E8\n"
        "    daddu  $7, $4, $0\n"
        "    andi   $9, $5, 0xFF\n"
        "    sltiu  $10, $6, 0x20\n"
        "    daddu  $8, $9, $0\n"
        "    dsll   $3, $8, 8\n"
        "    or     $8, $3, $9\n"
        "    pcpyh  $3, $8\n"
        "    bnez   $10, .Lmemset002641D8002605D4\n"
        "    sltiu  $2, $6, 0x8\n"
        "    pcpyld $8, $3, $3\n"
        "    .align 2\n"
        ".Lmemset002641D8002605A4:\n"
        "    sq     $8, 0x0($7)\n"
        "    addiu  $6, $6, -0x20\n"
        "    addiu  $7, $7, 0x10\n"
        "    sltiu  $2, $6, 0x20\n"
        "    sq     $8, 0x0($7)\n"
        "    beqz   $2, .Lmemset002641D8002605A4\n"
        "    addiu  $7, $7, 0x10\n"
        "    b      .Lmemset002641D8002605D4\n"
        "    sltiu  $2, $6, 0x8\n"
        "    .align 2\n"
        ".Lmemset002641D8002605C8:\n"
        "    addiu  $6, $6, -0x8\n"
        "    addiu  $7, $7, 0x8\n"
        "    sltiu  $2, $6, 0x8\n"
        "    .align 2\n"
        ".Lmemset002641D8002605D4:\n"
        "    nop\n"
        "    nop\n"
        "    beql   $2, $0, .Lmemset002641D8002605C8\n"
        "    sd     $3, 0x0($7)\n"
        "    daddu  $3, $7, $0\n"
        "    .align 2\n"
        ".Lmemset002641D8002605E8:\n"
        "    lui    $2, 0xFFFF\n"
        "    addiu  $6, $6, -0x1\n"
        "    ori    $2, $2, 0xFFFF\n"
        "    beq    $6, $2, .Lmemset002641D800260620\n"
        "    nop\n"
        "    lui    $2, 0xFFFF\n"
        "    ori    $2, $2, 0xFFFF\n"
        "    .align 2\n"
        ".Lmemset002641D800260604:\n"
        "    sb     $5, 0x0($3)\n"
        "    addiu  $6, $6, -0x1\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    bne    $6, $2, .Lmemset002641D800260604\n"
        "    addiu  $3, $3, 0x1\n"
        "    .align 2\n"
        ".Lmemset002641D800260620:\n"
        "    jr     $31\n"
        "    daddu  $2, $4, $0\n"
        "    .size memset, . - memset\n"
        "    .set reorder\n"
        "    .set at\n");

extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern void memset(void *a0, int a1, int a2);
