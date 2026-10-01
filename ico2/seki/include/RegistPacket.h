/*
 * ico2/seki/include/RegistPacket.h
 *
 * The declarations of what RegistPacket.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef REGISTPACKET_H
#define REGISTPACKET_H

#include "typedef.h"

struct PacHeader;

void reg_DispAccessoryWithShadow(Sub15C *o, Sub15C *src);
void reg_DispEnemy(void *sub);
void reg_DispMultiPri(Sub15C *o, int pri);
void reg_DispObj(Sub15C *o);
int reg_GetShinePri(int a0);
void reg_Init(void);
void reg_RenderReflection(Sub15C *o, int pri);
void reg_SetScissorSw(int val);
void reg_chooseReflectionMicroCode(int a0, int a1, int a2);
void reg_dispBoxLine(struct PacHeader *pk);
void reg_dispCObj(Sub15C *o);
void reg_dispLine(char *node, float alpha);
void reg_dispMObj(Sub15C *o);
void reg_dispNObj(Sub15C *o);
void reg_dispPoint(char *node, float alpha, int idx, int flag);
void reg_dispPointLineObj(Sub15C *o);
void reg_resetDissolve(int a0);
void reg_setCMatrixPacket(Sub15C *o, float alpha, int prilist);
int reg_setDissolve(float a, int pri);
char *reg_setMMatrixPacket(Sub15C *o, int idx);
char *reg_setNMatrixPacket(Sub15C *o, int idx);
void reg_setShape(Sub15C *o, int idx, int flag, struct PacHeader *pkt, char *mat);

#endif /* REGISTPACKET_H */
