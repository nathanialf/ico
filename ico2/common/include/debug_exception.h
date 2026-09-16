/*
 * ico2/common/include/debug_exception.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what debug_exception.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DEBUG_EXCEPTION_H
#define DEBUG_EXCEPTION_H

extern void RestoreNormalDrawEnvironment(void *a0, int a1, int a2);
extern void SetDrawEnvironment(int mode);
extern void debugEEExceptionMain();
extern void debug_assertMessage(char *file, int line, char *mes);
extern void drawSprite(int r, int g, int b, int a, int x0, int y0, int x1, int y1, int tex);

#endif /* DEBUG_EXCEPTION_H */
