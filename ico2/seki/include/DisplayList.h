/*
 * ico2/seki/include/DisplayList.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DisplayList.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DISPLAYLIST_H
#define DISPLAYLIST_H

void dl_CloseDma(void);
int dl_GetPri(void);
void dl_Init(void);
void dl_OpenDma(int a0, int a1, int a2);
void dl_SetDLPriority(int a0);

#endif /* DISPLAYLIST_H */
