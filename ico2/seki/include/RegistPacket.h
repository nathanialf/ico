/*
 * ico2/seki/include/RegistPacket.h
 *
 * The declarations of what RegistPacket.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef REGISTPACKET_H
#define REGISTPACKET_H

#include "typedef.h"

struct PacHeader;

struct PacLine;

struct PObjMaterial;

void reg_DispAccessoryWithShadow(Sub15C *o, Sub15C *src);
/* reg_DispEnemy: RegistPacket.c's row func_00121688 (DisplayEnemy calls it with the
   object's sub where the later builds call reg_DispEnemy); it keeps the ordinal name
   until that TU lands */
void func_00121688(void *sub);
void reg_DispMultiPri(Sub15C *o, int pri);
void reg_DispObj(Sub15C *o);
int reg_GetShinePri(int shine);
void reg_Init(void);
void reg_RenderReflection(Sub15C *o, int pri);
void reg_SetScissorSw(int val);

#endif /* REGISTPACKET_H */
