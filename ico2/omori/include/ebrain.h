/*
 * ico2/omori/include/ebrain.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what ebrain.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef EBRAIN_H
#define EBRAIN_H

/* MAIN.MAP globals: how many enemies chase the boy and the girl */
extern int eBrainBoyChaseCount;
extern int eBrainGirlChaseCount;

typedef struct EBSlot { /* field names derived */
    unsigned short status; /* 0x00, 0 idle, 1 chasing the boy, 2 chasing the girl */
    char pad2[2];
    void *target;          /* 0x04, the GObj the enemy is sent after */
    float dist[2];         /* 0x08, [0] to the boy, [1] to the girl */
    int message;           /* 0x10, the brain message waiting for the enemy */
    int chaseFrames;       /* 0x14, frames spent chasing the boy */
    void *owner;           /* 0x18, the enemy GObj the slot belongs to */
} EBSlot;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order ebrain.c's inline tail has. */
void eBrainInit(void);
int eBrainStatusSet(void *a0, int a1);
void eBrainSendMes(void *gop, int mes);
int GetStageFromLabel(int label);
int eBrainGetTargetGeneratorFromLabelStage(int label, int stage);

EBSlot *eBrainGetTarget(void *gop);
int eBrainGetTargetGeneratorFromLabel(int label);


#endif /* EBRAIN_H */
