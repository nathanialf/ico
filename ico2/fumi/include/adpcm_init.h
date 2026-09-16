/*
 * ico2/fumi/include/adpcm_init.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what adpcm_init.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ADPCM_INIT_H
#define ADPCM_INIT_H

extern void AdpcmFadeCloseAll(short a0);
extern int AdpcmFreeAreaGet(void);
extern void AdpcmInterStereoVolumeSet();
extern void AdpcmInterStereoVolumeSetAll(void);
extern int AdpcmIopBuffAlloc(void);
extern int AdpcmNotUseIopAreaFree(void);
extern void AdpcmOpen(int *self, int no, int a2, int a3);
extern int *AdpcmOpenSync(int *self);
extern void AdpcmPlay(void *a0);
extern void AdpcmStreamInit(void);
extern void AdpcmVolumeSet(int a0, int a1);
extern int *adpcmDataSet(int a0, int no, int bank, int a3, int size, int a5, int a6);
extern void adpcmPauseRequest(int val);
extern void adpcmTickProc2(int *a0);

#endif /* ADPCM_INIT_H */
