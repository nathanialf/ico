void func_001B59F0(void) {
    int n;
    int v;
    float a, c;
    int state;

    if (D_0062C1D8 != 0) {
        register float fee0 __asm__("$f1") = D_0062C1D0;
        register int v0 __asm__("$2");
        n = 0;
        v0 = (int)((float)D_004B8C80[0] - fee0);
        D_004B8C80[0] = v0;
        if (v0 < -0x1400) {
            D_004B8C80[0] = -0x1400;
            n = 1;
        }
        {
            register float fee4 __asm__("$f1") = D_0062C1D4;
            v0 = (int)((float)D_0062C1CC - fee4);
        }
        D_0062C1CC = v0;
        if (v0 < 0x280) {
            D_0062C1CC = 0x280;
            n++;
        }
        if (n == 2) D_0062C1D8 = 0;
    }

    {
        int b3 = D_0062B473;
        int b4 = D_0062B474;
        int r;
        if (b3 < b4) {
            b3 += 2;
            r = (b4 < b3) ? b4 : b3;
        } else {
            b3 -= 2;
            r = (b3 < b4) ? b4 : b3;
        }
        a = D_0062B460;
        c = D_0062B45C;
        *(volatile unsigned char *)&D_0062B473 = r;
    }

    if (c < a) {
        c += 0.5f;
        D_0062B45C = c;
        if (a < c) {
            D_0062B45C = a;
        }
    } else {
        c -= 0.5f;
        D_0062B45C = c;
        if (c < a) {
            D_0062B45C = a;
        }
    }

    state = D_0062C1DC;
    if ((unsigned)state >= 7) return;

    switch (state) {
    case 0:
        dl_PushPriority();
        D_0062B473 = 0;
        D_0062C1DC = D_0062C1DC + 1;
        /* fallthrough */
    case 1:
        D_0062B460 = 0;
        if (D_0062B473 != D_0062B474) return;
        if (D_0062B45C != D_0062B460) return;
        D_0062C1DC = D_0062C1DC + 1;
        return;
    case 2:
        staffRollWide();
        if (func_001B58B0() == 0) return;
        D_0062C1DC = D_0062C1DC + 1;
        return;
    case 3:
        if (staffRollWide() != 0) return;
        D_0062C1DC = D_0062C1DC + 1;
        return;
    case 4:
        D_0062B474 = 0;
        D_0062B460 = 0;
        if (D_0062B473 != 0) return;
        D_0062C1DC = state + 1;
        return;
    case 5:
        if (D_0062B45C != 0.0f) return;
        D_0062C1DC = state + 1;
        return;
    case 6:
        D_0062B458 = 0;
        return;
    }
}
