#include "common.h"
#include "memory.h"
#include "clothAnimation.h"

/* clothTest.o's whole .data run: the twenty anchor records of the test
   cloth, then the InitClothes config array, which is a list of 0x1C-byte
   records ended by one whose first field is -1. */
typedef struct ClothTestAnchor {
    int parent;   /* 0x00 */
    float len;    /* 0x04 */
    int f08;      /* 0x08 */
    int f0C;      /* 0x0C */
    float pos[4]; /* 0x10 */
    float vel[4]; /* 0x20 */
} ClothTestAnchor;

typedef struct ClothCfg {
    int num;       /* 0x00  rows, and -1 ends the array */
    float f04;     /* 0x04 */
    int div;       /* 0x08  columns */
    int f0C;       /* 0x0C */
    void *anchors; /* 0x10 */
    void *tex;     /* 0x14  null means the untextured mesh */
    float f18;     /* 0x18 */
} ClothCfg;

static ClothTestAnchor clothTestAnchors[20] = {
    {-1, 15.0f, 0, 0, {0.0f, 0.0f, 15.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-10.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-20.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-30.0f, 0.0f, 13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-40.0f, 0.0f, 10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-40.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-40.0f, 0.0f, -10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-30.0f, 0.0f, -13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-20.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {-10.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {0.0f, 0.0f, -15.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {10.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {20.0f, 0.0f, -14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {30.0f, 0.0f, -13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {40.0f, 0.0f, -10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {40.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {40.0f, 0.0f, 10.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {30.0f, 0.0f, 13.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {20.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {-1, 15.0f, 0, 0, {10.0f, 0.0f, 14.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
};

static ClothCfg clothTestCfg[2] = {{20, 20.0f, 15, 1, clothTestAnchors, 0, 3.0f}, {-1}};

extern int D_0063A438;

int *InitClothTestGeo(void)
{
    int *p = iosMallocDebug(D_0063A438, 0x290, "src/clothTest.c", 65);
    *p = InitClothes((char *)clothTestCfg);
    return p;
}

void ClothTestGeo(void) {}

void ClothTestDL(void) {}
