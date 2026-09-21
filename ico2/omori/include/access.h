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

/* reconstruction corrected: the ROM calls this with TWO arguments (stage and
   the pack flag) and hands the result to strcpy, and the second argument is
   what reaches GetDataFileName2 through omori/src/access.c's one-argument
   call. Declared old style, which is what lets the one-parameter definition
   in access.c stand. */
char *GetDataFileName();
char *GetDataFileName2(char *name, int isDF);

#endif /* ACCESS_H */
