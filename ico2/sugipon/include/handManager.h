/*
 * ico2/sugipon/include/handManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what handManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef HANDMANAGER_H
#define HANDMANAGER_H

extern void HandManager(char *obj);
extern float _handManager(char *obj, char *hw, char *vec, char *ref, int node);
extern void connectToTarget(char *obj, char *hw, int na, int nb, int nc);

#endif /* HANDMANAGER_H */
