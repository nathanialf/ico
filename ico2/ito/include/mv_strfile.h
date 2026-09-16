/*
 * ico2/ito/include/mv_strfile.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_strfile.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_STRFILE_H
#define MV_STRFILE_H

extern int strFileClose(void);
extern int strFileOpen(char *a0, char *name);
extern int strFileRead(void);

#endif /* MV_STRFILE_H */
