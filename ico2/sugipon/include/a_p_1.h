/*
 * ico2/sugipon/include/a_p_1.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what a_p_1.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef A_P_1_H
#define A_P_1_H

int AP1JumpReq(char *a0, int a1, void *a2);
int AP1MotReq(char *a0, int a1);
int AP1MotReqForce(char *a0, int a1);
int AP1Turn(char *a0, short a1);
int GetAP1Mode(char *a0);
int GetAP1SpecType(char *a0);
char *MakeAP1GObj(char *a0);
void SetAP1VisualState(char *a0, int a1);
void calcSubMission(char *a0);
int fitToCol(char *a0, int a1);
int rolling(char *a0);
void updateMatrix(char *a0);
void yAxisRotFitting(int *self, int arg2);

#endif /* A_P_1_H */
