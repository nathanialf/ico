/*
 * ico2/ito/include/gather_effect.h
 *
 * The declarations of what gather_effect.c defines, for the files that use
 * them.  The file name is derived.
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

int GatherEffect_Set(int no, void *pos, void *quat, void *goal, float speed, void (*endFunc)(int));
int GatherEffect_InqEnd(int id);
void GatherEffect_SetGoal(int id, void *goal);
int GatherEffect_Proc(struct GGeo *geo);

#endif /* GATHER_EFFECT_H */
