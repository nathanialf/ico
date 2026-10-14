#include "flag.h"
#include "ios.h"
#include "attackCheckBoundary.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "Light.h"
#include "Matrix.h"
#include "Primitive.h"
#include "clothAnimation.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include <string.h>
#include "include_asm.h"

/* the corners (x, y) of each half of a fixed four-point flag, one row
   per id */
static float flag4PointFix[2][4][4] = {
    {{0.0f, 0.0f, 0.0f, 0.0f},
     {0.48f, 0.02f, 0.0f, 0.0f},
     {0.0f, 0.1f, 0.0f, 0.0f},
     {0.5f, 0.2f, 0.0f, 0.0f}},
    {{0.48f, 0.02f, 0.0f, 0.0f},
     {1.0f, 0.0f, 0.0f, 0.0f},
     {0.5f, 0.2f, 0.0f, 0.0f},
     {1.0f, 0.25f, 0.0f, 0.0f}},
}; /* derived name */

/* Set a four-point flag's mesh: each vertex is interpolated between the
   corners of the id's row of flag4PointFix, its height raised by k.
   SetFlag4PointFixID is the one caller, passing turns * 0.25f as k.
 */
static inline void setFlag4PointMesh(Mesh3D *mesh, ClothCfg *cl, float k, int id) /* derived name */
{
    float *tbl = flag4PointFix[id][0];
    Prim3DVec *v = mesh->st;
    int n = cl->num;
    int m = cl->div;
    int i;
    int j;
    float a;
    float b;
    float c;
    float d;

    for (i = 0; i < n; i++) {
        a = tbl[0] + (tbl[4] - tbl[0]) * i / (n - 1);
        b = tbl[8] + (tbl[12] - tbl[8]) * i / (n - 1);
        for (j = 0; j < m; j++) {
            c = tbl[1] + (tbl[9] - tbl[1]) * j / (m - 1) + k;
            d = tbl[5] + (tbl[13] - tbl[5]) * j / (m - 1) + k;
            v[i * m + j].y = c + (d - c) * i / (n - 1);
            v[i * m + j].x = a + (b - a) * j / (m - 1);
        }
    }
}

/* InitFlagGeo builds a cloth from the laid-out object's row of layoutClothDef
   (attackCheckBoundary.h): its corners, the cloth type in the low four bits,
   the rows and columns, the length shared out over the columns and the fall. */

/* the flag's cloth template, copied into every new config; InitFlagGeo
   passes __LINE__, so its lines below are kept out of clang-format */
static ClothCfg flagCfg = {8, 50.0f, 10, 0, 0, 0, 5.0f}; /* derived name */

/* clang-format off */
INCLUDE_ASM(InitFlagGeo);

/* clang-format on */

INCLUDE_ASM(FlagGeo);

INCLUDE_ASM(FlagDL);
