/*
 * ico2/fumi/include/act-env.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act-env.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_ENV_H
#define ACT_ENV_H


struct GObj;
/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act-env.c's inline tail has. */
void ACTSetEnvAllmighty(struct GObj *a0);
void GetSofaPosition(struct GObj *a0, char *a1);
void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2);
int CheckWallAttributeEdegWall(int a0);

/* RECONSTRUCTION: ACTGetEnvironment's flag words (the caller passes the
 * actor's status block + 0x47C), read both as whole words and as single-bit
 * fields; the ROM proves the one-bit field stores (and/shift/or sequences)
 * and the word ORs.  The b0..b31 names are placeholders, not the developers'. */
typedef union {
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
} EnvFlag;

/* the 0x20-byte contact record (Sub15C + 0x180) the environment check keeps
   two copies of */
typedef struct { /* field names derived */
    char b[0x20];
} ClipCopy;

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
    char pad80[0x10];
    float cliffBackPos[4]; /* 0x90 */
    float edgeOrient[4];   /* 0xA0 */
    char padB0[0x10];
    float edgePos[4]; /* 0xC0 */
    char padD0[0x20];
    float pullPos[4]; /* 0xF0 */
    char pad100[0x30];
    int wallWord;      /* 0x130 */
    int cliffSel;      /* 0x134 */
    float cliffHeight; /* 0x138 */
    int wallObj;       /* 0x13C */
    int boxObj;        /* 0x140 */
    int holdBoxObj;    /* 0x144 */
    int kind12Obj;     /* 0x148 */
    int pullObj;       /* 0x14C */
    int pullKind;      /* 0x150 */
    char pad154[0x4];
    char *swapWeapon;      /* 0x158 */
    char *frontObj;        /* 0x15C */
    char *cageObj;         /* 0x160 */
    char *bombObj;         /* 0x164 */
    char *torchRevObj;     /* 0x168 */
    int sofaObj;           /* 0x16C */
    ClipCopy wallContact;  /* 0x170 */
    ClipCopy cliffContact; /* 0x190 */
} ActEnv;

void ACTGetEnvironment(void *self, void *a1, float *orient, EnvFlag *flags, ActEnv *env);

#endif /* ACT_ENV_H */
