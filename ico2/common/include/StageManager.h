/*
 * ico2/common/include/StageManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what StageManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

extern void CheckPoint(void);
extern void stgmgrForceSwitch(int stage);
extern void stgmgrForceSwitchWithFade(int stage, float fadeIn, float fadeOut);
extern void stgmgrForceSwitchWithFadeColor(int stage, float fadeIn, float fadeOut, unsigned char r, unsigned char g, unsigned char b);
extern void stgmgrNextStagePreLoadDistBoyMode(void);
extern void stgmgrNextStagePreLoadForceNoCancel(int val);
extern void stgmgrNextStagePreLoadForceStageSet(int val);

#endif /* STAGEMANAGER_H */
