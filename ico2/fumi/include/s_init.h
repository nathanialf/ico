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

int Ee2Iop(int a0, int a1, int a2);
void _soundSeDefStop(int a0, int a1);
void soundAllocIopHeap(void);
char *soundBDDataSet(int a0, int a1, int a2, int a3, int a4, int a5);
void soundBufAdpcmFree(char *self);
void soundBufSegFree(int a0, int a1);
char *soundDataAreaGet(int a0, int a1, int a2, int a3);
char *soundDataAreaSearch(int *a0);
void soundDataClose(int *obj);
void soundDataOpen(int *work, int mode, int a2, int a3, int a4);
void soundDataOpenChk(char *e);
int *soundDataOpenSync(int *work);
void soundDataSegAllClose(int a0, int a1);
void soundDataSegNextStageNotUseClose();
char *soundHDDataSet(int a0, int a1, int a2, int a3, int a4);
int soundInit(void);
int soundOutputModeGet(void);
void soundOutputModeSet(int a0);
int soundReverbDepthGet(void);
void soundReverbDepthSet(int a0);
char *soundSQDataSet(int a0, int a1, int a2, int a3, int a4);
int soundSeDefPlay(int a0, int a1, int a2, int a3);
void soundSeDefStop(int a0);
void soundSeDefStopNoRelease(int a0);
void soundSeEnvNotUseClose();
int soundSeGroupGet(void);
void soundSeGroupStop(int arg);
void soundSeKindBuild(void);
void soundSePlayModeStop(int arg);
int soundSeSemiCommonLoadChk(void);
void soundVBlank(void);

#endif /* S_INIT_H */
