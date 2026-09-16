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

int BreakItemFromOutside(char *gobj);
int BreakItemWithAttackHit(char *gobj, float *dir);
int CheckCarryableItem(char *a0);
int CheckItemDead(char *a0);
int GetCharHeldItem(char *a0);
int GetItemKind(char *a0);
void HoldItem(char *gobj, char *holder);
int IsBombExplode(char *a0);
void ReleaseItem(char *gobj);
int ReviveAllCarryableItems(void);
int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame);
int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz);
int ReviveCarryableItemsWithBoundary(void *center, float radius);
void ThrowItem(char *gobj, void *vel);
void carriedItemGeo(char *gobj);
void execBombGeo(char *gobj);
void uncarriedItemGeo(char *gobj);

#endif /* ITEM_H */
