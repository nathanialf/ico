/*
 * ico2/sugipon/include/delayFreeManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what delayFreeManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DELAYFREEMANAGER_H
#define DELAYFREEMANAGER_H

void EntryDelayFree(void *p);
void InitDelayFree(void);

#endif /* DELAYFREEMANAGER_H */
