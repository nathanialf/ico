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

typedef struct {
    char pad[0x64];
    int w64;
} WVTObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order way_sys.c's inline tail has. */
int GetWay_begin(void *a0, int a1, int a2);
void BridgeBox(void);
void DeleteGuideWay(WVTObj *o);

int GetWay_next(void *way, float *cur);
int _FUNC_GetWay_begin(void *a0, int a1, int a2, int a3);

#endif /* WAY_SYS_H */
