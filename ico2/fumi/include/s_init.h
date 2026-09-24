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

/* s_init.c defines these `inline`, and ee-gcc 2.9 emits a file's inline
   functions after all of its other functions, in the order their names were
   first declared. That order is the ROM's (Ee2Iop at 0x145EB8 through
   soundSeSemiCommonLoadChk; the file static soundSeEnvDefaultSet and
   debug_req, first declared in s_init.c, follow), so this block keeps it. */
int Ee2Iop(int a0, int a1, int a2);
int soundOutputModeGet(void);
int soundReverbDepthGet(void);
int soundBufAdpcmChAlloc(); /* (entry, int *ch): adpcm_init.c sees the entry as its
                               AdpcmObj and s_init.c as its SqEntry, so the shared
                               declaration carries no parameter list */
void soundBufAdpcmFree(char *self);
char *soundDataAreaSearch(int *a0);
char *soundDataAreaGet(int a0, int a1, int a2, int a3);
char *soundHDDataSet(int a0, int a1, int a2, int a3, int a4);
char *soundSQDataSet(int a0, int a1, int a2, int a3, int a4);
int soundSeDefPlay(int a0, int a1, int a2, int a3);
int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
float soundSeDefVolumeRateGet(int a0);
void soundSeDefVolumeRateSet(int a0, float f);
void soundSeGroupStop(int arg);
int soundSeGroupGet(void);
void soundSePlayModeStop(int arg);
void soundReqTickProc(void);
void soundVBlank(void);
void soundSeKindBuild(void);
int soundSeSemiCommonLoadChk(void);
void _soundSeDefStop(int a0, int a1);
void soundAllocIopHeap(void);
char *soundBDDataSet(int a0, int a1, int a2, int a3, int a4, int a5);
void soundBufSegFree(int a0, int a1);
void soundDataClose(int *obj);
void soundDataOpen(int *work, int mode, int a2, int a3, int a4);
int *soundDataOpenSync(int *work);
void soundDataSegAllClose(int a0, int a1);
void soundDataSegNextStageNotUseClose();
int soundInit(void);
void soundOutputModeSet(int a0);
void soundReverbDepthSet(int a0);
void soundSeDefStop(int a0);
void soundSeDefStopNoRelease(int a0);
void soundSeEnvNotUseClose();

#endif /* S_INIT_H */
