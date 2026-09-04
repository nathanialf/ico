# Rename ledger — aug6 (Aug-6-2001 prototype) symbols renamed from their PAL twins

Generated 2026-09-04 by a mechanical pass over
`/primary/dev/ico/.port_cache/aug6/aug6_pal_twins.json` (built by the same
`scan` correlation as the ntsc pass — see `tools/port_from_ntsc.py` in the PAL
checkout).  A *twin* pairs one aug6-prototype function with one PAL-retail
function; `via=anchor` means the two reloc-normalized instruction streams hash
equal AND that hash occurs exactly once in each build, so the pairing is
content-proven, not positional.  PAL names come from the PAL disc's own shipped
build metadata (SRCFILE.TXT / MAIN.MAP); the aug6 names they replace were
ordinal guesses correlated against a January-2002 MAIN.MAP, i.e. a different
link, and had drifted.

Rename rule applied:

* `via == anchor` -> rename (tag `// pal-twin`).  Anchor already implies the
  PAL stream hash is globally unique on the PAL side, so an anchor twin can
  never be in a PAL same-hash (interchangeable-wrapper) class.
* `via in {gap, ordinal}` -> rename only if `norm_equal` AND the PAL name is
  twin-tier (a real name, no `provisional-ordinal`) AND the PAL stream is not
  in a same-hash class.  **No pair survived that filter** (see the skip census),
  so no line carries a `// pal-twin-ordinal` tag.
* A proposal whose target name is still held by another aug6 address after the
  whole map is applied is dropped, iterated to a FIXED POINT (a rename chain
  A->B->C resolves fully; a chain that terminates on an address with no
  proposal of its own drops backwards along its whole length).  Two independent
  implementations (iterative re-scan and chain/cycle reachability) agree on the
  same 714 drops.
* The five VU1 `*MicroProgram` symbols are untouched.  aug6 has no
  `BEGIN GENERATED` banner and no hand-seed block, so nothing else is pinned.
  (`p2o_TransMicroProgram` at 0x0010ECB8 is an ordinary `.text` function in
  seki/src/DisplayP2O.c, not a VU program label, and IS renamed.)

Applied: **1428** renames (414 replace a real-but-wrong name, 1014 replace a
`func_<VMA>` placeholder).  The byte-identical link is unchanged by
construction (`verify_elf: OK (build/ico.rom sha1=2b4d7de41966ff38d061b4c985de45fc212e2fb2)`).

Spot check that the shift is real, not an artefact of the correlation:
aug6 `apply_m34` at 0x001970E8 -> PAL `cmpr` — the aug6 body is
`int f(int *a, int *b) { return a[4] - b[4]; }` in `ito/src/lightning.c`, a
qsort comparator, not a matrix apply.  Likewise aug6 `inflate` (0x001332E8)
zeroes seven 0x12C-stride entries and a flag — PAL calls it
`iosCdvdBackGroundMgrInit` — while PAL's `inflate` is the 0x4C4-byte routine
aug6 had left as `func_001351E0`.


## Real names replaced (old -> new)

| old (aug6, wrong) | new (PAL twin) | via | PAL VMA | PAL TU |
| --- | --- | --- | --- | --- |
| `ExecKeyInput` | `LimitExistGeometry` | anchor | 0x00104680 | `src/geometryManager` |
| `MatrixDrive_RotMatrixX` | `MatrixDrive_TurnXObjectMatrixYZ` | anchor | 0x001055B8 | `src/matrixDrive` |
| `MatrixDrive_RotMatrixY` | `MatrixDrive_TurnYObjectMatrixXZ` | anchor | 0x001056A0 | `src/matrixDrive` |
| `MatrixDrive_RotMatrixZ` | `MatrixDrive_TurnZObjectMatrixXY` | anchor | 0x00105788 | `src/matrixDrive` |
| `MatrixDrive_ScaleMatrix` | `MatrixDrive_GetTurnXAngleZY` | anchor | 0x00105870 | `src/matrixDrive` |
| `MatrixDrive_TurnViewMatrix` | `MatrixDrive_GetTurnXAngleYZ` | anchor | 0x00105950 | `src/matrixDrive` |
| `MatrixDrive_PushMatrixWithNoCopy` | `MatrixDrive_GetTurnYAngleXZ` | anchor | 0x00105A30 | `src/matrixDrive` |
| `MatrixDrive_PopMatrix` | `MatrixDrive_GetTurnYEAngleXZ` | anchor | 0x00105B10 | `src/matrixDrive` |
| `MatrixDrive_GetMatrix` | `MatrixDrive_GetTurnZAngleXY` | anchor | 0x00105C00 | `src/matrixDrive` |
| `MatrixDrive_GetLastMatrix` | `MatrixDrive_GetTurnZAngleYX` | anchor | 0x00105CE0 | `src/matrixDrive` |
| `MatrixDrive_TurnXObjectMatrixYZ` | `CopyMatrix` | anchor | 0x00105F68 | `src/matrixDrive` |
| `MatrixDrive_TurnYObjectMatrixXZ` | `CopyMatrixUncached` | anchor | 0x00105F90 | `src/matrixDrive` |
| `MatrixDrive_TurnZObjectMatrixXY` | `AddVectorXYZ` | anchor | 0x00105FC0 | `src/matrixDrive` |
| `MatrixDrive_GetTurnXAngleZY` | `SubVectorXYZ` | anchor | 0x00105FD8 | `src/matrixDrive` |
| `MatrixDrive_GetTurnXAngleYZ` | `UnitRotation` | anchor | 0x00105FF0 | `src/matrixDrive` |
| `MatrixDrive_GetTurnYAngleXZ` | `FSqrt` | anchor | 0x00106028 | `src/matrixDrive` |
| `MatrixDrive_GetTurnYEAngleXZ` | `VectorLength` | anchor | 0x00106048 | `src/matrixDrive` |
| `MatrixDrive_GetTurnZAngleXY` | `VectorLengthSquare` | anchor | 0x00106070 | `src/matrixDrive` |
| `MatrixDrive_GetTurnZAngleYX` | `GetPointDistance` | anchor | 0x00106090 | `src/matrixDrive` |
| `GetRootProjectionPosOfGObj` | `CopyMotion` | anchor | 0x0010A550 | `src/motionManager2` |
| `SetMotionPlaySpeedRatio` | `GetMotionRootPos` | anchor | 0x0010A590 | `src/motionManager2` |
| `SetSkeltonDispSwitch` | `GetBlendedMotion` | anchor | 0x0010A790 | `src/motionManager2` |
| `CopyMotion` | `GetFloatingMotionRootPos` | anchor | 0x0010A978 | `src/motionManager2` |
| `GetMotionRootPos` | `GetShapeMotion` | anchor | 0x0010AA98 | `src/motionManager2` |
| `setNodePursueParticleEffectWithUpperLimit` | `AdjustRootPositionToVerticalSidePlaneOfWall` | anchor | 0x0010ABD0 | `src/motionManager2` |
| `SetFallDownSplash` | `fitYToPlane` | anchor | 0x0010AC80 | `src/motionManager2` |
| `GetPoolGlobalDrainVector` | `GetBlendedMotionRootPos` | anchor | 0x0010ACC0 | `src/motionManager2` |
| `InitPoolGeo` | `_getMotRotElem` | anchor | 0x0010AD18 | `src/motionManager2` |
| `InitLimitedPoolReflactionMesh` | `setNodePursueParticleEffectWithUpperLimit` | anchor | 0x0010B038 | `src/pool` |
| `GetTableCos` | `PushQuaternionWithNoCopy` | anchor | 0x0010DA98 | `src/quaternion` |
| `InitTableSin` | `PopQuaternion` | anchor | 0x0010DAF0 | `src/quaternion` |
| `GetTableArcSin` | `SetQuaternionByAxisRotate` | anchor | 0x0010DB28 | `src/quaternion` |
| `GetTableArcCos` | `SetQuaternionByAxisRotateWithNoRegularize` | anchor | 0x0010DB98 | `src/quaternion` |
| `GetTableArcTan2` | `SetQuaternionByAxisRotateEAngle` | anchor | 0x0010DC00 | `src/quaternion` |
| `p2o_MakePacket` | `RotQuaternionEAZ` | anchor | 0x0010E360 | `src/quaternion` |
| `p2o_DispShadowVolume` | `GetXUnitVectorOfQuaternion` | anchor | 0x0010E460 | `src/quaternion` |
| `p2o_HideDispVU1` | `GetYUnitVectorOfQuaternion` | anchor | 0x0010E4F0 | `src/quaternion` |
| `p2o_DispVU1DObj` | `GetZUnitVectorOfQuaternion` | anchor | 0x0010E580 | `src/quaternion` |
| `p2o_DispVU1DObjMulti` | `GetDifferencialQuaternionWithNoRegularize` | anchor | 0x0010E610 | `src/quaternion` |
| `p2o_DispVU1Multi` | `GetQuaternionMagnitude` | anchor | 0x0010E6D0 | `src/quaternion` |
| `p2o_DispVU1MultiDefault` | `SetQuaternionByCosineAxisRotateVWithNoRegularize` | anchor | 0x0010E710 | `src/quaternion` |
| `p2o_DispVU1` | `SetQuaternionByCosineAxisRotateV` | anchor | 0x0010E7A0 | `src/quaternion` |
| `p2o_DispVU1Default` | `SetQuaternionByAxisRotateVEAngle` | anchor | 0x0010E830 | `src/quaternion` |
| `p2o_TransMicroProgram` | `GetQuaternionCosRadian` | anchor | 0x0010E8F0 | `src/quaternion` |
| `gif_EndPacketPath1` | `gif_SpriteOrg` | anchor | 0x001109C0 | `src/GifPacket` |
| `gif_MakeSpriteOffset` | `gif_DrawPolyF4` | anchor | 0x00110E90 | `src/GifPacket` |
| `gif_MakeSpriteWithStrip` | `gif_DrawStripF` | anchor | 0x00111198 | `src/GifPacket` |
| `gif_PointOffset` | `gif_DrawStripG` | anchor | 0x00111560 | `src/GifPacket` |
| `gif_Line` | `gif_Draw2DStripG` | anchor | 0x00111768 | `src/GifPacket` |
| `gif_Sprite` | `gif_Draw2DUVStripG` | anchor | 0x00111940 | `src/GifPacket` |
| `gif_SpriteOrg` | `gif_SetGsReg` | anchor | 0x00111BB0 | `src/GifPacket` |
| `gif_SetDrawEnviroment` | `gif_MakePoint2D` | anchor | 0x00111BE0 | `src/GifPacket` |
| `gif_DrawPolyF4` | `gif_MakePoint2DOffset` | anchor | 0x00111CA8 | `src/GifPacket` |
| `gif_DrawStripF` | `gif_MakeLine2D` | anchor | 0x00111D80 | `src/GifPacket` |
| `gif_DrawStripG` | `gif_MakeSpriteNoTexture` | anchor | 0x00111E90 | `src/GifPacket` |
| `gif_Draw2DStripG` | `gif_MakeSpriteNoTextureOffset` | anchor | 0x00111F88 | `src/GifPacket` |
| `gif_Draw2DUVStripG` | `gif_Point` | anchor | 0x00112098 | `src/GifPacket` |
| `gif_Init` | `gif_LineOffset` | anchor | 0x00112190 | `src/GifPacket` |
| `gsb_SetFrame` | `gif_SetAlpha` | anchor | 0x00112240 | `src/GifPacket` |
| `gsb_Init` | `gif_MoveImage` | anchor | 0x001122E0 | `src/GifPacket` |
| `gsb_Reduction` | `gif_SetZTest` | anchor | 0x001123E0 | `src/GifPacket` |
| `gsb_scissorOnDemo` | `_IsInScreen` | anchor | 0x001124F0 | `src/GifPacket` |
| `gsb_controlBrightness` | `gsb_SetFrame` | anchor | 0x00112558 | `src/GsBase` |
| `gsb_MakeCommonMatrix` | `gsb_controlBrightness` | anchor | 0x001136B0 | `src/GsBase` |
| `gsb_SetVSMatrixSub` | `gsb_MakeCommonMatrix` | anchor | 0x00113D68 | `src/GsBase` |
| `light_DispVolume` | `gsb_SetZoom` | anchor | 0x00116338 | `src/GsBase` |
| `_RemakeNormal` | `_RotCurrentMatrixY` | anchor | 0x00119678 | `src/Matrix` |
| `_Sqrt` | `_RotCurrentMatrixZ` | anchor | 0x00119738 | `src/Matrix` |
| `_InitCurrentMatrix` | `_ScaleCurrentMatrix` | anchor | 0x001197F8 | `src/Matrix` |
| `_PopCurrentMatrix` | `_SetCurrentMatrix` | anchor | 0x001198B0 | `src/Matrix` |
| `_TransCurrentMatrix` | `_MulCurrentMatrixR` | anchor | 0x001198C8 | `src/Matrix` |
| `_SetTransCurrentMatrix` | `_MulCurrentMatrixL` | anchor | 0x00119930 | `src/Matrix` |
| `_ClearTransCurrentMatrix` | `_ApplyCurrentMatrix` | anchor | 0x00119988 | `src/Matrix` |
| `_RotCurrentMatrixX` | `_RotTransPersCurrentMatrix` | anchor | 0x001199A8 | `src/Matrix` |
| `_RotCurrentMatrixY` | `_TransposeCurrentMatrix` | anchor | 0x001199D8 | `src/Matrix` |
| `_RotCurrentMatrixZ` | `_TransposeRotationCurrentMatrix` | anchor | 0x00119A28 | `src/Matrix` |
| `_ScaleCurrentMatrix` | `_InverseCurrentMatrix` | anchor | 0x00119A58 | `src/Matrix` |
| `_SetCurrentMatrix` | `_NormalizeVector` | anchor | 0x00119AA8 | `src/Matrix` |
| `_MulCurrentMatrixR` | `_InnerProduct` | anchor | 0x00119AD8 | `src/Matrix` |
| `_MulCurrentMatrixL` | `_OuterProduct` | anchor | 0x00119B08 | `src/Matrix` |
| `_ApplyCurrentMatrix` | `_AddVector` | anchor | 0x00119B28 | `src/Matrix` |
| `_RotTransPersCurrentMatrix` | `_AddVectorXYZ` | anchor | 0x00119B40 | `src/Matrix` |
| `_TransposeCurrentMatrix` | `_SubVector` | anchor | 0x00119B58 | `src/Matrix` |
| `_TransposeRotationCurrentMatrix` | `_SubVectorXYZ` | anchor | 0x00119B70 | `src/Matrix` |
| `_InverseCurrentMatrix` | `_ScaleVector` | anchor | 0x00119B88 | `src/Matrix` |
| `_PushVu0Registers` | `_ScaleVectorXYZ` | anchor | 0x00119BA8 | `src/Matrix` |
| `_PopVu0Registers` | `_ScaleVector2XYZ` | anchor | 0x00119BC8 | `src/Matrix` |
| `mc_setBaseOffset` | `_FTOI4Vector` | anchor | 0x00119BE8 | `src/Matrix` |
| `mc_SetMicroCode` | `_FTOI0Vector` | anchor | 0x00119C00 | `src/Matrix` |
| `pac_DispQW` | `_GetRandom` | anchor | 0x0011A230 | `src/Matrix` |
| `pac_DumpPac` | `_GetRandomVector` | anchor | 0x0011A248 | `src/Matrix` |
| `pac_makeBoundingBox` | `_GetRandomVector0` | anchor | 0x0011A268 | `src/Matrix` |
| `pac_error` | `_RotTransCurrentMatrix` | anchor | 0x0011A280 | `src/Matrix` |
| `pac_makeNormalStrip` | `mc_setBaseOffset` | anchor | 0x0011A2E0 | `src/MicroCode` |
| `pac_getWeight` | `mc_SetMicroCode` | anchor | 0x0011A430 | `src/MicroCode` |
| `pac_setGifTag` | `pac_DumpPac` | anchor | 0x0011A988 | `src/Packet` |
| `pac_closeTag` | `pac_makeBoundingBox` | anchor | 0x0011AB18 | `src/Packet` |
| `pac_checkDivide` | `pac_makeNormalStrip` | anchor | 0x0011AD08 | `src/Packet` |
| `pac_countOneVertexPacketSize` | `pac_getWeight` | anchor | 0x0011B168 | `src/Packet` |
| `pac_getTextureInfo` | `pac_setGifTag` | anchor | 0x0011BB00 | `src/Packet` |
| `pac_makeShapeTable` | `pac_closeTag` | anchor | 0x0011BBD8 | `src/Packet` |
| `pac_Dump` | `pac_countOneVertexPacketSize` | anchor | 0x0011BFC0 | `src/Packet` |
| `reg_clipPacketBoundingBox` | `prim_DispWireBox` | anchor | 0x0011FCC0 | `src/Primitive` |
| `shadow_KillShadow` | `reg_TransTexturePacket` | anchor | 0x00124450 | `src/RegistPacket` |
| `shadow_SetLength` | `reg_GetShinePri` | anchor | 0x00124488 | `src/RegistPacket` |
| `iosCdvdMgrSearchFile` | `tex_RemakeRegistersSampleMin` | anchor | 0x00132078 | `src/Texture` |
| `inflate` | `iosCdvdBackGroundMgrInit` | anchor | 0x00135728 | `ios/cdvd` |
| `iosMcMgrSync` | `iosMcSync` | anchor | 0x0013A0B8 | `ios/mcard` |
| `iosMcTest` | `iosMcGetInfo` | anchor | 0x0013A0D0 | `ios/mcard` |
| `iosMcSync` | `iosMcFormat` | anchor | 0x0013A110 | `ios/mcard` |
| `iosMcGetInfo` | `iosMcUnformat` | anchor | 0x0013A158 | `ios/mcard` |
| `iosMcIconWriteIconsys` | `iosMcGetDir` | anchor | 0x0013A1A0 | `ios/mcard` |
| `iosMcIconWriteIcon` | `iosMcDelete` | anchor | 0x0013A1E8 | `ios/mcard` |
| `_iosMcIconWriteIconsys` | `iosMcSaveIconBlock` | anchor | 0x0013A230 | `ios/mcard` |
| `controler_stable_check` | `signal_handler` | anchor | 0x0013CAA8 | `ios/message` |
| `Vibration_WaveDecode` | `iosPadActStopAll` | anchor | 0x0013DD58 | `ios/pad` |
| `Shock_Request` | `iosPadActVolumeSet` | anchor | 0x0013DDC0 | `ios/pad` |
| `ShockRequestBox_Clear` | `Vibration_WaveDecode` | anchor | 0x0013E208 | `ios/shockdriver` |
| `ShockRequestBox_Regst` | `Shock_Request` | anchor | 0x0013E4F8 | `ios/shockdriver` |
| `ShockRequestBox_RequestCancel` | `ShockRequestBox_Regst` | anchor | 0x0013E980 | `ios/shockdriver` |
| `ShockDriver_GetShockVoiceMax` | `ShockRequestBox_RequestCancel` | anchor | 0x0013ED40 | `ios/shockdriver` |
| `Init_ShockRequestAlloc` | `ShockDriver_GetShockVoiceMax` | anchor | 0x0013EF70 | `ios/shockdriver` |
| `iosThreadCreateS` | `Init_ShockRequestAlloc` | anchor | 0x0013F0D0 | `ios/shockdriver` |
| `iosThreadSetPri` | `Shock_SetShockVoiceSet` | anchor | 0x0013F2F0 | `ios/shockdriver` |
| `iosThreadMessage` | `Init_Player` | anchor | 0x0013F320 | `ios/shockdriver` |
| `iosThreadResume` | `Shock_Decode` | anchor | 0x0013F3C8 | `ios/shockdriver` |
| `iosThreadCreate` | `Vibration_SetDecodeEnd` | anchor | 0x0013F488 | `ios/shockdriver` |
| `iosThreadGetPri` | `requestFree` | anchor | 0x0013F4B8 | `ios/shockdriver` |
| `iosSemaWait` | `iosThreadSetPri` | anchor | 0x0013F828 | `ios/thread` |
| `iosSemaSignal` | `iosThreadMessage` | anchor | 0x0013F880 | `ios/thread` |
| `isysGObjSearchFromObjKindID_begin` | `isysGObjSearchFromObjKindID_next` | anchor | 0x00140FC8 | `isys/gobj` |
| `cut_gobj_dl_link` | `isysGObjSearchFromLabelTypeID` | anchor | 0x00141038 | `isys/gobj` |
| `isysGObjRemoveObjDL` | `isysGObjGetExist_begin` | anchor | 0x00141090 | `isys/gobj` |
| `isysGObjMoveObjDLHead` | `cut_gobj_dl_link` | anchor | 0x00141198 | `isys/gobj_dl` |
| `iosOmBeforeFuncStandard` | `iosOmSendMail` | anchor | 0x00142370 | `isys/obj_manager` |
| `soundInit` | `iosOmSendMailLink` | anchor | 0x001423B8 | `isys/obj_manager` |
| `soundOutputModeSet` | `iosOmExeMail` | anchor | 0x00142430 | `isys/obj_manager` |
| `soundReverbDepthSet` | `soundInit` | anchor | 0x00143550 | `sound/s_init` |
| `soundAllocIopHeap` | `soundOutputModeSet` | anchor | 0x001436A0 | `sound/s_init` |
| `soundAllocIopFree` | `soundReverbDepthSet` | anchor | 0x001436B0 | `sound/s_init` |
| `ACTGame_InnerVelocityUpdate` | `ACTGame_StageChangeGObjID` | anchor | 0x0014CAC8 | `src/act-game` |
| `ACTGame_BeforeFunc` | `ACTGame_StageChangeGObjDirect` | anchor | 0x0014CB48 | `src/act-game` |
| `hand_able_connect` | `ACTGameView_Init` | anchor | 0x0014CE30 | `src/act-game` |
| `ACTGameCollisionOff` | `ACTGame_isWeaponEnableCatchfire` | anchor | 0x0014D290 | `src/act-game` |
| `ACTGame_CheckItemMotion` | `ACTCheckCollis_WF` | anchor | 0x0014D2D8 | `src/act-game` |
| `ACTGame_CheckHandMotion` | `ACTCheckCollis_W` | anchor | 0x0014D3E0 | `src/act-game` |
| `ACTGame_StageChangeGObjID` | `ACTCheckCollis_CI` | anchor | 0x0014D510 | `src/act-game` |
| `ACTGame_StageChangeGObjDirect` | `ACTCheckCollis_WELL` | anchor | 0x0014D5B8 | `src/act-game` |
| `ACTGame_FLAG_LIFEPINCH` | `ACTCheckCollis_WAY` | anchor | 0x0014D6C0 | `src/act-game` |
| `ACTGame_FLAG_TETSUNAGI` | `ACTCheckViewCl` | anchor | 0x0014D808 | `src/act-game` |
| `ACTGameView_Init` | `ACTGameView_Check` | anchor | 0x0014DB00 | `src/act-game` |
| `ACTCharctrl_Lock` | `ACTGameViewSimple_Check` | anchor | 0x0014DB48 | `src/act-game` |
| `ACTCharctrl_Unlock` | `ACTGame_GetMotOrientFromWeapon` | anchor | 0x0014DB90 | `src/act-game` |
| `ACTGame_DisconnectHand` | `ACTGame_isWeaponCombustible` | anchor | 0x0014DC20 | `src/act-game` |
| `PAIR_GetPosition_BOY` | `ACTGame_GetNearestGObj` | anchor | 0x0014DC48 | `src/act-game` |
| `GetBoyWeaponGObj` | `IsGirlEscortedInNextStage` | anchor | 0x00158340 | `src/boyact` |
| `actBoyBHang` | `OnGirlEscortFlag` | anchor | 0x001583B0 | `src/boyact` |
| `actBoyFall` | `RequestStageChangeKidnapEnd` | anchor | 0x00158478 | `src/boyact` |
| `actBoyCall` | `GetEfStageCameraTargetID` | anchor | 0x00158528 | `src/boyact` |
| `actBoyBeslam` | `ACTSearchGObj` | anchor | 0x001587A0 | `src/boyact` |
| `actCommonSlowrun` | `ControlMotionOrient` | anchor | 0x001639C8 | `src/commonact` |
| `ACT_LAYOUT_GAMEOVER` | `_ACTMotDir_V` | anchor | 0x00163A38 | `src/commonact` |
| `_ACTMotDirSmzDirect` | `SetCorrectOrientOfChain` | anchor | 0x00163AC0 | `src/commonact` |
| `actCommonDelete` | `afterCommonBox` | anchor | 0x00163D38 | `src/commonact` |
| `IsEnemyBrainToBoy` | `FlyMail` | anchor | 0x0016ACF8 | `src/enemy_act` |
| `clip_floor_1` | `isEnemyHyde` | anchor | 0x0016AF98 | `src/enemy_act` |
| `DrawGObjWallCollision` | `clip_floor_1` | anchor | 0x0016B7F0 | `src/fieldCollision` |
| `ClipFloorByGObj` | `DrawGObjWallCollision` | anchor | 0x0016C288 | `src/fieldCollision` |
| `ClipWallField` | `ClipFloorByGObj` | anchor | 0x0016D1B8 | `src/fieldCollision` |
| `ClipWallFieldCheckCB` | `ClipWallField` | anchor | 0x0016D458 | `src/fieldCollision` |
| `ClipCollision` | `ClipWallFieldCheckCB` | anchor | 0x0016D520 | `src/fieldCollision` |
| `SetSimplePlane` | `ClipCollision` | anchor | 0x0016D5F0 | `src/fieldCollision` |
| `fzMagnitude2fv` | `SetSimplePlane` | anchor | 0x0016DA38 | `src/fieldCollision` |
| `fzMagnitudeByLine` | `GetWallAttribute` | anchor | 0x0016DA50 | `src/fieldCollision` |
| `fzMagnitudeByLineSeg` | `GetFloorAttribute` | anchor | 0x0016DA70 | `src/fieldCollision` |
| `GetEyeDirection` | `fzMagnitudeByLineSeg` | anchor | 0x0016F470 | `src/fuzio` |
| `funcGirlHandDisconnect` | `GetEyeDirection` | anchor | 0x0016F600 | `src/girl_act` |
| `subGirlBrain_Pulledup` | `sort_list` | anchor | 0x0016FC60 | `src/girl_act` |
| `subGirlControl` | `girlBrainMain_PositionUpdate` | anchor | 0x00171030 | `src/girl_act` |
| `actGirlPulledReady` | `checkWaterfallResult` | anchor | 0x00172A80 | `src/girl_act` |
| `actGirlReadyMove` | `isHideRecheck` | anchor | 0x00174808 | `src/girl_act` |
| `IsGirlStatusEscortEnable` | `GetSafePosition` | anchor | 0x00175D80 | `src/girl_act` |
| `actGirlSupportGBLoop` | `isEnterHideadv` | anchor | 0x00177898 | `src/girl_act` |
| `actGirlDitch3mExec` | `HandMgr_Update` | anchor | 0x00179208 | `src/girl_act` |
| `actGirlStand` | `HandMgr_Judge` | anchor | 0x00179300 | `src/girl_act` |
| `actGirlWalk` | `HandMgr_Print` | anchor | 0x00179468 | `src/girl_act` |
| `jimakuEnd` | `enemy_list_compare` | anchor | 0x0017C6B0 | `src/girl_act` |
| `jimakuDisp` | `ACTCheckCollis_SAFE` | anchor | 0x0017C6D0 | `src/girl_act` |
| `scpTorchLightOn` | `scpLinkBGAtoLayoutedTarget` | anchor | 0x00183808 | `src/script` |
| `scpTorchLightOff` | `scpLinkBGAtoLayoutedTargetSkelton` | anchor | 0x00183848 | `src/script` |
| `scpPlayMotDirSmz` | `scpGetWallCollision` | anchor | 0x00183A00 | `src/script` |
| `scpDoorTypeUpUp` | `scpIsTorchLightOn` | anchor | 0x00184078 | `src/script` |
| `scpSubAdpcmPlay` | `scpIsBombExplode` | anchor | 0x001840B8 | `src/script` |
| `_SCPMoveCharactorByWay_Cancel` | `scpTransLinear` | anchor | 0x00184218 | `src/script` |
| `scpSekizouCheckPoint` | `scpRotateLinear` | anchor | 0x001842F0 | `src/script` |
| `scpWakeupEnemyOne` | `scpTriggerPosBall` | anchor | 0x00184430 | `src/script` |
| `scpSleepEnemyOne` | `scpTriggerBall` | anchor | 0x00184520 | `src/script` |
| `preload` | `scpTriggerPosBox` | anchor | 0x001849A0 | `src/script` |
| `scpDispOffAllWithKind` | `scpEffectStart` | anchor | 0x00184AD8 | `src/script` |
| `actSt25aQueenAppearChk` | `scpMaskGeneratorAll` | anchor | 0x00184CE0 | `src/script` |
| `actConte13Jimaku` | `scpPlayMotNode` | anchor | 0x00184FF0 | `src/script` |
| `actSt25aGenerator` | `scpPlayPosSet` | anchor | 0x001850B8 | `src/script` |
| `actSt25aQueenDead` | `RequestStageChange` | anchor | 0x00185178 | `src/script` |
| `actSwordEff` | `RequestStageChangeSimple` | anchor | 0x001852E8 | `src/script` |
| `actSwordEffXL` | `RequestStageChangeDirect` | anchor | 0x00185338 | `src/script` |
| `actSt25aQueenBeforeChk` | `scpFadeOut` | anchor | 0x00185398 | `src/script` |
| `actConte11Jimaku` | `scpFadeIn` | anchor | 0x001853B8 | `src/script` |
| `actSt25aQueenDeadEvent` | `scpFadeChk` | anchor | 0x001853D0 | `src/script` |
| `warpGirlInit` | `ScpCallCameraGetTarget` | anchor | 0x00185838 | `src/script` |
| `MakeAttackPack_Actor` | `actConte11Jimaku` | anchor | 0x00187BC8 | `src/st25a` |
| `saveEditedDataBinary` | `brainUnlockGirl` | anchor | 0x0018A360 | `src/brain` |
| `saveEditedData` | `brainAddLevel` | anchor | 0x0018A370 | `src/brain` |
| `gif_test` | `brainSetLevel` | anchor | 0x0018A3C0 | `src/brain` |
| `DebugDispBox` | `brainCheckView` | anchor | 0x0018A448 | `src/brain` |
| `drawXZArrow` | `saveEditedDataBinary` | anchor | 0x0018A530 | `src/camera-editor` |
| `dispCameraPinType2` | `gif_test` | anchor | 0x0018A970 | `src/camera-editor` |
| `CameraEdit_DispPinType2` | `DebugDispBox` | anchor | 0x0018AA58 | `src/camera-editor` |
| `dispBox` | `drawXZArrow` | anchor | 0x0018B890 | `src/camera-editor` |
| `CameraEdit_DispBoxType2` | `dispCameraPinType2` | anchor | 0x0018BBE0 | `src/camera-editor` |
| `menuGroupSelect` | `CameraEdit_DispPinType2` | anchor | 0x0018BFF8 | `src/camera-editor` |
| `menuPinSelect` | `dispBox` | anchor | 0x0018C688 | `src/camera-editor` |
| `CameraSetCameraSet_Default` | `CameraEdit_reset_box` | anchor | 0x0018EB70 | `src/camera-editor` |
| `ico2camera_GetTargetPos` | `CameraEdit_reflect_box` | anchor | 0x0018EDE0 | `src/camera-editor` |
| `initMonitorCamera` | `CameraEdit_BOX_NUMBER` | anchor | 0x0018F050 | `src/camera-editor` |
| `monitorMonitorCamera` | `CameraEdit_PIN_NUMBER` | anchor | 0x0018F060 | `src/camera-editor` |
| `ChaseCamera` | `CameraEdit_PIN_NUMBER_ALL` | anchor | 0x0018F0A8 | `src/camera-editor` |
| `CameraMove` | `CameraEdit_BOX` | anchor | 0x0018F0E8 | `src/camera-editor` |
| `ReflectCameraSetBinary` | `CameraEdit_PIN` | anchor | 0x0018F100 | `src/camera-editor` |
| `InitIco2Camera` | `CameraEdit_DispPin` | anchor | 0x0018F128 | `src/camera-editor` |
| `SetCameraMatrix_Ico2` | `StickToTrans` | anchor | 0x0018F418 | `src/camera-editor` |
| `SetCameraZoomOffsetRatio` | `_CameraEdit_PIN` | anchor | 0x0018F680 | `src/camera-editor` |
| `GetCameraGroupCurrent` | `_CameraEdit_add_box` | anchor | 0x0018F6A8 | `src/camera-editor` |
| `GetCameraGroupFromGObj` | `_CameraEdit_add_pin` | anchor | 0x0018F820 | `src/camera-editor` |
| `MakeCameraSetBinary` | `ico2camera_GetTargetPos` | anchor | 0x0018FA28 | `src/camera-ico2` |
| `InitCamera` | `Camctrl_SetTarget` | anchor | 0x001948A0 | `src/camera-root` |
| `Camctrl_SetTarget` | `CameraChangeTargetParallel` | anchor | 0x00194918 | `src/camera-root` |
| `InitCameraSetManager` | `CameraGetTargets` | anchor | 0x001949E0 | `src/camera-root` |
| `StartPendulum` | `GetCameraInfo_tmp` | anchor | 0x00194EF8 | `src/camera-root` |
| `_InterGV` | `RestoreGeneratorGeo` | anchor | 0x0019BEC8 | `src/generator` |
| `_DistSqGV` | `DirectCallEnemy` | anchor | 0x0019C060 | `src/generator` |
| `_DistxzGV` | `UnlockEnemyGenerate` | anchor | 0x0019C218 | `src/generator` |
| `_RotyGV` | `ReturnEnemyToGenerator` | anchor | 0x0019C330 | `src/generator` |
| `_GetDirection` | `SetInfoSpKidnapGenerator` | anchor | 0x0019C450 | `src/generator` |
| `_RotGVF` | `IsEnableCallEnemyByTargetGObj` | anchor | 0x0019C4E8 | `src/generator` |
| `_OrientXZGV` | `_InterGV` | anchor | 0x0019C560 | `src/gv` |
| `HandyCamera_TargetMoveType` | `_DistSqGV` | anchor | 0x0019C8D8 | `src/gv` |
| `InitHandCameraCorrect` | `_DistxzGV` | anchor | 0x0019C940 | `src/gv` |
| `HandCameraCorrect` | `_RotyGV` | anchor | 0x0019CA48 | `src/gv` |
| `InitMailAdditionalData` | `AlignDegGV` | anchor | 0x0019CEF8 | `src/gv` |
| `GetMailAdditionalData` | `HandyCamera_TargetMoveType` | anchor | 0x0019D2C0 | `src/hand-camera` |
| `_IsInScreen2` | `do_DrawLine` | anchor | 0x0019E1D0 | `src/poly-flat` |
| `do_DrawLine` | `trans_bird` | anchor | 0x0019E6C8 | `src/act_bird` |
| `trans_bird` | `vector_angle_degree` | anchor | 0x0019FEA0 | `src/act_bird` |
| `BirdGeo` | `_ACTSendMailToBirdAll` | anchor | 0x001A00F0 | `src/act_bird` |
| `BossCtrlGeo` | `CapsuleGhostBossStart` | anchor | 0x001A10F0 | `src/itou_boss` |
| `m33_to_quat` | `lw_pos_to_ico_pos` | anchor | 0x001A1440 | `src/itou_sub` |
| `lw_pos_to_ico_pos` | `apply_matrix_w1` | anchor | 0x001A1470 | `src/itou_sub` |
| `apply_matrix_w1` | `ico_m33_to_quat` | anchor | 0x001A14A0 | `src/itou_sub` |
| `ico_m33_to_quat` | `pbga_start` | anchor | 0x001A14D8 | `src/itou_sub` |
| `pbga_start` | `set_vertex` | anchor | 0x001A1520 | `src/lightning` |
| `set_vertex` | `apply_m34` | anchor | 0x001A2558 | `src/lightning` |
| `DrawLightningN` | `lightning_test` | anchor | 0x001A2688 | `src/lightning` |
| `apply_m34` | `cmpr` | anchor | 0x001A2760 | `src/lightning` |
| `strFileClose` | `videoDecFlush` | anchor | 0x001A6B78 | `ito/mpeg/mv_videodec` |
| `videoDecCreate` | `videoDecIsFlushed` | anchor | 0x001A7008 | `ito/mpeg/mv_videodec` |
| `videoDecBeginPut` | `videoDecMain` | anchor | 0x001A7058 | `ito/mpeg/mv_videodec` |
| `videoDecEndPut` | `mpegError` | anchor | 0x001A70A8 | `ito/mpeg/mv_videodec` |
| `videoDecFlush` | `mpegNodata` | anchor | 0x001A70D0 | `ito/mpeg/mv_videodec` |
| `allocObjectData` | `voBufDecCount` | anchor | 0x001A7458 | `ito/mpeg/mv_vobuf` |
| `StageManager` | `stgmgrForceSwitchWithFade` | anchor | 0x001A8DC8 | `src/StageManager` |
| `stgmgrForceSwitchWithFade` | `stgmgrNextStagePreLoadForceStageSet` | anchor | 0x001A8E40 | `src/StageManager` |
| `backStageProcessMain` | `CheckPoint` | anchor | 0x001A8E70 | `src/StageManager` |
| `display` | `debug_PrintFontWindow` | anchor | 0x001AF580 | `src/debug` |
| `debugEEExceptionMain` | `debug_PrintfDummy` | anchor | 0x001AF850 | `src/debug` |
| `debugIOPExceptionMain` | `debug_PrintFontWindowDummy` | anchor | 0x001AF870 | `src/debug` |
| `debug_assertMessage` | `debug_StdPrintfDummy` | anchor | 0x001AF898 | `src/debug` |
| `debug_SetExceptionMessage` | `debug_PrintMatrix` | anchor | 0x001AFA78 | `src/debug` |
| `debug_TargetGObj_Func` | `debug_BeginTimer` | anchor | 0x001B2800 | `src/debug` |
| `gamesysObjInfoLoad` | `debug_STAFFROLLTest` | anchor | 0x001B3948 | `src/debug` |
| `gamesysObjInfoEmptyAreaSearch` | `debug_SETest_color` | anchor | 0x001B3970 | `src/debug` |
| `gamesysObjInfoBaseSet` | `debug_reverbTest` | anchor | 0x001B39B0 | `src/debug` |
| `gamesysGeneratorInfoLoad` | `debugCdvdLoadInfoSegDisp` | anchor | 0x001B3AE0 | `src/debug` |
| `gamesysObjInfoStageInitFlagCls` | `debug_BackStageTest` | anchor | 0x001B3C18 | `src/debug` |
| `gamesysObjInfoPosSetStage` | `debug_SelectPad2ControlGobj` | anchor | 0x001B3CC0 | `src/debug` |
| `gamesysObjInfoUniqDataSet` | `debug_FreeCamera` | anchor | 0x001B3DE0 | `src/debug` |
| `gamesysObjInfoPosNewStageSet` | `CloseVif1DirectPacket` | anchor | 0x001B3E20 | `src/debug` |
| `gamesysObjInfoGet` | `SendVif1DirectPacket` | anchor | 0x001B3E60 | `src/debug` |
| `gamesysObjInfoCls` | `RestoreNormalDrawEnvironment` | anchor | 0x001B3EB8 | `src/debug` |
| `gamesysGirlStageGet` | `SetTextureWithFrameBuffer` | anchor | 0x001B3F28 | `src/debug` |
| `gamesysGetGirlStageIDAndPosition` | `SetTexDrawEnvironment` | anchor | 0x001B3FE8 | `src/debug` |
| `gamesysStageExitTimeSet` | `SetDrawnTextureEnvironment` | anchor | 0x001B4090 | `src/debug` |
| `gamesysMemoryHandlerWrite` | `SetDrawEnvironment` | anchor | 0x001B4158 | `src/debug` |
| `gamesysMemoryHandlerRead` | `drawSprite` | anchor | 0x001B4218 | `src/debug` |
| `gamesysMemorySave` | `PutFont` | anchor | 0x001B45B0 | `src/debug` |
| `gamesysMemoryLoad` | `resetPath` | anchor | 0x001B49A0 | `src/debug` |
| `gamesysCharacterInfoSave` | `drawWin` | anchor | 0x001B4C20 | `src/debug` |
| `gamesysGeneratorInfoSave` | `saveBack` | anchor | 0x001B4DE8 | `src/debug` |
| `disp_memory_partition` | `gamesysObjInfoGet` | anchor | 0x001B7188 | `src/gamesys` |
| `ExecIcoMisc` | `gamesysObjInfoCls` | anchor | 0x001B7290 | `src/gamesys` |
| `InitIcoMisc` | `gamesysGirlStageGet` | anchor | 0x001B73A0 | `src/gamesys` |
| `ExitIcoMisc` | `gamesysStageExitTimeSet` | anchor | 0x001B7418 | `src/gamesys` |
| `la_vibe_select` | `la_boot_confirm_memory_card` | anchor | 0x001BE238 | `src/layout_action` |
| `la_load_game_memory_card_check` | `la_mc_preview_info` | anchor | 0x001BE2E0 | `src/layout_action` |
| `la_load_confirm_no_memory_card` | `la_general_mc_confirm` | anchor | 0x001BE478 | `src/layout_action` |
| `la_system_save_processing` | `la_game_loading` | anchor | 0x001BE9D0 | `src/layout_action` |
| `default_item_select` | `la_switching_stage` | anchor | 0x001BEBC8 | `src/layout_action` |
| `texture_fading` | `la_save_confirm_yesno` | anchor | 0x001BEC08 | `src/layout_action` |
| `display_primary_texture_layout` | `keyconfig_reset` | anchor | 0x001BEC80 | `src/layout_action` |
| `BoxMemoryFunc` | `GetDistanceOfGObj` | anchor | 0x001CAED8 | `src/box` |
| `getAlign` | `moveXPlus` | anchor | 0x001CAF40 | `src/box` |
| `GetDistanceOfGObj` | `moveXMinus` | anchor | 0x001CB000 | `src/box` |
| `moveXPlus` | `moveZPlus` | anchor | 0x001CB0C8 | `src/box` |
| `moveXMinus` | `moveZMinus` | anchor | 0x001CB188 | `src/box` |
| `GetChainAnimation` | `DispClothMesh` | anchor | 0x001D0EE8 | `src/clothAnimation` |
| `InitChains` | `proc` | anchor | 0x001D1A90 | `src/clothAnimation` |
| `DispClothMesh` | `getCloth4D_postProcess` | anchor | 0x001D30D8 | `src/clothAnimation` |
| `getCloth4D_preProcess` | `GetChainNodeGlobalQuaternion` | anchor | 0x001D3AD8 | `src/clothAnimation` |
| `proc` | `MoveChainExtendedWeight` | anchor | 0x001D3B80 | `src/clothAnimation` |
| `getCloth4D` | `InitChainVelocity` | anchor | 0x001D3B98 | `src/clothAnimation` |
| `getCloth4D_postProcess` | `DeleteChainExtendedWeight` | anchor | 0x001D3CA0 | `src/clothAnimation` |
| `GetCloth4D` | `GetChainNodeID` | anchor | 0x001D3CC8 | `src/clothAnimation` |
| `InitCloth4D` | `ResetClothAnimation` | anchor | 0x001D3CE0 | `src/clothAnimation` |
| `GetChainNodeGlobalQuaternion` | `GetChainExWeightGlobalQuaternion` | anchor | 0x001D3DC0 | `src/clothAnimation` |
| `MoveChainExtendedWeight` | `GetChainCollision` | anchor | 0x001D3E88 | `src/clothAnimation` |
| `InitChainVelocity` | `FSqrtInv` | anchor | 0x001D3F68 | `src/clothAnimation` |
| `DeleteChainExtendedWeight` | `getXZLength` | anchor | 0x001D3F88 | `src/clothAnimation` |
| `GetChainNodeID` | `getXZInvLength` | anchor | 0x001D3FB0 | `src/clothAnimation` |
| `InitClothTestGeo` | `getXZLengthSquare` | anchor | 0x001D3FD8 | `src/clothAnimation` |
| `ClothTestGeo` | `subAndGetInvLength` | anchor | 0x001D3FF8 | `src/clothAnimation` |
| `ClothTestDL` | `scaleAndAddVectorXYZ` | anchor | 0x001D4030 | `src/clothAnimation` |
| `editParam` | `StartQueenAttackEffect` | anchor | 0x001D7020 | `src/darkVolume` |
| `setQ` | `editParam` | anchor | 0x001D7248 | `src/effectTool` |
| `saveEffectData` | `setQ` | anchor | 0x001D7C70 | `src/effectTool` |
| `EnemyCheckHit` | `exitEffectTool` | anchor | 0x001D8690 | `src/effectTool` |
| `moveDataElements` | `SetEnemyStonizedVisual` | anchor | 0x001DA050 | `src/enemy` |
| `FlagDL` | `moveDataElements` | anchor | 0x001DAD60 | `src/enemyParts` |
| `playSE` | `executeSEPackageWithNoGObj` | anchor | 0x001DCB38 | `src/frameDependSequence` |
| `playEff` | `ExecuteSEPackageWithVolumeRate` | anchor | 0x001DCC90 | `src/frameDependSequence` |
| `executeSEPackageWithNoGObj` | `execSE` | anchor | 0x001DCF90 | `src/frameDependSequence` |
| `ExecuteSEPackage` | `checkModelDataID` | anchor | 0x001DD010 | `src/frameDependSequence` |
| `InitMotionFile` | `CheckMotionIncludeFacialData` | anchor | 0x001E14B8 | `src/motionFileManager` |
| `AddMotionMemorySize` | `limitHPAngleAndSetB` | anchor | 0x001E1588 | `src/motionManager` |
| `GetMotionMemorySize` | `avoidReverseInterpOnCurrentMatrix` | anchor | 0x001E1D10 | `src/motionManager` |
| `ResetDynamicMotionManager` | `avoidReverseInterpOnCurrentMatrixWithLimit` | anchor | 0x001E1E60 | `src/motionManager` |
| `CheckMotionIncludeFacialData` | `EditRotEmphasys` | anchor | 0x001E4C60 | `src/motionManager` |
| `dispSkelton` | `adjustSideWall` | anchor | 0x001E8EC8 | `src/motionManager` |
| `GetWallVector` | `checkWallUpperWall` | anchor | 0x001E92A8 | `src/motionManager` |
| `GetMotionPlaySpeedRatio` | `getFinalMatrixCore` | anchor | 0x001ED480 | `src/motionManager` |
| `execFrameTrigger` | `pursueNaturalGeometry` | anchor | 0x001ED560 | `src/motionManager` |
| `UpdateFrameCounter` | `GetWallVector` | anchor | 0x001ED610 | `src/motionManager` |
| `sendStateMail` | `upperFieldCheck` | anchor | 0x001ED640 | `src/motionManager` |
| `setParticleEffect` | `DispMultiBgaManagerWithKind` | anchor | 0x001F3B80 | `src/multiBgaManager` |
| `DispStageMultiBgaManager` | `auraInspireBefore` | anchor | 0x001F9A60 | `src/staticBlur` |
| `auraInspireBefore` | `reduceWork2ToWork0` | anchor | 0x001FB360 | `src/staticBlur` |
| `copyCurrentFBToFeedBackArea` | `pasteFullScreenFlare` | anchor | 0x001FBDF0 | `src/staticBlur` |
| `blendWork0ToWork1` | `copyToWork_233` | anchor | 0x001FBF58 | `src/staticBlur` |
| `parallelAddFeedBackAreaToWork0` | `copyToWork2` | anchor | 0x001FC080 | `src/staticBlur` |
| `blurBlendFeedBackAreaToWork1` | `pasteToFB` | anchor | 0x001FC178 | `src/staticBlur` |
| `cleanUpFB` | `calcSun` | anchor | 0x001FCC60 | `src/staticBlur` |
| `fillWork2` | `colorSetting` | anchor | 0x001FCD20 | `src/staticBlur` |
| `dispSun` | `dispPostInfo` | anchor | 0x001FCEE0 | `src/staticBlur` |
| `reduceWork2ToWork0` | `InitStaticBlur` | anchor | 0x001FD480 | `src/staticBlur` |
| `UpdateStormPackage` | `SetStaticBlur` | anchor | 0x001FD530 | `src/staticBlur` |
| `DispStormPackage` | `SetDepthFadeParam` | anchor | 0x001FD540 | `src/staticBlur` |
| `InitStormTestGeo` | `_initStaticBlur` | anchor | 0x001FD578 | `src/staticBlur` |
| `DeleteStreamMotionManager` | `CheckReadyStreamMotion` | anchor | 0x001FF090 | `src/streamMotionManager` |
| `SugiLeafGeo` | `_handler` | anchor | 0x001FF1E8 | `src/streamMotionManager` |
| `InitWindField` | `drawSenpuuki` | anchor | 0x00203810 | `src/windField` |
| `drawSenpuuki` | `GetWindVector` | anchor | 0x00203BF0 | `src/windField` |
| `ExecWindField` | `dummyGetWindVector` | anchor | 0x00203C10 | `src/windField` |
| `GetWindVector` | `getParallelWindVector` | anchor | 0x00203C28 | `src/windField` |
| `dummyGetWindVector` | `getRadiateWindVector` | anchor | 0x00203D38 | `src/windField` |
| `getParallelWindVector` | `StopWindField` | anchor | 0x00203DE8 | `src/windField` |
| `getRadiateWindVector` | `drawLines` | anchor | 0x00203DF8 | `src/windField` |
| `isysGObjLinkCameraDLBeforeGObj` | `isysGObjMoveCameraDLHead` | anchor | 0x0020C270 | `isys/gobj_cam_dl` |
| `AdpcmStreamInit` | `isysGObjLinkCameraDLHead` | anchor | 0x0020C340 | `isys/gobj_cam_dl` |
| `adpcmTickProc2` | `isysObjMoveCameraDLAfterGObj` | anchor | 0x0020C3F0 | `isys/gobj_cam_dl` |
| `adpcmDataSet` | `isysObjMoveCameraDLBeforeGObj` | anchor | 0x0020C450 | `isys/gobj_cam_dl` |
| `WayLengthOfPos_Pos` | `AddWayPoint` | anchor | 0x002161E0 | `src/way_llf` |
| `WayPointWithRangeFromPos` | `AddWayPointTop` | anchor | 0x00216248 | `src/way_llf` |
| `WayPointWithRangeFromPos2` | `InsertWayPointAfter` | anchor | 0x00216290 | `src/way_llf` |
| `DeleteWayGroup` | `WayPoint_next` | anchor | 0x00216658 | `src/way_llf` |
| `CloseWayGroup` | `WayPointList_begin` | anchor | 0x00216698 | `src/way_llf` |
| `CreateWayPoint` | `WayPointList_next` | anchor | 0x002166B8 | `src/way_llf` |
| `AddWayPoint` | `waypoint_bidirectional_list` | anchor | 0x002166F8 | `src/way_llf` |
| `AddWayPointTop` | `SetWayGroupActive` | anchor | 0x00216750 | `src/way_llf` |
| `InsertWayPointAfter` | `CheckWayGroupActive` | anchor | 0x00216770 | `src/way_llf` |
| `actE3St09aSekizo` | `actE3CageFallReadyChk` | anchor | 0x0021B660 | `src/e3` |
| `actOpDemo02Chk` | `actConte14_10_Jimaku` | anchor | 0x0021EAA8 | `src/end` |
| `actSt04cDoorDown` | `actSt04aEnvSe` | anchor | 0x0022A6F8 | `src/st04a` |
| `actSt04cEne` | `actSt04aEnvSeWakare1` | anchor | 0x0022A820 | `src/st04a` |
| `actSt04cWaterXL` | `actSt04aEnvSeWakare2` | anchor | 0x0022AAD8 | `src/st04a` |
| `actSt04cDoorDownEvent` | `actConte09_3Jimaku` | anchor | 0x0022AC00 | `src/st04a` |
| `audioDecStart` | `stageSE08bcrane` | anchor | 0x00256700 | `src/stageSEProc` |
| `audioDecPause` | `stageSE08brail` | anchor | 0x00256780 | `src/stageSEProc` |
| `audioDecResume` | `stageSE09asea` | anchor | 0x00256800 | `src/stageSEProc` |
| `dispClear` | `stageSE17bstrong` | anchor | 0x00256D50 | `src/stageSEProc` |
| `setImageSize` | `stageSE19astrong` | anchor | 0x00256E48 | `src/stageSEProc` |
| `sendDispEnv` | `stageSE19arain` | anchor | 0x00256EC0 | `src/stageSEProc` |
| `dispCreate` | `stageSE20astrong` | anchor | 0x00256EE8 | `src/stageSEProc` |
| `dispSwitch` | `stageSE22astrong` | anchor | 0x00256FC8 | `src/stageSEProc` |
| `vblankHandler` | `stageSE22arain` | anchor | 0x00257048 | `src/stageSEProc` |
| `loadImage` | `stageSE24arain` | anchor | 0x00257140 | `src/stageSEProc` |
| `startDisplay` | `stageSE47anoise` | anchor | 0x00257188 | `src/stageSEProc` |
| `viBufCreate` | `loadImage` | anchor | 0x00258B10 | `ito/mpeg/mv_disp` |
| `viBufBeginPut` | `startDisplay` | anchor | 0x00258B88 | `ito/mpeg/mv_disp` |
| `viBufPutTs` | `setRGBAQ` | anchor | 0x00258EF0 | `ito/mpeg/mv_disp` |
| `ResetGObjProc` | `setCLAMP_1` | anchor | 0x002591E8 | `ito/mpeg/mv_disp` |
| `GetMaxGObj` | `setBITBLTBUF` | anchor | 0x00259260 | `ito/mpeg/mv_disp` |
| `GetGObjP` | `setTRXPOS` | anchor | 0x00259298 | `ito/mpeg/mv_disp` |
| `GetGObjId` | `setTRXREG` | anchor | 0x002592D0 | `ito/mpeg/mv_disp` |
| `PrintGObjID` | `setTRXDIR` | anchor | 0x00259308 | `ito/mpeg/mv_disp` |
| `InitPObj` | `GetGObjId` | anchor | 0x0025A6E0 | `src/GobjProc` |
| `FreePObj` | `PrintGObjID` | anchor | 0x0025A728 | `src/GobjProc` |

## Placeholders replaced

| aug6 VMA | old | new (PAL twin) | PAL VMA |
| --- | --- | --- | --- |
| 0x00100110 | `func_00100110` | `ResetEE` | 0x00100110 |
| 0x00100120 | `func_00100120` | `SetGsCrt` | 0x00100120 |
| 0x00100130 | `func_00100130` | `RFU003` | 0x00100130 |
| 0x00100140 | `func_00100140` | `Exit` | 0x00100140 |
| 0x00100150 | `func_00100150` | `RFU005` | 0x00100150 |
| 0x00100160 | `func_00100160` | `LoadExecPS2` | 0x00100160 |
| 0x00100170 | `func_00100170` | `ExecPS2` | 0x00100170 |
| 0x00100180 | `func_00100180` | `RFU008` | 0x00100180 |
| 0x00100190 | `func_00100190` | `RFU009` | 0x00100190 |
| 0x001001A0 | `func_001001A0` | `AddSbusIntcHandler` | 0x001001A0 |
| 0x001001B0 | `func_001001B0` | `RemoveSbusIntcHandler` | 0x001001B0 |
| 0x001001C0 | `func_001001C0` | `Interrupt2Iop` | 0x001001C0 |
| 0x001001D0 | `func_001001D0` | `SetVTLBRefillHandler` | 0x001001D0 |
| 0x001001E0 | `func_001001E0` | `SetVCommonHandler` | 0x001001E0 |
| 0x001001F0 | `func_001001F0` | `SetVInterruptHandler` | 0x001001F0 |
| 0x00100220 | `func_00100220` | `RemoveIntcHandler` | 0x00100220 |
| 0x00100250 | `func_00100250` | `RemoveDmacHandler` | 0x00100250 |
| 0x00100260 | `func_00100260` | `_EnableIntc` | 0x00100260 |
| 0x00100270 | `func_00100270` | `_DisableIntc` | 0x00100270 |
| 0x00100280 | `func_00100280` | `_EnableDmac` | 0x00100280 |
| 0x00100290 | `func_00100290` | `_DisableDmac` | 0x00100290 |
| 0x001002A0 | `func_001002A0` | `SetAlarm` | 0x001002A0 |
| 0x001002B0 | `func_001002B0` | `ReleaseAlarm` | 0x001002B0 |
| 0x001002C0 | `func_001002C0` | `_iEnableIntc` | 0x001002C0 |
| 0x001002D0 | `func_001002D0` | `_iDisableIntc` | 0x001002D0 |
| 0x001002E0 | `func_001002E0` | `_iEnableDmac` | 0x001002E0 |
| 0x001002F0 | `func_001002F0` | `_iDisableDmac` | 0x001002F0 |
| 0x00100300 | `func_00100300` | `iSetAlarm` | 0x00100300 |
| 0x00100310 | `func_00100310` | `iReleaseAlarm` | 0x00100310 |
| 0x00100320 | `func_00100320` | `CreateThread` | 0x00100320 |
| 0x00100330 | `func_00100330` | `DeleteThread` | 0x00100330 |
| 0x00100340 | `func_00100340` | `StartThread` | 0x00100340 |
| 0x00100350 | `func_00100350` | `ExitThread` | 0x00100350 |
| 0x00100360 | `func_00100360` | `ExitDeleteThread` | 0x00100360 |
| 0x00100370 | `func_00100370` | `TerminateThread` | 0x00100370 |
| 0x00100380 | `func_00100380` | `iTerminateThread` | 0x00100380 |
| 0x00100390 | `func_00100390` | `DisableDispatchThread` | 0x00100390 |
| 0x001003A0 | `func_001003A0` | `EnableDispatchThread` | 0x001003A0 |
| 0x001003B0 | `func_001003B0` | `ChangeThreadPriority` | 0x001003B0 |
| 0x001003C0 | `func_001003C0` | `iChangeThreadPriority` | 0x001003C0 |
| 0x001003D0 | `func_001003D0` | `RotateThreadReadyQueue` | 0x001003D0 |
| 0x001003E0 | `func_001003E0` | `_iRotateThreadReadyQueue` | 0x001003E0 |
| 0x001003F0 | `func_001003F0` | `ReleaseWaitThread` | 0x001003F0 |
| 0x00100400 | `func_00100400` | `iReleaseWaitThread` | 0x00100400 |
| 0x00100410 | `func_00100410` | `GetThreadId` | 0x00100410 |
| 0x00100420 | `func_00100420` | `ReferThreadStatus` | 0x00100420 |
| 0x00100430 | `func_00100430` | `iReferThreadStatus` | 0x00100430 |
| 0x00100440 | `func_00100440` | `SleepThread` | 0x00100440 |
| 0x00100450 | `func_00100450` | `WakeupThread` | 0x00100450 |
| 0x00100460 | `func_00100460` | `_iWakeupThread` | 0x00100460 |
| 0x00100470 | `func_00100470` | `CancelWakeupThread` | 0x00100470 |
| 0x00100480 | `func_00100480` | `iCancelWakeupThread` | 0x00100480 |
| 0x00100490 | `func_00100490` | `SuspendThread` | 0x00100490 |
| 0x001004A0 | `func_001004A0` | `_iSuspendThread` | 0x001004A0 |
| 0x001004B0 | `func_001004B0` | `ResumeThread` | 0x001004B0 |
| 0x001004C0 | `func_001004C0` | `iResumeThread` | 0x001004C0 |
| 0x001004D0 | `func_001004D0` | `JoinThread` | 0x001004D0 |
| 0x001004E0 | `func_001004E0` | `RFU060` | 0x001004E0 |
| 0x001004F0 | `func_001004F0` | `RFU061` | 0x001004F0 |
| 0x00100500 | `func_00100500` | `EndOfHeap` | 0x00100500 |
| 0x00100510 | `func_00100510` | `RFU063` | 0x00100510 |
| 0x00100520 | `func_00100520` | `CreateSema` | 0x00100520 |
| 0x00100530 | `func_00100530` | `DeleteSema` | 0x00100530 |
| 0x00100540 | `func_00100540` | `SignalSema` | 0x00100540 |
| 0x00100550 | `func_00100550` | `iSignalSema` | 0x00100550 |
| 0x00100560 | `func_00100560` | `WaitSema` | 0x00100560 |
| 0x00100570 | `func_00100570` | `PollSema` | 0x00100570 |
| 0x00100580 | `func_00100580` | `iPollSema` | 0x00100580 |
| 0x00100590 | `func_00100590` | `ReferSemaStatus` | 0x00100590 |
| 0x001005A0 | `func_001005A0` | `iReferSemaStatus` | 0x001005A0 |
| 0x001005B0 | `func_001005B0` | `RFU073` | 0x001005B0 |
| 0x001005C0 | `func_001005C0` | `SetOsdConfigParam` | 0x001005C0 |
| 0x001005D0 | `func_001005D0` | `GetOsdConfigParam` | 0x001005D0 |
| 0x001005E0 | `func_001005E0` | `GetGsHParam` | 0x001005E0 |
| 0x001005F0 | `func_001005F0` | `GetGsVParam` | 0x001005F0 |
| 0x00100600 | `func_00100600` | `SetGsHParam` | 0x00100600 |
| 0x00100610 | `func_00100610` | `SetGsVParam` | 0x00100610 |
| 0x00100620 | `func_00100620` | `RFU080_CreateEventFlag` | 0x00100620 |
| 0x00100630 | `func_00100630` | `RFU081_DeleteEventFlag` | 0x00100630 |
| 0x00100640 | `func_00100640` | `RFU082_SetEventFlag` | 0x00100640 |
| 0x00100650 | `func_00100650` | `RFU083_iSetEventFlag` | 0x00100650 |
| 0x00100660 | `func_00100660` | `RFU084_ClearEventFlag` | 0x00100660 |
| 0x001006C0 | `func_001006C0` | `RFU090_iReferEventFlagStatus` | 0x001006C0 |
| 0x001006E0 | `func_001006E0` | `EnableIntcHandler` | 0x001006E0 |
| 0x001006F0 | `func_001006F0` | `iEnableIntcHandler` | 0x001006F0 |
| 0x00100700 | `func_00100700` | `DisableIntcHandler` | 0x00100700 |
| 0x00100710 | `func_00100710` | `iDisableIntcHandler` | 0x00100710 |
| 0x00100720 | `func_00100720` | `EnableDmacHandler` | 0x00100720 |
| 0x00100730 | `func_00100730` | `iEnableDmacHandler` | 0x00100730 |
| 0x00100740 | `func_00100740` | `DisableDmacHandler` | 0x00100740 |
| 0x00100750 | `func_00100750` | `iDisableDmacHandler` | 0x00100750 |
| 0x00100760 | `func_00100760` | `KSeg0` | 0x00100760 |
| 0x00100770 | `func_00100770` | `EnableCache` | 0x00100770 |
| 0x00100780 | `func_00100780` | `DisableCache` | 0x00100780 |
| 0x00100790 | `func_00100790` | `GetCop0` | 0x00100790 |
| 0x001007A0 | `func_001007A0` | `FlushCache` | 0x001007A0 |
| 0x001007B0 | `func_001007B0` | `CpuConfig` | 0x001007B0 |
| 0x001007C0 | `func_001007C0` | `iGetCop0` | 0x001007C0 |
| 0x001007D0 | `func_001007D0` | `iFlushCache` | 0x001007D0 |
| 0x001007E0 | `func_001007E0` | `iCpuConfig` | 0x001007E0 |
| 0x001007F0 | `func_001007F0` | `sceSifStopDma` | 0x001007F0 |
| 0x00100800 | `func_00100800` | `SetCPUTimerHandler` | 0x00100800 |
| 0x00100810 | `func_00100810` | `SetCPUTimer` | 0x00100810 |
| 0x00100820 | `func_00100820` | `SetOsdConfigParam2` | 0x00100820 |
| 0x00100830 | `func_00100830` | `GetOsdConfigParam2` | 0x00100830 |
| 0x00100840 | `func_00100840` | `GsGetIMR` | 0x00100840 |
| 0x00100850 | `func_00100850` | `iGsGetIMR` | 0x00100850 |
| 0x00100860 | `func_00100860` | `GsPutIMR` | 0x00100860 |
| 0x00100870 | `func_00100870` | `iGsPutIMR` | 0x00100870 |
| 0x00100880 | `func_00100880` | `SetPgifHandler` | 0x00100880 |
| 0x00100890 | `func_00100890` | `SetVSyncFlag` | 0x00100890 |
| 0x001008B0 | `func_001008B0` | `_print` | 0x001008B0 |
| 0x001008C0 | `func_001008C0` | `sceSifDmaStat` | 0x001008C0 |
| 0x001008D0 | `func_001008D0` | `isceSifDmaStat` | 0x001008D0 |
| 0x001008E0 | `func_001008E0` | `sceSifSetDma` | 0x001008E0 |
| 0x001008F0 | `func_001008F0` | `isceSifSetDma` | 0x001008F0 |
| 0x00100900 | `func_00100900` | `sceSifSetDChain` | 0x00100900 |
| 0x00100910 | `func_00100910` | `isceSifSetDChain` | 0x00100910 |
| 0x00100920 | `func_00100920` | `sceSifSetReg` | 0x00100920 |
| 0x00100930 | `func_00100930` | `sceSifGetReg` | 0x00100930 |
| 0x00100940 | `func_00100940` | `ExecOSD` | 0x00100940 |
| 0x00100950 | `func_00100950` | `Deci2Call` | 0x00100950 |
| 0x00100960 | `func_00100960` | `PSMode` | 0x00100960 |
| 0x00100970 | `func_00100970` | `MachineType` | 0x00100970 |
| 0x00100980 | `func_00100980` | `GetMemorySize` | 0x00100980 |
| 0x001009A0 | `func_001009A0` | `InitSysCall` | 0x001009A0 |
| 0x001009E0 | `func_001009E0` | `_InitSys` | 0x001009E0 |
| 0x00100C38 | `func_00100C38` | `Copy` | 0x00100C38 |
| 0x00100C48 | `func_00100C48` | `kCopy` | 0x00100C48 |
| 0x00100C90 | `func_00100C90` | `InitAlarm` | 0x00100C90 |
| 0x00100F18 | `func_00100F18` | `iWakeupThread` | 0x00100F18 |
| 0x00100FB0 | `func_00100FB0` | `iRotateThreadReadyQueue` | 0x00100FB0 |
| 0x00101030 | `func_00101030` | `iSuspendThread` | 0x00101030 |
| 0x001010C8 | `func_001010C8` | `kputchar` | 0x001010C8 |
| 0x001011B0 | `func_001011B0` | `serialPutchar` | 0x001011B0 |
| 0x001011E8 | `func_001011E8` | `ftoi` | 0x001011E8 |
| 0x00101278 | `func_00101278` | `printfloat` | 0x00101278 |
| 0x001013E0 | `func_001013E0` | `_printf` | 0x001013E0 |
| 0x001019A8 | `func_001019A8` | `kprintf` | 0x001019A8 |
| 0x001019E0 | `func_001019E0` | `scePrintf` | 0x001019E0 |
| 0x00101A40 | `func_00101A40` | `DIntr` | 0x00101A40 |
| 0x00101A88 | `func_00101A88` | `EIntr` | 0x00101A88 |
| 0x00101AA0 | `func_00101AA0` | `sceDeci2Open` | 0x00101AA0 |
| 0x00101AE8 | `func_00101AE8` | `sceDeci2Close` | 0x00101AE8 |
| 0x00101B10 | `func_00101B10` | `sceDeci2ReqSend` | 0x00101B10 |
| 0x00101B40 | `func_00101B40` | `sceDeci2Poll` | 0x00101B40 |
| 0x00101B68 | `func_00101B68` | `sceDeci2ExRecv` | 0x00101B68 |
| 0x00101BA0 | `func_00101BA0` | `sceDeci2ExSend` | 0x00101BA0 |
| 0x00101BD8 | `func_00101BD8` | `sceDeci2ExReqSend` | 0x00101BD8 |
| 0x00101C08 | `func_00101C08` | `sceDeci2ExLock` | 0x00101C08 |
| 0x00101C30 | `func_00101C30` | `sceDeci2ExUnLock` | 0x00101C30 |
| 0x00101C58 | `func_00101C58` | `kputs` | 0x00101C58 |
| 0x001023E8 | `func_001023E8` | `Emergency_DestroyAllThread` | 0x00102460 |
| 0x00102488 | `func_00102488` | `movie_abort_check` | 0x00102500 |
| 0x00104498 | `func_00104498` | `GetRootMatrixTransOffsetByDObj` | 0x001046E0 |
| 0x001044F0 | `func_001044F0` | `GetRootMatrixTransOffset` | 0x00104738 |
| 0x001046C8 | `func_001046C8` | `GetProjectionPosOfPlane` | 0x00104910 |
| 0x00104740 | `func_00104740` | `GetProjectionOfPlane` | 0x00104988 |
| 0x001047C0 | `func_001047C0` | `GetProjectionOfPlaneWithKeepAway` | 0x00104A08 |
| 0x00104848 | `func_00104848` | `getInitialInverseMatrix` | 0x00104A90 |
| 0x00104A80 | `func_00104A80` | `ExecKeyInput` | 0x00104CC8 |
| 0x00104D48 | `func_00104D48` | `MatrixDrive_RotMatrixX` | 0x00104F90 |
| 0x00104DC0 | `func_00104DC0` | `MatrixDrive_RotMatrixY` | 0x00105008 |
| 0x00104E38 | `func_00104E38` | `MatrixDrive_RotMatrixZ` | 0x00105080 |
| 0x00104EB0 | `func_00104EB0` | `MatrixDrive_ScaleMatrix` | 0x001050F8 |
| 0x00104EE0 | `func_00104EE0` | `MatrixDrive_TurnViewMatrix` | 0x00105128 |
| 0x00105058 | `func_00105058` | `MatrixDrive_PushMatrixWithNoCopy` | 0x001052A0 |
| 0x00105068 | `func_00105068` | `MatrixDrive_PopMatrix` | 0x001052B0 |
| 0x0010E088 | `func_0010E088` | `SetQuaternionByAxisRotateV` | 0x0010DCC0 |
| 0x0010E0E8 | `func_0010E0E8` | `SetQuaternionByAxisRotateVWithNoRegularize` | 0x0010DD20 |
| 0x0010E148 | `func_0010E148` | `MultiQuaternion` | 0x0010DD80 |
| 0x0010E188 | `func_0010E188` | `DivQuaternion` | 0x0010DDC0 |
| 0x0010E1D0 | `func_0010E1D0` | `GetMatrixFromQuaternionRotElem` | 0x0010DE08 |
| 0x0010E250 | `func_0010E250` | `GetMatrixFromQuaternionPos` | 0x0010DE88 |
| 0x0010E300 | `func_0010E300` | `MultiMatrixByQuaternion` | 0x0010DF38 |
| 0x0010E348 | `func_0010E348` | `GetMirrorQuaternion` | 0x0010DF80 |
| 0x0010E628 | `func_0010E628` | `RotQuaternionEAX` | 0x0010E260 |
| 0x0010ED30 | `func_0010ED30` | `GetTableCos` | 0x0010E968 |
| 0x0010ED88 | `func_0010ED88` | `InitTableSin` | 0x0010E9C0 |
| 0x0010EE60 | `func_0010EE60` | `GetTableArcSin` | 0x0010EA98 |
| 0x0010EEF0 | `func_0010EEF0` | `GetTableArcCos` | 0x0010EB28 |
| 0x0010EF98 | `func_0010EF98` | `GetTableArcTan2` | 0x0010EBD0 |
| 0x0010EFF8 | `func_0010EFF8` | `p2o_HideDispVU1` | 0x0010EC30 |
| 0x0010F058 | `func_0010F058` | `p2o_TransMicroProgram` | 0x0010EC90 |
| 0x0010FB08 | `func_0010FB08` | `gif_EndPacketPath1` | 0x0010F7E0 |
| 0x0010FEC8 | `func_0010FEC8` | `gif_MakeSpriteOffset` | 0x0010FBA0 |
| 0x00110060 | `func_00110060` | `gif_MakeSpriteWithStrip` | 0x0010FD38 |
| 0x001102C8 | `func_001102C8` | `gif_PointOffset` | 0x0010FFA0 |
| 0x001103F0 | `func_001103F0` | `gif_Line` | 0x001100C8 |
| 0x00110580 | `func_00110580` | `gif_Sprite` | 0x00110258 |
| 0x00118048 | `func_00118048` | `_Sqrt` | 0x001194E8 |
| 0x001180C0 | `func_001180C0` | `_PopCurrentMatrix` | 0x00119560 |
| 0x001180D8 | `func_001180D8` | `_TransCurrentMatrix` | 0x00119578 |
| 0x001180F8 | `func_001180F8` | `_SetTransCurrentMatrix` | 0x00119598 |
| 0x00118118 | `func_00118118` | `_RotCurrentMatrixX` | 0x001195B8 |
| 0x001188B8 | `func_001188B8` | `_InterVector` | 0x00119C48 |
| 0x001188E0 | `func_001188E0` | `_InterVectorXYZ` | 0x00119C70 |
| 0x00118908 | `func_00118908` | `_GetNorm` | 0x00119C98 |
| 0x00118938 | `func_00118938` | `_GetLength` | 0x00119CC8 |
| 0x00118970 | `func_00118970` | `_GetLengthXY` | 0x00119D00 |
| 0x001189A0 | `func_001189A0` | `_GetLengthXZ` | 0x00119D30 |
| 0x001189D0 | `func_001189D0` | `_CopyMatrix` | 0x00119D60 |
| 0x001189F8 | `func_001189F8` | `_MulMatrix` | 0x00119D88 |
| 0x00118A70 | `func_00118A70` | `_ApplyMatrix` | 0x00119E00 |
| 0x00118AA0 | `func_00118AA0` | `_UnitMatrix` | 0x00119E30 |
| 0x00118AC8 | `func_00118AC8` | `_UnitRotation` | 0x00119E58 |
| 0x00118AF0 | `func_00118AF0` | `_TransposeMatrix` | 0x00119E80 |
| 0x00118B38 | `func_00118B38` | `_InversMatrix` | 0x00119EC8 |
| 0x00118BA8 | `func_00118BA8` | `_ScaleMatrixV` | 0x00119F38 |
| 0x00118C40 | `func_00118C40` | `_SetCameraMatrix` | 0x00119FD0 |
| 0x00118E38 | `func_00118E38` | `_MakeLightColorMatrix` | 0x0011A1D8 |
| 0x00118E70 | `func_00118E70` | `_InitRandom` | 0x0011A210 |
| 0x0011B618 | `func_0011B618` | `pac_getTextureInfo` | 0x0011C9B8 |
| 0x0011B788 | `func_0011B788` | `pac_makeShapeTable` | 0x0011CB28 |
| 0x0011C328 | `func_0011C328` | `pac_Dump` | 0x0011D728 |
| 0x0012FC48 | `func_0012FC48` | `tex_GetTextureNo` | 0x00131A58 |
| 0x0012FD10 | `func_0012FD10` | `tex_SetSamplingType` | 0x00131B20 |
| 0x0012FD50 | `func_0012FD50` | `tex_GetVramFreeAddress` | 0x00131B60 |
| 0x0012FEC8 | `func_0012FEC8` | `tex_SetUVScroll` | 0x00131E90 |
| 0x00130000 | `func_00130000` | `tex_Init` | 0x00131FC8 |
| 0x001351E0 | `func_001351E0` | `inflate` | 0x00137770 |
| 0x00137DB8 | `func_00137DB8` | `iosMcSaveProductBlock` | 0x0013A278 |
| 0x00137E00 | `func_00137E00` | `iosMcLoadProductBlock` | 0x0013A2C0 |
| 0x00137E48 | `func_00137E48` | `iosMcSaveGameBlock` | 0x0013A308 |
| 0x00137E90 | `func_00137E90` | `iosMcLoadGameBlock` | 0x0013A350 |
| 0x00137ED8 | `func_00137ED8` | `iosMcChdirProduct` | 0x0013A398 |
| 0x00137F20 | `func_00137F20` | `iosMcGetBlockSaveInfo` | 0x0013A3E0 |
| 0x0013D388 | `func_0013D388` | `iosThreadGetPri` | 0x0013FC88 |
| 0x0013D5E8 | `func_0013D5E8` | `iosSemaWait` | 0x0013FEE8 |
| 0x0013D648 | `func_0013D648` | `iosSemaSignal` | 0x0013FF48 |
| 0x0013E7E0 | `func_0013E7E0` | `isysGObjGetExist_next` | 0x001410E0 |
| 0x0013F3A8 | `func_0013F3A8` | `isysGObjProcRemoveAll` | 0x00141CA8 |
| 0x0013F3E0 | `func_0013F3E0` | `isysGObjProcThreadSleep` | 0x00141CE0 |
| 0x0013F418 | `func_0013F418` | `isysGObjProcAddSGOppArg` | 0x00141D18 |
| 0x0013F448 | `func_0013F448` | `isysGObjProcActivePtr` | 0x00141D48 |
| 0x00149D00 | `func_00149D00` | `_ACTGame_GetParamF` | 0x0014DEE8 |
| 0x0014A008 | `func_0014A008` | `ActGame_GetOrientQ` | 0x0014E1F8 |
| 0x0014A0B0 | `func_0014A0B0` | `_GetRootObjectOrient` | 0x0014E2A0 |
| 0x0014A150 | `func_0014A150` | `ACTCheckCollis_VIEW` | 0x0014E4E0 |
| 0x0014A250 | `func_0014A250` | `ACTCheckViewClDetail` | 0x0014E5E0 |
| 0x0014A4D0 | `func_0014A4D0` | `GetGirlPositionAtThisStage` | 0x0014E860 |
| 0x001668B0 | `func_001668B0` | `CompareAttribute` | 0x0016DA90 |
| 0x00166910 | `func_00166910` | `GetWallGlobalInfo` | 0x0016DAF0 |
| 0x001669D0 | `func_001669D0` | `GetDistanceFromPlane` | 0x0016DBB0 |
| 0x00166A00 | `func_00166A00` | `GetYDistanceFromPlane` | 0x0016DBE0 |
| 0x00166A48 | `func_00166A48` | `GetYProjectionOfPlane` | 0x0016DC28 |
| 0x00166A88 | `func_00166A88` | `ResetCollisionPC` | 0x0016DC68 |
| 0x00166AB8 | `func_00166AB8` | `PositionOfExit` | 0x0016DC98 |
| 0x00166AF8 | `func_00166AF8` | `GetGlobalWallPlane` | 0x0016DCD8 |
| 0x00166BD8 | `func_00166BD8` | `_clipWDebug` | 0x0016DDB8 |
| 0x00166D00 | `func_00166D00` | `_clipW` | 0x0016DEE0 |
| 0x00166E50 | `func_00166E50` | `_clipWE` | 0x0016E030 |
| 0x00166FC0 | `func_00166FC0` | `_clipWEField` | 0x0016E1A0 |
| 0x00167120 | `func_00167120` | `_clipWR` | 0x0016E300 |
| 0x00167270 | `func_00167270` | `_clipWField` | 0x0016E450 |
| 0x001673B0 | `func_001673B0` | `_clipWDitchHangWalkStop` | 0x0016E590 |
| 0x001674F0 | `func_001674F0` | `_clipWWaveForce` | 0x0016E6D0 |
| 0x00167630 | `func_00167630` | `_clipWBoxStop` | 0x0016E810 |
| 0x00167798 | `func_00167798` | `_clipWAdjustPos` | 0x0016E978 |
| 0x001678D8 | `func_001678D8` | `_clipF` | 0x0016EAB8 |
| 0x00167A00 | `func_00167A00` | `_clipFE` | 0x0016EBE0 |
| 0x00167B48 | `func_00167B48` | `_clipFIH` | 0x0016ED28 |
| 0x00167C88 | `func_00167C88` | `_clipFR` | 0x0016EE68 |
| 0x00167F60 | `func_00167F60` | `ClipWallRD` | 0x0016F140 |
| 0x00167F88 | `func_00167F88` | `ClipWallVector` | 0x0016F168 |
| 0x00167FE8 | `func_00167FE8` | `MapCollisionData` | 0x0016F1C8 |
| 0x00168150 | `func_00168150` | `fzMagnitude2fv` | 0x0016F330 |
| 0x001681E0 | `func_001681E0` | `fzMagnitudeByLine` | 0x0016F3C0 |
| 0x0017A008 | `func_0017A008` | `scpWakeupEnemyOne` | 0x001835A8 |
| 0x0017A040 | `func_0017A040` | `scpSleepEnemyOne` | 0x001835E0 |
| 0x0017A158 | `func_0017A158` | `scpDispOffAllWithKind` | 0x00183700 |
| 0x0017A220 | `func_0017A220` | `scpDisActivateAllWithKind` | 0x001837C8 |
| 0x0017BD00 | `func_0017BD00` | `scpIsHangChainOptional` | 0x00185468 |
| 0x0017BD40 | `func_0017BD40` | `scpBornSpider` | 0x001854A8 |
| 0x0017BF50 | `func_0017BF50` | `scpWakeupItemWithBoundary` | 0x001856F0 |
| 0x0017C130 | `func_0017C130` | `scpTransGObj` | 0x001858E8 |
| 0x0017C1B0 | `func_0017C1B0` | `scpExplodeSecretItem` | 0x00185968 |
| 0x0017DA68 | `func_0017DA68` | `actConte13Jimaku` | 0x001872F8 |
| 0x00186198 | `func_00186198` | `ChaseCamera` | 0x00190780 |
| 0x00186330 | `func_00186330` | `CameraMove` | 0x00190918 |
| 0x00188588 | `func_00188588` | `GetCameraGroupFromGObj` | 0x00192B70 |
| 0x00188888 | `func_00188888` | `MakeCameraSetBinary` | 0x00192E70 |
| 0x0018A0D8 | `func_0018A0D8` | `CameraSetMode` | 0x001949F8 |
| 0x0018A0F0 | `func_0018A0F0` | `CameraGetOtherObjOffset` | 0x00194A10 |
| 0x0018A3A0 | `func_0018A3A0` | `InsertCamera_isEnable` | 0x00194E68 |
| 0x0018A3B0 | `func_0018A3B0` | `CameraSetCameraPosition` | 0x00194E78 |
| 0x0018E0E0 | `func_0018E0E0` | `chain_sub_simulate` | 0x00198C20 |
| 0x0018E2B8 | `func_0018E2B8` | `chain_sub_pendulum` | 0x00198DF8 |
| 0x00191E30 | `func_00191E30` | `_GetDirection` | 0x0019CB70 |
| 0x00191F18 | `func_00191F18` | `_RotGVF` | 0x0019CC58 |
| 0x00191FD0 | `func_00191FD0` | `_OrientXZGV` | 0x0019CD10 |
| 0x001920A8 | `func_001920A8` | `SwapGV` | 0x0019CDE8 |
| 0x001920F0 | `func_001920F0` | `GetCorrectDistance` | 0x0019CE30 |
| 0x00192160 | `func_00192160` | `RoundDegGV` | 0x0019CEA0 |
| 0x00192628 | `func_00192628` | `InitHandCameraCorrect` | 0x0019D590 |
| 0x00192A38 | `func_00192A38` | `_IsInScreen2` | 0x0019DFF0 |
| 0x00195B88 | `func_00195B88` | `m33_to_quat` | 0x001A1200 |
| 0x00196D70 | `func_00196D70` | `DrawLightningN` | 0x001A23E8 |
| 0x0019B730 | `func_0019B730` | `videoDecDelete` | 0x001A6F90 |
| 0x0019B790 | `func_0019B790` | `videoDecAbort` | 0x001A6FF0 |
| 0x0019B8E0 | `func_0019B8E0` | `mpegTS` | 0x001A7140 |
| 0x001A4C58 | `func_001A4C58` | `debug_SelectCsvWindowVal` | 0x001B0128 |
| 0x001A4DC0 | `func_001A4DC0` | `getLineBuffer` | 0x001B0290 |
| 0x001A5390 | `func_001A5390` | `debug_mcRetErrCheck` | 0x001B0860 |
| 0x001A5670 | `func_001A5670` | `debug_mcSaveMainBlock` | 0x001B0B40 |
| 0x001A5A90 | `func_001A5A90` | `debug_mcDeleteFile` | 0x001B0F68 |
| 0x001A6128 | `func_001A6128` | `debug_SESlotDisp` | 0x001B1600 |
| 0x001A6508 | `func_001A6508` | `debug_DispBox` | 0x001B19E0 |
| 0x001A6908 | `func_001A6908` | `debug_DispBall` | 0x001B1DE0 |
| 0x001A7350 | `func_001A7350` | `debug_GetTimerSec` | 0x001B2828 |
| 0x001A7420 | `func_001A7420` | `debug_GetTimerCount` | 0x001B28F8 |
| 0x001A7480 | `func_001A7480` | `debug_ClearFontWindow` | 0x001B2958 |
| 0x001A74C0 | `func_001A74C0` | `debug_SetBar` | 0x001B2998 |
| 0x001A7578 | `func_001A7578` | `debug_SetBar2` | 0x001B2A50 |
| 0x001A7630 | `func_001A7630` | `debug_ResetBar` | 0x001B2B08 |
| 0x001A77A8 | `func_001A77A8` | `debug_DispMatrix` | 0x001B2C80 |
| 0x001A7A88 | `func_001A7A88` | `debugSceOpen` | 0x001B2F60 |
| 0x001A7AE8 | `func_001A7AE8` | `debugSceClose` | 0x001B2FC0 |
| 0x001A7B18 | `func_001A7B18` | `debugSceCloseFdNew` | 0x001B2FF0 |
| 0x001A7B58 | `func_001A7B58` | `debugCdvdLoadInfoSegInit` | 0x001B3030 |
| 0x001A7BA0 | `func_001A7BA0` | `debugCdvdLoadInfoSegAdd` | 0x001B3078 |
| 0x001A7BD0 | `func_001A7BD0` | `debugCdvdLoadInfoSegCls` | 0x001B30A8 |
| 0x001A7BF8 | `func_001A7BF8` | `gsResetFunc` | 0x001B30D0 |
| 0x001A7C38 | `func_001A7C38` | `debug_SaveStartStageFile` | 0x001B3128 |
| 0x001A7CE8 | `func_001A7CE8` | `_debug_SelectCsvWindow` | 0x001B31D8 |
| 0x001A7F90 | `func_001A7F90` | `debug_SelectCsvWindowWithLineColor` | 0x001B3480 |
| 0x001A98E0 | `func_001A98E0` | `baseFunc` | 0x001B4E30 |
| 0x001A99D0 | `func_001A99D0` | `syncGS` | 0x001B4F20 |
| 0x001AA268 | `func_001AA268` | `display` | 0x001B57B8 |
| 0x001AAD88 | `func_001AAD88` | `SetPrimColor` | 0x001B62D8 |
| 0x001AAE80 | `func_001AAE80` | `SetPrimColorTex` | 0x001B63D0 |
| 0x001AB120 | `func_001AB120` | `debug_TargetGObj_Func` | 0x001B6670 |
| 0x001AB948 | `func_001AB948` | `gamesysObjInfoStageInitFlagCls` | 0x001B6F48 |
| 0x001AB9B8 | `func_001AB9B8` | `gamesysObjInfoPosSetStage` | 0x001B6FB8 |
| 0x001AB9F8 | `func_001AB9F8` | `gamesysObjInfoUniqDataSet` | 0x001B6FF8 |
| 0x001ABE38 | `func_001ABE38` | `gamesysMemoryHandlerRead` | 0x001B7438 |
| 0x001ABE88 | `func_001ABE88` | `gamesysMemorySave` | 0x001B7488 |
| 0x001AC5E8 | `func_001AC5E8` | `disp_memory_partition` | 0x001B7BE8 |
| 0x001B2EF8 | `func_001B2EF8` | `PSH_POSITIVE_OR_NEGATIVE` | 0x001BEC40 |
| 0x001BE168 | `func_001BE168` | `getAlign` | 0x001CAE70 |
| 0x001C6148 | `func_001C6148` | `scaleVectorXZ` | 0x001D4058 |
| 0x001C6168 | `func_001C6168` | `tensionMoveNoReduce` | 0x001D4078 |
| 0x001C61C0 | `func_001C61C0` | `tensionMove` | 0x001D40D0 |
| 0x001C6228 | `func_001C6228` | `getCrossPoint` | 0x001D4138 |
| 0x001C62E8 | `func_001C62E8` | `checkOverThePlane` | 0x001D41F8 |
| 0x001C6328 | `func_001C6328` | `checkFrontAcross` | 0x001D4238 |
| 0x001C6398 | `func_001C6398` | `LockZAnimation` | 0x001D42A8 |
| 0x001C6420 | `func_001C6420` | `getCloth4D_planeClip` | 0x001D4330 |
| 0x001C6548 | `func_001C6548` | `InitClothTestGeo` | 0x001D4458 |
| 0x001D2060 | `func_001D2060` | `InitMotionFile` | 0x001E1310 |
| 0x001D2140 | `func_001D2140` | `AddMotionMemorySize` | 0x001E13F0 |
| 0x001D2168 | `func_001D2168` | `GetMotionMemorySize` | 0x001E1418 |
| 0x001D5928 | `func_001D5928` | `getFinalMatrix` | 0x001E4E18 |
| 0x001D5AF0 | `func_001D5AF0` | `getFinalMatrixWithNaturalGeometry` | 0x001E4FE0 |
| 0x001D5C50 | `func_001D5C50` | `_calcNaturalGeometry` | 0x001E5140 |
| 0x001DA980 | `func_001DA980` | `avoidSideAdjustWall` | 0x001E9FD8 |
| 0x001DDAB8 | `func_001DDAB8` | `dispSkelton` | 0x001ED210 |
| 0x001E6040 | `func_001E6040` | `GetParticleLoopFlag` | 0x001F56B0 |
| 0x001E9750 | `func_001E9750` | `blendWork0ToWork1` | 0x001FA008 |
| 0x001E9888 | `func_001E9888` | `parallelAddFeedBackAreaToWork0` | 0x001FA140 |
| 0x001E9B38 | `func_001E9B38` | `blurBlendFeedBackAreaToWork1` | 0x001FA3F0 |
| 0x001EA3C8 | `func_001EA3C8` | `cleanUpFB` | 0x001FACD0 |
| 0x001EA558 | `func_001EA558` | `dispSun` | 0x001FAF28 |
| 0x001ED718 | `func_001ED718` | `InitStormTestGeo` | 0x001FE100 |
| 0x001F76C0 | `func_001F76C0` | `bga_ResetAnimation` | 0x0020AA38 |
| 0x002013B0 | `func_002013B0` | `actWaitCondition` | 0x002148F0 |
| 0x002018E0 | `func_002018E0` | `WayLengthOfPos_Pos` | 0x00214E20 |
| 0x00201AF0 | `func_00201AF0` | `WayPointWithRangeFromPos` | 0x00215030 |
| 0x00202900 | `func_00202900` | `DeleteWayGroup` | 0x002160B8 |
| 0x00202980 | `func_00202980` | `CloseWayGroup` | 0x00216138 |
| 0x00202D68 | `func_00202D68` | `WayBridgeAll_next` | 0x00216520 |
| 0x0020AB98 | `func_0020AB98` | `actStaff2Chk` | 0x0021EE00 |
| 0x00230C70 | `func_00230C70` | `actSt13cSekizoJimakuEff` | 0x0024D030 |
| 0x00238FB0 | `func_00238FB0` | `stageSE10lstrong` | 0x00256838 |
| 0x002390F0 | `func_002390F0` | `stageSE10rstrong` | 0x00256978 |
| 0x002391E8 | `func_002391E8` | `stageSE13arain` | 0x00256A70 |
| 0x00239228 | `func_00239228` | `stageSE13cNoise` | 0x00256AB0 |
| 0x00239250 | `func_00239250` | `stageSE13dterrace` | 0x00256AD8 |
| 0x00239290 | `func_00239290` | `stageSE13dstrong` | 0x00256B18 |
| 0x00239348 | `func_00239348` | `stageSE17astrong` | 0x00256BD0 |
| 0x002393A8 | `func_002393A8` | `stageSE18awind` | 0x00256C30 |
| 0x00239438 | `func_00239438` | `stageSE17brain` | 0x00256CC0 |
| 0x0023A850 | `func_0023A850` | `audioDecPause` | 0x00257FC0 |
| 0x0023AC90 | `func_0023AC90` | `setImageSize` | 0x002583E8 |
| 0x0023ACA0 | `func_0023ACA0` | `sendDispEnv` | 0x002583F8 |
| 0x0023B310 | `func_0023B310` | `dispSwitch` | 0x00258948 |
| 0x0023B348 | `func_0023B348` | `vblankHandler` | 0x00258980 |
| 0x0023B920 | `func_0023B920` | `setXYZ2` | 0x00258F58 |
| 0x0023B970 | `func_0023B970` | `setFRAME_1` | 0x00258FA8 |
| 0x0023B9D0 | `func_0023B9D0` | `setTEST_1` | 0x00259008 |
| 0x0023BA60 | `func_0023BA60` | `setSCISSOR_1` | 0x00259098 |
| 0x0023BAB8 | `func_0023BAB8` | `setXYOFFSET_1` | 0x002590F0 |
| 0x0023BAF0 | `func_0023BAF0` | `setPRMODECONT` | 0x00259128 |
| 0x0023BB20 | `func_0023BB20` | `setPRMODE` | 0x00259158 |
| 0x0023C1D8 | `func_0023C1D8` | `viBufBeginPut` | 0x00259810 |
| 0x0023CF90 | `func_0023CF90` | `viBufPutTs` | 0x0025A5C8 |
| 0x0023DF20 | `func_0023DF20` | `FreePObj` | 0x0025B558 |
| 0x0023DF40 | `func_0023DF40` | `DrawVObj` | 0x0025B578 |
| 0x0023E008 | `func_0023E008` | `SetVObjRT` | 0x0025B640 |
| 0x0023E048 | `func_0023E048` | `sceGsResetGraph` | 0x0025B680 |
| 0x0023E168 | `func_0023E168` | `sceGsResetPath` | 0x0025B7A0 |
| 0x0023E440 | `func_0023E440` | `sceGsPutDispEnv` | 0x0025BA78 |
| 0x0023E500 | `func_0023E500` | `sceGsSetDefDrawEnv` | 0x0025BB38 |
| 0x0023E6E8 | `func_0023E6E8` | `sceGsPutDrawEnv` | 0x0025BD20 |
| 0x0023E7D0 | `func_0023E7D0` | `sceGsSetDefDBuff` | 0x0025BE08 |
| 0x0023EA68 | `func_0023EA68` | `sceGsSwapDBuff` | 0x0025C0A0 |
| 0x0023EAC8 | `func_0023EAC8` | `sceGsSyncV` | 0x0025C100 |
| 0x0023EB60 | `func_0023EB60` | `sceGsSyncPath` | 0x0025C198 |
| 0x0023EE78 | `func_0023EE78` | `sceGsSetDefTexEnv` | 0x0025C4B0 |
| 0x0023EF88 | `func_0023EF88` | `sceGsSetDefAlphaEnv` | 0x0025C5C0 |
| 0x0023EFE8 | `func_0023EFE8` | `sceGsSetDefLoadImage` | 0x0025C620 |
| 0x0023F1D0 | `func_0023F1D0` | `sceGsSetDefStoreImage` | 0x0025C808 |
| 0x0023F310 | `func_0023F310` | `sceGsExecLoadImage` | 0x0025C948 |
| 0x0023F490 | `func_0023F490` | `sceGsExecStoreImage` | 0x0025CAC8 |
| 0x0023FB20 | `func_0023FB20` | `sceGsPutIMR` | 0x0025D158 |
| 0x0023FB60 | `func_0023FB60` | `sceGsSetHalfOffset` | 0x0025D198 |
| 0x0023FC08 | `func_0023FC08` | `sceGszbufaddr` | 0x0025D240 |
| 0x0023FCD0 | `func_0023FCD0` | `sceGsSetDefClear` | 0x0025D308 |
| 0x0023FDD8 | `func_0023FDD8` | `sceVu0ApplyMatrix` | 0x0025D410 |
| 0x0023FE50 | `func_0023FE50` | `sceVu0OuterProduct` | 0x0025D488 |
| 0x0023FE70 | `func_0023FE70` | `sceVu0InnerProduct` | 0x0025D4A8 |
| 0x0023FE98 | `func_0023FE98` | `sceVu0Normalize` | 0x0025D4D0 |
| 0x0023FED0 | `func_0023FED0` | `sceVu0TransposeMatrix` | 0x0025D508 |
| 0x0023FF18 | `func_0023FF18` | `sceVu0InversMatrix` | 0x0025D550 |
| 0x0023FF88 | `func_0023FF88` | `sceVu0DivVector` | 0x0025D5C0 |
| 0x0023FFA8 | `func_0023FFA8` | `sceVu0DivVectorXYZ` | 0x0025D5E0 |
| 0x0023FFC8 | `func_0023FFC8` | `sceVu0InterVector` | 0x0025D600 |
| 0x0023FFF0 | `func_0023FFF0` | `sceVu0AddVector` | 0x0025D628 |
| 0x00240008 | `func_00240008` | `sceVu0SubVector` | 0x0025D640 |
| 0x00240020 | `func_00240020` | `sceVu0MulVector` | 0x0025D658 |
| 0x00240038 | `func_00240038` | `sceVu0ScaleVector` | 0x0025D670 |
| 0x00240050 | `func_00240050` | `sceVu0TransMatrix` | 0x0025D688 |
| 0x00240080 | `func_00240080` | `sceVu0CopyVector` | 0x0025D6B8 |
| 0x00240090 | `func_00240090` | `sceVu0CopyMatrix` | 0x0025D6C8 |
| 0x002400B8 | `func_002400B8` | `sceVu0FTOI4Vector` | 0x0025D6F0 |
| 0x002400C8 | `func_002400C8` | `sceVu0FTOI0Vector` | 0x0025D700 |
| 0x002400D8 | `func_002400D8` | `sceVu0ITOF4Vector` | 0x0025D710 |
| 0x002400E8 | `func_002400E8` | `sceVu0ITOF0Vector` | 0x0025D720 |
| 0x002400F8 | `func_002400F8` | `sceVu0UnitMatrix` | 0x0025D730 |
| 0x00240390 | `func_00240390` | `sceVu0RotMatrix` | 0x0025D9C8 |
| 0x002403E0 | `func_002403E0` | `sceVu0ClampVector` | 0x0025DA18 |
| 0x00240408 | `func_00240408` | `sceVu0CameraMatrix` | 0x0025DA40 |
| 0x002404B8 | `func_002404B8` | `sceVu0NormalLightMatrix` | 0x0025DAF0 |
| 0x00240578 | `func_00240578` | `sceVu0LightColorMatrix` | 0x0025DBB0 |
| 0x002405E0 | `func_002405E0` | `sceVu0ViewScreenMatrix` | 0x0025DC18 |
| 0x002406E8 | `func_002406E8` | `sceVu0DropShadowMatrix` | 0x0025DD20 |
| 0x00240918 | `func_00240918` | `sceVu0CopyVectorXYZ` | 0x0025DF50 |
| 0x00240938 | `func_00240938` | `sceVu0InterVectorXYZ` | 0x0025DF70 |
| 0x00240968 | `func_00240968` | `sceVu0ScaleVectorXYZ` | 0x0025DFA0 |
| 0x00240980 | `func_00240980` | `sceVu0ClipScreen` | 0x0025DFB8 |
| 0x002409C8 | `func_002409C8` | `sceVu0ClipScreen3` | 0x0025E000 |
| 0x00240AB8 | `func_00240AB8` | `sceVpu0Reset` | 0x0025E0F0 |
| 0x00240B18 | `func_00240B18` | `memclr` | 0x0025E150 |
| 0x00240B50 | `func_00240B50` | `sceDmaGetChan` | 0x0025E188 |
| 0x00240B78 | `func_00240B78` | `sceDmaReset` | 0x0025E1B0 |
| 0x00240C58 | `func_00240C58` | `sceDmaDebug` | 0x0025E290 |
| 0x00240E40 | `func_00240E40` | `sceDmaGetEnv` | 0x0025E478 |
| 0x00240E78 | `func_00240E78` | `sceDmaPutStallAddr` | 0x0025E4B0 |
| 0x00240EA0 | `func_00240EA0` | `sceDmaSend` | 0x0025E4D8 |
| 0x00240F78 | `func_00240F78` | `sceDmaSendN` | 0x0025E5B0 |
| 0x00241060 | `func_00241060` | `sceDmaSendI` | 0x0025E698 |
| 0x00241148 | `func_00241148` | `sceDmaRecv` | 0x0025E780 |
| 0x00241210 | `func_00241210` | `sceDmaRecvN` | 0x0025E848 |
| 0x00241300 | `func_00241300` | `sceDmaRecvI` | 0x0025E938 |
| 0x002413F0 | `func_002413F0` | `sceDmaSync` | 0x0025EA28 |
| 0x002414B8 | `func_002414B8` | `sceDmaWatch` | 0x0025EAF0 |
| 0x002415C8 | `func_002415C8` | `sceVif1PkInit` | 0x0025EC00 |
| 0x002415D8 | `func_002415D8` | `sceVif1PkReset` | 0x0025EC10 |
| 0x002415E8 | `func_002415E8` | `sceVif1PkTerminate` | 0x0025EC20 |
| 0x002416F0 | `func_002416F0` | `sceVif1PkOpenDirectCode` | 0x0025ED28 |
| 0x00241748 | `func_00241748` | `sceVif1PkCloseDirectCode` | 0x0025ED80 |
| 0x00241778 | `func_00241778` | `sceVif1PkOpenGifTag` | 0x0025EDB0 |
| 0x00241790 | `func_00241790` | `sceVif1PkCloseGifTag` | 0x0025EDC8 |
| 0x00241838 | `func_00241838` | `sceVif1PkAlign` | 0x0025EE70 |
| 0x002418B8 | `func_002418B8` | `sceVif1PkAddGsData` | 0x0025EEF0 |
| 0x002418F0 | `func_002418F0` | `VSync` | 0x0025EF28 |
| 0x00241930 | `func_00241930` | `VSync2` | 0x0025EF68 |
| 0x00241990 | `func_00241990` | `write` | 0x0025EFC8 |
| 0x00241A10 | `func_00241A10` | `read` | 0x0025F048 |
| 0x00241AC8 | `func_00241AC8` | `sbrk` | 0x0025F100 |
| 0x00241B80 | `func_00241B80` | `fstat` | 0x0025F1B8 |
| 0x00241BA0 | `func_00241BA0` | `kill` | 0x0025F1D8 |
| 0x00241C18 | `func_00241C18` | `QueueInit` | 0x0025F250 |
| 0x00241C40 | `func_00241C40` | `QueuePeekWriteDone` | 0x0025F278 |
| 0x00241C80 | `func_00241C80` | `QueuePeekReadDone` | 0x0025F2B8 |
| 0x00241CC0 | `func_00241CC0` | `sceTtyHandler` | 0x0025F2F8 |
| 0x00241FA8 | `func_00241FA8` | `sceTtyRead` | 0x0025F5E0 |
| 0x00242078 | `func_00242078` | `sceTtyInit` | 0x0025F6B0 |
| 0x00242138 | `func_00242138` | `sceSifInitRpc` | 0x0025F770 |
| 0x002422D8 | `func_002422D8` | `sceSifExitRpc` | 0x0025F910 |
| 0x00242300 | `func_00242300` | `_sceRpcGetPacket` | 0x0025F938 |
| 0x002423A8 | `func_002423A8` | `_sceRpcFreePacket` | 0x0025F9E0 |
| 0x002423C8 | `func_002423C8` | `_sceRpcGetFPacket` | 0x0025FA00 |
| 0x002423F8 | `func_002423F8` | `_sceRpcGetFPacket2` | 0x0025FA30 |
| 0x00242438 | `func_00242438` | `_request_end` | 0x0025FA70 |
| 0x002424F0 | `func_002424F0` | `_request_rdata` | 0x0025FB28 |
| 0x00242550 | `func_00242550` | `sceSifGetOtherData` | 0x0025FB88 |
| 0x002426A8 | `func_002426A8` | `_search_svdata` | 0x0025FCE0 |
| 0x002426F8 | `func_002426F8` | `_request_bind` | 0x0025FD30 |
| 0x002427A8 | `func_002427A8` | `sceSifBindRpc` | 0x0025FDE0 |
| 0x002428E8 | `func_002428E8` | `_request_call` | 0x0025FF20 |
| 0x00242978 | `func_00242978` | `sceSifCallRpc` | 0x0025FFB0 |
| 0x00242B68 | `func_00242B68` | `sceSifCheckStatRpc` | 0x002601A0 |
| 0x00242BA8 | `func_00242BA8` | `sceSifSetRpcQueue` | 0x002601E0 |
| 0x00242C40 | `func_00242C40` | `sceSifRegisterRpc` | 0x00260278 |
| 0x00242D10 | `func_00242D10` | `sceSifRemoveRpc` | 0x00260348 |
| 0x00242DA8 | `func_00242DA8` | `sceSifRemoveRpcQueue` | 0x002603E0 |
| 0x00242E38 | `func_00242E38` | `sceSifGetNextRequest` | 0x00260470 |
| 0x00242E90 | `func_00242E90` | `sceSifExecRequest` | 0x002604C8 |
| 0x002430F8 | `func_002430F8` | `new_iob` | 0x00260730 |
| 0x002431F0 | `func_002431F0` | `_sceFs_Rcv_Intr` | 0x00260828 |
| 0x002435A8 | `func_002435A8` | `_sceFsSemInit` | 0x00260BE0 |
| 0x002435F8 | `func_002435F8` | `_sceFsWaitS` | 0x00260C30 |
| 0x00243638 | `func_00243638` | `sceFsInit` | 0x00260C70 |
| 0x00243868 | `func_00243868` | `sceFsReset` | 0x00260EA0 |
| 0x002438A0 | `func_002438A0` | `sceOpen` | 0x00260ED8 |
| 0x00243B28 | `func_00243B28` | `sceClose` | 0x00261160 |
| 0x00243EE0 | `func_00243EE0` | `sceRead` | 0x00261518 |
| 0x00244150 | `func_00244150` | `sceWrite` | 0x00261788 |
| 0x00244760 | `func_00244760` | `sceIoctl2` | 0x00261D98 |
| 0x00244938 | `func_00244938` | `_sceCallCode` | 0x00261F70 |
| 0x00244AE0 | `func_00244AE0` | `sceRemove` | 0x00262118 |
| 0x00244B00 | `func_00244B00` | `sceMkdir` | 0x00262138 |
| 0x00244CB0 | `func_00244CB0` | `sceRmdir` | 0x002622E8 |
| 0x00244CD0 | `func_00244CD0` | `sceFormat` | 0x00262308 |
| 0x00244F40 | `func_00244F40` | `sceAddDrv` | 0x00262578 |
| 0x00245060 | `func_00245060` | `sceDelDrv` | 0x00262698 |
| 0x00245080 | `func_00245080` | `sceDopen` | 0x002626B8 |
| 0x00245120 | `func_00245120` | `sceDclose` | 0x00262758 |
| 0x00245288 | `func_00245288` | `sceDread` | 0x002628C0 |
| 0x002453E0 | `func_002453E0` | `sceGetstat` | 0x00262A18 |
| 0x00245580 | `func_00245580` | `sceChstat` | 0x00262BB8 |
| 0x002457C0 | `func_002457C0` | `sceRename` | 0x00262DF8 |
| 0x002459B0 | `func_002459B0` | `sceChdir` | 0x00262FE8 |
| 0x002459D0 | `func_002459D0` | `sceSync` | 0x00263008 |
| 0x00245B68 | `func_00245B68` | `sceMount` | 0x002631A0 |
| 0x00245DD8 | `func_00245DD8` | `sceUmount` | 0x00263410 |
| 0x00246030 | `func_00246030` | `sceDevctl` | 0x00263668 |
| 0x00246260 | `func_00246260` | `sceSymlink` | 0x00263898 |
| 0x00246440 | `func_00246440` | `sceReadlink` | 0x00263A78 |
| 0x00246608 | `func_00246608` | `sceSifInitIopHeap` | 0x00263C40 |
| 0x00246690 | `func_00246690` | `sceSifAllocIopHeap` | 0x00263CC8 |
| 0x00246700 | `func_00246700` | `sceSifFreeIopHeap` | 0x00263D38 |
| 0x00246778 | `func_00246778` | `sceSifLoadIopHeap` | 0x00263DB0 |
| 0x00246868 | `func_00246868` | `_lf_bind` | 0x00263EA0 |
| 0x002469F8 | `func_002469F8` | `sceSifLoadFileReset` | 0x00264030 |
| 0x00246C38 | `func_00246C38` | `sceSifLoadModuleBuffer` | 0x00264270 |
| 0x00246EA0 | `func_00246EA0` | `sceSifLoadModule` | 0x002644D8 |
| 0x00246EC0 | `func_00246EC0` | `sceSifLoadStartModule` | 0x002644F8 |
| 0x00246FE8 | `func_00246FE8` | `sceSifLoadElfPart` | 0x00264620 |
| 0x00247008 | `func_00247008` | `sceSifLoadElf` | 0x00264640 |
| 0x00247030 | `func_00247030` | `sceSifGetIopAddr` | 0x00264668 |
| 0x00247120 | `func_00247120` | `sceSifSetIopAddr` | 0x00264758 |
| 0x00247200 | `func_00247200` | `sceSifResetIop` | 0x00264838 |
| 0x00247330 | `func_00247330` | `sceSifIsAliveIop` | 0x00264968 |
| 0x00247358 | `func_00247358` | `sceSifSyncIop` | 0x00264990 |
| 0x002473A0 | `func_002473A0` | `sceSifRebootIop` | 0x002649D8 |
| 0x002474B0 | `func_002474B0` | `_DumpTLB` | 0x00264AE8 |
| 0x00247548 | `func_00247548` | `kPutTLBEntry` | 0x00264B80 |
| 0x00247608 | `func_00247608` | `kSetTLBEntry` | 0x00264C40 |
| 0x00247650 | `func_00247650` | `kGetTLBEntry` | 0x00264C88 |
| 0x002476A0 | `func_002476A0` | `kProbeTLBEntry` | 0x00264CD8 |
| 0x002476F0 | `func_002476F0` | `kExpandScratchPad` | 0x00264D28 |
| 0x00247820 | `func_00247820` | `SetTLBHandler` | 0x00264E58 |
| 0x00247880 | `func_00247880` | `SetDebugHandler` | 0x00264EB8 |
| 0x00247918 | `func_00247918` | `InitTLBFunctions` | 0x00264F50 |
| 0x00247968 | `func_00247968` | `PutTLBEntry` | 0x00264FA0 |
| 0x00247998 | `func_00247998` | `iSetTLBEntry` | 0x00264FD0 |
| 0x002479B8 | `func_002479B8` | `iGetTLBEntry` | 0x00264FF0 |
| 0x002479C8 | `func_002479C8` | `ProbeTLBEntry` | 0x00265000 |
| 0x00247D80 | `func_00247D80` | `_change_addr` | 0x002653C0 |
| 0x00247DA8 | `func_00247DA8` | `sceSifSetSreg` | 0x002653E8 |
| 0x00248058 | `func_00248058` | `sceSifExitCmd` | 0x00265698 |
| 0x00248090 | `func_00248090` | `sceSifSetCmdBuffer` | 0x002656D0 |
| 0x002480A8 | `func_002480A8` | `sceSifSetSysCmdBuffer` | 0x002656E8 |
| 0x002480C0 | `func_002480C0` | `sceSifAddCmdHandler` | 0x00265700 |
| 0x002480F0 | `func_002480F0` | `sceSifRemoveCmdHandler` | 0x00265730 |
| 0x00248118 | `func_00248118` | `_sceSifSendCmd` | 0x00265758 |
| 0x00248250 | `func_00248250` | `sceSifSendCmd` | 0x00265890 |
| 0x00248290 | `func_00248290` | `isceSifSendCmd` | 0x002658D0 |
| 0x002482D0 | `func_002482D0` | `_sceSifCmdIntrHdlr` | 0x00265910 |
| 0x002484D0 | `func_002484D0` | `sceCdDelayThread` | 0x00265B10 |
| 0x00248538 | `func_00248538` | `sceCdCallback` | 0x00265B78 |
| 0x00248590 | `func_00248590` | `_sceCd_cd_callback` | 0x00265BD0 |
| 0x002487C8 | `func_002487C8` | `_sceCd_cd_read_intr` | 0x00265E08 |
| 0x00248868 | `func_00248868` | `cmd_sem_init` | 0x00265EA8 |
| 0x00248900 | `func_00248900` | `cdvd_exit` | 0x00265F40 |
| 0x00248980 | `func_00248980` | `sceCdPOffCallback` | 0x00265FC0 |
| 0x002489F0 | `func_002489F0` | `_sceCd_Poff_Intr` | 0x00266030 |
| 0x00248A30 | `func_00248A30` | `PowerOffCB` | 0x00266070 |
| 0x00248BB8 | `func_00248BB8` | `sceCdSearchFile` | 0x002661F8 |
| 0x002490C0 | `func_002490C0` | `sceCdSync` | 0x00266700 |
| 0x00249160 | `func_00249160` | `sceCdSyncS` | 0x002667A0 |
| 0x00249340 | `func_00249340` | `sceCdInit` | 0x00266980 |
| 0x00249620 | `func_00249620` | `sceCdDiskReady` | 0x00266C60 |
| 0x00249818 | `func_00249818` | `sceCdMmode` | 0x00266E58 |
| 0x002498E0 | `func_002498E0` | `sceCdRead` | 0x00266F20 |
| 0x00249D48 | `func_00249D48` | `sceCdStInit` | 0x002675F0 |
| 0x00249D78 | `func_00249D78` | `sceCdStStart` | 0x00267620 |
| 0x00249DB0 | `func_00249DB0` | `sceCdStSeekF` | 0x00267658 |
| 0x00249DE0 | `func_00249DE0` | `sceCdStSeek` | 0x00267688 |
| 0x00249E10 | `func_00249E10` | `sceCdStStop` | 0x002676B8 |
| 0x00249E48 | `func_00249E48` | `sceCdStRead` | 0x002676F0 |
| 0x00249FD0 | `func_00249FD0` | `sceCdStPause` | 0x00267878 |
| 0x0024A020 | `func_0024A020` | `sceCdStResume` | 0x002678C8 |
| 0x0024A078 | `func_0024A078` | `sceCdStStat` | 0x00267920 |
| 0x0024A0C0 | `func_0024A0C0` | `sceCdStream` | 0x00267968 |
| 0x0024A228 | `func_0024A228` | `_send_to_iop` | 0x00267AD0 |
| 0x0024A358 | `func_0024A358` | `scePadInit` | 0x00267C00 |
| 0x0024A498 | `func_0024A498` | `scePadInit2` | 0x00267D40 |
| 0x0024A538 | `func_0024A538` | `scePadEnd` | 0x00267DE0 |
| 0x0024A5B8 | `func_0024A5B8` | `scePadPortOpen` | 0x00267E60 |
| 0x0024A7A0 | `func_0024A7A0` | `scePadPortClose` | 0x00268048 |
| 0x0024A858 | `func_0024A858` | `scePadGetDmaStr` | 0x00268100 |
| 0x0024A8B8 | `func_0024A8B8` | `scePadGetFrameCount` | 0x00268160 |
| 0x0024A908 | `func_0024A908` | `scePadRead` | 0x002681B0 |
| 0x0024A988 | `func_0024A988` | `scePadGetState` | 0x00268230 |
| 0x0024AA38 | `func_0024AA38` | `scePadSetReqState` | 0x002682E0 |
| 0x0024AAA0 | `func_0024AAA0` | `scePadGetReqState` | 0x00268348 |
| 0x0024AB28 | `func_0024AB28` | `scePadInfoAct` | 0x002683D0 |
| 0x0024AC48 | `func_0024AC48` | `scePadInfoComb` | 0x002684F0 |
| 0x0024AD68 | `func_0024AD68` | `scePadInfoMode` | 0x00268610 |
| 0x0024AEA0 | `func_0024AEA0` | `scePadSetMainMode` | 0x00268748 |
| 0x0024AF58 | `func_0024AF58` | `scePadSetActDirect` | 0x00268800 |
| 0x0024B010 | `func_0024B010` | `scePadSetActAlign` | 0x002688B8 |
| 0x0024B0E8 | `func_0024B0E8` | `scePadGetButtonMask` | 0x00268990 |
| 0x0024B1A0 | `func_0024B1A0` | `scePadSetButtonInfo` | 0x00268A48 |
| 0x0024B250 | `func_0024B250` | `scePadInfoPressMode` | 0x00268AF8 |
| 0x0024B2B0 | `func_0024B2B0` | `scePadEnterPressMode` | 0x00268B58 |
| 0x0024B308 | `func_0024B308` | `scePadExitPressMode` | 0x00268BB0 |
| 0x0024B360 | `func_0024B360` | `scePadSetVrefParam` | 0x00268C08 |
| 0x0024B430 | `func_0024B430` | `scePadGetPortMax` | 0x00268CD8 |
| 0x0024B498 | `func_0024B498` | `scePadGetSlotMax` | 0x00268D40 |
| 0x0024B500 | `func_0024B500` | `scePadGetModVersion` | 0x00268DA8 |
| 0x0024B568 | `func_0024B568` | `scePadSetWarningLevel` | 0x00268E10 |
| 0x0024B5D0 | `func_0024B5D0` | `sceMcInit` | 0x00268E78 |
| 0x0024B788 | `func_0024B788` | `_lmcGetClientPtr` | 0x00269030 |
| 0x0024BA68 | `func_0024BA68` | `sceMcMkdir` | 0x00269310 |
| 0x0024BC30 | `func_0024BC30` | `mceIntrReadFixAlign` | 0x002694D8 |
| 0x0024BF60 | `func_0024BF60` | `mcHearAlarm` | 0x00269808 |
| 0x0024BF88 | `func_0024BF88` | `mcDelayThread` | 0x00269830 |
| 0x0024BFD0 | `func_0024BFD0` | `sceMcSync` | 0x00269878 |
| 0x0024C0B0 | `func_0024C0B0` | `mceGetInfoApdx` | 0x00269958 |
| 0x0024C108 | `func_0024C108` | `sceMcGetInfo` | 0x002699B0 |
| 0x0024C3E8 | `func_0024C3E8` | `mceStorePwd` | 0x00269C90 |
| 0x0024CD88 | `func_0024CD88` | `_type2id` | 0x0026A630 |
| 0x0024CE10 | `func_0024CE10` | `_id2type` | 0x0026A6B8 |
| 0x0024D010 | `func_0024D010` | `sceMpegDemuxPssRing` | 0x0026A8B8 |
| 0x0024D300 | `func_0024D300` | `sceMpegDemuxPss` | 0x0026ABA8 |
| 0x0024D320 | `func_0024D320` | `sceMpegAddStrCallback` | 0x0026ABC8 |
| 0x0024D418 | `func_0024D418` | `_pack_header` | 0x0026ACC0 |
| 0x0024D568 | `func_0024D568` | `_system_header` | 0x0026AE10 |
| 0x0024D5D8 | `func_0024D5D8` | `_PES_packet` | 0x0026AE80 |
| 0x0024DB60 | `func_0024DB60` | `sceMpegInit` | 0x0026B408 |
| 0x0024DC00 | `func_0024DC00` | `sceMpegCreate` | 0x0026B4A8 |
| 0x0024DE48 | `func_0024DE48` | `sceMpegAddBs` | 0x0026B6F0 |
| 0x0024DE80 | `func_0024DE80` | `sceMpegGetPicture` | 0x0026B728 |
| 0x0024DEC8 | `func_0024DEC8` | `sceMpegGetPictureRAW8` | 0x0026B770 |
| 0x0024DF10 | `func_0024DF10` | `sceMpegGetPictureRAW8xy` | 0x0026B7B8 |
| 0x0024DF60 | `func_0024DF60` | `sceMpegSetDecodeMode` | 0x0026B808 |
| 0x0024DF78 | `func_0024DF78` | `sceMpegGetDecodeMode` | 0x0026B820 |
| 0x0024DF98 | `func_0024DF98` | `sceMpegIsEnd` | 0x0026B840 |
| 0x0024DFA8 | `func_0024DFA8` | `sceMpegIsRefBuffEmpty` | 0x0026B850 |
| 0x0024DFB8 | `func_0024DFB8` | `sceMpegReset` | 0x0026B860 |
| 0x0024DFF8 | `func_0024DFF8` | `sceMpegClearRefBuff` | 0x0026B8A0 |
| 0x0024E060 | `func_0024E060` | `sceMpegAddCallback` | 0x0026B908 |
| 0x0024E088 | `func_0024E088` | `_dispatchMpegCallback` | 0x0026B930 |
| 0x0024E0D8 | `func_0024E0D8` | `_dispatchMpegCbNodata` | 0x0026B980 |
| 0x0024E100 | `func_0024E100` | `sceMpegSetDefaultPtsGap` | 0x0026B9A8 |
| 0x0024E118 | `func_0024E118` | `sceMpegResetDefaultPtsGap` | 0x0026B9C0 |
| 0x0024E128 | `func_0024E128` | `sceMpegSetImageBuff` | 0x0026B9D0 |
| 0x0024E140 | `func_0024E140` | `sceMpegDispWidth` | 0x0026B9E8 |
| 0x0024E150 | `func_0024E150` | `sceMpegDispHeight` | 0x0026B9F8 |
| 0x0024E180 | `func_0024E180` | `sceSetBrokenLink` | 0x0026BA28 |
| 0x0024E190 | `func_0024E190` | `sceSetPtm` | 0x0026BA38 |
| 0x0024E1A8 | `func_0024E1A8` | `_alalcInit` | 0x0026BA50 |
| 0x0024E1C0 | `func_0024E1C0` | `_alalcSetDynamic` | 0x0026BA68 |
| 0x0024E1D0 | `func_0024E1D0` | `_alalcFree` | 0x0026BA78 |
| 0x0024E1E0 | `func_0024E1E0` | `_alalcAlloc` | 0x0026BA88 |
| 0x0024E248 | `func_0024E248` | `_alalcRest` | 0x0026BAF0 |
| 0x0024E260 | `func_0024E260` | `_getpic` | 0x0026BB08 |
| 0x0024E3E8 | `func_0024E3E8` | `_decodeOrSkipFrame` | 0x0026BC90 |
| 0x0024E510 | `func_0024E510` | `_decodeOrSkip` | 0x0026BDB8 |
| 0x0024E550 | `func_0024E550` | `_decodeOrSkipField` | 0x0026BDF8 |
| 0x0024E6C0 | `func_0024E6C0` | `_sceMpegFlush` | 0x0026BF68 |
| 0x0024E730 | `func_0024E730` | `_initSeqAgain` | 0x0026BFD8 |
| 0x0024E740 | `func_0024E740` | `_lastFrame` | 0x0026BFE8 |
| 0x0024E7C8 | `func_0024E7C8` | `_clearOnce` | 0x0026C070 |
| 0x0024E818 | `func_0024E818` | `_clearEach` | 0x0026C0C0 |
| 0x0024E8F0 | `func_0024E8F0` | `_Error1` | 0x0026C198 |
| 0x0024E920 | `func_0024E920` | `_Error` | 0x0026C1C8 |
| 0x0024E978 | `func_0024E978` | `_sendDataToIPU` | 0x0026C220 |
| 0x0024EA50 | `func_0024EA50` | `_RefImageInit` | 0x0026C2F8 |
| 0x0024EA70 | `func_0024EA70` | `_sequenceHeader` | 0x0026C318 |
| 0x0024EF10 | `func_0024EF10` | `_initRefImages` | 0x0026C7B8 |
| 0x0024EFF8 | `func_0024EFF8` | `_setDefaultQM` | 0x0026C8A0 |
| 0x0024F0B8 | `func_0024F0B8` | `_sequenceExtension` | 0x0026C960 |
| 0x0024F220 | `func_0024F220` | `_sequenceDisplayExtension` | 0x0026CAC8 |
| 0x0024FD08 | `func_0024FD08` | `_getRef0` | 0x0026D5B8 |
| 0x00250128 | `func_00250128` | `_doMC` | 0x0026D9D8 |
| 0x002502B8 | `func_002502B8` | `_rix_000` | 0x0026DB68 |
| 0x00250330 | `func_00250330` | `_ri0_000` | 0x0026DBE0 |
| 0x002503C8 | `func_002503C8` | `_rix_001` | 0x0026DC78 |
| 0x00250480 | `func_00250480` | `_ri0_001` | 0x0026DD30 |
| 0x00250550 | `func_00250550` | `_rix_010` | 0x0026DE00 |
| 0x00250600 | `func_00250600` | `_ri0_010` | 0x0026DEB0 |
| 0x002506B8 | `func_002506B8` | `_rix_011` | 0x0026DF68 |
| 0x002507B0 | `func_002507B0` | `_ri0_011` | 0x0026E060 |
| 0x002508B0 | `func_002508B0` | `_rix_100` | 0x0026E160 |
| 0x00250958 | `func_00250958` | `_ri0_100` | 0x0026E208 |
| 0x00250A08 | `func_00250A08` | `_rix_101` | 0x0026E2B8 |
| 0x00250AF0 | `func_00250AF0` | `_ri0_101` | 0x0026E3A0 |
| 0x00250BD8 | `func_00250BD8` | `_rix_110` | 0x0026E488 |
| 0x00250CB8 | `func_00250CB8` | `_ri0_110` | 0x0026E568 |
| 0x00250D88 | `func_00250D88` | `_rix_111` | 0x0026E638 |
| 0x00250EB0 | `func_00250EB0` | `_ri0_111` | 0x0026E760 |
| 0x00250FC8 | `func_00250FC8` | `_copyAddRefImage` | 0x0026E878 |
| 0x00251088 | `func_00251088` | `_ipuSetMPEG1` | 0x0026E938 |
| 0x002510B0 | `func_002510B0` | `_waitBdecOut` | 0x0026E960 |
| 0x00251298 | `func_00251298` | `_dmVector` | 0x0026EB48 |
| 0x002512B8 | `func_002512B8` | `_dualPrimeVector` | 0x0026EB68 |
| 0x00251440 | `func_00251440` | `_mbAddressIncrement` | 0x0026ECF0 |
| 0x00251550 | `func_00251550` | `_pictureData0` | 0x0026EE00 |
| 0x00251678 | `func_00251678` | `_sliceA0` | 0x0026EF28 |
| 0x002519A0 | `func_002519A0` | `_skipMB0` | 0x0026F250 |
| 0x00251A70 | `func_00251A70` | `_decMB0` | 0x0026F320 |
| 0x00251F98 | `func_00251F98` | `_decode_motion_vector` | 0x0026F848 |
| 0x00252020 | `func_00252020` | `_motionVectors` | 0x0026F8D0 |
| 0x002521A0 | `func_002521A0` | `_motionVector` | 0x0026FA50 |
| 0x002522E0 | `func_002522E0` | `_sendIpuCommand` | 0x0026FB90 |
| 0x00252310 | `func_00252310` | `_waitIpuIdle` | 0x0026FBC0 |
| 0x002523B8 | `func_002523B8` | `_waitIpuIdle64` | 0x0026FC68 |
| 0x00252468 | `func_00252468` | `_ipuVdec` | 0x0026FD18 |
| 0x00252620 | `func_00252620` | `_peepBit` | 0x0026FED0 |
| 0x00252758 | `func_00252758` | `_flushBuf` | 0x00270008 |
| 0x00252870 | `func_00252870` | `_nextBit` | 0x00270120 |
| 0x002529D8 | `func_002529D8` | `_nextStartCode` | 0x00270288 |
| 0x00252A40 | `func_00252A40` | `_sliceB` | 0x002702F0 |
| 0x00252AB0 | `func_00252AB0` | `_nextHeader` | 0x00270360 |
| 0x00252BD8 | `func_00252BD8` | `_pictureHeader` | 0x00270488 |
| 0x00252CA8 | `func_00252CA8` | `_extensionAndUserData` | 0x00270558 |
| 0x00252D58 | `func_00252D58` | `_pictureCodingExtension` | 0x00270608 |
| 0x00252F88 | `func_00252F88` | `_extrainfo` | 0x00270838 |
| 0x002530A0 | `func_002530A0` | `_groupOfPicturesHeader` | 0x00270950 |
| 0x00253188 | `func_00253188` | `_quantMatrixExtension` | 0x00270A38 |
| 0x00253238 | `func_00253238` | `_pictureDisplayExtension` | 0x00270AE8 |
| 0x00253328 | `func_00253328` | `_copyrightExtension` | 0x00270BD8 |
| 0x002533D8 | `func_002533D8` | `_decPicture` | 0x00270C88 |
| 0x002534B8 | `func_002534B8` | `_outputFrame` | 0x00270D68 |
| 0x00253570 | `func_00253570` | `_updateRefImage` | 0x00270E20 |
| 0x00253950 | `func_00253950` | `_isOutSizeOK` | 0x00271200 |
| 0x002539F0 | `func_002539F0` | `_cpr8` | 0x002712A0 |
| 0x00253BE0 | `func_00253BE0` | `_markOutput` | 0x00271490 |
| 0x00253C18 | `func_00253C18` | `_getPtsDtsFlags` | 0x002714C8 |
| 0x00253DB0 | `func_00253DB0` | `_dispRefImage` | 0x00271660 |
| 0x00253EC8 | `func_00253EC8` | `_dispRefImageField` | 0x00271778 |
| 0x00254088 | `func_00254088` | `_doCSC` | 0x00271938 |
| 0x002542B8 | `func_002542B8` | `_doCSC2` | 0x00271B68 |
| 0x00254478 | `func_00254478` | `_ch4dma` | 0x00271D28 |
| 0x00254550 | `func_00254550` | `_csc_storeRefImage` | 0x00271E00 |
| 0x002547A8 | `func_002547A8` | `_sysbitInit` | 0x00272058 |
| 0x002547E0 | `func_002547E0` | `_sysbitNext` | 0x00272090 |
| 0x00254800 | `func_00254800` | `_sysbitFlush` | 0x002720B0 |
| 0x00254898 | `func_00254898` | `_sysbitGet` | 0x00272148 |
| 0x002548E8 | `func_002548E8` | `_sysbitMarker` | 0x00272198 |
| 0x00254930 | `func_00254930` | `_sysbitJump` | 0x002721E0 |
| 0x00254988 | `func_00254988` | `_sysbitPtr` | 0x00272238 |
| 0x00254A88 | `func_00254A88` | `sceIpuStopDMA` | 0x00272338 |
| 0x00254B70 | `func_00254B70` | `sceIpuRestartDMA` | 0x00272420 |
| 0x00254CC0 | `func_00254CC0` | `sceIpuSync` | 0x00272570 |
| 0x00254D90 | `func_00254D90` | `sceIpuInit` | 0x00272640 |
| 0x00254FC8 | `func_00254FC8` | `_SgGetSlotContext` | 0x00273228 |
| 0x00254FE0 | `func_00254FE0` | `_SgGetSeqContext` | 0x00273240 |
| 0x00255008 | `func_00255008` | `_SgGetVabContext` | 0x00273268 |
| 0x00255020 | `func_00255020` | `_SgSetSeVolValue` | 0x00273280 |
| 0x00255080 | `func_00255080` | `_SgGetPacketCntext` | 0x002732E0 |
| 0x002550A0 | `func_002550A0` | `_SgCalledTickProc` | 0x00273300 |
| 0x00255580 | `func_00255580` | `_SgSetPkAdd` | 0x002737E0 |
| 0x00255618 | `func_00255618` | `_SgSeMain` | 0x00273878 |
| 0x00255A38 | `func_00255A38` | `_SgBgmMain` | 0x00273C98 |
| 0x00255ED8 | `func_00255ED8` | `_SgSetRealtimeTickProc` | 0x00274138 |
| 0x002565E0 | `func_002565E0` | `_SgSetRealtimeVolume` | 0x00274840 |
| 0x002567C0 | `func_002567C0` | `_SgTableEnvAdd` | 0x00274A20 |
| 0x00256960 | `func_00256960` | `_SgSeqKeyOnSlot` | 0x00274BC0 |
| 0x00256A98 | `func_00256A98` | `_SgSeKeyOnSlot` | 0x00274CF8 |
| 0x00256CD0 | `func_00256CD0` | `_SgSeKeyOff` | 0x00274F30 |
| 0x00256E18 | `func_00256E18` | `_SgSeqKeyOff` | 0x00275078 |
| 0x00256F20 | `func_00256F20` | `_SgIntoKeyOn` | 0x00275180 |
| 0x00256FA8 | `func_00256FA8` | `_SgPitchTableVag` | 0x00275208 |
| 0x00256FF0 | `func_00256FF0` | `_SgSeqSeVolume` | 0x00275250 |
| 0x00257190 | `func_00257190` | `_SgPan` | 0x002753F0 |
| 0x00257220 | `func_00257220` | `_SgEndSeq` | 0x00275480 |
| 0x002572F0 | `func_002572F0` | `_SgTempoChange` | 0x00275550 |
| 0x00257380 | `func_00257380` | `_SgProgChange` | 0x002755E0 |
| 0x00257410 | `func_00257410` | `_SgContMod` | 0x00275670 |
| 0x00257570 | `func_00257570` | `_SgContModLoop` | 0x002757D0 |
| 0x002576E8 | `func_002576E8` | `_SgContPolta` | 0x00275948 |
| 0x00257838 | `func_00257838` | `_SgContVol` | 0x00275A98 |
| 0x002579F0 | `func_002579F0` | `_SgContPan` | 0x00275C50 |
| 0x00257C10 | `func_00257C10` | `_SgContDump` | 0x00275E70 |
| 0x00257D28 | `func_00257D28` | `_SgContSeLoop` | 0x00275F88 |
| 0x00257DE8 | `func_00257DE8` | `_SgContParam` | 0x00276048 |
| 0x00258168 | `func_00258168` | `_SgContLoopCount` | 0x002763C8 |
| 0x002581F0 | `func_002581F0` | `_SgContLoop` | 0x00276450 |
| 0x00258328 | `func_00258328` | `_SgBendForm` | 0x00276588 |
| 0x00258438 | `func_00258438` | `_SgDeltaTime` | 0x00276698 |
| 0x00258490 | `func_00258490` | `_SgSeqSeRrEnd` | 0x002766F0 |
| 0x00258650 | `func_00258650` | `_SgfadeParam` | 0x002768B0 |
| 0x00258688 | `func_00258688` | `_SgInit` | 0x002768E8 |
| 0x00258820 | `func_00258820` | `_SgSndn2Remote` | 0x00276A80 |
| 0x00258870 | `func_00258870` | `SgSndn2RemoteInit` | 0x00276AD0 |
| 0x00258900 | `func_00258900` | `SgSndn2RemoteSync` | 0x00276B60 |
| 0x00258958 | `func_00258958` | `SgQuit` | 0x00276BB8 |
| 0x002589C8 | `func_002589C8` | `SgCalledTickProc` | 0x00276C28 |
| 0x002589F8 | `func_002589F8` | `SgSetDigitalOutputMode` | 0x00276C58 |
| 0x00258A10 | `func_00258A10` | `SgDmaWrite` | 0x00276C70 |
| 0x00258A40 | `func_00258A40` | `SgDmaRead` | 0x00276CA0 |
| 0x00258A68 | `func_00258A68` | `_SgDmaCommon` | 0x00276CC8 |
| 0x00258AF8 | `func_00258AF8` | `SgGetDmaTransferStatus` | 0x00276D58 |
| 0x00258B88 | `func_00258B88` | `SgVabOpen` | 0x00276DE8 |
| 0x00258BF8 | `func_00258BF8` | `SgVabOpenFakeBody` | 0x00276E58 |
| 0x00258CF0 | `func_00258CF0` | `SgVabClose` | 0x00276F50 |
| 0x00258E50 | `func_00258E50` | `SgBgmOpen` | 0x002770B0 |
| 0x00258FB8 | `func_00258FB8` | `SgBgmClose` | 0x00277218 |
| 0x00259040 | `func_00259040` | `SgSetReverbEndAddr` | 0x002772A0 |
| 0x00259058 | `func_00259058` | `SgSetReverbType` | 0x002772B8 |
| 0x00259070 | `func_00259070` | `SgSetReverbDepth` | 0x002772D0 |
| 0x00259088 | `func_00259088` | `SgSetReverbDelaytime` | 0x002772E8 |
| 0x002590A0 | `func_002590A0` | `SgSetReverbFeedback` | 0x00277300 |
| 0x002590B8 | `func_002590B8` | `SgSetOutputMode` | 0x00277318 |
| 0x002590E0 | `func_002590E0` | `SgSetTickMode` | 0x00277340 |
| 0x00259108 | `func_00259108` | `SgGetSlotStatus` | 0x00277368 |
| 0x00259208 | `func_00259208` | `SgSetMasterVol` | 0x00277468 |
| 0x00259220 | `func_00259220` | `SgSetBgmVol` | 0x00277480 |
| 0x002592C8 | `func_002592C8` | `SgSetSeMasterVol` | 0x00277528 |
| 0x00259350 | `func_00259350` | `SgBgmPlay` | 0x002775B0 |
| 0x002593F8 | `func_002593F8` | `SgBgmStop` | 0x00277658 |
| 0x00259668 | `func_00259668` | `SgSetBgmTempo` | 0x002778C8 |
| 0x00259710 | `func_00259710` | `SgGetBgmTempo` | 0x00277970 |
| 0x00259740 | `func_00259740` | `SgGetBgmStatus` | 0x002779A0 |
| 0x002597C8 | `func_002597C8` | `SgGetBgmChStatus` | 0x00277A28 |
| 0x00259878 | `func_00259878` | `SgSetBgmPanpot` | 0x00277AD8 |
| 0x00259958 | `func_00259958` | `SgSePlay` | 0x00277BB8 |
| 0x00259B80 | `func_00259B80` | `SgSeStop` | 0x00277DE0 |
| 0x00259CB0 | `func_00259CB0` | `SgSeStopAll` | 0x00277F10 |
| 0x00259D58 | `func_00259D58` | `SgSetSeVolDirect` | 0x00277FB8 |
| 0x00259DF8 | `func_00259DF8` | `SgSetSePitchDirect` | 0x00278058 |
| 0x00259E68 | `func_00259E68` | `SgGetSpuSlotMalloc` | 0x002780C8 |
| 0x0025A040 | `func_0025A040` | `SgSetSpuSlotFree` | 0x002782A0 |
| 0x0025A080 | `func_0025A080` | `SgStAdpcmInit` | 0x002782E0 |
| 0x0025A098 | `func_0025A098` | `SgStAdpcmQuit` | 0x002782F8 |
| 0x0025A0B0 | `func_0025A0B0` | `SgStAdpcmOpen` | 0x00278310 |
| 0x0025A140 | `func_0025A140` | `SgStAdpcmClose` | 0x002783A0 |
| 0x0025A180 | `func_0025A180` | `SgStAdpcmChannelVolume` | 0x002783E0 |
| 0x0025A208 | `func_0025A208` | `SgStAdpcmChannelPitch` | 0x00278468 |
| 0x0025A280 | `func_0025A280` | `SgStAdpcmPlay` | 0x002784E0 |
| 0x0025A2E0 | `func_0025A2E0` | `SgStAdpcmStop` | 0x00278540 |
| 0x0025A340 | `func_0025A340` | `SgStAdpcmIopReadAddr` | 0x002785A0 |
| 0x0025A3B0 | `func_0025A3B0` | `SgStPcmInit` | 0x00278610 |
| 0x0025A3C8 | `func_0025A3C8` | `SgStPcmQuit` | 0x00278628 |
| 0x0025A3E0 | `func_0025A3E0` | `SgStPcmOpen` | 0x00278640 |
| 0x0025A450 | `func_0025A450` | `SgStPcmClose` | 0x002786B0 |
| 0x0025A490 | `func_0025A490` | `SgStPcmSetEffect` | 0x002786F0 |
| 0x0025A4A8 | `func_0025A4A8` | `SgStPcmPlay` | 0x00278708 |
| 0x0025A4E8 | `func_0025A4E8` | `SgStPcmStop` | 0x00278748 |
| 0x0025A528 | `func_0025A528` | `SgStPcmLseek` | 0x00278788 |
| 0x0025A578 | `func_0025A578` | `SgStPcmVolume` | 0x002787D8 |
| 0x0025A5C8 | `func_0025A5C8` | `SgStPcmIopReadAddr` | 0x00278828 |
| 0x0025A610 | `func_0025A610` | `SgStPcmBufMode` | 0x00278870 |
| 0x0025A678 | `func_0025A678` | `sinf` | 0x002788D8 |
| 0x0025A968 | `func_0025A968` | `atan2f` | 0x00278BC8 |
| 0x0025AA90 | `func_0025AA90` | `fmodf` | 0x00278CF0 |
| 0x0025ABD0 | `func_0025ABD0` | `__ieee754_acosf` | 0x00278E30 |
| 0x0025B000 | `func_0025B000` | `__ieee754_asinf` | 0x00279260 |
| 0x0025B3A0 | `func_0025B3A0` | `__ieee754_atan2f` | 0x00279600 |
| 0x0025B688 | `func_0025B688` | `__ieee754_fmodf` | 0x002798E8 |
| 0x0025B8D8 | `func_0025B8D8` | `__ieee754_rem_pio2f` | 0x00279B38 |
| 0x0025BCB8 | `func_0025BCB8` | `__ieee754_sqrtf` | 0x00279F18 |
| 0x0025BDF0 | `func_0025BDF0` | `__kernel_cosf` | 0x0027A050 |
| 0x0025BF48 | `func_0025BF48` | `__kernel_rem_pio2f` | 0x0027A1A8 |
| 0x0025C898 | `func_0025C898` | `__kernel_sinf` | 0x0027AAF8 |
| 0x0025C9A0 | `func_0025C9A0` | `matherr` | 0x0027AC00 |
| 0x0025C9C8 | `func_0025C9C8` | `atanf` | 0x0027AC28 |
| 0x0025CC70 | `func_0025CC70` | `fabsf` | 0x0027AED0 |
| 0x0025CC90 | `func_0025CC90` | `floorf` | 0x0027AEF0 |
| 0x0025CD78 | `func_0025CD78` | `isnanf` | 0x0027AFD8 |
| 0x0025CDA0 | `func_0025CDA0` | `scalbnf` | 0x0027B000 |
| 0x0025CF00 | `func_0025CF00` | `copysignf` | 0x0027B160 |
| 0x0025CF88 | `func_0025CF88` | `__do_global_ctors` | 0x0027B1E8 |
| 0x0025D038 | `func_0025D038` | `__main` | 0x0027B298 |
| 0x0025D058 | `func_0025D058` | `__divdi3` | 0x0027B2B8 |
| 0x0025D748 | `func_0025D748` | `__fixunsdfdi` | 0x0027B9A8 |
| 0x0025D838 | `func_0025D838` | `__floatdidf` | 0x0027BA98 |
| 0x0025D8D0 | `func_0025D8D0` | `__moddi3` | 0x0027BB30 |
| 0x0025DF38 | `func_0025DF38` | `__muldi3` | 0x0027C198 |
| 0x0025DF98 | `func_0025DF98` | `__udivdi3` | 0x0027C1F8 |
| 0x0025E568 | `func_0025E568` | `__umoddi3` | 0x0027C7C8 |
| 0x0025EAA8 | `func_0025EAA8` | `__pack_d` | 0x0027CD08 |
| 0x0025EBD8 | `func_0025EBD8` | `__unpack_d` | 0x0027CE38 |
| 0x0025EC78 | `func_0025EC78` | `_fpadd_parts` | 0x0027CED8 |
| 0x0025EEB8 | `func_0025EEB8` | `dpadd` | 0x0027D118 |
| 0x0025EF10 | `func_0025EF10` | `dpsub` | 0x0027D170 |
| 0x0025EF78 | `func_0025EF78` | `dpmul` | 0x0027D1D8 |
| 0x0025F220 | `func_0025F220` | `dpdiv` | 0x0027D480 |
| 0x0025F388 | `func_0025F388` | `__fpcmp_parts_d` | 0x0027D5E8 |
| 0x0025F4A0 | `func_0025F4A0` | `dpcmp` | 0x0027D700 |
| 0x0025F4F0 | `func_0025F4F0` | `litodp` | 0x0027D750 |
| 0x0025F5A8 | `func_0025F5A8` | `dptoli` | 0x0027D808 |
| 0x0025F640 | `func_0025F640` | `dptoul` | 0x0027D8A0 |
| 0x0025F6E0 | `func_0025F6E0` | `__negdf2` | 0x0027D940 |
| 0x0025F718 | `func_0025F718` | `__make_dp` | 0x0027D978 |
| 0x0025F748 | `func_0025F748` | `dptofp` | 0x0027D9A8 |
| 0x0025F7A0 | `func_0025F7A0` | `__pack_f` | 0x0027DA00 |
| 0x0025F8B0 | `func_0025F8B0` | `__unpack_f` | 0x0027DB10 |
| 0x0025FB78 | `func_0025FB78` | `fpadd` | 0x0027DDD8 |
| 0x0025FBD0 | `func_0025FBD0` | `fpsub` | 0x0027DE30 |
| 0x0025FC38 | `func_0025FC38` | `fpmul` | 0x0027DE98 |
| 0x0025FE30 | `func_0025FE30` | `fpdiv` | 0x0027E090 |
| 0x0025FF90 | `func_0025FF90` | `__fpcmp_parts_f` | 0x0027E1F0 |
| 0x002600A8 | `func_002600A8` | `fpcmp` | 0x0027E308 |
| 0x002600F8 | `func_002600F8` | `sitofp` | 0x0027E358 |
| 0x002601B0 | `func_002601B0` | `fptosi` | 0x0027E410 |
| 0x00260240 | `func_00260240` | `fptoui` | 0x0027E4A0 |
| 0x002602D8 | `func_002602D8` | `__negsf2` | 0x0027E538 |
| 0x00260310 | `func_00260310` | `__make_fp` | 0x0027E570 |
| 0x00260340 | `func_00260340` | `fptodp` | 0x0027E5A0 |
| 0x00260380 | `func_00260380` | `__assert` | 0x0027E5E0 |
| 0x002603B8 | `func_002603B8` | `atoi` | 0x0027E618 |
| 0x002603F0 | `func_002603F0` | `fiprintf` | 0x0027E650 |
| 0x00260424 | `func_00260424` | `memcmp` | 0x0027E684 |
| 0x002604B8 | `func_002604B8` | `memcpy` | 0x0027E718 |
| 0x00260568 | `func_00260568` | `memset` | 0x0027E7C8 |
| 0x00260628 | `func_00260628` | `_printf_r` | 0x0027E888 |
| 0x00260668 | `func_00260668` | `printf` | 0x0027E8C8 |
| 0x002606B8 | `func_002606B8` | `qsort` | 0x0027E918 |
| 0x002610E0 | `func_002610E0` | `srand` | 0x0027F340 |
| 0x002610F0 | `func_002610F0` | `rand` | 0x0027F350 |
| 0x00261120 | `func_00261120` | `_sprintf_r` | 0x0027F380 |
| 0x00261188 | `func_00261188` | `sprintf` | 0x0027F3E8 |
| 0x00261200 | `func_00261200` | `sscanf` | 0x0027F460 |
| 0x00261288 | `func_00261288` | `strcat` | 0x0027F4E8 |
| 0x002613B4 | `func_002613B4` | `strcmp` | 0x0027F614 |
| 0x002614F8 | `func_002614F8` | `strcpy` | 0x0027F758 |
| 0x0026160C | `func_0026160C` | `strlen` | 0x0027F86C |
| 0x00261748 | `func_00261748` | `strncmp` | 0x0027F9A8 |
| 0x00261900 | `func_00261900` | `strncpy` | 0x0027FB60 |
| 0x00261AC0 | `func_00261AC0` | `strrchr` | 0x0027FD20 |
| 0x00261B10 | `func_00261B10` | `strstr` | 0x0027FD70 |
| 0x00261B80 | `func_00261B80` | `strtok` | 0x0027FDE0 |
| 0x00264290 | `func_00264290` | `cvt` | 0x002824F0 |
| 0x00264440 | `func_00264440` | `exponent` | 0x002826A0 |
| 0x00264520 | `func_00264520` | `__svfscanf` | 0x00282780 |
| 0x00265028 | `func_00265028` | `__sccl` | 0x00283288 |
| 0x00265130 | `func_00265130` | `vsprintf` | 0x00283390 |
| 0x00265188 | `func_00265188` | `__swsetup` | 0x002833E8 |
| 0x002652D8 | `func_002652D8` | `quorem` | 0x00283538 |
| 0x002654F0 | `func_002654F0` | `_dtoa_r` | 0x00283750 |
| 0x002666C0 | `func_002666C0` | `fflush` | 0x00284920 |
| 0x002667C8 | `func_002667C8` | `std` | 0x00284A28 |
| 0x00266820 | `func_00266820` | `__sfmoreglue` | 0x00284A80 |
| 0x00266890 | `func_00266890` | `__sfp` | 0x00284AF0 |
| 0x00266990 | `func_00266990` | `__sinit` | 0x00284BF0 |
| 0x00266A20 | `func_00266A20` | `fread` | 0x00284C80 |
| 0x00266B40 | `func_00266B40` | `_free_r` | 0x00284DA0 |
| 0x00266E60 | `func_00266E60` | `_malloc_trim_r` | 0x002850C0 |
| 0x00266FD0 | `func_00266FD0` | `__sfvwrite` | 0x00285230 |
| 0x002673A8 | `func_002673A8` | `_fwalk` | 0x00285608 |
| 0x00267440 | `func_00267440` | `_setlocale_r` | 0x002856A0 |
| 0x00267530 | `func_00267530` | `__smakebuf` | 0x00285790 |
| 0x00267680 | `func_00267680` | `malloc_extend_top` | 0x002858E0 |
| 0x002678D8 | `func_002678D8` | `_malloc_r` | 0x00285B38 |
| 0x00268050 | `func_00268050` | `_mbtowc_r` | 0x002862B0 |
| 0x0026808C | `func_0026808C` | `memchr` | 0x002862EC |
| 0x0026816C | `func_0026816C` | `memmove` | 0x002863CC |
| 0x00268280 | `func_00268280` | `_Balloc` | 0x002864E0 |
| 0x00268328 | `func_00268328` | `_Bfree` | 0x00286588 |
| 0x00268358 | `func_00268358` | `_multadd` | 0x002865B8 |
| 0x00268470 | `func_00268470` | `_s2b` | 0x002866D0 |
| 0x002685B8 | `func_002685B8` | `_hi0bits` | 0x00286818 |
| 0x00268640 | `func_00268640` | `_lo0bits` | 0x002868A0 |
| 0x00268700 | `func_00268700` | `_i2b` | 0x00286960 |
| 0x00268738 | `func_00268738` | `_multiply` | 0x00286998 |
| 0x00268968 | `func_00268968` | `_pow5mult` | 0x00286BC8 |
| 0x00268A68 | `func_00268A68` | `_lshift` | 0x00286CC8 |
| 0x00268BE0 | `func_00268BE0` | `__mcmp` | 0x00286E40 |
| 0x00268C48 | `func_00268C48` | `__mdiff` | 0x00286EA8 |
| 0x00268DD8 | `func_00268DD8` | `_ulp` | 0x00287038 |
| 0x00268E70 | `func_00268E70` | `_b2d` | 0x002870D0 |
| 0x00268FF0 | `func_00268FF0` | `_d2b` | 0x00287250 |
| 0x00269170 | `func_00269170` | `_ratio` | 0x002873D0 |
| 0x00269230 | `func_00269230` | `_mprec_log10` | 0x00287490 |
| 0x002692C0 | `func_002692C0` | `__srefill` | 0x00287520 |
| 0x00269438 | `func_00269438` | `isinf` | 0x00287698 |
| 0x00269480 | `func_00269480` | `isnan` | 0x002876E0 |
| 0x002694B8 | `func_002694B8` | `_sbrk_r` | 0x00287718 |
| 0x00269518 | `func_00269518` | `_init_signal_r` | 0x00287778 |
| 0x00269588 | `func_00269588` | `_signal_r` | 0x002877E8 |
| 0x00269618 | `func_00269618` | `_raise_r` | 0x00287878 |
| 0x00269708 | `func_00269708` | `__sigtramp_r` | 0x00287968 |
| 0x002698E8 | `func_002698E8` | `__sread` | 0x00287B48 |
| 0x00269950 | `func_00269950` | `__swrite` | 0x00287BB0 |
| 0x002699D0 | `func_002699D0` | `__sseek` | 0x00287C30 |
| 0x00269A38 | `func_00269A38` | `__sclose` | 0x00287C98 |
| 0x00269A58 | `func_00269A58` | `_strtod_r` | 0x00287CB8 |
| 0x0026A988 | `func_0026A988` | `strtodf` | 0x00288BE8 |
| 0x0026A9B0 | `func_0026A9B0` | `_strtoul_r` | 0x00288C10 |
| 0x0026AC08 | `func_0026AC08` | `__submore` | 0x00288E68 |
| 0x0026ACF8 | `func_0026ACF8` | `ungetc` | 0x00288F58 |
| 0x0026AEE0 | `func_0026AEE0` | `_calloc_r` | 0x00289140 |
| 0x0026AFA0 | `func_0026AFA0` | `_close_r` | 0x00289200 |
| 0x0026B118 | `func_0026B118` | `_realloc_r` | 0x00289378 |
| 0x0026B688 | `func_0026B688` | `_sceSDC` | 0x002898E8 |
| 0x0026B7C8 | `func_0026B7C8` | `_sceIDC` | 0x00289A28 |
| 0x0026B908 | `func_0026B908` | `__fixdfdi` | 0x00289B68 |

## Dropped: target name still occupied by another aug6 address

Each PAL name below is still held, after the whole map is applied, by an
aug6 address that has no rename of its own — so taking it would create a
duplicate symbol.  Listed for a second pass once those holders are
themselves resolved.

| aug6 VMA | aug6 name (kept) | PAL name (not taken) | PAL VMA |
| --- | --- | --- | --- |
| 0x00102760 | `func_00102760` | `GetRootQuaternionByDObj` | 0x001027D8 |
| 0x00102830 | `func_00102830` | `SetRootBaseQuaternion` | 0x001028A8 |
| 0x00102840 | `func_00102840` | `SetRootQuaternion` | 0x001028B8 |
| 0x001028C0 | `GetRootQuaternionByDObj` | `SetRootMatrixWithTransOffsetByDObj` | 0x00102938 |
| 0x00102948 | `GetRootQuaternion` | `GetRootMatrixRotOffsetByDObj` | 0x001029C0 |
| 0x00102990 | `SetRootBaseQuaternion` | `SetRootMatrixRotOffsetByDObj` | 0x00102A08 |
| 0x00102DA0 | `GetRootMatrixRotOffset` | `GetGlobalDirectionOrient` | 0x00102FE8 |
| 0x00102F20 | `SetDirectRootPositionNoFittingWithNodePoint` | `GetInitialInverseMatrixByDObj` | 0x00103168 |
| 0x00102FE0 | `SetDirectRootPositionWithNodePoint` | `GetInitialInverseMatrix` | 0x00103228 |
| 0x001030A8 | `LocalizeGeometry` | `GetInitialSkeltonMatrixByDObj` | 0x001032F0 |
| 0x001048F0 | `func_001048F0` | `getInitialMatrix` | 0x00104B38 |
| 0x00104998 | `func_00104998` | `InitKeyInput` | 0x00104BE0 |
| 0x00104CF0 | `func_00104CF0` | `InitMatrixDrive` | 0x00104F38 |
| 0x00104D20 | `func_00104D20` | `MatrixDrive_PushMatrix` | 0x00104F68 |
| 0x001050A8 | `func_001050A8` | `MatrixDrive_TransMatrixV` | 0x001052F0 |
| 0x00105108 | `func_00105108` | `MatrixDrive_TransMatrix` | 0x00105350 |
| 0x00105190 | `InitMatrixDrive` | `MatrixDrive_TurnObjectMatrix` | 0x001053D8 |
| 0x00105288 | `MatrixDrive_PushMatrix` | `MatrixDrive_TurnXObjectMatrixZY` | 0x001054D0 |
| 0x00105B88 | `MatrixDrive_TransMatrixV` | `MatrixDrive_GetTurnMinusZAngleXY` | 0x00105DD0 |
| 0x00105C70 | `MatrixDrive_TransMatrix` | `MatrixDrive_SetTransposeMatrix` | 0x00105EB8 |
| 0x00106370 | `CopyVector` | `dispPlane` | 0x001063B0 |
| 0x00106980 | `GetOrientOfCliffOfGObj` | `SetMotionDirectionWithLimit` | 0x001069C0 |
| 0x00107560 | `calcFootIK` | `DispSkelton` | 0x001075B8 |
| 0x00107CA0 | `DispSkelton` | `getVerticalElementOfWallNormal` | 0x00107C18 |
| 0x00107CF0 | `SlopeIKControl` | `AdjustVerticalSidePlaneOfWall` | 0x00107C68 |
| 0x00107FC0 | `GetPureVerticalPlaneOfCurrentPosition` | `GetPureVerticalPlane` | 0x00107F38 |
| 0x00108178 | `getVerticalElementOfWallNormal` | `_getS16MotRotElem` | 0x001080F0 |
| 0x00108560 | `AdjustVerticalSidePlaneOfWall` | `_getMotion` | 0x001084D8 |
| 0x00108918 | `GetPureVerticalPlane` | `GetStreamMotion` | 0x00108890 |
| 0x00108A98 | `_getS16MotRotElem` | `copyMotionWithNodeHrc` | 0x00108A10 |
| 0x00108B60 | `_getMotion` | `CopyMotionWithNodeHrc` | 0x00108AD8 |
| 0x00109668 | `GetStreamMotion` | `MakeMirrorMotion` | 0x001095E0 |
| 0x001097E0 | `copyMotionWithNodeHrc` | `GetFloatingShapeMotion` | 0x00109758 |
| 0x00109A80 | `GetFloatingShapeMotion` | `DebugDisp1Collision` | 0x00109BB0 |
| 0x00109B78 | `FeedbackWallWorkInfoToBrainSystem` | `DebugDisp1CollisionWithColor` | 0x00109CA8 |
| 0x00109DD0 | `DebugDisp1Collision` | `InitMotionStateInfo` | 0x00109E80 |
| 0x0010A0A8 | `CheckFloorAttribute` | `GetStreamShapeMotion` | 0x0010A0C0 |
| 0x0010A608 | `GetMotionFrameFlag2` | `InitMotionRotElem` | 0x0010A398 |
| 0x0010B0C0 | `dispPool` | `copyToWork` | 0x0010ADC8 |
| 0x0010B238 | `PoolDL` | `flushWork` | 0x0010AF40 |
| 0x0010CB30 | `InitLayoutedPoolReflactionMesh` | `SetLayoutedPoolReflactionMesh` | 0x0010C7D0 |
| 0x0010D528 | `func_0010D528` | `InitLayoutedPoolReflactionMesh` | 0x0010D160 |
| 0x0010D6F0 | `MultiCurrentQuaternion` | `getWave` | 0x0010D328 |
| 0x0010D770 | `InvertCurrentQuaternion` | `MultiCurrentQuaternion` | 0x0010D3A8 |
| 0x0010D798 | `SetCurrentQuaternion` | `InvertCurrentQuaternion` | 0x0010D3D0 |
| 0x0010D7B8 | `RotCurrentQuaternionX` | `SetCurrentQuaternion` | 0x0010D3F0 |
| 0x0010D838 | `InitQuaternionDrive` | `PushQuaternion` | 0x0010D470 |
| 0x0010D8D0 | `getQuaternionFromMatrix` | `GetMatrixFromQuaternion` | 0x0010D508 |
| 0x0010D958 | `GetQuaternionFromMatrix` | `getQuaternionFromMatrix` | 0x0010D590 |
| 0x0010DB88 | `CopyQuaternion` | `GetQuaternionFromMatrix` | 0x0010D7C0 |
| 0x0010DBC8 | `RegularizeQuaternion` | `GetInverseQuaternion` | 0x0010D800 |
| 0x0010DC08 | `GetSlerpQuaternionNoRegularize` | `RegularizeQuaternion` | 0x0010D840 |
| 0x0010DC70 | `GetSlerpQuaternion` | `GetSlerpQuaternionNoRegularize` | 0x0010D8A8 |
| 0x0010ECE0 | `p2o_SetDefaultEnviroment` | `GetTableSin` | 0x0010E918 |
| 0x0010F9D0 | `func_0010F9D0` | `gif_EndPacket` | 0x0010F6A8 |
| 0x0010FC20 | `func_0010FC20` | `gif_MakeLine2DOffset` | 0x0010F8F8 |
| 0x0010FD48 | `func_0010FD48` | `gif_MakeSprite` | 0x0010FA20 |
| 0x00110780 | `gif_StartPacket` | `gif_SpriteSensitive` | 0x00110458 |
| 0x00110920 | `gif_EndPacket` | `gif_SpriteOffset` | 0x001105F8 |
| 0x00110B30 | `gif_StartPacketPath1` | `gif_SpriteSensitiveOffset` | 0x00110808 |
| 0x00110E90 | `gif_MakeLine2DOffset` | `gif_SpriteSensitiveOrg` | 0x00110B68 |
| 0x00112CA0 | `gsb_setSemitransReg` | `gsb_KeepFrameBuffer` | 0x00112CE8 |
| 0x00113B60 | `gsb_PostEffect` | `gsb_setNormalReg` | 0x00113BA0 |
| 0x00113BC8 | `gsb_InitGSSystem` | `gsb_setSemitransReg` | 0x00113C08 |
| 0x00113C38 | `gsb_UpdateGSSystem` | `gsb_setSpecularReg` | 0x00113C78 |
| 0x00113CB0 | `gsb_ResetGSSystem` | `gsb_setParticleReg` | 0x00113CF0 |
| 0x00114418 | `gsb_SetBGColor` | `gsb_ResetGSSystem` | 0x001145D0 |
| 0x00114AE0 | `light_killLinkAmbient` | `gsb_ClipBox` | 0x00114E58 |
| 0x00115118 | `light_getAmbientLight` | `gsb_SetBGColor` | 0x001161F8 |
| 0x00115170 | `light_MakeLightMatrix` | `gsb_GetBGColor` | 0x00116250 |
| 0x001169D8 | `func_001169D8` | `light_GetColorAnalog` | 0x00117C70 |
| 0x00116CB8 | `func_00116CB8` | `light_DrawCursor` | 0x00117F50 |
| 0x00117038 | `func_00117038` | `light_Tool` | 0x001182D0 |
| 0x00117B90 | `func_00117B90` | `light_KillAllFixLight` | 0x00118E30 |
| 0x00117BF0 | `func_00117BF0` | `light_KillAllAmbient` | 0x00118E90 |
| 0x00117CB8 | `func_00117CB8` | `light_resetFlatLight` | 0x00118F58 |
| 0x001180A8 | `func_001180A8` | `_PushCurrentMatrix` | 0x00119548 |
| 0x001183E8 | `_UnitCurrentMatrix` | `_GetCurrentMatrix` | 0x00119888 |
| 0x001192B0 | `pac_makeClusterStrip` | `mc_TransMicroCode` | 0x0011A650 |
| 0x0011A660 | `pac_setMaterialPacket` | `pac_openDmaTag` | 0x0011BA00 |
| 0x0011A6D0 | `pac_makeMaterialTable` | `pac_setVifCode` | 0x0011BA70 |
| 0x0011A718 | `pac_makeMaterialTableLine` | `pac_setVifEndCode` | 0x0011BAB8 |
| 0x0011B120 | `pac_DispVu1Memory` | `pac_setMaterialPacket` | 0x0011C4C0 |
| 0x0011B2A0 | `func_0011B2A0` | `pac_makeMaterialTable` | 0x0011C640 |
| 0x0011B468 | `func_0011B468` | `pac_makeMaterialTableLine` | 0x0011C808 |
| 0x0011C388 | `prim_SetFan2D` | `pac_DispVu1Memory` | 0x0011D788 |
| 0x0011C680 | `prim_makePacketMesh3D` | `prim_SetFan2D` | 0x0011DA80 |
| 0x0011C8C8 | `prim_InitMesh3D` | `prim_DispFan2D` | 0x0011DCC8 |
| 0x0011D258 | `setMatrix` | `prim_makeNormal` | 0x0011E658 |
| 0x0011D6B0 | `setLight` | `prim_UpdateMesh3D` | 0x0011EAB0 |
| 0x0011D958 | `clearUVOffset` | `setMatrix` | 0x0011ED58 |
| 0x0011DA20 | `prim_DispMesh3D` | `setLight` | 0x0011EE20 |
| 0x0011DAF8 | `prim_InitParticle` | `clearUVOffset` | 0x0011EEF8 |
| 0x0011E298 | `prim_DispWireYCylinder` | `prim_DeleteParticle` | 0x0011F6A8 |
| 0x0011E2D0 | `prim_DispWireSphere` | `drawDisc` | 0x0011F6E0 |
| 0x0011E470 | `reg_setShape` | `prim_DispWireYCylinder` | 0x0011F880 |
| 0x0011E5D8 | `reg_dispBoxLine` | `prim_DispWireSphere` | 0x0011F9E8 |
| 0x0011EEE8 | `reg_chooseMicroCode` | `reg_dispBoxLine` | 0x00120318 |
| 0x0011F1C8 | `func_0011F1C8` | `reg_chooseMicroCode` | 0x001205F8 |
| 0x0011F1F0 | `func_0011F1F0` | `reg_chooseSpecularMicroCode` | 0x00120620 |
| 0x0011F208 | `reg_setNMatrixPacket` | `reg_chooseReflectionMicroCode` | 0x00120638 |
| 0x00120040 | `reg_dispCObj` | `reg_transMaterialPacket` | 0x001214D8 |
| 0x00120090 | `reg_dispPoint` | `reg_setDissolve` | 0x00121528 |
| 0x00120298 | `reg_dispLine` | `reg_resetDissolve` | 0x00121730 |
| 0x00122560 | `__GetCameraPos` | `reg_setEMatrixPacket` | 0x00123AE0 |
| 0x00123AA8 | `func_00123AA8` | `shadow_Render` | 0x00125758 |
| 0x00124290 | `stage_ApplyData` | `__GetCameraPos` | 0x00125F40 |
| 0x00127EF8 | `stage_ContinueAnimation` | `shadow_MakeObjectData` | 0x00129738 |
| 0x00128260 | `stage_ResetAnimation` | `shadow_Tool` | 0x00129AA0 |
| 0x001295D8 | `stage_KillPlayBgAnimation` | `stage_SetAnimation` | 0x0012AEB0 |
| 0x0012AAB8 | `func_0012AAB8` | `stage_SetLoopFlag` | 0x0012C600 |
| 0x0012AB00 | `func_0012AB00` | `stage_SetFrameStep` | 0x0012C648 |
| 0x0012AB48 | `func_0012AB48` | `stage_SetParentOfGObj` | 0x0012C690 |
| 0x0012ABB0 | `func_0012ABB0` | `stage_SetParentOfGObjWithLocalRotationFlag` | 0x0012C6F8 |
| 0x0012AC18 | `tex_AllocVramAuto` | `stage_SetLocalizeGeometry` | 0x0012C760 |
| 0x0012ACC0 | `tex_loadImage` | `stage_KillPlayBgAnimationIfOverMaxCount` | 0x0012C808 |
| 0x0012ADA8 | `tex_transVramClutTex` | `tex_AllocVramAuto` | 0x0012C8F0 |
| 0x0012B728 | `tex_transTM2` | `tex_transVramClutTex` | 0x0012D270 |
| 0x0012B940 | `tex_initClutTexture` | `tex_transVramDirectTex` | 0x0012D488 |
| 0x0012BAC0 | `tex_setRegisters` | `tex_transRegister` | 0x0012D608 |
| 0x0012C4E8 | `tex_makeTexturePacket` | `tex_convertClutCSM2ToCSM1` | 0x0012E010 |
| 0x0012C7D0 | `tex_LoadTexturePart` | `tex_makeCopyImage` | 0x0012E2F8 |
| 0x0012D378 | `tex_FreeTexture` | `tex_scrollClut` | 0x0012F150 |
| 0x0012D920 | `tex_ResetVram` | `tex_textureAnimation` | 0x0012F6F8 |
| 0x0012DCD8 | `tex_dispClut` | `tex_SetClutAnimation` | 0x0012FAB0 |
| 0x0012DD58 | `tex_printTexture` | `tex_FreeTexture` | 0x0012FB30 |
| 0x0012E400 | `tex_GetTWTH` | `tex_printTexture` | 0x00130210 |
| 0x0012F6F0 | `fog_DrawFog` | `tex_ListTool` | 0x00131500 |
| 0x0012FBB8 | `fog_FogTool` | `tex_GetTWTH` | 0x001319C8 |
| 0x00130128 | `iosCdvdMgrStStop` | `fog_MakeFogClut` | 0x001320F0 |
| 0x00130E70 | `temp_loadfunc` | `fog_FogTool` | 0x00132EF8 |
| 0x00131FB8 | `iosCdvdLoad` | `iosCdvdHandlerRead` | 0x001342E0 |
| 0x001324D8 | `iosCdvdBackGroundMgr` | `iosCdvdLoad` | 0x00134800 |
| 0x00132510 | `iosCdvdDirectStOpen` | `iosCdvdPackLoad` | 0x00134838 |
| 0x00132CD0 | `iosCdvdLoadPackFile` | `iosCdvdChgFileName` | 0x00135370 |
| 0x00132E50 | `iosCdvdBackGroundMgrDelete` | `iosCdvdSync` | 0x001354F0 |
| 0x00132F08 | `iosCdvdBackGroundMgrEntryNum` | `iosCdvdBackGroundMgrDelete` | 0x001355A8 |
| 0x00132F18 | `iosCdvdBackGroundMgrSeek` | `iosCdvdBackGroundMgrNotDiskReadyPauseSet` | 0x001355B8 |
| 0x00132F38 | `iosCdvdBackGroundRead` | `iosCdvdBackGroundMgrDeleteRequestGet` | 0x001355D8 |
| 0x00132F80 | `iosCdvdBackGroundReadIOPm` | `iosCdvdBackGroundMgrEntryNum` | 0x00135620 |
| 0x00133320 | `open_inflate_handler` | `huft_build` | 0x001358B0 |
| 0x00133AE8 | `fill_inbuf` | `inflate_codes` | 0x00136078 |
| 0x00134230 | `huft_free` | `inflate_stored` | 0x001367C0 |
| 0x00134550 | `func_00134550` | `inflate_fixed` | 0x00136AE0 |
| 0x001347B0 | `func_001347B0` | `inflate_dynamic` | 0x00136D40 |
| 0x001350C8 | `func_001350C8` | `inflate_start` | 0x00137658 |
| 0x00135118 | `func_00135118` | `close_inflate_handler` | 0x001376A8 |
| 0x001356A8 | `func_001356A8` | `open_inflate_handler` | 0x00137C38 |
| 0x00135738 | `func_00135738` | `fill_inbuf` | 0x00137CC8 |
| 0x00135818 | `ios_init_plus` | `huft_free` | 0x00137DA8 |
| 0x00135BC0 | `new_mblock_node` | `iosSifAllocIopHeapDebug` | 0x001380B0 |
| 0x00135C68 | `reuse_mblock1` | `new_mblock_node` | 0x00138158 |
| 0x00135D68 | `init_mblock` | `reuse_mblock1` | 0x00138258 |
| 0x00135D90 | `new_segment` | `init_mblock` | 0x00138280 |
| 0x00135DA0 | `reuse_mblock` | `new_segment` | 0x00138290 |
| 0x00135E48 | `strdup_mblock` | `reuse_mblock` | 0x00138338 |
| 0x00135EA0 | `func_00135EA0` | `strdup_mblock` | 0x00138390 |
| 0x001384F8 | `iosMallocSetPartitionName` | `iosMallocSetPartition` | 0x0013AA78 |
| 0x00138718 | `iosMallocClearPartition` | `iosMallocResetPartition` | 0x0013AC98 |
| 0x001388F8 | `iosMallocDebug` | `iosMallocSetPartitionName` | 0x0013AE78 |
| 0x00139B40 | `func_00139B40` | `iosMallocInitPartition` | 0x0013C270 |
| 0x00139D08 | `iosMsgQueueCreate` | `deq_mes_th` | 0x0013C4A8 |
| 0x00139D38 | `iosMsgQueueDestroy` | `iosMsgQueueCreate` | 0x0013C4D8 |
| 0x00139DE0 | `send_signal_message` | `iosMsgQueueDestroy` | 0x0013C580 |
| 0x0013AD80 | `iosPadGetStick` | `iosPadNormalizeStick` | 0x0013D5F8 |
| 0x0013B0F8 | `iosPadDevRead` | `iosPadActRequest` | 0x0013D970 |
| 0x0013B200 | `iosPadGetPort` | `iosPadDevRead` | 0x0013DA78 |
| 0x0013B230 | `iosPadGetSlot` | `iosPadGetPort` | 0x0013DAA8 |
| 0x0013B248 | `iosPadGetDevice` | `iosPadGetSlot` | 0x0013DAC0 |
| 0x0013B260 | `iosPadConnect` | `iosPadGetDevice` | 0x0013DAD8 |
| 0x0013B2A8 | `iosPadStickCameraCoord` | `iosPadConnect` | 0x0013DB20 |
| 0x0013B360 | `iosPadActStop` | `iosPadActInit` | 0x0013DC60 |
| 0x0013B3D8 | `Vibration_ShotDecode` | `iosPadActStop` | 0x0013DCD8 |
| 0x0013B668 | `Init_ShockRequestBox` | `Vibration_ShotDecode` | 0x0013DF68 |
| 0x0013BE08 | `ShockRequestBox_Request` | `Shock_SetMotor` | 0x0013E708 |
| 0x0013BF70 | `ShockRequestBox_DecodeRequest` | `Init_ShockVoiceSet` | 0x0013E870 |
| 0x0013BFA8 | `ShockRequestBox_EndRequestFree` | `Vibration_SetDecodeData` | 0x0013E8A8 |
| 0x0013BFF8 | `ShockRequestBox_VoiceSetUseRequestFree` | `Init_ShockRequestBox` | 0x0013E8F8 |
| 0x0013C0A0 | `ShockRequestBox_RequestDirectCancel` | `ShockRequestBox_Request` | 0x0013E9A0 |
| 0x0013C230 | `Init_ShockDriver` | `ShockRequestBox_DecodeRequest` | 0x0013EB30 |
| 0x0013C308 | `ShockDriver_VoiceSet_NumberRegist` | `ShockRequestBox_EndRequestFree` | 0x0013EC08 |
| 0x0013C360 | `ShockDriver_VoiceSet_Regist` | `ShockRequestBox_VoiceSetUseRequestFree` | 0x0013EC60 |
| 0x0013C408 | `ShockDriver_VoiceSet_Remove` | `ShockRequestBox_GetRequest` | 0x0013ED08 |
| 0x0013C4C0 | `ShockDriver_GetShockVoiceSet` | `ShockRequestBox_RequestDirectCancel` | 0x0013EDC0 |
| 0x0013C530 | `ShockDriver_GetShockVoice` | `Init_ShockDriver` | 0x0013EE30 |
| 0x0013C588 | `Init_ShockEmulator` | `ShockDriver_VoiceSet_NumberRegist` | 0x0013EE88 |
| 0x0013C5C0 | `ShockEmulator_EmulationShot` | `ShockDriver_VoiceSet_Regist` | 0x0013EEC0 |
| 0x0013C638 | `ShockEmulator_EmulationWave` | `ShockDriver_VoiceSet_Remove` | 0x0013EF38 |
| 0x0013C6B8 | `Get_ShockRequestStruct` | `ShockDriver_GetShockVoiceSet` | 0x0013EFB8 |
| 0x0013C6E8 | `Reset_ShockRequestStruct` | `ShockDriver_GetShockVoice` | 0x0013EFE8 |
| 0x0013C760 | `iosThreadMain` | `ShockEmulator_EmulationWave` | 0x0013F060 |
| 0x0013C818 | `iosThreadStart` | `Get_ShockRequestStruct` | 0x0013F118 |
| 0x0013C860 | `iosThreadSleep` | `ShockRevice_Wave` | 0x0013F160 |
| 0x0013C930 | `iosThreadDestroy` | `Init_Shock` | 0x0013F230 |
| 0x0013CC28 | `iosGetIOSThreadFromId` | `iosThreadMain` | 0x0013F528 |
| 0x0013CEB0 | `iosThreadJoin` | `iosThreadStart` | 0x0013F7B0 |
| 0x0013CEC0 | `iosThreadCancelWakeup` | `iosThreadStop` | 0x0013F7C0 |
| 0x0013CEE0 | `iosSemaDelete` | `iosThreadDestroy` | 0x0013F7E0 |
| 0x0013D3C8 | `func_0013D3C8` | `iosGetIOSThreadFromId` | 0x0013FCC8 |
| 0x0013D410 | `func_0013D410` | `iosThreadWakeup` | 0x0013FD10 |
| 0x0013D430 | `func_0013D430` | `iosThreadJoin` | 0x0013FD30 |
| 0x0013D4B0 | `func_0013D4B0` | `iosThreadCancelWakeup` | 0x0013FDB0 |
| 0x0013D4E8 | `func_0013D4E8` | `iosSemaCreate` | 0x0013FDE8 |
| 0x0013D570 | `func_0013D570` | `iosSemaDelete` | 0x0013FE70 |
| 0x0013D698 | `func_0013D698` | `iosSemaReferStatus` | 0x0013FF98 |
| 0x0013D888 | `isysGObjKindTableInit` | `isysGObjInit` | 0x00140188 |
| 0x0013D8E0 | `isysGObjInit` | `cut_gobj_link` | 0x001401E0 |
| 0x0013DAD8 | `isysGObjRemoveAll` | `add_gobj_to_tail` | 0x001403D8 |
| 0x0013DBA8 | `add_gobj_to_tail` | `add_gobj_to_head` | 0x001404A8 |
| 0x0013DD08 | `isysGObjMoveHead` | `isysGObjAddAfterGObj` | 0x00140608 |
| 0x0013DE38 | `isysGObjAddAfterGObj` | `isysGObjAddBeforeGObj` | 0x00140738 |
| 0x0013DF70 | `isysGObjAddBeforeGObj` | `isysGetNbAllocedGObjs` | 0x00140870 |
| 0x0013DFB8 | `isysGetNbAllocedGObjs` | `isysGObjAlloc` | 0x001408B8 |
| 0x0013E2E0 | `isysGObjKindTableRemove` | `isysGObjMoveAfterGObj` | 0x00140BE0 |
| 0x0013E350 | `isysGObjMoveAfterGObj` | `isysGObjMoveBeforeGObj` | 0x00140C50 |
| 0x0013E3C0 | `isysGObjMoveBeforeGObj` | `isysGObjAdd` | 0x00140CC0 |
| 0x0013E4C8 | `isysGObjAdd` | `isysGObjAddHead` | 0x00140DC8 |
| 0x0013E5D0 | `isysGObjAddHead` | `isysGObjSearchFromObjLayoutID` | 0x00140ED0 |
| 0x0013EC18 | `isysGObjMoveObjDLAfterGObj` | `isysGObjLinkObjDL` | 0x00141518 |
| 0x0013ECB8 | `isysGObjMoveObjDLBeforeGObj` | `isysGObjLinkObjDLHead` | 0x001415B8 |
| 0x0013EDB0 | `isysGObjProcessInit` | `isysGObjDlInit` | 0x001416B0 |
| 0x0013EDF0 | `isysGObjProcAdd_` | `isysGObjMoveObjDLAfterGObj` | 0x001416F0 |
| 0x0013EE60 | `cut_gobj_process_link` | `isysGObjMoveObjDLBeforeGObj` | 0x00141760 |
| 0x0013F120 | `isysGObjProcAdd` | `cut_gobj_process_link` | 0x00141A20 |
| 0x0013F1A0 | `isysGObjProcAddS` | `isysGObjProcRemove` | 0x00141AA0 |
| 0x0013F1E8 | `isysGObjProcAddGOppArg` | `isysGObjProcessAlloc` | 0x00141AE8 |
| 0x0013F260 | `isysGObjProcPause` | `isysGObjProcAdd` | 0x00141B60 |
| 0x0013F290 | `isysGObjProcPauseAll` | `isysGObjProcAddS` | 0x00141B90 |
| 0x0013F2C0 | `isysGObjProcPausePtr` | `isysGObjProcAddGOppArg` | 0x00141BC0 |
| 0x0013F2F8 | `isysGObjProcActiveAll` | `isysGObjProcPauseAll` | 0x00141BF8 |
| 0x0013F330 | `isysInitialize` | `isysGObjProcPausePtr` | 0x00141C30 |
| 0x0013F360 | `func_0013F360` | `isysGObjProcActive` | 0x00141C60 |
| 0x0013F370 | `func_0013F370` | `isysGObjProcActiveAll` | 0x00141C70 |
| 0x0013F488 | `func_0013F488` | `iosOmInit` | 0x00141D88 |
| 0x0013F7F8 | `iosOmCreateDL` | `iosOmExeEachGObj` | 0x001420F8 |
| 0x0013F860 | `iosOmExeEachGObj` | `iosOmExeEachGObjAll` | 0x00142160 |
| 0x0013F900 | `iosOmExeEachGObjAll` | `iosOmReturnExeEachGObj` | 0x00142200 |
| 0x0013F998 | `iosOmReturnExeEachGObj` | `iosOmGetGObjStatus` | 0x00142298 |
| 0x0013F9C8 | `iosOmGetGObjStatus` | `iosOmSearchGObjId` | 0x001422C8 |
| 0x0013FA08 | `iosOmSearchGObjId` | `iosOmSearchGObjIdAll` | 0x00142308 |
| 0x00140A10 | `debug_DispSEInfo` | `soundDataSegAllClose` | 0x00144340 |
| 0x00140AC0 | `sound3DParamSet` | `soundSeVolSet` | 0x001443F0 |
| 0x00140CC0 | `_soundSeDefPlay` | `debug_DispSEInfo` | 0x001445F0 |
| 0x00141348 | `_soundSeDefStop` | `sound3DParamSet` | 0x00144C78 |
| 0x00141D10 | `soundSeEnvPlay` | `soundSeDefPitchSet` | 0x00145638 |
| 0x00142590 | `soundOutputModeGet` | `Ee2Iop` | 0x00145EB8 |
| 0x00142768 | `soundDataAreaSearch` | `soundBufAdpcmFree` | 0x00146098 |
| 0x00142788 | `soundDataAreaGet` | `soundDataAreaSearch` | 0x001460B8 |
| 0x00142BD8 | `soundSeDefPlayWithVolumeRate` | `soundSeDefPlay` | 0x00146508 |
| 0x00142C30 | `soundSeDefVolumeRateGet` | `soundSeDefPlayWithVolumeRate` | 0x00146560 |
| 0x00142C80 | `soundSeDefVolumeRateSet` | `soundSeDefVolumeRateGet` | 0x001465B0 |
| 0x00142CC0 | `soundSeGroupStop` | `soundSeDefVolumeRateSet` | 0x001465F0 |
| 0x00142CF8 | `soundSeGroupGet` | `soundSeGroupStop` | 0x00146628 |
| 0x00142D98 | `soundSePlayModeStop` | `soundSeGroupGet` | 0x001466C8 |
| 0x00142DC0 | `soundVBlank` | `soundSePlayModeStop` | 0x001466F0 |
| 0x00142F58 | `soundSeSemiCommonLoadChk` | `soundVBlank` | 0x00146888 |
| 0x00143080 | `sndBgmReadyNextStage` | `soundSeEnvDefaultSet` | 0x001469B0 |
| 0x001431A0 | `sndInit` | `debug_req` | 0x00146AD0 |
| 0x00143238 | `sndManager` | `sndBgmReadyNextStage` | 0x00146B68 |
| 0x001433E0 | `func_001433E0` | `ACTGame_DeleteActorInformation` | 0x00146D10 |
| 0x001433F0 | `func_001433F0` | `EXITDATA_GetNextPosition` | 0x00146D20 |
| 0x00143910 | `func_00143910` | `ACTCheckView` | 0x00147240 |
| 0x00143DE0 | `func_00143DE0` | `_ACTGame_SearchGObj` | 0x00147710 |
| 0x001443B8 | `func_001443B8` | `GetSkeltonOrient` | 0x00147D40 |
| 0x00148AB0 | `ActOrientTest` | `GetSkeltonPosition` | 0x0014CC80 |
| 0x00148B28 | `GetGirlHandlinkClInfo` | `SetDirectRootPositionWithNodePointLimit` | 0x0014CCF8 |
| 0x0014A6B8 | `func_0014A6B8` | `ActPara_StatusToFlag` | 0x0014EA48 |
| 0x00151DD8 | `actBoyRun` | `CorrectStickInfo` | 0x001577D0 |
| 0x00152730 | `actBoyBelift` | `ACTSearchEnemy` | 0x00157EE8 |
| 0x00154AD0 | `_ACTCorrectMsg` | `CollisCheckInRope` | 0x0015A648 |
| 0x00156040 | `WithMailFunc_WayBeginPosError` | `SetDirectRootPositionXZ` | 0x0015BD48 |
| 0x00157668 | `lever_nego1` | `correctJumpOrientByChain` | 0x0015D5A8 |
| 0x00157FB8 | `actCommonLever` | `debugDispSphere` | 0x0015E388 |
| 0x00158030 | `EBRAIN_SEND_MES` | `getLandOffset` | 0x0015E400 |
| 0x0015B4E8 | `funcCommonJumpDircorrect` | `ACTAdjustPlane` | 0x00161AE0 |
| 0x0015DC68 | `actEnemyForceSwitchToCarry` | `_MustChase` | 0x001644F8 |
| 0x00160948 | `enemy_dodge` | `GetFlyPosition` | 0x001679B0 |
| 0x00162FB0 | `actEnemyWalk` | `actEnemyHyde` | 0x0016A128 |
| 0x00163000 | `actEnemyRun` | `actEnemyFlagOnFree` | 0x0016A178 |
| 0x001630A8 | `actEnemyCarry` | `actEnemyFlagOnDead` | 0x0016A208 |
| 0x00163108 | `actEnemyNest` | `actEnemyFlagCheckDead` | 0x0016A268 |
| 0x00163130 | `funcEnemyCarryFail` | `actEnemyFlagCheckActive` | 0x0016A290 |
| 0x00163E58 | `_Clip` | `MakeCollisionDependGObjList` | 0x0016B038 |
| 0x00163F48 | `__ClipWall` | `GetReflectionElement` | 0x0016B128 |
| 0x00164088 | `__ClipFloor` | `clip_wall_1` | 0x0016B268 |
| 0x00164840 | `DrawGObjFloorCollision` | `DispCollisionPC` | 0x0016BA20 |
| 0x001649E0 | `DBG_VECTOR` | `makeCollisionBlockTable` | 0x0016BBC0 |
| 0x00164C40 | `GetEdgeOfFloor` | `_Clip` | 0x0016BE20 |
| 0x00165358 | `ClipWallDebug` | `DrawGObjFloorCollision` | 0x0016C538 |
| 0x00165590 | `ClipWall` | `DBG_VECTOR` | 0x0016C770 |
| 0x00165600 | `ClipWallR` | `GetEdgeOfFloor` | 0x0016C7E0 |
| 0x00165C30 | `ClipWallWaveForce` | `DrawCollisionRay` | 0x0016CE10 |
| 0x001661D8 | `ClipWallEField` | `ClipWallDebug` | 0x0016D3B8 |
| 0x001661F8 | `ClipWallBoxStop` | `ClipWall` | 0x0016D3D8 |
| 0x00166218 | `ClipWallAdjustPos` | `ClipWallR` | 0x0016D3F8 |
| 0x00166238 | `ClipWallE` | `ClipWallWaveForce` | 0x0016D418 |
| 0x00166258 | `ClipWallCheckCB` | `ClipWallFuchiHangWalkStop` | 0x0016D438 |
| 0x00166298 | `ClipFloor` | `ClipWallEField` | 0x0016D478 |
| 0x001662B8 | `ClipFloorE` | `ClipWallBoxStop` | 0x0016D498 |
| 0x001662D8 | `ClipFloorR` | `ClipWallAdjustPos` | 0x0016D4B8 |
| 0x001662F8 | `ClipFloorIH` | `ClipWallE` | 0x0016D4D8 |
| 0x00166318 | `ClipFloorCheckCB` | `ClipWallCheckCB` | 0x0016D4F8 |
| 0x00166368 | `ChangeFieldCollisionDebugMode` | `ClipFloor` | 0x0016D548 |
| 0x00166388 | `LoadCollision` | `ClipFloorE` | 0x0016D568 |
| 0x001663A8 | `DrawCollision` | `ClipFloorR` | 0x0016D588 |
| 0x001663C8 | `ClipPlane` | `ClipFloorIH` | 0x0016D5A8 |
| 0x001663E8 | `GetOrientOfWall` | `ClipFloorCheckCB` | 0x0016D5C8 |
| 0x00166480 | `fzShowV` | `ChangeFieldCollisionDebugMode` | 0x0016D660 |
| 0x001664C0 | `fzShowM` | `LoadCollision` | 0x0016D6A0 |
| 0x00166508 | `fzMagnitude2f` | `DrawCollision` | 0x0016D6E8 |
| 0x001665E8 | `fzMagnitude3f` | `ClipPlane` | 0x0016D7C8 |
| 0x00168008 | `func_00168008` | `fzShowV` | 0x0016F1E8 |
| 0x00168070 | `func_00168070` | `fzShowM` | 0x0016F250 |
| 0x001680D0 | `func_001680D0` | `fzMagnitude2f` | 0x0016F2B0 |
| 0x001680F8 | `func_001680F8` | `fzMagnitude3f` | 0x0016F2D8 |
| 0x00168128 | `func_00168128` | `fzMagnitudefv` | 0x0016F308 |
| 0x00173F48 | `func_00173F48` | `iosCdvdBackGroundReadJimaku` | 0x0017CB20 |
| 0x00173FA8 | `func_00173FA8` | `jimakuHandler` | 0x0017CB80 |
| 0x00174580 | `func_00174580` | `jimakuMgrJump` | 0x0017D1C0 |
| 0x00174650 | `func_00174650` | `jimakuMgrEnd` | 0x0017D290 |
| 0x00174698 | `func_00174698` | `jimakuBegin` | 0x0017D2D8 |
| 0x001746B8 | `func_001746B8` | `jimakuNext` | 0x0017D2F8 |
| 0x001746E8 | `_FUNC_GetWay_begin` | `jimakuJump` | 0x0017D328 |
| 0x00174E10 | `GetWay_begin` | `avoid_obstacle2` | 0x0017DA50 |
| 0x001755A0 | `BridgeBox` | `create_box_bridge` | 0x0017E1E0 |
| 0x00175E38 | `visible_waypoint_of_all_except_gid` | `GetNearNigePointN` | 0x0017EAA0 |
| 0x00176490 | `visible_waypoint_of_all_except_gid_ThreadVersion` | `GetWay_begin` | 0x0017F0F8 |
| 0x001764B8 | `visible_waypoint_of_all_except_temp_ThreadVersion` | `DeleteGuideWay` | 0x0017F120 |
| 0x00176BE8 | `shortest_path` | `short_direction_between_wp` | 0x0017F850 |
| 0x00176DD0 | `shortest_path_ThreadVersion` | `wgid_next` | 0x0017FA38 |
| 0x001770D8 | `set_check_wp` | `WayUtilWorkFree` | 0x0017FD48 |
| 0x00177990 | `nearest_waypoint_from_gobj` | `set_check_wp` | 0x00180600 |
| 0x00177AE8 | `nearest_waypoint_by_lineseg_of_group` | `set_bridge` | 0x00180758 |
| 0x00177DB0 | `nearest_waypoint_by_lineseg` | `nearest_waypoint_of_group` | 0x00180A20 |
| 0x00177E48 | `nearest_waypoint_by_lineseg_of_group_from_gobj` | `nearest_waypoint` | 0x00180AB8 |
| 0x00177EE8 | `nearest_waypoint_by_lineseg_from_gobj` | `nearest_waypoint_from_gobj` | 0x00180B58 |
| 0x00177F90 | `waypoint_with_range` | `nearest_waypoint_by_lineseg_of_group` | 0x00180C00 |
| 0x00178040 | `nearest_waypoint_of_all_except_group` | `nearest_waypoint_by_lineseg` | 0x00180CB0 |
| 0x001780F8 | `nearest_waypoint_of_all_not_bridge_except_group` | `nearest_waypoint_by_lineseg_of_group_from_gobj` | 0x00180D68 |
| 0x001781B8 | `nearest_waypoint_of_all` | `nearest_waypoint_by_lineseg_from_gobj` | 0x00180E28 |
| 0x00178278 | `visible_waypoint_of_all` | `waypoint_with_range` | 0x00180EE8 |
| 0x00178308 | `visible_waypoint_of_all_from_gobj` | `nearest_waypoint_of_all_except_group` | 0x00180F78 |
| 0x001783B0 | `visible_waypoint` | `nearest_waypoint_of_all_not_bridge_except_group` | 0x00181020 |
| 0x00178490 | `visible_waypoint_from_gobj` | `nearest_waypoint_of_all` | 0x00181100 |
| 0x00178538 | `get_wp_nearest_bridge_side_me` | `visible_waypoint_of_all` | 0x001811A8 |
| 0x00178558 | `get_wp_nearest_bridge_side_bridge` | `visible_waypoint_of_all_from_gobj` | 0x001811C8 |
| 0x00178588 | `direction_across_bridge` | `visible_waypoint` | 0x001811F8 |
| 0x001786A0 | `waybridge_between_group` | `visible_waypoint_from_gobj` | 0x00181310 |
| 0x001788E8 | `bridge_waypoint_side_bridge` | `direction_across_bridge` | 0x00181558 |
| 0x00178978 | `waypoint_connect_group_side_bridge` | `waybridge_between_group` | 0x001815E8 |
| 0x00178A18 | `NearestWgFromTarget` | `bridge_waypoint_side_me` | 0x00181688 |
| 0x00178AC0 | `wpsort_compfnc` | `waypoint_connect_group_side_me` | 0x00181730 |
| 0x00178B08 | `func_00178B08` | `bridge_waypoint_side_bridge` | 0x00181778 |
| 0x00178BB8 | `func_00178BB8` | `waypoint_connect_group_side_bridge` | 0x00181828 |
| 0x00178C00 | `func_00178C00` | `NearestWgFromTarget` | 0x00181870 |
| 0x00178DB0 | `func_00178DB0` | `gflagChk` | 0x00181A48 |
| 0x00178DD8 | `func_00178DD8` | `gflagOn` | 0x00181A70 |
| 0x00178E08 | `func_00178E08` | `gflagOff` | 0x00181AA0 |
| 0x00178E98 | `gflagLoad` | `scpSetCageVelocityFriction` | 0x00181B30 |
| 0x00178ED8 | `gflagChk` | `scpPlayMotDir` | 0x00181B70 |
| 0x00179120 | `func_00179120` | `scpTrans` | 0x00181DC0 |
| 0x00179130 | `func_00179130` | `scpTriggerBallTargetMan` | 0x00181DD0 |
| 0x0017A198 | `func_0017A198` | `scpDispOnAllWithKind` | 0x00183740 |
| 0x0017A1E0 | `func_0017A1E0` | `scpActivateAllWithKind` | 0x00183788 |
| 0x0017D318 | `func_0017D318` | `actConte12Jimaku` | 0x00186C40 |
| 0x0017DC10 | `func_0017DC10` | `BoySekikaTexScroll` | 0x001874A0 |
| 0x0017E160 | `func_0017E160` | `warpGirlOutStage` | 0x00187F00 |
| 0x0017F450 | `func_0017F450` | `brainAddLevelGirl` | 0x00189738 |
| 0x0017FD80 | `brainStatusDefaultSet` | `brainGetLevel` | 0x00189F50 |
| 0x0017FE70 | `brainGetTarget` | `brainInitGirlSet` | 0x0018A050 |
| 0x00180238 | `DispCameraGroup` | `EnterMenu` | 0x0018A478 |
| 0x00180E80 | `dispCameraGroupType2` | `DispCameraGroup` | 0x0018B0C0 |
| 0x001817A8 | `CameraEdit_DispBoxType2_Plane` | `DispAxisArrow` | 0x0018B9E8 |
| 0x00181DC8 | `menuGroupEdit` | `dispCameraGroupType2` | 0x0018C008 |
| 0x001827A0 | `menuPinEdit` | `CameraEdit_DispBoxType2_Plane` | 0x0018C9E0 |
| 0x00183F10 | `_CameraEdit_del_box` | `test_camedit` | 0x0018E150 |
| 0x00183F28 | `_CameraEdit_del_pin` | `_CameraEdit_del_box` | 0x0018E168 |
| 0x00184080 | `CameraEdit_add_box` | `_CameraEdit_del_pin` | 0x0018E2C0 |
| 0x00184200 | `CameraEdit_add_pin` | `CameraEdit_add_box` | 0x0018E440 |
| 0x001844E8 | `CameraEdit_del_box` | `CameraEdit_add_pin` | 0x0018E728 |
| 0x00184798 | `CameraEdit_del_pin` | `CameraEdit_del_box` | 0x0018E9D8 |
| 0x001847D0 | `CameraEdit_DispBox` | `CameraEdit_del_pin` | 0x0018EA10 |
| 0x00184820 | `CameraEdit_Save` | `CameraEdit_Reflect` | 0x0018EA60 |
| 0x00184830 | `debug_NMarker` | `CameraEdit_Save` | 0x0018EA70 |
| 0x00184840 | `debug_Marker` | `debug_NMarker` | 0x0018EA80 |
| 0x001848C8 | `debug_CameraEditor` | `InitCameraEditor` | 0x0018EB08 |
| 0x001848D8 | `CameraSetCameraSet` | `debug_CameraEditor` | 0x0018EB18 |
| 0x00185740 | `AddPluralCameraSet` | `CameraSetCameraSet` | 0x0018F980 |
| 0x001857C8 | `GetPluralCameraSet` | `GetRootPositionForCamera` | 0x0018FA08 |
| 0x00185A68 | `GetSizeOfCameraSetBinary` | `ico2camera_GetGroupNearest` | 0x0018FCA8 |
| 0x00188660 | `func_00188660` | `GetCameraGroupFromPosition` | 0x00192C48 |
| 0x00188B00 | `func_00188B00` | `GetSizeOfCameraSetBinary` | 0x001930E8 |
| 0x00188B48 | `func_00188B48` | `SetCameraTargetPosition` | 0x00193130 |
| 0x00188BE0 | `func_00188BE0` | `SetWSMatrix` | 0x001931C8 |
| 0x00189358 | `ConvertCameraSet` | `DebugCameraManual` | 0x001939B8 |
| 0x00189390 | `MakeCameraMatrix` | `DebugCameraSemiAuto` | 0x001939F0 |
| 0x00189450 | `CameraEditManual` | `BackToGameCamera` | 0x00193AB0 |
| 0x00189558 | `DebugCameraManual` | `GetCameraInfomationFromGlobalPosition` | 0x00193BB8 |
| 0x00189F50 | `GetCameraInfomationFromGlobalPosition` | `Camctrl_ExitEveRock` | 0x00194870 |
| 0x00189FB0 | `SetCameraMatrix` | `GetCameraDefaultTargetGObj` | 0x001948D0 |
| 0x0018B2A0 | `InitChainGeo` | `chain_simulate_term` | 0x00195F68 |
| 0x0018B4A8 | `ChainGeo` | `correct_vector` | 0x00196170 |
| 0x0018B638 | `ChainDL` | `pendulum_Process` | 0x00196300 |
| 0x0018DD78 | `eBrainProcess` | `GetRootPositionHandExtra` | 0x00198810 |
| 0x0018E430 | `func_0018E430` | `eBrainProcess` | 0x00198F70 |
| 0x0018E830 | `func_0018E830` | `eBrainGetTarget` | 0x00199370 |
| 0x0018F1A8 | `func_0018F1A8` | `eBrainInit` | 0x00199CE8 |
| 0x0018F1F0 | `func_0018F1F0` | `eBrainStatusSet` | 0x00199D30 |
| 0x0018F580 | `func_0018F580` | `EnemyCtrlBeforeFunc` | 0x0019A0C0 |
| 0x0018F608 | `func_0018F608` | `InitEnemyCtrlGeo` | 0x0019A148 |
| 0x0018F620 | `EnemyCtrlBeforeFunc` | `IsSelectID_EnemyCtrl` | 0x0019A160 |
| 0x0018F850 | `IsSelectID_EnemyCtrl` | `fightSoundProcess` | 0x0019A390 |
| 0x0018F950 | `fightSoundProcessMain` | `fightSoundClose` | 0x0019A490 |
| 0x001918B0 | `_OrientGV` | `GetMatrixDirectionToZ` | 0x0019C5F0 |
| 0x00191A18 | `_FrontGV` | `_InterRotGV` | 0x0019C758 |
| 0x00191B60 | `RotateAccordingToStick_PatternThree` | `_DistxzSqGV` | 0x0019C8A0 |
| 0x00191BC8 | `ClearHandCameraCorrect` | `_DistGV` | 0x0019C908 |
| 0x00191C40 | `SetLimitHandCameraCorrect` | `_MoveGV` | 0x0019C980 |
| 0x00191D90 | `func_00191D90` | `_AbsRotyGV` | 0x0019CAD0 |
| 0x00191DB8 | `func_00191DB8` | `_ApplyRyGV` | 0x0019CAF8 |
| 0x00191E78 | `func_00191E78` | `_RotGV` | 0x0019CBB8 |
| 0x00192008 | `func_00192008` | `_OrientGV` | 0x0019CD48 |
| 0x00192040 | `func_00192040` | `_FrontGV` | 0x0019CD80 |
| 0x001925C0 | `ClearMailAdditionalData` | `ClearHandCameraCorrect` | 0x0019D528 |
| 0x001926A8 | `func_001926A8` | `SetLimitHandCameraCorrect` | 0x0019D610 |
| 0x00192A08 | `func_00192A08` | `before_DrawPolygon` | 0x0019DFC0 |
| 0x00192B50 | `func_00192B50` | `before_DrawLine` | 0x0019E108 |
| 0x00192B80 | `after_DrawPolygon` | `DrawPolygon` | 0x0019E138 |
| 0x00192D10 | `before_DrawLine` | `IsPointIsInScreen` | 0x0019E2C8 |
| 0x00192D88 | `after_DrawLine` | `interp_vector_sa` | 0x0019E340 |
| 0x00194F18 | `GatherEffect_Set` | `GatherEffect_InqEnd` | 0x001A0560 |
| 0x00195848 | `effect_end_func` | `itou_boss_gflag_init` | 0x001A0DB0 |
| 0x001962C0 | `func_001962C0` | `DrawLightning2` | 0x001A1938 |
| 0x00196F08 | `DrawLightning2` | `DrawLightning` | 0x001A2580 |
| 0x001970F8 | `DrawLightning` | `scale_m34` | 0x001A2770 |
| 0x00199688 | `queenBallBeforeFunc` | `queen_barrier_set_damage` | 0x001A4E48 |
| 0x001996A0 | `InitQueenBallGeo` | `makeRefractST` | 0x001A4E60 |
| 0x00199BD0 | `queen_barrier_set_damage` | `queen_barrier_disp_init` | 0x001A53A0 |
| 0x00199E10 | `makeRefractST` | `queen_barrier_anim` | 0x001A55E0 |
| 0x00199E48 | `queen_barrier_disp_proc` | `GetStageDifferenceMatrix` | 0x001A5618 |
| 0x0019A018 | `queen_barrier_disp_init` | `StageOrientGet2` | 0x001A57E8 |
| 0x0019A230 | `queen_barrier_anim` | `OtherStagePositionGet` | 0x001A5A00 |
| 0x0019A4B8 | `func_0019A4B8` | `StageOrientGet` | 0x001A5C88 |
| 0x0019AB50 | `StageOrientGet` | `termAll` | 0x001A63C8 |
| 0x0019AC48 | `func_0019AC48` | `movie_init` | 0x001A64C0 |
| 0x0019AE20 | `func_0019AE20` | `movie_end` | 0x001A6698 |
| 0x0019AF30 | `switchThread` | `movie_proc` | 0x001A67A8 |
| 0x0019B068 | `movie_init` | `readBufBeginPut` | 0x001A68C8 |
| 0x0019B098 | `movie_end` | `readBufEndPut` | 0x001A68F8 |
| 0x0019B0D8 | `movie_proc` | `readBufBeginGet` | 0x001A6938 |
| 0x0019B120 | `free_buffer` | `readBufEndGet` | 0x001A6980 |
| 0x0019B3E0 | `strFileRead` | `videoCallback` | 0x001A6C40 |
| 0x0019BAC8 | `voBufIncCount` | `voBufReset` | 0x001A7328 |
| 0x0019BAD8 | `voBufGetData` | `voBufIsFull` | 0x001A7338 |
| 0x0019BAF0 | `voBufGetTag` | `voBufIncCount` | 0x001A7350 |
| 0x0019BB68 | `initGeometryState` | `voBufGetData` | 0x001A73C8 |
| 0x0019BBA0 | `initMatrixDObj` | `voBufGetTag` | 0x001A7400 |
| 0x0019C158 | `initPolygonState` | `initMatrixDObj` | 0x001A79B8 |
| 0x0019CAA8 | `func_0019CAA8` | `LinkParentOfDObj` | 0x001A8320 |
| 0x0019CC60 | `stop_free_resources` | `stage_initialize` | 0x001A84E0 |
| 0x0019CD10 | `stage_initialize` | `exit_stage` | 0x001A8590 |
| 0x0019DD98 | `backStageLoad` | `routeSetPos` | 0x001A9628 |
| 0x0019E5A8 | `func_0019E5A8` | `backStageProcessInit` | 0x001A9E38 |
| 0x001A02F8 | `debug_Assert` | `GetPObjAddress` | 0x001ABC20 |
| 0x001A03B0 | `debug_LogPrintf` | `debug_openLog` | 0x001ABCD8 |
| 0x001A03C8 | `debug_SaveDebugOptionFile` | `debug_LogPrintf` | 0x001ABCF0 |
| 0x001A0760 | `debug_VariableInit` | `debug_SetDmaCallback` | 0x001AC088 |
| 0x001A08D8 | `debug_Load` | `debug_Init` | 0x001AC258 |
| 0x001A11D8 | `debug_PrintCharacter` | `debug_makeBackImage` | 0x001ACBC8 |
| 0x001A1378 | `debug_PrintFont` | `debug_PrintCharacter` | 0x001ACD68 |
| 0x001A1668 | `debug_FlushFontWindow` | `debug_PrintFont` | 0x001AD058 |
| 0x001A17C0 | `debug_FlushFont` | `debug_FlushFontWindow` | 0x001AD1B0 |
| 0x001A1998 | `draw_shikaku` | `draw_batsu` | 0x001AD388 |
| 0x001A1AC0 | `debug_brainBar` | `draw_shikaku` | 0x001AD4B0 |
| 0x001A1FB0 | `debug_DrawBar` | `debug_MakeBarString` | 0x001AD9A0 |
| 0x001A3070 | `debug_WriteBMP` | `debug_ResizeSnapShot` | 0x001AEB10 |
| 0x001A9A50 | `ParentSimpleObjGeo` | `initLineTraceTable` | 0x001B4FA0 |
| 0x001A9C20 | `ParentSimpleObjDL` | `traceLine` | 0x001B5170 |
| 0x001A9FC0 | `InitParentSimpleObjGeo` | `dispSource` | 0x001B5510 |
| 0x001AAC60 | `func_001AAC60` | `debugExceptionInit` | 0x001B61B0 |
| 0x001AAFA0 | `func_001AAFA0` | `debug_TargetGObj` | 0x001B64F0 |
| 0x001AB108 | `func_001AB108` | `init_debug_menu` | 0x001B6658 |
| 0x001AB908 | `func_001AB908` | `gamesysNObjInfoInit` | 0x001B6F08 |
| 0x001AB980 | `func_001AB980` | `gamesysObjInfoStageInitPosSaveUnlock` | 0x001B6F80 |
| 0x001ABF40 | `func_001ABF40` | `gamesysVersionLoad` | 0x001B7540 |
| 0x001ABF88 | `func_001ABF88` | `gamesysVersionSave` | 0x001B7588 |
| 0x001AD128 | `kanbanInit` | `kanbanReqAdd` | 0x001B8738 |
| 0x001AD790 | `kanbanReqDel` | `fade_exec` | 0x001B8DE0 |
| 0x001ADA70 | `kanbanReqAllDel` | `kanbanReqDel` | 0x001B90D8 |
| 0x001ADAA8 | `kanbanReqAllDelFade` | `kanbanReqDelFade` | 0x001B9110 |
| 0x001ADAC8 | `kanbanExec` | `kanbanReqAllDel` | 0x001B9130 |
| 0x001ADB00 | `func_001ADB00` | `kanbanReqAllDelFade` | 0x001B9168 |
| 0x001ADB38 | `func_001ADB38` | `kanbanExec` | 0x001B91A0 |
| 0x001ADFC8 | `func_001ADFC8` | `kanbanBootInit` | 0x001B9A78 |
| 0x001AE050 | `kanbanBootStart` | `_la_mcard_error_check` | 0x001B9B00 |
| 0x001AE4A8 | `func_001AE4A8` | `_la_set_current_port_2` | 0x001B9F88 |
| 0x001AE800 | `func_001AE800` | `_la_set_current_port_lock_2` | 0x001BA2E0 |
| 0x001AE9C8 | `func_001AE9C8` | `_la_set_current_port_new` | 0x001BA4A8 |
| 0x001B54F0 | `GetStageStartInfo` | `ChangeStageStartInfo` | 0x001C1D68 |
| 0x001B55D8 | `func_001B55D8` | `MoveNextStage_Set` | 0x001C1E50 |
| 0x001B5638 | `staffRollStart` | `test_nextstage_firstwalk_set` | 0x001C1EB0 |
| 0x001B5648 | `staffRollScroll` | `GetStageStartInfo` | 0x001C1EC0 |
| 0x001B56D0 | `staffRollNameOut` | `MoveNextStage_Clear` | 0x001C1F48 |
| 0x001B5738 | `staffRollWide` | `staffRollScroll` | 0x001C2000 |
| 0x001B59F0 | `func_001B59F0` | `staffRollMain` | 0x001C22B8 |
| 0x001B5BE8 | `InitAP1` | `staffRollWide` | 0x001C24B0 |
| 0x001B8D08 | `func_001B8D08` | `IsActCharDead` | 0x001C56A0 |
| 0x001B8DE8 | `InitAttackCheckBoundaryGeo` | `SetActressLight` | 0x001C5780 |
| 0x001B9378 | `CreateAttackCheckBoundary` | `InitAttackCheckBoundaryGeo` | 0x001C5D00 |
| 0x001B93C8 | `GetAttackCheckBoundaryManagerStatus` | `AttackCheckBoundaryGeo` | 0x001C5D50 |
| 0x001B94A0 | `switchReleaseSE` | `actAttackCheckBoundaryStart` | 0x001C5E28 |
| 0x001BAB08 | `onPath` | `getNearestPosition` | 0x001C7648 |
| 0x001BC098 | `execFallDown` | `_checkItemBreak` | 0x001C8CA8 |
| 0x001BCA10 | `MoveBoxWithHoldPoint` | `_checkItemCollision` | 0x001C9688 |
| 0x001BD9D0 | `ExecBoxMoveStartReaction` | `GetBoxGlobalHoldPoint` | 0x001CA6D8 |
| 0x001BDB18 | `SetSwitchTriggerFunc` | `BoxGeoRestore` | 0x001CA820 |
| 0x001BE0E8 | `func_001BE0E8` | `initParentize` | 0x001CADF0 |
| 0x001BEA30 | `InitBoyGeo` | `LightLineDL` | 0x001CB838 |
| 0x001BF318 | `CageRideFunc` | `LightLineGeo` | 0x001CC630 |
| 0x001C0648 | `ChandelierDL` | `ChandelierGeo` | 0x001CD9A8 |
| 0x001C0BE0 | `CreateClipCollisionManagerGObj` | `GetChainExWeightGlobalPos` | 0x001CDF40 |
| 0x001C0BF8 | `RequestClipCollision` | `bindExWeight` | 0x001CDF58 |
| 0x001C1078 | `thStart` | `bind2` | 0x001CE3D8 |
| 0x001C13C0 | `func_001C13C0` | `calc2` | 0x001CE720 |
| 0x001C1B68 | `TestDispChainAnimation` | `SetChainExtendedWeight` | 0x001CEDC8 |
| 0x001C1C98 | `GetChainExWeightGlobalPos` | `GetClothAnimation` | 0x001CEEF8 |
| 0x001C2860 | `bindExWeight` | `clipCylinderCollision` | 0x001D00D8 |
| 0x001C3300 | `SetChainExtendedWeight` | `DispMeshWire` | 0x001D0FA8 |
| 0x001C3540 | `GetClothAnimation` | `DispCloth4D` | 0x001D11E8 |
| 0x001C65A8 | `func_001C65A8` | `draw` | 0x001D44B8 |
| 0x001C68B0 | `func_001C68B0` | `drawHT` | 0x001D47C0 |
| 0x001C6DA0 | `func_001C6DA0` | `renderViewCoordZSphere` | 0x001D4CB0 |
| 0x001C8B80 | `renderViewCoordZSphere` | `SetDarkVolumeEffect` | 0x001D6AA8 |
| 0x001C8E08 | `SetDarkVolumeEffect` | `InitGameOverEffect` | 0x001D6D30 |
| 0x001C90F8 | `dispCircle2` | `_dispParam` | 0x001D7088 |
| 0x001C96E0 | `dispEffectToolField` | `dispXZYZCircle` | 0x001D7670 |
| 0x001C9AA8 | `EditTarget` | `dispCircle2` | 0x001D7A38 |
| 0x001C9D30 | `moveEffectToolGeometry` | `dispEffectToolField` | 0x001D7CC0 |
| 0x001CA008 | `execEffectTool` | `EditTarget` | 0x001D7F98 |
| 0x001CA328 | `setEnemyObject` | `moveEffectToolGeometry` | 0x001D82B8 |
| 0x001CB900 | `EnemySetfAppearAll` | `EnemyDL` | 0x001D98E8 |
| 0x001CBB60 | `SetEnemyHitGeometryAction` | `enemySetParticleDie` | 0x001D9BB8 |
| 0x001CCA00 | `func_001CCA00` | `DispEnemyFootPrints` | 0x001DAA98 |
| 0x001CCB60 | `func_001CCB60` | `DispPointBlur` | 0x001DABF8 |
| 0x001CCBC0 | `func_001CCBC0` | `UpdateEnemyEye` | 0x001DAC58 |
| 0x001CCCB0 | `FlagGeo` | `ResetEnemyEye` | 0x001DAD48 |
| 0x001CD630 | `func_001CD630` | `DispFlyInfo` | 0x001DBBE0 |
| 0x001CD658 | `func_001CD658` | `InitFlyInfo` | 0x001DBC08 |
| 0x001CE620 | `playSERandomID` | `ExecuteSEPackageWithGroupVariation` | 0x001DCC68 |
| 0x001CF9E8 | `HoldItem` | `avoidInsideOfWall` | 0x001DE900 |
| 0x001D15C0 | `func_001D15C0` | `Draw2DLine` | 0x001E0840 |
| 0x001D16E0 | `SetLodLevel` | `Draw2DLineSeg_Start` | 0x001E0960 |
| 0x001D16F0 | `func_001D16F0` | `Draw2DLineSeg_Loop` | 0x001E0970 |
| 0x001D1790 | `func_001D1790` | `Draw2DLineG` | 0x001E0A10 |
| 0x001D1948 | `func_001D1948` | `_getLine` | 0x001E0BC8 |
| 0x001D1D58 | `func_001D1D58` | `DrawLine` | 0x001E0FD8 |
| 0x001D1DF0 | `func_001D1DF0` | `DrawLineG` | 0x001E1070 |
| 0x001D1F68 | `func_001D1F68` | `pursueNodeList` | 0x001E1218 |
| 0x001D2220 | `InitMotionMemorySize` | `dispSquare2` | 0x001E14D0 |
| 0x001D5FD8 | `checkActPointWithHeight` | `checkUpperWallState` | 0x001E54C8 |
| 0x001D7048 | `checkCliffAndWallStateOfLastPlane` | `dispActNode` | 0x001E6570 |
| 0x001DDB10 | `func_001DDB10` | `SkelTest` | 0x001ED268 |
| 0x001DDB68 | `func_001DDB68` | `SkelTestGeo` | 0x001ED2C0 |
| 0x001DF620 | `getStreamMotionGeometry` | `ForTest_ForceShiftMotion` | 0x001EEDA8 |
| 0x001E1BF0 | `dispProgressBar` | `setRootUpdateMode` | 0x001F17F0 |
| 0x001E1C08 | `objMenuProc` | `dispProgressBar` | 0x001F1808 |
| 0x001E2D78 | `func_001E2D78` | `lookAtTest` | 0x001F29D8 |
| 0x001E3BE8 | `func_001E3BE8` | `InitMoveColTestGeo` | 0x001F3848 |
| 0x001E3FE8 | `execParticleEffect` | `setParticleEffectGeometry` | 0x001F3C48 |
| 0x001E5368 | `SetParticleEffectGeometry` | `dispParticleEffect` | 0x001F4988 |
| 0x001E5BB0 | `InitParticleEffects` | `SetParticleEffectPackage` | 0x001F51A0 |
| 0x001E5E38 | `DeleteParticleEffectsByID` | `GetParticleEffectPackage` | 0x001F54A8 |
| 0x001E6118 | `func_001E6118` | `InitParticleLayoutGeo` | 0x001F57E0 |
| 0x001E6AE8 | `InitRopeFixGeo` | `RopeFixGeo` | 0x001F7038 |
| 0x001E6C80 | `moveStartSE` | `GetRotObjectHoldPoint` | 0x001F7130 |
| 0x001E72E8 | `CallSpidersToReviveEnemy` | `InitSpiderLayoutGeo` | 0x001F7A98 |
| 0x001E89E8 | `func_001E89E8` | `ExecSpiderGroupManager` | 0x001F8FE0 |
| 0x001E8C18 | `func_001E8C18` | `InitSpiderGroupManager` | 0x001F9210 |
| 0x001E8C40 | `func_001E8C40` | `EntryRevivedSpiderGroupManager` | 0x001F9238 |
| 0x001E8C68 | `func_001E8C68` | `DispAllSpiderGroups` | 0x001F9260 |
| 0x001E8D10 | `func_001E8D10` | `EntryToSpiderGroupManagerForReviveMaster` | 0x001F9308 |
| 0x001E8D38 | `func_001E8D38` | `getReviveEnemyGObj` | 0x001F9330 |
| 0x001E8D98 | `func_001E8D98` | `InitStageMultiBgaManager` | 0x001F9460 |
| 0x001E94E8 | `func_001E94E8` | `copyAlphaChannelOfWork0ToFeedBackArea` | 0x001F9D28 |
| 0x001E9BD0 | `func_001E9BD0` | `testAA` | 0x001FA488 |
| 0x001E9D28 | `func_001E9D28` | `subWork1ToCurrentFB` | 0x001FA5E0 |
| 0x001EA658 | `func_001EA658` | `pasteBackLightShadowToFB` | 0x001FB028 |
| 0x001EA798 | `func_001EA798` | `makeMaskPatternToWork2` | 0x001FB168 |
| 0x001EA888 | `blur` | `makeFullScreenFlareBefore` | 0x001FB258 |
| 0x001ECC10 | `func_001ECC10` | `InitStormPackage` | 0x001FD5F8 |
| 0x001ECEC8 | `func_001ECEC8` | `ClipStormByVolume` | 0x001FD8B0 |
| 0x001ED090 | `func_001ED090` | `ClipStormByCamera` | 0x001FDA78 |
| 0x001ED9E8 | `func_001ED9E8` | `PlayStreamMotion` | 0x001FE680 |
| 0x001EDCC0 | `PlayStreamMotion` | `_transRingBuf` | 0x001FEA18 |
| 0x001EE7E0 | `func_001EE7E0` | `InitSugiLeafGeo` | 0x001FF628 |
| 0x001EF310 | `func_001EF310` | `actWaySystemCore` | 0x00200B50 |
| 0x001F0A18 | `calcDynamicGeometry` | `dispInsectNet` | 0x002023F0 |
| 0x001F1658 | `LightTorchOffOfWeapon` | `drawSenpuukiHaneUnit` | 0x00203678 |
| 0x001F1FD8 | `InitWindManager` | `ExecWindManager` | 0x00203FF8 |
| 0x001F2130 | `func_001F2130` | `SetWindManager` | 0x00204150 |
| 0x001F2288 | `DispWireLetter` | `GetRegularizedWindSpeed` | 0x002042A8 |
| 0x001F2368 | `DispWireString` | `DispWireLetter` | 0x00204500 |
| 0x001F24C0 | `DefaultColorWireString` | `DispWireString` | 0x00204658 |
| 0x001F25C8 | `ChangeColorWireString` | `DefaultColorWireString` | 0x00204760 |
| 0x001F25F8 | `Draw2DBox` | `ChangeColorWireString` | 0x00204790 |
| 0x001F2610 | `func_001F2610` | `Draw2DBox` | 0x002047A8 |
| 0x001F26F0 | `func_001F26F0` | `outerProcess` | 0x00204888 |
| 0x001F2818 | `func_001F2818` | `simulate` | 0x002049B0 |
| 0x001F3690 | `GetWormRoute` | `GetWormCaptureVector` | 0x00205828 |
| 0x001F3C10 | `matrix_init` | `dma_init` | 0x00205DA8 |
| 0x001F3C78 | `malloc_MemCpy` | `matrix_init` | 0x00205E10 |
| 0x001F3CA0 | `freeseki` | `mallocseki` | 0x00205E38 |
| 0x001F3D80 | `resetmallocseki` | `freeseki` | 0x00205F18 |
| 0x001F3DA8 | `reallocseki` | `mallocsekistage` | 0x00205F40 |
| 0x001F3DF0 | `func_001F3DF0` | `reallocseki` | 0x00205F88 |
| 0x001F7248 | `bga_ResetCamera` | `bga_GetCameraMatrix` | 0x0020A610 |
| 0x001F7718 | `func_001F7718` | `font_CheckAlign` | 0x0020AA90 |
| 0x001F80E8 | `dl_Swap` | `font_GetHeight` | 0x0020B410 |
| 0x001F8110 | `dl_PushPriority` | `font_Init` | 0x0020B438 |
| 0x001F8248 | `dl_Debug` | `dl_Clear` | 0x0020B570 |
| 0x001F84E8 | `dl_OpenDma` | `dl_Debug` | 0x0020B810 |
| 0x001F8520 | `dl_GetPri` | `dl_CloseDma` | 0x0020B848 |
| 0x001F8660 | `func_001F8660` | `dl_Out` | 0x0020B988 |
| 0x001F86E8 | `dpk_SwapBuffer` | `dl_SetDLPriority` | 0x0020BA10 |
| 0x001F8710 | `dpk_Init` | `dl_OpenDma` | 0x0020BA38 |
| 0x001F87B0 | `func_001F87B0` | `dpk_Init` | 0x0020BAD8 |
| 0x001F8880 | `enemy_Initialize` | `dpk_CheckBufferSize` | 0x0020BBA8 |
| 0x001F88B0 | `enemy_GetPositionTable` | `enemy_Initialize` | 0x0020BBD8 |
| 0x001F8BF0 | `func_001F8BF0` | `enemy_GetPositionTable` | 0x0020BF18 |
| 0x001F8C30 | `func_001F8C30` | `cut_gobj_camera_dl_link` | 0x0020BF58 |
| 0x001F8DD0 | `isysGObjRemoveCameraDL` | `isysGObjMoveCameraDL` | 0x0020C0F8 |
| 0x001F8E08 | `func_001F8E08` | `isysGObjLinkCameraDL` | 0x0020C130 |
| 0x001FE250 | `func_001FE250` | `GetCollisCenterPositionSimple` | 0x00211340 |
| 0x001FE2F8 | `func_001FE2F8` | `CheckWallAttributeEdegWall` | 0x002113E8 |
| 0x002015F8 | `func_002015F8` | `setMailTarget` | 0x00214B38 |
| 0x00201628 | `func_00201628` | `seMail` | 0x00214B68 |
| 0x002017A0 | `func_002017A0` | `seMailTargetDistCheck` | 0x00214CE0 |
| 0x00201840 | `func_00201840` | `add_wp_pos` | 0x00214D80 |
| 0x00202450 | `seMail` | `NearestEnemyFromGirl` | 0x00215990 |
| 0x00202578 | `func_00202578` | `CopyWpPos` | 0x00215AB8 |
| 0x00202638 | `func_00202638` | `WayLengthOfGObj_Pos` | 0x00215B78 |
| 0x00202688 | `func_00202688` | `WayLengthOfGObj_GObj` | 0x00215BC8 |
| 0x002026E0 | `func_002026E0` | `WayPointWithRangeFromGObj` | 0x00215C20 |
| 0x00202B10 | `NearestEnemyFromGirl` | `DeleteWayPoint` | 0x002162C8 |
| 0x00202C30 | `CopyWpPos` | `WayGroup_next` | 0x002163E8 |
| 0x00202FD8 | `DeleteWayPoint` | `group_create` | 0x00216790 |
| 0x00203450 | `WayGroup_next` | `point_delete` | 0x00216C08 |
| 0x00203550 | `WayBridge_begin` | `point_insert` | 0x00216D08 |
| 0x002039D0 | `point_delete` | `wp_print_out` | 0x00217188 |
| 0x00203CE0 | `point_insert` | `draw_way_group` | 0x00217498 |
| 0x00204480 | `draw_way_group` | `point_nige` | 0x00217C38 |
| 0x00204518 | `way_toolDL` | `quick_save_wpfile` | 0x00217CD0 |
| 0x00206D70 | `func_00206D70` | `actE3GateJimaku` | 0x0021A820 |
| 0x0020CB40 | `actSt00aStair` | `actSubMpegReturnPreload` | 0x00220EB8 |
| 0x0020CD30 | `actSt00aDoor2Event` | `actSt24aConte01_2_Jimaku` | 0x002210B0 |
| 0x0020F008 | `actSt02aTakiWay` | `actSt02WaterFallBoySplashCheck` | 0x00223930 |
| 0x002123B0 | `actSt04bSekizo` | `actSt04aConte06Jimaku` | 0x002271E8 |
| 0x00225660 | `actSt13aChainNG` | `actSt07aTsuroEffect` | 0x0023E7A8 |
| 0x0022DAE0 | `actSt19aChainUp` | `actSt13bConte02Jimaku` | 0x00249A20 |
| 0x0022E288 | `actSt19aChainSwitch` | `actSt13b2Generator` | 0x00249F88 |
| 0x0022E838 | `actSt20aEnd` | `actSt13cConte04Jimaku` | 0x0024A568 |
| 0x0022F850 | `actSt20aFenceUpChk` | `actSt13cConte05Jimaku` | 0x0024B6B8 |
| 0x00230238 | `actSt20aGondola` | `actSt13cHandJimaku` | 0x0024C550 |
| 0x002310B8 | `func_002310B8` | `actSt13dExitR` | 0x0024D4B0 |
| 0x00231188 | `func_00231188` | `actSt13dExitL` | 0x0024D580 |
| 0x00231988 | `actSt24aSaku` | `actSt17aHasiEffect` | 0x0024DE10 |
| 0x00232170 | `func_00232170` | `actSt17aGirlWay` | 0x0024E7F8 |
| 0x00238178 | `func_00238178` | `stageSE10lstrong2` | 0x00255A00 |
| 0x002382C0 | `func_002382C0` | `stageSE19ataki` | 0x00255B48 |
| 0x002384E0 | `func_002384E0` | `stageSE02astrong` | 0x00255D68 |
| 0x002386B8 | `func_002386B8` | `stageSE03tsuiro` | 0x00255F40 |
| 0x002386F0 | `func_002386F0` | `stageSE03tnotSuiro` | 0x00255F78 |
| 0x00238860 | `func_00238860` | `stageSE04ewind` | 0x002560E8 |
| 0x002389A0 | `audioDecCreate` | `stageSE06astrong` | 0x00256228 |
| 0x00238AB0 | `audioDecEndPut` | `stageSE06abirdIn` | 0x00256338 |
| 0x00238B08 | `sendToIOP2area` | `stageSE06abirdOut` | 0x00256390 |
| 0x00238B60 | `audioDecSendToIOP` | `stageSE06ataimatsu` | 0x002563E8 |
| 0x00238BD0 | `pcmCallback` | `stageSE08astrong` | 0x00256458 |
| 0x00238CA0 | `audioDecDelete` | `stageSE08astrong2` | 0x00256528 |
| 0x00238D78 | `audioDecReset` | `stageSE08anoise3` | 0x00256600 |
| 0x00238E00 | `audioDecIsPreset` | `stageSE08ataimatsu` | 0x00256688 |
| 0x002399D8 | `setDMAscTag` | `GetDataFileName2` | 0x00257260 |
| 0x00239C58 | `setPRIM` | `ObjAction_Mail` | 0x00257398 |
| 0x00239DB8 | `ErrMessage` | `ObjAction_Init` | 0x002574F8 |
| 0x00239FC0 | `func_00239FC0` | `audioDecEndPut` | 0x00257708 |
| 0x0023A0E0 | `func_0023A0E0` | `sendToIOP2area` | 0x00257828 |
| 0x0023A410 | `func_0023A410` | `audioDecSendToIOP` | 0x00257B58 |
| 0x0023A5E8 | `func_0023A5E8` | `pcmCallback` | 0x00257D30 |
| 0x0023A748 | `func_0023A748` | `audioDecReset` | 0x00257EB8 |
| 0x0023A7A0 | `func_0023A7A0` | `audioDecIsPreset` | 0x00257F10 |
| 0x0023B518 | `viBufReset` | `handler_endimage` | 0x00258B50 |
| 0x0023B5A0 | `viBufAddDMA` | `setDMAscTag` | 0x00258BD8 |
| 0x0023B5F8 | `viBufStopDMA` | `setGIFtag` | 0x00258C30 |
| 0x0023B650 | `viBufRestartDMA` | `setGIFad` | 0x00258C88 |
| 0x0023B680 | `viBufFlush` | `setTEXFLUSH` | 0x00258CB8 |
| 0x0023B6A0 | `viBufModifyPts` | `setTEX1_1` | 0x00258CD8 |
| 0x0023B720 | `viBufGetTs` | `setTEX0_1` | 0x00258D58 |
| 0x0023B7D8 | `viBufDelete` | `setPRIM` | 0x00258E10 |
| 0x0023B870 | `viBufCount` | `setUV` | 0x00258EA8 |
| 0x0023BD10 | `CreateGObj` | `copy2area` | 0x00259348 |
| 0x0023C040 | `func_0023C040` | `viBufReset` | 0x00259678 |
| 0x0023C2C0 | `func_0023C2C0` | `viBufEndPut` | 0x002598F8 |
| 0x0023C310 | `func_0023C310` | `viBufAddDMA` | 0x00259948 |
| 0x0023C5B0 | `func_0023C5B0` | `viBufStopDMA` | 0x00259BE8 |
| 0x0023C738 | `func_0023C738` | `viBufRestartDMA` | 0x00259D70 |
| 0x0023CB20 | `func_0023CB20` | `viBufFlush` | 0x0025A158 |
| 0x0023CB70 | `func_0023CB70` | `viBufModifyPts` | 0x0025A1A8 |
| 0x0023CCE0 | `func_0023CCE0` | `viBufGetTs` | 0x0025A318 |
| 0x0023CE80 | `func_0023CE80` | `viBufDelete` | 0x0025A4B8 |
| 0x0023CF40 | `func_0023CF40` | `viBufCount` | 0x0025A578 |
| 0x0023D170 | `func_0023D170` | `InitCameraGObjs` | 0x0025A7A8 |
| 0x0023D260 | `func_0023D260` | `CreateGObj` | 0x0025A898 |
| 0x0023D3C0 | `func_0023D3C0` | `CreateGObjByFuncSet` | 0x0025A9F8 |
| 0x0023D4E8 | `func_0023D4E8` | `MakeBoundingBox` | 0x0025AB20 |

## Skip census (twins never proposed)

* 688 — via=ordinal not norm_equal
* 549 — via=gap/anchor PAL name provisional-ordinal
* 183 — via=gap PAL same-hash class
* 71 — PAL name is a func_<VMA> placeholder
* 18 — twin address has no symbol_addrs line on one side
* 15 — name already agrees

No `via=gap` or `via=ordinal` twin survived the filter, so every applied rename
is anchor-tier.  The 183 `gap` twins that were `norm_equal` with a twin-tier PAL
name were all rejected as PAL same-hash classes: their reloc-normalized stream
occurs more than once in the PAL build (families of interchangeable one-line
accessor wrappers), so the pairing inside the family is arbitrary.  Same-hash
classes were recomputed from `baserom/pal/baseelf.rom` with the correlation
tool's own `normalize()`/`norm_hash()` (5542 PAL functions -> 5001 distinct
hashes; 715 functions sit in a multi-member class).

## TU trailers

* 386 trailers rewritten to the PAL attribution.
* 767 left alone: the PAL TU is a `src/cod/vendor_<PAL VMA>` name, i.e. an
  address-derived label that means nothing in the aug6 link.
* 240 already agreed.
* 35 left alone: the PAL TU has no subsegment in `config/ico.aug6.yaml`, so
  writing it would invent a file the tree does not split.  These are the
  honest disagreements:
  * 10 functions: aug6 says `ito/mpeg/mv_vibuf.c`, PAL says `ito/mpeg/mv_disp`
  * 5 functions: aug6 says `common/src/GobjProc.c`, PAL says `ito/mpeg/mv_disp`
  * 4 functions: aug6 says `ito/mpeg/mv_videodec.c`, PAL says `ito/mpeg/mv_videodec`
  * 4 functions: aug6 says `ito/mpeg/mv_sub.c`, PAL says `ito/mpeg/mv_disp`
  * 3 functions: aug6 says `ito/mpeg/mv_strfile.c`, PAL says `ito/mpeg/mv_videodec`
  * 2 functions: aug6 says `sugipon/src/delayFreeManager.c`, PAL says `src/main`
  * 2 functions: aug6 says `common/src/GobjProc.c`, PAL says `ito/mpeg/mv_vibuf`
  * 2 functions: aug6 says `common/src/PObj.c`, PAL says `src/vobj`
  * 1 function: aug6 says `ito/mpeg/mv_vobuf.c`, PAL says `ito/mpeg/mv_videodec`
  * 1 function: aug6 says `common/src/DObj.c`, PAL says `ito/mpeg/mv_vobuf`
  * 1 function: aug6 says `ito/mpeg/mv_sub.c`, PAL says `ito/mpeg/mv_audiodec`

`config/ico.aug6.yaml` subsegment spans and names are untouched, and no file
was moved.  A rewritten trailer therefore now names the file the 2001 dev had
the function in, which for 386 functions is NOT the file the aug6 carve
currently compiles it from.

**Measured side effect.**  `tools/progress_tree.py` resolves "matched" by
looking for the symbol's `INCLUDE_ASM` inside the file its trailer names, so a
trailer that points away from the carve makes an unmatched function look
matched.  `docs/progress.json` `matched_funcs` moves 3538 -> 3656 and
`sections_from_symbols[".text"]` 403780 -> 445428 for that reason alone.  The
ELF-measured headline is unaffected: `matched_bytes` stays 406048 / 1489252
(27.27%).  The identical artefact exists on `ntsc` from the same procedure
(3145 -> 3352 funcs, 329428 -> 393652 bytes, commit d7185361).

## Application scope and exceptions

* Applied to: `config/symbol_addrs.aug6.txt`, `config/sweep_parked.txt`, every
  tracked `.c` / `.h` / `.inc` outside `tools/` and `lib/`, and `tough_nuts/`
  (both the `.c` bodies and the per-function `notes.md`).  604 files changed.
* Renaming is identifier-boundary and C-aware: a scanner tracks code / line
  comment / block comment / string / char states, so an apostrophe inside a
  comment cannot open a bogus literal (it did on the first attempt, and
  silently blocked the rename of `void inflate(void)` in `fumi/ios/inflate.c`
  until the scanner replaced the naive string regex).
* String literals are renamed only where they DEFINE or REFERENCE a symbol:
  whole-function `__asm__` block content (`.global NAME`, `NAME:`,
  `.size NAME`, `jal NAME`, `glabel`/`endlabel NAME`), and `__asm__("NAME")`
  symbol aliases.  `INCLUDE_ASM` path literals and other strings are left
  alone — several TU paths (`.../fumi/ios/inflate`, `common/src/StageManager`)
  spell a renamed symbol and must NOT follow it.
* One hand exception: `proc` in `fumi/isys/gobj.c` is a local `int`, not the
  global symbol of that name, so its 9 occurrences in that file were excluded
  from the `proc -> MoveChainExtendedWeight` rename.  It was the only
  old name in the map that also names a local or member anywhere in the tree
  (scanned for `#define`, typed declarations, member access, goto labels and
  struct/union/enum tags); no new name collided with any existing identifier.
* `config/ico.aug6.yaml` is not touched (the ntsc pass did not touch its yaml
  either), so a handful of yaml comments still spell pre-rename `func_<VMA>`
  names.
* Directory names under `tough_nuts/` are NOT renamed — the user directive
  forbids changing the prototype's folder structure — so a parked function's
  directory may still be spelled with its old name while the `.c` inside uses
  the new one.
* `seki/src/{cluster,mesh,normal_c,normal_l,particle}.S` were replaced with the
  `main`-branch copies, which carry the DVP assembler's own labels recovered
  from the PAL listing.  All five assemble to byte-identical objects
  (`build/seki/src/*.o` md5 unchanged across the swap) and the ROM SHA-1 is
  unchanged.

