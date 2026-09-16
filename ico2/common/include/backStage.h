/*
 * ico2/common/include/backStage.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what backStage.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BACKSTAGE_H
#define BACKSTAGE_H

extern void backStageDebugTimeZero(void);
extern void backStageProcessInStage(float arg);
extern void backStageProcessInit(void);
extern void backStageProcessOutStage(void);
extern void routeSetPos(int gobj0, int gobj1, float *out, float ratio);

#endif /* BACKSTAGE_H */
