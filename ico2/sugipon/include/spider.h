/*
 * ico2/sugipon/include/spider.h
 *
 * The declarations of what spider.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SPIDER_H
#define SPIDER_H

struct GObj;

/* spider-def: one spider kind, 0x20 bytes, the row a layout object's 0x30
   word picks: the hop act_a_p_1 makes when boxed in, the layout kind of its
   arm objects, the group's member count, whether the group also goes for the
   boy, the up vector's z (a_p_1's ap1LayoutUp) and whether the spider may
   attack, a float the actor converts into its flag word.  Readers: spider.c,
   a_p_1.c, act_a_p_1.c. */
typedef struct {   /* field names derived */
    float jump[3]; /* 0x00 */
    int layout;    /* 0x0C, CreateLayoutedGObj's kind */
    int count;     /* 0x10 */
    int targetBoy; /* 0x14, 1 to call the group to the boy as well */
    float upY;     /* 0x18 */
    float attack;  /* 0x1C */
} SpiderKindRec; /* derived name */

extern const SpiderKindRec spiderDef[];
extern int sgSelLine;
extern int sgInfoLine;
int CheckSpidersInsideOfReviveRange(int *out, struct GObj *gp, void *center);
int DeadAllSpiders(struct GObj *gp);
void DeleteAllSpidersOfLayoutGroup(struct GObj *gp);
struct GObj *DeleteSpiderFromLayoutGroup(struct GObj *a0, int a1);
void DispAllMemberOfSpider(struct GObj *self, int *col);
int GetAliveSpiders(struct GObj *gp);
void SetSpiderGroupReviveStatus(struct GObj *a0);
void SleepSpiderGroup(struct GObj *gp);
void WakeUpLayoutedSpiders(struct GObj *self);
void WakeupSpiderGroup(struct GObj *gp);

#endif /* SPIDER_H */
