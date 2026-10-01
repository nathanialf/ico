/*
 * ico2/ito/include/gather_effect.h
 *
 * The declarations of what gather_effect.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GATHER_EFFECT_H
#define GATHER_EFFECT_H

struct PEGeo;

int GatherEffect_Set(int no, void *pos, void *quat, void *goal, float speed, void (*endFunc)(int));
int GatherEffect_InqEnd(int id);
void GatherEffect_SetGoal(int id, void *goal);
int GatherEffect_Proc(struct PEGeo *geo);

#endif /* GATHER_EFFECT_H */
