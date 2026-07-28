# Phase 3 transplant ledger

Per-function accounting for `tools/transplant_retail.py splice --apply`,
appended automatically as each TU is processed. Every function transplanted
from the old `retail` branch's matched bodies (src/cod/&lt;HEX&gt;.c shards +
the ~91 named whole-TU files) into a new retail-v2 TU is either:

- **KEPT** — spliced in, quick_diff-verified (functionally, tolerating the
  known jal/branch absolute-address-vs-symbol cosmetic artifact — see
  `_normalize_for_compare` in tools/transplant_retail.py), and confirmed by
  the batch-level full `ninja` SHA-1 gate.
- **REVERTED(reason)** — old body doesn't produce byte-identical output in
  the new tree (compile error or genuine instruction mismatch); left as
  INCLUDE_ASM. Common reasons seen so far: struct layout divergence between
  old `include/ico/types.h` (had `Obj800`) and the new evolved header (no
  `Obj800`; fields inlined/renamed), and genuine scheduling/regalloc diffs.
- **QUARANTINED(reason)** — never attempted per the phase-3 scope rules:
  the 2 genuine VU0-inline-asm leaves (VMA 0x118A68, 0x1986A8), and bodies
  from old `src/DisplayList.c` (extra_cflags family).

Batches are gated by a full `tools/build.sh setup && ninja` verify_elf
round-trip before commit; a batch that fails is bisected with
`tools/first_diff.py`, the offending function's splice reverted, and the
gate re-run before commit.

## src/box (pre-batch validation run)
- KEPT `func_001C05A8` (old `func_001C05A8`) @ 0x001C05A8
- KEPT `func_001C05B8` (old `func_001C05B8`) @ 0x001C05B8
- KEPT `ExecBoxMoveStartReaction` (old `func_001C0648`) @ 0x001C0648
- REVERTED `initFloating` (old `func_001BE558`) @ 0x001BE558 — genuine scheduling mismatch (delay-slot-occupant, see COOKBOOK.md)
- REVERTED `ExecBoxMoveEndReaction` (old `func_001C0690`) @ 0x001C0690 — old body typed via `Obj800` (removed from new ico/types.h)
- REVERTED `BoxExtGeoRestore` (old `func_001C0708`) @ 0x001C0708 — old body typed via `Obj800` (removed from new ico/types.h)

## src/delayFreeManager
- KEPT `func_001024B8` (old `func_001024B8`) @ 0x001024B8
- KEPT `func_00102558` (old `func_00102558`) @ 0x00102558
- KEPT `func_001025E8` (old `func_001025E8`) @ 0x001025E8
- KEPT `func_00102790` (old `func_00102790`) @ 0x00102790
- KEPT `func_00102850` (old `func_00102850`) @ 0x00102850
- KEPT `func_00102858` (old `func_00102858`) @ 0x00102858
- KEPT `func_00102860` (old `func_00102860`) @ 0x00102860

## src/geometryManager
- KEPT `UpdateRootMatrixByDObj` (old `func_00102970`) @ 0x00102970
- KEPT `GetRootQuaternion` (old `func_00102978`) @ 0x00102978
- KEPT `SetRootBaseQuaternion` (old `func_001029C0`) @ 0x001029C0
- KEPT `GetRootMatrixRotOffset` (old `func_00102FA0`) @ 0x00102FA0
- KEPT `SetRootMatrixRotOffset` (old `func_00103110`) @ 0x00103110
- KEPT `GetRootVelocity` (old `func_00103AD0`) @ 0x00103AD0
- KEPT `cylinderCollisionCheck` (old `func_001040C0`) @ 0x001040C0
- KEPT `LocalizeDirectionOrient` (old `func_00104140`) @ 0x00104140
- KEPT `GetCylinderCollision` (old `func_001041C0`) @ 0x001041C0
- KEPT `GetRootMatrixByDObj` (old `func_00104508`) @ 0x00104508
- REVERTED `UpdateRootMatrix` (old `func_001029B8`) @ 0x001029B8 — insn 0: expected `j	0 <UpdateRootMatrix>` built `j	88 <GetRootQuaternion>`
- REVERTED `func_00102A38` (old `func_00102A38`) @ 0x00102A38 — src/geometryManager.c:41: too few arguments to function `SetRootBaseQuaternion'
- REVERTED `SetRootMatrixWithTransOffset` (old `func_00102DE0`) @ 0x00102DE0 — insn 3: expected `jal	0 <SetRootMatrixWithTransOffset>` built `jal	150 <func_00102A40>`

## src/keyInput
- KEPT `func_00104698` (old `func_00104698`) @ 0x00104698
- KEPT `func_001046F0` (old `func_001046F0`) @ 0x001046F0
- KEPT `func_00104A38` (old `func_00104A38`) @ 0x00104A38
- REVERTED `InitKeyInput` (old `func_00104590`) @ 0x00104590 — insn 41: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `func_001048C8` (old `func_001048C8`) @ 0x001048C8 — src/keyInput.c:26: warning: initialization from incompatible pointer type
- REVERTED `func_00104940` (old `func_00104940`) @ 0x00104940 — src/keyInput.c:26: warning: initialization from incompatible pointer type
- REVERTED `func_001049C0` (old `func_001049C0`) @ 0x001049C0 — src/keyInput.c:26: warning: initialization from incompatible pointer type
- REVERTED `func_00104EF0` (old `func_00104EF0`) @ 0x00104EF0 — src/keyInput.c:31: warning: initialization from incompatible pointer type
- REVERTED `func_00104F20` (old `func_00104F20`) @ 0x00104F20 — src/keyInput.c:29: warning: initialization from incompatible pointer type
- REVERTED `func_001050B0` (old `func_001050B0`) @ 0x001050B0 — src/keyInput.c:29: warning: initialization from incompatible pointer type
- REVERTED `func_00105258` (old `func_00105258`) @ 0x00105258 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_00105268` (old `func_00105268`) @ 0x00105268 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_00105278` (old `func_00105278`) @ 0x00105278 — src/keyInput.c:28: warning: initialization from incompatible pointer type
- REVERTED `func_00105290` (old `func_00105290`) @ 0x00105290 — src/keyInput.c:28: warning: initialization from incompatible pointer type
- REVERTED `func_001052A8` (old `func_001052A8`) @ 0x001052A8 — src/keyInput.c:29: warning: initialization from incompatible pointer type

## src/matrixDrive
- REVERTED `MatrixDrive_TurnObjectMatrix` (old `func_00105F00`) @ 0x00105F00 — insn 0: expected `lq	a2,0(a1)` built `lui	a0,0x0`
- REVERTED `MatrixDrive_TurnXObjectMatrixZY` (old `func_00105F10`) @ 0x00105F10 — insn 0: expected `lq	a2,0(a1)` built `lui	a0,0x0`
- REVERTED `MatrixDrive_TurnXObjectMatrixYZ` (old `func_00105F20`) @ 0x00105F20 — insn 0: expected `lq	a2,0(a1)` built `lui	a0,0x0`
- REVERTED `MatrixDrive_TurnYObjectMatrixXZ` (old `func_00105F48`) @ 0x00105F48 — insn 0: expected `lui	a3,0x2000` built `addiu	sp,sp,-16`
- REVERTED `MatrixDrive_TurnZObjectMatrixXY` (old `func_00105F78`) @ 0x00105F78 — src/matrixDrive.c:39: `lqc2' undeclared (first use in this function)
- REVERTED `MatrixDrive_GetTurnXAngleZY` (old `func_00105F90`) @ 0x00105F90 — src/matrixDrive.c:41: `lqc2' undeclared (first use in this function)
- REVERTED `MatrixDrive_GetTurnYAngleXZ` (old `func_00105FE0`) @ 0x00105FE0 — src/matrixDrive.c:46: `t0' undeclared (first use in this function)
- REVERTED `MatrixDrive_GetTurnYEAngleXZ` (old `func_00106000`) @ 0x00106000 — src/matrixDrive.c:47: `lqc2' undeclared (first use in this function)
- REVERTED `MatrixDrive_GetTurnZAngleXY` (old `func_00106028`) @ 0x00106028 — src/matrixDrive.c:49: `lqc2' undeclared (first use in this function)
- REVERTED `MatrixDrive_GetTurnZAngleYX` (old `func_00106048`) @ 0x00106048 — src/matrixDrive.c:56: `lqc2' undeclared (first use in this function)

## src/motionManager2
- KEPT `GetWaterReaction` (old `func_00106A98`) @ 0x00106A98
- KEPT `CheckFieldContact` (old `func_00106AA8`) @ 0x00106AA8
- KEPT `GetOrientOfWallOfGObj` (old `func_00106B70`) @ 0x00106B70
- KEPT `SetMotionDirection` (old `func_00106D20`) @ 0x00106D20
- KEPT `SetMotionDirectionWithLimit` (old `func_00106DA8`) @ 0x00106DA8
- KEPT `GetRootPosOfNextFrame` (old `func_00106DF0`) @ 0x00106DF0
- KEPT `DispSkelton` (old `func_00107DD8`) @ 0x00107DD8
- KEPT `GetFloatingMotion` (old `func_00109B98`) @ 0x00109B98
- KEPT `MakeMirrorMotion` (old `func_00109BA8`) @ 0x00109BA8
- KEPT `DebugDisp1CollisionWithColor` (old `func_00109F10`) @ 0x00109F10
- KEPT `ClearMotionBlendlessNode` (old `func_00109FF8`) @ 0x00109FF8
- KEPT `InitMotionStateInfo` (old `func_0010A008`) @ 0x0010A008
- KEPT `GetSkeltonFocusNode` (old `func_0010A018`) @ 0x0010A018
- KEPT `AdjustMotionHeightToNearestField` (old `func_0010A028`) @ 0x0010A028
- KEPT `SetRootUpdateMode` (old `func_0010A038`) @ 0x0010A038
- KEPT `ForMotionViewer_GetCurrentAnimationFrame` (old `func_0010A048`) @ 0x0010A048
- KEPT `ForMotionViewer_GetCurrentMotion` (old `func_0010A068`) @ 0x0010A068
- KEPT `EnableMotionOrientUpdate` (old `func_0010A088`) @ 0x0010A088
- KEPT `DisableMotionOrientUpdate` (old `func_0010A0A8`) @ 0x0010A0A8
- KEPT `GetDifferenceFromLastField` (old `func_0010A2E0`) @ 0x0010A2E0
- KEPT `GetDifferenceFromLowerField` (old `func_0010A2F0`) @ 0x0010A2F0
- KEPT `GetDifferenceFromWallLowerPlane` (old `func_0010A300`) @ 0x0010A300
- KEPT `GetDifferenceFromWallUpperPlane` (old `func_0010A310`) @ 0x0010A310
- KEPT `DisableChangeRootUpdateMode` (old `func_0010A320`) @ 0x0010A320
- KEPT `EnableChangeRootUpdateMode` (old `func_0010A330`) @ 0x0010A330
- KEPT `GetRopeHangablePos` (old `func_0010A380`) @ 0x0010A380
- KEPT `GetMotionFrameFlag1` (old `func_0010A390`) @ 0x0010A390
- KEPT `GetMotionFrameFlag2` (old `func_0010A3A0`) @ 0x0010A3A0
- KEPT `GetHeightOfWallFromGObj` (old `func_0010A498`) @ 0x0010A498
- KEPT `GetHeightOfCliffFromGObj` (old `func_0010A4E0`) @ 0x0010A4E0
- KEPT `InitMotionRotElem` (old `func_0010A4F0`) @ 0x0010A4F0
- KEPT `SetMotionNodeFixModeParameter` (old `func_0010A550`) @ 0x0010A550
- KEPT `GetMotionRootPos` (old `func_0010AAA0`) @ 0x0010AAA0
- REVERTED `DebugDisp1Collision` (old `func_00109E88`) @ 0x00109E88 — src/motionManager2.c:11: parse error before `D_00275DB0'
- REVERTED `CheckWallAttribute` (old `func_0010A120`) @ 0x0010A120 — insn 12: expected `ld	ra,0(sp)` built `trunc.w.s	$f1,$f0`
- REVERTED `CheckPureWallAttribute` (old `func_0010A160`) @ 0x0010A160 — insn 12: expected `ld	ra,0(sp)` built `trunc.w.s	$f1,$f0`
- REVERTED `GetRootProjectionPosOfGObj` (old `func_0010A558`) @ 0x0010A558 — src/motionManager2.c:143: warning: initialization from incompatible pointer type

## src/pool
- KEPT `falldownSE` (old `func_0010AB18`) @ 0x0010AB18
- KEPT `copyToWork` (old `func_0010AB20`) @ 0x0010AB20
- KEPT `SetFallDownSplash` (old `func_0010AC88`) @ 0x0010AC88
- KEPT `GetPoolGlobalDrainVector` (old `func_0010ACC8`) @ 0x0010ACC8
- KEPT `updatePoolGeo` (old `func_0010ADC8`) @ 0x0010ADC8
- KEPT `SetLimitedPoolReflactionMesh` (old `func_0010B2C0`) @ 0x0010B2C0
- KEPT `func_0010D070` (old `func_0010D070`) @ 0x0010D070
- KEPT `func_0010D078` (old `func_0010D078`) @ 0x0010D078
- KEPT `func_0010D180` (old `func_0010D180`) @ 0x0010D180
- REVERTED `func_0010D338` (old `func_0010D338`) @ 0x0010D338 — src/pool.c:72: warning: initialization from incompatible pointer type

## src/quaternion
- KEPT `InvertCurrentQuaternion` (old `func_0010D3E0`) @ 0x0010D3E0
- KEPT `SetCurrentQuaternion` (old `func_0010D408`) @ 0x0010D408
- KEPT `RotCurrentQuaternionX` (old `func_0010D428`) @ 0x0010D428
- KEPT `RotCurrentQuaternionY` (old `func_0010D448`) @ 0x0010D448
- KEPT `RotCurrentQuaternionZ` (old `func_0010D468`) @ 0x0010D468
- KEPT `PushQuaternion` (old `func_0010D488`) @ 0x0010D488
- KEPT `SetIdentityQuaternion` (old `func_0010D520`) @ 0x0010D520
- KEPT `GetMatrixFromQuaternion` (old `func_0010D530`) @ 0x0010D530
- KEPT `GetInverseQuaternion` (old `func_0010D830`) @ 0x0010D830
- KEPT `GetCurrentQuaternion` (old `func_0010DA78`) @ 0x0010DA78
- KEPT `GetLastQuaternion` (old `func_0010DAA0`) @ 0x0010DAA0
- REVERTED `MultiCurrentQuaternion` (old `func_0010D360`) @ 0x0010D360 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `RegularizeQuaternion` (old `func_0010D838`) @ 0x0010D838 — src/quaternion.c:79: too few arguments to function `GetInverseQuaternion'

## src/tableSin
- KEPT `GetTableSin` (old `func_0010DAB8`) @ 0x0010DAB8
- KEPT `GetTableCos` (old `func_0010DAD0`) @ 0x0010DAD0
- KEPT `InitTableSin` (old `func_0010DB28`) @ 0x0010DB28
- KEPT `func_0010DDF8` (old `func_0010DDF8`) @ 0x0010DDF8
- KEPT `func_0010DF70` (old `func_0010DF70`) @ 0x0010DF70
- REVERTED `GetTableArcCos` (old `func_0010DBD0`) @ 0x0010DBD0 — src/tableSin.c:63: void value not ignored as it ought to be
- REVERTED `func_0010DCF8` (old `func_0010DCF8`) @ 0x0010DCF8 — src/tableSin.c:65: void value not ignored as it ought to be
- REVERTED `func_0010DD58` (old `func_0010DD58`) @ 0x0010DD58 — src/tableSin.c:61: void value not ignored as it ought to be
- REVERTED `func_0010DDB8` (old `func_0010DDB8`) @ 0x0010DDB8 — src/tableSin.c:56: `lqc2' undeclared (first use in this function)

## src/DisplayP2O
- KEPT `func_0010EC50` (old `func_0010EC50`) @ 0x0010EC50
- KEPT `func_0010EC60` (old `func_0010EC60`) @ 0x0010EC60
- KEPT `func_0010EC68` (old `func_0010EC68`) @ 0x0010EC68
- REVERTED `p2o_DispVU1Multi` (old `func_0010E708`) @ 0x0010E708 — src/DisplayP2O.c:18: `lqc2' undeclared (first use in this function)
- REVERTED `p2o_TransMicroProgram` (old `func_0010E928`) @ 0x0010E928 — src/DisplayP2O.c:23: `lqc2' undeclared (first use in this function)
- REVERTED `func_0010EC08` (old `func_0010EC08`) @ 0x0010EC08 — insn 4: expected `bc1f	30 <func_0010EC08+0x30>` built `bc1f	8a8 <func_0010EC08+0x38>`

## src/FileManager
- KEPT `file_Init` (old `func_0010EC98`) @ 0x0010EC98
- KEPT `file_LoadCDFile` (old `func_0010ECA0`) @ 0x0010ECA0
- KEPT `func_0010ECC8` (old `func_0010ECC8`) @ 0x0010ECC8
- KEPT `func_0010ECD8` (old `func_0010ECD8`) @ 0x0010ECD8
- REVERTED `file_LoadFile` (old `func_0010ECA8`) @ 0x0010ECA8 — src/FileManager.c:19: too few arguments to function `file_LoadCDFile'
- REVERTED `func_0010ECB0` (old `func_0010ECB0`) @ 0x0010ECB0 — insn 0: expected `j	0 <func_0010ECB0>` built `j	10 <file_LoadFile>`
- REVERTED `func_0010ECB8` (old `func_0010ECB8`) @ 0x0010ECB8 — src/FileManager.c:23: too few arguments to function `file_Init'
- REVERTED `func_0010ECC0` (old `func_0010ECC0`) @ 0x0010ECC0 — insn 0: expected `j	0 <func_0010ECC0>` built `j	20 <func_0010ECB8>`
- REVERTED `func_0010F710` (old `func_0010F710`) @ 0x0010F710 — src/FileManager.c:59: `DmaTag' undeclared (first use in this function)

## src/matrixDrive
- KEPT `MatrixDrive_TurnObjectMatrix` (old `func_00105F00`) @ 0x00105F00
- KEPT `MatrixDrive_TurnXObjectMatrixZY` (old `func_00105F10`) @ 0x00105F10
- KEPT `MatrixDrive_TurnXObjectMatrixYZ` (old `func_00105F20`) @ 0x00105F20
- KEPT `MatrixDrive_TurnYObjectMatrixXZ` (old `func_00105F48`) @ 0x00105F48
- KEPT `MatrixDrive_TurnZObjectMatrixXY` (old `func_00105F78`) @ 0x00105F78
- KEPT `MatrixDrive_GetTurnXAngleZY` (old `func_00105F90`) @ 0x00105F90
- KEPT `MatrixDrive_GetTurnYAngleXZ` (old `func_00105FE0`) @ 0x00105FE0
- KEPT `MatrixDrive_GetTurnYEAngleXZ` (old `func_00106000`) @ 0x00106000
- KEPT `MatrixDrive_GetTurnZAngleXY` (old `func_00106028`) @ 0x00106028
- KEPT `MatrixDrive_GetTurnZAngleYX` (old `func_00106048`) @ 0x00106048

## src/keyInput
- KEPT `func_00104698` (old `func_00104698`) @ 0x00104698
- KEPT `func_001046F0` (old `func_001046F0`) @ 0x001046F0
- KEPT `func_00104A38` (old `func_00104A38`) @ 0x00104A38
- REVERTED `InitKeyInput` (old `func_00104590`) @ 0x00104590 — insn 41: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `func_001048C8` (old `func_001048C8`) @ 0x001048C8 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_00104940` (old `func_00104940`) @ 0x00104940 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_001049C0` (old `func_001049C0`) @ 0x001049C0 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_00104EF0` (old `func_00104EF0`) @ 0x00104EF0 — src/keyInput.c:31: warning: initialization from incompatible pointer type
- REVERTED `func_00104F20` (old `func_00104F20`) @ 0x00104F20 — src/keyInput.c:29: warning: initialization from incompatible pointer type
- REVERTED `func_001050B0` (old `func_001050B0`) @ 0x001050B0 — src/keyInput.c:29: warning: initialization from incompatible pointer type
- REVERTED `func_00105258` (old `func_00105258`) @ 0x00105258 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_00105268` (old `func_00105268`) @ 0x00105268 — src/keyInput.c:27: warning: initialization from incompatible pointer type
- REVERTED `func_00105278` (old `func_00105278`) @ 0x00105278 — src/keyInput.c:28: warning: initialization from incompatible pointer type
- REVERTED `func_00105290` (old `func_00105290`) @ 0x00105290 — src/keyInput.c:28: warning: initialization from incompatible pointer type
- REVERTED `func_001052A8` (old `func_001052A8`) @ 0x001052A8 — src/keyInput.c:29: warning: initialization from incompatible pointer type

## src/GifPacket
- KEPT `gif_SpriteSensitive` (old `func_001118B0`) @ 0x001118B0
- KEPT `gif_SpriteOffset` (old `func_001118B8`) @ 0x001118B8
- KEPT `gif_SpriteSensitiveOffset` (old `func_001118E8`) @ 0x001118E8
- KEPT `gif_SpriteSensitiveOrg` (old `func_00111940`) @ 0x00111940

## src/GsBase

## src/Light
- KEPT `light_MakeLightMatrix` (old `func_00114DD8`) @ 0x00114DD8
- KEPT `light_DispVolume` (old `func_00114E08`) @ 0x00114E08
- KEPT `light_InitLight` (old `func_00114FB8`) @ 0x00114FB8
- KEPT `func_00117750` (old `func_00117750`) @ 0x00117750
- KEPT `func_00117760` (old `func_00117760`) @ 0x00117760
- KEPT `func_00117C20` (old `func_00117C20`) @ 0x00117C20
- KEPT `func_00117C40` (old `func_00117C40`) @ 0x00117C40
- KEPT `func_00117C60` (old `func_00117C60`) @ 0x00117C60
- KEPT `func_00117C80` (old `func_00117C80`) @ 0x00117C80
- KEPT `func_00117C98` (old `func_00117C98`) @ 0x00117C98
- KEPT `func_00117CB0` (old `func_00117CB0`) @ 0x00117CB0
- KEPT `func_00117CD0` (old `func_00117CD0`) @ 0x00117CD0
- KEPT `func_00117CE0` (old `func_00117CE0`) @ 0x00117CE0
- REVERTED `light_GetColorAnalog` (old `func_00114E18`) @ 0x00114E18 — src/Light.c:40: void value not ignored as it ought to be
- REVERTED `light_KillAllFixLight` (old `func_00114FC8`) @ 0x00114FC8 — src/Light.c:57: `Light' undeclared (first use in this function)
- REVERTED `light_KillAllAmbient` (old `func_00115068`) @ 0x00115068 — src/Light.c:59: `AmbientVolume' undeclared (first use in this function)
- REVERTED `func_00117768` (old `func_00117768`) @ 0x00117768 — src/Light.c:77: `Light' undeclared (first use in this function)
- REVERTED `func_001177C8` (old `func_001177C8`) @ 0x001177C8 — src/Light.c:77: `AmbientVolume' undeclared (first use in this function)
- REVERTED `func_00117820` (old `func_00117820`) @ 0x00117820 — src/Light.c:83: `AmbientVolume' undeclared (first use in this function)

## src/Matrix
- KEPT `_UnitCurrentMatrix` (old `func_00117FC0`) @ 0x00117FC0
- KEPT `_PushCurrentMatrix` (old `func_00117FD8`) @ 0x00117FD8
- KEPT `_PopCurrentMatrix` (old `func_00117FE8`) @ 0x00117FE8
- KEPT `_SetTransCurrentMatrix` (old `func_00118068`) @ 0x00118068
- KEPT `_ClearTransCurrentMatrix` (old `func_001180C0`) @ 0x001180C0
- KEPT `_RotCurrentMatrixX` (old `func_001180E0`) @ 0x001180E0
- KEPT `_RotCurrentMatrixY` (old `func_00118110`) @ 0x00118110
- KEPT `_RotCurrentMatrixZ` (old `func_00118160`) @ 0x00118160
- KEPT `_ScaleCurrentMatrix` (old `func_00118190`) @ 0x00118190
- KEPT `_SetCurrentMatrix` (old `func_001182F0`) @ 0x001182F0
- KEPT `_MulCurrentMatrixR` (old `func_00118320`) @ 0x00118320
- KEPT `_MulCurrentMatrixL` (old `func_00118350`) @ 0x00118350
- KEPT `_ApplyCurrentMatrix` (old `func_00118370`) @ 0x00118370
- KEPT `_RotTransPersCurrentMatrix` (old `func_00118388`) @ 0x00118388
- KEPT `_TransposeCurrentMatrix` (old `func_001183A0`) @ 0x001183A0
- KEPT `_TransposeRotationCurrentMatrix` (old `func_001183B8`) @ 0x001183B8
- KEPT `_InverseCurrentMatrix` (old `func_001183D0`) @ 0x001183D0
- KEPT `_PushVu0Registers` (old `func_001183F0`) @ 0x001183F0
- KEPT `_PopVu0Registers` (old `func_00118410`) @ 0x00118410

## src/MicroCode
- KEPT `mc_setBaseOffset` (old `func_00118430`) @ 0x00118430
- KEPT `mc_SetMicroCode` (old `func_00118448`) @ 0x00118448
- KEPT `mc_TransMicroCode` (old `func_00118460`) @ 0x00118460
- KEPT `mc_Reset` (old `func_00118470`) @ 0x00118470
- KEPT `mc_Init` (old `func_00118480`) @ 0x00118480
- KEPT `func_00118490` (old `func_00118490`) @ 0x00118490
- KEPT `func_001184B8` (old `func_001184B8`) @ 0x001184B8
- KEPT `func_001184E0` (old `func_001184E0`) @ 0x001184E0
- KEPT `func_00118510` (old `func_00118510`) @ 0x00118510
- KEPT `func_00118548` (old `func_00118548`) @ 0x00118548
- KEPT `func_00118578` (old `func_00118578`) @ 0x00118578
- KEPT `func_001185A8` (old `func_001185A8`) @ 0x001185A8
- KEPT `func_001185D0` (old `func_001185D0`) @ 0x001185D0
- KEPT `func_00118648` (old `func_00118648`) @ 0x00118648
- KEPT `func_00118678` (old `func_00118678`) @ 0x00118678
- KEPT `func_001186A0` (old `func_001186A0`) @ 0x001186A0
- KEPT `func_00118A48` (old `func_00118A48`) @ 0x00118A48

## src/Packet
- KEPT `pac_DumpPac` (old `func_00118A80`) @ 0x00118A80
- KEPT `pac_makeBoundingBox` (old `func_00118AA0`) @ 0x00118AA0
- KEPT `pac_error` (old `func_00118AB8`) @ 0x00118AB8
- KEPT `pac_openDmaTag` (old `func_00118F58`) @ 0x00118F58
- KEPT `pac_setVifCode` (old `func_00118F98`) @ 0x00118F98
- KEPT `pac_makeMaterialTableLine` (old `func_0011A2F0`) @ 0x0011A2F0
- KEPT `func_0011BF40` (old `func_0011BF40`) @ 0x0011BF40
- KEPT `func_0011BF60` (old `func_0011BF60`) @ 0x0011BF60
- REVERTED `pac_setVifEndCode` (old `func_00118FD8`) @ 0x00118FD8 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `pac_continueTag` (old `func_00119470`) @ 0x00119470 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `pac_setMaterialPacket` (old `func_0011A238`) @ 0x0011A238 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `pac_makeMaterialTable` (old `func_0011A2A8`) @ 0x0011A2A8 — insn 1: expected `daddu	t0,a0,zero` built `lui	v0,0x6c00`
- QUARANTINED `pac_DispQW` (old `func_00118A68`) @ 0x00118A68 — vu0-inline-asm

## src/Primitive
- KEPT `prim_InitFan2D` (old `func_0011BFB8`) @ 0x0011BFB8
- KEPT `prim_DispWireYCylinder` (old `func_0011DEE0`) @ 0x0011DEE0

## src/RegistPacket
- KEPT `reg_chooseReflectionMicroCode` (old `func_0011EDF8`) @ 0x0011EDF8
- KEPT `func_0011EE30` (old `func_0011EE30`) @ 0x0011EE30
- KEPT `func_0011EE58` (old `func_0011EE58`) @ 0x0011EE58
- KEPT `reg_setNMatrixPacket` (old `func_0011EE70`) @ 0x0011EE70
- KEPT `reg_dispCObj` (old `func_0011FCD8`) @ 0x0011FCD8
- KEPT `reg_dispLine` (old `func_0011FF30`) @ 0x0011FF30
- REVERTED `func_0011E708` (old `func_0011E708`) @ 0x0011E708 — src/RegistPacket.c:14: void value not ignored as it ought to be

## src/Shadow
- KEPT `func_00122C40` (old `func_00122C40`) @ 0x00122C40
- KEPT `func_00122C48` (old `func_00122C48`) @ 0x00122C48
- KEPT `shadow_DispCancel` (old `func_00122C80`) @ 0x00122C80
- KEPT `shadow_SetLength` (old `func_00122C88`) @ 0x00122C88
- KEPT `func_00123C20` (old `func_00123C20`) @ 0x00123C20
- REVERTED `shadow_KillShadow` (old `func_00122C50`) @ 0x00122C50 — src/Shadow.c:42: void value not ignored as it ought to be

## src/StageAnimation
- KEPT `stage_CalcAnimationNoParent` (old `func_00128708`) @ 0x00128708
- KEPT `stage_DispAnimation` (old `func_001287B8`) @ 0x001287B8
- KEPT `stage_SetCameraForceOff` (old `func_00129A78`) @ 0x00129A78
- KEPT `stage_KillPlayBgAnimationIfOverMaxCount` (old `func_0012A7A0`) @ 0x0012A7A0
- KEPT `func_0012AA78` (old `func_0012AA78`) @ 0x0012AA78
- KEPT `func_0012ABE0` (old `func_0012ABE0`) @ 0x0012ABE0
- KEPT `func_0012AC28` (old `func_0012AC28`) @ 0x0012AC28
- REVERTED `func_0012AA80` (old `func_0012AA80`) @ 0x0012AA80 — src/StageAnimation.c:140: warning: passing arg 3 of `func_00263FF0' makes integer from pointer without a cast

## src/Texture
- KEPT `tex_AllocVramAuto` (old `func_0012AD40`) @ 0x0012AD40
- KEPT `tex_setRegisters` (old `func_0012BBE8`) @ 0x0012BBE8
- REVERTED `tex_loadImage` (old `func_0012ADE8`) @ 0x0012ADE8 — src/Texture.c:36: `AnimNode' undeclared (first use in this function)

## src/ZFog
- KEPT `fog_FogTool` (old `func_0012FCE0`) @ 0x0012FCE0
- KEPT `func_0012FE08` (old `func_0012FE08`) @ 0x0012FE08
- KEPT `func_0012FE20` (old `func_0012FE20`) @ 0x0012FE20
- KEPT `func_0012FE38` (old `func_0012FE38`) @ 0x0012FE38
- KEPT `func_0012FE60` (old `func_0012FE60`) @ 0x0012FE60
- KEPT `func_0012FE78` (old `func_0012FE78`) @ 0x0012FE78
- KEPT `func_0012FFE8` (old `func_0012FFE8`) @ 0x0012FFE8
- REVERTED `func_0012FD30` (old `func_0012FD30`) @ 0x0012FD30 — src/ZFog.c:26: void value not ignored as it ought to be

## ios/cdvd
- REVERTED `iosCdvdMgrPackLoad` (old `func_001312F0`) @ 0x001312F0 — ios/cdvd.c:21: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00131480` (old `func_00131480`) @ 0x00131480 — ios/cdvd.c:21: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00131560` (old `func_00131560`) @ 0x00131560 — ios/cdvd.c:15: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00131780` (old `func_00131780`) @ 0x00131780 — ios/cdvd.c:17: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdDiskReady` (old `func_00132038`) @ 0x00132038 — ios/cdvd.c:15: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdLoad` (old `func_001320E8`) @ 0x001320E8 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdPackLoad` (old `func_001321C8`) @ 0x001321C8 — ios/cdvd.c:16: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgr` (old `func_001325D8`) @ 0x001325D8 — ios/cdvd.c:13: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdDirectStOpen` (old `func_00132610`) @ 0x00132610 — ios/cdvd.c:13: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_001331D8` (old `func_001331D8`) @ 0x001331D8 — ios/cdvd.c:14: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdLoadPackFile` (old `func_00133218`) @ 0x00133218 — ios/cdvd.c:121: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskStatusGet` (old `func_001332B8`) @ 0x001332B8 — ios/cdvd.c:19: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgrDelete` (old `func_00133398`) @ 0x00133398 — ios/cdvd.c:13: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgrDeleteRequestGet` (old `func_00133448`) @ 0x00133448 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgrEntryNum` (old `func_00133450`) @ 0x00133450 — ios/cdvd.c:10: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundRead` (old `func_00133480`) @ 0x00133480 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundReadIOPm` (old `func_001334C8`) @ 0x001334C8 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00133500` (old `func_00133500`) @ 0x00133500 — ios/cdvd.c:10: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00133508` (old `func_00133508`) @ 0x00133508 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)

## ios/inflate
- KEPT `inflate` (old `func_001335D0`) @ 0x001335D0
- KEPT `func_00135468` (old `func_00135468`) @ 0x00135468
- REVERTED `func_00135A48` (old `func_00135A48`) @ 0x00135A48 — ios/inflate.c:59: warning: passing arg 1 of `new_segment' from incompatible pointer type

## ios/ios
- KEPT `ios_init_plus` (old `func_00135BB8`) @ 0x00135BB8

## ios/mblock
- KEPT `init_mblock` (old `func_00136060`) @ 0x00136060
- REVERTED `new_segment` (old `func_00136088`) @ 0x00136088 — insn 1: expected `jr	ra` built `sw	zero,0(a0)`
- REVERTED `strdup_mblock` (old `func_00136140`) @ 0x00136140 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

## ios/mcard
- KEPT `iosMcManager` (old `func_00137EE8`) @ 0x00137EE8
- KEPT `iosMcMgrSync` (old `func_00137EF0`) @ 0x00137EF0
- REVERTED `iosMcMgrLoadSeg` (old `func_00137538`) @ 0x00137538 — insn 2: expected `j	0 <iosMcMgrLoadSeg>` built `j	6d8 <iosMcMgrChdirProduct>`
- REVERTED `iosMcMgrSaveProductBlock` (old `func_00137548`) @ 0x00137548 — insn 2: expected `j	0 <iosMcMgrSaveProductBlock>` built `j	b08 <iosMcMgrSaveSeg>`

## ios/mcdata
- KEPT `func_00138390` (old `func_00138390`) @ 0x00138390
- KEPT `func_001383D8` (old `func_001383D8`) @ 0x001383D8
- REVERTED `func_001383F8` (old `func_001383F8`) @ 0x001383F8 — ios/mcdata.c:49: `Elem_001383F8' undeclared (first use in this function)

## ios/memory
- REVERTED `iosMallocDebug` (old `func_00138BF0`) @ 0x00138BF0 — ios/memory.c:25: void value not ignored as it ought to be
- REVERTED `iosMallocCheckLeak` (old `func_001394F0`) @ 0x001394F0 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_0013A200` (old `func_0013A200`) @ 0x0013A200 — insn 2: expected `jal	0 <func_0013A200>` built `jal	818 <func_00138E30>`

## ios/message
- KEPT `iosMsgInit` (old `func_0013A580`) @ 0x0013A580
- REVERTED `iosMsgQueueCreate` (old `func_0013A220`) @ 0x0013A220 — insn 11: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosMsgQueueDestroy` (old `func_0013A250`) @ 0x0013A250 — ios/message.c:29: warning: passing arg 3 of `func_00263FF0' makes integer from pointer without a cast
- REVERTED `send_signal_message` (old `func_0013A2F8`) @ 0x0013A2F8 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_0013A498` (old `func_0013A498`) @ 0x0013A498 — ios/message.c:33: `iosMsgSetEvent' undeclared (first use in this function)
- REVERTED `iosMsgSend` (old `func_0013A5B8`) @ 0x0013A5B8 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgQueueDestroyAll` (old `func_0013A7C8`) @ 0x0013A7C8 — insn 12: expected `jal	0 <iosMsgQueueDestroyAll>` built `jal	d8 <send_signal_message>`

## ios/cdvd
- REVERTED `iosCdvdMgrPackLoad` (old `func_001312F0`) @ 0x001312F0 — ios/cdvd.c:31: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00131480` (old `func_00131480`) @ 0x00131480 — ios/cdvd.c:21: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00131560` (old `func_00131560`) @ 0x00131560 — ios/cdvd.c:15: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00131780` (old `func_00131780`) @ 0x00131780 — ios/cdvd.c:17: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdDiskReady` (old `func_00132038`) @ 0x00132038 — ios/cdvd.c:15: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdLoad` (old `func_001320E8`) @ 0x001320E8 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdPackLoad` (old `func_001321C8`) @ 0x001321C8 — ios/cdvd.c:16: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgr` (old `func_001325D8`) @ 0x001325D8 — ios/cdvd.c:13: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdDirectStOpen` (old `func_00132610`) @ 0x00132610 — ios/cdvd.c:13: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_001331D8` (old `func_001331D8`) @ 0x001331D8 — ios/cdvd.c:14: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdLoadPackFile` (old `func_00133218`) @ 0x00133218 — ios/cdvd.c:121: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskStatusGet` (old `func_001332B8`) @ 0x001332B8 — ios/cdvd.c:19: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgrDelete` (old `func_00133398`) @ 0x00133398 — ios/cdvd.c:13: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgrDeleteRequestGet` (old `func_00133448`) @ 0x00133448 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundMgrEntryNum` (old `func_00133450`) @ 0x00133450 — ios/cdvd.c:10: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundRead` (old `func_00133480`) @ 0x00133480 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `iosCdvdBackGroundReadIOPm` (old `func_001334C8`) @ 0x001334C8 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00133500` (old `func_00133500`) @ 0x00133500 — ios/cdvd.c:10: `D_00631F70' undeclared (first use in this function)
- REVERTED `func_00133508` (old `func_00133508`) @ 0x00133508 — ios/cdvd.c:12: `D_00631F70' undeclared (first use in this function)

## ios/cdvd
- REVERTED `iosCdvdMgrPackLoad` (old `func_001312F0`) @ 0x001312F0 — ios/cdvd.c:110: invalid use of undefined type `struct E001332B8'
- REVERTED `func_00131480` (old `func_00131480`) @ 0x00131480 — ios/cdvd.c:93: void value not ignored as it ought to be
- REVERTED `func_00131560` (old `func_00131560`) @ 0x00131560 — ios/cdvd.c:67: void value not ignored as it ought to be
- REVERTED `func_00131780` (old `func_00131780`) @ 0x00131780 — ios/cdvd.c:67: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskReady` (old `func_00132038`) @ 0x00132038 — ios/cdvd.c:86: warning: passing arg 1 of `debug_assertMessage' makes pointer from integer without a cast
- REVERTED `iosCdvdLoad` (old `func_001320E8`) @ 0x001320E8 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdPackLoad` (old `func_001321C8`) @ 0x001321C8 — ios/cdvd.c:90: warning: assignment makes pointer from integer without a cast
- REVERTED `iosCdvdBackGroundMgr` (old `func_001325D8`) @ 0x001325D8 — ios/cdvd.c:78: dereferencing pointer to incomplete type
- REVERTED `iosCdvdDirectStOpen` (old `func_00132610`) @ 0x00132610 — ios/cdvd.c:80: warning: passing arg 1 of `iosMsgSend' makes pointer from integer without a cast
- REVERTED `func_001331D8` (old `func_001331D8`) @ 0x001331D8 — ios/cdvd.c:100: void value not ignored as it ought to be
- REVERTED `iosCdvdLoadPackFile` (old `func_00133218`) @ 0x00133218 — ios/cdvd.c:120: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskStatusGet` (old `func_001332B8`) @ 0x001332B8 — ios/cdvd.c:117: invalid use of undefined type `struct E001332B8'
- REVERTED `iosCdvdBackGroundMgrDelete` (old `func_00133398`) @ 0x00133398 — ios/cdvd.c:43: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundMgrDeleteRequestGet` (old `func_00133448`) @ 0x00133448 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundMgrEntryNum` (old `func_00133450`) @ 0x00133450 — ios/cdvd.c:40: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundRead` (old `func_00133480`) @ 0x00133480 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundReadIOPm` (old `func_001334C8`) @ 0x001334C8 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `func_00133500` (old `func_00133500`) @ 0x00133500 — ios/cdvd.c:40: void value not ignored as it ought to be
- REVERTED `func_00133508` (old `func_00133508`) @ 0x00133508 — ios/cdvd.c:42: void value not ignored as it ought to be

## ios/cdvd
- REVERTED `iosCdvdMgrPackLoad` (old `func_001312F0`) @ 0x001312F0 — ios/cdvd.c:110: invalid use of undefined type `struct E001332B8'
- REVERTED `func_00131480` (old `func_00131480`) @ 0x00131480 — ios/cdvd.c:93: void value not ignored as it ought to be
- REVERTED `func_00131560` (old `func_00131560`) @ 0x00131560 — ios/cdvd.c:67: void value not ignored as it ought to be
- REVERTED `func_00131780` (old `func_00131780`) @ 0x00131780 — ios/cdvd.c:67: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskReady` (old `func_00132038`) @ 0x00132038 — ios/cdvd.c:86: warning: passing arg 1 of `debug_assertMessage' makes pointer from integer without a cast
- REVERTED `iosCdvdLoad` (old `func_001320E8`) @ 0x001320E8 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdPackLoad` (old `func_001321C8`) @ 0x001321C8 — ios/cdvd.c:90: warning: assignment makes pointer from integer without a cast
- REVERTED `iosCdvdBackGroundMgr` (old `func_001325D8`) @ 0x001325D8 — ios/cdvd.c:85: warning: passing arg 1 of `iosMsgSend' makes pointer from integer without a cast
- REVERTED `iosCdvdDirectStOpen` (old `func_00132610`) @ 0x00132610 — ios/cdvd.c:80: warning: passing arg 1 of `iosMsgSend' makes pointer from integer without a cast
- REVERTED `func_001331D8` (old `func_001331D8`) @ 0x001331D8 — ios/cdvd.c:100: void value not ignored as it ought to be
- REVERTED `iosCdvdLoadPackFile` (old `func_00133218`) @ 0x00133218 — ios/cdvd.c:120: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskStatusGet` (old `func_001332B8`) @ 0x001332B8 — ios/cdvd.c:117: invalid use of undefined type `struct E001332B8'
- REVERTED `iosCdvdBackGroundMgrDelete` (old `func_00133398`) @ 0x00133398 — ios/cdvd.c:43: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundMgrDeleteRequestGet` (old `func_00133448`) @ 0x00133448 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundMgrEntryNum` (old `func_00133450`) @ 0x00133450 — ios/cdvd.c:40: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundRead` (old `func_00133480`) @ 0x00133480 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundReadIOPm` (old `func_001334C8`) @ 0x001334C8 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `func_00133500` (old `func_00133500`) @ 0x00133500 — ios/cdvd.c:40: void value not ignored as it ought to be
- REVERTED `func_00133508` (old `func_00133508`) @ 0x00133508 — ios/cdvd.c:42: void value not ignored as it ought to be

## ios/cdvd
- REVERTED `iosCdvdMgrPackLoad` (old `func_001312F0`) @ 0x001312F0 — ios/cdvd.c:107: void value not ignored as it ought to be
- REVERTED `func_00131480` (old `func_00131480`) @ 0x00131480 — ios/cdvd.c:93: void value not ignored as it ought to be
- REVERTED `func_00131560` (old `func_00131560`) @ 0x00131560 — ios/cdvd.c:67: void value not ignored as it ought to be
- REVERTED `func_00131780` (old `func_00131780`) @ 0x00131780 — ios/cdvd.c:67: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskReady` (old `func_00132038`) @ 0x00132038 — ios/cdvd.c:86: warning: passing arg 1 of `debug_assertMessage' makes pointer from integer without a cast
- REVERTED `iosCdvdLoad` (old `func_001320E8`) @ 0x001320E8 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdPackLoad` (old `func_001321C8`) @ 0x001321C8 — ios/cdvd.c:90: warning: assignment makes pointer from integer without a cast
- REVERTED `iosCdvdBackGroundMgr` (old `func_001325D8`) @ 0x001325D8 — ios/cdvd.c:85: warning: passing arg 1 of `iosMsgSend' makes pointer from integer without a cast
- REVERTED `iosCdvdDirectStOpen` (old `func_00132610`) @ 0x00132610 — ios/cdvd.c:80: warning: passing arg 1 of `iosMsgSend' makes pointer from integer without a cast
- REVERTED `func_001331D8` (old `func_001331D8`) @ 0x001331D8 — ios/cdvd.c:100: void value not ignored as it ought to be
- REVERTED `iosCdvdLoadPackFile` (old `func_00133218`) @ 0x00133218 — ios/cdvd.c:120: void value not ignored as it ought to be
- REVERTED `iosCdvdDiskStatusGet` (old `func_001332B8`) @ 0x001332B8 — ios/cdvd.c:120: warning: passing arg 3 of `func_00263FF0' makes integer from pointer without a cast
- REVERTED `iosCdvdBackGroundMgrDelete` (old `func_00133398`) @ 0x00133398 — ios/cdvd.c:43: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundMgrDeleteRequestGet` (old `func_00133448`) @ 0x00133448 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundMgrEntryNum` (old `func_00133450`) @ 0x00133450 — ios/cdvd.c:40: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundRead` (old `func_00133480`) @ 0x00133480 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `iosCdvdBackGroundReadIOPm` (old `func_001334C8`) @ 0x001334C8 — ios/cdvd.c:42: void value not ignored as it ought to be
- REVERTED `func_00133500` (old `func_00133500`) @ 0x00133500 — ios/cdvd.c:40: void value not ignored as it ought to be
- REVERTED `func_00133508` (old `func_00133508`) @ 0x00133508 — ios/cdvd.c:42: void value not ignored as it ought to be

## ios/cdvd
- KEPT `func_00131560` (old `func_00131560`) @ 0x00131560
- KEPT `func_001331D8` (old `func_001331D8`) @ 0x001331D8
- KEPT `iosCdvdLoadPackFile` (old `func_00133218`) @ 0x00133218
- KEPT `iosCdvdBackGroundMgrDelete` (old `func_00133398`) @ 0x00133398
- KEPT `iosCdvdBackGroundMgrDeleteRequestGet` (old `func_00133448`) @ 0x00133448
- KEPT `iosCdvdBackGroundMgrEntryNum` (old `func_00133450`) @ 0x00133450
- KEPT `iosCdvdBackGroundRead` (old `func_00133480`) @ 0x00133480
- KEPT `iosCdvdBackGroundReadIOPm` (old `func_001334C8`) @ 0x001334C8
- KEPT `func_00133500` (old `func_00133500`) @ 0x00133500
- KEPT `func_00133508` (old `func_00133508`) @ 0x00133508
- REVERTED `iosCdvdMgrPackLoad` (old `func_001312F0`) @ 0x001312F0 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `func_00131480` (old `func_00131480`) @ 0x00131480 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `func_00131780` (old `func_00131780`) @ 0x00131780 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `iosCdvdDiskReady` (old `func_00132038`) @ 0x00132038 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosCdvdLoad` (old `func_001320E8`) @ 0x001320E8 — insn 18: expected `j	0 <iosCdvdLoad>` built `j	1e60 <iosCdvdDiskReady>`
- REVERTED `iosCdvdPackLoad` (old `func_001321C8`) @ 0x001321C8 — [§4.2] signed div/shift collapsed to movn
- REVERTED `iosCdvdBackGroundMgr` (old `func_001325D8`) @ 0x001325D8 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `iosCdvdDirectStOpen` (old `func_00132610`) @ 0x00132610 — insn 0: expected `daddu	a1,a0,zero` built `addiu	v0,zero,2`
- REVERTED `iosCdvdDiskStatusGet` (old `func_001332B8`) @ 0x001332B8 — [§3.3 / 8.6] branch-likely mnemonic mismatch (beq↔beql / bne↔bnel)

## src/box
- REVERTED `initFloating` (old `func_001BE558`) @ 0x001BE558 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `ExecBoxMoveEndReaction` (old `func_001C0690`) @ 0x001C0690 — src/box.c:53: warning: initialization from incompatible pointer type
- REVERTED `BoxExtGeoRestore` (old `func_001C0708`) @ 0x001C0708 — src/box.c:58: warning: initialization from incompatible pointer type

## src/delayFreeManager

## src/geometryManager
- REVERTED `UpdateRootMatrix` (old `func_001029B8`) @ 0x001029B8 — insn 0: expected `j	0 <UpdateRootMatrix>` built `j	88 <GetRootQuaternion>`
- REVERTED `func_00102A38` (old `func_00102A38`) @ 0x00102A38 — src/geometryManager.c:50: too few arguments to function `SetRootBaseQuaternion'
- REVERTED `SetRootMatrixWithTransOffset` (old `func_00102DE0`) @ 0x00102DE0 — insn 3: expected `jal	0 <SetRootMatrixWithTransOffset>` built `jal	150 <func_00102A40>`

## src/keyInput
- KEPT `func_00104698` (old `func_00104698`) @ 0x00104698
- KEPT `func_00104A38` (old `func_00104A38`) @ 0x00104A38
- REVERTED `InitKeyInput` (old `func_00104590`) @ 0x00104590 — src/keyInput.c:5: redefinition of `struct GObj'
- REVERTED `func_001046F0` (old `func_001046F0`) @ 0x001046F0 — src/keyInput.c:6: redefinition of `struct GObj'
- REVERTED `func_001048C8` (old `func_001048C8`) @ 0x001048C8 — src/keyInput.c:41: incompatible type for argument 3 of `_PushVu0Registers'
- REVERTED `func_00104940` (old `func_00104940`) @ 0x00104940 — src/keyInput.c:46: incompatible type for argument 3 of `_PushVu0Registers'
- REVERTED `func_001049C0` (old `func_001049C0`) @ 0x001049C0 — src/keyInput.c:45: incompatible type for argument 3 of `_PushVu0Registers'
- REVERTED `func_00104EF0` (old `func_00104EF0`) @ 0x00104EF0 — src/keyInput.c:53: incompatible types in assignment
- REVERTED `func_00104F20` (old `func_00104F20`) @ 0x00104F20 — src/keyInput.c:53: wrong type argument to increment
- REVERTED `func_001050B0` (old `func_001050B0`) @ 0x001050B0 — src/keyInput.c:77: wrong type argument to decrement
- REVERTED `func_00105258` (old `func_00105258`) @ 0x00105258 — src/keyInput.c:63: wrong type argument to increment
- REVERTED `func_00105268` (old `func_00105268`) @ 0x00105268 — src/keyInput.c:65: wrong type argument to decrement
- REVERTED `func_00105278` (old `func_00105278`) @ 0x00105278 — src/keyInput.c:68: invalid operands to binary *
- REVERTED `func_00105290` (old `func_00105290`) @ 0x00105290 — src/keyInput.c:70: invalid operands to binary *
- REVERTED `func_001052A8` (old `func_001052A8`) @ 0x001052A8 — src/keyInput.c:76: invalid operands to binary *

## src/matrixDrive

## src/motionManager2
- KEPT `DebugDisp1Collision` (old `func_00109E88`) @ 0x00109E88
- KEPT `GetRootProjectionPosOfGObj` (old `func_0010A558`) @ 0x0010A558
- REVERTED `CheckWallAttribute` (old `func_0010A120`) @ 0x0010A120 — insn 12: expected `ld	ra,0(sp)` built `trunc.w.s	$f1,$f0`
- REVERTED `CheckPureWallAttribute` (old `func_0010A160`) @ 0x0010A160 — insn 12: expected `ld	ra,0(sp)` built `trunc.w.s	$f1,$f0`

## src/pool
- REVERTED `func_0010D338` (old `func_0010D338`) @ 0x0010D338 — src/pool.c:72: warning: initialization from incompatible pointer type

## src/quaternion
- REVERTED `MultiCurrentQuaternion` (old `func_0010D360`) @ 0x0010D360 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `RegularizeQuaternion` (old `func_0010D838`) @ 0x0010D838 — src/quaternion.c:79: too few arguments to function `GetInverseQuaternion'

## src/tableSin
- REVERTED `GetTableArcCos` (old `func_0010DBD0`) @ 0x0010DBD0 — src/tableSin.c:68: incompatible type for argument 3 of `_InverseCurrentMatrix'
- REVERTED `func_0010DCF8` (old `func_0010DCF8`) @ 0x0010DCF8 — src/tableSin.c:70: incompatible type for argument 3 of `_InverseCurrentMatrix'
- REVERTED `func_0010DD58` (old `func_0010DD58`) @ 0x0010DD58 — src/tableSin.c:66: incompatible type for argument 3 of `_InverseCurrentMatrix'
- REVERTED `func_0010DDB8` (old `func_0010DDB8`) @ 0x0010DDB8 — src/tableSin.c:84: too few arguments to function `func_0010DDB8'

## src/DisplayP2O
- KEPT `p2o_TransMicroProgram` (old `func_0010E928`) @ 0x0010E928
- REVERTED `p2o_DispVU1Multi` (old `func_0010E708`) @ 0x0010E708 — src/DisplayP2O.c:38: void value not ignored as it ought to be
- REVERTED `func_0010EC08` (old `func_0010EC08`) @ 0x0010EC08 — insn 4: expected `bc1f	30 <func_0010EC08+0x30>` built `bc1f	8a8 <func_0010EC08+0x38>`

## src/FileManager
- KEPT `func_0010F710` (old `func_0010F710`) @ 0x0010F710
- REVERTED `file_LoadFile` (old `func_0010ECA8`) @ 0x0010ECA8 — src/FileManager.c:7: redefinition of `struct GObj'
- REVERTED `func_0010ECB0` (old `func_0010ECB0`) @ 0x0010ECB0 — insn 0: expected `j	0 <func_0010ECB0>` built `j	10 <file_LoadFile>`
- REVERTED `func_0010ECB8` (old `func_0010ECB8`) @ 0x0010ECB8 — src/FileManager.c:7: redefinition of `struct GObj'
- REVERTED `func_0010ECC0` (old `func_0010ECC0`) @ 0x0010ECC0 — insn 0: expected `j	0 <func_0010ECC0>` built `j	20 <func_0010ECB8>`

## src/GifPacket

## src/GsBase

## src/Light
- KEPT `light_GetColorAnalog` (old `func_00114E18`) @ 0x00114E18
- KEPT `func_001177C8` (old `func_001177C8`) @ 0x001177C8
- REVERTED `light_KillAllFixLight` (old `func_00114FC8`) @ 0x00114FC8 — src/Light.c:88: `Light' undeclared (first use in this function)
- REVERTED `light_KillAllAmbient` (old `func_00115068`) @ 0x00115068 — [§3.3 / 8.6] branch-likely mnemonic mismatch (beq↔beql / bne↔bnel)
- REVERTED `func_00117768` (old `func_00117768`) @ 0x00117768 — src/Light.c:100: `Light' undeclared (first use in this function)
- REVERTED `func_00117820` (old `func_00117820`) @ 0x00117820 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/Matrix

## src/MicroCode

## src/Packet
- REVERTED `pac_setVifEndCode` (old `func_00118FD8`) @ 0x00118FD8 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `pac_continueTag` (old `func_00119470`) @ 0x00119470 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `pac_setMaterialPacket` (old `func_0011A238`) @ 0x0011A238 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `pac_makeMaterialTable` (old `func_0011A2A8`) @ 0x0011A2A8 — insn 1: expected `daddu	t0,a0,zero` built `lui	v0,0x6c00`
- QUARANTINED `pac_DispQW` (old `func_00118A68`) @ 0x00118A68 — vu0-inline-asm

## src/Primitive

## src/RegistPacket
- KEPT `func_0011E708` (old `func_0011E708`) @ 0x0011E708

## src/Shadow
- KEPT `shadow_KillShadow` (old `func_00122C50`) @ 0x00122C50

## src/StageAnimation
- KEPT `func_0012AA80` (old `func_0012AA80`) @ 0x0012AA80

## src/Texture
- KEPT `tex_loadImage` (old `func_0012ADE8`) @ 0x0012ADE8

## src/ZFog
- KEPT `func_0012FD30` (old `func_0012FD30`) @ 0x0012FD30

## ios/inflate
- REVERTED `func_00135A48` (old `func_00135A48`) @ 0x00135A48 — [§8.22] swc1 in jal delay slot where expected has addiu/lw

## ios/ios

## ios/mblock
- REVERTED `new_segment` (old `func_00136088`) @ 0x00136088 — insn 1: expected `jr	ra` built `sw	zero,0(a0)`
- REVERTED `strdup_mblock` (old `func_00136140`) @ 0x00136140 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

## ios/mcard
- REVERTED `iosMcMgrLoadSeg` (old `func_00137538`) @ 0x00137538 — insn 2: expected `j	0 <iosMcMgrLoadSeg>` built `j	6d8 <iosMcMgrChdirProduct>`
- REVERTED `iosMcMgrSaveProductBlock` (old `func_00137548`) @ 0x00137548 — insn 2: expected `j	0 <iosMcMgrSaveProductBlock>` built `j	b08 <iosMcMgrSaveSeg>`

## ios/mcdata
- REVERTED `func_001383F8` (old `func_001383F8`) @ 0x001383F8 — ios/mcdata.c:6: parse error before `Blk40_001383F8'

## ios/memory
- REVERTED `iosMallocDebug` (old `func_00138BF0`) @ 0x00138BF0 — insn 5: expected `bne	s0,zero,28 <iosMallocDebug+0x28>` built `bne	s0,zero,5fc <iosMallocDebug+0x24>`
- REVERTED `iosMallocCheckLeak` (old `func_001394F0`) @ 0x001394F0 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_0013A200` (old `func_0013A200`) @ 0x0013A200 — insn 2: expected `jal	0 <func_0013A200>` built `jal	818 <func_00138E30>`

## ios/message
- REVERTED `iosMsgQueueCreate` (old `func_0013A220`) @ 0x0013A220 — insn 11: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosMsgQueueDestroy` (old `func_0013A250`) @ 0x0013A250 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `send_signal_message` (old `func_0013A2F8`) @ 0x0013A2F8 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_0013A498` (old `func_0013A498`) @ 0x0013A498 — ios/message.c:35: `iosMsgSetEvent' undeclared (first use in this function)
- REVERTED `iosMsgSend` (old `func_0013A5B8`) @ 0x0013A5B8 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgQueueDestroyAll` (old `func_0013A7C8`) @ 0x0013A7C8 — insn 12: expected `jal	0 <iosMsgQueueDestroyAll>` built `jal	d8 <send_signal_message>`

## ios/pad
- KEPT `iosPadDisable` (old `func_0013B858`) @ 0x0013B858
- KEPT `iosPadEnableGet` (old `func_0013B868`) @ 0x0013B868
- KEPT `iosPadActInit` (old `func_0013B870`) @ 0x0013B870
- REVERTED `iosPadGetPort` (old `func_0013B718`) @ 0x0013B718 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `iosPadGetSlot` (old `func_0013B748`) @ 0x0013B748 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `iosPadGetDevice` (old `func_0013B760`) @ 0x0013B760 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `iosPadConnect` (old `func_0013B778`) @ 0x0013B778 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `iosPadStickCameraCoord` (old `func_0013B7C0`) @ 0x0013B7C0 — insn 0: expected `lui	v0,0x0` built `sw	a3,4(a0)`

## ios/shockdriver
- KEPT `Shock_Request` (old `func_0013B9D8`) @ 0x0013B9D8
- KEPT `Init_ShockVoiceSet` (old `func_0013BB70`) @ 0x0013BB70
- KEPT `Vibration_SetDecodeData` (old `func_0013BB78`) @ 0x0013BB78
- KEPT `ShockRequestBox_VoiceSetUseRequestFree` (old `func_0013C510`) @ 0x0013C510
- KEPT `ShockRequestBox_GetRequest` (old `func_0013C538`) @ 0x0013C538
- KEPT `ShockRequestBox_RequestCancel` (old `func_0013C598`) @ 0x0013C598
- KEPT `ShockDriver_VoiceSet_Remove` (old `func_0013C920`) @ 0x0013C920
- KEPT `Init_ShockEmulator` (old `func_0013CAA0`) @ 0x0013CAA0
- KEPT `ShockEmulator_EmulationWave` (old `func_0013CB50`) @ 0x0013CB50
- KEPT `Get_ShockRequestStruct` (old `func_0013CBD0`) @ 0x0013CBD0
- KEPT `Init_Shock` (old `func_0013CC70`) @ 0x0013CC70
- REVERTED `Vibration_ShotDecode` (old `func_0013B8F0`) @ 0x0013B8F0 — insn 10: expected `jal	0 <Vibration_ShotDecode>` built `jal	1068 <ShockDriver_GetShockVoiceMax>`
- REVERTED `Vibration_WaveDecode` (old `func_0013B970`) @ 0x0013B970 — insn 14: expected `jal	0 <Vibration_WaveDecode>` built `jal	1068 <ShockDriver_GetShockVoiceMax>`
- REVERTED `Shock_SetMotor` (old `func_0013BA20`) @ 0x0013BA20 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

## ios/thread
- KEPT `iosThreadStop` (old `func_0013CD70`) @ 0x0013CD70
- KEPT `iosThreadSetPri` (old `func_0013CF08`) @ 0x0013CF08
- KEPT `iosThreadSuspend` (old `func_0013CF80`) @ 0x0013CF80
- KEPT `iosThreadInit` (old `func_0013D098`) @ 0x0013D098
- KEPT `iosThreadCreate` (old `func_0013D0A0`) @ 0x0013D0A0
- KEPT `iosThreadJoin` (old `func_0013D3C8`) @ 0x0013D3C8
- KEPT `iosThreadCancelWakeup` (old `func_0013D3D8`) @ 0x0013D3D8
- KEPT `iosSemaCreate` (old `func_0013D3F0`) @ 0x0013D3F0
- KEPT `iosSemaDelete` (old `func_0013D3F8`) @ 0x0013D3F8
- KEPT `iosSemaWait` (old `func_0013D440`) @ 0x0013D440
- KEPT `iosSemaReferStatus` (old `func_0013D538`) @ 0x0013D538
- KEPT `iosThreadDestroyMgr` (old `func_0013D540`) @ 0x0013D540
- KEPT `iosThreadAllQuit` (old `func_0013D548`) @ 0x0013D548
- KEPT `func_0013D8A0` (old `func_0013D8A0`) @ 0x0013D8A0
- KEPT `func_0013D928` (old `func_0013D928`) @ 0x0013D928
- KEPT `func_0013D9C8` (old `func_0013D9C8`) @ 0x0013D9C8
- KEPT `func_0013DD88` (old `func_0013DD88`) @ 0x0013DD88
- REVERTED `iosThreadMessage` (old `func_0013CF38`) @ 0x0013CF38 — ios/thread.c:37: `iosThreadStart' undeclared (first use in this function)
- REVERTED `iosGetIOSThreadFromId` (old `func_0013D140`) @ 0x0013D140 — insn 20: expected `j	0 <iosGetIOSThreadFromId>` built `j	7c8 <iosSemaWait>`
- REVERTED `func_0013D8E0` (old `func_0013D8E0`) @ 0x0013D8E0 — insn 2: expected `bne	v0,zero,24 <func_0013D8E0+0x24>` built `bne	v0,zero,c88 <func_0013D8E0+0x20>`
- REVERTED `func_0013DA00` (old `func_0013DA00`) @ 0x0013DA00 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `func_0013DA88` (old `func_0013DA88`) @ 0x0013DA88 — insn 8: expected `bgez	s1,64 <func_0013DA88+0x64>` built `bgez	s1,e70 <func_0013DA88+0x60>`
- REVERTED `func_0013DB00` (old `func_0013DB00`) @ 0x0013DB00 — insn 10: expected `lui	a0,0x0` built `sll	zero,zero,0x0`
- REVERTED `func_0013DB60` (old `func_0013DB60`) @ 0x0013DB60 — insn 8: expected `bgez	s1,3c <func_0013DB60+0x3c>` built `bgez	s1,f20 <func_0013DB60+0x38>`
- REVERTED `func_0013DBB0` (old `func_0013DBB0`) @ 0x0013DBB0 — insn 9: expected `bgez	s1,68 <func_0013DBB0+0x68>` built `bgez	s1,f9c <func_0013DBB0+0x64>`

## isys/gobj
- KEPT `isysGObjAddBeforeGObj` (old `func_0013E488`) @ 0x0013E488
- REVERTED `add_gobj_to_head` (old `func_0013E190`) @ 0x0013E190 — insn 7: expected `jal	0 <add_gobj_to_head>` built `jal	58 <isysGObjInit>`
- REVERTED `isysGObjMove` (old `func_0013E1D8`) @ 0x0013E1D8 — insn 7: expected `jal	0 <isysGObjMove>` built `jal	58 <isysGObjInit>`
- REVERTED `isysGObjKindTableRemove` (old `func_0013E7F8`) @ 0x0013E7F8 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `isysGObjMoveAfterGObj` (old `func_0013E868`) @ 0x0013E868 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## isys/gobj_dl
- KEPT `func_0013ED40` (old `func_0013ED40`) @ 0x0013ED40
- KEPT `isysGObjMoveObjDL` (old `func_0013ED78`) @ 0x0013ED78
- KEPT `func_0013F1F8` (old `func_0013F1F8`) @ 0x0013F1F8
- KEPT `func_0013F260` (old `func_0013F260`) @ 0x0013F260
- REVERTED `func_0013ECF8` (old `func_0013ECF8`) @ 0x0013ECF8 — isys/gobj_dl.c:5: redefinition of `struct GObj'
- REVERTED `isysGObjLinkObjDL` (old `func_0013EE58`) @ 0x0013EE58 — insn 0: expected `j	0 <isysGObjLinkObjDL>` built `j	160 <isysGObjMoveObjDLHead>`
- REVERTED `isysGObjLinkObjDLBeforeGObj` (old `func_0013F0A0`) @ 0x0013F0A0 — insn 7: expected `jal	0 <isysGObjLinkObjDLBeforeGObj>` built `jal	160 <isysGObjMoveObjDLHead>`
- REVERTED `isysGObjDlInit` (old `func_0013F0E8`) @ 0x0013F0E8 — insn 7: expected `jal	0 <isysGObjDlInit>` built `jal	160 <isysGObjMoveObjDLHead>`
- REVERTED `isysGObjMoveObjDLAfterGObj` (old `func_0013F130`) @ 0x0013F130 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `isysGObjMoveObjDLBeforeGObj` (old `func_0013F1D0`) @ 0x0013F1D0 — insn 6: expected `j	0 <isysGObjMoveObjDLBeforeGObj>` built `j	380 <isysGObjLinkObjDLAfterGObj>`

## isys/gobj_process
- KEPT `isysGObjProcActive` (old `func_0013F808`) @ 0x0013F808
- KEPT `isysGObjProcActiveAll` (old `func_0013F810`) @ 0x0013F810
- REVERTED `isysGObjProcRemove` (old `func_0013F3E8`) @ 0x0013F3E8 — insn 0: expected `j	0 <isysGObjProcRemove>` built `j	438 <isysGObjProcAddGOppArg>`
- REVERTED `isysGObjProcAddS` (old `func_0013F6B8`) @ 0x0013F6B8 — insn 3: expected `jal	0 <isysGObjProcAddS>` built `jal	370 <isysGObjProcAdd>`
- REVERTED `isysGObjProcPause` (old `func_0013F778`) @ 0x0013F778 — insn 0: expected `daddu	t0,a3,zero` built `daddu	v0,a2,zero`
- REVERTED `isysGObjProcPauseAll` (old `func_0013F7A8`) @ 0x0013F7A8 — insn 7: expected `jal	0 <isysGObjProcPauseAll>` built `jal	128 <isysGObjProcessAlloc>`

## isys/isys
- KEPT `isysInitialize` (old `func_0013F848`) @ 0x0013F848
- KEPT `func_0013F888` (old `func_0013F888`) @ 0x0013F888
- KEPT `func_0013F8C0` (old `func_0013F8C0`) @ 0x0013F8C0
- KEPT `func_0013F8F8` (old `func_0013F8F8`) @ 0x0013F8F8
- KEPT `func_0013F930` (old `func_0013F930`) @ 0x0013F930
- KEPT `func_0013F960` (old `func_0013F960`) @ 0x0013F960
- KEPT `func_0013F990` (old `func_0013F990`) @ 0x0013F990
- KEPT `func_0013F9A0` (old `func_0013F9A0`) @ 0x0013F9A0
- REVERTED `func_0013F998` (old `func_0013F998`) @ 0x0013F998 — insn 0: expected `j	0 <func_0013F998>` built `j	158 <func_0013F9A0>`

## isys/obj_manager
- KEPT `_iosOmMain` (old `func_0013FBF8`) @ 0x0013FBF8
- KEPT `iosOmCreateDL` (old `func_0013FD10`) @ 0x0013FD10
- KEPT `iosOmExeEachGObj` (old `func_0013FD78`) @ 0x0013FD78
- KEPT `iosOmExeEachGObjAll` (old `func_0013FE18`) @ 0x0013FE18
- KEPT `iosOmReturnExeEachGObj` (old `func_0013FEB0`) @ 0x0013FEB0
- KEPT `iosOmGetGObjStatus` (old `func_0013FEE0`) @ 0x0013FEE0
- KEPT `iosOmSearchGObjIdAll` (old `func_0013FF80`) @ 0x0013FF80
- KEPT `iosOmBeforeFuncStandard` (old `func_0013FF88`) @ 0x0013FF88
- KEPT `soundInit` (old `func_0013FFD0`) @ 0x0013FFD0
- KEPT `func_00140130` (old `func_00140130`) @ 0x00140130
- REVERTED `soundOutputModeSet` (old `func_00140048`) @ 0x00140048 — insn 11: expected `blez	a2,c4 <.L001400FC+0x10>` built `blez	a2,73c <soundOutputModeSet+0xc4>`

## sound/adpcm_init
- KEPT `AdpcmInterStereoVolumeSet` (old `func_00140740`) @ 0x00140740
- KEPT `func_00140B70` (old `func_00140B70`) @ 0x00140B70
- KEPT `AdpcmInterStereoVolumeSetAll` (old `func_00140EE8`) @ 0x00140EE8
- KEPT `AdpcmInterLeaveVolumeGet` (old `func_00140F20`) @ 0x00140F20
- KEPT `AdpcmVolumeGet` (old `func_00140F58`) @ 0x00140F58
- KEPT `DebugActOrientFlag` (old `func_00141020`) @ 0x00141020
- KEPT `ACTGetEnvironment` (old `func_00141038`) @ 0x00141038
- KEPT `GetSofaPosition` (old `func_00141128`) @ 0x00141128
- KEPT `GetCollisCenterPositionSimple` (old `func_00141130`) @ 0x00141130
- KEPT `CheckWallAttributeEdegWall` (old `func_00141138`) @ 0x00141138
- KEPT `func_00141160` (old `func_00141160`) @ 0x00141160
- REVERTED `AdpcmClose` (old `func_00140710`) @ 0x00140710 — insn 4: expected `lui	a0,0x0` built `jal	0 <AdpcmStop>`
- REVERTED `AdpcmIopBuffAlloc` (old `func_00140B30`) @ 0x00140B30 — insn 9: expected `j	0 <AdpcmIopBuffAlloc>` built `j	8e8 <adpcmPauseRequest>`
- REVERTED `AdpcmOpenSync` (old `func_00140B60`) @ 0x00140B60 — insn 1: expected `j	0 <AdpcmOpenSync>` built `j	9f8 <AdpcmIopBuffAlloc>`
- REVERTED `func_00140B78` (old `func_00140B78`) @ 0x00140B78 — [§4.2] signed div/shift collapsed to movn
- REVERTED `func_00140D58` (old `func_00140D58`) @ 0x00140D58 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `AdpcmFreeAreaGet` (old `func_00140E48`) @ 0x00140E48 — insn 4: expected `lui	a0,0x0` built `jal	0 <AdpcmStop>`
- REVERTED `GetDitchPosition` (old `func_00140F90`) @ 0x00140F90 — insn 20: expected `jal	0 <GetDitchPosition>` built `jal	8e8 <adpcmPauseRequest>`

## sound/s_init
- KEPT `soundAllocIopHeap` (old `func_001412B8`) @ 0x001412B8
- KEPT `soundAllocIopFree` (old `func_001412C8`) @ 0x001412C8
- KEPT `soundBufAlloc` (old `func_001413A0`) @ 0x001413A0
- KEPT `soundSeEnvPlay` (old `func_00143250`) @ 0x00143250
- KEPT `soundReverbDepthGet` (old `func_00143B88`) @ 0x00143B88
- KEPT `soundBufAdpcmChAlloc` (old `func_00143B90`) @ 0x00143B90
- KEPT `soundDataAreaSearch` (old `func_00143CB0`) @ 0x00143CB0
- KEPT `soundSeDefVolumeRateSet` (old `func_001441C8`) @ 0x001441C8
- KEPT `soundSeGroupStop` (old `func_00144208`) @ 0x00144208
- KEPT `soundSePlayModeStop` (old `func_001442E0`) @ 0x001442E0
- KEPT `soundSeSemiCommonLoadChk` (old `func_001444A0`) @ 0x001444A0
- KEPT `debug_req` (old `func_001445C0`) @ 0x001445C0
- REVERTED `soundDataOpenChk` (old `func_00141340`) @ 0x00141340 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `soundDataOpen` (old `func_00141868`) @ 0x00141868 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `soundDataClose` (old `func_00141C28`) @ 0x00141C28 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `soundDataSegAllClose` (old `func_00141D18`) @ 0x00141D18 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `debug_DispSEInfo` (old `func_00141F58`) @ 0x00141F58 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `soundSeDefPitchSet` (old `func_00143240`) @ 0x00143240 — insn 0: expected `j	0 <soundSeDefPitchSet>` built `j	1fd0 <soundSeDefStopNoRelease>`
- REVERTED `soundReqTickProc` (old `func_00143248`) @ 0x00143248 — insn 0: expected `j	0 <soundReqTickProc>` built `j	1fd0 <soundSeDefStopNoRelease>`
- REVERTED `soundOutputModeGet` (old `func_00143AD0`) @ 0x00143AD0 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `soundSeDefPlayWithVolumeRate` (old `func_00144120`) @ 0x00144120 — insn 1: expected `lui	at,0xbf80` built `dli	t0,0xbff0`
- REVERTED `soundSeDefVolumeRateGet` (old `func_00144178`) @ 0x00144178 — sound/s_init.c:122: `soundSeDefStop' undeclared (first use in this function)
- REVERTED `soundSeGroupGet` (old `func_00144240`) @ 0x00144240 — insn 27: expected `jal	0 <soundSeGroupGet>` built `jal	20d8 <soundSeDefPitchSet>`
- REVERTED `soundVBlank` (old `func_00144308`) @ 0x00144308 — insn 21: expected `jal	0 <soundVBlank>` built `jal	20e0 <soundReqTickProc>`
- REVERTED `soundSeEnvDefaultSet` (old `func_00144500`) @ 0x00144500 — insn 1: expected `addiu	a1,zero,1388` built `lw	v1,0(gp)`

## sound/soundManager
- KEPT `sndManager` (old `func_00144780`) @ 0x00144780
- KEPT `func_001447E0` (old `func_001447E0`) @ 0x001447E0
- KEPT `func_00144928` (old `func_00144928`) @ 0x00144928
- KEPT `func_00144DF0` (old `func_00144DF0`) @ 0x00144DF0
- KEPT `func_00144E10` (old `func_00144E10`) @ 0x00144E10
- KEPT `func_00144E30` (old `func_00144E30`) @ 0x00144E30
- KEPT `func_00145300` (old `func_00145300`) @ 0x00145300
- KEPT `func_00145638` (old `func_00145638`) @ 0x00145638
- REVERTED `sndInit` (old `func_001446E8`) @ 0x001446E8 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

## src/act-game
- KEPT `ACTLookTarget_Exec` (old `func_00149E70`) @ 0x00149E70
- KEPT `ACTParaStatus_Clear` (old `func_00149EA8`) @ 0x00149EA8
- KEPT `func_00149EF8` (old `func_00149EF8`) @ 0x00149EF8
- KEPT `FunctionAboutClingedStatus` (old `func_0014A0A8`) @ 0x0014A0A8
- KEPT `ACTEnvGetTest` (old `func_0014A0D8`) @ 0x0014A0D8
- KEPT `hand_able_connect` (old `func_0014A2B0`) @ 0x0014A2B0
- KEPT `func_0014A2C8` (old `func_0014A2C8`) @ 0x0014A2C8
- KEPT `GetOtherStageGirlOrient` (old `func_0014A308`) @ 0x0014A308
- KEPT `ACTItemThrow` (old `func_0014A430`) @ 0x0014A430
- KEPT `func_0014A470` (old `func_0014A470`) @ 0x0014A470
- KEPT `ACTGame_InsertCamera_GirlIsPinch` (old `func_0014A4E0`) @ 0x0014A4E0
- KEPT `RequestChangeHandMode` (old `func_0014A5C0`) @ 0x0014A5C0
- KEPT `ACTCharctrl_Unlock` (old `func_0014B000`) @ 0x0014B000
- KEPT `ACTGame_ConnectHand` (old `func_0014B048`) @ 0x0014B048
- KEPT `PAIR_IsStatus_BOY_PULL` (old `func_0014B150`) @ 0x0014B150
- REVERTED `ACTParaStatus_Exec` (old `func_00149ED0`) @ 0x00149ED0 — insn 0: expected `lw	v0,348(a0)` built `addiu	sp,sp,-32`
- REVERTED `GetSkeltonOrient` (old `func_00149F20`) @ 0x00149F20 — src/act-game.c:8: redefinition of `struct GObj'
- REVERTED `ACTGame_InnerVelocityUpdate` (old `func_00149F70`) @ 0x00149F70 — src/act-game.c:62: subscripted value is neither array nor pointer
- REVERTED `ActOrientTest` (old `func_0014A100`) @ 0x0014A100 — src/act-game.c:9: redefinition of `struct GObj'
- REVERTED `GetTarget` (old `func_0014A330`) @ 0x0014A330 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `ACTLookTargetSystem_Exec` (old `func_0014A3A8`) @ 0x0014A3A8 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `ACTGameCollisionOff` (old `func_0014A700`) @ 0x0014A700 — insn 5: expected `jal	0 <ACTGameCollisionOff>` built `jal	15b8 <ACTGame_DisconnectHand>`
- REVERTED `ACTGame_StageChangeGObjID` (old `func_0014A980`) @ 0x0014A980 — src/act-game.c:253: `U64ag' undeclared (first use in this function)
- REVERTED `ACTGame_DisconnectHand` (old `func_0014B090`) @ 0x0014B090 — src/act-game.c:275: warning: passing arg 1 of `checkHit' from incompatible pointer type
- REVERTED `PAIR_GetPosition_BOY` (old `func_0014B0B8`) @ 0x0014B0B8 — insn 13: expected `beq	s0,zero,7c <PAIR_GetPosition_BOY+0x7c>` built `beq	s0,zero,165c <PAIR_GetPosition_BOY+0x84>`

## src/act-parallel-control
- KEPT `ActPara_MakeTbl` (old `func_0014B168`) @ 0x0014B168
- KEPT `ActPara_InitSystem` (old `func_0014B1D0`) @ 0x0014B1D0
- KEPT `ActPara_GetDefTbl` (old `func_0014B228`) @ 0x0014B228
- KEPT `ActPara_StatusToFlag` (old `func_0014B248`) @ 0x0014B248
- KEPT `func_0014B2F0` (old `func_0014B2F0`) @ 0x0014B2F0
- KEPT `func_0014B318` (old `func_0014B318`) @ 0x0014B318
- KEPT `func_0014B320` (old `func_0014B320`) @ 0x0014B320
- KEPT `func_0014B330` (old `func_0014B330`) @ 0x0014B330
- KEPT `func_0014B358` (old `func_0014B358`) @ 0x0014B358
- REVERTED `ActPara_DebugOut` (old `func_0014B260`) @ 0x0014B260 — insn 2: expected `jr	ra` built `sd	zero,88(v0)`
- REVERTED `func_0014B270` (old `func_0014B270`) @ 0x0014B270 — insn 7: expected `beq	a0,zero,1c <func_0014B270+0x1c>` built `beq	a0,zero,17c <func_0014B270+0x74>`

## src/act-wish
- KEPT `func_0014B768` (old `func_0014B768`) @ 0x0014B768
- KEPT `func_0014B800` (old `func_0014B800`) @ 0x0014B800
- KEPT `func_0014B840` (old `func_0014B840`) @ 0x0014B840
- KEPT `func_0014B858` (old `func_0014B858`) @ 0x0014B858
- KEPT `func_0014BB00` (old `func_0014BB00`) @ 0x0014BB00
- KEPT `func_0014BBF0` (old `func_0014BBF0`) @ 0x0014BBF0
- KEPT `func_0014BD88` (old `func_0014BD88`) @ 0x0014BD88
- KEPT `func_0014BDC8` (old `func_0014BDC8`) @ 0x0014BDC8
- KEPT `func_0014BDD8` (old `func_0014BDD8`) @ 0x0014BDD8
- REVERTED `ACTGetWish_FromPad` (old `func_0014B580`) @ 0x0014B580 — insn 13: expected `<end>` built `sll	zero,zero,0x0`

## src/boyact
- KEPT `findChainInJump` (old `func_0014BDF0`) @ 0x0014BDF0
- KEPT `actBoyRun` (old `func_001538C0`) @ 0x001538C0
- KEPT `actBoyTakeWeapon` (old `func_001539B8`) @ 0x001539B8
- KEPT `GetBoyWeaponGObj` (old `func_001545D8`) @ 0x001545D8
- KEPT `actBoyStand` (old `func_001545F0`) @ 0x001545F0
- KEPT `actBoyHang` (old `func_001545F8`) @ 0x001545F8
- KEPT `func_00154648` (old `func_00154648`) @ 0x00154648
- KEPT `func_00154668` (old `func_00154668`) @ 0x00154668
- KEPT `actBoyCall` (old `func_00154770`) @ 0x00154770
- KEPT `actBoyItem` (old `func_00154790`) @ 0x00154790
- KEPT `func_001547A0` (old `func_001547A0`) @ 0x001547A0
- KEPT `func_001547B0` (old `func_001547B0`) @ 0x001547B0
- KEPT `actBoySupportGBLoop` (old `func_00154CB8`) @ 0x00154CB8
- KEPT `actBoySupportGBEnd` (old `func_00154CC8`) @ 0x00154CC8
- KEPT `actBoyHangG3M` (old `func_00154E60`) @ 0x00154E60
- KEPT `IsAbleBoyControl` (old `func_00154E68`) @ 0x00154E68
- KEPT `ACTChkAttackIgnore_BOY` (old `func_00156480`) @ 0x00156480
- REVERTED `InitSwapWeapon` (old `func_001502D8`) @ 0x001502D8 — src/boyact.c:5: redefinition of `struct GObj'
- REVERTED `func_001504D8` (old `func_001504D8`) @ 0x001504D8 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_001538F8` (old `func_001538F8`) @ 0x001538F8 — insn 3: expected `lw	v1,356(v0)` built `lw	v1,1424(v0)`
- REVERTED `actBoyRescueReady` (old `func_00154390`) @ 0x00154390 — insn 5: expected `lw	s0,356(v0)` built `lw	s0,1424(v0)`
- REVERTED `actBoyDitch3mReady` (old `func_00154420`) @ 0x00154420 — insn 1: expected `lw	a0,356(v1)` built `lw	a0,1424(v1)`
- REVERTED `actBoyRescueSrc` (old `func_00154B20`) @ 0x00154B20 — src/boyact.c:15: redefinition of `struct GObj'

## src/commonact
- KEPT `func_00157DA0` (old `func_00157DA0`) @ 0x00157DA0
- KEPT `actCommonRopeClimbEnd1` (old `func_00158928`) @ 0x00158928
- KEPT `actCommonRopeSpecial` (old `func_00159230`) @ 0x00159230
- KEPT `Cling` (old `func_0015B678`) @ 0x0015B678
- KEPT `actCommonCling` (old `func_0015B6D0`) @ 0x0015B6D0
- KEPT `actCommonSlip` (old `func_0015B728`) @ 0x0015B728
- KEPT `func_0015D328` (old `func_0015D328`) @ 0x0015D328
- KEPT `actCommonJump` (old `func_0015D470`) @ 0x0015D470
- KEPT `actCommonDodge` (old `func_0015E7C0`) @ 0x0015E7C0
- KEPT `_ACTDebugPrint` (old `func_0015EE68`) @ 0x0015EE68
- KEPT `E3_LeverCheck` (old `func_0015EF40`) @ 0x0015EF40
- KEPT `actCommonBackhand` (old `func_0015F208`) @ 0x0015F208
- KEPT `func_0015F428` (old `func_0015F428`) @ 0x0015F428
- KEPT `actCommonRevive` (old `func_0015F4B8`) @ 0x0015F4B8
- KEPT `actCommonReviveAir` (old `func_0015F4E0`) @ 0x0015F4E0
- KEPT `actCommonPlay` (old `func_0015F4F0`) @ 0x0015F4F0
- KEPT `actCommonOne` (old `func_0015F518`) @ 0x0015F518
- KEPT `func_0015F5D0` (old `func_0015F5D0`) @ 0x0015F5D0
- REVERTED `WithMailFunc_WayBeginPosError` (old `func_00157BF8`) @ 0x00157BF8 — insn 5: expected `jal	0 <WithMailFunc_WayBeginPosError>` built `jal	8b70 <ContinueCorrectPosition>`
- REVERTED `GetCorrectOrientOfChain` (old `func_00157E68`) @ 0x00157E68 — src/commonact.c:42: too many arguments to function `func_00157DA0'
- REVERTED `actCommonLever` (old `func_00159C38`) @ 0x00159C38 — insn 17: expected `mov.s	$f12,$f20` built `jal	0 <ACTSetPositionWithFitting>`
- REVERTED `funcCommonJumpDircorrect` (old `func_0015D348`) @ 0x0015D348 — insn 0: expected `lui	at,0x41f0` built `dli	a0,0x807c`
- REVERTED `ACT_LAYOUT_GAMEOVER` (old `func_0015F298`) @ 0x0015F298 — insn 1: expected `lui	at,0xbf80` built `dli	a1,0xbff0`
- REVERTED `ACTAdjustPlane` (old `func_0015F2D8`) @ 0x0015F2D8 — src/commonact.c:254: incompatible type for argument 3 of `func_00243B18'
- REVERTED `_ACTMotDirSmzDirect` (old `func_0015F320`) @ 0x0015F320 — insn 5: expected `jal	0 <_ACTMotDirSmzDirect>` built `jal	d0 <ChangeMailInLadder>`
- REVERTED `actCommonDelete` (old `func_0015F550`) @ 0x0015F550 — insn 5: expected `jal	0 <actCommonDelete>` built `jal	24d8 <actCommonRopeCliff>`
- REVERTED `func_0015F650` (old `func_0015F650`) @ 0x0015F650 — src/commonact.c:14: redefinition of `struct GObj'

## src/enemy_act
- KEPT `boss_effect_process` (old `func_0015F698`) @ 0x0015F698
- KEPT `_DoAwait` (old `func_0015F6A8`) @ 0x0015F6A8
- KEPT `_DoAwaitGirl` (old `func_0015F6C0`) @ 0x0015F6C0
- KEPT `actEnemyStand` (old `func_00165158`) @ 0x00165158
- KEPT `actEnemyRun` (old `func_001651C8`) @ 0x001651C8
- KEPT `actEnemyHang` (old `func_001651F8`) @ 0x001651F8
- KEPT `actEnemyCarry` (old `func_00165270`) @ 0x00165270
- KEPT `func_001652A0` (old `func_001652A0`) @ 0x001652A0
- KEPT `func_001652B8` (old `func_001652B8`) @ 0x001652B8
- KEPT `func_001652D0` (old `func_001652D0`) @ 0x001652D0
- KEPT `funcEnemyCarryFail` (old `func_001652F8`) @ 0x001652F8
- KEPT `actEnemyFlagOnFree` (old `func_001653A0`) @ 0x001653A0
- KEPT `afterCommonCarry` (old `func_001653D0`) @ 0x001653D0
- KEPT `actEnemyFlagOnDead` (old `func_001653E8`) @ 0x001653E8
- KEPT `EnemyBrainStatus_Boy` (old `func_00165400`) @ 0x00165400
- KEPT `func_00165488` (old `func_00165488`) @ 0x00165488
- KEPT `actEnemyFlagCheckActive` (old `func_001654C8`) @ 0x001654C8
- KEPT `ACTEnemyForceSwitchToCarry` (old `func_001654D8`) @ 0x001654D8
- KEPT `func_00165B50` (old `func_00165B50`) @ 0x00165B50
- REVERTED `subEnemyCollision` (old `func_0015F9B0`) @ 0x0015F9B0 — insn 13: expected `j	0 <subEnemyCollision>` built `j	168 <subEnemyControl>`
- REVERTED `actEnemyRestart` (old `func_0015FB60`) @ 0x0015FB60 — src/enemy_act.c:6: redefinition of `struct GObj'
- REVERTED `PairSetGeometry` (old `func_0015FBD8`) @ 0x0015FBD8 — src/enemy_act.c:6: redefinition of `struct GObj'
- REVERTED `_ApproachTarget_Way` (old `func_00164EB0`) @ 0x00164EB0 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `func_00164EF8` (old `func_00164EF8`) @ 0x00164EF8 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `func_00164F40` (old `func_00164F40`) @ 0x00164F40 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `func_00164F88` (old `func_00164F88`) @ 0x00164F88 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `func_00164FD0` (old `func_00164FD0`) @ 0x00164FD0 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_00165178` (old `func_00165178`) @ 0x00165178 — insn 0: expected `lui	v0,0x0` built `addiu	sp,sp,-48`
- REVERTED `func_00165348` (old `func_00165348`) @ 0x00165348 — insn 4: expected `jal	0 <func_00165348>` built `jal	1460 <MoveChestForCatchBoy>`
- REVERTED `func_00165418` (old `func_00165418`) @ 0x00165418 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `actEnemy_isNormalEnemy` (old `func_00165540`) @ 0x00165540 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `IsEnemyBrainToBoy` (old `func_00165CE8`) @ 0x00165CE8 — insn 7: expected `jal	0 <IsEnemyBrainToBoy>` built `jal	46c8 <subEnemyBrain_ToBoy>`
- REVERTED `func_00165DC0` (old `func_00165DC0`) @ 0x00165DC0 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `func_00165E08` (old `func_00165E08`) @ 0x00165E08 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`

## src/fieldCollision
- KEPT `GetReflectionElement` (old `func_00165EB8`) @ 0x00165EB8
- KEPT `clip_floor_1` (old `func_00165F88`) @ 0x00165F88
- KEPT `makeCollisionBlockTable` (old `func_00166000`) @ 0x00166000
- REVERTED `MakeCollisionDependGObjList` (old `func_00165E60`) @ 0x00165E60 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `DrawCollisionRay` (old `func_00167230`) @ 0x00167230 — insn 8: expected `j	0 <DrawCollisionRay>` built `j	fb0 <GetEdgeOfFloor>`
- REVERTED `MakeExitAttributeIndex` (old `func_00167258`) @ 0x00167258 — insn 6: expected `j	0 <MakeExitAttributeIndex>` built `j	fb0 <GetEdgeOfFloor>`
- REVERTED `ClipWall` (old `func_00167760`) @ 0x00167760 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `ClipWallEField` (old `func_001683A8`) @ 0x001683A8 — src/fieldCollision.c:80: called object is not a function
- REVERTED `ClipWallBoxStop` (old `func_001683C8`) @ 0x001683C8 — src/fieldCollision.c:82: called object is not a function
- REVERTED `ClipWallAdjustPos` (old `func_001683E8`) @ 0x001683E8 — src/fieldCollision.c:84: called object is not a function
- REVERTED `ClipWallE` (old `func_00168408`) @ 0x00168408 — src/fieldCollision.c:86: called object is not a function
- REVERTED `ClipWallCheckCB` (old `func_00168428`) @ 0x00168428 — src/fieldCollision.c:88: called object is not a function
- REVERTED `ClipWallFieldCheckCB` (old `func_00168448`) @ 0x00168448 — src/fieldCollision.c:90: called object is not a function
- REVERTED `ClipFloor` (old `func_00168468`) @ 0x00168468 — src/fieldCollision.c:92: called object is not a function
- REVERTED `ClipFloorE` (old `func_00168488`) @ 0x00168488 — src/fieldCollision.c:94: called object is not a function
- REVERTED `ClipFloorR` (old `func_001684A8`) @ 0x001684A8 — src/fieldCollision.c:96: called object is not a function
- REVERTED `ClipFloorIH` (old `func_001684C8`) @ 0x001684C8 — src/fieldCollision.c:98: called object is not a function
- REVERTED `ClipFloorCheckCB` (old `func_001684E8`) @ 0x001684E8 — src/fieldCollision.c:102: called object is not a function
- REVERTED `ClipCollision` (old `func_00168510`) @ 0x00168510 — src/fieldCollision.c:104: called object is not a function
- REVERTED `ChangeFieldCollisionDebugMode` (old `func_00168538`) @ 0x00168538 — src/fieldCollision.c:102: called object is not a function
- REVERTED `LoadCollision` (old `func_00168558`) @ 0x00168558 — src/fieldCollision.c:104: called object is not a function
- REVERTED `DrawCollision` (old `func_00168578`) @ 0x00168578 — src/fieldCollision.c:106: called object is not a function
- REVERTED `ClipPlane` (old `func_00168598`) @ 0x00168598 — src/fieldCollision.c:108: called object is not a function
- REVERTED `GetOrientOfWall` (old `func_001685B8`) @ 0x001685B8 — src/fieldCollision.c:114: called object is not a function
- REVERTED `SetSimplePlane` (old `func_001685E0`) @ 0x001685E0 — src/fieldCollision.c:121: called object is not a function

## src/fuzio
- KEPT `fzMagnitude2fv` (old `func_00168A28`) @ 0x00168A28
- KEPT `fzMagnitudeByLine` (old `func_00168A40`) @ 0x00168A40
- KEPT `fzMagnitudeByLineSeg` (old `func_00168A60`) @ 0x00168A60
- KEPT `func_00168A80` (old `func_00168A80`) @ 0x00168A80
- KEPT `func_00168BD0` (old `func_00168BD0`) @ 0x00168BD0
- KEPT `func_00168C18` (old `func_00168C18`) @ 0x00168C18
- KEPT `func_00168C58` (old `func_00168C58`) @ 0x00168C58
- KEPT `func_00168C88` (old `func_00168C88`) @ 0x00168C88
- KEPT `func_0016A130` (old `func_0016A130`) @ 0x0016A130
- KEPT `func_0016A158` (old `func_0016A158`) @ 0x0016A158
- KEPT `func_0016A1B8` (old `func_0016A1B8`) @ 0x0016A1B8
- REVERTED `fzShowV` (old `func_00168650`) @ 0x00168650 — src/fuzio.c:13: `func_00169F80' undeclared (first use in this function)
- REVERTED `fzShowM` (old `func_00168690`) @ 0x00168690 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_00168BA0` (old `func_00168BA0`) @ 0x00168BA0 — src/fuzio.c:43: void value not ignored as it ought to be
- REVERTED `func_0016A1D8` (old `func_0016A1D8`) @ 0x0016A1D8 — insn 18: expected `lui	a0,0x0` built `ld	ra,48(sp)`
- REVERTED `func_0016A240` (old `func_0016A240`) @ 0x0016A240 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_0016A2A0` (old `func_0016A2A0`) @ 0x0016A2A0 — src/fuzio.c:157: void value not ignored as it ought to be
- REVERTED `func_0016A2C8` (old `func_0016A2C8`) @ 0x0016A2C8 — src/fuzio.c:159: void value not ignored as it ought to be
- REVERTED `func_0016A2F8` (old `func_0016A2F8`) @ 0x0016A2F8 — src/fuzio.c:162: void value not ignored as it ought to be
- REVERTED `func_0016A320` (old `func_0016A320`) @ 0x0016A320 — src/fuzio.c:174: void value not ignored as it ought to be

## src/girl_act
- KEPT `GirlBrainClearTarget` (old `func_0016A678`) @ 0x0016A678
- KEPT `func_0016AC10` (old `func_0016AC10`) @ 0x0016AC10
- KEPT `subGirlBrainMain` (old `func_0016AC20`) @ 0x0016AC20
- KEPT `func_001752D0` (old `func_001752D0`) @ 0x001752D0
- KEPT `func_00175308` (old `func_00175308`) @ 0x00175308
- REVERTED `afterGirlHand` (old `func_00175640`) @ 0x00175640 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
- REVERTED `afterGirlPulledGo` (old `func_00175688`) @ 0x00175688 — insn 3: expected `lui	a0,0x0` built `lw	v0,0(sp)`
