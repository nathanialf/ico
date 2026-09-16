/*
 * ico2/sugipon/include/item.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what item.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ITEM_H
#define ITEM_H

extern int BreakItemFromOutside(char *gobj);
extern int BreakItemWithAttackHit(char *gobj, float *dir);
extern int CheckCarryableItem(char *a0);
extern int CheckItemDead(char *a0);
extern int GetCharHeldItem(char *a0);
extern int GetItemKind(char *a0);
extern void HoldItem(char *gobj, char *holder);
extern int IsBombExplode(char *a0);
extern void ReleaseItem(char *gobj);
extern int ReviveAllCarryableItems(void);
extern int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame);
extern int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz);
extern int ReviveCarryableItemsWithBoundary(void *center, float radius);
extern void ThrowItem(char *gobj, void *vel);
extern void carriedItemGeo(char *gobj);
extern void execBombGeo(char *gobj);
extern void uncarriedItemGeo(char *gobj);

#endif /* ITEM_H */
