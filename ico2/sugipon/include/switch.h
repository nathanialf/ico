/*
 * ico2/sugipon/include/switch.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what switch.c.inc defines, in the order the
 * coalescing TU (box.c) declared them, which is the order its inline tail is
 * emitted in; every type here is read from the ROM's calling convention at
 * the call sites.
 */

#ifndef SWITCH_H
#define SWITCH_H

#include "sceneManager.h"

struct GObj;

/* The floor and wall lever geometry block InitFloorLeverGeo returns: eight
 * words, read back as such at box.c's own call sites.  RECONSTRUCTION: the
 * name is ours, and it deliberately is not FloorLeverGeo, which MAIN.MAP
 * gives to the lever's per-frame function in the same TU. */
typedef struct {     /* field names derived */
    short shake;     /* 0x00, the X rock the lever gives while it springs back */
    short angle;     /* 0x02, the lever's Z angle */
    int state;       /* 0x04, 0 at rest, 1 or -1 once thrown */
    int timer;       /* 0x08, frames since the lever was thrown */
    int base;        /* 0x0C, the base DObj, kept as a word: the ROM orders its
                        store and the handle's table load as an int store's */
    char *handle;    /* 0x10, the handle DObj, drawn turned by the two angles */
    int linked;      /* 0x14, nonzero once the lever is parented to the floor under it */
    int linkWait;    /* 0x18, frames counted before the parenting probe */
    int (*trigger)(struct GObj *, int); /* 0x1C, called with the parent object and the state */
} LeverGeoWork;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order box.c's inline tail has. */
int InitSwitchGeo(void);
void SwitchGeo(void);
void SwitchDL(void);
void SetSwitchTriggerFunc(struct GObj *a0, int (*a1)(struct GObj *, int));
void SetSwitchState(char *a0, int a1);
void SetFloorLeverWithNodePoint(struct GObj *a0, struct GObj *a1, int a2);
int CanFloorLeverPull(char *a0);
LeverGeoWork *InitFloorLeverGeo(char *a0, SObjSimpleSetting *a1);
int GetFloorLeverAngle(char *a0);
void SetWallLeverWithNodePoint(struct GObj *a0, struct GObj *a1, int a2);
int CanWallLeverPull(char *a0);
int IsWallLeverStatus(char *a0);
LeverGeoWork *InitWallLeverGeo(char *a0, SObjSimpleSetting *a1);
int GetWallLeverAngle(char *a0);

#endif /* SWITCH_H */
