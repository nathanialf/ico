/*
 * ico2/seki/include/Packet.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Packet.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef PACKET_H
#define PACKET_H

/* RECONSTRUCTION (names ours): the header of one packet pac_MakePacket
   builds: the bounding box's eight corners, the material, shape and texture
   numbers, the packet size (the byte count in the low 24 bits, the clip type
   in the top byte), the next packet of the model and its DMA data. */
typedef struct PacHeader {
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
} PacHeader;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order Packet.c's inline tail has. */
void pac_Dump(int *a0, int size);
void pac_Init(void);
void pac_DispVu1Memory(int idx, int n, int size);
void pac_DispQW(void *p, int size);
void pac_MakePacket(char *a0);
void pac_makePacket(void *a0, int a1, int a2);
int pac_makeNormalStrip(char *obj, short *strip, int num);
int pac_makeClusterStrip(char *obj, short *strip, int num);
void pac_countOneVertexPacketSize(char *shp, char *mat);

#endif /* PACKET_H */
