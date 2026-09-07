#include "common.h"

/* debug_exception_screen.c.inc (compiled into debug_exception.o) */

typedef struct { float f[4]; } __attribute__((packed)) Blk16;
typedef struct { int x, y, w, h; } FR;
typedef struct { char _0[0x20]; int f_20; char _24[0x18]; } GsysObjInfo;
extern char D_0061B440[];
extern char D_0063AE78[];
extern char D_0063AE80[];
void debug_Assert(char *fmt, ...) {
    char buf[0x100];
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 56);
    debug_assertMessage(D_0061B440, 0x570, buf);
    __assert(D_0061B440, 0x570, D_0063AE78);
    debug_assert(D_0061B440, 0x571);
    __assert(D_0061B440, 0x571, D_0063AE80);
}
extern int D_0063AE84;
void debug_openLog(void) {
    volatile char buf[256];
    D_0063AE84 = -1;

}
extern void sceWrite();
extern int strlen();
extern void vsprintf();
void debug_LogPrintf(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = strlen(buf);
    sceWrite(D_0063AE84, buf, info);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SaveDebugOptionFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_GetDebugOption);
extern int AddDmacHandler();
extern unsigned int D_0063AE8C;
extern void EnableDmac();
extern void RemoveDmacHandler();
extern int debug_CallbackGsFinish();
void debug_SetDmaCallback(void)
{
    if ((int)D_0063AE8C != -1) {
        RemoveDmacHandler(1, D_0063AE8C);
    }
    D_0063AE8C = AddDmacHandler(1, (int)debug_CallbackGsFinish, -1);
    EnableDmac(1);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_VariableInit);
extern int D_0063B110;
extern int D_0063B114;
extern int D_0063B118;
extern int D_0063B11C;
extern int D_0063B120;
extern int D_0063B124;
extern int D_0063B1C4;
extern void debug_ClearFontWindow(void);
extern void debug_makeBackImage(void);
void debug_Init(void) {
    debug_ClearFontWindow();
    D_0063B110 = 0;
    D_0063B114 = 0;
    D_0063B118 = 0;
    D_0063B11C = 0;
    D_0063B120 = 0;
    D_0063B124 = 0;
    D_0063B1C4 = 0;
    *(volatile int *)0x10000010 = 0x82;
    *(volatile int *)0x10000810 = 0x82;
    debug_makeBackImage();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Load);
ASM_LIT4_SLOT(D_00639338, 10059776.0f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeFont);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_makeBackImage);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintCharacter);
extern int D_0063AEB0;
extern int D_0063B13C;
extern void debug_PrintCharacter(char *str, int x, int y, int r, int g, int b, int sz);
extern int gif_CheckOpen(void);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_Sprite(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void gif_StartPacketPri(int a0);
void debug_PrintFont(int a0, int a1, int a2, char *a3) {
    FR buf[2];
    int r;

    buf[1].x = a0 - 0x142;
    buf[1].y = a1 - 0x71;
    r = strlen(a3);
    buf[1].h = 9;
    buf[1].w = r * 0xC + 4;
    buf[0] = buf[1];

    if (gif_CheckOpen() != 0) {
        return;
    }
    if (D_0063B13C & 2) {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_Sprite(&buf[0], 0xFFFFFFFDU, 0, &D_0063AEB0, 1);
        gif_EndPacket();
    } else {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_EndPacket();
    }
    debug_PrintCharacter(a3, a0, a1, (unsigned) a2 >> 24, ((unsigned) a2 >> 16) & 0xFF, ((unsigned) a2 >> 8) & 0xFF, 0x70);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_FlushFontWindow);
extern void debug_FlushFontWindow(void);
void debug_FlushFont(void) {
    debug_FlushFontWindow();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", draw_batsu);
INCLUDE_ASM("asm/nonmatchings/src/debug", draw_shikaku);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_brainBar);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeBarString);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DrawBar);
ASM_LIT4_SLOT(D_0063933C, 270000.0f);
ASM_LIT4_SLOT(D_00639340, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBar);
ASM_LIT4_SLOT(D_00639344, 270000.0f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_ResizeSnapShot);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_WriteBMP);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SnapShot);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispQW);
extern void debug_PrintFont();
void debug_Printf(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}
void debug_Printf2(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFontWindow);
void debug_PrintfDummy(int a0, int a1, unsigned int a2, int a3, ...) {
}
void debug_PrintFontWindowDummy(int a0, int a1, ...) {
}
void debug_StdPrintfDummy(char *fmt, ...)
{
    (void)fmt;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFontf);
extern const char D_0060DAF0_a[] __asm__("D_0061BB40");
extern const char D_00631CF0_a[] __asm__("D_0063AF50");
extern void debug_StdPrintfDummy__pn() __asm__("debug_StdPrintfDummy");
extern int fptodp(float);
void debug_PrintMatrix(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = fptodp(arg[0]);
        int v1 = fptodp(arg[1]);
        int v2 = fptodp(arg[2]);
        int v3 = fptodp(arg[3]);
        debug_StdPrintfDummy__pn((int)D_0060DAF0_a, v0, v1, v2, v3);
        arg += 4;
    }
    debug_StdPrintfDummy__pn((int)D_00631CF0_a);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispVu1FReg);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Mode);
extern char D_0061BC38[];
extern char D_0063AF70[];
extern char D_0063AF78[];
extern int debug_SelectCsvWindow(char *a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7, int a8, int *a9);
extern void sprintf();
extern unsigned int strlen__pn(char *buf) __asm__("strlen");
int debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5,
                   int (*fn)(int, int), int a7) {
    char buf[count][0x25];
    int i;
    for (i = 0; i < count; i++) {
        if (fn != 0) {
            int r = fn(i, a7);
            sprintf(buf[i], D_0063AF70, i, r);
        } else {
            sprintf(buf[i], D_0063AF78, i);
        }
        if (strlen__pn(buf[i]) >= 0x26) {
            buf[i][0x24] = 0;
            debug_StdPrintfDummy__pn((int)D_0061BC38);
        }
    }
    return debug_SelectCsvWindow(a0, a1, a2, a3, (char *)buf, 0x25, 0, 0, count, a5);
}
extern int D_0063AF90[];
extern void sprintf();
void getLineBuffer(int a0, int a1, int a2)
{
    sprintf(a0, D_0063AF90, a1, a2);
}
extern int D_0063AF80[];
void getBuffer(int a0)
{
    sprintf(a0, D_0063AF80);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindow);
/* stage records are 0x194 bytes; +0x80 (= D_005F5DD0) is the data file name */
typedef struct { char pad[0x194]; } StgFileName;
extern StgFileName D_005F5DD0[];
extern int D_0028F4D8[];
extern char D_0063AF98[];
extern char D_0061BC78[];
extern int stage_no;
extern int mpegPlayReturnStage;
extern int enable_game_pause;
extern int D_0063A650;
extern int D_0063AA08;
extern char *strstr(const char *s, const char *sub);
extern void soundDataSegAllClose(int a0, int a1);
extern void kanbanInit(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern void stgmgrForceSwitch(int stage);
extern void ACTGame_SetActors_Debug(int stage, int a1);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectStageMain);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectStage);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcRetErrCheck);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_selectFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcSaveMainBlock);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcLoadMainBlock);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_mcDeleteFile);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MemoryCard);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SETest);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SESlotDisp);
extern int D_0070F880[];
extern char D_0063B068[];
extern char D_0063B070[];
extern char D_0055F828[];
extern char D_0061C1D0[];
extern char D_007048C0[];
char *debugCdvdLoadInfoSegDispFunc(int idx, int page)
{
    char buf[0x10];
    int d;
    d = *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8))
      - *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8) + 4);
    if (d < 0) {
        sprintf(buf, D_0063B068, -d);
    } else {
        sprintf(buf, D_0063B070, d);
    }
    sprintf(D_007048C0, D_0061C1D0, D_0055F828 + idx * 0x24,
            *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)),
            *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8) + 4),
            buf);
    return D_007048C0;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectActGobj);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBox);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBall);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_CollisionTest);
ASM_LIT4_SLOT(D_00639348, 0.001f);
ASM_LIT4_SLOT(D_0063934C, 0.001f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Menu);
extern int D_0063B0F4;
void debug_Menu_off(void) {
    D_0063B0F4 = 0;
}
void debug_BeginTimer(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}
extern Blk16 D_0061B7C8;
float debug_GetTimerSec(void) {
    Blk16 buf;
    int v;
    float f2;

    buf = D_0061B7C8;
    if (*(volatile unsigned int *)0x10000810 & 0x800) {
        return -1.0f;
    }
    v = *(volatile int *)0x10000800;
    f2 = (float)(unsigned int)v;
    return f2 / buf.f[*(volatile unsigned int *)0x10000810 & 3] / 60.0f;
}
float debug_GetTimerCount(void) {
    if ((*(volatile int *)0x10000810) & 0x800) {
        return -1.0f;
    }
    return (float)(*(volatile unsigned int *)0x10000800);
}
extern int D_0063AE64;
extern char D_007082D0[];
void debug_ClearFontWindow(void)
{
    char *p = D_007082D0;
    int i;
    p += 0x5B4;
    for (i = 0x1A; i >= 0; i--) {
        *p = 0;
        p -= 0x38;
    }
    D_0063AE64 = 0;
}
extern int D_0063AEB4;
void debug_ResizeFontWindowHeight(int val) {
    D_0063AEB4 = val;
}
/* Profiler bar table: 0x400 entries of 0x1C bytes; D_0063C384 = live count.
   Callers pass (label, colour, __FILE__, __LINE__) -- see the call sites in
   main.c and motionManager2.c, where a3 is literally the caller's line number.
   +0x14 samples the EE timer T0_COUNT at 0x10000000; volatile because it is a
   hardware counter (and the ROM's 32-bit `lw` shows the read is not narrowed). */
typedef struct {
    char name[12];          /* 0x00 */
    unsigned char col[4];   /* 0x0C */
    char *file;             /* 0x10 */
    short count;            /* 0x14 */
    short pad16;            /* 0x16 */
    int line;               /* 0x18 */
} DebugBar;
extern DebugBar D_00708880[];
extern int D_0063C384;
extern int D_0063B1D4;
extern char D_0063AF30[];
void debug_SetBar(char *name, unsigned int col, char *file, int line)
{
    DebugBar *p = &D_00708880[D_0063C384];
    if (D_0063B1D4 == 0
        && D_0063C384 != 0x400) {
        sprintf(p->name, D_0063AF30, name);
        p->count = *(volatile int *)0x10000000;
        p->col[0] = col >> 24;
        p->col[1] = col >> 16;
        p->col[2] = col >> 8;
        p->col[3] = col;
        p->file = file;
        p->line = line;
        D_0063C384++;
    }
}
/* debug_SetBar with the inverted D_0063B1D4 gate (records only while the
   profiler flag is set). */
void debug_SetBar2(char *name, unsigned int col, char *file, int line)
{
    DebugBar *p = &D_00708880[D_0063C384];
    if (D_0063B1D4 != 0
        && D_0063C384 != 0x400) {
        sprintf(p->name, D_0063AF30, name);
        p->count = *(volatile int *)0x10000000;
        p->col[0] = col >> 24;
        p->col[1] = col >> 16;
        p->col[2] = col >> 8;
        p->col[3] = col;
        p->file = file;
        p->line = line;
        D_0063C384++;
    }
}
extern int D_0063B110;
extern int D_0063B114;
extern int D_0063B118;
extern int D_0063B11C;
extern int D_0063B120;
extern int D_0063B124;
extern int D_0063C384;
void debug_ResetBar(void)
{
    D_0063B120 = 0;
    *(volatile int *)0x10000000 = 0;
    D_0063B11C = 0;
    D_0063B118 = 0;
    D_0063B114 = 0;
    D_0063B110 = 0;
    D_0063B124 = 0;
    D_0063C384 = 0;
}
extern char D_0061BB80[];
void debug_DispVu1IReg(int no)
{
    int i;
    int buf[4];
    if (no >= 0) {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x420));
        __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
        debug_StdPrintfDummy(D_0061BB80, no, buf[0], buf[1], buf[2], buf[3]);
    } else {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x420));
        for (i = 0; i < 16; i++) {
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
            debug_StdPrintfDummy(D_0061BB80, i, buf[0], buf[1], buf[2], buf[3]);
        }
    }
}
extern char D_0061BBA0[];
void debug_DispVu1SReg(int no)
{
    int i;
    int buf[4];
    if (no >= 0) {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x420));
        __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
        debug_StdPrintfDummy(D_0061BBA0, no, buf[0], buf[1], buf[2], buf[3]);
    } else {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x420));
        for (i = 0; i < 16; i++) {
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
            debug_StdPrintfDummy(D_0061BBA0, i, buf[0], buf[1], buf[2], buf[3]);
        }
    }
}
extern void debug_DispQW();
void debug_DispMatrix(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        debug_DispQW(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}
void debug_SetBarDummy(void) {}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowWithLine);
int debug_TryToGetStartStage(void) {
    return -1;
}
extern int D_0061C580[];
extern int D_0063B100;
extern int D_0063B108[];
extern int D_007049D0[];
extern int sceOpen(void *a0, int a1);
extern void sprintf__pn(void *a0, void *a1, void *a2, int a3) __asm__("sprintf");
int debugSceOpen(int a0, int a1) {
    sprintf__pn(D_007049D0, D_0063B108, D_0061C580, a0);
    return D_0063B100 = sceOpen(D_007049D0, a1);
}
extern int D_0063B100;
extern int sceClose();
int debugSceClose(int a0) {
    if (a0 == D_0063B100) {
        D_0063B100 = -1;
    }
    return sceClose();
}
int debugSceCloseFdNew(void)
{
    int r = 0;
    int h = D_0063B100;
    if (h != -1) {
        D_0063B100 = -1;
        r = sceClose(h);
        D_0063B100 = -1;
    }
    return r;
}
void debug_closeLog(void) {}
extern int D_0070F880[];
void debugCdvdLoadInfoSegInit(int idx)
{
  int *p;
  char *new_var2;
  int new_var;
  int i;
  new_var2 = (char *) D_0070F880;
  p = (int *) ((new_var2 + (idx * 0xD0)) + 0xC8);
  if (1)
  {
    for (i = 0x19; i >= 0; i--)
    {
      new_var = (*p = 0);
      p = (p = (int *) (((char *) p) - 8));
    }

  }
}
void debugCdvdLoadInfoSegAdd(int page, int idx, int delta)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) += delta;
}
void debugCdvdLoadInfoSegCls(int page, int idx)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) = 0;
}
extern int D_0028F4F0[];
extern void gsb_Init();
int gsResetFunc(void)
{
    gsb_Init(D_0028F4F0);
    return 1;
}
extern int D_00639EA0;
void ChangeGirlControlMode(int a0) {
    if (a0 == 1) {
        D_00639EA0 = a0;
    }
}
extern int D_0063AE68;
int debug_CallbackGsFinish(void)
{
    D_0063AE68 = *(volatile int *)0x10000000;
    return 0;
}
extern char D_0061B4A8[];
extern char D_0061B4E8[];
extern char D_0061B500[];
extern char D_0061B538[];
extern char D_0061B570[];
extern char D_0063AE90[];
void debug_SaveStartStageFile(int stage)
{
    char buf[0x100];
    debug_StdPrintfDummy(D_0061B4A8);
    if (debugSceOpen((int)D_0061B4E8, 0x602) < 0) {
        debug_StdPrintfDummy(D_0061B500);
    } else {
        sprintf(buf, D_0063AE90, stage);
        sceWrite(0, buf, strlen(buf));
        debug_StdPrintfDummy(D_0061B538, stage);
        debugSceClose(0);
    }
    debug_StdPrintfDummy(D_0061B570);
    debug_openLog();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", _debug_SelectCsvWindow);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowWithLineColor);
/* src/debug.c:4415-4423 in the listing: a static helper both mc(Un)format
   inline -- prints the confirmation prompt and reads the pad:
   circle (0x20) = yes -> 1, cross (0x40) = cancel -> -1, otherwise 0. */
extern char D_0061BC98[];
extern int D_0028F8F4[];
static inline int debug_mcConfirm(char *msg)
{
    int yes = 0;
    debug_PrintfDummy(0x50, 0x46, 0xFFFFFF00u, (int)D_0061BC98, (int)msg);
    if (D_0028F8F4[0] & 0x20) {
        yes = 1;
    }
    return (D_0028F8F4[0] & 0x40) ? -1 : yes;
}
extern int D_0063AFA0;
extern int D_0063AFA4;
extern char D_0063AFA8[];
extern char D_0061BCA8[];
extern void iosMcFormat(int port);
extern int iosMcSync(int port);
int debug_mcFormat(int port)
{
    int r;
    switch (D_0063AFA0) {
    case 0:
        r = debug_mcConfirm(D_0063AFA8);
        if (r != 1) {
            return r;
        }
        iosMcFormat(port);
        D_0063AFA0++;
        break;
    case 1:
        if (D_0063AFA4++ & 0x10) {
            debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0061BCA8);
        }
        if (iosMcSync(port) != 0) {
            D_0063AFA0++;
        }
        break;
    default:
        D_0063AFA0 = 0;
        return 1;
    }
    return 0;
}
extern int D_0063AFB0;
extern int D_0063AFB4;
extern char D_0061BCB8[];
extern char D_0061BCC8[];
extern void iosMcUnformat(int port);
int debug_mcUnformat(int port)
{
    int r;
    switch (D_0063AFB0) {
    case 0:
        r = debug_mcConfirm(D_0061BCB8);
        if (r != 1) {
            return r;
        }
        iosMcUnformat(port);
        D_0063AFB0++;
        break;
    case 1:
        if (D_0063AFB4++ & 0x10) {
            debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0061BCC8);
        }
        if (iosMcSync(port) != 0) {
            D_0063AFB0++;
        }
        break;
    default:
        D_0063AFB0 = 0;
        return 1;
    }
    return 0;
}
extern char D_0063AFC8[];
extern char D_0063AFD0[];
void *debug_saveNumFunc(int a0, void *a1) {
    if ((1 << a0) & *(long long *)((char *)a1 + 0x9C0)) {
        return D_0063AFC8;
    }
    return D_0063AFD0;
}
extern void iosMcTest(void);
int debug_mcTest(void) {
    iosMcTest();
    return 1;
}
extern void staffRollStart(int a0, float a1);
int debug_STAFFROLLTest(void) {
    staffRollStart(0x80, 1.0f);
    return 1;
}
extern unsigned short D_0030C4E0[];
extern GsysObjInfo D_005D6DB0[];
int debug_SETest_color(int idx)
{
  int new_var;
  int v3 = D_005D6DB0[idx].f_20;
  unsigned short a4 = *((unsigned short *) (((char *) D_0030C4E0) + (v3 * 2)));
  int v0 = 0x80808000;
  int a3 = -0x100;
  if (new_var = a4 != 0)
  {
    v0 = a3;
  }
  return v0;
}
extern int soundReverbDepthGet(void);
extern void soundReverbDepthSet(int depth);
/* pad state block: +0x4 held buttons, +0xC newly-pressed (trigger) buttons */
typedef struct { int _0; int hold; int _8; int trg; } DbgReverbPad;
extern DbgReverbPad D_0028F8F0[];
extern char D_0061C1A8[];
int debug_reverbTest(void)
{
    int depth = soundReverbDepthGet();
    if (D_0028F8F0[0].trg & 0x1000) {
        if (depth <= 99) {
            depth++;
        }
    }
    if (D_0028F8F0[0].trg & 0x4000) {
        depth -= (0 < depth);
    }
    soundReverbDepthSet(depth);
    debug_PrintfDummy(10, 0x50, 0xFFFFFF00u, (int)D_0061C1A8, soundReverbDepthGet());
    return (D_0028F8F0[0].hold & 0x60) != 0;
}
extern int D_0063B060;
extern int D_0063B05C;
extern char D_0061C1C0[];
extern char D_00559D50[];
int debug_AdpcmTest(int a0) {
    int r;
    if (a0 != 0) {
        D_0063B060 = -1;
    }
    r = debug_SelectCsvWindow(D_0061C1C0, 10, 0x3C, 10, D_00559D50, 0x40, 0, 0, 0x69, &D_0063B05C);
    if (r > 0) {
        if (D_0063B05C != 0) {
            scpAdpcmPlayRequestFunc(D_0063B05C, 0, 1, 1, 1);
        }
    }
    return r;
}
typedef struct { char s[20]; } DbgTitle20;
typedef struct { long long a; long long b; unsigned short c; unsigned char d; } DbgTitle19;
extern DbgTitle20 D_0061C1E0;
extern DbgTitle19 D_0061C1F8;
extern int D_0063B078;
extern int D_0063B07C;
int debugCdvdLoadInfoSegDisp(void)
{
    char title[0x20];
    int r;
    *(DbgTitle20 *)title = D_0061C1E0;
    if (D_0063B078 != 0) {
        DbgTitle19 *t = (DbgTitle19 *)title;
        t->a = D_0061C1F8.a;
        t->b = D_0061C1F8.b;
        t->c = D_0061C1F8.c;
        t->d = D_0061C1F8.d;
    }
    r = debug_SelectCsvWindowVal((int)title, 0x50, 0x46, 0xA, 0x1A, (int)&D_0063B07C,
                                 (int (*)(int, int))debugCdvdLoadInfoSegDispFunc, D_0063B078);
    if (D_0028F8F4[0] & 0x10) {
        int i;
        int *p = (int *)((char *)D_0070F880 + D_0063B078 * 0xD0);
        for (i = 0x19; i >= 0; i--) {
            p[1] = p[0];
            p += 2;
        }
    }
    return r;
}
int debug_GameOver(void) {
    debug_Menu_off();
    return -1;
}
int debug_EndingDemo(void) {
    debug_Menu_off();
    return -1;
}
extern void backStageProcessInStage(float a0);
int debug_BackStageTest(void) {
    backStageProcessInStage(10000000.0f);
    return 1;
}
extern void backStageDebugTimeZero(void);
int debug_tsuresariTimeZero(void) {
    backStageDebugTimeZero();
    return 1;
}
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *gobj);
extern int IsTopHint(void *gobj);
extern void DebugHintStart(void *gobj);
int debug_hintStart(void)
{
    void *gobj;
    for (gobj = isysGObjGetExist_begin(); gobj != 0; gobj = isysGObjGetExist_next(gobj)) {
        if (IsTopHint(gobj)) {
            DebugHintStart(gobj);
            break;
        }
    }
    return 1;
}
/* src/debug.c:5380-5397 in the listing: a static helper that builds the
   {name, gobj} list of the pad-controllable objects (kind 2 = boy, 4 = girl). */
typedef struct { char *name; void *obj; } DbgGobjEnt;
extern char D_002C1270[];
static inline int debug_ListPadControlGobj(DbgGobjEnt *list)
{
    void *g;
    int n = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        int kind = ((int *)g)[3];
        if (kind == 2 || kind == 4) {
            list[n].obj = g;
            list[n].name = kind * 0x64 + D_002C1270;
            n++;
        }
    }
    return n;
}
extern int D_0063B084;
extern void *D_00639ED0;
extern char D_0061C228[];
int debug_SelectPad2ControlGobj(int reset)
{
    DbgGobjEnt list[10];
    int n;
    int r;
    n = debug_ListPadControlGobj(list);
    if (reset != 0) {
        D_0063B084 = 0;
    }
    r = debug_SelectCsvWindow(D_0061C228, 0xA, 0x32, 0xB, list, 8, 0, 1, n, &D_0063B084);
    if (r > 0) {
        D_00639ED0 = list[D_0063B084].obj;
        return 1;
    }
    return (r == -1) ? -1 : 0;
}
extern void CameraSetMode(int x);
extern int D_0028F8F4[];
int debug_FreeCamera(int a0)
{
    if (a0 != 0) {
        CameraSetMode(1);
    }
    CameraSetMode(1);
    return (D_0028F8F4[0] & 0x100) ? -1 : 0;
}
