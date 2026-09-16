/*
 * ico2/ito/include/mv_disp.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_disp.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_DISP_H
#define MV_DISP_H

void dispClear(int *self, unsigned int col);
void dispCreate(int *self, int a1, int a2, int a3, int a4);
void dispDelete(void);
void dispSetTags(int *self, int src, int a2, int a3, int p4, int p5, int p6, int p7, int p8, int p9);
void endDisplay(void);
int handler_endimage(void);
void startDisplay(int a0);
int vblankHandler(void);

#endif /* MV_DISP_H */
