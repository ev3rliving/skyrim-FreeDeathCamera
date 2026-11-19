# Changelog

## 1.2.1 — November 18, 2026

- Fixed the 1.2.0 startup regression that could leave all camera controls inactive
  after logging `Camera interface validation failed; no camera hooks installed`.
- Restored class-level hook installation without requiring live camera objects at
  DataLoaded. Retained hook-target, console-handler and FOV storage validation.
- Retry installation after save/new-game loading if it did not complete earlier.
- Added post-load camera readiness diagnostics and a startup regression check.
- Retained the same universal runtime targets and original camera controls/settings.
- Verified in game on Steam 1.6.1170: camera hooks installed and repeated death
  orbit/free-camera cycles logged without warnings or errors. Other targets still
  require in-game verification.

## 1.2.0 — November 17, 2026

- One DLL targeting Steam Skyrim 1.5.97, 1.6.1170, 1.7.99/1.7.104 and GOG 1.6.1179.
- Updated CommonLib runtime handling and Address Library format-5 support.
- Added camera hook/interface validation and clearer runtime diagnostics.
- Bounded the optional orbit-obstruction signature scan and validate its call target
  before patching. Unrecognized/unsafe signatures leave the engine check unchanged.
- Retained release 1.1's camera motion, orbit, handoff, hotkey and configuration behavior.
- Superseded by 1.2.1 after a startup regression was confirmed on 1.6.1170.

## 1.1

Original archived release, corresponding to internal build 0.1.11.
