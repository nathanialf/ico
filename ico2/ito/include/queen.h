/*
 * ico2/ito/include/queen.h
 *
 * The declarations of what queen.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef QUEEN_H
#define QUEEN_H

float GetQueenBallThickness(void);
int InqQueenBarrierExist(void);
float QueenBallRadius(struct GObj *gobj);
int QueenBarrierInqBreakable(void);
float QueenBarrierRadius(struct GObj *gobj);
int QueenInqDead(void);
void QueenStartAttack(void);
void gene_enemy(volatile int g);
void subQueenBrainMain(volatile int g);
void subQueenControl(volatile int g);

#endif /* QUEEN_H */
