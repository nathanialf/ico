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

## src/act_bird
- KEPT `birdBeforeFunc` (old `func_001970E0`) @ 0x001970E0
- KEPT `Debug_StickControl` (old `func_00197330`) @ 0x00197330
- KEPT `BirdDL` (old `func_001973A8`) @ 0x001973A8
- REVERTED `interp_vector_sa` (old `func_00197080`) @ 0x00197080 — src/act_bird.c:5: redefinition of `struct GObj'

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
- REVERTED `func_001769D0` (old `func_001769D0`) @ 0x001769D0 — src/jimaku.c:140: warning: passing arg 1 of `func_00133500' makes pointer from integer without a cast

## src/lightning
- KEPT `set_vertex` (old `func_00199790`) @ 0x00199790
- KEPT `apply_m34` (old `func_00199998`) @ 0x00199998
- REVERTED `func_00199A08` (old `func_00199A08`) @ 0x00199A08 — src/lightning.c:6: redefinition of `struct GObj'

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

## src/way_sys
- KEPT `avoid_obstacle2` (old `func_00176BB8`) @ 0x00176BB8

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

## src/box
- REVERTED `initFloating` (old `func_001BE558`) @ 0x001BE558 — [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `ExecBoxMoveEndReaction` (old `func_001C0690`) @ 0x001C0690 — src/box.c:53: warning: initialization from incompatible pointer type
- REVERTED `BoxExtGeoRestore` (old `func_001C0708`) @ 0x001C0708 — src/box.c:58: warning: initialization from incompatible pointer type

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
