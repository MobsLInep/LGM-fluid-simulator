Build Instructions (Windows)

- Install Ninja and CMake (winget install Ninja-build.Ninja, Kitware.CMake)
- Configure: & "C:\\Program Files\\CMake\\bin\\cmake.exe" -S lbm-fluid-simulator -B lbm-fluid-simulator/build -G Ninja -D CMAKE_CXX_COMPILER=g++
- Build: & "C:\\Program Files\\CMake\\bin\\cmake.exe" --build lbm-fluid-simulator/build --config Release
- Run: lbm-fluid-simulator\\build\\bin\\lbm-fluid-simulator.exe

Optional GPU

- Set -DENABLE_WEBGPU=ON after installing GLFW and wgpu-native; update CMake to link

 Manual Build (MSYS2 g++)

 - Ensure `C:\\msys64\\ucrt64\\bin\\g++.exe` is installed
 - Create `build/bin` directory
 - Compile simulator:
   - `C:\\msys64\\ucrt64\\bin\\g++.exe -std=c++17 -O2 src/core/application.cpp src/simulation/lbm_simulator.cpp src/gpu/renderer.cpp src/simulation/grid.cpp src/gpu/gpu_context.cpp src/main.cpp src/ui/visualization.cpp src/gpu/compute_pipeline.cpp src/gpu/buffer_manager.cpp -Isrc -o build/bin/lbm-fluid-simulator.exe -luser32 -lgdi32`
 - Compile tests:
   - `C:\\msys64\\ucrt64\\bin\\g++.exe -std=c++17 -O2 tests/test_vector.cpp -Isrc -o build/bin/test-vector.exe`
   - `C:\\msys64\\ucrt64\\bin\\g++.exe -std=c++17 -O2 tests/test_validation.cpp src/simulation/lbm_simulator.cpp src/simulation/grid.cpp src/gpu/buffer_manager.cpp -Isrc -o build/bin/test-validation.exe`
   - `C:\\msys64\\ucrt64\\bin\\g++.exe -std=c++17 -O2 tests/test_poiseuille.cpp src/simulation/lbm_simulator.cpp src/simulation/grid.cpp src/gpu/buffer_manager.cpp -Isrc -o build/bin/test-poiseuille.exe`
 - Run: `build/bin/*.exe`
