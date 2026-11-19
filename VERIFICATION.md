# Free Death Camera 1.2.1 validation

## Observed regression

The November 18, 2026 1.2.0 log from Skyrim 1.6.1170 showed all five hook-target
checks passing, followed by `Camera interface validation failed; no camera hooks
installed`. No hooks-installed message followed. The log did not distinguish
missing instances from a vtable mismatch, so the precise instance condition is
unknown. The broad startup gate definitively prevented installing the controls.
The failed installed DLL hash matched the packaged 1.2.0 DLL.

## Fix

Class-level hooks no longer depend on live camera instances at DataLoaded,
restoring the working 1.1 installation approach. Hook-target, console-handler and
FOV storage validation remain. Post-load/new-game callbacks retry installation
when needed; the installed flag prevents double hooking. Live-camera readiness
and mismatched vtables are logged after loading, separately from installation.
No camera motion, orbit, handoff, input settings or runtime allowlist was changed.

Targets remain Steam 1.5.97, 1.6.1170, 1.7.99/1.7.104 and GOG 1.6.1179.
The optional orbit-obstruction patch is still conditional on a safe unique match.

## Checks and limits

November 18 build: all five CTest checks passed. The compiled DLL passed x64,
export/version metadata, actual Query acceptance for all five targets, and
unsupported/editor rejection checks.

CameraMotion, OrbitRotation, Compatibility and RuntimeLayouts cover the existing
algorithms, signature matching, memory checks and runtime/accessor routing.
StartupInstallation guards against reintroducing a live-instance dependency in
class hook installation. DLL verification exercises actual Query acceptance and
unsupported/editor rejection, and checks loader metadata.
These checks do not run Skyrim or prove a particular engine ABI.

## In-game verification — November 18, 2026

The user confirmed that 1.2.1 restored working camera behavior on Steam Skyrim
1.6.1170. The session log showed all five hook targets validated, the conditional
orbit-obstruction retry hook installed, and `Death camera and tfc hooks installed`.
Both Free and Bleedout camera instances were ready after loading. Repeated death
orbit and free-camera toggle cycles were recorded without warnings or errors.

This confirms the startup fix on 1.6.1170. Logs alone do not verify every visual
camera axis. In-game testing remains pending for Steam 1.5.97, 1.7.99/1.7.104 and
GOG 1.6.1179. The existing precaution to exit free camera before loading saves
remains.

November 19 repository verification: a clean build using the bundled dependency
sources passed all five CTest checks and the compiled-DLL compatibility verifier.
This rebuild was not separately tested in game.
