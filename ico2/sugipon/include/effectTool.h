/*
 * ico2/sugipon/include/effectTool.h
 *
 * The declarations of what effectTool.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef EFFECTTOOL_H
#define EFFECTTOOL_H

extern int targetMemo;

int EditTarget(int id);
void dispCircle2(float rad, short elev, int step);
void dispEffectToolField(int idx);
void dispXZYZCircle(float rad, int from, int to, int step);
int editParam(int id, int sel);
int execEffectTool(void);
void moveEffectToolGeometry(int idx);
int saveEffectData(int id);

#endif /* EFFECTTOOL_H */
