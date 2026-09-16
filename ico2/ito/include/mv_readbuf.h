/*
 * ico2/ito/include/mv_readbuf.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_readbuf.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_READBUF_H
#define MV_READBUF_H

int readBufBeginGet(int *a0, int *out);
int readBufBeginPut(int *a0, int *a1);
int readBufCreate(int *self);
void readBufDelete(void);
int readBufEndGet(int a0, int a1);
void readBufEndPut(int *a0, int a1);

#endif /* MV_READBUF_H */
