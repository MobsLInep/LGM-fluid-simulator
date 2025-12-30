LBM Fluid Simulator (CPU baseline)

Overview

- Implements D2Q9 LBM on CPU with BGK collision, pull-streaming, bounce-back walls
- GPU/WebGPU and GLFW scaffolding are stubbed; enable later via ENABLE_WEBGPU
- Provides per-stage timing and simple console visualization metrics

 Build

 - CMake/Ninja
   - `cmake -S . -B build -G Ninja`
   - `cmake --build build --config Release`
   - Run: `build/bin/lbm-fluid-simulator.exe`
 - Manual (MSYS2 g++)
   - `C:\msys64\ucrt64\bin\g++.exe -std=c++17 -O2 src/core/application.cpp src/simulation/lbm_simulator.cpp src/gpu/renderer.cpp src/simulation/grid.cpp src/gpu/gpu_context.cpp src/main.cpp src/ui/visualization.cpp src/gpu/compute_pipeline.cpp src/gpu/buffer_manager.cpp -Isrc -o build/bin/lbm-fluid-simulator.exe -luser32 -lgdi32`
   - Run: `build/bin/lbm-fluid-simulator.exe`

 Tests

 - CMake: `ctest --test-dir build -C Release --output-on-failure`
 - Manual: build test binaries then run
   - `C:\msys64\ucrt64\bin\g++.exe -std=c++17 -O2 tests/test_vector.cpp -Isrc -o build/bin/test-vector.exe`
   - `C:\msys64\ucrt64\bin\g++.exe -std=c++17 -O2 tests/test_validation.cpp src/simulation/lbm_simulator.cpp src/simulation/grid.cpp src/gpu/buffer_manager.cpp -Isrc -o build/bin/test-validation.exe`
   - `C:\msys64\ucrt64\bin\g++.exe -std=c++17 -O2 tests/test_poiseuille.cpp src/simulation/lbm_simulator.cpp src/simulation/grid.cpp src/gpu/buffer_manager.cpp -Isrc -o build/bin/test-poiseuille.exe`
   - Run: `build/bin/test-*.exe`

Next

- Integrate wgpu-native + GLFW to run kernels on GPU
- Bind WGSL shaders (shaders/) to compute pipelines
