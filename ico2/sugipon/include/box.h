/*
 * ico2/sugipon/include/box.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what box.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef BOX_H
#define BOX_H

/* accessary: one accessory model set, 0x28 bytes, indexed by the object's
 * Sub15C+0x844. Readers: box.c and switch.c.inc (the two models, the
 * sub-box, and the pivot as the wheels' height and front and rear axle Z),
 * pool.c (the negated pivot), weapon.c, cage.c, puddle.c. */
typedef struct {     /* field names derived */
    int model;       /* 0x00, CSVSYSTEM_InitDObj's first model */
    int model2;      /* 0x04, its second model */
    int subModel;    /* 0x08, the sub-box model InitBoxGeo creates */
    float pivot[3];  /* 0x0C, pool.c places the model at its negation */
    float subPos[3]; /* 0x18, the sub-box's offset */
    float subRotY;   /* 0x24, the sub-box's facing in degrees */
} AccessaryRec;

extern AccessaryRec accessary[];

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order box.c's inline tail has. */
int CanHoldBox(struct GObj *a0);
void BoxDL(struct GObj *a0);
void GetBoxGlobalHoldPoint(void *a0, void *a1, void *a2);
int IsThisBoxTruck(struct GObj *a0);
void ExecBoxMoveStartReaction(struct GObj *a0, int a1);
void ExecBoxMoveEndReaction(struct GObj *a0);
int BoxGeoRestore(float *a0, float *a1);
int BoxExtGeoRestore(void);
int BoxMemoryFunc(void);

/* switch.c.inc is coalesced into box.c; its declarations follow this TU's own,
   which is the order the two headers were included in and therefore the order
   the deferred inline tail is emitted in. */
#include "switch.h"

int CheckReadyAllSwitches();
int GetBoxMode(struct GObj *a0);
void GetFloorLeverGlobalHoldPoint(void *dst, struct GObj *a1);
void GetWallLeverGlobalHoldPoint(void *out, void *lev);
void ReInitBoxGeo(struct GObj *a0);
int _checkItemCollision(void *a0);
void action(struct GObj *a0);
int checkFieldContact(struct GObj *a0, float d);
void dispWheels(struct GObj *a0);
void execFloating(struct GObj *a0);
int execNormalMove(struct GObj *a0, int a1);
int onPath(struct GObj *a0);

#endif /* BOX_H */
