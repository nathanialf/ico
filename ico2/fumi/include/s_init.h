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
int soundSeDefPlay(int a0, unsigned int a1, float *pos, int a3);
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
/* s_init.o's .sdata globals (MAIN.MAP) */
extern float soundSeEnvMasterVolRate;
extern int seEnvForceClose;
extern int soundIopHeapAddrs;
void soundAllocIopFree(void);
void soundSeEnvPlay(void);

/* sedef: one sound effect, 0x3C bytes. Readers: ico2/fumi/sound/s_init.c
 * (SeSrcDef), ico2/fumi/src/seMail.c (SeRec: mail, check, 0x34, flags),
 * ico2/common/src/debug.c, ico2/sugipon/src/frameDependSequence.c (0x20).
 * Owner: ico2/fumi/include/s_init.h. */
typedef struct {                                   /* field names derived */
    char name[32];                                 /* 0x00 */
    int kind;                                      /* 0x20, the seKind row */
    float volume;                                  /* 0x24 */
    int mail;                                      /* 0x28 */
    int (*check)(int target, int self, void *rec); /* 0x2C */
    int word30;                                    /* 0x30 */
    unsigned short mailArg;                        /* 0x34, ACTGame_SendSoundMail's argument */
    unsigned short half36;                         /* 0x36 */
    unsigned int flags;                            /* 0x38 */
} SeDef;                                           /* derived name */

/* selist: one sound kind, 8 bytes. Reader: ico2/fumi/sound/s_init.c
 * (SeKind). Owner: ico2/fumi/include/s_init.h. */
typedef struct { /* field names derived */
    short num;   /* 0x00 */
    short half2; /* 0x02 */
    short half4; /* 0x04 */
    short idx;   /* 0x06 */
} SeKind;        /* derived name */

#endif /* S_INIT_H */
