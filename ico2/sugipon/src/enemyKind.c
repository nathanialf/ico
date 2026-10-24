/*
 * ico2/sugipon/src/enemyKind.c
 *
 * The enemy kind table, the archive's code-less member enemy-def: by kind
 * the model and the particle object it is drawn with, its life, the scale its
 * model is drawn at, and the attribute
 * bits.  enemy.c reads it.  The file name is derived: MAIN.MAP links the
 * member as ico2000.a(enemy-def.o) and names its one symbol enemyKind.
 */

#include "enemy.h"

const EnemyDef enemyKind[] = {
    {12, -1, 200.0f, 1.0f, 0, 3}, {13, -1, 200.0f, 1.0f, 0, 3}, {14, -1, 200.0f, 1.0f, 0, 3},
    {15, -1, 200.0f, 1.0f, 0, 3}, {16, -1, 200.0f, 1.0f, 0, 3}, {17, -1, 200.0f, 1.0f, 1, 3},
    {18, -1, 200.0f, 1.0f, 1, 3}, {19, -1, 200.0f, 1.0f, 1, 3}, {20, -1, 200.0f, 1.0f, 1, 3},
    {21, -1, 200.0f, 1.0f, 1, 3}, {22, -1, 200.0f, 1.0f, 2, 3}, {23, -1, 200.0f, 1.0f, 2, 3},
    {24, -1, 200.0f, 1.0f, 2, 3}, {25, -1, 200.0f, 1.0f, 2, 3}, {1425, 0, 100.0f, 1.0f, 0, 0},
    {28, 0, 100.0f, 4.0f, 0, 3},  {11, -1, 100.0f, 1.0f, 0, 1}, {1425, 0, 100.0f, 4.0f, 0, 3},
};
