/*
 * ico2/omori/include/attackhit.h
 *
 * The declarations of what attackhit.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ATTACKHIT_H
#define ATTACKHIT_H

/* one row of attackData, the data-only member attack-def.o: an attack
   kind's motion, the node it hits from, its reach and power and its flags */
typedef struct { /* field names derived */
    char pad00[16];
    /* 0x10 */ int motion;    /* the motion the row belongs to */
    /* 0x14 */ int focusNode; /* the focus node a body attack hits from */
    /* 0x18 */ float radius;
    /* 0x1C */ float power;
    /* 0x20 */ unsigned int weapon : 1; /* the attack is the held weapon's */
    unsigned int down : 1;              /* it knocks the target down */
    unsigned int unguardable : 1;
    unsigned int stone : 1;  /* it is a stone hit */
    unsigned int toRoot : 1; /* the reach runs from the focus node to the root */
    unsigned int padBits : 27;
} AttackKindEntry; /* derived name */

extern const AttackKindEntry attackData[];
void CommonAttackCenter(struct GObj *gobj);

int _AttackCenter(struct GObj *gop, int group, float *pos, float *ofs, float radius,
                  struct GObj *spare);

void AttackCenter_WithDir(struct GObj *gop, int group, float *pos, float *dir, float radius);
void EnemyAttackCenter(struct GObj *gobj);

#endif /* ATTACKHIT_H */
