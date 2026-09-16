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

extern int audioDecCreate(int *self, int a1, int a2);
extern int audioDecDelete(int *self);
extern int audioDecIsPreset(int *self);
extern int audioDecPause(int a0);
extern void audioDecReset(int *self);
extern void audioDecResume(int *self);
extern int audioDecSendToIOP(int *self);
extern void audioDecStart(int *self);
extern int pcmCallback(int a0, int *pkt, int *ctx);

#endif /* MV_AUDIODEC_H */
