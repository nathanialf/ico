/*
 * ico2/fumi/include/mcdata.h
 *
 * The declarations of what mcdata.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MCDATA_H
#define MCDATA_H

struct McMgr;
struct IconFile;

/* The save's icon.sys record (964 bytes) under the SDK's name sceMcIconSys.
   The SDK's libmc.h in this tree does not declare it, so its field names are
   spelled after the SDK's, from no header on hand: derived.  The demo builds
   its save icon's record into the program (the data member mc-icon-sys,
   config/data_members.jun26.txt); nothing reads it. */
typedef struct { /* field names derived */
    unsigned char Head[4];        /* 0x0 "PS2D" */
    unsigned short Reserv1;       /* 0x4 */
    unsigned short OffsLF;        /* 0x6 */
    unsigned int Reserv2;         /* 0x8 */
    unsigned int TransRate;       /* 0xC */
    int BgColor[4][4];            /* 0x10 */
    float LightDir[3][4];         /* 0x50 */
    float LightColor[3][4];       /* 0x80 */
    float Ambient[4];             /* 0xB0 */
    unsigned char TitleName[68];  /* 0xC0 */
    unsigned char FnameView[64];  /* 0x104 */
    unsigned char FnameCopy[64];  /* 0x144 */
    unsigned char FnameDel[64];   /* 0x184 */
    unsigned char Reserve3[512];  /* 0x1C4 */
} sceMcIconSys;

int iosMcIconWriteIconsys(struct McMgr *self, const struct IconFile *p);
int iosMcIconWriteIcon(struct McMgr *self, const struct IconFile *p);

#endif /* MCDATA_H */
