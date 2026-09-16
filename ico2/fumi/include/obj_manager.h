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

void _iosOmMain(int a0, int a1, int a2, int a3);
void iosOmInit(void);
int iosOmSendMail(char *self_arg, int val5, int val6);

#endif /* OBJ_MANAGER_H */
