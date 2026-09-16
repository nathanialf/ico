/*
 * ico2/fumi/include/s_init.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what s_init.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef S_INIT_H
#define S_INIT_H

extern int Ee2Iop(int a0, int a1, int a2);
extern void _soundSeDefStop(int a0, int a1);
extern void soundAllocIopHeap(void);
extern void soundBDDataSet(void *buf, int a3, int kind, int mode, int a6, int size);
extern void soundBufAdpcmFree(char *self);
extern void soundBufSegFree(int a0, int a1);
extern char *soundDataAreaGet(int a0, int a1, int a2, int a3);
extern char *soundDataAreaSearch(int *a0);
extern void soundDataClose(int *obj);
extern void soundDataOpen(int *work, int mode, int a2, int a3, int a4);
extern void soundDataOpenChk(char *e);
extern int *soundDataOpenSync(int *work);
extern void soundDataSegAllClose(int a0, int a1);
extern void soundDataSegNextStageNotUseClose();
extern char *soundHDDataSet(int a0, int a1, int a2, int a3, int a4);
extern int soundInit(void);
extern int soundOutputModeGet(void);
extern void soundOutputModeSet(int a0);
extern int soundReverbDepthGet(void);
extern void soundReverbDepthSet(int a0);
extern char *soundSQDataSet(int a0, int a1, int a2, int a3, int a4);
extern int soundSeDefPlay(int a0, int a1, int a2, int a3);
extern void soundSeDefStop(int a0);
extern void soundSeDefStopNoRelease(int a0);
extern void soundSeEnvNotUseClose();
extern int soundSeGroupGet(void);
extern void soundSeGroupStop(int arg);
extern void soundSeKindBuild(void);
extern void soundSePlayModeStop(int arg);
extern int soundSeSemiCommonLoadChk(void);
extern void soundVBlank(void);

#endif /* S_INIT_H */
