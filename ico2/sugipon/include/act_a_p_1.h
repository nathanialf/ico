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

struct GObj;

char *GetAP1AIMode(struct GObj *self);
int IsActCharDead(struct GObj *a0);
void SetAP1DeadStatus(struct GObj *a0);
void SetAP1HostGObj(struct GObj *self, struct GObj *host);
void SetAP1PriorLevel(struct GObj *self, int val);
void WakeUpAP1(struct GObj *a0);
void subAP1BrainMain(volatile int self);

#endif /* ACT_A_P_1_H */
