#include "common.h"
#include "debug_exception.h"
#include "debug_exception_screen.c.inc"
#include "debug.h"
#include "GsBase.h"
#include <eekernel.h>
#include <sifdev.h>
#include <string.h>

extern int sceCdSync(int mode);
extern void sceFsReset(void);
extern char D_0061CF40[]; /* "TRTABLE.BIN" */
extern char D_0061CF50[]; /* the EUC-JP "cannot open the trace table" message */
extern char D_0061CF98[]; /* "No information.(\"%s\" can't read.)\n" */
extern char D_0061CFC0[]; /* the coloured "%d lines" report */
extern int D_0063B26C;    /* number of TRTABLE.BIN entries, this TU's .sdata */

/* One TRTABLE.BIN record: a code address and the byte offset of its line
   inside TRFILE.TXT.  Eight bytes, which is initLineTraceTable's size / 8. */
typedef struct {
    unsigned int addr; /* 0x0 */
    int pos;           /* 0x4 */
} TraceEntry;

/* Redeclared here (the debugExceptionInit block below carries the full note):
   the source-listing work buffer handed in at init. */
extern TraceEntry *D_0063B268;

/* The disc settle the debug monitor does around every raw file operation: wait
 * out the outstanding sceCdSync, then spin. The spin body is four nops so the
 * loop is real work rather than something the optimiser can drop. */
static inline void waitCd(void)
{
    int i;

    while (sceCdSync(1) != 0)
        ;
    i = 2000000;
    do {
        i--;
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
    } while (i != -1);
}

void initLineTraceTable(void)
{
    int fd;
    int size;

    waitCd();
    sceFsReset();
    if ((fd = debugSceOpen(D_0061CF40, 1)) < 0) {
        scePrintf(D_0061CF50, D_0061CF40, -fd);
        putString(0xFF000000, D_0061CF98, D_0061CF40);
        return;
    }
    size = sceLseek(fd, 0, 2);
    waitCd();
    sceLseek(fd, 0, 0);
    waitCd();
    sceRead(fd, D_0063B268, size);
    D_0063B26C = size / 8;
    scePrintf(D_0061CFC0, D_0063B26C);
    sceClose(fd);
    waitCd();
}

/* Compiled-out debug hook, the same construct icoMisc.c carries
   (partitionBarDebugDisp).  The Jan-2002 listing emits NO instruction for
   debug_exception.c:381, :382, :384 inside traceLine and :642 inside
   debugEEExceptionMain, and both functions need exactly the zero-byte insns
   those inlined empty bodies leave behind: ee-gcc emits `(use (const_int 0))`
   for an inlined call, an insn that takes a scheduling slot and a place in
   the live-range count while emitting nothing.  In traceLine the three of
   them carry the &buf[30] address's live range from 77 insns to 82, so
   global.c:allocno_compare scores it floor_log2(3)*3/82*10000 = 365 against
   the three &info.<field> addresses' floor_log2(2)*2/54*10000 = 370 and ranks
   those first, which is ROM's $s5/$s6/$s7/$s8; at 77 the buffer address
   scores 389, wins the rank and takes $s5, the four-register renaming that
   was the whole residual.  In debugEEExceptionMain the single one keeps
   `tex = 1` after the first display call, where ROM fills the jal delay slot
   with the page argument instead.  The name is ours: the listing records no
   symbol for an inlined empty body.  Evidence rung: ROM bytes
   (0x001B5170..0x001B5510 and 0x001B87C0..0x001B8C10) plus the listing's
   line map. */
static __inline__ void debugExcDebugDisp(void) {}

/* What traceLine parses out of one TRFILE.TXT line and hands to dispSource:
   the code address, the byte offset of the source line, the frame size and
   the offset of the saved return address, read with the format at
   D_0061D050. */
typedef struct {
    unsigned int addr; /* 0x0 */
    int offset;        /* 0x4 */
    int stack;         /* 0x8 */
    int ra;            /* 0xC */
} SrcRef;

/* debug_exception.c:329-393.  Turns a code address into a source-line
   reference by binary-searching TRTABLE.BIN for the last entry at or below it,
   then reading the matching TRFILE.TXT line back for the report.  The 16-byte
   record goes back BY VALUE: the caller hands the hidden result pointer in $a0
   and the callee returns it in $v0, which is why every `return info` is an
   unaligned 16-byte copy through that pointer. */

extern char D_0061D008[]; /* "TRFILE.TXT" */
extern char D_0061D018[]; /* the EUC-JP "cannot open the trace file" message */
extern char D_0061D050[]; /* "%08x:%010d:%04x:%04x\n" */
extern char D_0061D068[]; /* "%x:source Offset %d stack:%d ra:%d\n" */
extern char D_0061D090[]; /* "0x%x: %s\n" */
extern char D_0063B3A0[]; /* "%s" -- this TU's own .sdata, uncarved */

SrcRef traceLine(char *out, unsigned int addr)
{
    int pos = 0;
    int i = 0;
    int fd;
    int j;
    int n;
    char *src;
    SrcRef info = {-1, -1, -1, -1};
    unsigned char buf[1024];

    if (D_0063B268 == 0) {
        putString(0xFF000000, D_0061CF98, D_0061CF40);
        return info;
    }

    n = D_0063B26C;
    for (; i < n; i++) {
        if (addr < D_0063B268[i].addr) {
            break;
        }
        pos = D_0063B268[i].pos;
    }

    waitCd();
    sceFsReset();

    if ((fd = debugSceOpen(D_0061D008, 1)) < 0) {
        scePrintf(D_0061D018, D_0061D008, -fd);

        putString(0xFF000000, D_0061CF98, D_0061D008);

        return info;
    }

    waitCd();
    sceLseek(fd, pos, 0);
    waitCd();

    sceRead(fd, buf, 1024);

    for (j = 0; buf[j] != '\n'; j++)
        ;
    buf[j] = 0;

    sscanf((char *)buf, D_0061D050, &info.addr, &info.offset, &info.stack, &info.ra);
    /* The line's text starts past the 30-character "%08x:%010d:%04x:%04x\n"
       header the sscanf above just read.  gcse hoists this address into the
       block at :365 with the three &info.<field> addresses, which is why the
       listing has no instruction on this line. */
    src = (char *)&buf[30];
    info.addr = addr;
    info.stack = (short)info.stack;
    info.ra = (short)info.ra;
    scePrintf(D_0061D068, info.addr, info.offset, info.stack, info.ra);
    debugExcDebugDisp();
    debugExcDebugDisp();
    scePrintf(D_0061D090, info.addr, src);
    debugExcDebugDisp();

    if (out != 0) {
        sprintf(out, D_0063B3A0, src);
    }

    sceClose(fd);
    waitCd();

    return info;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug_exception", dispSource);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug_exception", display);

/* The EE exceptions the debug monitor traps: {cause code, printable name}.
 * The table is this TU's own .data -- it heads the 0x800-byte debug_exception
 * .data run at 0x004D9F70 -- and stays an extern until that run is carved. */
typedef struct {
    int code;   /* 0x0 */
    char *name; /* 0x4 */
} DebugExcEntry;

/* One saved EE general register: the whole 128-bit quadword the exception
   entry hands over, of which only the low word is reported. */
typedef struct {
    unsigned int w[4];
} EeReg128;

extern DebugExcEntry D_004D9F70[11];
/* The report window: {value, name} word pairs, one pair per EE register, with
   the names filled in from .data and the values written at exception time. */
extern unsigned int D_004D9FC8[64];
extern int D_0063B36C;    /* set once an exception is already being reported */
extern int D_0063AE74;    /* the "stop the game" flag the rest of the EE polls */
extern char D_0061D1A8[]; /* "called exception\n" */
extern char D_0061D1C0[]; /* "%s  (code = %d)\n" */
extern char D_0061D1D8[]; /* "CAUSE %p\n" */
extern char D_0061D1E8[]; /* "Frame buffer: %d\n" */
extern char D_0063B3F0[]; /* "EPC %p\n" -- this TU's own .sdata, uncarved */
extern void Emergency_DestroyAllThread(void);
extern int SetDebugHandler();
extern void iosPadEnable(void);
extern void ExecKeyInput(void);
extern void display(int code, unsigned int cause, unsigned int epc, unsigned int badvaddr,
                    unsigned int status, unsigned int *regs, int page);

/* debug_exception_screen.c.inc(476-477, 493-495): blank the character screen
   and put the cursor back at the top left.  Written as a helper because
   debugEEExceptionMain inlines it at two sites and each site needs its own
   pseudos; spelling the loop out by hand at both sites shares them. */
static inline void clearDbgScreen(void)
{
    int i;
    int j;

    for (i = 0; i < 26; i++) {
        for (j = 0; j < 256; j++) {
            D_0070FA90[i][j] = D_0063B388;
        }
    }
    D_0063B394 = 0;
    D_0063B398 = 0;
}

/* debug_exception_screen.c.inc(591-593, 598-600): put the frame the exception
   entry saved back into both texture buffers.  debugEEExceptionMain is the
   only caller and inlines it once, which is why the listing attributes all six
   calls to the include and gives the call site itself no instruction. */
static inline void restoreSavedFrame(void)
{
    SetTextureWithFrameBuffer(0);
    SetTexDrawEnvironment(0x3000);
    drawSprite(128, 128, 128, 128, -320, -112, 320, 112, 1);

    SetTextureWithFrameBuffer(0x1000);
    SetTexDrawEnvironment(0x4000);
    drawSprite(128, 128, 128, 128, -320, -112, 320, 112, 1);
}

/* debug_exception_screen.c.inc(579-582): put the saved frame back on screen. */
static inline void dispBack(int page, int tex)
{
    if (page != 0) {
        SetDrawnTextureEnvironment(0x4000);
    } else {
        SetDrawnTextureEnvironment(0x3000);
    }
    RestoreNormalDrawEnvironment(D_0028F4F0, buffer_ID, 0);
    drawSprite(128, 128, 128, 128, -320, -112, 320, 112, tex);
}

/* debug_exception.c:599-663.  The EE exception handler the monitor installs
   for every trapped cause: freeze the game, copy the register image into the
   report window, draw the saved frame back over the screen and then loop on
   the pad, paging through the three report screens. */
void debugEEExceptionMain(int arg0, unsigned int cause, unsigned int epc, unsigned int badvaddr,
                          unsigned int status, EeReg128 *regs)
{
    int code = (cause >> 2) & 0xF;
    int sel = 0;
    int page;
    int tex;
    unsigned int i;
    unsigned int k;
    int spin;

    if (D_0063B36C != 0) {
        return;
    }
    D_0063B36C = 1;
    Emergency_DestroyAllThread();
    D_0063AE74 = 1;

    scePrintf(D_0061D1A8);

    /* The report starts on page 1.  The store sits inside the copy loop, at
       listing line 617: it is loop invariant, so loop.c:move_movables lifts it
       into the preheader with emit_insn_before(..., loop_start), i.e. AFTER
       the gcse inserts that end this block, and only then does it carry a
       higher LUID than the hoisted `code * 8`.  Written before the loop it
       has the lower LUID, haifa's rank_for_schedule tie-break takes it for
       the slot between Emergency_DestroyAllThread and scePrintf, and the two
       values and their frame slots come out swapped against ROM. */
    for (i = 0; i < 32; i++) {
        D_004D9FC8[i * 2] = regs[i].w[0];
        page = 1;
    }

    spin = 1000000000;
    do {
        spin--;
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
    } while (spin != -1);

    restoreSavedFrame();

    syncGS();

    initLineTraceTable();

    scePrintf(D_0061D1C0, D_004D9F70[code].name, code);
    scePrintf(D_0061D1D8, cause);
    scePrintf(D_0063B3F0, epc);

    for (k = 0; k < 11; k++) {
        SetDebugHandler(D_004D9F70[k].code, 0);
    }

    iosPadEnable();

    resetPath();
    resetGS();

    clearDbgScreen();

    display(code, cause, epc, badvaddr, status, D_004D9FC8, 0);
    debugExcDebugDisp();

    tex = 1;

    for (;;) {
        if (D_0028F8F0[0]._4 & 0x20) {
            sel = page;
            if (sel >= 3) {
                sel = 0;
            }
            page = sel + 1;
            clearDbgScreen();
            if (sel != 0) {
                putString(0xFFFFFF00, D_0061D1E8, sel - 1);
            } else {
                display(code, cause, epc, badvaddr, status, D_004D9FC8, 0);
            }
        }

        if (sel != 0) {
            dispBack(sel - 1, tex);
        } else {
            dispBack(0, tex);
            saveBack();
        }

        baseFunc();
        syncGS();
        ExecKeyInput();
    }
}

extern DebugExcEntry D_004D9F70[11];
/* The source-listing work buffer handed in at init; initLineTraceTable and
 * traceLine read it back and pass it to sceRead as the read buffer. It sits in
 * src/debug's .sdata run, hence the gp-relative store. */
extern char D_0063B3F8[]; /* "num %d\n" -- this TU's own .sdata, uncarved */
extern int SetDebugHandler();

inline void debugExceptionInit(void *workBuf)
{
    int i;

    D_0063B268 = workBuf;
    scePrintf(D_0063B3F8, sizeof(D_004D9F70) / sizeof(D_004D9F70[0]));
    for (i = 0; i < sizeof(D_004D9F70) / sizeof(D_004D9F70[0]); i++) {
        SetDebugHandler(D_004D9F70[i].code, debugEEExceptionMain);
    }
}

/* "IOP DEAD\n" -- this TU's own .rodata, uncarved. */
extern char D_0061D200[];

void debugIOPExceptionMain(void)
{
    int i, j;

    resetPath();
    resetGS();
    for (i = 0; i < 26; i++) {
        for (j = 0; j < 256; j++) {
            D_0070FA90[i][j] = D_0063B388;
        }
    }
    D_0063B394 = 0;
    D_0063B398 = 0;
    putString(0xFFFFFF00, D_0061D200);
    for (;;) {
        SetDrawEnvironment(1);
        dispBase();
        drawWin();
        syncGS();
    }
}

/* The 0x200-byte message buffer the exception screen prints back; it heads the
 * debug_exception .data run just past the cause table. */
extern char D_004DA0C8[];
extern char D_0061D210[]; /* the coloured EUC-JP banner */
extern char D_0061D248[]; /* a rule of dashes */
extern char D_0061D278[]; /* the same rule, then the ANSI colour reset */
extern char D_0063B3B8[]; /* "%s\n" -- this TU's own .sdata, uncarved */

void debug_SetExceptionMessage(char *mes)
{
    strcpy(D_004DA0C8, mes);
    debug_StdPrintfDummy(D_0061D210);
    debug_StdPrintfDummy(D_0061D248);
    debug_StdPrintfDummy(D_0063B3B8, mes);
    debug_StdPrintfDummy(D_0061D278);
}

inline void debugIOPExceptionInit(void) {}

inline void debug_assertMessage(char *file, int line, char *mes)
{
    for (;;)
        ;
}

inline void debug_assert(char *file, int line)
{
    for (;;)
        ;
}
