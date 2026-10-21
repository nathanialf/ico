/*
 * ico2/script/include/st18a.h
 *
 * The declarations of what st18a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST18A_H
#define ST18A_H

#include "typedef.h"

void actSt18aDoorChk(GObj *volatile self);
void actSt18aDoorDownChk(GObj *volatile self);
void actSt18aSwitchLChk(GObj *volatile self);
void actSt18aSwitchRChk(GObj *volatile self);

#endif /* ST18A_H */
