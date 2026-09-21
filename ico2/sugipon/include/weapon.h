/*
 * ico2/sugipon/include/weapon.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what weapon.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WEAPON_H
#define WEAPON_H

int CheckWeaponKind(char *a0);
void ExecWeaponHitReaction(int a0, int a1, int a2, int a3);
int GetTorchGObjOfWeapon(char *a0);
void LightTorchOffOfWeapon(char *a0);
void LightTorchOnOfWeapon(char *a0);
void PickupWeapon(char *a0, char *a1, int a2);
void ReleaseWeapon(char *a0);
int ReleaseWeaponWithFumbleSequential(char *g);
void SetWeaponOffsetMode(char *a0, int a1);
void SetWeaponTorchChainReactionFlagAll(int a0);
void WeaponCurPos(char *a0, void *a1, void *a2, void *a3);
void calcBlur(char *g, float t);
void calcDynamicGeometry(char *g);
void dispBlur(char *g);
void dispInsectNet(char *g);
void dispLaserSword(char *g, float t);
/* unprototyped: the third argument is weapon.c's own layout record type. */
void initializeQueenzSword();
/* Unprototyped: the ROM proves two arities at the two call sites inside
 * weapon.c, one argument from calcDynamicGeometry (0x002015F8 and
 * 0x002016DC set only $4) and four from ExecWeaponHitReaction, so the 2001
 * declaration cannot have carried a parameter list. */
void weaponHitReactionSE();

#endif /* WEAPON_H */
