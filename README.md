# Free Death Camera — 1.2.1 universal

[Free Death Camera AE on Nexus Mods](https://www.nexusmods.com/skyrimspecialedition/mods/193983).

One DLL targets Steam Skyrim **1.5.97, 1.6.1170, 1.7.99/1.7.104**, and **GOG 1.6.1179**. This update is based on release 1.1 (internal build 0.1.11). The DLL and log now report 1.2.1 consistently. Version 1.2.1 was tested in game on Steam 1.6.1170; other listed runtimes still need in-game verification. Future unreviewed runtimes and VR are rejected.

## Install

Install `Free-Death-Camera-1.2.1.zip` through your mod manager, replacing the previous version. Keep only one `PostmortemTFC.dll` enabled. Retain your existing `PostmortemTFC.ini` if customized. Disable a separate Numpad + TFC shortcut to avoid double toggles.

Requires SKSE and Address Library matching your exact executable, plus the Microsoft Visual C++ v14 x64 runtime. No ESP, behavior generation or other camera plugin is required.

## Controls and retained behavior

- Move the mouse to orbit after death or during supported ragdoll/get-up states; use the wheel or W/S to zoom and mouse buttons to roll.
- Numpad + toggles free camera. After death, entering free camera preserves the orbit position and viewing direction.
- Death orbit starts at a consistent distance and clears inherited bow zoom. Configure `DeathOrbitDistance` in the INI.
- `DeathReloadDelaySeconds` controls automatic reload delay. `AliveSpeedPercent=100` retains normal living free-camera movement speed.

The existing limitation remains: loading a save while free camera is active can crash in some setups; exit free camera before loading. `tfc 1` after death remains unsupported.

## 1.2.1 startup fix

Version 1.2.0 could abort installation at DataLoaded when its live camera-interface check failed. Version 1.2.1 installs the validated class-level hooks as 1.1 did, retries after save/new-game loading if necessary, and logs live camera readiness separately. The mouse, orbit, zoom, roll and TFC behavior is retained.

## Startup validation

The log is `Documents/My Games/Skyrim Special Edition/SKSE/PostmortemTFC.log` (the game's SKSE log folder).
Look for the exact runtime, five successful camera hook validations, class-level hook/console/FOV validation, and `Death camera and tfc hooks installed`.

The orbit-obstruction retry patch uses the signature from 1.1, originally verified on 1.6.1170. It is only applied if a unique matching instruction sequence is found in readable Skyrim executable memory and the call target is executable. Otherwise a warning is logged and the engine's orbit reset check remains active; orbit behavior may differ until that runtime is tested. Executable memory checks cannot prove a function's ABI.

## Project folders

- `src`, `tests`, `config`: current source, regression tests and settings.
- `dependencies`, `licenses`: matching dependency sources and notices.
- `release/1.2.1`: generated install and complete-source archives with checksums (not tracked in Git).

## Build

Use an x64 MSVC 2022 developer shell, Windows SDK, CMake 3.24+ and Ninja. Run `./Build.ps1`. Dependency sources are included; no developer-specific paths are required. The optional `-PortableToolsRoot` argument supports the local portable toolchain.

With Windows Python and `pefile` installed, run `python verify_compatibility.py` to inspect the compiled DLL and exercise Query/runtime rejection. It never invokes supported-runtime Load outside Skyrim. Run `python package_release.py` to package install and complete-source ZIPs.

## Credits and licensing

Original [Free Death Camera](https://www.nexusmods.com/skyrim/mods/69791) by gp160 (Iron Armor). Modern CommonLibSSE-NG 13.1.0 snapshot: `12d61f3c39f7d4ba1b1ab543df2bca0e613dc747`.

This CommonLib-linked distribution includes GPLv3 text in `COPYING.txt` and the applicable CommonLib exceptions in `EXCEPTIONS.md`. Retain all original/third-party notices and provide corresponding source when distributing the DLL. Dependency licenses are included under `licenses` and `dependencies`.
