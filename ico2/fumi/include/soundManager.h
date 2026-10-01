/*
 * ico2/fumi/include/soundManager.h
 *
 * The declarations of what soundManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

/* soundManager.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void sndManager(void);

void sndBgmReadyNextStage(int a, int b);

/* soundManager.o's one .sdata global */
extern int sndInitBgmCancelFlag;

void sndInit(int idx);

#endif /* SOUNDMANAGER_H */
