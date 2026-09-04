#include "common.h"




extern int D_00632B00[];
extern int D_00632B10[];
extern void sprintf();
extern void debug_FlushFontWindow();
extern void vsprintf();
/* debug_exception .rodata run 0x615060..0x615900 (byte-verified; stubs and
 * the matched initLineTraceTable's jtbl emit the rest) */
const char D_00615060[0x18] = "(addr 0x%08x <fl>) : ";
const char D_00615078[0x18] = "(addr 0x%08x <%2d>) : ";
extern const char D_00632AB8[];
extern const char D_00632AC0[];
extern const char D_00632AC8[];
extern const char D_00632AD0[];
extern void debug_StdPrintfDummy(char *fmt, ...);
extern int fptodp(float);

void initLineTraceTable(unsigned char *arg, int slot_size) {
    int is_float = 0;
    int row;

    switch (slot_size) {
    case 0:
        is_float = 1;
        slot_size = 4;
        debug_StdPrintfDummy((int)D_00615060, arg);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_StdPrintfDummy((int)D_00615078, arg, slot_size);
        break;
    default:
        return;
    }

    for (row = 0; row < 0x10 / slot_size; row++) {
        if (!is_float) {
            int col;
            for (col = 0x10 / (0x10 / slot_size) - 1; col >= 0; col--) {
                debug_StdPrintfDummy((int)D_00632AB8, arg[row * slot_size + col]);
            }
            debug_StdPrintfDummy((int)D_00632AC0);
        } else {
            debug_StdPrintfDummy((int)D_00632AC8, fptodp(((float *)arg)[row]));
        }
    }
    debug_StdPrintfDummy((int)D_00632AD0);
}

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

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_PrintFontWindow);

void debug_PrintfDummy(int a0, int a1, int a2, int a3, ...) {
}

void debug_PrintFontWindowDummy(int a0, int a1, ...) {
}

void debug_StdPrintfDummy(char *fmt, ...)
{
    (void)fmt;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_assert);

const char D_006150F0[0x10] = "%f %f %f %f\n";

extern int fptodp(float);

void debug_PrintMatrix(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = fptodp(arg[0]);
        int v1 = fptodp(arg[1]);
        int v2 = fptodp(arg[2]);
        int v3 = fptodp(arg[3]);
        debug_StdPrintfDummy((int)D_006150F0, v0, v1, v2, v3);
        arg += 4;
    }
    debug_StdPrintfDummy((int)D_00632AD0);
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_DispVu1FReg);

const char D_00615130[0x20] = "VI%02d:%08x %08x %08x %08x\n";
const char D_00615150[0x20] = "VS%02d:%08x %08x %08x %08x\n";
INCLUDE_RODATA("asm/nonmatchings/src/debug_exception", D_00615170);  /* 8B */

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugIOPExceptionInit);

const char D_00615188[0x20] = "Push '‚' to save debug options.";
const char D_006151A8[0x10] = "%c%s : %s(%d)";
const char D_006151B8[0x10] = "%c%s : %d";
const char D_006151C8[0x10] = "debug%s => %s\n";
const char D_006151D8[0x10] = "debug%s => %d\n";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_SelectCsvWindowVal);

void getLineBuffer(int a0, int a1, int a2)
{
    sprintf(a0, D_00632B10, a1, a2);
}

void func_001A7838(int a0)
{
    sprintf(a0, D_00632B00);
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7848);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7AD0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7BB0);

const char D_00615248[0x10] = "%s? Yes:O No:X";
const char D_00615258[0x10] = "now formatting";
const char D_00615268[0x10] = "Unformat";
const char D_00615278[0x18] = "now unformatting";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_mcRetErrCheck);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_selectFile);

/* "debug_mcSaveMainBlock:" + EUC-JP, raw bytes */
const char D_00615400[0x40] = "debug_mcSaveMainBlock:´û¤ËÀßÄê¤µ¤ì¤¿¿ô°Ê¾å¤Î¥Ç¡¼¥¿¤òÊÝÂ¸¤·¤Æ¤ë\n";
const char D_00615440[0x10] = "SAVE NO.";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_mcSaveMainBlock);

/* "debug_mcLoadMainBlock:" + EUC-JP, raw bytes */
const char D_00615488[0x40] = "debug_mcLoadMainBlock:´û¤ËÀßÄê¤µ¤ì¤¿¿ô°Ê¾å¤Î¥Ç¡¼¥¿¤òÊÝÂ¸¤·¤Æ¤ë\n";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_mcLoadMainBlock);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_mcDeleteFile);

const char D_006156A8[0x10] = "UNFORMAT";
/* memory-card menu table: {sdata-ptr, handler} pairs; literal fixed VMAs
 * (targets are mid-TU func stubs; becomes &func/&str spelling as they match) */
const unsigned int D_006156B8[0xC] = { 0x00632B88, 0x001A82B0, 0x00632B90, 0x001A80D0, 0x00632B98, 0x001A84F8, 0x00632BA0, 0x001AACA0, 0x006156A8, 0x001AAD88, 0x00632BA8, 0x001AAEA0 };
const char D_006156E8[0x10] = "Formatted";
const char D_006156F8[0x10] = "Unformatted";
const unsigned int D_00615708[0xA] = { 0xFFFFFFFF, 0x00FFFF00, 0x006156E8, 0xFFFFFFFE, 0x00FFFF00, 0x006156F8, 0x00000000, 0xFF222200, 0x00632BB0, 0x00000000 };

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8670);

const char D_00615758[0x18] = "REVERB DEPTH %d%%\n";
const char D_00615770[0x10] = "ADPCM LIST";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A88F0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_SESlotDisp);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8D40);

const char D_00615790[0x18] = "CD LOAD INFO COMMON";
const char D_006157A8[0x18] = "CD LOAD INFO STAGE";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8E30);

const char D_006157D8[0x18] = "CHARACTER PAD2 CONTROL";
const char D_006157F0[0x10] = ">>%8s = %d\n";
const char D_00615800[0x10] = "  %8s = %d\n";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_DispBox);

const unsigned int D_00615848[0xA] = { 0x00632C08, 0x006EDF60, 0x00632C10, 0x006EDF64, 0x00632C18, 0x006EDF68, 0x00632C50, 0x00632C48, 0x00000000, 0x00000000 };
const unsigned int D_00615870[0x4] = { 0x00000000, 0x00000010, 0x00000020, 0x00000080 };
const char D_00615880[0x10] = "move dst";
const char D_00615890[0x10] = "move src";
const char D_006158A0[0x10] = "move all";
const char D_006158B0[0x10] = "Collision Test";

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_DispBall);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A96D0);

