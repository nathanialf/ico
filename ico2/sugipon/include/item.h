/*
 * ico2/sugipon/include/item.h
 *
 * The declarations of what item.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ITEM_H
#define ITEM_H

struct GObj;

/* item-kind-def: one item kind's break animations, 0x20 bytes, seven kinds:
   the stage BG animations (972 for none, JPN and KOR 949) and their modes the item plays
   while it stays, breaks, drops and is hit, and whether the break plays SE
   package 43. */
typedef struct {  /* field names derived */
    int stayAnim; /* 0x00 */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int breakAnim; /* 0x04 */
    int dropAnim;  /* 0x08 */
#ifdef VERSION_JUN26
    unsigned int flags; /* 0x0C, bit 0: play the break SE package */
#else
    int hitAnim;        /* 0x0C */
    unsigned int flags; /* 0x10, bit 0: play SE package 42 */
#endif
#else
    int stayMode;       /* 0x04 */
    int breakAnim;      /* 0x08 */
    int breakMode;      /* 0x0C */
    int dropAnim;       /* 0x10 */
    int hitAnim;        /* 0x14 */
    int hitMode;        /* 0x18 */
    unsigned int flags; /* 0x1C, bit 0: play SE package 43 */
#endif
} ItemBreakRec; /* derived name */

extern ItemBreakRec itemKind[];

#ifdef VERSION_JUN26
int CheckCarryableItem(struct GObj *gobj);
#else
int BreakItemFromOutside(struct GObj *gobj);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
int CheckCarryableItem(struct GObj *gobj);
int CheckItemDead(struct GObj *gobj);
#else
int BreakItemWithAttackHit(struct GObj *gobj, float *dir);
int CheckCarryableItem(struct GObj *gobj);
int CheckItemDead(struct GObj *gobj);
int GetCharHeldItem(struct GObj *chara);
#endif

int GetItemKind(struct GObj *gobj);
#endif

void HoldItem(struct GObj *gobj, struct GObj *holder);
int IsBombExplode(struct GObj *gobj);
void ReleaseItem(struct GObj *gobj);
int ReviveAllCarryableItems(void);

#ifndef VERSION_JUN26
int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame);
#endif

int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz);
int ReviveCarryableItemsWithBoundary(void *center, float radius);
void ThrowItem(struct GObj *gobj, void *vel);

struct ItemLayout;

char *InitItemGeo(struct GObj *gobj, struct ItemLayout *layout);
void ItemGeo(struct GObj *gobj);
void ItemDL(struct GObj *gobj);
int IsItemHoldable(struct GObj *gobj);
void *GetBombTorchGObj(struct GObj *item);

#ifndef VERSION_JUN26
void StopItemExplodeAnimationAll(void);
#endif

#endif /* ITEM_H */
