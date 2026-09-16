/*
 * ico2/omori/include/access.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what access.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACCESS_H
#define ACCESS_H

extern int GetDataFileName(int a0);
extern char *GetDataFileName2(char *name, int isDF);

#endif /* ACCESS_H */
