/*
 * ico2/sugipon/include/attackCheckBoundary.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what attackCheckBoundary.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ATTACKCHECKBOUNDARY_H
#define ATTACKCHECKBOUNDARY_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order attackCheckBoundary.c's inline tail has. */
int InitAttackCheckBoundaryGeo(int unused, void *obj);
void AttackCheckBoundaryGeo(void *a0);
void AttackCheckBoundaryDL(char *obj);
void actAttackCheckBoundaryStart(int *self);
float GetAttackCheckBoundaryRadius(char *a0);
char *CreateAttackCheckBoundary(int *obj, float x, float y, float z, float r);
int GetAttackCheckBoundaryManagerStatus(char *a0);
void SetAttackCheckBoundaryAttribute(char *a0, int a1);

#endif /* ATTACKCHECKBOUNDARY_H */
