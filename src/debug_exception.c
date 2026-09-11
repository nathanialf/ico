#include "common.h"

/* debug_exception.h prototypes: their order is the inline tail's emission order;
   they precede the screen include so its three inline helpers follow them. */
void debugExceptionInit(void *workBuf);
void debugIOPExceptionInit(void);
void debug_assertMessage(char *file, int line, char *mes);
void debug_assert(char *file, int line);

#include "debug_exception_screen.c.inc"

extern int sceCdSync(int mode);
extern void sceFsReset(void);
extern int debugSceOpen(char *name, int flag);
extern void scePrintf();
extern int sceLseek(int fd, int offset, int whence);
extern int sceRead(int fd, void *buf, int size);
extern int sceClose(int fd);
extern char D_0061CF40[]; /* "TRTABLE.BIN" */
extern char D_0061CF50[]; /* the EUC-JP "cannot open the trace table" message */
extern char D_0061CF98[]; /* "No information.(\"%s\" can't read.)\n" */
extern char D_0061CFC0[]; /* the coloured "%d lines" report */
extern int D_0063B26C;    /* number of TRTABLE.BIN entries, this TU's .sdata */
/* Redeclared here (the debugExceptionInit block below carries the full note):
   the source-listing work buffer handed in at init. */
extern void *D_0063B268;

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

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", traceLine);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", dispSource);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", display);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugEEExceptionMain);

/* The EE exceptions the debug monitor traps: {cause code, printable name}.
 * The table is this TU's own .data -- it heads the 0x800-byte debug_exception
 * .data run at 0x004D9F70 -- and stays an extern until that run is carved. */
typedef struct {
    int code;
    char *name;
} DebugExcEntry;

extern DebugExcEntry D_004D9F70[11];
/* The source-listing work buffer handed in at init; initLineTraceTable and
 * traceLine read it back and pass it to sceRead as the read buffer. It sits in
 * src/debug's .sdata run, hence the gp-relative store. */
extern void *D_0063B268;
extern char D_0063B3F8[]; /* "num %d\n" -- this TU's own .sdata, uncarved */
extern void debugEEExceptionMain();
extern int SetDebugHandler();
extern void scePrintf();

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
extern char *strcpy(char *dst, const char *src);
extern void debug_StdPrintfDummy();

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
