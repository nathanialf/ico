/*
 * ico2/fumi/include/act.h
 *
 * The declarations of what act.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_H
#define ACT_H

struct GObj;

struct Act;

struct GProc;

struct IosPadStick;

/* act.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void actInitialize_geo(void *self);
void actInitialize_only_charcter(char *self);
int ACTReserveTarget(struct GObj *self, void *arg, int mail);
void _ACTRun(int n);
void _ACTWait(int frames);
struct GProc *actCreateSubThreadGOppArg(void (*fn)(), int pri);
struct GProc *actCreateSubThread(void (*fn)(), int pri);
void actSetInterrupt(char *self, int val);
void ConvertStickToAbsCoord(void *out, struct IosPadStick *stick);
void ActSetStartBrainStatus(struct GObj *self, int status);
void actWaitCondition(int value, int mask);

void ACTDebugMove(struct GObj *self, int a1);
void actChangeActBrain(struct GObj *self, void (*fn)(), struct GProc **slot);
void actChangeActMain(struct GObj *self, void (*fn)(), struct GProc **slot);
void actCreateMotionThread(void (*fn)(), int pri, struct GProc **slot);
struct Act *actInitialize(struct GObj *self);
void actInitialize_ext_charcter(struct GObj *self);

/* act-mode-def: one act mode, 0x50 bytes, indexed by Act+0x30. Readers:
 * ico2/fumi/src/act.c (the act per actor kind, the mail, the intr-list
 * start, the flag bits), act-game.c, boyact.c, commonact.c, enemy_act.c,
 * girl_act.c (the flag bits, boyact.c and commonact.c the name too). Owner:
 * ico2/fumi/include/act.h. */
typedef struct { /* field names derived */
    struct {
        void (*act)(); /* +0x00, the mode's act function */
        int word4;     /* +0x04, compared across a mode change */
        int word8;     /* +0x08 */
    } ent[3];          /* 0x00, one per actor kind (Act+0x44) */

    char name[32];      /* 0x24, the debug name */
    int mail;           /* 0x44, ACTSendMailCorrect's mail */
    int intrList;       /* 0x48, the first actIntrList row */
    /* 0x4C, the mode's flag bits; a bit with no reader is named by its place */
    unsigned int escort : 1;   /* bit 0, an escort status (IsGirlStatusEscortEnable) */
    unsigned int holdDir : 1;  /* bit 1, Act flags18 bit 45: the stick does not turn the boy */
    unsigned int skipMarked : 1; /* bit 2, the flagged mail lists are skipped */
    unsigned int saveInfo : 1; /* bit 3, ACTGame_SaveActorInformation saves the position */
    unsigned int bit4 : 1;     /* bit 4, nothing in September reads it */
    unsigned int softIk : 1; /* bit 5, the girl's soft IK rate */
    unsigned int pullUp : 1;   /* bit 6, handoff_heroin does not let the girl go */
    unsigned int keepHand : 1; /* bit 7, actCommonBecarry: the boy keeps the girl's hand */
    unsigned int stopMail : 1; /* bit 8, a stopped enemy without the girl mails 242 */
    unsigned int onChain : 1;  /* bit 9, ACTGame_isHangChain */
    unsigned int bit10 : 1;    /* bit 10, nothing in September reads it */
    unsigned int carried : 1;  /* bit 11, actCommonBecarry ends the girl's carry */
    unsigned int bit12 : 1;    /* bits 12-14, set in no mode and read by nothing */
    unsigned int bit13 : 1;
    unsigned int bit14 : 1;
    unsigned int : 17;
} ActModeRec; /* derived name */
extern const ActModeRec actModeTbl[];

/* act-intrlist: one actor mail entry, 0x18 bytes; lists end at the entry
 * whose kind is 396. Readers: ico2/fumi/src/act.c (BeforeFunc,
 * act_check_intr_list, act_check_mail) and commonact.c (ACTRunIntrCorrect).
 * Owner: ico2/fumi/include/act.h. */
typedef struct IntrMail {                           /* field names derived */
    void (*motion)(int);                            /* 0x00, motion thread 21 */
    void (*extra)(int);                             /* 0x04, motion thread 22 */
    void (*handler)(char *self, int id, void *arg); /* 0x08, every frame the mail is held */
    void (*accept)(char *self, int id, void *arg);  /* 0x0C, when the mail is accepted */
    unsigned short kind;                            /* 0x10, the mail id */
    short mode;                                     /* 0x12, the act mode it switches to */
    unsigned int flags;                             /* 0x14, bit 18: entry live */
} IntrMail; /* derived name */
extern IntrMail actIntrList[];

#endif /* ACT_H */
