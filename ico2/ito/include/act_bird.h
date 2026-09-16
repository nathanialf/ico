/*
 * ico2/ito/include/act_bird.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act_bird.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_BIRD_H
#define ACT_BIRD_H

extern void Debug_StickControl(char *self);
extern void _ACTSendMailToBird(void *a0, void *a1, void *a2);
extern void subBirdBrainMain();

#endif /* ACT_BIRD_H */
