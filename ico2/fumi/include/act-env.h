/*
 * ico2/fumi/include/act-env.h
 *
 * The declarations of what act-env.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_ENV_H
#define ACT_ENV_H


struct GObj;
/* act-env.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void ACTSetEnvAllmighty(struct GObj *a0);
void GetSofaPosition(struct GObj *a0, char *a1);
void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2);
int CheckWallAttributeEdegWall(int a0);

/* ACTGetEnvironment's flag words (the caller passes the actor's status block
 * + 0x47C), set both bit by bit and by whole-word ORs.  The bits are named by
 * position. */
typedef union { /* field names derived */
    int w;

    struct {
        unsigned int b0 : 1;
        unsigned int b1 : 1;
        unsigned int b2 : 1;
        unsigned int b3 : 1;
        unsigned int b4 : 1;
        unsigned int b5 : 1;
        unsigned int b6 : 1;
        unsigned int b7 : 1;
        unsigned int b8 : 1;
        unsigned int b9 : 1;
        unsigned int b10 : 1;
        unsigned int b11 : 1;
        unsigned int b12 : 1;
        unsigned int b13 : 1;
        unsigned int b14 : 1;
        unsigned int b15 : 1;
        unsigned int b16 : 1;
        unsigned int b17 : 1;
        unsigned int b18 : 1;
        unsigned int b19 : 1;
        unsigned int b20 : 1;
        unsigned int b21 : 1;
        unsigned int b22 : 1;
        unsigned int b23 : 1;
        unsigned int b24 : 1;
        unsigned int b25 : 1;
        unsigned int b26 : 1;
        unsigned int b27 : 1;
        unsigned int b28 : 1;
        unsigned int b29 : 1;
        unsigned int b30 : 1;
        unsigned int b31 : 1;
    } bit;
} EnvFlag; /* derived name */

/* the 0x20-byte contact record (Sub15C + 0x180) the environment check keeps
   two copies of */
typedef struct { /* field names derived */
    char b[32];
} ClipCopy; /* derived name */

/* the actor's environment record (Act + 0x4B0) ACTGetEnvironment fills in:
   the wall and cliff orientations and positions, the contact objects and
   the two contact copies */
typedef struct {             /* field names derived */
    float wallOrient[4];     /* 0x0 */
    float cliffOrient[4];    /* 0x10 */
    float torchOrient[4];    /* 0x20 */
    float torchRevOrient[4]; /* 0x30 */
    float cliffEdgePos[4];   /* 0x40 */
    float cliffStepPos[4];   /* 0x50 */
    float ditchPos[4];       /* 0x60 */
    float ditchDir[4];       /* 0x70 */
    char pad80[16];
    float cliffBackPos[4]; /* 0x90 */
    float edgeOrient[4];   /* 0xA0 */
    char padB0[16];
    float edgePos[4]; /* 0xC0 */
    char padD0[32];
    float pullPos[4]; /* 0xF0 */
    char pad100[48];
    int wallWord;      /* 0x130 */
    int cliffSel;      /* 0x134 */
    float cliffHeight; /* 0x138 */
    int wallObj;       /* 0x13C */
    int boxObj;        /* 0x140 */
    int holdBoxObj;    /* 0x144 */
    int kind12Obj;     /* 0x148 */
    int pullObj;       /* 0x14C */
    int pullKind;      /* 0x150 */
    char pad154[4];
    char *swapWeapon;      /* 0x158 */
    char *frontObj;        /* 0x15C */
    char *cageObj;         /* 0x160 */
    char *bombObj;         /* 0x164 */
    char *torchRevObj;     /* 0x168 */
    int sofaObj;           /* 0x16C */
    ClipCopy wallContact;  /* 0x170 */
    ClipCopy cliffContact; /* 0x190 */
} ActEnv; /* derived name */

void ACTGetEnvironment(void *self, void *a1, float *orient, EnvFlag *flags, ActEnv *env);

#endif /* ACT_ENV_H */
