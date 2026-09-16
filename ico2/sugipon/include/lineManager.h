/*
 * ico2/sugipon/include/lineManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what lineManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

void Draw2DLineSeg_Loop(int *a0, int *a1, int *a2);
void Draw2DLineSeg_Start(void);
void DrawLine(int *p1, int *p2, int a2, int a3);
void DrawLineG(int *a0, int *a1, int *a2, int *a3, int a4);
int _getLine();

#endif /* LINEMANAGER_H */
