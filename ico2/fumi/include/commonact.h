/*
 * ico2/fumi/include/commonact.h
 *
 * The declarations of what commonact.c defines, for the files that use
 * them.  The file name is derived.
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
void ContinueCorrectPosition(void *obj);
void ControlMotionOrient(int a0, int a1);
void GetCorrectOrientOfChain(void *buf, void *obj);
int IsCorrectPosition(struct GObj *a0);
int SetMotionDirectionSmooze(struct GObj *a0, float *dir, float s);
void StartCorrectPosition(struct GObj *a0, float *pos, float *dir, int mode, float t);
int _ACTCorrectMsg(struct GObj *self, int msg, void *arg);
void _ACTDebugPrint(struct GObj *a0);
int _ACTMotDirSmzDirect(char *a0, float *a1);
void actAfterDown(struct GObj *volatile a0);
void actAfterFly(struct GObj *volatile a0);
void actAfterForceRope(struct GObj *volatile a0);
void actAfterForceRopeSwing(struct GObj *volatile a0);
void afterCommonBar(struct GObj *volatile a0);
void afterCommonOneWall(int x);
void afterCommonRevive(volatile unsigned int a0);
void afterCommonRope(struct GObj *volatile a0);
void afterCommonStone(struct GObj *volatile a0);
void afterCommonTruckLever(struct GObj *volatile a0);
void subCommonIdle(struct GObj *volatile a0);
float *test_CURRENTORIENT(struct GObj *a0);
float *test_CURRENTROOT(struct GObj *a0);
int FloorIsTruck(struct GObj *a0);
void afterCommonBox(struct GObj *volatile a0);
void actAfterFall(struct GObj *volatile a0);

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
