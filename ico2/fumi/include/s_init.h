/*
 * ico2/fumi/include/s_init.h
 *
 * The declarations of what s_init.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef S_INIT_H
#define S_INIT_H

struct GObj;

struct AdpcmStreamTag;

struct AdpcmOpenReq;

/* sound data area: one loaded bank, 0x30 bytes, the 16 rows of s_init.c's
 * soundDataTbl, keyed by its first word (num, bank). Readers: ico2/fumi/
 * sound/s_init.c, ico2/fumi/sound/adpcm_init.c (the stream at 0x2C); the
 * other directories hold it as the char * handle the Set and Open calls
 * return. At 0x18 a VAB or sequence keeps its SPU buffer and an ADPCM stream
 * its SPU channel mask. Owner: ico2/fumi/include/s_init.h. */
typedef struct SqEntry { /* field names derived */
    unsigned short num;  /* 0x00, the bank's row */
    unsigned short bank; /* 0x02, 10 BGM, 11 SE, 17 ADPCM */
    unsigned short mode; /* 0x04, 0 a VAB, 1 a sequence, 2 a stream */
    unsigned short seg;  /* 0x06, the SPU buffer segment */
    int bd;              /* 0x08, the VAB body's EE address */
    void *hd;            /* 0x0C, the VAB header */
    void *sq;            /* 0x10, the sequence */
    char pad14[4];

    union {
        struct {
            int addr; /* 0x18 */
            int size; /* 0x1C */
        } buf;

        long long chMask; /* 0x18 */
    } spu;

    unsigned long long seMask;     /* 0x20, the SE slots playing from it */
    int vab;                       /* 0x28, the VAB handle, -1 while closed */
    struct AdpcmStreamTag *stream; /* 0x2C */
} SqEntry; /* derived name */

/* s_init.c's `inline` functions, in the order of their definitions'
   out-of-line copies at the end of the object (first-declaration order), from
   Ee2Iop to soundSeSemiCommonLoadChk; the file statics soundSeEnvDefaultSet
   and debug_req, first declared in s_init.c, follow. */
int Ee2Iop(int a0, int a1, int a2);
int soundOutputModeGet(void);
int soundReverbDepthGet(void);
int soundBufAdpcmChAlloc(SqEntry *self, int *chp);
void soundBufAdpcmFree(SqEntry *self);
SqEntry *soundDataAreaSearch(int *a0);
SqEntry *soundDataAreaGet(int no, int bank, int mode, int seg);
SqEntry *soundHDDataSet(void *hd, int no, int bank, int mode, int seg);
SqEntry *soundSQDataSet(void *sq, int no, int bank, int mode, int seg);
int soundSeDefPlay(int a0, unsigned int a1, float *pos, int a3);
int soundSeDefPlayWithVolumeRate(int a0, unsigned int a1, float *pos, int a3, float rate);
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
SqEntry *soundBDDataSet(int bd, int no, int bank, int mode, int seg, int size);
void soundBufSegFree(int seg, int mode);
void soundDataClose(SqEntry *self);
void soundDataOpen(struct AdpcmOpenReq *work, int mode, int no, int ch, int loopNum);
SqEntry *soundDataOpenSync(struct AdpcmOpenReq *work);
void soundDataSegAllClose(int seg, int mode);
void soundDataSegNextStageNotUseClose(int a0, int a1);
int soundInit(void);
void soundOutputModeSet(int a0);
void soundReverbDepthSet(int a0);
void soundSeDefStop(int a0);
void soundSeDefStopNoRelease(int a0);
void soundSeEnvNotUseClose(int a, int b);
/* s_init.o's .sdata globals */
extern float soundSeEnvMasterVolRate;
extern int seEnvForceClose;
extern int soundIopHeapAddrs;
void soundAllocIopFree(void);
void soundSeEnvPlay(void);

/* sedef: one sound effect, 0x3C bytes. Readers: ico2/fumi/sound/s_init.c
 * (kind, volume, shock and the play bits), ico2/fumi/src/seMail.c (the mail,
 * its check, argument and target bits), ico2/common/src/debug.c,
 * ico2/sugipon/src/frameDependSequence.c (0x20).
 * Owner: ico2/fumi/include/s_init.h. */
typedef struct {                                                     /* field names derived */
    char name[32];                                                   /* 0x00 */
    int kind;                                                        /* 0x20, the seKind row */
    float volume;                                                    /* 0x24 */
    int mail;                                                        /* 0x28 */
    int (*check)(struct GObj *target, struct GObj *self, void *rec); /* 0x2C */
    int range;                  /* 0x30, how near seMailTargetDistCheck wants a target */
    unsigned short mailArg;     /* 0x34, ACTGame_SendSoundMail's argument */
    unsigned short shock;       /* 0x36, the shockList row */
    unsigned int mailMode : 4;  /* 0x38 bits 0..3, seMail's target bits */
    unsigned int playMode : 2;  /* 0 plays beside a playing copy, 1 keeps it, 2 restarts it */
    unsigned int shockStop : 1; /* the pad action stops with the sound */
    unsigned int audible : 1;   /* the slot's starting flag.bit.audible */
    unsigned int procRan : 1;   /* set once the slot's proc has run */
    unsigned int waitSkip : 1;  /* the mail is not sent while the target's sound wait runs */
    unsigned int : 22;
} SeDef; /* derived name */

/* se-env: one stage sound environment, 0x1C bytes, the rows a stage's
 * seEnvFirst..seEnvLast covers. Reader: ico2/fumi/sound/s_init.c
 * (soundSeEnvPlay, soundSeEnvDefaultSet, soundSeEnvNotUseClose). The names
 * of 0x08 to 0x14 and bit 3 are the labels debug_DispSEInfo prints for the
 * slot fields they are copied into. */
typedef struct SeEnvDef { /* field names derived */
    int se;               /* 0x00, the seDef row it plays */
    int (*proc)();        /* 0x04 */
    float volumeRate;     /* 0x08, 0 for the seDef's own volume */
    float maxVolumeRange; /* 0x0C, 0 for 500 */
    float attenuator;     /* 0x10, 0 for 1000 */
    float volumeLength;   /* 0x14, 0 for 3000 */
    /* 0x18, read as bits */
    unsigned int ownPos : 1;        /* the slot gets a position block of its own */
    unsigned int levelHeight : 1;   /* the distance is taken at the camera's height */
    unsigned int stereo : 1;        /* panned by the angle to the camera */
    unsigned int maxVolumeType : 1; /* the curve past maxVolumeRange */
    unsigned int : 28;
} SeEnvDef; /* derived name */

extern const SeEnvDef seEnv[];

/* sefile: one sound bank, 0x64 bytes, the rows a stage's seSegFirst..
 * seSegLast covers. Reader: ico2/fumi/sound/s_init.c (soundSeEnvNotUseClose:
 * the first loaded bank of each stage, compared by name), ico2/common/src/
 * charFileManager.c (ReadSoundBdFile). */
typedef struct SeBank {      /* field names derived */
    char hdPath[48];         /* 0x00, the .hd header file */
    char bdPath[48];         /* 0x30, the .bd body file */
    unsigned int loaded : 1; /* 0x60 bit 0, set while the bank is loaded */
    unsigned int : 31;
} SeBank; /* derived name */

extern const SeBank seFile[];

/* selist: one sound kind, 8 bytes. Reader: ico2/fumi/sound/s_init.c
 * (SeKind). Owner: ico2/fumi/include/s_init.h. */
typedef struct { /* field names derived */
    short num;   /* 0x00 */
    short prog;  /* 0x02, the VAB program SgSePlay plays */
    short tone;  /* 0x04 */
    short idx;   /* 0x06 */
} SeKind;        /* derived name */

extern const SeKind seList[];
extern unsigned short seKind[]; /* sekind: the selist row of each sound kind, filled at load */

#endif /* S_INIT_H */
