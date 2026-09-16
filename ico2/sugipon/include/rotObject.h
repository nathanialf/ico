/*
 * ico2/sugipon/include/rotObject.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what rotObject.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ROTOBJECT_H
#define ROTOBJECT_H

void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, char *a2);
void GetRotObjectGlobalHoldGeometry(void *pos, void *dir, void *gobj, void *posMtx, void *dirMtx);
void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3);
float GetRotObjectRotCount(char *a0);
int GetRotObjectZPlusDirection(void *gobj);
int MoveRotObjectWithHoldPoint(void *bar, void *hold, void *self, void *dir, void *up);
void SetRotObjectArmRadius(char *a0, float f);
void SetRotObjectLockFlag(char *a0, int a1);
void moveEndSE(int a0, int a1, int a2, int a3);
void moveStartSE(int a0, int a1, int a2, int a3);

#endif /* ROTOBJECT_H */
