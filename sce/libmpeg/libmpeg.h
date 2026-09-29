/*
 * sce/libmpeg/libmpeg.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libmpeg.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBMPEG_LIBMPEG_H
#define SCE_LIBMPEG_LIBMPEG_H

int sceMpegAddCallback(void *a0, int a1, int a2, int a3); /* definition in sce/ */
int sceMpegAddStrCallback();                              /* definition in sce/ */
int sceMpegCreate(void *self, void *buf, int size);       /* dominant spelling at 1 sites */
int sceMpegDelete(void);                                  /* definition in sce/ */

int sceMpegDemuxPssRing(int *dec, void *p, int n, int a3,
                        int p4);                         /* dominant spelling at 2 sites */

int sceMpegGetPicture(int *a0, unsigned int a1, int a2); /* definition in sce/ */
void sceMpegInit(void);                                  /* dominant spelling at 1 sites */
int sceMpegIsEnd(int **a0);                              /* definition in sce/ */
int sceMpegIsRefBuffEmpty(void *a0);                     /* definition in sce/ */
void sceMpegReset(int *a0);                              /* definition in sce/ */

/*
 * The library's internal symbols that one member of libmpeg.a defines and
 * another uses: they were globals across the archive's .o files in Sony's
 * link, so each is declared once here with the signature of its defining
 * member, the declaration every later member saw when the run was one file.
 */
void _Error(void *a0);                                  /* init.o */
void _Error1(int a0, int a1);                           /* init.o */
void *_dispatchMpegCallback(void *a0, void *a1);        /* mpeg.o */
void _dispatchMpegCbNodata(void *a0);                   /* mpeg.o */
void _alalcFree(int *a0);                               /* mpeg.o */
int _alalcAlloc(unsigned int *a0, int a1, unsigned int a2); /* mpeg.o */
void _sendIpuCommand(unsigned int a0);                  /* mpc.o */
int _sysbitNext(void *a0, int a1);                      /* bit.o */

/* the decoder state more than one member reads, spelled as the members that
 * first declared it spell it (the objects themselves are still in the data
 * blob) */
extern void *_theSceMpeg[];
extern int _picture_structure;
extern int _isMpeg2[];
extern int _isSecondField[];
extern int _totalFrames[];
extern int _mbcont[];
extern int _refFrame0[];
extern int _refFrame1[];
extern int _refFrame2[];
extern int _refTop0[];
extern int _refTop1[];
extern int _refTop2[];
extern int _refBot0[];
extern int _refBot1[];
extern int _refBot2[];
extern int *_forwFrame;
extern int *_backFrame;
extern int *_forwTop;
extern int *_backTop;
extern int *_forwBot;
extern int *_backBot;

#endif /* SCE_LIBMPEG_LIBMPEG_H */
