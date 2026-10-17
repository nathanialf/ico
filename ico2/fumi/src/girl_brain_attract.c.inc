/* girl_brain_attract.c.inc: the girl brain's "attract" state, #included as
 * source into girl_act.c.  Its includer in the 2002 tree is
 * girl_brain_main.c.inc, which is not split out, so the include sits at the
 * point of girl_act.c that girl_brain_main.c.inc's text occupies. */

static int ATGoalTurnMail(void *actor, float *dir, int node);
/* void (void *, int, void *, void *) here, int (char *, int, void *, void *) in mail-add-data.h */
extern void ActSendMail_WithAdditionalData(void *gop, int msg, void *sender, void *data);

static void *attractMailData; /* derived name */

/* expanded twice in subGirlBrain_Attract: turn toward the target, and when
   already facing it send the attract mail with the target attached.  The
   result (whether a turn was started) is dropped by both callers. */
static inline int girlAttractTurnMailL(void *actor, void *obj, float *from,
                                       float *to) /* derived name */
{
    float dir[4];

    _OrientXZGV(dir, from, to);
    if (ATGoalTurnMail(actor, dir, 0x2C)) {
        return 1;
    }
    attractMailData = obj;
    ActSendMail_WithAdditionalData(actor, 0x156, actor, &attractMailData);
    return 0;
}

/* the same turn toward the boy, then the plain mail */
static inline int girlAttractTurnMailR(void *actor, float *from, float *to) /* derived name */
{
    float dir[4];

    _OrientXZGV(dir, from, to);
    if (!ATGoalTurnMail(actor, dir, 0x2C)) {
        ACTSendMailCorrect(actor, 0x158);
        return 0;
    }
    return 1;
}

/* The record Act.enemy points at, as far as this file uses it: the sofa
   position the attract state hands over (copied from the actor's 0x5B0) and
   the facing _GetRootObjectOrient fills for it. */
typedef struct { /* field names derived */
    char pad0[560];
    sceVu0FVECTOR pos; /* 0x230 */
    sceVu0FVECTOR dir; /* 0x240 */
} GirlSofaWork;        /* derived name */

/* the three attract parameter sets */
static GirlAttractParam attractObjParam = {0, {0}, {0}, 0, 303, 100.0f, 100.0f}; /* derived name */

static GirlAttractParam attractSofaParam = {0,   {0},   {0},    59,
                                            241, 50.0f, 100.0f, 1}; /* derived name */

static GirlAttractParam attractBoyParam = {0, {0}, {0}, 0, 303, 100.0f, 70.0f}; /* derived name */

/* The actor entry parameter is volatile: the actor scheduler writes the
 * caller's home slot while this thread is parked in _ACTWait. */
