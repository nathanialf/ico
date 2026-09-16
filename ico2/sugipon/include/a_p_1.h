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

extern int AP1JumpReq(char *a0, int a1, void *a2);
extern int AP1MotReq(char *a0, int a1);
extern int AP1MotReqForce(char *a0, int a1);
extern int AP1Turn(char *a0, short a1);
extern int GetAP1Mode(char *a0);
extern int GetAP1SpecType(char *a0);
extern char *MakeAP1GObj(char *a0);
extern void SetAP1VisualState(char *a0, int a1);
extern void calcSubMission(char *a0);
extern int fitToCol(char *a0, int a1);
extern int rolling(char *a0);
extern void updateMatrix(char *a0);
extern void yAxisRotFitting(int *self, int arg2);

#endif /* A_P_1_H */
