/*
 * ico2/sugipon/include/girlForceField.h
 *
 * The declarations of what girlForceField.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GIRLFORCEFIELD_H
#define GIRLFORCEFIELD_H

#include "sceneManager.h"

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order girlForceField.c's inline tail has. */
GirlForceFieldWork *InitGirlForceFieldGeo(char *self, SObjSimpleSetting *param);
void GirlForceFieldGeo(void);

#endif /* GIRLFORCEFIELD_H */
