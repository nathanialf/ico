/*
 * ico2/sugipon/include/act_a_p_1.h
 *
 * The declarations of what act_a_p_1.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_A_P_1_H
#define ACT_A_P_1_H

struct GObj;

char *GetAP1AIMode(struct GObj *self);
int IsActCharDead(struct GObj *self);
void SetAP1DeadStatus(struct GObj *self);
void SetAP1HostGObj(struct GObj *self, struct GObj *host);
void SetAP1PriorLevel(struct GObj *self, int val);
void WakeUpAP1(struct GObj *self);
void subAP1BrainMain(struct GObj *volatile self);

#endif /* ACT_A_P_1_H */
