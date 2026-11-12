# Release verification

Nexus release 1.1 corresponds to plugin build 0.1.11.

- The x64 DLL built successfully and exports the three expected SKSE entry points.
- The camera motion and orbit tests passed.
- The Nexus ZIP's DLL matched the compiled DLL. SHA-256: 73222276f71bb5d34267d55a2c69bf3bdafdb68fe4e0bc83de7ccebd29a95fb6.
- The Steam 1.6.1170 log recorded a roughly −35° inherited FOV offset in a bow-zoom test and 0° in an unzoomed test, with the same starting orbit distance. This confirms the test exercised both inputs; the log does not verify the final rendered image.
- Skyrim SE 1.5.97 is a build target and has not been verified in game. Reloading while free camera is active can still crash in some setups.
