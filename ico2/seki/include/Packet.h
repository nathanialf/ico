/*
 * ico2/seki/include/Packet.h
 *
 * The declarations of what Packet.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PACKET_H
#define PACKET_H

#include "typedef.h"
#include <libvu0.h>

/* one packet pac_makePacket builds, 176 bytes in June: the bounding box's
   eight corners and their centre (pac_makeBoundingBox's box[8]; the later
   builds drop it), the material, the texture slot and the slot's three texture
   numbers, the tag and polygon counts, the packet size (the byte count in the
   low 24 bits, the clip type in the top byte), the next packet of the model
   and its DMA data. */
typedef struct PacHeader {  /* field names derived */
    sceVu0FVECTOR box[9];   /* 0x00 */
    short mat;              /* 0x90 */
    short texSlot;          /* 0x92 */
    short tex;              /* 0x94 */
    short tex1;             /* 0x96 */
    short tex2;             /* 0x98 */
    short ntag;             /* 0x9A */
    int npoly;              /* 0x9C */
    unsigned int size : 24; /* 0xA0 */
    unsigned char clip;     /* 0xA3 */
    struct PacHeader *next; /* 0xA4 */
    char *data;             /* 0xA8 */
    char padAC[4];
} PacHeader; /* derived name */

/* one colour of a line record, as the GS RGBAQ register takes it */
typedef struct PacColor { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} PacColor; /* derived name */

/* one 144-byte line record pac_makePacket builds and RegistPacket.c draws in
   June: a line's two vertices and texture coordinates.  A point keeps its
   last screen position in pos[1] and per trail index its screen positions
   at 0x40.  Then the two colours, the texture number (-1 for none), the
   blend and the type (1 a point, 2 a line, 0 the end of the list). */
typedef struct PacLine {    /* field names derived */
    sceVu0FVECTOR pos[2];   /* 0x00 */
    sceVu0FVECTOR uv[2];    /* 0x20 */
    sceVu0IVECTOR trail[3]; /* 0x40 */
    char pad70[16];
    PacColor col0;  /* 0x80 */
    PacColor col1;  /* 0x84 */
    short tex;      /* 0x88 */
    short blend;    /* 0x8A */
    short reserved; /* 0x8C, cleared when the record is built */
    short type;     /* 0x8E */
} PacLine;          /* derived name */

/* the 160-byte record (June; 144 in the later builds) a line part's group
   record points at: the line records at +0xC, which RegistPacket.c's line
   display walks */
typedef struct PacLineSet { /* field names derived */
    char pad00[12];
    PacLine *lines; /* 0x0C */
    char pad10[144];
} PacLineSet; /* derived name */

struct PObjMaterial;

struct PObjPart;

struct PObjModel;

struct PObjTexInfo;

/* Packet.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void pac_Dump(int *data, int size);
void pac_Init(void);
void pac_DispVu1Memory(int idx, int n, int size);
void pac_MakePacket(Sub15C *o);

#endif /* PACKET_H */
