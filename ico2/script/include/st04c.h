/*
 * ico2/script/include/st04c.h
 *
 * The declarations of what st04c.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST04C_H
#define ST04C_H

#include "typedef.h"

void actSt04cDoorDownChk(GObj *volatile a0);
void actSt04cDoorDownEffect(GObj *volatile a0);
void actSt04cEneChk(GObj *volatile a0);
void actSt04cIntroChk(GObj *volatile a0);
void actSt04lDoorChk(GObj *volatile a0);

/* a vector: four floats, or the same 16 bytes as two doublewords */
typedef union StVec { /* field names derived */
    float f[4];
    long long ll[2];
} StVec; /* derived name */

#endif /* ST04C_H */
