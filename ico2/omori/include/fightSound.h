/*
 * ico2/omori/include/fightSound.h
 *
 * The declarations of what fightSound.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FIGHTSOUND_H
#define FIGHTSOUND_H

void fightSoundClose(void);
int fightSoundPlayChk(void);
void fightSoundProcessRequestPause(void);
void fightSoundProcessRequestStart(void);
void fightSoundProcess(void);
int fightSoundProcessRequestStatus(void);

#endif /* FIGHTSOUND_H */
