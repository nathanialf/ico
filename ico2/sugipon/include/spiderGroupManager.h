/*
 * ico2/sugipon/include/spiderGroupManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what spiderGroupManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef SPIDERGROUPMANAGER_H
#define SPIDERGROUPMANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order spiderGroupManager.c's inline tail has. */
void InitSpiderGroupManager(void);
void EntryRevivedSpiderGroupManager(int a0);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1);
int *getReviveEnemyGObj(int count);

void EntrySpiderGroupManager(int gobj);
int tryToRevive(void);

#endif /* SPIDERGROUPMANAGER_H */
