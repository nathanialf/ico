/*
 * ico2/ito/include/stage_orient.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what stage_orient.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAGE_ORIENT_H
#define STAGE_ORIENT_H

void OtherStagePositionGet(float *dst, int stage, int id, int *buf);
void StageOrientInit(void);

#endif /* STAGE_ORIENT_H */
