/*
 * ico2/fumi/include/way_sys.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what way_sys.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WAY_SYS_H
#define WAY_SYS_H

/* The guide-way work block way_sys.c allocates and threads through every
 * member: 0x78 bytes, and only the words the TU reads or writes are named.
 * Every offset here is read off the ROM's own loads and stores. */
typedef struct {
    char pad00[0x10]; /* 0x00 */
    int pos[4];       /* 0x10 the current target position */
    char *w20;        /* 0x20 */
    char *w24;        /* 0x24 */
    int w28;          /* 0x28 */
    char *w2C;        /* 0x2C */
    int w30;          /* 0x30 */
    int w34;          /* 0x34 */
    int w38;          /* 0x38 */
    int w3C;          /* 0x3C */
    int w40;          /* 0x40 */
    int w44;          /* 0x44 */
    char pad48[0x8];  /* 0x48 */
    float nrm[4];     /* 0x50 the unit direction to the current way point */
    int w60;          /* 0x60 */
    int w64;          /* 0x64 the guide-way group, -1 when none */
    int w68;          /* 0x68 */
    int w6C;          /* 0x6C */
    int w70;          /* 0x70 */
    char *w74;        /* 0x74 */
} WVTObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order way_sys.c's inline tail has. */
int GetWay_begin(void *a0, int a1, int a2);
void BridgeBox(void);
void DeleteGuideWay(WVTObj *o);
int GetWay_next(WVTObj *w, float *pos);
int _FUNC_GetWay_begin(void *a0, WVTObj *a1, int a2, int a3);

#endif /* WAY_SYS_H */
