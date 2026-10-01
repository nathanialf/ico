/*
 * ico2/script/include/st08b.h
 *
 * The declarations of what st08b.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST08B_H
#define ST08B_H

#include "typedef.h"

/* st08b.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void actSt08bKuren(GObj *volatile self);
void actSt08bEne(GObj *volatile self);
void actSt08bEnemy1(GObj *volatile self);
void actSt08bEnemy2(GObj *volatile self);
inline void actSt08bKurenMain(GObj *volatile self);
inline void actSt08aGirlYoro(GObj *volatile self);
void actSt08bDoorEvent(int x);
inline void actSt08bDoorUpEffect(GObj *volatile self);
void actSt08bDoorDownEffect(GObj *volatile self);
inline void actSt08bEneChk(GObj *volatile self);
void actSt08bKurenSwitch(GObj *volatile self);

#endif /* ST08B_H */
