#include "common.h"

extern void debug_StdPrintfDummy(int a0, ...);
extern int fptodp(float);
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
        debug_StdPrintfDummy((int)D_0060DA60, arg);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_StdPrintfDummy((int)D_0060DA78, arg, slot_size);
        break;
    default:
        return;
    }

    for (row = 0; row < 0x10 / slot_size; row++) {
        if (!is_float) {
            int col;
            for (col = 0x10 / (0x10 / slot_size) - 1; col >= 0; col--) {
                debug_StdPrintfDummy((int)D_00631CD8_a, arg[row * slot_size + col]);
            }
            debug_StdPrintfDummy((int)D_00631CE0_a);
        } else {
            debug_StdPrintfDummy((int)D_00631CE8_a, fptodp(((float *)arg)[row]));
        }
    }
    debug_StdPrintfDummy((int)D_00631CF0_a);
}

extern int vsprintf(void *out, int x, void *args);
extern void debug_FlushFontWindow(int *a, int *b, int *c, void *p);

void traceLine(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_FlushFontWindow(a, b, c, buf);
}

void dispSource(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_FlushFontWindow(a, b, c, buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_PrintFontWindow);

/* debug_PrintfDummy — hand-asm register-capture stub: snapshots the
 * caller's $t0-$t3 to a scratch frame (no C expression names $t0-$t3). */
__asm__(
    ".section .text\n"
    "    .set noreorder\n"
    "glabel debug_PrintfDummy\n"
    "    addiu $29, $29, -0x60\n"
    "    sd $8, 0x40($29)\n"
    "    sd $9, 0x48($29)\n"
    "    sd $10, 0x50($29)\n"
    "    sd $11, 0x58($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x60\n"
    "endlabel debug_PrintfDummy\n"
    "    nop\n"
    "    .set reorder\n"
);

void debug_PrintFontWindowDummy(int a0, int a1, ...) {
}

void debug_StdPrintfDummy(int a0, ...) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_assert);

extern const char D_0060DAF0_a[] __asm__("D_0060DAF0");

void debug_PrintMatrix(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = fptodp(arg[0]);
        int v1 = fptodp(arg[1]);
        int v2 = fptodp(arg[2]);
        int v3 = fptodp(arg[3]);
        debug_StdPrintfDummy((int)D_0060DAF0_a, v0, v1, v2, v3);
        arg += 4;
    }
    debug_StdPrintfDummy((int)D_00631CF0_a);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debugExceptionInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debugIOPExceptionInit);

extern void sprintf(int a0, void *a1, ...);
extern unsigned int strlen(char *buf);
extern int func_001A4DE8(char *a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7, int a8, int *a9);
extern char D_0060DBE8[];
extern char D_0062CC38[];
extern char D_0062CC40[];

void debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5,
                   int (*fn)(int, int), int a7) {
    char buf[count][0x25];
    int i;

    for (i = 0; i < count; i++) {
        if (fn != 0) {
            int r = fn(i, a7);
            sprintf(buf[i], D_0062CC38, i, r);
        } else {
            sprintf(buf[i], D_0062CC40, i);
        }
        if (strlen(buf[i]) >= 0x26) {
            buf[i][0x24] = 0;
            debug_StdPrintfDummy((int)D_0060DBE8);
        }
    }
    func_001A4DE8(a0, a1, a2, a3, (char *)buf, 0x25, 0, 0, count, a5);
}


extern void sprintf(int a0, void *a1, ...);
extern int D_0062CC58[];

void getLineBuffer(int a0, int a1, int a2) {
    sprintf(a0, D_0062CC58, a1, a2);
}

extern int D_0062CC48[];

void func_001A4DD8(int a0) {
    sprintf(a0, D_0062CC48);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A4DE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5070);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5150);

extern char D_0060DC90[], D_0060DCC0[], D_0060DCD8[], D_0060DCF0[];
extern char D_0060DD20[], D_0060DD40[], D_0060DD50[];
extern int D_002715D4[];
extern void debug_PrintfDummy(int a0, int a1, unsigned int a2, void *a3, void *a4);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_mcRetErrCheck);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A54C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_mcSaveMainBlock);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5850);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_mcDeleteFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5C08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A5E88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_SESlotDisp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A62D8);

extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *a0);
extern int func_001A4DE8(char *a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7, int a8, int *a9);
extern void actCommonStone(int a0);
extern char D_0029F060[];
extern char D_0060E1C0[];
extern int D_0062AEC8;

typedef struct { int f0; int f4; } DbgEnt;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", func_001A63C8);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_DispBox);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug_exception", debug_DispBall);

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
