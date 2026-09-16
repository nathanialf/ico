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

void AdpcmFadeCloseAll(short a0);
int AdpcmFreeAreaGet(void);
void AdpcmInterStereoVolumeSet();
void AdpcmInterStereoVolumeSetAll(void);
int AdpcmIopBuffAlloc(void);
int AdpcmNotUseIopAreaFree(void);
void AdpcmOpen(int *self, int no, int a2, int a3);
int *AdpcmOpenSync(int *self);
void AdpcmPlay(void *a0);
void AdpcmStreamInit(void);
void AdpcmVolumeSet(int a0, int a1);
int *adpcmDataSet(int a0, int no, int bank, int a3, int size, int a5, int a6);
void adpcmPauseRequest(int val);
void adpcmTickProc2(int *a0);

#endif /* ADPCM_INIT_H */
