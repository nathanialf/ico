/*
 * ico2/seki/include/RegistPacket.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what RegistPacket.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef REGISTPACKET_H
#define REGISTPACKET_H

extern void reg_DispAccessoryWithShadow(char *o, char *src);
extern void reg_DispEnemy(void *sub);
extern void reg_DispMultiPri(char *o, int pri);
extern void reg_DispObj(char *o);
extern int reg_GetShinePri(int a0);
extern void reg_Init(void);
extern void reg_RenderReflection(char *o, int pri);
extern void reg_SetScissorSw(int val);
extern void reg_chooseReflectionMicroCode(int a0, int a1, int a2);
extern void reg_dispBoxLine(char *pk);
extern void reg_dispCObj(char *o);
extern void reg_dispLine(char *node, float alpha);
extern void reg_dispMObj(char *o);
extern void reg_dispNObj(char *o);
extern void reg_dispPoint(char *node, float alpha, int idx, int flag);
extern void reg_dispPointLineObj(char *o);
extern void reg_resetDissolve(int a0);
extern void reg_setCMatrixPacket(char *o, float alpha, int prilist);
extern int reg_setDissolve(float a, int pri);
extern char *reg_setMMatrixPacket(char *o, int idx);
extern char *reg_setNMatrixPacket(char *o, int idx);
extern void reg_setShape(char *o, int idx, int flag, char *pkt, char *mat);

#endif /* REGISTPACKET_H */
