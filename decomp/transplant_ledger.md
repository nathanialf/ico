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
