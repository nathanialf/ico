/*
 * ico2/sugipon/include/multiBgaManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what multiBgaManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MULTIBGAMANAGER_H
#define MULTIBGAMANAGER_H

extern void DispMultiBgaManagerWithKind(int a0, int a1, int a2);
extern void EntryMultiBgaManager(int id, int a1, int a2, int *root, void *q);
extern void *InitMultiBgaManager(int n);

#endif /* MULTIBGAMANAGER_H */
