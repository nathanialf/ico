/*
 * ico2/fumi/include/commonact.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what commonact.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef COMMONACT_H
#define COMMONACT_H

struct GObj;

void ACTAcceptMail(struct GObj *a0, int a1);
void ACTAdjustPlane(struct GObj *a0, void *wall); /* wall: the wall record the root is laid against */
int ACTGetOrientFromIntrK(char *self, int kind, void *buf, int i);

struct IntrMail; /* act.h */

void ACTRunIntrCorrect(struct GObj *self, struct IntrMail *a1, struct IntrMail *a2);
void ACTSendMailCorrect(struct GObj *a0, int a1);
void ACTSetPositionWithFitting(void *a0, float *pos);
void ACT_LAYOUT_GAMEOVER(void);
int CollisCheckInRope(void *a0, struct GObj *chain);
void ContinueCorrectPosition(void *obj);
void ControlMotionOrient(int a0, int a1);
void DamageFunc(char *a0);
void GetCorrectOrientOfChain(void *buf, void *obj);
int IsCorrectPosition(struct GObj *a0);
int SetMotionDirectionSmooze(struct GObj *a0, float *dir, float s);
void StartCorrectPosition(struct GObj *a0, float *pos, float *dir, int mode, float t);
void TestCageUpDown(int cage, struct GObj *gobj);
int _ACTCorrectMsg(struct GObj *self, int msg, void *arg);
void _ACTDebugPrint(struct GObj *a0);
int _ACTMotDirSmzDirect(char *a0, float *a1);
void _boxbar_set_sound(struct GObj *a0, int mode);
void actAfterDown(struct GObj *volatile a0);
void actAfterFly(struct GObj *volatile a0);
void actAfterForceRope(struct GObj *volatile a0);
void actAfterForceRopeSwing(struct GObj *volatile a0);
void actAfterJump(struct GObj *volatile a0);
void actAfterRopeJump(struct GObj *volatile a0);
void afterCommonBar(struct GObj *volatile a0);
void afterCommonOneWall(int x);
void afterCommonRevive(volatile unsigned int a0);
void afterCommonRope(struct GObj *volatile a0);
void afterCommonRopeTurnSpecial(struct GObj *volatile a0);
void afterCommonStone(struct GObj *volatile a0);
void afterCommonTruckLever(struct GObj *volatile a0);
void flyCoreLoop(struct GObj *a0, struct GObj *target, int flag);
void subCommonIdle(struct GObj *volatile a0);
float *test_CURRENTORIENT(struct GObj *a0);
float *test_CURRENTROOT(struct GObj *a0);
void DownFunc(char *a0);
int FloorIsTruck(struct GObj *a0);
void afterCommonRopeCliff(char *a0);
void afterCommonBox(struct GObj *volatile a0);
void actAfterFall(struct GObj *volatile a0);
void ClipCollisionWithField(char *a0);

/* idle-mot-def: one idling motion per actor kind, 0x0C bytes. Reader:
 * ico2/fumi/src/commonact.c (int [][3]). Owner: ico2/fumi/include/commonact.h. */
typedef struct {   /* field names derived */
    int motion[3]; /* 0x00, indexed by Act+0x48 */
} IdlingDef;       /* derived name */
extern const IdlingDef idlingDef[];

/* act-data-tbl: one idle-motion range, 0x14 bytes, indexed by Act+0x48.
 * Reader: ico2/fumi/src/commonact.c (SetIdleMotionRange, subCommonIdle).
 * Owner: ico2/fumi/include/commonact.h. */
typedef struct {     /* field names derived */
    int idleMotion;  /* 0x00 */
    int orientRow;   /* 0x04, the motionOrient row whose nextId takes the motion */
    int orientRow2;  /* 0x08, the row that takes the second motion */
    int orientFirst; /* 0x0C, the rows whose id takes the motion */
    int orientEnd;   /* 0x10 */
} IdleRangeRec;      /* derived name */
extern IdleRangeRec actDataTbl[];

/* node-fix-ofs: one cling pose, 0x24 bytes. Reader:
 * ico2/fumi/src/commonact.c (ClingRec, SetMotionNodeFixModeParameter's
 * arguments). Owner: ico2/fumi/include/commonact.h. */
typedef struct {  /* field names derived */
    int rot[3];   /* 0x00, degrees about x, y, z */
    float pos[3]; /* 0x0C */
    int mode;     /* 0x18 */
    int motion;   /* 0x1C, the motion the cling plays */
    int node;     /* 0x20 */
} ClingRec;       /* derived name */
extern ClingRec clingData[];

/* pair-motion: one paired motion, 8 bytes. Reader: ico2/fumi/src/
 * commonact.c (BecPair). Owner: ico2/fumi/include/commonact.h. */
typedef struct { /* field names derived */
    int mot;     /* 0x00 */
    int req;     /* 0x04 */
} BecPair;       /* derived name */
extern const BecPair pairMotion[];

void _ACTCommonMailTest(struct GObj *self, int a1, int a2, int a3);

#endif /* COMMONACT_H */
