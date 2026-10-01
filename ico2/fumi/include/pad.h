/*
 * ico2/fumi/include/pad.h
 *
 * The declarations of what pad.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef PAD_H
#define PAD_H

struct PadConf;
struct IosPadDevRec;

/* The caller's pad handle, the record iosPadConnect fills in: the device and
   configuration, then the button words iosPadRead derives. */
typedef struct IosPadCtx {      /* field names derived */
    struct IosPadDevRec *dev;   /* 0x00 */
    struct PadConf *conf;       /* 0x04 */
    int now;                    /* 0x08 */
    int trg;                    /* 0x0C */
    int rel;                    /* 0x10 */
    int word14;                 /* 0x14 masked and cleared with the three above; nothing sets it */
    int now2;                   /* 0x18 */
    int trg2;                   /* 0x1C */
    int rel2;                   /* 0x20 */
    int word24;                 /* 0x24 the copy of word14 */
} IosPadCtx;                    /* derived name */

int iosPadActRequest(int port, int id);
void iosPadActStop(int key);
void iosPadActStopAll(void);
int *iosPadActVolumeSet(int key, unsigned int val);
int iosPadConnect(void *pad, int a1, int port, struct PadConf *conf);
int iosPadDevInit(void *desc);
int iosPadDevRead(void);
void iosPadDisable(void);
void iosPadEnable(void);
int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int simulate);
int iosPadRead(void *pad);
void iosPadStickCameraCoord(void *out, float *stick);
/* pad.c's vibration enable flag (.sdata). */
extern int iosPadActRequestEnable;
/* pad.c's custom pad configuration, the record iosPadConnect takes for the
   player's own button layout */
extern struct PadConf iosPadConfCustom;
/* pad.c's default pad configuration, the layout the debug tools connect with */
extern struct PadConf iosPadConfDefault;
void iosPadActInit(void);

/* shocklist: one pad vibration, 8 bytes. Readers: ico2/fumi/ios/pad.c
 * (PadActDef), ico2/fumi/sound/s_init.c (SeInfo). Owner:
 * ico2/fumi/include/pad.h. */
typedef struct {  /* field names derived */
    int word0;    /* 0x00 */
    short voice;  /* 0x04 the voice Shock_Request plays */
    short life;   /* 0x06 */
} PadActDef;      /* derived name */

extern const PadActDef shockList[];

#endif /* PAD_H */
