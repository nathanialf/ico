/*
 * ico2/ito/include/mv_audiodec.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_audiodec.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_AUDIODEC_H
#define MV_AUDIODEC_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order mv_audiodec.c's inline tail has. */
int audioDecDelete(int *self);
void audioDecReset(int *self);
int audioDecIsPreset(int *self);
void audioDecStart(int *self);
int audioDecPause(int a0);
void audioDecResume(int *self);

int audioDecCreate(int *self, int a1, int a2);
int audioDecSendToIOP(int *self);
int pcmCallback(int a0, int *pkt, int *ctx);

#endif /* MV_AUDIODEC_H */
