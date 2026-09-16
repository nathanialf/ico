/*
 * ico2/ito/include/queen.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what queen.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef QUEEN_H
#define QUEEN_H

float GetQueenBallThickness(void);
int InqQueenBarrierExist(void);
float QueenBallRadius(char *a0);
int QueenBarrierInqBreakable(void);
float QueenBarrierRadius(char *a0);
int QueenInqDead(void);
void QueenStartAttack(void);
void gene_enemy(volatile int g);
void subQueenBrainMain(volatile int g);
void subQueenControl(volatile int g);

#endif /* QUEEN_H */
