/*
 * ico2/ito/include/mv_videodec.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_videodec.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_VIDEODEC_H
#define MV_VIDEODEC_H

void Free(int a0);
int videoCallback(int a0, char *pkt, int *a2);
void videoDecAbort(int a0);
int videoDecCreate(int self);
int videoDecDelete(int a0);
int videoDecFlush(int a0);
int videoDecGetState(int a0);
int videoDecIsFlushed(int *self);
void videoDecMain(int *self);
int videoDecSetStream(void);

#endif /* MV_VIDEODEC_H */
