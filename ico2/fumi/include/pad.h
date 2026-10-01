/*
 * ico2/fumi/include/pad.h
 *
 * The declarations of what pad.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PAD_H
#define PAD_H

struct PadConf;

int iosPadActRequest(int port, int id);
void iosPadActStop(int key);
void iosPadActStopAll(void);
int *iosPadActVolumeSet(int key, unsigned int val);
int iosPadConnect(void *pad, int a1, int port, struct PadConf *conf);
int iosPadDevInit(void *a0);
int iosPadDevRead(void);
int iosPadDevReadFunc(void);
void iosPadDisable(void);
void iosPadEnable(void);
int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5);
int iosPadGetStick_func(void *dev, void *out, int mode, int a3, int a4, int a5);
int iosPadRead(void *pad);
void iosPadStickCameraCoord(void *a0, float *a1);
/* pad.c's vibration enable flag (.sdata). */
extern int iosPadActRequestEnable;
/* pad.c's custom pad configuration, the record iosPadConnect takes for the
   player's own button layout */
extern struct PadConf iosPadConfCustom;
int controler_stable_check(void *a0);
void iosPadActInit(void);

/* shocklist: one pad vibration, 8 bytes. Readers: ico2/fumi/ios/pad.c
 * (PadActDef), ico2/fumi/sound/s_init.c (SeInfo). Owner:
 * ico2/fumi/include/pad.h. */
typedef struct {  /* field names derived */
    int word0;    /* 0x00 */
    short player; /* 0x04 */
    short life;   /* 0x06 */
} PadActDef;      /* derived name */

extern const PadActDef shockList[];

#endif /* PAD_H */
