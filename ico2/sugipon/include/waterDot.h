/*
 * ico2/sugipon/include/waterDot.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what waterDot.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WATERDOT_H
#define WATERDOT_H

extern char *AllocWaterDot(char *gobj, int num, int a2);
extern void DispWaterDot(int a0);
extern void EntryWaterDot(int work, void *pos, char *kind, float range);
extern int ExecWaterDot(int work);

#endif /* WATERDOT_H */
