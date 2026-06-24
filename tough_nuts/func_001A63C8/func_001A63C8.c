#include "common.h"

extern void debug_assertMessage(int a0, ...);
extern int func_00260340(float);
extern char D_0060DA60[];
extern char D_0060DA78[];
extern const char D_00631CD8_a[] __asm__("D_0062CC00");
extern const char D_00631CE0_a[] __asm__("D_0062CC08");
extern const char D_00631CE8_a[] __asm__("D_0062CC10");
extern const char D_00631CF0_a[] __asm__("D_0062CC18");

/* switch jump table jtbl_0060DA90 migrated into debug_exception.o via the
 * per-TU .rodata carve in config/ico.aug6.yaml + migrate_rodata_to_functions. */
void initLineTraceTable(unsigned char *arg, int slot_size) {
    int is_float = 0;
    int row;

    switch (slot_size) {
    case 0:
        is_float = 1;
        slot_size = 4;
        debug_assertMessage((int)D_0060DA60, arg);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_assertMessage((int)D_0060DA78, arg, slot_size);
        break;
    default:
        return;
    }

    for (row = 0; row < 0x10 / slot_size; row++) {
        if (!is_float) {
            int col;
            for (col = 0x10 / (0x10 / slot_size) - 1; col >= 0; col--) {
                debug_assertMessage((int)D_00631CD8_a, arg[row * slot_size + col]);
            }
            debug_assertMessage((int)D_00631CE0_a);
        } else {
            debug_assertMessage((int)D_00631CE8_a, func_00260340(((float *)arg)[row]));
        }
    }
    debug_assertMessage((int)D_00631CF0_a);
}

extern int func_00265130(void *out, int x, void *args);
extern void debug_FlushFontWindow(int *a, int *b, int *c, void *p);

void traceLine(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    func_00265130(buf, x, args);
    debug_FlushFontWindow(a, b, c, buf);
}

void dispSource(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    func_00265130(buf, x, args);
    debug_FlushFontWindow(a, b, c, buf);
}

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

void debug_assertMessage(int a0, ...) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_assert);

extern const char D_0060DAF0_a[] __asm__("D_0060DAF0");

void debug_SetExceptionMessage(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = func_00260340(arg[0]);
        int v1 = func_00260340(arg[1]);
        int v2 = func_00260340(arg[2]);
        int v3 = func_00260340(arg[3]);
        debug_assertMessage((int)D_0060DAF0_a, v0, v1, v2, v3);
        arg += 4;
    }
    debug_assertMessage((int)D_00631CF0_a);
}

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

extern void *isysGObjRemoveObjDL(void);
extern void *func_0013E7E0(void *a0);
extern int func_001A4DE8(char *a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7, int a8, int *a9);
extern void actCommonStone(int a0);
extern char D_0029F060[];
extern char D_0060E1C0[];
extern int D_0062AEC8;

typedef struct { int f0; int f4; } DbgEnt;

int func_001A63C8(int a0) {
    DbgEnt buf[10];
    DbgEnt *bp = buf;
    int n = 0;
    int r;
    void *obj = isysGObjRemoveObjDL();
    if (obj != 0) {
        do {
            int t = *(int *)((char *)obj + 0xC);
            switch (t) {
            case 1:
            case 2:
            case 4:
            case 0x2E:
                bp[n].f0 = (int)(D_0029F060 + t * 0x64);
                bp[n].f4 = (int)obj;
                n++;
                break;
            }
            obj = func_0013E7E0(obj);
        } while (obj != 0);
    }
    if (a0 != 0) {
    } else {
        D_0062AEC8 = 0;
    }
    r = func_001A4DE8(D_0060E1C0, 0xA, 0x32, 0xB, buf, 8, 0, 1, n, &D_0062AEC8);
    if (D_0062AEC8 >= 0) {
        actCommonStone(buf[D_0062AEC8].f4);
    }
    return ~r ? 0 : -1;
}


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
