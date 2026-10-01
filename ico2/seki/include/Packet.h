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

/* one packet pac_makePacket builds, 160 bytes: the bounding box's eight
   corners, the material, the texture slot and the slot's three texture
   numbers, the tag and polygon counts, the packet size (the byte count in the
   low 24 bits, the clip type in the top byte), the next packet of the model
   and its DMA data. */
typedef struct PacHeader {  /* field names derived */
    sceVu0FVECTOR box[8];   /* 0x00 */
    short mat;              /* 0x80 */
    short texSlot;          /* 0x82 */
    short tex;              /* 0x84 */
    short tex1;             /* 0x86 */
    short tex2;             /* 0x88 */
    short ntag;             /* 0x8A */
    int npoly;              /* 0x8C */
    unsigned int size : 24; /* 0x90 */
    unsigned char clip;     /* 0x93 */
    struct PacHeader *next; /* 0x94 */
    char *data;             /* 0x98 */
    char pad9C[4];
} PacHeader; /* derived name */

struct PObjMaterial;

struct PObjPart;

struct PObjModel;

struct PObjTexInfo;

/* Packet.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void pac_Dump(int *a0, int size);
void pac_Init(void);
void pac_DispVu1Memory(int idx, int n, int size);
void pac_DispQW(void *p, int size);
void pac_MakePacket(Sub15C *a0);
void pac_makePacket(struct PObjModel *obj, int a1, int a2);
int pac_makeNormalStrip(struct PObjPart *obj, short *strip, int num);
int pac_makeClusterStrip(struct PObjPart *obj, short *strip, int num);
void pac_countOneVertexPacketSize(struct PObjMaterial *mat, struct PObjTexInfo *tex);

#endif /* PACKET_H */
