#include "common.h"

/* debug_exception.h prototypes: their order is the inline tail's emission order;
   they precede the screen include so its three inline helpers follow them. */
void debugExceptionInit(void *workBuf);
void debugIOPExceptionInit(void);
void debug_assertMessage(char *file, int line, char *mes);
void debug_assert(char *file, int line);

#include "debug_exception_screen.c.inc"

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", initLineTraceTable);
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

inline void debugExceptionInit(void *workBuf) {
    int i;

    D_0063B268 = workBuf;
    scePrintf(D_0063B3F8, sizeof(D_004D9F70) / sizeof(D_004D9F70[0]));
    for (i = 0; i < sizeof(D_004D9F70) / sizeof(D_004D9F70[0]); i++) {
        SetDebugHandler(D_004D9F70[i].code, debugEEExceptionMain);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugIOPExceptionMain);
inline void debugIOPExceptionInit(void) {}
inline void debug_assertMessage(char *file, int line, char *mes) {
    for (;;)
        ;
}
inline void debug_assert(char *file, int line) {
    for (;;)
        ;
}
