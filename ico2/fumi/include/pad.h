/*
 * ico2/fumi/include/pad.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what pad.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef PAD_H
#define PAD_H

extern int iosPadActRequest(int port, int id);
extern void iosPadActStop(int key);
extern void iosPadActStopAll(void);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern int iosPadConnect(void *a0, int a1, int a2, int a3);
extern void iosPadDevInit(void *a0);
extern int iosPadDevRead(void);
extern void iosPadDevReadFunc(void);
extern void iosPadDisable(void);
extern void iosPadEnable(void);
extern int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5);
extern int iosPadGetStick_func(void *dev, void *out, int mode, int a3, int a4, int a5);
extern void iosPadRead(void *pad);
extern void iosPadStickCameraCoord(void *a0, float *a1);

#endif /* PAD_H */
