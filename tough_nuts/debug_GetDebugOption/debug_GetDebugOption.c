#include "common.h"

typedef struct { int w[6]; } AssertRec;
extern AssertRec D_006DE110[];

int debug_Assert(int a0) {
    return D_006DE110[a0].w[0];
}

extern void vsprintf(char *buf, const char *fmt, void *va);
extern void func_001AACE0(char *a0, int a1, char *a2);
extern void __assert(char *a0, int a1, char *a2);
extern void func_001AAD00(char *a0, int a1);
extern char D_0060D3B0[];
extern char D_0062CB40[];
extern char D_0062CB48[];

void debug_openLog(const char *fmt, ...) {
    char buf[0x100];
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    func_001AACE0(D_0060D3B0, 0x4F4, buf);
    __assert(D_0060D3B0, 0x4F4, D_0062CB40);
    func_001AAD00(D_0060D3B0, 0x4F5);
    __assert(D_0060D3B0, 0x4F5, D_0062CB48);
}

extern int D_0062ACCC;

void debug_LogPrintf(void) {
    char buf[0x100];
    D_0062ACCC = -1;
}

extern void vsprintf(char *buf, const char *fmt, void *va);
extern void *strlen(char *buf);
extern void sceWrite(int target, char *buf, void *info);

void debug_SaveDebugOptionFile(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = strlen(buf);
    sceWrite(D_0062ACCC, buf, info);
}

/* m2c scaffold from asm/aug6/nonmatchings/common/src/debug/debug_GetDebugOption.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern void debug_StdPrintfDummy();
extern int debugSceOpen(char *a0, int a1);
extern int debugSceClose(int a0);
extern void sprintf(char *buf, const char *fmt, ...);
extern char D_0060D4E0[], D_0060D520[], D_0060D560[], D_0060D578[], D_0060D5B0[];
extern char D_0062CB60[], D_0062CB68[];
typedef struct { int f0; int f4; int *f8; int fC; int f10; int f14; int f18; } DbgOpt;
extern DbgOpt D_0060C610[];

void debug_GetDebugOption(void) {
    char buf[256];
    int neg;
    DbgOpt *e;

    debug_StdPrintfDummy(D_0060D520);
    neg = (unsigned int) debugSceOpen(D_0060D560, 0x602) >> 31;
    if (neg != 0) {
        debug_StdPrintfDummy(D_0060D578);
    } else {
        e = D_0060C610;
        do {
            int *p;
            sprintf(buf, D_0062CB60, e->f0);
            sceWrite(neg, buf, strlen(buf));
            p = e->f8;
            e++;
            sprintf(buf, D_0062CB68, *p);
            sceWrite(neg, buf, strlen(buf));
        } while (e < (DbgOpt *) ((char *) D_0060C610 + 0x754));
        debugSceClose(neg);
        debug_StdPrintfDummy(D_0060D5B0);
    }
    debug_StdPrintfDummy(D_0060D4E0);
    debug_LogPrintf();
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SetDmaCallback);

extern unsigned int D_0062ACD4;
extern int func_00100230(int a, int b, int c);
extern void RemoveDmacHandler(int a, int b);
extern void func_001A7C20(void);
extern void func_00100B40(int a);

void debug_VariableInit(void)
{
    if ((int)D_0062ACD4 != -1) {
        RemoveDmacHandler(1, D_0062ACD4);
    }
    D_0062ACD4 = func_00100230(1, (int)func_001A7C20, -1);
    func_00100B40(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_Init);

extern int D_0062AF58;
extern int D_0062AF5C;
extern int D_0062AF60;
extern int D_0062B00C;
extern int D_0062AF64;
extern int D_0062AF68;
extern int D_0062AF6C;
extern void debug_ClearFontWindow(void);
extern void debug_PrintCharacter(void);

void debug_Load(void) {
    debug_ClearFontWindow();
    D_0062AF58 = 0;
    D_0062AF5C = 0;
    D_0062AF60 = 0;
    D_0062AF64 = 0;
    D_0062AF68 = 0;
    D_0062AF6C = 0;
    D_0062B00C = 0;
    *(volatile int *)0x10000010 = 0x82;
    *(volatile int *)0x10000810 = 0x82;
    debug_PrintCharacter();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_MakeFont);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_makeBackImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_PrintCharacter);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_PrintFont);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_FlushFontWindow);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_FlushFont);

extern void debug_FlushFont(void);

void draw_batsu(void) {
    debug_FlushFont();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", draw_shikaku);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_brainBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_MakeBarString);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DrawBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DispBar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_ResizeSnapShot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_WriteBMP);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_SnapShot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/debug", debug_DispQW);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    char               f_C;  /* 0x0C */
    char               f_D;  /* 0x0D */
    char               f_E;  /* 0x0E */
    char               f_F;  /* 0x0F */
    unsigned int       f_10;  /* 0x10 */
    short              f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
} S_006EB6D0;  /* stride 0x1C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060D910;  /* stride 0x4 */

/* end struct shapes */
