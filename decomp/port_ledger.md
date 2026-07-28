
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
- PORTED `_GetCurrentMatrix` w1 @ 0x001181E0 <- aug6 seki/src/Matrix (0 syms rebound)
- PORTED `_GetCurrentMatrixTrans` w1 @ 0x00118268 <- aug6 seki/src/Matrix (0 syms rebound)
- PORTED `_InitCurrentMatrix` w1 @ 0x00117F30 <- aug6 seki/src/Matrix (0 syms rebound)
- PORTED `_RemakeNormal` w1 @ 0x00117DB0 <- aug6 seki/src/Matrix (2 syms rebound)
- PORTED `_Sqrt` w1 @ 0x00117E70 <- aug6 seki/src/Matrix (2 syms rebound)
- PORTED `_TransCurrentMatrix` w1 @ 0x00118000 <- aug6 seki/src/Matrix (0 syms rebound)

### src/fieldCollision
- PORTED `ChangeFieldCollisionDebugMode` w1 @ 0x00168538 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipCollision` w1 @ 0x00168510 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `ClipFloor` w1 @ 0x00168468 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorCheckCB` w1 @ 0x001684E8 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `ClipFloorE` w1 @ 0x00168488 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorIH` w1 @ 0x001684C8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipFloorR` w1 @ 0x001684A8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipPlane` w1 @ 0x00168598 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWall` w1 @ 0x00167760 <- aug6 fumi/src/fieldCollision (3 syms rebound)
- PORTED `ClipWallAdjustPos` w1 @ 0x001683E8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallBoxStop` w1 @ 0x001683C8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallCheckCB` w1 @ 0x00168428 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallE` w1 @ 0x00168408 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallEField` w1 @ 0x001683A8 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallFieldCheckCB` w1 @ 0x00168448 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `ClipWallFuchiHangWalkStop` w1 @ 0x00168058 <- aug6 fumi/src/fieldCollision (9 syms rebound)
- PORTED `DispCollisionPC` w1 @ 0x00165FB8 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `DrawCollision` w1 @ 0x00168578 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- PORTED `DrawCollisionRay` w3 @ 0x00167230 <- aug6 fumi/src/fieldCollision (3 syms rebound)
- PORTED `GetOrientOfWall` w1 @ 0x001685B8 <- aug6 fumi/src/fieldCollision (2 syms rebound)
- PORTED `LoadCollision` w1 @ 0x00168558 <- aug6 fumi/src/fieldCollision (1 syms rebound)
- REVERTED `MakeCollisionDependGObjList` w3 @ 0x00165E60 — [codegen] insn 13: expected `sw	v0,288(s0)` built `sw	v0,272(s0)`
- PORTED `MakeExitAttributeIndex` w3 @ 0x00167258 <- aug6 fumi/src/fieldCollision (3 syms rebound)
- PORTED `SetSimplePlane` w1 @ 0x001685E0 <- aug6 fumi/src/fieldCollision (3 syms rebound)
- PORTED `__ClipWall` w1 @ 0x00166118 <- aug6 fumi/src/fieldCollision (7 syms rebound)

### ios/shockdriver
- PORTED `Init_ShockRequestAlloc` w1 @ 0x0013CB88 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `Reset_ShockRequestStruct` w1 @ 0x0013CC00 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockDriver_GetShockVoice` w1 @ 0x0013CA48 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockDriver_GetShockVoiceMax` w1 @ 0x0013C958 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockDriver_GetShockVoiceSet` w1 @ 0x0013C9D8 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `ShockDriver_VoiceSet_NumberRegist` w1 @ 0x0013C820 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockEmulator_EmulationShot` w1 @ 0x0013CAD8 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockRequestBox_DecodeRequest` w1 @ 0x0013C488 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `ShockRequestBox_EndRequestFree` w1 @ 0x0013C4C0 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `ShockRequestBox_Request` w1 @ 0x0013C320 <- aug6 fumi/ios/shockdriver (1 syms rebound)
- PORTED `ShockRevice_Wave` w1 @ 0x0013CC60 <- aug6 fumi/ios/shockdriver (0 syms rebound)
- PORTED `Shock_SetMotor` w1 @ 0x0013BA20 <- aug6 fumi/ios/shockdriver (5 syms rebound)
- PORTED `Vibration_ShotDecode` w1 @ 0x0013B8F0 <- aug6 fumi/ios/shockdriver (2 syms rebound)
- PORTED `Vibration_WaveDecode` w1 @ 0x0013B970 <- aug6 fumi/ios/shockdriver (2 syms rebound)

### src/act-game
- PORTED `ACTCharctrl_Lock` w1 @ 0x0014AFB8 <- aug6 fumi/src/act-game (1 syms rebound)
- PORTED `ACTGameCollisionOff` w1 @ 0x0014A700 <- aug6 fumi/src/act-game (2 syms rebound)
- REVERTED `ACTGameCollisionOn` w3 @ 0x0014A6B8 — [codegen] insn 10: expected `srl	v0,v0,0x9` built `srl	v0,v0,0x6`
- PORTED `ACTGameView_Init` w1 @ 0x0014AF70 <- aug6 fumi/src/act-game (1 syms rebound)
- PORTED `ACTGameView_Loop` w1 @ 0x00149AE0 <- aug6 fumi/src/act-game (12 syms rebound)
- PORTED `ACTGame_BeforeFunc` w1 @ 0x00149FF0 <- aug6 fumi/src/act-game (4 syms rebound)
- PORTED `ACTGame_CheckHandMotion` w1 @ 0x0014A850 <- aug6 fumi/src/act-game (4 syms rebound)
- PORTED `ACTGame_DisconnectHand` w1 @ 0x0014B090 <- aug6 fumi/src/act-game (1 syms rebound)
- PORTED `ACTGame_InnerVelocityUpdate` w1 @ 0x00149F70 <- aug6 fumi/src/act-game (3 syms rebound)
- PORTED `ACTGame_StageChangeGObjID` w1 @ 0x0014A980 <- aug6 fumi/src/act-game (3 syms rebound)
- PORTED `ACTLookTargetSystem_Exec` w1 @ 0x0014A3A8 <- aug6 fumi/src/act-game (3 syms rebound)
- REVERTED `ACTParaStatus_Exec` w3 @ 0x00149ED0 — [codegen] insn 1: expected `sw	zero,1348(v0)` built `sw	zero,1332(v0)`
- PORTED `ActOrientTest` w1 @ 0x0014A100 <- aug6 fumi/src/act-game (1 syms rebound)
- PORTED `GetGirlHandlinkClInfo` w1 @ 0x0014A178 <- aug6 fumi/src/act-game (7 syms rebound)
- REVERTED `GetSkeltonOrient` w3 @ 0x00149F20 — [codegen] insn 4: expected `lw	v0,1184(v1)` built `lw	v0,1168(v1)`
- PORTED `GetTarget` w1 @ 0x0014A330 <- aug6 fumi/src/act-game (3 syms rebound)
- REVERTED `PAIR_GetPosition_BOY` w1 @ 0x0014B0B8 — [undeclared] src/act-game.c:494: `D_0063226C_flt' undeclared (first use in this function)
- REVERTED `updateHMC` w3 @ 0x0014A560 — [codegen] insn 14: expected `lw	v1,1184(v0)` built `lw	v1,1168(v0)`

### src/commonact
- REVERTED `ACTAdjustPlane` w1 @ 0x0015F2D8 — [codegen] insn 1: expected `lui	at,0xbf80` built `dli	a2,0xbff0`
- REVERTED `ACTSendMailCorrect` w3 @ 0x0015EE78 — [codegen] insn 19: expected `sw	zero,1056(v0)` built `sw	zero,1040(v0)`
- REVERTED `ACTSetPositionNodeWithFitting` w3 @ 0x001564D0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `ACTSetPositionWithFitting` w3 @ 0x00156488 — [codegen] insn 9: expected `lw	a0,320(a0)` built `lw	a0,304(a0)`
- PORTED `ACT_LAYOUT_GAMEOVER` w1 @ 0x0015F298 <- aug6 fumi/src/commonact (2 syms rebound)
- REVERTED `BoxBarSoundOn` w3 @ 0x0015BCC8 — [codegen] insn 0: expected `addiu	v0,zero,168` built `addiu	v0,zero,166`
- PORTED `GetCorrectOrientOfChain` w1 @ 0x00157E68 <- aug6 fumi/src/commonact (2 syms rebound)
- PORTED `SetMotionDirectionSmooze` w1 @ 0x0015EE10 <- aug6 fumi/src/commonact (4 syms rebound)
- PORTED `WithMailFunc_AttackRejectInQueen` w1 @ 0x00157DC8 <- aug6 fumi/src/commonact (5 syms rebound)
- PORTED `WithMailFunc_WayBeginPosError` w1 @ 0x00157BF8 <- aug6 fumi/src/commonact (2 syms rebound)
- PORTED `_ACTMotDirSmzDirect` w1 @ 0x0015F320 <- aug6 fumi/src/commonact (2 syms rebound)
- REVERTED `_boxbar_set_sound` w3 @ 0x0015C130 — [codegen] insn 5: expected `jal	0 <_boxbar_set_sound>` built `jal	8b00 <subCommonIdle>`
- REVERTED `actCommonBecarry` w3 @ 0x0015EF50 — [codegen] insn 6: expected `sw	v0,288(s0)` built `sw	v0,272(s0)`
- PORTED `actCommonDelete` w1 @ 0x0015F550 <- aug6 fumi/src/commonact (1 syms rebound)
- PORTED `actCommonLever` w1 @ 0x00159C38 <- aug6 fumi/src/commonact (8 syms rebound)
- REVERTED `actCommonRope` w1 @ 0x001584D8 — [codegen] insn 29: expected `jal	0 <actCommonRope>` built `jal	2050 <func_00158328.15>`
- REVERTED `actCommonSlowrun` w1 @ 0x0015F228 — [parse] src/commonact.c:292: parse error before `D_00292540'
- REVERTED `correctJumpOrientByChain` w3 @ 0x0015D3C0 — [codegen] insn 6: expected `lw	t1,1184(a2)` built `lw	t1,1168(a2)`
- PORTED `funcCommonBeginReady` w3 @ 0x0015EA50 <- aug6 fumi/src/commonact (3 syms rebound)
- PORTED `funcCommonEndReady` w3 @ 0x0015EA80 <- aug6 fumi/src/commonact (3 syms rebound)
- PORTED `funcCommonError` w1 @ 0x0015EDB8 <- aug6 fumi/src/commonact (4 syms rebound)
- REVERTED `funcCommonFallDircorrect` w3 @ 0x0015D358 — [codegen] insn 9: expected `swc1	$f0,272(a3)` built `swc1	$f0,256(a3)`
- PORTED `funcCommonJumpDircorrect` w1 @ 0x0015D348 <- aug6 fumi/src/commonact (1 syms rebound)
- REVERTED `motCommonRopeTurnL` w3 @ 0x00158770 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `subCommonIdle` w3 @ 0x0015EF88 — [codegen] insn 19: expected `addiu	s0,s0,224` built `addiu	s0,s0,208`

### src/camera-ico2
- PORTED `AddPluralCameraSet` w1 @ 0x00188228 <- aug6 omori/src/camera-ico2 (4 syms rebound)
- PORTED `CameraMove` w1 @ 0x00187990 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- REVERTED `CameraSetCameraSet` w1 @ 0x001873C0 — [codegen] insn 21: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `CameraSetCameraSet_Default` w1 @ 0x00187418 <- aug6 omori/src/camera-ico2 (4 syms rebound)
- PORTED `ChaseCamera` w1 @ 0x00187950 <- aug6 omori/src/camera-ico2 (0 syms rebound)
- PORTED `GetCameraGroupFromGObj` w1 @ 0x001880C8 <- aug6 omori/src/camera-ico2 (2 syms rebound)
- PORTED `GetRootPositionForCamera` w1 @ 0x00187570 <- aug6 omori/src/camera-ico2 (2 syms rebound)
- REVERTED `GetSizeOfCameraSetBinary` w1 @ 0x00188550 — [undeclared] src/camera-ico2.c:234: `D_0062C844_f' undeclared (first use in this function)
- REVERTED `InitIco2Camera` w1 @ 0x001879D0 — [callee-sig-conflict] src/camera-ico2.c:15: conflicting types for `func_001D49C0'
- REVERTED `InitPluralCameraSet` w3 @ 0x00188290 — [codegen] insn 1: expected `addiu	a0,zero,404` built `addiu	a0,zero,400`
- REVERTED `MakeCameraSetBinary` w1 @ 0x001882D0 — [undeclared] src/camera-ico2.c:273: `g_E30' undeclared (first use in this function)
- PORTED `ReflectCameraSetBinary` w1 @ 0x001879A8 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- PORTED `SetCameraMatrix_Ico2` w1 @ 0x00187CC0 <- aug6 omori/src/camera-ico2 (7 syms rebound)
- PORTED `ico2camera_GetGroupNearest` w1 @ 0x001877E0 <- aug6 omori/src/camera-ico2 (2 syms rebound)
- PORTED `ico2camera_GetTargetPos` w1 @ 0x00187688 <- aug6 omori/src/camera-ico2 (4 syms rebound)
- PORTED `initMonitorCamera` w1 @ 0x001878F8 <- aug6 omori/src/camera-ico2 (1 syms rebound)
- PORTED `monitorMonitorCamera` w1 @ 0x00187908 <- aug6 omori/src/camera-ico2 (1 syms rebound)

### sound/s_init
- PORTED `debug_DispSEInfo` w1 @ 0x00141F58 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundDataAreaGet` w1 @ 0x00143CD0 <- aug6 fumi/sound/s_init (1 syms rebound)
- REVERTED `soundDataClose` w3 @ 0x00141C28 — [codegen] insn 12: expected `addiu	a1,zero,618` built `addiu	a1,zero,605`
- REVERTED `soundDataOpen` w3 @ 0x00141868 — [codegen] insn 8: expected `addiu	a1,zero,487` built `addiu	a1,zero,475`
- REVERTED `soundDataOpenChk` w3 @ 0x00141340 — [codegen] insn 7: expected `addiu	a2,zero,254` built `addiu	a2,zero,230`
- PORTED `soundOutputModeGet` w1 @ 0x00143AD0 <- aug6 fumi/sound/s_init (7 syms rebound)
- PORTED `soundReqTickProc` w3 @ 0x00143248 <- aug6 fumi/sound/s_init (1 syms rebound)
- REVERTED `soundSQDataSet` w3 @ 0x00143E60 — [codegen] insn 55: expected `addiu	a1,zero,334` built `addiu	a1,zero,322`
- PORTED `soundSeDefPitchSet` w3 @ 0x00143240 <- aug6 fumi/sound/s_init (1 syms rebound)
- REVERTED `soundSeDefPlay` w3 @ 0x00143FC0 — [codegen] insn 55: expected `addiu	a1,zero,334` built `addiu	a1,zero,322`
- PORTED `soundSeDefPlayWithVolumeRate` w1 @ 0x00144120 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundSeDefVolumeRateGet` w1 @ 0x00144178 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundSeEnvDefaultSet` w1 @ 0x00144500 <- aug6 fumi/sound/s_init (3 syms rebound)
- PORTED `soundSeGroupGet` w1 @ 0x00144240 <- aug6 fumi/sound/s_init (2 syms rebound)
- PORTED `soundSeKindBuild` w1 @ 0x00144390 <- aug6 fumi/sound/s_init (6 syms rebound)
- PORTED `soundVBlank` w1 @ 0x00144308 <- aug6 fumi/sound/s_init (2 syms rebound)

### src/enemy_act
- PORTED `GetEnemyTypeFromGObj` w1 @ 0x00165D18 <- aug6 fumi/src/enemy_act (2 syms rebound)
- PORTED `IsEnemyBrainToBoy` w1 @ 0x00165CE8 <- aug6 fumi/src/enemy_act (1 syms rebound)
- REVERTED `IsEnemyBrainToGenerator` w3 @ 0x00165B80 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `PairSetGeometry` w3 @ 0x0015FBD8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `_ApproachTarget_Way` w1 @ 0x00164EB0 <- aug6 fumi/src/enemy_act (3 syms rebound)
- REVERTED `_MustChase` w3 @ 0x0015F6F0 — [undeclared] src/enemy_act.c:59: `D_00632398' undeclared (first use in this function)
- PORTED `actEnemyForceSwitchToCarry` w1 @ 0x0015FC50 <- aug6 fumi/src/enemy_act (4 syms rebound)
- REVERTED `actEnemyRestart` w3 @ 0x0015FB60 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actEnemy_GetClingTarget` w1 @ 0x001654E0 <- aug6 fumi/src/enemy_act (1 syms rebound)
- REVERTED `actEnemy_isNormalEnemy` w3 @ 0x00165540 — [codegen] insn 11: expected `addiu	a1,zero,2002` built `addiu	a1,zero,1984`
- REVERTED `subEnemyBrain_ToBoy` w3 @ 0x00163D60 — [undeclared] src/enemy_act.c:9: `D_00558E10' undeclared (first use in this function)
- PORTED `subEnemyCollision` w1 @ 0x0015F9B0 <- aug6 fumi/src/enemy_act (1 syms rebound)

### ios/thread
- PORTED `iosGetIOSThreadFromId` w1 @ 0x0013D140 <- aug6 fumi/ios/thread (3 syms rebound)
- PORTED `iosSemaSignal` w1 @ 0x0013D498 <- aug6 fumi/ios/thread (9 syms rebound)
- PORTED `iosThreadCreateS` w1 @ 0x0013CCE8 <- aug6 fumi/ios/thread (0 syms rebound)
- REVERTED `iosThreadMain` w1 @ 0x0013CC78 — [codegen] insn 27: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosThreadMessage` w1 @ 0x0013CF38 — [codegen] insn 2: expected `addiu	v0,v0,0` built `addiu	v0,v0,184`
- PORTED `iosThreadName` w1 @ 0x0013CF70 <- aug6 fumi/ios/thread (0 syms rebound)
- PORTED `iosThreadStart` w1 @ 0x0013CD30 <- aug6 fumi/ios/thread (0 syms rebound)

### isys/gobj
- PORTED `add_gobj_to_head` w3 @ 0x0013E190 <- aug6 fumi/isys/gobj (2 syms rebound)
- REVERTED `add_gobj_to_tail` w1 @ 0x0013E0C0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- REVERTED `cut_gobj_link` w3 @ 0x0013DEA0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjAdd` w1 @ 0x0013E9E0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjAddAfterGObj` w1 @ 0x0013E350 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PORTED `isysGObjAddHead` w1 @ 0x0013EAE8 <- aug6 fumi/isys/gobj (2 syms rebound)
- REVERTED `isysGObjAlloc` w3 @ 0x0013E548 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `isysGObjInit` w1 @ 0x0013DDF8 — [codegen] insn 1: expected `bnel	a1,zero,18 <isysGObjInit+0x18>` built `bnel	a1,zero,6c <isysGObjInit+0x14>`
- REVERTED `isysGObjKindTableAdd` w3 @ 0x0013E728 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `isysGObjKindTableInit` w1 @ 0x0013DDA0 — [codegen] insn 1: expected `lui	v1,0x0` built `lui	v0,0x0`
- REVERTED `isysGObjKindTableRemove` w1 @ 0x0013E7F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `isysGObjMove` w3 @ 0x0013E1D8 <- aug6 fumi/isys/gobj (2 syms rebound)
- PORTED `isysGObjMoveAfterGObj` w1 @ 0x0013E868 <- aug6 fumi/isys/gobj (2 syms rebound)
- REVERTED `isysGObjMoveBeforeGObj` w1 @ 0x0013E8D8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `isysGObjMoveHead` w1 @ 0x0013E220 — [codegen] insn 20: expected `bne	a0,a2,6c <isysGObjMoveHead+0x6c>` built `bne	a0,a2,4e8 <isysGObjMoveHead+0x68>`
- REVERTED `isysGObjRemove` w3 @ 0x0013E648 — [codegen] insn 12: expected `jal	0 <isysGObjRemove>` built `jal	db0 <isysGObjSearchFromObjLayoutID>`
- REVERTED `isysGObjRemoveAll` w1 @ 0x0013DFF0 — [codegen] insn 7: expected `lw	a3,0(v1)` built `lw	a1,0(v1)`
- PORTED `isysGObjSearchFromObjKindID_begin` w1 @ 0x0013EBE0 <- aug6 fumi/isys/gobj (3 syms rebound)
- REVERTED `isysGObjSearchFromObjLayoutID` w3 @ 0x0013EB50 — [codegen] insn 27: expected `sltiu	v0,v0,67` built `sltiu	v0,v0,66`
- REVERTED `isysGetNbAllocedGObjs` w1 @ 0x0013E4D0 — [codegen] insn 3: expected `lui	a2,0x0` built `daddu	s0,a0,zero`

### src/camera-editor
- PORTED `CameraEdit_DispBox` w1 @ 0x001872B8 <- aug6 omori/src/camera-editor (3 syms rebound)
- PORTED `CameraEdit_Reflect` w3 @ 0x00187300 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `CameraEdit_Save` w1 @ 0x00187308 <- aug6 omori/src/camera-editor (2 syms rebound)
- PORTED `CameraEdit_del_pin` w1 @ 0x00187280 <- aug6 omori/src/camera-editor (3 syms rebound)
- PORTED `DispCameraGroup` w1 @ 0x00182D20 <- aug6 omori/src/camera-editor (7 syms rebound)
- REVERTED `_CameraEdit_del_box` w1 @ 0x001869F8 — [codegen] insn 2: expected `addiu	a0,a0,0` built `addiu	a0,a0,10864`
- REVERTED `debug_Marker` w1 @ 0x00187328 — [codegen] insn 15: expected `mtc1	zero,$f13` built `jal	0 <EnterMenu>`
- PORTED `debug_NMarker` w1 @ 0x00187318 <- aug6 omori/src/camera-editor (2 syms rebound)
- PORTED `dispCameraPinType2` w1 @ 0x00183218 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `gif_test` w1 @ 0x00182C68 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `menuGroupSelect` w1 @ 0x001848A0 <- aug6 omori/src/camera-editor (1 syms rebound)
- PORTED `saveEditedData` w1 @ 0x00182C18 <- aug6 omori/src/camera-editor (0 syms rebound)
- PORTED `wakeup_cameraedit` w3 @ 0x00185660 <- aug6 omori/src/camera-editor (1 syms rebound)

### src/gamesys
- PORTED `gamesysBackStageProcess` w1 @ 0x001AAFC8 <- aug6 common/src/gamesys (6 syms rebound)
- PORTED `gamesysGeneratorInfoLoad` w1 @ 0x001AB058 <- aug6 common/src/gamesys (8 syms rebound)
- PORTED `gamesysGeneratorInfoSave` w1 @ 0x001AC300 <- aug6 common/src/gamesys (2 syms rebound)
- PORTED `gamesysMemoryLoad` w1 @ 0x001ABEB8 <- aug6 common/src/gamesys (4 syms rebound)
- REVERTED `gamesysObjInfoCls` w1 @ 0x001AB3D0 — [unresolved-symbol] unresolved-symbol: insn 7 `D_20000150`: no retail lui partner for %lo (+3 more)
- REVERTED `gamesysObjInfoInit` w3 @ 0x001AAE70 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `gamesysObjInfoLoad` w1 @ 0x001AAEC0 <- aug6 common/src/gamesys (1 syms rebound)
- PORTED `gamesysObjInfoStageInitFlagCls` w1 @ 0x001AB190 <- aug6 common/src/gamesys (2 syms rebound)

### ios/cdvd
- PORTED `iosCdvdBackGroundMgr` w1 @ 0x001325D8 <- aug6 fumi/ios/cdvd (2 syms rebound)
- PORTED `iosCdvdBackGroundMgrNotDiskReadyPauseSet` w1 @ 0x001333C8 <- aug6 fumi/ios/cdvd (5 syms rebound)
- PORTED `iosCdvdBackGroundMgrSeek` w1 @ 0x00133460 <- aug6 fumi/ios/cdvd (0 syms rebound)
- PORTED `iosCdvdDirectStOpen` w1 @ 0x00132610 <- aug6 fumi/ios/cdvd (2 syms rebound)
- PORTED `iosCdvdDiskReady` w1 @ 0x00132038 <- aug6 fumi/ios/cdvd (4 syms rebound)
- PORTED `iosCdvdLoad` w1 @ 0x001320E8 <- aug6 fumi/ios/cdvd (3 syms rebound)
- REVERTED `iosCdvdMgrPackLoad` w1 @ 0x001312F0 — [undeclared] ios/cdvd.c:138: `D_tbl_0027E520' undeclared (first use in this function)
- PORTED `iosCdvdMgrSearchFile` w1 @ 0x001301D8 <- aug6 fumi/ios/cdvd (3 syms rebound)

### ito/mpeg/mv_disp
- PORTED `dispCreate` w1 @ 0x0023D0F0 <- aug6 ito/mpeg/mv_disp (7 syms rebound)
- PORTED `dispDelete` w1 @ 0x0023D2E8 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `dispSetTags` w1 @ 0x0023D170 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `dispSwitch` w1 @ 0x0023D1D0 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- REVERTED `endDisplay` w3 @ 0x0023D420 — [codegen] insn 7: expected `addiu	v1,zero,404` built `addiu	v1,zero,400`
- PORTED `loadImage` w1 @ 0x0023D348 <- aug6 ito/mpeg/mv_disp (2 syms rebound)
- REVERTED `setGIFad` w3 @ 0x0023D528 — [codegen] insn 14: expected `addiu	a0,zero,60` built `addiu	a0,zero,59`
- PORTED `setGIFtag` w3 @ 0x0023D518 <- aug6 ito/mpeg/mv_disp (2 syms rebound)
- PORTED `setImageSize` w1 @ 0x0023D050 <- aug6 ito/mpeg/mv_disp (6 syms rebound)
- PORTED `setPRIM` w1 @ 0x0023D6E8 <- aug6 ito/mpeg/mv_disp (3 syms rebound)
- REVERTED `setTEX0_1` w3 @ 0x0023D668 — [codegen] insn 21: expected `addiu	v0,zero,815` built `addiu	v0,zero,814`
- PORTED `setTEXFLUSH` w1 @ 0x0023D5A8 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- PORTED `setUV` w1 @ 0x0023D750 <- aug6 ito/mpeg/mv_disp (5 syms rebound)
- REVERTED `startDisplay` w1 @ 0x0023D390 — [arity] ito/mpeg/mv_disp.c:158: too many arguments to function `UpdateRootPosition'

### ito/mpeg/mv_vibuf
- PORTED `viBufAddDMA` w1 @ 0x0023F080 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufBeginPut` w1 @ 0x0023F030 <- aug6 ito/mpeg/mv_vibuf (4 syms rebound)
- PORTED `viBufCount` w1 @ 0x0023F350 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufCreate` w1 @ 0x0023EFB8 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufDelete` w1 @ 0x0023F2B8 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufGetTs` w1 @ 0x0023F200 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufModifyPts` w1 @ 0x0023F180 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufPutTs` w1 @ 0x0023F398 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufRestartDMA` w1 @ 0x0023F130 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)
- PORTED `viBufStopDMA` w1 @ 0x0023F0D8 <- aug6 ito/mpeg/mv_vibuf (0 syms rebound)

### src/Packet
- PORTED `pac_DispQW` w1 @ 0x00118A68 <- aug6 seki/src/Packet (0 syms rebound)
- REVERTED `pac_closeTag` w1 @ 0x00119350 — [missing-body] aug6 body not found in seki/src/Packet.c
- REVERTED `pac_getWeight` w1 @ 0x00118C68 — [missing-body] aug6 body not found in seki/src/Packet.c
- PORTED `pac_makeClusterStrip` w1 @ 0x00118E88 <- aug6 seki/src/Packet (7 syms rebound)
- PORTED `pac_makeMaterialTable` w1 @ 0x0011A2A8 <- aug6 seki/src/Packet (3 syms rebound)
- SKIPPED `pac_makeNormalStrip` w1 @ 0x00118B18 — jtbl
- REVERTED `pac_setGifTag` w1 @ 0x001191C0 — [missing-body] aug6 body not found in seki/src/Packet.c
- PORTED `pac_setMaterialPacket` w1 @ 0x0011A238 <- aug6 seki/src/Packet (5 syms rebound)
- SKIPPED `pac_setVifEndCode` w1 @ 0x00118FD8 — jtbl

### src/boyact
- REVERTED `BoyBgaManager` w3 @ 0x0014E5E8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `CheckCollisionAttr` w3 @ 0x0014E300 — [unresolved-symbol] unresolved-symbol: insn 39 `D_006A45A0`: no retail lui partner for %lo
- REVERTED `E3_StageStartBoy` w3 @ 0x0014E708 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `InitSwapWeapon` w1 @ 0x001502D8 <- aug6 fumi/src/boyact (3 syms rebound)
- REVERTED `UpdateGeo` w1 @ 0x0014E488 — [missing-body] aug6 body not found in fumi/src/boyact.c
- PORTED `actBoyBelift` w1 @ 0x00154218 <- aug6 fumi/src/boyact (7 syms rebound)
- PORTED `actBoyBeslam` w1 @ 0x001549B8 <- aug6 fumi/src/boyact (7 syms rebound)
- REVERTED `actBoyDitch3mExec` w1 @ 0x00154DD0 — [undeclared] src/boyact.c:356: `dst60_a' undeclared (first use in this function)
- PORTED `actBoyDitch3mReady` w1 @ 0x00154420 <- aug6 fumi/src/boyact (1 syms rebound)
- REVERTED `actBoyHangBefore` w3 @ 0x001547B8 — [codegen] insn 23: expected `lw	v0,320(v1)` built `lw	v0,304(v1)`
- PORTED `actBoyReadyMove` w1 @ 0x001548F0 <- aug6 fumi/src/boyact (2 syms rebound)
- REVERTED `actBoyRescueReady` w3 @ 0x00154390 — [codegen] insn 6: expected `lw	a0,320(s0)` built `lw	a0,304(s0)`
- REVERTED `actBoyRescueSrc` w3 @ 0x00154B20 — [codegen] insn 19: expected `sdl	v1,455(v0)` built `sdl	v1,439(v0)`
- REVERTED `actBoySupportBGBegin` w3 @ 0x00154D20 — [codegen] insn 12: expected `addiu	s3,s0,256` built `addiu	s3,s0,240`
- REVERTED `subBoyCollision` w1 @ 0x001521F0 — [codegen] insn 44: expected `lui	at,0x4348` built `lui	at,0x43e1`

### src/way_util
- REVERTED `NearestWgFromTarget` w1 @ 0x0017AE98 — [undeclared] src/way_util.c:305: `wcf_c' undeclared (first use in this function)
- REVERTED `bridge_waypoint_side_bridge` w1 @ 0x0017AD68 — [undeclared] src/way_util.c:301: `wcf_c' undeclared (first use in this function)
- PORTED `get_wp_nearest_bridge_side_me` w1 @ 0x0017A9B8 <- aug6 fumi/src/way_util (1 syms rebound)
- PORTED `nearest_waypoint_by_lineseg` w1 @ 0x0017A230 <- aug6 fumi/src/way_util (5 syms rebound)
- PORTED `nearest_waypoint_by_lineseg_of_group_from_gobj` w1 @ 0x0017A2C8 <- aug6 fumi/src/way_util (6 syms rebound)
- PORTED `visible_waypoint_from_gobj` w1 @ 0x0017A910 <- aug6 fumi/src/way_util (5 syms rebound)
- PORTED `visible_waypoint_of_all_except_gid_ThreadVersion` w1 @ 0x00178908 <- aug6 fumi/src/way_util (1 syms rebound)
- REVERTED `visible_waypoint_of_all_except_temp_ThreadVersion` w1 @ 0x00178930 — [undeclared] src/way_util.c:44: `D_004C7CF0_ve' undeclared (first use in this function)
- PORTED `visible_waypoint_of_all_from_gobj` w1 @ 0x0017A788 <- aug6 fumi/src/way_util (5 syms rebound)
- REVERTED `waypoint_connect_group_side_bridge` w1 @ 0x0017ADF8 — [undeclared] src/way_util.c:303: `wcf_c' undeclared (first use in this function)
- PORTED `wpsort_compfnc` w1 @ 0x0017AF40 <- aug6 fumi/src/way_util (1 syms rebound)

### src/quaternion
- PORTED `CopyQuaternion` w1 @ 0x0010D7F8 <- aug6 sugipon/src/quaternion (2 syms rebound)
- PORTED `GetSlerpQuaternionNoRegularize` w1 @ 0x0010D878 <- aug6 sugipon/src/quaternion (2 syms rebound)
- PORTED `InitQuaternionDrive` w1 @ 0x0010D4A8 <- aug6 sugipon/src/quaternion (7 syms rebound)
- PORTED `RegularizeQuaternion` w1 @ 0x0010D838 <- aug6 sugipon/src/quaternion (2 syms rebound)
- PORTED `getQuaternionFromMatrix` w1 @ 0x0010D540 <- aug6 sugipon/src/quaternion (3 syms rebound)

### src/st25a
- REVERTED `actConte12Jimaku` w3 @ 0x0017E160 — [codegen] insn 4: expected `sw	zero,272(v0)` built `sw	zero,256(v0)`
- PORTED `actConte13Jimaku` w1 @ 0x0017E1A8 <- aug6 script/src/st25a (3 syms rebound)
- PORTED `actSt25aGenerator` w1 @ 0x0017E270 <- aug6 script/src/st25a (3 syms rebound)
- PORTED `actSt25aQueenBeforeChk` w1 @ 0x0017E550 <- aug6 script/src/st25a (6 syms rebound)
- PORTED `actSt25aQueenDead` w1 @ 0x0017E330 <- aug6 script/src/st25a (1 syms rebound)
- PORTED `actSt25aQueenDeadChk` w1 @ 0x0017E188 <- aug6 script/src/st25a (1 syms rebound)

### sound/adpcm_init
- PORTED `AdpcmClose` w1 @ 0x00140710 <- aug6 fumi/sound/adpcm_init (3 syms rebound)
- PORTED `AdpcmFreeAreaGet` w1 @ 0x00140E48 <- aug6 fumi/sound/adpcm_init (6 syms rebound)
- PORTED `AdpcmIopBuffAlloc` w1 @ 0x00140B30 <- aug6 fumi/sound/adpcm_init (1 syms rebound)
- PORTED `AdpcmOpenSync` w1 @ 0x00140B60 <- aug6 fumi/sound/adpcm_init (1 syms rebound)
- PORTED `AdpcmUseAreaGet` w1 @ 0x00140CE0 <- aug6 fumi/sound/adpcm_init (4 syms rebound)
- PORTED `GetDitchPosition` w1 @ 0x00140F90 <- aug6 fumi/src/act-env (2 syms rebound)

### src/layout_action
- PORTED `_la_memory_card_check` w1 @ 0x001B4D48 <- aug6 common/src/layout_action (9 syms rebound)
- PORTED `_la_set_current_port_2` w1 @ 0x001B4E78 <- aug6 common/src/layout_action (5 syms rebound)
- PORTED `_la_set_preview_info` w1 @ 0x001B4FC8 <- aug6 common/src/layout_action (10 syms rebound)
- PORTED `la_mc_confirm_save_file` w3 @ 0x001B5528 <- aug6 common/src/layout_action (12 syms rebound)

### isys/gobj_process
- PORTED `cut_gobj_process_link` w1 @ 0x0013F378 <- aug6 fumi/isys/gobj_process (2 syms rebound)
- PORTED `isysGObjProcAddGOppArg` w1 @ 0x0013F700 <- aug6 fumi/isys/gobj_process (5 syms rebound)
- PORTED `isysGObjProcAddS` w1 @ 0x0013F6B8 <- aug6 fumi/isys/gobj_process (2 syms rebound)
- PORTED `isysGObjProcAdd_` w1 @ 0x0013F308 <- aug6 fumi/isys/gobj_process (2 syms rebound)
- PORTED `isysGObjProcPause` w1 @ 0x0013F778 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- PORTED `isysGObjProcPauseAll` w1 @ 0x0013F7A8 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- PORTED `isysGObjProcPausePtr` w1 @ 0x0013F7D8 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- PORTED `isysGObjProcRemove` w3 @ 0x0013F3E8 <- aug6 fumi/isys/gobj_process (1 syms rebound)
- REVERTED `isysGObjProcessInit` w1 @ 0x0013F2C8 — [codegen] insn 15: expected `<end>` built `sll	zero,zero,0x0`

### src/camera-root
- PORTED `Camctrl_SetTarget` w1 @ 0x0018CB20 <- aug6 omori/src/camera-root (5 syms rebound)
- PORTED `CameraEditManual` w1 @ 0x0018BF70 <- aug6 omori/src/camera-root (12 syms rebound)
- PORTED `DebugCameraManual` w1 @ 0x0018C078 <- aug6 omori/src/camera-root (3 syms rebound)
- PORTED `MakeCameraMatrix` w1 @ 0x0018BEB0 <- aug6 omori/src/camera-root (8 syms rebound)

### src/clothAnimation
- PORTED `GetChainAnimation` w1 @ 0x001C5FD0 <- aug6 sugipon/src/clothAnimation (12 syms rebound)
- PORTED `InitCloth4D` w1 @ 0x001C8B60 <- aug6 sugipon/src/clothAnimation (2 syms rebound)
- PORTED `getCloth4D_preProcess` w1 @ 0x001C8958 <- aug6 sugipon/src/clothAnimation (5 syms rebound)

### src/girl_act
- PORTED `GetEyeDirection` w1 @ 0x0016A460 <- aug6 fumi/src/girl_act (2 syms rebound)
- REVERTED `actGirlAttack` w3 @ 0x00174D78 — [codegen] insn 1: expected `addiu	a1,zero,253` built `addiu	a1,zero,250`
- REVERTED `actGirlDitch3mReady` w3 @ 0x0016EB68 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- SKIPPED `actGirlHang` w3 @ 0x001736B8 — jtbl
- PORTED `actGirlStand` w1 @ 0x00173268 <- aug6 fumi/src/girl_act (2 syms rebound)
- REVERTED `actGirlSupportGBLoop` w1 @ 0x00171AB0 — [codegen] insn 6: expected `beq	a1,zero,f8 <actGirlSupportGBLoop+0xf8>` built `beq	a1,zero,774c <actGirlSupportGBLoop+0xfc>`
- PORTED `afterGirlHand` w1 @ 0x00175640 <- aug6 fumi/src/girl_act (3 syms rebound)
- PORTED `afterGirlPulledGo` w1 @ 0x00175688 <- aug6 fumi/src/girl_act (3 syms rebound)
- PORTED `subGirlCollision` w1 @ 0x0016BCF0 <- aug6 fumi/src/girl_act (2 syms rebound)
- PORTED `subGirlControl` w1 @ 0x0016BCA0 <- aug6 fumi/src/girl_act (5 syms rebound)

### src/motionManager2
- PORTED `CheckFloorAttribute` w1 @ 0x0010A0C8 <- aug6 sugipon/src/motionManager2 (0 syms rebound)
- REVERTED `CopyMotionWithNodeHrc` w3 @ 0x00109B58 — [codegen] insn 2: expected `ldl	a0,423(v0)` built `ldl	a0,407(v0)`
- REVERTED `GetCollisionOfLastActiveField` w3 @ 0x00109E48 — [codegen] insn 4: expected `lw	a2,2032(v1)` built `lw	a2,2016(v1)`
- PORTED `GetStreamMotion` w1 @ 0x001097A0 <- aug6 sugipon/src/motionManager2 (3 syms rebound)
- PORTED `SetMotionPlaySpeedRatio` w1 @ 0x0010A598 <- aug6 sugipon/src/motionManager2 (0 syms rebound)
- REVERTED `_GetMotionDirection` w3 @ 0x00106D68 — [codegen] insn 5: expected `addiu	a1,a0,592` built `addiu	a1,a0,576`
- REVERTED `calcFootIK` w1 @ 0x00107778 — [unresolved-symbol] unresolved-symbol: insn 6 `D_0062BF0C`: retail symbol D_00633C0C (0x00633C0C) undefined
- REVERTED `dispPlane` w3 @ 0x00106AB8 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)

### src/script
- PORTED `_SCPBoySupportGirl` w3 @ 0x0017D308 <- aug6 script/src/script (4 syms rebound)
- REVERTED `scpActivateAllWithKind` w3 @ 0x0017DD60 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `scpDispOnAllWithKind` w3 @ 0x0017DCD8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `scpDoorTypeUpUp` w1 @ 0x0017D230 <- aug6 script/src/script (2 syms rebound)
- PORTED `scpPlayMotDir` w3 @ 0x0017CC80 <- aug6 script/src/script (5 syms rebound)
- PORTED `scpPlayStart` w1 @ 0x0017D030 <- aug6 script/src/script (1 syms rebound)
- PORTED `scpSetCageVelocityFriction` w3 @ 0x0017CBE8 <- aug6 script/src/script (5 syms rebound)
- PORTED `scpTorchLightOff` w1 @ 0x0017CB60 <- aug6 script/src/script (5 syms rebound)
- REVERTED `scpTorchLightOn` w1 @ 0x0017CB20 — [codegen] insn 15: expected `<end>` built `sll	zero,zero,0x0`

### ios/message
- REVERTED `iosMsgQueueCreate` w1 @ 0x0013A220 — [codegen] insn 11: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `iosMsgQueueDestroy` w1 @ 0x0013A250 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- PORTED `iosMsgQueueDestroyAll` w1 @ 0x0013A7C8 <- aug6 fumi/ios/message (2 syms rebound)
- REVERTED `iosMsgRecv` w1 @ 0x0013A6C0 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgSend` w1 @ 0x0013A5B8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `iosMsgSetEvent` w1 @ 0x0013A380 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- REVERTED `send_signal_message` w1 @ 0x0013A2F8 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)

### ios/pad
- PORTED `controler_stable_check` w1 @ 0x0013A820 <- aug6 fumi/ios/pad (3 syms rebound)
- PORTED `iosPadActStop` w1 @ 0x0013B878 <- aug6 fumi/ios/pad (8 syms rebound)
- PORTED `iosPadConnect` w1 @ 0x0013B778 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadGetDevice` w1 @ 0x0013B760 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadGetPort` w1 @ 0x0013B718 <- aug6 fumi/ios/pad (2 syms rebound)
- PORTED `iosPadGetSlot` w1 @ 0x0013B748 <- aug6 fumi/ios/pad (1 syms rebound)
- PORTED `iosPadStickCameraCoord` w1 @ 0x0013B7C0 <- aug6 fumi/ios/pad (1 syms rebound)

### src/GobjProc
- PORTED `CreateGObj` w1 @ 0x0023F7F0 <- aug6 common/src/GobjProc (1 syms rebound)
- PORTED `CreateGObjByFuncSet` w1 @ 0x0023F928 <- aug6 common/src/GobjProc (1 syms rebound)
- PORTED `GetGObjId` w1 @ 0x0023F778 <- aug6 common/src/GobjProc (0 syms rebound)
- PORTED `PrintGObjID` w1 @ 0x0023F7B0 <- aug6 common/src/GobjProc (0 syms rebound)
- REVERTED `ResetGObjProc` w1 @ 0x0023F690 — [codegen] insn 29: expected `<end>` built `sll	zero,zero,0x0`

### src/GsBase
- PORTED `gsb_InitGSSystem` w1 @ 0x00113820 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_KeepFrameBuffer` w3 @ 0x00112188 <- aug6 seki/src/GsBase (1 syms rebound)
- PORTED `gsb_PostEffect` w1 @ 0x001137B8 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_Reduction` w1 @ 0x00112148 <- aug6 seki/src/GsBase (1 syms rebound)
- PORTED `gsb_ResetGSSystem` w1 @ 0x00113908 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_SetFrame` w1 @ 0x00111FA8 <- aug6 seki/src/GsBase (2 syms rebound)
- PORTED `gsb_UpdateGSSystem` w1 @ 0x00113890 <- aug6 seki/src/GsBase (5 syms rebound)
- PORTED `gsb_fade` w1 @ 0x001121E0 <- aug6 seki/src/GsBase (3 syms rebound)
- PORTED `gsb_scissorOnDemo` w1 @ 0x00112260 <- aug6 seki/src/GsBase (0 syms rebound)

### src/st13b
- PORTED `actConte10b` w1 @ 0x00229C30 <- aug6 script/src/st13b (5 syms rebound)
- PORTED `actSt13bBoss` w1 @ 0x00229B60 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actSt13bConte02` w1 @ 0x00229890 <- aug6 script/src/st13b (6 syms rebound)
- REVERTED `actSt13bConte02Jimaku` w3 @ 0x00229FF0 — [codegen] insn 21: expected `addiu	a0,zero,358` built `addiu	a0,zero,357`
- REVERTED `actSt13bDoor` w3 @ 0x00229F30 — [codegen] insn 23: expected `addiu	a0,zero,320` built `addiu	a0,zero,319`
- PORTED `actSt13bExit` w3 @ 0x00229EC8 <- aug6 script/src/st13b (4 syms rebound)
- PORTED `actSt13bFloorChk` w1 @ 0x002297D8 <- aug6 script/src/st13b (6 syms rebound)
- PORTED `actSt13bMeetAgain` w1 @ 0x00229AA8 <- aug6 script/src/st13b (6 syms rebound)
- REVERTED `actSt13bMeetAgainChk` w3 @ 0x0022A0A0 — [codegen] insn 28: expected `addiu	a0,zero,331` built `addiu	a0,zero,330`
- PORTED `actSt13bSekizo` w3 @ 0x00229D88 <- aug6 script/src/st13b (4 syms rebound)
- PORTED `actSt13bSekizo2` w3 @ 0x00229DE0 <- aug6 script/src/st13b (4 syms rebound)
- REVERTED `actSt13bSekizo2Chk` w3 @ 0x00229A30 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt13bSekizoChk` w1 @ 0x00229960 <- aug6 script/src/st13b (6 syms rebound)

### src/way_llf
- PORTED `AddWayPointTop` w1 @ 0x00205B30 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `CloseWayGroup` w1 @ 0x00205A78 <- aug6 fumi/src/way_llf (1 syms rebound)
- REVERTED `CreateTempWayGroup` w3 @ 0x002059F8 — [codegen] insn 3: expected `addiu	a0,v1,17600` built `addiu	a0,v1,13760`
- PORTED `CreateWayGroup` w1 @ 0x002059A0 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `CreateWayPoint` w1 @ 0x00205A98 <- aug6 fumi/src/way_llf (1 syms rebound)
- PORTED `DeleteWayGroup` w1 @ 0x00205A38 <- aug6 fumi/src/way_llf (1 syms rebound)
- REVERTED `InitWayPointSystem` w3 @ 0x00205948 — [codegen] insn 3: expected `addiu	a0,v1,4888` built `addiu	a0,v1,3328`
- PORTED `WayBridge_begin` w1 @ 0x002060E8 <- aug6 fumi/src/way_llf (14 syms rebound)

### isys/gobj_dl
- REVERTED `cut_gobj_dl_link` w1 @ 0x0013EC50 — [codegen] insn 21: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `isysGObjDlInit` w3 @ 0x0013F0E8 <- aug6 fumi/isys/gobj_dl (2 syms rebound)
- PORTED `isysGObjLinkObjDL` w3 @ 0x0013EE58 <- aug6 fumi/isys/gobj_dl (1 syms rebound)
- PORTED `isysGObjLinkObjDLAfterGObj` w1 @ 0x0013EFD0 <- aug6 fumi/isys/gobj_dl (2 syms rebound)
- PORTED `isysGObjLinkObjDLBeforeGObj` w3 @ 0x0013F0A0 <- aug6 fumi/isys/gobj_dl (2 syms rebound)
- REVERTED `isysGObjLinkObjDLHead` w1 @ 0x0013EE60 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s2,a2,zero`
- REVERTED `isysGObjMoveObjDLAfterGObj` w1 @ 0x0013F130 — [codegen] insn 5: expected `lui	a0,0x0` built `daddu	s4,a3,zero`
- PORTED `isysGObjMoveObjDLBeforeGObj` w1 @ 0x0013F1D0 <- aug6 fumi/isys/gobj_dl (1 syms rebound)
- REVERTED `isysGObjMoveObjDLHead` w1 @ 0x0013EDB0 — [codegen] insn 1: expected `bnel	a1,zero,18 <isysGObjMoveObjDLHead+0x18>` built `bnel	a1,zero,174 <isysGObjMoveObjDLHead+0x14>`
- PORTED `isysGObjRemoveObjDL` w1 @ 0x0013ECA8 <- aug6 fumi/isys/gobj_dl (2 syms rebound)

### isys/obj_manager
- PORTED `iosOmSearchGObjId` w1 @ 0x0013FF20 <- aug6 fumi/isys/obj_manager (1 syms rebound)

### ito/mpeg/mv_audiodec
- PORTED `audioDecIsPreset` w1 @ 0x0023C890 <- aug6 ito/mpeg/mv_audiodec (5 syms rebound)
- PORTED `audioDecReset` w1 @ 0x0023C808 <- aug6 ito/mpeg/mv_audiodec (5 syms rebound)
- PORTED `audioDecResume` w1 @ 0x0023CA08 <- aug6 ito/mpeg/mv_audiodec (2 syms rebound)
- PORTED `audioDecSendToIOP` w1 @ 0x0023C5F0 <- aug6 ito/mpeg/mv_audiodec (2 syms rebound)
- PORTED `audioDecStart` w1 @ 0x0023C908 <- aug6 ito/mpeg/mv_audiodec (8 syms rebound)

### src/DisplayList
- PORTED `dl_CloseDma` w1 @ 0x001FB658 <- aug6 seki/src/DisplayList (9 syms rebound)
- PORTED `dl_Debug` w1 @ 0x001FB5E0 <- aug6 seki/src/DisplayList (7 syms rebound)
- PORTED `dl_Out` w1 @ 0x001FB768 <- aug6 seki/src/DisplayList (9 syms rebound)
- PORTED `dl_PushPriority` w1 @ 0x001FB4A8 <- aug6 seki/src/DisplayList (5 syms rebound)
- PORTED `dl_SetDLPriority` w1 @ 0x001FB7F8 <- aug6 seki/src/DisplayList (9 syms rebound)

### src/StageManager
- PORTED `StageManager` w1 @ 0x0019FF98 <- aug6 common/src/StageManager (1 syms rebound)
- REVERTED `exit_stage` w1 @ 0x0019F7A8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `stgmgrForceSwitch` w1 @ 0x0019FFA8 — [callee-sig-conflict] src/StageManager.c:61: conflicting types for `stgmgrForceSwitch'
- REVERTED `stgmgrNextStagePreLoad` w3 @ 0x0019FB30 — [codegen] insn 0: expected `addiu	v0,zero,404` built `addiu	v0,zero,400`
- REVERTED `stop_free_resources` w1 @ 0x0019F6A8 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo

### src/act
- PORTED `_ACTRun` w1 @ 0x00203A58 <- aug6 fumi/src/act (1 syms rebound)
- PORTED `_ACTWait` w1 @ 0x00203AA0 <- aug6 fumi/src/act (2 syms rebound)
- REVERTED `actChangeActBrain` w1 @ 0x00201DE0 — [codegen] insn 9: expected `jal	0 <actChangeActBrain>` built `jal	1d98 <actCreateSubThread>`
- PORTED `actChangeActMain` w1 @ 0x00201E70 <- aug6 fumi/src/act (7 syms rebound)
- PORTED `actCreateMotionThread` w1 @ 0x00201F38 <- aug6 fumi/src/act (6 syms rebound)
- PORTED `actCreateSubThread` w1 @ 0x00203B78 <- aug6 fumi/src/act (7 syms rebound)

### src/gv
- REVERTED `GetMatrixDirectionToZ` w3 @ 0x00193A00 — [codegen] insn 6: expected `lw	a2,2048(v0)` built `lw	a2,2032(v0)`
- PORTED `_DistxzGV` w1 @ 0x00193D30 <- aug6 omori/src/gv (3 syms rebound)
- PORTED `_GetDirection` w1 @ 0x00193F68 <- aug6 omori/src/gv (0 syms rebound)
- REVERTED `_InterRotGV` w3 @ 0x00193A58 — [codegen] insn 2: expected `lw	a2,2048(a3)` built `lw	a2,2032(a3)`
- PORTED `_OrientXZGV` w1 @ 0x00194020 <- aug6 omori/src/gv (3 syms rebound)
- PORTED `_RotGVF` w1 @ 0x00193FA8 <- aug6 omori/src/gv (1 syms rebound)
- PORTED `_RotyGV` w1 @ 0x00193E48 <- aug6 omori/src/gv (1 syms rebound)

### src/particleEffect
- REVERTED `DeleteParticleEffect` w1 @ 0x001E89F8 — [undeclared] src/particleEffect.c:69: `D_007097F0' undeclared (first use in this function)
- PORTED `ExecParticleEffects` w1 @ 0x001E8598 <- aug6 sugipon/src/particleEffect (4 syms rebound)
- PORTED `InitParticleEffects` w1 @ 0x001E8930 <- aug6 sugipon/src/particleEffect (5 syms rebound)
- REVERTED `ResetParticleEffectPackages` w1 @ 0x001E85D8 — [undeclared] src/particleEffect.c:51: `D_007097F0' undeclared (first use in this function)
- REVERTED `SetParticleEffectActiveSensing` w1 @ 0x001E8A60 — [undeclared] src/particleEffect.c:70: `D_007097F0' undeclared (first use in this function)

### src/st02a
- PORTED `actSt02WaterFallBoySplashCheck` w1 @ 0x002113C8 <- aug6 script/src/st02a (5 syms rebound)
- REVERTED `actSt02aBox` w3 @ 0x00211590 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1216`
- REVERTED `actSt02aBoxEvent2` w3 @ 0x00211620 — [codegen] insn 30: expected `addiu	v1,s1,0` built `addiu	v1,s1,1392`
- PORTED `actSt02aDoor` w1 @ 0x002111D8 <- aug6 script/src/st02a (6 syms rebound)
- PORTED `actSt02aDoorDownChk` w1 @ 0x00211338 <- aug6 script/src/st02a (6 syms rebound)
- PORTED `actSt02aDoorUpChk` w1 @ 0x00211290 <- aug6 script/src/st02a (6 syms rebound)
- REVERTED `actSt02aEne` w3 @ 0x002116D0 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `actSt02aEnemy2` w3 @ 0x002117D0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt02aGondolaDown` w3 @ 0x00211518 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt02aGondolaUp` w1 @ 0x002114A8 <- aug6 script/src/st02a (5 syms rebound)
- REVERTED `actSt02aInit` w3 @ 0x00211160 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt02aSekizo` w3 @ 0x002118D8 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- PORTED `actSt02aTakiWay` w1 @ 0x00211BE8 <- aug6 script/src/st02a (7 syms rebound)
- PORTED `actSt02aWaterFallChk` w1 @ 0x00211438 <- aug6 script/src/st02a (5 syms rebound)

### src/st19a
- REVERTED `actSt19aChain` w1 @ 0x00231748 — [codegen] insn 38: expected `addiu	a0,s0,0` built `addiu	a0,s0,1616`
- PORTED `actSt19aChainDown` w1 @ 0x002313C8 <- aug6 script/src/st19a (3 syms rebound)
- PORTED `actSt19aChainMain` w1 @ 0x002319E0 <- aug6 script/src/st19a (8 syms rebound)
- PORTED `actSt19aChainSwitch` w1 @ 0x00231A98 <- aug6 script/src/st19a (2 syms rebound)
- REVERTED `actSt19aHagurumaChk` w3 @ 0x002312C8 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1800`
- REVERTED `actSt19aOriXL` w1 @ 0x002315D8 — [codegen] insn 32: expected `addiu	a0,s0,0` built `addiu	a0,s0,1224`
- REVERTED `actSt19aPipeChk` w3 @ 0x00231330 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### isys/gobj_cam_dl
- PORTED `adpcmDataSet` w1 @ 0x001FC4C0 <- aug6 fumi/sound/adpcm_init (2 syms rebound)
- PORTED `adpcmTickProc2` w1 @ 0x001FC460 <- aug6 fumi/sound/adpcm_init (2 syms rebound)
- REVERTED `cut_gobj_camera_dl_link` w1 @ 0x001FC048 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- PORTED `isysGObjLinkCameraDLBeforeGObj` w1 @ 0x001FC2E0 <- aug6 fumi/isys/gobj_cam_dl (3 syms rebound)

### ito/mpeg/mv_main
- REVERTED `proceedAudio` w3 @ 0x0019D9C8 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory
- REVERTED `readMpeg` w3 @ 0x0019D9D0 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory
- REVERTED `switchThread` w1 @ 0x0019D960 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory
- REVERTED `termAll` w1 @ 0x0019D9E8 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_main.c:3: mv_defs.h: No such file or directory

### src/DisplayP2O
- PORTED `p2o_DispVU1` w1 @ 0x0010E7D8 <- aug6 seki/src/DisplayP2O (3 syms rebound)
- PORTED `p2o_DispVU1Default` w1 @ 0x0010E868 <- aug6 seki/src/DisplayP2O (2 syms rebound)
- PORTED `p2o_DispVU1Multi` w1 @ 0x0010E708 <- aug6 seki/src/DisplayP2O (1 syms rebound)
- PORTED `p2o_DispVU1MultiDefault` w1 @ 0x0010E748 <- aug6 seki/src/DisplayP2O (2 syms rebound)
- PORTED `p2o_SetDefaultEnviroment` w1 @ 0x0010E950 <- aug6 seki/src/DisplayP2O (1 syms rebound)

### src/fuzio
- PORTED `fzMagnitude3f` w1 @ 0x001687B8 <- aug6 fumi/src/fuzio (2 syms rebound)
- PORTED `fzMagnitudefv` w3 @ 0x001688E0 <- aug6 fumi/src/fuzio (7 syms rebound)
- PORTED `fzShowM` w1 @ 0x00168690 <- aug6 fumi/src/fuzio (1 syms rebound)
- REVERTED `fzShowV` w1 @ 0x00168650 — [codegen] insn 9: expected `addiu	v0,v0,0` built `addiu	v0,v0,6448`

### src/layout_texture
- PORTED `default_item_select` w1 @ 0x001B5958 <- aug6 common/src/layout_texture (4 syms rebound)
- PORTED `display_primary_texture_layout` w1 @ 0x001B5A10 <- aug6 common/src/layout_texture (2 syms rebound)
- PORTED `exec_layout_texture` w1 @ 0x001B5B30 <- aug6 common/src/layout_texture (5 syms rebound)
- PORTED `lt_fade_status` w1 @ 0x001B6FD8 <- aug6 common/src/layout_texture (5 syms rebound)
- PORTED `texture_fading` w1 @ 0x001B5998 <- aug6 common/src/layout_texture (2 syms rebound)

### src/pool
- PORTED `InitLimitedPoolReflactionMesh` w1 @ 0x0010B040 <- aug6 sugipon/src/pool (4 syms rebound)
- PORTED `PoolDL` w1 @ 0x0010AF48 <- aug6 sugipon/src/pool (11 syms rebound)
- REVERTED `flushWork` w3 @ 0x0010AB28 — [codegen] insn 7: expected `lw	v1,392(v0)` built `lw	v1,376(v0)`
- PORTED `getWave` w1 @ 0x0010CF88 <- aug6 sugipon/src/pool (18 syms rebound)
- PORTED `setNodePursueParticleEffectWithUpperLimit` w1 @ 0x0010ABD8 <- aug6 sugipon/src/pool (7 syms rebound)

### src/st00a
- REVERTED `actSt00aAtr2` w3 @ 0x0020F7A0 — [codegen] insn 13: expected `addiu	a0,zero,349` built `addiu	a0,zero,348`
- REVERTED `actSt00aAtr2Chk` w1 @ 0x0020F830 — [codegen] insn 9: expected `addiu	a0,a0,0` built `addiu	a0,a0,5784`
- REVERTED `actSt00aDoor1DownEffect` w3 @ 0x0020FE60 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt00aDoor1Event` w3 @ 0x0020FB38 — [codegen] insn 27: expected `addiu	a0,zero,3453` built `addiu	a0,zero,3415`
- REVERTED `actSt00aDoor1UpChk` w3 @ 0x0020ED30 — [codegen] insn 20: expected `addiu	a0,zero,131` built `addiu	a0,zero,130`
- REVERTED `actSt00aDoor2DownChk` w1 @ 0x0020E8C8 — [codegen] insn 39: expected `addiu	a0,s0,0` built `addiu	a0,s0,4696`
- REVERTED `actSt00aDoor2UpEffect` w3 @ 0x0020FA98 — [codegen] insn 5: expected `addiu	a0,zero,75` built `addiu	a0,zero,74`
- REVERTED `actSt00aEne` w1 @ 0x0020F1E0 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `actSt00aEnemy2` w3 @ 0x0020F688 — [codegen] insn 14: expected `addiu	a0,zero,155` built `addiu	a0,zero,154`
- REVERTED `actSt00aInit` w1 @ 0x0020D7A8 — [undeclared] src/st00a.c:12: `actSt00aEnd_ext' undeclared (first use in this function)
- PORTED `actSt00aStair` w1 @ 0x0020F720 <- aug6 script/src/st00a (4 syms rebound)
- PORTED `actSt00aStairChk` w1 @ 0x0020D880 <- aug6 script/src/st00a (9 syms rebound)

### src/way_kidnap
- PORTED `CopyWpPos` w1 @ 0x002057C8 <- aug6 fumi/src/way_kidnap (1 syms rebound)
- REVERTED `NearestEnemyFromGirl` w1 @ 0x002056A8 — [parse] src/way_kidnap.c:3: parse error before `Nd'
- REVERTED `NumOfWpPos` w3 @ 0x00205788 — [codegen] insn 3: expected `addiu	a0,v1,4888` built `addiu	a0,v1,3328`
- PORTED `WayLengthOfGObj_GObj` w1 @ 0x00205860 <- aug6 fumi/src/way_kidnap (1 syms rebound)
- REVERTED `WayLengthOfGObj_Pos` w3 @ 0x00205808 — [codegen] insn 3: expected `addiu	a0,v1,4888` built `addiu	a0,v1,3328`
- REVERTED `WayLengthOfPos_Pos` w1 @ 0x002055C0 — [parse] src/way_kidnap.c:3: parse error before `Nd'
- REVERTED `WayPointWithRangeFromGObj` w3 @ 0x002058B8 — [codegen] insn 3: expected `addiu	a0,v1,4888` built `addiu	a0,v1,3328`
- REVERTED `add_wp_pos` w3 @ 0x00205548 — [undeclared] src/way_kidnap.c:16: structure has no member named `f0'

### ito/mpeg/mv_readbuf
- REVERTED `free_buffer` w1 @ 0x0019DB50 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory
- REVERTED `readBufBeginGet` w1 @ 0x0019DBF0 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory
- REVERTED `readBufBeginPut` w1 @ 0x0019DBC8 — [codegen] /primary/dev/ico-retail/ito/mpeg/mv_readbuf.c:3: mv_defs.h: No such file or directory

### src/Basic
- REVERTED `dma_init` w3 @ 0x001F6AA0 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)
- REVERTED `freeseki` w1 @ 0x001F6CB0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `matrix_init` w1 @ 0x001F6C20 <- aug6 seki/src/Basic (6 syms rebound)
- REVERTED `reallocseki` w1 @ 0x001F6DB8 — [codegen] insn 5: expected `lui	a2,0x0` built `addiu	a3,zero,382`

### src/BgAnimation
- PORTED `bga_CalcObject` w1 @ 0x001F9348 <- aug6 seki/src/BgAnimation (1 syms rebound)
- REVERTED `bga_CalcSdfCamera` w3 @ 0x001F9DD8 — [codegen] src/BgAnimation.c:131: invalid lvalue in increment
- PORTED `bga_CheckAnimationFinish` w1 @ 0x001FA760 <- aug6 seki/src/BgAnimation (1 syms rebound)
- REVERTED `bga_CheckAnimationFrame` w1 @ 0x001FA7F8 — [codegen] insn 25: expected `bc1f	98 <bga_CheckAnimationFrame+0x98>` built `sll	zero,zero,0x0`
- REVERTED `bga_GetCameraMatrix` w3 @ 0x001FA5E0 — [codegen] insn 14: expected `addiu	a1,zero,996` built `addiu	a1,zero,899`
- PORTED `bga_SetCamFrame` w1 @ 0x001FA6D8 <- aug6 seki/src/BgAnimation (1 syms rebound)

### src/brain
- PORTED `brainGetLevel` w1 @ 0x00182AB8 <- aug6 omori/src/brain (2 syms rebound)
- PORTED `brainGetTarget` w1 @ 0x00182958 <- aug6 omori/src/brain (2 syms rebound)
- PORTED `brainLevelProcess` w1 @ 0x00182890 <- aug6 omori/src/brain (2 syms rebound)
- PORTED `brainStatusSet` w1 @ 0x001829D0 <- aug6 omori/src/brain (2 syms rebound)

### src/frameDependSequence
- PORTED `ExecFrameDependSequence` w3 @ 0x001D12D8 <- aug6 sugipon/src/frameDependSequence (1 syms rebound)
- PORTED `ExecuteSEPackage` w1 @ 0x001D1428 <- aug6 sugipon/src/frameDependSequence (0 syms rebound)
- REVERTED `ExecuteSEPackageWithGroupVariation` w3 @ 0x001D1410 — [codegen] insn 1: expected `lwc1	$f0,1604(v0)` built `lwc1	$f0,1588(v0)`
- REVERTED `execEff` w3 @ 0x001D12C0 — [codegen] insn 4: expected `lw	a0,1564(v0)` built `lw	a0,1548(v0)`
- PORTED `executeSEPackageByGObj` w1 @ 0x001D12E0 <- aug6 sugipon/src/frameDependSequence (1 syms rebound)
- PORTED `executeSEPackageWithNoGObj` w1 @ 0x001D13A8 <- aug6 sugipon/src/frameDependSequence (3 syms rebound)
- PORTED `playSEConditionID` w3 @ 0x001D12A8 <- aug6 sugipon/src/frameDependSequence (1 syms rebound)

### src/geometryManager
- PORTED `GetRootQuaternionByDObj` w1 @ 0x001028F0 <- aug6 sugipon/src/geometryManager (5 syms rebound)
- PORTED `SetRootMatrixWithTransOffset` w1 @ 0x00102DE0 <- aug6 sugipon/src/geometryManager (2 syms rebound)
- PORTED `UpdateRootMatrix` w3 @ 0x001029B8 <- aug6 sugipon/src/geometryManager (1 syms rebound)

### src/hand-camera
- PORTED `ClearHandCameraCorrect` w1 @ 0x001943C8 <- aug6 omori/src/hand-camera (3 syms rebound)
- PORTED `HandyCamera_TargetMoveType` w1 @ 0x00194398 <- aug6 omori/src/hand-camera (2 syms rebound)
- PORTED `InitHandCameraCorrect` w1 @ 0x00194400 <- aug6 omori/src/hand-camera (3 syms rebound)
- REVERTED `RotateAccordingToStick_PatternThree` w1 @ 0x00194360 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `SetLimitHandCameraCorrect` w1 @ 0x00194440 <- aug6 omori/src/hand-camera (3 syms rebound)

### src/lightning
- PORTED `DrawLightning` w1 @ 0x001999A8 <- aug6 ito/src/lightning (2 syms rebound)
- PORTED `DrawLightning2` w1 @ 0x001997B8 <- aug6 ito/src/lightning (2 syms rebound)
- REVERTED `DrawLightningN` w1 @ 0x001998C0 — [codegen] src/lightning.c:45: invalid initializer

### src/motionOrientManager
- REVERTED `CopyBlendMotionDataSource` w3 @ 0x001E3D08 — [codegen] insn 11: expected `lw	a0,2112(v1)` built `lw	a0,2096(v1)`
- REVERTED `ExecutePauseSlipProc` w3 @ 0x001E4548 — [codegen] insn 15: expected `xori	v0,v0,0x43d` built `xori	v0,v0,0x43f`
- REVERTED `ForTest_ForceShiftMotion` w3 @ 0x001E10F0 — [codegen] [§5.7] far in-TU global via gp_rel where original uses %hi/%lo
- REVERTED `GetNbMotionFrames` w3 @ 0x001E09F8 — [codegen] insn 10: expected `lw	v1,2012(a1)` built `lw	v1,1996(a1)`
- REVERTED `SetParallelMotionTable` w3 @ 0x001E3F40 — [codegen] insn 8: expected `lw	s0,1136(v0)` built `lw	s0,1120(v0)`
- PORTED `execFrameTrigger` w1 @ 0x001E0B58 <- aug6 sugipon/src/motionOrientManager (7 syms rebound)
- PORTED `getStreamMotionGeometry` w1 @ 0x001E2370 <- aug6 sugipon/src/motionOrientManager (1 syms rebound)
- REVERTED `orientDebug` w3 @ 0x001E0988 — [codegen] insn 8: expected `lw	v1,2012(a1)` built `lw	v1,1996(a1)`
- PORTED `sendStateMail` w1 @ 0x001E0C38 <- aug6 sugipon/src/motionOrientManager (2 syms rebound)
- REVERTED `shiftMotionData` w3 @ 0x001E0C98 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `shiftMotionOrientBeginFunc` w1 @ 0x001E0FE8 — [unresolved-symbol] unresolved-symbol: insn 19 `D_006169D8`: retail symbol D_004BC710 (0x004BC710) undefined
- SKIPPED `shiftMotionOrientEndFunc` w3 @ 0x001E0D50 — jtbl

### src/switch
- REVERTED `BoxMemoryFunc` w1 @ 0x001C0E48 — [codegen] src/switch.c:85: storage size of `buf2' isn't known
- REVERTED `GetDistanceOfGObj` w1 @ 0x001C0F70 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory
- REVERTED `getAlign` w1 @ 0x001C0EB0 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory
- REVERTED `moveXMinus` w1 @ 0x001C10F8 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory
- REVERTED `moveXPlus` w1 @ 0x001C1038 — [codegen] src/switch.c:9: switch.c.inc: No such file or directory

### src/windField
- REVERTED `InitWindField` w1 @ 0x001F4800 — [codegen] insn 83: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `drawSenpuuki` w1 @ 0x001F4BE0 <- aug6 sugipon/src/windField (1 syms rebound)
- REVERTED `getParallelWindVector` w1 @ 0x001F4DD8 — [codegen] insn 1: expected `addiu	v0,v0,0` built `addiu	v0,v0,1024`
- PORTED `getRadiateWindVector` w1 @ 0x001F4DE8 <- aug6 sugipon/src/windField (2 syms rebound)

### ios/mcard
- PORTED `iosMcGetInfo` w1 @ 0x00137F90 <- aug6 fumi/ios/mcard (2 syms rebound)
- PORTED `iosMcMgrLoadSeg` w3 @ 0x00137538 <- aug6 fumi/ios/mcard (1 syms rebound)
- PORTED `iosMcMgrSaveProductBlock` w3 @ 0x00137548 <- aug6 fumi/ios/mcard (1 syms rebound)
- PORTED `iosMcSync` w1 @ 0x00137F48 <- aug6 fumi/ios/mcard (2 syms rebound)
- PORTED `iosMcTest` w1 @ 0x00137F08 <- aug6 fumi/ios/mcard (2 syms rebound)

### ito/mpeg/mv_videodec
- REVERTED `videoDecEndPut` w1 @ 0x0019E278 — [emits-data] emits-data: +4 bytes of .rodata/.sdata/.lit4 (string or out-of-line float literal; needs a Phase-5 rodata carve)

### src/DObj
- PORTED `FreeDObj` w1 @ 0x0019EF10 <- aug6 common/src/DObj (4 syms rebound)
- REVERTED `initGeometryState` w1 @ 0x0019E598 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `initMatrixDObj` w1 @ 0x0019E5D0 <- aug6 common/src/DObj (0 syms rebound)

### src/DisplayFont
- PORTED `font_CheckAlign` w1 @ 0x001FA898 <- aug6 seki/src/DisplayFont (1 syms rebound)
- PORTED `font_GetWidth` w1 @ 0x001FAA30 <- aug6 seki/src/DisplayFont (1 syms rebound)
- PORTED `font_Print` w1 @ 0x001FA998 <- aug6 seki/src/DisplayFont (1 syms rebound)

### src/Light
- REVERTED `light_DrawCursor` w3 @ 0x00114E78 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `light_Tool` w3 @ 0x00114F18 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `light_getAmbientLight` w1 @ 0x00114D80 <- aug6 seki/src/Light (1 syms rebound)

### src/RegistPacket
- PORTED `reg_dispSObj` w1 @ 0x0011FC28 <- aug6 seki/src/RegistPacket (7 syms rebound)

### src/Texture
- PORTED `tex_setTexReg` w1 @ 0x0012AE40 <- aug6 seki/src/Texture (4 syms rebound)

### src/attackCheckBoundary
- REVERTED `AttackCheckBoundaryBeforeFunc` w3 @ 0x001BB820 — [unresolved-symbol] unresolved-symbol: insn 11 `D_004BA260`: retail symbol D_0062EF60 (0x0062EF60) undefined
- PORTED `CreateAttackCheckBoundary` w1 @ 0x001BBE50 <- aug6 sugipon/src/attackCheckBoundary (3 syms rebound)
- PORTED `GetAttackCheckBoundaryManagerStatus` w1 @ 0x001BBEA0 <- aug6 sugipon/src/attackCheckBoundary (0 syms rebound)
- PORTED `InitAttackCheckBoundaryGeo` w1 @ 0x001BB8C0 <- aug6 sugipon/src/attackCheckBoundary (6 syms rebound)
- REVERTED `actAttackCheckBoundaryStart` w3 @ 0x001BBDD8 — [codegen] insn 1: expected `lw	t1,2048(v1)` built `lw	t1,2032(v1)`

### src/chain
- PORTED `InitChainGeo` w1 @ 0x0018DDF0 <- aug6 omori/src/chain (5 syms rebound)
- REVERTED `UpdateRootPosition` w3 @ 0x0018CF60 — [codegen] insn 7: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `chain_simulate_term_simple` w1 @ 0x0018CFE0 <- aug6 omori/src/chain (1 syms rebound)
- PORTED `collisionCheck` w1 @ 0x0018CFD0 <- aug6 omori/src/chain (1 syms rebound)
- REVERTED `pendulum_Process` w3 @ 0x0018DD80 — [codegen] insn 9: expected `lw	s1,2048(v1)` built `lw	s1,2032(v1)`

### src/charFileManager
- PORTED `CSVSYSTEM_ReadCharFiles` w1 @ 0x001A26E0 <- aug6 common/src/charFileManager (6 syms rebound)
- REVERTED `ReadModelFile` w3 @ 0x001A1030 — [codegen] insn 1: expected `dli	v1,0x9450` built `dli	v1,0x93c0`
- PORTED `ReadParticleEffectFile` w1 @ 0x001A1D88 <- aug6 common/src/charFileManager (11 syms rebound)
- PORTED `ReadSoundHdFile` w1 @ 0x001A20D8 <- aug6 common/src/charFileManager (7 syms rebound)
- PORTED `ReadStageSettingFile` w1 @ 0x001A2610 <- aug6 common/src/charFileManager (12 syms rebound)
- REVERTED `ReadVolumeModelFile` w3 @ 0x001A10B0 — [codegen] insn 1: expected `dli	v1,0x9450` built `dli	v1,0x93c0`

### src/debug
- REVERTED `debug_Assert` w1 @ 0x001A2D58 — [codegen] insn 7: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `debug_FlushFontWindow` w1 @ 0x001A40C8 <- aug6 common/src/debug (11 syms rebound)
- REVERTED `debug_openLog` w3 @ 0x001A2D78 — [codegen] insn 15: expected `addiu	a1,zero,1283` built `addiu	a1,zero,1268`
- PORTED `draw_batsu` w3 @ 0x001A43F0 <- aug6 common/src/debug (1 syms rebound)

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
- PORTED `actSt10rChain` w3 @ 0x00227500 <- aug6 script/src/st10r (4 syms rebound)
- PORTED `actSt10rEnemy1` w1 @ 0x00227750 <- aug6 script/src/st10r (5 syms rebound)
- PORTED `actSt10rSekizo` w3 @ 0x002275E0 <- aug6 script/src/st10r (4 syms rebound)
- PORTED `actSt10rTower` w1 @ 0x00227478 <- aug6 script/src/st10r (6 syms rebound)

### src/staffroll
- PORTED `staffRollMain` w1 @ 0x001B81B8 <- aug6 common/src/staffroll (13 syms rebound)
- PORTED `staffRollScroll` w1 @ 0x001B8120 <- aug6 common/src/staffroll (4 syms rebound)

### src/tableSin
- PORTED `GetTableArcCos` w1 @ 0x0010DBD0 <- aug6 sugipon/src/tableSin (3 syms rebound)
- PORTED `GetTableArcTan2` w1 @ 0x0010DC38 <- aug6 sugipon/src/tableSin (2 syms rebound)

### ios/inflate
- PORTED `close_inflate_handler` w1 @ 0x00133570 <- aug6 fumi/ios/inflate (1 syms rebound)
- PORTED `inflate_start` w1 @ 0x00133510 <- aug6 fumi/ios/inflate (3 syms rebound)

### ios/mblock
- PORTED `new_segment` w1 @ 0x00136088 <- aug6 fumi/ios/mblock (0 syms rebound)
- PORTED `strdup_mblock` w1 @ 0x00136140 <- aug6 fumi/ios/mblock (1 syms rebound)

### ios/mcdata
- PORTED `_iosMcIconWriteIconsys` w1 @ 0x00138068 <- aug6 fumi/ios/mcdata (2 syms rebound)
- PORTED `iosMcIconWriteIcon` w1 @ 0x00138020 <- aug6 fumi/ios/mcdata (2 syms rebound)
- REVERTED `iosMcIconWriteIconsys` w1 @ 0x00137FD8 — [codegen] insn 17: expected `<end>` built `sll	zero,zero,0x0`

### ito/mpeg/mv_vobuf
- PORTED `voBufGetTag` w1 @ 0x0019E520 <- aug6 ito/mpeg/mv_vobuf (1 syms rebound)
- PORTED `voBufReset` w3 @ 0x0019E4E0 <- aug6 ito/mpeg/mv_vobuf (1 syms rebound)

### src/PObj
- PORTED `FreePObj` w1 @ 0x00240BD0 <- aug6 common/src/PObj (4 syms rebound)
- PORTED `InitPObj` w1 @ 0x00240B88 <- aug6 common/src/PObj (2 syms rebound)
- PORTED `MakeBoundingBox` w3 @ 0x00240B60 <- aug6 common/src/PObj (1 syms rebound)
- PORTED `MakePacket` w3 @ 0x00240B68 <- aug6 common/src/PObj (1 syms rebound)

### src/act_bird
- PORTED `BirdGeo` w1 @ 0x00197338 <- aug6 ito/src/act_bird (3 syms rebound)
- REVERTED `interp_vector_sa` w3 @ 0x00197080 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `trans_bird` w1 @ 0x001970E8 <- aug6 ito/src/act_bird (4 syms rebound)

### src/e3
- REVERTED `actE3CageFall` w3 @ 0x0020A360 — [codegen] src/e3.c:48: incompatible types in assignment
- REVERTED `actE3CageFallDemo` w3 @ 0x0020A4C0 — [codegen] insn 7: expected `addiu	a0,zero,327` built `addiu	a0,zero,326`
- REVERTED `actE3CageFallEffect` w3 @ 0x0020A578 — [codegen] insn 6: expected `addiu	a0,zero,331` built `addiu	a0,zero,330`
- REVERTED `actE3Capsule` w3 @ 0x0020A0A0 — [codegen] insn 17: expected `addiu	a0,zero,330` built `addiu	a0,zero,329`
- REVERTED `actE3CapsuleDemoCancel` w3 @ 0x0020A150 — [codegen] insn 17: expected `addiu	a0,zero,330` built `addiu	a0,zero,329`
- REVERTED `actE3GateChk` w1 @ 0x0020A720 — [codegen] src/e3.c:65: invalid initializer
- REVERTED `actE3GateDemo` w3 @ 0x0020A7B0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actE3GateJimaku` w3 @ 0x0020A8C0 — [codegen] insn 6: expected `addiu	a0,zero,740` built `addiu	a0,zero,739`
- REVERTED `actE3Inst1` w3 @ 0x0020AEF0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actE3Inst1Chk` w3 @ 0x00209FE8 — [codegen] insn 17: expected `addiu	a0,zero,330` built `addiu	a0,zero,329`
- REVERTED `actE3St01bInit` w3 @ 0x0020AB70 — [codegen] insn 30: expected `addiu	a2,zero,483` built `addiu	a2,zero,482`
- PORTED `actE3St09aSekizo` w1 @ 0x0020A5F8 <- aug6 script/src/e3 (6 syms rebound)
- REVERTED `actE3St09aSekizoChk` w3 @ 0x0020A668 — [codegen] insn 24: expected `addiu	a0,zero,330` built `addiu	a0,zero,329`
- REVERTED `actE3St13cInit` w3 @ 0x0020A2D0 — [codegen] insn 7: expected `addiu	a0,zero,326` built `addiu	a0,zero,325`
- REVERTED `actE3Title` w3 @ 0x00209E88 — [codegen] insn 17: expected `addiu	a0,zero,332` built `addiu	a0,zero,331`
- PORTED `actE3TitleChk` w1 @ 0x00209F28 <- aug6 script/src/e3 (2 syms rebound)
- REVERTED `actE3TitleFrameChk` w3 @ 0x00209F58 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actE3Warning` w3 @ 0x0020ACB0 — [codegen] insn 6: expected `addiu	a0,zero,750` built `addiu	a0,zero,749`
- REVERTED `actE3WarningChk` w3 @ 0x00209DD0 — [codegen] insn 17: expected `addiu	a0,zero,332` built `addiu	a0,zero,331`

### src/enemy
- PORTED `EnemyCheckHit` w1 @ 0x001CD490 <- aug6 sugipon/src/enemy (7 syms rebound)
- REVERTED `EnemyGetNSafeParts` w3 @ 0x001CE7C8 — [codegen] insn 9: expected `lw	a0,2048(v0)` built `lw	a0,2032(v0)`
- REVERTED `EnemySetfDisappear` w3 @ 0x001CE718 — [codegen] insn 2: expected `lw	v0,2112(v0)` built `lw	v0,2096(v0)`
- REVERTED `GetEnemyHitNodeFlag` w3 @ 0x001CE9B8 — [codegen] insn 4: expected `lw	v0,2048(v0)` built `lw	v0,2032(v0)`
- REVERTED `HotInitDemoMotionGeo` w3 @ 0x001CE998 — [codegen] insn 2: expected `lw	v0,2048(a2)` built `lw	v0,2032(a2)`
- REVERTED `InitDemoMotionGeo` w3 @ 0x001CE978 — [codegen] insn 2: expected `lw	v0,2048(a2)` built `lw	v0,2032(a2)`
- REVERTED `ReviveEnemyParticle` w3 @ 0x001CE768 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- PORTED `SetEnemyHitGeometryAction` w1 @ 0x001CE8F0 <- aug6 sugipon/src/enemy (5 syms rebound)
- REVERTED `isExistEnemyParticle` w3 @ 0x001CE778 — [codegen] insn 6: expected `lw	a0,2048(v0)` built `lw	a0,2032(v0)`

### src/itou_boss
- PORTED `BossCtrlGeo` w1 @ 0x00198328 <- aug6 ito/src/itou_boss (1 syms rebound)
- REVERTED `effect_end_func` w1 @ 0x00197FE8 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `gene_enemy` w3 @ 0x00198218 — [codegen] [§5.9] rodata lui+addiu materialized late next to jal

### src/kanbanBoot
- PORTED `kanbanBootMain` w1 @ 0x001B0A98 <- aug6 common/src/kanbanBoot (1 syms rebound)
- PORTED `kanbanBootMcCheck` w1 @ 0x001B0A80 <- aug6 common/src/kanbanBoot (1 syms rebound)

### src/st01b
- PORTED `actSt01bEnd` w3 @ 0x00210AC8 <- aug6 script/src/st01b (4 syms rebound)
- REVERTED `actSt01bEnemy1` w3 @ 0x002106C0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt01bEnemy2` w1 @ 0x00210738 <- aug6 script/src/st01b (6 syms rebound)
- PORTED `actSt01bEnemy3` w1 @ 0x002107E0 <- aug6 script/src/st01b (6 syms rebound)
- REVERTED `actSt01bEnemy5` w3 @ 0x00210908 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt01bEnemy6` w1 @ 0x00210980 <- aug6 script/src/st01b (4 syms rebound)
- REVERTED `actSt01bFloorChk` w3 @ 0x00210298 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt01bFloorEvent` w3 @ 0x00210BB8 <- aug6 script/src/st01b (4 syms rebound)
- REVERTED `actSt01bInit` w3 @ 0x0020FF68 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,2688`
- PORTED `actSt01bWay` w3 @ 0x002109E8 <- aug6 script/src/st01b (4 syms rebound)
- REVERTED `actSt01bWayOffChk` w3 @ 0x00210D78 — [codegen] insn 8: expected `addiu	a0,zero,162` built `addiu	a0,zero,161`
- PORTED `actSt01bWayOnChk` w3 @ 0x00210C98 <- aug6 script/src/st01b (4 syms rebound)

### src/st03t
- PORTED `actSt03tBoxA` w3 @ 0x002125D8 <- aug6 script/src/st03t (6 syms rebound)
- PORTED `actSt03tBoxB` w3 @ 0x00212668 <- aug6 script/src/st03t (6 syms rebound)
- REVERTED `actSt03tEneChk` w1 @ 0x00212D00 — [codegen] insn 14: expected `lui	a1,0x500` built `lui	a1,0x300`
- PORTED `actSt03tGene` w3 @ 0x00212908 <- aug6 script/src/st03t (4 syms rebound)
- REVERTED `actSt03tGirlCam` w3 @ 0x00212760 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt03tGirlCamEndChk` w3 @ 0x00212B60 — [codegen] insn 15: expected `addiu	a0,zero,85` built `addiu	a0,zero,84`
- PORTED `actSt03tGirlCamEvent` w3 @ 0x002129E8 <- aug6 script/src/st03t (4 syms rebound)
- REVERTED `actSt03tInit` w3 @ 0x002126F8 — [codegen] insn 12: expected `addiu	a2,zero,88` built `addiu	a2,zero,87`
- REVERTED `actSt03tSekizo` w3 @ 0x00212808 — [codegen] insn 19: expected `addiu	a1,zero,397` built `addiu	a1,zero,393`
- REVERTED `actSt03tSwitchL` w3 @ 0x00212260 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt03tSwitchLChk` w3 @ 0x00212348 — [codegen] insn 15: expected `addiu	a0,zero,87` built `addiu	a0,zero,86`
- REVERTED `actSt03tSwitchLUpChk` w3 @ 0x002123F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt03tSwitchR` w3 @ 0x00212470 — [unresolved-symbol] unresolved-symbol: insn 18 `actSt02aSecretItem`: retail symbol D_00211EC8 (0x00211EC8) undefined
- REVERTED `actSt03tSwitchRChk` w3 @ 0x00212510 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt03tSwitchRUpChk` w3 @ 0x00212560 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt03tWay` w3 @ 0x00212880 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/st09a
- REVERTED `actSt09aBrg` w3 @ 0x00224E80 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt09aBrgDown` w3 @ 0x00224C78 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt09aElv` w3 @ 0x00224DE0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt09aElvDown` w3 @ 0x002249F8 — [codegen] insn 23: expected `addiu	a0,zero,357` built `addiu	a0,zero,356`
- REVERTED `actSt09aElvMain` w3 @ 0x00224F28 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt09aElvSwitch` w3 @ 0x00224FD0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt09aElvUp` w3 @ 0x00225040 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt09aIntro` w3 @ 0x00224E30 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt09aIntroChk` w1 @ 0x00225150 <- aug6 script/src/st09a (6 syms rebound)
- REVERTED `actSt09aSekizo` w3 @ 0x00224B10 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt09aSekizoEvent` w1 @ 0x002250B8 <- aug6 script/src/st09a (6 syms rebound)

### src/st10l
- REVERTED `actSt10lChain` w3 @ 0x00225E28 — [codegen] insn 8: expected `addiu	a0,a0,0` built `addiu	a0,a0,1536`
- PORTED `actSt10lFloor` w1 @ 0x00225EF0 <- aug6 script/src/st10l (6 syms rebound)
- PORTED `actSt10lFloorLeft` w3 @ 0x002259D0 <- aug6 script/src/st10l (4 syms rebound)
- PORTED `actSt10lFloorRight` w1 @ 0x00225AB0 <- aug6 script/src/st10l (4 syms rebound)
- PORTED `actSt10lGondola` w1 @ 0x00225F68 <- aug6 script/src/st10l (2 syms rebound)
- REVERTED `actSt10lGondolaUp` w3 @ 0x00225B20 — [codegen] insn 4: expected `addiu	a0,zero,1452` built `addiu	a0,zero,1446`
- REVERTED `actSt10lInit` w3 @ 0x002258F0 — [codegen] insn 55: expected `<end>` built `sll	zero,zero,0x0`

### src/st13c
- PORTED `actSt13cCage1stDownDemoCancel` w1 @ 0x0022B810 <- aug6 script/src/st13c (4 syms rebound)
- REVERTED `actSt13cCageFallChk` w3 @ 0x0022B9A8 — [codegen] insn 36: expected `addiu	a2,zero,341` built `addiu	a2,zero,340`
- REVERTED `actSt13cCageFallEffect` w3 @ 0x0022BC30 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt13cConte04` w3 @ 0x0022B650 <- aug6 script/src/st13c (4 syms rebound)
- PORTED `actSt13cConte04Jimaku` w3 @ 0x0022B730 <- aug6 script/src/st13c (4 syms rebound)
- REVERTED `actSt13cConte05` w3 @ 0x0022BA70 — [codegen] insn 17: expected `addiu	a0,zero,343` built `addiu	a0,zero,342`
- REVERTED `actSt13cConte05Jimaku` w3 @ 0x0022BB98 — [codegen] insn 15: expected `addiu	a0,zero,340` built `addiu	a0,zero,339`
- PORTED `actSt13cEnd` w3 @ 0x0022B510 <- aug6 script/src/st13c (6 syms rebound)
- REVERTED `actSt13cGirlCarryChk` w3 @ 0x0022BCA8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt13cInit` w3 @ 0x0022B480 <- aug6 script/src/st13c (6 syms rebound)

### src/st47a
- PORTED `actSt47aBarricade` w1 @ 0x00236BA8 <- aug6 script/src/st47a (6 syms rebound)
- REVERTED `actSt47aEnd` w3 @ 0x00235E98 — [codegen] insn 23: expected `addiu	a0,zero,101` built `addiu	a0,zero,100`
- REVERTED `actSt47aEnemy1` w3 @ 0x00236588 — [codegen] insn 13: expected `addiu	a0,zero,715` built `addiu	a0,zero,714`
- REVERTED `actSt47aHane1` w3 @ 0x00236A00 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt47aHane2` w1 @ 0x00236A78 <- aug6 script/src/st47a (6 syms rebound)
- REVERTED `actSt47aInit` w3 @ 0x00235C70 — [codegen] insn 24: expected `lui	s3,0x4d` built `lui	s3,0x0`
- REVERTED `actSt47aRope` w3 @ 0x00236B30 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt47aRopeChk` w3 @ 0x00236478 — [codegen] insn 26: expected `addiu	a0,zero,104` built `addiu	a0,zero,103`
- REVERTED `actSt47aSekizo1` w3 @ 0x00236730 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt47aSekizo1Chk` w3 @ 0x00235FD8 — [codegen] insn 24: expected `lui	s3,0x4d` built `lui	s3,0x0`
- REVERTED `actSt47aSekizo2` w3 @ 0x002367A8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt47aSekizo3` w3 @ 0x00236870 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt47aSekizo4` w3 @ 0x00236938 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt47aTorch` w3 @ 0x00236660 — [codegen] insn 13: expected `addiu	a0,zero,716` built `addiu	a0,zero,715`

### src/stormTest
- PORTED `InitStormTestGeo` w1 @ 0x001EF9E0 <- aug6 sugipon/src/stormTest (4 syms rebound)
- PORTED `StormTestGeo` w3 @ 0x001EF9D0 <- aug6 sugipon/src/stormTest (1 syms rebound)

### src/sugiTree
- REVERTED `SugiLeafDL2` w1 @ 0x001F11A0 — [callee-sig-conflict] src/sugiTree.c:4: conflicting types for `SugiCb'
- REVERTED `SugiLeafGeo2` w1 @ 0x001F1148 — [codegen] insn 7: expected `<end>` built `sll	zero,zero,0x0`

### src/way_sys
- REVERTED `_FUNC_GetWay_begin` w1 @ 0x00176B38 — [codegen] insn 31: expected `<end>` built `sll	zero,zero,0x0`
- PORTED `create_box_bridge` w1 @ 0x00176BC8 <- aug6 fumi/src/way_sys (14 syms rebound)

### src/way_tool
- PORTED `draw_way_group` w1 @ 0x00207018 <- aug6 fumi/src/way_tool (7 syms rebound)
- REVERTED `group_create` w1 @ 0x00206208 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PORTED `way_toolDL` w1 @ 0x002070B0 <- aug6 fumi/src/way_tool (10 syms rebound)

### ios/memory
- PORTED `iosMallocCheckLeak` w1 @ 0x001394F0 <- aug6 fumi/ios/memory (4 syms rebound)
- REVERTED `iosMallocCheckLeak2` w3 @ 0x00139598 — [callee-sig-conflict] ios/memory.c:111: conflicting types for `iosMallocCheckLeak2'
- PORTED `iosMallocDebug` w1 @ 0x00138BF0 <- aug6 fumi/ios/memory (6 syms rebound)
- PORTED `iosMallocInitPartition` w3 @ 0x00139C30 <- aug6 fumi/ios/memory (12 syms rebound)

### sound/soundManager
- PORTED `sndInit` w1 @ 0x001446E8 <- aug6 fumi/sound/soundManager (4 syms rebound)

### src/DmaPacket
- PORTED `dpk_Init` w1 @ 0x001FBAA8 <- aug6 seki/src/DmaPacket (3 syms rebound)

### src/Primitive
- PORTED `prim_SetFan2D` w1 @ 0x0011BFC0 <- aug6 seki/src/Primitive (1 syms rebound)

### src/act-way
- PORTED `ACTWay_IsMustWalkFromWay` w1 @ 0x00201D50 <- aug6 fumi/src/act-way (2 syms rebound)

### src/act2
- PORTED `BeforeFunc2` w1 @ 0x00203C40 <- aug6 fumi/src/act2 (3 syms rebound)

### src/backStage
- PORTED `backStageDebugTimeZero` w3 @ 0x001A0EB8 <- aug6 common/src/backStage (10 syms rebound)
- PORTED `backStageTsuresariReturn` w3 @ 0x001A0F60 <- aug6 common/src/backStage (10 syms rebound)

### src/chandelier
- PORTED `ChandelierDL` w1 @ 0x001C33D8 <- aug6 sugipon/src/chandelier (5 syms rebound)
- PORTED `InitChandelierGeo` w1 @ 0x001C3470 <- aug6 sugipon/src/chandelier (2 syms rebound)

### src/clipCollisionManager
- PORTED `actClipCollisionCore` w1 @ 0x001C3760 <- aug6 sugipon/src/clipCollisionManager (1 syms rebound)

### src/darkVolume
- PORTED `renderViewCoordZSphere` w1 @ 0x001CB910 <- aug6 sugipon/src/darkVolume (3 syms rebound)

### src/gflag
- REVERTED `gflagInit` w3 @ 0x0017B2B8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `gflagOff` w3 @ 0x0017B3F8 — [codegen] insn 13: expected `addiu	s1,zero,1214` built `addiu	s1,zero,1193`

### src/icoMisc
- PORTED `ExitIcoMisc` w1 @ 0x001AE880 <- aug6 common/src/icoMisc (2 syms rebound)

### src/jimaku
- REVERTED `jimakuUndisp` w3 @ 0x00176130 — [codegen] insn 4: expected `sw	zero,1588(v1)` built `sw	zero,1572(v1)`

### src/motionFileManager
- PORTED `InitMotionMemorySize` w1 @ 0x001D4E88 <- aug6 sugipon/src/motionFileManager (6 syms rebound)
- REVERTED `pursueNodeList` w3 @ 0x001D4E30 — [codegen] insn 5: expected `addiu	a1,zero,1085` built `addiu	a1,zero,1087`

### src/motionManager
- PORTED `GetWallVector` w1 @ 0x001DC938 <- aug6 sugipon/src/motionManager (9 syms rebound)
- REVERTED `_checkCliffAndWall` w3 @ 0x001D9C58 — [codegen] insn 10: expected `lwc1	$f0,464(v0)` built `lwc1	$f0,448(v0)`
- PORTED `checkActPointWithHeight` w1 @ 0x001D8C40 <- aug6 sugipon/src/motionManager (12 syms rebound)
- REVERTED `checkCliffAndWallStateAtJump` w3 @ 0x001D9E10 — [codegen] insn 15: expected `lwc1	$f14,440(v0)` built `lwc1	$f14,424(v0)`
- REVERTED `checkCliffState` w3 @ 0x001D9BB8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/poly-flat
- PORTED `after_DrawPolygon` w1 @ 0x00195380 <- aug6 omori/src/poly-flat (3 syms rebound)
- PORTED `before_DrawLine` w1 @ 0x00195510 <- aug6 omori/src/poly-flat (5 syms rebound)

### src/sceneManager
- REVERTED `test_nextstage_firstwalk_set` w3 @ 0x001B7F20 — [codegen] insn 20: expected `addiu	a1,zero,47` built `addiu	a1,zero,46`

### src/st05c
- PORTED `actSt04rDoor` w1 @ 0x0021EE70 <- aug6 script/src/st05c (6 syms rebound)
- PORTED `actSt04rDoor2` w1 @ 0x0021EEF8 <- aug6 script/src/st05c (5 syms rebound)
- REVERTED `actSt04rDoor2Chk` w3 @ 0x0021ECF8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rDoorChk` w3 @ 0x0021ECB0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05cDoorDownChk` w3 @ 0x0021EC18 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05cSolarXL` w3 @ 0x0021ED40 — [codegen] insn 16: expected `addiu	a0,zero,225` built `addiu	a0,zero,224`
- REVERTED `actSt05cWaterXL` w3 @ 0x0021EDC8 — [codegen] insn 13: expected `addiu	a0,zero,1098` built `addiu	a0,zero,1095`

### src/st08a
- REVERTED `actSt08aDoorUp` w3 @ 0x00223B38 — [codegen] insn 16: expected `addiu	a0,zero,314` built `addiu	a0,zero,313`
- REVERTED `actSt08aEnd` w3 @ 0x00223970 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt08aEne1Chk` w3 @ 0x00223A08 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt08aEne2Chk` w3 @ 0x00223AA0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `actSt08aEnemy1` w1 @ 0x00223D58 <- aug6 script/src/st08a (5 syms rebound)
- PORTED `actSt08aIntroChk` w1 @ 0x00223E50 <- aug6 script/src/st08a (3 syms rebound)

### src/st17a
- PORTED `actSt17aHasiChk` w1 @ 0x0022D5C8 <- aug6 script/src/st17a (6 syms rebound)

### src/st20a
- REVERTED `actSt20aBridgeMain` w3 @ 0x00233F80 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aBridgeSwitch` w3 @ 0x00233FF8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aEne` w3 @ 0x00233D70 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aEnemy1` w3 @ 0x00233DE8 — [codegen] insn 23: expected `addiu	a0,zero,135` built `addiu	a0,zero,134`
- PORTED `actSt20aEnemy2` w1 @ 0x00233E80 <- aug6 script/src/st20a (5 syms rebound)
- PORTED `actSt20aEnemy3` w1 @ 0x00233EE8 <- aug6 script/src/st20a (5 syms rebound)
- REVERTED `actSt20aExit` w3 @ 0x00233C48 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aGondolaDown` w3 @ 0x00232350 — [codegen] insn 33: expected `addiu	a0,s0,0` built `addiu	a0,s0,760`
- REVERTED `actSt20aGondolaMain` w3 @ 0x00234070 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aGondolaSwitch` w3 @ 0x002340E8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aGondolaUp` w3 @ 0x002324E0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt20aInit` w3 @ 0x00231F18 — [codegen] insn 7: expected `addiu	a0,zero,554` built `addiu	a0,zero,553`

### src/staticBlur
- PORTED `cleanUpFB` w1 @ 0x001EF118 <- aug6 sugipon/src/staticBlur (12 syms rebound)

### src/waySystemManager
- REVERTED `CreateWaySystemManagerGObj` w3 @ 0x001F2250 — [codegen] insn 9: expected `addiu	a2,a0,496` built `addiu	a2,a0,480`
- REVERTED `RequestGetWayBegin` w1 @ 0x001F22A0 — [codegen] insn 4: expected `addiu	t0,t0,0` built `addiu	t0,t0,288`
- REVERTED `actWaySystemCore` w1 @ 0x001F22E0 — [codegen] insn 7: expected `addiu	a0,a0,0` built `addiu	a0,a0,208`

### ito/mpeg/mv_sub
- REVERTED `ErrMessage` w1 @ 0x0023D848 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `copy2area` w3 @ 0x0023D8A0 <- aug6 ito/mpeg/mv_sub (1 syms rebound)

### src/GifPacket
- PORTED `gif_SpriteOrg` w1 @ 0x00111918 <- aug6 seki/src/GifPacket (1 syms rebound)

### src/StageAnimation
- PORTED `stage_ApplyData` w1 @ 0x001243E8 <- aug6 seki/src/StageAnimation (8 syms rebound)
- REVERTED `stage_CalcAnimationParent` w3 @ 0x00128710 — [codegen] insn 18: expected `lw	a1,2080(v0)` built `lw	a1,2064(v0)`
- REVERTED `stage_DispBgAnimation` w3 @ 0x00129970 — [codegen] insn 50: expected `addiu	a1,zero,909` built `addiu	a1,zero,882`

### src/a_p_1
- PORTED `fitToCol` w3 @ 0x001B8DC8 <- aug6 sugipon/src/a_p_1 (11 syms rebound)
- PORTED `zAxisRotFitting` w3 @ 0x001B8CE0 <- aug6 sugipon/src/a_p_1 (11 syms rebound)

### src/act-wish
- REVERTED `ACTGetWish_FromPad` w1 @ 0x0014B580 — [codegen] insn 13: expected `<end>` built `sll	zero,zero,0x0`

### src/box
- REVERTED `BoxExtGeoRestore` w3 @ 0x001C0708 — [codegen] src/box.c: In function `BoxExtGeoRestore':
- REVERTED `BoxGeoRestore` w3 @ 0x001C06A0 — [codegen] src/box.c: In function `BoxGeoRestore':
- REVERTED `ExecBoxMoveEndReaction` w3 @ 0x001C0690 — [codegen] src/box.c: In function `func_001C05B8':
- REVERTED `inertiaMove` w3 @ 0x001BEE60 — [codegen] src/box.c: In function `func_001C05B8':
- REVERTED `initLanding` w3 @ 0x001BEC30 — [codegen] src/box.c: In function `func_001C05B8':

### src/camera-set-manager
- REVERTED `InitCameraSetManager` w1 @ 0x0018CBE8 — [codegen] insn 5: expected `<end>` built `sll	zero,zero,0x0`

### src/debug_menu
- PORTED `debug_TargetGObj_Func` w1 @ 0x001A9D90 <- aug6 common/src/debug_menu (0 syms rebound)

### src/ebrain
- REVERTED `GetStageFromLabel` w3 @ 0x00190680 — [codegen] insn 2: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `eBrainGetTarget` w3 @ 0x00190620 — [codegen] insn 2: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `eBrainGetTargetGeneratorFromLabelStage` w3 @ 0x00190698 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `eBrainInit` w3 @ 0x00190638 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `eBrainProcess` w1 @ 0x00190478 — [codegen] insn 27: expected `<end>` built `sll	zero,zero,0x0`
- REVERTED `eBrainSendMes` w3 @ 0x00190658 — [codegen] insn 3: expected `lw	v1,2048(a1)` built `lw	v1,2032(a1)`
- REVERTED `eBrainStatusSet` w3 @ 0x00190648 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`

### src/enemy-control
- REVERTED `EnemyCtrlBeforeFunc` w1 @ 0x00191D20 — [codegen] insn 19: expected `<end>` built `sll	zero,zero,0x0`

### src/enemyParts
- REVERTED `DispEnemyEye` w3 @ 0x001CEC60 — [codegen] insn 3: expected `lw	a0,2048(v0)` built `lw	a0,2032(v0)`
- REVERTED `DispEnemyFootPrints` w3 @ 0x001CEBC0 — [codegen] insn 3: expected `lw	a2,2048(v0)` built `lw	a2,2032(v0)`
- REVERTED `EntryEnemyFootPrint` w3 @ 0x001CEBB0 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `InitEnemyEye` w3 @ 0x001CEB08 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `InitPointBlur` w3 @ 0x001CEBF0 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `UpdateEnemyEye` w3 @ 0x001CEC30 — [codegen] insn 3: expected `lw	a0,2048(v1)` built `lw	a0,2032(v1)`
- PORTED `moveDataElements` w1 @ 0x001CED28 <- aug6 sugipon/src/enemyParts (3 syms rebound)

### src/flyManager
- PORTED `InitFlyInfo` w1 @ 0x001D03E8 <- aug6 sugipon/src/flyManager (5 syms rebound)

### src/gather_effect
- REVERTED `GatherEffect_InqEnd` w3 @ 0x00197818 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `GatherEffect_Set` w1 @ 0x001977A8 <- aug6 ito/src/gather_effect (1 syms rebound)

### src/generator
- REVERTED `Generator_Call` w3 @ 0x00193818 — [codegen] insn 1: expected `lw	a0,2048(v0)` built `lw	a0,2032(v0)`
- REVERTED `Generator_Mask` w3 @ 0x00193848 — [codegen] insn 2: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `Generator_MaskOff` w3 @ 0x00193860 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `Generator_QuickCall` w3 @ 0x00192B58 — [codegen] insn 6: expected `lw	v0,2048(v1)` built `lw	v0,2032(v1)`
- REVERTED `Generator_ResetCount` w3 @ 0x00193830 — [codegen] insn 2: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `MakeGeneratorPacket` w3 @ 0x00192E08 — [codegen] insn 5: expected `addiu	a0,zero,3454` built `addiu	a0,zero,3416`
- REVERTED `SetMotherGenerator` w3 @ 0x00193870 — [codegen] insn 1: expected `addiu	v0,zero,3453` built `addiu	v0,zero,3415`

### src/girl
- REVERTED `InitGirlGeo` w3 @ 0x001D14B8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- PORTED `SetGirlClothDispSwitch` w1 @ 0x001D1A98 <- aug6 sugipon/src/girl (4 syms rebound)

### src/item
- REVERTED `ReleaseItem` w3 @ 0x001D2738 — [codegen] insn 8: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `avoidInsideOfWall` w3 @ 0x001D26C8 — [codegen] insn 6: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `bombExplodeSE` w3 @ 0x001D2550 — [codegen] insn 24: expected `lw	s2,2048(v0)` built `lw	s2,2032(v0)`
- REVERTED `execBombGeo` w3 @ 0x001D3A30 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/itou_gflag
- PORTED `itouGFlagInit` w1 @ 0x001983F8 <- aug6 ito/src/itou_gflag (1 syms rebound)

### src/motionViewer
- REVERTED `setMotionSpeed` w3 @ 0x001E4938 — [codegen] insn 8: expected `sw	zero,1576(v0)` built `sw	zero,1560(v0)`
- REVERTED `setRootUpdateMode` w3 @ 0x001E4868 — [codegen] insn 5: expected `lw	a0,1572(v0)` built `lw	a0,1556(v0)`

### src/op
- REVERTED `actOpDemo01` w3 @ 0x0020CE78 — [codegen] insn 16: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`
- REVERTED `actOpDemo01_2` w3 @ 0x0020D008 — [codegen] insn 26: expected `addiu	a0,zero,310` built `addiu	a0,zero,309`
- REVERTED `actOpDemo01_2Chk` w3 @ 0x0020D090 — [codegen] insn 6: expected `addiu	a0,zero,759` built `addiu	a0,zero,758`
- REVERTED `actOpDemo02` w3 @ 0x0020D108 — [codegen] insn 26: expected `addiu	a0,zero,311` built `addiu	a0,zero,310`
- REVERTED `actOpDemo03Chk` w3 @ 0x0020D208 — [codegen] insn 4: expected `addiu	a0,zero,312` built `addiu	a0,zero,311`
- PORTED `actSt00aEneChk` w1 @ 0x0020D718 <- aug6 script/src/st00a (3 syms rebound)
- REVERTED `actSt13aConte01_3` w3 @ 0x0020D238 — [codegen] insn 5: expected `addiu	a0,zero,761` built `addiu	a0,zero,760`
- REVERTED `actSt24aConte01_2` w3 @ 0x0020D190 — [codegen] insn 6: expected `addiu	a0,zero,760` built `addiu	a0,zero,759`
- REVERTED `actSt26aConte01_1_newgame` w3 @ 0x0020D370 — [codegen] insn 29: expected `addiu	a0,zero,317` built `addiu	a0,zero,316`
- REVERTED `actSubMpegReturnPreload` w3 @ 0x0020D2F0 — [codegen] insn 24: expected `addiu	a0,zero,314` built `addiu	a0,zero,313`
- REVERTED `actTitleCamera2` w3 @ 0x0020CE00 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actTitleReadTimeDemo0` w3 @ 0x0020CF80 — [codegen] insn 26: expected `addiu	a0,zero,309` built `addiu	a0,zero,308`
- REVERTED `actTitleShortCut` w3 @ 0x0020CEE0 — [codegen] insn 32: expected `addiu	a0,zero,308` built `addiu	a0,zero,307`

### src/queen_barrier_disp
- PORTED `makeRefractST` w1 @ 0x0019C798 <- aug6 ito/src/queen_barrier_disp (3 syms rebound)

### src/ropeFix
- REVERTED `RopeFixDL` w3 @ 0x001E9810 — [codegen] src/ropeFix.c: In function `InitRopeFixGeo':

### src/rotObject
- PORTED `moveStartSE` w1 @ 0x001E9980 <- aug6 sugipon/src/rotObject (8 syms rebound)

### src/seMail
- REVERTED `seMail` w1 @ 0x00204D70 — [callee-sig-conflict] src/seMail.c:8: conflicting types for `GetRootMatrixByDObj'

### src/st04b
- REVERTED `actSt04bEnd` w3 @ 0x00214040 — [codegen] insn 22: expected `addiu	a0,zero,3453` built `addiu	a0,zero,3415`
- REVERTED `actSt04bGirlWay` w1 @ 0x002165B0 — [codegen] insn 11: expected `lui	s0,0x22` built `lui	s0,0x0`

### src/st04c
- REVERTED `actSt04cDoorDownChk` w3 @ 0x00217B48 — [codegen] insn 9: expected `addiu	a0,zero,258` built `addiu	a0,zero,257`
- REVERTED `actSt04cEnd` w3 @ 0x00217AA0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04cEnemy1` w3 @ 0x00217FF8 — [codegen] insn 14: expected `addiu	a0,a0,1312` built `addiu	a0,a0,1296`
- PORTED `actSt04cEnemy2` w1 @ 0x002180C8 <- aug6 script/src/st04c (11 syms rebound)
- REVERTED `actSt04cIntro` w3 @ 0x00217D40 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,2456`
- REVERTED `actSt04cIntroChk` w3 @ 0x00218868 — [codegen] insn 23: expected `addiu	a0,zero,3453` built `addiu	a0,zero,3415`
- REVERTED `actSt04cSolarXL` w3 @ 0x00217C10 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04lDoor` w3 @ 0x00217CD8 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1576`
- REVERTED `actSt04lDoorEvent` w3 @ 0x00218950 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/st04d
- REVERTED `actSt04dDoor1` w3 @ 0x00218CF8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04dDoor1DownEffect` w3 @ 0x00219150 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04dDoor1UpChk` w3 @ 0x00218D60 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04dDoor1UpEffect` w3 @ 0x00219100 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04dDoor2DownChk` w3 @ 0x00218E90 — [codegen] insn 21: expected `addiu	a0,s2,0` built `addiu	a0,s2,2016`
- REVERTED `actSt04dDoor2DownEffect` w3 @ 0x002192E0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04dDoor2Event` w3 @ 0x002191F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04dDoor2UpEffect` w3 @ 0x00219270 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/stageMultiBgaManager
- REVERTED `InitStageMultiBgaManager` w1 @ 0x001EBCD0 — [codegen] insn 51: expected `<end>` built `sll	zero,zero,0x0`

### src/weapon
- REVERTED `CheckSwapableWeapon` w3 @ 0x001F42E8 — [codegen] insn 3: expected `lw	a0,2048(v0)` built `lw	a0,2032(v0)`
- REVERTED `CheckWeaponKind` w3 @ 0x001F43D0 — [codegen] insn 11: expected `addiu	a3,zero,754` built `addiu	a3,zero,755`
- REVERTED `ExecWeaponHitReaction` w3 @ 0x001F4098 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `LightTorchOnOfWeapon` w3 @ 0x001F44C8 — [codegen] insn 1: expected `lw	a0,2048(v1)` built `lw	a0,2032(v1)`
- REVERTED `PickupWeapon` w3 @ 0x001F42D0 — [codegen] insn 2: expected `lw	v1,2048(a1)` built `lw	v1,2032(a1)`
- REVERTED `ReleaseWeapon` w3 @ 0x001F4318 — [codegen] insn 14: expected `lw	s1,2048(v0)` built `lw	s1,2032(v0)`
- REVERTED `WeaponDL` w3 @ 0x001F4250 — [codegen] insn 8: expected `lw	a0,2048(s0)` built `lw	a0,2032(s0)`
- REVERTED `WeaponGeo` w3 @ 0x001F41C8 — [codegen] insn 5: expected `lw	s1,2048(v1)` built `lw	s1,2032(v1)`
- REVERTED `WeaponHitEffect` w3 @ 0x001F3FB0 — [codegen] insn 21: expected `lw	v1,2048(a0)` built `lw	v1,2032(a0)`
- PORTED `calcDynamicPathGeometry` w1 @ 0x001F3A00 <- aug6 sugipon/src/weapon (2 syms rebound)
- REVERTED `checkHit` w3 @ 0x001F40C8 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `torchOffOfWeaponSE` w3 @ 0x001F3308 — [codegen] insn 9: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `weaponHitReactionSE` w3 @ 0x001F3368 — [codegen] insn 2: expected `lw	a2,2048(v0)` built `lw	a2,2032(v0)`

### src/windManager
- PORTED `ExecWindManager` w3 @ 0x001F4E68 <- aug6 sugipon/src/windManager (3 syms rebound)
- REVERTED `GetRegularizedWindSpeed` w3 @ 0x001F5068 — [undeclared] src/windManager.c:7: `D_0063375C' undeclared (first use in this function)
- PORTED `InitWindManager` w1 @ 0x001F4FE8 <- aug6 sugipon/src/windManager (8 syms rebound)
- PORTED `ReinitWindManager` w3 @ 0x001F4EE8 <- aug6 sugipon/src/windManager (3 syms rebound)
- PORTED `SetWindManager` w3 @ 0x001F4F68 <- aug6 sugipon/src/windManager (3 syms rebound)

### src/worm
- PORTED `GetWormCaptureVector` w3 @ 0x001F69B0 <- aug6 sugipon/src/worm (1 syms rebound)
- PORTED `GetWormRoute` w1 @ 0x001F66A0 <- aug6 sugipon/src/worm (3 syms rebound)
- REVERTED `WormDL` w3 @ 0x001F6A90 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`

### src/st04r
- REVERTED `actSt04rBrg1Chk` w3 @ 0x0021DDE0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rBrg2Chk` w3 @ 0x0021DFC0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rC1BallTurn` w3 @ 0x0021D600 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rC2BallTurn` w3 @ 0x0021D698 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rC3BallTurn` w3 @ 0x0021D750 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rCrest02` w3 @ 0x0021D808 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rCrest2Main` w3 @ 0x0021D960 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rCrest3Main` w3 @ 0x0021D9D8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rCrestMain` w3 @ 0x0021D8C0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rRope1Chk` w3 @ 0x0021DC90 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rRope2Chk` w3 @ 0x0021DD38 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rRope3Chk` w3 @ 0x0021DE78 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rRope4Chk` w3 @ 0x0021DF18 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rSekizoChk` w3 @ 0x0021DBE8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rSolarBeam` w3 @ 0x0021DA50 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rSolarBeamChk` w3 @ 0x0021DAC8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04rStairChk` w3 @ 0x0021DB40 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05cInit` w3 @ 0x0021D340 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05dInit` w3 @ 0x0021D420 — [codegen] insn 37: expected `addiu	a0,zero,220` built `addiu	a0,zero,219`
- REVERTED `actSt05eEnd` w3 @ 0x0021D188 — [codegen] insn 63: expected `addiu	a0,zero,219` built `addiu	a0,zero,218`
- REVERTED `actSt05eInit` w3 @ 0x0021D560 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/st07a
- REVERTED `actSt07ChanEvent` w3 @ 0x002238D8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aChan` w3 @ 0x00223310 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aChanChk` w3 @ 0x00222FF0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aChanEffect` w3 @ 0x00223050 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aEnd` w3 @ 0x00222F28 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aEne` w3 @ 0x00223200 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aEne2` w3 @ 0x002236C8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aEneChk` w3 @ 0x00223288 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aGene1` w3 @ 0x00223550 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aGene2` w3 @ 0x002235E8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aGene2_1` w3 @ 0x00223710 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aGene2_2` w3 @ 0x002237A8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aGene2_3` w3 @ 0x00223840 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aGene3` w3 @ 0x00223680 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aInit` w3 @ 0x00222E90 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aIntro` w3 @ 0x00223440 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aSekizo` w3 @ 0x002234C8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aSekizoChk` w3 @ 0x00223188 — [codegen] insn 12: expected `addiu	a0,zero,286` built `addiu	a0,zero,285`
- REVERTED `actSt07aTsuro` w3 @ 0x002233A8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aTsuroChk` w3 @ 0x002230B0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt07aTsuroEffect` w3 @ 0x00223110 — [codegen] insn 12: expected `addiu	a0,zero,285` built `addiu	a0,zero,284`

### src/st06a
- REVERTED `actSt06aBox` w3 @ 0x002228D8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aBox2` w3 @ 0x00222978 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aBox3` w3 @ 0x002229F0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aBoxChk` w3 @ 0x00222570 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aBoxEvent2` w3 @ 0x00222A68 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aDoorDownChk` w3 @ 0x00222188 — [codegen] insn 29: expected `addiu	a0,zero,201` built `addiu	a0,zero,200`
- REVERTED `actSt06aExit` w3 @ 0x00222820 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aHead` w3 @ 0x00222D50 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aHeadChk` w3 @ 0x002226B0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aShutter` w3 @ 0x00222768 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aShutterOpen` w3 @ 0x002224F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aStatue` w3 @ 0x00222CA8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aStatueChk` w3 @ 0x00222610 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aTree` w3 @ 0x00222DF8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aWallWay` w3 @ 0x00222B58 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aWallWay2` w3 @ 0x00222C00 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt06aWay` w3 @ 0x00222AE0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/end
- REVERTED `actConte14_1` w3 @ 0x0020B138 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actConte14_13` w3 @ 0x0020C3A0 — [codegen] insn 13: expected `addiu	a0,zero,786` built `addiu	a0,zero,785`
- REVERTED `actConte14_2` w3 @ 0x0020B3F8 — [codegen] insn 25: expected `addiu	a2,zero,483` built `addiu	a2,zero,482`
- REVERTED `actConte14_6` w3 @ 0x0020B7D8 — [codegen] insn 12: expected `addiu	a0,zero,780` built `addiu	a0,zero,779`
- REVERTED `actConte14_7` w3 @ 0x0020BBF0 — [codegen] insn 5: expected `addiu	a0,zero,577` built `addiu	a0,zero,576`
- REVERTED `actEndDemo01` w3 @ 0x0020B028 — [codegen] insn 7: expected `addiu	a0,zero,764` built `addiu	a0,zero,763`
- REVERTED `actEndDemo03` w3 @ 0x0020CB40 — [codegen] insn 29: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`
- REVERTED `actEndDemo04` w3 @ 0x0020CBE0 — [codegen] insn 44: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`
- REVERTED `actEndDemo06` w3 @ 0x0020B4D8 — [codegen] insn 7: expected `addiu	a0,zero,769` built `addiu	a0,zero,768`
- REVERTED `actEndDemo07` w3 @ 0x0020B8D8 — [codegen] insn 9: expected `addiu	a0,zero,523` built `addiu	a0,zero,522`
- REVERTED `actEndDemo14` w3 @ 0x0020C910 — [codegen] insn 31: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`
- REVERTED `actSt27aEndChk` w3 @ 0x0020CA30 — [codegen] insn 23: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`
- REVERTED `actSt27aEndDemo` w3 @ 0x0020CAB8 — [codegen] insn 24: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`
- REVERTED `actStaff2Demo` w3 @ 0x0020C748 — [codegen] insn 6: expected `addiu	a0,zero,792` built `addiu	a0,zero,791`
- REVERTED `actStaff3Demo` w3 @ 0x0020C868 — [codegen] insn 31: expected `sw	v0,196(s0)` built `sw	v0,180(s0)`

### src/st08b
- REVERTED `actSt08aGirlYoro` w3 @ 0x00224270 — [codegen] insn 9: expected `addiu	a0,zero,1308` built `addiu	a0,zero,1304`
- REVERTED `actSt08bDoor` w3 @ 0x00223F70 — [codegen] insn 28: expected `addiu	a0,zero,311` built `addiu	a0,zero,310`
- REVERTED `actSt08bDoorDownChk` w3 @ 0x002240C0 — [codegen] insn 9: expected `addiu	a0,zero,1304` built `addiu	a0,zero,1300`
- REVERTED `actSt08bDoorEvent` w3 @ 0x002242B8 — [codegen] insn 9: expected `addiu	a0,zero,1309` built `addiu	a0,zero,1305`
- REVERTED `actSt08bDoorUpChk` w3 @ 0x00224038 — [codegen] insn 21: expected `addiu	a1,zero,397` built `addiu	a1,zero,393`
- REVERTED `actSt08bDoorUpEffect` w3 @ 0x00224300 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt08bEne` w3 @ 0x00224150 — [codegen] insn 9: expected `addiu	a0,zero,1382` built `addiu	a0,zero,1376`
- REVERTED `actSt08bEneChk` w3 @ 0x00224708 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt08bEnemy1` w3 @ 0x00224198 — [codegen] insn 9: expected `addiu	a0,zero,1383` built `addiu	a0,zero,1377`
- REVERTED `actSt08bEnemy2` w3 @ 0x002241E0 — [codegen] insn 9: expected `addiu	a0,zero,1384` built `addiu	a0,zero,1378`
- REVERTED `actSt08bKuren` w3 @ 0x00224108 — [codegen] insn 9: expected `addiu	a0,zero,1305` built `addiu	a0,zero,1301`
- REVERTED `actSt08bKurenMain` w3 @ 0x00224228 — [codegen] insn 9: expected `addiu	a0,zero,1385` built `addiu	a0,zero,1379`

### src/st04a
- REVERTED `actConte09Jimaku` w3 @ 0x002135B0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actConte09_3` w3 @ 0x00213AD0 — [codegen] insn 10: expected `addiu	a0,zero,273` built `addiu	a0,zero,272`
- REVERTED `actSt04aConte06Jimaku` w3 @ 0x002130A8 — [codegen] insn 9: expected `addiu	a0,zero,1639` built `addiu	a0,zero,1625`
- REVERTED `actSt04aGateL` w3 @ 0x00213DD8 — [codegen] insn 13: expected `addiu	a0,zero,818` built `addiu	a0,zero,817`
- REVERTED `actSt04aGateOpen` w3 @ 0x002130F8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04aGateOpen3Chk` w3 @ 0x00213A20 — [codegen] insn 10: expected `addiu	a0,zero,272` built `addiu	a0,zero,271`
- REVERTED `actSt04aGateRChk` w3 @ 0x00213BE8 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,4160`
- REVERTED `actSt04aTorch1Chk` w3 @ 0x00213CB8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04aTorchAllFlagfChk` w3 @ 0x00213D60 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04aTorchXL` w3 @ 0x00213E90 — [codegen] insn 37: expected `addiu	v1,s1,0` built `addiu	v1,s1,4368`

### src/act_a_p_1
- REVERTED `AP1BeforeFunc` w3 @ 0x001BA6B0 — [codegen] insn 3: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `GetAP1AIMode` w3 @ 0x001BA838 — [codegen] insn 5: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `SetAP1HostGObj` w3 @ 0x001BA7C0 — [codegen] insn 2: expected `lw	v0,2048(a1)` built `lw	v0,2032(a1)`
- REVERTED `SetAP1PriorLevel` w3 @ 0x001BA7E8 — [codegen] insn 6: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `SleepAP1` w3 @ 0x001BA530 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `WakeUpAP1` w3 @ 0x001BA5C0 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `actAP1Start` w3 @ 0x001BA6F0 — [codegen] insn 6: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `hitProc` w3 @ 0x001BA5E0 — [codegen] insn 7: expected `lw	v0,2048(v1)` built `lw	v0,2032(v1)`
- REVERTED `subAP1BrainMain` w3 @ 0x001BA5D0 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `walkAI` w3 @ 0x001BA2E0 — [codegen] insn 7: expected `lw	s1,2048(v0)` built `lw	s1,2032(v0)`

### src/st04l
- REVERTED `actSt04cInit` w3 @ 0x0021AD40 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04eInit` w3 @ 0x0021B010 — [codegen] insn 13: expected `addiu	a0,zero,1030` built `addiu	a0,zero,1027`
- REVERTED `actSt04lC1BallTurn` w3 @ 0x0021B2E8 — [codegen] insn 9: expected `addiu	a0,zero,1110` built `addiu	a0,zero,1107`
- REVERTED `actSt04lC3BallTurn` w3 @ 0x0021B750 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04lCrest02` w3 @ 0x0021B890 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04lCrest2Main` w3 @ 0x0021BB00 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04lCrest3Main` w3 @ 0x0021BC40 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt04lCrestMain` w3 @ 0x0021B9D0 — [codegen] insn 33: expected `addiu	a0,zero,196` built `addiu	a0,zero,195`
- REVERTED `actSt04lMonyou02Chk` w3 @ 0x0021CE30 — [codegen] insn 38: expected `addiu	a1,zero,59` built `addiu	a1,zero,58`
- REVERTED `actSt04lStairChk` w3 @ 0x0021BD80 — [codegen] insn 33: expected `addiu	a0,zero,197` built `addiu	a0,zero,196`

### src/st05d
- REVERTED `actSt05dDoor2` w3 @ 0x0021F3B8 — [codegen] insn 25: expected `addiu	a0,zero,202` built `addiu	a0,zero,201`
- REVERTED `actSt05dDoor2UpChk` w3 @ 0x0021F470 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)

### src/st05b
- REVERTED `actSt05bBallXL` w3 @ 0x0021E320 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bCrest01XL` w3 @ 0x0021E038 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bDoorXL` w3 @ 0x0021E128 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bGirlWay` w3 @ 0x0021E4E8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bMonyoDoorXL` w3 @ 0x0021E1F0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bSekizo` w3 @ 0x0021E288 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bSekizoChk` w3 @ 0x0021E0B0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bSekizoEvent` w3 @ 0x0021E450 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05bSolarXL` w3 @ 0x0021E3B8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/st05e
- REVERTED `actSt05eSolar` w3 @ 0x0021FDB8 — [codegen] insn 26: expected `addiu	a0,zero,284` built `addiu	a0,zero,283`
- REVERTED `actSt05eSolarChk` w3 @ 0x0021FA30 — [codegen] insn 5: expected `addiu	a0,zero,295` built `addiu	a0,zero,294`
- REVERTED `actSt05eWater` w3 @ 0x0021FD20 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05eWaterFlagOn` w3 @ 0x002201C8 — [codegen] insn 9: expected `addiu	a0,zero,1304` built `addiu	a0,zero,1300`
- REVERTED `actSt05eWaterMain` w3 @ 0x0021FEE0 — [codegen] insn 26: expected `addiu	a0,zero,285` built `addiu	a0,zero,284`
- REVERTED `actSt05eWaterStop` w3 @ 0x002200E0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt05eWaterSwitch` w3 @ 0x00220008 — [codegen] insn 20: expected `addiu	a0,zero,286` built `addiu	a0,zero,285`

### src/torch
- REVERTED `InitTorchGeo` w3 @ 0x001F2158 — [codegen] insn 19: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `IsTorchLightOn` w3 @ 0x001F2240 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `TorchDL` w3 @ 0x001F2230 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `TorchGeo` w3 @ 0x001F2148 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `torchOffSE` w3 @ 0x001F1AD8 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/act-parallel-control
- REVERTED `ActPara_DebugOut` w3 @ 0x0014B260 — [codegen] insn 1: expected `sd	zero,96(v0)` built `sw	zero,88(v0)`

### src/candle
- REVERTED `CandleGeo` w3 @ 0x001C2FF0 — [codegen] [§frame-size] prologue sp delta differs (missing callee-saved reg / hoist)
- PORTED `DeleteLayoutedCandleParticleEffect` w3 @ 0x001C3130 <- aug6 sugipon/src/candle (2 syms rebound)
- REVERTED `InitCandleGeo` w3 @ 0x001C2FA0 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `_deleteLayoutedCandleParticleEffect` w3 @ 0x001C3178 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)

### src/lineManager
- REVERTED `Draw2DLine` w3 @ 0x001D3D40 — [codegen] insn 4: expected `lw	a0,2048(v0)` built `lw	a0,2032(v0)`
- REVERTED `Draw2DLineG` w3 @ 0x001D3D98 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `Draw2DLineSeg_Loop` w3 @ 0x001D3D80 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `Draw2DLineSeg_Start` w3 @ 0x001D3D70 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`

### src/cage
- REVERTED `CageDL` w3 @ 0x001C2760 — [codegen] insn 10: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `HotInitCageGeo` w3 @ 0x001C22F0 — [codegen] insn 6: expected `lw	s0,2048(v1)` built `lw	s0,2032(v1)`
- REVERTED `InitCageGeo` w3 @ 0x001C21B8 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)

### src/rope
- REVERTED `HoldRope` w3 @ 0x001E93D0 — [codegen] insn 1: expected `lw	v0,2048(a2)` built `lw	v0,2032(a2)`
- REVERTED `ReleaseRope` w3 @ 0x001E97F8 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`
- REVERTED `RopeDL` w3 @ 0x001E9588 — [codegen] insn 8: expected `lw	s2,2048(v0)` built `lw	s2,2032(v0)`

### src/st22a
- REVERTED `actSt22aIntroSub` w3 @ 0x002341F8 — [codegen] insn 11: expected `lui	s1,0x62` built `lui	s1,0x0`
- REVERTED `actSt22aLightningVolime` w3 @ 0x00234170 — [codegen] insn 15: expected `addiu	v1,v1,0` built `addiu	v1,v1,1640`

### src/FileManager
- PORTED `file_LoadFile` w3 @ 0x0010ECA8 <- aug6 seki/src/FileManager (1 syms rebound)

### src/cageFix
- REVERTED `CageFixDL` w3 @ 0x001C2E28 — [codegen] insn 8: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `CageFixGeo` w3 @ 0x001C2DF8 — [codegen] insn 5: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`
- REVERTED `InitCageFixGeo` w3 @ 0x001C2EB8 — [codegen] insn 1: expected `lw	v1,2048(v0)` built `lw	v1,2032(v0)`

### src/deja
- REVERTED `actDeja` w3 @ 0x002083B0 — [codegen] insn 12: expected `lui	s1,0x21` built `lui	s1,0x0`
- REVERTED `actDejaAfterChk` w3 @ 0x00208228 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actDejaChk` w3 @ 0x00207DF0 — [codegen] insn 14: expected `addiu	a0,a0,0` built `addiu	a0,a0,248`

### src/girlForceField
- REVERTED `GirlForceFieldDL` w3 @ 0x001D1B30 — [codegen] src/girlForceField.c:24: storage size of `target_vec' isn't known
- REVERTED `InitGirlForceFieldGeo` w3 @ 0x001D1AD8 — [codegen] insn 3: expected `lw	v1,2048(v1)` built `lw	v1,2032(v1)`

### src/st04e
- REVERTED `actSt04eWater` w3 @ 0x00219840 — [codegen] insn 27: expected `addiu	a0,s2,0` built `addiu	a0,s2,1656`
- REVERTED `actSt04eWaterFlagOn` w3 @ 0x00219D50 — [codegen] [§regalloc-swap] register-allocation swap (same op, one reg differs, recurring)
- REVERTED `actSt04eWaterSwitch` w3 @ 0x00219AF0 — [codegen] [§fp-licm] loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)

### src/st18a
- REVERTED `actSt18aEne` w3 @ 0x00230928 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt18aEne2Chk` w3 @ 0x00231098 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work
- REVERTED `actSt18aEnemy1_2` w3 @ 0x00230A40 — [codegen] [§delay-slot-occupant] epilogue ld ra folded into an early-exit branch delay vs fall-through work

### src/boy
- REVERTED `dispClothes` w3 @ 0x001C11C0 — [codegen] insn 7: expected `lw	s0,2048(a2)` built `lw	s0,2032(a2)`
- REVERTED `execClothes` w3 @ 0x001C1250 — [codegen] insn 6: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`

### src/actressLight
- REVERTED `SetActressLight` w3 @ 0x001BA880 — [codegen] insn 11: expected `lw	s0,2048(v0)` built `lw	s0,2032(v0)`

### src/keyInput
- REVERTED `InitKeyInput` w3 @ 0x00104590 — [codegen] insn 22: expected `lwc1	$f1,192(s2)` built `lwc1	$f1,176(s2)`
