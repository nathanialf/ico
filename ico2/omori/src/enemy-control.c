#include "sugiCommon.h"
#include "enemy-control.h"

/* How many enemies asked to act this round, which one was picked, the round
   counter, and the ids that asked. */
static int enemyReqNum; /* derived name */

static int enemyPicked; /* derived name */

static int enemyRound; /* derived name */

static int enemyReqIds[100]; /* derived name */

inline int InitEnemyCtrlGeo(void)
{
    enemyReqNum = 0;
    enemyPicked = -1;
    enemyRound = 0;
    return 0;
}

void EnemyCtrlBeforeFunc(void)
{
    if (enemyReqNum > 0) {
        enemyPicked = enemyReqIds[(int)(random_unit() * 10.0f) % enemyReqNum];
    } else {
        enemyPicked = -1;
    }
    enemyRound++;
    enemyReqNum = 0;
}

inline int IsSelectID_EnemyCtrl(int a0)
{
    if (enemyPicked < 0)
        goto init;
    if (a0 != enemyPicked)
        goto append;
    return 1;
init:
    enemyPicked = a0;
    return 1;
append:
    enemyReqIds[enemyReqNum] = a0;
    enemyReqNum++;
    return 0;
}
