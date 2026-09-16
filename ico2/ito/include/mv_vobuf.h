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

int voBufCreate(char *self);
void voBufDecCount(int *p);
void voBufDelete(void);
void *voBufGetData(int *self);
void *voBufGetTag(int *self);
void voBufIncCount(int *self);
int voBufIsFull(int *self);
void voBufReset(volatile int *self);

#endif /* MV_VOBUF_H */
