# `src/` — recovered ICO source

Game code — actor logic, render pipeline, scene/file management.

**83 file(s)** recovered from `__FILE__` literals in `baserom/baseelf.elf` `.rodata`. Each placeholder records its anchor vma — the address of the literal that lets us tie a `.text` function back to this TU.

See `../source_tree.md` for the full recovery method.

## Player AI

- `boy.c` — anchor 0x00618838
- `boyact.c` — anchor 0x005582c8
- `girl.c` — anchor 0x00618ef8
- `girlForceField.c` — anchor 0x00618f08
- `girl_act.c` — anchor 0x00559780
- `girl_brain_main.c` — anchor 0x00559528
- `girl_brain_attract.c` — anchor 0x00559620

## Enemy AI

- `enemy.c` — anchor 0x00618cf0
- `enemyParts.c` — anchor 0x00618db0
- `enemy_act.c` — anchor 0x00558e10
- `EnemyInit.c` — anchor 0x0061ac70
- `ebrain.c` — anchor 0x0055ae08
- `itou_boss.c` — anchor 0x0055c178
- `queen.c` — anchor 0x0055c690
- `spider.c` — anchor 0x0061a040
- `spiderGroupManager.c` — anchor 0x0061a1f8
- `worm.c` — anchor 0x0061a880

## World objects

- `box.c` — anchor 0x006186a0
- `cage.c` — anchor 0x00618848
- `candle.c` — anchor 0x00618858
- `chain.c` — anchor 0x0055aa90
- `flag.c` — anchor 0x00618dc8
- `item.c` — anchor 0x00618f68
- `kanban.c` — anchor 0x00616ca8
- `rope.c` — anchor 0x00619ee0
- `rotObject.c` — anchor 0x00619fc8
- `switch.c` — anchor 0x00618630
- `sugiTree.c` — anchor 0x0061a6d8
- `torch.c` — anchor 0x0061a6e8
- `weapon.c` — anchor 0x0061a850

## Combat

- `attackhit.c` — anchor 0x0055a518
- `attackCheckBoundary.c` — anchor 0x006185e8
- `fightSound.c` — anchor 0x0055ae88
- `fieldCollision.c` — anchor 0x005591f0
- `moveColTest.c` — anchor 0x00619d98

## Animation

- `BgAnimation.c` — anchor 0x0061a8d8
- `StageAnimation.c` — anchor 0x00555bf8
- `motionManager.c` — anchor 0x006192e0
- `motionManager2.c` — anchor 0x00553ca0
- `motionOrientManager.c` — anchor 0x006197d0
- `motionViewer.c` — anchor 0x00619c00
- `streamMotionManager.c` — anchor 0x0061a668
- `multiBgaManager.c` — anchor 0x00619dc8
- `clothAnimation.c` — anchor 0x00618930
- `clothTest.c` — anchor 0x00618960
- `particleEffect.c` — anchor 0x00619e08
- `particleLayout.c` — anchor 0x00619ec0

## Render pipeline (PS2-specific)

- `DObj.c` — anchor 0x00612620
- `PObj.c` — anchor 0x0062e010
- `DisplayList.c` — anchor 0x0061ab88
- `DmaPacket.c` — anchor 0x0061ac60
- `Packet.c` — anchor 0x00554fd0
- `RegistPacket.c` — anchor 0x00555650
- `Light.c` — anchor 0x00554ca8
- `Texture.c` — anchor 0x00555ed8
- `Primitive.c` — anchor 0x00555490
- `Basic.c` — anchor 0x0061a8a8
- `layout_texture.c` — anchor 0x00617218
- `geometryManager.c` — anchor 0x00553ad0
- `lodManager.c` — anchor 0x00619060

## Core / system

- `FileManager.c` — anchor 0x00554040
- `delayFreeManager.c` — anchor 0x00553ab8
- `pool.c` — anchor 0x00553de0
- `sceneManager.c` — anchor 0x006172e0
- `debug.c` — anchor 0x006149a8
- `jimaku.c` — anchor 0x00559b88
- `staffroll.c` — anchor 0x00617378
- `icoMisc.c` — anchor 0x00616988
- `commonact.c` — anchor 0x00558860
- `charFileManager.c` — anchor 0x00612a70

## Generators / scripting

- `generator.c` — anchor 0x0055aea0
- `act.c` — anchor 0x0061afa0
- `act-env.c` — anchor 0x0061ae10
- `act-game.c` — anchor 0x00557f00
- `act-parallel-control.c` — anchor 0x005581b8
- `mail-add-data.c` — anchor 0x0055af08

## Camera

- `camera-editor.c` — anchor 0x0055a5c0
- `camera-ico2.c` — anchor 0x0055a940

## Misc / unsorted

- `a_p_1.c` — anchor 0x00618550
- `act_bird.c` — anchor 0x0055afd8
- `way_tool.c` — anchor 0x0061b7c0
- `way_util.c` — anchor 0x00559da0
- `stormTest.c` — anchor 0x0061a470
