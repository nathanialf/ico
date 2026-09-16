/*
 * ico2/sugipon/include/puddle.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what puddle.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef PUDDLE_H
#define PUDDLE_H

extern void baseSetup(char *a0);
extern void copy(int pri);
extern void drawAreaRestore(void);
extern void drawAreaSetup(void);
extern void drawRipple(float t, void *pos);
extern void drawRipples(char *a0, int pri);
extern void leveldown(int pri);

#endif /* PUDDLE_H */
