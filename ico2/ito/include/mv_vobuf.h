/*
 * ico2/ito/include/mv_vobuf.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_vobuf.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_VOBUF_H
#define MV_VOBUF_H

extern int voBufCreate(char *self);
extern void voBufDecCount(int *p);
extern void voBufDelete(void);
extern void *voBufGetData(int *self);
extern void *voBufGetTag(int *self);
extern void voBufIncCount(int *self);
extern int voBufIsFull(int *self);
extern void voBufReset(volatile int *self);

#endif /* MV_VOBUF_H */
