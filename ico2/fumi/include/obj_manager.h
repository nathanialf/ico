/*
 * ico2/fumi/include/obj_manager.h
 *
 * The declarations of what obj_manager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

#include "typedef.h"

/* obj_manager.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void iosOmExeEachGObj(int idx, void (*fn)(int *, int), int arg);
void iosOmExeEachGObjAll(void (*fn)(int *, int), int arg);
int iosOmReturnExeEachGObj(int a0, int (*fn)(int *, int), int arg, int flag);
void iosOmGetGObjStatus(int a0, int a1);
int *iosOmSearchGObjId(int idx, int target);
int *iosOmSearchGObjIdAll(int a0);
void iosOmBeforeFuncStandard(void);
int iosOmSendMail(GObj *g, int type, void *arg);
int iosOmSendMailLink(int a0, int val5, int val6);
int iosOmExeMail(void (*func)(IosMail));
void _iosOmMain(void);
void iosOmInit(void);
void iosOmMain(void);
void iosOmCreateDL(void);

#endif /* OBJ_MANAGER_H */
