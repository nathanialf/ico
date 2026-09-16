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

extern float GetQueenBallThickness(void);
extern int InqQueenBarrierExist(void);
extern float QueenBallRadius(char *a0);
extern int QueenBarrierInqBreakable(void);
extern float QueenBarrierRadius(char *a0);
extern int QueenInqDead(void);
extern void QueenStartAttack(void);
extern void gene_enemy(volatile int g);
extern void subQueenBrainMain(volatile int g);
extern void subQueenControl(volatile int g);

#endif /* QUEEN_H */
