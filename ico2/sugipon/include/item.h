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

struct GObj;

/* item-kind-def: one item kind's break animations, 0x20 bytes, seven kinds:
   the stage BG animations (972 for none) and their modes the item plays
   while it stays, breaks, drops and is hit, and whether the break plays SE
   package 43. */
typedef struct {        /* field names derived */
    int stayAnim;       /* 0x00 */
    int stayMode;       /* 0x04 */
    int breakAnim;      /* 0x08 */
    int breakMode;      /* 0x0C */
    int dropAnim;       /* 0x10 */
    int hitAnim;        /* 0x14 */
    int hitMode;        /* 0x18 */
    unsigned int flags; /* 0x1C, bit 0: play SE package 43 */
} ItemBreakRec;

extern ItemBreakRec itemKind[];
int BreakItemFromOutside(struct GObj *gobj);
int BreakItemWithAttackHit(struct GObj *gobj, float *dir);
int CheckCarryableItem(char *a0);
int CheckItemDead(char *a0);
int GetCharHeldItem(char *a0);
int GetItemKind(struct GObj *a0);
void HoldItem(struct GObj *gobj, struct GObj *holder);
int IsBombExplode(struct GObj *a0);
void ReleaseItem(char *gobj);
int ReviveAllCarryableItems(void);
int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame);
int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz);
int ReviveCarryableItemsWithBoundary(void *center, float radius);
void ThrowItem(char *gobj, void *vel);
void carriedItemGeo(struct GObj *gobj);
void execBombGeo(struct GObj *gobj);
void uncarriedItemGeo(struct GObj *gobj);

#endif /* ITEM_H */
