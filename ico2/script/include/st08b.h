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
void actSt08bKuren(GObj *volatile a0);
void actSt08bEne(GObj *volatile a0);
void actSt08bEnemy1(GObj *volatile a0);
void actSt08bEnemy2(GObj *volatile a0);
inline void actSt08bKurenMain(GObj *volatile a0);
inline void actSt08aGirlYoro(GObj *volatile a0);
void actSt08bDoorEvent(int x);
inline void actSt08bDoorUpEffect(GObj *volatile a0);
void actSt08bDoorDownEffect(GObj *volatile a0);
inline void actSt08bEneChk(GObj *volatile a0);
void actSt08bKurenSwitch(GObj *volatile a0);

#endif /* ST08B_H */
