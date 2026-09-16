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

void DispStageMultiBgaManager(void);
void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, int sensitive, int stay);
void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay);

#endif /* STAGEMULTIBGAMANAGER_H */
