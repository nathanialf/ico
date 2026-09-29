/* the hand manager, included inside actGirlHand's body, on the listing's .inc lines */ /* clang-format off */
void HandMgr_GetDistHand(float *dist, float *height)
{
    union GAIF g[4], b[4];
    int n, m;
    n = GetSkeltonFocusNode(D_00639EA8, 0x12);

    g[0].f = *(float *)((n << 6) + *(int *)(*(int *)((char *)D_00639EA8 + 0x15C) + 0xC) + 0x30); g[1].f = *(float *)((n << 6) + *(int *)(*(int *)((char *)D_00639EA8 + 0x15C) + 0xC) + 0x34); g[2].f = *(float *)((n << 6) + *(int *)(*(int *)((char *)D_00639EA8 + 0x15C) + 0xC) + 0x38);
    m = GetSkeltonFocusNode(D_00639EA4, 2);

    b[0].f = *(float *)((m << 6) + *(int *)(*(int *)((char *)D_00639EA4 + 0x15C) + 0xC) + 0x30); b[1].f = *(float *)((m << 6) + *(int *)(*(int *)((char *)D_00639EA4 + 0x15C) + 0xC) + 0x34); b[2].f = *(float *)((m << 6) + *(int *)(*(int *)((char *)D_00639EA4 + 0x15C) + 0xC) + 0x38);


    *dist = _DistGV(g, b);
    *height = g[1].f - (b[1].f - 40.0f) < 0.0f ? -(g[1].f - (b[1].f - 40.0f))
                                               : g[1].f - (b[1].f - 40.0f);
}

__inline void HandMgr_Init(void) { GetRootPosition(D_002A2F70.prev, D_00639EA8); }

void HandMgr_Update(void)
{
    GetRootPosition(D_002A2F70.cur, D_00639EA8);
    D_002A2F70.f_20 = _DistGV(D_002A2F70.cur, D_002A2F70.prev);
    D_002A2F70.sub30[0] = ((float *)test_CURRENTORIENT(D_00639EA8))[0]; D_002A2F70.sub30[1] = ((float *)test_CURRENTORIENT(D_00639EA8))[1]; D_002A2F70.sub30[2] = ((float *)test_CURRENTORIENT(D_00639EA8))[2];
    _OrientXZGV(D_002A2F70.sub40, test_CURRENTROOT(D_00639EA4), D_002A2F70.cur);
    HandMgr_GetDistHand(&D_002A2F70.f_50, &D_002A2F70.f_54);

    D_002A2F70.f_58 = 0;
    D_002A2F70.f_59 = 0;
    D_002A2F70.f_5A = 0;
    D_002A2F70.f_5B = 0;
    D_002A2F70.f_5C = 0;
    D_002A2F70.f_5D = 0;
    D_002A2F70.f_5E = 0;


    D_002A2F70.prev[0] = D_002A2F70.cur[0]; D_002A2F70.prev[1] = D_002A2F70.cur[1]; D_002A2F70.prev[2] = D_002A2F70.cur[2];
}

void HandMgr_Judge(void)
{
    float one = 1.0f;
    if (D_002A2F70.f_20 < 2.0f) {
        D_002A2F70.f_58 = 1;
    }
    if ((_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30) < 0
             ? -_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)
             : _RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)) >= 0x3D) {
        D_002A2F70.f_59 = 1;
    }
    if (D_002A2F70.f_54 > 15.0f) {
        D_002A2F70.f_5E = 1;
    }
    if (one * 100.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5A = 1;
    }
    if (one * 125.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5B = 1;
    }
    if (one * 135.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5C = 1;
    }
    if (D_002A2F70.f_50 < 90.0f) {
        D_002A2F70.f_5D = 1;
    }
}

void HandMgr_Print(void)
{
    if (D_0063B13C & 1) {
        debug_Printf(10, 60, 0xFFFFFFF, "[%d] [%d]", (int)D_002A2F70.f_50,
                     (int)D_002A2F70.f_54);
        if (D_0063B13C & 1) {
            debug_Printf(10, 70, 0xFFFFFFF, "gv[%d] mo[%d] hd[%d] hd2[%d]\n", D_002A2F70.f_58,
                         D_002A2F70.f_59, D_002A2F70.f_5B, D_002A2F70.f_5D);
            if (D_0063B13C & 1) {
                debug_Printf(10, 80, 0xFFFFFFF, "\tgv[%d] mo[%d] hd[%d]\n", (int)D_002A2F70.f_20,
                             _RotyGV(D_002A2F70.sub40, D_002A2F70.sub30),
                             (int)D_002A2F70.f_50);
            }
        }
    }
}

void HandMgr_Speed(float f)
{
    float lim = 1.5f;
    int m;
    if (D_002A2F70.f_5E) {
        f = f + f;
        lim = 2.0f;
    }
    f = f < 1.0f ? 1.0f : (lim < f ? lim : f);
    f = f < 1.0f ? 1.0f : (_ACTGame_GetParamF(8) < f ? _ACTGame_GetParamF(8) : f);
    ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, f, 2);
    m = GOBJ_ACT(D_00639EA4)->unk34;
    if ((unsigned int)m < 4) {
        if (m != 0) {
            float one = 1.0f;
            float r;
            if (one < f) {
                f = one - (f - one);
            }
            r = f < _ACTGame_GetParamF(7) ? _ACTGame_GetParamF(7) : (one < f ? one : f);
            ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, r, 2);
        }
    }
    if (D_002A2F70.f_50 < 60.0f) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, 0.9f, 3);
    }
    if (90.0f < D_002A2F70.f_50) {
        float r;
        if (*(int *)((char *)GOBJ_ACT(D_00639EA4) + 0x154) != 0) {
            r = 2.0f;
        } else if (D_0028F4C0[0] == 1) {
            r = (D_002A2F70.f_50 - 90.0f) / 120.0f + 1.1f;
            r = r < 1.0f ? 1.0f : (r > 1.4 ? 1.4f : r);
        } else {
            r = 1.3f;
        }
        ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, r, 3);
    }
}
