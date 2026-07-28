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

## src/jimaku
- KEPT `jimakuMgrJump` (old `func_00175C70`) @ 0x00175C70
- KEPT `jimakuMgrEnd` (old `func_00175C90`) @ 0x00175C90
- KEPT `jimakuBegin` (old `func_00175CB0`) @ 0x00175CB0
- KEPT `jimakuEnd` (old `func_00175F60`) @ 0x00175F60
- KEPT `jimakuManager` (old `func_001760F0`) @ 0x001760F0
- KEPT `func_00176150` (old `func_00176150`) @ 0x00176150
- KEPT `func_00176198` (old `func_00176198`) @ 0x00176198
- KEPT `func_001761B8` (old `func_001761B8`) @ 0x001761B8
- KEPT `func_00176398` (old `func_00176398`) @ 0x00176398
- KEPT `func_00176AA0` (old `func_00176AA0`) @ 0x00176AA0
- KEPT `func_00176AE8` (old `func_00176AE8`) @ 0x00176AE8
- KEPT `func_00176B08` (old `func_00176B08`) @ 0x00176B08
- REVERTED `jimakuUndisp` (old `func_00176130`) @ 0x00176130 — src/jimaku.c:8: redefinition of `struct GObj'
- REVERTED `func_00176808` (old `func_00176808`) @ 0x00176808 — src/jimaku.c:172: dereferencing pointer to incomplete type
- REVERTED `func_001769D0` (old `func_001769D0`) @ 0x001769D0 — [§4.2] signed div/shift collapsed to movn

## src/way_sys
- KEPT `avoid_obstacle2` (old `func_00176BB8`) @ 0x00176BB8

## src/way_util
- KEPT `visible_waypoint_of_all_except_temp` (old `func_00178928`) @ 0x00178928
- KEPT `WayUtilWorkAlloc` (old `func_00179040`) @ 0x00179040
- KEPT `WayUtilWorkFree` (old `func_00179050`) @ 0x00179050
- KEPT `set_check_wp` (old `func_00179558`) @ 0x00179558
- KEPT `visible_waypoint_of_all` (old `func_0017A6F8`) @ 0x0017A6F8
- KEPT `bridge_waypoint_side_me` (old `func_0017AC48`) @ 0x0017AC48
- KEPT `waypoint_connect_group_side_me` (old `func_0017ACD8`) @ 0x0017ACD8
- KEPT `func_0017B0D8` (old `func_0017B0D8`) @ 0x0017B0D8
- KEPT `func_0017B1A8` (old `func_0017B1A8`) @ 0x0017B1A8
- KEPT `func_0017B1F0` (old `func_0017B1F0`) @ 0x0017B1F0
- KEPT `func_0017B258` (old `func_0017B258`) @ 0x0017B258
- KEPT `func_0017B288` (old `func_0017B288`) @ 0x0017B288
- REVERTED `get_wp_nearest_bridge_side_me` (old `func_0017A9B8`) @ 0x0017A9B8 — insn 2: expected `jal	0 <get_wp_nearest_bridge_side_me>` built `jal	6e0 <ez_line>`
- REVERTED `func_0017A9D8` (old `func_0017A9D8`) @ 0x0017A9D8 — insn 6: expected `jal	0 <func_0017A9D8>` built `jal	6e0 <ez_line>`
- REVERTED `func_0017B230` (old `func_0017B230`) @ 0x0017B230 — insn 5: expected `lbu	v0,0(v1)` built `lb	v0,0(v1)`

## src/gflag
- KEPT `gflagSave` (old `func_0017B2E8`) @ 0x0017B2E8
- KEPT `gflagLoad` (old `func_0017B318`) @ 0x0017B318
- KEPT `gflagChk` (old `func_0017B358`) @ 0x0017B358
- KEPT `func_0017B4E0` (old `func_0017B4E0`) @ 0x0017B4E0
- KEPT `func_0017B528` (old `func_0017B528`) @ 0x0017B528
- KEPT `func_0017B568` (old `func_0017B568`) @ 0x0017B568
- KEPT `func_0017C818` (old `func_0017C818`) @ 0x0017C818
- KEPT `func_0017C8C0` (old `func_0017C8C0`) @ 0x0017C8C0
- KEPT `func_0017C8F8` (old `func_0017C8F8`) @ 0x0017C8F8
- KEPT `func_0017C930` (old `func_0017C930`) @ 0x0017C930
- KEPT `func_0017C960` (old `func_0017C960`) @ 0x0017C960
- KEPT `func_0017C990` (old `func_0017C990`) @ 0x0017C990
- KEPT `func_0017C9B0` (old `func_0017C9B0`) @ 0x0017C9B0
- KEPT `func_0017CA10` (old `func_0017CA10`) @ 0x0017CA10
- KEPT `func_0017CA18` (old `func_0017CA18`) @ 0x0017CA18
- KEPT `func_0017CA58` (old `func_0017CA58`) @ 0x0017CA58
- KEPT `func_0017CAA0` (old `func_0017CAA0`) @ 0x0017CAA0
- KEPT `func_0017CAE0` (old `func_0017CAE0`) @ 0x0017CAE0
- REVERTED `gflagInit` (old `func_0017B2B8`) @ 0x0017B2B8 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `gflagOn` (old `func_0017B398`) @ 0x0017B398 — src/gflag.c:8: redefinition of `struct GObj'
- REVERTED `func_0017B5A0` (old `func_0017B5A0`) @ 0x0017B5A0 — insn 0: expected `lwc1	$f14,8(a1)` built `addiu	sp,sp,-80`

## src/script
- KEPT `scpPlayEnd` (old `func_0017D098`) @ 0x0017D098
- KEPT `scpTrans` (old `func_0017D0D0`) @ 0x0017D0D0
- KEPT `scpTriggerBallTargetMan` (old `func_0017D0F8`) @ 0x0017D0F8
- KEPT `func_0017D1D0` (old `func_0017D1D0`) @ 0x0017D1D0
- KEPT `scpSubAdpcmPlay` (old `func_0017D270`) @ 0x0017D270
- KEPT `scpSekizou` (old `func_0017D2C8`) @ 0x0017D2C8
- KEPT `scpDispOffAllWithKind` (old `func_0017DC90`) @ 0x0017DC90

## src/st25a
- KEPT `actSt25aQueenAppearChk` (old `func_0017DE98`) @ 0x0017DE98
- KEPT `actConte11` (old `func_0017DEE0`) @ 0x0017DEE0
- KEPT `BoySekikaTexScroll` (old `func_0017E240`) @ 0x0017E240
- KEPT `actSt25aQueenBefore` (old `func_0017E2E8`) @ 0x0017E2E8
- KEPT `actSt25aQueenTalk` (old `func_0017E328`) @ 0x0017E328
- KEPT `actSwordEff` (old `func_0017E4A0`) @ 0x0017E4A0
- KEPT `actSwordEffXL` (old `func_0017E4F0`) @ 0x0017E4F0
- KEPT `actConte11Jimaku` (old `func_0017E570`) @ 0x0017E570
- KEPT `actSt25aQueenDeadEvent` (old `func_0017E588`) @ 0x0017E588
- KEPT `actItouQueenAttackChk` (old `func_0017E5B0`) @ 0x0017E5B0
- KEPT `func_0017E600` (old `func_0017E600`) @ 0x0017E600
- KEPT `func_0017E620` (old `func_0017E620`) @ 0x0017E620
- REVERTED `func_0017E838` (old `func_0017E838`) @ 0x0017E838 — src/st25a.c:42: warning: passing arg 1 of `Generator_Mask' from incompatible pointer type

## src/warpGirl
- KEPT `warpGirlOutStage` (old `func_0017E920`) @ 0x0017E920
- KEPT `warpGirlInit` (old `func_0017E9B0`) @ 0x0017E9B0
- KEPT `func_0017E9D8` (old `func_0017E9D8`) @ 0x0017E9D8
- KEPT `func_0017EA00` (old `func_0017EA00`) @ 0x0017EA00
- KEPT `func_0017EA28` (old `func_0017EA28`) @ 0x0017EA28
- KEPT `func_0017EC50` (old `func_0017EC50`) @ 0x0017EC50
- KEPT `func_0017EC78` (old `func_0017EC78`) @ 0x0017EC78
- KEPT `func_00180580` (old `func_00180580`) @ 0x00180580
- REVERTED `func_00180550` (old `func_00180550`) @ 0x00180550 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/attackhit
- KEPT `AttackCheckSameGroup` (old `func_00180B28`) @ 0x00180B28
- KEPT `AttackGenerate` (old `func_00180F38`) @ 0x00180F38
- KEPT `func_00181BB8` (old `func_00181BB8`) @ 0x00181BB8
- KEPT `func_00181BC0` (old `func_00181BC0`) @ 0x00181BC0
- KEPT `func_00181F38` (old `func_00181F38`) @ 0x00181F38
- KEPT `func_00181F58` (old `func_00181F58`) @ 0x00181F58
- KEPT `func_00181FB0` (old `func_00181FB0`) @ 0x00181FB0
- REVERTED `AttackCenter_WithDir` (old `func_00181960`) @ 0x00181960 — [§branch-direction] opposite branch sense — body inline vs out-of-line
- REVERTED `func_00181BC8` (old `func_00181BC8`) @ 0x00181BC8 — insn 5: expected `jal	0 <func_00181BC8>` built `jal	630 <EnemyAttackCenter>`

## src/brain
- KEPT `OverrideBrainStatusByGObj` (old `func_00182860`) @ 0x00182860
- KEPT `brainStatusDefaultSet` (old `func_00182868`) @ 0x00182868
- KEPT `brainInitGirlSet` (old `func_00182BE8`) @ 0x00182BE8

## src/camera-editor
- KEPT `EnterMenu` (old `func_00182BF8`) @ 0x00182BF8
- KEPT `saveEditedDataBinary` (old `func_00182C08`) @ 0x00182C08
- KEPT `DebugDispBox` (old `func_00182CF0`) @ 0x00182CF0
- KEPT `debug_Arrow` (old `func_001873A0`) @ 0x001873A0
- KEPT `InitCameraEditor` (old `func_001873A8`) @ 0x001873A8
- KEPT `debug_CameraEditor` (old `func_001873B0`) @ 0x001873B0
- REVERTED `menuGroupSelect` (old `func_001848A0`) @ 0x001848A0 — insn 1: expected `j	0 <menuGroupSelect>` built `j	1890 <CameraEdit_DispBoxType2>`
- REVERTED `wakeup_cameraedit` (old `func_00185660`) @ 0x00185660 — insn 0: expected `j	0 <wakeup_cameraedit>` built `j	1cb8 <menuGroupEdit>`
- REVERTED `_CameraEdit_del_box` (old `func_001869F8`) @ 0x001869F8 — src/camera-editor.c:61: `test_camedit' undeclared (first use in this function)
- REVERTED `CameraEdit_del_pin` (old `func_00187280`) @ 0x00187280 — insn 5: expected `jal	0 <CameraEdit_del_pin>` built `jal	3e18 <_CameraEdit_del_pin>`
- REVERTED `CameraEdit_DispBox` (old `func_001872B8`) @ 0x001872B8 — insn 8: expected `jal	0 <CameraEdit_DispBox>` built `jal	3f70 <CameraEdit_add_box>`
- REVERTED `CameraEdit_Reflect` (old `func_00187300`) @ 0x00187300 — insn 0: expected `j	0 <CameraEdit_Reflect>` built `j	d70 <dispCameraGroupType2>`
- REVERTED `CameraEdit_Save` (old `func_00187308`) @ 0x00187308 — src/camera-editor.c:80: subscripted value is neither array nor pointer
- REVERTED `debug_NMarker` (old `func_00187318`) @ 0x00187318 — src/camera-editor.c:81: subscripted value is neither array nor pointer
- REVERTED `debug_Marker` (old `func_00187328`) @ 0x00187328 — src/camera-editor.c:84: incompatible type for argument 3 of `func_00243B18'

## src/camera-ico2
- KEPT `SetCameraZoomOffsetRatio` (old `func_00187F28`) @ 0x00187F28
- KEPT `GetCameraGroupFromPosition` (old `func_00188220`) @ 0x00188220
- KEPT `GetPluralCameraSet` (old `func_001882B0`) @ 0x001882B0
- KEPT `SetCameraTargetPosition` (old `func_001886D0`) @ 0x001886D0
- KEPT `func_0018B098` (old `func_0018B098`) @ 0x0018B098
- KEPT `func_0018B0A0` (old `func_0018B0A0`) @ 0x0018B0A0
- KEPT `func_0018B2F8` (old `func_0018B2F8`) @ 0x0018B2F8
- REVERTED `CameraSetCameraSet` (old `func_001873C0`) @ 0x001873C0 — insn 12: expected `lbu	v0,0(gp)` built `lb	v0,0(gp)`
- REVERTED `initMonitorCamera` (old `func_001878F8`) @ 0x001878F8 — src/camera-ico2.c:16: invalid type argument of `unary *'
- REVERTED `monitorMonitorCamera` (old `func_00187908`) @ 0x00187908 — insn 4: expected `jal	0 <monitorMonitorCamera>` built `jal	5d0 <CameraMove>`
- REVERTED `CameraMove` (old `func_00187990`) @ 0x00187990 — src/camera-ico2.c:23: subscripted value is neither array nor pointer
- REVERTED `ReflectCameraSetBinary` (old `func_001879A8`) @ 0x001879A8 — src/camera-ico2.c:25: subscripted value is neither array nor pointer
- REVERTED `InitPluralCameraSet` (old `func_00188290`) @ 0x00188290 — insn 6: expected `j	0 <InitPluralCameraSet>` built `j	e68 <AddPluralCameraSet>`
- REVERTED `func_0018B700` (old `func_0018B700`) @ 0x0018B700 — insn 6: expected `jal	0 <func_0018B700>` built `jal	4378 <func_0018B738>`

## src/camera-root
- KEPT `ConvertCameraSet` (old `func_0018BE78`) @ 0x0018BE78
- KEPT `GetCameraInfomationFromGlobalPosition` (old `func_0018CA78`) @ 0x0018CA78
- KEPT `InitCamera` (old `func_0018CAA8`) @ 0x0018CAA8
- KEPT `SetCameraMatrix` (old `func_0018CAD8`) @ 0x0018CAD8
- KEPT `Camctrl_ExitEveRock` (old `func_0018CB10`) @ 0x0018CB10
- KEPT `GetCameraDefaultTargetGObj` (old `func_0018CBE0`) @ 0x0018CBE0

## src/camera-set-manager
- KEPT `func_0018CC00` (old `func_0018CC00`) @ 0x0018CC00
- KEPT `func_0018CC10` (old `func_0018CC10`) @ 0x0018CC10
- KEPT `func_0018CEC0` (old `func_0018CEC0`) @ 0x0018CEC0
- KEPT `func_0018CEF0` (old `func_0018CEF0`) @ 0x0018CEF0
- KEPT `func_0018CF58` (old `func_0018CF58`) @ 0x0018CF58
- REVERTED `InitCameraSetManager` (old `func_0018CBE8`) @ 0x0018CBE8 — insn 5: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `func_0018CF00` (old `func_0018CF00`) @ 0x0018CF00 — [§2.7] FP register letter swap ($fA ↔ $fB, otherwise identical)

## src/chain
- KEPT `StartPendulum` (old `func_0018CF80`) @ 0x0018CF80
- KEPT `chain_simulate_term_loop` (old `func_0018CFF0`) @ 0x0018CFF0
- REVERTED `UpdateRootPosition` (old `func_0018CF60`) @ 0x0018CF60 — insn 7: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `pendulum_Process` (old `func_0018DD80`) @ 0x0018DD80 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `InitChainGeo` (old `func_0018DDF0`) @ 0x0018DDF0 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `func_00190298` (old `func_00190298`) @ 0x00190298 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_001902C8` (old `func_001902C8`) @ 0x001902C8 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_001902D8` (old `func_001902D8`) @ 0x001902D8 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_00190318` (old `func_00190318`) @ 0x00190318 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_00190330` (old `func_00190330`) @ 0x00190330 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_00190360` (old `func_00190360`) @ 0x00190360 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_00190388` (old `func_00190388`) @ 0x00190388 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_001903A8` (old `func_001903A8`) @ 0x001903A8 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_001903B8` (old `func_001903B8`) @ 0x001903B8 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_00190430` (old `func_00190430`) @ 0x00190430 — src/chain.c:7: redefinition of `struct GObj'
- REVERTED `func_00190440` (old `func_00190440`) @ 0x00190440 — src/chain.c:7: redefinition of `struct GObj'

## src/ebrain
- KEPT `func_001918A8` (old `func_001918A8`) @ 0x001918A8
- KEPT `func_00191D08` (old `func_00191D08`) @ 0x00191D08
- REVERTED `eBrainGetTarget` (old `func_00190620`) @ 0x00190620 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `eBrainInit` (old `func_00190638`) @ 0x00190638 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `eBrainStatusSet` (old `func_00190648`) @ 0x00190648 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `eBrainSendMes` (old `func_00190658`) @ 0x00190658 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `GetStageFromLabel` (old `func_00190680`) @ 0x00190680 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `eBrainGetTargetGeneratorFromLabelStage` (old `func_00190698`) @ 0x00190698 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `func_001906A8` (old `func_001906A8`) @ 0x001906A8 — src/ebrain.c:5: redefinition of `struct GObj'
- REVERTED `func_001909B8` (old `func_001909B8`) @ 0x001909B8 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## src/enemy-control
- KEPT `func_00192040` (old `func_00192040`) @ 0x00192040
- REVERTED `EnemyCtrlBeforeFunc` (old `func_00191D20`) @ 0x00191D20 — insn 19: expected `<end>` built `sll	zero,zero,0x0`

## src/fightSound
- KEPT `fightSoundProcessMain` (old `func_00192050`) @ 0x00192050
- KEPT `fightSoundProcess` (old `func_00192088`) @ 0x00192088
- KEPT `fightSoundProcessRequestPause` (old `func_00192090`) @ 0x00192090
- KEPT `fightSoundClose` (old `func_00192098`) @ 0x00192098

## src/generator
- KEPT `GetbufpGeneratorPacket` (old `func_001939C8`) @ 0x001939C8
- KEPT `GetsizeGeneratorPacket` (old `func_001939D8`) @ 0x001939D8
- REVERTED `Generator_QuickCall` (old `func_00192B58`) @ 0x00192B58 — src/generator.c:5: redefinition of `struct GObj'
- REVERTED `Generator_Call` (old `func_00193818`) @ 0x00193818 — src/generator.c:5: redefinition of `struct GObj'
- REVERTED `Generator_ResetCount` (old `func_00193830`) @ 0x00193830 — src/generator.c:5: redefinition of `struct GObj'
- REVERTED `Generator_Mask` (old `func_00193848`) @ 0x00193848 — src/generator.c:5: redefinition of `struct GObj'
- REVERTED `Generator_MaskOff` (old `func_00193860`) @ 0x00193860 — src/generator.c:5: redefinition of `struct GObj'

## src/gv
- KEPT `_InterGV` (old `func_001939E0`) @ 0x001939E0
- KEPT `_DistGV` (old `func_00193CE8`) @ 0x00193CE8
- KEPT `func_00193F48` (old `func_00193F48`) @ 0x00193F48
- KEPT `_RotGV` (old `func_00193F78`) @ 0x00193F78
- REVERTED `GetMatrixDirectionToZ` (old `func_00193A00`) @ 0x00193A00 — src/gv.c:5: redefinition of `struct GObj'
- REVERTED `_InterRotGV` (old `func_00193A58`) @ 0x00193A58 — src/gv.c:5: redefinition of `struct GObj'
- REVERTED `func_00193EC8` (old `func_00193EC8`) @ 0x00193EC8 — src/gv.c:6: redefinition of `struct GObj'

## src/hand-camera
- KEPT `func_001947D0` (old `func_001947D0`) @ 0x001947D0
- KEPT `func_00194808` (old `func_00194808`) @ 0x00194808
- KEPT `func_001948A8` (old `func_001948A8`) @ 0x001948A8
- KEPT `func_00194960` (old `func_00194960`) @ 0x00194960
- REVERTED `RotateAccordingToStick_PatternThree` (old `func_00194360`) @ 0x00194360 — insn 13: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `ClearHandCameraCorrect` (old `func_001943C8`) @ 0x001943C8 — src/hand-camera.c:15: invalid use of void expression
- REVERTED `func_00194590` (old `func_00194590`) @ 0x00194590 — insn 2: expected `jal	0 <func_00194590>` built `jal	1a8 <HandCameraCorrect>`
- REVERTED `func_00194630` (old `func_00194630`) @ 0x00194630 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_00194840` (old `func_00194840`) @ 0x00194840 — insn 15: expected `jal	0 <func_00194840>` built `jal	1a8 <HandCameraCorrect>`
- REVERTED `func_001948F0` (old `func_001948F0`) @ 0x001948F0 — insn 13: expected `mov.s	$f1,$f0` built `mtc1	v0,$f1`

## src/mail-add-data
- KEPT `InitMailAdditionalData` (old `func_001949B8`) @ 0x001949B8
- KEPT `ClearMailAdditionalData` (old `func_00194DC0`) @ 0x00194DC0
- KEPT `func_00194E28` (old `func_00194E28`) @ 0x00194E28
- KEPT `func_00194EA8` (old `func_00194EA8`) @ 0x00194EA8
- KEPT `func_00195208` (old `func_00195208`) @ 0x00195208
- KEPT `func_00195230` (old `func_00195230`) @ 0x00195230
- KEPT `func_00195350` (old `func_00195350`) @ 0x00195350
- REVERTED `func_00194FE8` (old `func_00194FE8`) @ 0x00194FE8 — insn 1: expected `j	0 <func_00194FE8>` built `j	7e8 <func_001951A0>`
- REVERTED `func_001951A0` (old `func_001951A0`) @ 0x001951A0 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

## src/poly-flat
- KEPT `before_DrawPolygon` (old `func_00195378`) @ 0x00195378
- KEPT `func_00197078` (old `func_00197078`) @ 0x00197078

## src/act_bird
- KEPT `birdBeforeFunc` (old `func_001970E0`) @ 0x001970E0
- KEPT `Debug_StickControl` (old `func_00197330`) @ 0x00197330
- KEPT `BirdDL` (old `func_001973A8`) @ 0x001973A8
- REVERTED `interp_vector_sa` (old `func_00197080`) @ 0x00197080 — src/act_bird.c:5: redefinition of `struct GObj'

## src/gather_effect

## src/itou_boss
- KEPT `bossCtrlBeforeFunc` (old `func_00198110`) @ 0x00198110
- REVERTED `effect_end_func` (old `func_00197FE8`) @ 0x00197FE8 — insn 5: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `gene_enemy` (old `func_00198218`) @ 0x00198218 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `BossCtrlGeo` (old `func_00198328`) @ 0x00198328 — insn 3: expected `sb	v0,0(v1)` built `sw	v0,0(v1)`

## src/itou_gflag
- KEPT `itouGflagLoad` (old `func_00198420`) @ 0x00198420
- KEPT `itouGflagSave` (old `func_00198428`) @ 0x00198428
- KEPT `func_00198430` (old `func_00198430`) @ 0x00198430

## src/itou_sub
- KEPT `m33_to_quat` (old `func_00198678`) @ 0x00198678
- KEPT `apply_matrix_w1` (old `func_001986D8`) @ 0x001986D8
- KEPT `ico_m33_to_quat` (old `func_00198710`) @ 0x00198710
- QUARANTINED `lw_pos_to_ico_pos` (old `func_001986A8`) @ 0x001986A8 — vu0-inline-asm

## src/lightning
- KEPT `set_vertex` (old `func_00199790`) @ 0x00199790
- KEPT `apply_m34` (old `func_00199998`) @ 0x00199998
- REVERTED `func_00199A08` (old `func_00199A08`) @ 0x00199A08 — src/lightning.c:6: redefinition of `struct GObj'

## src/queen
- KEPT `queenBallBeforeFunc` (old `func_0019C010`) @ 0x0019C010
- REVERTED `func_0019A9A0` (old `func_0019A9A0`) @ 0x0019A9A0 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019AE50` (old `func_0019AE50`) @ 0x0019AE50 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019B7F8` (old `func_0019B7F8`) @ 0x0019B7F8 — src/queen.c:31: `func_0019BCE0' undeclared (first use in this function)
- REVERTED `func_0019B888` (old `func_0019B888`) @ 0x0019B888 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019B8E8` (old `func_0019B8E8`) @ 0x0019B8E8 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019B910` (old `func_0019B910`) @ 0x0019B910 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019B938` (old `func_0019B938`) @ 0x0019B938 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019B948` (old `func_0019B948`) @ 0x0019B948 — src/queen.c:33: subscripted value is neither array nor pointer
- REVERTED `func_0019BA60` (old `func_0019BA60`) @ 0x0019BA60 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019BAA8` (old `func_0019BAA8`) @ 0x0019BAA8 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019BB40` (old `func_0019BB40`) @ 0x0019BB40 — src/queen.c:5: redefinition of `struct GObj'
- REVERTED `func_0019BC58` (old `func_0019BC58`) @ 0x0019BC58 — src/queen.c:5: redefinition of `struct GObj'

## src/queen_barrier_disp
- REVERTED `makeRefractST` (old `func_0019C798`) @ 0x0019C798 — insn 0: expected `lhu	v0,0(gp)` built `lw	v0,0(gp)`

- REVERTED `nearest_waypoint_by_lineseg` (old `func_0017A230`) @ 0x0017A230 — extra trailing pad nop appears once all 13 siblings are coalesced (alignment/scheduling shift); passed isolated quick_diff, broke the full-ELF SHA gate (post-hoc, bisected)

## src/stage_orient
- KEPT `GetStageDifferenceMatrix` (old `func_0019CF70`) @ 0x0019CF70
- KEPT `StageOrientGet2` (old `func_0019CF78`) @ 0x0019CF78

## ito/mpeg/mv_main
- KEPT `initAll` (old `func_0019D9D8`) @ 0x0019D9D8
- KEPT `movie_init` (old `func_0019DA98`) @ 0x0019DA98
- KEPT `movie_end` (old `func_0019DAC8`) @ 0x0019DAC8
- KEPT `movie_proc` (old `func_0019DB08`) @ 0x0019DB08
- REVERTED `proceedAudio` (old `func_0019D9C8`) @ 0x0019D9C8 — insn 0: expected `j	0 <proceedAudio>` built `j	78 <initAll>`
- REVERTED `readMpeg` (old `func_0019D9D0`) @ 0x0019D9D0 — insn 0: expected `j	0 <readMpeg>` built `j	68 <proceedAudio>`

## ito/mpeg/mv_readbuf
- KEPT `readBufDelete` (old `func_0019DB70`) @ 0x0019DB70
- KEPT `readBufCreate` (old `func_0019DBA8`) @ 0x0019DBA8
- KEPT `readBufEndPut` (old `func_0019DBE8`) @ 0x0019DBE8
- KEPT `readBufEndGet` (old `func_0019DD38`) @ 0x0019DD38

## ito/mpeg/mv_strfile
- KEPT `strFileOpen` (old `func_0019DD40`) @ 0x0019DD40
- KEPT `func_0019E150` (old `func_0019E150`) @ 0x0019E150
- KEPT `func_0019E160` (old `func_0019E160`) @ 0x0019E160
- KEPT `func_0019E1A0` (old `func_0019E1A0`) @ 0x0019E1A0

## ito/mpeg/mv_videodec
- KEPT `free_buf` (old `func_0019E1D0`) @ 0x0019E1D0
- KEPT `videoDecCreate` (old `func_0019E1D8`) @ 0x0019E1D8
- KEPT `videoDecBeginPut` (old `func_0019E228`) @ 0x0019E228
- KEPT `videoDecFlush` (old `func_0019E2A0`) @ 0x0019E2A0
- KEPT `videoCallback` (old `func_0019E2D0`) @ 0x0019E2D0
- KEPT `decBitStrm0` (old `func_0019E2F0`) @ 0x0019E2F0
- REVERTED `videoDecEndPut` (old `func_0019E278`) @ 0x0019E278 — insn 1: expected `lui	a0,0x0` built `addiu	a0,gp,0`

## ito/mpeg/mv_vobuf
- KEPT `func_0019E310` (old `func_0019E310`) @ 0x0019E310
- KEPT `voBufIsFull` (old `func_0019E4E8`) @ 0x0019E4E8
- KEPT `voBufGetData` (old `func_0019E508`) @ 0x0019E508
- REVERTED `voBufCreate` (old `func_0019E350`) @ 0x0019E350 — insn 4: expected `jal	0 <voBufCreate>` built `jal	1d8 <voBufIsFull>`
- REVERTED `voBufReset` (old `func_0019E4E0`) @ 0x0019E4E0 — insn 0: expected `j	0 <voBufReset>` built `j	40 <voBufCreate>`

## src/DObj
- KEPT `allocObjectData` (old `func_0019E628`) @ 0x0019E628
- KEPT `func_0019F4E0` (old `func_0019F4E0`) @ 0x0019F4E0
- REVERTED `FreeDObj` (old `func_0019EF10`) @ 0x0019EF10 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `func_0019F530` (old `func_0019F530`) @ 0x0019F530 — src/DObj.c:5: redefinition of `struct GObj'

## src/StageManager
- KEPT `stage_initialize` (old `func_0019F758`) @ 0x0019F758
- KEPT `stgmgrForceSwitchWithFade` (old `func_001A0010`) @ 0x001A0010
- KEPT `stgmgrForceSwitchWithFadeColor` (old `func_001A0028`) @ 0x001A0028
- REVERTED `stop_free_resources` (old `func_0019F6A8`) @ 0x0019F6A8 — src/StageManager.c:7: conflicting types for `D_00612730'
- REVERTED `StageManager` (old `func_0019FF98`) @ 0x0019FF98 — insn 2: expected `j	0 <StageManager>` built `j	900 <stgmgrForceSwitch>`

## src/backStage
- KEPT `backStageProcessOutStage` (old `func_001A0038`) @ 0x001A0038
- KEPT `backStageProcessMain` (old `func_001A0040`) @ 0x001A0040
- KEPT `routeSetPos` (old `func_001A0090`) @ 0x001A0090
- KEPT `func_001A1008` (old `func_001A1008`) @ 0x001A1008

## src/charFileManager
- KEPT `InitCharFileManager` (old `func_001A1020`) @ 0x001A1020
- KEPT `ResetCharFileManager` (old `func_001A1028`) @ 0x001A1028
- REVERTED `ReadModelFile` (old `func_001A1030`) @ 0x001A1030 — src/charFileManager.c:23: dereferencing pointer to incomplete type
- REVERTED `ReadVolumeModelFile` (old `func_001A10B0`) @ 0x001A10B0 — src/charFileManager.c:26: dereferencing pointer to incomplete type
- REVERTED `CSVSYSTEM_ReadCharFiles` (old `func_001A26E0`) @ 0x001A26E0 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/debug
- KEPT `debug_LogPrintf` (old `func_001A2E10`) @ 0x001A2E10
- KEPT `func_001A2E28` (old `func_001A2E28`) @ 0x001A2E28
- KEPT `debug_VariableInit` (old `func_001A31C0`) @ 0x001A31C0
- REVERTED `debug_Assert` (old `func_001A2D58`) @ 0x001A2D58 — insn 7: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `debug_openLog` (old `func_001A2D78`) @ 0x001A2D78 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_001A3340` (old `func_001A3340`) @ 0x001A3340 — insn 19: expected `j	0 <func_001A3340>` built `j	ee0 <debug_PrintCharacter>`
- REVERTED `draw_batsu` (old `func_001A43F0`) @ 0x001A43F0 — insn 0: expected `j	0 <draw_batsu>` built `j	14c8 <debug_FlushFont>`

## src/debug_exception
- KEPT `traceLine` (old `func_001A6A30`) @ 0x001A6A30
- KEPT `dispSource` (old `func_001A6AA0`) @ 0x001A6AA0
- KEPT `debug_assertMessage` (old `func_001A6E28`) @ 0x001A6E28
- KEPT `func_001A7820` (old `func_001A7820`) @ 0x001A7820
- KEPT `func_001A7838` (old `func_001A7838`) @ 0x001A7838

## src/debug_menu
- KEPT `init_debug_menu` (old `func_001A9D88`) @ 0x001A9D88
- KEPT `func_001A9EE8` (old `func_001A9EE8`) @ 0x001A9EE8
- KEPT `func_001A9F20` (old `func_001A9F20`) @ 0x001A9F20
- KEPT `func_001AA098` (old `func_001AA098`) @ 0x001AA098
- KEPT `func_001AA210` (old `func_001AA210`) @ 0x001AA210
- KEPT `func_001AA258` (old `func_001AA258`) @ 0x001AA258
- KEPT `func_001AA4E8` (old `func_001AA4E8`) @ 0x001AA4E8
- KEPT `func_001AA4F0` (old `func_001AA4F0`) @ 0x001AA4F0
- KEPT `func_001AA5B8` (old `func_001AA5B8`) @ 0x001AA5B8
- KEPT `func_001AA5C0` (old `func_001AA5C0`) @ 0x001AA5C0
- KEPT `func_001AA660` (old `func_001AA660`) @ 0x001AA660
- KEPT `func_001AA688` (old `func_001AA688`) @ 0x001AA688
- REVERTED `func_001AA608` (old `func_001AA608`) @ 0x001AA608 — insn 0: expected `addiu	v0,zero,208` built `addiu	v0,zero,832`
- REVERTED `func_001AA638` (old `func_001AA638`) @ 0x001AA638 — insn 0: expected `addiu	v1,zero,208` built `addiu	v1,zero,832`

## src/gamesys
- KEPT `gamesysObjInfoSave` (old `func_001AAEA0`) @ 0x001AAEA0
- KEPT `gamesysObjInfoEmptyAreaSearch` (old `func_001AAEE8`) @ 0x001AAEE8
- KEPT `gamesysCharacterInfoLoad` (old `func_001AB150`) @ 0x001AB150
- KEPT `gamesysNObjInfoInit` (old `func_001AB170`) @ 0x001AB170
- KEPT `gamesysObjInfoStageInitPosSaveUnlock` (old `func_001AB1B8`) @ 0x001AB1B8
- KEPT `gamesysObjInfoUniqDataSet` (old `func_001AB2F8`) @ 0x001AB2F8
- KEPT `gamesysObjInfoPosNewStageSet` (old `func_001AB338`) @ 0x001AB338
- KEPT `gamesysObjInfoGet` (old `func_001AB378`) @ 0x001AB378
- KEPT `gamesysVersionLoad` (old `func_001ABF58`) @ 0x001ABF58
- REVERTED `gamesysObjInfoInit` (old `func_001AAE70`) @ 0x001AAE70 — insn 11: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `gamesysObjInfoLoad` (old `func_001AAEC0`) @ 0x001AAEC0 — insn 1: expected `lui	at,0x3f80` built `dli	a1,0xffc0`
- REVERTED `gamesysObjInfoStageInitFlagCls` (old `func_001AB190`) @ 0x001AB190 — insn 5: expected `ld	ra,0(sp)` built `jal	0 <gamesysObjInfoInit>`
- REVERTED `gamesysGeneratorInfoSave` (old `func_001AC300`) @ 0x001AC300 — insn 2: expected `jal	0 <gamesysGeneratorInfoSave>` built `jal	800 <gamesysMemoryHandlerWrite>`

## src/haveParentSimpleObj
- KEPT `func_001AD740` (old `func_001AD740`) @ 0x001AD740
- KEPT `func_001ADB70` (old `func_001ADB70`) @ 0x001ADB70
- KEPT `func_001ADB88` (old `func_001ADB88`) @ 0x001ADB88
- KEPT `func_001ADBC0` (old `func_001ADBC0`) @ 0x001ADBC0
- KEPT `func_001ADCB0` (old `func_001ADCB0`) @ 0x001ADCB0
- KEPT `func_001AE1B8` (old `func_001AE1B8`) @ 0x001AE1B8
- KEPT `func_001AE258` (old `func_001AE258`) @ 0x001AE258
- KEPT `func_001AE308` (old `func_001AE308`) @ 0x001AE308
- KEPT `func_001AE370` (old `func_001AE370`) @ 0x001AE370
- KEPT `func_001AE3B0` (old `func_001AE3B0`) @ 0x001AE3B0
- KEPT `func_001AE3E8` (old `func_001AE3E8`) @ 0x001AE3E8
- REVERTED `func_001AE188` (old `func_001AE188`) @ 0x001AE188 — insn 6: expected `lhu	v0,68(v0)` built `lh	v0,68(v0)`
- REVERTED `func_001AE210` (old `func_001AE210`) @ 0x001AE210 — insn 16: expected `j	0 <func_001AE210>` built `j	1d00 <func_001AE1B8>`
- REVERTED `func_001AE2C0` (old `func_001AE2C0`) @ 0x001AE2C0 — insn 16: expected `j	0 <func_001AE2C0>` built `j	1d00 <func_001AE1B8>`
- REVERTED `func_001AE420` (old `func_001AE420`) @ 0x001AE420 — insn 6: expected `jal	0 <func_001AE420>` built `jal	1a20 <func_001ADED8>`

## src/icoMisc
- KEPT `InitIcoMisc` (old `func_001AE808`) @ 0x001AE808
- KEPT `DispIcoMisc` (old `func_001AE830`) @ 0x001AE830
- KEPT `func_001AE8A0` (old `func_001AE8A0`) @ 0x001AE8A0
- KEPT `func_001AEA50` (old `func_001AEA50`) @ 0x001AEA50
- KEPT `func_001AEA58` (old `func_001AEA58`) @ 0x001AEA58
- KEPT `func_001AEA60` (old `func_001AEA60`) @ 0x001AEA60
- REVERTED `ExitIcoMisc` (old `func_001AE880`) @ 0x001AE880 — insn 1: expected `sll	a0,a0,0x2` built `lbu	v1,0(gp)`
- REVERTED `func_001AE8F0` (old `func_001AE8F0`) @ 0x001AE8F0 — src/icoMisc.c:44: `func_001AE8F0_FnPtr' undeclared (first use in this function)
- REVERTED `func_001AE948` (old `func_001AE948`) @ 0x001AE948 — src/icoMisc.c:49: syntax error before `fn'
- REVERTED `func_001AE9A8` (old `func_001AE9A8`) @ 0x001AE9A8 — src/icoMisc.c:55: incompatible types in assignment
- REVERTED `func_001AE9F0` (old `func_001AE9F0`) @ 0x001AE9F0 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

## src/kanban
- KEPT `init_textures_of_specified_property` (old `func_001AFB90`) @ 0x001AFB90
- KEPT `kanbanReqAllDel` (old `func_001B04E0`) @ 0x001B04E0
- KEPT `kanbanReqAllDelFade` (old `func_001B0518`) @ 0x001B0518
- KEPT `kanbanExec` (old `func_001B0538`) @ 0x001B0538
- KEPT `func_001B0570` (old `func_001B0570`) @ 0x001B0570
- REVERTED `func_001B0A38` (old `func_001B0A38`) @ 0x001B0A38 — src/kanban.c:90: incompatible types in assignment
- REVERTED `func_001B0A68` (old `func_001B0A68`) @ 0x001B0A68 — insn 0: expected `lui	a1,0xffff` built `addiu	a0,zero,400`

## src/kanbanBoot
- KEPT `kanbanBootInit` (old `func_001B0AB0`) @ 0x001B0AB0
- REVERTED `kanbanBootMcCheck` (old `func_001B0A80`) @ 0x001B0A80 — insn 0: expected `lui	a1,0xffff` built `addiu	a0,zero,401`
- REVERTED `kanbanBootMain` (old `func_001B0A98`) @ 0x001B0A98 — insn 0: expected `lui	a1,0xffff` built `addiu	a0,zero,399`

## src/layout_action
- KEPT `_la_set_current_port_lock_2` (old `func_001B4EC0`) @ 0x001B4EC0
- KEPT `_la_set_current_port_new` (old `func_001B4EF0`) @ 0x001B4EF0
- KEPT `la_vibe_select` (old `func_001B4F20`) @ 0x001B4F20
- KEPT `la_title_continue_or_new` (old `func_001B4F58`) @ 0x001B4F58
- KEPT `la_title_new_game_only` (old `func_001B4FC0`) @ 0x001B4FC0
- KEPT `la_load_game_memory_card_check` (old `func_001B5118`) @ 0x001B5118
- KEPT `la_mc_load_current_slot_select` (old `func_001B5158`) @ 0x001B5158
- KEPT `la_load_confirm_no_memory_card` (old `func_001B5220`) @ 0x001B5220
- KEPT `la_save_game_memory_card_check` (old `func_001B5610`) @ 0x001B5610
- KEPT `progressive_bar` (old `func_001B5618`) @ 0x001B5618
- KEPT `la_save_start_check` (old `func_001B56D0`) @ 0x001B56D0
- KEPT `la_save_confirm_overwrite` (old `func_001B5728`) @ 0x001B5728
- KEPT `la_format_confirm` (old `func_001B5768`) @ 0x001B5768
- KEPT `la_system_save_processing` (old `func_001B5770`) @ 0x001B5770
- KEPT `func_001B5788` (old `func_001B5788`) @ 0x001B5788
- REVERTED `_la_set_current_port_2` (old `func_001B4E78`) @ 0x001B4E78 — insn 1: expected `lw	v0,0(gp)` built `addiu	v0,gp,0`

## src/layout_texture
- KEPT `display_texture_fade_cancel_chk` (old `func_001B5870`) @ 0x001B5870
- KEPT `func_001B59D0` (old `func_001B59D0`) @ 0x001B59D0
- KEPT `lt_set_item_select_func` (old `func_001B7040`) @ 0x001B7040
- REVERTED `texture_fading` (old `func_001B5998`) @ 0x001B5998 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

## src/sceneManager
- KEPT `GetRealModelId` (old `func_001B7250`) @ 0x001B7250
- KEPT `InitStageLight` (old `func_001B7280`) @ 0x001B7280
- KEPT `initSceneGObj` (old `func_001B7288`) @ 0x001B7288
- KEPT `initParentLink` (old `func_001B7290`) @ 0x001B7290
- KEPT `CreateLayoutedGObj` (old `func_001B7CD8`) @ 0x001B7CD8
- KEPT `GetStageStartInfo` (old `func_001B7FC8`) @ 0x001B7FC8

## src/staffroll
- KEPT `staffRollStart` (old `func_001B8110`) @ 0x001B8110
- KEPT `staffRollNameOut` (old `func_001B81A8`) @ 0x001B81A8
- REVERTED `func_001B84C8` (old `func_001B84C8`) @ 0x001B84C8 — src/staffroll.c:83: incompatible types in assignment

## src/a_p_1
- KEPT `InitAP1` (old `func_001B86C0`) @ 0x001B86C0
- REVERTED `zAxisRotFitting` (old `func_001B8CE0`) @ 0x001B8CE0 — src/a_p_1.c:57: warning: passing arg 3 of `func_0010DCF8' makes pointer from integer without a cast
- REVERTED `fitToCol` (old `func_001B8DC8`) @ 0x001B8DC8 — src/a_p_1.c:59: warning: passing arg 3 of `func_0010DCF8' makes pointer from integer without a cast

## src/act_a_p_1
- KEPT `SetAP1DeadStatus` (old `func_001BA668`) @ 0x001BA668
- KEPT `IsActCharDead` (old `func_001BA770`) @ 0x001BA770
- REVERTED `standAI` (old `func_001BA090`) @ 0x001BA090 — src/act_a_p_1.c:6: redefinition of `struct GObj'
- REVERTED `walkAI` (old `func_001BA2E0`) @ 0x001BA2E0 — src/act_a_p_1.c:5: redefinition of `struct GObj'
- REVERTED `SleepAP1` (old `func_001BA530`) @ 0x001BA530 — src/act_a_p_1.c:5: redefinition of `struct GObj'
- REVERTED `WakeUpAP1` (old `func_001BA5C0`) @ 0x001BA5C0 — src/act_a_p_1.c:5: redefinition of `struct GObj'
- REVERTED `subAP1BrainMain` (old `func_001BA5D0`) @ 0x001BA5D0 — src/act_a_p_1.c:5: redefinition of `struct GObj'
- REVERTED `hitProc` (old `func_001BA5E0`) @ 0x001BA5E0 — src/act_a_p_1.c:5: redefinition of `struct GObj'
- REVERTED `AP1BeforeFunc` (old `func_001BA6B0`) @ 0x001BA6B0 — src/act_a_p_1.c:6: redefinition of `struct GObj'
- REVERTED `actAP1Start` (old `func_001BA6F0`) @ 0x001BA6F0 — src/act_a_p_1.c:6: redefinition of `struct GObj'
- REVERTED `SetAP1HostGObj` (old `func_001BA7C0`) @ 0x001BA7C0 — src/act_a_p_1.c:7: redefinition of `struct GObj'
- REVERTED `SetAP1PriorLevel` (old `func_001BA7E8`) @ 0x001BA7E8 — src/act_a_p_1.c:7: redefinition of `struct GObj'
- REVERTED `GetAP1AIMode` (old `func_001BA838`) @ 0x001BA838 — src/act_a_p_1.c:7: redefinition of `struct GObj'

## src/actressLight
- KEPT `func_001BAEE0` (old `func_001BAEE0`) @ 0x001BAEE0
- KEPT `func_001BB390` (old `func_001BB390`) @ 0x001BB390
- KEPT `func_001BB7E0` (old `func_001BB7E0`) @ 0x001BB7E0
- KEPT `func_001BB800` (old `func_001BB800`) @ 0x001BB800
- KEPT `func_001BB810` (old `func_001BB810`) @ 0x001BB810

## src/attackCheckBoundary
- KEPT `InitAttackCheckBoundaryManagerGeo` (old `func_001BB860`) @ 0x001BB860
- KEPT `AttackCheckBoundaryManagerGeo` (old `func_001BB888`) @ 0x001BB888
- KEPT `AttackCheckBoundaryManagerDL` (old `func_001BB8B0`) @ 0x001BB8B0
- KEPT `GetAttackCheckBoundaryRadius` (old `func_001BBE48`) @ 0x001BBE48
- KEPT `switchReleaseSE` (old `func_001BBF78`) @ 0x001BBF78
- KEPT `func_001BC0A8` (old `func_001BC0A8`) @ 0x001BC0A8
- KEPT `func_001BC0B0` (old `func_001BC0B0`) @ 0x001BC0B0
- KEPT `func_001BC9A0` (old `func_001BC9A0`) @ 0x001BC9A0
- KEPT `func_001BC9A8` (old `func_001BC9A8`) @ 0x001BC9A8
- KEPT `func_001BC9B0` (old `func_001BC9B0`) @ 0x001BC9B0
- KEPT `func_001BC9B8` (old `func_001BC9B8`) @ 0x001BC9B8
- KEPT `func_001BC9C0` (old `func_001BC9C0`) @ 0x001BC9C0
- REVERTED `AttackCheckBoundaryBeforeFunc` (old `func_001BB820`) @ 0x001BB820 — [§3.3 / 8.6] branch-likely mnemonic mismatch (beq↔beql / bne↔bnel)
- REVERTED `CreateAttackCheckBoundary` (old `func_001BBE50`) @ 0x001BBE50 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `GetAttackCheckBoundaryManagerStatus` (old `func_001BBEA0`) @ 0x001BBEA0 — src/attackCheckBoundary.c:6: redefinition of `struct GObj'
- REVERTED `func_001BBFD0` (old `func_001BBFD0`) @ 0x001BBFD0 — src/attackCheckBoundary.c:7: redefinition of `struct GObj'
- REVERTED `func_001BC088` (old `func_001BC088`) @ 0x001BC088 — src/attackCheckBoundary.c:7: redefinition of `struct GObj'
- REVERTED `func_001BC098` (old `func_001BC098`) @ 0x001BC098 — src/attackCheckBoundary.c:7: redefinition of `struct GObj'

## src/switch
- KEPT `SetSwitchState` (old `func_001C0838`) @ 0x001C0838
- KEPT `SetFloorLeverWithNodePoint` (old `func_001C0840`) @ 0x001C0840
- KEPT `CanFloorLeverPull` (old `func_001C0848`) @ 0x001C0848
- KEPT `InitFloorLeverGeo` (old `func_001C0850`) @ 0x001C0850
- KEPT `GetFloorLeverAngle` (old `func_001C0858`) @ 0x001C0858
- KEPT `CanWallLeverPull` (old `func_001C0870`) @ 0x001C0870
- KEPT `func_001C0BF8` (old `func_001C0BF8`) @ 0x001C0BF8
- REVERTED `SetWallLeverWithNodePoint` (old `func_001C0860`) @ 0x001C0860 — src/switch.c:5: redefinition of `struct GObj'
- REVERTED `InitWallLeverGeo` (old `func_001C09B0`) @ 0x001C09B0 — src/switch.c:6: redefinition of `struct GObj'
- REVERTED `initParentize` (old `func_001C0AD8`) @ 0x001C0AD8 — src/switch.c:6: redefinition of `struct GObj'
- REVERTED `func_001C0BE0` (old `func_001C0BE0`) @ 0x001C0BE0 — src/switch.c:6: redefinition of `struct GObj'
- REVERTED `func_001C0D50` (old `func_001C0D50`) @ 0x001C0D50 — src/switch.c:6: redefinition of `struct GObj'

## src/boy
- REVERTED `func_001C2098` (old `func_001C2098`) @ 0x001C2098 — src/boy.c:5: redefinition of `struct GObj'

## src/cage
- KEPT `SetCageFixGeometry` (old `func_001C2170`) @ 0x001C2170
- REVERTED `HotInitCageGeo` (old `func_001C22F0`) @ 0x001C22F0 — src/cage.c:6: redefinition of `struct GObj'

## src/cageFix
- KEPT `func_001C2EC8` (old `func_001C2EC8`) @ 0x001C2EC8
- KEPT `func_001C2F20` (old `func_001C2F20`) @ 0x001C2F20
- REVERTED `CageFixGeo` (old `func_001C2DF8`) @ 0x001C2DF8 — src/cageFix.c:5: redefinition of `struct GObj'
- REVERTED `InitCageFixGeo` (old `func_001C2EB8`) @ 0x001C2EB8 — src/cageFix.c:5: redefinition of `struct GObj'
- REVERTED `func_001C2F10` (old `func_001C2F10`) @ 0x001C2F10 — src/cageFix.c:6: redefinition of `struct GObj'

## src/candle
- KEPT `CandleDL` (old `func_001C2FE8`) @ 0x001C2FE8
- REVERTED `InitCandleGeo` (old `func_001C2FA0`) @ 0x001C2FA0 — src/candle.c:5: redefinition of `struct GObj'
- REVERTED `CandleGeo` (old `func_001C2FF0`) @ 0x001C2FF0 — src/candle.c:5: redefinition of `struct GObj'
- REVERTED `DeleteLayoutedCandleParticleEffect` (old `func_001C3130`) @ 0x001C3130 — src/candle.c:5: redefinition of `struct GObj'

## src/chandelier
- KEPT `func_001C34B8` (old `func_001C34B8`) @ 0x001C34B8
- KEPT `func_001C36E0` (old `func_001C36E0`) @ 0x001C36E0
- REVERTED `InitChandelierGeo` (old `func_001C3470`) @ 0x001C3470 — src/chandelier.c:5: redefinition of `struct GObj'

## src/clipCollisionManager
- KEPT `CreateClipCollisionManagerGObj` (old `func_001C3970`) @ 0x001C3970

## src/clothAnimation
- KEPT `proc` (old `func_001C8A00`) @ 0x001C8A00
- KEPT `getCloth4D_postProcess` (old `func_001C8B20`) @ 0x001C8B20
- KEPT `GetCloth4D` (old `func_001C8B48`) @ 0x001C8B48
- KEPT `InitChainVelocity` (old `func_001C8DE8`) @ 0x001C8DE8
- KEPT `DeleteChainExtendedWeight` (old `func_001C8E08`) @ 0x001C8E08
- KEPT `GetChainNodeID` (old `func_001C8E30`) @ 0x001C8E30

## src/clothTest
- KEPT `InitClothTestGeo` (old `func_001C8E58`) @ 0x001C8E58
- KEPT `ClothTestGeo` (old `func_001C8E78`) @ 0x001C8E78
- KEPT `ClothTestDL` (old `func_001C8EB0`) @ 0x001C8EB0
- KEPT `func_001C8ED8` (old `func_001C8ED8`) @ 0x001C8ED8
- KEPT `func_001C8EF8` (old `func_001C8EF8`) @ 0x001C8EF8
- KEPT `func_001C9078` (old `func_001C9078`) @ 0x001C9078
- KEPT `func_001C9328` (old `func_001C9328`) @ 0x001C9328
- KEPT `func_001C9330` (old `func_001C9330`) @ 0x001C9330
- REVERTED `func_001C92D8` (old `func_001C92D8`) @ 0x001C92D8 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/darkVolume
- KEPT `darkVolume` (old `func_001CBB88`) @ 0x001CBB88
- KEPT `DispGameOverEffect` (old `func_001CBD68`) @ 0x001CBD68
- KEPT `GetGameOverEffectCenterPosition` (old `func_001CBD70`) @ 0x001CBD70
- KEPT `InitGameOverEffect` (old `func_001CBD78`) @ 0x001CBD78
- KEPT `InitDarkVolumeGeo` (old `func_001CBD80`) @ 0x001CBD80
- REVERTED `renderViewCoordZSphere` (old `func_001CB910`) @ 0x001CB910 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/effectTool
- KEPT `_dispParam` (old `func_001CBD88`) @ 0x001CBD88
- KEPT `editParam` (old `func_001CBE20`) @ 0x001CBE20
- KEPT `dispXZYZCircle` (old `func_001CBE78`) @ 0x001CBE78
- REVERTED `saveEffectData` (old `func_001CCA70`) @ 0x001CCA70 — insn 5: expected `lhu	a1,0(gp)` built `lh	a1,0(gp)`

## src/enemy
- KEPT `EnemySetfAppearAll` (old `func_001CE690`) @ 0x001CE690
- KEPT `EnemySetfDisappearAll` (old `func_001CE6F0`) @ 0x001CE6F0
- KEPT `enemySetParticleDie` (old `func_001CE760`) @ 0x001CE760
- REVERTED `EnemyCheckHit` (old `func_001CD490`) @ 0x001CD490 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `ReviveEnemyParticle` (old `func_001CE768`) @ 0x001CE768 — src/enemy.c:7: redefinition of `struct GObj'
- REVERTED `InitDemoMotionGeo` (old `func_001CE978`) @ 0x001CE978 — src/enemy.c:7: redefinition of `struct GObj'
- REVERTED `HotInitDemoMotionGeo` (old `func_001CE998`) @ 0x001CE998 — src/enemy.c:7: redefinition of `struct GObj'

## src/enemyParts
- KEPT `InitEnemyFootPrint` (old `func_001CEB18`) @ 0x001CEB18
- KEPT `ExecEnemyFootPrints` (old `func_001CEB68`) @ 0x001CEB68
- KEPT `DispPointBlur` (old `func_001CEC00`) @ 0x001CEC00
- KEPT `func_001CF770` (old `func_001CF770`) @ 0x001CF770
- KEPT `func_001CF8D0` (old `func_001CF8D0`) @ 0x001CF8D0
- REVERTED `InitEnemyEye` (old `func_001CEB08`) @ 0x001CEB08 — src/enemyParts.c:5: redefinition of `struct GObj'
- REVERTED `EntryEnemyFootPrint` (old `func_001CEBB0`) @ 0x001CEBB0 — src/enemyParts.c:6: redefinition of `struct GObj'
- REVERTED `DispEnemyFootPrints` (old `func_001CEBC0`) @ 0x001CEBC0 — src/enemyParts.c:6: redefinition of `struct GObj'
- REVERTED `InitPointBlur` (old `func_001CEBF0`) @ 0x001CEBF0 — src/enemyParts.c:6: redefinition of `struct GObj'
- REVERTED `UpdateEnemyEye` (old `func_001CEC30`) @ 0x001CEC30 — src/enemyParts.c:7: redefinition of `struct GObj'
- REVERTED `DispEnemyEye` (old `func_001CEC60`) @ 0x001CEC60 — src/enemyParts.c:7: redefinition of `struct GObj'
- REVERTED `moveDataElements` (old `func_001CED28`) @ 0x001CED28 — src/enemyParts.c:7: redefinition of `struct GObj'

## src/flag
- KEPT `FlagGeo` (old `func_001CFA20`) @ 0x001CFA20
- KEPT `func_001D03A0` (old `func_001D03A0`) @ 0x001D03A0
- KEPT `func_001D03C8` (old `func_001D03C8`) @ 0x001D03C8

## src/flyManager
- KEPT `DispFlyInfo` (old `func_001D03E0`) @ 0x001D03E0

## src/frameDependSequence
- KEPT `playSERandomID` (old `func_001D1288`) @ 0x001D1288
- KEPT `playEff` (old `func_001D12B0`) @ 0x001D12B0
- REVERTED `playSEConditionID` (old `func_001D12A8`) @ 0x001D12A8 — src/frameDependSequence.c:20: too many arguments to function `playSERandomID'
- REVERTED `execEff` (old `func_001D12C0`) @ 0x001D12C0 — src/frameDependSequence.c:6: redefinition of `struct GObj'
- REVERTED `ExecFrameDependSequence` (old `func_001D12D8`) @ 0x001D12D8 — insn 0: expected `j	0 <ExecFrameDependSequence>` built `j	168 <execEff>`
- REVERTED `ExecuteSEPackageWithGroupVariation` (old `func_001D1410`) @ 0x001D1410 — src/frameDependSequence.c:6: redefinition of `struct GObj'
- REVERTED `ExecuteSEPackage` (old `func_001D1428`) @ 0x001D1428 — src/frameDependSequence.c:6: redefinition of `struct GObj'

## src/girl
- KEPT `func_001D1440` (old `func_001D1440`) @ 0x001D1440
- KEPT `func_001D1468` (old `func_001D1468`) @ 0x001D1468
- REVERTED `SetGirlClothDispSwitch` (old `func_001D1A98`) @ 0x001D1A98 — insn 7: expected `jal	0 <SetGirlClothDispSwitch>` built `jal	140 <GirlGeo>`

## src/girlForceField
- KEPT `GirlForceFieldGeo` (old `func_001D1AD0`) @ 0x001D1AD0
- KEPT `func_001D1CF8` (old `func_001D1CF8`) @ 0x001D1CF8

## src/handManager
- KEPT `HandManager` (old `func_001D2538`) @ 0x001D2538

## src/item
- KEPT `bombSparkStartSE` (old `func_001D2540`) @ 0x001D2540
- KEPT `bombSparkSE` (old `func_001D2548`) @ 0x001D2548
- KEPT `HoldItem` (old `func_001D2650`) @ 0x001D2650
- REVERTED `avoidInsideOfWall` (old `func_001D26C8`) @ 0x001D26C8 — src/item.c:42: `Obj800' undeclared (first use in this function)
- REVERTED `ReleaseItem` (old `func_001D2738`) @ 0x001D2738 — src/item.c:43: `Obj800' undeclared (first use in this function)

## src/lineManager
- KEPT `_getLine` (old `func_001D3DB0`) @ 0x001D3DB0
- REVERTED `Draw2DLine` (old `func_001D3D40`) @ 0x001D3D40 — src/lineManager.c:5: redefinition of `struct GObj'
- REVERTED `Draw2DLineSeg_Start` (old `func_001D3D70`) @ 0x001D3D70 — src/lineManager.c:5: redefinition of `struct GObj'
- REVERTED `Draw2DLineSeg_Loop` (old `func_001D3D80`) @ 0x001D3D80 — src/lineManager.c:5: redefinition of `struct GObj'
- REVERTED `Draw2DLineG` (old `func_001D3D98`) @ 0x001D3D98 — src/lineManager.c:5: redefinition of `struct GObj'
- REVERTED `func_001D40A0` (old `func_001D40A0`) @ 0x001D40A0 — src/lineManager.c:5: redefinition of `struct GObj'

## src/lodManager
- KEPT `SetLodLevel` (old `func_001D4348`) @ 0x001D4348
- KEPT `func_001D49C0` (old `func_001D49C0`) @ 0x001D49C0
- KEPT `func_001D4D98` (old `func_001D4D98`) @ 0x001D4D98
- KEPT `func_001D4DA8` (old `func_001D4DA8`) @ 0x001D4DA8
- KEPT `func_001D4DD0` (old `func_001D4DD0`) @ 0x001D4DD0

## src/motionFileManager
- KEPT `InitMotionFile` (old `func_001D4E70`) @ 0x001D4E70
- REVERTED `pursueNodeList` (old `func_001D4E30`) @ 0x001D4E30 — insn 15: expected `<end>` built `sll	zero,zero,0x0`

## src/motionManager
- KEPT `SkelTestGeo` (old `func_001DC8D8`) @ 0x001DC8D8
- KEPT `SetHitCollisionDisplay` (old `func_001DC908`) @ 0x001DC908
- KEPT `func_001E0978` (old `func_001E0978`) @ 0x001E0978
- REVERTED `_checkCliffAndWall` (old `func_001D9C58`) @ 0x001D9C58 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `GetWallVector` (old `func_001DC938`) @ 0x001DC938 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `func_001E0860` (old `func_001E0860`) @ 0x001E0860 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

## src/motionOrientManager
- KEPT `UpdateFrameCounter` (old `func_001E0C08`) @ 0x001E0C08
- KEPT `ExecuteSlipProc` (old `func_001E44C0`) @ 0x001E44C0
- KEPT `func_001E4838` (old `func_001E4838`) @ 0x001E4838
- REVERTED `getStreamMotionGeometry` (old `func_001E2370`) @ 0x001E2370 — insn 1: expected `j	0 <getStreamMotionGeometry>` built `j	1118 <getNodeBlendedFloatingMotion>`
- REVERTED `SetParallelMotionTable` (old `func_001E3F40`) @ 0x001E3F40 — src/motionOrientManager.c:6: redefinition of `struct GObj'
- REVERTED `func_001E4700` (old `func_001E4700`) @ 0x001E4700 — src/motionOrientManager.c:7: redefinition of `struct GObj'
- REVERTED `func_001E4728` (old `func_001E4728`) @ 0x001E4728 — insn 17: expected `jal	0 <func_001E4728>` built `jal	1d18 <getStreamMotion>`
- REVERTED `func_001E4798` (old `func_001E4798`) @ 0x001E4798 — src/motionOrientManager.c:7: redefinition of `struct GObj'

## src/motionViewer
- KEPT `dispProgressBar` (old `func_001E4970`) @ 0x001E4970
- KEPT `dispMotFrameProgress` (old `func_001E4980`) @ 0x001E4980
- REVERTED `setMotionSpeed` (old `func_001E4938`) @ 0x001E4938 — src/motionViewer.c:5: redefinition of `struct GObj'

## src/moveColTest
- KEPT `InitMoveColTestGeo` (old `func_001E6960`) @ 0x001E6960
- REVERTED `func_001E6968` (old `func_001E6968`) @ 0x001E6968 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/multiBgaManager
- KEPT `EntryMultiBgaManager` (old `func_001E6A98`) @ 0x001E6A98
- KEPT `EntryMultiBgaManagerSensitive` (old `func_001E6B00`) @ 0x001E6B00

## src/particleEffect
- KEPT `execParticleEffect` (old `func_001E6D68`) @ 0x001E6D68
- KEPT `DeleteParticleEffectsByID` (old `func_001E8BD8`) @ 0x001E8BD8
- REVERTED `ResetParticleEffectPackages` (old `func_001E85D8`) @ 0x001E85D8 — insn 11: expected `j	0 <ResetParticleEffectPackages>` built `j	778 <SetParticleEffect>`
- REVERTED `SetParticleEffectActiveSensing` (old `func_001E8A60`) @ 0x001E8A60 — insn 10: expected `jal	0 <SetParticleEffectActiveSensing>` built `jal	14a8 <SetParticleEffectGeometry>`
- REVERTED `func_001E8B48` (old `func_001E8B48`) @ 0x001E8B48 — insn 3: expected `jal	0 <func_001E8B48>` built `jal	17c8 <SetParticleEffectUpperLimit>`

## src/particleLayout
- KEPT `ParticleLayoutGeo` (old `func_001E8D50`) @ 0x001E8D50
- KEPT `func_001E8DE0` (old `func_001E8DE0`) @ 0x001E8DE0
- KEPT `func_001E8E80` (old `func_001E8E80`) @ 0x001E8E80
- KEPT `func_001E8F28` (old `func_001E8F28`) @ 0x001E8F28
- REVERTED `func_001E8EA8` (old `func_001E8EA8`) @ 0x001E8EA8 — src/particleLayout.c:7: redefinition of `struct GObj'
- REVERTED `func_001E8EB8` (old `func_001E8EB8`) @ 0x001E8EB8 — src/particleLayout.c:7: redefinition of `struct GObj'

## src/rope
- KEPT `InitRopeGeo` (old `func_001E8F30`) @ 0x001E8F30
- REVERTED `HoldRope` (old `func_001E93D0`) @ 0x001E93D0 — src/rope.c:5: redefinition of `struct GObj'
- REVERTED `ReleaseRope` (old `func_001E97F8`) @ 0x001E97F8 — src/rope.c:5: redefinition of `struct GObj'

## src/ropeFix
- KEPT `RopeFixGeo` (old `func_001E9808`) @ 0x001E9808
- KEPT `InitRopeFixGeo` (old `func_001E9888`) @ 0x001E9888
- KEPT `func_001E9910` (old `func_001E9910`) @ 0x001E9910
- KEPT `func_001E9918` (old `func_001E9918`) @ 0x001E9918
- KEPT `func_001E9920` (old `func_001E9920`) @ 0x001E9920
- REVERTED `func_001E98C8` (old `func_001E98C8`) @ 0x001E98C8 — src/ropeFix.c:6: redefinition of `struct GObj'
- REVERTED `func_001E9950` (old `func_001E9950`) @ 0x001E9950 — src/ropeFix.c:8: redefinition of `struct GObj'

## src/rotObject
- KEPT `func_001E9DE8` (old `func_001E9DE8`) @ 0x001E9DE8
- KEPT `func_001E9DF0` (old `func_001E9DF0`) @ 0x001E9DF0
- KEPT `func_001EA220` (old `func_001EA220`) @ 0x001EA220
- REVERTED `func_001EA108` (old `func_001EA108`) @ 0x001EA108 — src/rotObject.c:7: redefinition of `struct GObj'
- REVERTED `func_001EA228` (old `func_001EA228`) @ 0x001EA228 — src/rotObject.c:7: redefinition of `struct GObj'
- REVERTED `func_001EA248` (old `func_001EA248`) @ 0x001EA248 — src/rotObject.c:7: redefinition of `struct GObj'
- REVERTED `func_001EA268` (old `func_001EA268`) @ 0x001EA268 — src/rotObject.c:7: redefinition of `struct GObj'

## src/spider
- KEPT `func_001EB0B8` (old `func_001EB0B8`) @ 0x001EB0B8
- REVERTED `func_001EA3E0` (old `func_001EA3E0`) @ 0x001EA3E0 — src/spider.c:5: redefinition of `struct GObj'
- REVERTED `func_001EACE8` (old `func_001EACE8`) @ 0x001EACE8 — src/spider.c:5: redefinition of `struct GObj'
- REVERTED `func_001EAE70` (old `func_001EAE70`) @ 0x001EAE70 — src/spider.c:5: redefinition of `struct GObj'

## src/spiderGroupManager
- KEPT `func_001EB9F0` (old `func_001EB9F0`) @ 0x001EB9F0
- KEPT `func_001EBA18` (old `func_001EBA18`) @ 0x001EBA18
- KEPT `func_001EBA40` (old `func_001EBA40`) @ 0x001EBA40
- KEPT `func_001EBAE8` (old `func_001EBAE8`) @ 0x001EBAE8
- KEPT `func_001EBB10` (old `func_001EBB10`) @ 0x001EBB10

## src/stageMultiBgaManager

## src/staticBlur
- KEPT `subWork1ToCurrentFB` (old `func_001EEF08`) @ 0x001EEF08

## src/stormTest
- KEPT `InitStormPackage` (old `func_001EF980`) @ 0x001EF980
- KEPT `ClipStormByVolume` (old `func_001EF988`) @ 0x001EF988
- KEPT `ClipStormByCamera` (old `func_001EF990`) @ 0x001EF990
- KEPT `UpdateStormPackage` (old `func_001EF998`) @ 0x001EF998
- KEPT `DispStormPackage` (old `func_001EF9A8`) @ 0x001EF9A8
- KEPT `StormTestDL` (old `func_001EF9D8`) @ 0x001EF9D8
- KEPT `func_001EFA58` (old `func_001EFA58`) @ 0x001EFA58
- KEPT `func_001F0858` (old `func_001F0858`) @ 0x001F0858
- KEPT `func_001F0A28` (old `func_001F0A28`) @ 0x001F0A28
- REVERTED `StormTestGeo` (old `func_001EF9D0`) @ 0x001EF9D0 — src/stormTest.c:38: incompatible types in assignment
- REVERTED `InitStormTestGeo` (old `func_001EF9E0`) @ 0x001EF9E0 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_001F0540` (old `func_001F0540`) @ 0x001F0540 — src/stormTest.c:9: redefinition of `struct GObj'
- REVERTED `func_001F0550` (old `func_001F0550`) @ 0x001F0550 — src/stormTest.c:9: redefinition of `struct GObj'
- REVERTED `func_001F0568` (old `func_001F0568`) @ 0x001F0568 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/streamMotionManager
- KEPT `PlayStreamMotion` (old `func_001F0B20`) @ 0x001F0B20
- KEPT `func_001F0F90` (old `func_001F0F90`) @ 0x001F0F90
- KEPT `ExecStreamMotionManager` (old `func_001F1058`) @ 0x001F1058
- KEPT `StandbyStreamMotion` (old `func_001F10A8`) @ 0x001F10A8
- KEPT `StopStreamMotion` (old `func_001F10F8`) @ 0x001F10F8
- KEPT `DeleteStreamMotionManager` (old `func_001F1108`) @ 0x001F1108
- REVERTED `func_001F0DA8` (old `func_001F0DA8`) @ 0x001F0DA8 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

## src/sugiTree
- KEPT `func_001F1168` (old `func_001F1168`) @ 0x001F1168
- KEPT `InitSugiLeafGeo` (old `func_001F1240`) @ 0x001F1240
- KEPT `func_001F1838` (old `func_001F1838`) @ 0x001F1838
- REVERTED `SugiLeafDL2` (old `func_001F11A0`) @ 0x001F11A0 — src/sugiTree.c:37: structure has no member named `data'

## src/torch
- KEPT `CheckTorchChainReactionReverse` (old `func_001F2140`) @ 0x001F2140
- REVERTED `TorchGeo` (old `func_001F2148`) @ 0x001F2148 — src/torch.c:5: redefinition of `struct GObj'
- REVERTED `TorchDL` (old `func_001F2230`) @ 0x001F2230 — src/torch.c:5: redefinition of `struct GObj'
- REVERTED `IsTorchLightOn` (old `func_001F2240`) @ 0x001F2240 — src/torch.c:5: redefinition of `struct GObj'

## src/waySystemManager
- KEPT `func_001F2320` (old `func_001F2320`) @ 0x001F2320
- KEPT `func_001F2390` (old `func_001F2390`) @ 0x001F2390
- KEPT `func_001F23C0` (old `func_001F23C0`) @ 0x001F23C0
- KEPT `func_001F23C8` (old `func_001F23C8`) @ 0x001F23C8
- KEPT `func_001F23D0` (old `func_001F23D0`) @ 0x001F23D0
- REVERTED `CreateWaySystemManagerGObj` (old `func_001F2250`) @ 0x001F2250 — src/waySystemManager.c:5: redefinition of `struct GObj'
- REVERTED `RequestGetWayBegin` (old `func_001F22A0`) @ 0x001F22A0 — src/waySystemManager.c:9: `func_001F2370' undeclared (first use in this function)

## src/weapon
- KEPT `weaponFumbleSE` (old `func_001F3388`) @ 0x001F3388
- KEPT `WeaponCurPos` (old `func_001F3F58`) @ 0x001F3F58
- KEPT `dispInsectNet` (old `func_001F4228`) @ 0x001F4228
- REVERTED `torchOffOfWeaponSE` (old `func_001F3308`) @ 0x001F3308 — src/weapon.c:5: redefinition of `struct GObj'
- REVERTED `weaponHitReactionSE` (old `func_001F3368`) @ 0x001F3368 — src/weapon.c:5: redefinition of `struct GObj'
- REVERTED `calcDynamicPathGeometry` (old `func_001F3A00`) @ 0x001F3A00 — insn 8: expected `j	0 <calcDynamicPathGeometry>` built `j	208 <weaponStickSE>`
- REVERTED `WeaponHitEffect` (old `func_001F3FB0`) @ 0x001F3FB0 — src/weapon.c:8: redefinition of `struct GObj'
- REVERTED `ExecWeaponHitReaction` (old `func_001F4098`) @ 0x001F4098 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `checkHit` (old `func_001F40C8`) @ 0x001F40C8 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `initializeQueenzSword` (old `func_001F40D8`) @ 0x001F40D8 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `InitWeaponGeo` (old `func_001F4150`) @ 0x001F4150 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `WeaponGeo` (old `func_001F41C8`) @ 0x001F41C8 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `WeaponDL` (old `func_001F4250`) @ 0x001F4250 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `PickupWeapon` (old `func_001F42D0`) @ 0x001F42D0 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `CheckSwapableWeapon` (old `func_001F42E8`) @ 0x001F42E8 — src/weapon.c:76: request for member `field' in something not a structure or union
- REVERTED `ReleaseWeapon` (old `func_001F4318`) @ 0x001F4318 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `CheckWeaponKind` (old `func_001F43D0`) @ 0x001F43D0 — src/weapon.c:7: redefinition of `struct GObj'
- REVERTED `LightTorchOnOfWeapon` (old `func_001F44C8`) @ 0x001F44C8 — src/weapon.c:7: redefinition of `struct GObj'

## src/windField
- KEPT `ExecWindField` (old `func_001F4C00`) @ 0x001F4C00
- REVERTED `drawSenpuuki` (old `func_001F4BE0`) @ 0x001F4BE0 — src/windField.c:10: called object is not a function
- REVERTED `getParallelWindVector` (old `func_001F4DD8`) @ 0x001F4DD8 — insn 1: expected `addiu	v0,v0,0` built `addiu	v0,v0,1024`

## src/windManager

## src/wireLetter
- KEPT `ChangeColorWireString` (old `func_001F55D8`) @ 0x001F55D8
- KEPT `Draw2DBox` (old `func_001F5608`) @ 0x001F5608

## src/worm
- REVERTED `GetWormRoute` (old `func_001F66A0`) @ 0x001F66A0 — src/worm.c:5: redefinition of `struct GObj'
- REVERTED `GetWormCaptureVector` (old `func_001F69B0`) @ 0x001F69B0 — insn 0: expected `j	0 <GetWormCaptureVector>` built `j	208 <simulate>`
- REVERTED `WormDL` (old `func_001F6A90`) @ 0x001F6A90 — src/worm.c:5: redefinition of `struct GObj'

## src/Basic
- KEPT `malloc_MemCpy` (old `func_001F6C88`) @ 0x001F6C88
- KEPT `malloc_SetPartition` (old `func_001F6C98`) @ 0x001F6C98
- KEPT `malloc_GetPartition` (old `func_001F6CA0`) @ 0x001F6CA0
- KEPT `mallocseki` (old `func_001F6CA8`) @ 0x001F6CA8
- KEPT `resetmallocseki` (old `func_001F6D90`) @ 0x001F6D90
- KEPT `mallocsekistage` (old `func_001F6DB0`) @ 0x001F6DB0
- REVERTED `reallocseki` (old `func_001F6DB8`) @ 0x001F6DB8 — insn 5: expected `lui	a2,0x0` built `addiu	a3,zero,382`
- REVERTED `func_001F6E00` (old `func_001F6E00`) @ 0x001F6E00 — [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

## src/BgAnimation
- KEPT `bga_DispLightning` (old `func_001FA590`) @ 0x001FA590
- KEPT `bga_ResetCamera` (old `func_001FA598`) @ 0x001FA598
- REVERTED `bga_GetCameraMatrix` (old `func_001FA5E0`) @ 0x001FA5E0 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

## src/DisplayFont
- KEPT `font_GetHeight` (old `func_001FAA40`) @ 0x001FAA40
- KEPT `font_Init` (old `func_001FAA50`) @ 0x001FAA50
- REVERTED `func_001FAAA8` (old `func_001FAAA8`) @ 0x001FAAA8 — insn 0: expected `jr	ra` built `lwc1	$f0,0(gp)`

## src/DisplayList
- KEPT `dl_Clear` (old `func_001FB478`) @ 0x001FB478
- KEPT `dl_Swap` (old `func_001FB480`) @ 0x001FB480
- KEPT `dl_OpenDma` (old `func_001FB880`) @ 0x001FB880
- QUARANTINED `dl_Debug` (old `func_001FB5E0`) @ 0x001FB5E0 — DisplayList-extra_cflags

## src/DmaPacket
- KEPT `dpk_SwapBuffer` (old `func_001FBA80`) @ 0x001FBA80
- KEPT `dpk_CheckBufferSize` (old `func_001FBB40`) @ 0x001FBB40
- REVERTED `func_001FBB48` (old `func_001FBB48`) @ 0x001FBB48 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

## src/EnemyInit
- KEPT `enemy_Initialize` (old `func_001FBC18`) @ 0x001FBC18
- KEPT `func_001FBF88` (old `func_001FBF88`) @ 0x001FBF88
- REVERTED `func_001FC040` (old `func_001FC040`) @ 0x001FC040 — insn 0: expected `j	0 <func_001FC040>` built `j	3b0 <func_001FBFC8>`

## isys/gobj_cam_dl
- KEPT `isysGObjRemoveCameraDL` (old `func_001FC168`) @ 0x001FC168
- KEPT `isysGObjMoveCameraDL` (old `func_001FC220`) @ 0x001FC220
- KEPT `isysGObjLinkCameraDL` (old `func_001FC278`) @ 0x001FC278
- KEPT `isysGObjLinkCameraDLAfterGObj` (old `func_001FC2D0`) @ 0x001FC2D0
- REVERTED `func_001FC1A0` (old `func_001FC1A0`) @ 0x001FC1A0 — insn 5: expected `lui	a0,0x0` built `daddu	s4,a1,zero`

## src/act-env
- KEPT `func_00200A98` (old `func_00200A98`) @ 0x00200A98
- REVERTED `func_00200970` (old `func_00200970`) @ 0x00200970 — src/act-env.c:5: redefinition of `struct GObj'

## src/act-way
- KEPT `ACTWay_SetBeginPositionIllegal` (old `func_00201DC8`) @ 0x00201DC8

## src/act
- KEPT `actInitialize_geo` (old `func_00203910`) @ 0x00203910
- KEPT `ACTReserveTarget` (old `func_00203A10`) @ 0x00203A10
- KEPT `actCreateSubThreadGOppArg` (old `func_00203B40`) @ 0x00203B40
- KEPT `actSetInterrupt` (old `func_00203C38`) @ 0x00203C38

## src/act2
- KEPT `actDummy` (old `func_00203CB8`) @ 0x00203CB8
- KEPT `func_00203F18` (old `func_00203F18`) @ 0x00203F18

## src/seMail
- KEPT `seMailTargetDistCheck` (old `func_00204E90`) @ 0x00204E90
- KEPT `func_00205048` (old `func_00205048`) @ 0x00205048
- KEPT `func_00205518` (old `func_00205518`) @ 0x00205518
- REVERTED `func_00204F58` (old `func_00204F58`) @ 0x00204F58 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `func_00205000` (old `func_00205000`) @ 0x00205000 — insn 5: expected `beq	zero,zero,38 <func_00205000+0x38>` built `beq	zero,zero,860 <func_00205000+0x40>`

## src/way_kidnap
- KEPT `WayPointWithRangeFromPos` (old `func_00205628`) @ 0x00205628
- KEPT `WayPointWithRangeFromPos2` (old `func_00205670`) @ 0x00205670

## src/way_llf
- KEPT `AddWayPoint` (old `func_00205AD8`) @ 0x00205AD8
- KEPT `InsertWayPointAfter` (old `func_00205B50`) @ 0x00205B50

## src/way_tool
- REVERTED `draw_way_group` (old `func_00207018`) @ 0x00207018 — insn 15: expected `lui	a0,0x0` built `andi	v1,v0,0x40`

## src/deja
- KEPT `func_00208740` (old `func_00208740`) @ 0x00208740
- KEPT `func_00209AB0` (old `func_00209AB0`) @ 0x00209AB0

## src/e3

## src/end

## src/op
- KEPT `actOpDemo03` (old `func_0020D2B8`) @ 0x0020D2B8
- KEPT `func_0020D770` (old `func_0020D770`) @ 0x0020D770

## src/st00a
- KEPT `actSt00aDoor2DownEffect` (old `func_0020FB00`) @ 0x0020FB00

## src/st01b
- KEPT `actSt01bFloor` (old `func_002109D8`) @ 0x002109D8
- KEPT `actSt01bSekizoEvent` (old `func_00210BA8`) @ 0x00210BA8

## src/st02a
- KEPT `actSt02aGondola` (old `func_002115F8`) @ 0x002115F8
- KEPT `actSt02aFence` (old `func_00211600`) @ 0x00211600
- KEPT `actSt02aWaterFall` (old `func_00211610`) @ 0x00211610
- KEPT `actSt02aEnemy1` (old `func_00211780`) @ 0x00211780

## src/st03t
- KEPT `actSt03tEne` (old `func_002128F8`) @ 0x002128F8
- KEPT `actSt03tWayOnChk` (old `func_00212D68`) @ 0x00212D68

## src/st04a
- KEPT `actSt04aGateR` (old `func_00213E80`) @ 0x00213E80
- KEPT `actSt04aGateOpen3` (old `func_00214030`) @ 0x00214030

## src/st04b

## src/st04c

## src/st04d
- KEPT `actSt04dDoor1DownChk` (old `func_00218DC0`) @ 0x00218DC0
- KEPT `actSt04dDoor2UpChk` (old `func_00218E58`) @ 0x00218E58
- KEPT `func_00219478` (old `func_00219478`) @ 0x00219478
- KEPT `func_002194C8` (old `func_002194C8`) @ 0x002194C8
- KEPT `func_00219728` (old `func_00219728`) @ 0x00219728

## src/st04e
- KEPT `func_00219EA8` (old `func_00219EA8`) @ 0x00219EA8
- KEPT `func_0021A078` (old `func_0021A078`) @ 0x0021A078

## src/st04l

## src/st04r

## src/st05b

## src/st05c
- KEPT `actSt05cDoorDownEffect` (old `func_0021F2A8`) @ 0x0021F2A8
- KEPT `actSt05cEneChk` (old `func_0021F2B8`) @ 0x0021F2B8
- KEPT `func_0021F2C8` (old `func_0021F2C8`) @ 0x0021F2C8
- KEPT `func_0021F2D8` (old `func_0021F2D8`) @ 0x0021F2D8
- KEPT `func_0021F2E8` (old `func_0021F2E8`) @ 0x0021F2E8
- KEPT `func_0021F2F8` (old `func_0021F2F8`) @ 0x0021F2F8
- KEPT `func_0021F3A8` (old `func_0021F3A8`) @ 0x0021F3A8

## src/st05d
- KEPT `actSt05dDoor2DownChk` (old `func_0021F4F8`) @ 0x0021F4F8
- KEPT `actSt05dEne` (old `func_0021F508`) @ 0x0021F508
- KEPT `actSt05dEnemy1` (old `func_0021F518`) @ 0x0021F518
- KEPT `actSt05dEnemy2` (old `func_0021F528`) @ 0x0021F528
- KEPT `actSt05dDoor2Event` (old `func_0021F538`) @ 0x0021F538
- KEPT `actSt05dDoor2UpEffect` (old `func_0021F548`) @ 0x0021F548
- KEPT `actSt05dDoor2DownEffect` (old `func_0021F558`) @ 0x0021F558
- KEPT `actSt05dEneChk` (old `func_0021F568`) @ 0x0021F568
- KEPT `func_0021F578` (old `func_0021F578`) @ 0x0021F578
- KEPT `func_0021F588` (old `func_0021F588`) @ 0x0021F588
- KEPT `func_0021F7F0` (old `func_0021F7F0`) @ 0x0021F7F0

## src/st05e

## src/st06a

## src/st07a

## src/st08a
- KEPT `actSt08aEnemy2` (old `func_00223DE0`) @ 0x00223DE0
- KEPT `actSt08aEnemy3` (old `func_00223DF0`) @ 0x00223DF0
- KEPT `actSt08aEnemy4` (old `func_00223E00`) @ 0x00223E00
- KEPT `actSt08aIntro` (old `func_00223E10`) @ 0x00223E10
- KEPT `actSt08aInit` (old `func_00223E20`) @ 0x00223E20
- KEPT `actSt08aDoorMain` (old `func_00223E30`) @ 0x00223E30
- KEPT `actSt08aDoorSwitch` (old `func_00223E40`) @ 0x00223E40
- KEPT `func_00223EF0` (old `func_00223EF0`) @ 0x00223EF0
- KEPT `func_00223F00` (old `func_00223F00`) @ 0x00223F00
- KEPT `func_00223F10` (old `func_00223F10`) @ 0x00223F10
- KEPT `func_00223F20` (old `func_00223F20`) @ 0x00223F20
- KEPT `func_00223F30` (old `func_00223F30`) @ 0x00223F30

## src/st08b
- KEPT `actSt08bKurenSwitch` (old `func_00223F40`) @ 0x00223F40
- KEPT `actSt08bKurenLeft` (old `func_00223F50`) @ 0x00223F50
- KEPT `actSt08bKurenRight` (old `func_00223F60`) @ 0x00223F60
- KEPT `func_00224960` (old `func_00224960`) @ 0x00224960

## src/st09a
- KEPT `actSt09aBrgMain` (old `func_002251E0`) @ 0x002251E0
- KEPT `func_002258E0` (old `func_002258E0`) @ 0x002258E0

## src/st10l

## src/st10r
- KEPT `actSt10rFloor` (old `func_00227350`) @ 0x00227350
- KEPT `actSt10rExit` (old `func_002274F0`) @ 0x002274F0

## src/st13a

## src/st13b
- KEPT `actSt13bElevDown` (old `func_00229CA0`) @ 0x00229CA0
- KEPT `actSt13bElevUp` (old `func_00229CB0`) @ 0x00229CB0
- KEPT `actSt13bElevUpChk` (old `func_00229D30`) @ 0x00229D30
- KEPT `actSt13bBossAfter` (old `func_00229E38`) @ 0x00229E38
- KEPT `actSt13bStoneGirl` (old `func_00229E48`) @ 0x00229E48
- KEPT `actSt13bElev` (old `func_00229F20`) @ 0x00229F20
- KEPT `actBossTest` (old `func_00229FE0`) @ 0x00229FE0
- KEPT `actSt13bSekizo2Event` (old `func_0022A068`) @ 0x0022A068
- REVERTED `actSt13bSekizo` (old `func_00229D88`) @ 0x00229D88 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `actSt13bSekizo2` (old `func_00229DE0`) @ 0x00229DE0 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `actSt13bExit` (old `func_00229EC8`) @ 0x00229EC8 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## src/st13b2

## src/st13c
- KEPT `actSt13cBmg1Chk` (old `func_0022B640`) @ 0x0022B640
- KEPT `actSt13cCage1stDown` (old `func_0022B878`) @ 0x0022B878
- KEPT `actSt13cSleep` (old `func_0022BED0`) @ 0x0022BED0

## src/st13d

## src/st17a
- KEPT `actSt17aSekizo` (old `func_0022D6B0`) @ 0x0022D6B0

## src/st17b
- KEPT `func_0022EEF0` (old `func_0022EEF0`) @ 0x0022EEF0
- KEPT `func_0022F850` (old `func_0022F850`) @ 0x0022F850
- REVERTED `func_0022ED40` (old `func_0022ED40`) @ 0x0022ED40 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## src/st18a

## src/st19a
- KEPT `actSt19aOri` (old `func_002315C8`) @ 0x002315C8
- KEPT `actSt19bIntroChk` (old `func_00231AC8`) @ 0x00231AC8
- KEPT `func_00231AF8` (old `func_00231AF8`) @ 0x00231AF8

## src/st20a

## src/st22a
- KEPT `actSt22aIntro` (old `func_002341D8`) @ 0x002341D8
- KEPT `actSt22aIntroChk` (old `func_002341E8`) @ 0x002341E8
- KEPT `func_00234438` (old `func_00234438`) @ 0x00234438
- KEPT `func_00234448` (old `func_00234448`) @ 0x00234448
- KEPT `func_002347C8` (old `func_002347C8`) @ 0x002347C8
- KEPT `func_00234AB0` (old `func_00234AB0`) @ 0x00234AB0

## src/st24a
- KEPT `func_002356C0` (old `func_002356C0`) @ 0x002356C0
- KEPT `func_00235728` (old `func_00235728`) @ 0x00235728
- KEPT `func_002358F8` (old `func_002358F8`) @ 0x002358F8
- KEPT `func_00235B68` (old `func_00235B68`) @ 0x00235B68
- KEPT `func_00235C38` (old `func_00235C38`) @ 0x00235C38
- REVERTED `func_002359C8` (old `func_002359C8`) @ 0x002359C8 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## src/st47a
- KEPT `actSt47aExit` (old `func_00236C60`) @ 0x00236C60
- KEPT `func_00237B78` (old `func_00237B78`) @ 0x00237B78
- KEPT `func_00237BD0` (old `func_00237BD0`) @ 0x00237BD0
- KEPT `func_00239750` (old `func_00239750`) @ 0x00239750
- KEPT `func_002397F8` (old `func_002397F8`) @ 0x002397F8

## src/access
- KEPT `func_0023A9E0` (old `func_0023A9E0`) @ 0x0023A9E0
- KEPT `func_0023AA88` (old `func_0023AA88`) @ 0x0023AA88
- KEPT `func_0023AA98` (old `func_0023AA98`) @ 0x0023AA98
- KEPT `func_0023AAA8` (old `func_0023AAA8`) @ 0x0023AAA8
- KEPT `func_0023AD58` (old `func_0023AD58`) @ 0x0023AD58
- KEPT `func_0023AEA0` (old `func_0023AEA0`) @ 0x0023AEA0
- REVERTED `func_0023AB90` (old `func_0023AB90`) @ 0x0023AB90 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_0023ABE0` (old `func_0023ABE0`) @ 0x0023ABE0 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `func_0023AD08` (old `func_0023AD08`) @ 0x0023AD08 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## src/objact
- KEPT `func_0023C090` (old `func_0023C090`) @ 0x0023C090
- KEPT `func_0023C0E8` (old `func_0023C0E8`) @ 0x0023C0E8

## ito/mpeg/mv_audiodec
- KEPT `audioDecEndPut` (old `func_0023C540`) @ 0x0023C540
- KEPT `sendToIOP2area` (old `func_0023C598`) @ 0x0023C598
- KEPT `func_0023CC78` (old `func_0023CC78`) @ 0x0023CC78
- KEPT `func_0023CCE0` (old `func_0023CCE0`) @ 0x0023CCE0

## ito/mpeg/mv_disp
- KEPT `setDispEnv` (old `func_0023D030`) @ 0x0023D030
- KEPT `sendDispEnv` (old `func_0023D0C8`) @ 0x0023D0C8
- KEPT `handler_endimage` (old `func_0023D370`) @ 0x0023D370
- KEPT `setTEX1_1` (old `func_0023D660`) @ 0x0023D660
- REVERTED `endDisplay` (old `func_0023D420`) @ 0x0023D420 — insn 12: expected `jal	0 <endDisplay>` built `jal	510 <setDMAscTag>`
- REVERTED `setGIFtag` (old `func_0023D518`) @ 0x0023D518 — insn 0: expected `lwc1	$f12,0(gp)` built `addiu	sp,sp,-16`

## ito/mpeg/mv_sub
- KEPT `func_0023E170` (old `func_0023E170`) @ 0x0023E170
- KEPT `func_0023E228` (old `func_0023E228`) @ 0x0023E228
- KEPT `func_0023E280` (old `func_0023E280`) @ 0x0023E280
- KEPT `func_0023E298` (old `func_0023E298`) @ 0x0023E298
- KEPT `func_0023E330` (old `func_0023E330`) @ 0x0023E330
- KEPT `func_0023E368` (old `func_0023E368`) @ 0x0023E368
- KEPT `func_0023EDF0` (old `func_0023EDF0`) @ 0x0023EDF0
- REVERTED `copy2area` (old `func_0023D8A0`) @ 0x0023D8A0 — insn 0: expected `j	0 <copy2area>` built `j	928 <func_0023E170>`
- REVERTED `func_0023E770` (old `func_0023E770`) @ 0x0023E770 — insn 2: expected `j	0 <func_0023E770>` built `j	d30 <func_0023E578>`

## ito/mpeg/mv_vibuf
- KEPT `func_0023EFB0` (old `func_0023EFB0`) @ 0x0023EFB0
- KEPT `viBufReset` (old `func_0023EFF8`) @ 0x0023EFF8
- KEPT `viBufEndPut` (old `func_0023F070`) @ 0x0023F070
- KEPT `viBufFlush` (old `func_0023F160`) @ 0x0023F160
- REVERTED `func_0023F5D0` (old `func_0023F5D0`) @ 0x0023F5D0 — insn 9: expected `jr	ra` built `sw	zero,12(a0)`

## src/GobjProc
- KEPT `GetMaxGObj` (old `func_0023F708`) @ 0x0023F708
- KEPT `GetGObjP` (old `func_0023F740`) @ 0x0023F740
- KEPT `InitCameraGObjs` (old `func_0023F7E0`) @ 0x0023F7E0
- KEPT `func_00240950` (old `func_00240950`) @ 0x00240950
- KEPT `func_00240A20` (old `func_00240A20`) @ 0x00240A20
- REVERTED `PrintGObjID` (old `func_0023F7B0`) @ 0x0023F7B0 — insn 9: expected `jr	ra` built `sw	zero,12(a0)`
- REVERTED `CreateGObjByFuncSet` (old `func_0023F928`) @ 0x0023F928 — insn 4: expected `jal	0 <CreateGObjByFuncSet>` built `jal	12c0 <func_00240950>`
- REVERTED `func_0023FDA0` (old `func_0023FDA0`) @ 0x0023FDA0 — [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

## src/PObj
- KEPT `AllocPObj` (old `func_00240B70`) @ 0x00240B70
- REVERTED `MakeBoundingBox` (old `func_00240B60`) @ 0x00240B60 — src/PObj.c:6: incompatible types in assignment
- REVERTED `MakePacket` (old `func_00240B68`) @ 0x00240B68 — insn 0: expected `jr	ra` built `addiu	v0,gp,0`
- REVERTED `FreePObj` (old `func_00240BD0`) @ 0x00240BD0 — [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)


# Phase 4 — aug6 -> retail body port (`tools/port_from_aug6.py`)

Bodies below were carried over from the aug6 prototype branch's matched C
(clean-room, `main` in AUG6_ROOT) with every aug6 symbol rebound to its
retail counterpart by the lockstep reloc-slot walk.  Nothing here was
hand-tuned: each function either reproduced the retail instruction stream
as-is (`PORTED`) or went straight back to `INCLUDE_ASM` (`REVERTED`, with
the first divergence or compiler diagnostic recorded).  `SKIPPED` = deferred
to the Phase-5 jump-table queue.

Revert-reason classes: `unresolved-symbol` (a reloc slot the walk could not
bind), `callee-sig-conflict` / `arity` (a Phase-3 retail body in the same TU
declares the callee with a placeholder signature the aug6 body contradicts),
`undeclared` / `parse` (decl context), `codegen` (compiles, wrong bytes).

### src/Matrix
- PORTED `_RemakeNormal` w1 @ 0x00117DB0 <- aug6 seki/src/Matrix (2 syms rebound)
- PORTED `_Sqrt` w1 @ 0x00117E70 <- aug6 seki/src/Matrix (2 syms rebound)
- PORTED `_InitCurrentMatrix` w1 @ 0x00117F30 <- aug6 seki/src/Matrix (0 syms rebound)
- PORTED `_TransCurrentMatrix` w1 @ 0x00118000 <- aug6 seki/src/Matrix (0 syms rebound)
- PORTED `_GetCurrentMatrix` w1 @ 0x001181E0 <- aug6 seki/src/Matrix (0 syms rebound)
- PORTED `_GetCurrentMatrixTrans` w1 @ 0x00118268 <- aug6 seki/src/Matrix (0 syms rebound)

### src/fieldCollision
- PORTED `DispCollisionPC` w1 @ 0x00165FB8 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `__ClipWall` w1 @ 0x00166118 <- aug6 fumi/src/fieldCollision (7 syms rebound)
- PORTED `ClipWall` w1 @ 0x00167760 <- aug6 fumi/src/fieldCollision (3 syms rebound)
- PORTED `ClipWallFuchiHangWalkStop` w1 @ 0x00168058 <- aug6 fumi/src/fieldCollision (9 syms rebound)
- PORTED `ChangeFieldCollisionDebugMode` w1 @ 0x00168538 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `LoadCollision` w1 @ 0x00168558 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `DrawCollision` w1 @ 0x00168578 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipPlane` w1 @ 0x00168598 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `GetOrientOfWall` w1 @ 0x001685B8 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- REVERTED `ClipWallEField` w1 @ 0x001683A8 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipWallBoxStop` w1 @ 0x001683C8 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipWallAdjustPos` w1 @ 0x001683E8 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipWallE` w1 @ 0x00168408 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipWallCheckCB` w1 @ 0x00168428 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipWallFieldCheckCB` w1 @ 0x00168448 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipFloor` w1 @ 0x00168468 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipFloorE` w1 @ 0x00168488 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipFloorR` w1 @ 0x001684A8 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipFloorIH` w1 @ 0x001684C8 — [codegen] insn 1: expected `lw	v0,0(gp)` built `sd	ra,0(sp)`
- REVERTED `ClipFloorCheckCB` w1 @ 0x001684E8 — [codegen] insn 0: expected `addiu	sp,sp,-16` built `sw	a1,0(gp)`
- REVERTED `ClipCollision` w1 @ 0x00168510 — [codegen] insn 0: expected `addiu	sp,sp,-16` built `sw	a1,0(gp)`
- REVERTED `SetSimplePlane` w1 @ 0x001685E0 — [codegen] insn 9: expected `lw	v0,0(gp)` built `daddu	a0,s0,zero`

### ios/shockdriver
- PORTED `Vibration_ShotDecode` w1 @ 0x0013B8F0 <- aug6 fumi/ios/shockdriver (2 syms rebound)
- PORTED `Vibration_WaveDecode` w1 @ 0x0013B970 <- aug6 fumi/ios/shockdriver (2 syms rebound)
- PORTED `Shock_SetMotor` w1 @ 0x0013BA20 <- aug6 fumi/ios/shockdriver (5 syms rebound)
- PORTED `ShockRequestBox_Request` w1 @ 0x0013C320 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockRequestBox_DecodeRequest` w1 @ 0x0013C488 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `ShockRequestBox_EndRequestFree` w1 @ 0x0013C4C0 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `ShockDriver_VoiceSet_NumberRegist` w1 @ 0x0013C820 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockDriver_GetShockVoiceMax` w1 @ 0x0013C958 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockDriver_GetShockVoiceSet` w1 @ 0x0013C9D8 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `ShockDriver_GetShockVoice` w1 @ 0x0013CA48 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockRevice_Wave` w1 @ 0x0013CC60 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- REVERTED `ShockEmulator_EmulationShot` w1 @ 0x0013CAD8 — [codegen] ios/shockdriver.c:385: request for member `arr' in something not a structure or union
- REVERTED `Init_ShockRequestAlloc` w1 @ 0x0013CB88 — [codegen] ios/shockdriver.c:397: request for member `arr' in something not a structure or union
- REVERTED `Reset_ShockRequestStruct` w1 @ 0x0013CC00 — [codegen] ios/shockdriver.c:405: request for member `arr' in something not a structure or union

### src/act-game
- PORTED `ACTGameView_Loop` w1 @ 0x00149AE0 <- aug6 fumi/src/act-game (12 syms rebound)
- PORTED `ACTGame_InnerVelocityUpdate` w1 @ 0x00149F70 <- aug6 fumi/src/act-game (3 syms rebound)
- PORTED `ACTGame_BeforeFunc` w1 @ 0x00149FF0 <- aug6 fumi/src/act-game (4 syms rebound)
- PORTED `ActOrientTest` w1 @ 0x0014A100 <- aug6 fumi/src/act-game (1 syms rebound)
- PORTED `GetGirlHandlinkClInfo` w1 @ 0x0014A178 <- aug6 fumi/src/act-game (7 syms rebound)
- PORTED `GetTarget` w1 @ 0x0014A330 <- aug6 fumi/src/act-game (3 syms rebound)
- PORTED `ACTLookTargetSystem_Exec` w1 @ 0x0014A3A8 <- aug6 fumi/src/act-game (3 syms rebound)
- PORTED `ACTGameCollisionOff` w1 @ 0x0014A700 <- aug6 fumi/src/act-game (2 syms rebound)
- PORTED `ACTGame_CheckHandMotion` w1 @ 0x0014A850 <- aug6 fumi/src/act-game (4 syms rebound)
- PORTED `ACTGame_StageChangeGObjID` w1 @ 0x0014A980 <- aug6 fumi/src/act-game (3 syms rebound)
- PORTED `ACTGameView_Init` w1 @ 0x0014AF70 <- aug6 fumi/src/act-game (1 syms rebound)
- PORTED `ACTCharctrl_Lock` w1 @ 0x0014AFB8 <- aug6 fumi/src/act-game (1 syms rebound)
- REVERTED `ACTGame_DisconnectHand` w1 @ 0x0014B090 — [arity] src/act-game.c:489: too few arguments to function `checkHit'
- REVERTED `PAIR_GetPosition_BOY` w1 @ 0x0014B0B8 — [undeclared] src/act-game.c:494: `D_0063226C_flt' undeclared (first use in this function)

### src/commonact
- PORTED `WithMailFunc_WayBeginPosError` w1 @ 0x00157BF8 <- aug6 fumi/src/commonact (2 syms rebound)
- PORTED `actCommonLever` w1 @ 0x00159C38 <- aug6 fumi/src/commonact (8 syms rebound)
- PORTED `funcCommonJumpDircorrect` w1 @ 0x0015D348 <- aug6 fumi/src/commonact (1 syms rebound)
- PORTED `funcCommonError` w1 @ 0x0015EDB8 <- aug6 fumi/src/commonact (4 syms rebound)
- PORTED `SetMotionDirectionSmooze` w1 @ 0x0015EE10 <- aug6 fumi/src/commonact (4 syms rebound)
- PORTED `ACT_LAYOUT_GAMEOVER` w1 @ 0x0015F298 <- aug6 fumi/src/commonact (2 syms rebound)
- PORTED `_ACTMotDirSmzDirect` w1 @ 0x0015F320 <- aug6 fumi/src/commonact (2 syms rebound)
- PORTED `actCommonDelete` w1 @ 0x0015F550 <- aug6 fumi/src/commonact (1 syms rebound)
- REVERTED `WithMailFunc_AttackRejectInQueen` w1 @ 0x00157DC8 — [arity] src/commonact.c:80: too many arguments to function `func_00157DA0'
- REVERTED `GetCorrectOrientOfChain` w1 @ 0x00157E68 — [arity] src/commonact.c:74: too many arguments to function `func_00157DA0'
- REVERTED `actCommonRope` w1 @ 0x001584D8 — [codegen] insn 29: expected `jal	0 <actCommonRope>` built `jal	2050 <func_00158328.9>`
- REVERTED `actCommonSlowrun` w1 @ 0x0015F228 — [parse] src/commonact.c:292: parse error before `D_00292540'
- REVERTED `ACTAdjustPlane` w1 @ 0x0015F2D8 — [codegen] insn 1: expected `lui	at,0xbf80` built `dli	a2,0xbff0`

### src/camera-ico2
- PORTED `CameraSetCameraSet_Default` w1 @ 0x00187418 <- aug6 omori/src/camera-ico2 (4 syms rebound)
- PORTED `GetRootPositionForCamera` w1 @ 0x00187570 <- aug6 omori/src/camera-ico2 (2 syms rebound)
- PORTED `ico2camera_GetTargetPos` w1 @ 0x00187688 <- aug6 omori/src/camera-ico2 (4 syms rebound)
- PORTED `ico2camera_GetGroupNearest` w1 @ 0x001877E0 <- aug6 omori/src/camera-ico2 (2 syms rebound)
- PORTED `initMonitorCamera` w1 @ 0x001878F8 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- PORTED `monitorMonitorCamera` w1 @ 0x00187908 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- PORTED `ChaseCamera` w1 @ 0x00187950 <- aug6 omori/src/camera-ico2 (0 syms rebound)
- PORTED `CameraMove` w1 @ 0x00187990 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- PORTED `ReflectCameraSetBinary` w1 @ 0x001879A8 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- PORTED `SetCameraMatrix_Ico2` w1 @ 0x00187CC0 <- aug6 omori/src/camera-ico2 (7 syms rebound)
- PORTED `GetCameraGroupFromGObj` w1 @ 0x001880C8 <- aug6 omori/src/camera-ico2 (2 syms rebound)
- PORTED `AddPluralCameraSet` w1 @ 0x00188228 <- aug6 omori/src/camera-ico2 (4 syms rebound)
- REVERTED `CameraSetCameraSet` w1 @ 0x001873C0 — [codegen] insn 21: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `InitIco2Camera` w1 @ 0x001879D0 — [callee-sig-conflict] src/camera-ico2.c:15: conflicting types for `func_001D49C0'
- REVERTED `MakeCameraSetBinary` w1 @ 0x001882D0 — [undeclared] src/camera-ico2.c:273: `g_E30' undeclared (first use in this function)
- REVERTED `GetSizeOfCameraSetBinary` w1 @ 0x00188550 — [undeclared] src/camera-ico2.c:234: `D_0062C844_f' undeclared (first use in this function)

### sound/s_init
- PORTED `debug_DispSEInfo` w1 @ 0x00141F58 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundOutputModeGet` w1 @ 0x00143AD0 <- aug6 fumi/sound/s_init (7 syms rebound)
- PORTED `soundDataAreaGet` w1 @ 0x00143CD0 <- aug6 fumi/sound/s_init (1 syms rebound)
- PORTED `soundSeDefPlayWithVolumeRate` w1 @ 0x00144120 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundSeDefVolumeRateGet` w1 @ 0x00144178 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundSeGroupGet` w1 @ 0x00144240 <- aug6 fumi/sound/s_init (2 syms rebound)
- PORTED `soundVBlank` w1 @ 0x00144308 <- aug6 fumi/sound/s_init (2 syms rebound)
- PORTED `soundSeKindBuild` w1 @ 0x00144390 <- aug6 fumi/sound/s_init (6 syms rebound)
- PORTED `soundSeEnvDefaultSet` w1 @ 0x00144500 <- aug6 fumi/sound/s_init (3 syms rebound)

### src/enemy_act
- PORTED `subEnemyCollision` w1 @ 0x0015F9B0 <- aug6 fumi/src/enemy_act (1 syms rebound)
- PORTED `actEnemyForceSwitchToCarry` w1 @ 0x0015FC50 <- aug6 fumi/src/enemy_act (4 syms rebound)
- PORTED `_ApproachTarget_Way` w1 @ 0x00164EB0 <- aug6 fumi/src/enemy_act (3 syms rebound)
- PORTED `actEnemy_GetClingTarget` w1 @ 0x001654E0 <- aug6 fumi/src/enemy_act (1 syms rebound)
- PORTED `IsEnemyBrainToBoy` w1 @ 0x00165CE8 <- aug6 fumi/src/enemy_act (1 syms rebound)
- PORTED `GetEnemyTypeFromGObj` w1 @ 0x00165D18 <- aug6 fumi/src/enemy_act (2 syms rebound)

### src/Matrix

### src/fieldCollision
- PORTED `ClipWallEField` w1 @ 0x001683A8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallBoxStop` w1 @ 0x001683C8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallAdjustPos` w1 @ 0x001683E8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallE` w1 @ 0x00168408 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallCheckCB` w1 @ 0x00168428 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallFieldCheckCB` w1 @ 0x00168448 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloor` w1 @ 0x00168468 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorE` w1 @ 0x00168488 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorR` w1 @ 0x001684A8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorIH` w1 @ 0x001684C8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorCheckCB` w1 @ 0x001684E8 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `ClipCollision` w1 @ 0x00168510 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `SetSimplePlane` w1 @ 0x001685E0 <- aug6 fumi/src/fieldCollision (3 syms rebound)

### ios/shockdriver
- REVERTED `ShockEmulator_EmulationShot` w1 @ 0x0013CAD8 — [codegen] ios/shockdriver.c:385: request for member `arr' in something not a structure or union
- REVERTED `Init_ShockRequestAlloc` w1 @ 0x0013CB88 — [codegen] ios/shockdriver.c:397: request for member `arr' in something not a structure or union
- REVERTED `Reset_ShockRequestStruct` w1 @ 0x0013CC00 — [codegen] ios/shockdriver.c:405: request for member `arr' in something not a structure or union

### src/act-game
- REVERTED `ACTGame_DisconnectHand` w1 @ 0x0014B090 — [arity] src/act-game.c:489: too few arguments to function `checkHit'
- REVERTED `PAIR_GetPosition_BOY` w1 @ 0x0014B0B8 — [undeclared] src/act-game.c:494: `D_0063226C_flt' undeclared (first use in this function)

### src/commonact
- REVERTED `WithMailFunc_AttackRejectInQueen` w1 @ 0x00157DC8 — [arity] src/commonact.c:80: too many arguments to function `func_00157DA0'
- REVERTED `GetCorrectOrientOfChain` w1 @ 0x00157E68 — [arity] src/commonact.c:74: too many arguments to function `func_00157DA0'
- REVERTED `actCommonRope` w1 @ 0x001584D8 — [codegen] insn 29: expected `jal	0 <actCommonRope>` built `jal	2050 <func_00158328.9>`
- REVERTED `actCommonSlowrun` w1 @ 0x0015F228 — [parse] src/commonact.c:292: parse error before `D_00292540'
- REVERTED `ACTAdjustPlane` w1 @ 0x0015F2D8 — [codegen] insn 1: expected `lui	at,0xbf80` built `dli	a2,0xbff0`

### src/camera-ico2
- REVERTED `CameraSetCameraSet` w1 @ 0x001873C0 — [codegen] insn 21: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `InitIco2Camera` w1 @ 0x001879D0 — [callee-sig-conflict] src/camera-ico2.c:15: conflicting types for `func_001D49C0'
- REVERTED `MakeCameraSetBinary` w1 @ 0x001882D0 — [undeclared] src/camera-ico2.c:273: `g_E30' undeclared (first use in this function)
- REVERTED `GetSizeOfCameraSetBinary` w1 @ 0x00188550 — [undeclared] src/camera-ico2.c:234: `D_0062C844_f' undeclared (first use in this function)

### sound/s_init

### src/enemy_act

### ios/thread
- PORTED `iosThreadCreateS` w1 @ 0x0013CCE8 <- aug6 fumi/ios/thread (0 syms rebound)
- PORTED `iosThreadStart` w1 @ 0x0013CD30 <- aug6 fumi/ios/thread (0 syms rebound)
- PORTED `iosThreadName` w1 @ 0x0013CF70 <- aug6 fumi/ios/thread (0 syms rebound)
- PORTED `iosSemaSignal` w1 @ 0x0013D498 <- aug6 fumi/ios/thread (9 syms rebound)
- REVERTED `iosThreadMain` w1 @ 0x0013CC78 — [codegen] insn 27: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosThreadMessage` w1 @ 0x0013CF38 — [codegen] insn 2: expected `addiu	v0,v0,0` built `addiu	v0,v0,184`
- REVERTED `iosGetIOSThreadFromId` w1 @ 0x0013D140 — [callee-sig-conflict] ios/thread.c:173: conflicting types for `iosSemaWait'

### isys/gobj
- PORTED `isysGObjMoveAfterGObj` w1 @ 0x0013E868 <- aug6 fumi/isys/gobj (2 syms rebound)
- PORTED `isysGObjAddHead` w1 @ 0x0013EAE8 <- aug6 fumi/isys/gobj (2 syms rebound)
- REVERTED `isysGObjKindTableInit` w1 @ 0x0013DDA0 — [codegen] insn 1: expected `lui	v1,0x0` built `lui	v0,0x0`
- REVERTED `isysGObjInit` w1 @ 0x0013DDF8 — [codegen] insn 1: expected `bnel	a1,zero,18 <isysGObjInit+0x18>` built `bnel	a1,zero,6c <isysGObjInit+0x14>`
- REVERTED `isysGObjRemoveAll` w1 @ 0x0013DFF0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `add_gobj_to_tail` w1 @ 0x0013E0C0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `isysGObjMoveHead` w1 @ 0x0013E220 — [undeclared] isys/gobj.c:35: structure has no member named `f_0'
- REVERTED `isysGObjAddAfterGObj` w1 @ 0x0013E350 — [undeclared] isys/gobj.c:39: structure has no member named `f_0'
- REVERTED `isysGetNbAllocedGObjs` w1 @ 0x0013E4D0 — [codegen] insn 3: expected `lui	a2,0x0` built `daddu	s0,a0,zero`
- REVERTED `isysGObjKindTableRemove` w1 @ 0x0013E7F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `isysGObjMoveBeforeGObj` w1 @ 0x0013E8D8 — [undeclared] isys/gobj.c:80: structure has no member named `f_0'
- REVERTED `isysGObjAdd` w1 @ 0x0013E9E0 — [undeclared] isys/gobj.c:82: structure has no member named `f_0'
- REVERTED `isysGObjSearchFromObjKindID_begin` w1 @ 0x0013EBE0 — [undeclared] isys/gobj.c:94: structure has no member named `pad_C'

### src/camera-editor
- PORTED `saveEditedData` w1 @ 0x00182C18 <- aug6 omori/src/camera-editor (0 syms rebound)
- PORTED `gif_test` w1 @ 0x00182C68 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `DispCameraGroup` w1 @ 0x00182D20 <- aug6 omori/src/camera-editor (7 syms rebound)
- PORTED `dispCameraPinType2` w1 @ 0x00183218 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `menuGroupSelect` w1 @ 0x001848A0 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `CameraEdit_del_pin` w1 @ 0x00187280 <- aug6 omori/src/camera-editor (3 syms rebound)
- PORTED `CameraEdit_DispBox` w1 @ 0x001872B8 <- aug6 omori/src/camera-editor (3 syms rebound)
- PORTED `CameraEdit_Save` w1 @ 0x00187308 <- aug6 omori/src/camera-editor (2 syms rebound)
- PORTED `debug_NMarker` w1 @ 0x00187318 <- aug6 omori/src/camera-editor (2 syms rebound)
- REVERTED `_CameraEdit_del_box` w1 @ 0x001869F8 — [codegen] insn 2: expected `addiu	a0,a0,0` built `addiu	a0,a0,10864`
- REVERTED `debug_Marker` w1 @ 0x00187328 — [codegen] insn 15: expected `mtc1	zero,$f13` built `jal	0 <EnterMenu>`

### src/gamesys
- PORTED `gamesysObjInfoLoad` w1 @ 0x001AAEC0 <- aug6 common/src/gamesys (1 syms rebound)
- PORTED `gamesysBackStageProcess` w1 @ 0x001AAFC8 <- aug6 common/src/gamesys (6 syms rebound)
- PORTED `gamesysGeneratorInfoLoad` w1 @ 0x001AB058 <- aug6 common/src/gamesys (8 syms rebound)
- PORTED `gamesysObjInfoStageInitFlagCls` w1 @ 0x001AB190 <- aug6 common/src/gamesys (2 syms rebound)
- PORTED `gamesysMemoryLoad` w1 @ 0x001ABEB8 <- aug6 common/src/gamesys (4 syms rebound)
- PORTED `gamesysGeneratorInfoSave` w1 @ 0x001AC300 <- aug6 common/src/gamesys (2 syms rebound)
- REVERTED `gamesysObjInfoCls` w1 @ 0x001AB3D0 — [unresolved-symbol] unresolved-symbol: insn 7 `D_20000150`: no retail lui partner for %lo (+3 more)

### ios/cdvd
- PORTED `iosCdvdMgrSearchFile` w1 @ 0x001301D8 <- aug6 fumi/ios/cdvd (3 syms rebound)
- PORTED `iosCdvdDiskReady` w1 @ 0x00132038 <- aug6 fumi/ios/cdvd (4 syms rebound)
- PORTED `iosCdvdLoad` w1 @ 0x001320E8 <- aug6 fumi/ios/cdvd (3 syms rebound)
- PORTED `iosCdvdBackGroundMgr` w1 @ 0x001325D8 <- aug6 fumi/ios/cdvd (2 syms rebound)
- PORTED `iosCdvdDirectStOpen` w1 @ 0x00132610 <- aug6 fumi/ios/cdvd (2 syms rebound)
- PORTED `iosCdvdBackGroundMgrNotDiskReadyPauseSet` w1 @ 0x001333C8 <- aug6 fumi/ios/cdvd (5 syms rebound)
- PORTED `iosCdvdBackGroundMgrSeek` w1 @ 0x00133460 <- aug6 fumi/ios/cdvd (0 syms rebound)
- REVERTED `iosCdvdMgrPackLoad` w1 @ 0x001312F0 — [undeclared] ios/cdvd.c:138: `D_tbl_0027E520' undeclared (first use in this function)

### ito/mpeg/mv_disp
- PORTED `setImageSize` w1 @ 0x0023D050 <- aug6 ito/mpeg/mv_disp (6 syms rebound)
- PORTED `dispCreate` w1 @ 0x0023D0F0 <- aug6 ito/mpeg/mv_disp (7 syms rebound)
- PORTED `dispSetTags` w1 @ 0x0023D170 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `dispSwitch` w1 @ 0x0023D1D0 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `dispDelete` w1 @ 0x0023D2E8 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `loadImage` w1 @ 0x0023D348 <- aug6 ito/mpeg/mv_disp (2 syms rebound)
- PORTED `setTEXFLUSH` w1 @ 0x0023D5A8 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `setPRIM` w1 @ 0x0023D6E8 <- aug6 ito/mpeg/mv_disp (3 syms rebound)
- PORTED `setUV` w1 @ 0x0023D750 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- REVERTED `startDisplay` w1 @ 0x0023D390 — [arity] ito/mpeg/mv_disp.c:158: too many arguments to function `UpdateRootPosition'

### ito/mpeg/mv_vibuf
- PORTED `viBufCreate` w1 @ 0x0023EFB8 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufBeginPut` w1 @ 0x0023F030 <- aug6 ito/mpeg/mv_vibuf (4 syms rebound)
- PORTED `viBufAddDMA` w1 @ 0x0023F080 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufStopDMA` w1 @ 0x0023F0D8 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufRestartDMA` w1 @ 0x0023F130 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufModifyPts` w1 @ 0x0023F180 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufGetTs` w1 @ 0x0023F200 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufDelete` w1 @ 0x0023F2B8 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufCount` w1 @ 0x0023F350 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufPutTs` w1 @ 0x0023F398 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)

### src/Packet
- PORTED `pac_DispQW` w1 @ 0x00118A68 <- aug6 seki/src/Packet (0 syms rebound)
- PORTED `pac_makeClusterStrip` w1 @ 0x00118E88 <- aug6 seki/src/Packet (7 syms rebound)
- PORTED `pac_setMaterialPacket` w1 @ 0x0011A238 <- aug6 seki/src/Packet (5 syms rebound)
- PORTED `pac_makeMaterialTable` w1 @ 0x0011A2A8 <- aug6 seki/src/Packet (3 syms rebound)
- REVERTED `pac_getWeight` w1 @ 0x00118C68 — [missing-body] aug6 body not found in seki/src/Packet.c
- REVERTED `pac_setGifTag` w1 @ 0x001191C0 — [missing-body] aug6 body not found in seki/src/Packet.c
- REVERTED `pac_closeTag` w1 @ 0x00119350 — [missing-body] aug6 body not found in seki/src/Packet.c
- SKIPPED `pac_makeNormalStrip` w1 @ 0x00118B18 — jtbl
- SKIPPED `pac_setVifEndCode` w1 @ 0x00118FD8 — jtbl

### src/boyact
- PORTED `InitSwapWeapon` w1 @ 0x001502D8 <- aug6 fumi/src/boyact (3 syms rebound)
- PORTED `actBoyBelift` w1 @ 0x00154218 <- aug6 fumi/src/boyact (7 syms rebound)
- PORTED `actBoyDitch3mReady` w1 @ 0x00154420 <- aug6 fumi/src/boyact (1 syms rebound)
- PORTED `actBoyReadyMove` w1 @ 0x001548F0 <- aug6 fumi/src/boyact (2 syms rebound)
- PORTED `actBoyBeslam` w1 @ 0x001549B8 <- aug6 fumi/src/boyact (7 syms rebound)
- REVERTED `UpdateGeo` w1 @ 0x0014E488 — [missing-body] aug6 body not found in fumi/src/boyact.c
- REVERTED `subBoyCollision` w1 @ 0x001521F0 — [codegen] insn 44: expected `lui	at,0x4348` built `lui	at,0x43e1`
- REVERTED `actBoyDitch3mExec` w1 @ 0x00154DD0 — [undeclared] src/boyact.c:356: `dst60_a' undeclared (first use in this function)

### src/way_util
- PORTED `visible_waypoint_of_all_except_gid_ThreadVersion` w1 @ 0x00178908 <- aug6 fumi/src/way_util (1 syms rebound)
- PORTED `nearest_waypoint_by_lineseg` w1 @ 0x0017A230 <- aug6 fumi/src/way_util (5 syms rebound)
- PORTED `nearest_waypoint_by_lineseg_of_group_from_gobj` w1 @ 0x0017A2C8 <- aug6 fumi/src/way_util (6 syms rebound)
- PORTED `visible_waypoint_of_all_from_gobj` w1 @ 0x0017A788 <- aug6 fumi/src/way_util (5 syms rebound)
- PORTED `visible_waypoint_from_gobj` w1 @ 0x0017A910 <- aug6 fumi/src/way_util (5 syms rebound)
- PORTED `get_wp_nearest_bridge_side_me` w1 @ 0x0017A9B8 <- aug6 fumi/src/way_util (1 syms rebound)
- PORTED `wpsort_compfnc` w1 @ 0x0017AF40 <- aug6 fumi/src/way_util (1 syms rebound)
- REVERTED `visible_waypoint_of_all_except_temp_ThreadVersion` w1 @ 0x00178930 — [undeclared] src/way_util.c:44: `D_004C7CF0_ve' undeclared (first use in this function)
- REVERTED `bridge_waypoint_side_bridge` w1 @ 0x0017AD68 — [undeclared] src/way_util.c:301: `wcf_c' undeclared (first use in this function)
- REVERTED `waypoint_connect_group_side_bridge` w1 @ 0x0017ADF8 — [undeclared] src/way_util.c:303: `wcf_c' undeclared (first use in this function)
- REVERTED `NearestWgFromTarget` w1 @ 0x0017AE98 — [undeclared] src/way_util.c:305: `wcf_c' undeclared (first use in this function)

### src/quaternion
- PORTED `InitQuaternionDrive` w1 @ 0x0010D4A8 <- aug6 sugipon/src/quaternion (7 syms rebound)
- PORTED `getQuaternionFromMatrix` w1 @ 0x0010D540 <- aug6 sugipon/src/quaternion (3 syms rebound)
- PORTED `CopyQuaternion` w1 @ 0x0010D7F8 <- aug6 sugipon/src/quaternion (2 syms rebound)
- PORTED `GetSlerpQuaternionNoRegularize` w1 @ 0x0010D878 <- aug6 sugipon/src/quaternion (2 syms rebound)
- REVERTED `RegularizeQuaternion` w1 @ 0x0010D838 — [arity] src/quaternion.c:149: too few arguments to function `GetInverseQuaternion'

### src/st25a
- PORTED `actSt25aQueenDeadChk` w1 @ 0x0017E188 <- aug6 script/src/st25a (1 syms rebound)
- PORTED `actConte13Jimaku` w1 @ 0x0017E1A8 <- aug6 script/src/st25a (3 syms rebound)
- PORTED `actSt25aGenerator` w1 @ 0x0017E270 <- aug6 script/src/st25a (3 syms rebound)
- PORTED `actSt25aQueenDead` w1 @ 0x0017E330 <- aug6 script/src/st25a (1 syms rebound)
- PORTED `actSt25aQueenBeforeChk` w1 @ 0x0017E550 <- aug6 script/src/st25a (6 syms rebound)

### sound/adpcm_init
- PORTED `AdpcmClose` w1 @ 0x00140710 <- aug6 fumi/sound/adpcm_init (3 syms rebound)
- PORTED `AdpcmIopBuffAlloc` w1 @ 0x00140B30 <- aug6 fumi/sound/adpcm_init (1 syms rebound)
- PORTED `AdpcmOpenSync` w1 @ 0x00140B60 <- aug6 fumi/sound/adpcm_init (1 syms rebound)
- PORTED `AdpcmUseAreaGet` w1 @ 0x00140CE0 <- aug6 fumi/sound/adpcm_init (4 syms rebound)
- PORTED `AdpcmFreeAreaGet` w1 @ 0x00140E48 <- aug6 fumi/sound/adpcm_init (6 syms rebound)
- REVERTED `GetDitchPosition` w1 @ 0x00140F90 — [arity] sound/adpcm_init.c:155: too few arguments to function `adpcmPauseRequest'

### src/layout_action
- PORTED `_la_set_current_port_2` w1 @ 0x001B4E78 <- aug6 common/src/layout_action (5 syms rebound)
- REVERTED `_la_memory_card_check` w1 @ 0x001B4D48 — [parse] src/layout_action.c:46: parse error before `D_00274EC0'
- REVERTED `_la_set_preview_info` w1 @ 0x001B4FC8 — [parse] src/layout_action.c:108: parse error before `D_00275250'

### isys/gobj
- PORTED `isysGObjSearchFromObjKindID_begin` w1 @ 0x0013EBE0 <- aug6 fumi/isys/gobj (3 syms rebound)
- REVERTED `isysGObjKindTableInit` w1 @ 0x0013DDA0 — [codegen] insn 1: expected `lui	v1,0x0` built `lui	v0,0x0`
- REVERTED `isysGObjInit` w1 @ 0x0013DDF8 — [codegen] insn 1: expected `bnel	a1,zero,18 <isysGObjInit+0x18>` built `bnel	a1,zero,6c <isysGObjInit+0x14>`
- REVERTED `isysGObjRemoveAll` w1 @ 0x0013DFF0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `add_gobj_to_tail` w1 @ 0x0013E0C0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `isysGObjMoveHead` w1 @ 0x0013E220 — [codegen] insn 20: expected `bne	a0,a2,6c <isysGObjMoveHead+0x6c>` built `bne	a0,a2,4e8 <isysGObjMoveHead+0x68>`
- REVERTED `isysGObjAddAfterGObj` w1 @ 0x0013E350 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGetNbAllocedGObjs` w1 @ 0x0013E4D0 — [codegen] insn 3: expected `lui	a2,0x0` built `daddu	s0,a0,zero`
- REVERTED `isysGObjKindTableRemove` w1 @ 0x0013E7F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `isysGObjMoveBeforeGObj` w1 @ 0x0013E8D8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjAdd` w1 @ 0x0013E9E0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

### src/Matrix

### src/fieldCollision

### ios/shockdriver
- PORTED `ShockEmulator_EmulationShot` w1 @ 0x0013CAD8 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `Init_ShockRequestAlloc` w1 @ 0x0013CB88 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `Reset_ShockRequestStruct` w1 @ 0x0013CC00 <- aug6 fumi/ios/shockdriver (1 syms rebound)

### src/act-game
- PORTED `ACTGame_DisconnectHand` w1 @ 0x0014B090 <- aug6 fumi/src/act-game (1 syms rebound)

### src/commonact
- PORTED `WithMailFunc_AttackRejectInQueen` w1 @ 0x00157DC8 <- aug6 fumi/src/commonact (5 syms rebound)
- PORTED `GetCorrectOrientOfChain` w1 @ 0x00157E68 <- aug6 fumi/src/commonact (2 syms rebound)
- REVERTED `actCommonRope` w1 @ 0x001584D8 — [codegen] insn 29: expected `jal	0 <actCommonRope>` built `jal	2050 <func_00158328.15>`

### src/camera-ico2
- REVERTED `CameraSetCameraSet` w1 @ 0x001873C0 — [codegen] insn 21: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `InitIco2Camera` w1 @ 0x001879D0 — [callee-sig-conflict] src/camera-ico2.c:15: conflicting types for `func_001D49C0'

### sound/s_init

### src/enemy_act

### ios/thread
- PORTED `iosGetIOSThreadFromId` w1 @ 0x0013D140 <- aug6 fumi/ios/thread (3 syms rebound)
- REVERTED `iosThreadMain` w1 @ 0x0013CC78 — [codegen] insn 27: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosThreadMessage` w1 @ 0x0013CF38 — [codegen] insn 2: expected `addiu	v0,v0,0` built `addiu	v0,v0,184`

### isys/gobj
- REVERTED `isysGObjKindTableInit` w1 @ 0x0013DDA0 — [codegen] insn 1: expected `lui	v1,0x0` built `lui	v0,0x0`
- REVERTED `isysGObjInit` w1 @ 0x0013DDF8 — [codegen] insn 1: expected `bnel	a1,zero,18 <isysGObjInit+0x18>` built `bnel	a1,zero,6c <isysGObjInit+0x14>`
- REVERTED `isysGObjRemoveAll` w1 @ 0x0013DFF0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `add_gobj_to_tail` w1 @ 0x0013E0C0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `isysGObjMoveHead` w1 @ 0x0013E220 — [codegen] insn 20: expected `bne	a0,a2,6c <isysGObjMoveHead+0x6c>` built `bne	a0,a2,4e8 <isysGObjMoveHead+0x68>`
- REVERTED `isysGObjAddAfterGObj` w1 @ 0x0013E350 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGetNbAllocedGObjs` w1 @ 0x0013E4D0 — [codegen] insn 3: expected `lui	a2,0x0` built `daddu	s0,a0,zero`
- REVERTED `isysGObjKindTableRemove` w1 @ 0x0013E7F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `isysGObjMoveBeforeGObj` w1 @ 0x0013E8D8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjAdd` w1 @ 0x0013E9E0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

### src/camera-editor
- REVERTED `_CameraEdit_del_box` w1 @ 0x001869F8 — [codegen] insn 2: expected `addiu	a0,a0,0` built `addiu	a0,a0,10864`

### src/gamesys
- REVERTED `gamesysObjInfoCls` w1 @ 0x001AB3D0 — [unresolved-symbol] unresolved-symbol: insn 7 `D_20000150`: no retail lui partner for %lo (+3 more)

### ios/cdvd

### ito/mpeg/mv_disp
- REVERTED `startDisplay` w1 @ 0x0023D390 — [arity] ito/mpeg/mv_disp.c:158: too many arguments to function `UpdateRootPosition'

### ito/mpeg/mv_vibuf

### src/way_util

### src/boyact
- REVERTED `subBoyCollision` w1 @ 0x001521F0 — [codegen] insn 44: expected `lui	at,0x4348` built `lui	at,0x43e1`

### src/quaternion
- PORTED `RegularizeQuaternion` w1 @ 0x0010D838 <- aug6 sugipon/src/quaternion (2 syms rebound)

### src/st25a

### sound/adpcm_init
- PORTED `GetDitchPosition` w1 @ 0x00140F90 <- aug6 fumi/src/act-env (2 syms rebound)

### src/layout_action
- PORTED `_la_memory_card_check` w1 @ 0x001B4D48 <- aug6 common/src/layout_action (9 syms rebound)
- PORTED `_la_set_preview_info` w1 @ 0x001B4FC8 <- aug6 common/src/layout_action (10 syms rebound)

### src/matrixDrive

### isys/gobj_process
- PORTED `isysGObjProcAdd_` w1 @ 0x0013F308 <- aug6 fumi/isys/gobj_process (2 syms rebound)
- PORTED `cut_gobj_process_link` w1 @ 0x0013F378 <- aug6 fumi/isys/gobj_process (2 syms rebound)
- PORTED `isysGObjProcAddS` w1 @ 0x0013F6B8 <- aug6 fumi/isys/gobj_process (2 syms rebound)
- PORTED `isysGObjProcAddGOppArg` w1 @ 0x0013F700 <- aug6 fumi/isys/gobj_process (5 syms rebound)
- PORTED `isysGObjProcPause` w1 @ 0x0013F778 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- PORTED `isysGObjProcPauseAll` w1 @ 0x0013F7A8 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- PORTED `isysGObjProcPausePtr` w1 @ 0x0013F7D8 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- REVERTED `isysGObjProcessInit` w1 @ 0x0013F2C8 — [codegen] insn 15: expected `<end>` built `sll	zero,zero,0x0`

### src/Packet
- SKIPPED `pac_setVifEndCode` w1 @ 0x00118FD8 — jtbl

### src/camera-root
- PORTED `MakeCameraMatrix` w1 @ 0x0018BEB0 <- aug6 omori/src/camera-root (8 syms rebound)
- PORTED `CameraEditManual` w1 @ 0x0018BF70 <- aug6 omori/src/camera-root (12 syms rebound)
- PORTED `DebugCameraManual` w1 @ 0x0018C078 <- aug6 omori/src/camera-root (3 syms rebound)
- PORTED `Camctrl_SetTarget` w1 @ 0x0018CB20 <- aug6 omori/src/camera-root (5 syms rebound)

### src/clothAnimation
- PORTED `GetChainAnimation` w1 @ 0x001C5FD0 <- aug6 sugipon/src/clothAnimation (12 syms rebound)
- PORTED `getCloth4D_preProcess` w1 @ 0x001C8958 <- aug6 sugipon/src/clothAnimation (5 syms rebound)
- PORTED `InitCloth4D` w1 @ 0x001C8B60 <- aug6 sugipon/src/clothAnimation (2 syms rebound)

### src/girl_act
- PORTED `GetEyeDirection` w1 @ 0x0016A460 <- aug6 fumi/src/girl_act (2 syms rebound)
- PORTED `subGirlControl` w1 @ 0x0016BCA0 <- aug6 fumi/src/girl_act (5 syms rebound)
- PORTED `subGirlCollision` w1 @ 0x0016BCF0 <- aug6 fumi/src/girl_act (2 syms rebound)
- PORTED `actGirlStand` w1 @ 0x00173268 <- aug6 fumi/src/girl_act (2 syms rebound)
- PORTED `afterGirlHand` w1 @ 0x00175640 <- aug6 fumi/src/girl_act (3 syms rebound)
- PORTED `afterGirlPulledGo` w1 @ 0x00175688 <- aug6 fumi/src/girl_act (3 syms rebound)
- REVERTED `actGirlSupportGBLoop` w1 @ 0x00171AB0 — [codegen] insn 6: expected `beq	a1,zero,f8 <actGirlSupportGBLoop+0xf8>` built `beq	a1,zero,774c <actGirlSupportGBLoop+0xfc>`

### src/motionManager2
- PORTED `GetStreamMotion` w1 @ 0x001097A0 <- aug6 sugipon/src/motionManager2 (3 syms rebound)
- PORTED `CheckFloorAttribute` w1 @ 0x0010A0C8 <- aug6 sugipon/src/motionManager2 (0 syms rebound)
- PORTED `SetMotionPlaySpeedRatio` w1 @ 0x0010A598 <- aug6 sugipon/src/motionManager2 (0 syms rebound)
- REVERTED `calcFootIK` w1 @ 0x00107778 — [unresolved-symbol] unresolved-symbol: insn 6 `D_0062BF0C`: retail symbol D_00633C0C (0x00633C0C) undefined

### src/script
- PORTED `scpTorchLightOff` w1 @ 0x0017CB60 <- aug6 script/src/script (5 syms rebound)
- PORTED `scpPlayStart` w1 @ 0x0017D030 <- aug6 script/src/script (1 syms rebound)
- PORTED `scpDoorTypeUpUp` w1 @ 0x0017D230 <- aug6 script/src/script (2 syms rebound)
- REVERTED `scpTorchLightOn` w1 @ 0x0017CB20 — [codegen] insn 15: expected `<end>` built `sll	zero,zero,0x0`

### ios/message
- PORTED `iosMsgQueueDestroyAll` w1 @ 0x0013A7C8 <- aug6 fumi/ios/message (2 syms rebound)
- REVERTED `iosMsgQueueCreate` w1 @ 0x0013A220 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosMsgQueueDestroy` w1 @ 0x0013A250 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `send_signal_message` w1 @ 0x0013A2F8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgSetEvent` w1 @ 0x0013A380 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgSend` w1 @ 0x0013A5B8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgRecv` w1 @ 0x0013A6C0 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

### ios/pad
- PORTED `controler_stable_check` w1 @ 0x0013A820 <- aug6 fumi/ios/pad (3 syms rebound)
- PORTED `iosPadGetPort` w1 @ 0x0013B718 <- aug6 fumi/ios/pad (2 syms rebound)
- PORTED `iosPadGetSlot` w1 @ 0x0013B748 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadGetDevice` w1 @ 0x0013B760 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadConnect` w1 @ 0x0013B778 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadStickCameraCoord` w1 @ 0x0013B7C0 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadActStop` w1 @ 0x0013B878 <- aug6 fumi/ios/pad (8 syms rebound)

### src/GobjProc
- PORTED `GetGObjId` w1 @ 0x0023F778 <- aug6 common/src/GobjProc (0 syms rebound)
- PORTED `PrintGObjID` w1 @ 0x0023F7B0 <- aug6 common/src/GobjProc (0 syms rebound)
- PORTED `CreateGObj` w1 @ 0x0023F7F0 <- aug6 common/src/GobjProc (1 syms rebound)
- PORTED `CreateGObjByFuncSet` w1 @ 0x0023F928 <- aug6 common/src/GobjProc (1 syms rebound)
- REVERTED `ResetGObjProc` w1 @ 0x0023F690 — [codegen] insn 29: expected `<end>` built `sll	zero,zero,0x0`

### src/GsBase
- PORTED `gsb_SetFrame` w1 @ 0x00111FA8 <- aug6 seki/src/GsBase (2 syms rebound)
- PORTED `gsb_Reduction` w1 @ 0x00112148 <- aug6 seki/src/GsBase (1 syms rebound)
- PORTED `gsb_fade` w1 @ 0x001121E0 <- aug6 seki/src/GsBase (3 syms rebound)
- PORTED `gsb_scissorOnDemo` w1 @ 0x00112260 <- aug6 seki/src/GsBase (0 syms rebound)
- PORTED `gsb_PostEffect` w1 @ 0x001137B8 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_InitGSSystem` w1 @ 0x00113820 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_UpdateGSSystem` w1 @ 0x00113890 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_ResetGSSystem` w1 @ 0x00113908 <- aug6 seki/src/GsBase (5 syms rebound)

### src/st13b
- PORTED `actSt13bFloorChk` w1 @ 0x002297D8 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actSt13bConte02` w1 @ 0x00229890 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actSt13bSekizoChk` w1 @ 0x00229960 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actSt13bMeetAgain` w1 @ 0x00229AA8 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actSt13bBoss` w1 @ 0x00229B60 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actConte10b` w1 @ 0x00229C30 <- aug6 script/src/st13b (5 syms rebound)

### src/way_llf
- PORTED `CreateWayGroup` w1 @ 0x002059A0 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `DeleteWayGroup` w1 @ 0x00205A38 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `CloseWayGroup` w1 @ 0x00205A78 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `CreateWayPoint` w1 @ 0x00205A98 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `AddWayPointTop` w1 @ 0x00205B30 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `WayBridge_begin` w1 @ 0x002060E8 <- aug6 fumi/src/way_llf (14 syms rebound)

### isys/gobj_dl
- PORTED `isysGObjRemoveObjDL` w1 @ 0x0013ECA8 <- aug6 fumi/isys/gobj_dl (2 syms rebound)
- PORTED `isysGObjLinkObjDLAfterGObj` w1 @ 0x0013EFD0 <- aug6 fumi/isys/gobj_dl (2 syms rebound)
- PORTED `isysGObjMoveObjDLBeforeGObj` w1 @ 0x0013F1D0 <- aug6 fumi/isys/gobj_dl (1 syms rebound)
- REVERTED `cut_gobj_dl_link` w1 @ 0x0013EC50 — [codegen] insn 21: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `isysGObjMoveObjDLHead` w1 @ 0x0013EDB0 — [codegen] insn 1: expected `bnel	a1,zero,18 <isysGObjMoveObjDLHead+0x18>` built `bnel	a1,zero,174 <isysGObjMoveObjDLHead+0x14>`
- REVERTED `isysGObjLinkObjDLHead` w1 @ 0x0013EE60 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s2,a2,zero`
- REVERTED `isysGObjMoveObjDLAfterGObj` w1 @ 0x0013F130 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s4,a3,zero`

### isys/obj_manager
- PORTED `iosOmSearchGObjId` w1 @ 0x0013FF20 <- aug6 fumi/isys/obj_manager (1 syms rebound)

### ito/mpeg/mv_audiodec
- PORTED `audioDecSendToIOP` w1 @ 0x0023C5F0 <- aug6 ito/mpeg/mv_audiodec (2 syms rebound)
- PORTED `audioDecReset` w1 @ 0x0023C808 <- aug6 ito/mpeg/mv_audiodec (5 syms rebound)
- PORTED `audioDecIsPreset` w1 @ 0x0023C890 <- aug6 ito/mpeg/mv_audiodec (5 syms rebound)
- PORTED `audioDecStart` w1 @ 0x0023C908 <- aug6 ito/mpeg/mv_audiodec (8 syms rebound)
- PORTED `audioDecResume` w1 @ 0x0023CA08 <- aug6 ito/mpeg/mv_audiodec (2 syms rebound)

### src/DisplayList
- PORTED `dl_PushPriority` w1 @ 0x001FB4A8 <- aug6 seki/src/DisplayList (5 syms rebound)
- PORTED `dl_Debug` w1 @ 0x001FB5E0 <- aug6 seki/src/DisplayList (7 syms rebound)
- PORTED `dl_CloseDma` w1 @ 0x001FB658 <- aug6 seki/src/DisplayList (9 syms rebound)
- PORTED `dl_Out` w1 @ 0x001FB768 <- aug6 seki/src/DisplayList (9 syms rebound)
- PORTED `dl_SetDLPriority` w1 @ 0x001FB7F8 <- aug6 seki/src/DisplayList (9 syms rebound)

### src/StageManager
- PORTED `StageManager` w1 @ 0x0019FF98 <- aug6 common/src/StageManager (1 syms rebound)
- REVERTED `stop_free_resources` w1 @ 0x0019F6A8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `exit_stage` w1 @ 0x0019F7A8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `stgmgrForceSwitch` w1 @ 0x0019FFA8 — [callee-sig-conflict] src/StageManager.c:61: conflicting types for `stgmgrForceSwitch'

### src/way_llf
- PORTED `CreateWayGroup` w1 @ 0x002059A0 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `DeleteWayGroup` w1 @ 0x00205A38 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `CloseWayGroup` w1 @ 0x00205A78 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `CreateWayPoint` w1 @ 0x00205A98 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `AddWayPointTop` w1 @ 0x00205B30 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `WayBridge_begin` w1 @ 0x002060E8 <- aug6 fumi/src/way_llf (14 syms rebound)

### src/act
- PORTED `actChangeActMain` w1 @ 0x00201E70 <- aug6 fumi/src/act (7 syms rebound)
- PORTED `actCreateMotionThread` w1 @ 0x00201F38 <- aug6 fumi/src/act (6 syms rebound)
- PORTED `_ACTRun` w1 @ 0x00203A58 <- aug6 fumi/src/act (1 syms rebound)
- PORTED `_ACTWait` w1 @ 0x00203AA0 <- aug6 fumi/src/act (2 syms rebound)
- PORTED `actCreateSubThread` w1 @ 0x00203B78 <- aug6 fumi/src/act (7 syms rebound)
- REVERTED `actChangeActBrain` w1 @ 0x00201DE0 — [codegen] insn 9: expected `jal	0 <actChangeActBrain>` built `jal	1d98 <actCreateSubThread>`

### src/gv
- PORTED `_DistxzGV` w1 @ 0x00193D30 <- aug6 omori/src/gv (3 syms rebound)
- PORTED `_RotyGV` w1 @ 0x00193E48 <- aug6 omori/src/gv (1 syms rebound)
- PORTED `_GetDirection` w1 @ 0x00193F68 <- aug6 omori/src/gv (0 syms rebound)
- PORTED `_RotGVF` w1 @ 0x00193FA8 <- aug6 omori/src/gv (1 syms rebound)
- PORTED `_OrientXZGV` w1 @ 0x00194020 <- aug6 omori/src/gv (3 syms rebound)

### src/particleEffect
- PORTED `ExecParticleEffects` w1 @ 0x001E8598 <- aug6 sugipon/src/particleEffect (4 syms rebound)
- PORTED `InitParticleEffects` w1 @ 0x001E8930 <- aug6 sugipon/src/particleEffect (5 syms rebound)
- REVERTED `ResetParticleEffectPackages` w1 @ 0x001E85D8 — [undeclared] src/particleEffect.c:51: `D_007097F0' undeclared (first use in this function)
- REVERTED `DeleteParticleEffect` w1 @ 0x001E89F8 — [undeclared] src/particleEffect.c:69: `D_007097F0' undeclared (first use in this function)
- REVERTED `SetParticleEffectActiveSensing` w1 @ 0x001E8A60 — [undeclared] src/particleEffect.c:70: `D_007097F0' undeclared (first use in this function)

### src/st02a
- PORTED `actSt02aDoor` w1 @ 0x002111D8 <- aug6 script/src/st02a (6 syms rebound)
- PORTED `actSt02aDoorUpChk` w1 @ 0x00211290 <- aug6 script/src/st02a (6 syms rebound)
- PORTED `actSt02aDoorDownChk` w1 @ 0x00211338 <- aug6 script/src/st02a (6 syms rebound)
- PORTED `actSt02WaterFallBoySplashCheck` w1 @ 0x002113C8 <- aug6 script/src/st02a (5 syms rebound)
- PORTED `actSt02aWaterFallChk` w1 @ 0x00211438 <- aug6 script/src/st02a (5 syms rebound)
- PORTED `actSt02aGondolaUp` w1 @ 0x002114A8 <- aug6 script/src/st02a (5 syms rebound)
- PORTED `actSt02aTakiWay` w1 @ 0x00211BE8 <- aug6 script/src/st02a (7 syms rebound)

### src/st19a
- PORTED `actSt19aChainDown` w1 @ 0x002313C8 <- aug6 script/src/st19a (3 syms rebound)
- PORTED `actSt19aChainMain` w1 @ 0x002319E0 <- aug6 script/src/st19a (8 syms rebound)
- PORTED `actSt19aChainSwitch` w1 @ 0x00231A98 <- aug6 script/src/st19a (2 syms rebound)
- REVERTED `actSt19aOriXL` w1 @ 0x002315D8 — [codegen] insn 32: expected `addiu	a0,s0,0` built `addiu	a0,s0,1224`
- REVERTED `actSt19aChain` w1 @ 0x00231748 — [codegen] insn 38: expected `addiu	a0,s0,0` built `addiu	a0,s0,1616`

### isys/gobj_cam_dl
- PORTED `isysGObjLinkCameraDLBeforeGObj` w1 @ 0x001FC2E0 <- aug6 fumi/isys/gobj_cam_dl (3 syms rebound)
- PORTED `adpcmTickProc2` w1 @ 0x001FC460 <- aug6 fumi/sound/adpcm_init (2 syms rebound)
- PORTED `adpcmDataSet` w1 @ 0x001FC4C0 <- aug6 fumi/sound/adpcm_init (2 syms rebound)
- REVERTED `cut_gobj_camera_dl_link` w1 @ 0x001FC048 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

### ito/mpeg/mv_main
- REVERTED `switchThread` w1 @ 0x0019D960 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory
- REVERTED `termAll` w1 @ 0x0019D9E8 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory

### src/DisplayP2O
- PORTED `p2o_DispVU1Multi` w1 @ 0x0010E708 <- aug6 seki/src/DisplayP2O (1 syms rebound)
- PORTED `p2o_DispVU1MultiDefault` w1 @ 0x0010E748 <- aug6 seki/src/DisplayP2O (2 syms rebound)
- PORTED `p2o_DispVU1` w1 @ 0x0010E7D8 <- aug6 seki/src/DisplayP2O (3 syms rebound)
- PORTED `p2o_DispVU1Default` w1 @ 0x0010E868 <- aug6 seki/src/DisplayP2O (2 syms rebound)
- PORTED `p2o_SetDefaultEnviroment` w1 @ 0x0010E950 <- aug6 seki/src/DisplayP2O (1 syms rebound)

### src/fuzio
- PORTED `fzShowM` w1 @ 0x00168690 <- aug6 fumi/src/fuzio (1 syms rebound)
- PORTED `fzMagnitude3f` w1 @ 0x001687B8 <- aug6 fumi/src/fuzio (2 syms rebound)
- REVERTED `fzShowV` w1 @ 0x00168650 — [codegen] insn 9: expected `addiu	v0,v0,0` built `addiu	v0,v0,6448`

### src/layout_texture
- PORTED `default_item_select` w1 @ 0x001B5958 <- aug6 common/src/layout_texture (4 syms rebound)
- PORTED `texture_fading` w1 @ 0x001B5998 <- aug6 common/src/layout_texture (2 syms rebound)
- PORTED `display_primary_texture_layout` w1 @ 0x001B5A10 <- aug6 common/src/layout_texture (2 syms rebound)
- PORTED `exec_layout_texture` w1 @ 0x001B5B30 <- aug6 common/src/layout_texture (5 syms rebound)
- PORTED `lt_fade_status` w1 @ 0x001B6FD8 <- aug6 common/src/layout_texture (5 syms rebound)

### src/pool
- PORTED `setNodePursueParticleEffectWithUpperLimit` w1 @ 0x0010ABD8 <- aug6 sugipon/src/pool (7 syms rebound)
- PORTED `PoolDL` w1 @ 0x0010AF48 <- aug6 sugipon/src/pool (11 syms rebound)
- PORTED `InitLimitedPoolReflactionMesh` w1 @ 0x0010B040 <- aug6 sugipon/src/pool (4 syms rebound)
- PORTED `getWave` w1 @ 0x0010CF88 <- aug6 sugipon/src/pool (18 syms rebound)

### src/st00a
- PORTED `actSt00aStairChk` w1 @ 0x0020D880 <- aug6 script/src/st00a (9 syms rebound)
- PORTED `actSt00aStair` w1 @ 0x0020F720 <- aug6 script/src/st00a (4 syms rebound)
- REVERTED `actSt00aInit` w1 @ 0x0020D7A8 — [undeclared] src/st00a.c:12: `actSt00aEnd_ext' undeclared (first use in this function)
- REVERTED `actSt00aDoor2DownChk` w1 @ 0x0020E8C8 — [codegen] insn 39: expected `addiu	a0,s0,0` built `addiu	a0,s0,4696`
- REVERTED `actSt00aEne` w1 @ 0x0020F1E0 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `actSt00aAtr2Chk` w1 @ 0x0020F830 — [codegen] insn 9: expected `addiu	a0,a0,0` built `addiu	a0,a0,5784`

### src/way_kidnap
- PORTED `CopyWpPos` w1 @ 0x002057C8 <- aug6 fumi/src/way_kidnap (1 syms rebound)
- PORTED `WayLengthOfGObj_GObj` w1 @ 0x00205860 <- aug6 fumi/src/way_kidnap (1 syms rebound)
- REVERTED `WayLengthOfPos_Pos` w1 @ 0x002055C0 — [parse] src/way_kidnap.c:3: parse error before `Nd'
- REVERTED `NearestEnemyFromGirl` w1 @ 0x002056A8 — [parse] src/way_kidnap.c:3: parse error before `Nd'

### ito/mpeg/mv_readbuf
- REVERTED `free_buffer` w1 @ 0x0019DB50 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory
- REVERTED `readBufBeginPut` w1 @ 0x0019DBC8 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory
- REVERTED `readBufBeginGet` w1 @ 0x0019DBF0 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory

### src/Basic
- PORTED `matrix_init` w1 @ 0x001F6C20 <- aug6 seki/src/Basic (6 syms rebound)
- REVERTED `freeseki` w1 @ 0x001F6CB0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `reallocseki` w1 @ 0x001F6DB8 — [codegen] insn 5: expected `lui	a2,0x0` built `addiu	a3,zero,382`

### src/BgAnimation
- PORTED `bga_CalcObject` w1 @ 0x001F9348 <- aug6 seki/src/BgAnimation (1 syms rebound)
- PORTED `bga_SetCamFrame` w1 @ 0x001FA6D8 <- aug6 seki/src/BgAnimation (1 syms rebound)
- PORTED `bga_CheckAnimationFinish` w1 @ 0x001FA760 <- aug6 seki/src/BgAnimation (1 syms rebound)
- REVERTED `bga_CheckAnimationFrame` w1 @ 0x001FA7F8 — [codegen] insn 25: expected `bc1f	98 <bga_CheckAnimationFrame+0x98>` built `sll	zero,zero,0x0`

### src/brain
- PORTED `brainLevelProcess` w1 @ 0x00182890 <- aug6 omori/src/brain (2 syms rebound)
- PORTED `brainGetTarget` w1 @ 0x00182958 <- aug6 omori/src/brain (2 syms rebound)
- PORTED `brainStatusSet` w1 @ 0x001829D0 <- aug6 omori/src/brain (2 syms rebound)
- PORTED `brainGetLevel` w1 @ 0x00182AB8 <- aug6 omori/src/brain (2 syms rebound)

### src/frameDependSequence
- PORTED `executeSEPackageByGObj` w1 @ 0x001D12E0 <- aug6 sugipon/src/frameDependSequence (1 syms rebound)
- PORTED `executeSEPackageWithNoGObj` w1 @ 0x001D13A8 <- aug6 sugipon/src/frameDependSequence (3 syms rebound)
- PORTED `ExecuteSEPackage` w1 @ 0x001D1428 <- aug6 sugipon/src/frameDependSequence (0 syms rebound)

### src/geometryManager
- PORTED `GetRootQuaternionByDObj` w1 @ 0x001028F0 <- aug6 sugipon/src/geometryManager (5 syms rebound)
- PORTED `SetRootMatrixWithTransOffset` w1 @ 0x00102DE0 <- aug6 sugipon/src/geometryManager (2 syms rebound)

### src/hand-camera
- PORTED `HandyCamera_TargetMoveType` w1 @ 0x00194398 <- aug6 omori/src/hand-camera (2 syms rebound)
- PORTED `ClearHandCameraCorrect` w1 @ 0x001943C8 <- aug6 omori/src/hand-camera (3 syms rebound)
- PORTED `InitHandCameraCorrect` w1 @ 0x00194400 <- aug6 omori/src/hand-camera (3 syms rebound)
- PORTED `SetLimitHandCameraCorrect` w1 @ 0x00194440 <- aug6 omori/src/hand-camera (3 syms rebound)
- REVERTED `RotateAccordingToStick_PatternThree` w1 @ 0x00194360 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`

### src/lightning
- PORTED `DrawLightning2` w1 @ 0x001997B8 <- aug6 ito/src/lightning (2 syms rebound)
- PORTED `DrawLightning` w1 @ 0x001999A8 <- aug6 ito/src/lightning (2 syms rebound)
- REVERTED `DrawLightningN` w1 @ 0x001998C0 — [codegen] src/lightning.c:45: invalid initializer

### src/motionOrientManager
- PORTED `execFrameTrigger` w1 @ 0x001E0B58 <- aug6 sugipon/src/motionOrientManager (7 syms rebound)
- PORTED `sendStateMail` w1 @ 0x001E0C38 <- aug6 sugipon/src/motionOrientManager (2 syms rebound)
- PORTED `getStreamMotionGeometry` w1 @ 0x001E2370 <- aug6 sugipon/src/motionOrientManager (1 syms rebound)
- REVERTED `shiftMotionOrientBeginFunc` w1 @ 0x001E0FE8 — [unresolved-symbol] unresolved-symbol: insn 19 `D_006169D8`: retail symbol D_004BC710 (0x004BC710) undefined

### src/switch
- REVERTED `BoxMemoryFunc` w1 @ 0x001C0E48 — [codegen] src/switch.c:85: storage size of `buf2' isn't known
- REVERTED `getAlign` w1 @ 0x001C0EB0 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory
- REVERTED `GetDistanceOfGObj` w1 @ 0x001C0F70 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory
- REVERTED `moveXPlus` w1 @ 0x001C1038 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory
- REVERTED `moveXMinus` w1 @ 0x001C10F8 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory

### src/windField
- PORTED `drawSenpuuki` w1 @ 0x001F4BE0 <- aug6 sugipon/src/windField (1 syms rebound)
- PORTED `getRadiateWindVector` w1 @ 0x001F4DE8 <- aug6 sugipon/src/windField (2 syms rebound)
- REVERTED `InitWindField` w1 @ 0x001F4800 — [codegen] insn 83: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `getParallelWindVector` w1 @ 0x001F4DD8 — [codegen] insn 1: expected `addiu	v0,v0,0` built `addiu	v0,v0,1024`

### ios/mcard
- PORTED `iosMcTest` w1 @ 0x00137F08 <- aug6 fumi/ios/mcard (2 syms rebound)
- PORTED `iosMcSync` w1 @ 0x00137F48 <- aug6 fumi/ios/mcard (2 syms rebound)
- PORTED `iosMcGetInfo` w1 @ 0x00137F90 <- aug6 fumi/ios/mcard (2 syms rebound)

### ito/mpeg/mv_videodec
- REVERTED `videoDecEndPut` w1 @ 0x0019E278 — [emits-data] emits-data: +4 bytes of .rodata/.sdata/.lit4 (string or out-of-line float literal; needs a Phase-5 rodata carve)

### src/DObj
- PORTED `initMatrixDObj` w1 @ 0x0019E5D0 <- aug6 common/src/DObj (0 syms rebound)
- PORTED `FreeDObj` w1 @ 0x0019EF10 <- aug6 common/src/DObj (4 syms rebound)
- REVERTED `initGeometryState` w1 @ 0x0019E598 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`

### src/DisplayFont
- PORTED `font_CheckAlign` w1 @ 0x001FA898 <- aug6 seki/src/DisplayFont (1 syms rebound)
- PORTED `font_Print` w1 @ 0x001FA998 <- aug6 seki/src/DisplayFont (1 syms rebound)
- PORTED `font_GetWidth` w1 @ 0x001FAA30 <- aug6 seki/src/DisplayFont (1 syms rebound)

### src/Light
- PORTED `light_getAmbientLight` w1 @ 0x00114D80 <- aug6 seki/src/Light (1 syms rebound)

### src/RegistPacket
- PORTED `reg_dispSObj` w1 @ 0x0011FC28 <- aug6 seki/src/RegistPacket (7 syms rebound)

### src/Texture
- PORTED `tex_setTexReg` w1 @ 0x0012AE40 <- aug6 seki/src/Texture (4 syms rebound)

### src/attackCheckBoundary
- PORTED `InitAttackCheckBoundaryGeo` w1 @ 0x001BB8C0 <- aug6 sugipon/src/attackCheckBoundary (6 syms rebound)
- PORTED `CreateAttackCheckBoundary` w1 @ 0x001BBE50 <- aug6 sugipon/src/attackCheckBoundary (3 syms rebound)
- PORTED `GetAttackCheckBoundaryManagerStatus` w1 @ 0x001BBEA0 <- aug6 sugipon/src/attackCheckBoundary (0 syms rebound)

### src/chain
- PORTED `collisionCheck` w1 @ 0x0018CFD0 <- aug6 omori/src/chain (1 syms rebound)
- PORTED `chain_simulate_term_simple` w1 @ 0x0018CFE0 <- aug6 omori/src/chain (1 syms rebound)
- PORTED `InitChainGeo` w1 @ 0x0018DDF0 <- aug6 omori/src/chain (5 syms rebound)

### src/charFileManager
- PORTED `ReadParticleEffectFile` w1 @ 0x001A1D88 <- aug6 common/src/charFileManager (11 syms rebound)
- PORTED `ReadSoundHdFile` w1 @ 0x001A20D8 <- aug6 common/src/charFileManager (7 syms rebound)
- PORTED `ReadStageSettingFile` w1 @ 0x001A2610 <- aug6 common/src/charFileManager (12 syms rebound)
- PORTED `CSVSYSTEM_ReadCharFiles` w1 @ 0x001A26E0 <- aug6 common/src/charFileManager (6 syms rebound)

### src/debug
- PORTED `debug_FlushFontWindow` w1 @ 0x001A40C8 <- aug6 common/src/debug (11 syms rebound)
- REVERTED `debug_Assert` w1 @ 0x001A2D58 — [codegen] insn 7: expected `<end>` built `sll	zero,zero,0x0`

### src/debug_exception
- PORTED `debugIOPExceptionMain` w1 @ 0x001A6E00 <- aug6 common/src/debug_exception (0 syms rebound)
- PORTED `debug_SetExceptionMessage` w1 @ 0x001A7008 <- aug6 common/src/debug_exception (4 syms rebound)
- SKIPPED `initLineTraceTable` w1 @ 0x001A6848 — jtbl

### src/effectTool
- PORTED `saveEffectData` w1 @ 0x001CCA70 <- aug6 sugipon/src/effectTool (5 syms rebound)

### src/itou_sub
- PORTED `lw_pos_to_ico_pos` w1 @ 0x001986A8 <- aug6 ito/src/itou_sub (0 syms rebound)

### src/multiBgaManager
- PORTED `DispMultiBgaManager` w1 @ 0x001E6B70 <- aug6 sugipon/src/multiBgaManager (3 syms rebound)
- REVERTED `InitMultiBgaManager` w1 @ 0x001E69D8 — [codegen] src/multiBgaManager.c:26: incompatible types in assignment

### src/particleLayout
- PORTED `DeleteParticleLayout` w1 @ 0x001E8C88 <- aug6 sugipon/src/particleLayout (4 syms rebound)
- PORTED `InitParticleLayoutGeo` w1 @ 0x001E8D30 <- aug6 sugipon/src/particleLayout (1 syms rebound)
- PORTED `ParticleLayoutDL` w1 @ 0x001E8D70 <- aug6 sugipon/src/particleLayout (2 syms rebound)

### src/st10r
- PORTED `actSt10rTower` w1 @ 0x00227478 <- aug6 script/src/st10r (6 syms rebound)
- PORTED `actSt10rEnemy1` w1 @ 0x00227750 <- aug6 script/src/st10r (5 syms rebound)

### src/staffroll
- PORTED `staffRollScroll` w1 @ 0x001B8120 <- aug6 common/src/staffroll (4 syms rebound)
- PORTED `staffRollMain` w1 @ 0x001B81B8 <- aug6 common/src/staffroll (13 syms rebound)

### src/tableSin
- PORTED `GetTableArcCos` w1 @ 0x0010DBD0 <- aug6 sugipon/src/tableSin (3 syms rebound)
- PORTED `GetTableArcTan2` w1 @ 0x0010DC38 <- aug6 sugipon/src/tableSin (2 syms rebound)

### ios/inflate
- PORTED `inflate_start` w1 @ 0x00133510 <- aug6 fumi/ios/inflate (3 syms rebound)
- PORTED `close_inflate_handler` w1 @ 0x00133570 <- aug6 fumi/ios/inflate (1 syms rebound)

### ios/mblock
- PORTED `new_segment` w1 @ 0x00136088 <- aug6 fumi/ios/mblock (0 syms rebound)
- PORTED `strdup_mblock` w1 @ 0x00136140 <- aug6 fumi/ios/mblock (1 syms rebound)

### ios/mcdata
- PORTED `iosMcIconWriteIcon` w1 @ 0x00138020 <- aug6 fumi/ios/mcdata (2 syms rebound)
- PORTED `_iosMcIconWriteIconsys` w1 @ 0x00138068 <- aug6 fumi/ios/mcdata (2 syms rebound)
- REVERTED `iosMcIconWriteIconsys` w1 @ 0x00137FD8 — [codegen] insn 17: expected `<end>` built `sll	zero,zero,0x0`

### ito/mpeg/mv_vobuf
- PORTED `voBufGetTag` w1 @ 0x0019E520 <- aug6 ito/mpeg/mv_vobuf (1 syms rebound)

### src/PObj
- PORTED `InitPObj` w1 @ 0x00240B88 <- aug6 common/src/PObj (2 syms rebound)
- PORTED `FreePObj` w1 @ 0x00240BD0 <- aug6 common/src/PObj (4 syms rebound)

### src/act_bird
- PORTED `trans_bird` w1 @ 0x001970E8 <- aug6 ito/src/act_bird (4 syms rebound)
- PORTED `BirdGeo` w1 @ 0x00197338 <- aug6 ito/src/act_bird (3 syms rebound)

### src/clothTest

### src/e3
- PORTED `actE3TitleChk` w1 @ 0x00209F28 <- aug6 script/src/e3 (2 syms rebound)
- PORTED `actE3St09aSekizo` w1 @ 0x0020A5F8 <- aug6 script/src/e3 (6 syms rebound)
- REVERTED `actE3GateChk` w1 @ 0x0020A720 — [codegen] src/e3.c:65: invalid initializer

### src/enemy
- PORTED `EnemyCheckHit` w1 @ 0x001CD490 <- aug6 sugipon/src/enemy (7 syms rebound)
- PORTED `SetEnemyHitGeometryAction` w1 @ 0x001CE8F0 <- aug6 sugipon/src/enemy (5 syms rebound)

### src/itou_boss
- PORTED `BossCtrlGeo` w1 @ 0x00198328 <- aug6 ito/src/itou_boss (1 syms rebound)
- REVERTED `effect_end_func` w1 @ 0x00197FE8 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`

### src/kanban

### src/kanbanBoot
- PORTED `kanbanBootMcCheck` w1 @ 0x001B0A80 <- aug6 common/src/kanbanBoot (1 syms rebound)
- PORTED `kanbanBootMain` w1 @ 0x001B0A98 <- aug6 common/src/kanbanBoot (1 syms rebound)

### src/st01b
- PORTED `actSt01bEnemy2` w1 @ 0x00210738 <- aug6 script/src/st01b (6 syms rebound)
- PORTED `actSt01bEnemy3` w1 @ 0x002107E0 <- aug6 script/src/st01b (6 syms rebound)
- PORTED `actSt01bEnemy6` w1 @ 0x00210980 <- aug6 script/src/st01b (4 syms rebound)

### src/st03t
- REVERTED `actSt03tEneChk` w1 @ 0x00212D00 — [codegen] insn 14: expected `lui	a1,0x500` built `lui	a1,0x300`

### src/st09a
- PORTED `actSt09aSekizoEvent` w1 @ 0x002250B8 <- aug6 script/src/st09a (6 syms rebound)
- PORTED `actSt09aIntroChk` w1 @ 0x00225150 <- aug6 script/src/st09a (6 syms rebound)

### src/st10l
- PORTED `actSt10lFloorRight` w1 @ 0x00225AB0 <- aug6 script/src/st10l (4 syms rebound)
- PORTED `actSt10lFloor` w1 @ 0x00225EF0 <- aug6 script/src/st10l (6 syms rebound)
- PORTED `actSt10lGondola` w1 @ 0x00225F68 <- aug6 script/src/st10l (2 syms rebound)

### src/st13c
- PORTED `actSt13cCage1stDownDemoCancel` w1 @ 0x0022B810 <- aug6 script/src/st13c (4 syms rebound)

### src/st47a
- PORTED `actSt47aHane2` w1 @ 0x00236A78 <- aug6 script/src/st47a (6 syms rebound)
- PORTED `actSt47aBarricade` w1 @ 0x00236BA8 <- aug6 script/src/st47a (6 syms rebound)

### src/stormTest
- PORTED `InitStormTestGeo` w1 @ 0x001EF9E0 <- aug6 sugipon/src/stormTest (4 syms rebound)

### src/streamMotionManager

### src/sugiTree
- REVERTED `SugiLeafGeo2` w1 @ 0x001F1148 — [codegen] insn 7: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `SugiLeafDL2` w1 @ 0x001F11A0 — [callee-sig-conflict] src/sugiTree.c:4: conflicting types for `SugiCb'

### src/way_sys
- PORTED `create_box_bridge` w1 @ 0x00176BC8 <- aug6 fumi/src/way_sys (14 syms rebound)
- REVERTED `_FUNC_GetWay_begin` w1 @ 0x00176B38 — [codegen] insn 31: expected `<end>` built `sll	zero,zero,0x0`

### src/way_tool
- PORTED `draw_way_group` w1 @ 0x00207018 <- aug6 fumi/src/way_tool (7 syms rebound)
- PORTED `way_toolDL` w1 @ 0x002070B0 <- aug6 fumi/src/way_tool (10 syms rebound)
- REVERTED `group_create` w1 @ 0x00206208 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

### ios/memory
- PORTED `iosMallocDebug` w1 @ 0x00138BF0 <- aug6 fumi/ios/memory (6 syms rebound)
- PORTED `iosMallocCheckLeak` w1 @ 0x001394F0 <- aug6 fumi/ios/memory (4 syms rebound)

### sound/soundManager
- PORTED `sndInit` w1 @ 0x001446E8 <- aug6 fumi/sound/soundManager (4 syms rebound)

### src/DmaPacket
- PORTED `dpk_Init` w1 @ 0x001FBAA8 <- aug6 seki/src/DmaPacket (3 syms rebound)

### src/MicroCode

### src/Primitive
- PORTED `prim_SetFan2D` w1 @ 0x0011BFC0 <- aug6 seki/src/Primitive (1 syms rebound)

### src/Shadow

### src/act-way
- PORTED `ACTWay_IsMustWalkFromWay` w1 @ 0x00201D50 <- aug6 fumi/src/act-way (2 syms rebound)

### src/act2
- PORTED `BeforeFunc2` w1 @ 0x00203C40 <- aug6 fumi/src/act2 (3 syms rebound)

### src/backStage

### src/chandelier
- PORTED `ChandelierDL` w1 @ 0x001C33D8 <- aug6 sugipon/src/chandelier (5 syms rebound)
- PORTED `InitChandelierGeo` w1 @ 0x001C3470 <- aug6 sugipon/src/chandelier (2 syms rebound)

### src/clipCollisionManager
- PORTED `actClipCollisionCore` w1 @ 0x001C3760 <- aug6 sugipon/src/clipCollisionManager (1 syms rebound)

### src/darkVolume
- PORTED `renderViewCoordZSphere` w1 @ 0x001CB910 <- aug6 sugipon/src/darkVolume (3 syms rebound)

### src/fightSound

### src/gflag

### src/icoMisc
- PORTED `ExitIcoMisc` w1 @ 0x001AE880 <- aug6 common/src/icoMisc (2 syms rebound)

### src/jimaku

### src/mail-add-data

### src/motionFileManager
- PORTED `InitMotionMemorySize` w1 @ 0x001D4E88 <- aug6 sugipon/src/motionFileManager (6 syms rebound)

### src/motionManager
- PORTED `checkActPointWithHeight` w1 @ 0x001D8C40 <- aug6 sugipon/src/motionManager (12 syms rebound)
- PORTED `GetWallVector` w1 @ 0x001DC938 <- aug6 sugipon/src/motionManager (9 syms rebound)

### src/poly-flat
- PORTED `after_DrawPolygon` w1 @ 0x00195380 <- aug6 omori/src/poly-flat (3 syms rebound)
- PORTED `before_DrawLine` w1 @ 0x00195510 <- aug6 omori/src/poly-flat (5 syms rebound)

### src/sceneManager

### src/st05c
- PORTED `actSt04rDoor` w1 @ 0x0021EE70 <- aug6 script/src/st05c (6 syms rebound)
- PORTED `actSt04rDoor2` w1 @ 0x0021EEF8 <- aug6 script/src/st05c (5 syms rebound)

### src/st08a
- PORTED `actSt08aEnemy1` w1 @ 0x00223D58 <- aug6 script/src/st08a (5 syms rebound)
- PORTED `actSt08aIntroChk` w1 @ 0x00223E50 <- aug6 script/src/st08a (3 syms rebound)

### src/st17a
- PORTED `actSt17aHasiChk` w1 @ 0x0022D5C8 <- aug6 script/src/st17a (6 syms rebound)

### src/st20a
- PORTED `actSt20aEnemy2` w1 @ 0x00233E80 <- aug6 script/src/st20a (5 syms rebound)
- PORTED `actSt20aEnemy3` w1 @ 0x00233EE8 <- aug6 script/src/st20a (5 syms rebound)

### src/staticBlur
- PORTED `cleanUpFB` w1 @ 0x001EF118 <- aug6 sugipon/src/staticBlur (12 syms rebound)

### src/warpGirl

### src/waySystemManager
- REVERTED `RequestGetWayBegin` w1 @ 0x001F22A0 — [codegen] insn 4: expected `addiu	t0,t0,0` built `addiu	t0,t0,288`
- REVERTED `actWaySystemCore` w1 @ 0x001F22E0 — [codegen] insn 7: expected `addiu	a0,a0,0` built `addiu	a0,a0,208`

### src/wireLetter

### ios/ios

### isys/isys

### ito/mpeg/mv_sub
- REVERTED `ErrMessage` w1 @ 0x0023D848 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/EnemyInit

### src/GifPacket
- PORTED `gif_SpriteOrg` w1 @ 0x00111918 <- aug6 seki/src/GifPacket (1 syms rebound)

### src/StageAnimation
- PORTED `stage_ApplyData` w1 @ 0x001243E8 <- aug6 seki/src/StageAnimation (8 syms rebound)

### src/ZFog

### src/a_p_1

### src/act-wish
- REVERTED `ACTGetWish_FromPad` w1 @ 0x0014B580 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`

### src/attackhit

### src/box

### src/camera-set-manager
- REVERTED `InitCameraSetManager` w1 @ 0x0018CBE8 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`

### src/debug_menu
- PORTED `debug_TargetGObj_Func` w1 @ 0x001A9D90 <- aug6 common/src/debug_menu (0 syms rebound)

### src/ebrain
- REVERTED `eBrainProcess` w1 @ 0x00190478 — [codegen] insn 27: expected `<end>` built `sll	zero,zero,0x0`

### src/enemy-control
- REVERTED `EnemyCtrlBeforeFunc` w1 @ 0x00191D20 — [codegen] insn 19: expected `<end>` built `sll	zero,zero,0x0`

### src/enemyParts
- PORTED `moveDataElements` w1 @ 0x001CED28 <- aug6 sugipon/src/enemyParts (3 syms rebound)

### src/flag

### src/flyManager
- PORTED `InitFlyInfo` w1 @ 0x001D03E8 <- aug6 sugipon/src/flyManager (5 syms rebound)

### src/gather_effect
- PORTED `GatherEffect_Set` w1 @ 0x001977A8 <- aug6 ito/src/gather_effect (1 syms rebound)

### src/generator

### src/girl
- PORTED `SetGirlClothDispSwitch` w1 @ 0x001D1A98 <- aug6 sugipon/src/girl (4 syms rebound)

### src/item

### src/itou_gflag
- PORTED `itouGFlagInit` w1 @ 0x001983F8 <- aug6 ito/src/itou_gflag (1 syms rebound)

### src/lodManager

### src/motionViewer

### src/op
- PORTED `actSt00aEneChk` w1 @ 0x0020D718 <- aug6 script/src/st00a (3 syms rebound)

### src/queen

### src/queen_barrier_disp
- PORTED `makeRefractST` w1 @ 0x0019C798 <- aug6 ito/src/queen_barrier_disp (3 syms rebound)

### src/ropeFix

### src/rotObject
- PORTED `moveStartSE` w1 @ 0x001E9980 <- aug6 sugipon/src/rotObject (8 syms rebound)

### src/seMail
- REVERTED `seMail` w1 @ 0x00204D70 — [callee-sig-conflict] src/seMail.c:8: conflicting types for `GetRootMatrixByDObj'

### src/st04b
- REVERTED `actSt04bGirlWay` w1 @ 0x002165B0 — [codegen] insn 11: expected `lui	s0,0x22` built `lui	s0,0x0`

### src/st04c
- PORTED `actSt04cEnemy2` w1 @ 0x002180C8 <- aug6 script/src/st04c (11 syms rebound)

### src/st04d

### src/stageMultiBgaManager
- REVERTED `InitStageMultiBgaManager` w1 @ 0x001EBCD0 — [codegen] insn 51: expected `<end>` built `sll	zero,zero,0x0`

### src/stage_orient

### src/weapon
- PORTED `calcDynamicPathGeometry` w1 @ 0x001F3A00 <- aug6 sugipon/src/weapon (2 syms rebound)

### src/windManager
- PORTED `InitWindManager` w1 @ 0x001F4FE8 <- aug6 sugipon/src/windManager (8 syms rebound)

### src/worm
- PORTED `GetWormRoute` w1 @ 0x001F66A0 <- aug6 sugipon/src/worm (3 syms rebound)
