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

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act_bird.c's inline tail has. */
float vector_angle_degree(void *a0, void *a1);
void subBirdControl(void *volatile gobj);
void subBirdCollision(void *volatile gobj);
void actBirdStart(void *a0);
char *InitBirdGeo(char *a0, void *a1);
void BirdAI(void);
void _ACTSendMailToBirdAll(void *a0, void *a1);

void Debug_StickControl(char *self);
void _ACTSendMailToBird(void *a0, void *a1, void *a2);
void subBirdBrainMain();

#endif /* ACT_BIRD_H */
