# Rename ledger — ntsc (USA retail) symbols renamed from their PAL twins

Generated 2026-09-04 by a mechanical pass over
`/primary/dev/ico/.port_cache/ntsc_pal_twins.json` (built by
`tools/port_from_ntsc.py scan` in the PAL checkout).  A *twin* pairs one
USA-retail function with one PAL-retail function; `via=anchor` means the
two reloc-normalized instruction streams hash equal AND that hash occurs
exactly once in each build, so the pairing is content-proven, not
positional.  PAL names come from the PAL disc's own shipped build
metadata (SRCFILE.TXT / MAIN.MAP); the USA names they replace were
ordinal guesses carried over from the Aug-2001 prototype.

Rename rule applied:

* `via == anchor` -> rename (tag `// pal-twin`).
* `via in {gap, ordinal}` -> rename only if `norm_equal` AND the PAL name
  is twin-tier AND the PAL stream is not in a same-hash class.  **No pair
  survived that filter** (see the skip census below), so no line carries
  the `// pal-twin-ordinal` tag.
* A proposal whose target name is still held by another ntsc address after
  the whole map is applied is dropped (iterated to a fixed point).
* Hand-written seed lines above the `BEGIN GENERATED` banner, `_start` and
  the five `*MicroProgram` symbols are untouched.

Applied: **1655** renames (554 replace a real-but-wrong name,
1101 replace a `func_<VMA>` placeholder).  The byte-identical link is
unchanged by construction (`verify_elf: OK ... fbf50c75cd5911273511c4f9af90503ff8423582`).

## Real names replaced (old -> new)

| old (ntsc, wrong) | new (PAL twin) | via | PAL VMA | PAL TU |
| --- | --- | --- | --- | --- |
| `GetRootQuaternion` | `GetRootMatrixRotOffsetByDObj` | anchor | 0x001029C0 | `src/geometryManager` |
| `SetRootBaseQuaternion` | `SetRootMatrixRotOffsetByDObj` | anchor | 0x00102A08 | `src/geometryManager` |
| `GetRootMatrixRotOffsetByDObj` | `LocalizeGeometry` | anchor | 0x00102E50 | `src/geometryManager` |
| `GetRootMatrixRotOffset` | `GetGlobalDirectionOrient` | anchor | 0x00102FE8 | `src/geometryManager` |
| `SetRootMatrixRotOffsetByDObj` | `GlobalizeGeometry` | anchor | 0x00103060 | `src/geometryManager` |
| `SetRootMatrixRotOffset` | `GetRootVelocity` | anchor | 0x00103158 | `src/geometryManager` |
| `SetDirectRootPositionWithNodePoint` | `GetInitialInverseMatrix` | anchor | 0x00103228 | `src/geometryManager` |
| `LocalizeGeometry` | `GetInitialSkeltonMatrixByDObj` | anchor | 0x001032F0 | `src/geometryManager` |
| `GetGlobalDirectionOrient` | `MakeCharGObjList` | anchor | 0x001033B8 | `src/geometryManager` |
| `GlobalizeGeometry` | `cylinderCollisionCheck` | anchor | 0x00103500 | `src/geometryManager` |
| `GetRootVelocity` | `LocalizeDirectionOrient` | anchor | 0x00103B18 | `src/geometryManager` |
| `GetInitialInverseMatrixByDObj` | `GetCylinderCollision` | anchor | 0x00103B90 | `src/geometryManager` |
| `GetInitialInverseMatrix` | `GetCylinderCollisionWithExceptOwnCollision` | anchor | 0x00103C90 | `src/geometryManager` |
| `GetInitialSkeltonMatrixByDObj` | `CylinderCollision` | anchor | 0x00103D98 | `src/geometryManager` |
| `MakeCharGObjList` | `CylinderCollisionWithControlDynamics` | anchor | 0x00103F48 | `src/geometryManager` |
| `cylinderCollisionCheck` | `GetRootMatrixByDObj` | anchor | 0x00104108 | `src/geometryManager` |
| `LocalizeDirectionOrient` | `GetRootMatrix` | anchor | 0x00104188 | `src/geometryManager` |
| `GetCylinderCollision` | `GetRootPositionByDObj` | anchor | 0x00104208 | `src/geometryManager` |
| `GetCylinderCollisionWithExceptOwnCollision` | `SetDirectRootPosition` | anchor | 0x00104288 | `src/geometryManager` |
| `CylinderCollision` | `SetDirectRootPositionNoFitting` | anchor | 0x001043A8 | `src/geometryManager` |
| `CylinderCollisionWithControlDynamics` | `SetRootPosition` | anchor | 0x001044C0 | `src/geometryManager` |
| `GetRootMatrixByDObj` | `GetRootPosition` | anchor | 0x00104550 | `src/geometryManager` |
| `InitKeyInput` | `GetRootOrient` | anchor | 0x001045D8 | `src/geometryManager` |
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
| `GetDifferenceFromWallLowerPlane` | `GetRopeHangablePos` | anchor | 0x0010A2F8 | `src/motionManager2` |
| `GetDifferenceFromWallUpperPlane` | `GetMotionFrameFlag1` | anchor | 0x0010A308 | `src/motionManager2` |
| `GetRopeHangablePos` | `GetHeightOfWallFromGObj` | anchor | 0x0010A378 | `src/motionManager2` |
| `GetMotionFrameFlag1` | `GetHeightOfCliffFromGObj` | anchor | 0x0010A388 | `src/motionManager2` |
| `GetHeightOfWallFromGObj` | `GetRootProjectionPosOfGObj` | anchor | 0x0010A490 | `src/motionManager2` |
| `GetHeightOfCliffFromGObj` | `SetMotionPlaySpeedRatio` | anchor | 0x0010A4D8 | `src/motionManager2` |
| `GetRootProjectionPosOfGObj` | `CopyMotion` | anchor | 0x0010A550 | `src/motionManager2` |
| `SetMotionPlaySpeedRatio` | `GetMotionRootPos` | anchor | 0x0010A590 | `src/motionManager2` |
| `SetSkeltonDispSwitch` | `GetBlendedMotion` | anchor | 0x0010A790 | `src/motionManager2` |
| `CopyMotion` | `GetFloatingMotionRootPos` | anchor | 0x0010A978 | `src/motionManager2` |
| `GetMotionRootPos` | `GetShapeMotion` | anchor | 0x0010AA98 | `src/motionManager2` |
| `flushWork` | `GetOutOutsideOfWall` | anchor | 0x0010AB20 | `src/motionManager2` |
| `setNodePursueParticleEffectWithUpperLimit` | `AdjustRootPositionToVerticalSidePlaneOfWall` | anchor | 0x0010ABD0 | `src/motionManager2` |
| `SetFallDownSplash` | `fitYToPlane` | anchor | 0x0010AC80 | `src/motionManager2` |
| `GetPoolGlobalDrainVector` | `GetBlendedMotionRootPos` | anchor | 0x0010ACC0 | `src/motionManager2` |
| `InitPoolGeo` | `_getMotRotElem` | anchor | 0x0010AD18 | `src/motionManager2` |
| `PoolDL` | `flushWork` | anchor | 0x0010AF40 | `src/pool` |
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
| `light_InitLight` | `gsb_ClearFrameBuffer` | anchor | 0x00116500 | `src/GsBase` |
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
| `mc_Init` | `_UnitVector` | anchor | 0x00119C38 | `src/Matrix` |
| `pac_DispQW` | `_GetRandom` | anchor | 0x0011A230 | `src/Matrix` |
| `pac_DumpPac` | `_GetRandomVector` | anchor | 0x0011A248 | `src/Matrix` |
| `pac_makeBoundingBox` | `_GetRandomVector0` | anchor | 0x0011A268 | `src/Matrix` |
| `pac_error` | `_RotTransCurrentMatrix` | anchor | 0x0011A280 | `src/Matrix` |
| `pac_makeNormalStrip` | `mc_setBaseOffset` | anchor | 0x0011A2E0 | `src/MicroCode` |
| `pac_getWeight` | `mc_SetMicroCode` | anchor | 0x0011A430 | `src/MicroCode` |
| `pac_setGifTag` | `pac_DumpPac` | anchor | 0x0011A988 | `src/Packet` |
| `pac_closeTag` | `pac_makeBoundingBox` | anchor | 0x0011AB18 | `src/Packet` |
| `pac_continueTag` | `pac_error` | anchor | 0x0011AC38 | `src/Packet` |
| `pac_checkDivide` | `pac_makeNormalStrip` | anchor | 0x0011AD08 | `src/Packet` |
| `pac_countOneVertexPacketSize` | `pac_getWeight` | anchor | 0x0011B168 | `src/Packet` |
| `pac_getTextureInfo` | `pac_setGifTag` | anchor | 0x0011BB00 | `src/Packet` |
| `pac_makeShapeTable` | `pac_closeTag` | anchor | 0x0011BBD8 | `src/Packet` |
| `pac_makePacket` | `pac_continueTag` | anchor | 0x0011BCE8 | `src/Packet` |
| `pac_MakePacket` | `pac_checkDivide` | anchor | 0x0011BE30 | `src/Packet` |
| `pac_Dump` | `pac_countOneVertexPacketSize` | anchor | 0x0011BFC0 | `src/Packet` |
| `reg_clipPacketBoundingBox` | `prim_DispWireBox` | anchor | 0x0011FCC0 | `src/Primitive` |
| `shadow_KillShadow` | `reg_TransTexturePacket` | anchor | 0x00124450 | `src/RegistPacket` |
| `shadow_SetLength` | `reg_GetShinePri` | anchor | 0x00124488 | `src/RegistPacket` |
| `stage_ContinueAnimation` | `shadow_MakeObjectData` | anchor | 0x00129738 | `src/Shadow` |
| `stage_ResetAnimation` | `shadow_Tool` | anchor | 0x00129AA0 | `src/Shadow` |
| `stage_SetCameraForceOff` | `stage_ResetAnimation` | anchor | 0x0012B188 | `src/StageAnimation` |
| `iosCdvdMgrSearchFile` | `tex_RemakeRegistersSampleMin` | anchor | 0x00132078 | `src/Texture` |
| `iosCdvdBackGroundMgrDelete` | `iosCdvdSync` | anchor | 0x001354F0 | `ios/cdvd` |
| `iosCdvdBackGroundMgrEntryNum` | `iosCdvdBackGroundMgrDelete` | anchor | 0x001355A8 | `ios/cdvd` |
| `iosCdvdBackGroundReadIOPm` | `iosCdvdBackGroundMgrEntryNum` | anchor | 0x00135620 | `ios/cdvd` |
| `inflate_start` | `iosCdvdDirectStRead` | anchor | 0x00135668 | `ios/cdvd` |
| `inflate` | `iosCdvdBackGroundMgrInit` | anchor | 0x00135728 | `ios/cdvd` |
| `open_inflate_handler` | `huft_build` | anchor | 0x001358B0 | `ios/inflate` |
| `fill_inbuf` | `inflate_codes` | anchor | 0x00136078 | `ios/inflate` |
| `huft_free` | `inflate_stored` | anchor | 0x001367C0 | `ios/inflate` |
| `ios_init_plus` | `huft_free` | anchor | 0x00137DA8 | `ios/inflate` |
| `iosInitialize` | `ios_init_plus` | anchor | 0x00137DE8 | `ios/ios` |
| `iosMcMgrSync` | `iosMcSync` | anchor | 0x0013A0B8 | `ios/mcard` |
| `iosMcTest` | `iosMcGetInfo` | anchor | 0x0013A0D0 | `ios/mcard` |
| `iosMcSync` | `iosMcFormat` | anchor | 0x0013A110 | `ios/mcard` |
| `iosMcGetInfo` | `iosMcUnformat` | anchor | 0x0013A158 | `ios/mcard` |
| `iosMcIconWriteIconsys` | `iosMcGetDir` | anchor | 0x0013A1A0 | `ios/mcard` |
| `iosMcIconWriteIcon` | `iosMcDelete` | anchor | 0x0013A1E8 | `ios/mcard` |
| `_iosMcIconWriteIconsys` | `iosMcSaveIconBlock` | anchor | 0x0013A230 | `ios/mcard` |
| `iosMallocCheckLeak` | `_iosFreeWithFill` | anchor | 0x0013B778 | `ios/memory` |
| `iosMsgQueueCreate` | `deq_mes_th` | anchor | 0x0013C4A8 | `ios/message` |
| `iosMsgQueueDestroy` | `iosMsgQueueCreate` | anchor | 0x0013C4D8 | `ios/message` |
| `send_signal_message` | `iosMsgQueueDestroy` | anchor | 0x0013C580 | `ios/message` |
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
| `AdpcmStop` | `adpcmTickProc2` | anchor | 0x00142520 | `sound/adpcm_init` |
| `AdpcmClose` | `AdpcmPlay` | anchor | 0x00142AF8 | `sound/adpcm_init` |
| `AdpcmInterStereoVolumeSet` | `AdpcmStop` | anchor | 0x00142B28 | `sound/adpcm_init` |
| `adpcmPauseRequest` | `AdpcmInterStereoVolumeSet` | anchor | 0x00142E08 | `sound/adpcm_init` |
| `ACTSetEnvAllmighty` | `adpcmTickProc` | anchor | 0x00143430 | `sound/adpcm_init` |
| `CheckWallAttributeEdegWall` | `adpcmOpenProc` | anchor | 0x00143520 | `sound/adpcm_init` |
| `soundReverbDepthSet` | `soundInit` | anchor | 0x00143550 | `sound/s_init` |
| `soundAllocIopHeap` | `soundOutputModeSet` | anchor | 0x001436A0 | `sound/s_init` |
| `soundAllocIopFree` | `soundReverbDepthSet` | anchor | 0x001436B0 | `sound/s_init` |
| `soundDataOpenChk` | `soundAllocIopHeap` | anchor | 0x00143728 | `sound/s_init` |
| `soundBufSegFree` | `soundDataOpenChk` | anchor | 0x00143790 | `sound/s_init` |
| `ACTParaStatus_Exec` | `ACTGameCollisionOff` | anchor | 0x0014CA20 | `src/act-game` |
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
| `ActPara_DebugOut` | `_ACTCharStatus_Init` | anchor | 0x0014DDF8 | `src/act-game` |
| `actBoyRun` | `CorrectStickInfo` | anchor | 0x001577D0 | `src/boyact` |
| `GetBoyWeaponGObj` | `IsGirlEscortedInNextStage` | anchor | 0x00158340 | `src/boyact` |
| `actBoyCall` | `GetEfStageCameraTargetID` | anchor | 0x00158528 | `src/boyact` |
| `actBoyBeslam` | `ACTSearchGObj` | anchor | 0x001587A0 | `src/boyact` |
| `actBoyRescueSrc` | `afterBoySwim` | anchor | 0x00158908 | `src/boyact` |
| `actCommonLever` | `debugDispSphere` | anchor | 0x0015E388 | `src/commonact` |
| `EBRAIN_SEND_MES` | `getLandOffset` | anchor | 0x0015E400 | `src/commonact` |
| `actCommonSlowrun` | `ControlMotionOrient` | anchor | 0x001639C8 | `src/commonact` |
| `ACT_LAYOUT_GAMEOVER` | `_ACTMotDir_V` | anchor | 0x00163A38 | `src/commonact` |
| `_ACTMotDirSmzDirect` | `SetCorrectOrientOfChain` | anchor | 0x00163AC0 | `src/commonact` |
| `actCommonDelete` | `afterCommonBox` | anchor | 0x00163D38 | `src/commonact` |
| `IsEnemyBrainToBoy` | `FlyMail` | anchor | 0x0016ACF8 | `src/enemy_act` |
| `clip_floor_1` | `isEnemyHyde` | anchor | 0x0016AF98 | `src/enemy_act` |
| `makeCollisionBlockTable` | `afterEnemyBodylift` | anchor | 0x0016B010 | `src/enemy_act` |
| `DrawGObjWallCollision` | `clip_floor_1` | anchor | 0x0016B7F0 | `src/fieldCollision` |
| `DBG_VECTOR` | `makeCollisionBlockTable` | anchor | 0x0016BBC0 | `src/fieldCollision` |
| `ClipFloorByGObj` | `DrawGObjWallCollision` | anchor | 0x0016C288 | `src/fieldCollision` |
| `ClipWall` | `DBG_VECTOR` | anchor | 0x0016C770 | `src/fieldCollision` |
| `ClipWallField` | `ClipFloorByGObj` | anchor | 0x0016D1B8 | `src/fieldCollision` |
| `ClipWallBoxStop` | `ClipWall` | anchor | 0x0016D3D8 | `src/fieldCollision` |
| `ClipWallFieldCheckCB` | `ClipWallField` | anchor | 0x0016D458 | `src/fieldCollision` |
| `ClipFloorE` | `ClipWallBoxStop` | anchor | 0x0016D498 | `src/fieldCollision` |
| `ClipCollision` | `ClipWallFieldCheckCB` | anchor | 0x0016D520 | `src/fieldCollision` |
| `LoadCollision` | `ClipFloorE` | anchor | 0x0016D568 | `src/fieldCollision` |
| `SetSimplePlane` | `ClipCollision` | anchor | 0x0016D5F0 | `src/fieldCollision` |
| `fzShowM` | `LoadCollision` | anchor | 0x0016D6A0 | `src/fieldCollision` |
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
| `waypoint_connect_group_side_me` | `get_wp_nearest_bridge_side_bridge` | anchor | 0x001814C8 | `src/way_util` |
| `bridge_waypoint_side_bridge` | `direction_across_bridge` | anchor | 0x00181558 | `src/way_util` |
| `wpsort_compfnc` | `waypoint_connect_group_side_me` | anchor | 0x00181730 | `src/way_util` |
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
| `actConte11` | `scpKillEnemyOne` | anchor | 0x00184D28 | `src/script` |
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
| `DispAxisArrow` | `saveEditedData` | anchor | 0x0018A678 | `src/camera-editor` |
| `dispCameraPinType2` | `gif_test` | anchor | 0x0018A970 | `src/camera-editor` |
| `CameraEdit_DispPinType2` | `DebugDispBox` | anchor | 0x0018AA58 | `src/camera-editor` |
| `dispBox` | `drawXZArrow` | anchor | 0x0018B890 | `src/camera-editor` |
| `CameraEdit_DispBoxType2_Plane` | `DispAxisArrow` | anchor | 0x0018B9E8 | `src/camera-editor` |
| `CameraEdit_DispBoxType2` | `dispCameraPinType2` | anchor | 0x0018BBE0 | `src/camera-editor` |
| `menuGroupSelect` | `CameraEdit_DispPinType2` | anchor | 0x0018BFF8 | `src/camera-editor` |
| `menuPinSelect` | `dispBox` | anchor | 0x0018C688 | `src/camera-editor` |
| `menuPinEdit` | `CameraEdit_DispBoxType2_Plane` | anchor | 0x0018C9E0 | `src/camera-editor` |
| `CameraSetCameraSet_Default` | `CameraEdit_reset_box` | anchor | 0x0018EB70 | `src/camera-editor` |
| `ico2camera_GetTargetPos` | `CameraEdit_reflect_box` | anchor | 0x0018EDE0 | `src/camera-editor` |
| `initMonitorCamera` | `CameraEdit_BOX_NUMBER` | anchor | 0x0018F050 | `src/camera-editor` |
| `monitorMonitorCamera` | `CameraEdit_PIN_NUMBER` | anchor | 0x0018F060 | `src/camera-editor` |
| `ChaseCamera` | `CameraEdit_PIN_NUMBER_ALL` | anchor | 0x0018F0A8 | `src/camera-editor` |
| `CameraMove` | `CameraEdit_BOX` | anchor | 0x0018F0E8 | `src/camera-editor` |
| `ReflectCameraSetBinary` | `CameraEdit_PIN` | anchor | 0x0018F100 | `src/camera-editor` |
| `InitIco2Camera` | `CameraEdit_DispPin` | anchor | 0x0018F128 | `src/camera-editor` |
| `GetTargetOffset` | `ConvertCameraSetBuffer` | anchor | 0x0018F2A8 | `src/camera-editor` |
| `SetCameraMatrix_Ico2` | `StickToTrans` | anchor | 0x0018F418 | `src/camera-editor` |
| `SetCameraZoomOffsetRatio` | `_CameraEdit_PIN` | anchor | 0x0018F680 | `src/camera-editor` |
| `GetCameraGroupCurrent` | `_CameraEdit_add_box` | anchor | 0x0018F6A8 | `src/camera-editor` |
| `GetCameraGroupFromGObj` | `_CameraEdit_add_pin` | anchor | 0x0018F820 | `src/camera-editor` |
| `InitPluralCameraSet` | `CameraSetCameraSet_Default` | anchor | 0x0018F9E8 | `src/camera-ico2` |
| `MakeCameraSetBinary` | `ico2camera_GetTargetPos` | anchor | 0x0018FA28 | `src/camera-ico2` |
| `SetCameraTargetPosition` | `initMonitorCamera` | anchor | 0x0018FE28 | `src/camera-ico2` |
| `InitCamera` | `Camctrl_SetTarget` | anchor | 0x001948A0 | `src/camera-root` |
| `Camctrl_SetTarget` | `CameraChangeTargetParallel` | anchor | 0x00194918 | `src/camera-root` |
| `InitCameraSetManager` | `CameraGetTargets` | anchor | 0x001949E0 | `src/camera-root` |
| `StartPendulum` | `GetCameraInfo_tmp` | anchor | 0x00194EF8 | `src/camera-root` |
| `_InterGV` | `RestoreGeneratorGeo` | anchor | 0x0019BEC8 | `src/generator` |
| `_DistSqGV` | `DirectCallEnemy` | anchor | 0x0019C060 | `src/generator` |
| `_DistGV` | `LockEnemyGenerate` | anchor | 0x0019C1D0 | `src/generator` |
| `_DistxzGV` | `UnlockEnemyGenerate` | anchor | 0x0019C218 | `src/generator` |
| `_RotyGV` | `ReturnEnemyToGenerator` | anchor | 0x0019C330 | `src/generator` |
| `_GetDirection` | `SetInfoSpKidnapGenerator` | anchor | 0x0019C450 | `src/generator` |
| `_RotGV` | `SetInfoSpKidnapEnemy` | anchor | 0x0019C460 | `src/generator` |
| `_RotGVF` | `IsEnableCallEnemyByTargetGObj` | anchor | 0x0019C4E8 | `src/generator` |
| `_OrientXZGV` | `_InterGV` | anchor | 0x0019C560 | `src/gv` |
| `HandyCamera_TargetMoveType` | `_DistSqGV` | anchor | 0x0019C8D8 | `src/gv` |
| `ClearHandCameraCorrect` | `_DistGV` | anchor | 0x0019C908 | `src/gv` |
| `InitHandCameraCorrect` | `_DistxzGV` | anchor | 0x0019C940 | `src/gv` |
| `HandCameraCorrect` | `_RotyGV` | anchor | 0x0019CA48 | `src/gv` |
| `InitMailAdditionalData` | `AlignDegGV` | anchor | 0x0019CEF8 | `src/gv` |
| `GetMailAdditionalData` | `HandyCamera_TargetMoveType` | anchor | 0x0019D2C0 | `src/hand-camera` |
| `ClearMailAdditionalData` | `ClearHandCameraCorrect` | anchor | 0x0019D528 | `src/hand-camera` |
| `_IsInScreen2` | `do_DrawLine` | anchor | 0x0019E1D0 | `src/poly-flat` |
| `do_DrawLine` | `trans_bird` | anchor | 0x0019E6C8 | `src/act_bird` |
| `trans_bird` | `vector_angle_degree` | anchor | 0x0019FEA0 | `src/act_bird` |
| `BirdGeo` | `_ACTSendMailToBirdAll` | anchor | 0x001A00F0 | `src/act_bird` |
| `effect_end_func` | `itou_boss_gflag_init` | anchor | 0x001A0DB0 | `src/itou_boss` |
| `BossEnemyFunc` | `actBossCtrlStart` | anchor | 0x001A0F08 | `src/itou_boss` |
| `gene_enemy` | `InitBossCtrlGeo` | anchor | 0x001A0FE0 | `src/itou_boss` |
| `BossCtrlGeo` | `CapsuleGhostBossStart` | anchor | 0x001A10F0 | `src/itou_boss` |
| `m33_to_quat` | `lw_pos_to_ico_pos` | anchor | 0x001A1440 | `src/itou_sub` |
| `lw_pos_to_ico_pos` | `apply_matrix_w1` | anchor | 0x001A1470 | `src/itou_sub` |
| `apply_matrix_w1` | `ico_m33_to_quat` | anchor | 0x001A14A0 | `src/itou_sub` |
| `ico_m33_to_quat` | `pbga_start` | anchor | 0x001A14D8 | `src/itou_sub` |
| `pbga_start` | `set_vertex` | anchor | 0x001A1520 | `src/lightning` |
| `set_vertex` | `apply_m34` | anchor | 0x001A2558 | `src/lightning` |
| `DrawLightning2` | `DrawLightning` | anchor | 0x001A2580 | `src/lightning` |
| `DrawLightningN` | `lightning_test` | anchor | 0x001A2688 | `src/lightning` |
| `apply_m34` | `cmpr` | anchor | 0x001A2760 | `src/lightning` |
| `DrawLightning` | `scale_m34` | anchor | 0x001A2770 | `src/queen` |
| `movie_end` | `readBufEndPut` | anchor | 0x001A68F8 | `ito/mpeg/mv_readbuf` |
| `readBufEndPut` | `free_buf` | anchor | 0x001A6A18 | `ito/mpeg/mv_videodec` |
| `strFileClose` | `videoDecFlush` | anchor | 0x001A6B78 | `ito/mpeg/mv_videodec` |
| `free_buf` | `videoDecGetState` | anchor | 0x001A7000 | `ito/mpeg/mv_videodec` |
| `videoDecCreate` | `videoDecIsFlushed` | anchor | 0x001A7008 | `ito/mpeg/mv_videodec` |
| `videoDecBeginPut` | `videoDecMain` | anchor | 0x001A7058 | `ito/mpeg/mv_videodec` |
| `videoDecEndPut` | `mpegError` | anchor | 0x001A70A8 | `ito/mpeg/mv_videodec` |
| `videoDecFlush` | `mpegNodata` | anchor | 0x001A70D0 | `ito/mpeg/mv_videodec` |
| `allocObjectData` | `voBufDecCount` | anchor | 0x001A7458 | `ito/mpeg/mv_vobuf` |
| `StageManager` | `stgmgrForceSwitchWithFade` | anchor | 0x001A8DC8 | `src/StageManager` |
| `stgmgrForceSwitchWithFade` | `stgmgrNextStagePreLoadForceStageSet` | anchor | 0x001A8E40 | `src/StageManager` |
| `backStageProcessMain` | `CheckPoint` | anchor | 0x001A8E70 | `src/StageManager` |
| `debug_VariableInit` | `debug_SetDmaCallback` | anchor | 0x001AC088 | `src/debug` |
| `display` | `debug_PrintFontWindow` | anchor | 0x001AF580 | `src/debug` |
| `debugEEExceptionMain` | `debug_PrintfDummy` | anchor | 0x001AF850 | `src/debug` |
| `debugIOPExceptionMain` | `debug_PrintFontWindowDummy` | anchor | 0x001AF870 | `src/debug` |
| `debug_assertMessage` | `debug_StdPrintfDummy` | anchor | 0x001AF898 | `src/debug` |
| `debug_SetExceptionMessage` | `debug_PrintMatrix` | anchor | 0x001AFA78 | `src/debug` |
| `debugExceptionInit` | `debug_DispVu1FReg` | anchor | 0x001AFB28 | `src/debug` |
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
| `disp_memory_partition_bar` | `gamesysObjInfoPosNewStageSet` | anchor | 0x001B7060 | `src/gamesys` |
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
| `onPath` | `getNearestPosition` | anchor | 0x001C7648 | `src/box` |
| `ExecBoxMoveStartReaction` | `GetBoxGlobalHoldPoint` | anchor | 0x001CA6D8 | `src/box` |
| `BoxMemoryFunc` | `GetDistanceOfGObj` | anchor | 0x001CAED8 | `src/box` |
| `getAlign` | `moveXPlus` | anchor | 0x001CAF40 | `src/box` |
| `GetDistanceOfGObj` | `moveXMinus` | anchor | 0x001CB000 | `src/box` |
| `moveXPlus` | `moveZPlus` | anchor | 0x001CB0C8 | `src/box` |
| `moveXMinus` | `moveZMinus` | anchor | 0x001CB188 | `src/box` |
| `CageRideFunc` | `LightLineGeo` | anchor | 0x001CC630 | `src/boy` |
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
| `setEnemyParticleObject` | `saveEffectData` | anchor | 0x001D81D0 | `src/effectTool` |
| `EnemyCheckHit` | `exitEffectTool` | anchor | 0x001D8690 | `src/effectTool` |
| `moveDataElements` | `SetEnemyStonizedVisual` | anchor | 0x001DA050 | `src/enemy` |
| `FlagDL` | `moveDataElements` | anchor | 0x001DAD60 | `src/enemyParts` |
| `playSE` | `executeSEPackageWithNoGObj` | anchor | 0x001DCB38 | `src/frameDependSequence` |
| `playSERandomID` | `ExecuteSEPackageWithGroupVariation` | anchor | 0x001DCC68 | `src/frameDependSequence` |
| `playSEConditionID` | `ExecuteSEPackage` | anchor | 0x001DCC88 | `src/frameDependSequence` |
| `playEff` | `ExecuteSEPackageWithVolumeRate` | anchor | 0x001DCC90 | `src/frameDependSequence` |
| `execEff` | `StopSEPackageWithGroupVariation` | anchor | 0x001DCCA0 | `src/frameDependSequence` |
| `executeSEPackageWithNoGObj` | `execSE` | anchor | 0x001DCF90 | `src/frameDependSequence` |
| `ExecuteSEPackageWithGroupVariation` | `checkWaterDepth` | anchor | 0x001DCFF8 | `src/frameDependSequence` |
| `ExecuteSEPackage` | `checkModelDataID` | anchor | 0x001DD010 | `src/frameDependSequence` |
| `InitMotionFile` | `CheckMotionIncludeFacialData` | anchor | 0x001E14B8 | `src/motionFileManager` |
| `AddMotionMemorySize` | `limitHPAngleAndSetB` | anchor | 0x001E1588 | `src/motionManager` |
| `GetMotionMemorySize` | `avoidReverseInterpOnCurrentMatrix` | anchor | 0x001E1D10 | `src/motionManager` |
| `ResetDynamicMotionManager` | `avoidReverseInterpOnCurrentMatrixWithLimit` | anchor | 0x001E1E60 | `src/motionManager` |
| `CheckMotionIncludeFacialData` | `EditRotEmphasys` | anchor | 0x001E4C60 | `src/motionManager` |
| `checkCliffState` | `checkCliffAndWallStateOfLastPlane` | anchor | 0x001E6478 | `src/motionManager` |
| `_checkCliffAndWall` | `checkCliffAndWallStateAtJump` | anchor | 0x001E6518 | `src/motionManager` |
| `checkCliffAndWallStateOfLastPlane` | `dispActNode` | anchor | 0x001E6570 | `src/motionManager` |
| `checkCliffAndWallStateAtJump` | `dispLastNode` | anchor | 0x001E66D0 | `src/motionManager` |
| `dispActNode` | `_wallHitReaction` | anchor | 0x001E6750 | `src/motionManager` |
| `dispLastNode` | `_wallCollisionPreProcess` | anchor | 0x001E6C20 | `src/motionManager` |
| `execPositionReserver` | `setIKAndAdjustRootHeight` | anchor | 0x001E6EA8 | `src/motionManager` |
| `GetGeometryOfMotion` | `landingFieldAction` | anchor | 0x001E7688 | `src/motionManager` |
| `GetMatrixOfMotion` | `floorFitting` | anchor | 0x001E77C8 | `src/motionManager` |
| `dispSkelton` | `adjustSideWall` | anchor | 0x001E8EC8 | `src/motionManager` |
| `SkelTestGeo` | `forceFallDown` | anchor | 0x001E9248 | `src/motionManager` |
| `GetWallVector` | `checkWallUpperWall` | anchor | 0x001E92A8 | `src/motionManager` |
| `getGeometryOfMotion` | `calcWallFittingGeometry` | anchor | 0x001E9308 | `src/motionManager` |
| `GetMotionPlaySpeedRatio` | `getFinalMatrixCore` | anchor | 0x001ED480 | `src/motionManager` |
| `execFrameTrigger` | `pursueNaturalGeometry` | anchor | 0x001ED560 | `src/motionManager` |
| `UpdateFrameCounter` | `GetWallVector` | anchor | 0x001ED610 | `src/motionManager` |
| `sendStateMail` | `upperFieldCheck` | anchor | 0x001ED640 | `src/motionManager` |
| `shiftMotionData` | `getGeometryOfMotion` | anchor | 0x001ED6A0 | `src/motionManager` |
| `SetMotionRequest` | `sendStateMail` | anchor | 0x001EE140 | `src/motionOrientManager` |
| `setParticleEffect` | `DispMultiBgaManagerWithKind` | anchor | 0x001F3B80 | `src/multiBgaManager` |
| `moveStartSE` | `GetRotObjectHoldPoint` | anchor | 0x001F7130 | `src/rotObject` |
| `CallSpidersToReviveEnemy` | `InitSpiderLayoutGeo` | anchor | 0x001F7A98 | `src/spider` |
| `DispStageMultiBgaManager` | `auraInspireBefore` | anchor | 0x001F9A60 | `src/staticBlur` |
| `auraInspireBefore` | `reduceWork2ToWork0` | anchor | 0x001FB360 | `src/staticBlur` |
| `copyCurrentFBToFeedBackArea` | `pasteFullScreenFlare` | anchor | 0x001FBDF0 | `src/staticBlur` |
| `blendWork0ToWork1` | `copyToWork_233` | anchor | 0x001FBF58 | `src/staticBlur` |
| `parallelAddFeedBackAreaToWork0` | `copyToWork2` | anchor | 0x001FC080 | `src/staticBlur` |
| `blurBlendFeedBackAreaToWork1` | `pasteToFB` | anchor | 0x001FC178 | `src/staticBlur` |
| `auraInspireAfter` | `MotionBlur` | anchor | 0x001FCA60 | `src/staticBlur` |
| `cleanUpFB` | `calcSun` | anchor | 0x001FCC60 | `src/staticBlur` |
| `fillWork2` | `colorSetting` | anchor | 0x001FCD20 | `src/staticBlur` |
| `dispSun` | `dispPostInfo` | anchor | 0x001FCEE0 | `src/staticBlur` |
| `reduceWork2ToWork0` | `InitStaticBlur` | anchor | 0x001FD480 | `src/staticBlur` |
| `UpdateStormPackage` | `SetStaticBlur` | anchor | 0x001FD530 | `src/staticBlur` |
| `DispStormPackage` | `SetDepthFadeParam` | anchor | 0x001FD540 | `src/staticBlur` |
| `InitStormTestGeo` | `_initStaticBlur` | anchor | 0x001FD578 | `src/staticBlur` |
| `DeleteStreamMotionManager` | `CheckReadyStreamMotion` | anchor | 0x001FF090 | `src/streamMotionManager` |
| `SugiLeafGeo` | `_handler` | anchor | 0x001FF1E8 | `src/streamMotionManager` |
| `CreateWaySystemManagerGObj` | `UpdateRealTimeGeometryValue` | anchor | 0x00200358 | `src/torch` |
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
| `add_wp_pos` | `CreateWayPoint` | anchor | 0x00216168 | `src/way_llf` |
| `WayLengthOfPos_Pos` | `AddWayPoint` | anchor | 0x002161E0 | `src/way_llf` |
| `WayPointWithRangeFromPos` | `AddWayPointTop` | anchor | 0x00216248 | `src/way_llf` |
| `WayPointWithRangeFromPos2` | `InsertWayPointAfter` | anchor | 0x00216290 | `src/way_llf` |
| `WayPointWithRangeFromGObj` | `WayBridgeAll_begin` | anchor | 0x002164D8 | `src/way_llf` |
| `CreateTempWayGroup` | `WayPoint_begin` | anchor | 0x00216618 | `src/way_llf` |
| `DeleteWayGroup` | `WayPoint_next` | anchor | 0x00216658 | `src/way_llf` |
| `CloseWayGroup` | `WayPointList_begin` | anchor | 0x00216698 | `src/way_llf` |
| `CreateWayPoint` | `WayPointList_next` | anchor | 0x002166B8 | `src/way_llf` |
| `AddWayPoint` | `waypoint_bidirectional_list` | anchor | 0x002166F8 | `src/way_llf` |
| `AddWayPointTop` | `SetWayGroupActive` | anchor | 0x00216750 | `src/way_llf` |
| `InsertWayPointAfter` | `CheckWayGroupActive` | anchor | 0x00216770 | `src/way_llf` |
| `actE3St09aSekizo` | `actE3CageFallReadyChk` | anchor | 0x0021B660 | `src/e3` |
| `actOpDemo02Chk` | `actConte14_10_Jimaku` | anchor | 0x0021EAA8 | `src/end` |
| `actSt00aDoor2Event` | `actSt24aConte01_2_Jimaku` | anchor | 0x002210B0 | `src/op` |
| `actSt04cDoorDown` | `actSt04aEnvSe` | anchor | 0x0022A6F8 | `src/st04a` |
| `actSt04cEne` | `actSt04aEnvSeWakare1` | anchor | 0x0022A820 | `src/st04a` |
| `actSt04cWaterXL` | `actSt04aEnvSeWakare2` | anchor | 0x0022AAD8 | `src/st04a` |
| `actSt04cDoorDownEvent` | `actConte09_3Jimaku` | anchor | 0x0022AC00 | `src/st04a` |
| `actSt24aSaku` | `actSt17aHasiEffect` | anchor | 0x0024DE10 | `src/st17a` |
| `audioDecCreate` | `stageSE06astrong` | anchor | 0x00256228 | `src/stageSEProc` |
| `audioDecEndPut` | `stageSE06abirdIn` | anchor | 0x00256338 | `src/stageSEProc` |
| `sendToIOP2area` | `stageSE06abirdOut` | anchor | 0x00256390 | `src/stageSEProc` |
| `audioDecSendToIOP` | `stageSE06ataimatsu` | anchor | 0x002563E8 | `src/stageSEProc` |
| `pcmCallback` | `stageSE08astrong` | anchor | 0x00256458 | `src/stageSEProc` |
| `audioDecDelete` | `stageSE08astrong2` | anchor | 0x00256528 | `src/stageSEProc` |
| `audioDecReset` | `stageSE08anoise3` | anchor | 0x00256600 | `src/stageSEProc` |
| `audioDecIsPreset` | `stageSE08ataimatsu` | anchor | 0x00256688 | `src/stageSEProc` |
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
| `endDisplay` | `GetDataFileName` | anchor | 0x00257218 | `src/access` |
| `setDMAscTag` | `GetDataFileName2` | anchor | 0x00257260 | `src/access` |
| `setPRIM` | `ObjAction_Mail` | anchor | 0x00257398 | `src/objact` |
| `ErrMessage` | `ObjAction_Init` | anchor | 0x002574F8 | `src/objact` |
| `viBufCreate` | `loadImage` | anchor | 0x00258B10 | `ito/mpeg/mv_disp` |
| `viBufBeginPut` | `startDisplay` | anchor | 0x00258B88 | `ito/mpeg/mv_disp` |
| `viBufAddDMA` | `setDMAscTag` | anchor | 0x00258BD8 | `ito/mpeg/mv_disp` |
| `viBufDelete` | `setPRIM` | anchor | 0x00258E10 | `ito/mpeg/mv_disp` |
| `viBufPutTs` | `setRGBAQ` | anchor | 0x00258EF0 | `ito/mpeg/mv_disp` |
| `ResetGObjProc` | `setCLAMP_1` | anchor | 0x002591E8 | `ito/mpeg/mv_disp` |
| `GetMaxGObj` | `setBITBLTBUF` | anchor | 0x00259260 | `ito/mpeg/mv_disp` |
| `GetGObjP` | `setTRXPOS` | anchor | 0x00259298 | `ito/mpeg/mv_disp` |
| `GetGObjId` | `setTRXREG` | anchor | 0x002592D0 | `ito/mpeg/mv_disp` |
| `PrintGObjID` | `setTRXDIR` | anchor | 0x00259308 | `ito/mpeg/mv_disp` |
| `InitPObj` | `GetGObjId` | anchor | 0x0025A6E0 | `src/GobjProc` |
| `FreePObj` | `PrintGObjID` | anchor | 0x0025A728 | `src/GobjProc` |

## Placeholders replaced

1101 `func_<VMA>` symbols took their PAL twin's name.  They carry no
history worth preserving: the address in the old name is the entry in
`config/symbol_addrs.us.txt`, so every one of them is recoverable from the
address column there.

## Dropped: target name still occupied by another ntsc address

730 anchor twins were NOT applied because the PAL name is still
carried by a different ntsc symbol that this pass could not move.  Most of
those blockers are themselves wrong (327 are tagged `provisional-ordinal`,
358 are untagged but their own PAL twin names them something else) — a
follow-up pass that first demotes a contradicted blocker back to
`func_<VMA>` would recover most of this list.

| ntsc addr | old | wanted (PAL twin) | blocked by ntsc symbol at |
| --- | --- | --- | --- |
| 0x00102790 | `func_00102790` | `GetRootQuaternionByDObj` | 0x001028F0 |
| 0x001027C8 | `func_001027C8` | `UpdateRootMatrixByDObj` | 0x00102970 |
| 0x00102870 | `func_00102870` | `SetRootQuaternion` | 0x00102A38 |
| 0x001028F0 | `GetRootQuaternionByDObj` | `SetRootMatrixWithTransOffsetByDObj` | 0x00102A40 |
| 0x00102A40 | `SetRootMatrixWithTransOffsetByDObj` | `SetDirectRootPositionNoFittingWithNodePoint` | 0x00103120 |
| 0x00104AF0 | `func_00104AF0` | `getInitialMatrix` | 0x001DC0E8 |
| 0x00104EF0 | `func_00104EF0` | `InitMatrixDrive` | 0x00105390 |
| 0x00104F20 | `func_00104F20` | `MatrixDrive_PushMatrix` | 0x00105488 |
| 0x001052A8 | `func_001052A8` | `MatrixDrive_TransMatrixV` | 0x00105D88 |
| 0x00105308 | `func_00105308` | `MatrixDrive_TransMatrix` | 0x00105E70 |
| 0x00105390 | `InitMatrixDrive` | `MatrixDrive_TurnObjectMatrix` | 0x00105F00 |
| 0x00105488 | `MatrixDrive_PushMatrix` | `MatrixDrive_TurnXObjectMatrixZY` | 0x00105F10 |
| 0x00105D88 | `MatrixDrive_TransMatrixV` | `MatrixDrive_GetTurnMinusZAngleXY` | 0x00106090 |
| 0x00105E70 | `MatrixDrive_TransMatrix` | `MatrixDrive_SetTransposeMatrix` | 0x00106390 |
| 0x00106570 | `CopyVector` | `dispPlane` | 0x00106AB8 |
| 0x00106A98 | `GetWaterReaction` | `GetOrientOfWallOfGObj` | 0x00106B70 |
| 0x00106AA8 | `CheckFieldContact` | `GetOrientOfCliffOfGObj` | 0x00106B80 |
| 0x00106AB8 | `dispPlane` | `SetMotionDirection` | 0x00106D20 |
| 0x00106B70 | `GetOrientOfWallOfGObj` | `_GetMotionDirection` | 0x00106D68 |
| 0x00106B80 | `GetOrientOfCliffOfGObj` | `SetMotionDirectionWithLimit` | 0x00106DA8 |
| 0x00106D20 | `SetMotionDirection` | `GetRootPosOfNextFrame` | 0x00106DF0 |
| 0x00106D68 | `_GetMotionDirection` | `AdjustMotionHeightToField` | 0x00106E38 |
| 0x00106E38 | `AdjustMotionHeightToField` | `calcFootIK` | 0x00107778 |
| 0x00107270 | `GetLowerPlaneCollision` | `InitMotionGeoInfo` | 0x001077F8 |
| 0x00107778 | `calcFootIK` | `DispSkelton` | 0x00107DD8 |
| 0x00107DD8 | `DispSkelton` | `getVerticalElementOfWallNormal` | 0x001082B0 |
| 0x00107E28 | `SlopeIKControl` | `AdjustVerticalSidePlaneOfWall` | 0x00108698 |
| 0x001080F8 | `GetPureVerticalPlaneOfCurrentPosition` | `GetPureVerticalPlane` | 0x00108A50 |
| 0x001082B0 | `getVerticalElementOfWallNormal` | `_getS16MotRotElem` | 0x00108BD0 |
| 0x00108698 | `AdjustVerticalSidePlaneOfWall` | `_getMotion` | 0x00108C98 |
| 0x00108A50 | `GetPureVerticalPlane` | `GetStreamMotion` | 0x001097A0 |
| 0x00108BD0 | `_getS16MotRotElem` | `copyMotionWithNodeHrc` | 0x00109918 |
| 0x00108C98 | `_getMotion` | `CopyMotionWithNodeHrc` | 0x00109B58 |
| 0x00108DA0 | `GetMotion` | `GetFloatingMotion` | 0x00109B98 |
| 0x001097A0 | `GetStreamMotion` | `MakeMirrorMotion` | 0x00109BA8 |
| 0x00109918 | `copyMotionWithNodeHrc` | `GetFloatingShapeMotion` | 0x00109BB8 |
| 0x00109B98 | `GetFloatingMotion` | `GetMotionPointer` | 0x00109DA8 |
| 0x00109BA8 | `MakeMirrorMotion` | `GetCollisionOfLastActiveField` | 0x00109E48 |
| 0x00109BB8 | `GetFloatingShapeMotion` | `DebugDisp1Collision` | 0x00109E88 |
| 0x00109CB0 | `FeedbackWallWorkInfoToBrainSystem` | `DebugDisp1CollisionWithColor` | 0x00109F10 |
| 0x00109E88 | `DebugDisp1Collision` | `InitMotionStateInfo` | 0x0010A008 |
| 0x00109F28 | `SetMotionBlendlessNode` | `AdjustMotionHeightToNearestField` | 0x0010A028 |
| 0x00109FF8 | `ClearMotionBlendlessNode` | `SetRootUpdateMode` | 0x0010A038 |
| 0x0010A008 | `InitMotionStateInfo` | `ForMotionViewer_GetCurrentAnimationFrame` | 0x0010A048 |
| 0x0010A018 | `GetSkeltonFocusNode` | `ForMotionViewer_GetCurrentMotion` | 0x0010A068 |
| 0x0010A028 | `AdjustMotionHeightToNearestField` | `EnableMotionOrientUpdate` | 0x0010A088 |
| 0x0010A038 | `SetRootUpdateMode` | `DisableMotionOrientUpdate` | 0x0010A0A8 |
| 0x0010A048 | `ForMotionViewer_GetCurrentAnimationFrame` | `CheckFloorAttribute` | 0x0010A0C8 |
| 0x0010A068 | `ForMotionViewer_GetCurrentMotion` | `CheckWallAttribute` | 0x0010A120 |
| 0x0010A088 | `EnableMotionOrientUpdate` | `CheckPureWallAttribute` | 0x0010A160 |
| 0x0010A0A8 | `DisableMotionOrientUpdate` | `CheckPureCliffAttribute` | 0x0010A1A0 |
| 0x0010A0C8 | `CheckFloorAttribute` | `GetStreamShapeMotion` | 0x0010A200 |
| 0x0010A2E0 | `GetDifferenceFromLastField` | `DisableChangeRootUpdateMode` | 0x0010A320 |
| 0x0010A2F0 | `GetDifferenceFromLowerField` | `EnableChangeRootUpdateMode` | 0x0010A330 |
| 0x0010A320 | `DisableChangeRootUpdateMode` | `GetMotionFrameFlag2` | 0x0010A3A0 |
| 0x0010A330 | `EnableChangeRootUpdateMode` | `GetHeightOfFieldPlaneDifference` | 0x0010A3F0 |
| 0x0010A3A0 | `GetMotionFrameFlag2` | `InitMotionRotElem` | 0x0010A4F0 |
| 0x0010A4F0 | `InitMotionRotElem` | `ClearMotionGeometryInfo` | 0x0010A5E0 |
| 0x0010ADD0 | `dispPool` | `copyToWork` | 0x0010AB20 |
| 0x0010C808 | `InitLayoutedPoolReflactionMesh` | `SetLayoutedPoolReflactionMesh` | 0x0010B0D8 |
| 0x0010D198 | `func_0010D198` | `InitLayoutedPoolReflactionMesh` | 0x0010C808 |
| 0x0010D360 | `MultiCurrentQuaternion` | `getWave` | 0x0010CF88 |
| 0x0010D3E0 | `InvertCurrentQuaternion` | `MultiCurrentQuaternion` | 0x0010D360 |
| 0x0010D408 | `SetCurrentQuaternion` | `InvertCurrentQuaternion` | 0x0010D3E0 |
| 0x0010D428 | `RotCurrentQuaternionX` | `SetCurrentQuaternion` | 0x0010D408 |
| 0x0010D4A8 | `InitQuaternionDrive` | `PushQuaternion` | 0x0010D488 |
| 0x0010D540 | `getQuaternionFromMatrix` | `GetMatrixFromQuaternion` | 0x0010D530 |
| 0x0010D5C8 | `GetQuaternionFromMatrix` | `getQuaternionFromMatrix` | 0x0010D540 |
| 0x0010D7F8 | `CopyQuaternion` | `GetQuaternionFromMatrix` | 0x0010D5C8 |
| 0x0010D838 | `RegularizeQuaternion` | `GetInverseQuaternion` | 0x0010D830 |
| 0x0010D878 | `GetSlerpQuaternionNoRegularize` | `RegularizeQuaternion` | 0x0010D838 |
| 0x0010D8E0 | `GetSlerpQuaternion` | `GetSlerpQuaternionNoRegularize` | 0x0010D878 |
| 0x0010E950 | `p2o_SetDefaultEnviroment` | `GetTableSin` | 0x0010DAB8 |
| 0x0010F630 | `func_0010F630` | `gif_EndPacket` | 0x00110580 |
| 0x0010F880 | `func_0010F880` | `gif_MakeLine2DOffset` | 0x00110AF0 |
| 0x0010F9A8 | `func_0010F9A8` | `gif_MakeSprite` | 0x00110C38 |
| 0x001103E0 | `gif_StartPacket` | `gif_SpriteSensitive` | 0x001118B0 |
| 0x00110580 | `gif_EndPacket` | `gif_SpriteOffset` | 0x001118B8 |
| 0x00110790 | `gif_StartPacketPath1` | `gif_SpriteSensitiveOffset` | 0x001118E8 |
| 0x00110AF0 | `gif_MakeLine2DOffset` | `gif_SpriteSensitiveOrg` | 0x00111940 |
| 0x001128F8 | `gsb_setSemitransReg` | `gsb_KeepFrameBuffer` | 0x00112188 |
| 0x001137B8 | `gsb_PostEffect` | `gsb_setNormalReg` | 0x00112520 |
| 0x00113820 | `gsb_InitGSSystem` | `gsb_setSemitransReg` | 0x001128F8 |
| 0x00113890 | `gsb_UpdateGSSystem` | `gsb_setSpecularReg` | 0x00112B88 |
| 0x00113908 | `gsb_ResetGSSystem` | `gsb_setParticleReg` | 0x00112F08 |
| 0x00114080 | `gsb_SetBGColor` | `gsb_ResetGSSystem` | 0x00113908 |
| 0x00114748 | `light_killLinkAmbient` | `gsb_ClipBox` | 0x00113C98 |
| 0x00114D80 | `light_getAmbientLight` | `gsb_SetBGColor` | 0x00114080 |
| 0x00114DD8 | `light_MakeLightMatrix` | `gsb_GetBGColor` | 0x001141A0 |
| 0x00114FC8 | `light_KillAllFixLight` | `light_killLinkLight` | 0x00114560 |
| 0x00115068 | `light_KillAllAmbient` | `light_killLinkAmbient` | 0x00114748 |
| 0x001165A8 | `func_001165A8` | `light_GetColorAnalog` | 0x00114E18 |
| 0x00116888 | `func_00116888` | `light_DrawCursor` | 0x00114E78 |
| 0x00116C08 | `func_00116C08` | `light_Tool` | 0x00114F18 |
| 0x00117768 | `func_00117768` | `light_KillAllFixLight` | 0x00114FC8 |
| 0x001177C8 | `func_001177C8` | `light_KillAllAmbient` | 0x00115068 |
| 0x00117820 | `func_00117820` | `light_AddAmbientObject` | 0x00115108 |
| 0x00117890 | `func_00117890` | `light_resetFlatLight` | 0x00115410 |
| 0x00117FC0 | `_UnitCurrentMatrix` | `_GetCurrentMatrix` | 0x001181E0 |
| 0x00117FD8 | `_PushCurrentMatrix` | `_GetCurrentMatrixTrans` | 0x00118268 |
| 0x00118E88 | `pac_makeClusterStrip` | `mc_TransMicroCode` | 0x00118460 |
| 0x0011A238 | `pac_setMaterialPacket` | `pac_openDmaTag` | 0x00118F58 |
| 0x0011A2A8 | `pac_makeMaterialTable` | `pac_setVifCode` | 0x00118F98 |
| 0x0011A2F0 | `pac_makeMaterialTableLine` | `pac_setVifEndCode` | 0x00118FD8 |
| 0x0011A990 | `pac_Init` | `pac_makeStrip` | 0x00119CA0 |
| 0x0011ACF8 | `pac_DispVu1Memory` | `pac_setMaterialPacket` | 0x0011A238 |
| 0x0011AE78 | `func_0011AE78` | `pac_makeMaterialTable` | 0x0011A2A8 |
| 0x0011B040 | `func_0011B040` | `pac_makeMaterialTableLine` | 0x0011A2F0 |
| 0x0011BFC0 | `prim_SetFan2D` | `pac_DispVu1Memory` | 0x0011ACF8 |
| 0x0011C028 | `prim_DispFan2D` | `prim_InitFan2D` | 0x0011BFB8 |
| 0x0011C2B8 | `prim_makePacketMesh3D` | `prim_SetFan2D` | 0x0011BFC0 |
| 0x0011C500 | `prim_InitMesh3D` | `prim_DispFan2D` | 0x0011C028 |
| 0x0011C868 | `prim_makeNormal` | `prim_makePacketMesh3D` | 0x0011C2B8 |
| 0x0011CE90 | `setMatrix` | `prim_makeNormal` | 0x0011C868 |
| 0x0011D2E8 | `setLight` | `prim_UpdateMesh3D` | 0x0011CBF8 |
| 0x0011D590 | `clearUVOffset` | `setMatrix` | 0x0011CE90 |
| 0x0011D658 | `prim_DispMesh3D` | `setLight` | 0x0011D2E8 |
| 0x0011D730 | `prim_InitParticle` | `clearUVOffset` | 0x0011D590 |
| 0x0011D800 | `prim_DispParticle` | `prim_DispMesh3D` | 0x0011D658 |
| 0x0011DEE0 | `prim_DispWireYCylinder` | `prim_DeleteParticle` | 0x0011D9A0 |
| 0x0011DF18 | `prim_DispWireSphere` | `drawDisc` | 0x0011DD08 |
| 0x0011E0B8 | `reg_setShape` | `prim_DispWireYCylinder` | 0x0011DEE0 |
| 0x0011E220 | `reg_dispBoxLine` | `prim_DispWireSphere` | 0x0011DF18 |
| 0x0011E708 | `func_0011E708` | `prim_InitParticle` | 0x0011D730 |
| 0x0011EB50 | `reg_chooseMicroCode` | `reg_dispBoxLine` | 0x0011E220 |
| 0x0011EE30 | `func_0011EE30` | `reg_chooseMicroCode` | 0x0011EB50 |
| 0x0011EE58 | `func_0011EE58` | `reg_chooseSpecularMicroCode` | 0x0011ECE0 |
| 0x0011EE70 | `reg_setNMatrixPacket` | `reg_chooseReflectionMicroCode` | 0x0011EDF8 |
| 0x0011FCD8 | `reg_dispCObj` | `reg_transMaterialPacket` | 0x0011F040 |
| 0x0011FD28 | `reg_dispPoint` | `reg_setDissolve` | 0x0011F248 |
| 0x0011FF30 | `reg_dispLine` | `reg_resetDissolve` | 0x0011F398 |
| 0x00120DF8 | `reg_setEMatrixPacket` | `reg_dispPoint` | 0x0011FD28 |
| 0x00121298 | `reg_DispEnemy` | `reg_dispLine` | 0x0011FF30 |
| 0x001222E0 | `__GetCameraPos` | `reg_setEMatrixPacket` | 0x00120DF8 |
| 0x00123C00 | `func_00123C00` | `shadow_Render` | 0x00121A90 |
| 0x001243E8 | `stage_ApplyData` | `__GetCameraPos` | 0x001222E0 |
| 0x001297A0 | `stage_KillPlayBgAnimation` | `stage_SetAnimation` | 0x00126260 |
| 0x0012A7A0 | `stage_KillPlayBgAnimationIfOverMaxCount` | `stage_KillPlayBgAnimation` | 0x001297A0 |
| 0x0012ABE0 | `func_0012ABE0` | `stage_SetLoopFlag` | 0x00129E28 |
| 0x0012AC28 | `func_0012AC28` | `stage_SetFrameStep` | 0x00129F58 |
| 0x0012AC70 | `func_0012AC70` | `stage_SetParentOfGObj` | 0x0012A060 |
| 0x0012ACD8 | `func_0012ACD8` | `stage_SetParentOfGObjWithLocalRotationFlag` | 0x0012A318 |
| 0x0012AD40 | `tex_AllocVramAuto` | `stage_SetLocalizeGeometry` | 0x0012A618 |
| 0x0012ADE8 | `tex_loadImage` | `stage_KillPlayBgAnimationIfOverMaxCount` | 0x0012A7A0 |
| 0x0012AED0 | `tex_transVramClutTex` | `tex_AllocVramAuto` | 0x0012AD40 |
| 0x0012B850 | `tex_transTM2` | `tex_transVramClutTex` | 0x0012AED0 |
| 0x0012BA68 | `tex_initClutTexture` | `tex_transVramDirectTex` | 0x0012AFC0 |
| 0x0012BBE8 | `tex_setRegisters` | `tex_transRegister` | 0x0012B1C0 |
| 0x0012C610 | `tex_makeTexturePacket` | `tex_convertClutCSM2ToCSM1` | 0x0012BEB0 |
| 0x0012C8F8 | `tex_LoadTexturePart` | `tex_makeCopyImage` | 0x0012C3D0 |
| 0x0012D4A0 | `tex_FreeTexture` | `tex_scrollClut` | 0x0012CEF8 |
| 0x0012DA48 | `tex_ResetVram` | `tex_textureAnimation` | 0x0012D218 |
| 0x0012DE00 | `tex_dispClut` | `tex_SetClutAnimation` | 0x0012D370 |
| 0x0012DE80 | `tex_printTexture` | `tex_FreeTexture` | 0x0012D4A0 |
| 0x0012E528 | `tex_GetTWTH` | `tex_printTexture` | 0x0012DE80 |
| 0x0012F818 | `fog_DrawFog` | `tex_ListTool` | 0x0012E0D8 |
| 0x0012FCE0 | `fog_FogTool` | `tex_GetTWTH` | 0x0012E528 |
| 0x00130250 | `iosCdvdMgrStStop` | `fog_MakeFogClut` | 0x0012E940 |
| 0x00130F98 | `temp_loadfunc` | `fog_FogTool` | 0x0012FCE0 |
| 0x001320E8 | `iosCdvdLoad` | `iosCdvdHandlerRead` | 0x00131780 |
| 0x001325D8 | `iosCdvdBackGroundMgr` | `iosCdvdLoad` | 0x001320E8 |
| 0x00132610 | `iosCdvdDirectStOpen` | `iosCdvdPackLoad` | 0x001321C8 |
| 0x00133218 | `iosCdvdLoadPackFile` | `iosCdvdChgFileName` | 0x00132630 |
| 0x00133460 | `iosCdvdBackGroundMgrSeek` | `iosCdvdBackGroundMgrNotDiskReadyPauseSet` | 0x001333C8 |
| 0x00133480 | `iosCdvdBackGroundRead` | `iosCdvdBackGroundMgrDeleteRequestGet` | 0x00133448 |
| 0x00133500 | `func_00133500` | `iosCdvdBackGroundMgrSeek` | 0x00133460 |
| 0x00133608 | `func_00133608` | `iosCdvdBackGroundMgr` | 0x001325D8 |
| 0x001354B8 | `func_001354B8` | `close_inflate_handler` | 0x00133570 |
| 0x00135EB8 | `new_mblock_node` | `iosSifAllocIopHeapDebug` | 0x00135CE8 |
| 0x00135F60 | `reuse_mblock1` | `new_mblock_node` | 0x00135EB8 |
| 0x00136060 | `init_mblock` | `reuse_mblock1` | 0x00135F60 |
| 0x00136088 | `new_segment` | `init_mblock` | 0x00136060 |
| 0x00136098 | `reuse_mblock` | `new_segment` | 0x00136088 |
| 0x00136140 | `strdup_mblock` | `reuse_mblock` | 0x00136098 |
| 0x00136198 | `func_00136198` | `strdup_mblock` | 0x00136140 |
| 0x001387F0 | `iosMallocSetPartitionName` | `iosMallocSetPartition` | 0x00138618 |
| 0x00138A10 | `iosMallocClearPartition` | `iosMallocResetPartition` | 0x00138720 |
| 0x00138BF0 | `iosMallocDebug` | `iosMallocSetPartitionName` | 0x001387F0 |
| 0x001392A8 | `func_001392A8` | `iosMallocAlignDebug` | 0x00139D78 |
| 0x00139D78 | `iosMallocAlignDebug` | `iosReallocDebug` | 0x00139A50 |
| 0x00139FE8 | `func_00139FE8` | `iosMallocInitPartition` | 0x00139C30 |
| 0x0013A0F8 | `func_0013A0F8` | `iosMallocDebug` | 0x00138BF0 |
| 0x0013B298 | `iosPadGetStick` | `iosPadNormalizeStick` | 0x0013B160 |
| 0x0013B610 | `iosPadDevRead` | `iosPadActRequest` | 0x0013B450 |
| 0x0013B718 | `iosPadGetPort` | `iosPadDevRead` | 0x0013B610 |
| 0x0013B748 | `iosPadGetSlot` | `iosPadGetPort` | 0x0013B718 |
| 0x0013B760 | `iosPadGetDevice` | `iosPadGetSlot` | 0x0013B748 |
| 0x0013B778 | `iosPadConnect` | `iosPadGetDevice` | 0x0013B760 |
| 0x0013B7C0 | `iosPadStickCameraCoord` | `iosPadConnect` | 0x0013B778 |
| 0x0013B878 | `iosPadActStop` | `iosPadActInit` | 0x0013B870 |
| 0x0013B8F0 | `Vibration_ShotDecode` | `iosPadActStop` | 0x0013B878 |
| 0x0013BB80 | `Init_ShockRequestBox` | `Vibration_ShotDecode` | 0x0013B8F0 |
| 0x0013C320 | `ShockRequestBox_Request` | `Shock_SetMotor` | 0x0013BA20 |
| 0x0013C488 | `ShockRequestBox_DecodeRequest` | `Init_ShockVoiceSet` | 0x0013BB70 |
| 0x0013C4C0 | `ShockRequestBox_EndRequestFree` | `Vibration_SetDecodeData` | 0x0013BB78 |
| 0x0013C510 | `ShockRequestBox_VoiceSetUseRequestFree` | `Init_ShockRequestBox` | 0x0013BB80 |
| 0x0013C5B8 | `ShockRequestBox_RequestDirectCancel` | `ShockRequestBox_Request` | 0x0013C320 |
| 0x0013C748 | `Init_ShockDriver` | `ShockRequestBox_DecodeRequest` | 0x0013C488 |
| 0x0013C820 | `ShockDriver_VoiceSet_NumberRegist` | `ShockRequestBox_EndRequestFree` | 0x0013C4C0 |
| 0x0013C878 | `ShockDriver_VoiceSet_Regist` | `ShockRequestBox_VoiceSetUseRequestFree` | 0x0013C510 |
| 0x0013C920 | `ShockDriver_VoiceSet_Remove` | `ShockRequestBox_GetRequest` | 0x0013C538 |
| 0x0013C9D8 | `ShockDriver_GetShockVoiceSet` | `ShockRequestBox_RequestDirectCancel` | 0x0013C5B8 |
| 0x0013CA48 | `ShockDriver_GetShockVoice` | `Init_ShockDriver` | 0x0013C748 |
| 0x0013CAA0 | `Init_ShockEmulator` | `ShockDriver_VoiceSet_NumberRegist` | 0x0013C820 |
| 0x0013CAD8 | `ShockEmulator_EmulationShot` | `ShockDriver_VoiceSet_Regist` | 0x0013C878 |
| 0x0013CB50 | `ShockEmulator_EmulationWave` | `ShockDriver_VoiceSet_Remove` | 0x0013C920 |
| 0x0013CBD0 | `Get_ShockRequestStruct` | `ShockDriver_GetShockVoiceSet` | 0x0013C9D8 |
| 0x0013CC00 | `Reset_ShockRequestStruct` | `ShockDriver_GetShockVoice` | 0x0013CA48 |
| 0x0013CC70 | `Init_Shock` | `ShockEmulator_EmulationShot` | 0x0013CAD8 |
| 0x0013CC78 | `iosThreadMain` | `ShockEmulator_EmulationWave` | 0x0013CB50 |
| 0x0013CD30 | `iosThreadStart` | `Get_ShockRequestStruct` | 0x0013CBD0 |
| 0x0013CD70 | `iosThreadStop` | `Reset_ShockRequestStruct` | 0x0013CC00 |
| 0x0013CD78 | `iosThreadSleep` | `ShockRevice_Wave` | 0x0013CC60 |
| 0x0013CE48 | `iosThreadDestroy` | `Init_Shock` | 0x0013CC70 |
| 0x0013D140 | `iosGetIOSThreadFromId` | `iosThreadMain` | 0x0013CC78 |
| 0x0013D3C8 | `iosThreadJoin` | `iosThreadStart` | 0x0013CD30 |
| 0x0013D3D8 | `iosThreadCancelWakeup` | `iosThreadStop` | 0x0013CD70 |
| 0x0013D3F8 | `iosSemaDelete` | `iosThreadDestroy` | 0x0013CE48 |
| 0x0013D8E0 | `func_0013D8E0` | `iosGetIOSThreadFromId` | 0x0013D140 |
| 0x0013D928 | `func_0013D928` | `iosThreadWakeup` | 0x0013D1B0 |
| 0x0013D948 | `func_0013D948` | `iosThreadJoin` | 0x0013D3C8 |
| 0x0013D9C8 | `func_0013D9C8` | `iosThreadCancelWakeup` | 0x0013D3D8 |
| 0x0013DA00 | `func_0013DA00` | `iosSemaCreate` | 0x0013D3F0 |
| 0x0013DA88 | `func_0013DA88` | `iosSemaDelete` | 0x0013D3F8 |
| 0x0013DBB0 | `func_0013DBB0` | `iosSemaReferStatus` | 0x0013D538 |
| 0x0013DDA0 | `isysGObjKindTableInit` | `isysGObjInit` | 0x0013DDF8 |
| 0x0013DDF8 | `isysGObjInit` | `cut_gobj_link` | 0x0013DEA0 |
| 0x0013DFF0 | `isysGObjRemoveAll` | `add_gobj_to_tail` | 0x0013E0C0 |
| 0x0013E0C0 | `add_gobj_to_tail` | `add_gobj_to_head` | 0x0013E190 |
| 0x0013E220 | `isysGObjMoveHead` | `isysGObjAddAfterGObj` | 0x0013E350 |
| 0x0013E350 | `isysGObjAddAfterGObj` | `isysGObjAddBeforeGObj` | 0x0013E488 |
| 0x0013E488 | `isysGObjAddBeforeGObj` | `isysGetNbAllocedGObjs` | 0x0013E4D0 |
| 0x0013E4D0 | `isysGetNbAllocedGObjs` | `isysGObjAlloc` | 0x0013E548 |
| 0x0013E7F8 | `isysGObjKindTableRemove` | `isysGObjMoveAfterGObj` | 0x0013E868 |
| 0x0013E868 | `isysGObjMoveAfterGObj` | `isysGObjMoveBeforeGObj` | 0x0013E8D8 |
| 0x0013E8D8 | `isysGObjMoveBeforeGObj` | `isysGObjAdd` | 0x0013E9E0 |
| 0x0013E9E0 | `isysGObjAdd` | `isysGObjAddHead` | 0x0013EAE8 |
| 0x0013EAE8 | `isysGObjAddHead` | `isysGObjSearchFromObjLayoutID` | 0x0013EB50 |
| 0x0013F130 | `isysGObjMoveObjDLAfterGObj` | `isysGObjLinkObjDL` | 0x0013EE58 |
| 0x0013F1D0 | `isysGObjMoveObjDLBeforeGObj` | `isysGObjLinkObjDLHead` | 0x0013EE60 |
| 0x0013F2C8 | `isysGObjProcessInit` | `isysGObjDlInit` | 0x0013F0E8 |
| 0x0013F308 | `isysGObjProcAdd_` | `isysGObjMoveObjDLAfterGObj` | 0x0013F130 |
| 0x0013F378 | `cut_gobj_process_link` | `isysGObjMoveObjDLBeforeGObj` | 0x0013F1D0 |
| 0x0013F3F0 | `isysGObjProcessAlloc` | `isysGObjProcAdd_` | 0x0013F308 |
| 0x0013F638 | `isysGObjProcAdd` | `cut_gobj_process_link` | 0x0013F378 |
| 0x0013F6B8 | `isysGObjProcAddS` | `isysGObjProcRemove` | 0x0013F3E8 |
| 0x0013F700 | `isysGObjProcAddGOppArg` | `isysGObjProcessAlloc` | 0x0013F3F0 |
| 0x0013F778 | `isysGObjProcPause` | `isysGObjProcAdd` | 0x0013F638 |
| 0x0013F7A8 | `isysGObjProcPauseAll` | `isysGObjProcAddS` | 0x0013F6B8 |
| 0x0013F7D8 | `isysGObjProcPausePtr` | `isysGObjProcAddGOppArg` | 0x0013F700 |
| 0x0013F808 | `isysGObjProcActive` | `isysGObjProcPause` | 0x0013F778 |
| 0x0013F810 | `isysGObjProcActiveAll` | `isysGObjProcPauseAll` | 0x0013F7A8 |
| 0x0013F848 | `isysInitialize` | `isysGObjProcPausePtr` | 0x0013F7D8 |
| 0x0013F878 | `func_0013F878` | `isysGObjProcActive` | 0x0013F808 |
| 0x0013F888 | `func_0013F888` | `isysGObjProcActiveAll` | 0x0013F810 |
| 0x0013F9A0 | `func_0013F9A0` | `iosOmInit` | 0x0013F9D0 |
| 0x0013F9D0 | `iosOmInit` | `_iosOmMain` | 0x0013FBF8 |
| 0x0013FC00 | `iosOmMain` | `iosOmCreateDL` | 0x0013FD10 |
| 0x0013FD10 | `iosOmCreateDL` | `iosOmExeEachGObj` | 0x0013FD78 |
| 0x0013FD78 | `iosOmExeEachGObj` | `iosOmExeEachGObjAll` | 0x0013FE18 |
| 0x0013FE18 | `iosOmExeEachGObjAll` | `iosOmReturnExeEachGObj` | 0x0013FEB0 |
| 0x0013FEB0 | `iosOmReturnExeEachGObj` | `iosOmGetGObjStatus` | 0x0013FEE0 |
| 0x0013FEE0 | `iosOmGetGObjStatus` | `iosOmSearchGObjId` | 0x0013FF20 |
| 0x0013FF20 | `iosOmSearchGObjId` | `iosOmSearchGObjIdAll` | 0x0013FF80 |
| 0x00140748 | `AdpcmInterLeaveVolumeSet` | `AdpcmOpen` | 0x00140340 |
| 0x00140B30 | `AdpcmIopBuffAlloc` | `AdpcmInterLeaveVolumeSet` | 0x00140748 |
| 0x00140B60 | `AdpcmOpenSync` | `AdpcmVolumeSet` | 0x00140888 |
| 0x00140CE0 | `AdpcmUseAreaGet` | `AdpcmIopBuffAlloc` | 0x00140B30 |
| 0x00140E48 | `AdpcmFreeAreaGet` | `AdpcmOpenSync` | 0x00140B60 |
| 0x00140EE8 | `AdpcmInterStereoVolumeSetAll` | `AdpcmFadeCloseAll` | 0x00140B70 |
| 0x00140F20 | `AdpcmInterLeaveVolumeGet` | `AdpcmUseAreaGet` | 0x00140CE0 |
| 0x00140F58 | `AdpcmVolumeGet` | `AdpcmFreeAreaGet` | 0x00140E48 |
| 0x00140F90 | `GetDitchPosition` | `AdpcmInterStereoVolumeSetAll` | 0x00140EE8 |
| 0x00141020 | `DebugActOrientFlag` | `AdpcmInterLeaveVolumeGet` | 0x00140F20 |
| 0x00141038 | `ACTGetEnvironment` | `AdpcmVolumeGet` | 0x00140F58 |
| 0x00141980 | `soundDataOpenSync` | `soundBDDataSet` | 0x00141660 |
| 0x00141E00 | `soundSeVolSet` | `soundDataClose` | 0x00141C28 |
| 0x00141F58 | `debug_DispSEInfo` | `soundDataSegAllClose` | 0x00141D18 |
| 0x00142008 | `sound3DParamSet` | `soundSeVolSet` | 0x00141E00 |
| 0x00142208 | `_soundSeDefPlay` | `debug_DispSEInfo` | 0x00141F58 |
| 0x00142890 | `_soundSeDefStop` | `sound3DParamSet` | 0x00142008 |
| 0x00143138 | `soundSeDefStopNoRelease` | `_soundSeDefStop` | 0x00142890 |
| 0x00143248 | `soundReqTickProc` | `soundSeDefStopNoRelease` | 0x00143138 |
| 0x00143250 | `soundSeEnvPlay` | `soundSeDefPitchSet` | 0x00143240 |
| 0x00143AD0 | `soundOutputModeGet` | `Ee2Iop` | 0x00143948 |
| 0x00143B98 | `soundBufAdpcmFree` | `soundBufAdpcmChAlloc` | 0x00143B90 |
| 0x00143CB0 | `soundDataAreaSearch` | `soundBufAdpcmFree` | 0x00143B98 |
| 0x00143CD0 | `soundDataAreaGet` | `soundDataAreaSearch` | 0x00143CB0 |
| 0x00143D18 | `soundHDDataSet` | `soundDataAreaGet` | 0x00143CD0 |
| 0x00143E60 | `soundSQDataSet` | `soundHDDataSet` | 0x00143D18 |
| 0x00143FC0 | `soundSeDefPlay` | `soundSQDataSet` | 0x00143E60 |
| 0x00144120 | `soundSeDefPlayWithVolumeRate` | `soundSeDefPlay` | 0x00143FC0 |
| 0x00144178 | `soundSeDefVolumeRateGet` | `soundSeDefPlayWithVolumeRate` | 0x00144120 |
| 0x001441C8 | `soundSeDefVolumeRateSet` | `soundSeDefVolumeRateGet` | 0x00144178 |
| 0x00144208 | `soundSeGroupStop` | `soundSeDefVolumeRateSet` | 0x001441C8 |
| 0x00144240 | `soundSeGroupGet` | `soundSeGroupStop` | 0x00144208 |
| 0x001442E0 | `soundSePlayModeStop` | `soundSeGroupGet` | 0x00144240 |
| 0x00144308 | `soundVBlank` | `soundSePlayModeStop` | 0x001442E0 |
| 0x001444A0 | `soundSeSemiCommonLoadChk` | `soundVBlank` | 0x00144308 |
| 0x001445C8 | `sndBgmReadyNextStage` | `soundSeEnvDefaultSet` | 0x00144500 |
| 0x001446E8 | `sndInit` | `debug_req` | 0x001445C0 |
| 0x00144780 | `sndManager` | `sndBgmReadyNextStage` | 0x001445C8 |
| 0x001447E0 | `func_001447E0` | `sndInit` | 0x001446E8 |
| 0x00145328 | `func_00145328` | `_ACTGame_SearchGObj` | 0x00149D60 |
| 0x001457A8 | `func_001457A8` | `_ACTCharStatus_Clear` | 0x00149EF8 |
| 0x00145900 | `func_00145900` | `GetSkeltonOrient` | 0x00149F20 |
| 0x00149C28 | `ACTGame_LwsEffectProcess` | `updateHMC` | 0x0014A560 |
| 0x00149EA8 | `ACTParaStatus_Clear` | `ACTGameCollisionOn` | 0x0014A6B8 |
| 0x0014A100 | `ActOrientTest` | `GetSkeltonPosition` | 0x0014ADF8 |
| 0x0014A178 | `GetGirlHandlinkClInfo` | `SetDirectRootPositionWithNodePointLimit` | 0x0014AEC8 |
| 0x0014B7A8 | `func_0014B7A8` | `GetOtherStageGirlOrient` | 0x0014A308 |
| 0x0014BDD8 | `func_0014BDD8` | `ActPara_StatusToFlag` | 0x0014B248 |
| 0x00154218 | `actBoyBelift` | `ACTSearchEnemy` | 0x00154E70 |
| 0x00156688 | `_ACTCorrectMsg` | `CollisCheckInRope` | 0x00157EB0 |
| 0x00157BF8 | `WithMailFunc_WayBeginPosError` | `SetDirectRootPositionXZ` | 0x001594B0 |
| 0x00159240 | `lever_nego1` | `correctJumpOrientByChain` | 0x0015D3C0 |
| 0x0015C130 | `_boxbar_set_sound` | `E3_LeverCheck` | 0x0015EF40 |
| 0x0015D348 | `funcCommonJumpDircorrect` | `ACTAdjustPlane` | 0x0015F2D8 |
| 0x0015FC50 | `actEnemyForceSwitchToCarry` | `_MustChase` | 0x0015F6F0 |
| 0x00162AC8 | `enemy_dodge` | `GetFlyPosition` | 0x00163068 |
| 0x001651C8 | `actEnemyRun` | `actEnemyFlagOnFree` | 0x001653A0 |
| 0x00165270 | `actEnemyCarry` | `actEnemyFlagOnDead` | 0x001653E8 |
| 0x001652F8 | `funcEnemyCarryFail` | `actEnemyFlagCheckActive` | 0x001654C8 |
| 0x00166028 | `_Clip` | `MakeCollisionDependGObjList` | 0x00165E60 |
| 0x00166118 | `__ClipWall` | `GetReflectionElement` | 0x00165EB8 |
| 0x00166258 | `__ClipFloor` | `clip_wall_1` | 0x00165F00 |
| 0x00166A10 | `DrawGObjFloorCollision` | `DispCollisionPC` | 0x00165FB8 |
| 0x00166E10 | `GetEdgeOfFloor` | `_Clip` | 0x00166028 |
| 0x00167528 | `ClipWallDebug` | `DrawGObjFloorCollision` | 0x00166A10 |
| 0x001677D0 | `ClipWallR` | `GetEdgeOfFloor` | 0x00166E10 |
| 0x00167E00 | `ClipWallWaveForce` | `DrawCollisionRay` | 0x00167230 |
| 0x00168058 | `ClipWallFuchiHangWalkStop` | `MakeExitAttributeIndex` | 0x00167258 |
| 0x001683A8 | `ClipWallEField` | `ClipWallDebug` | 0x00167528 |
| 0x001683E8 | `ClipWallAdjustPos` | `ClipWallR` | 0x001677D0 |
| 0x00168408 | `ClipWallE` | `ClipWallWaveForce` | 0x00167E00 |
| 0x00168428 | `ClipWallCheckCB` | `ClipWallFuchiHangWalkStop` | 0x00168058 |
| 0x00168468 | `ClipFloor` | `ClipWallEField` | 0x001683A8 |
| 0x001684A8 | `ClipFloorR` | `ClipWallAdjustPos` | 0x001683E8 |
| 0x001684C8 | `ClipFloorIH` | `ClipWallE` | 0x00168408 |
| 0x001684E8 | `ClipFloorCheckCB` | `ClipWallCheckCB` | 0x00168428 |
| 0x00168538 | `ChangeFieldCollisionDebugMode` | `ClipFloor` | 0x00168468 |
| 0x00168578 | `DrawCollision` | `ClipFloorR` | 0x001684A8 |
| 0x00168598 | `ClipPlane` | `ClipFloorIH` | 0x001684C8 |
| 0x001685B8 | `GetOrientOfWall` | `ClipFloorCheckCB` | 0x001684E8 |
| 0x00168650 | `fzShowV` | `ChangeFieldCollisionDebugMode` | 0x00168538 |
| 0x001686D8 | `fzMagnitude2f` | `DrawCollision` | 0x00168578 |
| 0x001687B8 | `fzMagnitude3f` | `ClipPlane` | 0x00168598 |
| 0x0016A1D8 | `func_0016A1D8` | `fzShowV` | 0x00168650 |
| 0x0016A2A0 | `func_0016A2A0` | `fzMagnitude2f` | 0x001686D8 |
| 0x0016A2C8 | `func_0016A2C8` | `fzMagnitude3f` | 0x001687B8 |
| 0x0016A2F8 | `func_0016A2F8` | `fzMagnitudefv` | 0x001688E0 |
| 0x001760F0 | `jimakuManager` | `afterGirlHand` | 0x00175640 |
| 0x00176130 | `jimakuUndisp` | `afterGirlPulledGo` | 0x00175688 |
| 0x00176398 | `func_00176398` | `iosCdvdBackGroundReadJimaku` | 0x001758F8 |
| 0x001763F8 | `func_001763F8` | `jimakuHandler` | 0x00175A98 |
| 0x001769D0 | `func_001769D0` | `jimakuMgrJump` | 0x00175C70 |
| 0x00176AA0 | `func_00176AA0` | `jimakuMgrEnd` | 0x00175C90 |
| 0x00176AE8 | `func_00176AE8` | `jimakuBegin` | 0x00175CB0 |
| 0x00176B08 | `func_00176B08` | `jimakuNext` | 0x00175CE0 |
| 0x00176B38 | `_FUNC_GetWay_begin` | `jimakuJump` | 0x00175DC0 |
| 0x00177260 | `GetWay_begin` | `avoid_obstacle2` | 0x00176BB8 |
| 0x001779F0 | `BridgeBox` | `create_box_bridge` | 0x00176BC8 |
| 0x00177CA0 | `DeleteGuideWay` | `GetWay_next` | 0x00176CE8 |
| 0x001782B0 | `visible_waypoint_of_all_except_gid` | `GetNearNigePointN` | 0x00176DE0 |
| 0x00178908 | `visible_waypoint_of_all_except_gid_ThreadVersion` | `GetWay_begin` | 0x00177260 |
| 0x00178930 | `visible_waypoint_of_all_except_temp_ThreadVersion` | `DeleteGuideWay` | 0x00177CA0 |
| 0x00178990 | `ez_line` | `visible_waypoint_of_all_except_gid` | 0x001782B0 |
| 0x00178B20 | `ez_circle` | `visible_waypoint_of_all_except_gid_ThreadVersion` | 0x00178908 |
| 0x00178CC8 | `short_direction_between_wp` | `visible_waypoint_of_all_except_temp` | 0x00178928 |
| 0x00178E78 | `wgid_next` | `visible_waypoint_of_all_except_temp_ThreadVersion` | 0x00178930 |
| 0x00179060 | `shortest_path` | `short_direction_between_wp` | 0x00178CC8 |
| 0x00179248 | `shortest_path_ThreadVersion` | `wgid_next` | 0x00178E78 |
| 0x00179438 | `GetWgAll` | `WayUtilWorkAlloc` | 0x00179040 |
| 0x00179558 | `set_check_wp` | `WayUtilWorkFree` | 0x00179050 |
| 0x001795B8 | `set_bridge` | `shortest_path` | 0x00179060 |
| 0x00179878 | `nearest_waypoint_of_group` | `shortest_path_ThreadVersion` | 0x00179248 |
| 0x00179B50 | `nearest_waypoint` | `GetWgAll` | 0x00179438 |
| 0x00179E10 | `nearest_waypoint_from_gobj` | `set_check_wp` | 0x00179558 |
| 0x00179F68 | `nearest_waypoint_by_lineseg_of_group` | `set_bridge` | 0x001795B8 |
| 0x0017A230 | `nearest_waypoint_by_lineseg` | `nearest_waypoint_of_group` | 0x00179878 |
| 0x0017A2C8 | `nearest_waypoint_by_lineseg_of_group_from_gobj` | `nearest_waypoint` | 0x00179B50 |
| 0x0017A368 | `nearest_waypoint_by_lineseg_from_gobj` | `nearest_waypoint_from_gobj` | 0x00179E10 |
| 0x0017A410 | `waypoint_with_range` | `nearest_waypoint_by_lineseg_of_group` | 0x00179F68 |
| 0x0017A4C0 | `nearest_waypoint_of_all_except_group` | `nearest_waypoint_by_lineseg` | 0x0017A230 |
| 0x0017A578 | `nearest_waypoint_of_all_not_bridge_except_group` | `nearest_waypoint_by_lineseg_of_group_from_gobj` | 0x0017A2C8 |
| 0x0017A638 | `nearest_waypoint_of_all` | `nearest_waypoint_by_lineseg_from_gobj` | 0x0017A368 |
| 0x0017A6F8 | `visible_waypoint_of_all` | `waypoint_with_range` | 0x0017A410 |
| 0x0017A788 | `visible_waypoint_of_all_from_gobj` | `nearest_waypoint_of_all_except_group` | 0x0017A4C0 |
| 0x0017A830 | `visible_waypoint` | `nearest_waypoint_of_all_not_bridge_except_group` | 0x0017A578 |
| 0x0017A910 | `visible_waypoint_from_gobj` | `nearest_waypoint_of_all` | 0x0017A638 |
| 0x0017A9B8 | `get_wp_nearest_bridge_side_me` | `visible_waypoint_of_all` | 0x0017A6F8 |
| 0x0017AB20 | `waybridge_between_group` | `visible_waypoint_from_gobj` | 0x0017A910 |
| 0x0017AC48 | `bridge_waypoint_side_me` | `get_wp_nearest_bridge_side_me` | 0x0017A9B8 |
| 0x0017ADF8 | `waypoint_connect_group_side_bridge` | `waybridge_between_group` | 0x0017AB20 |
| 0x0017AE98 | `NearestWgFromTarget` | `bridge_waypoint_side_me` | 0x0017AC48 |
| 0x0017B038 | `func_0017B038` | `waypoint_connect_group_side_bridge` | 0x0017ADF8 |
| 0x0017B080 | `func_0017B080` | `NearestWgFromTarget` | 0x0017AE98 |
| 0x0017B230 | `func_0017B230` | `gflagChk` | 0x0017B358 |
| 0x0017B258 | `func_0017B258` | `gflagOn` | 0x0017B398 |
| 0x0017B288 | `func_0017B288` | `gflagOff` | 0x0017B3F8 |
| 0x0017B318 | `gflagLoad` | `scpSetCageVelocityFriction` | 0x0017CBE8 |
| 0x0017B358 | `gflagChk` | `scpPlayMotDir` | 0x0017CC80 |
| 0x0017B528 | `func_0017B528` | `scpPlayStart` | 0x0017D030 |
| 0x0017B568 | `func_0017B568` | `scpPlayEnd` | 0x0017D098 |
| 0x0017B5A0 | `func_0017B5A0` | `scpTrans` | 0x0017D0D0 |
| 0x0017B5B0 | `func_0017B5B0` | `scpTriggerBallTargetMan` | 0x0017D0F8 |
| 0x0017C990 | `func_0017C990` | `scpKillSpiderGroup` | 0x0017D9E0 |
| 0x0017CA58 | `func_0017CA58` | `scpDispOnAllWithKind` | 0x0017DCD8 |
| 0x0017CAA0 | `func_0017CAA0` | `scpActivateAllWithKind` | 0x0017DD60 |
| 0x0017FCF8 | `func_0017FCF8` | `actConte12Jimaku` | 0x0017E160 |
| 0x00180550 | `func_00180550` | `BoySekikaTexScroll` | 0x0017E240 |
| 0x00181F38 | `func_00181F38` | `brainAddLevelGirl` | 0x001823F0 |
| 0x00182868 | `brainStatusDefaultSet` | `brainGetLevel` | 0x00182AB8 |
| 0x00182958 | `brainGetTarget` | `brainInitGirlSet` | 0x00182BE8 |
| 0x00182D20 | `DispCameraGroup` | `EnterMenu` | 0x00182BF8 |
| 0x00183968 | `dispCameraGroupType2` | `DispCameraGroup` | 0x00182D20 |
| 0x001848B0 | `menuGroupEdit` | `dispCameraGroupType2` | 0x00183968 |
| 0x001869F8 | `_CameraEdit_del_box` | `test_camedit` | 0x00185668 |
| 0x00186A10 | `_CameraEdit_del_pin` | `_CameraEdit_del_box` | 0x001869F8 |
| 0x00186B68 | `CameraEdit_add_box` | `_CameraEdit_del_pin` | 0x00186A10 |
| 0x00186CE8 | `CameraEdit_add_pin` | `CameraEdit_add_box` | 0x00186B68 |
| 0x00186FD0 | `CameraEdit_del_box` | `CameraEdit_add_pin` | 0x00186CE8 |
| 0x00187280 | `CameraEdit_del_pin` | `CameraEdit_del_box` | 0x00186FD0 |
| 0x001872B8 | `CameraEdit_DispBox` | `CameraEdit_del_pin` | 0x00187280 |
| 0x00187308 | `CameraEdit_Save` | `CameraEdit_Reflect` | 0x00187300 |
| 0x00187318 | `debug_NMarker` | `CameraEdit_Save` | 0x00187308 |
| 0x00187328 | `debug_Marker` | `debug_NMarker` | 0x00187318 |
| 0x001873B0 | `debug_CameraEditor` | `InitCameraEditor` | 0x001873A8 |
| 0x001873C0 | `CameraSetCameraSet` | `debug_CameraEditor` | 0x001873B0 |
| 0x00188228 | `AddPluralCameraSet` | `CameraSetCameraSet` | 0x001873C0 |
| 0x001882B0 | `GetPluralCameraSet` | `GetRootPositionForCamera` | 0x00187570 |
| 0x00188550 | `GetSizeOfCameraSetBinary` | `ico2camera_GetGroupNearest` | 0x001877E0 |
| 0x0018B180 | `func_0018B180` | `GetCameraGroupFromPosition` | 0x00188220 |
| 0x0018B620 | `func_0018B620` | `GetSizeOfCameraSetBinary` | 0x00188550 |
| 0x0018B700 | `func_0018B700` | `SetWSMatrix` | 0x0018B9D0 |
| 0x0018BE78 | `ConvertCameraSet` | `DebugCameraManual` | 0x0018C078 |
| 0x0018BEB0 | `MakeCameraMatrix` | `DebugCameraSemiAuto` | 0x0018C0A8 |
| 0x0018BF70 | `CameraEditManual` | `BackToGameCamera` | 0x0018C210 |
| 0x0018C078 | `DebugCameraManual` | `GetCameraInfomationFromGlobalPosition` | 0x0018CA78 |
| 0x0018CA78 | `GetCameraInfomationFromGlobalPosition` | `Camctrl_ExitEveRock` | 0x0018CB10 |
| 0x0018CAD8 | `SetCameraMatrix` | `GetCameraDefaultTargetGObj` | 0x0018CBE0 |
| 0x0018DDF0 | `InitChainGeo` | `chain_simulate_term` | 0x0018D7D0 |
| 0x0018DFF8 | `ChainGeo` | `correct_vector` | 0x0018DB90 |
| 0x0018E188 | `ChainDL` | `pendulum_Process` | 0x0018DD80 |
| 0x00190478 | `eBrainProcess` | `GetRootPositionHandExtra` | 0x001903B8 |
| 0x00190B30 | `func_00190B30` | `eBrainProcess` | 0x00190478 |
| 0x00190F30 | `func_00190F30` | `eBrainGetTarget` | 0x00190620 |
| 0x001918A8 | `func_001918A8` | `eBrainInit` | 0x00190638 |
| 0x001918F0 | `func_001918F0` | `eBrainStatusSet` | 0x00190648 |
| 0x00191B70 | `func_00191B70` | `eBrainGetTargetGeneratorFromLabelStage` | 0x00190698 |
| 0x00191C80 | `func_00191C80` | `EnemyCtrlBeforeFunc` | 0x00191D20 |
| 0x00191D08 | `func_00191D08` | `InitEnemyCtrlGeo` | 0x00191D70 |
| 0x00191D20 | `EnemyCtrlBeforeFunc` | `IsSelectID_EnemyCtrl` | 0x00191F50 |
| 0x00191F50 | `IsSelectID_EnemyCtrl` | `fightSoundProcess` | 0x00192088 |
| 0x00192050 | `fightSoundProcessMain` | `fightSoundClose` | 0x00192098 |
| 0x001940B0 | `_OrientGV` | `GetMatrixDirectionToZ` | 0x00193A00 |
| 0x00194218 | `_FrontGV` | `_InterRotGV` | 0x00193A58 |
| 0x00194360 | `RotateAccordingToStick_PatternThree` | `_DistxzSqGV` | 0x00193A78 |
| 0x00194440 | `SetLimitHandCameraCorrect` | `_MoveGV` | 0x00193DC0 |
| 0x00194590 | `func_00194590` | `_AbsRotyGV` | 0x00193EC8 |
| 0x001945B8 | `func_001945B8` | `_ApplyRyGV` | 0x00193EE0 |
| 0x00194808 | `func_00194808` | `_OrientGV` | 0x001940B0 |
| 0x00194840 | `func_00194840` | `_FrontGV` | 0x00194218 |
| 0x00194EA8 | `func_00194EA8` | `SetLimitHandCameraCorrect` | 0x00194440 |
| 0x00195208 | `func_00195208` | `before_DrawPolygon` | 0x00195378 |
| 0x00195350 | `func_00195350` | `before_DrawLine` | 0x00195510 |
| 0x00195380 | `after_DrawPolygon` | `DrawPolygon` | 0x001956E8 |
| 0x00195510 | `before_DrawLine` | `IsPointIsInScreen` | 0x00195A40 |
| 0x00195588 | `after_DrawLine` | `interp_vector_sa` | 0x00197080 |
| 0x001977A8 | `GatherEffect_Set` | `GatherEffect_InqEnd` | 0x00197818 |
| 0x0019C010 | `queenBallBeforeFunc` | `queen_barrier_set_damage` | 0x0019C558 |
| 0x0019C028 | `InitQueenBallGeo` | `makeRefractST` | 0x0019C798 |
| 0x0019C558 | `queen_barrier_set_damage` | `queen_barrier_disp_init` | 0x0019C9A0 |
| 0x0019C798 | `makeRefractST` | `queen_barrier_anim` | 0x0019CBB8 |
| 0x0019C7D0 | `queen_barrier_disp_proc` | `GetStageDifferenceMatrix` | 0x0019CF70 |
| 0x0019C9A0 | `queen_barrier_disp_init` | `StageOrientGet2` | 0x0019CF78 |
| 0x0019CBB8 | `queen_barrier_anim` | `OtherStagePositionGet` | 0x0019CF88 |
| 0x0019CE40 | `func_0019CE40` | `StageOrientGet` | 0x0019D580 |
| 0x0019CF88 | `OtherStagePositionGet` | `readMpeg` | 0x0019D9D0 |
| 0x0019D278 | `StageOrientInit` | `initAll` | 0x0019D9D8 |
| 0x0019D580 | `StageOrientGet` | `termAll` | 0x0019D9E8 |
| 0x0019D678 | `func_0019D678` | `movie_init` | 0x0019DA98 |
| 0x0019D960 | `switchThread` | `movie_proc` | 0x0019DB08 |
| 0x0019DA98 | `movie_init` | `readBufBeginPut` | 0x0019DBC8 |
| 0x0019DB08 | `movie_proc` | `readBufBeginGet` | 0x0019DBF0 |
| 0x0019DB50 | `free_buffer` | `readBufEndGet` | 0x0019DD38 |
| 0x0019DE10 | `strFileRead` | `videoCallback` | 0x0019E2D0 |
| 0x0019E4F8 | `voBufIncCount` | `voBufReset` | 0x0019E4E0 |
| 0x0019E508 | `voBufGetData` | `voBufIsFull` | 0x0019E4E8 |
| 0x0019E520 | `voBufGetTag` | `voBufIncCount` | 0x0019E4F8 |
| 0x0019E598 | `initGeometryState` | `voBufGetData` | 0x0019E508 |
| 0x0019E5D0 | `initMatrixDObj` | `voBufGetTag` | 0x0019E520 |
| 0x0019EB88 | `initPolygonState` | `initMatrixDObj` | 0x0019E5D0 |
| 0x0019F4E8 | `func_0019F4E8` | `LinkParentOfDObj` | 0x0019EF58 |
| 0x0019F6A8 | `stop_free_resources` | `stage_initialize` | 0x0019F758 |
| 0x0019F758 | `stage_initialize` | `exit_stage` | 0x0019F7A8 |
| 0x0019F8F8 | `start_stage_Load_thread` | `stgmgrNextStagePreLoad` | 0x0019FB30 |
| 0x0019FB30 | `stgmgrNextStagePreLoad` | `stgmgrNextStagePreLoadEntry` | 0x0019FC78 |
| 0x001A07F8 | `backStageLoad` | `routeSetPos` | 0x001A0090 |
| 0x001A1008 | `func_001A1008` | `backStageProcessInit` | 0x001A0A38 |
| 0x001A2D58 | `debug_Assert` | `GetPObjAddress` | 0x001A2AB0 |
| 0x001A2E10 | `debug_LogPrintf` | `debug_openLog` | 0x001A2D78 |
| 0x001A3C38 | `debug_PrintCharacter` | `debug_makeBackImage` | 0x001A3980 |
| 0x001A3DD8 | `debug_PrintFont` | `debug_PrintCharacter` | 0x001A3C38 |
| 0x001A40C8 | `debug_FlushFontWindow` | `debug_PrintFont` | 0x001A3DD8 |
| 0x001A4220 | `debug_FlushFont` | `debug_FlushFontWindow` | 0x001A40C8 |
| 0x001A43F8 | `draw_shikaku` | `draw_batsu` | 0x001A43F0 |
| 0x001A4520 | `debug_brainBar` | `draw_shikaku` | 0x001A43F8 |
| 0x001A4A10 | `debug_DrawBar` | `debug_MakeBarString` | 0x001A46A0 |
| 0x001A5AD0 | `debug_WriteBMP` | `debug_ResizeSnapShot` | 0x001A5970 |
| 0x001AC4B8 | `ParentSimpleObjGeo` | `initLineTraceTable` | 0x001A6848 |
| 0x001AC688 | `ParentSimpleObjDL` | `traceLine` | 0x001A6A30 |
| 0x001ACA28 | `InitParentSimpleObjGeo` | `dispSource` | 0x001A6AA0 |
| 0x001ADA08 | `func_001ADA08` | `debug_TargetGObj` | 0x001A9B28 |
| 0x001ADB70 | `func_001ADB70` | `init_debug_menu` | 0x001A9D88 |
| 0x001AE370 | `func_001AE370` | `gamesysNObjInfoInit` | 0x001AB170 |
| 0x001AE3E8 | `func_001AE3E8` | `gamesysObjInfoStageInitPosSaveUnlock` | 0x001AB1B8 |
| 0x001AE9A8 | `func_001AE9A8` | `gamesysVersionLoad` | 0x001ABF58 |
| 0x001AE9F0 | `func_001AE9F0` | `gamesysVersionSave` | 0x001ABF80 |
| 0x001AF9C8 | `kanbanReqAdd` | `DispIcoMisc` | 0x001AE830 |
| 0x001AFB98 | `kanbanInit` | `kanbanReqAdd` | 0x001AF9C8 |
| 0x001B0200 | `kanbanReqDel` | `fade_exec` | 0x001AFE50 |
| 0x001B04E0 | `kanbanReqAllDel` | `kanbanReqDel` | 0x001B0200 |
| 0x001B0518 | `kanbanReqAllDelFade` | `kanbanReqDelFade` | 0x001B0348 |
| 0x001B0538 | `kanbanExec` | `kanbanReqAllDel` | 0x001B04E0 |
| 0x001B0570 | `func_001B0570` | `kanbanReqAllDelFade` | 0x001B0518 |
| 0x001B05A8 | `func_001B05A8` | `kanbanExec` | 0x001B0538 |
| 0x001B0A38 | `func_001B0A38` | `kanbanBootInit` | 0x001B0AB0 |
| 0x001B0AC0 | `kanbanBootStart` | `_la_mcard_error_check` | 0x001B4BF8 |
| 0x001B0F18 | `func_001B0F18` | `_la_set_current_port_2` | 0x001B4E78 |
| 0x001B1270 | `func_001B1270` | `_la_set_current_port_lock_2` | 0x001B4EC0 |
| 0x001B1438 | `func_001B1438` | `_la_set_current_port_new` | 0x001B4EF0 |
| 0x001B7298 | `initWayData` | `GetRealModelId` | 0x001B7250 |
| 0x001B7F20 | `test_nextstage_firstwalk_set` | `HotInitSceneObjects` | 0x001B76F8 |
| 0x001B7FC8 | `GetStageStartInfo` | `ChangeStageStartInfo` | 0x001B7B88 |
| 0x001B80B0 | `func_001B80B0` | `MoveNextStage_Set` | 0x001B7CE0 |
| 0x001B8110 | `staffRollStart` | `test_nextstage_firstwalk_set` | 0x001B7F20 |
| 0x001B8120 | `staffRollScroll` | `GetStageStartInfo` | 0x001B7FC8 |
| 0x001B81A8 | `staffRollNameOut` | `MoveNextStage_Clear` | 0x001B7FE8 |
| 0x001B8210 | `staffRollWide` | `staffRollScroll` | 0x001B8120 |
| 0x001B84C8 | `func_001B84C8` | `staffRollMain` | 0x001B81B8 |
| 0x001B86C0 | `InitAP1` | `staffRollWide` | 0x001B8210 |
| 0x001BB7E0 | `func_001BB7E0` | `IsActCharDead` | 0x001BA770 |
| 0x001BB8C0 | `InitAttackCheckBoundaryGeo` | `SetActressLight` | 0x001BA880 |
| 0x001BBE50 | `CreateAttackCheckBoundary` | `InitAttackCheckBoundaryGeo` | 0x001BB8C0 |
| 0x001BBEA0 | `GetAttackCheckBoundaryManagerStatus` | `AttackCheckBoundaryGeo` | 0x001BB988 |
| 0x001BBF78 | `switchReleaseSE` | `actAttackCheckBoundaryStart` | 0x001BBDD8 |
| 0x001BE558 | `initFloating` | `avoidCharGObj` | 0x001BE120 |
| 0x001BED00 | `execFallDown` | `_checkItemBreak` | 0x001BE6A8 |
| 0x001BF6A0 | `MoveBoxWithHoldPoint` | `_checkItemCollision` | 0x001BF2C8 |
| 0x001C0790 | `SetSwitchTriggerFunc` | `BoxGeoRestore` | 0x001C06A0 |
| 0x001C0D60 | `func_001C0D60` | `initParentize` | 0x001C0AD8 |
| 0x001C16A8 | `InitBoyGeo` | `LightLineDL` | 0x001C1380 |
| 0x001C33D8 | `ChandelierDL` | `ChandelierGeo` | 0x001C3338 |
| 0x001C34C0 | `func_001C34C0` | `actClipCollisionCore` | 0x001C3760 |
| 0x001C3970 | `CreateClipCollisionManagerGObj` | `GetChainExWeightGlobalPos` | 0x001C4A28 |
| 0x001C3988 | `RequestClipCollision` | `bindExWeight` | 0x001C55F0 |
| 0x001C3E08 | `thStart` | `bind2` | 0x001C58C0 |
| 0x001C4150 | `func_001C4150` | `calc2` | 0x001C5BA0 |
| 0x001C48F8 | `TestDispChainAnimation` | `SetChainExtendedWeight` | 0x001C6090 |
| 0x001C4A28 | `GetChainExWeightGlobalPos` | `GetClothAnimation` | 0x001C62D0 |
| 0x001C55F0 | `bindExWeight` | `clipCylinderCollision` | 0x001C63C8 |
| 0x001C6090 | `SetChainExtendedWeight` | `DispMeshWire` | 0x001C8218 |
| 0x001C62D0 | `GetClothAnimation` | `DispCloth4D` | 0x001C8478 |
| 0x001C9338 | `func_001C9338` | `draw` | 0x001C9DE8 |
| 0x001C9640 | `func_001C9640` | `drawHT` | 0x001CADE0 |
| 0x001C9B30 | `func_001C9B30` | `renderViewCoordZSphere` | 0x001CB910 |
| 0x001CB910 | `renderViewCoordZSphere` | `SetDarkVolumeEffect` | 0x001CBB98 |
| 0x001CBB98 | `SetDarkVolumeEffect` | `InitGameOverEffect` | 0x001CBD78 |
| 0x001CBE88 | `dispCircle2` | `_dispParam` | 0x001CBD88 |
| 0x001CC470 | `dispEffectToolField` | `dispXZYZCircle` | 0x001CBE78 |
| 0x001CC838 | `EditTarget` | `dispCircle2` | 0x001CBE88 |
| 0x001CCAC0 | `moveEffectToolGeometry` | `dispEffectToolField` | 0x001CC470 |
| 0x001CCD98 | `execEffectTool` | `EditTarget` | 0x001CC838 |
| 0x001CD0B8 | `setEnemyObject` | `moveEffectToolGeometry` | 0x001CCAC0 |
| 0x001CE690 | `EnemySetfAppearAll` | `EnemyDL` | 0x001CDE30 |
| 0x001CE6F0 | `EnemySetfDisappearAll` | `DemoMotionGeo` | 0x001CE028 |
| 0x001CE8F0 | `SetEnemyHitGeometryAction` | `enemySetParticleDie` | 0x001CE760 |
| 0x001CEA00 | `UpdatePointBlur` | `EnemyDeleteParticle` | 0x001CE818 |
| 0x001CED80 | `func_001CED80` | `UpdatePointBlur` | 0x001CEA00 |
| 0x001CF770 | `func_001CF770` | `DispEnemyFootPrints` | 0x001CEBC0 |
| 0x001CF790 | `func_001CF790` | `InitPointBlur` | 0x001CEBF0 |
| 0x001CF8D0 | `func_001CF8D0` | `DispPointBlur` | 0x001CEC00 |
| 0x001CF930 | `func_001CF930` | `UpdateEnemyEye` | 0x001CEC30 |
| 0x001CF998 | `InitFlagGeo` | `DispEnemyEye` | 0x001CEC60 |
| 0x001CFA20 | `FlagGeo` | `ResetEnemyEye` | 0x001CEC88 |
| 0x001D03A0 | `func_001D03A0` | `DispFlyInfo` | 0x001D03E0 |
| 0x001D03C8 | `func_001D03C8` | `InitFlyInfo` | 0x001D03E8 |
| 0x001D1A98 | `SetGirlClothDispSwitch` | `GirlDL` | 0x001D17F8 |
| 0x001D2548 | `bombSparkSE` | `bombSparkStartSE` | 0x001D2540 |
| 0x001D2650 | `HoldItem` | `avoidInsideOfWall` | 0x001D26C8 |
| 0x001D4228 | `func_001D4228` | `Draw2DLine` | 0x001D3D40 |
| 0x001D4348 | `SetLodLevel` | `Draw2DLineSeg_Start` | 0x001D3D70 |
| 0x001D4358 | `func_001D4358` | `Draw2DLineSeg_Loop` | 0x001D3D80 |
| 0x001D43F8 | `func_001D43F8` | `Draw2DLineG` | 0x001D3D98 |
| 0x001D45B0 | `func_001D45B0` | `_getLine` | 0x001D3DB0 |
| 0x001D49C0 | `func_001D49C0` | `DrawLine` | 0x001D3DD8 |
| 0x001D4A58 | `func_001D4A58` | `DrawLineG` | 0x001D3E80 |
| 0x001D4BD0 | `func_001D4BD0` | `pursueNodeList` | 0x001D4E30 |
| 0x001D4E88 | `InitMotionMemorySize` | `dispSquare2` | 0x001D8AB0 |
| 0x001D8968 | `func_001D8968` | `findActPoint` | 0x001D8BA8 |
| 0x001D8AB0 | `dispSquare2` | `checkActPointWithHeight` | 0x001D8C40 |
| 0x001D8BA8 | `findActPoint` | `clearCollisionStatus` | 0x001D8CF0 |
| 0x001D8C40 | `checkActPointWithHeight` | `checkUpperWallState` | 0x001D8E40 |
| 0x001D8CF0 | `clearCollisionStatus` | `checkWallSideState` | 0x001D92E0 |
| 0x001D8E40 | `checkUpperWallState` | `checkWallState` | 0x001D9890 |
| 0x001E0860 | `func_001E0860` | `SkelTest` | 0x001DC720 |
| 0x001E2370 | `getStreamMotionGeometry` | `ForTest_ForceShiftMotion` | 0x001E10F0 |
| 0x001E4700 | `func_001E4700` | `SetParallelMotionTableWithNoRequest` | 0x001E3E20 |
| 0x001E4798 | `func_001E4798` | `InitMotionOrient` | 0x001E3FC8 |
| 0x001E4938 | `setMotionSpeed` | `ExecutePauseSlipProc` | 0x001E4548 |
| 0x001E4970 | `dispProgressBar` | `setRootUpdateMode` | 0x001E4868 |
| 0x001E4988 | `objMenuProc` | `dispProgressBar` | 0x001E4970 |
| 0x001E5AF8 | `func_001E5AF8` | `lookAtTest` | 0x001E54E0 |
| 0x001E6968 | `func_001E6968` | `InitMoveColTestGeo` | 0x001E6960 |
| 0x001E6D68 | `execParticleEffect` | `setParticleEffectGeometry` | 0x001E6C30 |
| 0x001E80D8 | `SetParticleEffectGeometry` | `dispParticleEffect` | 0x001E6DA0 |
| 0x001E8930 | `InitParticleEffects` | `SetParticleEffectPackage` | 0x001E8618 |
| 0x001E8B48 | `func_001E8B48` | `SetParticleEffect` | 0x001E73A8 |
| 0x001E8BD8 | `DeleteParticleEffectsByID` | `GetParticleEffectPackage` | 0x001E8AB8 |
| 0x001E8EB8 | `func_001E8EB8` | `InitParticleLayoutGeo` | 0x001E8D30 |
| 0x001E9888 | `InitRopeFixGeo` | `RopeFixGeo` | 0x001E9808 |
| 0x001EBB70 | `func_001EBB70` | `InitStageMultiBgaManager` | 0x001EBCD0 |
| 0x001EC2E0 | `func_001EC2E0` | `copyAlphaChannelOfWork0ToFeedBackArea` | 0x001EE0E8 |
| 0x001ECA40 | `func_001ECA40` | `testAA` | 0x001EE860 |
| 0x001ECB98 | `func_001ECB98` | `subWork1ToCurrentFB` | 0x001EEF08 |
| 0x001ED4C8 | `func_001ED4C8` | `pasteBackLightShadowToFB` | 0x001EF508 |
| 0x001ED608 | `func_001ED608` | `makeMaskPatternToWork2` | 0x001EF600 |
| 0x001ED6F8 | `blur` | `makeFullScreenFlareBefore` | 0x001EF770 |
| 0x001EFA60 | `func_001EFA60` | `InitStormPackage` | 0x001EF980 |
| 0x001EFD18 | `func_001EFD18` | `ClipStormByVolume` | 0x001EF988 |
| 0x001EFEE0 | `func_001EFEE0` | `ClipStormByCamera` | 0x001EF990 |
| 0x001F0858 | `func_001F0858` | `PlayStreamMotion` | 0x001F0B20 |
| 0x001F0B20 | `PlayStreamMotion` | `_transRingBuf` | 0x001F0F98 |
| 0x001F16A0 | `func_001F16A0` | `InitSugiLeafGeo` | 0x001F1240 |
| 0x001F2320 | `func_001F2320` | `actWaySystemCore` | 0x001F22E0 |
| 0x001F3A28 | `calcDynamicGeometry` | `dispInsectNet` | 0x001F4228 |
| 0x001F4668 | `LightTorchOffOfWeapon` | `drawSenpuukiHaneUnit` | 0x001F4950 |
| 0x001F4FE8 | `InitWindManager` | `ExecWindManager` | 0x001F4E68 |
| 0x001F5068 | `GetRegularizedWindSpeed` | `ReinitWindManager` | 0x001F4EE8 |
| 0x001F5140 | `func_001F5140` | `SetWindManager` | 0x001F4F68 |
| 0x001F51C0 | `func_001F51C0` | `InitWindManager` | 0x001F4FE8 |
| 0x001F5298 | `DispWireLetter` | `GetRegularizedWindSpeed` | 0x001F5068 |
| 0x001F5378 | `DispWireString` | `DispWireLetter` | 0x001F5298 |
| 0x001F54D0 | `DefaultColorWireString` | `DispWireString` | 0x001F5378 |
| 0x001F55D8 | `ChangeColorWireString` | `DefaultColorWireString` | 0x001F54D0 |
| 0x001F5608 | `Draw2DBox` | `ChangeColorWireString` | 0x001F55D8 |
| 0x001F5620 | `func_001F5620` | `Draw2DBox` | 0x001F5608 |
| 0x001F5700 | `func_001F5700` | `outerProcess` | 0x001F5B58 |
| 0x001F5828 | `func_001F5828` | `simulate` | 0x001F5D60 |
| 0x001F66A0 | `GetWormRoute` | `GetWormCaptureVector` | 0x001F69B0 |
| 0x001F6C20 | `matrix_init` | `dma_init` | 0x001F6AA0 |
| 0x001F6C88 | `malloc_MemCpy` | `matrix_init` | 0x001F6C20 |
| 0x001F6CB0 | `freeseki` | `mallocseki` | 0x001F6CA8 |
| 0x001F6D90 | `resetmallocseki` | `freeseki` | 0x001F6CB0 |
| 0x001F6DB8 | `reallocseki` | `mallocsekistage` | 0x001F6DB0 |
| 0x001F6E00 | `func_001F6E00` | `reallocseki` | 0x001F6DB8 |
| 0x001F88C0 | `bga_calcEnvelope` | `_RotTransCurrentMatrixYXZ` | 0x001F8B90 |
| 0x001FA598 | `bga_ResetCamera` | `bga_GetCameraMatrix` | 0x001FA5E0 |
| 0x001FAAB0 | `func_001FAAB0` | `font_CheckAlign` | 0x001FA898 |
| 0x001FB478 | `dl_Clear` | `font_GetWidth` | 0x001FAA30 |
| 0x001FB480 | `dl_Swap` | `font_GetHeight` | 0x001FAA40 |
| 0x001FB4A8 | `dl_PushPriority` | `font_Init` | 0x001FAA50 |
| 0x001FB5E0 | `dl_Debug` | `dl_Clear` | 0x001FB478 |
| 0x001FB658 | `dl_CloseDma` | `dl_Swap` | 0x001FB480 |
| 0x001FB880 | `dl_OpenDma` | `dl_Debug` | 0x001FB5E0 |
| 0x001FB8B8 | `dl_GetPri` | `dl_CloseDma` | 0x001FB658 |
| 0x001FB9F8 | `func_001FB9F8` | `dl_Out` | 0x001FB768 |
| 0x001FBA80 | `dpk_SwapBuffer` | `dl_SetDLPriority` | 0x001FB7F8 |
| 0x001FBAA8 | `dpk_Init` | `dl_OpenDma` | 0x001FB880 |
| 0x001FBB48 | `func_001FBB48` | `dpk_Init` | 0x001FBAA8 |
| 0x001FBC18 | `enemy_Initialize` | `dpk_CheckBufferSize` | 0x001FBB40 |
| 0x001FBC48 | `enemy_GetPositionTable` | `enemy_Initialize` | 0x001FBC18 |
| 0x001FBF88 | `func_001FBF88` | `enemy_GetPositionTable` | 0x001FBC48 |
| 0x001FBFC8 | `func_001FBFC8` | `cut_gobj_camera_dl_link` | 0x001FC048 |
| 0x001FC168 | `isysGObjRemoveCameraDL` | `isysGObjMoveCameraDL` | 0x001FC220 |
| 0x001FC1A0 | `func_001FC1A0` | `isysGObjLinkCameraDL` | 0x001FC278 |
| 0x002009F0 | `func_002009F0` | `GetCollisCenterPositionSimple` | 0x00141130 |
| 0x00203F18 | `func_00203F18` | `setMailTarget` | 0x002047E0 |
| 0x00203F48 | `func_00203F48` | `seMail` | 0x00204D70 |
| 0x002040C0 | `func_002040C0` | `seMailTargetDistCheck` | 0x00204E90 |
| 0x00204D70 | `seMail` | `NearestEnemyFromGirl` | 0x002056A8 |
| 0x00204E98 | `func_00204E98` | `CopyWpPos` | 0x002057C8 |
| 0x00204F58 | `func_00204F58` | `WayLengthOfGObj_Pos` | 0x00205808 |
| 0x00204FA8 | `func_00204FA8` | `WayLengthOfGObj_GObj` | 0x00205860 |
| 0x002052F8 | `func_002052F8` | `InitWayPointSystem` | 0x00205948 |
| 0x002056A8 | `NearestEnemyFromGirl` | `DeleteWayPoint` | 0x00205B70 |
| 0x00205788 | `NumOfWpPos` | `WayGroup_begin` | 0x00205CD0 |
| 0x002057C8 | `CopyWpPos` | `WayGroup_next` | 0x00205FE8 |
| 0x00205B70 | `DeleteWayPoint` | `group_create` | 0x00206208 |
| 0x00205CD0 | `WayGroup_begin` | `group_select` | 0x00206328 |
| 0x00205FE8 | `WayGroup_next` | `point_delete` | 0x00206568 |
| 0x002060E8 | `WayBridge_begin` | `point_insert` | 0x00206878 |
| 0x00206208 | `group_create` | `quick_load_wpfile` | 0x00206A90 |
| 0x00206328 | `group_select` | `ExtractWayData` | 0x00206D18 |
| 0x00206568 | `point_delete` | `wp_print_out` | 0x00206F38 |
| 0x00206878 | `point_insert` | `draw_way_group` | 0x00207018 |
| 0x00206A90 | `quick_load_wpfile` | `way_toolDL` | 0x002070B0 |
| 0x00207018 | `draw_way_group` | `point_nige` | 0x00207768 |
| 0x002070B0 | `way_toolDL` | `quick_save_wpfile` | 0x002078B8 |
| 0x00209908 | `func_00209908` | `actE3GateJimaku` | 0x0020A8C0 |
| 0x0020F720 | `actSt00aStair` | `actSubMpegReturnPreload` | 0x0020D2F0 |
| 0x00211BE8 | `actSt02aTakiWay` | `actSt02WaterFallBoySplashCheck` | 0x002113C8 |
| 0x00215108 | `actSt04bSekizo` | `actSt04aConte06Jimaku` | 0x002130A8 |
| 0x00228C70 | `actSt13aChainNG` | `actSt07aTsuroEffect` | 0x00223110 |
| 0x00231448 | `actSt19aChainUp` | `actSt13bConte02Jimaku` | 0x00229FF0 |
| 0x00231A98 | `actSt19aChainSwitch` | `actSt13b2Generator` | 0x0022A1B8 |
| 0x00232058 | `actSt20aEnd` | `actSt13cConte04Jimaku` | 0x0022B730 |
| 0x002330A0 | `actSt20aFenceUpChk` | `actSt13cConte05Jimaku` | 0x0022BB98 |
| 0x00233A98 | `actSt20aGondola` | `actSt13cHandJimaku` | 0x0022BDF0 |
| 0x0023EFF8 | `viBufReset` | `handler_endimage` | 0x0023D370 |
| 0x0023F0D8 | `viBufStopDMA` | `setGIFtag` | 0x0023D518 |
| 0x0023F130 | `viBufRestartDMA` | `setGIFad` | 0x0023D528 |
| 0x0023F160 | `viBufFlush` | `setTEXFLUSH` | 0x0023D5A8 |
| 0x0023F180 | `viBufModifyPts` | `setTEX1_1` | 0x0023D660 |
| 0x0023F200 | `viBufGetTs` | `setTEX0_1` | 0x0023D668 |
| 0x0023F350 | `viBufCount` | `setUV` | 0x0023D750 |
| 0x0023F7F0 | `CreateGObj` | `copy2area` | 0x0023D8A0 |
| 0x0023FB20 | `func_0023FB20` | `viBufReset` | 0x0023EFF8 |
| 0x0023FDA0 | `func_0023FDA0` | `viBufEndPut` | 0x0023F070 |
| 0x00240090 | `func_00240090` | `viBufStopDMA` | 0x0023F0D8 |
| 0x00240218 | `func_00240218` | `viBufRestartDMA` | 0x0023F130 |
| 0x00240600 | `func_00240600` | `viBufFlush` | 0x0023F160 |
| 0x00240650 | `func_00240650` | `viBufModifyPts` | 0x0023F180 |
| 0x002407C0 | `func_002407C0` | `viBufGetTs` | 0x0023F200 |
| 0x00240A20 | `func_00240A20` | `viBufCount` | 0x0023F350 |
| 0x00240C50 | `func_00240C50` | `InitCameraGObjs` | 0x0023F7E0 |
| 0x00240D40 | `func_00240D40` | `CreateGObj` | 0x0023F7F0 |
| 0x00240EA0 | `func_00240EA0` | `CreateGObjByFuncSet` | 0x0023F928 |
| 0x00240FC8 | `func_00240FC8` | `MakeBoundingBox` | 0x00240B60 |

## Skip census (twins never proposed)

* 923 — via=ordinal not norm_equal
* 354 — via=gap PAL name provisional-ordinal
* 193 — via=gap PAL same-hash class
* 47 — ntsc hand seed above banner

## TU trailers

* 471 trailers rewritten to the PAL attribution.
* 615 left alone: the PAL TU is a `src/cod/vendor_<PAL VMA>`
  name, i.e. an address-derived label that means nothing in the USA link.
* 39 left alone: the PAL TU has no subsegment in
  `config/ico.us.yaml`, so writing it would invent a file the tree does not
  split.  These are the honest disagreements:
  * 20 functions: ntsc says `ito/mpeg/mv_audiodec.c`, PAL says `src/stageSEProc.c`
  * 8 functions: ntsc says `ito/mpeg/mv_disp.c`, PAL says `src/stageSEProc.c`
  * 6 functions: ntsc says `src/objact.c`, PAL says `src/stageSEProc.c`
  * 3 functions: ntsc says `src/delayFreeManager.c`, PAL says `src/main.c`
  * 2 functions: ntsc says `src/cod/vendor_2418A0.c`, PAL says `src/vobj.c`

`config/ico.us.yaml` subsegment spans and names are untouched.

