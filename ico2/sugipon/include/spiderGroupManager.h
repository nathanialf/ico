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
void EntryRevivedSpiderGroupManager(struct GObj *group);
void DispAllSpiderGroups(void);
void EntryToSpiderGroupManagerForReviveMaster(struct GObj *group, struct GObj *master);
struct GObj *getReviveEnemyGObj(int count);
void EntrySpiderGroupManager(struct GObj *gobj);
void ExecSpiderGroupManager(void);

#endif /* SPIDERGROUPMANAGER_H */
