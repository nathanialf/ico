#include "common.h"
#include "typedef.h"
#include "queen.h"
#include "debug.h"
#include "memory.h"
#include "pad.h"
#include "gobj.h"
#include "obj_manager.h"
#include "act.h"
#include "enemy_act.h"
#include "queen_barrier_disp.h"
#include "attackhit.h"
#include "generator.h"
#include "script.h"
#include "StageAnimation.h"
#include "actressLight.h"
#include "clothAnimation.h"
#include "darkVolume.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "particleEffect.h"
#include "quaternion.h"
#include <libvu0.h>
#include <math.h>
#include "weapon.h"
#include "motionOrientManager.h"
#include "DisplayP2O.h"

typedef struct {
    float v[4];
} LVec;

typedef struct {
    QVec x;
    QVec y;
    QVec z;
    QVec w;
} QMat33;

typedef struct {
    QVec x;
    QVec y;
    QVec z;
} QMat3;

typedef struct QueenMailEntry {
    /* 0x0 */ unsigned int mail;
    /* 0x4 */ void *data;
} QueenMailEntry;

typedef struct QueenMailQueue {
    /* 0x00 */ int unk0;
    /* 0x04 */ int num;
    /* 0x08 */ QueenMailEntry e[1];
} QueenMailQueue;

extern int D_0063A438;
extern int stage_no;
extern int D_0063B13C;

/* .bss, owned by queen.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the queen's four ball-ring animations. */
static int queenBga[4];

/* The texture both of the queen's cloth meshes are drawn with.  Named, not a
   literal at the two use sites, because queen.o's plain .rodata input is the
   (0, 1, 0, 1) template at the end of the run and one input cannot hold both
   ends of it. */
static const char queenClothTexture[] = "queen_effect2";

/* The queen's two generated cloth meshes, in the order InitQueenGeo hands them
   to InitCloth4D: the cape, which hangs from queenClothHang, and the second
   cloth, which hangs from nothing.  MAIN.MAP names no symbol in queen.o's
   .data, so these names are ours.  The floats are the generator's own
   three-decimal output, read back from the ROM. */

static Cloth4DCol queenClothMeshCols[15];

static Cloth4DCfg queenClothMesh = {
    15, 11, 1, 0, 0x0, 0x0, 0x0, 0x80, queenClothTexture, queenClothMeshCols, 17.058f, 0,
};

static float queenClothMeshUv[15][11][2] = {
    {{0.839f, 0.127f},
     {0.871f, 0.207f},
     {0.904f, 0.286f},
     {0.937f, 0.366f},
     {0.97f, 0.445f},
     {1.003f, 0.525f},
     {1.035f, 0.605f},
     {1.068f, 0.684f},
     {1.101f, 0.764f},
     {1.134f, 0.844f},
     {1.166f, 0.923f}},
    {{0.624f, 0.114f},
     {0.644f, 0.193f},
     {0.663f, 0.272f},
     {0.683f, 0.351f},
     {0.702f, 0.43f},
     {0.722f, 0.509f},
     {0.741f, 0.588f},
     {0.761f, 0.668f},
     {0.78f, 0.747f},
     {0.8f, 0.826f},
     {0.819f, 0.905f}},
    {{0.973f, 0.094f},
     {0.917f, 0.174f},
     {0.86f, 0.254f},
     {0.804f, 0.334f},
     {0.748f, 0.414f},
     {0.691f, 0.493f},
     {0.635f, 0.573f},
     {0.579f, 0.653f},
     {0.523f, 0.733f},
     {0.466f, 0.813f},
     {0.41f, 0.893f}},
    {{0.771f, 0.078f},
     {0.782f, 0.158f},
     {0.794f, 0.238f},
     {0.805f, 0.318f},
     {0.817f, 0.398f},
     {0.828f, 0.477f},
     {0.84f, 0.557f},
     {0.851f, 0.637f},
     {0.863f, 0.717f},
     {0.874f, 0.797f},
     {0.886f, 0.877f}},
    {{0.499f, 0.071f},
     {0.509f, 0.151f},
     {0.519f, 0.231f},
     {0.53f, 0.311f},
     {0.54f, 0.391f},
     {0.55f, 0.472f},
     {0.561f, 0.552f},
     {0.571f, 0.632f},
     {0.581f, 0.712f},
     {0.591f, 0.792f},
     {0.602f, 0.872f}},
    {{0.37f, 0.113f},
     {0.368f, 0.19f},
     {0.367f, 0.266f},
     {0.366f, 0.343f},
     {0.364f, 0.419f},
     {0.363f, 0.495f},
     {0.361f, 0.572f},
     {0.36f, 0.648f},
     {0.359f, 0.725f},
     {0.357f, 0.801f},
     {0.356f, 0.878f}},
    {{0.497f, 0.114f},
     {0.508f, 0.191f},
     {0.518f, 0.267f},
     {0.529f, 0.343f},
     {0.539f, 0.419f},
     {0.55f, 0.496f},
     {0.56f, 0.572f},
     {0.571f, 0.648f},
     {0.581f, 0.724f},
     {0.592f, 0.801f},
     {0.602f, 0.877f}},
    {{0.023f, 0.09f},
     {0.035f, 0.176f},
     {0.046f, 0.263f},
     {0.058f, 0.35f},
     {0.069f, 0.437f},
     {0.081f, 0.523f},
     {0.092f, 0.61f},
     {0.104f, 0.697f},
     {0.116f, 0.784f},
     {0.127f, 0.87f},
     {0.139f, 0.957f}},
    {{0.206f, 0.074f},
     {0.217f, 0.145f},
     {0.227f, 0.216f},
     {0.238f, 0.287f},
     {0.248f, 0.358f},
     {0.259f, 0.429f},
     {0.269f, 0.5f},
     {0.28f, 0.571f},
     {0.29f, 0.642f},
     {0.301f, 0.714f},
     {0.311f, 0.785f}},
    {{0.964f, 0.121f},
     {0.871f, 0.198f},
     {0.778f, 0.275f},
     {0.685f, 0.352f},
     {0.592f, 0.429f},
     {0.5f, 0.506f},
     {0.407f, 0.583f},
     {0.314f, 0.66f},
     {0.221f, 0.737f},
     {0.128f, 0.814f},
     {0.035f, 0.891f}},
    {{0.03f, 0.116f},
     {-0.016f, 0.19f},
     {-0.062f, 0.264f},
     {-0.109f, 0.338f},
     {-0.155f, 0.411f},
     {-0.201f, 0.485f},
     {-0.247f, 0.559f},
     {-0.293f, 0.633f},
     {-0.339f, 0.706f},
     {-0.385f, 0.78f},
     {-0.431f, 0.854f}},
    {{0.154f, 0.123f},
     {0.201f, 0.202f},
     {0.247f, 0.281f},
     {0.293f, 0.36f},
     {0.339f, 0.439f},
     {0.385f, 0.518f},
     {0.431f, 0.597f},
     {0.477f, 0.676f},
     {0.523f, 0.754f},
     {0.569f, 0.833f},
     {0.615f, 0.912f}},
    {{0.261f, 0.113f},
     {0.249f, 0.189f},
     {0.236f, 0.265f},
     {0.224f, 0.341f},
     {0.211f, 0.418f},
     {0.199f, 0.494f},
     {0.186f, 0.57f},
     {0.174f, 0.646f},
     {0.161f, 0.723f},
     {0.149f, 0.799f},
     {0.136f, 0.875f}},
    {{0.733f, 0.115f},
     {0.758f, 0.195f},
     {0.782f, 0.276f},
     {0.807f, 0.356f},
     {0.832f, 0.436f},
     {0.857f, 0.516f},
     {0.882f, 0.597f},
     {0.907f, 0.677f},
     {0.931f, 0.757f},
     {0.956f, 0.838f},
     {0.981f, 0.918f}},
    {{0.624f, 0.114f},
     {0.644f, 0.193f},
     {0.663f, 0.272f},
     {0.683f, 0.351f},
     {0.702f, 0.43f},
     {0.722f, 0.509f},
     {0.741f, 0.588f},
     {0.761f, 0.668f},
     {0.78f, 0.747f},
     {0.8f, 0.826f},
     {0.819f, 0.905f}},
};

static Cloth4DCol queenClothMeshCols[15] = {
    {11.74f,
     {0},
     {-6.96f, 84.761f, 3.983f, 1.0f},
     {-0.163f, 0.376f, 0.912f, 0.0f},
     40,
     0.1f,
     45,
     0.9f,
     queenClothMeshUv[1],
     {0},
     {-2.007f, -10.392f, 5.08f, 0.0f}},
    {11.883f,
     {0},
     {-12.811f, 84.763f, 2.835f, 1.0f},
     {-0.41f, 0.429f, 0.805f, 0.0f},
     40,
     0.1f,
     45,
     0.9f,
     queenClothMeshUv[13],
     {0},
     {-3.776f, -10.393f, 4.352f, 0.0f}},
    {11.889f,
     {0},
     {-17.743f, 83.39f, -0.429f, 1.0f},
     {-0.788f, 0.473f, 0.395f, 0.0f},
     40,
     0.1f,
     45,
     0.9f,
     queenClothMeshUv[0],
     {0},
     {-5.722f, -10.257f, 1.841f, 0.0f}},
    {12.951f,
     {0},
     {-17.716f, 84.158f, -11.773f, 1.0f},
     {-0.87f, 0.489f, -0.068f, 0.0f},
     40,
     0.5f,
     45,
     0.5f,
     queenClothMeshUv[9],
     {0},
     {-5.83f, -10.332f, -5.194f, 0.0f}},
    {14.351f,
     {0},
     {-13.033f, 87.372f, -18.54f, 1.0f},
     {-0.602f, 0.66f, -0.449f, 0.0f},
     40,
     0.7f,
     45,
     0.3f,
     queenClothMeshUv[2],
     {0},
     {-4.245f, -10.646f, -8.637f, 0.0f}},
    {15.248f,
     {0},
     {-6.168f, 89.387f, -21.167f, 1.0f},
     {-0.367f, 0.7f, -0.612f, 0.0f},
     40,
     1.0f,
     -1,
     0.0f,
     queenClothMeshUv[3],
     {0},
     {-1.94f, -10.842f, -10.545f, 0.0f}},
    {15.087f,
     {0},
     {0.0f, 89.912f, -21.419f, 1.0f},
     {0.0f, 0.696f, -0.718f, 0.0f},
     40,
     1.0f,
     -1,
     0.0f,
     queenClothMeshUv[4],
     {0},
     {0.0f, -10.894f, -10.437f, 0.0f}},
    {15.248f,
     {0},
     {6.168f, 89.387f, -21.167f, 1.0f},
     {0.367f, 0.7f, -0.612f, 0.0f},
     40,
     1.0f,
     -1,
     0.0f,
     queenClothMeshUv[8],
     {0},
     {1.94f, -10.842f, -10.545f, 0.0f}},
    {14.351f,
     {0},
     {13.033f, 87.372f, -18.54f, 1.0f},
     {0.602f, 0.66f, -0.449f, 0.0f},
     40,
     0.7f,
     41,
     0.3f,
     queenClothMeshUv[7],
     {0},
     {4.245f, -10.646f, -8.637f, 0.0f}},
    {12.951f,
     {0},
     {17.716f, 84.158f, -11.773f, 1.0f},
     {0.87f, 0.489f, -0.068f, 0.0f},
     40,
     0.5f,
     41,
     0.5f,
     queenClothMeshUv[10],
     {0},
     {5.83f, -10.332f, -5.194f, 0.0f}},
    {11.889f,
     {0},
     {17.743f, 83.39f, -0.429f, 1.0f},
     {0.788f, 0.473f, 0.395f, 0.0f},
     40,
     0.1f,
     41,
     0.9f,
     queenClothMeshUv[11],
     {0},
     {5.722f, -10.257f, 1.841f, 0.0f}},
    {11.883f,
     {0},
     {12.811f, 84.763f, 2.835f, 1.0f},
     {0.41f, 0.429f, 0.805f, 0.0f},
     40,
     0.1f,
     41,
     0.9f,
     queenClothMeshUv[12],
     {0},
     {3.776f, -10.393f, 4.352f, 0.0f}},
    {11.74f,
     {0},
     {6.96f, 84.761f, 3.983f, 1.0f},
     {0.163f, 0.376f, 0.912f, 0.0f},
     40,
     0.1f,
     41,
     0.9f,
     queenClothMeshUv[5],
     {0},
     {2.007f, -10.392f, 5.08f, 0.0f}},
    {11.422f,
     {0},
     {0.0f, 84.683f, 4.502f, 1.0f},
     {-0.0f, 0.364f, 0.931f, 0.0f},
     40,
     1.0f,
     -1,
     0.0f,
     queenClothMeshUv[6],
     {0},
     {-0.0f, -10.384f, 4.758f, 0.0f}},
    {11.74f,
     {0},
     {-6.96f, 84.761f, 3.983f, 1.0f},
     {-0.163f, 0.376f, 0.912f, 0.0f},
     40,
     0.1f,
     45,
     0.9f,
     queenClothMeshUv[14],
     {0},
     {-2.007f, -10.392f, 5.08f, 0.0f}},
};

static Cloth4DCol queenClothMesh2Cols[13];

static Cloth4DCfg queenClothMesh2 = {
    13, 16, 0, 0, 0x0, 0x0, 0x0, 0x80, queenClothTexture, queenClothMesh2Cols, 34.852f, 0,
};

static float queenClothMesh2Uv[13][16][2] = {
    {{0.402f, 0.275f},
     {0.393f, 0.323f},
     {0.384f, 0.371f},
     {0.374f, 0.418f},
     {0.365f, 0.466f},
     {0.355f, 0.514f},
     {0.346f, 0.561f},
     {0.337f, 0.609f},
     {0.327f, 0.657f},
     {0.318f, 0.704f},
     {0.309f, 0.752f},
     {0.299f, 0.8f},
     {0.29f, 0.847f},
     {0.28f, 0.895f},
     {0.271f, 0.943f},
     {0.262f, 0.99f}},
    {{0.966f, 0.277f},
     {0.968f, 0.323f},
     {0.969f, 0.37f},
     {0.97f, 0.416f},
     {0.972f, 0.463f},
     {0.973f, 0.509f},
     {0.974f, 0.556f},
     {0.975f, 0.602f},
     {0.977f, 0.649f},
     {0.978f, 0.695f},
     {0.979f, 0.742f},
     {0.98f, 0.788f},
     {0.982f, 0.835f},
     {0.983f, 0.881f},
     {0.984f, 0.927f},
     {0.986f, 0.974f}},
    {{0.016f, 0.203f},
     {0.027f, 0.254f},
     {0.038f, 0.306f},
     {0.049f, 0.357f},
     {0.06f, 0.409f},
     {0.071f, 0.46f},
     {0.082f, 0.511f},
     {0.093f, 0.563f},
     {0.104f, 0.614f},
     {0.115f, 0.665f},
     {0.126f, 0.717f},
     {0.137f, 0.768f},
     {0.148f, 0.819f},
     {0.159f, 0.871f},
     {0.17f, 0.922f},
     {0.181f, 0.973f}},
    {{0.637f, 0.324f},
     {0.633f, 0.369f},
     {0.628f, 0.413f},
     {0.624f, 0.458f},
     {0.62f, 0.502f},
     {0.616f, 0.547f},
     {0.612f, 0.591f},
     {0.608f, 0.636f},
     {0.603f, 0.68f},
     {0.599f, 0.725f},
     {0.595f, 0.77f},
     {0.591f, 0.814f},
     {0.587f, 0.859f},
     {0.583f, 0.903f},
     {0.578f, 0.948f},
     {0.574f, 0.992f}},
    {{0.334f, 0.239f},
     {0.327f, 0.289f},
     {0.32f, 0.338f},
     {0.314f, 0.388f},
     {0.307f, 0.438f},
     {0.3f, 0.488f},
     {0.293f, 0.537f},
     {0.287f, 0.587f},
     {0.28f, 0.637f},
     {0.273f, 0.687f},
     {0.266f, 0.736f},
     {0.26f, 0.786f},
     {0.253f, 0.836f},
     {0.246f, 0.886f},
     {0.239f, 0.935f},
     {0.233f, 0.985f}},
    {{0.525f, 0.238f},
     {0.52f, 0.287f},
     {0.515f, 0.335f},
     {0.509f, 0.383f},
     {0.504f, 0.432f},
     {0.499f, 0.48f},
     {0.493f, 0.528f},
     {0.488f, 0.576f},
     {0.483f, 0.625f},
     {0.477f, 0.673f},
     {0.472f, 0.721f},
     {0.467f, 0.77f},
     {0.461f, 0.818f},
     {0.456f, 0.866f},
     {0.451f, 0.915f},
     {0.445f, 0.963f}},
    {{0.68f, 0.27f},
     {0.68f, 0.318f},
     {0.681f, 0.365f},
     {0.681f, 0.412f},
     {0.682f, 0.46f},
     {0.683f, 0.507f},
     {0.683f, 0.555f},
     {0.684f, 0.602f},
     {0.684f, 0.649f},
     {0.685f, 0.697f},
     {0.686f, 0.744f},
     {0.686f, 0.791f},
     {0.687f, 0.839f},
     {0.687f, 0.886f},
     {0.688f, 0.934f},
     {0.689f, 0.981f}},
    {{0.03f, 0.914f},
     {0.029f, 0.918f},
     {0.027f, 0.922f},
     {0.025f, 0.926f},
     {0.024f, 0.93f},
     {0.022f, 0.934f},
     {0.02f, 0.938f},
     {0.019f, 0.942f},
     {0.017f, 0.946f},
     {0.015f, 0.95f},
     {0.014f, 0.954f},
     {0.012f, 0.958f},
     {0.01f, 0.962f},
     {0.009f, 0.966f},
     {0.007f, 0.97f},
     {0.005f, 0.974f}},
    {{0.076f, 0.251f},
     {0.072f, 0.3f},
     {0.069f, 0.349f},
     {0.065f, 0.398f},
     {0.062f, 0.446f},
     {0.058f, 0.495f},
     {0.055f, 0.544f},
     {0.051f, 0.593f},
     {0.048f, 0.641f},
     {0.044f, 0.69f},
     {0.041f, 0.739f},
     {0.037f, 0.788f},
     {0.034f, 0.836f},
     {0.03f, 0.885f},
     {0.027f, 0.934f},
     {0.023f, 0.982f}},
    {{0.838f, 0.275f},
     {0.836f, 0.322f},
     {0.834f, 0.369f},
     {0.832f, 0.416f},
     {0.83f, 0.462f},
     {0.828f, 0.509f},
     {0.826f, 0.556f},
     {0.825f, 0.603f},
     {0.823f, 0.65f},
     {0.821f, 0.697f},
     {0.819f, 0.744f},
     {0.817f, 0.791f},
     {0.815f, 0.838f},
     {0.813f, 0.885f},
     {0.812f, 0.932f},
     {0.81f, 0.979f}},
    {{0.356f, 0.194f},
     {0.36f, 0.245f},
     {0.365f, 0.297f},
     {0.369f, 0.348f},
     {0.373f, 0.4f},
     {0.378f, 0.451f},
     {0.382f, 0.503f},
     {0.386f, 0.554f},
     {0.391f, 0.606f},
     {0.395f, 0.657f},
     {0.399f, 0.709f},
     {0.404f, 0.76f},
     {0.408f, 0.812f},
     {0.412f, 0.863f},
     {0.417f, 0.915f},
     {0.421f, 0.966f}},
    {{0.53f, 0.219f},
     {0.531f, 0.269f},
     {0.533f, 0.32f},
     {0.535f, 0.37f},
     {0.537f, 0.421f},
     {0.538f, 0.471f},
     {0.54f, 0.522f},
     {0.542f, 0.572f},
     {0.544f, 0.623f},
     {0.545f, 0.673f},
     {0.547f, 0.724f},
     {0.549f, 0.774f},
     {0.551f, 0.825f},
     {0.552f, 0.876f},
     {0.554f, 0.926f},
     {0.556f, 0.977f}},
    {{0.008f, 0.863f},
     {0.011f, 0.871f},
     {0.014f, 0.878f},
     {0.016f, 0.886f},
     {0.019f, 0.893f},
     {0.022f, 0.901f},
     {0.025f, 0.909f},
     {0.028f, 0.916f},
     {0.031f, 0.924f},
     {0.034f, 0.931f},
     {0.036f, 0.939f},
     {0.039f, 0.946f},
     {0.042f, 0.954f},
     {0.045f, 0.961f},
     {0.048f, 0.969f},
     {0.051f, 0.977f}},
};

static Cloth4DCol queenClothMesh2Cols[13] = {
    {2.609f,
     {0},
     {-53.885f, 143.321f, -5.563f, 1.0f},
     {0.102f, 0.52f, 0.848f, 0.0f},
     20,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[7],
     {0},
     {-2.371f, 0.923f, -0.578f, 0.0f}},
    {6.062f,
     {0},
     {-46.821f, 144.768f, -7.302f, 1.0f},
     {0.128f, 0.58f, 0.805f, 0.0f},
     20,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[8],
     {0},
     {-4.979f, 1.591f, -3.07f, 0.0f}},
    {9.557f,
     {0},
     {-32.474f, 145.372f, -11.092f, 1.0f},
     {0.012f, 0.869f, 0.495f, 0.0f},
     19,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[4],
     {0},
     {-6.21f, 0.855f, -7.214f, 0.0f}},
    {12.18f,
     {0},
     {-28.467f, 145.58f, -15.865f, 1.0f},
     {0.179f, 0.94f, -0.291f, 0.0f},
     19,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[5],
     {0},
     {-6.111f, -2.391f, -10.261f, 0.0f}},
    {14.214f,
     {0},
     {-17.627f, 132.789f, -20.177f, 1.0f},
     {0.136f, 0.546f, -0.827f, 0.0f},
     18,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[0],
     {0},
     {-5.552f, -6.954f, -11.084f, 0.0f}},
    {15.347f,
     {0},
     {-8.462f, 129.807f, -22.04f, 1.0f},
     {-0.196f, 0.421f, -0.886f, 0.0f},
     18,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[3],
     {0},
     {-2.878f, -9.596f, -11.626f, 0.0f}},
    {16.54f,
     {0},
     {-0.001f, 128.527f, -23.174f, 1.0f},
     {0.0f, 0.277f, -0.961f, 0.0f},
     1,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[1],
     {0},
     {0.077f, -11.838f, -11.551f, 0.0f}},
    {15.333f,
     {0},
     {8.453f, 129.807f, -22.04f, 1.0f},
     {0.203f, 0.416f, -0.886f, 0.0f},
     2,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[9],
     {0},
     {2.802f, -9.596f, -11.626f, 0.0f}},
    {13.888f,
     {0},
     {17.616f, 132.787f, -20.177f, 1.0f},
     {-0.125f, 0.529f, -0.839f, 0.0f},
     2,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[6],
     {0},
     {4.362f, -6.904f, -11.233f, 0.0f}},
    {11.604f,
     {0},
     {28.706f, 145.453f, -16.137f, 1.0f},
     {-0.165f, 0.946f, -0.28f, 0.0f},
     3,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[11],
     {0},
     {4.904f, -2.383f, -10.243f, 0.0f}},
    {9.074f,
     {0},
     {32.632f, 145.253f, -11.155f, 1.0f},
     {-0.024f, 0.825f, 0.565f, 0.0f},
     3,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[10],
     {0},
     {5.466f, 0.866f, -7.191f, 0.0f}},
    {5.437f,
     {0},
     {46.704f, 144.817f, -8.304f, 1.0f},
     {-0.111f, 0.611f, 0.784f, 0.0f},
     4,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[2],
     {0},
     {4.207f, 1.588f, -3.056f, 0.0f}},
    {2.531f,
     {0},
     {53.846f, 143.068f, -6.081f, 1.0f},
     {-0.108f, 0.583f, 0.806f, 0.0f},
     4,
     1.0f,
     -1,
     0.0f,
     queenClothMesh2Uv[12],
     {0},
     {2.297f, 0.913f, -0.543f, 0.0f}},
};

/* the five points the queen's cape hangs from.  MAIN.MAP names no symbol in
   queen.o's .data, so this name is ours. */
static ClothHangCfg queenClothHang[6] = {
    {1, -5.0f, 45.0f, 10.0f, 49, {0}, 0.0f, 0.0f, {0}, 1.0f, 1.0f, {0}},
    {1, -5.0f, 60.0f, 10.0f, 50, {0}, 0.0f, 0.0f, {0}, 1.0f, 1.0f, {0}},
    {1, -5.0f, 45.0f, 10.0f, 45, {0}, 0.0f, 0.0f, {0}, 1.0f, 1.0f, {0}},
    {1, -5.0f, 60.0f, 10.0f, 46, {0}, 0.0f, 0.0f, {0}, 1.0f, 1.0f, {0}},
    {1, -20.0f, 45.0f, 10.0f, 44, {0}, 0.0f, 0.0f, {0}, 1.0f, 1.0f, {0}},
    {-1, 0.0f, 0.0f, 0.0f, 0, {0}, 0.0f, 0.0f, {0}, 0.0f, 0.0f, {0}},
};

/* the six places an enemy is dropped back into the last stage when it is
   called again; LW coordinates, converted by lw_pos_to_ico_pos at the site */
static float queenSpawnPos[6][4] = {
    {1200.0f, -1000.0f, 300.0f, 0.0f}, {1200.0f, -1000.0f, -100.0f, 0.0f},
    {1100.0f, -1000.0f, 100.0f, 0.0f}, {800.0f, -920.0f, 200.0f, 0.0f},
    {600.0f, -900.0f, -200.0f, 0.0f},  {400.0f, -900.0f, 100.0f, 0.0f},
};

extern int D_0028F4D4[];

/* .sbss, owned by queen.o (MAIN.MAP names no symbol in the run): the queen's own frame counter, the
   timestamp every wait in her state machine is measured against */
static int queenFrame;

extern char *D_00639EA4;
/* kept local: this TU's uses of ACTDispLwsBoyStonize_InQueenStage do not fit the prototype in boyact.h */
extern void ACTDispLwsBoyStonize_InQueenStage(char *g);
extern void *memset(void *p, int c, int n);

/* PAL listing rows 87-90: a static identity-3x3 helper, expanded into
 * QueenBarrierGeo (and QueenBallGeo). */
static inline void UnitMatrix33(QMat3 *m)
{
    m->x.f[0] = 1.0f;
    m->x.f[1] = 0.0f;
    m->x.f[2] = 0.0f;
    m->x.f[3] = 0.0f;
    m->y.f[0] = 0.0f;
    m->y.f[1] = 1.0f;
    m->y.f[2] = 0.0f;
    m->y.f[3] = 0.0f;
    m->z.f[0] = 0.0f;
    m->z.f[1] = 0.0f;
    m->z.f[2] = 1.0f;
    m->z.f[3] = 0.0f;
}

void scale_m34(LVec *a0, void *a1, float f)
{
    sceVu0CopyMatrix(a0, a1);
    sceVu0ScaleVector(a0, a0, f);
    sceVu0ScaleVector(a0 + 1, a0 + 1, f);
    return sceVu0ScaleVector(a0 + 2, a0 + 2, f);
}

/* census: static effect_end_func (ito/src/itou_boss.c holds the public symbol
   of the same name, so this copy stays file-static). */

static void effect_end_func(int no)
{
    char *g = isysGObjSearchFromObjKindID_begin(47);
    char *weapon = *(char **)(*(char **)(D_00639EA4 + 0x164) + 0x150);

    if (g != 0) {
        *(int *)(GOBJ_SUB(g)->f_830 + 4) += 1;
    }
    if (weapon != 0) {
        LightTorchOnOfWeapon(weapon);
    }
}

typedef struct {
    float f[8];
} QMotBlock;

/* queen.o's .rodata run, in the order the object emits it.  The ten rate
   tables come in two parallel sets of five, the first used when stage_no is
   0x25 (the queen's own stage, st25a) and the second everywhere else; each is
   indexed by the ball's phase counter at ballw+0x18, which runs 0 to 10. */
typedef struct QueenUVScroll {
    float v[6];
} QueenUVScroll;

static const float genWaitRateSt25[11] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                          1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

static const float ballWaitRateSt25[11] = {7.0f, 6.0f, 6.0f, 5.0f, 5.0f, 4.0f,
                                           4.0f, 4.0f, 4.0f, 4.0f, 4.0f};

static const float ballHoldRateSt25[11] = {5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f,
                                           5.0f, 5.0f, 5.0f, 5.0f, 5.0f};

static const float ballSpeedRateSt25[11] = {0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
                                            0.6f, 0.6f, 0.6f, 0.6f, 0.6f};

static const QueenUVScroll ballUVScrollSt25[11] = {
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
};

static const float genWaitRateDefault[11] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

static const float ballWaitRateDefault[11] = {3.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                              1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

static const float ballHoldRateDefault[11] = {4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f,
                                              4.0f, 4.0f, 4.0f, 4.0f, 4.0f};

static const float ballSpeedRateDefault[11] = {0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,
                                               0.6f, 0.6f, 0.6f, 0.6f, 0.6f};

static const QueenUVScroll ballUVScrollDefault[11] = {
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}}, {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
    {{0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f}},
};

static const char queenAttackedMsg[] = "queen attacked\n";

static const char enemyDeadMsg[] = "enemy dead %p\n";

/* kept local: this TU's uses of GatherEffect_Set do not fit the prototype in gather_effect.h */
extern int GatherEffect_Set(int no, void *a1, int a2, void *goal, void (*endFunc)(int),
                            float speed);

void queenBeforeFunc(char *g)
{
    QVec pos;
    QVec target;
    QueenMailQueue *q = (QueenMailQueue *)(g + 0x54);
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    Act *act = GOBJ_ACT(g);
    int i;

    for (i = 0; i < q->num; i++) {
        QueenMailEntry *e = &q->e[i];

        switch (e->mail) {
        case 0x2E:
            *(char *)w = 1;
            break;
        case 0x2F:
            *(char *)w = 0;
            break;
        case 0xD:
            if (scpGameStat_BoyWeaponkind() == 5) {
                char *o;

                debug_StdPrintfDummy(queenAttackedMsg);
                *(char *)(w + 2) = 1;
                o = isysGObjSearchFromObjKindID_begin(53);
                if (o != 0) {
                    *(char *)(*(char **)((char *)GOBJ_SUB(o) + 0x830) + 0x1A) = 1;
                }
            }
            break;
        case 0x12: {
            char *boy = *(char **)(*(char **)(D_00639EA4 + 0x164) + 0x150);

            debug_StdPrintfDummy(enemyDeadMsg, boy);
            if (e->data != 0 && boy != 0) {
                GetRootPosition(&pos, e->data);
                GetRootPosition(&target, boy);
                GatherEffect_Set(0xC, &pos, (int)IdentityQuaternion, &target, effect_end_func,
                                 2.5f);
            }
            break;
        }
        }
    }
    q->num = 0;
    *(QMotBlock *)((char *)act + 0x620) = *(QMotBlock *)((int)GOBJ_SUB(g) + 0x180);
}

/* PAL listing: queen.c lines 300-385 (the disc's objdump -dl line map). */
typedef struct QueenGenTable {
    /* 0x0 */ int n;
    /* 0x4 */ const int *list;
} QueenGenTable;

/* The layout ids gene_enemy picks a spawn point from, one list per stage set. */
static const int genEnemyLayoutSt25[6] = {2152, 2153, 2154, 2155, 2156, 2157};

static const int genEnemyLayoutDefault[6] = {3535, 3536, 3537, 3538, 3539, 3540};

static const QueenGenTable genEnemyTable[2] = {
    {6, genEnemyLayoutSt25},
    {6, genEnemyLayoutDefault},
};

static const char genEnemyStatFmt[] = "n_enemy_max:%d n_enemy:%d counter:%d";

extern int D_0028F4C0[];
extern float _GetRandom(void);
/* kept local: this TU's uses of lw_pos_to_ico_pos do not fit the prototype in itou_sub.h */
extern void lw_pos_to_ico_pos(float *dst, float *src);

void gene_enemy(volatile int g)
{
    union {
        float f[4];
        int i[4];
    } pos;

    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    const QueenGenTable *tbl;
    char *o;
    char *c;
    char *e;
    int num;
    int total;
    int alive;
    int timer;
    int wait;
    int k;
    char *obj;

    o = isysGObjSearchFromObjKindID_begin(54);
    num = (o != 0) ? *(int *)(*(char **)((char *)GOBJ_SUB(o) + 0x830) + 0x18) : 0;
    tbl = (stage_no == 0x25) ? &genEnemyTable[0] : &genEnemyTable[1];

    timer = 0;
    total = 0;
    for (c = isysGObjSearchFromObjKindID_begin(4); c != 0;
         c = isysGObjSearchFromObjKindID_next(c)) {
        total++;
    }
    _ACTWait(1);

    for (;;) {
        if ((*(int *)w & 0xFF0000FF) == 0 && *(signed char *)(w + 1) != 0) {
            alive = 0;
            e = isysGObjSearchFromObjKindID_begin(4);
            while (e != 0 && isEnemyHyde(e) == 0) {
                alive++;
                e = isysGObjSearchFromObjKindID_next(e);
            }
            if (D_0063B13C & 1) {
                debug_Printf(10, 90, -1, genEnemyStatFmt, total, alive, timer);
            }
            if (alive < total) {
                if (timer > ((stage_no == 0x25) ? genWaitRateSt25 : genWaitRateDefault)[num] *
                                ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1])) {
                    if (stage_no == 0x25) {
                        obj = (char *)isysGObjSearchFromObjLayoutID(
                            tbl->list[(int)(_GetRandom() * tbl->n)]);
                        if (obj != 0) {
                            lw_pos_to_ico_pos(pos.f, queenSpawnPos[(int)(_GetRandom() * 6.0f)]);
                            SetRootPosition(obj, pos.f);
                            wait = (int)(((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f);
                            for (k = 0; k <= wait; k++) {
                                _ACTWait(1);
                            }
                            Generator_Call(obj);
                            _ACTWait(1);
                            while (stage_CheckAnimationFinish(506) == 0) {
                                _ACTWait(1);
                            }
                            for (k = 0; k <= wait; k++) {
                                _ACTWait(1);
                            }
                            pos.f[0] = 4294967296.0f;
                            pos.f[1] = 4294967296.0f;
                            pos.f[2] = 4294967296.0f;
                            pos.i[3] = 0;
                            SetRootPosition(obj, pos.f);
                        }
                        timer = 0;
                    }
                }
            }
            timer++;
        }
        _ACTWait(1);
    }
}

/* r5 seed (478/478 insns, 7 diff sites / 20 non-reloc rows) at
 * scratchpad/seeds/subQueenBrainMain.r5.rc220_7sites.c (whole-TU snapshot) and
 * .r5.body.c (this block only).  Residual: one scheduling cluster, see LEDGER r5. */
/* kept local: the declaration in Texture.h changes this TU codegen */
extern void tex_SetUVScroll(void *p, int a1, float a2, float a3, float a4, float a5, float a6,
                            float a7);

/* The position the queen is dropped at outside her own stage. */
static const QVec queenStartPos __attribute__((aligned(16))) = {{0.0f, 800.0f, 0.0f, 1.0f}};

static const char queenDeadMsg[] = "queen dead\n";

static const char queenBallScrTexture[] = "queen_ball_scr";

extern char D_0063AC58[];

/* The queen's per-frame motion-status record, refreshed from the actor
 * extension at gobj->x15C every tick. */
/* One status slot: the motion-parameter words the actor extension keeps are
 * read as a float here and as an int elsewhere, so the record stores them in a
 * union (ROM re-loads gobj->x15C after every write to one, which only an
 * alias-set-0 union member does). */
typedef union QueenVal {
    int i;
    float f;
} QueenVal;

/* The look-at block the queen's motion system keeps in her actor parameter
 * area (gobj->x15C): a world-space target the head and body steer toward, and
 * the slot that enables it.  Like every other slot of that parameter block the
 * enable is a QueenVal (the block's words are written as int here and read as
 * float by the motion evaluator), and the target is a QVec. */
typedef struct QueenLookAt {
    /* 0x00 */ QueenVal on;
    /* 0x04 */ QueenVal pad[3];
    /* 0x10 */ QVec pos;
} QueenLookAt;

typedef struct QueenStatus {
    /* 0x00 */ int motion;
    /* 0x04 */ int prevMotion;
    /* 0x08 */ QueenVal ratio;
    /* 0x0C */ QueenVal prevRatio;
    /* 0x10 */ int step;
    /* 0x14 */ int prevStep;
    /* 0x18 */ int changed;
    /* 0x1C */ int active;
    /* 0x20 */ int count;
    /* 0x24 */ int unk24;
    /* 0x28 */ int unk28;
    /* 0x2C */ int unk2C;
} QueenStatus;

/* PAL listing rows 402-424. */
static inline void QueenStatusUpdate(char *g, QueenStatus *st)
{
    st->prevMotion = st->motion;
    st->prevRatio.f = st->ratio.f;
    st->prevStep = st->step;

    st->motion = GOBJ_SUB(g)->f_4A0;
    st->ratio.f = GOBJ_SUB(g)->f_4AC;
    st->step = *(int *)((int)GOBJ_SUB(g) + 0x4CC);
    st->changed = 0;
    if (st->motion != st->prevMotion) {
        st->count = 1;
        st->changed = 1;
    }
    if (st->motion == st->prevMotion) {
        if (st->prevStep != 0) {
            st->count++;
        }
    }
    st->active = (st->changed != 0 || st->step != 0) ? 1 : 0;
}

/* PAL listing rows 426-433. */
static inline void QueenStatusRestart(char *g, QueenStatus *st)
{
    QueenStatusUpdate(g, st);
    st->changed = 0;
    st->active = 1;
    st->count = 1;
}

/* INTERIM: the PAL listing shows QueenStartAttack (queen.c:164-169) expanded
 * inline here, but the tail of this TU still holds asm members, so the public
 * definition stays at its own ROM slot below and this stand-in serves the C
 * caller.  Fold the two together once the TU is fully C. */
static inline void QueenStartAttack_inl(int flag)
{
    char *g;

    g = isysGObjSearchFromObjKindID_begin(47);
    *(char *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 1) = flag;

    g = isysGObjSearchFromObjKindID_begin(54);
    while (g != 0) {
        *(char *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 0x12) = 1;
        g = isysGObjSearchFromObjKindID_next(g);
    }
}

/* The queen's brain thread.  `g` is volatile because this body is an actor
 * coroutine: _ACTWait() unwinds and resumes it, and the actor system can move
 * the GObj between resumes, so the thread's own copy in its frame is re-read at
 * every use rather than cached in a register (ROM reloads 0(sp) at every use).
 */
void subQueenBrainMain(volatile int g)
{
    QueenStatus st;
    QVec pos;
    QVec rootPos;
    QVec dir;
    LVec target;
    char *w;
    int motionOk;
    int first;
    int wait;
    char *ext;
    int startFrame;
    char *bar;
    char *ball;
    char *barw;
    char *ballw;
    char *qw;
    char *boy;
    QueenUVScroll *uv;

    ext = *(char **)(g + 0x164);
    w = *(char **)((char *)GOBJ_SUB(g) + 0x830);

    motionOk = 0;
    first = 1;
    startFrame = queenFrame;
    wait = 1000;

    _ACTWait(1);
    if (stage_no != 0x25) {
        pos = queenStartPos;
        SetDirectRootPosition(D_00639EA4, &pos);
        QueenStartAttack_inl(first);
    }
    QueenStatusRestart((char *)g, &st);

    for (;;) {
        bar = isysGObjSearchFromObjKindID_begin(53);
        ball = isysGObjSearchFromObjKindID_begin(54);
        QueenStatusUpdate((char *)g, &st);
        if (D_0063B13C & 1) {
            debug_Printf(10, 80, -1, D_0063AC58, InqQueenBarrierExist());
        }
        if ((*(int *)w & 0xFF0000FF) == 0 && *(signed char *)(w + 1) != 0 && bar != 0 &&
            ball != 0) {
            qw = *(char **)((char *)GOBJ_SUB(g) + 0x830);

            GetRootPosition(&rootPos, (char *)g);
            _GetMotionDirection(&dir, (char *)g);
            barw = *(char **)((char *)GOBJ_SUB(bar) + 0x830);
            ballw = *(char **)((char *)GOBJ_SUB(ball) + 0x830);

            if (*(signed char *)(qw + 2) != 0 && *(signed char *)(ballw + 0x12) == 0) {
                *(char *)(qw + 3) = 1;
                debug_StdPrintfDummy(queenDeadMsg);
            }

            if (*(signed char *)(ballw + 0x11) != 0) {
                if ((((QueenVal *)(ext + 0x130))->i =
                         SetMotionRequest((char *)g, 0x146, ext + 0x620)) != 0) {
                    *(char *)(ballw + 0x11) = 0;
                }
            }

            switch (GOBJ_SUB(g)->f_4A0) {
            case 0x430:
            case 0x435:
            case 0x436:
                GetRootPosition(&target, D_00639EA4);
                ((QueenLookAt *)((char *)GOBJ_SUB(g) + 0x380))->pos.f[0] = target.v[0];
                ((QueenLookAt *)((char *)GOBJ_SUB(g) + 0x380))->pos.f[1] = target.v[1];
                ((QueenLookAt *)((char *)GOBJ_SUB(g) + 0x380))->pos.f[2] = target.v[2];
                ((QueenLookAt *)((char *)GOBJ_SUB(g) + 0x380))->on.i = 1;
            }

            switch (GOBJ_SUB(g)->f_4A0) {
            case 0x431:
            case 0x432:
            case 0x433:
            case 0x434:
            default:
                ((QueenVal *)(ext + 0x130))->i = SetMotionRequest((char *)g, 1, ext + 0x620);
                break;

            case 0x430:
                motionOk = 1;
                if ((((QueenVal *)(ext + 0x130))->i =
                         SetMotionRequest((char *)g, 0x144, ext + 0x620)) != 0) {
                    if (first) {
                        startFrame = queenFrame;
                        wait = (int)(*((stage_no == 0x25)
                                           ? &ballWaitRateSt25[*(int *)(ballw + 0x18)]
                                           : &ballWaitRateDefault[*(int *)(ballw + 0x18)]) *
                                     ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                    }
                    first = 0;
                }
                break;

            case 0x435:
                if (*(signed char *)(barw + 0x10) == 0 && motionOk != 0 &&
                    queenFrame - startFrame >= wait) {
                    ((QueenVal *)(ext + 0x130))->i =
                        SetMotionRequest((char *)g, 0x145, ext + 0x620);
                }
                break;

            case 0x436:
                ((QueenVal *)(ext + 0x130))->i = SetMotionRequest((char *)g, 1, ext + 0x620);
                if (GOBJ_SUB(g)->f_4AC > 15.0f && *(signed char *)(barw + 0x10) == 0 &&
                    motionOk != 0) {
                    uv = (stage_no == 0x25) ? &ballUVScrollSt25[*(int *)(ballw + 0x18)]
                                            : &ballUVScrollDefault[*(int *)(ballw + 0x18)];

                    motionOk = 0;
                    sceVu0ScaleVectorXYZ(&target, &dir, 100.0f);
                    sceVu0AddVector(&target, &rootPos, &target);
                    SetDirectRootPosition(bar, &target);
                    *(char *)(barw + 0x10) = 1;
                    *(char *)(barw + 0x11) = 1;
                    *(int *)(barw + 0x14) = 0;
                    *(char *)(barw + 0x19) = 0;
                    startFrame = queenFrame;
                    wait =
                        (int)(*((stage_no == 0x25) ? &ballWaitRateSt25[*(int *)(ballw + 0x18)]
                                                   : &ballWaitRateDefault[*(int *)(ballw + 0x18)]) *
                              ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                    tex_SetUVScroll(queenBallScrTexture, 1, uv->v[0], uv->v[1], uv->v[2], uv->v[3],
                                    uv->v[4], uv->v[5]);
                }
                break;

            case 0x437:
                startFrame = queenFrame;
                wait = (int)(*((stage_no == 0x25) ? &ballHoldRateSt25[*(int *)(ballw + 0x18)]
                                                  : &ballHoldRateDefault[*(int *)(ballw + 0x18)]) *
                             ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                ((QueenVal *)(ext + 0x130))->i = SetMotionRequest((char *)g, 1, ext + 0x620);
                break;
            }
        }
        boy = *(char **)(*(char **)(D_00639EA4 + 0x164) + 0x150);
        if (boy != 0) {
            GetRootPosition(&target, boy);
            ParticleEffects_SetAllGoal(&target);
        }
        *(char *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 2) = 0;
        _ACTWait(1);
    }
}

extern char *D_00639EC0;
extern char *D_00639ED0;
/* kept local: this TU's uses of CorrectStickInfo do not fit the prototype in boyact.h */
extern int CorrectStickInfo(void *dir, void *stick);

/* census: static Debug_StickControl; ito/src/act_bird.c holds the public symbol
   of that name, so this copy is a file-static. */
/* The rest of queen.o's .rodata run: it follows subQueenBrainMain's switch
   table, which the compiler emits after that function's body. */
static const char queenFile[] = __FILE__;

static const char queenBarrierAttackedMsg[] = "queen barrier attacked\n";

/* The barrier's own spawn layout id, one per stage set.  The bound is left
   unspecified: under -G 8 a sized 4-byte const array is small enough for
   .sdata, and the ROM has both in .rodata. */
static const int barrierLayoutSt25[] = {2150};

static const int barrierLayoutDefault[] = {3527};

static const char damageFmt[] = "damage:%d";

static const char mailFmt[] = "mail %d\n";

static const char queenBallAttackedMsg[] = "queen ball attacked\n";

static void Debug_StickControl(char *self)
{
    QVec dir;
    Act *ext = GOBJ_ACT(self);

    if (self == D_00639EC0) {
        char *pad = (char *)ext + 0x2D8;
        char *stick = (char *)ext + 0x338;

        iosPadConnect(pad, 0, 0, (char *)ext + 0x1E8);
        iosPadRead(pad);
        iosPadGetStick(pad, stick, 0, 2, 2, 0);
        _GetMotionDirection(&dir, self);
        *(int *)((char *)ext + 0x340) = CorrectStickInfo(&dir, stick);
        if (*(float *)((char *)ext + 0x34C) > 0.001f) {
            ConvertStickToAbsCoord((char *)ext + 0x120, stick);
        }
    } else if (self == D_00639ED0) {
        iosPadConnect((char *)ext + 0x2D8, 0, 1, (char *)ext + 0x1E8);
    } else {
        iosPadConnect((char *)ext + 0x2D8, 0, 1, (char *)ext + 0x1E8);
    }
}

void *InitQueenGeo(char *g)
{
    Sub15C *ext = GOBJ_SUB(g);
    char *w;
    int i;

    w = (char *)iosMallocDebug(D_0063A438, 0x18, queenFile, 732);
    memset(w, 0, 0x18);
    for (i = 3; i >= 0; i--) {
        queenBga[i] = 0;
    }
    *(int *)(w + 0xC) = 1;
    *(int *)(w + 0x10) = InitCloth4D(g, &queenClothMesh, queenClothHang);
    *(int *)(w + 0x14) = InitCloth4D(g, &queenClothMesh2, 0);
    *(char **)((char *)ext + 0x830) = w;
    InitMotionOrient(g, 0x967, 0x975, 0xC, 0x18, 0x430);
    SetLodLevel(g, 2);
    actInitialize(g);
    actInitialize_ext_charcter(g);
    return w;
}

void QueenGeo(char *g)
{
    char *w;

    if (D_0028F4D4[0] == 0) {
        queenFrame++;
    }
    ExecMotionOrient(g);
    SetActressLight(g, 0x23, 0x2C, 0x1D8);
    w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    if (*(int *)(w + 0xC) != 0) {
        GetCloth4D(*(void **)(w + 0x10), 3.0f, 0.98f);
        GetCloth4D(*(void **)(w + 0x14), 5.0f, 0.9f);
    }
    CylinderCollision(g, 1, 100.0f, 100.0f, 0.001f);
}

void QueenDL(char *g)
{
    char *w;

    if (D_00639EA4 != 0) {
        ACTDispLwsBoyStonize_InQueenStage(D_00639EA4);
    }
    p2o_SetDefaultEnviroment();
    p2o_DispVU1(g);
    w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    if (*(int *)(w + 0xC) != 0) {
        DispCloth4D(*(void **)(w + 0x10), (char *)GOBJ_SUB(g)->p_874 + 0x40,
                    (char *)GOBJ_SUB(g)->p_874);
    }
    DispCloth4D(*(void **)(w + 0x14), (char *)GOBJ_SUB(g)->p_874 + 0x40,
                (char *)GOBJ_SUB(g)->p_874);
}

/* PAL listing rows 871-873 belong to a static angle-wrap helper. */
static inline float WrapRad(float a)
{
    a = fmodf(a, 6.2831854820251465f);
    if (a > 3.1415927410125732f) {
        a -= 6.2831854820251465f;
    } else if (a < -3.1415927410125732f) {
        a += 6.2831854820251465f;
    }
    return a;
}

void QueenBarrierGeo(char *g)
{
    QVec pos;
    QVec rootPos;
    QMat33 m1;
    QMat3 rot;
    QVec trans;
    QVec ofs;
    QVec axis;
    QMat33 m3;
    char *w;
    char *queen;
    char *qw;
    const int *tbl;
    unsigned int i;
    unsigned int found;
    unsigned int mine;

    memset(&pos, 0, sizeof(pos));
    pos.f[1] = 2000.0f;
    w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    queen = isysGObjSearchFromObjKindID_begin(47);
    qw = *(char **)((char *)GOBJ_SUB(queen) + 0x830);
    if (stage_no == 0x25) {
        tbl = barrierLayoutSt25;
    } else {
        tbl = barrierLayoutDefault;
    }
    mine = 0;
    if (D_0063B13C & 1) {
        debug_Printf(10, 70, 0xFFFFFFFF, damageFmt, *(int *)(w + 0x18));
    }
    for (i = 0; i < 1; i++) {
        char *o = (char *)isysGObjSearchFromObjLayoutID(tbl[i]);

        if (o == 0) {
            continue;
        }
        if (*(signed char *)(*(char **)((char *)GOBJ_SUB(o) + 0x830) + 0x12) != 0) {
            continue;
        }
        break;
    }
    found = i;
    for (i = 0; i < 1; i++) {
        if (*(int *)(g + 8) == tbl[i]) {
            mine = i;
            break;
        }
    }
    GetRootPosition(&rootPos, queen);
    if (*(signed char *)(w + 0x12) == 0 || *(int *)(queen + 0x16C) == 0 ||
        (*(int *)qw & 0xFF0000FF) != 0 || *(signed char *)(qw + 1) == 0) {
        GetRootMatrix(&m1, g);
        sceVu0CopyVector(&m1.w, &pos);
        CopyMatrix(*(void **)((char *)GOBJ_SUB(g) + 0xC), &m1);
    } else {
        axis.f[0] = 0.05235987901687622f;
        axis.f[1] = 0.0872664675116539f;
        axis.f[2] = 0.12217305600643158f;
        axis.f[3] = 0.0f;
        ofs = axis;
        sceVu0ScaleVector(&ofs, &ofs,
                          (float)(unsigned int)(-mine) * 0.019999999552965164f +
                              0.05000000074505806f);
        sceVu0AddVector(w + 0x20, w + 0x20, &ofs);
        *(float *)(w + 0x20) = WrapRad(*(float *)(w + 0x20));
        *(float *)(w + 0x24) = WrapRad(*(float *)(w + 0x24));
        *(float *)(w + 0x28) = WrapRad(*(float *)(w + 0x28));
        UnitMatrix33(&rot);
        sceVu0CopyVector(&trans, w);
        CopyMatrix(*(void **)((char *)GOBJ_SUB(g) + 0xC), &rot);
    }
    if (*(signed char *)(w + 0x10) != 0 && mine == found - 1) {
        void *weapon;

        *(int *)(qw + 4) = 0;
        weapon = (void *)*(int *)(*(int *)(D_00639EA4 + 0x164) + 0x150);
        if (weapon != 0) {
            LightTorchOffOfWeapon(weapon);
        }
        *(int *)(qw + 8) = 0x12;
        ExecuteSEPackage((int)g, 0x5F);
        *(int *)(w + 0x18) = *(int *)(w + 0x18) + 1;
        if (*(int *)(w + 0x18) >= 5) {
            GetRootMatrix(&m3, g);
            sceVu0CopyVector(&m3.w, &pos);
            CopyMatrix(*(void **)((char *)GOBJ_SUB(g) + 0xC), &m3);
            *(char *)(w + 0x12) = 0;
            ExecuteSEPackage((int)D_00639EA4, 0x62);
        }
    }
    if (*(int *)(qw + 8) > 0) {
        *(int *)(qw + 8) = *(int *)(qw + 8) - 1;
    }
    *(char *)(w + 0x10) = 0;
    queen_barrier_anim();
}

void QueenBarrierDL(char *g)
{
    char *b = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    if (*(signed char *)(b + 0x12)) {
        queen_barrier_disp_proc(1.0f - *(int *)(b + 0x18) / 5.0f);
    }
}

/* ROM 0x0012B6F0 never reads $a1: the callee takes (id, scale) only. */
/* kept local: this TU's uses of ico_m33_to_quat do not fit the prototype in itou_sub.h */
extern void ico_m33_to_quat(void *dst, void *m);
/* kept local: this TU's uses of pbga_start do not fit the prototype in itou_sub.h */
extern void pbga_start(int *bga, int id);
/* kept local: this TU's uses of _GetLength do not fit the prototype in Matrix.h */
extern float _GetLength(QVec *a, QVec *b);
/* kept local: this TU's uses of apply_matrix_w1 do not fit the prototype in itou_sub.h */
extern void apply_matrix_w1(QVec *dst, QMat33 *m, QVec *src);
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *dst, void *src);

/* PAL listing rows 1069-1081: a static helper that QueenBallGeo and QueenBallDL
 * each expand inline. */
static inline void SetQueenBallOrient(char *o, QVec *from, QVec *to)
{
    QVec side;
    QVec up = {{0.0f, 1.0f, 0.0f, 1.0f}};
    QVec dir;
    QMat33 m;

    sceVu0CopyVector(o + 0x20, to);
    sceVu0SubVector(&dir, from, to);
    dir.f[1] = 0.0f;
    sceVu0Normalize(&dir, &dir);
    sceVu0OuterProduct(&side, &up, &dir);
    sceVu0CopyVector(&m.x, &side);
    sceVu0CopyVector(&m.y, &up);
    sceVu0CopyVector(&m.z, &dir);
    ico_m33_to_quat(o + 0x30, &m);
}

/* r4/r5 seed (rc55 / 36 sites) at scratchpad/seeds/QueenBallGeo.r5.body.c (this
 * block, incl. the three helpers it alone expands) and .r4.rc55.c (whole-TU).
 * Residual: the FP-constant census, see LEDGER r4. */
/* PAL listing rows 1092-1093. */
static inline void StartQueenBallEffect(int *bga, int id, QVec *from, QVec *to)
{
    if (*bga == 0) {
        pbga_start(bga, id);
        SetQueenBallOrient((char *)*bga, from, to);
    }
}

/* PAL listing rows 1105-1116. */
static inline void CheckQueenBallRing(int *bga, int id, QVec *from, QVec *to, float r)
{
    float d = _GetLength(to, from);
    int in = (d < r && r < d + 100.0f);

    if (in) {
        StartQueenBallEffect(bga, id, from, to);
    }
}

/* PAL listing rows 1131-1151: the parameterised box test.  Builds the frame that
 * looks from `from` towards `pos`, transforms `target` into it and reports whether
 * the target sits inside the box around `pos`.
 *
 * The half-width and the near plane are ints and the half-height and the far plane
 * floats: that asymmetry is what ROM's register census shows.  A float parameter is
 * bound by a movsf at the top of the inlined body (the listing attributes 300.0f and
 * 600.0f to queen.c:1131, the helper's own first line) and inside the object loop it
 * can never be sunk to its use, so it takes a callee-saved FP register; an int
 * parameter is substituted as a CONST_INT by integrate.c's const_equiv_map, the
 * int->float conversion folds to a CONST_DOUBLE at the compare itself, and ROM
 * materialises 130.0f/-120.0f there in a call-clobbered register (queen.c:1150). */
static inline int CheckQueenBallBox(QVec *pos, QVec *from, QVec *target, int xl, float yl, int zmin,
                                    float zmax)
{
    QVec side;
    QVec up = {{0.0f, 1.0f, 0.0f, 1.0f}};
    QVec dir;
    QMat33 m;
    QMat33 inv;
    QVec out;
    int hit = 0;

    sceVu0SubVector(&dir, pos, from);
    dir.f[1] = 0.0f;
    sceVu0Normalize(&dir, &dir);
    sceVu0OuterProduct(&side, &up, &dir);
    sceVu0CopyVector(&m.x, &side);
    sceVu0CopyVector(&m.y, &up);
    sceVu0CopyVector(&m.z, &dir);
    sceVu0CopyVector(&m.w, pos);
    m.x.f[3] = m.y.f[3] = m.z.f[3] = 0.0f;
    m.w.f[3] = 1.0f;
    sceVu0InversMatrix(&inv, &m);
    apply_matrix_w1(&out, &inv, target);
    if (__builtin_fabsf(out.f[0]) < xl && __builtin_fabsf(out.f[1]) < yl && out.f[2] >= zmin &&
        out.f[2] < zmax) {
        hit = 1;
    }
    return hit;
}

void QueenBallGeo(char *g)
{
    /* The root matrix is a plain float matrix, not a QMat33 of the (union) QVec:
     * ROM's scheduler hoists the CopyMatrix destination load above the far-position
     * stores of the else arm below, which a store through a union member -- alias
     * set 0, conflicting with every load -- would forbid. */
    float m[4][4];
    QVec queenPos;
    int num;
    int i;
    char *weapon;
    char *w;
    char *ball;
    char *o;
    char *sword;
    char *act;
    int *bga;
    int hit;
    float r;

    w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    ball = isysGObjSearchFromObjKindID_begin(54);
    num = (ball != 0) ? *(int *)(*(char **)((char *)GOBJ_SUB(ball) + 0x830) + 0x18) : 0;
    r = *(float *)(w + 0x14) * 100.0f;
    weapon = *(char **)(*(char **)(D_00639EA4 + 0x164) + 0x150);
    GetRootMatrix(m, g);
    GetRootPosition(&queenPos, D_00639EA4);
    i = 0;
    act = *(char **)(D_00639EA4 + 0x164);
    hit = (*(int *)(act + 0x34) == 0x31);
    if (*(signed char *)(w + 0x11) != 0) {
        for (o = isysGObjSearchFromObjKindID_begin(17); o != 0;
             o = isysGObjSearchFromObjKindID_next(o), i++) {
            QVec objPos;

            GetRootPosition(&objPos, o);
            hit |= CheckQueenBallBox(&objPos, (QVec *)m[3], &queenPos, 130, 300.0f, -120, 600.0f);
            bga = &queenBga[i];
            CheckQueenBallRing(bga, 0x1E2, (QVec *)m[3], &objPos, r);
            if (*bga != 0) {
                SetQueenBallOrient((char *)*bga, (QVec *)m[3], &objPos);
            }
        }
        if (*(signed char *)(w + 0x11) != 0) {
            sword = isysGObjSearchFromObjKindID_begin(14);
            if (weapon == 0 && sword != 0) {
                QVec objPos;

                GetRootPosition(&objPos, sword);
                hit |=
                    CheckQueenBallBox(&objPos, (QVec *)m[3], &queenPos, 75, 300.0f, -150, 500.0f);
                CheckQueenBallRing(&queenBga[2], 0x1E4, (QVec *)m[3], &objPos, r);
            }
        }
    }
    if (hit) {
        GOBJ_SUB(g)->f_74 = 0;
    } else {
        GOBJ_SUB(g)->f_74 = 1;
    }
    if (*(signed char *)(w + 0x18) != 0) {
        *(char *)(w + 0x18) = 0;
        *(char *)(w + 0x11) = 0;
        pbga_start((int *)(w + 0x1C), 0x1DF);
        _CopyVector(*(char **)(w + 0x1C) + 0x20, m[3]);
        CopyQuaternion(*(char **)(w + 0x1C) + 0x30, IdentityQuaternion);
        ExecuteSEPackage((int)g, 0x5E);
    }
    if (*(signed char *)(w + 0x1A) != 0) {
        *(char *)(w + 0x1A) = 0;
        *(char *)(w + 0x10) = 0;
        *(char *)(w + 0x11) = 0;
    }
    if (*(signed char *)(w + 0x11) != 0) {
        UnitMatrix33((QMat3 *)m);
        scale_m34((LVec *)m, m, *(float *)(w + 0x14));
        CopyMatrix(*(void **)((char *)GOBJ_SUB(g) + 0xC), m);
        if (hit == 0 && *(signed char *)(w + 0x19) == 0 &&
            _AttackCenter(g, 0x10, m[3], 0, r, 0) != 0) {
            *(char *)(w + 0x19) = 1;
            if (weapon != 0) {
                ExecuteSEPackage((int)D_00639EA4, 0x61);
            } else {
                ExecuteSEPackage((int)D_00639EA4, 0x5B);
            }
        }
        if (r > 5000.0f) {
            *(char *)(w + 0x10) = 0;
            *(char *)(w + 0x11) = 0;
        }
        {
            /* Per-ball-index growth rate, one table per stage.  ROM selects the
             * table ENTRY, not the table: the sll/addu that index it are shared by
             * both arms, and the address pseudo is the one that survives the join. */
            float *rate;

            if (stage_no == 0x25) {
                rate = &ballSpeedRateSt25[num];
            } else {
                rate = &ballSpeedRateDefault[num];
            }
            *(float *)(w + 0x14) += *rate;
        }
    } else {
        m[3][0] = 4294967296.0f;
        m[3][1] = 4294967296.0f;
        m[3][2] = 4294967296.0f;
        m[3][3] = 0.0f;
        CopyMatrix(*(void **)((char *)GOBJ_SUB(g) + 0xC), m);
    }
}

/* The loop is written ASCENDING: gcc's check_dbra_loop reverses it into ROM's
 * `addiu $18,$18,-1` / `bgez $18` countdown, which is what puts the counter's
 * initial value after loop.c's hoisted 0x1E3/0x1E5 constants. */
void QueenBallDL(char *g)
{
    QVec ballPos;
    QVec selfPos;
    QVec queenPos;
    char *w;
    char *o;
    int *q;
    int i;

    w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    if (*(signed char *)(w + 0x11) != 0) {
        GetRootPosition(&ballPos, g);
        SetupDarkVolume(&ballPos, *(float *)(w + 0x14) * 100.0f, 10.0f);
        p2o_SetDefaultEnviroment();
        p2o_DispVU1Default(g);
    }
    if (*(int *)(w + 0x1C) != 0) {
        stage_SetScale(0x1DF, *(float *)(w + 0x14));
        if (stage_DispBgAnimation(w + 0x1C) != 0) {
            char *act;

            *(int *)(w + 0x1C) = 0;
            *(char *)(w + 0x10) = 0;
            act = *(char **)(g + 0x164);
            *(int *)(act + 0x1B0) = 0;
            *(char *)(act + 0x1DA) = 0;
        }
    }
    GetRootPosition(&selfPos, g);
    GetRootPosition(&queenPos, D_00639EA4);
    q = queenBga;
    for (i = 0; i < 4; i++, q++) {
        if ((o = (char *)*q) != 0) {
            long long id = *(long long *)o & 0x3FFF;

            if (id == 0x1E3 || id == 0x1E5) {
                SetQueenBallOrient(o, &selfPos, &queenPos);
            }
            if (stage_DispBgAnimation(q) != 0) {
                *q = 0;
            }
        }
    }
}

void actQueenStart(char *g)
{
    char *sub = actInitialize(g);

    actInitialize_ext_charcter(g);
    _ACTWait(1);
    actCreateSubThread(subQueenBrainMain, 20);
    actCreateSubThread(subQueenControl, 21);
    actCreateSubThread(gene_enemy, 21);
    *(int *)(sub + 0x130) = SetMotionRequest(g, 0x10E, sub + 0x620);
    GOBJ_SUB(g)->f_7C = 1;
}

void QueenStartAttack(void)
{
    char *g;

    g = isysGObjSearchFromObjKindID_begin(47);
    *(char *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 1) = 1;

    g = isysGObjSearchFromObjKindID_begin(54);
    while (g != 0) {
        *(char *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 0x12) = 1;
        g = isysGObjSearchFromObjKindID_next(g);
    }
}

int QueenInqDead(void)
{
    char *g = isysGObjSearchFromObjKindID_begin(47);
    return *(signed char *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 3);
}

int QueenBoysWeaponPower(void)
{
    char *g = isysGObjSearchFromObjKindID_begin(47);
    return *(int *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 4);
}

float QueenBarrierRadius(char *a0)
{
    return *(float *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x14);
}

int QueenBarrierInqBreakable(void)
{
    char *b;
    int ret = 0;

    b = *(char **)(*(char **)(isysGObjSearchFromObjKindID_begin(47) + 0x15C) + 0x830);
    if (*(int *)(b + 4) > 0 || *(int *)(b + 8) > 0) {
        ret = 1;
    }
    return ret;
}

void queenBarrierBeforeFunc(char *g)
{
    QueenMailQueue *q = (QueenMailQueue *)(g + 0x54);
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    char *other;
    int i;

    for (i = 0; i < q->num; i++) {
        QueenMailEntry *e = &q->e[i];

        if (e->mail == 0xD) {
            debug_StdPrintfDummy(queenBarrierAttackedMsg);
            *(char *)(w + 0x10) = 1;
            *(char *)(w + 0x11) = 1;
            other = isysGObjSearchFromObjKindID_begin(53);
            if (other != 0) {
                *(char *)(*(char **)((char *)GOBJ_SUB(other) + 0x830) + 0x1A) = 1;
            }
            queen_barrier_set_damage();
        }
    }
    q->num = 0;
}

int InqQueenBarrierExist(void)
{
    char *g;
    int exist = 0;

    g = isysGObjSearchFromObjKindID_begin(54);
    if (g != 0) {
        exist = *(int *)(*(char **)((char *)GOBJ_SUB(g) + 0x830) + 0x18) < 5;
    }
    return exist;
}

void *InitQueenBarrierGeo(char *g)
{
    char *w;

    Sub15C *ext = GOBJ_SUB(g);

    w = (char *)iosMallocDebug(D_0063A438, 0x30, queenFile, 991);
    memset(w, 0, 0x30);
    *(char **)((char *)ext + 0x830) = w;
    *(float *)(w + 0x14) = 300.0f;
    GetRootPosition(w, g);
    actInitialize(g);
    actInitialize_ext_charcter(g);
    queen_barrier_disp_init();
    return w;
}

float QueenBallRadius(char *a0)
{
    return *(float *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x14) * 100.0f;
}

float GetQueenBallThickness(void)
{
    return 150.0f;
}

void queenBallBeforeFunc(char *g)
{
    QueenMailQueue *q = (QueenMailQueue *)(g + 0x54);
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    int i;

    for (i = 0; i < q->num; i++) {
        QueenMailEntry *e = &q->e[i];

        if (e->mail != 0xD) {
            debug_StdPrintfDummy(mailFmt, e->mail);
        } else if (scpGameStat_BoyWeaponkind() == 5) {
            debug_StdPrintfDummy(queenBallAttackedMsg);
            *(char *)(w + 0x18) = 1;
            iosOmSendMail(D_00639EA4, 0x1A9, g);
        }
    }
    q->num = 0;
}

void *InitQueenBallGeo(char *g)
{
    char *w;

    Sub15C *ext = GOBJ_SUB(g);

    w = (char *)iosMallocDebug(D_0063A438, 0x20, queenFile, 1284);
    *(char **)((char *)ext + 0x830) = w;
    memset(w, 0, 0x20);
    *(float *)(w + 0x14) = 0.0f;
    GetRootPosition(w, g);
    actInitialize(g);
    actInitialize_ext_charcter(g);
    return w;
}

void subQueenControl(volatile int g)
{
    signed char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);

    _ACTWait(1);
    for (;;) {
        if (*w == 0) {
            Debug_StickControl((char *)g);
        }
        _ACTWait(1);
    }
}
