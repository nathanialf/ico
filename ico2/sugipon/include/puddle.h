/*
 * ico2/sugipon/include/puddle.h
 *
 * The declarations of what puddle.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PUDDLE_H
#define PUDDLE_H

struct GObj;

void baseSetup(struct GObj *a0);
void copy(int pri);
void drawAreaRestore(void);
void drawAreaSetup(void);
void drawRipple(float t, void *pos);
void drawRipples(struct GObj *a0, int pri);
void leveldown(int pri);

struct PuddleWork;

struct SObjSimpleSetting;

struct PuddleWork *InitPuddleGeo(struct GObj *a0, struct SObjSimpleSetting *a1);
void PuddleDL(struct GObj *a0);

#endif /* PUDDLE_H */
