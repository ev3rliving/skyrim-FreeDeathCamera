# Free Death Camera AE

[Free Death Camera AE on Nexus Mods](https://www.nexusmods.com/skyrimspecialedition/mods/193983).

Install with your mod manager and restart Skyrim through SKSE. Replace the previous Free Death Camera AE files and disable any separate Numpad + TFC shortcut to avoid double toggles. If you customized PostmortemTFC.ini, keep your existing settings.

Requires matching [SKSE](https://skse.silverlock.org/) and [Address Library](https://www.nexusmods.com/skyrimspecialedition/mods/32444). The DLL targets Steam 1.6.1170 and SE 1.5.97. The main test environment was 1.6.1170; 1.5.97 behavior has not been verified in game.

- Move the mouse to orbit after death or during supported ragdoll and get-up states. Use the wheel or W/S to zoom, and the mouse buttons to roll.
- Numpad + toggles free camera. After death, entering free camera preserves the orbit camera's position and viewing direction.
- Death orbit starts at a consistent distance and clears inherited bow zoom. Adjust the starting distance with DeathOrbitDistance in PostmortemTFC.ini.
- Use DeathReloadDelaySeconds to set the automatic death reload delay. AliveSpeedPercent=100 keeps Skyrim's normal living free-camera movement speed.

Exit free camera before loading a save if you encounter a crash. The plugin does not support time freeze via tfc 1 after death.

Nexus release 1.1 packages plugin build 0.1.11. The DLL and its log retain that internal version.

Original [Free Death Camera](https://www.nexusmods.com/skyrim/mods/69791) by gp160 (Iron Armor). Third-party dependency licenses are included.

## Build the source

Use Visual Studio 2022 x64 C++, the Windows SDK, and CMake 3.24+. Run Build.ps1 from PowerShell.
