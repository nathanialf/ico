/* motMan_rootUpdate.c.inc -- #included by motionManager.c into one motionManager.o (PAL listing SRCFILE.TXT). */
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", _wallHitReaction);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", _wallCollisionPreProcess);

inline int upperFieldCheck(char *a0, float f)
{
    char buf[0xC0] __attribute__((aligned(16)));
    CopyVector((void *)buf, a0);
    CopyVector((void *)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ClipFloor(buf);
    return *(int *)(buf + 0x94);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", getFieldCollision);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", setIKAndAdjustRootHeight);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", landingFieldAction);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", floorFitting);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateXZ);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateXZ_MotPos);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", adjustSideWall);

int checkSideWall(int a0, int a1, int p, int a3, int a4)
{
    char buf[0x10];
    int flag;
    int mag;
    int mask;

    *(int *)(p + 0x70) = 0;
    CopyVector((void *)p, (void *)a3);
    sceVu0ApplyMatrix((int *)(p + 0x10), a1, (char *)a0);
    ClipWall((void *)p);

    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    if (*(int *)(D_0063C490 + 0x324) != 0) {
        ClipWallFuchiHangWalkStop((void *)p);
        if (*(int *)(p + 0x88) != 0) {
            flag = 0;
            mag = GetWallAttribute((void *)p);
            switch (*(int *)(D_0063C490 + 0x324)) {
            default:
            case 1:
                mask = 0x20000000;
                break;
            case 2:
                mask = 0x10000000;
                break;
            }
            if (mag & mask) {
                flag = 1;
                if (mag & 0x0FFFFFFF) {
                    return -1;
                }
            }
            if (flag != 0) {
                return adjustSideWall(p, 0, a4);
            }
            goto block12;
        }
    }
block12:
    _ApplyMatrix(buf, a1, D_004ECA80);
    CopyVector((void *)p, (void *)(p + 0x10));
    _AddVectorXYZ(p + 0x10, p, buf);
    ClipWall((void *)p);
    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    CopyVector((void *)p, (void *)(p + 0x10));
    CopyVector((void *)(p + 0x10), (void *)(a3 + 0x10));
    ClipWall((void *)p);
    if (*(int *)(p + 0x88) != 0) {
    disp_one:
        return adjustSideWall(p, 1, a4);
    }
    return 0;
}

void forceFallDown(void)
{
    iosOmSendMail(D_0063B93C, 0x18, D_0063B93C);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
}

void forceReset(void)
{
    iosOmSendMail(D_0063B93C, 0x103, D_0063B93C);
    CopyVector((char *)D_0063C490 + 0x150, (char *)D_0063C490);
}

void checkWallUpperWall(void)
{
    int v;
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    {
        register float *p = (float *)D_0063C490;
        MatrixDrive_TransMatrix(p[0], p[1] - D_007201F4[0], p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    checkUpperWallState();
    MatrixDrive_PopMatrix();
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", calcWallFittingGeometry);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateHang);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateSwim);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", avoidSideAdjustWall);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateStepSolution);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateTrueMotion);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateDirectPlayForStream);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateDirectPlay);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", keepVerticalZWithQ);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateNodeFix);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateY);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateY_Rope);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateFly);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateEnemyFly);
