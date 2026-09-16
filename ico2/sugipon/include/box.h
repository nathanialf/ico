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

int CheckReadyAllSwitches();
int GetBoxMode(char *a0);
void GetFloorLeverGlobalHoldPoint(void *dst, char *a1);
void GetWallLeverGlobalHoldPoint(void *out, void *lev);
int IsThisBoxTruck(char *a0);
int IsWallLeverStatus(char *a0);
void ReInitBoxGeo(char *a0);
void SetFloorLeverWithNodePoint(char *a0, char *a1, int a2);
void SetSwitchState(char *a0, int a1);
void SetWallLeverWithNodePoint(char *a0, char *a1, int a2);
int _checkItemCollision(void *a0);
void action(char *a0);
int checkFieldContact(char *a0, float d);
void dispWheels(char *a0);
void execFloating(char *a0);
int execNormalMove(char *a0, int a1);
int onPath(char *a0);

#endif /* BOX_H */
