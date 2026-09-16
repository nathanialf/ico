/*
 * ico2/common/include/debug.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what debug.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DEBUG_H
#define DEBUG_H

extern void debugCdvdLoadInfoSegAdd(int page, int idx, int delta);
extern int debugSceClose(int a0);
extern int debugSceOpen(int a0, int a1);
extern void debug_Assert(char *fmt, ...);
extern void debug_BeginTimer(int a0);
extern int debug_CallbackGsFinish(void);
extern void debug_ClearFontWindow(void);
extern void debug_DispQW(void *p, int size);
extern void debug_DrawBar(void);
extern void debug_FlushFontWindow(void);
extern float debug_GetTimerSec(void);
extern void debug_Init(void);
extern void debug_MakeFont(void);
extern void debug_PrintCharacter(char *str, int x, int y, int r, int g, int b, int sz);
extern void debug_PrintFont(int a0, int a1, int a2, char *a3);
extern void debug_PrintFontWindow();
extern void debug_Printf(int a, int b, unsigned int c, int x, ...);
extern void debug_PrintfDummy(int a0, int a1, unsigned int a2, int a3, ...);
extern int debug_SETest_color(int idx);
extern int debug_SelectCsvWindow(char *title, int x, int y, int rows, void *base, int stride, int off, int deref, int n, int *psel);
extern int debug_SelectCsvWindowWithLine(char *title, int x, int y, int rows, void *base, int stride, int off, int deref, int n, int *psel);
extern void debug_SetDmaCallback(void);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_brainBar(void);
extern void debug_closeLog(void);
extern void debug_makeBackImage(void);
extern int debug_mcFormat(int port);
extern int debug_mcTest(void);
extern int debug_mcUnformat(int port);
extern void debug_openLog(void);
extern void *debug_saveNumFunc(int a0, void *a1);
extern void getBuffer(int a0);
extern void getLineBuffer(int a0, int a1, int a2);
extern int gsResetFunc(void);

#endif /* DEBUG_H */
