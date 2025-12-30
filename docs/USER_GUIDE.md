User Guide

 Run

 - Launch `build/bin/lbm-fluid-simulator.exe`; it runs 200 frames
 - Logs include per-stage timings, density/velocity extrema, clamp counts, and MLUPS
 - An impulse is injected at frame 10 at the domain center

 Controls

 - Window opens via Win32; rendering is CPU RGBA blit
 - No mouse interaction in CPU baseline; input stubs are present for future GPU mode

 Validation

 - With CMake: `ctest --test-dir build -C Release --output-on-failure`
 - Manual runs: execute `build/bin/test-vector.exe`, `test-validation.exe`, `test-poiseuille.exe`
