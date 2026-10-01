/*
 * ico2/sugipon/include/weapon.h
 *
 * The declarations of what weapon.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WEAPON_H
#define WEAPON_H

struct GObj;

/* weapon-def: one weapon kind, 0x24 bytes: the blur trail's length, the grip
   and the hit power (attackhit's damage factor), the weight GetWeaponWeight
   gives, the blend mode of the blur the weapon trails (-1 for none) and the
   blur's colour.
   Readers: weapon.c, ico2/omori/src/attackhit.c (power),
   ico2/fumi/src/act-game.c (0x1C). */
typedef struct {            /* field names derived */
    float length;           /* 0x00, the blade tip's distance */
    float grip;             /* 0x04 */
    float power;            /* 0x08 */
    int weight;             /* 0x0C */
    int word10;             /* 0x10 */
    int blur;               /* 0x14, the blur's blend mode, -1 for none */
    unsigned char color[4]; /* 0x18, the blur's colour */
    int word1C;             /* 0x1C */
    int word20;             /* 0x20 */
} WeaponDef; /* derived name */

/* weapon-fumble-def: one fumble placement, 0x18 bytes, three to a weapon
   slot: the target position and the three turns the dropped weapon is given,
   in degrees. */
typedef struct {  /* field names derived */
    float pos[3]; /* 0x00 */
    float rotY;   /* 0x0C */
    float rotX;   /* 0x10 */
    float rotZ;   /* 0x14 */
} FumbleRow; /* derived name */

struct GObj *CheckSwapableWeapon(struct GObj *a0, float dist);
int CheckWeaponKind(struct GObj *a0);
void ExecWeaponHitReaction(struct GObj *a0);
int GetTorchGObjOfWeapon(struct GObj *a0);
void LightTorchOffOfWeapon(struct GObj *a0);
void LightTorchOnOfWeapon(struct GObj *a0);
void PickupWeapon(struct GObj *a0, struct GObj *a1, int a2);
void ReleaseWeapon(struct GObj *a0);
int ReleaseWeaponWithFumbleSequential(struct GObj *g);
void SetWeaponOffsetMode(struct GObj *a0, int a1);
void SetWeaponTorchChainReactionFlagAll(int a0);
void WeaponCurPos(struct GObj *a0, void *a1, void *a2, void *a3);
void calcBlur(struct GObj *g, float t);
void calcDynamicGeometry(struct GObj *g);
void dispBlur(struct GObj *g);
void dispInsectNet(struct GObj *g);
void dispLaserSword(struct GObj *g, float t);
/* unprototyped: the third argument is weapon.c's own layout record type. */
void initializeQueenzSword();
void weaponHitReactionSE(struct GObj *);
float GetWeaponWeight(struct GObj *a0);

#endif /* WEAPON_H */
