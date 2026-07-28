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
