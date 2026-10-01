/*
 * ico2/sugipon/include/stageMultiBgaManager.h
 *
 * The declarations of what stageMultiBgaManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef STAGEMULTIBGAMANAGER_H
#define STAGEMULTIBGAMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order stageMultiBgaManager.c's inline tail has. */
void InitStageMultiBgaManager(void);
void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
void EntryStageMultiBgaManagerSensitive(int kind, void *pos, void *rot, void *vel);
void EntryStageMultiBgaManagerWithStay(int kind, void *pos, void *rot, int stay);
void DispStageMultiBgaManager(void);

void EntryStageMultiBgaManagerSensitiveWithStay(int kind, void *pos, void *rot, void *vel,
                                                int stay);

#endif /* STAGEMULTIBGAMANAGER_H */
