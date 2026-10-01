/*
 * ico2/fumi/include/girl_act.h
 *
 * The declarations of what girl_act.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GIRL_ACT_H
#define GIRL_ACT_H

struct GObj;

/* girl_act.c's `inline` functions, in the order of their definitions'
   out-of-line copies at the end of the object (first-declaration order).  The
   four subGirlBrain_* states, enemy_list_compare and ACTCheckCollis_SAFE follow
   through their first declarations in girl_act.c. */
void ACTGame_GirlBeforeFunc(struct GObj *self);
void *FindGirlPullupFloorBoxGObj(void);
void actGirlSupportGBBegin(struct GObj *volatile a0);
void actGirlSupportGBLoop(struct GObj *volatile a0);
void actGirlSupportGBEnd(struct GObj *volatile a0);
void actGirlHangG3M(struct GObj *volatile a0);
void actGirlDitch3mExec(struct GObj *volatile a0);
void actGirlStand(struct GObj *volatile a0);
void actGirlWalk(struct GObj *volatile a0);
void actGirlRun(struct GObj *volatile a0);
void actGirlHang(struct GObj *volatile a0);
void actGirlBHang(struct GObj *volatile a0);
void actGirlAttack(struct GObj *volatile a0);
void actGirlBecall(struct GObj *volatile a0);
void actGirlBehanged(struct GObj *volatile a0);
void actGirlAttractAction(struct GObj *volatile a0);
void actGirlHintVoice(struct GObj *volatile a0);
void actGirlCannotReach(struct GObj *volatile a0);
void actGirlHand50(struct GObj *volatile a0);
void afterGirlHand50(struct GObj *volatile a0);
void actGirlHand100(struct GObj *volatile a0);
void afterGirlHand100(struct GObj *volatile a0);
void actGirlHand200(struct GObj *volatile a0);
void afterGirlHand200(struct GObj *volatile a0);
int NotNeedBackHand(void);
void SetGirlDangerGObj(struct GObj *a0);
void ClearGirlDangerGObj(void);
void GirlAct_BoyAndMeCollisionMail(void *a0);
int IsGirlStatusEscortEnable(int a0, int a1);
void subGirlBrainMain(struct GObj *volatile a0);
void subGirlCollision(struct GObj *volatile a0);
void subGirlControl(struct GObj *volatile a0);
/* girl_act.o's .sdata globals: the debug flag and the three pad timers, then
 * the look timer/state pair and girlcalled, which come last (tentative
 * definitions). */
extern int hyde_test;
extern int padtimer_stand;
extern int padtimer_walk;
extern int padtimer_run;
extern int GirlInfo[2];
extern int girlcalled;
/* girl_act.o's .data globals: the brain's work record and the
 * hand manager's record (their types are girl_act.c's own). */
extern struct GirlBrainWork brain_val;
extern struct GirlStand handmgr;

/* param-escape-run: one escape-run timer range, 8 bytes, [t][mode]. Reader:
 * ico2/fumi/src/girl_act.c (brain_val.limit). Owner:
 * ico2/fumi/include/girl_act.h. */
typedef struct { /* field names derived */
    int lo;      /* 0x00 */
    int hi;      /* 0x04 */
} EscapeRange;   /* derived name */

/* auto-escort: one escort point, 0x1C bytes. Reader: ico2/fumi/src/
 * girl_act.c (EscortPoint). Owner: ico2/fumi/include/girl_act.h. */
typedef struct {  /* field names derived */
    float pos[3]; /* 0x00 */
    int area;     /* 0x0C, matched with the first key */
    int point;    /* 0x10, matched with the second key */
    float range;  /* 0x14, the distance under which it applies */
    float rate;   /* 0x18, the distance factor into the girl's 0x330 */
} EscortPoint;    /* derived name */
extern const EscortPoint autoEscortData[];

#endif /* GIRL_ACT_H */
