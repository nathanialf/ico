/*
 * ico2/sugipon/include/flag.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what flag.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef FLAG_H
#define FLAG_H

void SetFlag4PointFixID(char *self, int a1, int id);

typedef struct {
    float m[4];
} Vec4Flag;

/* The InitClothes config record, the same 0x1C-byte layout clothTest.c
   carries (rows, spacing, columns, anchors, texture, weight). */
typedef struct ClothCfg {
    int num;       /* 0x00  rows, and -1 ends the array */
    float f04;     /* 0x04 */
    int div;       /* 0x08  columns */
    int f0C;       /* 0x0C */
    void *anchors; /* 0x10 */
    void *tex;     /* 0x14  null means the untextured mesh */
    float f18;     /* 0x18 */
} ClothCfg;

/* The 0x15C sub-object slot, read as a union member (alias set 0) the way
   cage.c, girlForceField.c and box.c read it. */
typedef union GObjSubSlot {
    int handle;
    void *p;
} GObjSubSlot;

/* one word of a record reached through a union member (alias set 0): the
   node flags' bit clears, and the stores the ROM keeps ahead of later loads
   (InitFlagGeo lines 103, 182 and 221) */
typedef union {
    long long ll;
    int i;
    float f;
    short h;
} FlagNodeWord;

/* RECONSTRUCTION.  The sub record's display-list buffers (0xC the matrices,
   0x10 the vectors, 0x870 the 80-byte nodes) freed and reallocated for n
   nodes, the nodes reset.  The listing attributes the whole block to the one
   line that invokes it (flag.c:132, every allocation passing that line), the
   mark of a macro; worm.c and boy.c carry the same block.  Its counter is
   the block's own, which is why the ROM keeps it in a caller-saved
   register; each node's 0.0f words come from one float set at the top of
   the loop body, which is why the ROM stores them from an FPR (`mtc1 $0`)
   where a constant 0.0f store is `sw $0`. */
#define FLAG_ALLOC_NODES(o, num)                                                                   \
    {                                                                                              \
        int n;                                                                                     \
        if (*(int *)((o) + 0xC) != 0) {                                                            \
            iosFree((void *)(*(int *)((o) + 0xC) & 0x0FFFFFFF));                                   \
        }                                                                                          \
        if (*(int *)((o) + 0x10) != 0) {                                                           \
            iosFree((void *)(*(int *)((o) + 0x10) & 0x0FFFFFFF));                                  \
        }                                                                                          \
        *(char **)((o) + 0xC) = 0;                                                                 \
        *(char **)((o) + 0x10) = 0;                                                                \
        *(char **)((o) + 0xC) = iosMallocDebug(D_0063A44C, (num) * 64, __FILE__, __LINE__);        \
        *(char **)((o) + 0x10) = iosMallocDebug(D_0063A44C, (num) * 16, __FILE__, __LINE__);       \
        *(int *)((o) + 0x8) = (num);                                                               \
        if (*(int *)((o) + 0x870) != 0) {                                                          \
            iosFree((void *)(*(int *)((o) + 0x870) & 0x0FFFFFFF));                                 \
        }                                                                                          \
        *(char **)((o) + 0x870) = iosMallocDebug(D_0063A44C, (num) * 80, __FILE__, __LINE__);      \
        for (n = 0; n < (num); n++) {                                                              \
            float zero = 0.0f;                                                                     \
            ((FlagNodeWord *)(*(char **)((o) + 0x870) + n * 80 + 0x38))->ll &= ~1;                 \
            ((FlagNodeWord *)(*(char **)((o) + 0x870) + n * 80 + 0x38))->ll &= ~2;                 \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x40) = zero;                            \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x44) = zero;                            \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x48) = zero;                            \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x4C) = 1.0f;                            \
            ((FlagNodeWord *)(*(char **)((o) + 0x870) + n * 80 + 0x38))->ll &= ~4;                 \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x30) = zero;                            \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x34) = 1.0f;                            \
            *(short *)(*(char **)((o) + 0x870) + n * 80 + 0x3A) = 0;                               \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x20) = 1.0f;                            \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x24) = 1.0f;                            \
            *(float *)(*(char **)((o) + 0x870) + n * 80 + 0x28) = 1.0f;                            \
        }                                                                                          \
        *(short *)((o) + 0x84C) = 2;                                                               \
    }

#endif /* FLAG_H */
