/*
 * ico2/sugipon/include/flag.h
 *
 * The declarations of what flag.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FLAG_H
#define FLAG_H

struct GObj;

void SetFlag4PointFixID(struct GObj *self, int a1, int id);

typedef struct { /* field names derived */
    float m[4];
} Vec4Flag; /* derived name */

/* The InitClothes config record, the same 0x1C-byte layout clothTest.c
   carries (rows, spacing, columns, anchors, texture, weight). */
typedef struct ClothCfg { /* field names derived */
    int num;         /* 0x00  rows, and -1 ends the array */
    float segLength; /* 0x04  the spacing between rows */
    int div;         /* 0x08  columns */
    int wrap;        /* 0x0C  nonzero when the last column joins the first */
    void *anchors;   /* 0x10 */
    void *tex;       /* 0x14  null means the untextured mesh */
    float weight;    /* 0x18  the fall added to each point a step */
} ClothCfg; /* derived name */

/* one word of a record, read and written through a union member: the
   node flags' bit clears and InitFlagGeo's float stores */
typedef union { /* field names derived */
    long long ll;
    int i;
    float f;
    short h;
} FlagNodeWord; /* derived name */

/* The sub record's display-list buffers (0xC the matrices, 0x10 the
   vectors, 0x870 the 80-byte nodes) freed and reallocated for n nodes, and
   the nodes reset; worm.c and boy.c carry the same block.  The block has its
   own counter, and each node's 0.0f words are stored from one float set at
   the top of the loop body. */
#define FLAG_ALLOC_NODES(o, num) /* derived name */ \
    {                                                                                              \
        int n;                                                                                     \
        if ((o)->nodeMtx != 0) {                                                                   \
            iosFree((void *)((o)->nodeMtx & 0x0FFFFFFF));                                          \
        }                                                                                          \
        if ((o)->nodeQuat != 0) {                                                                  \
            iosFree((void *)((o)->nodeQuat & 0x0FFFFFFF));                                         \
        }                                                                                          \
        *(char **)((char *)(o) + 0xC) = 0;                                                         \
        *(char **)((char *)(o) + 0x10) = 0;                                                        \
        *(char **)((char *)(o) + 0xC) =                                                            \
            iosMallocDebug(ios_partition_seki, (num) * 64, __FILE__, __LINE__);                    \
        *(char **)((char *)(o) + 0x10) =                                                           \
            iosMallocDebug(ios_partition_seki, (num) * 16, __FILE__, __LINE__);                    \
        (o)->nodeNum = (num);                                                                      \
        if ((o)->nodes != 0) {                                                                     \
            iosFree((void *)((int)(o)->nodes & 0x0FFFFFFF));                                       \
        }                                                                                          \
        (o)->nodes = iosMallocDebug(ios_partition_seki, (num) * 80, __FILE__, __LINE__);           \
        for (n = 0; n < (num); n++) {                                                              \
            float zero = 0.0f;                                                                     \
            (o)->nodes[n].flags.ll &= ~1;                                                          \
            (o)->nodes[n].flags.ll &= ~2;                                                          \
            (o)->nodes[n].pos[0] = zero;                                                           \
            (o)->nodes[n].pos[1] = zero;                                                           \
            (o)->nodes[n].pos[2] = zero;                                                           \
            (o)->nodes[n].pos[3] = 1.0f;                                                           \
            (o)->nodes[n].flags.ll &= ~4;                                                          \
            (o)->nodes[n].fade = zero;                                                             \
            (o)->nodes[n].alpha = 1.0f;                                                            \
            *(short *)((char *)&(o)->nodes[n] + 0x3A) = 0;                                         \
            (o)->nodes[n].scale[0] = 1.0f;                                                         \
            (o)->nodes[n].scale[1] = 1.0f;                                                         \
            (o)->nodes[n].scale[2] = 1.0f;                                                         \
        }                                                                                          \
        (o)->dispType = 2;                                                                         \
    }
#endif /* FLAG_H */
