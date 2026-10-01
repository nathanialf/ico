/*
 * ico2/fumi/include/shockdriver.h
 *
 * The declarations of what shockdriver.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SHOCKDRIVER_H
#define SHOCKDRIVER_H

/* One voice parameter: in a voice set's voice table the shot and wave
   pattern indexes (0xFF for none) with the volume and time scale the
   request starts from; as Shock_Request's argument the voice set, the
   request's waveId and the volume and time scale it scales those by. */
typedef struct ShockParam { /* field names derived */
    /* 0x0 */ unsigned char voice;
    /* 0x1 */ unsigned char waveId;
    /* 0x2 */ unsigned char volume;
    /* 0x3 */ unsigned char timeScale;
} ShockParam; /* derived name */

/* One pattern decoder, the shot's or the wave's: the pattern, the read
   position and the step's timing. */
typedef struct VibDecode { /* field names derived */
    /* 0x0 */ unsigned char *buf;
    /* 0x4 */ unsigned short pos;
    /* 0x6 */ unsigned short acc;
    /* 0x8 */ unsigned short prev;
    /* 0xA */ unsigned short len;
    /* 0xC */ short time;
    /* 0xE */ short cnt;
} VibDecode; /* derived name */

/* One vibration request, a 64-byte slot of the ShockRequest pool: the
   decode flags (bit 0 the shot, bit 4 the wave; a zero first byte is a free
   slot), the two decoders, the wave's level ramp, the box links and the
   voice table entry it was made from. */
typedef struct SHOCKREQUEST { /* field names derived */
    /* 0x00 */ unsigned char flags;
    /* 0x01 */ unsigned char waveId;
    /* 0x02 */ unsigned char volume;
    /* 0x03 */ unsigned char timeScale;
    /* 0x04 */ VibDecode shot;
    /* 0x14 */ VibDecode wave;
    /* 0x24 */ unsigned char waveFrom;
    /* 0x25 */ unsigned char waveTo;
    /* 0x26 */ unsigned char shotRep;
    /* 0x27 */ unsigned char waveRep;
    /* 0x28 */ int key;
    /* 0x2C */ int arg;
    /* 0x30 */ struct SHOCKREQUEST *prev;
    /* 0x34 */ struct SHOCKREQUEST *next;
    /* 0x38 */ unsigned char voice;
    /* 0x39 */ unsigned char pad39[3];
    /* 0x3C */ ShockParam *org;
} SHOCKREQUEST; /* derived name */

/* the request pool header ShockRequestMemory holds: a count and the pool's
   base */
typedef struct ShockReqAlloc { /* field names derived */
    int num;
    SHOCKREQUEST *buf;
} ShockReqAlloc; /* derived name */

/* A player's request list: the newest request and the pool's allocate and
   release functions with the pool they are handed. */
typedef struct ShockRequestBox { /* field names derived */
    /* 0x0 */ SHOCKREQUEST *head;
    /* 0x4 */ SHOCKREQUEST *(*alloc)(ShockReqAlloc *pool, int arg);
    /* 0x8 */ void (*free)(SHOCKREQUEST *req, ShockReqAlloc *pool);
    /* 0xC */ ShockReqAlloc *pool;
} ShockRequestBox; /* derived name */

/* The motor state Shock_SetMotor keeps: the output and the accumulated
   level, then the type and value it hands scePadSetActDirect. */
typedef struct ShockReq { /* field names derived */
    /* 0x0 */ unsigned short out;
    /* 0x2 */ unsigned short acc;
    /* 0x4 */ unsigned char type;
    /* 0x5 */ unsigned char val;
} ShockReq; /* derived name */

/* A voice-set file as ReadShockFile loads it: this 16-byte record, then the
 * file image (charFileManager.c allocates size + 16 and reads the image just
 * past the record).  The image's halfwords at +2, +6 and +10 are the word
 * offsets of the shot, wave and voice tables, and +8 is the voice count
 * ShockDriver_GetShockVoice bounds by.  The image start is a union of its word
 * and halfword views. */
typedef struct ShockVoiceSet { /* field names derived */
    /* 0x0 */ union {
        int *word;
        unsigned short *half;
    } top;

    /* 0x4 */ int *shot;
    /* 0x8 */ int *wave;
    /* 0xC */ int *voice;
} ShockVoiceSet; /* derived name */

/* The voice set manager: its slot count, the slot table and the hook the
   decoders call on a 0x3F command (Init_ShockDriver clears it). */
typedef struct { /* field names derived */
    int count;
    int *arr; /* the voice sets (ShockVoiceSet *), held as words */
    void (*callback)(SHOCKREQUEST *req, unsigned char *cmd);
} ShockMgr; /* derived name */

/* shockdriver.c's globals (ShockRequest, the pool, is left out: pad.c reads
   the requests through SHOCKREQUEST). */
extern int ShockDriver[4];
extern ShockMgr *System_shock_driver;
extern ShockVoiceSet *ShockVoiceSetCommon;
extern ShockVoiceSet *ShockVoiceSetStage;
extern int ShockVoiceSetBuf[2];
extern ShockReqAlloc ShockRequestMemory;

void Init_Controler(ShockReq *motor);
void Init_Player(ShockRequestBox *box);
void Init_Shock(void);

void Init_ShockVoiceSet(ShockVoiceSet *set, int *data);
SHOCKREQUEST *ShockRequestBox_EndRequestFree(ShockRequestBox *box);
SHOCKREQUEST *ShockRequestBox_GetRequest(ShockRequestBox *box, int key);
int ShockRequestBox_RequestCancel(ShockRequestBox *box, int key);
SHOCKREQUEST *Shock_Request(ShockRequestBox *box, int voice, ShockParam v, int key, int arg);
void Shock_Decode(ShockRequestBox *box, unsigned char *pFlags, unsigned char *pLevel);
void Shock_SetMotor(int flags, int level, ShockReq *box, int port, int slot);
int Shock_SetShockVoiceSet(int idx, int val);
SHOCKREQUEST *dumyAllocFunc(ShockReqAlloc *pool, int arg);

void Vibration_SetDecodeData(SHOCKREQUEST *req, unsigned char *shot, unsigned char *wave,
                             unsigned char volume, unsigned char timeScale);

#endif /* SHOCKDRIVER_H */
