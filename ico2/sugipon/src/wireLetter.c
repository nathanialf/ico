#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void ChangeColorWireString(int a0, int a1, int a2);
void Draw2DBox(float x0, float y0, float x1, float y1);

typedef struct {
    float x;
    float y;
    int z;
} WLPnt;

/* the vector font: one stroke list per glyph, four floats per stroke
 * (x0, y0, x1, y1), the list ending on a first coordinate of 999999.0.
 * wireLetterGlyphs is indexed by the character minus '.'. */
static float wireLetterA[][4] = {
    -10.0f, -10.0f, 0.0f,  10.0f,  0.0f,      10.0f, 10.0f, -10.0f,
    -7.07f, -4.15f, 7.07f, -4.15f, 999999.0f, 0.0f,  0.0f,  0.0f,
};

static float wireLetterB[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 10.0f,  5.0f, 10.0f,  5.0f,      10.0f,  10.0f, 5.0f,
    5.0f,   0.0f,   10.0f,  5.0f,  -10.0f, 0.0f,   5.0f, 0.0f,   5.0f,      -10.0f, 10.0f, -5.0f,
    5.0f,   0.0f,   10.0f,  -5.0f, -10.0f, -10.0f, 5.0f, -10.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetterC[][4] = {
    -10.0f, -5.0f,  -5.0f,  -10.0f, -10.0f, 5.0f,  -5.0f,     10.0f, -5.0f,  10.0f, 5.0f,
    10.0f,  10.0f,  5.0f,   5.0f,   10.0f,  -5.0f, -10.0f,    5.0f,  -10.0f, 10.0f, -5.0f,
    5.0f,   -10.0f, -10.0f, 5.0f,   -10.0f, -5.0f, 999999.0f, 0.0f,  0.0f,   0.0f,
};

static float wireLetterD[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f,  -10.0f,    10.0f,  5.0f,  10.0f, 10.0f, 5.0f,
    5.0f,   10.0f,  -10.0f, -10.0f, 5.0f,      -10.0f, 10.0f, -5.0f, 5.0f,  -10.0f,
    10.0f,  5.0f,   10.0f,  -5.0f,  999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetterE[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f,  -10.0f, 10.0f,  10.0f,     10.0f, -10.0f, 0.0f,
    5.0f,   0.0f,   -10.0f, -10.0f, 10.0f,  -10.0f, 999999.0f, 0.0f,  0.0f,   0.0f,
};

static float wireLetterF[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f,    10.0f, 10.0f, 10.0f,
    -10.0f, 0.0f,   10.0f,  0.0f,  999999.0f, 0.0f,  0.0f,  0.0f,
};

static float wireLetterG[][4] = {
    -10.0f, -5.0f, -5.0f, -10.0f, -10.0f, 5.0f,  -5.0f,     10.0f,  -5.0f, 10.0f,
    5.0f,   10.0f, 10.0f, 5.0f,   5.0f,   10.0f, -5.0f,     -10.0f, 5.0f,  -10.0f,
    10.0f,  -5.0f, 5.0f,  -10.0f, -10.0f, 5.0f,  -10.0f,    -5.0f,  10.0f, 0.0f,
    10.0f,  -5.0f, 10.0f, 0.0f,   0.0f,   0.0f,  999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetterH[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, 10.0f,     -10.0f, 10.0f, 10.0f,
    -10.0f, 0.0f,   10.0f,  0.0f,  999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetterI[][4] = {
    0.0f, -10.0f, 0.0f, 10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetterJ[][4] = {
    10.0f, 10.0f,  10.0f, -5.0f,  10.0f,  -5.0f, 5.0f,      -10.0f, 5.0f, -10.0f,
    -5.0f, -10.0f, -5.0f, -10.0f, -10.0f, -5.0f, 999999.0f, 0.0f,   0.0f, 0.0f,
};

static float wireLetterK[][4] = {
    -10.0f, 10.0f,  -10.0f, -10.0f, 10.0f,     10.0f, -10.0f, 0.0f,
    10.0f,  -10.0f, -10.0f, 0.0f,   999999.0f, 0.0f,  0.0f,   0.0f,
};

static float wireLetterL[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetterM[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f,  10.0f, -10.0f, 10.0f,     10.0f, 0.0f, -10.0f,
    -10.0f, 10.0f,  0.0f,   -10.0f, 10.0f, 10.0f,  999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetterN[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, 10.0f,     -10.0f, -10.0f, 10.0f,
    10.0f,  -10.0f, 10.0f,  10.0f, 999999.0f, 0.0f,   0.0f,   0.0f,
};

static float wireLetterO[][4] = {
    -10.0f, -5.0f,  -5.0f,  -10.0f, -10.0f, 5.0f, -5.0f, 10.0f, -5.0f,     10.0f, 5.0f, 10.0f,
    -5.0f,  -10.0f, 5.0f,   -10.0f, 10.0f,  5.0f, 5.0f,  10.0f, 10.0f,     -5.0f, 5.0f, -10.0f,
    -10.0f, 5.0f,   -10.0f, -5.0f,  10.0f,  5.0f, 10.0f, -5.0f, 999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetterP[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 10.0f, 5.0f,   10.0f, 5.0f,      10.0f, 10.0f, 5.0f,
    10.0f,  5.0f,   5.0f,   0.0f,  5.0f,   0.0f,  -10.0f, 0.0f,  999999.0f, 0.0f,  0.0f,  0.0f,
};

static float wireLetterQ[][4] = {
    -10.0f, -5.0f, -5.0f, -10.0f, -10.0f, 5.0f,   -5.0f,     10.0f, -5.0f, 10.0f,
    5.0f,   10.0f, -5.0f, -10.0f, 5.0f,   -10.0f, 10.0f,     5.0f,  5.0f,  10.0f,
    10.0f,  -5.0f, 5.0f,  -10.0f, -10.0f, 5.0f,   -10.0f,    -5.0f, 10.0f, 5.0f,
    10.0f,  -5.0f, 0.0f,  0.0f,   10.0f,  -10.0f, 999999.0f, 0.0f,  0.0f,  0.0f,
};

static float wireLetterR[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f,  -10.0f,    10.0f, 5.0f, 10.0f, 5.0f,   10.0f,
    10.0f,  5.0f,   10.0f,  5.0f,   5.0f,      0.0f,  5.0f, 0.0f,  -10.0f, 0.0f,
    0.0f,   0.0f,   10.0f,  -10.0f, 999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetterS[][4] = {
    10.0f,  5.0f,   5.0f,   10.0f,  5.0f,   10.0f, -5.0f,     10.0f,  -5.0f, 10.0f,
    -10.0f, 5.0f,   -10.0f, 5.0f,   -5.0f,  0.0f,  -5.0f,     0.0f,   5.0f,  0.0f,
    5.0f,   0.0f,   10.0f,  -5.0f,  10.0f,  -5.0f, 5.0f,      -10.0f, 5.0f,  -10.0f,
    -5.0f,  -10.0f, -5.0f,  -10.0f, -10.0f, -5.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetterSlash[][4] = {
    -10.0f, 5.0f,  -5.0f, 10.0f,  -5.0f, 10.0f,  5.0f,      10.0f, 5.0f, 10.0f, 10.0f,
    5.0f,   10.0f, 5.0f,  5.0f,   0.0f,  5.0f,   0.0f,      0.0f,  0.0f, 0.0f,  0.0f,
    0.0f,   -5.0f, 0.0f,  -10.0f, 0.0f,  -15.0f, 999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetterDot[][4] = {
    0.0f, -10.0f, 0.0f, -15.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetterT[][4] = {
    -10.0f, 10.0f, 10.0f, 10.0f, 0.0f, -10.0f, 0.0f, 10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetterU[][4] = {
    -10.0f, 10.0f,  -10.0f, -5.0f, -10.0f, -5.0f, -5.0f, -10.0f, -5.0f,     -10.0f, 5.0f, -10.0f,
    5.0f,   -10.0f, 10.0f,  -5.0f, 10.0f,  -5.0f, 10.0f, 10.0f,  999999.0f, 0.0f,   0.0f, 0.0f,
};

static float wireLetterV[][4] = {
    -10.0f, 10.0f, 0.0f, -10.0f, 0.0f, -10.0f, 10.0f, 10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetterW[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, 10.0f, -10.0f, 10.0f,     10.0f, 0.0f, 0.0f,
    -10.0f, -10.0f, 0.0f,   0.0f,  10.0f, -10.0f, 999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetterY[][4] = {
    -10.0f, 10.0f, 0.0f, 0.0f,   10.0f,     10.0f, 0.0f, 0.0f,
    0.0f,   0.0f,  0.0f, -10.0f, 999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetterX[][4] = {
    -10.0f, 10.0f, 10.0f, -10.0f, -10.0f, -10.0f, 10.0f, 10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetterZ[][4] = {
    -10.0f, 10.0f,  10.0f, 10.0f, -10.0f,    -10.0f, 10.0f, -10.0f,
    -10.0f, -10.0f, 10.0f, 10.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetter0[][4] = {
    -10.0f, -5.0f,  -5.0f,  -10.0f, -10.0f, 5.0f, -5.0f, 10.0f, -5.0f,     10.0f, 5.0f, 10.0f,
    -5.0f,  -10.0f, 5.0f,   -10.0f, 10.0f,  5.0f, 5.0f,  10.0f, 10.0f,     -5.0f, 5.0f, -10.0f,
    -10.0f, 5.0f,   -10.0f, -5.0f,  10.0f,  5.0f, 10.0f, -5.0f, 999999.0f, 0.0f,  0.0f, 0.0f,
};

static float wireLetter1[][4] = {
    0.0f, -10.0f, 0.0f, 10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetter2[][4] = {
    -10.0f, 10.0f,  10.0f, 10.0f, -10.0f,    -10.0f, 10.0f, -10.0f,
    -10.0f, -10.0f, 10.0f, 10.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetter3[][4] = {
    10.0f, -10.0f, 10.0f,  10.0f,  -10.0f, 10.0f,  10.0f,     10.0f, 10.0f, 0.0f,
    -5.0f, 0.0f,   -10.0f, -10.0f, 10.0f,  -10.0f, 999999.0f, 0.0f,  0.0f,  0.0f,
};

static float wireLetter4[][4] = {
    -10.0f, 0.0f, -10.0f, 10.0f, 10.0f,     -10.0f, 10.0f, 10.0f,
    -10.0f, 0.0f, 10.0f,  0.0f,  999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetter5[][4] = {
    10.0f,  5.0f,   5.0f,   10.0f,  5.0f,   10.0f, -5.0f,     10.0f,  -5.0f, 10.0f,
    -10.0f, 5.0f,   -10.0f, 5.0f,   -5.0f,  0.0f,  -5.0f,     0.0f,   5.0f,  0.0f,
    5.0f,   0.0f,   10.0f,  -5.0f,  10.0f,  -5.0f, 5.0f,      -10.0f, 5.0f,  -10.0f,
    -5.0f,  -10.0f, -5.0f,  -10.0f, -10.0f, -5.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetter6[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 10.0f,  5.0f, 10.0f,  5.0f,      10.0f,  10.0f, 5.0f,
    5.0f,   0.0f,   10.0f,  5.0f,  -10.0f, 0.0f,   5.0f, 0.0f,   5.0f,      -10.0f, 10.0f, -5.0f,
    5.0f,   0.0f,   10.0f,  -5.0f, -10.0f, -10.0f, 5.0f, -10.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetter7[][4] = {
    -10.0f, 10.0f, 10.0f, 10.0f, 0.0f, -10.0f, 0.0f, 10.0f, 999999.0f, 0.0f, 0.0f, 0.0f,
};

static float wireLetter8[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 10.0f,  5.0f, 10.0f,  5.0f,      10.0f,  10.0f, 5.0f,
    5.0f,   0.0f,   10.0f,  5.0f,  -10.0f, 0.0f,   5.0f, 0.0f,   5.0f,      -10.0f, 10.0f, -5.0f,
    5.0f,   0.0f,   10.0f,  -5.0f, -10.0f, -10.0f, 5.0f, -10.0f, 999999.0f, 0.0f,   0.0f,  0.0f,
};

static float wireLetter9[][4] = {
    -10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 10.0f, 5.0f,   10.0f, 5.0f,      10.0f, 10.0f, 5.0f,
    10.0f,  5.0f,   5.0f,   0.0f,  5.0f,   0.0f,  -10.0f, 0.0f,  999999.0f, 0.0f,  0.0f,  0.0f,
};

static float *wireLetterGlyphs[48] = {
    &wireLetterDot[0][0],
    &wireLetterSlash[0][0],
    &wireLetter0[0][0],
    &wireLetter1[0][0],
    &wireLetter2[0][0],
    &wireLetter3[0][0],
    &wireLetter4[0][0],
    &wireLetter5[0][0],
    &wireLetter6[0][0],
    &wireLetter7[0][0],
    &wireLetter8[0][0],
    &wireLetter9[0][0],
    &wireLetterSlash[0][0],
    &wireLetterSlash[0][0],
    &wireLetterSlash[0][0],
    &wireLetterSlash[0][0],
    &wireLetterSlash[0][0],
    &wireLetterSlash[0][0],
    &wireLetterQ[0][0],
    &wireLetterA[0][0],
    &wireLetterB[0][0],
    &wireLetterC[0][0],
    &wireLetterD[0][0],
    &wireLetterE[0][0],
    &wireLetterF[0][0],
    &wireLetterG[0][0],
    &wireLetterH[0][0],
    &wireLetterI[0][0],
    &wireLetterJ[0][0],
    &wireLetterK[0][0],
    &wireLetterL[0][0],
    &wireLetterM[0][0],
    &wireLetterN[0][0],
    &wireLetterO[0][0],
    &wireLetterP[0][0],
    &wireLetterQ[0][0],
    &wireLetterR[0][0],
    &wireLetterS[0][0],
    &wireLetterT[0][0],
    &wireLetterU[0][0],
    &wireLetterV[0][0],
    &wireLetterW[0][0],
    &wireLetterX[0][0],
    &wireLetterY[0][0],
    &wireLetterZ[0][0],
    0,
    0,
    0,
};

static int wireStringColorDefault[4] = {0x80, 0xC8, 0xFF, 0x80};

static int wireStringColor[4] = {0x80, 0xC8, 0xFF, 0x80};

extern void DrawLineG(void *a0, void *a1, void *a2, void *a3, int a4);
extern void gif_EndPacket(void);
extern void gif_StartPacketPri(int a0);

inline void Draw2DBox(float x0, float y0, float x1, float y1)
{
    WLPnt a __attribute__((aligned(16))) = {x0, y0, 0};
    WLPnt b __attribute__((aligned(16))) = {x0, y1, 0};
    WLPnt c __attribute__((aligned(16))) = {x1, y1, 0};
    WLPnt d __attribute__((aligned(16))) = {x1, y0, 0};
    gif_StartPacketPri(0xB);
    DrawLineG(&a, wireStringColor, &b, wireStringColor, -1);
    DrawLineG(&b, wireStringColor, &c, wireStringColor, -1);
    DrawLineG(&c, wireStringColor, &d, wireStringColor, -1);
    DrawLineG(&d, wireStringColor, &a, wireStringColor, -1);
    gif_EndPacket();
}

extern int D_0063B188;
extern int strlen();
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void gif_SetAlpha(int a, int b, int c);
void DispWireLetter(int c);

void DispWireLetter(int c)
{
    int idx = c - '.';
    float *p;
    int i;

    if (c != ' ') {
        p = wireLetterGlyphs[idx];
        if (p != 0) {
            MatrixDrive_PushMatrix();
            gif_StartPacketPri(0xB);
            gif_SetAlpha(1, 5, 0);
            for (i = 0; p[i * 4] < 100.0f; i++) {
                WLPnt a = {p[i * 4 + 0], -p[i * 4 + 1], 0};
                WLPnt b = {p[i * 4 + 2], -p[i * 4 + 3], 0};

                DrawLineG(&a, wireStringColor, &b, wireStringColor, -1);
            }
            gif_EndPacket();
            MatrixDrive_PopMatrix();
        }
    }
}

void DispWireString(char *s)
{
    int len;
    int w;

    len = strlen(s);
    if (D_0063B188 == 0) {
        return;
    }
    if (len == 0) {
        return;
    }
    w = (int)((float)len * 20.0f + (float)(len - 1) * 3.0f);
    MatrixDrive_ScaleMatrix(0.7f, 0.7f, 0.7f);
    MatrixDrive_TransMatrix((float)(-w / 2) + 10.0f, 0.0f, 0.0f);
    if (len > 0)
        for (w = len; w != 0; w--) {
            DispWireLetter(*s++);
            MatrixDrive_TransMatrix(23.0f, 0.0f, 0.0f);
        }
}

inline void ChangeColorWireString(int a0, int a1, int a2)
{
    wireStringColor[0] = a0;
    wireStringColor[1] = a1;
    wireStringColor[2] = a2;
}

void DefaultColorWireString(void)
{
    int new_var;
    new_var = wireStringColorDefault[1];
    wireStringColor[0] = wireStringColorDefault[0];
    wireStringColor[1] = new_var;
    wireStringColor[2] = wireStringColorDefault[2];
}
