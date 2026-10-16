/*
 * ico2/sugipon/include/stageMultiBgaManager.h
 *
 * The declarations of what stageMultiBgaManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STAGEMULTIBGAMANAGER_H
#define STAGEMULTIBGAMANAGER_H

void InitStageMultiBgaManager(void);
void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, void *vel);
void DispStageMultiBgaManager(void);

#endif /* STAGEMULTIBGAMANAGER_H */
