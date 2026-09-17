/*
 * ico2/fumi/include/obj_manager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what obj_manager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order obj_manager.c's inline tail has. */
void iosOmExeEachGObj(int idx, void (*fn)(int *, int), int arg);
void iosOmExeEachGObjAll(void (*fn)(int *, int), int arg);
int iosOmReturnExeEachGObj(int a0, int (*fn)(int *, int), int arg, int flag);
void iosOmGetGObjStatus(int a0, int a1);
int *iosOmSearchGObjId(int idx, int target);
int *iosOmSearchGObjIdAll(int a0);
void iosOmBeforeFuncStandard(void);
int iosOmSendMail(char *self_arg, int val5, int val6);
int iosOmSendMailLink(int a0, int val5, int val6);
int iosOmExeMail(void (*func)(IosMail));

void _iosOmMain(int a0, int a1, int a2, int a3);
void iosOmInit(void);

#endif /* OBJ_MANAGER_H */
