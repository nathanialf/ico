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

void DispAllSpiderGroups(void);
void EntryRevivedSpiderGroupManager(int a0);
void EntrySpiderGroupManager(int gobj);
void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1);
int tryToRevive(void);

#endif /* SPIDERGROUPMANAGER_H */
