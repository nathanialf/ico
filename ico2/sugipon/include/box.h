/*
 * ico2/sugipon/include/box.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what box.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BOX_H
#define BOX_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order box.c's inline tail has. */
int CanHoldBox(char *a0);
void BoxDL(char *a0);
void GetBoxGlobalHoldPoint(void *a0, void *a1, void *a2);
int IsThisBoxTruck(char *a0);
void ExecBoxMoveStartReaction(char *a0, int a1);
void ExecBoxMoveEndReaction(char *a0);
int BoxGeoRestore(float *a0, float *a1);
int BoxExtGeoRestore(void);
int BoxMemoryFunc(void);

/* switch.c.inc is coalesced into box.c; its declarations follow this TU's own,
   which is the order the two headers were included in and therefore the order
   the deferred inline tail is emitted in. */
#include "switch.h"

int CheckReadyAllSwitches();
int GetBoxMode(char *a0);
void GetFloorLeverGlobalHoldPoint(void *dst, char *a1);
void GetWallLeverGlobalHoldPoint(void *out, void *lev);
void ReInitBoxGeo(char *a0);
int _checkItemCollision(void *a0);
void action(char *a0);
int checkFieldContact(char *a0, float d);
void dispWheels(char *a0);
void execFloating(char *a0);
int execNormalMove(char *a0, int a1);
int onPath(char *a0);

#endif /* BOX_H */
