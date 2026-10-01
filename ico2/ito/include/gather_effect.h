/*
 * ico2/ito/include/gather_effect.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gather_effect.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GATHER_EFFECT_H
#define GATHER_EFFECT_H

/* One particle of a gather effect, the particle effect's own record. */
struct GEl {        /* field names derived */
    int moving;     /* 0x00, still flying to the goal */
    char pad4[12];  /* 0x04 */
    float pos[4];   /* 0x10 */
    float vel[4];   /* 0x20 */
    char pad30[4];  /* 0x30 */
    float size;     /* 0x34, shrinks once the particle has arrived */
    char pad38[4];  /* 0x38 */
    float alpha;    /* 0x3C, fades once the particle has arrived */
    char pad40[48]; /* 0x40 */
};

/* A gather effect's view of its particle effect geometry: the particles and
   their count, then the goal they converge on, their speed, the geometry
   callback and the end callback with its argument, which the gather effect
   keeps in the geometry's user area. */
struct GGeo {                   /* field names derived */
    char pad0[36];              /* 0x00 */
    struct GEl *parts;          /* 0x24 */
    char pad28[8];              /* 0x28 */
    int n;                      /* 0x30 */
    char pad34[28];             /* 0x34 */
    float goal[4];              /* 0x50 */
    float speed;                /* 0x60 */
    int (*proc)(struct GGeo *); /* 0x64 */
    void (*endFunc)(int);       /* 0x68 */
    int id;                     /* 0x6C, the effect's id, endFunc's argument */

    union {
        int capsule;        /* the boss capsule the effect gathers at */
        volatile int *done; /* the releasing thread's done flag */
    } user;                 /* 0x70, the gather effect's caller's word */
};

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order gather_effect.c's inline tail has. */
int GatherEffect_Set(int no, void *pos, void *quat, void *goal, float speed, void (*endFunc)(int));
int GatherEffect_InqEnd(int a0);
void GatherEffect_SetGoal(int a0, void *a1);
int GatherEffect_Proc(struct GGeo *geo);

#endif /* GATHER_EFFECT_H */
