#include "common.h"
#include "debug_exception.h"

/* The EE exceptions the debug monitor traps: {cause code, printable name}. */
typedef struct {
    int code;   /* 0x0 */
    char *name; /* 0x4 */
} DebugExcEntry;

/* The cause names, this TU's .rodata (not yet carved). */
extern char D_0061CD90[]; /* "TRAP exception" */
extern char D_0061CDA0[]; /* "ARITHMETIC OVERFLOW exception" */
extern char D_0061CDC0[]; /* "COPROCESSOR UNUSABLE exception" */
extern char D_0061CDE0[]; /* "RESERVE OPERATION exception" */
extern char D_0061CE00[]; /* "BUS ERROR exception LOAD OR STORE" */
extern char D_0061CE28[]; /* "BUS ERROR exception OPERATION" */
extern char D_0061CE48[]; /* "ADDRESS ERROR exception STORE" */
extern char D_0061CE68[]; /* "ADDRESS ERROR exception LOAD or OPERATION" */
extern char D_0061CE98[]; /* "TLB NOT MATCH exception STORE" */
extern char D_0061CEB8[]; /* "TLB NOT MATCH exception LOAD or OPERATION" */
extern char D_0061CEE8[]; /* "TLB MOD exception" */
/* The register names, this TU's .sdata (not yet carved), r0 to r31. */
extern char D_0063B368[], D_0063B360[], D_0063B358[], D_0063B350[]; /* " 0" at v0 v1 */
extern char D_0063B348[], D_0063B340[], D_0063B338[], D_0063B330[]; /* a0 a1 a2 a3 */
extern char D_0063B328[], D_0063B320[], D_0063B318[], D_0063B310[]; /* t0 t1 t2 t3 */
extern char D_0063B308[], D_0063B300[], D_0063B2F8[], D_0063B2F0[]; /* t4 t5 t6 t7 */
extern char D_0063B2E8[], D_0063B2E0[], D_0063B2D8[], D_0063B2D0[]; /* s0 s1 s2 s3 */
extern char D_0063B2C8[], D_0063B2C0[], D_0063B2B8[], D_0063B2B0[]; /* s4 s5 s6 s7 */
extern char D_0063B2A8[], D_0063B2A0[], D_0063B298[], D_0063B290[]; /* t8 t9 k0 k1 */
extern char D_0063B288[], D_0063B280[], D_0063B278[], D_0063B270[]; /* gp sp s8 ra */

/* This file's .data (VMA 0x4D9F70..0x4DA4C8), ahead of the screen include's.
   The monitor installs debugEEExceptionMain for every cause in the table. */
static DebugExcEntry excTable[11] = {
    {1, D_0061CEE8},  {2, D_0061CEB8},  {3, D_0061CE98},  {4, D_0061CE68},
    {5, D_0061CE48},  {6, D_0061CE28},  {7, D_0061CE00},  {10, D_0061CDE0},
    {11, D_0061CDC0}, {12, D_0061CDA0}, {13, D_0061CD90},
};

/* The report window: {value, name} word pairs, one pair per EE register,
   the values written at exception time and read back flat by display. */
static unsigned int regInfo[64] = {
    0, (unsigned int)D_0063B368, 0, (unsigned int)D_0063B360, 0, (unsigned int)D_0063B358,
    0, (unsigned int)D_0063B350, 0, (unsigned int)D_0063B348, 0, (unsigned int)D_0063B340,
    0, (unsigned int)D_0063B338, 0, (unsigned int)D_0063B330, 0, (unsigned int)D_0063B328,
    0, (unsigned int)D_0063B320, 0, (unsigned int)D_0063B318, 0, (unsigned int)D_0063B310,
    0, (unsigned int)D_0063B308, 0, (unsigned int)D_0063B300, 0, (unsigned int)D_0063B2F8,
    0, (unsigned int)D_0063B2F0, 0, (unsigned int)D_0063B2E8, 0, (unsigned int)D_0063B2E0,
    0, (unsigned int)D_0063B2D8, 0, (unsigned int)D_0063B2D0, 0, (unsigned int)D_0063B2C8,
    0, (unsigned int)D_0063B2C0, 0, (unsigned int)D_0063B2B8, 0, (unsigned int)D_0063B2B0,
    0, (unsigned int)D_0063B2A8, 0, (unsigned int)D_0063B2A0, 0, (unsigned int)D_0063B298,
    0, (unsigned int)D_0063B290, 0, (unsigned int)D_0063B288, 0, (unsigned int)D_0063B280,
    0, (unsigned int)D_0063B278, 0, (unsigned int)D_0063B270,
};

/* The message debug_SetExceptionMessage saves and the report prints back.
   The bytes pin 1025 to 1032 bytes before the next object's 16-byte
   alignment; the round kilobyte is ours. */
static char exceptionMessage[1024] = "";

/* This file's .bss (VMA 0x70FA80..0x70FA90), ahead of the screen include's:
   the quadword display stages one saved register in to print it as four
   words. */
static unsigned int regQuad[4];

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

extern char D_0061D0C8[]; /* "SRCFILE.TXT" */
extern char D_0061D0D8[]; /* the EUC-JP "cannot open the source file" message */
extern char D_0063B3A8[]; /* " \n" -- this TU's own .sdata, uncarved */
extern char D_0063B3B0[]; /* "  %x:" -- this TU's own .sdata, uncarved */
extern char D_0063B3B8[]; /* "%s\n" -- this TU's own .sdata, uncarved */

/* debug_exception.c:409-464.  Prints the source lines around the faulting
   address: opens SRCFILE.TXT, reads a kilobyte at the offset traceLine found
   and walks it line by line, highlighting the one whose listing address
   matches.  The reference arrives BY VALUE: the EE ABI hands a 16-byte struct
   over by invisible reference and the callee copies it into its own frame,
   which is the unaligned 16-byte copy at the head.

   The four debugExcDebugDisp() calls are the TU's compiled-out debug hook
   (see its definition above), one in the listing's code-free run 431-435
   and three in 444-449.  WHAT THE BYTES PIN: the hook in 431-435 is a
   zero-byte insn that sched2 ranks ahead of `n = 0` by LUID, so it takes
   the free issue slot beside the sceRead call and `n = 0` falls into the
   putString delay slot with the loop constants after the call, the ROM's
   order; the three in 444-449 lengthen every loop-wide live range by
   three, which global.c's allocno_compare needs for the ROM's s0-s8
   assignment (fd 12/90 against the "%s\n" high part 10/75 ties and fd,
   the lower allocno, takes $s4; the frame reference against &buf[1024]
   needs two or more).  WHAT THEY CANNOT PIN: that the developer's
   compiled-out debug code was this construct, or its exact lines. */

void dispSource(SrcRef ref, int lines)
{
    unsigned char buf[1024];
    char *line;
    int fd;
    int i;
    int n;
    int num;

    if (ref.offset < 0) {
        return;
    }

    waitCd();
    sceFsReset();

    if ((fd = debugSceOpen(D_0061D0C8, 1)) < 0) {
        scePrintf(D_0061D0D8, D_0061D0C8, -fd);

        putString(0xFF000000, D_0061CF98, D_0061D0C8);

        return;
    }

    waitCd();
    sceLseek(fd, ref.offset, 0);
    waitCd();

    sceRead(fd, buf, 1024);
    buf[1023] = 0;

    line = (char *)buf;
    debugExcDebugDisp();

    putString(0xFFFFFF00, D_0063B3A8);
    n = 0;

    for (i = 0; i < 1024; i++) {
        if (buf[i] == 0xA) {
            num = 0;

            buf[i] = 0;
            sscanf(line, D_0063B3B0, &num);
            debugExcDebugDisp();
            debugExcDebugDisp();
            debugExcDebugDisp();

            if (ref.addr == num) {
                *line = 0x87;
                putString(0x00FFFF00, D_0063B3B8, line);
            } else {
                putString(0xFFFFFF00, D_0063B3B8, line);
            }

            line = (char *)(&buf[i] + 1);
            if (++n >= lines) {
                break;
            }
        }
    }

    sceClose(fd);
    waitCd();
}

extern char D_0061D0A0[]; /* the eight-word register row format */
extern char D_0061D108[]; /* "page %d\n" */
extern char D_0061D120[]; /* the coloured exception banner */
extern char D_0061D148[]; /* "EPC %8.8x BADV %8.8x SR %8.8x\n" */
extern char D_0061D160[]; /* "sp %8.8x stack %d ra %d\n" */
extern char D_0061D188[]; /* "%s=%8.8x_%8.8x_%8.8x_%8.8x\n" */
extern char D_0063B3C0[]; /* "%s\n" for the saved message -- this TU's .sdata */
extern char D_0063B3C8[]; /* the coloured source-line header -- .sdata */
extern char D_0063B3D0[]; /* the first unwind row format -- .sdata */
extern char D_0063B3D8[]; /* the second unwind row format -- .sdata */
extern char D_0063B3E0[]; /* the third unwind row format -- .sdata */
extern char D_0063B3E8[]; /* the fourth unwind row format -- .sdata */

/* debug_exception.c:398-399, inlined into display: eight rows of four
   {name, value} register pairs.  The array is indexed by the counter, not
   walked by a pointer: the listing puts the pointer copy and its 32-byte step
   on the for line, which is loop.c's reduced giv, and only that giv's late
   preheader copy gives display the ROM's jal slot and register choice. */
static inline void dispRegs(unsigned int *regs)
{
    int i;

    for (i = 0; i < 8; i++) {
        putString(0xFFFFFF00, D_0061D0A0, regs[i * 8 + 1], regs[i * 8], regs[i * 8 + 3],
                  regs[i * 8 + 2], regs[i * 8 + 5], regs[i * 8 + 4], regs[i * 8 + 7],
                  regs[i * 8 + 6]);
    }
}

/* debug_exception.c:473-581.  One page of the exception screen.  Seven word
   arguments, so a0 to a3 then t0 to t3 under the EABI; the second (cause) is
   never read, which is why nothing is copied out of a1.  `regs` is the flat
   {value, name} pair array regInfo, two words per EE register, so
   regs[62] is the saved ra and regs[58] the saved sp. */
void display(int code, unsigned int cause, unsigned int epc, unsigned int badvaddr,
             unsigned int status, unsigned int *regs, int page)
{
    unsigned char buf[1024];
    unsigned char buf2[1024];
    SrcRef info;
    SrcRef cur;
    unsigned int *p;
    unsigned int ra;
    unsigned int sp;
    int i;

    scePrintf(D_0061D108, page);
    debug_ClearFontWindow();

    putString(0xFFFFFF00, D_0061D120);
    putString(0xFFFFFF00, D_0063B3C0, exceptionMessage);

    switch (page) {
    case 0:
        putString(0x40C0FF00, D_0063B3B8, excTable[code].name);

        putString(0x40C0FF00, D_0061D148, epc, badvaddr, status);

        dispRegs(regs);

        ra = regs[62] - 1;
        sp = regs[58];
        info = traceLine((char *)buf, epc);
        cur = info;
        scePrintf(D_0061D160, sp, info.stack, info.ra);

        putString(0xFFFFFF00, D_0063B3C8, buf);
        putString(0xFFFFFF00, D_0063B3B8, buf);

        if (cur.stack >= 0 && cur.ra >= 0) {
            unsigned int r = *(unsigned int *)(sp + cur.ra);
            sp += cur.stack;
            cur = traceLine((char *)buf2, r - 1);
            putString(0xE0F0FF00, D_0063B3D0, buf2);
        } else {
            cur = traceLine((char *)buf2, ra);
            putString(0xE0F0FF00, D_0063B3D0, buf2);
        }

        if (cur.stack >= 0 && cur.ra >= 0) {
            unsigned int r = *(unsigned int *)(sp + cur.ra);
            sp += cur.stack;
            cur = traceLine((char *)buf2, r - 1);
            putString(0xB0D0F000, D_0063B3D8, buf2);
        }

        if (cur.stack >= 0 && cur.ra >= 0) {
            unsigned int r = *(unsigned int *)(sp + cur.ra);
            sp += cur.stack;
            cur = traceLine((char *)buf2, r - 1);
            putString(0x80B0E000, D_0063B3E0, buf2);
        }

        if (cur.stack >= 0 && cur.ra >= 0) {
            unsigned int r = *(unsigned int *)(sp + cur.ra);
            sp += cur.stack;
            cur = traceLine((char *)buf2, r - 1);
            putString(0x5090D000, D_0063B3E8, buf2);
        }

        dispSource(info, 5);
        break;

    case 1:
        for (i = 0, p = regs; i < 16; i++, p += 2) {
            regQuad[0] = p[0];
            putString(0xFFFFFF00, D_0061D188, p[1], regQuad[3], regQuad[2], regQuad[1], regQuad[0]);
        }
        break;

    case 2:
        for (i = 0, p = regs + 32; i < 16; i++, p += 2) {
            regQuad[0] = p[0];
            putString(0xFFFFFF00, D_0061D188, p[1], regQuad[3], regQuad[2], regQuad[1], regQuad[0]);
        }
        break;
    }
}

/* One saved EE general register: the whole 128-bit quadword the exception
   entry hands over, of which only the low word is reported. */
typedef struct {
    unsigned int w[4];
} EeReg128;

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
            charScreen[i][j] = D_0063B388;
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
        regInfo[i * 2] = regs[i].w[0];
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

    scePrintf(D_0061D1C0, excTable[code].name, code);
    scePrintf(D_0061D1D8, cause);
    scePrintf(D_0063B3F0, epc);

    for (k = 0; k < 11; k++) {
        SetDebugHandler(excTable[k].code, 0);
    }

    iosPadEnable();

    resetPath();
    resetGS();

    clearDbgScreen();

    display(code, cause, epc, badvaddr, status, regInfo, 0);
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
                display(code, cause, epc, badvaddr, status, regInfo, 0);
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

/* The source-listing work buffer handed in at init; initLineTraceTable and
 * traceLine read it back and pass it to sceRead as the read buffer. It sits in
 * src/debug's .sdata run, hence the gp-relative store. */
extern char D_0063B3F8[]; /* "num %d\n" -- this TU's own .sdata, uncarved */
extern int SetDebugHandler();

inline void debugExceptionInit(void *workBuf)
{
    int i;

    D_0063B268 = workBuf;
    scePrintf(D_0063B3F8, sizeof(excTable) / sizeof(excTable[0]));
    for (i = 0; i < sizeof(excTable) / sizeof(excTable[0]); i++) {
        SetDebugHandler(excTable[i].code, debugEEExceptionMain);
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
            charScreen[i][j] = D_0063B388;
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

extern char D_0061D210[]; /* the coloured EUC-JP banner */
extern char D_0061D248[]; /* a rule of dashes */
extern char D_0061D278[]; /* the same rule, then the ANSI colour reset */
extern char D_0063B3B8[]; /* "%s\n" -- this TU's own .sdata, uncarved */

void debug_SetExceptionMessage(char *mes)
{
    strcpy(exceptionMessage, mes);
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
