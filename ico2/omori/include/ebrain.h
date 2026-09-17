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

typedef struct EBSlot {
    unsigned short f0; /* 0x00 status */
    char pad2[2];
    void *f04;     /* 0x04 target GObj */
    float dist[2]; /* 0x08 [0]=to boy, 0x0C [1]=to girl */
    int f10;       /* 0x10 message */
    int f14;       /* 0x14 */
    void *f18;     /* 0x18 owner GObj */
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

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct StageLabelRange {
    char pad0[0x128];
    int labelTop; /* 0x128 */
    int labelEnd; /* 0x12C */
    char pad130[0x190 - 0x130];
    unsigned int f190; /* 0x190 */
} StageLabelRange;

#endif /* EBRAIN_H */
