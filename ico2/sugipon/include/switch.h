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

/* The floor and wall lever geometry block InitFloorLeverGeo returns: eight
 * words, read back as such at box.c's own call sites. */
typedef struct {
    int w[8];
} FloorLeverGeo;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order box.c's inline tail has. */
int InitSwitchGeo(void);
void SwitchGeo(void);
void SwitchDL(void);
void SetSwitchTriggerFunc(char *a0, void *a1);
void SetSwitchState(char *a0, int a1);
void SetFloorLeverWithNodePoint(char *a0, char *a1, int a2);
int CanFloorLeverPull(char *a0);
FloorLeverGeo *InitFloorLeverGeo(char *a0, char *a1);
int GetFloorLeverAngle(char *a0);
void SetWallLeverWithNodePoint(char *a0, char *a1, int a2);
int CanWallLeverPull(char *a0);
int IsWallLeverStatus(char *a0);
FloorLeverGeo *InitWallLeverGeo(char *a0, char *a1);
int GetWallLeverAngle(char *a0);

#endif /* SWITCH_H */
