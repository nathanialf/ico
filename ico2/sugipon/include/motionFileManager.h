/*
 * ico2/sugipon/include/motionFileManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionFileManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONFILEMANAGER_H
#define MOTIONFILEMANAGER_H

int AddMotionMemorySize(int a0, int a1);
int GetMotionMemorySize(int a0);
void InitMotionFile(void *buf, int a1);
void ResetDynamicMotionManager(void);

#endif /* MOTIONFILEMANAGER_H */
