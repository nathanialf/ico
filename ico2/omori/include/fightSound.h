/*
 * ico2/omori/include/fightSound.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what fightSound.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef FIGHTSOUND_H
#define FIGHTSOUND_H

void fightSoundClose(void);
int fightSoundPlayChk(void);
void fightSoundProcessMain(void);
void fightSoundProcessRequestPause(void);
void fightSoundProcessRequestStart(void);

#endif /* FIGHTSOUND_H */
