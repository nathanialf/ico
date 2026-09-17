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

void debugCdvdLoadInfoSegAdd(int page, int idx, int delta);
int debugSceClose(int a0);
int debugSceOpen(int a0, int a1);
void debug_Assert(char *fmt, ...);
void debug_BeginTimer(int a0);
int debug_CallbackGsFinish(void);
void debug_ClearFontWindow(void);
void debug_DispQW(void *p, int size);
void debug_DrawBar(void);
void debug_FlushFontWindow(void);
float debug_GetTimerSec(void);
void debug_Init(void);
void debug_MakeFont(void);
void debug_PrintCharacter(char *str, int x, int y, int r, int g, int b, int sz);
void debug_PrintFont(int a0, int a1, int a2, char *a3);
void debug_PrintFontWindow(int col, char *fmt, ...);
void debug_Printf(int a, int b, unsigned int c, int x, ...);
void debug_PrintfDummy(int a0, int a1, unsigned int a2, int a3, ...);
int debug_SETest_color(int idx);
int debug_SelectCsvWindow(char *title, int x, int y, int rows, void *base, int stride, int off, int deref, int n, int *psel);
int debug_SelectCsvWindowWithLine(char *title, int x, int y, int rows, void *base, int stride, int off, int deref, int n, int *psel);
void debug_SetDmaCallback(void);
void debug_StdPrintfDummy(char *fmt, ...);
void debug_brainBar(void);
void debug_closeLog(void);
void debug_makeBackImage(void);
int debug_mcFormat(int port);
int debug_mcTest(void);
int debug_mcUnformat(int port);
void debug_openLog(void);
void *debug_saveNumFunc(int a0, void *a1);
void getBuffer(int a0);
void getLineBuffer(int a0, int a1, int a2);
int gsResetFunc(void);

#endif /* DEBUG_H */
