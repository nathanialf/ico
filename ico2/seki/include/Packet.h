/*
 * ico2/seki/include/Packet.h
 *
 * The declarations of what Packet.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PACKET_H
#define PACKET_H

#include "typedef.h"

/* the header of one packet pac_MakePacket builds: the bounding box's eight corners, the material, shape and texture
   numbers, the packet size (the byte count in the low 24 bits, the clip type
   in the top byte), the next packet of the model and its DMA data. */
typedef struct PacHeader { /* field names derived */
    float box[8][4];        /* 0x00 */
    short mat;              /* 0x80 */
    short shape;            /* 0x82 */
    short tex;              /* 0x84 */
    short tex1;             /* 0x86 */
    short tex2;             /* 0x88 */
    short pad8A[3];         /* 0x8A */
    int size;               /* 0x90 */
    struct PacHeader *next; /* 0x94 */
    char *data;             /* 0x98 */
} PacHeader; /* derived name */

/* Packet.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void pac_Dump(int *a0, int size);
void pac_Init(void);
void pac_DispVu1Memory(int idx, int n, int size);
void pac_DispQW(void *p, int size);
void pac_MakePacket(Sub15C *a0);
void pac_makePacket(void *a0, int a1, int a2);
int pac_makeNormalStrip(char *obj, short *strip, int num);
int pac_makeClusterStrip(char *obj, short *strip, int num);
void pac_countOneVertexPacketSize(char *shp, char *mat);

#endif /* PACKET_H */
