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

/* The bird's own work record, hung on its sub-object (Sub15C f_830). */
typedef struct BirdWork { /* field names derived */
    float home[4];        /* 0x00, where the bird was placed */
    char scared;          /* 0x10, a mail 423 sender came within 200 */
    char pad11[15];       /* 0x11 */
    float scarer[4];      /* 0x20, where that sender stood */
    int *bga;             /* 0x30, the take-off's play node; StageAnimation.c keeps
                        its position at 0x20 and its orientation at 0x30 */
    char pad34[12];       /* 0x34 */
} BirdWork;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act_bird.c's inline tail has. */
float vector_angle_degree(void *a0, void *a1);
void subBirdControl(void *volatile gobj);
void subBirdCollision(void *volatile gobj);
void actBirdStart(void *a0);
BirdWork *InitBirdGeo(char *a0, void *a1);
void BirdAI(void);
void _ACTSendMailToBirdAll(int mail, void *data);
void Debug_StickControl(char *self);
void _ACTSendMailToBird(void *obj, int mail, void *data);
void subBirdBrainMain();
void Debug_WireString_Bird(float *pos, char *fmt, ...);

#endif /* ACT_BIRD_H */
