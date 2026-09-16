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

int iosPadActRequest(int port, int id);
void iosPadActStop(int key);
void iosPadActStopAll(void);
int *iosPadActVolumeSet(int key, unsigned int val);
int iosPadConnect(void *a0, int a1, int a2, int a3);
void iosPadDevInit(void *a0);
int iosPadDevRead(void);
void iosPadDevReadFunc(void);
void iosPadDisable(void);
void iosPadEnable(void);
int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5);
int iosPadGetStick_func(void *dev, void *out, int mode, int a3, int a4, int a5);
void iosPadRead(void *pad);
void iosPadStickCameraCoord(void *a0, float *a1);

#endif /* PAD_H */
