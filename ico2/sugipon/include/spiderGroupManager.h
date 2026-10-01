/*
 * ico2/sugipon/include/spiderGroupManager.h
 *
 * The declarations of what spiderGroupManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SPIDERGROUPMANAGER_H
#define SPIDERGROUPMANAGER_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order spiderGroupManager.c's inline tail has. */
void InitSpiderGroupManager(void);
void EntryRevivedSpiderGroupManager(int a0);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(struct GObj *a0, struct GObj *a1);
int *getReviveEnemyGObj(int count);

void EntrySpiderGroupManager(int gobj);
int tryToRevive(void);

#endif /* SPIDERGROUPMANAGER_H */
