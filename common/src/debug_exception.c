#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", initLineTraceTable);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", traceLine);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", dispSource);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", display);

/* debugEEExceptionMain — hand-asm register-capture stub: snapshots the
 * caller's $t0-$t3 to a scratch frame (no C expression names $t0-$t3). */
__asm__(
    ".section .text\n"
    "    .set noreorder\n"
    "glabel debugEEExceptionMain\n"
    "    addiu $29, $29, -0x60\n"
    "    sd $8, 0x40($29)\n"
    "    sd $9, 0x48($29)\n"
    "    sd $10, 0x50($29)\n"
    "    sd $11, 0x58($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x60\n"
    "endlabel debugEEExceptionMain\n"
    "    nop\n"
    "    .set reorder\n"
);

void debugIOPExceptionMain(int a0, int a1, ...) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_assertMessage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_assert);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_SetExceptionMessage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debugExceptionInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debugIOPExceptionInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A4C58);

extern void func_00261188(int a0, void *a1, ...);
extern int D_0062CC58[];

void func_001A4DC0(int a0, int a1, int a2) {
    func_00261188(a0, D_0062CC58, a1, a2);
}

extern int D_0062CC48[];

void func_001A4DD8(int a0) {
    func_00261188(a0, D_0062CC48);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A4DE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5070);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5150);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5390);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A54C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5670);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5850);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5A90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5C08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5E88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A6128);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A62D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A63C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A6508);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A6908);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A6C68);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_0060C610;  /* stride 0x1C */

typedef struct {
    char               f_4;  /* 0x04 */
    char               f_5;  /* 0x05 */
} S_0062CCA0;

typedef struct {
    char               f_0;  /* 0x00 */
    char               f_1;  /* 0x01 */
} S_0062CC88;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060DA90;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060DD70;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060DDE0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060DE50;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060DEE0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060E090;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060E230;  /* stride 0x4 */

/* end struct shapes */
