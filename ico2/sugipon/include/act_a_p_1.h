/*
 * ico2/sugipon/include/act_a_p_1.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act_a_p_1.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_A_P_1_H
#define ACT_A_P_1_H

extern char *GetAP1AIMode(char *self);
extern int IsActCharDead(int *a0);
extern void SetAP1DeadStatus(int *a0);
extern void SetAP1HostGObj(char *self, int val);
extern void SetAP1PriorLevel(char *self, int val);
extern void WakeUpAP1(int *a0);
extern void subAP1BrainMain(volatile int self);

#endif /* ACT_A_P_1_H */
