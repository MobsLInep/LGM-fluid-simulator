<h1 align="center">LGM-fluid-simulator</h1>
<p align="center">Experience real-time, high-fidelity fluid dynamics simulations, empowering engineers and artists with powerful visualization and analysis tools.</p>

<p align="center">
  <img alt="Build Status" src="https://img.shields.io/badge/build-passing-brightgreen?style=flat-square">
  <img alt="License" src="https://img.shields.io/github/license/MobsLInep/LGM-fluid-simulator?style=flat-square">
  <img alt="PRs Welcome" src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square">
  <img alt="GitHub Stars" src="https://img.shields.io/github/stars/MobsLInep/LGM-fluid-simulator?style=social">
</p>

---

## The Strategic "Why"

> Accurate and efficient fluid dynamics simulations are often computationally intensive, resource-demanding, and require specialized knowledge, hindering rapid prototyping and accessible visualization across diverse applications from scientific research to game development. Traditional solutions frequently sacrifice either fidelity or performance, creating a significant barrier for innovation.

LGM-fluid-simulator provides a robust, real-time C++ framework for simulating complex fluid behaviors, democratizing access to high-performance fluid dynamics for researchers, game developers, and VFX artists alike. Its modular design and efficient GPU-accelerated algorithms deliver both precision and responsiveness, enabling rapid iteration and deeper insights into fluid phenomena without the steep learning curve or prohibitive computational cost.

## Key Features

✨ **Real-time Fluid Dynamics**: Experience instantaneous feedback with high-performance, real-time simulation capabilities, perfect for interactive applications and rapid prototyping.

🚀 **GPU-Accelerated Rendering**: Leverage modern shader technology to render stunning, physically accurate fluid visualizations with exceptional detail and speed.

⚙️ **Customizable Simulation Parameters**: Fine-tune fluid properties, boundary conditions, and interaction forces to model a wide range of scenarios, from turbulent flows to viscous liquids.

🧪 **Modular & Extensible Architecture**: Designed with C++ best practices, the codebase is easy to understand, modify, and extend, allowing developers to integrate custom solvers or visualization techniques.

🎯 **Comprehensive Test Suite**: Ensure reliability and accuracy with a dedicated suite of unit and integration tests, guaranteeing consistent performance and correct behavior.

📈 **Optimized for Performance**: Built from the ground up for efficiency, ensuring smooth operation even with complex fluid systems and high-resolution simulations.

## Technical Architecture

The LGM-fluid-simulator project is engineered for performance and extensibility, leveraging a modern C++ foundation and a well-defined build system.

| Technology | Purpose                               | Key Benefit                                     |
| :--------- | :------------------------------------ | :---------------------------------------------- |
| C++        | Core simulation logic, high-performance | Speed, memory control, system-level access      |
| CMake      | Build system automation               | Cross-platform compilation, dependency management |
| OpenGL     | Graphics rendering, GPU acceleration  | Real-time visualization, hardware utilization   |
| GLSL       | Shader programming                    | Customizable visual effects, GPU compute        |
| Git        | Version control                       | Collaborative development, history tracking     |

### Project Structure

```
📁 LGM-fluid-simulator/
├── 📄 .gitignore
├── 📄 CMakeLists.txt
├── 📁 docs/
│   └── ... (Documentation files)
├── 📁 shaders/
│   ├── 📄 fluid.frag
│   ├── 📄 fluid.vert
│   └── ... (Other shader files)
├── 📁 src/
│   ├── 📄 main.cpp
│   ├── 📄 FluidSimulator.cpp
│   ├── 📄 FluidSimulator.h
│   └── ... (Core source files)
└── 📁 tests/
    ├── 📄 TestFluidSolver.cpp
    └── ... (Unit and integration tests)
```

## Operational Setup

### Prerequisites

Before you begin, ensure you have the following installed on your system:

*   **C++ Compiler**: GCC, Clang, or MSVC (supporting C++17 or later).
*   **CMake**: Version 3.10 or higher.
*   **Git**: For cloning the repository.
*   **OpenGL Development Libraries**: Typically `freeglut-dev` or `mesa-common-dev` on Linux, Xcode Command Line Tools on macOS, or Visual Studio with Desktop development with C++ workload on Windows.

### Installation

Follow these steps to get your local copy of LGM-fluid-simulator up and running:

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/YOUR_USERNAME/LGM-fluid-simulator.git
    cd LGM-fluid-simulator
    ```

2.  **Create a build directory and configure CMake**:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3.  **Build the project**:
    ```bash
    make -j$(nproc) # Use -j<number_of_cores> for parallel compilation
    ```
    *   On Windows with MSVC, use `cmake --build . --config Release`

4.  **Run the simulator**:
    ```bash
    ./LGM-fluid-simulator
    ```
    *   On Windows, the executable might be found in `build/Release/LGM-fluid-simulator.exe`.

## Community & Governance

### Contributing

We welcome contributions from the community to enhance LGM-fluid-simulator! To contribute:

1.  **Fork** the repository.
2.  **Create a new branch** for your feature or bug fix: `git checkout -b feature/your-feature-name` or `bugfix/issue-description`.
3.  **Make your changes**, ensuring code quality and adherence to existing coding standards.
4.  **Add/update tests** as appropriate for your changes.
5.  **Commit your changes** with a clear and descriptive message.
6.  **Push your branch** to your forked repository.
7.  **Open a Pull Request** against the `main` branch of the original repository, detailing your changes and their benefits.

Please ensure your pull requests are well-documented and pass all existing tests.

### License

This project is licensed under the **MIT License**.

Refer to the `LICENSE` file in the root of the repository for full details. In summary, the MIT License is a permissive free software license, meaning you are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software, provided the original copyright notice and permission notice are included in all copies or substantial portions of the Software. The software is provided "as is," without warranty of any kind.
