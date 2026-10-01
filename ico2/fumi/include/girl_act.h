/*
 * ico2/fumi/include/girl_act.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what girl_act.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GIRL_ACT_H
#define GIRL_ACT_H

struct GObj;

/* girl_act.c defines these `inline`, so the compiler emits them after the
   rest of the file in the order they are first declared: this list is the
   ROM's order of the TU's closing run, 0x17B760..0x17C840.  The four
   subGirlBrain_* states, enemy_list_compare and ACTCheckCollis_SAFE follow
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
void SetGirlDangerGObj(int a0);
void ClearGirlDangerGObj(void);
void GirlAct_BoyAndMeCollisionMail(void *a0);
int IsGirlStatusEscortEnable(int a0, int a1);
void _girlBrainHide_MakeHidePoint(float *p, float dist);
int girlBrainHideCheckIntercept(float *from, float *to, char *list, int n);
int girlBrainMain_CheckWarningMode(unsigned char check);
int isEnterHideadv_EnemyLocation(float *bpos, float *gpos);
void subGirlBrainMain(struct GObj *volatile a0);
void subGirlCollision(struct GObj *volatile a0);
void subGirlControl(struct GObj *volatile a0);
/* MAIN.MAP globals of girl_act.o's .sdata: the debug flag and the three pad
 * timers in place, then the look timer/state pair and girlcalled, which the
 * compiler emits at the end of the run (tentative definitions). */
extern int hyde_test;
extern int padtimer_stand;
extern int padtimer_walk;
extern int padtimer_run;
extern int GirlInfo[2];
extern int girlcalled;
/* MAIN.MAP globals of girl_act.o's .data: the brain's work record and the
 * hand manager's record (their types are girl_act.c's own). */
extern struct GirlBrainWork brain_val;
extern struct GirlStand handmgr;
int isEnterHideadv(void);

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

#endif /* GIRL_ACT_H */
