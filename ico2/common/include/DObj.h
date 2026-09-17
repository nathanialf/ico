/*
 * ico2/common/include/DObj.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DObj.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DOBJ_H
#define DOBJ_H

/* The parent-link word LinkParentOfDObj copies: one long long the ROM moves with
 * an ld/sd pair off a 4-byte-aligned address, so the struct is packed. */
typedef struct {
    long long x;
} __attribute__((packed, aligned(4))) PackedLL_19CAF0;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order DObj.c's inline tail has. */
void FreeDObj(void);
void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1);
void UnlinkParentOfDObj(void *a0);

char *CSVSYSTEM_InitDObj(int id, float *lay);
void initPolygonState(char *d, float *lay);

#endif /* DOBJ_H */
