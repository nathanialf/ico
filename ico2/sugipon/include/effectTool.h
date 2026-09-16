/*
 * ico2/sugipon/include/effectTool.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what effectTool.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef EFFECTTOOL_H
#define EFFECTTOOL_H

extern int EditTarget(int id);
extern void dispCircle2(float rad, short elev, int step);
extern void dispEffectToolField(int idx);
extern void dispXZYZCircle(float rad, int from, int to, int step);
extern int editParam(int id, int sel);
extern int execEffectTool(void);
extern void moveEffectToolGeometry(int idx);
extern int saveEffectData(int id);

#endif /* EFFECTTOOL_H */
