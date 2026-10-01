#include "memory.h"
#include "clothAnimation.h"
#include "ios.h"

/* the twenty anchor records of the test cloth, then the InitClothes config
   array, a list of 0x1C-byte records ended by one whose first field is -1 */
typedef struct ClothTestAnchor { /* field names derived */
    int parent;                  /* 0x00 */
    float len;                   /* 0x04 */
    char pad08[8];
    float pos[4];  /* 0x10 */
    float vel[4];  /* 0x20 */
} ClothTestAnchor; /* derived name */

typedef struct ClothCfg { /* field names derived */
    int num;              /* 0x00  rows, and -1 ends the array */
    float segLength;      /* 0x04  the spacing between rows */
    int div;              /* 0x08  columns */
    int wrap;             /* 0x0C  nonzero when the last column joins the first */
    void *anchors;        /* 0x10 */
    void *tex;            /* 0x14  null means the untextured mesh */
    float weight;         /* 0x18  the fall added to each point a step */
} ClothCfg;               /* derived name */

static ClothTestAnchor clothTestAnchors[20] = {
    {-1, 15.0f, {0}, {0.0f, 0.0f, 15.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-10.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-20.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-30.0f, 0.0f, 13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-40.0f, 0.0f, 10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-40.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-40.0f, 0.0f, -10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-30.0f, 0.0f, -13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-20.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {-10.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {0.0f, 0.0f, -15.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {10.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {20.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {30.0f, 0.0f, -13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {40.0f, 0.0f, -10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {40.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {40.0f, 0.0f, 10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {30.0f, 0.0f, 13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {20.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, {0}, {10.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
}; /* derived name */

static ClothCfg clothTestCfg[2] = {{20, 20.0f, 15, 1, clothTestAnchors, 0, 3.0f},
                                   {-1}}; /* derived name */

int *InitClothTestGeo(void)
{
    int *p = iosMallocDebug(ios_partition_sugipon, 0x290, "src/clothTest.c", 65);
    *p = InitClothes((char *)clothTestCfg);
    return p;
}

void ClothTestGeo(void) {}

void ClothTestDL(void) {}
