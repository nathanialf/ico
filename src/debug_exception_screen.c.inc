/* debug_exception_screen.c.inc -- the debug screen primitives (Vif1 direct packets, GS draw environments, the 26x256 text
 * screen, sprite/font blits). #included once at the top of debug_exception.c: the PAL listing (SRCFILE.TXT) names
 * this file for these functions and MAIN.MAP lists them under debug_exception.o; debug.c calls them as externs.
 * The three Vif1/GIF helpers are inline (they inline into drawSprite/PutFont and their out-of-line copies close the
 * object); the rest are ordinary functions emitted in this order. */
extern int strlen();
extern void vsprintf();
extern int D_0028F4F0[];
extern void gsb_Init();
extern void sceVif1PkCloseDirectCode();
extern void sceVif1PkCloseGifTag();
extern void sceVif1PkEnd();
extern void sceVif1PkTerminate();
extern int sceDmaGetChan(unsigned a0);
extern void sceDmaSend();
extern void sceGsSyncPath();
extern int sceGsSetDefTexEnv();
extern int sceGsSetDefAlphaEnv();
extern unsigned long long D_004DA4D0[];
extern int sceGsSetDefDrawEnv();
extern unsigned long long D_004DA570[];
extern unsigned long long D_004DA600[];
extern unsigned long long D_004DA6A0[];
typedef unsigned int u128_dbgscr __attribute__((mode(TI)));
/* sceVif1Packet: 0x20 bytes (two per drawSprite frame at sp+0x00 / sp+0x20).
 * Field offsets 0x00/0x04/0x0C/0x14 are the ones the libpkt bodies in
 * src/cod/vendor_25EC00.c touch; 0x08/0x10/0x18 are unused here. */
typedef struct {
    int *cur;
    int *base;
    int *f_8;
    int *directTag;
    int *f_10;
    int *gifTag;
    int f_18[2];
} Vif1Packet;
extern void sceVif1PkInit();
extern void sceVif1PkReset();
extern void sceVif1PkCnt();
extern void sceVif1PkOpenDirectCode();
extern void sceVif1PkOpenGifTag(void *packet, u128_dbgscr tag);
extern void sceVif1PkAddGsData(void *packet, unsigned long long data);
extern int D_0063B370;
extern unsigned int D_0063B374;
extern unsigned int D_0063B378;
extern int D_0063A064;
extern int D_0063A068;
extern u128_dbgscr D_0061CF20[];
extern u128_dbgscr D_0061CF30[];
extern u128_dbgscr D_004DA740[];
extern u128_dbgscr D_004DA750[];
extern int D_0063B37C;
extern int D_0063B380;
extern int D_0063B384;
extern const unsigned char D_0061C590[];
extern u128_dbgscr D_004DA760[];
extern void sceDmaReset(int a0);
extern void sceDmaSync(int *a0, int a1, int a2);
extern void sceGsResetPath(void);
extern void sceVpu0Reset();
typedef struct {
    int col;
    char ch;
} DbgChar;
extern DbgChar D_0070FA90[26][256];
extern DbgChar D_0063B388;
extern int D_0063B394;
extern int D_0063B398;
extern int D_0063B390;
extern void SetDrawEnvironment(int a0);
extern void drawSprite(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
typedef struct { int _0; int _4; int _8; int btn; } DbgPad;
extern DbgPad D_0028F8F0[];
extern int D_0063B39C;
extern int buffer_ID;
extern int odd_even;
extern int frame_count;
extern void FlushCache(int a0);
extern void RestoreNormalDrawEnvironment(void *a0, int a1, int a2);
extern void gsb_Reduction(void);
extern void sceGsSwapDBuff(void *a0, int a1);
extern void sceGsSyncPath__pn(int a0, int a1) __asm__("sceGsSyncPath");
extern int sceGsSyncV(int a0);
inline void OpenVif1DirectPacket(void *packet) {
    sceVif1PkInit(packet, (D_0063B370 << 13) | 0x70000000);
    sceVif1PkReset(packet);
    sceVif1PkCnt(packet, 0);
    sceVif1PkOpenDirectCode(packet, 0);
    D_0063B370 = (D_0063B370 + 1) & 1;
}
void CloseVif1DirectPacket(int a0)
{
    sceVif1PkCloseGifTag(a0);
    sceVif1PkCloseDirectCode(a0);
    sceVif1PkEnd(a0, 0);
    sceVif1PkTerminate(a0);
}
void SendVif1DirectPacket(int *self)
{
    int *p;
    sceGsSyncPath(0, 0);
    p = sceDmaGetChan(1);
    *p |= 0x40;
    sceDmaSend(p, (self[0x4/4] & 0x3FF0) | 0x80000000);
}
void RestoreNormalDrawEnvironment(void *a0, int a1, int a2) {
    unsigned int base = (unsigned int)a0 | 0x20000000;
    if (a1 != 0) {
        sceGsSetHalfOffset((void *)(base + 0x150), 0x800, 0x800, (short)a2);
        sceGsPutDrawEnv((void *)(base + 0x140));
    } else {
        sceGsSetHalfOffset((void *)(base + 0x60), 0x800, 0x800, (short)a2);
        sceGsPutDrawEnv((void *)(base + 0x50));
    }
}
void SetTextureWithFrameBuffer(int x)
{
    unsigned long long *env;

    env = (unsigned long long *)((unsigned int)D_004DA4D0 | 0x20000000);
    sceGsSetDefTexEnv(&env[12], 0, (short)x, (short)(D_0063A064 / 64), 1, 10, 8, 0, 0, 0, 0, 1);
    sceGsSetDefAlphaEnv(&env[4], 0);
    env[4] = 0x44;
    env[2] = 0x20000;
    env[3] = 0x47;
    env[18] = 0;
    env[14] = 0x61;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
void SetTexDrawEnvironment(int addr)
{
    unsigned long long *env;

    env = (unsigned long long *)((unsigned int)D_004DA570 | 0x20000000);
    sceGsSetDefDrawEnv(&env[2], 0, (short)D_0063A064, (short)D_0063A068, 1, 0x31);
    env[2] = (env[2] & ~0x1FF) | ((addr / 32) & 0x1FF);
    env[4] |= 0x100000000;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
void SetDrawnTextureEnvironment(int x)
{
    unsigned long long *env;

    env = (unsigned long long *)((unsigned int)D_004DA600 | 0x20000000);
    sceGsSetDefTexEnv(&env[12], 0, (short)x, (short)(D_0063A064 / 64), 0, 10, 8, 0, 0, 0, 0, 1);
    sceGsSetDefAlphaEnv(&env[4], 0);
    env[4] = 0x44;
    env[2] = 0x20000;
    env[3] = 0x47;
    env[18] = 0;
    env[14] = 0x61;
    env[10] = 0;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
void SetDrawEnvironment(int mode)
{
    unsigned long long *env;

    env = (unsigned long long *)((unsigned int)D_004DA6A0 | 0x20000000);
    sceGsSetDefAlphaEnv(&env[4], 0);
    switch (mode) {
    case 0:
        env[4] = 0x48;
        break;
    case 1:
        env[4] = 0x44;
        break;
    case 2:
        env[4] = 0x42;
        break;
    case 3:
        env[4] = 0x0000002800000064ULL;
        break;
    case 4:
        env[4] = 0x68;
        break;
    }
    env[2] = 0x20000;
    env[3] = 0x47;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(env);
}
inline void SetPrimColor(int prim, int r, int g, int b, int a) {
    Vif1Packet packet;
    OpenVif1DirectPacket(&packet);
    sceVif1PkOpenGifTag(&packet, D_0061CF20[0]);
    sceVif1PkAddGsData(&packet, prim | 0x40);
    sceVif1PkAddGsData(&packet,
                       (unsigned long long)r | ((unsigned long long)g << 8) |
                           ((unsigned long long)b << 16) | ((unsigned long long)a << 24) |
                           ((unsigned long long)D_0063B374 << 32));
    CloseVif1DirectPacket((int)&packet);
    SendVif1DirectPacket((int *)&packet);
}
inline void SetPrimColorTex(int prim, int r, int g, int b, int a, int fst) {
    Vif1Packet packet;
    unsigned long long data;
    OpenVif1DirectPacket(&packet);
    sceVif1PkOpenGifTag(&packet, D_0061CF30[0]);
    data = prim | 0x10;
    if (fst != 0) {
        data |= 0x100;
    }
    sceVif1PkAddGsData(&packet, data);
    sceVif1PkAddGsData(&packet,
                       (unsigned long long)r | ((unsigned long long)g << 8) |
                           ((unsigned long long)b << 16) | ((unsigned long long)a << 24) |
                           ((unsigned long long)D_0063B378 << 32));
    CloseVif1DirectPacket((int)&packet);
    SendVif1DirectPacket((int *)&packet);
}
void drawSprite(int r, int g, int b, int a, int x0, int y0, int x1, int y1, int tex) {
    Vif1Packet packet;

    if (tex != 0) {
        SetPrimColorTex(6, r, g, b, a, 1);
        OpenVif1DirectPacket(&packet);
        sceVif1PkOpenGifTag(&packet, D_004DA740[0]);
        sceVif1PkAddGsData(&packet, 0);
        sceVif1PkAddGsData(&packet,
                           (unsigned long long)((x0 + 0x800) << 4) |
                               ((unsigned long long)((y0 + 0x800) << 4) << 16) |
                               0x0080000000000000ULL);
        sceVif1PkAddGsData(&packet,
                           (unsigned long long)(D_0063A064 << 4) |
                               ((unsigned long long)(D_0063A068 << 4) << 16));
        sceVif1PkAddGsData(&packet,
                           (unsigned long long)((x1 + 0x800) << 4) |
                               ((unsigned long long)((y1 + 0x800) << 4) << 16) |
                               0x0080000000000000ULL);
        CloseVif1DirectPacket((int)&packet);
        SendVif1DirectPacket((int *)&packet);
    } else {
        SetPrimColor(6, r, g, b, a);
        OpenVif1DirectPacket(&packet);
        sceVif1PkOpenGifTag(&packet, D_004DA750[0]);
        sceVif1PkAddGsData(&packet,
                           (unsigned long long)((x0 + 0x800) << 4) |
                               ((unsigned long long)((y0 + 0x800) << 4) << 16) |
                               0x0080000000000000ULL);
        sceVif1PkAddGsData(&packet,
                           (unsigned long long)((x1 + 0x800) << 4) |
                               ((unsigned long long)((y1 + 0x800) << 4) << 16) |
                               0x0080000000000000ULL);
        CloseVif1DirectPacket((int)&packet);
        SendVif1DirectPacket((int *)&packet);
    }
}
void PutFont(int c, int x, int y) {
    Vif1Packet packet;
    int i, j;
    int y2 = y + 2;

    SetPrimColor(6, D_0063B37C >> 2, D_0063B380 >> 2, D_0063B384 >> 2, 0x40);
    OpenVif1DirectPacket(&packet);
    sceVif1PkOpenGifTag(&packet, D_004DA760[0]);
    for (j = 0; j < 8; j++) {
        int oy = j * 2 + 0x800;
        for (i = 0; i < 8; i++) {
            if ((D_0061C590[j + c * 8] >> i) & 1) {
                sceVif1PkAddGsData(&packet,
                                   (unsigned long long)((x + i - 2 + 0x800) << 4) |
                                       ((unsigned long long)((y + oy - 1) << 4) << 16) |
                                       0x0080000000000000ULL);
                sceVif1PkAddGsData(&packet,
                                   (unsigned long long)((x + i + 3 + 0x800) << 4) |
                                       ((unsigned long long)((y2 + oy) << 4) << 16) |
                                       0x0080000000000000ULL);
            }
        }
    }
    CloseVif1DirectPacket((int)&packet);
    SendVif1DirectPacket((int *)&packet);

    SetPrimColor(0, D_0063B37C, D_0063B380, D_0063B384, 0x80);
    OpenVif1DirectPacket(&packet);
    sceVif1PkOpenGifTag(&packet, D_004DA760[0]);
    for (j = 0; j < 8; j++) {
        int oy = j * 2 + 0x800;
        for (i = 0; i < 8; i++) {
            if ((D_0061C590[j + c * 8] >> i) & 1) {
                sceVif1PkAddGsData(&packet,
                                   (unsigned long long)((x + i + 0x800) << 4) |
                                       ((unsigned long long)((y + oy) << 4) << 16) |
                                       0x0080000000000000ULL);
            }
        }
    }
    CloseVif1DirectPacket((int)&packet);
    SendVif1DirectPacket((int *)&packet);
}
void resetPath(void) {
    sceDmaReset(1);
    sceDmaSync((int *)sceDmaGetChan(0), 0, 0x64);
    sceDmaSync((int *)sceDmaGetChan(1), 0, 0x64);
    sceDmaSync((int *)sceDmaGetChan(2), 0, 0x64);
    *(int *)sceDmaGetChan(0) |= 0x40;
    *(int *)sceDmaGetChan(1) |= 0x40;
    *(int *)sceDmaGetChan(2) |= 0x40;
    sceGsResetPath();
}
void resetGS(int a0)
{
    sceVpu0Reset(a0);
    gsb_Init(D_0028F4F0);
}
static inline void scrollDbgScreen(void) {
    int i, j;

    for (i = 1; i < 26; i++) {
        for (j = 0; j < 256; j++) {
            D_0070FA90[i - 1][j] = D_0070FA90[i][j];
        }
    }
    for (j = 0; j < 256; j++) {
        D_0070FA90[25][j] = D_0063B388;
    }
}
void putString(int color, char *fmt, ...) {
    char buf[256];
    char *str = buf;
    unsigned int i;

    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x30);
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '\t') {
            D_0063B394 += 2;
        } else if (str[i] == '\n') {
            D_0063B398++;
            D_0063B394 = 0;
        } else {
            D_0070FA90[D_0063B398][D_0063B394].col = color;
            D_0070FA90[D_0063B398][D_0063B394].ch = str[i];
            D_0063B394++;
        }
        if (D_0063B394 >= 256) {
            D_0063B394 = 255;
        }
        if (D_0063B398 >= 26) {
            scrollDbgScreen();
            D_0063B398 = 25;
        }
    }
}
void drawWin(void) {
    int i, j, k;
    int len = 50;
    int st;

    for (i = 0; i < 26; i++) {
        for (j = 255; D_0070FA90[i][j].ch == ' ' && j >= 0; j--) {
        }
        j++;
        if (len < j) len = j;

        if (j < 50) {
            st = 0;
        } else if (j - D_0063B390 - 50 >= 0) {
            st = D_0063B390;
        } else {
            st = j - 50;
        }
        for (k = 0; k < 50; k++) {
            DbgChar *p = &D_0070FA90[i][st + k];
            if (p->ch != ' ') {
                D_0063B37C = ((p->col >> 24) & 0xFF) * 0.8f;
                D_0063B380 = ((p->col >> 16) & 0xFF) * 0.8f;
                D_0063B384 = ((p->col >> 8) & 0xFF) * 0.8f;
                PutFont(p->ch, k * 10 - 250, (i - 13) * 16);
            }
        }
    }
    if (len - D_0063B390 - 50 < 0) {
        D_0063B390 = len - 50;
    }
}
void saveBack(void)
{
    SetDrawEnvironment(1);
    drawSprite(0x10, 0x20, 0x30, 0x40, -0x136, -0x6B, 0x136, 0x6B, 0);
    SetDrawEnvironment(1);
}
static inline void putBaseChar(int c) {
    unsigned int col = 0xFFFFFF00;
    D_0070FA90[D_0063B398][D_0063B394].col = col;
    D_0070FA90[D_0063B398][D_0063B394].ch = c;
}
static inline void dispBase(void) {
    int c;
    switch (D_0063B39C) {
    case 0:
    default: c = '-'; break;
    case 1: c = '/'; break;
    case 2: c = '|'; break;
    case 3: c = '\\'; break;
    }
    putBaseChar(c);
    D_0063B39C = (D_0063B39C + 1) & 3;
}
void baseFunc(void) {
    if (D_0028F8F0[0].btn & 0x8000) if (--D_0063B390 < 0) D_0063B390 = 0;
    if (D_0028F8F0[0].btn & 0x2000) if (++D_0063B390 >= 50) D_0063B390 = 49;
    SetDrawEnvironment(1);
    dispBase();
    drawWin();
}
void syncGS(void) {
    FlushCache(0);
    sceGsSyncPath__pn(1, 0);
    odd_even = sceGsSyncV(0);
    frame_count++;
    buffer_ID = frame_count & 1;
    gsb_Reduction();
    sceGsSwapDBuff(D_0028F4F0, buffer_ID);
    RestoreNormalDrawEnvironment(D_0028F4F0, buffer_ID, odd_even);
    SetDrawEnvironment(1);
}
