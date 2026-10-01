/*
 * ico2/sugipon/include/a_p_1.h
 *
 * The declarations of what a_p_1.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef A_P_1_H
#define A_P_1_H

#include "sceneManager.h"

struct GObj;

int AP1JumpReq(struct GObj *a0, int a1, void *a2);
int AP1MotReq(struct GObj *a0, int a1);
int AP1MotReqForce(struct GObj *a0, int a1);
int AP1Turn(struct GObj *a0, short a1);
int GetAP1Mode(struct GObj *a0);
int GetAP1SpecType(struct GObj *a0);
struct GObj *MakeAP1GObj(SObjSimpleSetting *a0);
void SetAP1VisualState(struct GObj *a0, int a1);
void calcSubMission(struct GObj *a0);
int fitToCol(struct GObj *a0, int a1);
int rolling(struct GObj *a0);
void updateMatrix(struct GObj *a0);
void yAxisRotFitting(struct GObj *self, void *arg2);

#endif /* A_P_1_H */
