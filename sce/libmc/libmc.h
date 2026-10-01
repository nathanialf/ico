/*
 * sce/libmc/libmc.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libmc.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBMC_LIBMC_H
#define SCE_LIBMC_LIBMC_H

/* a file's date and time as the card stores it */
typedef struct sceMcStDateTime {
    unsigned char Resv2;
    unsigned char Sec;
    unsigned char Min;
    unsigned char Hour;
    unsigned char Day;
    unsigned char Month;
    unsigned short Year;
} sceMcStDateTime;

/* the 64-byte directory entry sceMcGetDir has the IOP fill, one per entry
   asked for */
typedef struct sceMcTblGetDir {
    sceMcStDateTime _Create;     /* 0x00 */
    sceMcStDateTime _Modify;     /* 0x08 */
    unsigned int FileSizeByte;   /* 0x10 */
    unsigned short AttrFile;     /* 0x14 */
    unsigned short Reserve1;     /* 0x16 */
    unsigned int Reserve2;       /* 0x18 */
    unsigned int PdaAplNo;       /* 0x1C */
    unsigned char EntryName[32]; /* 0x20 */
} sceMcTblGetDir;

int sceMcChdir(int a0, int a1, char *name, char *pwd); /* definition in sce/ */
int sceMcClose(int arg);                               /* definition in sce/ */
int sceMcDelete(int a0, int a1, char *name);           /* definition in sce/ */
int sceMcFlush(int arg);                               /* definition in sce/ */
int sceMcFormat(int a0, int a1);                       /* definition in sce/ */

int sceMcGetDir(int a0, int a1, char *name, int a3, int nblk,
                struct sceMcTblGetDir *table); /* definition in sce/ */

int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
int sceMcInit(void);
int sceMcMkdir(int a0, int a1, char *name);           /* definition in sce/ */
int sceMcOpen(int a0, int a1, char *name, int flags); /* definition in sce/ */
int sceMcRead(int a0, void *buf, int len);            /* definition in sce/ */
int sceMcSeek(int a0, int a1, int a2);                /* definition in sce/ */
int sceMcSync(int a0, int *a1, int *a2);              /* definition in sce/ */
int sceMcUnformat(int a0, int a1);                    /* definition in sce/ */
int sceMcWrite(int fd, void *buf, int len);

#endif /* SCE_LIBMC_LIBMC_H */
