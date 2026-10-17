/*
 * ico2/sugipon/include/item.h
 *
 * The declarations of what item.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ITEM_H
#define ITEM_H

struct GObj;

/* item-kind-def: one item kind's break animations, 0x10 bytes, six kinds:
   the stage BG animations (763 for none) the item plays while it stays,
   breaks and drops, and whether the break plays an SE package.
   uncarriedItemGeo multiplies the kind by 16 and reads 0x00, 0x04 and the
   flags at 0x0C; the later builds' hit animation has no field. */
typedef struct {        /* field names derived */
    int stayAnim;       /* 0x00 */
    int breakAnim;      /* 0x04 */
    int dropAnim;       /* 0x08 */
    unsigned int flags; /* 0x0C, bit 0: play the break SE package */
} ItemBreakRec;         /* derived name */

extern ItemBreakRec itemKind[];
int BreakItemFromOutside(struct GObj *gobj);
int BreakItemWithAttackHit(struct GObj *gobj, float *dir);
int CheckCarryableItem(struct GObj *gobj);
int CheckItemDead(struct GObj *gobj);
int GetCharHeldItem(struct GObj *chara);
int GetItemKind(struct GObj *gobj);
void HoldItem(struct GObj *gobj, struct GObj *holder);
int IsBombExplode(struct GObj *gobj);
void ReleaseItem(struct GObj *gobj);
int ReviveAllCarryableItems(void);
int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame);
int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz);
int ReviveCarryableItemsWithBoundary(void *center, float radius);
void ThrowItem(struct GObj *gobj, void *vel);

struct ItemLayout;

char *InitItemGeo(struct GObj *gobj, struct ItemLayout *layout);
void ItemGeo(struct GObj *gobj);
void ItemDL(struct GObj *gobj);
int IsItemHoldable(struct GObj *gobj);
void *GetBombTorchGObj(struct GObj *item);
void StopItemExplodeAnimationAll(void);

#endif /* ITEM_H */
