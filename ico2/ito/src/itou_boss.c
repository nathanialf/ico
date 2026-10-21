#include "itou_boss.h"
#include "debug.h"
#include "memory.h"
#include "gobj.h"
#include "act-game.h"
#include "act.h"
#include "enemy_act.h"
#include "script.h"
#include "Matrix.h"
#include "StageAnimation.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "quaternion.h"
#include "generator.h"
#include "sugiCommon.h"
#include <string.h>
#include <libvu0.h>
#include "main.h"
#include "ios.h"
#include "particleEffect.h"
#include "gather_effect.h"
#include "itou_sub.h"
#include "itou_common.h"
#include "tableSin.h"
#include "motionManager2.h"
#include "include_asm.h"

/* One of the fifty-three capsules, in the work block InitBossCtrlGeo
   allocates (the controller's GObj work at 0x7D0): its BGA, its state (0
   closed, 1 gathering, 2 open) and the placement InitBossCtrlGeo gives it. */
typedef struct {        /* field names derived */
    BgaPlayNode *bga;   /* 0x00 */
    signed char state;  /* 0x04 */
    sceVu0FVECTOR quat; /* 0x10 */
    sceVu0FVECTOR pos;  /* 0x20 */
} CapsuleRec;           /* derived name */

/* One of the thirty grid cells gene_enemy releases enemies at in this
   build: whether a release is using it, and its position. */
typedef struct {       /* field names derived */
    signed char busy;  /* 0x00 */
    sceVu0FVECTOR pos; /* 0x10 */
} GeneCell;            /* derived name */

/* The gene_enemy threads' done flags, twelve in this build (gene_enemy
   indexes them by its thread count), then the thirty cells (0x7606A0 and
   0x7606D0..0x760A90).  This build has no boss flag block before them. */
static volatile int geneDone[12]; /* derived name */

static GeneCell geneCell[30]; /* derived name */

/* The fifty-three capsules' placements and the points their enemies are
   released at.  InitBossCtrlGeo copies each position and turns each rotation
   into the record's quaternion, and gene_enemy puts a released enemy at the
   capsule's release point. */
typedef struct {     /* field names derived */
    float rot[3][4]; /* the rotation rows, w zero */
    float pos[4];
} CapsulePlace; /* derived name */

static const CapsulePlace capsulePlace[53] = {
    /* derived name */
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {1100.0f, -763.8f, 1641.22f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {800.0f, -763.8f, 1641.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {1100.0f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {800.0f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {499.998f, -763.8f, 1641.22f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {199.998f, -763.8f, 1641.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {499.998f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {199.998f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-100.002f, -763.8f, 1641.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-100.002f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-399.911f, -763.8f, 1641.22f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-699.91f, -763.8f, 1641.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-399.911f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-699.91f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-999.913f, -763.8f, 1641.22f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-1299.91f, -763.8f, 1641.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-999.913f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-1299.91f, -363.8f, 1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-1599.91f, -363.8f, 1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {1100.1f, -763.8f, -1641.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-1300.1f, -763.8f, -1641.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-1600.1f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-1300.1f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-1000.1f, -763.8f, -1641.22f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-700.097f, -763.8f, -1641.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-700.097f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-400.097f, -763.8f, -1641.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-400.097f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-100.188f, -763.8f, -1641.22f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {199.811f, -763.8f, -1641.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-100.188f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {199.811f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {499.814f, -763.8f, -1641.22f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {799.811f, -763.8f, -1641.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {499.814f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {799.811f, -363.8f, -1441.2f, 1.0f}},
    {{{-1.0f, 0.0f, 1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {1099.81f, -363.8f, -1441.2f, 1.0f}},
    {{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
     {-1894.99f, -763.8f, 1884.19f, 1.0f}},
    {{{0.987688f, 0.0f, 0.156434f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.156434f, 0.0f, 0.987688f, 0.0f}},
     {-2187.96f, -763.8f, 1838.31f, 1.0f}},
    {{{0.951057f, 0.0f, 0.309017f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.309017f, 0.0f, 0.951057f, 0.0f}},
     {-2470.14f, -763.8f, 1747.17f, 1.0f}},
    {{{0.891007f, 0.0f, 0.45399f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.45399f, 0.0f, 0.891007f, 0.0f}},
     {-2734.59f, -763.8f, 1613.0f, 1.0f}},
    {{{0.809017f, 0.0f, 0.587785f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.587785f, 0.0f, 0.809017f, 0.0f}},
     {-2974.8f, -763.8f, 1439.12f, 1.0f}},
    {{{0.707107f, 0.0f, 0.707107f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.707107f, 0.0f, 0.707107f, 0.0f}},
     {-3184.85f, -763.8f, 1229.8f, 1.0f}},
    {{{0.587785f, 0.0f, 0.809017f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.809017f, 0.0f, 0.587785f, 0.0f}},
     {-3359.56f, -763.8f, 990.199f, 1.0f}},
    {{{0.45399f, 0.0f, 0.891007f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.891007f, 0.0f, 0.45399f, 0.0f}},
     {-3494.65f, -763.8f, 726.217f, 1.0f}},
    {{{-1.0f, 0.0f, -1.22461e-16f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {1.22461e-16f, 0.0f, -1.0f, 0.0f}},
     {-1895.0f, -763.8f, -1884.2f, 1.0f}},
    {{{-0.987688f, 0.0f, 0.156434f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.156434f, 0.0f, -0.987688f, 0.0f}},
     {-2187.97f, -763.8f, -1838.32f, 1.0f}},
    {{{-0.951057f, 0.0f, 0.309017f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.309017f, 0.0f, -0.951057f, 0.0f}},
     {-2470.15f, -763.8f, -1747.17f, 1.0f}},
    {{{-0.891007f, 0.0f, 0.45399f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.45399f, 0.0f, -0.891007f, 0.0f}},
     {-2734.6f, -763.8f, -1613.01f, 1.0f}},
    {{{-0.809017f, 0.0f, 0.587785f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.587785f, 0.0f, -0.809017f, 0.0f}},
     {-2974.81f, -763.8f, -1439.12f, 1.0f}},
    {{{-0.707107f, 0.0f, 0.707107f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.707107f, 0.0f, -0.707107f, 0.0f}},
     {-3184.86f, -763.8f, -1229.8f, 1.0f}},
    {{{-0.587785f, 0.0f, 0.809017f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.809017f, 0.0f, -0.587785f, 0.0f}},
     {-3359.58f, -763.8f, -990.197f, 1.0f}},
    {{{-0.45399f, 0.0f, 0.891007f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {-0.891007f, 0.0f, -0.45399f, 0.0f}},
     {-3494.66f, -763.8f, -726.213f, 1.0f}},
};

/* the thirty points on a 300-unit grid the cells take (in LightWave
   coordinates: actBossCtrlStart converts each into its cell) */
static const float geneCellPos[30][4] = {
    /* derived name */
    {-600.0f, 5.0f, -600.0f, 0.0f}, {-300.0f, 5.0f, -600.0f, 0.0f}, {0.0f, 5.0f, -600.0f, 0.0f},
    {300.0f, 5.0f, -600.0f, 0.0f},  {600.0f, 5.0f, -600.0f, 0.0f},  {900.0f, 5.0f, -600.0f, 0.0f},
    {-600.0f, 5.0f, -300.0f, 0.0f}, {-300.0f, 5.0f, -300.0f, 0.0f}, {0.0f, 5.0f, -300.0f, 0.0f},
    {300.0f, 5.0f, -300.0f, 0.0f},  {600.0f, 5.0f, -300.0f, 0.0f},  {900.0f, 5.0f, -300.0f, 0.0f},
    {-600.0f, 5.0f, 0.0f, 0.0f},    {-300.0f, 5.0f, 0.0f, 0.0f},    {0.0f, 5.0f, 0.0f, 0.0f},
    {300.0f, 5.0f, 0.0f, 0.0f},     {600.0f, 5.0f, 0.0f, 0.0f},     {900.0f, 5.0f, 0.0f, 0.0f},
    {-600.0f, 5.0f, 300.0f, 0.0f},  {-300.0f, 5.0f, 300.0f, 0.0f},  {0.0f, 5.0f, 300.0f, 0.0f},
    {300.0f, 5.0f, 300.0f, 0.0f},   {600.0f, 5.0f, 300.0f, 0.0f},   {900.0f, 5.0f, 300.0f, 0.0f},
    {-600.0f, 5.0f, 600.0f, 0.0f},  {-300.0f, 5.0f, 600.0f, 0.0f},  {0.0f, 5.0f, 600.0f, 0.0f},
    {300.0f, 5.0f, 600.0f, 0.0f},   {600.0f, 5.0f, 600.0f, 0.0f},   {900.0f, 5.0f, 600.0f, 0.0f},
};

/* the number of gene_enemy threads started, which indexes their done
   flags, and the number of releases under way */
static int geneCount; /* derived name */

static int geneReleasing; /* derived name */

static inline void effect_end_func(int id);
static inline void gene_eff_end_func(int id);

void bossCtrlBeforeFunc(GObj *self)
{
    int buf[53];
    float pos[4];
    GObjMailQueue *q;
    GObjMailEntry *e;
    CapsuleRec *base;
    int idx;
    CapsuleRec *e2;
    int i;
    unsigned int j;
    int cnt;
    int r;

    q = (GObjMailQueue *)&self->mailBox;
    base = GOBJ_SUB(self)->work;
    for (i = 0; i < q->num; i++) {
        e = &q->e[i];
        if (e->mail == 18) {
            if (e->data != 0) {
                cnt = 0;
                for (j = 0; j < 53; j++) {
                    if (base[j].state == 0) {
                        buf[cnt++] = j;
                    }
                }
                if (cnt > 0) {
                    idx = buf[(int)(random_unit() * cnt)];
                    e2 = &base[idx];
                    GetRootPosition(pos, e->data);
                    r = GatherEffect_Set(12, pos, IdentityQuaternion, e2->pos, 1.0f,
                                         effect_end_func);
                    if (r >= 0) {
                        GetParticleEffectData(r)->user.capsule = idx;
                        e2->state = 1;
                    }
                }
            }
        }
    }
    q->num = 0;
}

/* this file's own gene_enemy; queen.c defines a global of the same name */
static void gene_enemy(volatile int gobj)
{
    CapsuleRec *base = GOBJ_SUB(gobj)->work;
    int no = geneCount;
    volatile int *flag = &geneDone[geneCount++];
    CapsuleRec *buf[53];
    GObj *o;
    void *c;
    CapsuleRec *p;
    int i;
    unsigned int j;
    int total;
    int alive;
    int num;

    _ACTWait(1);

    i = 0;
    for (o = isysGObjSearchFromObjKindID_begin(33); o != 0;
         o = isysGObjSearchFromObjKindID_next(o), i++) {
        if (i == no) {
            break;
        }
    }

    for (;; _ACTWait(1)) {
        total = 0;
        alive = 0;
        c = isysGObjSearchFromObjKindID_begin(4);
        while (c != 0) {
            total++;
            if (isEnemyHyde(c) == 0) {
                alive++;
            }
            c = isysGObjSearchFromObjKindID_next(c);
        }
        if ((debug_font_flag & 1) != 0) {
            debug_Printf(10, 90, 0xFFFFFFFF, "enemy %d/%d\n", alive, total);
        }
        num = 0;
        for (j = 0; j < 53; j++) {
            p = &base[j];
            if (p->state <= 0) {
                buf[num++] = p;
            }
        }
        if (alive + geneReleasing < total && num > 0 && o != 0) {
            float pp[4];
            float pos[4];
            float dir[4];
            float m[4][4];
            CapsuleRec *sel;
            float best;
            float d;
            unsigned int cell;
            unsigned int k;
            short ang;
            int r;

            GetRootPosition(pp, boyGObj);
            cell = 0;
            best = 3.40282347e+38f /* FLT_MAX */;
            for (k = 0; k < 30; k++) {
                if (geneCell[k].busy == 0) {
                    d = _GetLength(pp, geneCell[k].pos);
                    if (d < best) {
                        best = d;
                        cell = k;
                    }
                }
            }
            while (geneCell[cell].busy != 0) {
                cell = (cell + 1) % 30;
            }
            geneReleasing++;
            geneCell[cell].busy = 1;
            sceVu0CopyVector(pos, geneCell[cell].pos);
            ang = (short)(degrees_to_radians(random_unit() * 360.0f) * 10430.378f);
            pos[0] += GetTableSin(ang) * 100.0f;
            pos[2] += GetTableCos(ang) * 100.0f;

            sel = buf[(int)(random_unit() * num)];
            *flag = 0;
            r = GatherEffect_Set(12, sel->pos, sel->quat, pos, 1.0f, gene_eff_end_func);
            if (r >= 0) {
                GetParticleEffectData(r)->user.done = flag;
                SetParticleEffectClipEnableFlag(r, 0);
                while (*flag == 0) {
                    _ACTWait(1);
                }
            }
            SetRootPosition(o, pos);
            GetRootPosition(pp, boyGObj);
            sceVu0SubVector(dir, pp, pos);
            sceVu0Normalize(dir, dir);
            sceVu0UnitMatrix(m);
            m[1][0] = 0.0f;
            m[1][1] = 1.0f;
            m[1][2] = 0.0f;
            m[1][3] = 0.0f;
            sceVu0CopyVector(m[2], dir);
            sceVu0OuterProduct(m[0], m[1], m[2]);
            {
                float q[4];
                ico_m33_to_quat(q, m);
                SetRootQuaternion(o, q);
            }
            Generator_Call(o);
            while (GeneratorWorkEnd(o) == 0) {
                _ACTWait(1);
            }
            geneCell[cell].busy = 0;
            geneReleasing--;
            _ACTWait(((60 - systemStatus[0] * 10) / systemStatus[1]) * 8);
            /* send the enemy off-world */
            pos[2] = pos[1] = pos[0] = 4294967296.0f;
            pos[3] = 0.0f;
            SetRootPosition(o, pos);
        }
    }
}

void BossCtrlGeo(void *self)
{
    CapsuleRec *base = GOBJ_SUB(self)->work;
    CapsuleRec *e;
    GObj *o;
    unsigned int k;
    int n;

    for (o = isysGObjSearchFromObjKindID_begin(4); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (isEnemyHyde(o) == 0) {
            _ACTSetEnemyDisappearSpeed(o, 4.0f);
            /* the motion is read off the controller, not the enemy */
            switch (GOBJ_SUB(self)->ctrl.motion) {
            case 894:
                SetMotionPlaySpeedRatio(o, 4.0f);
                break;
            case 982:
                SetMotionPlaySpeedRatio(o, 6.0f);
                break;
            case 983:
                SetMotionPlaySpeedRatio(o, 8.0f);
                break;
            case 984:
                SetMotionPlaySpeedRatio(o, 10.0f);
                break;
            }
        }
    }

    n = 0;
    for (k = 0; k < 53; k++) {
        e = &base[k];
        if (e->state >= 2) {
            if (stage_DispBgAnimation(&e->bga) != 0) {
                stage_SetLoopFlag(440, 1);
                pbga_start(&e->bga, 440);
                _CopyVector(e->bga->pos, e->pos);
                CopyQuaternion(e->bga->rot, e->quat);
            }
        }
        if (e->state != 0) {
            n++;
        }
    }
    if ((debug_font_flag & 1) != 0) {
        debug_Printf(10, 60, 0xFFFFFFFF, "capsule %d/%d", n, 53);
    }
}

INCLUDE_ASM(actBossCtrlStart);

int InitBossCtrlGeo(void *gobj)
{
    CapsuleRec *base;
    unsigned int k;

    base = iosMallocDebug(ios_partition_sugipon, sizeof(CapsuleRec) * 53, __FILE__, 332);
    memset(base, 0, sizeof(CapsuleRec) * 53);
    actInitialize(gobj);
    actInitialize_ext_charcter(gobj);
    debug_StdPrintfDummy("N_CAPSULE %d\n", 53);
    for (k = 0; k < 53; k++) {
        sceVu0CopyVector(base[k].pos, (float *)capsulePlace[k].pos);
        ico_m33_to_quat(base[k].quat, (void *)capsulePlace[k].rot);
    }
    return (int)base;
}

int InqCapsuleGhostBossEnd(void)
{
    unsigned int cnt = 0;
    GObj *o = isysGObjSearchFromObjKindID_begin(62);

    if (o != 0) {
        CapsuleRec *base = GOBJ_SUB(o)->work;
        unsigned int i = 0;
        do {
            if (base[i].state >= 2) {
                cnt++;
            }
            i++;
        } while (i < 53);
    }
    return cnt >= 53;
}

void BossCtrlDL(void) {}

static inline void effect_end_func(int id)
{
    GObj *o = isysGObjSearchFromObjKindID_begin(62);

    if (o != 0) {
        CapsuleRec *base = GOBJ_SUB(o)->work;
        CapsuleRec *e = &base[GetParticleEffectData(id)->user.capsule];

        pbga_start(&e->bga, 439);
        _CopyVector(e->bga->pos, e->pos);
        CopyQuaternion(e->bga->rot, e->quat);
        e->state = 2;
    }
}

static inline void gene_eff_end_func(int id)
{
    *GetParticleEffectData(id)->user.done = 1;
}
