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

extern int CheckReadyAllSwitches();
extern int GetBoxMode(char *a0);
extern void GetFloorLeverGlobalHoldPoint(void *dst, char *a1);
extern void GetWallLeverGlobalHoldPoint(void *out, void *lev);
extern int IsThisBoxTruck(char *a0);
extern int IsWallLeverStatus(char *a0);
extern void ReInitBoxGeo(char *a0);
extern void SetFloorLeverWithNodePoint(char *a0, char *a1, int a2);
extern void SetSwitchState(char *a0, int a1);
extern void SetWallLeverWithNodePoint(char *a0, char *a1, int a2);
extern int _checkItemCollision(void *a0);
extern void action(char *a0);
extern int checkFieldContact(char *a0, float d);
extern void dispWheels(char *a0);
extern void execFloating(char *a0);
extern int execNormalMove(char *a0, int a1);
extern int onPath(char *a0);

#endif /* BOX_H */
