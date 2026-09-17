/*
 * ico2/sugipon/include/stageMultiBgaManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what stageMultiBgaManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAGEMULTIBGAMANAGER_H
#define STAGEMULTIBGAMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order stageMultiBgaManager.c's inline tail has. */
void InitStageMultiBgaManager(void);
void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, int sensitive);
void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay);

void DispStageMultiBgaManager(void);
void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, int sensitive, int stay);

#endif /* STAGEMULTIBGAMANAGER_H */
